//
// Created by sigge on 2024-01-19.
//

#ifndef FINALPROJECT_GAMEBOARD_H
#define FINALPROJECT_GAMEBOARD_H

#include <vector>
#include <iostream>

class GameBoard {

public:
    GameBoard();
    void printBoard() const;
    std::string getBoardAsString() const;
    bool makeMove(int position, char symbol);
    bool checkWin() const;


private:
    char board[3][3];
//    std::vector<char> charList;
};


#endif //FINALPROJECT_GAMEBOARD_H
