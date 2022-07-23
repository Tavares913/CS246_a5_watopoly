#include "collect_osap.h"
#include "non_property.h"

int CollectOSAP::collectionAmount = 200;

CollectOSAP::CollectOSAP(int location) : NonProperty{"Collect OSAP", location} {}

void CollectOSAP::visit(Player &p) {
    p.receiveMoney(collectionAmount);
}