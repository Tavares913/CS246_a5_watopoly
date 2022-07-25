#ifndef __GAMEBOARD_H__
#define __GAMEBOARD_H__

#include <memory>
#include <vector>
#include <unordered_map>
#include <string>
#include <utility>
#include "subject.h"
#include "player.h"
#include "tile.h"
#include "display.h"

class Property;
class DCTimsLine;
class Watopoly;

class GameBoard : public Subject {
    int curPlayer = 0;
    std::vector<std::unique_ptr<Player>> players;
    std::vector<std::unique_ptr<Tile>> board;
    std::unordered_map<std::string, Property *> nameToProperties;
    std::unique_ptr<Display> display;
    DCTimsLine *dcTimsLine;
    bool testing;

    void initBoard();

  public:
    GameBoard();
    static std::pair<int, int> roll();
    static std::string &getChoice(
        const std::string &message, const std::vector<std::string> &validChoices
    );
    void moveCurPlayer();
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