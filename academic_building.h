#ifndef __ACADEMIC_BUILDING_H__
#define __ACADEMIC_BUILDING_H__

#include <vector>
#include <string>
#include "property.h"

class AcademicBuilding : public Property {
    int improvementCost;
    std::vector<int> tuition;

  public:
    AcademicBuilding(
        int location, std::string name, int purchaseCost, int improvementCost, const std::vector<int> &tuition
    );
    int getTuition() const override;
    void mortgage() override;
    void buyImprovement() override;
    void sellImprovement() override;
    int getImprovementCost() const override;
};

#endif