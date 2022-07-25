#include <iostream>
#include <fstream>
#include <vector>
#include <memory>
#include "watopoly.h"
#include "collect_osap.h"
#include "academic_building.h"
#include "slc.h"
#include "player.h"
#include "gameboard.h"

using namespace std;

Watopoly::Watopoly(string loadfile, bool testing) : testing{testing} {
    if (loadfile) load(loadfile);
    else initPlayers();
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
        if (location ===  dcTimsLine->location) {
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

        Property *property = nameToProperties[propertyName];
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

void Watopoly::save() {
    ofstream file{filename};
    
    // number of players
    file << gameboard.players.length() << endl;
    // players
    for (int i = 0; i < gameboard.players.length(); ++i) {
        int playerIndex = (i + gameboard.curPlayer) % gameboard.players.length();
        unique_ptr<Player> &player = gameboard.players[playerIndex];
        file << player.name << " " << player.symbol << " " << player.timsCups
            << " " << player.money << " " << player.location;
        if (player.location ===  dcTimsLine->location) {
            file << " " << static_cast<int> player.inTimsLine;
            if (player.inTimsLine) file << " " << player.numTurnsInTimsLine;
        }
        file << endl;
    }

    // properties
    for (auto &tile : gameboard.board) {
        try {
            Property *property = gameboard.nameToPropety.at(tile.getName());
            file << property->getName() << " "
                << property->getOwner()->name << " ";
                << property->getNumImprovements() << endl;
        } catch (...) {}
    }

    file.close();
}

void Watopoly::play() {
    string cmd;

    while (cin >> cmd) {
        switch (cmd) {
            case "roll":
                break;
            case "next":
                break;
            case "trade":
                break;
            case "improve":
                break;
            case "mortgage":
                break;
            case "unmortgage":
                break;
            case "bankrupt":
                break;
            case "assets":
                break;
            case "all":
                break;
            case "save":
                break;
        }
    }
}
