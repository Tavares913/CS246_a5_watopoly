#include "go_to_tims.h"
#include "non_property.h"
#include "player.h"
#include "dc_tims_line.h"

GoToTims::GoToTims(int location) : NonProperty{location, "Go to Tims"} {}

void GoToTims::visit(Player &p) {
    p.goToTimsLine();
}
