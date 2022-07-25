#ifndef __DISPLAY_H__
#define __DISPLAY_H__

#include <vector>
#include "tile_print.h"
#include "display_messages.h"

struct PlayerMove;
struct Improvement;
struct Unimprovement;

using namespace std;

class Display {
    vector<vector<TilePrint>> display;

    public:
        Display();
        void print();
        void notify(PlayerMove p);
        void notify(Improvement i);
        void notify(Unimprovement u);
};

#endif