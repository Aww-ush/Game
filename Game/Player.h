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
    int GetTotalPoints();
    int GetTotalCapture();
    bool SetTotalCapure(int number);
    bool isFirstMoveMaker();
    bool SetTotalMoves(int number);
    bool IncreasePoint(int points);
    int GetTotalMoves();
    bool SetBoard(Board* board);
    Board* GetBoard();
    bool SetColour(char colour);
    char GetColour();
    bool SetFirstMoveMaker();
    virtual bool SetName(std::string name) = 0;
    virtual std::string GetName() = 0;
    virtual bool MakeMove(int row, int column) = 0;
    bool Reset();
    bool CalculateMove();
    
};
#endif // Player_H