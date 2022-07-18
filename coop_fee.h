#ifndef __COOP_FEE_H__
#define __COOP_FEE_H__
#include "non_property.h"

class CoopFee : public NonProperty {
    static int payment;

public:
    CoopFee(int location);
    void visit(Player &p);
};

#endif