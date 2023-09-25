#ifndef Player_H
#define Player_H
#include <iostream>
#include "Board.h"
class Player
{
private:
    int totalPoints = 0;
    int totalMoves = 0;
    int totalCapture = 0;
    int roundPoints = 0;
    char _colour = '0';
    Board* _board;
    bool isFirstMover = false;
    bool isTurnToMove = false;
protected:
    std::string _playerName;
    std::string _computerName = "Computer";
public:
    //count the total points position are A10 where A is row abd 10 is column
    bool Move(int row, int column, char colour);
    //tournament points
    int GetTotalPoints();
    bool IncreasePoint(int points);
    //tournament points
    int GetTotalRoundPoints();
    bool IncreaseRoundPoint(int points);
    // capture points
    int GetTotalCapture();
    bool SetTotalCapure(int number);
    // first move maker
    bool SetFirstMoveMaker();
    bool isFirstMoveMaker();
    // set and get total moves
    bool SetTotalMoves(int number);
    int GetTotalMoves();
    // set and get board
    bool SetBoard(Board* board);
    Board* GetBoard();
    // set and get colour
    bool SetColour(char colour);
    char GetColour();

    virtual bool SetName(std::string name) = 0;
    virtual std::string GetName() = 0;
    virtual bool MakeMove(int row, int column) = 0;
    bool Reset();
    bool CalculateMove();
    
};
#endif // Player_H