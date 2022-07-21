#ifndef __WATOPOLY_H__
#define __WATOPOLY_H_
#include <vector>
class Player;
class GameBoard;

class Watoloply {
    vector<Player> players;
    vector<Tile> tiles;
    GameBoard g;

public:
    void init();
    void play();
};

#endif