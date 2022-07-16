#ifndef __GOOSE_NESTING_H__
#define __GOOSE_NESTING_H__
#include "non_property.h"

class GooseNesting : public NonProperty {
    public:
        GooseNesting(int location);
        void visit(Player &p);
};

#endif