#include "property.h"

class Player;

class Gym : public Property {
 public:
  Gym(string name, int purchaseCost) : name{name}, purchaseCost{purchaseCost} {}
  int getTuition() const override {
    switch (getNumOwned()) {
      case 1:
        return GameBoard::roll() * 4;
      case 2:
        return GameBoard::roll() * 10;
      default:
        throw; // idk, this should not be possible
    }
  }
  void visit(Player &player);
};
