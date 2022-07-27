#ifndef __TILE_H__
#define __TILE_H__

#include <string>

class Player;

class Tile {
    int location;
    std::string name;

  public:
    Tile(int location, std::string name);
    std::string getName() const;
    int getLocation() const;
    virtual void visit(Player &) = 0;
    virtual ~Tile() = 0;
};

#endif
