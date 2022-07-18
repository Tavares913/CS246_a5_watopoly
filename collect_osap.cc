#include "collect_osap.h"

int CollectOSAP::collectionAmount = 200;

CollectOSAP::CollectOSAP(int location) : NonProperty{location} {}

void CollectOSAP::visit(Player &p) {
    p.setFunds(p.getFunds() + collectionAmount);
}