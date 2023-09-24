#include "Round.h"
#ifndef TOURNAMENT_H
#define TOURNAMENT_H
class Tournament
{
public:
	Tournament(Board* board, Player* human, Player* computer);
	Tournament();
	bool PlayRound();
	bool SaveGame();
	bool LoadGame();
	bool PrintWinner();
	bool AskToPlayNewRound();
	bool SetPlayNextRound(bool input);
	bool GetPlayNextRound();
	bool SaveScore();
	bool DisplayTotalScore();
	bool AskToSaveGame();
	bool GetSave();
	bool SetSave(bool answer);
private:
	int totalHumanPoints;
	int totalComputerPoints;
	int totalRoundsPlayed;
	bool playNextRound;
	// pointers
	Round* round;
	Board* board;
	Player* human;
	Player* computer;
	PointCounter* pointCounter;
	bool save;
	// remove human and computer points
};

#endif // !TOURNAMENT_H


