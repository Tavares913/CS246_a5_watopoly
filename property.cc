#include <string>
#include <vector>
#include "player.h"

Property::Property(int location, string name, int purchaseCost) :
    Tile{location, name}, purchaseCost{purchaseCost} {}

void Property::mortgage() { mortgaged = true; }

void Property::unmortgage() { mortgaged = false; }

void Property::setOwner(const Player *owner) { this->owner = owner; }

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

void Property::buyImprovement() { throw; /* cannot improve error */ }

void Property::sellImprovement() { throw; /* cannot 'un'improve error */ }

void Property::visit(Player &player) {
    if (owner) {
      int tuition = getTuition();
      p.payPlayer(tuition, *owner);
      return;
    }

    p.offerProperty(*this);
}
