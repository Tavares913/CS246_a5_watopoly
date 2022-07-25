#ifndef __SLC_H__
#define __SLC_H__

#include "non_property.h"

class CollectOSAP;
class Player;

class SLC : public NonProperty {
    CollectOSAP *osap;

  public:
    SLC(int location, CollectOSAP *osap);
    void visit(Player &p);
};

#endif