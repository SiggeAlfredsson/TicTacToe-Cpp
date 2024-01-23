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

void Client::receiveMessages(int clientSocket) {
    char buffer[256];
    memset(buffer, 0, sizeof(buffer));

    while (true) {
        // Receive messages from the server
        ssize_t bytesRead = recv(clientSocket, buffer, sizeof(buffer), 0);

        if (bytesRead <= 0) {
            // Either an error occurred or the server closed the connection
            std::cout << "Server disconnected." << std::endl;
            break;
        }

        std::cout << buffer << std::endl;

        // Clear the buffer for the next message
        memset(buffer, 0, sizeof(buffer));
    }
}

void Client::startConnection(const std::string& ipAddress, int port) {
    serverAddress.sin_family = AF_INET;
    serverAddress.sin_port = htons(port);
    serverAddress.sin_addr.s_addr = inet_addr(ipAddress.c_str());

    if (connect(clientSocket, (struct sockaddr*)&serverAddress, sizeof(serverAddress)) == -1) {
        perror("Error connecting to the server");
        exit(EXIT_FAILURE);
    }

    char buffer[256];
    memset(buffer, 0, sizeof(buffer));

    // Receive welcome message from the server
    recv(clientSocket, buffer, sizeof(buffer), 0);
    std::cout << buffer << std::endl;

    // Start a separate thread to continuously receive messages
    std::thread receiveThread(receiveMessages, clientSocket);

    // Main thread to continuously send messages
    while (true) {
        std::string userInput;
        std::getline(std::cin, userInput);

        // Send the user's input to the server
        send(clientSocket, userInput.c_str(), userInput.size(), 0);
    }

    // Close the client socket when done
    close(clientSocket);

    // Wait for the receive thread to finish
    receiveThread.join();
}



//void Client::sendMessage(const std::string& message) {
//    // Send the user's input to the server
//    send(clientSocket, message.c_str(), message.size(), 0);
//}
//
//void Client::receiveMessagesThread(Client* client) {
//    client->receiveMessages();
//}
//
//void Client::receiveMessages() {
//    while (true) {
//        // Receive messages from the server
//        ssize_t bytesRead = recv(clientSocket, buffer, sizeof(buffer), 0);
//
//        if (bytesRead <= 0) {
//            // Either an error occurred or the server closed the connection
//            std::cout << "Server disconnected." << std::endl;
//            break;
//        }
//
//        std::cout << buffer << std::endl;
//
//        // Clear the buffer for the next message
//        memset(buffer, 0, sizeof(buffer));
//    }
//}

