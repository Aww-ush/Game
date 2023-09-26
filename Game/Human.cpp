#include "Human.h"
#include "Board.h"
#include <iostream>
using namespace std;
Human::Human(Board* board, char colour)
{
    if (!SetBoard(board))
    {
        cout << "There was error setting the board for human" << endl;
    }
    if (!SetColour(colour))
    {
        cout << "There was error setting the color for human" << endl;
    }
    if (!IncreasePoint(0)) {
        cout << "There was error setting the score for human" << endl;

    }
    if (!SetTotalCapure(0)) {
        cout << "There was error setting the caputure point for human" << endl;

    }
}

Human::Human(Board* board, char colour, int score, int capturePoints, int pieceCaputuredByEnemy)
{
    if (!SetBoard(board))
    {
        cout << "There was error setting the board for human" << endl;
    }
    if (!SetColour(colour))
    {
        cout << "There was error setting the color for human" << endl;
    }
    if (!IncreasePoint(score)) {
        cout << "There was error setting the score for human" << endl;

    }
    if (!SetTotalCapure(capturePoints)) {
        cout << "There was error setting the caputure point for human" << endl;

    }
    if (!CalculateMove(pieceCaputuredByEnemy)) {
        cout << "There was error setting the caputure point for computer" << endl;
    }
}

bool Human::MakeMove(int row, int column, int pieceCaputuredByEnemy)
{
    try
    {
        Board* board = GetBoard();
        char colour = GetColour();
        if (colour == 'W') {
            if (!SetFirstMoveMaker()) {
                cout << "Internal Server error in human::MakeMove" << endl;
                return false;
            }
        }
        if (!Move(row, column, colour, pieceCaputuredByEnemy))
        {
            cout << "Could not move the piece to position " << row << " " << column << endl;
            return false;
        }
        return true;
    }
    catch (const std::exception& e)
    {
        std::cerr << e.what() << '\n';
        return false;
    }
}


bool Human::SetName(string name)
{
    try
    {
        _playerName = "Human";
        return true;
    }
    catch (const std::exception& e)
    {
        std::cerr << e.what() << '\n';
        return false;
    }
}

string Human::GetName()
{
    return _playerName;
}
