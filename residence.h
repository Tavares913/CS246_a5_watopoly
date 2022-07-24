#ifndef __RESIDENCE_H__
#define __RESIDENCE_H__

#include "property.h"

class Player;

class Residence : public Property {
    int tuition;

  public:
    Residence(int location, string name, int purchaseCost, int tuition);
    int getTuition() const override;
};


#endif