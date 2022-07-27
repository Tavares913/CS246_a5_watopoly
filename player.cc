#include <vector>
#include <iostream>
#include <algorithm>
#include "property.h"
#include "watopoly.h"
#include "gameboard.h"
#include "display.h"
#include "error.h"

using namespace std;

int Player::totalTimsCups = 0;

Player::Player(
    string name, char symbol, float money, int location, int timsCups,
    bool inTimsLine, int numTurnsInTimsLine
) : name{name}, symbol{symbol}, location{location}, money{money}, timsCups{timsCups},
    inTimsLine{inTimsLine}, numTurnsInTimsLine{numTurnsInTimsLine} {}

string Player::getName() const { return name; }

char Player::getSymbol() const { return symbol; }

bool Player::isInTimsLine() const { return inTimsLine; }

bool Player::moveBy(int moveBy) {
    if (!inTimsLine) {
        cout << "not in tims line" << endl;
        location += moveBy;
        if (location >= GameBoard::NUM_TILES) {
            location %= GameBoard::NUM_TILES;
            return true;
        }
        if (location < 0) location += GameBoard::NUM_TILES;
    }
    cout << "in tims line" << endl;
    return false;
}

int Player::getLocation() const { return location; }

void Player::spendMoney(float amount, bool check) { 
    if (amount > money) throw NotEnoughMoneyError{this, amount};
    if (check) return;
    money -= amount;
    Display::printMessage("Player " + name + " spends $" + to_string(amount));
}

void Player::receiveMoney(float amount) {
    money += amount;
    Display::printMessage("Player " + name + " receives $" + to_string(amount));
}

void Player::offerProperty(Property &property) {
    string c = Watopoly::getChoice(
        "Would you like to buy this property (" + property.getName() + ")?",
        vector<string>{"y", "n"}
    );
    if (c == "y") {
        buyProperty(property);
    } else {
        GameBoard::startAuction(&property);
    }
}

void Player::giveProperty(Property &property) {
    ownedProperties.erase(find(ownedProperties.begin(), ownedProperties.end(), &property));
    property.setOwner(nullptr);
}

void Player::receiveProperty(Property &property) {
    ownedProperties.push_back(&property);
    property.setOwner(this);
    Display::printMessage("Player " + name + " receives property " + property.getName());
    if (property.getNumImprovements() == -1) {
        string c = Watopoly::getChoice(
            "Would you like to unmortgage this property (" + property.getName() + ")?",
            vector<string>{"y", "n"}
        );
        if (c == "y") unmortgage(property);
        else spendMoney(0.1 * property.getPurchaseCost());
    }
}

void Player::buyProperty(Property &property, int purchaseCost) {
    spendMoney(purchaseCost ? purchaseCost : property.getPurchaseCost());
    receiveProperty(property);
}

void Player::buyImprovement(Property &property) {
    if (this != property.getOwner()) throw NotOwnerError{};
    property.buyImprovement();
    spendMoney(property.getImprovementCost());
}

void Player::sellImprovement(Property &property) {
    if (this != property.getOwner()) throw NotOwnerError{};
    property.sellImprovement();
    receiveMoney(property.getImprovementCost() * 0.5);
}

void Player::mortgage(Property &property) {
    if (this != property.getOwner()) throw NotOwnerError{};
    receiveMoney(property.getPurchaseCost() * 0.5);
    property.mortgage();
}

void Player::unmortgage(Property &property) {
    if (this != property.getOwner()) throw NotOwnerError{};
    spendMoney(property.getPurchaseCost() * 0.6);
    property.unmortgage();
}

void Player::assets() {
    // add a display assets method
    cout << endl;
    cout << "Player " << name << "'s assets:" << endl;
    cout << "Money: " << money << endl;
    cout << "Properties Owned: " << endl;
    for (auto &property : ownedProperties) {
        cout << "  " << property->getName() << endl;
        cout << "    " << "Price: " << property->getPurchaseCost() << endl;
        cout << "    " << "Number of Improvements: " << property->getNumImprovements() << endl; 
    }
    cout << endl;
}

void Player::incrementNumTurnsInLine() { if (numTurnsInTimsLine < 3) ++numTurnsInTimsLine; }

int Player::getNumTurnsInLine() { return numTurnsInTimsLine; }

void Player::goToTimsLine() {
    Display::printMessage("You rolled 3 doubles and have been sent to the back of the DC Tims Line!");
    location = GameBoard::DC_TIMS_LOCATION;
    inTimsLine = true;
    numTurnsInTimsLine = 0;
}

bool Player::leaveTimsLine() {
    if (inTimsLine) {
        inTimsLine = false;
        numTurnsInTimsLine = 0;
        Display::printMessage("Congrats! You get to leave the Tims line!");
        return true;
    }
    return false;
}

void Player::receiveTimsCup() {
    if (totalTimsCups == 4) return;
    ++totalTimsCups;
    ++timsCups;
    Display::printMessage("Player " + name + " receives a Tims Cup");
}

void Player::updateNumTurnsInTimsLine() { ++numTurnsInTimsLine; }

void Player::useTimsCup(bool check) {
    if (timsCups == 0) throw NotEnoughCupsError{};
    if (check) return;
    --timsCups; 
    --totalTimsCups;
    leaveTimsLine();
}

float Player::getWorth() {
    float worth = money;
    for (auto &property : ownedProperties) {
        worth += property->getPurchaseCost();
        worth += (property->getImprovementCost() * property->getNumImprovements());
    }
    return worth;
}

void Player::bankrupt(Player *payee) {
    if (payee) {
        payee->receiveMoney(money);
        for (int i = 0; i < timsCups; ++i) {
            --totalTimsCups;
            payee->receiveTimsCup();
        }
        NotEnoughMoneyError notEnoughMoney;
        for (auto &property : ownedProperties) {
            try {
                payee->receiveProperty(*property);
            } catch (NotEnoughMoneyError e) {
                Display::printMessage(e.getMessage());
                notEnoughMoney = NotEnoughMoneyError{this, notEnoughMoney.getAmount() + e.getAmount()};
            }
        }
        if (notEnoughMoney.owesMoney()) throw notEnoughMoney;
    } else {
        totalTimsCups -= timsCups;
        for (auto &property : ownedProperties) {
            giveProperty(*property);
            property->unmortgage();
            GameBoard::startAuction(property);
        }
    }
}

void Player::visit(Tile &tile) {
    tile.visit(*this);
}
