#include <vector>
#include <iostream>
#include <string>
#include "auction.h"
#include "player.h"
#include "property.h"

using namespace std;

Auction::Auction(vector<Player *> &players, Property *property) :
    players{players}, property{property}, curPlayer{0}, propPrice{0} {}

void Auction::nextPlayer() {
    ++curPlayer;
    if (curPlayer == players.size()) curPlayer = 0;
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
            players.erase(players.begin() + curPlayer);
            --curPlayer;
            nextPlayer();
        }
    }

    players[0]->buyProperty(*property, propPrice);
}