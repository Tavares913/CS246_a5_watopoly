#include <vector>
#include <iostream>
#include <algorithm>
#include <memory>
#include <string>
#include "auction.h"
#include "player.h"
#include "property.h"
#include "display.h"
#include "error.h"

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

void Auction::removePlayer(Player *player) {
    players.erase(find(players.begin(), players.end(), player));
}

void Auction::setProperty(Property *property) { this->property = property; }

void Auction::auction(int curPlayerIdx) {
    curPlayer = curPlayerIdx;
    propPrice = 1;
    withdrawnPlayers.clear();
    string cmd;

    while (true) {
        if (withdrawnPlayers.size() == players.size() - 1) break;
        
        if (propPrice > 0) cout << "Winning Bid: " << propPrice << endl;

        int amountToRaise = 0;
        cout << "Player " << players[curPlayer]->getName() << ": Would you like to raise or withdraw? ";
        if (!(cin >> cmd)) continue;
        if (cmd == "raise") {
            try {
                cin >> amountToRaise;
                if (cin.fail()) {
                    cin.clear();
                    throw NonNumericRaiseAmountError{};
                }
                if (amountToRaise == 0) throw NegativeRaiseAmountError{};
                try { players[curPlayer]->spendMoney(propPrice + amountToRaise, true); }
                catch (NotEnoughMoneyError e) { throw TooHighRaiseAmountError{}; }
                propPrice += amountToRaise;
            } catch (Error &e) {
                Display::printMessage(e.getMessage());
                continue;
            }
        } else if (cmd == "withdraw") {
            withdrawnPlayers.emplace_back(curPlayer);
        }
        nextPlayer();
    }
    cout << property->getName() << " sold to player " << curWinner().getName() << " for $" << propPrice << "." << endl;
    curWinner().buyProperty(*property, propPrice);
}
