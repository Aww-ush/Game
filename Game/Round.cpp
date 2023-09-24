#include <iostream>
#include "Round.h"
#include <string>

using namespace std;
Round::Round(Player *human, Player *computer, Board *board)
{
    this->human = human;
    this->computer = computer;
    this->board = board;
    this->pointCounter = new PointCounter(this->board);
    this->strategy = new Strategy(this->board);
    this->doesPlayerWantToContinue = false;

}
bool Round::PlayRound()
{
    try
    {
        bool playRound = true;

        // Initialize the game based on the first mover
        InitializeGame();
        if (!PrintGameStatus())
        {
            cout << "Internal Server Error: Game status could not be printed" << endl;
            return false;
        }
        // Main game loop
        while (playRound)
        {
            if (nextMover == HUMAN_CHARACTER)
            {
                // Handle human's turn
                HandleHumanTurn();
                // check if human won
                if (GetPlayerWins() || human->GetTotalCapture() == CAPTURE_REQ_TO_WIN)
                {
                    AnnounceRoundWinner();

                    if (!PrintScores())
                    {
                        cout << "Internal Server Error: Scores could not be printed" << endl;
                    }

                    return false;
                }
            }
            else if (nextMover == COMPUTER_CHARACTER)
            {
                // Handle computer's turn
                HandleComputerTurn();
                if (GetPlayerWins() || human->GetTotalCapture() == CAPTURE_REQ_TO_WIN)
                {
                    AnnounceRoundWinner();
                    if (!PrintScores())
                    {
                        cout << "Internal Server Error: Scores could not be printed" << endl;
                    }
                    return false;
                }
                // check if compute won
            }

            // Print the current board and scores
            if (!PrintGameStatus())
            {
                cout << "Internal Server Error: Game status could not be printed" << endl;
                return false;
            }

            // Check if the game should continue
            if (!Continue()) {

                AnnounceRoundWinner();
                SetDoesPlayerWantToContinuetName(false);
                return false;
            }
        }

        return true;
    }
    catch (const std::exception& e)
    {
        std::cerr << e.what() << '\n';
        return false;
    }
}
// this method figures who to move first based on the colour of the piece
void Round::InitializeGame()
{
    if (human->GetColour() == 'W')
    {
        InitializeHumanFirst();
    }
    else
    {
        InitializeComputerFirst();
    }
}
// this method makes human do the first move and checks if the first move is in
// the center of the board
void Round::InitializeHumanFirst()
{
    string position;
    pair<int, int> numericalPosition;

    do
    {
        position = AskForPosition();
        numericalPosition = ConvertMoveToRowCol(position);
    } while (numericalPosition.first == -1 || numericalPosition.second == -1);
    // if it is not the center of the board ask to do it again
    while (!human->MakeMove(numericalPosition.first, numericalPosition.second))
    {
        cout << "Failed to make first move, you can only insert in center 'J10'" << endl;
        position = AskForPosition();
        numericalPosition = ConvertMoveToRowCol(position);
    }

    int tmpScore = pointCounter->CalculatePoint(numericalPosition.first, numericalPosition.second, human->GetColour());
    if (tmpScore > 0)
        human->IncreasePoint(tmpScore);
    SetNextMover(COMPUTER_CHARACTER);
}

void Round::InitializeComputerFirst()
{
    pair<int, int> numericalPosition = board->GetCenterOfBoard();

    while (!computer->MakeMove(numericalPosition.first, numericalPosition.second))
    {
        cout << "Failed to make first move by computer" << endl;
    }
    int tmpScore = pointCounter->CalculatePoint(numericalPosition.first, numericalPosition.second, computer->GetColour());
    if (tmpScore > 0)
        computer->IncreasePoint(tmpScore);

    SetNextMover(HUMAN_CHARACTER);
}

void Round::HandleHumanTurn()
{
    string position;
    pair<int, int> numericalPosition;

    do
    {
        if (this->board->IsBoardFull())
        {
            cout << "There is no place to insert any more piece" << endl;
            return;
        }
        position = AskForPosition();
        numericalPosition = ConvertMoveToRowCol(position);


    } while (!human->MakeMove(numericalPosition.first, numericalPosition.second));

    int tmpScore = pointCounter->CalculatePoint(numericalPosition.first, numericalPosition.second, human->GetColour());
    int capturePoint = pointCounter->CalculateCapture(numericalPosition.first, numericalPosition.second, human->GetColour());
    if(tmpScore > 0) 
        human->IncreasePoint(tmpScore);
    if (capturePoint > 0)
        human->SetTotalCapure(capturePoint);

    SetNextMover(COMPUTER_CHARACTER);

}

void Round::HandleComputerTurn()
{
    if (this->board->IsBoardFull())
    {
        cout << "There is no place to insert any more piece" << endl;
        return;
    }
    pair<int, int> numericalPosition = strategy->GenerateMove();

    while (!computer->MakeMove(numericalPosition.first, numericalPosition.second))
    {
        numericalPosition = strategy->GenerateMove();
    }
    // caculate scores
     int tmpScore = pointCounter->CalculatePoint(numericalPosition.first, numericalPosition.second, computer->GetColour());
     if (tmpScore > 0)
        computer->IncreasePoint(tmpScore);
    if (GetPlayerWins())
    {
        WinnerRoundMessage(computer->GetName());
        if (!PrintGameStatus())
        {
            cout << "Internal Server Error: HandleComputerTurn" << endl;
        }
    }
    SetNextMover(HUMAN_CHARACTER);

}

bool Round::PrintGameStatus()
{
    // Print board and scores
    board->PrintBoard();

    // Print scores
    if (!PrintScores())
    {
        cout << "Internal Server Error: Scores could not be printed" << endl;
        return false;
    }

    return true;
}


bool Round::AnnounceRoundWinner()
{

    try
    {
        string name = "";
       
        if (this->human->GetTotalPoints() > this->computer->GetTotalPoints())
            cout << WinnerRoundMessage("Human") << endl;
        else
            cout << WinnerRoundMessage("Computer") << endl;
        return true;
    }
    catch (const std::exception &e)
    {
        std::cerr << e.what() << '\n';
        cout << "Internal Server Error: Round::AnnounceRoundWinner()" << endl;
        return false;
    }
}

bool Round::RestGame()
{
    try
    {
        SetDoesPlayerWantToContinuetName(true);
        playerWins = false;
        return true;
    }
    catch (const std::exception& e)
    {
        std::cerr << e.what() << '\n';
        cout << "Internal Server Error: Round::RestGame()" << endl;

        return false;
    }
}

string Round::WinnerRoundMessage(string playerName)
{
    string message = playerName + " has won this match!!!";
    return message;
}

bool Round::Continue()
{
    try
    {
        char result;
        do {
            cout << "Do you want to continue? Y or N" << endl;
            cin >> result;
            result = toupper(result);
        } while (result != 'Y' && result != 'N');

        return result == 'Y' ? true : false;
    }
    catch (const std::exception &e)
    {
        std::cerr << e.what() << '\n';
        cout << "Internal Server Error";
        return false;
    }
}

void Round::SetNextMover(char player)
{
    nextMover = player;

}
pair<int, int> Round::ConvertMoveToRowCol(string position)
{
	// suppose the input is A10
    // this means that the first is col and row
    // to validate it check if it is alpha 
    if (!isalpha(position.at(0))) {

        return pair<int, int>(-1, -1);
    }
     
	char alphaCol = position.at(0);
    // realize that the row is form pottom up
	string alphaRow = position.substr(1);
	int col = alphaCol - 'A';
    int row = (board->GetBoardSize() - stoi(alphaRow));
	return pair<int, int>{row, col};

}
bool Round::GetPlayerWins()
{
    return pointCounter->isThereWinner();
}
void Round::SetPlayerWins(bool answer) {
    pointCounter->SetHasWon(answer);
}
bool Round::PrintScores()
{
    try {
        cout << "Human:" << endl;
        cout << "Capture pairs: " << human->GetTotalCapture() << endl;
        cout << "Score: " << human->GetTotalPoints() << endl;
        cout << endl << endl;
        cout << "Computer:" << endl;
        cout << "Capture pairs: " << computer->GetTotalCapture() << endl;
        cout << "Score: " << computer->GetTotalPoints() << endl;
        cout << endl << endl;
        
        cout << "Next player: ";
        if (this->nextMover == HUMAN_CHARACTER) {
            cout << "Human - ";
            if (human->GetColour() == board->GetWhitePiece()) {
                cout << "White" << endl;
            }
            else {
                cout << "Black" << endl;
            }
        }
        else {
            cout << "Computer - ";
            if (computer->GetColour() == board->GetWhitePiece()) {
                cout << "White" << endl;
            }
            else {
                cout << "Black" << endl;
            }
        }
        return true;
    }
    catch (const std::exception& e)
    {
        std::cerr << e.what() << '\n';
        cout << "Internal Server Error";
        return false;
    }
}


string Round::AskForPosition()
{
    string position;
    do {
        cout << "Where do you want to move you Piece ?" << endl;
        cin >> position;
    } while (position.size() < 2);
    string capitalPosition = "";
    for (char &c : position)
    {
        capitalPosition += toupper(c);
    }
    return capitalPosition;
}

bool Round::GetDoesPlayerWantToContinue()
{
    return doesPlayerWantToContinue;

}

bool Round::SetDoesPlayerWantToContinuetName(bool answer)
{
    try
    {
        this->doesPlayerWantToContinue = answer;
        return true;
    }
    catch (const std::exception& e)
    {
        std::cerr << e.what() << '\n';
        return false;
    }
}

