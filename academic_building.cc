#include <vector>
#include "property.h"
#include "player.h"
#include "academic_building.h"
#include "error.h"
#include "gameboard.h"

using namespace std;

AcademicBuilding::AcademicBuilding(
  int location, string name, int purchaseCost, PropertyBlock block, int improvementCost, const vector<int> &tuition
) : Property{location, name, purchaseCost, block}, improvementCost{improvementCost}, tuition{tuition} {}

int AcademicBuilding::getTuition() const {
  if (numImprovements == 0 && monopoly()) {
    return 2 * tuition[numImprovements];
  }
  return tuition[numImprovements];
}

void AcademicBuilding::mortgage() {
  if (numImprovements > 0) throw CannotMortgageWithImprovementsError{};
  Property::mortgage();
}

void AcademicBuilding::buyImprovement() { 
  if (!monopoly()) throw NoMonopolyError{};
  if (numImprovements == tuition.size() - 1) throw MaxImprovementsError{};
  ++numImprovements;
}

void AcademicBuilding::sellImprovement() {
  if (numImprovements == 0) throw MinImprovementsError{};
  --numImprovements;
}

int AcademicBuilding::getImprovementCost() const { return improvementCost; }
