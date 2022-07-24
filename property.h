#ifndef __PROPERTY_H__
#define __PROPERTY_H__

#include <string>
#include <vector>
#include "tile.h"
#include "watopoly.h"

class Player;

class Property : public Tile {
    std::string name;
    int purchaseCost;
    Player *owner = nullptr;
    std::vector<Property *> propertyBlock;
    bool mortgaged = false;
    int numImprovements = 0;

  public:
    Property(int location, std::string name, int purchaseCost);
    virtual int getTuition() const = 0;
    virtual void mortgage();
    void visit(Player &player);
    void unmortgage();
    void setOwner(const Player *owner);
    Player *getOwner() const;
    void setPropertyBlock(const std::vector<Property *> &propertyBlock);
    int getNumOwned() const;
    int getNumImprovements() const;
    bool monopoly() const;
    virtual void buyImprovement();
    virtual void sellImprovement();
    void visit(Player &player);

    friend class Watopoly;
};

#endif