#ifndef __PLAYER_H__
#define __PLAYER_H__

#include <vector>
#include "watopoly.h"

class Tile;
// class Residence;
// class Gym;
// class GooseNesting;
// class GoToTims;
// class CollectOSAP;
// class DCTimsLine;
// class CoopFee;
// class Tuition;
// class NeedlesHall;
// class SLC;

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
    void move(int moveBy);
    void spendMoney(float amount);
    void receiveMoney(float amount);
    void payPlayer(float amount, Player &payee);
    // TODO move trade to gameboard; call give/receive Property/Money as appropriate
    void offerProperty(Property &property);
    void giveProperty(Property &property);
    void receiveProperty(Property &property);
    void buyProperty(Property &property, int purchaseCost = 0);
    void buyImprovement(AcademicBuilding &property);
    void sellImprovement(AcademicBuilding &property);
    void mortgage(Property &property);
    void unmortgage(Property &property);
    void assets(); // TODO move to display class
    void goToTimsLine();
    void leaveTimsLine();
    void receiveTimsCup();
    void updateNumTurnsInTimsLine();
    void useTimsCup();
    float getWorth();
    // misc thought - what if we used references everywhere instead of pointers?
    void visit(Tile &tile);
    // void visit(Property &property);
    // void visit(GooseNesting &gooseNesting);
    // void visit(GoToTims &goToTims);
    // void visit(CollectOSAP &collectOSAP);
    // void visit(DCTimsLine &dcTimsLine);
    // void visit(CoopFee &coopFee);
    // void visit(Tuition &tuition);
    // void visit(NeedlesHall &needlesHall);
    // void visit(SLC &slc);
    friend class Watopoly;
};

#endif