#ifndef __WATOPOLY_H__
#define __WATOPOLY_H__

#include <vector>
#include <memory>
#include "gameboard.h"

class Player;
class GameBoard;
class Tile;

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