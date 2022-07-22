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

class Player {
  string name;
  char symbol;
  float money = 1500;
  vector<Property *> ownedProperties;
  int rollUpRimCards = 0;
  bool inTimsLine = false;
  int numTurnsInTimsLine = 0;
 public:
  Player(string name, char symbol) : name{name}, symbol{symbol} {}
  // TODO move trade to gameboard; call give/receive Property/Money as appropriate
  void giveProperty(Property *property) {
    for (auto it = ownedProperties.begin(); it != ownedProperties.end(); ++it) {
      if (*it == property) {
        ownedProperties.erase(it);
        break;
      }
    }
    property->setOwner(nullptr);
  }
  void receiveProperty(Property *property) {
    ownedProperties.push_back(property);
    property->setOwner(this);
  }
  void spendMoney(float amount) { 
    if (amount > money) throw; // not enough money error
    money -= amount;
  }
  void receiveMoney(float amount) { spendMoney(-amount); }
  void buyImprovement(AcademicBuilding *property) {
    spendMoney(property->improvementCost);
    property->buyImprovement();
  }
  void sellImprovement(AcademicBuilding **property) {
    receiveMoney(property->improvementCost * 0.5);
    property->sellImprovement();
  }
  void mortgage(Property *property) {
    receiveMoney(property->purchaseCost * 0.5);
    property->mortgage();
  }
  void unmortgage(Property *property) {
    spendMoney(property->purchaseCost * 0.6)
    property->unmortgage();
  }
  void assets() {
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
  void buyProperty(Property *property) {
    spendMoney(property->purchaseCost);
    receiveProperty(property);
  }
  void payRent(Property *property)
  void goToTimsLine() { inTimsLine = true; numTurnsInTimsLine = 0; }
  void leaveTimsLine() { inTimsLine = false; }
  void receiveRollUpRimCard() { ++rollUpRimCards; }
  void updateNumTurnsInTimsLine() { ++numTurnsInTimsLine; }
  void useRollUpRimCard() {
    if (rollUpRimCards == 0) throw; // not enough cards error
    --rollUpRimCards; 
    leaveTimsLine();
  }
  float getWorth() {
    float worth = money;
    for (auto &property : ownedProperties) {
      worth += property.purchaseCost;
      worth += (property.improvementCost * property.numImprovements);
    }
    return worth;
  }
  // misc thought - what if we used references everywhere instead of pointers?
  void visit(Property &property) {
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
  void visit(GooseNesting &gooseNesting) {}
  void visit(GoToTims &goToTims) {
    goToTimsLine();
  }
  void visit(CollectOSAP &collectOSAP) {
    receiveMoney(200);
  }
  void visit(DCTimsLine &dcTimsLine) {
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
  void visit(CoopFee &coopFee) {
    spendMoney(150);
  }
  void visit(Tuition &tuition) {
    while (true) {
      cout << "Do you wish to pay $300 or 10% of your total? ($300/10%) ";
      string s;
      cin >> s;
      switch (s) {
        case "$300":
          spendMoney(300);
          return;
        case "10%":
          spendMoney(0.1 * getWorth());
          return;
        default:
          cout << "Invalid choice, please try again." << endl;
      }
    }
  }
  void visit(NeedlesHall &needlesHall) {
    needlesHall.visit(*this);
  }
  void visit(SLC &slc) {
    slc.visit(*this);
  }
};
