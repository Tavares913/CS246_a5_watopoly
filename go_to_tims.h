#ifndef __GO_TO_TIMS_H__
#define __GO_TO_TIMS_H__

#include "non_property.h"

class Player;

class GoToTims : public NonProperty {
  public:
    GoToTims(int location);
    void visit(Player &p);
};

#endif
