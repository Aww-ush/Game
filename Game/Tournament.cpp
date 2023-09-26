#include "Tournament.h"
#include <utility> 
#include "Serialization.h"
#include "Coin.h"
using namespace std;
// play round
//make round
// pass the strategy

Tournament::Tournament(Board* board, Player* human, Player* computer, bool isLoadedFromFile, char startingPlayer)
{
	this->board = board;
	this->human = human;
	this->computer = computer;
	this->pointCounter = new PointCounter(this->board);
	this->playNextRound = true;
	this->isLoaded = isLoadedFromFile;
	this->startingPlayer = startingPlayer;
}

bool Tournament::PlayRound()
{
	try {
		
		this->round = new Round(human, computer, board, isLoaded, startingPlayer);
		while (GetPlayNextRound()) {

			if (!board->PrintBoard()) {
				cout << "There was error printing board" << endl;
				return false;
			}
			if (totalRoundsPlayed > 0) {
				// this also because the reset Game was outside then the newly loaded board will be wiped
				if (!ResetGame()) {
					cout << "Internal Server error: Could not reset the board" << endl;
				}
				if (human->GetTotalPoints() > computer->GetTotalPoints())
				{

					human->SetColour(board->GetWhitePiece());
					computer->SetColour(board->GetBlackPiece());

				}
				else if(human->GetTotalPoints() < computer->GetTotalPoints()){
					computer->SetColour(board->GetWhitePiece());
					human->SetColour(board->GetBlackPiece());
				}
				else {
					cout << "The first player is decided by coin toss because it wa a time. Guess the side of coin H OR T!" << endl;
						char userChoice;
						cin >> userChoice;
						Coin* coin = new Coin();
						char humanColour, computerColour;
					if (coin->Toss())
					{
						if (coin->WinOrLose(userChoice))
						{
							cout << "You have won the toss please go first" << endl;
							human->SetColour(board->GetWhitePiece());
							computer->SetColour(board->GetBlackPiece());
						}
						else
						{
							cout << "Coumputer has won the toss you will go second" << endl;
							computer->SetColour(board->GetWhitePiece());
							human->SetColour(board->GetBlackPiece());
						}
					}

				}

			}
			if (!round->PlayRound()) {
				// one of the player wins the round
				if (round->GetPlayerWins()) {
					if (!SaveScore()) {
						cout << "Could not save score from tournament" << endl;
						return false;
					}
					totalRoundsPlayed++;
					//set the player wins flag off
					round->SetPlayerWins(false);

					if (!AskToPlayNewRound()) {
						cout << "Internal Server Error: Input could not be processed" << endl;
						return false;
					}
				}
				// human does not want to continue playing any more form inside the round
				// this is needed to haldile if the user because it returns false in two cases
				// when use dont want to play
				// next when there is internal server error
				else if (!round->GetDoesPlayerWantToContinue()) {
					totalRoundsPlayed++;
					if (!DisplayTotalScore()) {
						cout << "Internal Server Error: Scores could not be showed" << endl;
						return false;
					}
					if (!PrintWinner()) {
						cout << "Internal Server Error: Winner could not be showed" << endl;
						return false;
					}
					if (!SetPlayNextRound(false)) {
						cout << "Internal Server Error" << endl;
						return false;
					}
				}
				else {
					cout << "Internal Server Error" << endl;
					return false;
				}

			}
		}
		if (!AskToSaveGame()) {
			cout << "Internal Server Error: Input could not be processed" << endl;
			return false;
		}
		if (GetSave()) {
			if (!SaveGame()) {
				cout << "Internal Server Error: Game could not be saved" << endl;
				return false;
			}
		}
		cout << "Thank you for playing" << endl;
		return true;
	}
	catch (const std::exception& e)
	{
		std::cerr << e.what() << '\n';
		cout << "Internal Server Error Method:  Tournament::PlayRound()" << endl;
		return false;
	}
}

// prints the winner but if there is tie prints tie lol
bool Tournament::PrintWinner()
{

	try
	{
		if (human->GetTotalPoints() == computer->GetTotalPoints()) {
			cout << "Congratulations there was a tie" << endl;
		}
		else {
			cout << (human->GetTotalPoints() > computer->GetTotalPoints() ? "Human" : "Computer") << " has won this tournament!!!" << endl;

		}
		return true;
	}
	catch (const std::exception& e)
	{
		std::cerr << e.what() << '\n';
		cout << "Internal Server Error Method:  Tournament::PrintWinner()" << endl;
		return false;
	}
}
// this ask the uesr to play another round
// also sets the flag to play another to true or false based on the user`s choice
bool Tournament::AskToPlayNewRound()
{
	try
	{
		char result;
		do {
			cout << "Do you want to play another round? Y or N" << endl;
			cin >> result;
			result = toupper(result);
		} while (result != 'Y' && result != 'N');
		this->SetPlayNextRound((result == 'Y') ? true : false);
		return true;
	}
	catch (const std::exception& e)
	{
		std::cerr << e.what() << '\n';
		cout << "Internal Server Error Method:  Tournament::AskToPlayNewRound()" << endl;
		return false;
	}
}

bool Tournament::SetPlayNextRound(bool input)
{
	try {
		this->playNextRound = input;
		return true;
	}
	catch (const std::exception& e)
	{
		std::cerr << e.what() << '\n';
		cout << "Internal Server Error Method:  Tournament::AskToPlayNewRound()" << endl;
		return false;
	}
}

bool Tournament::GetPlayNextRound()
{
	return playNextRound;
}


bool Tournament::DisplayTotalScore()
{
	try {
		cout << "Total Human Score: " << human->GetTotalPoints() << endl;
		cout << "Total Computer Score: " << computer->GetTotalPoints() << endl;
		return true;
	}
	catch (const std::exception& e)
	{
		std::cerr << e.what() << '\n';
		cout << "Internal Server Error";
		return false;
	}
}

// this ask the uesr to play another round
// also sets the flag to play another to true or false based on the user`s choice to save

bool Tournament::AskToSaveGame()
{
	try
	{
		char result;
		do {
			cout << "Do you want to save the game? Y or N" << endl;
			cin >> result;
			result = toupper(result);
		} while (result != 'Y' && result != 'N');
		this->SetSave((result == 'Y') ? true : false);
		return true;
	}
	catch (const std::exception& e)
	{
		std::cerr << e.what() << '\n';
		cout << "Internal Server Error Method:  Tournament::AskToPlayNewRound()" << endl;
		return false;
	}
}
// return the flag which stores users choice to save or not save the file
bool Tournament::GetSave()
{
	return save;
}
// sets the flag to save or not save the game
bool Tournament::SetSave(bool answer)
{
	try {
		this->save = answer;
		return true;
	}
	catch (const std::exception& e)
	{
		std::cerr << e.what() << '\n';
		cout << "Internal Server Error";
		return false;
	}
}


// calls the serialization class to save the file
bool Tournament::SaveGame()
{
	try {
		Serialization* serializationObj = new Serialization(true);
		string nextPlayer, nextPlayerColour;
		if (round->GetNextMover() == HUMAN_CHARACTER) {
			nextPlayer = "Human";
			if (human->GetColour() == 'W') {
				nextPlayerColour = "White";
			}
			else {
				nextPlayerColour = "Black";
			}
		}
		else {
			nextPlayer = "Computer";
			if (computer->GetColour() == 'W') {
				nextPlayerColour = "White";
			}
			else {
				nextPlayerColour = "Black";
			}
				
		}
		if (!serializationObj->SaveGame(this->board, this->human, this->computer, nextPlayer, nextPlayerColour))
		{
			cout << "Internal Server Error: Tournament::SaveGame()"<< endl;
			return false;
		}
		cout << "Done Saving." << endl;
		return true;
	}
	catch (const std::exception& e)
	{
		std::cerr << e.what() << '\n';
		cout << "Internal Server Error: Tournament::SaveGame";
		return false;
	}
}
bool Tournament::ResetGame()
{
	try {
		if (!board->ResetBoard()) {
			cout << "Internal Server Error: board could not be reset" << endl;
			return false;
		}
		if (!human->Reset()) {
			cout << "Internal Server Error: human could not be reset" << endl;
			return false;
		}
		if (!computer->Reset()) {
			cout << "Internal Server Error: computer could not be reset" << endl;
			return false;
		}
		if (!this->round->RestGame()) {
			cout << "Internal Server Error: New round could not be processed" << endl;
			return false;
		}
		return true;
	}
	catch (const std::exception& e)
	{
		std::cerr << e.what() << '\n';
		cout << "Internal Server Error: Tournament::SaveGame";
		return false;
	}
}
bool Tournament::SaveScore() {
	try {
		this->human->IncreasePoint(human->GetTotalRoundPoints());
		this->computer->IncreasePoint(computer->GetTotalRoundPoints());
		
		return true;
	}
	catch (const std::exception& e)
	{
		std::cerr << e.what() << '\n';
		cout << "Internal Server Error: Tournament::SaveScore";
		return false;
	}
}
