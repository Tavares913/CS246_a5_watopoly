#ifndef __PLAYER_H__
#define __PLAYER_H__

#include <vector>
#include <string>

class Tile;
class Property;
class Watopoly;

class Player {
    static int totalTimsCups;
    std::string name;
    char symbol;
    int location;
    float money;
    std::vector<Property *> ownedProperties;
    int timsCups;
    bool inTimsLine;
    int numTurnsInTimsLine;

  public:
    Player(
        std::string name, char symbol, float money = 1500, int location = 0,
        int timsCups = 0, bool inTimsLine = false, int numTurnsInTimsLine = 0
    );
    std::string getName() const;
    char getSymbol() const;
    bool isInTimsLine() const;
    bool moveBy(int moveBy);
    int getLocation() const;
    void spendMoney(float amount, bool check = false);
    void receiveMoney(float amount);
    void offerProperty(Property &property);
    void giveProperty(Property &property);
    void receiveProperty(Property &property);
    void buyProperty(Property &property, int purchaseCost = 0);
    void buyImprovement(Property &property);
    void sellImprovement(Property &property);
    void mortgage(Property &property);
    void unmortgage(Property &property);
    void assets();
    void incrementNumTurnsInLine();
    int getNumTurnsInLine();
    void goToTimsLine();
    bool leaveTimsLine();
    void receiveTimsCup();
    void updateNumTurnsInTimsLine();
    void useTimsCup(bool check = false);
    float getWorth();
    void visit(Tile &tile);
    void bankrupt(Player &payee = nullptr);

    friend class Watopoly;
};

#endif