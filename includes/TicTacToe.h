//
// Created by sigge on 2024-01-18.
//

class TicTacToe {
private:
//    char board[3][3];

    char board[3][3]={
            {'1', '2', '3'},
            {'4', '5', '6'},
            {'7', '8', '9'}
    };

public:
    TicTacToe();

    void printBoard() const;

    bool makeMove(int row, int col, char player);

    bool isBoardFull() const;

    char checkWinner() const;
};


