#include "tuition.h"

int Tuition::payment = 300;
float Tuition::rate = 0.3;

Tuition::Tuition(int location) : NonProperty{location, "Tuition"} {}

void Tuition::visit(Player &p, bool flatPayment) {
    if (flatPayment) p.spendMoney(payment);
    else p.spendMoney(p.getWorth() * rate);
}