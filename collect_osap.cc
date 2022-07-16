#include "collect_osap.h"

CollectOSAP::CollectOSAP() {}

void CollectOSAP::visit(Player &p) {
    p.setFunds(p.getFunds() + collectionAmount);
}