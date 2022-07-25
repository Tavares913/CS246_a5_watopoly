#include "go_to_tims.h"
#include "non_property.h"
#include "player.h"
#include "dc_tims_line.h"

GoToTims::GoToTims(int location, DCTimsLine *dcTimsLine) :
    NonProperty{location, "Go to Tims"}, dcTimsLine{dcTimsLine} {}

void GoToTims::visit(Player &p) {
    dcTimsLine->visit(p);
}