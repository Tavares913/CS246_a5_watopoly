#ifndef __GAMEBOARD_H__
#define __GAMEBOARD_H__

#include <memory>
#include <vector>
#include <unordered_map>
#include <string>
#include "subject.h"
#include "player.h"
#include "tile.h"
#include "display.h"

class Property;
class Watopoly;

class GameBoard : public Subject {
    int curPlayer = 0;
    std::vector<std::unique_ptr<Player>> players;
    std::vector<std::unique_ptr<Tile>> board;
    std::unordered_map<std::string, Property *> nameToProperties;
    std::unique_ptr<Display> display;
    bool testing;

    void initBoard();

  public:
    static const int NUM_TILES = 40;
    static const int DC_TIMS_LOCATION = 10;

    GameBoard();
    Player &getCurPlayer() const;
    void moveCurPlayer(int moveBy);
    void next();
    void buyImprovement(Player &p, std::string propertyName);
    void sellImprovement(Player &p, std::string propertyName);
    void allAssets();
    void buyProperty(Player &p, std::string propertyName);
    void mortgage(Player &p, std::string propertyName);
    void unmortgage(Player &p, std::string propertyName);
    void auction(Property *p);

    friend class Watopoly;
};

#endif