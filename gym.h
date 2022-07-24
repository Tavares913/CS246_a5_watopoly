#ifndef __GYM_H__
#define __GYM_H__

#include <string>
#include "property.h"
#include "player.h"

using namespace std;

class Gym : public Property {
  public:
    Gym(int location, string name, int purchaseCost);
    int getTuition() const override;
};

#endif