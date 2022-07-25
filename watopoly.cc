#include <iostream>
#include <fstream>
#include <vector>
#include <memory>
#include <string>
#include "watopoly.h"
#include "collect_osap.h"
#include "academic_building.h"
#include "slc.h"
#include "player.h"
#include "gameboard.h"
#include "dc_tims_line.h"

using namespace std;

Watopoly::Watopoly(string loadfile, bool testing) : testing{testing} {
    if (loadfile != "") load(loadfile);
    else initPlayers();
}

string Watopoly::getChoice(const string &message, const vector<string> &validChoices) {
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

void Watopoly::initPlayers() {
    int numPlayers;
    string curPlayerName;
    char curPlayerSymbol;

    cin >> numPlayers;
    for (int i = 0; i < numPlayers; ++i) {
        cin >> curPlayerName;
        cin >> curPlayerSymbol;

        gameboard.players.emplace_back(
            make_unique<Player>(curPlayerName, curPlayerSymbol)
        );
    }
}

void Watopoly::load(string filename) {
    ifstream file{filename};

    // players
    int numPlayers;
    string playerName;
    char playerSymbol;
    float money;
    int location;
    int timsCups;
    bool inTimsLine;
    int numTurnsInTimsLine;

    cin >> numPlayers;
    for (int i = 0; i < numPlayers; ++i) {
        cin >> playerName;
        cin >> playerSymbol;
        cin >> timsCups;
        cin >> money;
        cin >> location;

        inTimsLine = false;
        numTurnsInTimsLine = 0;
        if (location == gameboard.dcTimsLine->getLocation()) {
            cin >> inTimsLine;
            if (inTimsLine) cin >> numTurnsInTimsLine;
        }

        gameboard.players.emplace_back(
            make_unique<Player>(
                playerName, playerSymbol, money, location, timsCups, inTimsLine, numTurnsInTimsLine
            )
        );
    }

    // properties
    string propertyName;
    string ownerName;
    int numImprovements;

    for (int i = 0; i < gameboard.nameToProperties.size(); ++i) {
        cin >> propertyName;
        cin >> ownerName;
        cin >> numImprovements;

        Property *property = gameboard.nameToProperties[propertyName];
        for (auto &player : gameboard.players) {
            if (player->name == ownerName) {
                property->owner = player.get();
                player->ownedProperties.emplace_back(property);
                break;
            }
            if (numImprovements == -1) property->mortgaged = true;
            else property->numImprovements = numImprovements;
        }
    }

    file.close();
}

void Watopoly::save(string filename) {
    ofstream file{filename};
    
    // number of players
    int numPlayers = gameboard.players.size();
    file << numPlayers << endl;
    // players
    for (int i = 0; i < numPlayers; ++i) {
        int playerIndex = (i + gameboard.curPlayer) % numPlayers;
        Player &player = *gameboard.players[playerIndex];
        file << player.name << " " << player.symbol << " " << player.timsCups
            << " " << player.money << " " << player.location;
        if (player.location ==  gameboard.dcTimsLine->getLocation()) {
            file << " " << static_cast<int>(player.inTimsLine);
            if (player.inTimsLine) file << " " << player.numTurnsInTimsLine;
        }
        file << endl;
    }

    // properties
    for (auto &tile : gameboard.board) {
        try {
            Property *property = gameboard.nameToProperties.at(tile->getName());
            file << property->getName() << " "
                << property->getOwner()->name << " "
                << property->getNumImprovements() << endl;
        } catch (...) {}
    }

    file.close();
}

void Watopoly::play() {
    string cmd;

    while (cin >> cmd) {
        if (cmd == "roll") {

        } else if (cmd == "next") {

        } else if (cmd == "trade") {

        } else if (cmd == "improve") {

        } else if (cmd == "mortgage") {

        } else if (cmd == "unmortgage") {

        } else if (cmd == "bankrupt") {

        } else if (cmd == "assets") {

        } else if (cmd == "all") {

        } else if (cmd == "save") {

        } else {
            cout << "Invalid command - please try again." << endl;
        }
    }
}
