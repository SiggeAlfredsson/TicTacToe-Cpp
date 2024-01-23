//
// Created by sigge on 2024-01-23.
//

#ifndef FINALPROJECT_CLIENT_H
#define FINALPROJECT_CLIENT_H


#include <string>
#include <iostream>
#include <cstring>
#include <arpa/inet.h>
#include <unistd.h>
#include <thread>

class Client {
public:
    Client();
    ~Client();
    void startConnection(const std::string& ipAdress, int port);
//    void sendMessage(const std::string& message);
//    void receiveMessages();

private:
    int clientSocket;
    sockaddr_in serverAddress;
    char buffer[256];
    static void receiveMessages(int clientSocket, bool& serverDisconnected);

//    static void receiveMessagesThread(Client* client);


};


#endif //FINALPROJECT_CLIENT_H
