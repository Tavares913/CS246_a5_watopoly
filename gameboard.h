#ifndef __GAMEBOARD_H__
#define __GAMEBOARD_H_
#include "subject.h"

class Player;
class Tile;
class Property;
class Display;

class GameBoard : public Subject {
    int curPlayer;
    vector<Player *> players;
    vector<Tile **> board;
    vector<Property **> boughtProperties;
    Display *display;

public:
    GameBoard(vector<Player *> players, vector<Tile **> board);
    void roll();
    void next();
    void improve(Player &p, string propertyName);
    void deteriorate(Player &p, string propertyName);
    void all();
    void buyProperty(Player &p, string propertyName);
    void mortgage(Player &p, string propertyName);
    void unmortgage(Player &p, string propertyName);
    void auction(Property *p);
};

#endif