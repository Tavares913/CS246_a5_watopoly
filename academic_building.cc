#include "property.h"

class Player;

class AcademicBuilding: public Property {
  int improvementCost;
  int numImprovements;
 public:
  AcademicBuilding(
    string name, int purchaseCost, int improvementCost,
    vector<Property *> propertyBlock
  ) : name{name}, purchaseCost{purchaseCost}, improvementCost{improvementCost},
    propertyBlock{propertyBlock}, ownedBy{nullptr}, numImprovements{0} {}
  bool blockMonopoly() const override {
    for (auto property : propertyBlock) {
      if (property->ownedBy != ownedBy) return false;
    }
    return true;
  }
  int getTuition() const override {
    if (numImprovements == 0 && blockMonopoly()) return 2 * tuition[numImprovements];
    return tuition[numImprovements];
  }
  void improve() { if (blockMonopoly()) ++numImprovements; }
  void visit(Player &player) override;
};
