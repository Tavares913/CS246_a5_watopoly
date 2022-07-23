#include "non_property.h"
#include "goose_nesting.h"

GooseNesting::GooseNesting(int location) : NonProperty{"Goose Nesting", location} {}

void GooseNesting::visit(Player &p) {}