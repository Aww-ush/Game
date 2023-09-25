#include "Strategy.h"
#include "PointCounter.h"
#include <utility> 
#include <map>
using namespace std;
Strategy::Strategy(Board* board)
{
    this->board = board;
    this->pointCounter = new PointCounter(board);
}

std::pair<int, int> Strategy::GenerateMove(char colour, int totalMoves, int playerScore, int opponentScore)
{
    try {
        pair<int, int> result(-1,-1);
        if (playerScore < opponentScore) {
            result = BestLocationForBlocking(colour);
            if (result.first != -1 || result.second != -1) {
                return result;
            }
            result = BestLocationForCapture(colour);
            if (result.first != -1 || result.second != -1) {
                return result;
            }
            result = BestLocationForScore(colour);
            if (result.first != -1 || result.second != -1) {
                return result;
            }
            result = BestLocationForCreating(colour);
            if (result.first != -1 || result.second != -1) {
                return result;
            }
            result = GenerateRandom(colour, totalMoves);
            if (result.first != -1 || result.second != -1) {
                cout << "Could not generate random number" << endl;
                return result;
            }

        }
        else {
            result = BestLocationForCapture(colour);
            if (result.first != -1 || result.second != -1) {
                return result;
            }
            result = BestLocationForBlocking(colour);
            if (result.first != -1 || result.second != -1) {
                return result;
            }
            result = BestLocationForScore(colour);
            if (result.first != -1 || result.second != -1) {
                return result;
            }
            result = BestLocationForCreating(colour);
            if (result.first != -1 || result.second != -1) {
                return result;
            }
            result = GenerateRandom(colour, totalMoves);
            if (result.first != -1 || result.second != -1) {
                cout << "Could not generate random number" << endl;
                return result;
            }
        }
    }
    catch (const std::exception& e)
    {
        std::cerr << e.what() << '\n';
        cout << "Could not generate move" << endl;
        return pair<int, int>();
    }
}

pair<int, int> Strategy::GenerateRandom(char colour,int totalMoves)
{
    try{
        if (totalMoves == 1) {
            return GenerateSecondRandom(colour);
        }
        else{
            int boardSize = board->GetBoardSize();
            int row = rand() % boardSize;
            int column = rand() % boardSize;
            while (!board->IsPositionEmpty(row, column)) {
                row = rand() % boardSize;
                column = rand() % boardSize;
            }
            return pair<int, int>(row, column);
        }
    }
    catch (const std::exception& e)
    {
        std::cerr << e.what() << '\n';
        cout << "Could not generate random" << endl;
        return pair<int,int>(-1, -1);
    }
}
pair<int, int> Strategy::GenerateSecondRandom(char colour)
{
    try {
        int row = -1, column = -1;
        do {
            int boardSize = board->GetBoardSize();
            row = rand() % boardSize;
             column = rand() % boardSize;
            // check if it is within the board
            while (!board->isWithInBoard(row)) {
                row = rand() % boardSize;
            }
            while (!board->isWithInBoard(column)) {
                column = rand() % boardSize;
            }
        } while (board->IsSecondPieceValid(row, column));
        
    }
    catch (const std::exception& e)
    {
        std::cerr << e.what() << '\n';
        cout << "Could not generate move" << endl;
        return pair<int, int>(-1, -1);
    }
}

std::pair<int, int> Strategy::BestLocationForScore(char colour)
{
    try {
        pair<int, int> bestLocation(-1, -1);
        int score = 0;
        int newScore = 0;
        
        // add for every point and see how many it can capture 
        // brute force but also most efficient
        for (int row = 0; row < board->GetBoardSize(); row++)
        {
            for (int column = 0; column < board->GetBoardSize(); column++)
            {
                if(board->IsPositionEmpty(row, column)) {
                    newScore = pointCounter->CalculatePoint(row, column, colour);
                    if (newScore > score) {
                        bestLocation.first = row;
                        bestLocation.second = column;
                        score = newScore;

                    }
                }

            }
        }
        return bestLocation;
    }
    catch (const std::exception& e)
    {
        std::cerr << e.what() << '\n';
        cout << "Could not generate move" << endl;
        return pair<int, int>();
    }
}

pair<int, int> Strategy::BestLocationForCapture(char colour)
{
    try {
        pair<int, int> bestLocation(-1, -1);
        int score = 0;
        int newScore = 0;
        // add for every point and see how many it can capture 
        // brute force but also most efficient
        for (int row = 0; row < board->GetBoardSize(); row++)
        {
            for (int column = 0; column < board->GetBoardSize(); column++)
            {
                if (board->IsPositionEmpty(row, column)) {
                    newScore = CalculateCapturePoint(row, column, colour);
                    if (newScore > score) {
                        bestLocation.first = row;
                        bestLocation.second = column;

                    }
                }
                     
            }
        }
        return bestLocation;
    }
    catch (const std::exception& e)
    {
        std::cerr << e.what() << '\n';
        cout << "Could not generate move" << endl;
        return pair<int, int>();
    }
}

std::pair<int, int> Strategy::BestLocationForBlocking(char colour)
{
    try {
        pair<int, int> bestLocation(-1, -1);
        int score = 0;
        int newScore = 0;
        char oppositeColour = board->GetOppositeColour(colour);
        // add for every point and see how many it can capture 
        // brute force but also most efficient
        for (int row = 0; row < board->GetBoardSize(); row++)
        {
            for (int column = 0; column < board->GetBoardSize(); column++)
            {
                // check if there is two on each end
                if (board->IsPositionEmpty(row, column)) {
                    if (CheckIfTwoOnEachEnd(row, column, oppositeColour)) {
                        cout << "This blocks 5 in a row" << endl;
                        return pair<int, int>(row, column);
                    }
                    // check if there is two with in 
                    else if (CheckIfTwoAndOneEitherEnd(row, column, colour, oppositeColour)) {
                        cout << "This blocks 4 in a row" << endl;
                        return pair<int, int>(row, column);
                    }
                    else {
                        // check if in middle of building initiative
                        if (CheckIfCreatingInitiative(row, column, colour, oppositeColour)) {
                            cout << "This blocks creating initiative" << endl;
                            return pair<int, int>(row, column);
                        }
                    }
                }
            }
        }
        return bestLocation;
    }
    catch (const std::exception& e)
    {
        std::cerr << e.what() << '\n';
        cout << "Could not generate move" << endl;
        return pair<int, int>();
    }
}

bool Strategy::CheckIfTwoOnEachEnd(int row, int column, char oppositeColour)
{
    try {
        // check for right diagonal
        if (ShouldBlockRightDiagonalForFive(row, column, oppositeColour)) {
            return true;
        }
        // check for left diagonal
        if (ShouldBlockLeftDiagonalForFive(row, column, oppositeColour)) {
            return true;
        }
        //check for horizontal
        if (ShouldBlockHorizontalForFive(row, column, oppositeColour)) {
            return true;
        }
        //check for vertical
        if (ShouldBlockVerticalForFive(row, column, oppositeColour)) {
            return true;
        }
        return false;
   }
    catch (const std::exception& e)
    {
        std::cerr << e.what() << '\n';
        cout << "Could not generate move" << endl;
        return false;
    }
}
bool Strategy::CheckIfTwoAndOneEitherEnd(int row, int column, char colour, char oppositeColour)
{
    try {
        // check for right diagonal
        if (ShouldBlockRightDiagonalForFour(row, column, oppositeColour)) {
            return true;
        }
        // check for left diagonal
        if (ShouldBlockLeftDiagonalForFour(row, column, oppositeColour)) {
            return true;
        }
        //check for horizontal
        if (ShouldBlockHorizontalForFour(row, column, oppositeColour)) {
            return true;
        }
        //check for vertical
        if (ShouldBlockVerticalForFour(row, column, oppositeColour)) {
            return true;
        }
        return false;
    }
    catch (const std::exception& e)
    {
        std::cerr << e.what() << '\n';
        cout << "Could not generate move" << endl;
        return false;
    }
}
bool Strategy::CheckIfCreatingInitiative(int row, int column, char colour, char oppositeColour)
{
    try {
        // check for right diagonal
        if (ShouldBlockRightDiagonalConsecutive(row, column, oppositeColour)) {
            return true;
        }
        // check for left diagonal
        if (ShouldBlockLeftDiagonalForConsecutive(row, column, oppositeColour)) {
            return true;
        }
        //check for horizontal
        if (ShouldBlockHorizontalForConsecutive(row, column, oppositeColour)) {
            return true;
        }
        //check for vertical
        if (ShouldBlockVerticalForConsecutive(row, column, oppositeColour)) {
            return true;
        }
        return false;
    }
    catch (const std::exception& e)
    {
        std::cerr << e.what() << '\n';
        cout << "Could not generate move" << endl;
        return false;
    }
}
bool  Strategy::ShouldBlockRightDiagonalForFive(int row, int column, char oppositeColour) {
    try{
        // check on the top of the diagonal
        pair<int, int> pointOneIntersectionAway = CalculatePointRightDiagonalUp(row, column, oppositeColour, pair<int, int>(1, 1));
        if (board->GetBoard()[pointOneIntersectionAway.first][pointOneIntersectionAway.second] == oppositeColour) {
            pair<int, int> pointTwoIntersectionAway = CalculatePointRightDiagonalUp(row, column, oppositeColour, pair<int, int>(2, 2));
            if (board->GetBoard()[pointTwoIntersectionAway.first][pointTwoIntersectionAway.second] != oppositeColour)
            {
                pair<int, int> pointOneIntersectionAwayDown = CalculatePointRightDiagonalDown(row, column, oppositeColour, pair<int, int>(1, 1));
                if (board->GetBoard()[pointOneIntersectionAwayDown.first][pointOneIntersectionAwayDown.second] == oppositeColour) {
                    pair<int, int>pointTwoIntersectionAwayDown = CalculatePointRightDiagonalDown(row, column, oppositeColour, pair<int, int>(2, 2));
                    if (board->GetBoard()[pointTwoIntersectionAwayDown.first][pointTwoIntersectionAwayDown.second] == oppositeColour) {
                        pair<int, int>pointThreeIntersectionAwayDown = CalculatePointRightDiagonalDown(row, column, oppositeColour, pair<int, int>(2, 2));
                        if (board->GetBoard()[pointThreeIntersectionAwayDown.first][pointThreeIntersectionAwayDown.second] == oppositeColour) {
                            //three is a situation like xoxxx
                            return true;

                        }
                    }
                }

            }
                
        }
        else {
            return false;
        }

        // check on the botton of the diagonal
        pointOneIntersectionAway = CalculatePointRightDiagonalDown(row, column, oppositeColour, pair<int, int>(1, 1));
        if (board->GetBoard()[pointOneIntersectionAway.first][pointOneIntersectionAway.second] == oppositeColour) {
            pair<int, int>pointTwoIntersectionAway = CalculatePointRightDiagonalDown(row, column, oppositeColour, pair<int, int>(2, 2));
            if (board->GetBoard()[pointTwoIntersectionAway.first][pointTwoIntersectionAway.second] != oppositeColour)
            {
                pair<int, int> pointOneIntersectionAwayUp = CalculatePointRightDiagonalUp(row, column, oppositeColour, pair<int, int>(1, 1));
                if (board->GetBoard()[pointOneIntersectionAwayUp.first][pointOneIntersectionAwayUp.second] == oppositeColour) {
                    pair<int, int>pointTwoIntersectionAwayDown = CalculatePointRightDiagonalUp(row, column, oppositeColour, pair<int, int>(2, 2));
                    if (board->GetBoard()[pointTwoIntersectionAwayDown.first][pointTwoIntersectionAwayDown.second] == oppositeColour) {
                        pair<int, int>pointThreeIntersectionAwayUp = CalculatePointRightDiagonalUp(row, column, oppositeColour, pair<int, int>(2, 2));
                        if (board->GetBoard()[pointThreeIntersectionAwayUp.first][pointThreeIntersectionAwayUp.second] == oppositeColour) {
                            // there is situation like xxxox
                            return true;
                        }
                    }
                }
            }

        }
        else {
            return false;
        }
        // there is situation like xxoxx
        return true;
    }
    catch (const std::exception& e)
    {
        std::cerr << e.what() << '\n';
        cout << "Internal Server Error: ShouldBlockRightDiagonalForFive" << endl;
        return false;
    }

}
bool  Strategy::ShouldBlockLeftDiagonalForFive(int row, int column, char oppositeColour) {
    try {
        // check on the top of the diagonal
        pair<int, int> pointOneIntersectionAway = CalculatePointLeftDiagonalUp(row, column, oppositeColour, pair<int, int>(1, 1));
        if (board->GetBoard()[pointOneIntersectionAway.first][pointOneIntersectionAway.second] == oppositeColour) {
            pair<int, int> pointTwoIntersectionAway = CalculatePointLeftDiagonalUp(row, column, oppositeColour, pair<int, int>(2, 2));
            if (board->GetBoard()[pointTwoIntersectionAway.first][pointTwoIntersectionAway.second] != oppositeColour)
            {
                pair<int, int> pointOneIntersectionAwayDown = CalculatePointLeftDiagonalDown(row, column, oppositeColour, pair<int, int>(1, 1));
                if (board->GetBoard()[pointOneIntersectionAwayDown.first][pointOneIntersectionAwayDown.second] == oppositeColour) {
                    pair<int, int>pointTwoIntersectionAwayDown = CalculatePointLeftDiagonalDown(row, column, oppositeColour, pair<int, int>(2, 2));
                    if (board->GetBoard()[pointTwoIntersectionAwayDown.first][pointTwoIntersectionAwayDown.second] == oppositeColour) {
                        pair<int, int>pointThreeIntersectionAwayDown = CalculatePointLeftDiagonalDown(row, column, oppositeColour, pair<int, int>(2, 2));
                        if (board->GetBoard()[pointThreeIntersectionAwayDown.first][pointThreeIntersectionAwayDown.second] == oppositeColour) {
                            //three is a situation like xoxxx
                            return true;

                        }
                    }
                }

            }

        }
        else {
            return false;
        }

        // check on the botton of the diagonal
        pointOneIntersectionAway = CalculatePointLeftDiagonalDown(row, column, oppositeColour, pair<int, int>(1, 1));
        if (board->GetBoard()[pointOneIntersectionAway.first][pointOneIntersectionAway.second] == oppositeColour) {
            pair<int, int>pointTwoIntersectionAway = CalculatePointLeftDiagonalDown(row, column, oppositeColour, pair<int, int>(2, 2));
            if (board->GetBoard()[pointTwoIntersectionAway.first][pointTwoIntersectionAway.second] != oppositeColour)
            {
                pair<int, int> pointOneIntersectionAwayUp = CalculatePointLeftDiagonalUp(row, column, oppositeColour, pair<int, int>(1, 1));
                if (board->GetBoard()[pointOneIntersectionAwayUp.first][pointOneIntersectionAwayUp.second] == oppositeColour) {
                    pair<int, int>pointTwoIntersectionAwayDown = CalculatePointLeftDiagonalUp(row, column, oppositeColour, pair<int, int>(2, 2));
                    if (board->GetBoard()[pointTwoIntersectionAwayDown.first][pointTwoIntersectionAwayDown.second] == oppositeColour) {
                        pair<int, int>pointThreeIntersectionAwayUp = CalculatePointLeftDiagonalUp(row, column, oppositeColour, pair<int, int>(2, 2));
                        if (board->GetBoard()[pointThreeIntersectionAwayUp.first][pointThreeIntersectionAwayUp.second] == oppositeColour) {
                            // there is situation like xxxox
                            return true;
                        }
                    }
                }
            }

        }
        else {
            return false;
        }
        // there is situation like xxoxx
        return true;
    }
    catch (const std::exception& e)
    {
        std::cerr << e.what() << '\n';
        cout << "Internal Server Error: ShouldBlockRightDiagonalForFive" << endl;
        return false;
    }

}
bool  Strategy::ShouldBlockHorizontalForFive(int row, int column, char oppositeColour) {
    try {
        // check on the top of the diagonal
        pair<int, int> pointOneIntersectionAway = CalculatePointLeftHorizontal(row, column, oppositeColour, pair<int, int>(1, 1));
        if (board->GetBoard()[pointOneIntersectionAway.first][pointOneIntersectionAway.second] == oppositeColour) {
            pair<int, int> pointTwoIntersectionAway = CalculatePointLeftHorizontal(row, column, oppositeColour, pair<int, int>(2, 2));
            if (board->GetBoard()[pointTwoIntersectionAway.first][pointTwoIntersectionAway.second] != oppositeColour)
            {
                pair<int, int> pointOneIntersectionAwayDown = CalculatePointRightHorizontal(row, column, oppositeColour, pair<int, int>(1, 1));
                if (board->GetBoard()[pointOneIntersectionAwayDown.first][pointOneIntersectionAwayDown.second] == oppositeColour) {
                    pair<int, int>pointTwoIntersectionAwayDown = CalculatePointRightHorizontal(row, column, oppositeColour, pair<int, int>(2, 2));
                    if (board->GetBoard()[pointTwoIntersectionAwayDown.first][pointTwoIntersectionAwayDown.second] == oppositeColour) {
                        pair<int, int>pointThreeIntersectionAwayDown = CalculatePointRightHorizontal(row, column, oppositeColour, pair<int, int>(2, 2));
                        if (board->GetBoard()[pointThreeIntersectionAwayDown.first][pointThreeIntersectionAwayDown.second] == oppositeColour) {
                            //three is a situation like xoxxx
                            return true;

                        }
                    }
                }

            }

        }
        else {
            return false;
        }

        // check on the botton of the diagonal
        pointOneIntersectionAway = CalculatePointRightHorizontal(row, column, oppositeColour, pair<int, int>(1, 1));
        if (board->GetBoard()[pointOneIntersectionAway.first][pointOneIntersectionAway.second] == oppositeColour) {
            pair<int, int>pointTwoIntersectionAway = CalculatePointRightHorizontal(row, column, oppositeColour, pair<int, int>(2, 2));
            if (board->GetBoard()[pointTwoIntersectionAway.first][pointTwoIntersectionAway.second] != oppositeColour)
            {
                pair<int, int> pointOneIntersectionAwayUp = CalculatePointLeftHorizontal(row, column, oppositeColour, pair<int, int>(1, 1));
                if (board->GetBoard()[pointOneIntersectionAwayUp.first][pointOneIntersectionAwayUp.second] == oppositeColour) {
                    pair<int, int>pointTwoIntersectionAwayDown = CalculatePointLeftHorizontal(row, column, oppositeColour, pair<int, int>(2, 2));
                    if (board->GetBoard()[pointTwoIntersectionAwayDown.first][pointTwoIntersectionAwayDown.second] == oppositeColour) {
                        pair<int, int>pointThreeIntersectionAwayUp = CalculatePointLeftHorizontal(row, column, oppositeColour, pair<int, int>(2, 2));
                        if (board->GetBoard()[pointThreeIntersectionAwayUp.first][pointThreeIntersectionAwayUp.second] == oppositeColour) {
                            // there is situation like xxxox
                            return true;
                        }
                    }
                }
            }

        }
        else {
            return false;
        }
        // there is situation like xxoxx
        return true;
    }
    catch (const std::exception& e)
    {
        std::cerr << e.what() << '\n';
        cout << "Internal Server Error: ShouldBlockRightDiagonalForFive" << endl;
        return false;
    }

}
bool  Strategy::ShouldBlockVerticalForFive(int row, int column, char oppositeColour) {
    try {
        // check on the top of the diagonal
        pair<int, int> pointOneIntersectionAway = CalculatePointUpVertical(row, column, oppositeColour, pair<int, int>(1, 1));
        if (board->GetBoard()[pointOneIntersectionAway.first][pointOneIntersectionAway.second] == oppositeColour) {
            pair<int, int> pointTwoIntersectionAway = CalculatePointUpVertical(row, column, oppositeColour, pair<int, int>(2, 2));
            if (board->GetBoard()[pointTwoIntersectionAway.first][pointTwoIntersectionAway.second] != oppositeColour)
            {
                pair<int, int> pointOneIntersectionAwayDown = CalculatePointDownVertical(row, column, oppositeColour, pair<int, int>(1, 1));
                if (board->GetBoard()[pointOneIntersectionAwayDown.first][pointOneIntersectionAwayDown.second] == oppositeColour) {
                    pair<int, int>pointTwoIntersectionAwayDown = CalculatePointDownVertical(row, column, oppositeColour, pair<int, int>(2, 2));
                    if (board->GetBoard()[pointTwoIntersectionAwayDown.first][pointTwoIntersectionAwayDown.second] == oppositeColour) {
                        pair<int, int>pointThreeIntersectionAwayDown = CalculatePointDownVertical(row, column, oppositeColour, pair<int, int>(2, 2));
                        if (board->GetBoard()[pointThreeIntersectionAwayDown.first][pointThreeIntersectionAwayDown.second] == oppositeColour) {
                            //three is a situation like xoxxx
                            return true;

                        }
                    }
                }

            }

        }
        else {
            return false;
        }

        // check on the botton of the diagonal
        pointOneIntersectionAway = CalculatePointDownVertical(row, column, oppositeColour, pair<int, int>(1, 1));
        if (board->GetBoard()[pointOneIntersectionAway.first][pointOneIntersectionAway.second] == oppositeColour) {
            pair<int, int>pointTwoIntersectionAway = CalculatePointDownVertical(row, column, oppositeColour, pair<int, int>(2, 2));
            if (board->GetBoard()[pointTwoIntersectionAway.first][pointTwoIntersectionAway.second] != oppositeColour)
            {
                pair<int, int> pointOneIntersectionAwayUp = CalculatePointUpVertical(row, column, oppositeColour, pair<int, int>(1, 1));
                if (board->GetBoard()[pointOneIntersectionAwayUp.first][pointOneIntersectionAwayUp.second] == oppositeColour) {
                    pair<int, int>pointTwoIntersectionAwayDown = CalculatePointUpVertical(row, column, oppositeColour, pair<int, int>(2, 2));
                    if (board->GetBoard()[pointTwoIntersectionAwayDown.first][pointTwoIntersectionAwayDown.second] == oppositeColour) {
                        pair<int, int>pointThreeIntersectionAwayUp = CalculatePointUpVertical(row, column, oppositeColour, pair<int, int>(2, 2));
                        if (board->GetBoard()[pointThreeIntersectionAwayUp.first][pointThreeIntersectionAwayUp.second] == oppositeColour) {
                            // there is situation like xxxox
                            return true;
                        }
                    }
                }
            }

        }
        else {
            return false;
        }
        // there is situation like xxoxx
        return true;
    }
    catch (const std::exception& e)
    {
        std::cerr << e.what() << '\n';
        cout << "Internal Server Error: ShouldBlockRightDiagonalForFive" << endl;
        return false;
    }

}

int Strategy::CalculateCapturePoint(int row, int column, char colour)
{
    try {
        int totalCapture = 0;
        pair<int, int> threeIntersectionAway(3, 3);

        // calculate the point ie 3 distance away in rt diagonal - up send (-1, -1) if not within board
        pair<int, int> righDiagonalUp = CalculatePointRightDiagonalUp(row, column, colour, threeIntersectionAway);
        // check if there is piece
        // if there is remove 
        // gain a point
        // else continue
        if (righDiagonalUp.first != -1 || righDiagonalUp.second != -1) {
            if (colour == board->GetBoard()[righDiagonalUp.first][righDiagonalUp.second]) {
                int count = 0;
                vector<pair<int, int>> captureLocation;
                for (int tmpRow = row, tmpColumn = column; tmpRow >= righDiagonalUp.first; tmpRow--, tmpColumn++) {
                    if (board->GetBoard()[tmpRow][tmpColumn] == board->GetOppositeColour(colour)) {
                        captureLocation.push_back(pair<int, int>(tmpRow, tmpColumn));
                        count++;
                    }
                }
                if (count == 2) {
                    totalCapture++;
                }
            }

        }
        // calculate the point ie 3 distance away in rt diagonal - down send (-1, -1) if not within board
        pair<int, int> righDiagonalDown = CalculatePointRightDiagonalDown(row, column, colour, threeIntersectionAway);
        if (righDiagonalDown.first != -1 || righDiagonalDown.second != -1) {
            if (colour == board->GetBoard()[righDiagonalDown.first][righDiagonalDown.second]) {
                int count = 0;
                vector<pair<int, int>> captureLocation;
                for (int tmpRow = row, tmpColumn = column; tmpRow <= righDiagonalDown.first; tmpRow++, tmpColumn--) {
                    if (board->GetBoard()[tmpRow][tmpColumn] == board->GetOppositeColour(colour)) {
                        captureLocation.push_back(pair<int, int>(tmpRow, tmpColumn));
                        count++;
                    }
                }
                if (count == 2) {
                    totalCapture++;

                }
            }
        }
        // calculate the point ie 3 distance away in lt diagonal -up send (-1, -1) if not within board
        pair<int, int> leftDiagonalUp = CalculatePointLeftDiagonalUp(row, column, colour, threeIntersectionAway);
        if (leftDiagonalUp.first != -1 || leftDiagonalUp.second != -1) {
            if (colour == board->GetBoard()[leftDiagonalUp.first][leftDiagonalUp.second]) {
                int count = 0;
                vector<pair<int, int>> captureLocation;
                for (int tmpRow = row, tmpColumn = column; tmpRow >= leftDiagonalUp.first; tmpRow--, tmpColumn--) {
                    if (board->GetBoard()[tmpRow][tmpColumn] == board->GetOppositeColour(colour)) {
                        captureLocation.push_back(pair<int, int>(tmpRow, tmpColumn));
                        count++;
                    }
                }
                if (count == 2) {
                    totalCapture++;
                }
            }
        }
        // calculate the point ie 3 distance away in lt diagonal -down send (-1, -1) if not within board
        pair<int, int> leftDiagonalDown = CalculatePointLeftDiagonalDown(row, column, colour, threeIntersectionAway);
        if (leftDiagonalDown.first != -1 || leftDiagonalDown.second != -1) {
            if (colour == board->GetBoard()[leftDiagonalDown.first][leftDiagonalDown.second]) {

                int count = 0;
                vector<pair<int, int>> captureLocation;
                for (int tmpRow = row, tmpColumn = column; tmpRow <= leftDiagonalDown.first; tmpRow++, tmpColumn++) {
                    if (board->GetBoard()[tmpRow][tmpColumn] == board->GetOppositeColour(colour)) {
                        captureLocation.push_back(pair<int, int>(tmpRow, tmpColumn));
                        count++;
                    }
                }
                if (count == 2) {
                    totalCapture++;

                }
            }
        }
        // calculate the point ie 3 distance away in lt horizontal send (-1, -1) if not within board
        pair<int, int> leftHorizontal = CalculatePointLeftHorizontal(row, column, colour, threeIntersectionAway);
        if (leftHorizontal.first != -1 || leftHorizontal.second != -1) {
            if (colour == board->GetBoard()[leftHorizontal.first][leftHorizontal.second]) {

                int count = 0;
                vector<pair<int, int>> captureLocation;
                for (int tmpRow = row, tmpColumn = column; tmpColumn >= leftHorizontal.second; tmpColumn--) {
                    if (board->GetBoard()[tmpRow][tmpColumn] == board->GetOppositeColour(colour)) {
                        captureLocation.push_back(pair<int, int>(tmpRow, tmpColumn));
                        count++;
                    }
                }
                if (count == 2) {
                    totalCapture++;

                }
            }
        }
        // calculate the point ie 3 distance away in rt horizontal send (-1, -1) if not within board
        pair<int, int> rightHorizontal = CalculatePointRightHorizontal(row, column, colour, threeIntersectionAway);
        if (rightHorizontal.first != -1 || rightHorizontal.second != -1) {
            if (colour == board->GetBoard()[rightHorizontal.first][rightHorizontal.second]) {

                int count = 0;
                vector<pair<int, int>> captureLocation;
                for (int tmpRow = row, tmpColumn = column; tmpColumn <= rightHorizontal.second; tmpColumn++) {
                    if (board->GetBoard()[tmpRow][tmpColumn] == board->GetOppositeColour(colour)) {
                        captureLocation.push_back(pair<int, int>(tmpRow, tmpColumn));
                        count++;
                    }
                }
                if (count == 2) {
                    totalCapture++;

                }
            }
        }
        // calculate the point ie 3 distance away in rt vertical send (-1, -1) if not within board
        pair<int, int> upVertical = CalculatePointUpVertical(row, column, colour, threeIntersectionAway);
        if (upVertical.first != -1 || upVertical.second != -1) {
            if (colour == board->GetBoard()[upVertical.first][upVertical.second]) {

                int count = 0;
                vector<pair<int, int>> captureLocation;
                for (int tmpRow = row, tmpColumn = column; tmpRow >= upVertical.first; tmpRow--) {
                    if (board->GetBoard()[tmpRow][tmpColumn] == board->GetOppositeColour(colour)) {
                        captureLocation.push_back(pair<int, int>(tmpRow, tmpColumn));
                        count++;
                    }
                }
                if (count == 2) {
                    totalCapture++;

                }
            }
        }
        // calculate the point ie 3 distance away in tt vertical send (-1, -1) if not within board
        pair<int, int> downVertical = CalculatePointDownVertical(row, column, colour, threeIntersectionAway);
        if (downVertical.first != -1 || downVertical.second != -1) {
            if (colour == board->GetBoard()[downVertical.first][downVertical.second]) {

                int count = 0;
                vector<pair<int, int>> captureLocation;
                for (int tmpRow = row, tmpColumn = column; tmpRow <= downVertical.first; tmpRow++) {
                    if (board->GetBoard()[tmpRow][tmpColumn] == board->GetOppositeColour(colour)) {
                        captureLocation.push_back(pair<int, int>(tmpRow, tmpColumn));
                        count++;
                    }
                }
                if (count == 2) {
                    totalCapture++;

                }
            }
        }
        return totalCapture;
    }
    catch (const std::exception& e)
    {
        cout << e.what() << endl;
        cout << "Internal Server Error: PointCounter::SetHasWon()" << endl;
        return 0;
    }

}

std::pair<int, int> Strategy::CalculatePointRightDiagonalUp(int row, int column, char colour, pair<int, int> location)
{
    try {
        int newRow = row - location.first;
        int newColumn = column + location.second;

        // Check boundaries
        if (newRow >= 0 && newRow < board->GetBoardSize() && newColumn >= 0 && newColumn < board->GetBoardSize())
        {
            // The point is within valid boundaries
            return std::pair<int, int>(newRow, newColumn);
        }
        else
        {
            // The point is out of bounds
            return std::pair<int, int>(-1, -1);
        }
    }
    catch (const std::exception& e) {
        std::cerr << e.what() << '\n';
        cout << "Internal Server Error: PointCounter::CalculatePointRightDiagonalUp" << endl;
        return std::pair<int, int>(-1, -1);
    }
}

std::pair<int, int> Strategy::CalculatePointRightDiagonalDown(int row, int column, char colour, pair<int, int> location)
{
    try {
        int newRow = row + location.first;
        int newColumn = column - location.second;

        // Check boundaries
        if (newRow >= 0 && newRow < board->GetBoardSize() && newColumn >= 0 && newColumn < board->GetBoardSize())
        {
            // The point is within valid boundaries
            return std::pair<int, int>(newRow, newColumn);
        }
        else
        {
            // The point is out of bounds
            return std::pair<int, int>(-1, -1);
        }
    }
    catch (const std::exception& e) {
        std::cerr << e.what() << '\n';
        cout << "Internal Server Error: PointCounter::CalculatePointRightDiagonalUp" << endl;
        return std::pair<int, int>(-1, -1);
    }
}

std::pair<int, int> Strategy::CalculatePointLeftDiagonalUp(int row, int column, char colour, pair<int, int> location)
{
    try {
        int newRow = row - location.first;
        int newColumn = column - location.second;

        // Check boundaries
        if (newRow >= 0 && newRow < board->GetBoardSize() && newColumn >= 0 && newColumn < board->GetBoardSize())
        {
            // The point is within valid boundaries
            return std::pair<int, int>(newRow, newColumn);
        }
        else
        {
            // The point is out of bounds
            return std::pair<int, int>(-1, -1);
        }
    }
    catch (const std::exception& e) {
        std::cerr << e.what() << '\n';
        cout << "Internal Server Error: PointCounter::CalculatePointRightDiagonalUp" << endl;
        return std::pair<int, int>(-1, -1);
    }
}

std::pair<int, int> Strategy::CalculatePointLeftDiagonalDown(int row, int column, char colour, pair<int, int> location)
{
    try {
        int newRow = row + location.first;
        int newColumn = column + location.second;

        // Check boundaries
        if (newRow >= 0 && newRow < board->GetBoardSize() && newColumn >= 0 && newColumn < board->GetBoardSize())
        {
            // The point is within valid boundaries
            return std::pair<int, int>(newRow, newColumn);
        }
        else
        {
            // The point is out of bounds
            return std::pair<int, int>(-1, -1);
        }
    }
    catch (const std::exception& e) {
        std::cerr << e.what() << '\n';
        cout << "Internal Server Error: PointCounter::CalculatePointRightDiagonalUp" << endl;
        return std::pair<int, int>(-1, -1);
    }
}

std::pair<int, int> Strategy::CalculatePointLeftHorizontal(int row, int column, char colour, pair<int, int> location)
{
    try {
        int newRow = row;
        int newColumn = column - location.second;

        // Check boundaries
        if (newRow >= 0 && newRow < board->GetBoardSize() && newColumn >= 0 && newColumn < board->GetBoardSize())
        {
            // The point is within valid boundaries
            return std::pair<int, int>(newRow, newColumn);
        }
        else
        {
            // The point is out of bounds
            return std::pair<int, int>(-1, -1);
        }
    }
    catch (const std::exception& e) {
        std::cerr << e.what() << '\n';
        cout << "Internal Server Error: PointCounter::CalculatePointRightDiagonalUp" << endl;
        return std::pair<int, int>(-1, -1);
    }
}

std::pair<int, int> Strategy::CalculatePointRightHorizontal(int row, int column, char colour, pair<int, int> location)
{
    try {
        int newRow = row;
        int newColumn = column + location.second;

        // Check boundaries
        if (newRow >= 0 && newRow < board->GetBoardSize() && newColumn >= 0 && newColumn < board->GetBoardSize())
        {
            // The point is within valid boundaries
            return std::pair<int, int>(newRow, newColumn);
        }
        else
        {
            // The point is out of bounds
            return std::pair<int, int>(-1, -1);
        }
    }
    catch (const std::exception& e) {
        std::cerr << e.what() << '\n';
        cout << "Internal Server Error: PointCounter::CalculatePointRightDiagonalUp" << endl;
        return std::pair<int, int>(-1, -1);
    }
}

std::pair<int, int> Strategy::CalculatePointUpVertical(int row, int column, char colour, pair<int, int> location)
{
    try {
        int newRow = row - location.second;
        int newColumn = column;

        // Check boundaries
        if (newRow >= 0 && newRow < board->GetBoardSize() && newColumn >= 0 && newColumn < board->GetBoardSize())
        {
            // The point is within valid boundaries
            return std::pair<int, int>(newRow, newColumn);
        }
        else
        {
            // The point is out of bounds
            return std::pair<int, int>(-1, -1);
        }
    }
    catch (const std::exception& e) {
        std::cerr << e.what() << '\n';
        cout << "Internal Server Error: PointCounter::CalculatePointRightDiagonalUp" << endl;
        return std::pair<int, int>(-1, -1);
    }
}

std::pair<int, int> Strategy::CalculatePointDownVertical(int row, int column, char colour, pair<int, int> location)
{
    try {
        int newRow = row + location.first;
        int newColumn = column;

        // Check boundaries
        if (newRow >= 0 && newRow < board->GetBoardSize() && newColumn >= 0 && newColumn < board->GetBoardSize())
        {
            // The point is within valid boundaries
            return std::pair<int, int>(newRow, newColumn);
        }
        else
        {
            // The point is out of bounds
            return std::pair<int, int>(-1, -1);
        }
    }
    catch (const std::exception& e) {
        std::cerr << e.what() << '\n';
        cout << "Internal Server Error: PointCounter::CalculatePointRightDiagonalUp" << endl;
        return std::pair<int, int>(-1, -1);
    }
}



// four

bool  Strategy::ShouldBlockRightDiagonalForFour(int row, int column, char oppositeColour) {
    try {
        // check on the top of the diagonal
        pair<int, int> pointOneIntersectionAway = CalculatePointRightDiagonalUp(row, column, oppositeColour, pair<int, int>(1, 1));
        if (board->GetBoard()[pointOneIntersectionAway.first][pointOneIntersectionAway.second] == oppositeColour) {
            pair<int, int> pointTwoIntersectionAway = CalculatePointRightDiagonalUp(row, column, oppositeColour, pair<int, int>(2, 2));
            if (board->GetBoard()[pointTwoIntersectionAway.first][pointTwoIntersectionAway.second] == oppositeColour)
            {
                pair<int, int> pointOneIntersectionAwayDown = CalculatePointRightDiagonalDown(row, column, oppositeColour, pair<int, int>(1, 1));
                if (board->GetBoard()[pointOneIntersectionAwayDown.first][pointOneIntersectionAwayDown.second] == oppositeColour) {
                    return true;
                }
            }
        }
        else {
            return false;
        }
        pair<int, int> pointOneIntersectionAwayDown = CalculatePointRightDiagonalDown(row, column, oppositeColour, pair<int, int>(1, 1));
        if (board->GetBoard()[pointOneIntersectionAwayDown.first][pointOneIntersectionAwayDown.second] == oppositeColour) {
            pair<int, int> pointTwoIntersectionAwayDown = CalculatePointRightDiagonalUp(row, column, oppositeColour, pair<int, int>(2, 2));
            if (board->GetBoard()[pointTwoIntersectionAwayDown.first][pointTwoIntersectionAwayDown.second] == oppositeColour)
            {
                pair<int, int> pointOneIntersectionAway = CalculatePointRightDiagonalUp(row, column, oppositeColour, pair<int, int>(1, 1));
                if (board->GetBoard()[pointOneIntersectionAwayDown.first][pointOneIntersectionAwayDown.second] == oppositeColour) {
                    return true;
                }
            }
        }
        else {
            return false;
        }
        return false;
    }
    catch (const std::exception& e)
    {
        std::cerr << e.what() << '\n';
        cout << "Internal Server Error: ShouldBlockRightDiagonalForFive" << endl;
        return false;
    }

}
bool  Strategy::ShouldBlockLeftDiagonalForFour(int row, int column, char oppositeColour) {
    try {
        // check on the top of the diagonal
        pair<int, int> pointOneIntersectionAway = CalculatePointLeftDiagonalUp(row, column, oppositeColour, pair<int, int>(1, 1));
        if (board->GetBoard()[pointOneIntersectionAway.first][pointOneIntersectionAway.second] == oppositeColour) {
            pair<int, int> pointTwoIntersectionAway = CalculatePointLeftDiagonalUp(row, column, oppositeColour, pair<int, int>(2, 2));
            if (board->GetBoard()[pointTwoIntersectionAway.first][pointTwoIntersectionAway.second] == oppositeColour)
            {
                pair<int, int> pointOneIntersectionAwayDown = CalculatePointLeftDiagonalDown(row, column, oppositeColour, pair<int, int>(1, 1));
                if (board->GetBoard()[pointOneIntersectionAwayDown.first][pointOneIntersectionAwayDown.second] == oppositeColour) {
                    return true;
                }
            }
        }
        else {
            return false;
        }
        pair<int, int> pointOneIntersectionAwayDown = CalculatePointLeftDiagonalDown(row, column, oppositeColour, pair<int, int>(1, 1));
        if (board->GetBoard()[pointOneIntersectionAwayDown.first][pointOneIntersectionAwayDown.second] == oppositeColour) {
            pair<int, int> pointTwoIntersectionAwayDown = CalculatePointLeftDiagonalUp(row, column, oppositeColour, pair<int, int>(2, 2));
            if (board->GetBoard()[pointTwoIntersectionAwayDown.first][pointTwoIntersectionAwayDown.second] == oppositeColour)
            {
                pair<int, int> pointOneIntersectionAway = CalculatePointLeftDiagonalUp(row, column, oppositeColour, pair<int, int>(1, 1));
                if (board->GetBoard()[pointOneIntersectionAwayDown.first][pointOneIntersectionAwayDown.second] == oppositeColour) {
                    return true;
                }
            }
        }
        else {
            return false;
        }
        return false;
    }
    catch (const std::exception& e)
    {
        std::cerr << e.what() << '\n';
        cout << "Internal Server Error: ShouldBlockRightDiagonalForFive" << endl;
        return false;
    }

}
bool  Strategy::ShouldBlockHorizontalForFour(int row, int column, char oppositeColour) {
    try {
        // check on the top of the diagonal
        pair<int, int> pointOneIntersectionAway = CalculatePointLeftHorizontal(row, column, oppositeColour, pair<int, int>(1, 1));
        if (board->GetBoard()[pointOneIntersectionAway.first][pointOneIntersectionAway.second] == oppositeColour) {
            pair<int, int> pointTwoIntersectionAway = CalculatePointLeftHorizontal(row, column, oppositeColour, pair<int, int>(2, 2));
            if (board->GetBoard()[pointTwoIntersectionAway.first][pointTwoIntersectionAway.second] == oppositeColour)
            {
                pair<int, int> pointOneIntersectionAwayRight = CalculatePointRightHorizontal(row, column, oppositeColour, pair<int, int>(1, 1));
                if (board->GetBoard()[pointOneIntersectionAwayRight.first][pointOneIntersectionAwayRight.second] == oppositeColour) {
                    return true;
                }
            }
        }
        else {
            return false;
        }
        pair<int, int> pointOneIntersectionAwayDown = CalculatePointRightHorizontal(row, column, oppositeColour, pair<int, int>(1, 1));
        if (board->GetBoard()[pointOneIntersectionAwayDown.first][pointOneIntersectionAwayDown.second] == oppositeColour) {
            pair<int, int> pointTwoIntersectionAwayDown = CalculatePointRightHorizontal(row, column, oppositeColour, pair<int, int>(2, 2));
            if (board->GetBoard()[pointTwoIntersectionAwayDown.first][pointTwoIntersectionAwayDown.second] == oppositeColour)
            {
                pair<int, int> pointOneIntersectionAway = CalculatePointLeftHorizontal(row, column, oppositeColour, pair<int, int>(1, 1));
                if (board->GetBoard()[pointOneIntersectionAwayDown.first][pointOneIntersectionAwayDown.second] == oppositeColour) {
                    return true;
                }
            }
        }
        else {
            return false;
        }
        return false;
    }
    catch (const std::exception& e)
    {
        std::cerr << e.what() << '\n';
        cout << "Internal Server Error: ShouldBlockRightDiagonalForFive" << endl;
        return false;
    }

}
bool  Strategy::ShouldBlockVerticalForFour(int row, int column, char oppositeColour) {
    try {
        // check on the top of the diagonal
        pair<int, int> pointOneIntersectionAway = CalculatePointUpVertical(row, column, oppositeColour, pair<int, int>(1, 1));
        if (board->GetBoard()[pointOneIntersectionAway.first][pointOneIntersectionAway.second] == oppositeColour) {
            pair<int, int> pointTwoIntersectionAway = CalculatePointUpVertical(row, column, oppositeColour, pair<int, int>(2, 2));
            if (board->GetBoard()[pointTwoIntersectionAway.first][pointTwoIntersectionAway.second] == oppositeColour)
            {
                pair<int, int> pointOneIntersectionAwayRight = CalculatePointDownVertical(row, column, oppositeColour, pair<int, int>(1, 1));
                if (board->GetBoard()[pointOneIntersectionAwayRight.first][pointOneIntersectionAwayRight.second] == oppositeColour) {
                    return true;
                }
            }
        }
        else {
            return false;
        }
        pair<int, int> pointOneIntersectionAwayDown = CalculatePointDownVertical(row, column, oppositeColour, pair<int, int>(1, 1));
        if (board->GetBoard()[pointOneIntersectionAwayDown.first][pointOneIntersectionAwayDown.second] == oppositeColour) {
            pair<int, int> pointTwoIntersectionAwayDown = CalculatePointDownVertical(row, column, oppositeColour, pair<int, int>(2, 2));
            if (board->GetBoard()[pointTwoIntersectionAwayDown.first][pointTwoIntersectionAwayDown.second] == oppositeColour)
            {
                pair<int, int> pointOneIntersectionAway = CalculatePointUpVertical(row, column, oppositeColour, pair<int, int>(1, 1));
                if (board->GetBoard()[pointOneIntersectionAwayDown.first][pointOneIntersectionAwayDown.second] == oppositeColour) {
                    return true;
                }
            }
        }
        else {
            return false;
        }
        return false;
    }
    catch (const std::exception& e)
    {
        std::cerr << e.what() << '\n';
        cout << "Internal Server Error: ShouldBlockRightDiagonalForFive" << endl;
        return false;
    }

}

bool Strategy::ShouldBlockRightDiagonalConsecutive(int row, int column, char oppositeColour)
{
    try{
        pair<int, int> pointOneIntersectionAway = CalculatePointRightDiagonalUp(row, column, oppositeColour, pair<int, int>(1, 1));
        if (board->GetBoard()[pointOneIntersectionAway.first][pointOneIntersectionAway.second] == oppositeColour) {
            pair<int, int> pointTwoIntersectionAway = CalculatePointRightDiagonalUp(row, column, oppositeColour, pair<int, int>(2, 2));
            if (board->GetBoard()[pointTwoIntersectionAway.first][pointTwoIntersectionAway.second] == oppositeColour)
            {
                return true;
            }
        }
        pointOneIntersectionAway = CalculatePointRightDiagonalDown(row, column, oppositeColour, pair<int, int>(1, 1));
        if (board->GetBoard()[pointOneIntersectionAway.first][pointOneIntersectionAway.second] == oppositeColour) {
            pair<int, int> pointTwoIntersectionAway = CalculatePointRightDiagonalDown(row, column, oppositeColour, pair<int, int>(2, 2));
            if (board->GetBoard()[pointTwoIntersectionAway.first][pointTwoIntersectionAway.second] == oppositeColour)
            {
                return true;
            }
        }
        return false;

    }
    catch (const std::exception& e)
    {
        std::cerr << e.what() << '\n';
        cout << "Internal Server Error: ShouldBlockRightDiagonalForFive" << endl;
        return false;
    }

}

bool Strategy::ShouldBlockLeftDiagonalForConsecutive(int row, int column, char oppositeColour)
{
    try {
        pair<int, int> pointOneIntersectionAway = CalculatePointLeftDiagonalUp(row, column, oppositeColour, pair<int, int>(1, 1));
        if (board->GetBoard()[pointOneIntersectionAway.first][pointOneIntersectionAway.second] == oppositeColour) {
            pair<int, int> pointTwoIntersectionAway = CalculatePointLeftDiagonalUp(row, column, oppositeColour, pair<int, int>(2, 2));
            if (board->GetBoard()[pointTwoIntersectionAway.first][pointTwoIntersectionAway.second] == oppositeColour)
            {
                return true;
            }
        }
        pointOneIntersectionAway = CalculatePointLeftDiagonalDown(row, column, oppositeColour, pair<int, int>(1, 1));
        if (board->GetBoard()[pointOneIntersectionAway.first][pointOneIntersectionAway.second] == oppositeColour) {
            pair<int, int> pointTwoIntersectionAway = CalculatePointLeftDiagonalDown(row, column, oppositeColour, pair<int, int>(2, 2));
            if (board->GetBoard()[pointTwoIntersectionAway.first][pointTwoIntersectionAway.second] == oppositeColour)
            {
                return true;
            }
        }
        return false;

    }
    catch (const std::exception& e)
    {
        std::cerr << e.what() << '\n';
        cout << "Internal Server Error: ShouldBlockRightDiagonalForFive" << endl;
        return false;
    }
}

bool Strategy::ShouldBlockHorizontalForConsecutive(int row, int column, char oppositeColour)
{
    try {
        pair<int, int> pointOneIntersectionAway = CalculatePointLeftHorizontal(row, column, oppositeColour, pair<int, int>(1, 1));
        if (board->GetBoard()[pointOneIntersectionAway.first][pointOneIntersectionAway.second] == oppositeColour) {
            pair<int, int> pointTwoIntersectionAway = CalculatePointLeftHorizontal(row, column, oppositeColour, pair<int, int>(2, 2));
            if (board->GetBoard()[pointTwoIntersectionAway.first][pointTwoIntersectionAway.second] == oppositeColour)
            {
                return true;
            }
        }
        pointOneIntersectionAway = CalculatePointRightHorizontal(row, column, oppositeColour, pair<int, int>(1, 1));
        if (board->GetBoard()[pointOneIntersectionAway.first][pointOneIntersectionAway.second] == oppositeColour) {
            pair<int, int> pointTwoIntersectionAway = CalculatePointRightHorizontal(row, column, oppositeColour, pair<int, int>(2, 2));
            if (board->GetBoard()[pointTwoIntersectionAway.first][pointTwoIntersectionAway.second] == oppositeColour)
            {
                return true;
            }
        }
        return false;

    }
    catch (const std::exception& e)
    {
        std::cerr << e.what() << '\n';
        cout << "Internal Server Error: ShouldBlockRightDiagonalForFive" << endl;
        return false;
    }
}

bool Strategy::ShouldBlockVerticalForConsecutive(int row, int column, char oppositeColour)
{
    try {
        pair<int, int> pointOneIntersectionAway = CalculatePointUpVertical(row, column, oppositeColour, pair<int, int>(1, 1));
        if (board->GetBoard()[pointOneIntersectionAway.first][pointOneIntersectionAway.second] == oppositeColour) {
            pair<int, int> pointTwoIntersectionAway = CalculatePointUpVertical(row, column, oppositeColour, pair<int, int>(2, 2));
            if (board->GetBoard()[pointTwoIntersectionAway.first][pointTwoIntersectionAway.second] == oppositeColour)
            {
                return true;
            }
        }
        pointOneIntersectionAway = CalculatePointDownVertical(row, column, oppositeColour, pair<int, int>(1, 1));
        if (board->GetBoard()[pointOneIntersectionAway.first][pointOneIntersectionAway.second] == oppositeColour) {
            pair<int, int> pointTwoIntersectionAway = CalculatePointDownVertical(row, column, oppositeColour, pair<int, int>(2, 2));
            if (board->GetBoard()[pointTwoIntersectionAway.first][pointTwoIntersectionAway.second] == oppositeColour)
            {
                return true;
            }
        }
        return false;

    }
    catch (const std::exception& e)
    {
        std::cerr << e.what() << '\n';
        cout << "Internal Server Error: ShouldBlockRightDiagonalForFive" << endl;
        return false;
    }
}
std::pair<int, int> Strategy::BestLocationForCreating(char colour)
{
    try {
        pair<int, int> bestLocation(-1, -1);
        // check for bridges and place inside the bridge
        for (int row = 0; row < board->GetBoardSize(); row++)
        {
            for (int column = 0; column < board->GetBoardSize(); column++)
            {
                pair<int, int> locationToPlace = CheckForBridges(row, column, colour);
                if (locationToPlace.first != -1 || locationToPlace.second != -1) {
                    
                    return pair<int, int>(row, column);
                }
                
            }
        }
        // create a bridge
        for (int row = 0; row < board->GetBoardSize(); row++)
        {
            for (int column = 0; column < board->GetBoardSize(); column++)
            {
                pair<int, int> locationToPlace = CreateBridge(row, column, colour);
                if (locationToPlace.first != -1 || locationToPlace.second != -1) {
                    
                }




            }
        }
        // place randomly in a spot where bridge can be created
        // place randomly since no suitable place found
    }
    catch (const std::exception& e)
    {
        std::cerr << e.what() << '\n';
        cout << "Internal Server Error: ShouldBlockRightDiagonalForFive" << endl;
        return pair<int, int>(-1, -1);
    }
}

std::pair<int, int> Strategy::CreateBridge(int row, int column, char colour)
{
    try {
        pair<int, int> righDiagonalUp = CalculatePointRightDiagonalUp(row, column, colour, pair<int, int>(3,3));
        if (righDiagonalUp.first != -1 || righDiagonalUp.second != -1) {
            if (board->IsPositionEmpty(righDiagonalUp.first,righDiagonalUp.second)) {
                int count = 0;
                for (int tmpRow = row, tmpColumn = column; tmpRow >= righDiagonalUp.first; tmpRow--, tmpColumn++) {
                    if (board->GetBoard()[tmpRow][tmpColumn] == colour || board->IsPositionEmpty(tmpRow, tmpColumn)) {
                        count++;
                    }
                }
                if (count == 2) {
                    return righDiagonalUp;
                }
            }

        }
        // calculate the point ie 3 distance away in rt diagonal - down send (-1, -1) if not within board
        pair<int, int> righDiagonalDown = CalculatePointRightDiagonalDown(row, column, colour, pair<int, int>(3, 3));
        if (righDiagonalDown.first != -1 || righDiagonalDown.second != -1) {
            if (board->IsPositionEmpty(righDiagonalDown.first,righDiagonalDown.second)) {
                int count = 0;
                for (int tmpRow = row, tmpColumn = column; tmpRow <= righDiagonalDown.first; tmpRow++, tmpColumn--) {
                    if (board->GetBoard()[tmpRow][tmpColumn] == colour || board->IsPositionEmpty(tmpRow, tmpColumn)) {
                        count++;
                    }
                }
                if (count == 2) {
                    return righDiagonalDown;

                }
            }
        }
        // calculate the point ie 3 distance away in lt diagonal -up send (-1, -1) if not within board
        pair<int, int> leftDiagonalUp = CalculatePointLeftDiagonalUp(row, column, colour, pair<int, int>(3, 3));
        if (leftDiagonalUp.first != -1 || leftDiagonalUp.second != -1) {
            if (board->IsPositionEmpty(leftDiagonalUp.first, leftDiagonalUp.second)) {

                int count = 0;
                for (int tmpRow = row, tmpColumn = column; tmpRow >= leftDiagonalUp.first; tmpRow--, tmpColumn--) {
                    if (board->GetBoard()[tmpRow][tmpColumn] == board->GetOppositeColour(colour) || board->IsPositionEmpty(tmpRow, tmpColumn)) {
                        count++;
                    }
                }
                if (count == 2) {
                    return leftDiagonalUp;
                }
            }
        }
        // calculate the point ie 3 distance away in lt diagonal -down send (-1, -1) if not within board
        pair<int, int> leftDiagonalDown = CalculatePointLeftDiagonalDown(row, column, colour, pair<int, int>(3, 3));
        if (leftDiagonalDown.first != -1 || leftDiagonalDown.second != -1) {
            if (board->IsPositionEmpty(leftDiagonalDown.first, leftDiagonalDown.second)) {

                int count = 0;
                for (int tmpRow = row, tmpColumn = column; tmpRow <= leftDiagonalDown.first; tmpRow++, tmpColumn++) {
                    if (board->GetBoard()[tmpRow][tmpColumn] == colour || board->IsPositionEmpty(tmpRow, tmpColumn)) {
                        count++;
                    }
                }
                if (count == 2) {
                    
                    return leftDiagonalDown;
                }
            }
        }
        // calculate the point ie 3 distance away in lt horizontal send (-1, -1) if not within board
        pair<int, int> leftHorizontal = CalculatePointLeftHorizontal(row, column, colour, pair<int, int>(3, 3));
        if (leftHorizontal.first != -1 || leftHorizontal.second != -1) {
            if (board->IsPositionEmpty(leftHorizontal.first, leftHorizontal.second)) {

                int count = 0;
                for (int tmpRow = row, tmpColumn = column; tmpColumn >= leftHorizontal.second; tmpColumn--) {
                    if (board->GetBoard()[tmpRow][tmpColumn] == colour || board->IsPositionEmpty(tmpRow, tmpColumn)) {
                        count++;
                    }
                }
                if (count == 2) {
                    
                    return leftHorizontal;
                }
            }
        }
        // calculate the point ie 3 distance away in rt horizontal send (-1, -1) if not within board
        pair<int, int> rightHorizontal = CalculatePointRightHorizontal(row, column, colour, pair<int, int>(3, 3));
        if (rightHorizontal.first != -1 || rightHorizontal.second != -1) {
            if (board->IsPositionEmpty(rightHorizontal.first, rightHorizontal.second)) {

                int count = 0;
                for (int tmpRow = row, tmpColumn = column; tmpColumn <= rightHorizontal.second; tmpColumn++) {
                    if (board->GetBoard()[tmpRow][tmpColumn] ==colour || board->IsPositionEmpty(tmpRow, tmpColumn)) {
                        count++;
                    }
                }
                if (count == 2) {
                    // remove the piece
                    return rightHorizontal;

                }
            }
        }
        // calculate the point ie 3 distance away in rt vertical send (-1, -1) if not within board
        pair<int, int> upVertical = CalculatePointUpVertical(row, column, colour, pair<int, int>(3, 3));
        if (upVertical.first != -1 || upVertical.second != -1) {
            if (board->IsPositionEmpty(upVertical.first, upVertical.second)) {

                int count = 0;
                for (int tmpRow = row, tmpColumn = column; tmpRow >= upVertical.first; tmpRow--) {
                    if (board->GetBoard()[tmpRow][tmpColumn] == colour || board->IsPositionEmpty(tmpRow, tmpColumn)) {
                        count++;
                    }
                }
                if (count == 2) {
                    return upVertical;
                }
            }
        }
        // calculate the point ie 3 distance away in tt vertical send (-1, -1) if not within board
        pair<int, int> downVertical = CalculatePointDownVertical(row, column, colour, pair<int, int>(3, 3));
        if (downVertical.first != -1 || downVertical.second != -1) {
            if (board->IsPositionEmpty(downVertical.first, downVertical.second)) {

                int count = 0;
                for (int tmpRow = row, tmpColumn = column; tmpRow <= downVertical.first; tmpRow++) {
                    if (board->GetBoard()[tmpRow][tmpColumn] == colour || board->IsPositionEmpty(tmpRow, tmpColumn)) {
                        count++;
                    }
                }
                if (count == 2) {
                    return downVertical;

                }
            }
        }
        return pair<int, int>(-1, -1);

    }
    catch (const std::exception& e)
    {
        std::cerr << e.what() << '\n';
        cout << "Internal Server Error: CreateBridge" << endl;
        return pair<int, int>(-1, -1);
    }
}


std::pair<int, int> Strategy::CheckForBridges(int row, int column, char colour)
{
    try {
        pair<int, int> righDiagonalUp = CalculatePointRightDiagonalUp(row, column, colour, pair<int, int>(3, 3));
        if (righDiagonalUp.first != -1 || righDiagonalUp.second != -1) {
            if (colour == board->GetBoard()[righDiagonalUp.first][righDiagonalUp.second]) {
                int count = 0;
                for (int tmpRow = row, tmpColumn = column; tmpRow >= righDiagonalUp.first; tmpRow--, tmpColumn++) {
                    if (board->IsPositionEmpty(tmpRow, tmpColumn)) {
                        count++;
                    }
                }
                if (count == 2) {
                    return righDiagonalUp;
                }
            }

        }
        // calculate the point ie 3 distance away in rt diagonal - down send (-1, -1) if not within board
        pair<int, int> righDiagonalDown = CalculatePointRightDiagonalDown(row, column, colour, pair<int, int>(3, 3));
        if (righDiagonalDown.first != -1 || righDiagonalDown.second != -1) {
            if (colour == board->GetBoard()[righDiagonalDown.first][righDiagonalDown.second]) {
                int count = 0;
                for (int tmpRow = row, tmpColumn = column; tmpRow <= righDiagonalDown.first; tmpRow++, tmpColumn--) {
                    if (board->IsPositionEmpty(tmpRow, tmpColumn)) {
                        count++;
                    }
                }
                if (count == 2) {
                    return righDiagonalDown;

                }
            }
        }
        // calculate the point ie 3 distance away in lt diagonal -up send (-1, -1) if not within board
        pair<int, int> leftDiagonalUp = CalculatePointLeftDiagonalUp(row, column, colour, pair<int, int>(3, 3));
        if (leftDiagonalUp.first != -1 || leftDiagonalUp.second != -1) {
            if (colour == board->GetBoard()[leftDiagonalUp.first][leftDiagonalUp.second]) {
                int count = 0;
                for (int tmpRow = row, tmpColumn = column; tmpRow >= leftDiagonalUp.first; tmpRow--, tmpColumn--) {
                        if (board->IsPositionEmpty(tmpRow, tmpColumn)) {
                        count++;
                    }
                }
                if (count == 2) {
                    return leftDiagonalUp;
                }
            }
        }
        // calculate the point ie 3 distance away in lt diagonal -down send (-1, -1) if not within board
        pair<int, int> leftDiagonalDown = CalculatePointLeftDiagonalDown(row, column, colour, pair<int, int>(3, 3));
        if (leftDiagonalDown.first != -1 || leftDiagonalDown.second != -1) {
            if (colour == board->GetBoard()[leftDiagonalDown.first][leftDiagonalDown.second]) {

                int count = 0;
                for (int tmpRow = row, tmpColumn = column; tmpRow <= leftDiagonalDown.first; tmpRow++, tmpColumn++) {
                        if (board->IsPositionEmpty(tmpRow, tmpColumn)) {

                        count++;
                    }
                }
                if (count == 2) {

                    return leftDiagonalDown;
                }
            }
        }
        // calculate the point ie 3 distance away in lt horizontal send (-1, -1) if not within board
        pair<int, int> leftHorizontal = CalculatePointLeftHorizontal(row, column, colour, pair<int, int>(3, 3));
        if (leftHorizontal.first != -1 || leftHorizontal.second != -1) {
            if (colour == board->GetBoard()[leftHorizontal.first][leftHorizontal.second]) {

                int count = 0;
                for (int tmpRow = row, tmpColumn = column; tmpColumn >= leftHorizontal.second; tmpColumn--) {
                    if (board->IsPositionEmpty(tmpRow, tmpColumn)) {

                        count++;
                    }
                }
                if (count == 2) {

                    return leftHorizontal;
                }
            }
        }
        // calculate the point ie 3 distance away in rt horizontal send (-1, -1) if not within board
        pair<int, int> rightHorizontal = CalculatePointRightHorizontal(row, column, colour, pair<int, int>(3, 3));
        if (rightHorizontal.first != -1 || rightHorizontal.second != -1) {
            if (colour == board->GetBoard()[rightHorizontal.first][rightHorizontal.second]) {

                int count = 0;
                for (int tmpRow = row, tmpColumn = column; tmpColumn <= rightHorizontal.second; tmpColumn++) {
                    if ( board->IsPositionEmpty(tmpRow, tmpColumn)) {
                        count++;
                    }
                }
                if (count == 2) {
                    // remove the piece
                    return rightHorizontal;

                }
            }
        }
        // calculate the point ie 3 distance away in rt vertical send (-1, -1) if not within board
        pair<int, int> upVertical = CalculatePointUpVertical(row, column, colour, pair<int, int>(3, 3));
        if (upVertical.first != -1 || upVertical.second != -1) {
            if (colour == board->GetBoard()[upVertical.first][upVertical.second]) {

                int count = 0;
                for (int tmpRow = row, tmpColumn = column; tmpRow >= upVertical.first; tmpRow--) {
                    if ( board->IsPositionEmpty(tmpRow, tmpColumn)) {
                        count++;
                    }
                }
                if (count == 2) {
                    return upVertical;
                }
            }
        }
        // calculate the point ie 3 distance away in tt vertical send (-1, -1) if not within board
        pair<int, int> downVertical = CalculatePointDownVertical(row, column, colour, pair<int, int>(3, 3));
        if (downVertical.first != -1 || downVertical.second != -1) {
            if (colour == board->GetBoard()[downVertical.first][downVertical.second]) {

                int count = 0;
                for (int tmpRow = row, tmpColumn = column; tmpRow <= downVertical.first; tmpRow++) {
                    if ( board->IsPositionEmpty(tmpRow, tmpColumn)) {
                        count++;
                    }
                }
                if (count == 2) {
                    return downVertical;

                }
            }
        }
        return pair<int, int>(-1, -1);

    }
    catch (const std::exception& e)
    {
        std::cerr << e.what() << '\n';
        cout << "Internal Server Error: ShouldBlockRightDiagonalForFive" << endl;
        return pair<int, int>(-1, -1);
    }
}
bool Strategy::IsGoodPointToCreateBridge(int row, int column, char colour)
{
    try {
        pair<int, int> righDiagonalUp = CalculatePointRightDiagonalUp(row, column, colour, pair<int, int>(3, 3));
        if (righDiagonalUp.first != -1 || righDiagonalUp.second != -1) {
            if (board->IsPositionEmpty(righDiagonalUp.first, righDiagonalUp.second)) {
                int count = 0;
                for (int tmpRow = row, tmpColumn = column; tmpRow >= righDiagonalUp.first; tmpRow--, tmpColumn++) {
                    if (board->IsPositionEmpty(tmpRow, tmpColumn)) {
                        count++;
                    }
                }
                if (count == 2) {
                    return true;
                }
            }

        }
        pair<int, int> righDiagonalDown = CalculatePointRightDiagonalDown(row, column, colour, pair<int, int>(3, 3));
        if (righDiagonalDown.first != -1 || righDiagonalDown.second != -1) {
            if (board->IsPositionEmpty(righDiagonalDown.first, righDiagonalDown.second)) {
                int count = 0;
                for (int tmpRow = row, tmpColumn = column; tmpRow <= righDiagonalDown.first; tmpRow++, tmpColumn--) {
                    if (board->IsPositionEmpty(tmpRow, tmpColumn)) {
                        count++;
                    }
                }
                if (count == 2) {
                    return true;

                }
            }
        }
        // calculate the point ie 3 distance away in lt diagonal -up send (-1, -1) if not within board
        pair<int, int> leftDiagonalUp = CalculatePointLeftDiagonalUp(row, column, colour, pair<int, int>(3, 3));
        if (leftDiagonalUp.first != -1 || leftDiagonalUp.second != -1) {
            if (board->IsPositionEmpty(leftDiagonalUp.first, leftDiagonalUp.second)) {

                int count = 0;
                for (int tmpRow = row, tmpColumn = column; tmpRow >= leftDiagonalUp.first; tmpRow--, tmpColumn--) {
                    if ( board->IsPositionEmpty(tmpRow, tmpColumn)) {
                        count++;
                    }
                }
                if (count == 2) {
                    return true;
                }
            }
        }
        // calculate the point ie 3 distance away in lt diagonal -down send (-1, -1) if not within board
        pair<int, int> leftDiagonalDown = CalculatePointLeftDiagonalDown(row, column, colour, pair<int, int>(3, 3));
        if (leftDiagonalDown.first != -1 || leftDiagonalDown.second != -1) {
            if (board->IsPositionEmpty(leftDiagonalDown.first, leftDiagonalDown.second)) {

                int count = 0;
                for (int tmpRow = row, tmpColumn = column; tmpRow <= leftDiagonalDown.first; tmpRow++, tmpColumn++) {
                    if ( board->IsPositionEmpty(tmpRow, tmpColumn)) {
                        count++;
                    }
                }
                if (count == 2) {

                    return true;
                }
            }
        }
        // calculate the point ie 3 distance away in lt horizontal send (-1, -1) if not within board
        pair<int, int> leftHorizontal = CalculatePointLeftHorizontal(row, column, colour, pair<int, int>(3, 3));
        if (leftHorizontal.first != -1 || leftHorizontal.second != -1) {
            if (board->IsPositionEmpty(leftHorizontal.first, leftHorizontal.second)) {

                int count = 0;
                for (int tmpRow = row, tmpColumn = column; tmpColumn >= leftHorizontal.second; tmpColumn--) {
                    if ( board->IsPositionEmpty(tmpRow, tmpColumn)) {
                        count++;
                    }
                }
                if (count == 2) {

                    return true;
                }
            }
        }
        // calculate the point ie 3 distance away in rt horizontal send (-1, -1) if not within board
        pair<int, int> rightHorizontal = CalculatePointRightHorizontal(row, column, colour, pair<int, int>(3, 3));
        if (rightHorizontal.first != -1 || rightHorizontal.second != -1) {
            if (board->IsPositionEmpty(rightHorizontal.first, rightHorizontal.second)) {

                int count = 0;
                for (int tmpRow = row, tmpColumn = column; tmpColumn <= rightHorizontal.second; tmpColumn++) {
                    if ( board->IsPositionEmpty(tmpRow, tmpColumn)) {
                        count++;
                    }
                }
                if (count == 2) {
                    // remove the piece
                    return true;

                }
            }
        }
        // calculate the point ie 3 distance away in rt vertical send (-1, -1) if not within board
        pair<int, int> upVertical = CalculatePointUpVertical(row, column, colour, pair<int, int>(3, 3));
        if (upVertical.first != -1 || upVertical.second != -1) {
            if (board->IsPositionEmpty(upVertical.first, upVertical.second)) {

                int count = 0;
                for (int tmpRow = row, tmpColumn = column; tmpRow >= upVertical.first; tmpRow--) {
                    if ( board->IsPositionEmpty(tmpRow, tmpColumn)) {
                        count++;
                    }
                }
                if (count == 2) {
                    return true;
                }
            }
        }
        // calculate the point ie 3 distance away in tt vertical send (-1, -1) if not within board
        pair<int, int> downVertical = CalculatePointDownVertical(row, column, colour, pair<int, int>(3, 3));
        if (downVertical.first != -1 || downVertical.second != -1) {
            if (board->IsPositionEmpty(downVertical.first, downVertical.second)) {

                int count = 0;
                for (int tmpRow = row, tmpColumn = column; tmpRow <= downVertical.first; tmpRow++) {
                    if ( board->IsPositionEmpty(tmpRow, tmpColumn)) {
                        count++;
                    }
                }
                if (count == 2) {
                    return true;

                }
            }
        }
        return false;
    }
    catch (const std::exception& e)
    {
        std::cerr << e.what() << '\n';
        cout << "Internal Server Error: IsGoodPointToCreateBridge" << endl;
        return false;
    }
}
