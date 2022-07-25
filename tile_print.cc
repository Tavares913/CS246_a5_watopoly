#include "tile_print.h"
#include <sstream>

using namespace std;

TilePrint::TilePrint(string name, bool buildable, bool endTile, bool blank) : name{name}, buildable{buildable}, endTile{endTile}, blank{blank}, improvements{0}, players{} {}

string empty() { return "       "; }

string alignLeft(string s, int rowNum, int rowSize) {
    string output = "";
    string line1 = "";
    string line2 = "";

    istringstream iss{s};
    iss >> line1;
    iss >> line2;

    if (line1.size() + line2.size() <= rowSize) {
        line1 += " " + line2;
        line2 = "";
        iss >> line2;
    }

    int l1size = rowSize - line1.size();
    int l2size = rowSize - line2.size();
    for (int i = 0; i < l1size; ++i) {
        line1 += " ";
    }
    for (int i = 0; i < l2size; ++i) {
        line2 += " ";
    }

    if (rowNum == 1) {
        return line1;
    } else {
        return line2;
    }
}

string TilePrint::getRow(int row) {
    if (blank) {
        return empty();
    }

    string retval = "|";
    if (row == 1) {
        retval += "________";
    } else if (row == 2) {
        if (buildable) {
            for (int i = 0; i < improvements; ++i) {
                retval += "I";
            }
        } else {
            if (name.size() > 7) {
                retval += alignLeft(name, 1, 7);
            }
        }
    } else if (row == 3) {
        if (buildable) {
            retval += "-------";
        } else {
            if (name.size() > 7) {
                retval += alignLeft(name, 2, 7);
            }
        }
    } else if (row == 4) {
        if (buildable) {
            retval += name;
        } else {
            retval += empty();
        }
    } else if (row == 5) {
        retval += empty();
    } else if (row == 6) {
        for (auto &p : players) {
            retval += p;
        }
        for (int i = 0; i < 7 - players.size(); ++i) {
            retval += " ";
        }
    } else if (row == 7) {
        retval += "_______";
    }

    if (endTile) {
        retval += "|";
    }

    return retval;
}

void TilePrint::improve() {
    ++improvements;
}

void TilePrint::unimprove() {
    --improvements;
}

void TilePrint::addPlayer(char p) {
    players.emplace_back(p);
}

void TilePrint::removePlayer(char p) {
    for (int i = 0; i < players.size(); ++i) {
        if (p == players[i]) {
            players.erase(players.begin() + i);
            break;
        }
    }
}