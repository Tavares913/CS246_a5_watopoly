#include "property.h"

class Player;

class Residence : public Property {
  int tuition;
 public:
  Residence(string name, int purchaseCost, int tuition)
    : name{name}, purchaseCost{purchaseCost}, tuition{tuition} {}
  int getTuition() const override {
    return tuition * (2 ** getNumOwned());
  }
  void visit(Player &player);
};
