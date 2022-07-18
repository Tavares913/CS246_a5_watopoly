#ifndef __NEEDLES_HALL_H__
#define __NEEDLES_HALL_H__
#include "non_property.h"

class NeedlesHall : public NonProperty {

public:
    NeedlesHall(int location);
    void visit(Player &p);
};

#endif