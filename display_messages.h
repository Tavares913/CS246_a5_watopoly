#ifndef DISPLAY_MESSAGES_H
#define DISPLAY_MESSAGES_H

struct PlayerMove {
    int oldTile;
    int newTile;
    char who;
};

struct Improvement {
    int tile;
};

struct Unimprovement {
    int tile;
};

#endif
