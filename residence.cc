#include "property.h"
#include "player.h"

Residence::Residence(string name, int location, int purchaseCost, int tuition) :
  Property{location, name, purchaseCost}, tuition{tuition} {}

int Residence::getTuition() const {
  return tuition * (2 ** getNumOwned());
}
