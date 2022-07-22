#include <vector>
#include "property.h"

class Residence;
class Gym;
class GooseNesting;
class GoToTims;
class CollectOSAP;
class DCTimsLine;
class CoopFee;
class Tuition;
class NeedlesHall;
class SLC;

Player::Player(string name, char symbol) : name{name}, symbol{symbol} {}
// TODO move trade to gameboard; call give/receive Property/Money as appropriate
void Player::move(int moveBy) { location += moveBy; }
void Player::giveProperty(Property *property) {
  for (auto it = ownedProperties.begin(); it != ownedProperties.end(); ++it) {
    if (*it == property) {
      ownedProperties.erase(it);
      break;
    }
  }
  property->setOwner(nullptr);
}
void Player::receiveProperty(Property *property) {
  ownedProperties.push_back(property);
  property->setOwner(this);
}
void Player::spendMoney(float amount) { 
  if (amount > money) throw; // not enough money error
  money -= amount;
}
void Player::receiveMoney(float amount) { spendMoney(-amount); }
void Player::buyImprovement(AcademicBuilding *property) {
  spendMoney(property->improvementCost);
  property->buyImprovement();
}
void Player::sellImprovement(AcademicBuilding **property) {
  receiveMoney(property->improvementCost * 0.5);
  property->sellImprovement();
}
void mortgage(Property *property) {
  receiveMoney(property->purchaseCost * 0.5);
  property->mortgage();
}
void Player::unmortgage(Property *property) {
  spendMoney(property->purchaseCost * 0.6)
  property->unmortgage();
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
void Player::buyProperty(Property *property) {
  spendMoney(property->purchaseCost);
  receiveProperty(property);
}
void Player::payRent(Property *property)
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
    while (true) {
      cout << "Purchase property? (Y/N) ";
      char c;
      cin >> c;
      switch (c) {
        case 'Y':
          buyProperty(property);
          break;
        case 'N':
          // start auction
          break;
        default:
          cout << "Invalid choice, please try again." << endl;
          continue;
      }
      break;
  }
}
void Player::visit(GooseNesting &gooseNesting) {}
void Player::visit(GoToTims &goToTims) {
  goToTimsLine();
}
void Player::visit(CollectOSAP &collectOSAP) {
  receiveMoney(200);
}
void Player::visit(DCTimsLine &dcTimsLine) {
  if (rollUpRimCards > 0) {
    while (true) {
        cout << "Would you like to use a Roll Up The Rim card? (Y/N) ";
        char c;
        cin >> c;
        switch (c) {
          case 'Y':
            useRollUpRimCard();
            return;
          case 'N':
            break;
          default:
            cout << "Invalid choice, please try again." << endl;
            continue;
        }
        break;
    }
  }

  while (true) {
    cout << "Would you like to pay $50 to leave the Tim's line? (Y/N) ";
    char c;
    cin >> c;
    switch (c) {
      case 'Y':
        spendMoney(50);
        leaveTimsLine();
        return;
      case 'N':
        break;
      default:
        cout << "Invalid choice, please try again." << endl;
        continue;
    }
    break;
  }

  pair<int, int> roll = GameBoard::roll() // TODO make roll return a pair instead
  if (roll.first == roll.second) {
    // doubles!
    leaveTimsLine();
    return;
  }

  ++numTurnsInTimsLine;
  if (numTurnsInTimsLine == 3) {
    while (true) {
      cout << "Would you like to pay $50 or use a Roll Up The Rim card? (pay/card) ";
      string s;
      cin >> s;
      switch (c) {
        case "pay":
          spendMoney(50);
          leaveTimsLine();
          return;
        case "card":
          useRollUpRimCard();
          return;
        default:
          cout << "Invalid choice, please try again." << endl;
      }
    }
  }
}
void Player::visit(CoopFee &coopFee) {
  spendMoney(150);
}
void Player::visit(Tuition &tuition) {
  tuition.visit(*this);
}
void Player::visit(NeedlesHall &needlesHall) {
  needlesHall.visit(*this);
}
void Player::visit(SLC &slc) {
  slc.visit(*this);
}
};
