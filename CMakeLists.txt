cmake_minimum_required(VERSION 3.27)
project(finalproject)

set(CMAKE_CXX_STANDARD 20)

add_executable(finalproject main.cpp
        includes/TicTacToe.cpp
        includes/TicTacToe.h
        Player.cpp
        Player.h
        GameBoard.cpp
        GameBoard.h
        GameSession.cpp
        GameSession.h
        History.cpp
        History.h
        Server.cpp
        Server.h
        Client.cpp
        Client.h
)
