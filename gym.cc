#include "property.h"

class Player;

class Gym: public Property {
 public:
  Gym(string name, int purchaseCost, int tuition, vector<Property *> propertyBlock)
    : name{name}, purchaseCost{purchaseCost}, propertyBlock{propertyBlock}, ownedBy{nullptr} {
    this->tuition[0] = tuition;
  }
  void visit(Player &player);
};
