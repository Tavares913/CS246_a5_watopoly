#include <string>
#include <iostream>
#include <vector>
#include <utility>
#include "dc_tims_line.h"
#include "non_property.h"
#include "player.h"
#include "watopoly.h"
#include "error.h"

using namespace std;

DCTimsLine::DCTimsLine(int location) : NonProperty{location, "DC Tims Line"} {}

void DCTimsLine::visit(Player &p) {
    string c;
    if (p.getTimsCups() > 0) {
        c = Watopoly::getChoice(
            "Would you like to use a Roll Up The Rim cup?",
            vector<string>{"y", "n"}
        );
        if (c == "Y") {
            p.useTimsCup();
            return;
        }
    }
    if (p.getMoney() >= priceOfCoffee) {
        c = Watopoly::getChoice(
            "Would you like to pay $" + to_string(priceOfCoffee) + "to leave the Tim's line?",
            vector<string>{"y", "n"}
        );
        if (c == "Y") {
            p.spendMoney(priceOfCoffee);
            p.leaveTimsLine();
            return;
        }
    }

    p.incrementNumTurnsInLine();
    if (p.getNumTurnsInLine() == 3) {
        c = Watopoly::getChoice(
            "Would you like to pay $" + to_string(priceOfCoffee) + "or use a Roll Up The Rim cup?",
            vector<string>{"pay", "card"}
        );
        if (c == "pay") {
            p.spendMoney(priceOfCoffee);
            p.leaveTimsLine();
        } else {
            p.useTimsCup();
        }
    }
}