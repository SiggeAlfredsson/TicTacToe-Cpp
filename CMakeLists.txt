cmake_minimum_required(VERSION 3.27)
project(finalproject)

set(CMAKE_CXX_STANDARD 20)

add_executable(finalproject main.cpp
        includes/Player.cpp
        includes/Player.h
        includes/GameBoard.cpp
        includes/GameBoard.h
        includes/GameSession.cpp
        includes/GameSession.h
        includes/Server.cpp
        includes/Server.h
        includes/Client.cpp
        includes/Client.h
)
