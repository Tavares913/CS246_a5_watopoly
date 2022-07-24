#ifndef __COOP_FEE_H__
#define __COOP_FEE_H__

#include "non_property.h"

class Player;

class CoopFee : public NonProperty {
    int payment;

  public:
    CoopFee(int location, int payment);
    void visit(Player &p);
};

#endif