//
// Created by sigge on 2024-01-23.
//

#include "Client.h"

Client::Client() {
    clientSocket = socket(AF_INET, SOCK_STREAM, 0);
    if (clientSocket == -1) {
        perror("Error creating socket");
        exit(EXIT_FAILURE);
    }
}

Client::~Client() {
    close(clientSocket);
}

void Client::receiveMessages(int clientSocket, bool& connectedToServer) {
    char buffer[256];
    memset(buffer, 0, sizeof(buffer));

    while (true) {
        // get "messages" from the server
        ssize_t bytesRead = recv(clientSocket, buffer, sizeof(buffer), 0);

        if (bytesRead <= 0) {
            std::cout << "Server disconnected." << std::endl;
            connectedToServer = false;
            break;
        }

        std::cout << buffer << std::endl;

        // clear the buffer for the next message
        memset(buffer, 0, sizeof(buffer));
    }
}

// ip address is passed by reference instead of value bcs its "best practice for string"? and not for int?
// anyways it avoids copying the whole string
void Client::startConnection(const std::string& ipAddress,const int port) {
    serverAddress.sin_family = AF_INET;
    serverAddress.sin_port = htons(port);
    serverAddress.sin_addr.s_addr = inet_addr(ipAddress.c_str());

    if (connect(clientSocket, (struct sockaddr*)&serverAddress, sizeof(serverAddress)) == -1) {
        perror("Error connecting to the server");
        exit(EXIT_FAILURE);
    }

    char buffer[256];
    memset(buffer, 0, sizeof(buffer));

    bool connectedToServer = true;

    // thread to receive messages
    std::thread receiveThread(receiveMessages, clientSocket, std::ref(connectedToServer));

    // main thread to send messages
    while (connectedToServer) {
        std::string userInput;
        std::getline(std::cin, userInput);

        // send the input to the server
        send(clientSocket, userInput.c_str(), userInput.size(), 0);
    }

    close(clientSocket);

    // Wait for the receive thread to finish
    receiveThread.join();
}
