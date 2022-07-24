#ifndef __RESIDENCE_H__
#define __RESIDENCE_H__

#include <string>
#include "property.h"

class Residence : public Property {
    int tuition;

  public:
    Residence(int location, std::string name, int purchaseCost, int tuition);
    int getTuition() const override;
};


#endif