#ifndef __COLLECT_OSAP_H__
#define __COLLECT_OSAP_H__

#include "non_property.h"

class Player;

class CollectOSAP : public NonProperty {
    int collectionAmount;

  public:
    CollectOSAP(int location, int collectionAmount);
    void visit(Player &p);
};

#endif