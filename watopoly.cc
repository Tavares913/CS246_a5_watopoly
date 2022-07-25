#include <iostream>
#include <fstream>
#include <vector>
#include <unordered_map>
#include <memory>
#include <algorithm>
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

unordered_map<char, string> Watopoly::playerPieces = {
    {'G', "Goose"}, {'B', "GRT Bus"}, {'D', "Tim Hortons Doughnut"}, {'T', "Pink Tie"},
    {'P', "Professor"}, {'S', "Student"}, {'$', "Money"}, {'L', "Laptop"}
};

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

    cout << "How many players are playing? ";
    cin >> numPlayers;

    for (int i = 0; i < numPlayers; ++i) {
        while (true) {
            cout << "The following pieces are available to choose from: ";
            for (auto &piece : playerPieces) cout << piece.first << "  ";
            cout << endl;

            cout << "Player " << i + 1 << " - choose your piece: ";
            cin >> curPlayerSymbol;

            try {
                curPlayerName = playerPieces.at(curPlayerSymbol);
                playerPieces.erase(curPlayerSymbol);
                gameboard.players.emplace_back(
                    make_unique<Player>(curPlayerName, curPlayerSymbol)
                );
                break;
            } catch (...) {
                cout << "That piece is not available. Please try again." << endl;
            }
        }
    }
    gameboard.curPlayer = gameboard.players.begin();
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
        replace(playerName.begin(), playerName.end(), '_', ' ');
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
    gameboard.curPlayer = gameboard.players.begin();
    cout << "Loaded " << numPlayers << " players." << endl; 

    // properties
    string propertyName;
    string ownerName;
    int numImprovements;

    for (int i = 0; i < gameboard.nameToProperties.size(); ++i) {
        cin >> propertyName;
        cin >> ownerName;
        cin >> numImprovements;

        Property *property = gameboard.nameToProperties[propertyName];
        if (ownerName != "BANK") {
            for (auto &player : gameboard.players) {
                if (player->name == ownerName) {
                    property->owner = player.get();
                    player->ownedProperties.emplace_back(property);
                    break;
                }
            }
        }
        if (numImprovements == -1) property->mortgaged = true;
        else property->numImprovements = numImprovements;
    }

    file.close();

    cout << "Game load complete!" << endl;
}

void Watopoly::save(string filename) {
    ofstream file{filename};
    
    // number of players
    int numPlayers = gameboard.players.size();
    file << numPlayers << endl;
    // players
    for (int i = 0; i < numPlayers; ++i) {
        int playerIndex = (i + (gameboard.curPlayer - gameboard.players.begin())) % numPlayers;
        Player &player = *gameboard.players[playerIndex];
        string playerName{player.name};
        replace(playerName.begin(), playerName.end(), ' ', '_');
        file << playerName << " " << player.symbol << " " << player.timsCups
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
            string owner = property->getOwner() ? property->getOwner()->name : "BANK";
            file << property->getName() << " " << owner << " " << property->getNumImprovements() << endl;
        } catch (...) {}
    }

    file.close();
    cout << "Saved to " << filename << endl;
}

void Watopoly::play() {
    string cmd;

    cout << "Welcome to Watopoly!" << endl;
    cout << (*gameboard.curPlayer)->name << "'s turn." << endl; 
    cout << "Enter command: ";
    while (cin >> cmd) {
        if (cmd == "roll") {
            pair<int, int> roll = gameboard.moveCurPlayer();
            cout << "You rolled " << roll.first << " and " << roll.second << endl;
            cout << "You are now on " << gameboard.board[(*gameboard.curPlayer)->location]->getName() << "." << endl;
        } else if (cmd == "next") {
            gameboard.next();
            cout << (*gameboard.curPlayer)->name << "'s turn." << endl;
        } else if (cmd == "trade") {

        } else if (cmd == "improve") {

        } else if (cmd == "mortgage") {

        } else if (cmd == "unmortgage") {

        } else if (cmd == "bankrupt") {

        } else if (cmd == "assets") {

        } else if (cmd == "all") {

        } else if (cmd == "save") {
            string filename;
            cin >> filename;
            save(filename);
        } else {
            cout << "Invalid command - please try again." << endl;
        }
        cout << "Enter command: ";
    }
}
