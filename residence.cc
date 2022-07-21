#include "property.h"

class Player;

class Residence: public Property {
 public:
  Residence(
    string name, int purchaseCost, vector<Property *> propertyBlock, int tuition
  ) : name{name}, purchaseCost{purchaseCost}, propertyBlock{propertyBlock},
    ownedBy{nullptr} {
    this->tuition[0] = tuition;
  }
  int getNumOwned() const {
    int numOwned = 0;
    for (auto property : propertyBlock) {
      if (property->ownedBy == ownedBy) ++numOwned;
    }
    return numOwned;
  }
  int getTuition() override {
    int numOwned = getNumOwned();
    return tuition[0] * (2 ** numOwned);
  }
  void visit(Player &player);
};
