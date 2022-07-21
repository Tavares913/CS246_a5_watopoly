#include <iostream>
#include <vector>

using namespace std;

void Watopoly::init() {
    players.clear;

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
}

void Watopoly::play() {

}