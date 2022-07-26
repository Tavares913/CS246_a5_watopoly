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
    if (find(withdrawnPlayers.begin(), withdrawnPlayers.end(), curPlayer) != withdrawnPlayers.end()) {
        nextPlayer();
    }
}

Player &Auction::curWinner() const {
    return *players[curPlayer];
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
    withdrawnPlayers.clear();
    string cmd;

    while (true) {
        if (withdrawnPlayers.size() == players.size() - 1) break;
        
        if (propPrice > 0) cout << "Current Winner: " << curWinner().getName() << ", Winning Bid: " << propPrice << endl;

        int amountToRaise = 0;
        cout << "Player " << players[curPlayer]->getName() << ": Would you like to raise or withdraw? ";
        cin >> cmd;
        if (cmd == "raise") {
            cin >> amountToRaise;
            if (cin.fail()) {
                cout << "Please enter a number." << endl;
                cin.clear();
                continue;
            }
            if (amountToRaise == 0) {
                cout << "Please raise by a positive amount." << endl;
                continue;
            }
            propPrice += amountToRaise;
        } else if (cmd == "withdraw") {
            withdrawnPlayers.emplace_back(curPlayer);
        }
        nextPlayer();
    }
    cout << property->getName() << " sold to player " << players[0]->getName() << " for $" << propPrice << "." << endl;
    players[0]->buyProperty(*property, propPrice);
}