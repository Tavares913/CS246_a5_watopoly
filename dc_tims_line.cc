#include "dc_tims_line.h"

DCTimsLine::DCTimsLine() {}

void DCTimsLine::visit(Player &p) {
    p.setJailed(true);
}