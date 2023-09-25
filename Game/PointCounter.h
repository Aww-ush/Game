#ifndef POINCOUNTER_H
#define POINCOUNTER_H
#include "Board.h"
#include <utility>
class PointCounter {
public:
    PointCounter(Board* board);
    // this function takes the recent position and determies if the board has the more points near to it
    // if there is four in a row then there is one point
    // if there is 5 in a row then its a win
    int CalculatePoint(int row, int column, char colour);
    // check if there is a winner
    bool isThereWinner();
    // checking if there are more same pieces in a diagonal angled 45* 
    int TotalRightDiagonalPieces(int row, int column, char colour);
    // checking if there are more same pieces in a diagonal angled 135* 
    int TotalLeftDiagonalPieces(int row, int column, char colour);
    // checking if there are more same pieces in the horizontal space
    int TotalHorizontalPieces(int row, int column, char colour);
    // checking if there are more same pieces in the vertical lin
    int TotalVerticalPieces(int row, int column, char colour);
    // recursively checki there are more pieces in a line
    int CheckMoreDownLeft(int row, int column, int count, char colour);
    int CheckMoreDownRight(int row, int column, int count, char colour);
    int CheckMoreUpLeft(int row, int column, int count, char colour);
    int CheckMoreUpRight(int row, int column, int count, char colour);
    int CheckMoreUp(int row, int column, int count, char colour);
    int CheckMoreDown(int row, int column, int count, char colour);
    int CheckMoreRight(int row, int column, int count, char colour);
    int CheckMoreLeft(int row, int column, int count, char colour);
    // get the point if any in this recent position
    int GetPoints();
    // return true if the any player wins
    bool GetHasWon();
    // set the flag if any player wins
    bool SetHasWon(bool input);
    // for capture
    int CalculateCapture(int row, int column, char colour);
    
    // calculate totalScore in tthe round that has beenLoaded
    int CalculatedScoreInLoadedRound(char colour);
    std::pair<int, int> CalculatePointRightDiagonalUp(int row, int column, char colour);
    std::pair<int, int> CalculatePointRightDiagonalDown(int row, int column, char colour);
    std::pair<int, int> CalculatePointLeftDiagonalUp(int row, int column, char colour);
    std::pair<int, int> CalculatePointLeftDiagonalDown(int row, int column, char colour);
    std::pair<int, int> CalculatePointLeftHorizontal(int row, int column, char colour);
    std::pair<int, int> CalculatePointRightHorizontal(int row, int column, char colour);
    std::pair<int, int> CalculatePointUpVertical(int row, int column, char colour);
    std::pair<int, int> CalculatePointDownVertical(int row, int column, char colour);
private:
    Board* board;
    int points;
    bool HasWon = false;
    const static constexpr int CONSECUTIVE_PIECE_FOR_A_POINT = 4;
    const static constexpr int CONSECUTIVE_PIECE_FOR_WIN = 5;
};
#endif //POINCOUNTER_H


