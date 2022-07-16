#ifndef __TILE_H__
#define __TILE_H__

class Player;

class Tile {
        int location;

    public:
        Tile(int location);
        virtual void visit(Player &) = 0;
};

#endif