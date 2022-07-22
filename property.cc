#include "player.h"
#include <string>
#include <vector>

Property::Property(string name, int purchaseCost) : name{name}, purchaseCost{purchaseCost}, owner{}, propertyBlock{}, mortgaged{false} {}

void Property::mortgage() { mortgaged = true; }

void Property::unmortgage() { mortgaged = false; }

void Property::setOwner(const Player *owner) { owner = owner; }

Player *Property::getOwner() const { return owner; }

void Property::setPropertyBlock(const vector<Property *> &propertyBlock) { propertyBlock = propertyBlock; }

int Property::getNumOwned() const {
    if (!owner) return 0;

    int numOwned = 0;
    for (auto property : propertyBlock) {
        if (property->owner == owner) ++numOwned;
    }

    return numOwned;
}

bool Property::monopoly() const { return getNumOwned() == propertyBlock.size(); }