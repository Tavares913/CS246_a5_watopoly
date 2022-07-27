#ifndef __RESIDENCE_H__
#define __RESIDENCE_H__

#include <string>
#include "property.h"
#include "gameboard.h"

class Residence : public Property {
    int tuition;

  public:
    Residence(int location, std::string name, int purchaseCost, PropertyBlock block, int tuition);
    int getTuition() const override;
};


#endif
