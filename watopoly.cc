#include <iostream>
#include <vector>
#include "watopoly.h"
#include "collect_osap.h"
#include "academic_building.h"
#include "slc.h"

using namespace std;

void Watopoly::init() {
    players.clear();

    int numPlayers = 0;
    string curPlayerName = "";
    char curPlayerSymbol = '';

    vector<string> playerNames;
    vector<char> playerSymbols;

    cin >> skipws;
    cin >> numPlayers;
    for (int i = 0; i < numPlayers; ++i) {
        cin >> curPlayerName;
        cin >> curPlayerSymbol;

        playerNames.emplace_back(curPlayerName);
        playerSymbols.emplace_back(curPlayerSymbol);
    }

    for (int i = 0; i < playerNames.size(); ++i) {
        players.emplace_back(playerName, playerSymbol);
    }
    tiles.emplace_back(CollectOSAP{0});
    tiles.emplace_back(AcademicBuilding{"AL", 1, 40, 50, vector<int> {2, 10, 30, 90, 160, 250}});
    tiles.emplace_back(SLC{2, dcPointer, osapPointer});
    tiles.emaplace_back();
}

void Watopoly::play() {

}