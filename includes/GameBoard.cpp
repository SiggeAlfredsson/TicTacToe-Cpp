//
// Created by sigge on 2024-01-19.
//



#include "GameBoard.h"

GameBoard::GameBoard() {
    // initialize the board with numbers representing each cell
    char cellNumber = '1';
    for (int i = 0; i < 3; ++i)
        for (int j = 0; j < 3; ++j)
            board[i][j] = cellNumber++;

//    char board[3][3]={                   // it is like this
//            {'1', '2', '3'},
//            {'4', '5', '6'},
//            {'7', '8', '9'}
//    };

}

void GameBoard::printBoard() const {
    // print board

    std::cout << " " << board[0][0] << " | " << board[0][1] << " | " << board[0][2] << std::endl;
    std::cout << " - - - - - " << std::endl;
    std::cout << " " << board[1][0] << " | " << board[1][1] << " | " << board[1][2] << std::endl;
    std::cout << " - - - - - " << std::endl;
    std::cout << " " << board[2][0] << " | " << board[2][1] << " | " << board[2][2] << std::endl;
}

std::string GameBoard::getBoardAsString() const { // this was made after for online play but i guess the app would work on only this.

    std::string boardString =
            " " + std::string(1, board[0][0]) + " | " + std::string(1, board[0][1]) + " | " + std::string(1, board[0][2]) + "\n\r" +
            " - - - - - \n\r" +
            " " + std::string(1, board[1][0]) + " | " + std::string(1, board[1][1]) + " | " + std::string(1, board[1][2]) + "\n\r" +
            " - - - - - \n\r" +
            " " + std::string(1, board[2][0]) + " | " + std::string(1, board[2][1]) + " | " + std::string(1, board[2][2]) + "\n\r";

    return boardString;

}

bool GameBoard::makeMove(int position, char symbol) {

    if (position < 1 || position > 9) {
        return false;
    }

    // finds the row/col bcs its char[3][3] and not a list
    int row = (position - 1) / 3;
    int col = (position - 1) % 3;

    // check so move is legal (not already made)
    if (board[row][col] != 'X' && board[row][col] != 'O') {
        // add the symbol to the board and return true
        board[row][col] = symbol;
        return true;
    } else {
        return false;
    }
}

bool GameBoard::checkWin() const {
    // this checks all possible wins and checks so they are the same symbol and that symbol is not nothing or != " "; i guess it never is nothing tho bcs it has a number from the start?

    // straight lines
    for (int i = 0; i < 3; ++i) {
        if (board[i][0] == board[i][1] && board[i][1] == board[i][2] && board[i][0] != ' ')
            return true;  // rows
        if (board[0][i] == board[1][i] && board[1][i] == board[2][i] && board[0][i] != ' ')
            return true;  // columns
    }

    // diagonals , only two
    if (board[0][0] == board[1][1] && board[1][1] == board[2][2] && board[0][0] != ' ')
        return true;
    if (board[0][2] == board[1][1] && board[1][1] == board[2][0] && board[0][2] != ' ')
        return true;

    return false;  // no winner
}