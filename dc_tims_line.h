#ifndef __DC_TIMS_LINE_H__
#define __DC_TIMS_LINE_H_
#include "non_property.h"

class DCTimsLine : public NonProperty {
    public:
        DCTimsLine(int location);
        void visit(Player &p);
};

#endif