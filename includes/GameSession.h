//
// Created by sigge on 2024-01-19.
//

class Server;

#ifndef FINALPROJECT_GAMESESSION_H
#define FINALPROJECT_GAMESESSION_H
#include "Server.h"
#include "Player.h"
#include "GameBoard.h"
#include <vector>
#include <iostream>
#include <fstream>

class GameSession {
private:
    Player player1, player2;
    GameBoard board;
    std::vector<std::string> moves;
    Server* server;

public:
    GameSession(const std::string& name1, const std::string& name2);
    void startLocalGame();
    void startOnlineGame(Server& server);
    void saveGameResultToFile(const std::string &filename, bool b);
};



#endif //FINALPROJECT_GAMESESSION_H
