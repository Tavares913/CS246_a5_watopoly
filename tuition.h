#ifndef __TUITION_H__
#define __TUITION_H__
#include "non_property.h"

class Tuition : public NonProperty {
    static int payment;
    static float rate;

public:
    Tuition(int location);
    void visit(Player &p, bool flatPayment = true);
};

#endif