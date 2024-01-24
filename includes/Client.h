//
// Created by sigge on 2024-01-23.
//

#ifndef FINALPROJECT_CLIENT_H
#define FINALPROJECT_CLIENT_H


#include <iostream>
#include <cstring>
#include <arpa/inet.h>
#include <unistd.h>
#include <thread>

class Client {
public:
    Client();
    ~Client();
    void startConnection(const std::string& ipAddress,int port);

private:
    int clientSocket;
    sockaddr_in serverAddress;
    static void receiveMessages(int clientSocket, bool& connectedToServer);

};


#endif //FINALPROJECT_CLIENT_H
