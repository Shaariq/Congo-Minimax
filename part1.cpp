// This is part 1 of the congo-ai assignment
// It will take user input and output the game state 

#include <iostream>
#include <string>
#include <array>
#include <vector>
#include <sstream>

using namespace std;

// initialise piece tokens
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

// Class for a piece
class Piece
{
    private:
        string Row;
        string Column;
        string Color;
    
    public:
        // function to set the row and column
        void setRowColumn(string row, string column)
        {
            Row = row;
            Column = column;
        }

        void setColor(string color)
        {
            Color = color;
        }

        // function to get the row
        string getRow()
        {
            return Row;
        }

        // function to get the column
        string getColumn()
        {
            return Column;
        }

        // function to get the name
        string getColor()
        {
            return Color;
        }
};

// Class for a pawn
class Pawn : public Piece
{
    public:
        // function to get the token
        string getToken()
        {
            return whitePawnToken;
        }
};

// Class for a super pawn
class SuperPawn : public Piece
{
    public:
        // function to get the token
        string getToken()
        {
            return whiteSuperPawnToken;
        }
};

// Class for a giraffe
class Giraffe : public Piece
{
    public:
        // function to get the token
        string getToken()
        {
            return whiteGiraffeToken;
        }
};

// Class for a monkey
class Monkey : public Piece
{
    public:
        // function to get the token
        string getToken()
        {
            return whiteMonkeyToken;
        }
};

// Class for an elephant
class Elephant : public Piece
{
    public:
        // function to get the token
        string getToken()
        {
            return whiteElephantToken;
        }
};

// Class for a lion
class Lion : public Piece
{
    public:
        // function to get the token
        string getToken()
        {
            return whiteLionToken;
        }
};

// Class for a crocodile
class Crocodile : public Piece
{
    public:
        // function to get the token
        string getToken()
        {
            return whiteCrocodileToken;
        }
};

// Class for a zebra
class Zebra : public Piece
{
    public:
        // function to get the token
        string getToken()
        {
            return whiteZebraToken;
        }
};

// This function will read in user input
// The user will first enter the number of FEN strings to be entered
// Then the user will enter the FEN strings
// The function will return an array of FEN strings
vector<string> readInput() 
{
    vector<string> fenStrings;
    string fenCount;

    getline(cin, fenCount);

    for (int i = 0; i < stoi(fenCount); i++) {
        string tmp;
        getline(cin, tmp);
        fenStrings.push_back(tmp);
    }

    return fenStrings;
}

// This function will split a string into an array of strings
vector<string> split(string str, char delimiter) 
{
    vector<string> splitString;
    stringstream ss(str);
    string tmp;

    while (!ss.eof()) {
        getline(ss, tmp, delimiter);
        splitString.push_back(tmp);
    }

    return splitString;
}

// This is the format of the FEN string
// 1m1El2/P1P2P1/1S4C/4S2/1E3S1/1P3c1/2GL3 b 79

// print the game board
void printBoard(array<array<string, 7>, 7> board)
{
    for (int i = 0; i < board.size(); i++) {
        for (int j = 0; j < board[i].size(); j++) {
            cout << board[i][j];
        }
        cout << endl;
    }
}

// this function will flip the board
array<array<string, 7>, 7> flipBoard(array<array<string, 7>, 7> board)
{
    array<array<string, 7>, 7> flippedBoard;

    // loop through the board
    for (int i = 0; i < board.size(); i++) {
        for (int j = 0; j < board[i].size(); j++) {
            // flip the board
            flippedBoard[i][j] = board[board.size() - i - 1][board[i].size() - j - 1];
        }
    }

    return flippedBoard;
}

// this function will rotate the board 90 degrees clockwise
array<array<string, 7>, 7> rotateBoard(array<array<string, 7>, 7> board)
{
    array<array<string, 7>, 7> rotatedBoard;

    // loop through the board
    for (int i = 0; i < board.size(); i++) {
        for (int j = 0; j < board[i].size(); j++) {
            // rotate the board
            rotatedBoard[i][j] = board[board[i].size() - j - 1][i];
        }
    }

    return rotatedBoard;
}

// this function will flip the board horizontally
array<array<string, 7>, 7> flipBoardHorizontal(array<array<string, 7>, 7> board)
{
    array<array<string, 7>, 7> flippedBoard;

    // loop through the board
    for (int i = 0; i < board.size(); i++) {
        for (int j = 0; j < board[i].size(); j++) {
            // flip the board
            flippedBoard[i][j] = board[i][board[i].size() - j - 1];
        }
    }

    return flippedBoard;
}

// this function will flip the board about the x axis
array<array<string, 7>, 7> flipBoardXAxis(array<array<string, 7>, 7> board)
{
    array<array<string, 7>, 7> flippedBoard;

    // loop through the board
    for (int i = 0; i < board.size(); i++) {
        for (int j = 0; j < board[i].size(); j++) {
            // flip the board
            flippedBoard[i][j] = board[board.size() - i - 1][j];
        }
    }

    return flippedBoard;
}

// This function will populate the game board
array<array<string, 7>, 7> populateBoard(vector<string> gameState)
{
    array<array<string, 7>, 7> board;

    for (int i = 0; i < board.size(); i++) {
        for (int j = 0; j < board[i].size(); j++) {
            board[i][j] = " ";
        }
    }

    // loop through the game state 
    // if there is a digit, convert it to a series of 1s 
    for (int i = 0; i < gameState.size(); i++) {
        string tmp = gameState[i];
        string newString = "";
        for (int j = 0; j < tmp.length(); j++) {
            if (isdigit(tmp[j])) {
                for (int k = 0; k < tmp[j] - '0'; k++) {
                    newString += "1";
                }
            } else {
                newString += tmp[j];
            }
        }
        gameState[i] = newString;
    }

    // loop through the game state
    for (int i = 0; i < gameState.size(); i++) {
        for (int j = 0; j < gameState[i].size(); j++) {
            if (isdigit(gameState[i][j])) {
                int num = gameState[i][j] - '0';
                // skip those many spaces on the board
                for (int k = 0; k < num; k++) {
                    board[i][j] = " ";
                }
            } else {
                board[i][j] = gameState[i][j];
            } 
        }
    }

    // return board;
    return flipBoardXAxis(board);
}

// This function will process the FEN string
array<array<string, 7>, 7> processFenString(string fenString)
{
    // First the string is split by empty space
    vector<string> fenStringSplit = split(fenString, ' ');

    string gameState = fenStringSplit[0];
    string turn = fenStringSplit[1];
    string moveCount = fenStringSplit[2];

    if (turn == "w") {
        turnToPlay = "white";
    }
    else if (turn == "b") {
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

// convert row numbers to letters
string convertRow(int row)
{
    switch (row) {
        case 0:
            return "a";
        case 1:
            return "b";
        case 2:
            return "c";
        case 3:
            return "d";
        case 4:
            return "e";
        case 5:
            return "f";
        case 6:
            return "g";
        default:
            return " ";
    }
}

// convert column numbers to numbers
string convertColumn(int column)
{
    switch (column) {
        case 0:
            return "1";
        case 1:
            return "2";
        case 2:
            return "3";
        case 3:
            return "4";
        case 4:
            return "5";
        case 5:
            return "6";
        case 6:
            return "7";
        default:
            return " ";
    }
}

// output the game state
void outputGameState(array<array<string, 7>, 7> board)
{
    // initialise arrays for each piece
    vector<Pawn> whitePawn;
    vector<Pawn> blackPawn;
    vector<SuperPawn> whiteSuperPawn;
    vector<SuperPawn> blackSuperPawn;
    vector<Giraffe> whiteGiraffe;
    vector<Giraffe> blackGiraffe;
    vector<Monkey> whiteMonkey;
    vector<Monkey> blackMonkey;
    vector<Elephant> whiteElephant;
    vector<Elephant> blackElephant;
    vector<Lion> whiteLion;
    vector<Lion> blackLion;
    vector<Crocodile> whiteCrocodile;
    vector<Crocodile> blackCrocodile;
    vector<Zebra> whiteZebra;
    vector<Zebra> blackZebra;

    for (int i = 0; i < board.size(); i++) {
        for (int j = 0; j < board[i].size(); j++) {
            if (board[i][j] == whitePawnToken) {
                Pawn pawn;
                pawn.setColor("w");
                pawn.setRowColumn(convertRow(j), convertColumn(i));
                whitePawn.push_back(pawn);
            } else if (board[i][j] == blackPawnToken) {
                Pawn pawn;
                pawn.setColor("b");
                pawn.setRowColumn(convertRow(j), convertColumn(i));
                blackPawn.push_back(pawn);
            } else if (board[i][j] == whiteSuperPawnToken) {
                SuperPawn superPawn;
                superPawn.setColor("w");
                superPawn.setRowColumn(convertRow(j), convertColumn(i));
                whiteSuperPawn.push_back(superPawn);
            } else if (board[i][j] == blackSuperPawnToken) {
                SuperPawn superPawn;
                superPawn.setColor("b");
                superPawn.setRowColumn(convertRow(j), convertColumn(i));
                blackSuperPawn.push_back(superPawn);
            } else if (board[i][j] == whiteGiraffeToken) {
                Giraffe giraffe;
                giraffe.setColor("w");
                giraffe.setRowColumn(convertRow(j), convertColumn(i));
                whiteGiraffe.push_back(giraffe);
            } else if (board[i][j] == blackGiraffeToken) {
                Giraffe giraffe;
                giraffe.setColor("b");
                giraffe.setRowColumn(convertRow(j), convertColumn(i));
                blackGiraffe.push_back(giraffe);
            } else if (board[i][j] == whiteMonkeyToken) {
                Monkey monkey;
                monkey.setColor("w");
                monkey.setRowColumn(convertRow(j), convertColumn(i));
                whiteMonkey.push_back(monkey);
            } else if (board[i][j] == blackMonkeyToken) {
                Monkey monkey;
                monkey.setColor("b");
                monkey.setRowColumn(convertRow(j), convertColumn(i));
                blackMonkey.push_back(monkey);
            } else if (board[i][j] == whiteElephantToken) {
                Elephant elephant;
                elephant.setColor("w");
                elephant.setRowColumn(convertRow(j), convertColumn(i));
                whiteElephant.push_back(elephant);
            } else if (board[i][j] == blackElephantToken) {
                Elephant elephant;
                elephant.setColor("b");
                elephant.setRowColumn(convertRow(j), convertColumn(i));
                blackElephant.push_back(elephant);
            } else if (board[i][j] == whiteLionToken) {
                Lion lion;
                lion.setColor("w");
                lion.setRowColumn(convertRow(j), convertColumn(i));
                whiteLion.push_back(lion);
            } else if (board[i][j] == blackLionToken) {
                Lion lion;
                lion.setColor("b");
                lion.setRowColumn(convertRow(j), convertColumn(i));
                blackLion.push_back(lion);
            } else if (board[i][j] == whiteCrocodileToken) {
                Crocodile crocodile;
                crocodile.setColor("w");
                crocodile.setRowColumn(convertRow(j), convertColumn(i));
                whiteCrocodile.push_back(crocodile);
            } else if (board[i][j] == blackCrocodileToken) {
                Crocodile crocodile;
                crocodile.setColor("b");
                crocodile.setRowColumn(convertRow(j), convertColumn(i));
                blackCrocodile.push_back(crocodile);
            } else if (board[i][j] == whiteZebraToken) {
                Zebra zebra;
                zebra.setColor("w");
                zebra.setRowColumn(convertRow(j), convertColumn(i));
                whiteZebra.push_back(zebra);
            } else if (board[i][j] == blackZebraToken) {
                Zebra zebra;
                zebra.setColor("b");
                zebra.setRowColumn(convertRow(j), convertColumn(i));
                blackZebra.push_back(zebra);
            }
        }
    }

    //loop through each piece and print out its state
    cout << "white pawn: ";
    for (int i = 0; i < whitePawn.size(); i++) {
        cout << whitePawn[i].getRow() << whitePawn[i].getColumn() << " ";
    }
    cout << endl;
    cout << "black pawn: ";
    for (int i = 0; i < blackPawn.size(); i++) {
        cout << blackPawn[i].getRow() << blackPawn[i].getColumn() << " ";
    }
    cout << endl;
    cout << "white superpawn: ";
    for (int i = 0; i < whiteSuperPawn.size(); i++) {
        cout << whiteSuperPawn[i].getRow() << whiteSuperPawn[i].getColumn() << " ";
    }
    cout << endl;
    cout << "black superpawn: ";
    for (int i = 0; i < blackSuperPawn.size(); i++) {
        cout << blackSuperPawn[i].getRow() << blackSuperPawn[i].getColumn() << " ";
    }
    cout << endl;
    cout << "white giraffe: ";
    for (int i = 0; i < whiteGiraffe.size(); i++) {
        cout << whiteGiraffe[i].getRow() << whiteGiraffe[i].getColumn() << " ";
    }
    cout << endl;
    cout << "black giraffe: ";
    for (int i = 0; i < blackGiraffe.size(); i++) {
        cout << blackGiraffe[i].getRow() << blackGiraffe[i].getColumn() << " ";
    }
    cout << endl;
    cout << "white monkey: ";
    for (int i = 0; i < whiteMonkey.size(); i++) {
        cout << whiteMonkey[i].getRow() << whiteMonkey[i].getColumn() << " ";
    }
    cout << endl;
    cout << "black monkey: ";
    for (int i = 0; i < blackMonkey.size(); i++) {
        cout << blackMonkey[i].getRow() << blackMonkey[i].getColumn() << " ";
    }
    cout << endl;
    cout << "white elephant: ";
    for (int i = 0; i < whiteElephant.size(); i++) {
        cout << whiteElephant[i].getRow() << whiteElephant[i].getColumn() << " ";
    }
    cout << endl;
    cout << "black elephant: ";
    for (int i = 0; i < blackElephant.size(); i++) {
        cout << blackElephant[i].getRow() << blackElephant[i].getColumn() << " ";
    }
    cout << endl;
    cout << "white lion: ";
    for (int i = 0; i < whiteLion.size(); i++) {
        cout << whiteLion[i].getRow() << whiteLion[i].getColumn() << " ";
    }
    cout << endl;
    cout << "black lion: ";
    for (int i = 0; i < blackLion.size(); i++) {
        cout << blackLion[i].getRow() << blackLion[i].getColumn() << " ";
    }
    cout << endl;
    cout << "white crocodile: ";
    for (int i = 0; i < whiteCrocodile.size(); i++) {
        cout << whiteCrocodile[i].getRow() << whiteCrocodile[i].getColumn() << " ";
    }
    cout << endl;
    cout << "black crocodile: ";
    for (int i = 0; i < blackCrocodile.size(); i++) {
        cout << blackCrocodile[i].getRow() << blackCrocodile[i].getColumn() << " ";
    }
    cout << endl;
    cout << "white zebra: ";
    for (int i = 0; i < whiteZebra.size(); i++) {
        cout << whiteZebra[i].getRow() << whiteZebra[i].getColumn() << " ";
    }
    cout << endl;
    cout << "black zebra: ";
    for (int i = 0; i < blackZebra.size(); i++) {
        cout << blackZebra[i].getRow() << blackZebra[i].getColumn() << " ";
    }
    cout << endl;
    cout << "side to play: " << turnToPlay << endl;
}

int main()
{
    vector<string> fenStrings = readInput();
    for (int i = 0; i < fenStrings.size(); i++) {
        outputGameState(processFenString(fenStrings[i]));
        cout << "\n";
    }

    return 0;
}