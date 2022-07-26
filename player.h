#ifndef __PLAYER_H__
#define __PLAYER_H__

#include <vector>
#include <string>

class Tile;
class Property;
class Watopoly;

class Player {
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
    void moveBy(int moveBy);
    int getLocation() const;
    void spendMoney(float amount, bool check = false);
    void receiveMoney(float amount);
    void payPlayer(float amount, Player &payee);
    // TODO move trade to gameboard; call give/receive Property/Money as appropriate
    void offerProperty(Property &property);
    void giveProperty(Property &property);
    void receiveProperty(Property &property);
    void buyProperty(Property &property, int purchaseCost = 0);
    void buyImprovement(Property &property);
    void sellImprovement(Property &property);
    void mortgage(Property &property);
    void unmortgage(Property &property);
    void assets(); // TODO move to display class
    void incrementNumTurnsInLine();
    int getNumTurnsInLine();
    void goToTimsLine();
    bool leaveTimsLine();
    void receiveTimsCup();
    void updateNumTurnsInTimsLine();
    void useTimsCup(bool check = false);
    float getWorth();
    void visit(Tile *tile);

    friend class Watopoly;
};

#endif