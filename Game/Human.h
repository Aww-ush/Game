#ifndef HUMAN_H
#define HUMAN_H
#include "Player.h"
#include "Board.h"

class Human : public Player
{
private:

public:
    Human(Board* board, char color);
    Human(Board* board, char colour, int score, int capturePoints, int pieceCaputuredByEnemy);
    bool MakeMove(int row, int column, int pieceCaputuredByEnemy) override;
     bool SetName(std::string name) override;
     std::string GetName() override;
};

#endif // HUMAN_H