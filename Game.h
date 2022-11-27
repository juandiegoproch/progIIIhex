#ifndef HEX_GAME_GAME_H
#define HEX_GAME_GAME_H

#include <iostream>
#include <vector>
#include <iomanip>
#include <synchapi.h>
#include <condition_variable>
#include <thread>

#include "Player.h"

class Game {
private:
    int tableSize;
    std::vector<std::vector<char>> table;
    std::vector<Player> players;
    int indexOfWinnerPlayer;
    int turnTime;

protected:
    static std::string getCenteredText(const std::string& text, int width);
    static std::string getCenteredTitle(const std::string& text, int width);
    bool isAWinner(char playerSymbol, bool isVerticalCheck);
    void printTable();

public:
    explicit Game();

    void setUpGame();
    void setUpPlayers();
    void startGame();

    ~Game();
};

#endif //HEX_GAME_GAME_H
