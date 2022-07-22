#ifndef __GAMEBOARD_H__
#define __GAMEBOARD_H__
#include "subject.h"
#include <memory>
#include <unordered_map>

class Player;
class Tile;
class Property;
class Display;

class GameBoard : public Subject {
    int curPlayer;
    vector<unique_ptr<Player>> players;
    vector<unique_ptr<Tile>> board;
    unordered_map<string, Property *> nameToProperties;
    unique_ptr<Display> display;

public:
    GameBoard(vector<unique_ptr<Player>> players, vector<unique_ptr<Tile>> board);
    static void roll();
    void moveCurPlayer();
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