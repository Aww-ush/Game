#include "Round.h"
#ifndef TOURNAMENT_H
#define TOURNAMENT_H
class Tournament
{
public:
	Tournament(Board* board, Player* human, Player* computer, bool isLoaded, char startingPlayer);
	bool PlayRound();
	bool SaveGame();
	bool PrintWinner();
	bool AskToPlayNewRound();
	bool SetPlayNextRound(bool input);
	bool GetPlayNextRound();
	bool DisplayTotalScore();
	bool AskToSaveGame();
	bool GetSave();
	bool SetSave(bool answer);
	bool ResetGame();
	bool SaveScore();
private:
	char startingPlayer;
	int totalRoundsPlayed;
	bool playNextRound;
	// pointers
	Round* round;
	Board* board;
	Player* human;
	Player* computer;
	PointCounter* pointCounter;
	bool save;
	bool isLoaded;
	static  const char HUMAN_CHARACTER = 'H';
	static  const char COMPUTER_CHARACTER = 'C';
	// remove human and computer points
};

#endif // !TOURNAMENT_H


