#include <iostream>
#include <string>
#include <vector>

using namespace std;

int main() {
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
}