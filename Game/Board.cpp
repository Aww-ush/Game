#include "Board.h"
#include <iostream>
#include <string>
#include <vector>
#include <utility>
// constructor
using namespace std;

// insert a piece with colour colur at specific row and column
bool Board::InsertPiece(int row, int column, char pieceType)
{
    try
    {
        if (!isWithInBoard(row))
        {
            cout << "the row is not within the board" << endl;
            return false;
        }
        if (!isWithInBoard(column))
        {
            cout << "the column is not within the board " << endl;
            return false;
        }
        if (!IsPieceValid(pieceType))
        {
            cout << "the piece is not of valid colour" << endl;
            return false;
        }
        if (!IsPositionEmpty(row, column)) {
            cout << "the position is not empty" << endl;
            return false;
        }
        _board[row][column] = pieceType;
        //if (!PrintBoard()) {
        //    cout << "There was error printing board" << endl;
        //    return false;
        //}
        return true;
    }
    catch (const std::exception& e)
    {
        std::cerr << e.what() << '\n';
        cout << "Could not enter the piece" << endl;
        return false;
    }
}

std::vector<std::vector<char>> Board::GetBoard()
{
    return this->_board;
}

// print the current status of the board
bool Board::PrintBoard()
{
    try
    {
        
        for (int row = 0; row < BOARD_SIZE; row++)
        { 
            if(row == 0){
                for (int alphaRow = 'A'; alphaRow <= 'S'; alphaRow++) {
                    char index = alphaRow;
                    cout << (alphaRow == 'A'? "   ": "") << index;
                }
                cout << endl;
            }
            for (int column = 0; column < BOARD_SIZE; column++)
            {
                if (column == 0) {
                    
                    cout << BOARD_SIZE -  row << (row < 10 ? " " : "  ") ;
                }
                cout << _board[row][column];
            }
            cout << endl;
        }
        return true;
    }
    catch (const std::exception& e)
    {
        std::cerr << e.what() << '\n';
        return false;
    }
}
bool Board::isWithInBoard(int position)
{
    try
    {
        // fix this
        return (position < BOARD_SIZE && position >= 0) ? true : false;
    }
    catch (const std::exception& e)
    {
        std::cerr << e.what() << '\n';
        return false;
    }
}
bool Board::IsPieceValid(char input)
{
    if (input != WHITE_PIECE && input != BLACK_PIECE)
    {
        return false;
    }
    return true;
}
bool Board::IsPositionEmpty(int row, int cloumn)
{

    return (_board[row][cloumn] == INITIAL_BOARD_PIECE) ? true : false;
}
bool Board::InsertFirstPiece(char colour)
{
    // check if the colour is valid                                     
    int middle = (BOARD_SIZE + 1) / 2;
    return InsertPiece(middle, middle, colour);
}
bool Board::IsSecondPieceValid(int row, int column)
{
	// first check if ther is already the piece in the place they are tyna put
	try
	{
		if (!IsPositionEmpty(row, column))
		{
			cout << "the position is not empty" << endl;
			return false;
		}
		pair<int, int>
			center = GetCenterOfBoard();
		// since it it at the center which is (10, 10)
		// and they want to pu the new piece at (10, 11)
		int dx = abs(row - center.first);
		int dy = abs(column - center.second);

		if ((dx >= 3 && dy >= 0) ||
			(dx >= 0 && dy >= 3) ||
			(dx >= 3 && dy >= 3))
		{
			return true;
		}
        return false;
	}
	catch (const std::exception& e)
	{
		std::cerr << e.what() << '\n';
		cout << "Failed to insert the piece" << endl;
		return false;
	}
}
bool Board::RemovePiece(int row, int column)
{
    try
    {
        if (IsPositionEmpty(row, column))
        {
            cout << "The position is empty so no pieve to remove" << endl;
            return false;
        }
        _board[row][column] = INITIAL_BOARD_PIECE;
        return true;
    }
    catch (const std::exception& e)
    {
        std::cerr << e.what() << '\n';
        cout << "Failed to remove the piece" << endl;
        return false;
    }
}
pair<int, int> Board::GetCenterOfBoard()
{
    int middle = (BOARD_SIZE + 1) / 2 - 1;
    return pair<int, int>(middle, middle);

}
bool Board::ResetBoard() {
    try
    {
        for (int row = 0; row < BOARD_SIZE; row++)
        {
            for (int column = 0; column < BOARD_SIZE; column++)
            {
                this->_board[row][column] = INITIAL_BOARD_PIECE;
            }
        }
        return true;
    }
    catch (const std::exception& e)
    {
        std::cerr << e.what() << '\n';
        cout << "There was error while resetting the board" << endl;
        return false;
    }
}
bool Board::IsBoardFull()
{
    try
    {
        for (int row = 0; row < BOARD_SIZE; row++)
        {
            for (int column = 0; column < BOARD_SIZE; column++)
            {
                if (this->_board[row][column] == INITIAL_BOARD_PIECE) {
                    return false;
                }
            }
        }
        return true;
    }
    catch (const std::exception& e)
    {
        std::cerr << e.what() << '\n';
        cout << "There was error while checking if the board was full" << endl;
        return false;
    }
}
char Board::ReturnPiece(int row, int column) {
    return _board[row][column];
}

int Board::GetBoardSize()
{
    try
    {
        return BOARD_SIZE;
    }
    catch (const std::exception& e)
    {
        std::cerr << e.what() << '\n';
        cout << "Could not get the size of the board" << endl;
        return 0;
    }
}

char Board::GetWhitePiece()
{
    return WHITE_PIECE;
}

char Board::GetBlackPiece()
{
    return BLACK_PIECE;
}

char Board::GetOppositeColour(char colour)
{
    if (colour == GetWhitePiece()) {
        return GetBlackPiece();
    }
    else {
        return GetWhitePiece();
    }
}

bool Board::SetBoard(std::vector<std::vector<char>> board)
{
    try {
        for (int row = 0; row < BOARD_SIZE; row++)
        {
            for (int column = 0; column < BOARD_SIZE; column++)
            {

                this->_board[row][column] = board[row][column];
            }
        }
        return true;
   }
    catch (const std::exception& e)
    {
        std::cerr << e.what() << '\n';
        cout << "There was error while setting the board" << endl;
        return false;
    }
}
