#include "coop_fee.h";

int CoopFee::payment = 150;

CoopFee::CoopFee(int location) : NonProperty{location} {}

void CoopFee::visit(Player &p) {
    p.setMoney(p.getMoney - payment);
}