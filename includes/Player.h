//
// Created by sigge on 2024-01-19.
//

#ifndef FINALPROJECT_PLAYER_H
#define FINALPROJECT_PLAYER_H


#include <iostream>

class Player {
public:
    Player(const std::string& playerName);

    std::string getName() const;

private:
    std::string name;
//    char symbol; not used, but should maybe impl
};



#endif //FINALPROJECT_PLAYER_H
