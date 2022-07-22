#ifndef __ACADEMIC_BUILDING_H__
#define __ACADEMIC_BUILDING_H__

#include "property.h"
#include <vector>

using namespace std;

class Player;

class AcademicBuilding : public Property {
  vector<int> tuition;
  int improvementCost;
  int numImprovements = 0;

 public:
  AcademicBuilding(string name, int purchaseCost, int improvementCost, vector<int> &tuition);
  int getTuition() const override;
  void mortgage() override;
  void buyImprovement();
  void sellImprovement();
  void visit(Player &player) override;
};

#endif