#ifndef ROUND_H
#define ROUND_H
#include "Human.h"
#include "Computer.h"
#include "Board.h"
#include "Player.h"
#include "PointCounter.h"
#include "Strategy.h"
class Round
{
private:
	char nextMover;
	bool doesPlayerWantToContinue;
	std::string WinnerRoundMessage(std::string playerName);
	static constexpr const char HUMAN_CHARACTER = 'H';
	static constexpr const char COMPUTER_CHARACTER = 'C';
	Player* human;
	Player* computer;
	Board* board;
	Strategy* strategy;
	PointCounter* pointCounter;
	bool playerWins = false;
	bool saveGame = false;
	const int CAPTURE_REQ_TO_WIN = 5;
	
public:
	Round(Player* human, Player* computer, Board* board);
	void SetNextMover(char player);
	bool PlayRound();
	bool AnnounceRoundWinner();
	bool RestGame();
	bool Continue();
	std::string AskForPosition();
	std::pair<int, int> ConvertMoveToRowCol(std::string position);
	// check if there is any winner
	bool GetPlayerWins();
	void SetPlayerWins(bool answer);
	// print the board and the score
	bool PrintGameStatus();
	// computer makes turns this called strategy
	void HandleComputerTurn();
	// human makes turns this does not called strategy
	// for now later it must
	void HandleHumanTurn();
	// human makes turns this does not called strategy
	// for now later it must
	void InitializeHumanFirst();

	// computer moves to the center of the board
	void InitializeComputerFirst();
	// calls the human first move and human second omve
	void InitializeGame();
	// just print the scores
	bool PrintScores();
	bool GetDoesPlayerWantToContinue();
	bool SetDoesPlayerWantToContinuetName(bool answer);
	// get total human points
	int GetHumanPoints();
	//get total computer points
	int GetComputerPoints();

};
#endif // ROUND_H