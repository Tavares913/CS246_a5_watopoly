#ifndef __GYM_H__
#define __GYM_H__

#include <string>
#include "property.h"
#include "gameboard.h"

class Gym : public Property {
  public:
    Gym(int location, std::string name, int purchaseCost, PropertyBlock block);
    int getTuition() const override;
};

#endif
