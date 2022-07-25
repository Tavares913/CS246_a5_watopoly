#include <cstdlib>
#include "slc.h"
#include "player.h"
#include "dc_tims_line.h"
#include "collect_osap.h"

using namespace std;

SLC::SLC(int location, DCTimsLine *dc, CollectOSAP *osap) : NonProperty{location, "SLC"}, dc{dc}, osap{osap} {}

void SLC::visit(Player &p) {
    int timsCupChance = rand() % 100;
    if (timsCupChance == 0) {
        p.receiveTimsCup();
    }

    int randNum = rand() % 24;
    if (randNum < 3) {
        p.move(-3);
    } else if (randNum < 7) {
        p.move(-2);
    } else if (randNum < 11) {
        p.move(-1);
    } else if (randNum < 14) {
        p.move(1);
    } else if (randNum < 18) {
        p.move(2);
    } else if (randNum < 22) {
        p.move(3);
    } else if (randNum < 23) {
        p.visit(dc);
    } else if (randNum < 24) {
        p.visit(osap);
    }
}