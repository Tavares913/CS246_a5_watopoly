#ifndef __GO_TO_TIMS_H__
#define __GO_TO_TIMS_H__
#include "non_property.h"

class DCTimsLine;

class GoToTims : public NonProperty {
    DCTimsLine *dcTimsLine;

public:
    GoToTims(int location, DCTimsLine *dcTimsLine);
    void visit(Player &p);
};

#endif