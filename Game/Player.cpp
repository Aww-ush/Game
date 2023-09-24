#include <iostream>
#include "Player.h"
#include "Board.h"
using namespace std;

// count the total points position are A10 where A is row abd 10 is column
bool Player::Move(int row, int column, char colour)
{
	// i want this fucntion to be overloaded in human calss
	try
	{

		// first move
		//if (!CalculateMove()) {
		//	cout << "Internal Server Error: Player::Move -> CalculateMove" << endl;
		//	return false;
		//}
		if (isFirstMoveMaker() && GetTotalMoves() == 0)
		{
			pair<int, int> center = _board->GetCenterOfBoard(); // remove this
			if (center.first != row) {
				cout << "The piece must be in the center of the board J10" << endl;
				return false;
			}  
			if (center.second != column) {
				cout << "The piece must be in the center of the board J10" << endl;
				return false;
			}
			if (!_board->InsertPiece(row, column, colour))
			{
				cout << "There was error placing first piece" << endl;
				return false;
			}
		}
		else if (isFirstMoveMaker() && GetTotalMoves() == 1)
		{
			if (!_board->IsSecondPieceValid(row, column))
			{
				cout << "Could not place the second piece to that position " << endl;
				cout << "The piece must be place on the 3 intersections away from the center" << endl;
				return false;
			}
			if (!_board->InsertPiece(row, column, colour))
			{
				cout << "Something went wrong while moving the piece" << endl;
				return false;
			}
		}
		else
		{
			if (!_board->InsertPiece(row, column, colour))
			{
				cout << "Something went wrong while moving the piece" << endl;
				return false;
			}
		}
		totalMoves++;
		return true;
	}
	catch (const std::exception& e)
	{
		std::cerr << e.what() << '\n';
		return false;
	}
}



int Player::GetTotalPoints()
{
	return totalPoints;
}



bool Player::IncreasePoint(int points)
{
	try
	{
		totalPoints += points;
		return true;
	}
	catch (const std::exception& e)
	{
		std::cerr << e.what() << '\n';
		return false;
	}
}

bool Player::SetTotalMoves(int number)
{
	try
	{
		totalMoves = number;
		return true;
	}
	catch (const std::exception& e)
	{
		std::cerr << e.what() << '\n';
		return false;
	}
}

bool Player::SetBoard(Board* board)
{
	try
	{
		_board = board;
		return true;
	}
	catch (const std::exception& e)
	{
		std::cerr << e.what() << '\n';
		return false;
	}
}

Board* Player::GetBoard()
{
	return _board;
}

bool Player::SetColour(char colour)
{
	try
	{
		_colour = colour;
		return true;
	}
	catch (const std::exception& e)
	{
		std::cerr << e.what() << '\n';
		return false;
	}
}


bool Player::SetFirstMoveMaker()
{
	try
	{
		isFirstMover = true;
		return true;
	}
	catch (const std::exception& e)
	{
		std::cerr << e.what() << '\n';
		cout << "Internal Server Error: Player::SetFirstMoveMaker()" << endl;
		return false;
	}
}

bool Player::Reset()
{
	try {
		this->SetTotalMoves(0);
		//this->IncreasePoint(0);
		this->SetTotalCapure(0);
	}
	catch (const std::exception& e)
	{
		std::cerr << e.what() << '\n';
		cout << "Internal Server Error: Player::SetFirstMoveMaker()" << endl;
		return false;
	}
}

bool Player::CalculateMove()
{
	try {
		int count = 0;
		for (int row = 0; row < _board->GetBoardSize(); row++)
		{
			for (int column = 0; column < _board->GetBoardSize(); column++)
			{
				if (this->_board->GetBoard()[row][column] == GetColour())
					count++;

			}
		}
		SetTotalMoves(count);
		return true;
	}
	catch (const std::exception& e)
	{
		std::cerr << e.what() << '\n';
		cout << "Internal Server Error: Player::CalculateMove()" << endl;
		return false;
	}
}

bool Player::isFirstMoveMaker()
{
	return isFirstMover;
}
int Player::GetTotalMoves() {
	return totalMoves;
}
char Player::GetColour() {
	return _colour;
}
int Player::GetTotalCapture()
{
	return totalCapture;
}

bool Player::SetTotalCapure(int number)
{
	try
	{
		totalCapture = number;
		return true;
	}
	catch (const std::exception& e)
	{
		std::cerr << e.what() << '\n';
		cout << "Internal Server Error: Player::SetTotalCapure(int number)" << endl;
		return false;
	}
}
