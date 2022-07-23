#include "auction.h"
#include "player.h"
#include "property.h"
#include <vector>
#include <iostream>
#include <string>

using namespace std;

Auction::Auction(vector<Player *> &players, Property *property) :
    players{players}, property{property}, curPlayer{0}, propPrice{0} {}

void Auction::nextPlayer() {
    if (curPlayer == players.size()) {
        curPlayer = 0;
    } else {
        ++curPlayer;
    }
}

void Auction::auction() {
    string cmd;

    while (true) {
        if (players.size() == 1) {
            break;
        }

        int amountToRaise = 0;
        cin >> cmd;
        if (cmd == "raise") {
            cin >> amountToRaise;
            propPrice += amountToRaise;
            nextPlayer();
        } else if (cmd == "withdraw") {
            players.erase(curPlayer);
            nextPlayer();
        }
    }

    players[0]->buyProperty(*property, propPrice);
}