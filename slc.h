#ifndef __SLC_H__
#define __SLC_H__
#include "non_property.h"

class DCTimsLine;
class CollectOSAP;

class SLC : public NonProperty {
    DCTimsLine *dc;
    CollectOSAP *osap;

public:
    SLC(int location, DCTimsLine *dc, CollectOSAP *osap);
    void visit(Player &p);
};

#endif