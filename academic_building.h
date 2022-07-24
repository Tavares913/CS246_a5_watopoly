#ifndef __ACADEMIC_BUILDING_H__
#define __ACADEMIC_BUILDING_H__

#include <vector>
#include "property.h"

class Player;

class AcademicBuilding : public Property {
    vector<int> tuition;
    int improvementCost;

  public:
    AcademicBuilding(int location, string name, int purchaseCost, int improvementCost, vector<int> &tuition);
    int getTuition() const override;
    void mortgage() override;
    void buyImprovement() override;
    void sellImprovement() override;
};

#endif