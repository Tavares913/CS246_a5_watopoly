#include <string>
#include <vector>
#include "property.h"
#include "player.h"
#include "gameboard.h"
#include "error.h"

using namespace std;

Property::Property(int location, string name, int purchaseCost, PropertyBlock block) :
    Tile{location, name}, purchaseCost{purchaseCost}, block{block} {}

void Property::mortgage() { mortgaged = true; }

void Property::unmortgage() { mortgaged = false; }

void Property::setOwner(Player *owner) { this->owner = owner; }

Player *Property::getOwner() const { return owner; }

int Property::getNumOwned() const {
    if (!owner) return 0;

    int numOwned = 0;
    for (auto property : GameBoard::propertyBlocks[block]) {
        if (property->owner == owner) ++numOwned;
    }

    return numOwned;
}

int Property::getNumImprovements() const { return mortgaged ? -1 : numImprovements; }

bool Property::monopoly() const { return getNumOwned() == GameBoard::propertyBlocks[block].size(); }

int Property::getPurchaseCost() const { return purchaseCost; }

void Property::buyImprovement() { throw CannotImproveError{}; }

void Property::sellImprovement() { throw CannotImproveError{}; }

int Property::getImprovementCost() const { throw CannotImproveError{}; }

void Property::visit(Player &p) {
    if (owner == &p) return;
    if (owner) {
        try {
            int tuition = getTuition();
            p.spendMoney(tuition);
            if (!mortgaged) owner->receiveMoney(tuition);
            return;
        } catch (NotEnoughMoneyError &e) {
            throw NotEnoughMoneyError{&p, e.getAmount(), owner};
        }
    }

    p.offerProperty(*this);
}

bool Property::tradeable() const {
    if (mortgaged) throw MortgagedPropertyError{};
    if (monopoly()) {
        for (auto otherProperty : GameBoard::propertyBlocks[block]) {
            if (otherProperty->getNumImprovements() > 0) {
                throw PropertyWithImprovementsError{};
            }
        }
    }
    return true;
}
