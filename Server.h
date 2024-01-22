////
//// Created by sigge on 2024-01-20.
////

#ifndef FINALPROJECT_SERVER_H
#define FINALPROJECT_SERVER_H

#include "GameSession.h"
#include <iostream>
#include <cstdlib>
#include <cstring>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

class Server {
public:
    Server();
    ~Server();
    void start(std::string hostName);
    void sendMessage(const char* question);
    int receiveAnswer();
    void closeConnection();


private:
    int serverSocket;
    int clientSocket;
    socklen_t clientLen;
    struct sockaddr_in serverAddress;
    struct sockaddr_in clientAddress;

    void initializeSocket();
    void bindSocket();
    void listenForConnections();
    void acceptConnection();
//    void sendQuestion(const char* question);
//    int receiveAnswer();

};


#endif //FINALPROJECT_SERVER_H
