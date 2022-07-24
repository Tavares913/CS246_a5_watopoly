#include <utility>
#include <string>
#include "gym.h"
#include "property.h"
#include "gameboard.h"

using namespace std;

Gym::Gym(int location, string name, int purchaseCost) : Property{location, name, purchaseCost} {}

int Gym::getTuition() const {
  pair<int, int> roll = GameBoard::roll();

  switch (getNumOwned()) {
    case 1:
      return roll * 4;
    case 2:
      return roll * 10;
    default:
      throw; // idk, this should not be possible
  }
}
