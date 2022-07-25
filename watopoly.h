#ifndef __WATOPOLY_H__
#define __WATOPOLY_H__

#include <string>

class GameBoard;

class Watopoly {
    GameBoard gameboard;
    bool testing;

    void initPlayers();
    void load(std::string filename);
    void save(std::string filename);

  public:
    Watopoly(std::string loadfile = "", bool testing = false);
    void play();
};

#endif