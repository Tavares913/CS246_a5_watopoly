#ifndef __TILE_H__
#define __TILE_H__

#include <string>

class Player;

class Tile {
    std::string name;
    int location;

  public:
    Tile(std::string name, int location);
    std::string getName() const;
    virtual void visit(Player &) = 0;
};

#endif