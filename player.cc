#include <iostream>
#include <vector>
#include "property.h"
#include "watopoly.h"
#include "gameboard.h"

using namespace std;

Player::Player(
    string name, char symbol, float money, int location, int timsCups,
    bool inTimsLine, int numTurnsInTimsLine
) : name{name}, symbol{symbol}, location{location}, money{money}, timsCups{timsCups},
    inTimsLine{inTimsLine}, numTurnsInTimsLine{numTurnsInTimsLine} {}

void Player::move(int moveBy) {
    location += moveBy;
    location %= GameBoard::NUM_TILES;
}

int Player::getLocation() const { return location; }

void Player::spendMoney(float amount) { 
    if (amount > money) throw; // not enough money error
    money -= amount;
}

void Player::receiveMoney(float amount) { spendMoney(-amount); }

void Player::payPlayer(float amount, Player &payee) {
    spendMoney(amount);
    payee.receiveMoney(amount);
}

void Player::offerProperty(Property &property) {
    string c = Watopoly::getChoice(
        "Would you like to buy this property?",
        vector<string>{"y", "n"}
    );
    if (c == "y") {
        buyProperty(property);
    } else {
        // TODO start auction
    }
}

void Player::giveProperty(Property &property) {
    ownedProperties.erase(find(ownedProperties.begin(), ownedProperties.end(), &property));
    property.setOwner(nullptr);
}

void Player::receiveProperty(Property &property) {
    ownedProperties.push_back(&property);
    property.setOwner(this);
}

void Player::buyProperty(Property &property, int purchaseCost) {
    spendMoney(purchaseCost ? purchaseCost : property.getPurchaseCost());
    receiveProperty(property);
}

void Player::buyImprovement(Property &property) {
    property.buyImprovement();
    spendMoney(property.getImprovementCost());
}

void Player::sellImprovement(Property &property) {
    property.sellImprovement();
    receiveMoney(property.getImprovementCost() * 0.5);
}

void Player::mortgage(Property &property) {
    receiveMoney(property.getPurchaseCost() * 0.5);
    property.mortgage();
}

void Player::unmortgage(Property &property) {
    spendMoney(property.getPurchaseCost() * 0.6);
    property.unmortgage();
}

void Player::assets() {
    cout << name << "'s assets:" << endl;
    cout << "Money: " << money << endl;
    cout << "Properties Owned: " << endl;
    for (auto &property : ownedProperties) {
        cout << property->getName() << " ";
        cout << property->getPurchaseCost() << " ";
        for (int i = 0; i < property->getNumImprovements(); ++i) cout << "I";
        cout << endl;
    }
}

int Player::getTimsCups() { return timsCups; }

void Player::incrementNumTurnsInLine() { ++numTurnsInTimsLine; }

int Player::getNumTurnsInLine() { return numTurnsInTimsLine; }

void Player::goToTimsLine() {
    inTimsLine = true;
    numTurnsInTimsLine = 0;
}

void Player::leaveTimsLine() {
    inTimsLine = false;
    numTurnsInTimsLine = 0;
}

void Player::receiveTimsCup() { ++timsCups; }

void Player::updateNumTurnsInTimsLine() { ++numTurnsInTimsLine; }

void Player::useTimsCup() {
    if (timsCups == 0) throw; // not enough cards error
    --timsCups; 
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

void Player::visit(Tile *tile) {
    tile->visit(*this);
}
