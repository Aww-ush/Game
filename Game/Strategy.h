#include "Board.h"
#include "PointCounter.h"

//Creating initiative - building 
// Avoiding capture
// Countering initiative - capturing
// Blocking a build
// for now generate random move lol
#ifndef STRATEGY_H
#define STRATEGY_H
#include <utility>

using namespace std;
class Strategy
{
public:
	Strategy(Board* board);
	std::pair<int, int> GenerateMove(char colour, int totalMoves, int playerScore, int opponentScore);
    std::pair<int, int> GenerateRandom(char colour, int totalMoves);
    std::pair<int, int> GenerateSecondRandom(char colour);

    // best location for scoring
    std::pair<int, int> BestLocationForScore(char colour);
    // return the best location for capture
    std::pair<int, int> BestLocationForCapture(char colour);
    // prevents opponents 5 in a row
    std::pair<int, int> PreventFinishingGame(char colour);
    // return best locaiton for blocking maximun number of pieces
    std::pair<int, int> BestLocationForBlocking(char colour);
    bool CheckIfTwoOnEachEnd(int row, int column, char oppositeColour);
    bool CheckIfTwoAndOneEitherEnd(int row, int column, char colour, char oppositeColour);
    bool CheckIfCreatingInitiative(int row, int column, char colour, char oppositeColour);
    

    // five consecutive
    bool ShouldBlockRightDiagonalForFive(int row, int column, char oppositeColour);
    bool ShouldBlockLeftDiagonalForFive(int row, int column, char oppositeColour);
    bool ShouldBlockHorizontalForFive(int row, int column, char oppositeColour);
    bool ShouldBlockVerticalForFive(int row, int column, char oppositeColour);
    
    // four consecutive
    bool ShouldBlockRightDiagonalForFour(int row, int column, char oppositeColour);
    bool ShouldBlockLeftDiagonalForFour(int row, int column, char oppositeColour);
    bool ShouldBlockHorizontalForFour(int row, int column, char oppositeColour);
    bool ShouldBlockVerticalForFour(int row, int column, char oppositeColour);

    // consecutive
    bool ShouldBlockRightDiagonalConsecutive(int row, int column, char oppositeColour);
    bool ShouldBlockLeftDiagonalForConsecutive(int row, int column, char oppositeColour);
    bool ShouldBlockHorizontalForConsecutive(int row, int column, char oppositeColour);
    bool ShouldBlockVerticalForConsecutive(int row, int column, char oppositeColour);

    
    // pioritize blocking
    std::pair<int, int> PreventCapturingInitiative(char colour);
    // for creating iniciative
    std::pair<int, int> BestLocationForCreating(char colour);
    // thre bridge is which is clear insert inside the bridge
    std::pair<int, int> CheckForBridges(int row, int column, char colour);
    // if there is single point and need to create a bridge
    std::pair<int, int> CreateBridge(int row, int column, char colour);
    // no bridges found start to create a bridge
    bool IsGoodPointToCreateBridge(int row, int column, char colour);


	int CalculateCapturePoint(int row, int column, char colour);

    // gives relative location
    std::pair<int, int> CalculatePointRightDiagonalUp(int row, int column, char colour, pair<int,int> location);
    std::pair<int, int> CalculatePointRightDiagonalDown(int row, int column, char colour, pair<int, int> location);
    std::pair<int, int> CalculatePointLeftDiagonalUp(int row, int column, char colour, pair<int, int> location);
    std::pair<int, int> CalculatePointLeftDiagonalDown(int row, int column, char colour, pair<int, int> location);
    std::pair<int, int> CalculatePointLeftHorizontal(int row, int column, char colour, pair<int, int> location);
    std::pair<int, int> CalculatePointRightHorizontal(int row, int column, char colour, pair<int, int> location);
    std::pair<int, int> CalculatePointUpVertical(int row, int column, char colour, pair<int, int> location);
    std::pair<int, int> CalculatePointDownVertical(int row, int column, char colour, pair<int, int> location);

    // check if valid point
    bool ArePointsValid(int row, int column);
private:
	Board* board;
    PointCounter* pointCounter;
    const string ErrorPointMessage = "The point is not vaild: Out of bound";
};

#endif // !STRATEGY_H
