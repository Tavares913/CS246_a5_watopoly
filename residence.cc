#include <string>
#include <cmath>
#include "residence.h"
#include "property.h"
#include "player.h"
#include "gameboard.h"

using namespace std;

Residence::Residence(int location, string name, int purchaseCost, PropertyBlock block, int tuition) :
  Property{location, name, purchaseCost, block}, tuition{tuition} {}

int Residence::getTuition() const {
  return tuition * pow(2, getNumOwned());
}
