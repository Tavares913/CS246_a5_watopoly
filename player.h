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
  int location = 0;
  float money = 1500;
  vector<Property *> ownedProperties;
  int rollUpRimCards = 0;
  bool inTimsLine = false;
  int numTurnsInTimsLine = 0;
 public:
  Player(string name, char symbol);
  void move(int moveBy);
  // TODO move trade to gameboard; call give/receive Property/Money as appropriate
  void giveProperty(Property *property);
  void receiveProperty(Property *property);
  void spendMoney(float amount);
  void receiveMoney(float amount);
  void buyImprovement(AcademicBuilding *property);
  void sellImprovement(AcademicBuilding *property);
  void mortgage(Property *property);
  void unmortgage(Property *property);
  void assets(); // TODO move to display class
  void buyProperty(Property *property);
  void payRent(Property *property);
  void goToTimsLine();
  void leaveTimsLine();
  void receiveRollUpRimCard();
  void updateNumTurnsInTimsLine();
  void useRollUpRimCard();
  float getWorth();
  // misc thought - what if we used references everywhere instead of pointers?
  void visit(Property &property);
  void visit(GooseNesting &gooseNesting);
  void visit(GoToTims &goToTims);
  void visit(CollectOSAP &collectOSAP);
  void visit(DCTimsLine &dcTimsLine);
  void visit(CoopFee &coopFee);
  void visit(Tuition &tuition);
  void visit(NeedlesHall &needlesHall);
  void visit(SLC &slc);
};
