#include <vector>
#include <iostream>
#include <memory>
#include <string>
#include "auction.h"
#include "player.h"
#include "property.h"

using namespace std;

void Auction::nextPlayer() {
    ++curPlayer;
    if (curPlayer == players.size()) curPlayer = 0;
}

void Auction::setPlayers(vector<unique_ptr<Player>> &players) {
    for (auto &player : players) {
        this->players.emplace_back(player.get());
    }
}

void Auction::setProperty(Property *property) { this->property = property; }

void Auction::auction() {
    curPlayer = 0;
    propPrice = 0;
    string cmd;

    while (true) {
        if (players.size() == 1) {
            break;
        }

        int amountToRaise = 0;
        cout << "Player " << players[0]->getName() << ": Would you like to raise or withdraw? ";
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
    cout << property->getName() << " sold to player " << players[0]->getName() << " for $" << propPrice << "." << endl;
    players[0]->buyProperty(*property, propPrice);
}