#include <string>
#include <vector>
#include "dc_tims_line.h"
#include "gameboard.h"

DCTimsLine::DCTimsLine(int location) : NonProperty{"DC Tims Line", location} {}

void DCTimsLine::visit(Player &p) {
    string c;
    if (p.rollUpRimCards > 0) {
        c = GameBoard::getChoice(
            "Would you like to use a Roll Up The Rim card?",
            vector{"Y", "N"}
        );
        if (c == "Y") {
            p.useRollUpRimCard();
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

    pair<int, int> roll = GameBoard::roll() // TODO make roll return a pair instead
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
            p.useRollUpRimCard();
        }
    }
}