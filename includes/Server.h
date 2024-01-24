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
#include <fstream>

class Server {
public:
    explicit Server(int port); // const makes it read only
    ~Server();
    void start(std::string hostName);
    void sendMessage(const char* question);
    int receiveAnswer();
    void closeConnection();


private:
    int port;
//    int hostName; not used
    int serverSocket;
    int clientSocket;
    socklen_t clientLen;

    // standard socket struct from imports, to define socket addresses for both server and client !!
    struct sockaddr_in serverAddress;
    struct sockaddr_in clientAddress;

    void initializeSocket(int port);
    void bindSocket();
    void listenForConnections(int port);
    void acceptConnection();
    void saveTextToFile(const std::string& text);
};


#endif //FINALPROJECT_SERVER_H
