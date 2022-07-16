#ifndef __COLLECT_OSAP_H__
#define __COLLECT_OSAP_H_
#include "non_property.h"

class CollectOSAP : public NonProperty {
    static int collectionAmount = 200;

public:
    CollectOSAP();
    void visit(Player &p);
};

#endif