#ifndef __TILE_H__
#define __TILE_H__
#include <string>

using namespace std;

class Player;

class Tile {
        string name;
        int location;
        

    public:
        Tile(string name, int location);
        string getName();
        virtual void visit(Player &) = 0;
};

#endif