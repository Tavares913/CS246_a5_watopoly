#ifndef __WATOPOLY_H__
#define __WATOPOLY_H_
#include <vector>
#include "gameboard.h"

using namespace std;

class Player;
class GameBoard;
class Tile;

class Watopoly {
    vector<Player> players;
    vector<Tile> tiles;
    GameBoard gameboard;

public:
    void init();
    void play();
};

#endif