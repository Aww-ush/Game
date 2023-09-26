#include "Serialization.h"
#include <fstream>
#include <chrono>
Serialization::Serialization()
{
    filePath = AskForPath();
    ParseFile();
}

Serialization::Serialization(bool saveFile)
{
    this->saveFile = saveFile;
}

std::string Serialization::AskForPath()
{
    try
    {
        std::ifstream file;
        std::string path;

        do {
            std::cout << "Please enter a valid file path where your game is saved: " << std::endl;
            std::cin >> path;

            file.open(path); // Attempt to open the file

            if (!file.is_open()) {
                std::cerr << "File could not be opened. Please enter a valid file path." << std::endl;
            }

        } while (path.empty() || !file.is_open());

        file.close();
        return path;
    }
    catch (const std::exception& e)
    {
        std::cerr << e.what() << '\n';
        std::cout << "Internal Server Error: Asking for Path" << std::endl;
        return "";
    }
}

bool Serialization::ParseFile()
{
    try {
        
        ifstream file(filePath);
        if (file.is_open()) {
            std::string line;
            int count = 0;
            while (std::getline(file, line)) {
                if(count > 0 && count <= 19)
                {
                    std::vector<char> row;

                    for (char c : line) {
                        row.push_back(c);
                    }

                    this->board.push_back(row);
                }
                else if (count == 22 || count == 26)
                {
                    if (count == 22)
                        this->humanCapturePoint = ReturnCaptureOrScore(line);
                    else
                        this->computerCapturePoint = ReturnCaptureOrScore(line);
                }
                else if (count == 23 || count == 27) {
                    if (count == 23)
                        this->humanScore = ReturnCaptureOrScore(line);
                    else
                        this->computerScore = ReturnCaptureOrScore(line);
                }
                else if (count == 29) {
                    // Next Player: Human - Black
                    SetColour(line);
                }
                count++;
            }

        }
        else {
            cout << "Internal Server Error while Parsing the file" << endl;
        }
        file.close();
    }
    catch (const std::exception& e)
    {
        std::cerr << e.what() << '\n';
        cout << "Internal Server Error: Asking for Path" << endl;
        return false;
    }
}

int Serialization::ReturnCaptureOrScore(string line) {
    int found = line.find(':');
    if (found == string::npos) {
        cout << "Internal Server Error could not split the string";
    }
    string substring = line.substr(found + 1, line.length());
    //remove white space
    string tmp = Trim(substring);
    int scoreOrCapture = stoi(tmp);
    return scoreOrCapture;
}
void Serialization::SetColour(string line) {
    try{
        int found = line.find(':');
        if (found == string::npos) {
            cout << "Internal Server Error could not split the string";
        }
        string substring = line.substr(found +1, line.length());
        int findDash = substring.find('-');
        string nextPlayer = substring.substr(0, findDash);
        nextPlayer = Trim(nextPlayer);

        string nextPlayerColour = substring.substr(findDash + 1, substring.length());
        nextPlayerColour = Trim(nextPlayerColour);
        if (nextPlayer == "Human") {
            nextMover = HUMAN_CHARACTER;
     
        }
        else {
            nextMover = COMPUTER_CHARACTER;
        }
		if (nextMover == HUMAN_CHARACTER) {
			if (nextPlayerColour == "White") {
				humanColour = 'W';
				computerColour = 'B';
			}
			else {
				humanColour = 'B';
				computerColour = 'W';
			}
		}
        else {
            if (nextPlayerColour == "White") {
                computerColour = 'W';
                humanColour = 'B';
            }
            else {
                computerColour = 'B';
                humanColour = 'W';
            }
        }
    }
    catch (const std::exception& e)
    {
        std::cerr << e.what() << '\n';
        cout << "Internal Server Error: Setting Colour for Human and Computer" << endl;
    }
    
}

bool Serialization::SaveGame(Board* board, Player* human, Player* computer, string nextPlayer, string nextPlayerColour)
{
    try{

        string fileName = "Game.txt";
        std::ofstream file(fileName);

        // Write some data to the file
        file << "Board:\n";
        for (int row = 0; row < board->GetBoardSize(); row++) {
            for (int column = 0; column < board->GetBoardSize(); column++) {
                file << board->GetBoard()[row][column];
            }
            file << "\n";
        }
        file << endl;
        file << "Human:\n";
        file << "Capture pairs: " << human->GetTotalCapture() << endl;
        file << "Score: " << human->GetTotalPoints() << endl;
        file << endl;
        file << "Computer:" << endl;
        file << "Capture pairs: " << computer->GetTotalCapture() << endl;
        file << "Score: " << computer->GetTotalPoints() << endl;
        file << endl;
        file << "Next player: " << nextPlayer << " - " << nextPlayerColour << endl;
        // Close the file
        file.close();
        return true;
    }
    catch (const std::exception& e)
    {
        std::cerr << e.what() << '\n';
        cout << "Internal Server Error: Saving Game " << endl;
        return false;
    }
}
string Serialization::Trim(string str) {
    size_t first = str.find_first_not_of(" \t\n\r");

    if (first == std::string::npos) {
        // The string contains only whitespace
        return "";
    }

    size_t last = str.find_last_not_of(" \t\n\r");

    return str.substr(first, (last - first + 1));
}
vector<vector<char>> Serialization::GetBoard()
{
    return board;
}

char Serialization::GetHumanColour()
{
    return humanColour;
}

char Serialization::GetComputerColour()
{
    return computerColour;
}

int Serialization::GetHumanScore()
{
    return humanScore;
}

int Serialization::GetComputerScore()
{
    return computerScore;
}

int Serialization::GetHumanCapturePoints()
{
    return humanCapturePoint;
}

int Serialization::GetComputerCapturePoints()
{
    return computerCapturePoint;
}

char Serialization::GetNextMover()
{
    return nextMover;
}
