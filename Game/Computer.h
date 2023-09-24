#pragma once
#ifndef COMPUTER_H
#define COMPUTER_H
#include "Player.h"
class Computer : public Player
{
private:
    
public:
    Computer(Board* board, char colour);
    bool MakeMove(int row, int column) override;
    std::string GetName() override;
    bool SetName(std::string name);

};

#endif //COMPUTER_H