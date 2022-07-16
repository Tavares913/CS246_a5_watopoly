#include "go_to_tims.h"

GoToTims::GoToTims(int location, DCTimsLine *dcTimsLine) : NonProperty{location}, dcTimsLine{dcTimsLine} {}

void GoToTims::visit(Player &p) {
    p.visit(dcTimsLine);
}