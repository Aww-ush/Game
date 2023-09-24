#include "Strategy.h"
#include <utility> 
using namespace std;
Strategy::Strategy(Board* board)
{
    this->board = board;
}
// next time 
// dont have to account for board full already checked in calling funciton
pair<int, int> Strategy::GenerateMove()
{
    try{
        int boardSize = board->GetBoardSize();
        int row = rand() % boardSize;
        int column = rand() % boardSize;
        // check if it is within the board
        while (!board->isWithInBoard(row)) {
            row = rand() % boardSize;
        }
        while (!board->isWithInBoard(column)) {
            column = rand() % boardSize;
        }
        return pair<int, int>(row, column);
    }
    catch (const std::exception& e)
    {
        std::cerr << e.what() << '\n';
        cout << "Could not generate move" << endl;
        return pair<int,int>();
    }
}
//Creating initiative - building
//Avoiding capture
//Countering initiative - capturing
//Blocking a build
