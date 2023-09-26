#ifndef SERIALIZATION_H
#define SERIALIZATION_H
#include <iostream>
#include <vector>
#include <string>
#include "Board.h"
#include "Computer.h"
#include "Human.h"
using namespace std;
class Serialization
{
public:
	Serialization();
	Serialization(bool saveFile);

	bool ParseFile();
	vector<vector<char>> GetBoard();
	char GetHumanColour();
	char GetComputerColour();
	int GetHumanScore();
	int GetComputerScore();
	int GetHumanCapturePoints();
	int GetComputerCapturePoints();
	char GetNextMover();
	string AskForPath();
	string FormatTimestampForFilename(const std::string& timestamp);
	string Trim(string str);
	int ReturnCaptureOrScore(string line);
	void SetColour(string line);
	bool SaveGame(Board *board, Player *human, Player * computer, string nextPlayer, string nextPlayerColour);
private:
	int humanCapturePoint;
	int computerCapturePoint;
	int humanScore;
	int computerScore;
	char humanColour;
	char computerColour;
	vector<vector<char>> board;
	char nextMover;
	string filePath;
	const string CAPTURED_MESSAGE = "Captured pairs: ";
	const string SCORE_MESSAGE = "Score: ";
	const char HUMAN_CHARACTER = 'H';
	const char COMPUTER_CHARACTER = 'C';
	bool saveFile = false;
};

#endif // !SERIALIZATION_H
