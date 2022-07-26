#include <string>
#include <vector>
#include "property.h"
#include "player.h"
#include "error.h"

using namespace std;

Property::Property(int location, string name, int purchaseCost) :
    Tile{location, name}, purchaseCost{purchaseCost} {}

void Property::mortgage() { mortgaged = true; }

void Property::unmortgage() { mortgaged = false; }

void Property::setOwner(Player *owner) { this->owner = owner; }

Player *Property::getOwner() const { return owner; }

void Property::setPropertyBlock(const vector<Property *> &propertyBlock) {
    this->propertyBlock = propertyBlock;
}

int Property::getNumOwned() const {
    if (!owner) return 0;

    int numOwned = 0;
    for (auto property : propertyBlock) {
        if (property->owner == owner) ++numOwned;
    }

    return numOwned;
}

int Property::getNumImprovements() const { return mortgaged ? -1 : numImprovements; }

bool Property::monopoly() const { return getNumOwned() == propertyBlock.size(); }

int Property::getPurchaseCost() const { return purchaseCost; }

void Property::buyImprovement() { throw CannotImproveError{}; }

void Property::sellImprovement() { throw CannotImproveError{}; }

int Property::getImprovementCost() const { throw CannotImproveError{}; }

void Property::visit(Player &p) {
    if (owner) {
      int tuition = getTuition();
      p.payPlayer(tuition, *owner);
      return;
    }

    p.offerProperty(*this);
}

bool Property::tradeable() const {
    if (monopoly()) {
        for (auto otherProperty : propertyBlock) {
            if (otherProperty->getNumImprovements() > 0) return false;
        }
    }
    return !mortgaged;
}
