#include "Player.h"

Player::Player(const std::string& name, char playerSymbol, bool isComputer, int timeLeft) {
    this->name = name;
    this->playerSymbol = playerSymbol;
    this->isComputer = isComputer;
    this->timeLeft = timeLeft;
}

std::string Player::getName() const {
    return this->name;
}

char Player::getPlayerSymbol() const {
    return this->playerSymbol;
}

bool Player::isIsComputer() const {
    return this->isComputer;
}

int Player::getTimeLeft() const {
    return this->timeLeft;
}

void Player::setTimeLeft(int left) {
    this->timeLeft = left;
}

void Player::decreaseTimeLeft(int time) {
    this->timeLeft -= time;
}

Player::~Player() = default;
