#include "coop_fee.h";
#include "non_property.h"

CoopFee::CoopFee(int location, int payment) : NonProperty{location, "Coop Fee"}, payment{payment} {}

void CoopFee::visit(Player &p) {
    p.spendMoney(payment);
}