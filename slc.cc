#include <cstdlib>
#include "slc.h"
#include "player.h"
#include "dc_tims_line.h"
#include "collect_osap.h"

using namespace std;

SLC::SLC(int location, CollectOSAP *osap) : NonProperty{location, "SLC"}, osap{osap} {}

void SLC::visit(Player &p) {
    int timsCupChance = rand() % 100;
    if (timsCupChance == 0) {
        p.receiveTimsCup();
    }

    int randNum = rand() % 24;
    bool collectOsap = false;
    if (randNum < 3) {
        collectOsap = p.moveBy(-3);
    } else if (randNum < 7) {
        collectOsap = p.moveBy(-2);
    } else if (randNum < 11) {
        collectOsap = p.moveBy(-1);
    } else if (randNum < 14) {
        collectOsap = p.moveBy(1);
    } else if (randNum < 18) {
        collectOsap = p.moveBy(2);
    } else if (randNum < 22) {
        collectOsap = p.moveBy(3);
    } else if (randNum < 23) {
        p.goToTimsLine();
    } else if (randNum < 24) {
        collectOsap = true;
    }
    if (collectOsap) p.visit(*osap);
}
