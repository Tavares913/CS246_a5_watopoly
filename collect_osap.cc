#include "collect_osap.h"

int CollectOSAP::collectionAmount = 200;

CollectOSAP::CollectOSAP(int location) : NonProperty{"Collect OSAP", location} {}

void CollectOSAP::visit(Player &p) {
    p.setFunds(p.getFunds() + collectionAmount);
}