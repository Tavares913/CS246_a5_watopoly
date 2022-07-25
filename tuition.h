#ifndef __TUITION_H__
#define __TUITION_H__

#include "non_property.h"

class Player;

class Tuition : public NonProperty {
    int payment;
    float rate;

  public:
    Tuition(int location, int payment, float rate);
    void visit(Player &p);
};

#endif