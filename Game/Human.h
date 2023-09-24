#ifndef HUMAN_H
#define HUMAN_H
#include "Player.h"
#include "Board.h"

class Human : public Player
{
private:

public:
    Human(Board* board, char color);
    bool MakeMove(int row, int column) override;
    bool AskForHelp();
     bool SetName(std::string name) override;
     std::string GetName() override;
};

#endif // HUMAN_H