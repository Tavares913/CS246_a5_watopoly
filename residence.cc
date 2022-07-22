#include "property.h"
#include "player.h"

class Residence : public Property {
  int tuition;

 public:
  Residence(string name, int purchaseCost, int tuition) : Property{name, purchaseCost}, tuition{tuition} {}

  int Residence::getTuition() const override {
    return tuition * (2 ** getNumOwned());
  }
};
