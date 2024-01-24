//
// Created by sigge on 2024-01-19.
//

#include "Player.h"

Player::Player(const std::string& playerName) : name(new std::string(playerName)) {
}

Player::~Player() {
    delete name; // free memory
}

std::string Player::getName() const {
    return *name;
}
