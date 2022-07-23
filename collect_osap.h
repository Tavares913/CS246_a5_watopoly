#ifndef __COLLECT_OSAP_H__
#define __COLLECT_OSAP_H__

#include "non_property.h"

class CollectOSAP : public NonProperty {
    static int collectionAmount;

  public:
    CollectOSAP(int location);
    void visit(Player &p);
};

#endif