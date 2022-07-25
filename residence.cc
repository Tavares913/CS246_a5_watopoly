#include <string>
#include <cmath>
#include "residence.h"
#include "property.h"
#include "player.h"

using namespace std;

Residence::Residence(int location, string name, int purchaseCost, int tuition) :
  Property{location, name, purchaseCost}, tuition{tuition} {}

int Residence::getTuition() const {
  return tuition * pow(2, getNumOwned());
}
