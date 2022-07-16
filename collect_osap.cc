#include "collect_osap.h"

CollectOSAP::CollectOSAP(int location) : NonProperty{location} {}

void CollectOSAP::visit(Player &p) {
    p.setFunds(p.getFunds() + collectionAmount);
}