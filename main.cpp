#include <iostream>
#include <string>
#include <fstream>
#include <thread>

#include "includes/GameSession.h"
#include "includes/Server.h"
#include "includes/Client.h"


// Would be nice if a socketplayer could enter their own name but i only got numbers to work
// client player needs to press enter to get back to the menu
// fix so history txt file is not in the cmake folder??

// study more what does what


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
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // discard invalid input
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
                // connection is closed from within startConnection

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
                std::cout << "Invalid choice. Please enter a number between 1 and 5.\n";
            }
        }
    }while(choice != 5);

    std::cout << "Thanks for using the program!\n";
    return 0;
}

