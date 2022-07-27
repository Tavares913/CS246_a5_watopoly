#ifndef __TILE_PRINT_H__
#define __TILE_PRINT_H__

#include <vector>
#include <string>

using namespace std;

class TilePrint {
    string name;
    bool buildable;
    bool endTile;
    bool blank;
    bool blankAndBottom;
    bool blankAndSide;
    int improvements;
    vector<char> players;

    public:
        TilePrint(string name, bool buildable = false, bool endTile = false, bool blank = false, bool blankAndBottom = false, bool blankAndSide = false);
        string getRow(int row);
        void improve();
        void unimprove();
        void addPlayer(char p);
        void removePlayer(char p);
};

#endif