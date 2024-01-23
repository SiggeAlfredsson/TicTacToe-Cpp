//
// Created by sigge on 2024-01-19.
//

#include "Player.h"

Player::Player(const std::string& playerName) : name(playerName) {
    // Optionally, you can add more initialization logic here
}

std::string Player::getName() const {
    return name;
}
