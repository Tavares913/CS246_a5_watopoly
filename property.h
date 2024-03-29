#ifndef __PROPERTY_H__
#define __PROPERTY_H__

#include <string>
#include <vector>
#include "tile.h"
#include "gameboard.h"

class Player;
class Watopoly;

class Property : public Tile {
    std::string name;
    int purchaseCost;
    Player *owner = nullptr;
    PropertyBlock block;
    bool mortgaged = false;

  protected:
    int numImprovements = 0;

  public:
    Property(int location, std::string name, int purchaseCost, PropertyBlock block);
    virtual int getTuition() const = 0;
    virtual void mortgage();
    void unmortgage();
    void setOwner(Player *owner);
    Player *getOwner() const;
    int getNumOwned() const;
    int getNumImprovements() const;
    bool monopoly() const;
    int getPurchaseCost() const;
    virtual void buyImprovement();
    virtual void sellImprovement();
    virtual int getImprovementCost() const;
    void visit(Player &p);
    bool tradeable() const;

    friend class Watopoly;
};

#endif
