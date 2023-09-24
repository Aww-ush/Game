#ifndef SERIALIZATION_H
#define SERIALIZATION_H
#include <iostream>
#include <vector>
#include <string>
using namespace std;
class Serialization
{
public:
	Serialization();
	bool ParseFile();
	vector<vector<char>> GetBoard();
	char GetHumanColour();
	char GetComputerColour();
	int GetHumanScore();
	int GetComputerScore();
	char GetNextMover();
	string AskForPath();
	string Trim(string str);
	int ReturnCaptureOrScore(string line);
	void SetColour(string line);
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

};

#endif // !SERIALIZATION_H
