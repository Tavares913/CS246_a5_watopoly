#include <vector>
#include "property.h"

Player::Player(string name, char symbol) : name{name}, symbol{symbol} {}

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

void Player::buyProperty(Property &property, int purchaseCost = 0) {
  spendMoney(purchaseCost ? purchaseCost : property.purchaseCost);
  receiveProperty(property);
}

void Player::buyImprovement(AcademicBuilding &property) {
  spendMoney(property.improvementCost);
  property.buyImprovement();
}

void Player::sellImprovement(AcademicBuilding &property) {
  receiveMoney(property.improvementCost * 0.5);
  property.sellImprovement();
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

void Player::goToTimsLine() {
  inTimsLine = true;
  numTurnsInTimsLine = 0;
}

void Player::leaveTimsLine() { inTimsLine = false; }

void Player::receiveRollUpRimCard() { ++rollUpRimCards; }

void Player::updateNumTurnsInTimsLine() { ++numTurnsInTimsLine; }

void Player::useRollUpRimCard() {
  if (rollUpRimCards == 0) throw; // not enough cards error
  --rollUpRimCards; 
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

// misc thought - what if we used references everywhere instead of pointers?
void Player::visit(Property &property) {
  if (building.ownedBy) {
    if (building.ownedBy != this) {
      // pay rent
      spendMoney(building.getTuition());
    }
  } else {
    // offer property for purchase
    // may should be in gameboard instead?
    
}

void Player::visit(NonProperty &nonProperty) {
  nonProperty.visit(*this);
}

// void Player::visit(GoToTims &goToTims) {
//   goToTims.visit(*this);
// }
// void Player::visit(CollectOSAP &collectOSAP) {
//   collectOSAP.visit(*this);
// }
// void Player::visit(Tuition &tuition) {
//   tuition.visit(*this);
// }
// void Player::visit(CoopFee &coopFee) {
//   coopFee.visit(*this);
// }
// void Player::visit(NeedlesHall &needlesHall) {
//   needlesHall.visit(*this);
// }
// void Player::visit(SLC &slc) {
//   slc.visit(*this);
// }
