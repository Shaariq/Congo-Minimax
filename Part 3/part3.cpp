// To-Do-List:
// 1. Add drowning to the game...

#include <iostream>
#include <string>
#include <array>
#include <vector>
#include <sstream>

using namespace std;

// Global variables
int LOWER_BOUND = 0;
int UPPER_BOUND = 6;
int RIVER_ROW = 3;

string whitePawnToken = "P";
string blackPawnToken = "p";
string whiteSuperPawnToken = "S";
string blackSuperPawnToken = "s";
string whiteGiraffeToken = "G";
string blackGiraffeToken = "g";
string whiteMonkeyToken = "M";
string blackMonkeyToken = "m";
string whiteElephantToken = "E";
string blackElephantToken = "e";
string whiteLionToken = "L";
string blackLionToken = "l";
string whiteCrocodileToken = "C";
string blackCrocodileToken = "c";
string whiteZebraToken = "Z";
string blackZebraToken = "z";

string turnToPlay = "white";
vector<string> movesToPlay;
int moveCount = 0;
string gameStatus = "continue";

vector<string> readInput()
{
    vector<string> fenStrings;
    string fenCount;

    getline(cin, fenCount);

    for (int i = 0; i < stoi(fenCount); i++)
    {
        string tmp;
        getline(cin, tmp);
        fenStrings.push_back(tmp);
        string move;
        getline(cin, move);
        movesToPlay.push_back(move);
    }

    return fenStrings;
}

vector<string> split(string str, char delimiter)
{
    vector<string> splitString;
    stringstream ss(str);
    string tmp;

    while (!ss.eof())
    {
        getline(ss, tmp, delimiter);
        splitString.push_back(tmp);
    }

    return splitString;
}

array<array<string, 7>, 7> flipBoardXAxis(array<array<string, 7>, 7> board)
{
    array<array<string, 7>, 7> flippedBoard;

    // loop through the board
    for (int i = 0; i < board.size(); i++)
    {
        for (int j = 0; j < board[i].size(); j++)
        {
            // flip the board
            flippedBoard[i][j] = board[board.size() - i - 1][j];
        }
    }

    return flippedBoard;
}

array<array<string, 7>, 7> populateBoard(vector<string> gameState)
{
    array<array<string, 7>, 7> board;

    for (int i = 0; i < board.size(); i++)
    {
        for (int j = 0; j < board[i].size(); j++)
        {
            board[i][j] = " ";
        }
    }

    // loop through the game state
    // if there is a digit, convert it to a series of 1s
    for (int i = 0; i < gameState.size(); i++)
    {
        string tmp = gameState[i];
        string newString = "";
        for (int j = 0; j < tmp.length(); j++)
        {
            if (isdigit(tmp[j]))
            {
                for (int k = 0; k < tmp[j] - '0'; k++)
                {
                    newString += "1";
                }
            }
            else
            {
                newString += tmp[j];
            }
        }
        gameState[i] = newString;
    }

    // loop through the game state
    for (int i = 0; i < gameState.size(); i++)
    {
        for (int j = 0; j < gameState[i].size(); j++)
        {
            if (isdigit(gameState[i][j]))
            {
                int num = gameState[i][j] - '0';
                // skip those many spaces on the board
                for (int k = 0; k < num; k++)
                {
                    board[i][j] = " ";
                }
            }
            else
            {
                board[i][j] = gameState[i][j];
            }
        }
    }

    // return board;
    // return flipBoardXAxis(board);
    return board;
}

string convertToFenString(array<array<string, 7>, 7> board)
{
    string fenString = "";

    for (int i = 0; i < board.size(); i++)
    {
        int count = 0;
        for (int j = 0; j < board[i].size(); j++)
        {
            if (board[i][j] == " ")
            {
                count++;
            }
            else
            {
                if (count > 0)
                {
                    fenString += to_string(count);
                    count = 0;
                }
                fenString += board[i][j];
            }
        }
        if (count > 0)
        {
            fenString += to_string(count);
        }
        if (i < board.size() - 1)
        {
            fenString += "/";
        }
    }

    return fenString;
}

array<array<string, 7>, 7> processFenString(string fenString)
{
    // First the string is split by empty space
    vector<string> fenStringSplit = split(fenString, ' ');

    string gameState = fenStringSplit[0];
    string turn = fenStringSplit[1];
    string moveCounter = fenStringSplit[2];

    // set moveCount
    moveCount = stoi(moveCounter);

    if (turn == "w")
    {
        turnToPlay = "white";
    }
    else if (turn == "b")
    {
        turnToPlay = "black";
    }

    vector<string> gameStateSplit = split(gameState, '/');
    string row1 = gameStateSplit[0];
    string row2 = gameStateSplit[1];
    string row3 = gameStateSplit[2];
    string row4 = gameStateSplit[3];
    string row5 = gameStateSplit[4];
    string row6 = gameStateSplit[5];
    string row7 = gameStateSplit[6];

    // return the game board
    return populateBoard(gameStateSplit);
}

void printBoard(array<array<string, 7>, 7> board)
{
    for (int i = 0; i < board.size(); i++)
    {
        for (int j = 0; j < board[i].size(); j++)
        {
            cout << board[i][j];
        }
        cout << endl;
    }
}

int convertRowToIndex(string row)
{
    if (row == "7")
    {
        return 0;
    }
    else if (row == "6")
    {
        return 1;
    }
    else if (row == "5")
    {
        return 2;
    }
    else if (row == "4")
    {
        return 3;
    }
    else if (row == "3")
    {
        return 4;
    }
    else if (row == "2")
    {
        return 5;
    }
    else if (row == "1")
    {
        return 6;
    }
    else
    {
        return -1;
    }
}

string convertIndexToRow(int row)
{
    if (row == 0)
    {
        return "7";
    }
    else if (row == 1)
    {
        return "6";
    }
    else if (row == 2)
    {
        return "5";
    }
    else if (row == 3)
    {
        return "4";
    }
    else if (row == 4)
    {
        return "3";
    }
    else if (row == 5)
    {
        return "2";
    }
    else if (row == 6)
    {
        return "1";
    }
    else
    {
        return "-1";
    }
}

int convertColumnToIndex(string column)
{
    if (column == "a")
    {
        return 0;
    }
    else if (column == "b")
    {
        return 1;
    }
    else if (column == "c")
    {
        return 2;
    }
    else if (column == "d")
    {
        return 3;
    }
    else if (column == "e")
    {
        return 4;
    }
    else if (column == "f")
    {
        return 5;
    }
    else if (column == "g")
    {
        return 6;
    }
    else
    {
        return -1;
    }
}

string convertIndexToColumn(int column)
{
    if (column == 0)
    {
        return "a";
    }
    else if (column == 1)
    {
        return "b";
    }
    else if (column == 2)
    {
        return "c";
    }
    else if (column == 3)
    {
        return "d";
    }
    else if (column == 4)
    {
        return "e";
    }
    else if (column == 5)
    {
        return "f";
    }
    else if (column == 6)
    {
        return "g";
    }
    else
    {
        return "-1";
    }
}

bool isBlack(string piece)
{
    if (piece == blackPawnToken || piece == blackSuperPawnToken || piece == blackGiraffeToken || piece == blackMonkeyToken || piece == blackElephantToken || piece == blackLionToken || piece == blackCrocodileToken || piece == blackZebraToken)
    {
        return true;
    }
    else
    {
        return false;
    }
}

bool isWhite(string piece)
{
    if (piece == whitePawnToken || piece == whiteSuperPawnToken || piece == whiteGiraffeToken || piece == whiteMonkeyToken || piece == whiteElephantToken || piece == whiteLionToken || piece == whiteCrocodileToken || piece == whiteZebraToken)
    {
        return true;
    }
    else
    {
        return false;
    }
}

vector<string> whiteLionMoves(int row, int col, array<array<string, 7>, 7> board, string color)
{
    vector<string> moves;

    // a white lion can go as far as column 2 on the left and column 4 on the right
    // a white lion can go as far as row 4 on the top and row 6 on the bottom

    // up
    if (row - 1 >= 4)
    {
        if (board[row - 1][col] == " ")
        {
            moves.push_back(convertIndexToColumn(col) + convertIndexToRow(row - 1));
        }
        else if (isBlack(board[row - 1][col]))
        {
            moves.push_back(convertIndexToColumn(col) + convertIndexToRow(row - 1));
        }
    }

    // down
    if (row + 1 <= 6)
    {
        if (board[row + 1][col] == " ")
        {
            moves.push_back(convertIndexToColumn(col) + convertIndexToRow(row + 1));
        }
        else if (isBlack(board[row + 1][col]))
        {
            moves.push_back(convertIndexToColumn(col) + convertIndexToRow(row + 1));
        }
    }

    // left
    if (col - 1 >= 2)
    {
        if (board[row][col - 1] == " ")
        {
            moves.push_back(convertIndexToColumn(col - 1) + convertIndexToRow(row));
        }
        else if (isBlack(board[row][col - 1]))
        {
            moves.push_back(convertIndexToColumn(col - 1) + convertIndexToRow(row));
        }
    }

    // right
    if (col + 1 <= 4)
    {
        if (board[row][col + 1] == " ")
        {
            moves.push_back(convertIndexToColumn(col + 1) + convertIndexToRow(row));
        }
        else if (isBlack(board[row][col + 1]))
        {
            moves.push_back(convertIndexToColumn(col + 1) + convertIndexToRow(row));
        }
    }

    // diagonal up left
    if (row - 1 >= 4 && col - 1 >= 2)
    {
        if (board[row - 1][col - 1] == " ")
        {
            moves.push_back(convertIndexToColumn(col - 1) + convertIndexToRow(row - 1));
        }
        else if (isBlack(board[row - 1][col - 1]))
        {
            moves.push_back(convertIndexToColumn(col - 1) + convertIndexToRow(row - 1));
        }
    }

    // diagonal up right
    if (row - 1 >= 4 && col + 1 <= 4)
    {
        if (board[row - 1][col + 1] == " ")
        {
            moves.push_back(convertIndexToColumn(col + 1) + convertIndexToRow(row - 1));
        }
        else if (isBlack(board[row - 1][col + 1]))
        {
            moves.push_back(convertIndexToColumn(col + 1) + convertIndexToRow(row - 1));
        }
    }

    // diagonal down left
    if (row + 1 <= 6 && col - 1 >= 2)
    {
        if (board[row + 1][col - 1] == " ")
        {
            moves.push_back(convertIndexToColumn(col - 1) + convertIndexToRow(row + 1));
        }
        else if (isBlack(board[row + 1][col - 1]))
        {
            moves.push_back(convertIndexToColumn(col - 1) + convertIndexToRow(row + 1));
        }
    }

    // diagonal down right
    if (row + 1 <= 6 && col + 1 <= 4)
    {
        if (board[row + 1][col + 1] == " ")
        {
            moves.push_back(convertIndexToColumn(col + 1) + convertIndexToRow(row + 1));
        }
        else if (isBlack(board[row + 1][col + 1]))
        {
            moves.push_back(convertIndexToColumn(col + 1) + convertIndexToRow(row + 1));
        }
    }

    // a lion may jump across the river to capture a black lion
    // if (row == 4 && 2 <= col && col <= 4)
    // {
    //     if (board[2][2] == blackLionToken)
    //     {
    //         moves.push_back(convertIndexToColumn(2) + convertIndexToRow(2));
    //     }
    //     else if (board[2][3] == blackLionToken)
    //     {
    //         moves.push_back(convertIndexToColumn(3) + convertIndexToRow(2));
    //     }
    //     else if (board[2][4] == blackLionToken)
    //     {
    //         moves.push_back(convertIndexToColumn(4) + convertIndexToRow(2));
    //     }
    // }
    
    // a lion may jump across the river if it can capture the black lion
    // either in a straight line or diagonally

    // first check if the white lion is in line with the black lion
    // if it is, then check if there is a piece in between the white lion and the black lion
    // if there is no piece in between, then the white lion can jump across the river to capture the black lion
    if (board[0][col] == blackLionToken || board[1][col] == blackLionToken || board[2][col] == blackLionToken)
    {
        if (board[0][col] == blackLionToken)
        {
            if (board[1][col] == " " && board[2][col] == " ")
            {
                moves.push_back(convertIndexToColumn(col) + convertIndexToRow(0));
            }
        }
        else if (board[1][col] == blackLionToken)
        {
            if (board[0][col] == " " && board[2][col] == " ")
            {
                moves.push_back(convertIndexToColumn(col) + convertIndexToRow(1));
            }
        }
        else if (board[2][col] == blackLionToken)
        {
            if (board[0][col] == " " && board[1][col] == " ")
            {
                moves.push_back(convertIndexToColumn(col) + convertIndexToRow(2));
            }
        }
    }

    // check if the lion can capture the black lion diagonally
    // if it can, then check if there is a piece in between the white lion and the black lion
    // if there is no piece in between, then the white lion can jump across the river to capture the black lion
    if (board[0][col - 1] == blackLionToken || board[1][col - 1] == blackLionToken || board[2][col - 1] == blackLionToken)
    {
        if (board[0][col - 1] == blackLionToken)
        {
            if (board[1][col - 1] == " " && board[2][col - 1] == " ")
            {
                moves.push_back(convertIndexToColumn(col - 1) + convertIndexToRow(0));
            }
        }
        else if (board[1][col - 1] == blackLionToken)
        {
            if (board[0][col - 1] == " " && board[2][col - 1] == " ")
            {
                moves.push_back(convertIndexToColumn(col - 1) + convertIndexToRow(1));
            }
        }
        else if (board[2][col - 1] == blackLionToken)
        {
            if (board[0][col - 1] == " " && board[1][col - 1] == " ")
            {
                moves.push_back(convertIndexToColumn(col - 1) + convertIndexToRow(2));
            }
        }
    }

    // check the other diagonal 
    if (board[0][col + 1] == blackLionToken || board[1][col + 1] == blackLionToken || board[2][col + 1] == blackLionToken)
    {
        if (board[0][col + 1] == blackLionToken)
        {
            if (board[1][col + 1] == " " && board[2][col + 1] == " ")
            {
                moves.push_back(convertIndexToColumn(col + 1) + convertIndexToRow(0));
            }
        }
        else if (board[1][col + 1] == blackLionToken)
        {
            if (board[0][col + 1] == " " && board[2][col + 1] == " ")
            {
                moves.push_back(convertIndexToColumn(col + 1) + convertIndexToRow(1));
            }
        }
        else if (board[2][col + 1] == blackLionToken)
        {
            if (board[0][col + 1] == " " && board[1][col + 1] == " ")
            {
                moves.push_back(convertIndexToColumn(col + 1) + convertIndexToRow(2));
            }
        }
    }

    return moves;
}

vector<string> blackLionMoves(int row, int col, array<array<string, 7>, 7> board, string color)
{
    vector<string> moves;

    // a black lion can go as far as column 2 on the left and column 4 on the right
    // a black lion can go as far as row 0 on the top and row 2 on the bottom

    // up
    if (row - 1 >= 0)
    {
        if (board[row - 1][col] == " ")
        {
            moves.push_back(convertIndexToColumn(col) + convertIndexToRow(row - 1));
        }
        else if (isWhite(board[row - 1][col]))
        {
            moves.push_back(convertIndexToColumn(col) + convertIndexToRow(row - 1));
        }
    }

    // down
    if (row + 1 <= 2)
    {
        if (board[row + 1][col] == " ")
        {
            moves.push_back(convertIndexToColumn(col) + convertIndexToRow(row + 1));
        }
        else if (isWhite(board[row + 1][col]))
        {
            moves.push_back(convertIndexToColumn(col) + convertIndexToRow(row + 1));
        }
    }

    // left
    if (col - 1 >= 2)
    {
        if (board[row][col - 1] == " ")
        {
            moves.push_back(convertIndexToColumn(col - 1) + convertIndexToRow(row));
        }
        else if (isWhite(board[row][col - 1]))
        {
            moves.push_back(convertIndexToColumn(col - 1) + convertIndexToRow(row));
        }
    }

    // right
    if (col + 1 <= 4)
    {
        if (board[row][col + 1] == " ")
        {
            moves.push_back(convertIndexToColumn(col + 1) + convertIndexToRow(row));
        }
        else if (isWhite(board[row][col + 1]))
        {
            moves.push_back(convertIndexToColumn(col + 1) + convertIndexToRow(row));
        }
    }

    // diagonal up left
    if (row - 1 >= 0 && col - 1 >= 2)
    {
        if (board[row - 1][col - 1] == " ")
        {
            moves.push_back(convertIndexToColumn(col - 1) + convertIndexToRow(row - 1));
        }
        else if (isWhite(board[row - 1][col - 1]))
        {
            moves.push_back(convertIndexToColumn(col - 1) + convertIndexToRow(row - 1));
        }
    }

    // diagonal up right
    if (row - 1 >= 0 && col + 1 <= 4)
    {
        if (board[row - 1][col + 1] == " ")
        {
            moves.push_back(convertIndexToColumn(col + 1) + convertIndexToRow(row - 1));
        }
        else if (isWhite(board[row - 1][col + 1]))
        {
            moves.push_back(convertIndexToColumn(col + 1) + convertIndexToRow(row - 1));
        }
    }

    // diagonal down left
    if (row + 1 <= 2 && col - 1 >= 2)
    {
        if (board[row + 1][col - 1] == " ")
        {
            moves.push_back(convertIndexToColumn(col - 1) + convertIndexToRow(row + 1));
        }
        else if (isWhite(board[row + 1][col - 1]))
        {
            moves.push_back(convertIndexToColumn(col - 1) + convertIndexToRow(row + 1));
        }
    }

    // diagonal down right
    if (row + 1 <= 2 && col + 1 <= 4)
    {
        if (board[row + 1][col + 1] == " ")
        {
            moves.push_back(convertIndexToColumn(col + 1) + convertIndexToRow(row + 1));
        }
        else if (isWhite(board[row + 1][col + 1]))
        {
            moves.push_back(convertIndexToColumn(col + 1) + convertIndexToRow(row + 1));
        }
    }

    // a lion may jump across the river to capture a white lion
    // if (row == 2 && 2 <= col && col <= 4)
    // {
    //     if (board[4][2] == whiteLionToken)
    //     {
    //         moves.push_back(convertIndexToColumn(2) + convertIndexToRow(4));
    //     }
    //     else if (board[4][3] == whiteLionToken)
    //     {
    //         moves.push_back(convertIndexToColumn(3) + convertIndexToRow(4));
    //     }
    //     else if (board[4][4] == whiteLionToken)
    //     {
    //         moves.push_back(convertIndexToColumn(4) + convertIndexToRow(4));
    //     }
    // }

    // a lion may jump across the river to capture a white lion
    if (board[6][col] == whiteLionToken || board[5][col] == whiteLionToken || board[4][col] == whiteLionToken) {
        if (board[6][col] == whiteLionToken) {
            if (board[5][col] == " " && board[4][col] == " ") {
                moves.push_back(convertIndexToColumn(col) + convertIndexToRow(6));
            }
        }
        else if (board[5][col] == whiteLionToken) {
            if (board[4][col] == " " && board[6][col] == " ") {
                moves.push_back(convertIndexToColumn(col) + convertIndexToRow(5));
            }
        }
        else if (board[4][col] == whiteLionToken) {
            if (board[5][col] == " " && board[6][col] == " ") {
                moves.push_back(convertIndexToColumn(col) + convertIndexToRow(4));
            }
        }
    }

    // check diagonal for capture
    if (board[6][col - 1] == whiteLionToken || board[5][col - 1] == whiteLionToken || board[4][col - 1] == whiteLionToken) {
        if (board[6][col - 1] == whiteLionToken) {
            if (board[5][col - 1] == " " && board[4][col - 1] == " ") {
                moves.push_back(convertIndexToColumn(col - 1) + convertIndexToRow(6));
            }
        }
        else if (board[5][col - 1] == whiteLionToken) {
            if (board[4][col - 1] == " " && board[6][col - 1] == " ") {
                moves.push_back(convertIndexToColumn(col - 1) + convertIndexToRow(5));
            }
        }
        else if (board[4][col - 1] == whiteLionToken) {
            if (board[5][col - 1] == " " && board[6][col - 1] == " ") {
                moves.push_back(convertIndexToColumn(col - 1) + convertIndexToRow(4));
            }
        }
    }

    // check other diagonal
    if (board[6][col + 1] == whiteLionToken || board[5][col + 1] == whiteLionToken || board[4][col + 1] == whiteLionToken) {
        if (board[6][col + 1] == whiteLionToken) {
            if (board[5][col + 1] == " " && board[4][col + 1] == " ") {
                moves.push_back(convertIndexToColumn(col + 1) + convertIndexToRow(6));
            }
        }
        else if (board[5][col + 1] == whiteLionToken) {
            if (board[4][col + 1] == " " && board[6][col + 1] == " ") {
                moves.push_back(convertIndexToColumn(col + 1) + convertIndexToRow(5));
            }
        }
        else if (board[4][col + 1] == whiteLionToken) {
            if (board[5][col + 1] == " " && board[6][col + 1] == " ") {
                moves.push_back(convertIndexToColumn(col + 1) + convertIndexToRow(4));
            }
        }
    }

    return moves;
}

vector<string> lionMoves(int row, int col, array<array<string, 7>, 7> board, string color)
{
    vector<string> moves;

    if (color == "white")
    {
        moves = whiteLionMoves(row, col, board, color);
        string currPosition = convertIndexToColumn(col) + convertIndexToRow(row);

        // append currPosition to each string in moves
        for (int i = 0; i < moves.size(); i++)
        {
            moves[i] = currPosition + moves[i];
        }
        return moves;
    }
    else if (color == "black")
    {
        moves = blackLionMoves(row, col, board, color);
        string currPosition = convertIndexToColumn(col) + convertIndexToRow(row);

        // append currPosition to each string in moves
        for (int i = 0; i < moves.size(); i++)
        {
            moves[i] = currPosition + moves[i];
        }
        return moves;
    }
    else
    {

        return moves;
    }
}

vector<string> zebraMoves(int row, int col, array<array<string, 7>, 7> board, string color)
{
    vector<string> moves;

    // A zebra moves in an L shape only

    // Up and right
    if (row - 2 >= LOWER_BOUND && col + 1 <= UPPER_BOUND)
    {
        if (board[row - 2][col + 1] == " ")
        {
            moves.insert(moves.end(), convertIndexToColumn(col + 1) + convertIndexToRow(row - 2));
        }
        else if (isBlack(board[row - 2][col + 1]) && color == "white")
        {
            moves.insert(moves.end(), convertIndexToColumn(col + 1) + convertIndexToRow(row - 2));
        }
        else if (isWhite(board[row - 2][col + 1]) && color == "black")
        {
            moves.insert(moves.end(), convertIndexToColumn(col + 1) + convertIndexToRow(row - 2));
        }
    }

    // Up and left
    if (row - 2 >= LOWER_BOUND && col - 1 >= LOWER_BOUND)
    {
        if (board[row - 2][col - 1] == " ")
        {
            moves.insert(moves.end(), convertIndexToColumn(col - 1) + convertIndexToRow(row - 2));
        }
        else if (isBlack(board[row - 2][col - 1]) && color == "white")
        {
            moves.insert(moves.end(), convertIndexToColumn(col - 1) + convertIndexToRow(row - 2));
        }
        else if (isWhite(board[row - 2][col - 1]) && color == "black")
        {
            moves.insert(moves.end(), convertIndexToColumn(col - 1) + convertIndexToRow(row - 2));
        }
    }

    // Down and right
    if (row + 2 <= UPPER_BOUND && col + 1 <= UPPER_BOUND)
    {
        if (board[row + 2][col + 1] == " ")
        {
            moves.insert(moves.end(), convertIndexToColumn(col + 1) + convertIndexToRow(row + 2));
        }
        else if (isBlack(board[row + 2][col + 1]) && color == "white")
        {
            moves.insert(moves.end(), convertIndexToColumn(col + 1) + convertIndexToRow(row + 2));
        }
        else if (isWhite(board[row + 2][col + 1]) && color == "black")
        {
            moves.insert(moves.end(), convertIndexToColumn(col + 1) + convertIndexToRow(row + 2));
        }
    }

    // Down and left
    if (row + 2 <= UPPER_BOUND && col - 1 >= LOWER_BOUND)
    {
        if (board[row + 2][col - 1] == " ")
        {
            moves.insert(moves.end(), convertIndexToColumn(col - 1) + convertIndexToRow(row + 2));
        }
        else if (isBlack(board[row + 2][col - 1]) && color == "white")
        {
            moves.insert(moves.end(), convertIndexToColumn(col - 1) + convertIndexToRow(row + 2));
        }
        else if (isWhite(board[row + 2][col - 1]) && color == "black")
        {
            moves.insert(moves.end(), convertIndexToColumn(col - 1) + convertIndexToRow(row + 2));
        }
    }

    // Right and up
    if (row - 1 >= LOWER_BOUND && col + 2 <= UPPER_BOUND)
    {
        if (board[row - 1][col + 2] == " ")
        {
            moves.insert(moves.end(), convertIndexToColumn(col + 2) + convertIndexToRow(row - 1));
        }
        else if (isBlack(board[row - 1][col + 2]) && color == "white")
        {
            moves.insert(moves.end(), convertIndexToColumn(col + 2) + convertIndexToRow(row - 1));
        }
        else if (isWhite(board[row - 1][col + 2]) && color == "black")
        {
            moves.insert(moves.end(), convertIndexToColumn(col + 2) + convertIndexToRow(row - 1));
        }
    }

    // Right and down
    if (row + 1 <= UPPER_BOUND && col + 2 <= UPPER_BOUND)
    {
        if (board[row + 1][col + 2] == " ")
        {
            moves.insert(moves.end(), convertIndexToColumn(col + 2) + convertIndexToRow(row + 1));
        }
        else if (isBlack(board[row + 1][col + 2]) && color == "white")
        {
            moves.insert(moves.end(), convertIndexToColumn(col + 2) + convertIndexToRow(row + 1));
        }
        else if (isWhite(board[row + 1][col + 2]) && color == "black")
        {
            moves.insert(moves.end(), convertIndexToColumn(col + 2) + convertIndexToRow(row + 1));
        }
    }

    // Left and up
    if (row - 1 >= LOWER_BOUND && col - 2 >= LOWER_BOUND)
    {
        if (board[row - 1][col - 2] == " ")
        {
            moves.insert(moves.end(), convertIndexToColumn(col - 2) + convertIndexToRow(row - 1));
        }
        else if (isBlack(board[row - 1][col - 2]) && color == "white")
        {
            moves.insert(moves.end(), convertIndexToColumn(col - 2) + convertIndexToRow(row - 1));
        }
        else if (isWhite(board[row - 1][col - 2]) && color == "black")
        {
            moves.insert(moves.end(), convertIndexToColumn(col - 2) + convertIndexToRow(row - 1));
        }
    }

    // Left and down
    if (row + 1 <= UPPER_BOUND && col - 2 >= LOWER_BOUND)
    {
        if (board[row + 1][col - 2] == " ")
        {
            moves.insert(moves.end(), convertIndexToColumn(col - 2) + convertIndexToRow(row + 1));
        }
        else if (isBlack(board[row + 1][col - 2]) && color == "white")
        {
            moves.insert(moves.end(), convertIndexToColumn(col - 2) + convertIndexToRow(row + 1));
        }
        else if (isWhite(board[row + 1][col - 2]) && color == "black")
        {
            moves.insert(moves.end(), convertIndexToColumn(col - 2) + convertIndexToRow(row + 1));
        }
    }

    string currPosition = convertIndexToColumn(col) + convertIndexToRow(row);

    // append currPosition to each string in moves
    for (int i = 0; i < moves.size(); i++)
    {
        moves[i] = currPosition + moves[i];
    }

    return moves;
}

vector<string> giraffeMoves(int row, int col, array<array<string, 7>, 7> board, string color)
{
    vector<string> moves;

    // A giraffe moves one or two spaces in any direction
    // it can only capture two spaces away

    // one up
    if (row - 1 >= LOWER_BOUND)
    {
        if (board[row - 1][col] == " ")
        {
            moves.insert(moves.end(), convertIndexToColumn(col) + convertIndexToRow(row - 1));
        }
    }

    // one down
    if (row + 1 <= UPPER_BOUND)
    {
        if (board[row + 1][col] == " ")
        {
            moves.insert(moves.end(), convertIndexToColumn(col) + convertIndexToRow(row + 1));
        }
    }

    // one left
    if (col - 1 >= LOWER_BOUND)
    {
        if (board[row][col - 1] == " ")
        {
            moves.insert(moves.end(), convertIndexToColumn(col - 1) + convertIndexToRow(row));
        }
    }

    // one right
    if (col + 1 <= UPPER_BOUND)
    {
        if (board[row][col + 1] == " ")
        {
            moves.insert(moves.end(), convertIndexToColumn(col + 1) + convertIndexToRow(row));
        }
    }

    // one diagonal up and right
    if (row - 1 >= LOWER_BOUND && col + 1 <= UPPER_BOUND)
    {
        if (board[row - 1][col + 1] == " ")
        {
            moves.insert(moves.end(), convertIndexToColumn(col + 1) + convertIndexToRow(row - 1));
        }
    }

    // one diagonal up and left
    if (row - 1 >= LOWER_BOUND && col - 1 >= LOWER_BOUND)
    {
        if (board[row - 1][col - 1] == " ")
        {
            moves.insert(moves.end(), convertIndexToColumn(col - 1) + convertIndexToRow(row - 1));
        }
    }

    // one diagonal down and right
    if (row + 1 <= UPPER_BOUND && col + 1 <= UPPER_BOUND)
    {
        if (board[row + 1][col + 1] == " ")
        {
            moves.insert(moves.end(), convertIndexToColumn(col + 1) + convertIndexToRow(row + 1));
        }
    }

    // one diagonal down and left
    if (row + 1 <= UPPER_BOUND && col - 1 >= LOWER_BOUND)
    {
        if (board[row + 1][col - 1] == " ")
        {
            moves.insert(moves.end(), convertIndexToColumn(col - 1) + convertIndexToRow(row + 1));
        }
    }

    // two up
    if (row - 2 >= LOWER_BOUND)
    {
        if (board[row - 2][col] == " ")
        {
            moves.insert(moves.end(), convertIndexToColumn(col) + convertIndexToRow(row - 2));
        }
        else if (isBlack(board[row - 2][col]) && color == "white")
        {
            moves.insert(moves.end(), convertIndexToColumn(col) + convertIndexToRow(row - 2));
        }
        else if (isWhite(board[row - 2][col]) && color == "black")
        {
            moves.insert(moves.end(), convertIndexToColumn(col) + convertIndexToRow(row - 2));
        }
    }

    // two down
    if (row + 2 <= UPPER_BOUND)
    {
        if (board[row + 2][col] == " ")
        {
            moves.insert(moves.end(), convertIndexToColumn(col) + convertIndexToRow(row + 2));
        }
        else if (isBlack(board[row + 2][col]) && color == "white")
        {
            moves.insert(moves.end(), convertIndexToColumn(col) + convertIndexToRow(row + 2));
        }
        else if (isWhite(board[row + 2][col]) && color == "black")
        {
            moves.insert(moves.end(), convertIndexToColumn(col) + convertIndexToRow(row + 2));
        }
    }

    // two left
    if (col - 2 >= LOWER_BOUND)
    {
        if (board[row][col - 2] == " ")
        {
            moves.insert(moves.end(), convertIndexToColumn(col - 2) + convertIndexToRow(row));
        }
        else if (isBlack(board[row][col - 2]) && color == "white")
        {
            moves.insert(moves.end(), convertIndexToColumn(col - 2) + convertIndexToRow(row));
        }
        else if (isWhite(board[row][col - 2]) && color == "black")
        {
            moves.insert(moves.end(), convertIndexToColumn(col - 2) + convertIndexToRow(row));
        }
    }

    // two right
    if (col + 2 <= UPPER_BOUND)
    {
        if (board[row][col + 2] == " ")
        {
            moves.insert(moves.end(), convertIndexToColumn(col + 2) + convertIndexToRow(row));
        }
        else if (isBlack(board[row][col + 2]) && color == "white")
        {
            moves.insert(moves.end(), convertIndexToColumn(col + 2) + convertIndexToRow(row));
        }
        else if (isWhite(board[row][col + 2]) && color == "black")
        {
            moves.insert(moves.end(), convertIndexToColumn(col + 2) + convertIndexToRow(row));
        }
    }

    // two diagonal up and right
    if (row - 2 >= LOWER_BOUND && col + 2 <= UPPER_BOUND)
    {
        if (board[row - 2][col + 2] == " ")
        {
            moves.insert(moves.end(), convertIndexToColumn(col + 2) + convertIndexToRow(row - 2));
        }
        else if (isBlack(board[row - 2][col + 2]) && color == "white")
        {
            moves.insert(moves.end(), convertIndexToColumn(col + 2) + convertIndexToRow(row - 2));
        }
        else if (isWhite(board[row - 2][col + 2]) && color == "black")
        {
            moves.insert(moves.end(), convertIndexToColumn(col + 2) + convertIndexToRow(row - 2));
        }
    }

    // two diagonal up and left
    if (row - 2 >= LOWER_BOUND && col - 2 >= LOWER_BOUND)
    {
        if (board[row - 2][col - 2] == " ")
        {
            moves.insert(moves.end(), convertIndexToColumn(col - 2) + convertIndexToRow(row - 2));
        }
        else if (isBlack(board[row - 2][col - 2]) && color == "white")
        {
            moves.insert(moves.end(), convertIndexToColumn(col - 2) + convertIndexToRow(row - 2));
        }
        else if (isWhite(board[row - 2][col - 2]) && color == "black")
        {
            moves.insert(moves.end(), convertIndexToColumn(col - 2) + convertIndexToRow(row - 2));
        }
    }

    // two diagonal down and right
    if (row + 2 <= UPPER_BOUND && col + 2 <= UPPER_BOUND)
    {
        if (board[row + 2][col + 2] == " ")
        {
            moves.insert(moves.end(), convertIndexToColumn(col + 2) + convertIndexToRow(row + 2));
        }
        else if (isBlack(board[row + 2][col + 2]) && color == "white")
        {
            moves.insert(moves.end(), convertIndexToColumn(col + 2) + convertIndexToRow(row + 2));
        }
        else if (isWhite(board[row + 2][col + 2]) && color == "black")
        {
            moves.insert(moves.end(), convertIndexToColumn(col + 2) + convertIndexToRow(row + 2));
        }
    }

    // two diagonal down and left
    if (row + 2 <= UPPER_BOUND && col - 2 >= LOWER_BOUND)
    {
        if (board[row + 2][col - 2] == " ")
        {
            moves.insert(moves.end(), convertIndexToColumn(col - 2) + convertIndexToRow(row + 2));
        }
        else if (isBlack(board[row + 2][col - 2]) && color == "white")
        {
            moves.insert(moves.end(), convertIndexToColumn(col - 2) + convertIndexToRow(row + 2));
        }
        else if (isWhite(board[row + 2][col - 2]) && color == "black")
        {
            moves.insert(moves.end(), convertIndexToColumn(col - 2) + convertIndexToRow(row + 2));
        }
    }

    string currPosition = convertIndexToColumn(col) + convertIndexToRow(row);

    // append currPosition to each string in moves
    for (int i = 0; i < moves.size(); i++)
    {
        moves[i] = currPosition + moves[i];
    }

    return moves;
}

vector<string> whitePawnMoves(int row, int col, array<array<string, 7>, 7> board)
{
    vector<string> moves;

    // A white pawn moves and captures one step forward or diagonally forward.

    // one forward
    if (row - 1 >= LOWER_BOUND)
    {
        if (board[row - 1][col] == " ")
        {
            moves.insert(moves.end(), convertIndexToColumn(col) + convertIndexToRow(row - 1));
        }
        else if (isBlack(board[row - 1][col]))
        {
            moves.insert(moves.end(), convertIndexToColumn(col) + convertIndexToRow(row - 1));
        }
    }

    // one diagonal forward and right
    if (row - 1 >= LOWER_BOUND && col + 1 <= UPPER_BOUND)
    {
        if (board[row - 1][col + 1] == " ")
        {
            moves.insert(moves.end(), convertIndexToColumn(col + 1) + convertIndexToRow(row - 1));
        }
        else if (isBlack(board[row - 1][col + 1]))
        {
            moves.insert(moves.end(), convertIndexToColumn(col + 1) + convertIndexToRow(row - 1));
        }
    }

    // one diagonal forward and left
    if (row - 1 >= LOWER_BOUND && col - 1 >= LOWER_BOUND)
    {
        if (board[row - 1][col - 1] == " ")
        {
            moves.insert(moves.end(), convertIndexToColumn(col - 1) + convertIndexToRow(row - 1));
        }
        else if (isBlack(board[row - 1][col - 1]))
        {
            moves.insert(moves.end(), convertIndexToColumn(col - 1) + convertIndexToRow(row - 1));
        }
    }

    // when past the river, a pawn can retreat either one or two steps backwards
    // this is not a jumping move

    // one retreat backwards
    if (row < RIVER_ROW && row + 1 <= UPPER_BOUND)
    {
        if (board[row + 1][col] == " ")
        {
            moves.insert(moves.end(), convertIndexToColumn(col) + convertIndexToRow(row + 1));
        }
    }

    // two retreat backwards
    if (row < RIVER_ROW && row + 2 <= UPPER_BOUND)
    {
        if (board[row + 1][col] == " " && board[row + 2][col] == " ")
        {
            moves.insert(moves.end(), convertIndexToColumn(col) + convertIndexToRow(row + 2));
        }
    }

    // promote to superpawn... not implemented
    return moves;
}

vector<string> blackPawnMoves(int row, int col, array<array<string, 7>, 7> board)
{
    vector<string> moves;

    // A black pawn moves and captures one step forward or diagonally forward.

    // one forward
    if (row + 1 <= UPPER_BOUND)
    {
        if (board[row + 1][col] == " ")
        {
            moves.insert(moves.end(), convertIndexToColumn(col) + convertIndexToRow(row + 1));
        }
        else if (isWhite(board[row + 1][col]))
        {
            moves.insert(moves.end(), convertIndexToColumn(col) + convertIndexToRow(row + 1));
        }
    }

    // one diagonal forward and right
    if (row + 1 <= UPPER_BOUND && col + 1 <= UPPER_BOUND)
    {
        if (board[row + 1][col + 1] == " ")
        {
            moves.insert(moves.end(), convertIndexToColumn(col + 1) + convertIndexToRow(row + 1));
        }
        else if (isWhite(board[row + 1][col + 1]))
        {
            moves.insert(moves.end(), convertIndexToColumn(col + 1) + convertIndexToRow(row + 1));
        }
    }

    // one diagonal forward and left
    if (row + 1 <= UPPER_BOUND && col - 1 >= LOWER_BOUND)
    {
        if (board[row + 1][col - 1] == " ")
        {
            moves.insert(moves.end(), convertIndexToColumn(col - 1) + convertIndexToRow(row + 1));
        }
        else if (isWhite(board[row + 1][col - 1]))
        {
            moves.insert(moves.end(), convertIndexToColumn(col - 1) + convertIndexToRow(row + 1));
        }
    }

    // when past the river, a pawn can retreat either one or two steps backwards
    // this is not a jumping move

    // one retreat backwards
    if (row > RIVER_ROW && row - 1 >= LOWER_BOUND)
    {
        if (board[row - 1][col] == " ")
        {
            moves.insert(moves.end(), convertIndexToColumn(col) + convertIndexToRow(row - 1));
        }
    }

    // two retreat backwards
    if (row > RIVER_ROW && row - 2 >= LOWER_BOUND)
    {
        if (board[row - 1][col] == " " && board[row - 2][col] == " ")
        {
            moves.insert(moves.end(), convertIndexToColumn(col) + convertIndexToRow(row - 2));
        }
    }

    // promote to superpawn... not implemented
    return moves;
}

vector<string> pawnMoves(int row, int col, array<array<string, 7>, 7> board, string color)
{
    vector<string> moves;

    if (color == "white")
    {
        moves = whitePawnMoves(row, col, board);
        string currPosition = convertIndexToColumn(col) + convertIndexToRow(row);

        // append currPosition to each string in moves
        for (int i = 0; i < moves.size(); i++)
        {
            moves[i] = currPosition + moves[i];
        }

        return moves;
    }
    else if (color == "black")
    {
        moves = blackPawnMoves(row, col, board);
        string currPosition = convertIndexToColumn(col) + convertIndexToRow(row);

        // append currPosition to each string in moves
        for (int i = 0; i < moves.size(); i++)
        {
            moves[i] = currPosition + moves[i];
        }

        return moves;
    }
    else
    {
        vector<string> moves;
        return moves;
    }
}

vector<string> whiteSuperpawnMoves(int row, int col, array<array<string, 7>, 7> board)
{
    vector<string> moves;

    // one forward
    if (row - 1 >= LOWER_BOUND)
    {
        if (board[row - 1][col] == " ")
        {
            moves.insert(moves.end(), convertIndexToColumn(col) + convertIndexToRow(row - 1));
        }
        else if (isBlack(board[row - 1][col]))
        {
            moves.insert(moves.end(), convertIndexToColumn(col) + convertIndexToRow(row - 1));
        }
    }

    // one diagonal forward and right
    if (row - 1 >= LOWER_BOUND && col + 1 <= UPPER_BOUND)
    {
        if (board[row - 1][col + 1] == " ")
        {
            moves.insert(moves.end(), convertIndexToColumn(col + 1) + convertIndexToRow(row - 1));
        }
        else if (isBlack(board[row - 1][col + 1]))
        {
            moves.insert(moves.end(), convertIndexToColumn(col + 1) + convertIndexToRow(row - 1));
        }
    }

    // one diagonal forward and left
    if (row - 1 >= LOWER_BOUND && col - 1 >= LOWER_BOUND)
    {
        if (board[row - 1][col - 1] == " ")
        {
            moves.insert(moves.end(), convertIndexToColumn(col - 1) + convertIndexToRow(row - 1));
        }
        else if (isBlack(board[row - 1][col - 1]))
        {
            moves.insert(moves.end(), convertIndexToColumn(col - 1) + convertIndexToRow(row - 1));
        }
    }

    // one left
    if (col - 1 >= LOWER_BOUND)
    {
        if (board[row][col - 1] == " ")
        {
            moves.insert(moves.end(), convertIndexToColumn(col - 1) + convertIndexToRow(row));
        }
        else if (isBlack(board[row][col - 1]))
        {
            moves.insert(moves.end(), convertIndexToColumn(col - 1) + convertIndexToRow(row));
        }
    }

    // one right
    if (col + 1 <= UPPER_BOUND)
    {
        if (board[row][col + 1] == " ")
        {
            moves.insert(moves.end(), convertIndexToColumn(col + 1) + convertIndexToRow(row));
        }
        else if (isBlack(board[row][col + 1]))
        {
            moves.insert(moves.end(), convertIndexToColumn(col + 1) + convertIndexToRow(row));
        }
    }

    // a pawn can retreat regardless of river

    // one retreat backwards
    if (row + 1 <= UPPER_BOUND)
    {
        if (board[row + 1][col] == " ")
        {
            moves.insert(moves.end(), convertIndexToColumn(col) + convertIndexToRow(row + 1));
        }
    }

    // two retreat backwards
    if (row + 2 <= UPPER_BOUND)
    {
        if (board[row + 1][col] == " " && board[row + 2][col] == " ")
        {
            moves.insert(moves.end(), convertIndexToColumn(col) + convertIndexToRow(row + 2));
        }
    }

    // one diagonal retreat backwards and right
    if (row + 1 <= UPPER_BOUND && col + 1 <= UPPER_BOUND)
    {
        if (board[row + 1][col + 1] == " ")
        {
            moves.insert(moves.end(), convertIndexToColumn(col + 1) + convertIndexToRow(row + 1));
        }
    }

    // one diagonal retreat backwards and left
    if (row + 1 <= UPPER_BOUND && col - 1 >= LOWER_BOUND)
    {
        if (board[row + 1][col - 1] == " ")
        {
            moves.insert(moves.end(), convertIndexToColumn(col - 1) + convertIndexToRow(row + 1));
        }
    }

    // two diagonal retreat backwards and right
    if (row + 2 <= UPPER_BOUND && col + 2 <= UPPER_BOUND)
    {
        if (board[row + 1][col + 1] == " " && board[row + 2][col + 2] == " ")
        {
            moves.insert(moves.end(), convertIndexToColumn(col + 2) + convertIndexToRow(row + 2));
        }
    }

    // two diagonal retreat backwards and left
    if (row + 2 <= UPPER_BOUND && col - 2 >= LOWER_BOUND)
    {
        if (board[row + 1][col - 1] == " " && board[row + 2][col - 2] == " ")
        {
            moves.insert(moves.end(), convertIndexToColumn(col - 2) + convertIndexToRow(row + 2));
        }
    }

    return moves;
}

vector<string> blackSuperpawnMoves(int row, int col, array<array<string, 7>, 7> board)
{
    vector<string> moves;

    // one forward
    if (row + 1 <= UPPER_BOUND)
    {
        if (board[row + 1][col] == " ")
        {
            moves.insert(moves.end(), convertIndexToColumn(col) + convertIndexToRow(row + 1));
        }
        else if (isWhite(board[row + 1][col]))
        {
            moves.insert(moves.end(), convertIndexToColumn(col) + convertIndexToRow(row + 1));
        }
    }

    // one diagonal forward and right
    if (row + 1 <= UPPER_BOUND && col + 1 <= UPPER_BOUND)
    {
        if (board[row + 1][col + 1] == " ")
        {
            moves.insert(moves.end(), convertIndexToColumn(col + 1) + convertIndexToRow(row + 1));
        }
        else if (isWhite(board[row + 1][col + 1]))
        {
            moves.insert(moves.end(), convertIndexToColumn(col + 1) + convertIndexToRow(row + 1));
        }
    }

    // one diagonal forward and left
    if (row + 1 <= UPPER_BOUND && col - 1 >= LOWER_BOUND)
    {
        if (board[row + 1][col - 1] == " ")
        {
            moves.insert(moves.end(), convertIndexToColumn(col - 1) + convertIndexToRow(row + 1));
        }
        else if (isWhite(board[row + 1][col - 1]))
        {
            moves.insert(moves.end(), convertIndexToColumn(col - 1) + convertIndexToRow(row + 1));
        }
    }

    // one left
    if (col - 1 >= LOWER_BOUND)
    {
        if (board[row][col - 1] == " ")
        {
            moves.insert(moves.end(), convertIndexToColumn(col - 1) + convertIndexToRow(row));
        }
        else if (isWhite(board[row][col - 1]))
        {
            moves.insert(moves.end(), convertIndexToColumn(col - 1) + convertIndexToRow(row));
        }
    }

    // one right
    if (col + 1 <= UPPER_BOUND)
    {
        if (board[row][col + 1] == " ")
        {
            moves.insert(moves.end(), convertIndexToColumn(col + 1) + convertIndexToRow(row));
        }
        else if (isWhite(board[row][col + 1]))
        {
            moves.insert(moves.end(), convertIndexToColumn(col + 1) + convertIndexToRow(row));
        }
    }

    // a pawn can retreat regardless of river

    // one retreat backwards
    if (row - 1 >= LOWER_BOUND)
    {
        if (board[row - 1][col] == " ")
        {
            moves.insert(moves.end(), convertIndexToColumn(col) + convertIndexToRow(row - 1));
        }
    }

    // two retreat backwards
    if (row - 2 >= LOWER_BOUND)
    {
        if (board[row - 1][col] == " " && board[row - 2][col] == " ")
        {
            moves.insert(moves.end(), convertIndexToColumn(col) + convertIndexToRow(row - 2));
        }
    }

    // one diagonal retreat backwards and right
    if (row - 1 >= LOWER_BOUND && col + 1 <= UPPER_BOUND)
    {
        if (board[row - 1][col + 1] == " ")
        {
            moves.insert(moves.end(), convertIndexToColumn(col + 1) + convertIndexToRow(row - 1));
        }
    }

    // one diagonal retreat backwards and left
    if (row - 1 >= LOWER_BOUND && col - 1 >= LOWER_BOUND)
    {
        if (board[row - 1][col - 1] == " ")
        {
            moves.insert(moves.end(), convertIndexToColumn(col - 1) + convertIndexToRow(row - 1));
        }
    }

    // two diagonal retreat backwards and right
    if (row - 2 >= LOWER_BOUND && col + 2 <= UPPER_BOUND)
    {
        if (board[row - 1][col + 1] == " " && board[row - 2][col + 2] == " ")
        {
            moves.insert(moves.end(), convertIndexToColumn(col + 2) + convertIndexToRow(row - 2));
        }
    }

    // two diagonal retreat backwards and left
    if (row - 2 >= LOWER_BOUND && col - 2 >= LOWER_BOUND)
    {
        if (board[row - 1][col - 1] == " " && board[row - 2][col - 2] == " ")
        {
            moves.insert(moves.end(), convertIndexToColumn(col - 2) + convertIndexToRow(row - 2));
        }
    }

    return moves;
}

vector<string> superpawnMoves(int row, int col, array<array<string, 7>, 7> board, string color)
{
    vector<string> moves;

    if (color == "white")
    {
        moves = whiteSuperpawnMoves(row, col, board);
        string currPosition = convertIndexToColumn(col) + convertIndexToRow(row);

        // append currPosition to each string in moves
        for (int i = 0; i < moves.size(); i++)
        {
            moves[i] = currPosition + moves[i];
        }

        return moves;
    }
    else
    {
        moves = blackSuperpawnMoves(row, col, board);
        string currPosition = convertIndexToColumn(col) + convertIndexToRow(row);

        // append currPosition to each string in moves
        for (int i = 0; i < moves.size(); i++)
        {
            moves[i] = currPosition + moves[i];
        }

        return moves;
    }
}

int main()
{

    vector<string> fenStrings = readInput();
    for (int i = 0; i < fenStrings.size(); i++)
    {
        array<array<string, 7>, 7> board = processFenString(fenStrings[i]);

        // take the move and split the string in two substrings
        string startingPosition = movesToPlay[i].substr(0, 2);
        string endingPosition = movesToPlay[i].substr(2, 2);

        // convert the substrings to row and column
        int startingRow = convertRowToIndex(string(1, startingPosition[1]));
        int startingCol = convertColumnToIndex(string(1, startingPosition[0]));
        int endingRow = convertRowToIndex(string(1, endingPosition[1]));
        int endingCol = convertColumnToIndex(string(1, endingPosition[0]));

        string pieceToken = board[startingRow][startingCol];

        vector<string> river;

        // add pieces that are in the river to the river vector
        if (turnToPlay == "white")
        {
            // loop through river on board which is row 3
            // and look for pieces that are white 
            for (int i = 0; i < 7; i++)
            {
                if (isWhite(board[3][i]))
                {
                    river.insert(river.end(), board[3][i]);
                }
            }
        }
        else if (turnToPlay == "black")
        {
            // loop through river on board which is row 3
            // and look for pieces that are black 
            for (int i = 0; i < 7; i++)
            {
                if (isBlack(board[3][i]))
                {
                    river.insert(river.end(), board[3][i]);
                }
            }
        }

        board[startingRow][startingCol] = " ";
        board[endingRow][endingCol] = pieceToken;

        if (turnToPlay == "white")
        {
            turnToPlay = "black";
        }
        else
        {
            moveCount++;
            turnToPlay = "white";
        }

        // check if there is a black lion on the board, return false if there is not a black lion
        bool blackLionExists = false;
        for (int row = 0; row < 7; row++)
        {
            for (int col = 0; col < 7; col++)
            {
                if (board[row][col] == "l")
                {
                    blackLionExists = true;
                }
            }
        }

        // check if there is a white lion on the board, return false if there is not a white lion
        bool whiteLionExists = false;
        for (int row = 0; row < 7; row++)
        {
            for (int col = 0; col < 7; col++)
            {
                if (board[row][col] == "L")
                {
                    whiteLionExists = true;
                }
            }
        }

        if (!blackLionExists)
        {
            gameStatus = "White wins";
        }
        else if (!whiteLionExists)
        {
            gameStatus = "Black wins";
        }
        else
        {
            gameStatus = "Continue";
        }

        // check if pieces in the river have remained in the river
        // if so, remove them
        if (turnToPlay == "white")
        {
            // loop through the river 
            // if a piece in the river is in the river vector
            // remove it from the board
            for (int i = 0; i < river.size(); i++)
            {
                if (board[3][i] == river[i])
                {
                    board[3][i] = " ";
                }
            }
        }
        else if (turnToPlay == "black")
        {
            // loop through the river 
            // if a piece in the river is in the river vector
            // remove it from the board
            for (int i = 0; i < river.size(); i++)
            {
                if (board[3][i] == river[i])
                {
                    board[3][i] = " ";
                }
            }
        }

        string FEN = convertToFenString(board);
        string turn;
        if (turnToPlay == "white")
        {
            turn = "w";
        }
        else
        {
            turn = "b";
        }

        FEN = FEN + " " + turn + " " + to_string(moveCount);

        cout << FEN << endl;
        cout << gameStatus << endl;
    }

    return 0;
}