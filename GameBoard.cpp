//
// Created by sigge on 2024-01-19.
//



#include <iostream>
#include "GameBoard.h"

GameBoard::GameBoard() {
    // Initialize the board with numbers representing each cell
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

std::string GameBoard::getBoardAsString() const {

    std::string boardString =
            " " + std::string(1, board[0][0]) + " | " + std::string(1, board[0][1]) + " | " + std::string(1, board[0][2]) + "\n\r" +
            " - - - - - \n\r" +
            " " + std::string(1, board[1][0]) + " | " + std::string(1, board[1][1]) + " | " + std::string(1, board[1][2]) + "\n\r" +
            " - - - - - \n\r" +
            " " + std::string(1, board[2][0]) + " | " + std::string(1, board[2][1]) + " | " + std::string(1, board[2][2]) + "\n\r";

    return boardString;

}

bool GameBoard::makeMove(int position, char symbol) {
    // Check if the move is valid
    if (position < 1 || position > 9) {
        return false;
    }

    // Find the corresponding row and column for the given position
    int row = (position - 1) / 3;
    int col = (position - 1) % 3;

    // Check if the cell is already taken
    if (board[row][col] != 'X' && board[row][col] != 'O') {
        // Make the move
        board[row][col] = symbol;
        return true;
    } else {
        return false;
    }
}

bool GameBoard::checkWin() const {
    // Check rows and columns for a win
    for (int i = 0; i < 3; ++i) {
        if (board[i][0] == board[i][1] && board[i][1] == board[i][2] && board[i][0] != ' ')
            return true;  // Check rows
        if (board[0][i] == board[1][i] && board[1][i] == board[2][i] && board[0][i] != ' ')
            return true;  // Check columns
    }

    // Check diagonals for a win
    if (board[0][0] == board[1][1] && board[1][1] == board[2][2] && board[0][0] != ' ')
        return true;  // Check main diagonal
    if (board[0][2] == board[1][1] && board[1][1] == board[2][0] && board[0][2] != ' ')
        return true;  // Check reverse diagonal

    return false;  // No winner yet
}