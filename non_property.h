#ifndef __NON_PROPERTY_H__
#define __NON_PROPERTY_H__

#include <string>
#include "tile.h"

class NonProperty : public Tile {
  public:
    NonProperty(int location, std::string name);
};

#endif