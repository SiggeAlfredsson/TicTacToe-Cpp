//
// Created by sigge on 2024-01-19.
//

#include "GameSession.h"


GameSession::GameSession(const std::string& name1, const std::string& name2)
        : player1(name1), player2(name2) {
}

void GameSession::startLocalGame() {

    bool player1Turn = true; // x always starts
    int moveCounter = 0; // to keep track if there is a draw (when 9 moves is made)

    while (!board.checkWin() && moveCounter < 9) {
        std::cout << "Current Board:\n";
        board.printBoard();

        Player& currentPlayer = (player1Turn) ? player1 : player2;
        char symbol = (player1Turn) ? 'X' : 'O'; // if player1 turn its x, else its o

        std::cout << currentPlayer.getName() << ", it's your turn. Enter a position (1-9): ";
        int position;
        std::cin >> position;

        if (board.makeMove(position, symbol)) {
            if (player1Turn) { // could be imrpoved
                moves.push_back(player1.getName() + " placed " + symbol + " on " + std::to_string(position));
            } else {
                moves.push_back(player2.getName() + " placed " + symbol + " on " + std::to_string(position));
            }
            // successful move
            player1Turn = !player1Turn;
            moveCounter++;
        } else {
            std::cout << "Invalid move. Try again.\n";
        }
    }

    // print final board
    std::cout << "Final Board:\n";
    board.printBoard();

    // eval result and print
    if (board.checkWin()) {
        std::cout << "Congratulations! " << ((player1Turn) ? player2.getName() : player1.getName()) << " wins!\n";
    } else {
        std::cout << "It's a draw!\n";
    }

    saveGameResultToFile("./game_history.txt", player1Turn);
}

void GameSession::startOnlineGame(Server& server) {


    bool player1Turn = true; // x always starts
    int moveCounter = 0; // to keep track if there is a draw (when 9 moves is made)

    while (!board.checkWin() && moveCounter < 9) {
        std::cout << "Current Board:\n";
        board.printBoard();
        server.sendMessage("Current Board:\n\r");
        server.sendMessage(board.getBoardAsString().c_str());

        Player& currentPlayer = (player1Turn) ? player1 : player2;
        char symbol = (player1Turn) ? 'X' : 'O'; // if player1 turn its x, else its o


        int position;

        if(!player1Turn) {
            std::cout << "Waiting for other player to enter his choice..." << std::endl;
            server.sendMessage("Its your tour, eneter a position (1-9): \n\r");
            position = server.receiveAnswer();
        } else {
            server.sendMessage("Waiting for other player to enter his choice...\n\r");
            std::cout << currentPlayer.getName() << ", it's your turn. Enter a position (1-9): ";
            std::cin >> position;
        }

        if (board.makeMove(position, symbol)) {
            if (player1Turn) { // could be imrpoved
                std::string moveMessage = (player1.getName() + " choose " + std::to_string(position) + "\n\r");
                server.sendMessage(moveMessage.c_str());
                moves.push_back(player1.getName() + " placed " + symbol + " on " + std::to_string(position));
            } else {
                std::cout << player2.getName() << " choose " << std::to_string(position) + "\n\r";
                moves.push_back(player2.getName() + " placed " + symbol + " on " + std::to_string(position));
            }
            // successful move
            player1Turn = !player1Turn;
            moveCounter++;
        } else {
            std::cout << "Invalid move. Try again.\n";
        }
    }

    // print final board
    std::cout << "Final Board:\n";
    board.printBoard();
    server.sendMessage("Final Board:\n\r");
    server.sendMessage(board.getBoardAsString().c_str());

    // eval result and print/send
    if (board.checkWin()) {
        std::string winnerMessage = "Congratulations! " +
                                    ((player1Turn) ? player2.getName() : player1.getName()) +
                                    " wins!\n\r";
        std::cout << winnerMessage;
        server.sendMessage(winnerMessage.c_str());
    } else {
        std::string drawMessage = "Its a draw.\n\r";
        std::cout << drawMessage;
        server.sendMessage(drawMessage.c_str());
    }

    server.closeConnection();

    saveGameResultToFile("./game_history.txt", player1Turn);
}


void GameSession::saveGameResultToFile(const std::string &filename, const bool player1Turn) {

    //eval result again, maybe could save the result in the previus eval but really does not matter
    std::string result;
    if (board.checkWin()) {
        result = "Winner: " + ((player1Turn) ? player2.getName() : player1.getName());
    } else {
        result = "Draw";
    }

    std::ofstream file(filename, std::ios::app);
    if (file.is_open()) {
        file << player1.getName() + " vs " + player2.getName() + " - " + result << "\n";
        file << "moves:" << "\n";
        for (const auto& entry : moves) {
            file << entry << "\n";
        }
        file << "------------------" << "\n";
        file.close();
    } else {
        std::cerr << "Error: Unable to open file when saving history!!!! :(";
    }
}


