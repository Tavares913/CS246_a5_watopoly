#ifndef __GYM_H__
#define __GYM_H__

#include "property.h"
#include "player.h"
#include <string>

using namespace std;

class Gym : public Property {
 public:
     Gym(string name, int purchaseCost);
     int getTuition() const override;
     void visit(Player &player);
};


#endif