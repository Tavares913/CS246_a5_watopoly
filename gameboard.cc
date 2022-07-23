#include <vector>
#include <cstdlib>
#include <string>
#include <utility>
#include "gameboard.h"
#include "tile.h"
#include "auction.h"
#include "player.h"

using namespace std;

GameBoard::GameBoard(vector<unique_ptr<Player> &players, vector<unique_ptr<Tile> &board) :
    curPlayer{0}, players{players}, board{board} {}


static pair<int, int> GameBoard::roll() {
    int die1 = rand() % 6 + 1;
    int die2 = rand() % 6 + 1;
    return pair<int, int> rollResult(die1, die2);
}

static string &GameBoard::getChoice(const string &message, const vector<string> &validChoices) const {
    while (true) {
        cout << message << " ";
        cout << "(";
        bool addDelimiter = false;
        for (auto &choice : validChoices) {
            if (addDelimiter) cout << "/";
            cout << choice;
            addDelimiter = true;
        }
        cout << ") ";
        string c;
        cin >> c;
        if (find(validChoices.begin(), validChoices.end(), c) != validChoices.end()) {
            return c;
        }
        cout << "Invalid choice, please try again." << endl;
    }
}

void GameBoard::moveCurPlayer() {
    pair<int, int> roll = roll();
    // TODO check for doubles, etc
    players[curPlayer]->move(roll.first + roll.second);
    next();
}

void GameBoard::next() {
    if (curPlayer == players.size() - 1) {
        curPlayer = 0;
    } else {
        ++curPlayer;
    }
}

void GameBoard::buyImprovement(Player &p, string propertyName) {
    p.buyImprovement(*nameToProperties[propertyName]);
}

void GameBoard::sellImprovement(Player &p, string propertyName) {
    p.sellImprovement(*nameToProperties[propertyName]);
}

void GameBoard::allAssets() {
    for (auto &p : players) {
        p->assets();
    }
}

void GameBoard::buyProperty(Player &p, string propertyName) {
    if (!nameToProperties[propertyName]->getOwner()) {
        p.buyProperty(*nameToProperties[propertyName]);
    }
}

void GameBoard::mortgage(Player &p, string propertyName) {
    p.mortgage(*nameToProperties[propertyName]);
}

void GameBoard::unmortgage(Player &p, string propertyName) {
    p.unmortgage(*nameToProperties[propertyName]);
}

void GameBoard::auction(Property *p) {
    Auction a{players, p};
    a.auction();
}