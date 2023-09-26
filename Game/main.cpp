#include <iostream>
#include "Board.h"
#include "Player.h"
#include "Coin.h"
#include "Human.h"
#include "Computer.h"
#include "Round.h"
#include "PointCounter.h"
#include "Tournament.h"
#include "Serialization.h"
using namespace std;


bool AskToLoadGame()
{
	try
	{
		char result;
		do {
			cout << "Do you want to load the game? Y or N" << endl;
			cin >> result;
			result = toupper(result);
		} while (result != 'Y' && result != 'N');
		bool reply = (result == 'Y') ? true : false;
		return reply;
	}
	catch (const std::exception& e)
	{
		std::cerr << e.what() << '\n';
		cout << "Internal Server Error Method:  Tournament::AskToPlayNewRound()" << endl;
		return false;
	}
}
int main()
{
	static const char WHITE_PIECE = 'W';
	static const char BLACK_PIECE = 'B';
	// start the serialization19
	if (AskToLoadGame()) {
		Serialization* serializationObj = new Serialization();
		//set board
		Board* boardPtr = new Board(serializationObj->GetBoard());
		Player* humanPlayer = new Human(boardPtr, serializationObj->GetHumanColour(), serializationObj->GetHumanScore(), serializationObj->GetHumanCapturePoints(), serializationObj->GetComputerCapturePoints());
		Player* computerPlayer = new Computer(boardPtr, serializationObj->GetComputerColour(), serializationObj->GetComputerScore(), serializationObj->GetComputerCapturePoints(), serializationObj->GetHumanCapturePoints());
		PointCounter* pointCounter = new PointCounter(boardPtr);
		Tournament* tournament = new Tournament(boardPtr, humanPlayer, computerPlayer, true, serializationObj->GetNextMover());
		if (!tournament->PlayRound())
		{
			cout << "Bye-bye!" << endl;
		}
	}
	else {
		Board* boardPtr = new Board();

		cout << "The first player is decided by coin toss. Guess the side of coin H OR T!" << endl;
		char userChoice;
		cin >> userChoice;
		Coin* coin = new Coin();
		char humanColour, computerColour;
		if (coin->Toss())
		{
			if (coin->WinOrLose(userChoice))
			{
				cout << "You have won the toss please go first" << endl;
				humanColour = WHITE_PIECE;
				computerColour = BLACK_PIECE;
			}
			else
			{
				cout << "Coumputer has won the toss you will go second" << endl;
				humanColour = BLACK_PIECE;
				computerColour = WHITE_PIECE;
			}
		}
		Player* humanPlayer = new Human(boardPtr, humanColour);
		Player* computerPlayer = new Computer(boardPtr, computerColour);
		PointCounter* pointCounter = new PointCounter(boardPtr);
		char startingPlayer = (humanColour == WHITE_PIECE) ? 'H' : 'C';
		Tournament* tournament = new Tournament(boardPtr, humanPlayer, computerPlayer, false, startingPlayer);
		if (!tournament->PlayRound())
		{
			cout << "Do you want to save the game?" << endl;
		}
	}

	return 0;
}
