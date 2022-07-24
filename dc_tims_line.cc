#include <string>
#include <vector>
#include <utility>
#include "dc_tims_line.h"
#include "gameboard.h"
#include "non_property.h"
#include "player.h"

DCTimsLine::DCTimsLine(int location) : NonProperty{location, "DC Tims Line"} {}

void DCTimsLine::visit(Player &p) {
    string c;
    if (p.timsCups > 0) {
        c = GameBoard::getChoice(
            "Would you like to use a Roll Up The Rim card?",
            vector{"Y", "N"}
        );
        if (c == "Y") {
            p.useTimsCup();
            return;
        }
    }

    c = GameBoard::getChoice(
        "Would you like to pay $50 to leave the Tim's line?",
        vector{"Y", "N"}
    );
    if (c == "Y") {
        p.spendMoney(50);
        p.leaveTimsLine();
        return;
    }

    pair<int, int> roll = GameBoard::roll();
    if (roll.first == roll.second) {
        // doubles!
        p.leaveTimsLine();
        return;
    }

    ++p.numTurnsInTimsLine;
    if (p.numTurnsInTimsLine == 3) {
        c = GameBoard::getChoice(
            "Would you like to pay $50 or use a Roll Up The Rim card?",
            vector{"pay", "card"}
        );
        if (c == "pay") {
            p.spendMoney(50);
            p.leaveTimsLine();
        } else {
            p.useTimsCup();
        }
    }
}