#include <iostream>
#include <string>
#include <fstream>
#include <thread>

#include "GameSession.h"
#include "Server.h"
#include "Client.h"

// server stuff
#include <iostream>
#include <fstream>
#include <cstdlib>
#include <cstring>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

int main() {

    int choice = 0;

    do {
        std::cout << "1. Start a new 1v1 locally\n";
        std::cout << "2. Start a online game\n";
        std::cout << "3. Connect to a online game\n";
        std::cout << "4. View your game history\n";
        std::cout << "5. Exit\n";
        std::cout << "Enter your choice (1-5): ";

        std::cin >> choice;

        // prevents loop if input it invalid
        if (std::cin.fail()) {
            std::cin.clear(); // Clear the error flag
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Discard invalid input
        }

        switch (choice) {
            case 1: {

                std::string player1Name, player2Name;

                // start a new game
                std::cout << "Enter Player 1 name: ";
                std::cin >> player1Name;
                std::cout << "Enter Player 2 name: ";
                std::cin >> player2Name;

                GameSession game(player1Name, player2Name);

                // begin the game
                game.startLocalGame();

                // does a game need to be eneded? Deleted?
                break;
            }

            case 2: {
                //start a server and wait for a second player
                std::string player1Name;

                // start a new game
                std::cout << "Enter Player 1 name: ";
                std::cin >> player1Name;
                Server server;
                server.start(player1Name);

//                int socketInput = server.receiveAnswer();
//                std::cout << "Online Player choice: " << socketInput << std::endl;

                GameSession game(player1Name, "SocketPlayer");

                game.startOnlineGame(server);




                break;
            }

            case 3: {
                // connect to a server

                Client client;

                std::string ipAddress;
                int port;

                std::cout << "Enter server IP address: ";
                std::cin >> ipAddress;

                std::cout << "Enter server port: ";
                std::cin >> port;

                client.startConnection(ipAddress, port);

                while (true) {
                    std::string userInput;
                    std::getline(std::cin, userInput);

                    // Send the user's input to the server
                    client.sendMessage(userInput);
                }

                break;
            }

            case 4: {
                // read history
                std::ifstream inputFile("game_history.txt");

                // print if file could not be opened
                if (!inputFile.is_open()) {
                    std::cerr << "Error opening the file." << std::endl;
                }
                // read n print line by line
                std::string line;
                while (std::getline(inputFile, line)) {
                    std::cout << line << std::endl;
                }
                inputFile.close();

                break;
            }

            case 5: {
                // exit the program
//                std::cout << "Thanks for using the program!\n";
                //do while stops and it exsits loop so no need for cout abow., could do return 0 here too
                break;
            }

            default: {
                std::cout << "Invalid choice. Please enter a number between 1 and 3.\n";
            }
        }
    }while(choice != 5);

    std::cout << "Thanks for using the program!\n";
    return 0;
}
    // Create a socket
//    int serverSocket = socket(AF_INET, SOCK_STREAM, 0);
//    if (serverSocket == -1) {
//        perror("Error creating socket");
//        exit(EXIT_FAILURE);
//    }
//
//    // Set up server address structure
//    struct sockaddr_in serverAddress;
//    serverAddress.sin_family = AF_INET;
//    serverAddress.sin_addr.s_addr = INADDR_ANY;
//    serverAddress.sin_port = htons(8888); // You can choose any available port
//
//    // Bind the socket to the specified address and port
//    if (bind(serverSocket, (struct sockaddr*)&serverAddress, sizeof(serverAddress)) == -1) {
//        perror("Error binding socket");
//        close(serverSocket);
//        exit(EXIT_FAILURE);
//    }
//
//    // Listen for incoming connections
//    if (listen(serverSocket, 5) == -1) {
//        perror("Error listening for connections");
//        close(serverSocket);
//        exit(EXIT_FAILURE);
//    }
//
//    std::cout << "Server listening on port 8888...\n";
//
//    while (true) {
//        // Accept incoming connections
//        int clientSocket = accept(serverSocket, nullptr, nullptr);
//        if (clientSocket == -1) {
//            perror("Error accepting connection");
//            close(serverSocket);
//            exit(EXIT_FAILURE);
//        }
//
//        // Send a welcome message to the client
//        const char* welcomeMessage = "Welcome to the server! Enter 1 or 2, or 3 to exit:\n";
//        send(clientSocket, welcomeMessage, strlen(welcomeMessage), 0);
//
//        // Receive user input from the client
//        char buffer[256];
//        memset(buffer, 0, sizeof(buffer));
//        recv(clientSocket, buffer, sizeof(buffer), 0);
//
//        // Process user input
//
//// ... (previous code)
//
//        while (true) {
//            // Receive user input from the client
//            char buffer[256];
//            memset(buffer, 0, sizeof(buffer));
//            recv(clientSocket, buffer, sizeof(buffer), 0);
//
//            // Process user input
//            int userInput = atoi(buffer);
//
//            switch (userInput) {
//                case 1: {
//                    const char *responseMessage = "You selected Option 1.\n";
//                    send(clientSocket, responseMessage, strlen(responseMessage), 0);
//                    break;
//                }
//                case 2: {
//                    const char *responseMessage = "You selected Option 2.\n";
//                    send(clientSocket, responseMessage, strlen(responseMessage), 0);
//                    break;
//                }
//                case 3: {
//                    // Close the client socket and break out of the loop
//                    close(clientSocket);
//                    break;
//                }
//                default: {
//                    const char *errorMessage = "Invalid choice. Please enter 1 or 2.\n";
//                    send(clientSocket, errorMessage, strlen(errorMessage), 0);
//                    break;
//                }
//            }
//        }

// ... (remaining code)


//        if (userInput == 1) {
//            const char* responseMessage = "You selected Option 1.\n";
//            send(clientSocket, responseMessage, strlen(responseMessage), 0);
//        } else if (userInput == 2) {
//            const char* responseMessage = "You selected Option 2.\n";
//            send(clientSocket, responseMessage, strlen(responseMessage), 0);
//        } else {
//            const char* errorMessage = "Invalid choice. Please enter 1 or 2.\n";
//            send(clientSocket, errorMessage, strlen(errorMessage), 0);
//        }

        // Close the client socket
//        close(clientSocket);
//    }
//
//    // This code is unreachable, and the loop runs indefinitely
//    close(serverSocket);
//    return 0;
//}
