#ifndef __DC_TIMS_LINE_H__
#define __DC_TIMS_LINE_H__

#include "non_property.h"

class Player;

class DCTimsLine : public NonProperty {
    int priceOfCoffee = 50;
  
  public:
    DCTimsLine(int location);
    void visit(Player &p);
};

#endif
