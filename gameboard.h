#ifndef __GAMEBOARD_H__
#define __GAMEBOARD_H__

#include <memory>
#include <unordered_map>
#include <string>
#include <utility>
#include "subject.h"

class Player;
class Tile;
class Property;
class Display;

// TODO prefix stuff with std
class GameBoard : public Subject {
    int curPlayer;
    vector<unique_ptr<Player>> players;
    vector<unique_ptr<Tile>> board;
    unordered_map<string, Property *> nameToProperties;
    unique_ptr<Display> display;

  public:
    GameBoard(vector<unique_ptr<Player>> &players, vector<unique_ptr<Tile>> &board);
    static pair<int, int> roll();
    static string &getChoice(const string &message, const vector<string> &validChoices) const;
    void moveCurPlayer();
    void next();
    void buyImprovement(Player &p, string propertyName);
    void sellImprovement(Player &p, string propertyName);
    void allAssets();
    void buyProperty(Player &p, string propertyName);
    void mortgage(Player &p, string propertyName);
    void unmortgage(Player &p, string propertyName);
    void auction(Property *p);
};

#endif