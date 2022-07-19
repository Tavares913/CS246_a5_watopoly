#include "tuition.h"

int Tuition::payment = 300;
float Tuition::rate = 0.3;

Tuition::Tuition(int location) : NonProperty{"Tuition", location} {}

void Tuition::visit(Player &p, bool flatPayment) {
    if (flatPayment) {
        p.setMoney(p.getMoney - payment);
    } else {
        p.setMoney(p.getMoney() * rate);
    }
}