#include "collect_osap.h"
#include "non_property.h"
#include "player.h"

CollectOSAP::CollectOSAP(int location, int collectionAmount) :
    NonProperty{location, "Collect OSAP"}, collectionAmount{collectionAmount} {}

void CollectOSAP::visit(Player &p) {
    p.receiveMoney(collectionAmount);
}