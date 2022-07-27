#include <string>
#include "tuition.h"
#include "watopoly.h"

using namespace std;

Tuition::Tuition(int location, int payment, float rate) :
    NonProperty{location, "Tuition"}, payment{payment}, rate{rate} {}

void Tuition::visit(Player &p) {
    string c = Watopoly::getChoice(
        "Would you like to pay $" + to_string(payment) + " or " + to_string(rate * 100) + "\% of your worth?",
        vector<string>{"fee", "worth"}
    );
    if (c == "fee") p.spendMoney(payment);
    else p.spendMoney(p.getWorth() * rate);
}
