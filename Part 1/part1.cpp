// Here i will generate moves for each piece

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

array<array<string, 7>, 7> processFenString(string fenString)
{
    // First the string is split by empty space
    vector<string> fenStringSplit = split(fenString, ' ');

    string gameState = fenStringSplit[0];
    string turn = fenStringSplit[1];
    string moveCount = fenStringSplit[2];

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

// function that returns a vector of strings in alphabetical order
vector<string> sortVector(vector<string> vectorToSort)
{
    // sort the vector manually without using the sort function
    for (int i = 0; i < vectorToSort.size(); i++)
    {
        for (int j = i + 1; j < vectorToSort.size(); j++)
        {
            if (vectorToSort[i] > vectorToSort[j])
            {
                string tmp = vectorToSort[i];
                vectorToSort[i] = vectorToSort[j];
                vectorToSort[j] = tmp;
            }
        }
    }

    return vectorToSort;
}

void outputGameState(array<array<string, 7>, 7> board)
{
    // initialize a vector for each piece 
    vector<string> whitePawn;
    vector<string> blackPawn;
    vector<string> whiteSuperPawn;
    vector<string> blackSuperPawn;
    vector<string> whiteGiraffe;
    vector<string> blackGiraffe;
    vector<string> whiteMonkey;
    vector<string> blackMonkey;
    vector<string> whiteElephant;
    vector<string> blackElephant;
    vector<string> whiteLion;
    vector<string> blackLion;
    vector<string> whiteCrocodile;
    vector<string> blackCrocodile;
    vector<string> whiteZebra;
    vector<string> blackZebra;

    // loop through the board and add the pieces to the vectors
    for (int i = 0; i < board.size(); i++)
    {
        for (int j = 0; j < board[i].size(); j++)
        {
            if (board[i][j] == whitePawnToken)
            {
                whitePawn.push_back(convertIndexToColumn(j) + convertIndexToRow(i));
            }
            else if (board[i][j] == blackPawnToken)
            {
                blackPawn.push_back(convertIndexToColumn(j) + convertIndexToRow(i));
            }
            else if (board[i][j] == whiteSuperPawnToken)
            {
                whiteSuperPawn.push_back(convertIndexToColumn(j) + convertIndexToRow(i));
            }
            else if (board[i][j] == blackSuperPawnToken)
            {
                blackSuperPawn.push_back(convertIndexToColumn(j) + convertIndexToRow(i));
            }
            else if (board[i][j] == whiteGiraffeToken)
            {
                whiteGiraffe.push_back(convertIndexToColumn(j) + convertIndexToRow(i));
            }
            else if (board[i][j] == blackGiraffeToken)
            {
                blackGiraffe.push_back(convertIndexToColumn(j) + convertIndexToRow(i));
            }
            else if (board[i][j] == whiteMonkeyToken)
            {
                whiteMonkey.push_back(convertIndexToColumn(j) + convertIndexToRow(i));
            }
            else if (board[i][j] == blackMonkeyToken)
            {
                blackMonkey.push_back(convertIndexToColumn(j) + convertIndexToRow(i));
            }
            else if (board[i][j] == whiteElephantToken)
            {
                whiteElephant.push_back(convertIndexToColumn(j) + convertIndexToRow(i));
            }
            else if (board[i][j] == blackElephantToken)
            {
                blackElephant.push_back(convertIndexToColumn(j) + convertIndexToRow(i));
            }
            else if (board[i][j] == whiteLionToken)
            {
                whiteLion.push_back(convertIndexToColumn(j) + convertIndexToRow(i));
            }
            else if (board[i][j] == blackLionToken)
            {
                blackLion.push_back(convertIndexToColumn(j) + convertIndexToRow(i));
            }
            else if (board[i][j] == whiteCrocodileToken)
            {
                whiteCrocodile.push_back(convertIndexToColumn(j) + convertIndexToRow(i));
            }
            else if (board[i][j] == blackCrocodileToken)
            {
                blackCrocodile.push_back(convertIndexToColumn(j) + convertIndexToRow(i));
            }
            else if (board[i][j] == whiteZebraToken)
            {
                whiteZebra.push_back(convertIndexToColumn(j) + convertIndexToRow(i));
            }
            else if (board[i][j] == blackZebraToken)
            {
                blackZebra.push_back(convertIndexToColumn(j) + convertIndexToRow(i));
            }
        }
    }

    // alphabetize the vectors
    whitePawn = sortVector(whitePawn);
    blackPawn = sortVector(blackPawn);
    whiteSuperPawn = sortVector(whiteSuperPawn);
    blackSuperPawn = sortVector(blackSuperPawn);
    whiteGiraffe = sortVector(whiteGiraffe);
    blackGiraffe = sortVector(blackGiraffe);
    whiteMonkey = sortVector(whiteMonkey);
    blackMonkey = sortVector(blackMonkey);
    whiteElephant = sortVector(whiteElephant);
    blackElephant = sortVector(blackElephant);
    whiteLion = sortVector(whiteLion);
    blackLion = sortVector(blackLion);
    whiteCrocodile = sortVector(whiteCrocodile);
    blackCrocodile = sortVector(blackCrocodile);
    whiteZebra = sortVector(whiteZebra);
    blackZebra = sortVector(blackZebra);

    // output the status of the board
    cout << "White Pawn: ";
    for (int i = 0; i < whitePawn.size(); i++)
    {
        cout << whitePawn[i] << " ";
    }
    cout << endl;
    cout << "Black Pawn: ";
    for (int i = 0; i < blackPawn.size(); i++)
    {
        cout << blackPawn[i] << " ";
    }
    cout << endl;
    cout << "White Super Pawn: ";
    for (int i = 0; i < whiteSuperPawn.size(); i++)
    {
        cout << whiteSuperPawn[i] << " ";
    }
    cout << endl;
    cout << "Black Super Pawn: ";
    for (int i = 0; i < blackSuperPawn.size(); i++)
    {
        cout << blackSuperPawn[i] << " ";
    }
    cout << endl;
    cout << "White Giraffe: ";
    for (int i = 0; i < whiteGiraffe.size(); i++)
    {
        cout << whiteGiraffe[i] << " ";
    }
    cout << endl;
    cout << "Black Giraffe: ";
    for (int i = 0; i < blackGiraffe.size(); i++)
    {
        cout << blackGiraffe[i] << " ";
    }
    cout << endl;
    cout << "White Monkey: ";
    for (int i = 0; i < whiteMonkey.size(); i++)
    {
        cout << whiteMonkey[i] << " ";
    }
    cout << endl;
    cout << "Black Monkey: ";
    for (int i = 0; i < blackMonkey.size(); i++)
    {
        cout << blackMonkey[i] << " ";
    }
    cout << endl;
    cout << "White Elephant: ";
    for (int i = 0; i < whiteElephant.size(); i++)
    {
        cout << whiteElephant[i] << " ";
    }
    cout << endl;
    cout << "Black Elephant: ";
    for (int i = 0; i < blackElephant.size(); i++)
    {
        cout << blackElephant[i] << " ";
    }
    cout << endl;
    cout << "White Lion: ";
    for (int i = 0; i < whiteLion.size(); i++)
    {
        cout << whiteLion[i] << " ";
    }
    cout << endl;
    cout << "Black Lion: ";
    for (int i = 0; i < blackLion.size(); i++)
    {
        cout << blackLion[i] << " ";
    }
    cout << endl;
    cout << "White Crocodile: ";
    for (int i = 0; i < whiteCrocodile.size(); i++)
    {
        cout << whiteCrocodile[i] << " ";
    }
    cout << endl;
    cout << "Black Crocodile: ";
    for (int i = 0; i < blackCrocodile.size(); i++)
    {
        cout << blackCrocodile[i] << " ";
    }
    cout << endl;
    cout << "White Zebra: ";
    for (int i = 0; i < whiteZebra.size(); i++)
    {
        cout << whiteZebra[i] << " ";
    }
    cout << endl;
    cout << "Black Zebra: ";
    for (int i = 0; i < blackZebra.size(); i++)
    {
        cout << blackZebra[i] << " ";
    }
    cout << endl;

}

int main()
{   
    vector<string> fenStrings = readInput();
    for (int i = 0; i < fenStrings.size(); i++) {
        outputGameState(processFenString(fenStrings[i]));
        if (turnToPlay == "white") {
            cout << "side to play: white" << endl;
        }
        else {
            cout << "side to play: black" << endl;
        }
        cout << "\n";
    }
    return 0;
}