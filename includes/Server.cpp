////
//// Created by sigge on 2024-01-20.
////
//
#include "Server.h"

Server::Server() : serverSocket(-1), clientSocket(-1), clientLen(0), serverAddress(), clientAddress() {
    initializeSocket();
    bindSocket();
    listenForConnections();
}


Server::~Server() {
    closeConnection();
}

void Server::initializeSocket() {
    serverSocket = socket(AF_INET, SOCK_STREAM, 0);
    if (serverSocket == -1) {
        perror("Error creating socket");
        exit(EXIT_FAILURE);
    }

    serverAddress.sin_family = AF_INET;
    serverAddress.sin_addr.s_addr = INADDR_ANY;
    serverAddress.sin_port = htons(8888);

    std::cout << "Server socket initialized.\n";
}

void Server::bindSocket() {
    if (bind(serverSocket, (struct sockaddr*)&serverAddress, sizeof(serverAddress)) == -1) {
        perror("Error binding socket");
        close(serverSocket);
        exit(EXIT_FAILURE);
    }

    std::cout << "Server socket bound.\n";
}

void Server::listenForConnections() {
    if (listen(serverSocket, 1) == -1) {
        perror("Error listening for connections");
        close(serverSocket);
        exit(EXIT_FAILURE);
    }

    std::cout << "Server listening for connections on port 8888...\n";
}

void Server::acceptConnection() {
    clientLen = sizeof(clientAddress);
    clientSocket = accept(serverSocket, (struct sockaddr*)&clientAddress, &clientLen);
    if (clientSocket == -1) {
        perror("Error accepting connection");
        close(serverSocket);
        exit(EXIT_FAILURE);
    }

    std::cout << "Connection accepted from " << inet_ntoa(clientAddress.sin_addr) << "\n";
}

void Server::sendMessage(const char* question) {
    send(clientSocket, question, strlen(question), 0);
}

int Server::receiveAnswer() {
    char buffer[256];
    memset(buffer, 0, sizeof(buffer));

    recv(clientSocket, buffer, sizeof(buffer), 0);

    int userInput = atoi(buffer);

    std::cout << userInput << "\n";
    return int(userInput);
}

void Server::closeConnection() {
    if (clientSocket != -1) {
        close(clientSocket);
    }
    if (serverSocket != -1) {
        close(serverSocket);
    }
}

void Server::start(std::string hostName) {
    acceptConnection();

    std::string welcomeMessage = ("Welcome to Tic Tac Toe, you play against " + hostName + "\n\r");

    sendMessage(welcomeMessage.c_str());

}
