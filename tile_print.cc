#include "tile_print.h"
#include <sstream>
#include <iostream>

using namespace std;

TilePrint::TilePrint(string name, bool buildable, bool endTile, bool blank, bool blankAndBottom, bool blankAndSide) : name{name}, buildable{buildable}, endTile{endTile}, blank{blank}, blankAndBottom{blankAndBottom}, blankAndSide{blankAndSide}, improvements{0}, players{} {}

string empty(int num) {
    string retval = "";
    for (int i = 0; i < num; ++i) {
        retval += " ";
    }
    return retval;
}

string alignLeft(string s, int rowNum, int rowSize) {
    string output = "";
    string word1 = "";
    string word2 = "";
    string word3 = "";
    vector<string> line1;
    vector<string> line2;

    istringstream iss{s};
    iss >> word1;
    iss >> word2;
    iss >> word3;

    line1.emplace_back(word1);
    if (word1.size() + word2.size() <= rowSize - 1) {
        line1.emplace_back(word2);
        if (word3.size() > 0) line2.emplace_back(word3);
    } else {
        line2.emplace_back(word2);
        if (word3.size() > 0) line2.emplace_back(word3);
    }

    if (rowNum == 1) {
        for (auto &s : line1) {
            output += s;
            output += " ";
        }
        output = output.substr(0, output.size() - 1);
        int padding = rowSize - output.size();
        for (int i = 0; i < padding; ++i) {
            output += " ";
        }
    } else {
        for (auto &s : line2) {
            output += s;
            output += " ";
        }
        output = output.substr(0, output.size() - 1);
        int padding = rowSize - output.size();
        for (int i = 0; i < padding; ++i) {
            output += " ";
        }
    }

    return output;
}

string TilePrint::getRow(int row) {
    if (blank && blankAndBottom && !blankAndSide && row == 7) {
        return "_______";
    } else if (blank && blankAndBottom && blankAndSide && row == 7) {
        return "_______________";
    } else if (blank && blankAndSide) {
        return empty(7);
    } else if (blank){
        return empty(8);
    }

    string retval = "|";
    if (row == 1) {
        return "________";
    } else if (row == 2) {
        if (buildable) {
            for (int i = 0; i < improvements; ++i) {
                retval += "I";
            }
            for (int i = 0; i < 7 - improvements; ++i) {
                retval += " ";
            }
        } else {
            retval += alignLeft(name, 1, 7);
        }
    } else if (row == 3) {
        if (buildable) {
            retval += "-------";
        } else {
            retval += alignLeft(name, 2, 7);
        }
    } else if (row == 4) {
        if (buildable) {
            retval += alignLeft(name, 1, 7);
        } else {
            retval += empty(7);
        }
    } else if (row == 5) {
        retval += empty(7);
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
