#include "go_to_tims.h"
#include "non_property.h"
#include "player.h"
#include "dc_tims_line.h"

GoToTims::GoToTims(int location, DCTimsLine *dcTimsLine) :
    NonProperty{"Go to Tims", location}, dcTimsLine{dcTimsLine} {}

void GoToTims::visit(Player &p) {
    p.visit(*dcTimsLine);
}