////
//// Created by sigge on 2024-01-20.
////
//
#include "Server.h"

//const here supposoble makes the port read only in the functions called from here too.
Server::Server(const int port) : serverSocket(-1), clientSocket(-1), clientLen(0), serverAddress(), clientAddress(), port(port) {
    initializeSocket(port);
    bindSocket();
    listenForConnections(port);
}


Server::~Server() {
    closeConnection();
}

void Server::initializeSocket(int port) {
    serverSocket = socket(AF_INET, SOCK_STREAM, 0);
    if (serverSocket == -1) {
        perror("Error creating socket");
        exit(EXIT_FAILURE);
    }

    // server adress setup
    serverAddress.sin_family = AF_INET; // makes socket work with IPv4 adress
    serverAddress.sin_addr.s_addr = INADDR_ANY; // allowing it to accept connections from any source ip
    serverAddress.sin_port = htons(port); // port to bind with

    std::cout << "Server socket initialized.\n";
}

void Server::bindSocket() {
    // bind socket to specified address and port
    if (bind(serverSocket, (struct sockaddr*)&serverAddress, sizeof(serverAddress)) == -1) {
        perror("Error binding socket");
        close(serverSocket);
        exit(EXIT_FAILURE);
    }

    std::cout << "Server socket bound.\n";
}

void Server::listenForConnections(int port) {
    if (listen(serverSocket, 1) == -1) {
        perror("Error listening for connections");
        close(serverSocket);
        exit(EXIT_FAILURE);
    }

    std::cout << "Server listening for connections on port " << port << "...\n";
}

void Server::acceptConnection() {
    clientLen = sizeof(clientAddress);
    clientSocket = accept(serverSocket, (struct sockaddr*)&clientAddress, &clientLen);
    if (clientSocket == -1) {
        perror("Error accepting connection");
        close(serverSocket);
        exit(EXIT_FAILURE);
    }

    std::string clientIpAddress = inet_ntoa(clientAddress.sin_addr);

    std::string acceptedConnectionInfo = "SocketPlayer connected from ip:  " + clientIpAddress;
    std::cout << acceptedConnectionInfo << std::endl;
    saveTextToFile(acceptedConnectionInfo);

}

void Server::sendMessage(const char* question) { // pointer to question
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

// i guess the server is already started but it starts to accept connections ? heh
void Server::start(const std::string hostName) {

    saveTextToFile("Server started by " + hostName + " on port : " + std::to_string(port));

    acceptConnection();

    std::string welcomeMessage = ("Welcome to Tic Tac Toe, you play against " + hostName + "\n\r");

    sendMessage(welcomeMessage.c_str());
}

void Server::saveTextToFile(const std::string& text) {
    std::ofstream file("./server_history.txt", std::ios::app);
    if (file.is_open()) {
        file << text << "\n";
        file.close();
    } else {
        std::cerr << "Error: Unable to open file to write server history ! :(";
    }

}
