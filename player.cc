#include <vector>
#include "property.h"

Player::Player(
    string name, char symbol, float money, int location, int timsCups,
    bool inTimsLine, int numTurnsInTimsLine
) : name{name}, symbol{symbol}, money{money}, location{location}, timsCups{timsCups},
    inTimsLine{inTimsLine}, numTurnsInTimsLine{numTurnsInTimsLine} {}

void Player::move(int moveBy) { location += moveBy; }

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
    string c = GameBoard::getChoice(
        "Would you like to buy this property?",
        vector{"y", "n"}
    );
    if (c == "y") {
        buyProperty(property);
    } else {
        // TODO start auction
    }
}

void Player::giveProperty(Property &property) {
    ownedProperties.erase(find(ownedProperties.begin(), ownedProperties.end()));
    property.setOwner(nullptr);
}

void Player::receiveProperty(Property &property) {
    ownedProperties.push_back(&property);
    property.setOwner(this);
}

void Player::buyProperty(Property &property, int purchaseCost) {
    spendMoney(purchaseCost ? purchaseCost : property.purchaseCost);
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
    receiveMoney(property.purchaseCost * 0.5);
    property.mortgage();
}

void Player::unmortgage(Property &property) {
    spendMoney(property.purchaseCost * 0.6)
    property.unmortgage();
}

void Player::assets() {
    cout << name << "'s assets:" << endl;
    cout << "Money: " << money << endl;
    cout << "Properties Owned: " << endl;
    for (auto &property : ownedProperties) {
        cout << property.name << " ";
        cout << property.purchaseAmount << " ";
        for (int i = 0; i < property.numImprovements; ++i) cout << "I";
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
        worth += property.purchaseCost;
        worth += (property.improvementCost * property.numImprovements);
    }
    return worth;
}

void Player::visit(Tile &tile) {
    tile.visit(*this);
}
