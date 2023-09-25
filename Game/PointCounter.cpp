#include <iostream>
#include "PointCounter.h"
using namespace std;

PointCounter::PointCounter(Board* board)
{
    this->board = board;
    if (!this->SetHasWon(false)) {
        cout << "Internal Server Error: PointCounter::SetHasWon()" << endl;
    }
}
int PointCounter::GetPoints() {
    return this->points;
}
bool PointCounter::GetHasWon()
{
    return this->HasWon;
}

bool PointCounter::SetHasWon(bool input)
{
    try
    {
        this->HasWon = input;
        return true;
    }
    catch (const std::exception& e)
    {
        cout << e.what() << endl;
        cout << "Internal Server Error: PointCounter::SetHasWon()" << endl;
        return false;
    }
}

int PointCounter::CalculateCapture(int row, int column, char colour)
{
    try{
        int totalCapture = 0;
        // calculate the point ie 3 distance away in rt diagonal - up send (-1, -1) if not within board
        pair<int, int> righDiagonalUp = CalculatePointRightDiagonalUp(row, column, colour);
        // check if there is piece
        // if there is remove 
        // gain a point
        // else continue
        if (righDiagonalUp.first != -1 || righDiagonalUp.second != -1) {
            if(colour == board->GetBoard()[righDiagonalUp.first][righDiagonalUp.second]) {
                int count = 0;
                vector<pair<int, int>> captureLocation;
                for (int tmpRow = row, tmpColumn = column; tmpRow >= righDiagonalUp.first; tmpRow--, tmpColumn++) {
                    if (board->GetBoard()[tmpRow][tmpColumn] == board->GetOppositeColour(colour)) {
                        captureLocation.push_back(pair<int, int>(tmpRow, tmpColumn));
                        count++;
                    }
                }
                if (count == 2) {
                    // remove the piece
                    for (auto location : captureLocation)
                    {
                        board->RemovePiece(location.first, location.second);
                    }
                    totalCapture++;
                }
            }
            
        }
        // calculate the point ie 3 distance away in rt diagonal - down send (-1, -1) if not within board
        pair<int, int> righDiagonalDown = CalculatePointRightDiagonalDown(row, column, colour);
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
                    // remove the piece
                    for (auto location : captureLocation)
                    {
                        board->RemovePiece(location.first, location.second);
                    }
                    totalCapture++;

                }
            }
        }
        // calculate the point ie 3 distance away in lt diagonal -up send (-1, -1) if not within board
        pair<int, int> leftDiagonalUp = CalculatePointLeftDiagonalUp(row, column, colour);
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
                        // remove the piece
                        for (auto location : captureLocation)
                        {
                            board->RemovePiece(location.first, location.second);
                        }
                        totalCapture++;
                    }
                }
        }
        // calculate the point ie 3 distance away in lt diagonal -down send (-1, -1) if not within board
        pair<int, int> leftDiagonalDown = CalculatePointLeftDiagonalDown(row, column, colour);
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
                    // remove the piece
                    for (auto location : captureLocation)
                    {
                        board->RemovePiece(location.first, location.second);
                    }
                    totalCapture++;

                }
            }
        }
        // calculate the point ie 3 distance away in lt horizontal send (-1, -1) if not within board
        pair<int, int> leftHorizontal = CalculatePointLeftHorizontal(row, column, colour);
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
                    // remove the piece
                    for (auto location : captureLocation)
                    {
                        board->RemovePiece(location.first, location.second);
                    }
                    totalCapture++;

                }
            }
        }
        // calculate the point ie 3 distance away in rt horizontal send (-1, -1) if not within board
        pair<int, int> rightHorizontal = CalculatePointRightHorizontal(row, column, colour);
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
                    // remove the piece
                    for (auto location : captureLocation)
                    {
                        board->RemovePiece(location.first, location.second);
                    }
                    totalCapture++;

                }
            }
        }
        // calculate the point ie 3 distance away in rt vertical send (-1, -1) if not within board
        pair<int, int> upVertical = CalculatePointUpVertical(row, column, colour);
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
                    // remove the piece
                    for (auto location : captureLocation)
                    {
                        board->RemovePiece(location.first, location.second);
                    }
                    totalCapture++;

                }
            }
        }
        // calculate the point ie 3 distance away in tt vertical send (-1, -1) if not within board
        pair<int, int> downVertical = CalculatePointDownVertical(row, column, colour);
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
                    // remove the piece
                    for (auto location : captureLocation)
                    {
                        board->RemovePiece(location.first, location.second);
                    }
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



int PointCounter::CalculatePoint(int row, int column, char colour)
{
    try
    {
        int totalPoint = 0;
        int rtDiagonalSequence = TotalRightDiagonalPieces(row, column, colour) + 1;
        int ltDiagonalSequence = TotalLeftDiagonalPieces(row, column, colour) + 1;
        int horizontalSequence = TotalHorizontalPieces(row, column, colour) + 1;
        int verticalSequence = TotalVerticalPieces(row, column, colour) + 1;
        vector<int> sequences{ rtDiagonalSequence, ltDiagonalSequence, horizontalSequence, verticalSequence };
        for (int i : sequences)
        {
            if (i >= 4)
            {
                if (i >= 5)
                {
                    if (!(i % 5))
                    {
                        // a win is 5 points
                        totalPoint += i;
                    }
                    else
                    {
                        totalPoint += (i - 5) / 4; // extra point if it is greater
                        totalPoint += 5; // for winning
                    }
                    HasWon = true;
                }
                else
                {
                    totalPoint++;
                }
            }
        }
        return totalPoint;
    }
    catch (const std::exception& e)
    {
        std::cerr << e.what() << '\n';
        return false;
    }
}
bool PointCounter::isThereWinner() {
    return HasWon;
}
// find all diagonal points
//       w
//     w
//   w
// w
int PointCounter::TotalRightDiagonalPieces(int row, int column, char colour)
{
    try
    {
        int totalCount = 0;
        int tmpRow = row, tmpColumn = column;
        totalCount += CheckMoreDownLeft(++tmpRow, --tmpColumn, totalCount, colour);
         tmpRow = row, tmpColumn = column;
        totalCount += CheckMoreUpRight(--tmpRow, ++tmpColumn, totalCount, colour);
        return totalCount;
    }
    catch (const std::exception& e)
    {
        std::cerr << e.what() << '\n';
        return 0;
    }
}
int PointCounter::TotalLeftDiagonalPieces(int row, int column, char colour)
{
    try
    {
        int totalCount = 0;
        int tmpRow = row, tmpColumn = column;

        totalCount += CheckMoreUpLeft(--tmpRow, --tmpColumn, totalCount, colour);
        tmpRow = row, tmpColumn = column;
        totalCount += CheckMoreDownRight(++tmpRow, ++tmpColumn, totalCount, colour);
        return totalCount;
    }
    catch (const std::exception& e)
    {
        std::cerr << e.what() << '\n';
        return 0;
    }
}
int PointCounter::TotalHorizontalPieces(int row, int column, char colour)
{
    try
    {
        int totalCount = 0;
        int tmpRow = row, tmpColumn = column;
        totalCount += CheckMoreLeft(tmpRow, --tmpColumn, totalCount, colour);
        tmpRow = row, tmpColumn = column;
        totalCount += CheckMoreRight(tmpRow, ++tmpColumn, totalCount, colour);
        return totalCount;
    }
    catch (const std::exception& e)
    {
        std::cerr << e.what() << '\n';
        return 0;
    }
}
int PointCounter::TotalVerticalPieces(int row, int column, char colour)
{
    try
    {
        int totalCount = 0;
        int tmpRow = row, tmpColumn = column;
        totalCount += CheckMoreUp(--tmpRow, tmpColumn, totalCount, colour);
        tmpRow = row, tmpColumn = column;
        totalCount += CheckMoreDown(++tmpRow, tmpColumn, totalCount, colour);
        return totalCount;
    }
    catch (const std::exception& e)
    {
        std::cerr << e.what() << '\n';
        return 0;
    }
}

int PointCounter::CheckMoreDownLeft(int row, int column, int count, char colour)
{
    try {
        int totalCount = 0;

        for (int tmpRow = row, tmpColumn = column; tmpRow < board->GetBoardSize() && tmpColumn >= 0; tmpRow++, tmpColumn--) {
            if (board->GetBoard()[tmpRow][tmpColumn] != colour) {
                return totalCount;
            }
            totalCount++;
        }
        return totalCount;
    }
    catch (const std::exception& e)
    {
        std::cerr << e.what() << '\n';
        return 0;
    }
}


int PointCounter::CheckMoreDownRight(int row, int column, int count, char colour)
{
    try {
        int totalCount = 0;

        for (int tmpRow = row, tmpColumn = column; tmpRow < board->GetBoardSize() && tmpColumn < board->GetBoardSize(); tmpRow++, tmpColumn++) {
            if (board->GetBoard()[tmpRow][tmpColumn] != colour) {
                return totalCount;
            }
            totalCount++;
        }
        return totalCount;
    }
    catch (const std::exception& e)
    {
        std::cerr << e.what() << '\n';
        return 0;
    }
}

int PointCounter::CheckMoreUpLeft(int row, int column, int count, char colour)
{
    try {
        int totalCount = 0;

        for (int tmpRow = row, tmpColumn = column; tmpRow >= 0 && tmpColumn >= 0; tmpRow--, tmpColumn--) {
            if (board->GetBoard()[tmpRow][tmpColumn] != colour) {
                return totalCount;
            }
            totalCount++;
        }
        return totalCount;
    }
    catch (const std::exception& e)
    {
        std::cerr << e.what() << '\n';
        return 0;
    }
}

int PointCounter::CheckMoreUpRight(int row, int column, int count, char colour)
{
    try {
        int totalCount = 0;

        for (int tmpRow = row, tmpColumn = column; tmpRow > 0  && tmpColumn  < board->GetBoardSize(); tmpRow--, tmpColumn++) {
            if (board->GetBoard()[tmpRow][tmpColumn] != colour) {
                return totalCount;
            }
            totalCount++;
        }
        return totalCount;
    }
    catch (const std::exception& e)
    {
        std::cerr << e.what() << '\n';
        return 0;
    }
}

int PointCounter::CheckMoreUp(int row, int column, int count, char colour)
{
    try {
        int totalCount = 0;

        for (; row >= 0; row--) {
            if (board->GetBoard()[row][column] != colour) {
                return totalCount;
            }
            totalCount++;
        }
        return totalCount;
    }
    catch (const std::exception& e)
    {
        std::cerr << e.what() << '\n';
        return 0;
    }
}

int PointCounter::CheckMoreDown(int row, int column, int count, char colour)
{
    try {
        int totalCount = 0;

        for (; row < board->GetBoardSize(); row++) {
            if (board->GetBoard()[row][column] != colour) {
                return totalCount;
            }
            totalCount++;
        }
        return totalCount;
    }
    catch (const std::exception& e)
    {
        std::cerr << e.what() << '\n';
        return 0;
    }
}

int PointCounter::CheckMoreRight(int row, int column, int count, char colour)
{
    try {
        int totalCount = 0;

        for (; column < board->GetBoardSize(); column++) {
            if (board->GetBoard()[row][column] != colour) {
                return totalCount;
            }
            totalCount++;
        }
        return totalCount;
    }
    catch (const std::exception& e)
    {
        std::cerr << e.what() << '\n';
        return 0;
    }
}

int PointCounter::CheckMoreLeft(int row, int column, int count, char colour)
{
    try {
        int totalCount = 0;

        for (; column >= 0; column--) {
            if (board->GetBoard()[row][column] != colour) {
                return totalCount;
            }
            totalCount++;
        }
        return totalCount;
    }
    catch (const std::exception& e)
    {
        std::cerr << e.what() << '\n';
        return 0;
    }
}

std::pair<int, int> PointCounter::CalculatePointRightDiagonalUp(int row, int column, char colour)
{
    try {
        int newRow = row - 3;
        int newColumn = column + 3;

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
    catch (const std::exception& e){
        std::cerr << e.what() << '\n';
        cout << "Internal Server Error: PointCounter::CalculatePointRightDiagonalUp" << endl;
        return std::pair<int, int>(-1, -1);
    }
}

std::pair<int, int> PointCounter::CalculatePointRightDiagonalDown(int row, int column, char colour)
{
    try {
        int newRow = row + 3;
        int newColumn = column - 3;

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

std::pair<int, int> PointCounter::CalculatePointLeftDiagonalUp(int row, int column, char colour)
{
    try {
        int newRow = row - 3;
        int newColumn = column - 3;

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

std::pair<int, int> PointCounter::CalculatePointLeftDiagonalDown(int row, int column, char colour)
{
    try {
        int newRow = row + 3;
        int newColumn = column + 3;

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

std::pair<int, int> PointCounter::CalculatePointLeftHorizontal(int row, int column, char colour)
{
    try {
        int newRow = row;
        int newColumn = column - 3;

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

std::pair<int, int> PointCounter::CalculatePointRightHorizontal(int row, int column, char colour)
{
    try {
        int newRow = row;
        int newColumn = column + 3;

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

std::pair<int, int> PointCounter::CalculatePointUpVertical(int row, int column, char colour)
{
    try {
        int newRow = row - 3;
        int newColumn = column ;

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

std::pair<int, int> PointCounter::CalculatePointDownVertical(int row, int column, char colour)
{
    try {
        int newRow = row + 3;
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
int PointCounter::CalculatedScoreInLoadedRound(char colour)
{
    // make internal copy of the board that can be deleted and changed
    try {
        int totalScore = 0;
        vector<vector<char>> tmpBoard(19, vector<char>(19));
        for (int row = 0; row < board->GetBoardSize(); row++)
        {
            for (int column = 0; column < board->GetBoardSize(); column++)
            {

                tmpBoard[row][column] = this->board->GetBoard()[row][column];
            }
        }
        for (int row = 0; row < board->GetBoardSize(); row++)
        {
            for (int column = 0; column < board->GetBoardSize(); column++)
            {

                if(!board->IsPositionEmpty(row, column)){
                    totalScore += CalculatePoint(row, column, colour);
                    if (!board->RemovePiece(row, column)) {
                        cout << "Internal Server Error: failed to remove a piece" << endl;
                        return -1;
                    }
                }
            }
        }
        // reset the board
        if (!board->SetBoard(tmpBoard)) {
            cout << "Internal Server Error: CalculatedScoreInLoadedRound" << endl;
        }
        return totalScore;
    }
    catch (const std::exception& e) {
        std::cerr << e.what() << '\n';
        cout << "Internal Server Error: PointCounter::CalculatePointRightDiagonalUp" << endl;
        return  -1;
    }
}