#include "gym.h"
#include "property.h"
#include "gameboard.h"
#include <utility>
#include <string>

using namespace std;

Gym::Gym(string name, int purchaseCost) : Property{name, purchaseCost} {}

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
void visit(Player &player) {}
