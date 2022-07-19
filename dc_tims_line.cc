#include "dc_tims_line.h"

DCTimsLine::DCTimsLine(int location) : NonProperty{"DC Tims Line", location} {}

void DCTimsLine::visit(Player &p) {
    p.setJailed(true);
}