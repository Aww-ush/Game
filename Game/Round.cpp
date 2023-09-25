#include <iostream>
#include "Round.h"
#include <string>

using namespace std;
Round::Round(Player *human, Player *computer, Board *board, bool isLoaded, char nextMover)
{
    this->human = human;
    this->computer = computer;
    this->board = board;
    this->pointCounter = new PointCounter(this->board);
    this->strategy = new Strategy(this->board);
    this->doesPlayerWantToContinue = false;
    this->isLoaded = isLoaded;
    this->nextMover = nextMover;
}
bool Round::PlayRound()
{
    try
    {
        bool playRound = true;
        if (isLoaded) {
            //calcute and set the code for this round for both human and computer
            // for now it is just dummy data ie 0
            int humanScore = pointCounter->CalculatedScoreInLoadedRound(human->GetColour());
            int computerScore = pointCounter->CalculatedScoreInLoadedRound(computer->GetColour());
            human->IncreaseRoundPoint(humanScore);
            computer->IncreaseRoundPoint(computerScore);
            cout << "The game was loaded" << endl;
            
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
                if (GetPlayerWins() || computer->GetTotalCapture() == CAPTURE_REQ_TO_WIN)
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
            if (!board->PrintBoard())
            {
                cout << "Internal Server Error: Scores could not be printed" << endl;
                return false;
            }
            // Check if the game should continue
            if (!Continue()) {
                if (!PrintScores())
                {
                    cout << "Internal Server Error: Scores could not be printed" << endl;
                }
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
    {
        human->IncreasePoint(tmpScore);
        human->IncreaseRoundPoint(tmpScore);
    }
    if (capturePoint > 0)
    {
        human->SetTotalCapure(capturePoint);
        human->IncreasePoint(capturePoint);
        human->IncreaseRoundPoint(capturePoint);
    }

    SetNextMover(COMPUTER_CHARACTER);

}

void Round::HandleComputerTurn()
{
    if (this->board->IsBoardFull())
    {
        cout << "There is no place to insert any more piece" << endl;
        return;
    }
    pair<int, int> numericalPosition = strategy->GenerateMove(computer->GetColour(), computer->GetTotalMoves(), computer->GetTotalPoints(), human->GetTotalPoints());

    while (!computer->MakeMove(numericalPosition.first, numericalPosition.second))
    {
        numericalPosition = strategy->GenerateMove(computer->GetColour(), computer->GetTotalMoves(), computer->GetTotalPoints(), human->GetTotalPoints());
    }
    // caculate scores
     int tmpScore = pointCounter->CalculatePoint(numericalPosition.first, numericalPosition.second, computer->GetColour());
     int capturePoint = pointCounter->CalculateCapture(numericalPosition.first, numericalPosition.second, computer->GetColour());
     if (tmpScore > 0)
     {
         computer->IncreasePoint(tmpScore + capturePoint);
         computer->IncreaseRoundPoint(tmpScore + capturePoint);
     }
     if (capturePoint > 0)
     {
         computer->SetTotalCapure(capturePoint);
         computer->IncreasePoint(capturePoint);
         computer->IncreaseRoundPoint(capturePoint);
     }
    SetNextMover(HUMAN_CHARACTER);

}



bool Round::AnnounceRoundWinner()
{

    try
    {
        if (this->human->GetTotalRoundPoints() > this->computer->GetTotalRoundPoints())
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
        human->IncreaseRoundPoint(0);
        computer->IncreaseRoundPoint(0);
        human->SetTotalCapure(0);
        computer->SetTotalCapure(0);
        playerWins = false;
        isLoaded = false;
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

