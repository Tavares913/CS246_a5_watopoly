#ifndef __PROPERTY_H__
#define __PROPERTY_H__

#include <string>
#include <vector>
#include "tile.h"

class Player;
class Watopoly;

class Property : public Tile {
    std::string name;
    int purchaseCost;
    Player *owner = nullptr;
    std::vector<Property *> propertyBlock;
    bool mortgaged = false;

  protected:
    int numImprovements = 0;

  public:
    Property(int location, std::string name, int purchaseCost);
    virtual int getTuition() const = 0;
    virtual void mortgage();
    void unmortgage();
    void setOwner(const Player *owner);
    Player *getOwner() const;
    void setPropertyBlock(const std::vector<Property *> &propertyBlock);
    int getNumOwned() const;
    int getNumImprovements() const;
    bool monopoly() const;
    virtual void buyImprovement();
    virtual void sellImprovement();
    virtual int getImprovementCost();
    void visit(Player &player);

    friend class Watopoly;
};

#endif