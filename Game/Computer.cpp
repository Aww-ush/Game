#include "Computer.h"
#include "Board.h"
#include <iostream>
using namespace std;
Computer::Computer(Board* board, char colour)
{
    if (!SetBoard(board))
    {
        cout << "There was error setting the board for computer" << endl;
    }
    if (!SetName("Computer"))
    {
        cout << "There was error setting the name for computer" << endl;
    }
    if (!SetColour(colour))
    {
        cout << "There was error setting the color for computer" << endl;
    }
}
bool Computer::MakeMove(int row, int column)
{
    try
    {
        Board* board = GetBoard();
        char colour = GetColour();
        if (colour == 'W')
        {
            if (!SetFirstMoveMaker())
            {
                cout << "Internal Server error in Computer::SetFirstMoveMaker" << endl;
                return false;
            }
        }

        if (!Move(row, column, colour))
        {
            cout << "Could not move the piece to position " << row << " " << column << endl;
            return false;
        }
        char rowPositiom = 'A' + row;
        cout << "The computer placed a piece in " << rowPositiom << column << endl;
        return true;
    }
    catch (const std::exception& e)
    {
        std::cerr << e.what() << '\n';
        return false;
    }
}

string Computer::GetName()
{
    return _computerName;

}

bool Computer::SetName(std::string name)
{
    try
    {
        _computerName = "Computer";
        cout << "Set the Computer name to " << _computerName << endl;
        return true;
    }
    catch (const std::exception& e)
    {
        std::cerr << e.what() << '\n';
        return false;
    }
}

