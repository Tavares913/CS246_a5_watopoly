#include <vector>
#include "property.h"
#include "player.h"
#include "academic_building.h"

using namespace std;

AcademicBuilding::AcademicBuilding(
  int location, string name, int purchaseCost, int improvementCost, const vector<int> &tuition
) : Property{location, name, purchaseCost}, improvementCost{improvementCost}, tuition{tuition} {}

int AcademicBuilding::getTuition() const {
  if (numImprovements == 0 && monopoly()) {
    return 2 * tuition[numImprovements];
  }
  return tuition[numImprovements];
}

void AcademicBuilding::mortgage() {
  if (numImprovements > 0) throw; // remove improvements before mortgage error
  Property::mortgage();
}

void AcademicBuilding::buyImprovement() { 
  if (!monopoly()) throw; // no monopoly error
  if (numImprovements == tuition.size() - 1) throw; // cant improve more error
  ++numImprovements;
}

void AcademicBuilding::sellImprovement() {
  if (numImprovements == 0) throw; // cant deteriorate further error
  --numImprovements;
}

int AcademicBuilding::getImprovementCost() const { return improvementCost; }
