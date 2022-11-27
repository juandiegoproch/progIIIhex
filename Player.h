#ifndef HEX_GAME_PLAYER_H
#define HEX_GAME_PLAYER_H

#include <string>

class Player {
private:
    std::string name;
    char playerSymbol;
    bool isComputer;
    int timeLeft;

public:
    Player(const std::string& name, char playerSymbol, bool isComputer, int timeLeft);

    std::string getName() const;
    char getPlayerSymbol() const;
    bool isIsComputer() const;
    int getTimeLeft() const;

    void setTimeLeft(int left);
    void decreaseTimeLeft(int time);

    ~Player();
};

#endif //HEX_GAME_PLAYER_H
