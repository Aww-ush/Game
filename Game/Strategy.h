#include "Board.h"
//Creating initiative - building 
// Avoiding capture
// Countering initiative - capturing
// Blocking a build
// for now generate random move lol
#ifndef STRATEGY_H
#define STRATEGY_H
#include <utility>

class Strategy
{
public:
	Strategy(Board* board);
	std::pair<int, int> GenerateMove();
	

private:
	Board* board;
};

#endif // !STRATEGY_H
