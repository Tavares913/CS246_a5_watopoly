#include <vector>
#include <iostream>
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
    cout << property->getName() << " sold to player " << players[0]->getName() << " for $" << propPrice << "." << endl;
    players[0]->buyProperty(*property, propPrice);
}