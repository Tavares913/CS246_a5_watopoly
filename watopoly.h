#ifndef __WATOPOLY_H__
#define __WATOPOLY_H__

#include <string>

class GameBoard;

class Watopoly {
    GameBoard gameboard;

    void initPlayers();

  public:
    void init();
    void play();
    void load(std::string filename);
    void save(std::string filename);
};

#endif