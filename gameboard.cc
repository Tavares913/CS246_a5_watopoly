#include "gameboard.h"
#include "tile.h"
#include "auction.h"
#include <vector>
#include <cstdlib>
#include <string>

using namespace std;

GameBoard::GameBoard(vector<Player *> players, vector<Tile **> board) : players{players}, board{board} {}


void GameBoard::next() {
    if (curPlayer == players.size() - 1) {
        curPlayer = 0;
    } else {
        ++curPlayer;
    }
}

void GameBoard::roll() {
    int die1 = rand() % 6 + 1;
    int die2 = rand() % 6 + 1;

    players[curPlayer]->move(die1 + die2);

    next();
}

void GameBoard::improve(Player &p, string propertyName) {
    for (auto &t : board) {
        if (*t->getName().compare(propertyName) == 0) {
            p.improve(t);
        }
    }
}

void GameBoard::deteriorate(Player &p, string propertyName) {
    for (auto &t : board) {
        if (*t->getName().compare(propertyName) == 0) {
            p.improve(t);
        }
    }
}

void GameBoard::all() {
    for (auto &p : players) {
        p->assets();
    }
}

void GameBoard::buyProperty(Player &p, string propertyName) {
    for (auto &p : boughtProperties) {
        if (p.getName().compare(propertyName) == 0) {
            return;
        }
    }

    for (auto &t : board) {
        if (*t->getName().compare(propertyName) == 0) {
            p.buy(t);
        }
    }
}

void GameBoard::mortgage(Player &p, string propertyName) {
    p.mortgage(propertyName);
}

void GameBoard::unmortgage(Player &p, string propertyName) {
    p.unmortgage(propertyName);
}

void GameBoard::auction(Property *p) {
    Auction a{players, p};
    a.auction();
}