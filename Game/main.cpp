#include <iostream>
#include "Board.h"
#include "Player.h"
#include "Coin.h"
#include "Human.h"
#include "Computer.h"
#include "Round.h"
#include "PointCounter.h"
#include "Tournament.h"
#include "Serialization.h"
using namespace std;
const char WHITE_PIECE = 'W';
const char BLACK_PIECE = 'B';
int main()
{
    // start the serialization19
    Serialization* serializationObj = new Serialization();
    vector<vector<char>> board = serializationObj->GetBoard();
    for (int row = 0; row < 19; row++)
    {
        for (int column = 0; column < 19; column++)
        {
            cout << board[row][column];
        }
        cout << endl;
    }
    cout << "Next mover is " << serializationObj->GetNextMover() << endl;
    cout << "Human Colour is " << serializationObj->GetHumanColour() << endl;
    cout << "Human Score is " << serializationObj->GetHumanScore() << endl;
    cout << "Computer Colour is " << serializationObj->GetComputerColour() << endl;
    cout << "Computer Score is " << serializationObj->GetComputerScore() << endl;
    /*Board* boardPtr = new Board();

    cout << "The first player is decided by coin toss. Guess the side of coin H OR T!" << endl;
    char userChoice;
    cin >> userChoice;
    Coin* coin = new Coin();
    char humanColour, computerColour;
    if (coin->Toss())
    {
        if (coin->WinOrLose(userChoice))
        {
            cout << "You have won the toss please go first" << endl;
            humanColour = WHITE_PIECE;
            computerColour = BLACK_PIECE;
        }
        else
        {
            cout << "Coumputer has won the toss you will go second" << endl;
            humanColour = BLACK_PIECE;
            computerColour = WHITE_PIECE;
        }
    }
    Player* humanPlayer = new Human(boardPtr, 'W');
    Player* computerPlayer = new Computer(boardPtr, 'B');
    PointCounter* pointCounter = new PointCounter(boardPtr);
    Tournament* tournament = new Tournament(boardPtr, humanPlayer, computerPlayer);
    if (!tournament->PlayRound())
    {
        cout << "Do you want to save the game?" << endl;
    }*/
    return 0;
}
