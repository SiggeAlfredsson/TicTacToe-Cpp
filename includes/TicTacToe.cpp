//
// Created by sigge on 2024-01-18.
//

#include "TicTacToe.h"
#include <iostream>

TicTacToe::TicTacToe() {
    // Initialize the board
//    char board[3][3]={
//            {'1', '2', '3'},
//            {'4', '5', '6'},
//            {'7', '8', '9'}
//    };

}

void TicTacToe::printBoard() const {
    std::cout << " " << board[0][0] << " | " << board[0][1] << " | " << board[0][2] << std::endl;
    std::cout << " - - - - - " << std::endl;
    std::cout << " " << board[1][0] << " | " << board[1][1] << " | " << board[1][2] << std::endl;
    std::cout << " - - - - - " << std::endl;
    std::cout << " " << board[2][0] << " | " << board[2][1] << " | " << board[2][2] << std::endl;
}

bool TicTacToe::makeMove(int row, int col, char player) {
    // Implementation...
}

bool TicTacToe::isBoardFull() const {
    // Implementation...
}

char TicTacToe::checkWinner() const {
    // Implementation...
}



