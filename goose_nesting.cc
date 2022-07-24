#include "non_property.h"
#include "goose_nesting.h"

GooseNesting::GooseNesting(int location) : NonProperty{location, "Goose Nesting"} {}

void GooseNesting::visit(Player &p) {}