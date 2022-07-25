#ifndef __WATOPOLY_H__
#define __WATOPOLY_H__

#include <vector>
#include <string>
#include <unordered_map>
#include "gameboard.h"

class Watopoly {
    GameBoard gameboard;
    bool testing;
    static std::unordered_map<char, std::string> playerPieces;

    void initPlayers();
    void load(std::string filename);
    void save(std::string filename);

  public:
    Watopoly(std::string loadfile = "", bool testing = false);
    static std::string getChoice(
        const std::string &message, const std::vector<std::string> &validChoices
    );
    void play();
};

#endif