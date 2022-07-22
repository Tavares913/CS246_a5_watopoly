#include "property.h"

class Player;

class AcademicBuilding : public Property {
  vector<int> tuition;
  int improvementCost;
  int numImprovements = 0;
 public:
  AcademicBuilding(
    string name, int purchaseCost, int improvementCost, vector<int> &tuition
  ) : name{name}, purchaseCost{purchaseCost}, improvementCost{improvementCost},
    tuition{tuition} {}
  int getTuition() const override {
    if (numImprovements == 0 && monopoly() ) {
      return 2 * tuition[numImprovements];
    }
    return tuition[numImprovements];
  }
  void mortgage() override {
    if (numImprovements > 0) throw; // remove improvements before mortgage error
    Property::mortgage();
  }
  void buyImprovement() { 
    if (!monopoly()) throw; // no monopoly error
    if (numImprovements == tuition.size() - 1) throw; // cant improve more error
    ++numImprovements;
  }
  void sellImprovement() {
    if (numImprovements == 0) throw; // cant deteriorate further error
    --numImprovements;
  }
  void visit(Player &player) override;
};
