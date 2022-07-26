#include <iostream>
#include <fstream>
#include <vector>
#include <unordered_map>
#include <memory>
#include <algorithm>
#include <string>
#include <utility>
#include "watopoly.h"
#include "collect_osap.h"
#include "academic_building.h"
#include "slc.h"
#include "player.h"
#include "gameboard.h"
#include "dc_tims_line.h"
#include "error.h"

using namespace std;

Watopoly::Watopoly(string loadfile, bool testing) : testing{testing} {
    if (loadfile != "") load(loadfile);
    else initPlayers();
}

unordered_map<char, string> Watopoly::playerPieces = {
    {'G', "Goose"}, {'B', "GRT Bus"}, {'D', "Tim Hortons Doughnut"}, {'T', "Pink Tie"},
    {'P', "Professor"}, {'S', "Student"}, {'$', "Money"}, {'L', "Laptop"}
};

pair<int, int> Watopoly::roll() {
    int die1 = rand() % 6 + 1;
    int die2 = rand() % 6 + 1;
    return pair<int, int>{die1, die2};
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

    cout << "How many players are playing? ";
    cin >> numPlayers;

    vector<Player> players;
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
                players.emplace_back(Player{curPlayerName, curPlayerSymbol});
                break;
            } catch (...) {
                cout << "That piece is not available. Please try again." << endl;
            }
        }
    }
    gameboard.initPlayers(players);
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
    vector<Player> players;
    for (int i = 0; i < numPlayers; ++i) {
        cin >> playerName;
        replace(playerName.begin(), playerName.end(), '_', ' ');
        cin >> playerSymbol;
        cin >> timsCups;
        cin >> money;
        cin >> location;

        inTimsLine = false;
        numTurnsInTimsLine = 0;
        if (location == gameboard.DC_TIMS_LOCATION) {
            cin >> inTimsLine;
            if (inTimsLine) cin >> numTurnsInTimsLine;
        }

        players.emplace_back(
            Player{playerName, playerSymbol, money, location, timsCups, inTimsLine, numTurnsInTimsLine}
        );
    }
    gameboard.initPlayers(players);
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
        int playerIndex = (i + gameboard.curPlayer) % numPlayers;
        Player &player = *gameboard.players[playerIndex];
        string playerName{player.name};
        replace(playerName.begin(), playerName.end(), ' ', '_');
        file << playerName << " " << player.symbol << " " << player.timsCups
            << " " << player.money << " " << player.location;
        if (player.location ==  gameboard.DC_TIMS_LOCATION) {
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
    cout << "Welcome to Watopoly!" << endl;
    gameboard.display->print();
    while (true) {
        string cmd;
        Player &curPlayer = gameboard.getCurPlayer();
        // gameboard.display.print();
        cout << endl;
        cout << curPlayer.getName() << "'s turn." << endl; 
        bool hasRolled = false;
        int numDoubles = 0;
        while (true) {
            cout << "Enter command: ";
            cin >> cmd;
            try {
                if (cmd == "roll") {
                    if (hasRolled) cout << "You have already rolled for this turn." << endl;
                    else {
                        pair<int, int> roll = this->roll();
                        cout << "You rolled " << roll.first << " and " << roll.second << "." << endl;
                        if (roll.first == roll.second) {
                            if (curPlayer.leaveTimsLine()) {
                                cout << "Congrats! You get to leave the Tims line!" << endl;
                                hasRolled = true;
                            }
                            ++numDoubles;
                            if (numDoubles == 3) {
                                cout << "You rolled 3 doubles and have been sent to the back of the DC Tims Line!" << endl;
                                curPlayer.goToTimsLine();
                                hasRolled = true;
                                continue;
                            }
                        } else {
                            hasRolled = true;
                        }
                        gameboard.moveCurPlayer(roll.first + roll.second);
                    }
                } else if (cmd == "next") {
                    if (!hasRolled) throw NextWithoutRollError{};
                    else {
                        gameboard.next();
                        break;
                    }
                } else if (cmd == "trade") {
                    string tradeWith;
                    string give;
                    string receive;

                    cin >> tradeWith;
                    cin >> give;
                    cin >> receive;

                    Trade trade;
                    try {
                        trade = gameboard.createTrade(tradeWith, give, receive);
                    } catch (...) {
                        cout << "Invalid trade. ";
                        throw;
                    }

                    string response;
                    cout << "Player " << tradeWith << ": Accept trade? (accept/reject) ";
                    cin >> response;

                    if (response == "accept") gameboard.trade(trade);
                    else if (response != "reject") throw InvalidCommandError{};
                } else if (cmd == "improve") {
                    string propertyName;
                    string cmd;
                    cin >> propertyName;
                    cin >> cmd;
                    if (cmd =="buy") gameboard.buyImprovement(curPlayer, propertyName);
                    else if (cmd == "sell") gameboard.sellImprovement(curPlayer, propertyName);
                    else throw InvalidCommandError{};
                } else if (cmd == "mortgage") {
                    string propertyName;
                    cin >> propertyName;
                    gameboard.mortgage(curPlayer, propertyName);
                } else if (cmd == "unmortgage") {
                    string propertyName;
                    cin >> propertyName;
                    gameboard.unmortgage(curPlayer, propertyName);
                } else if (cmd == "bankrupt") {

                } else if (cmd == "assets") {
                    curPlayer.assets();
                } else if (cmd == "all") {
                    gameboard.allAssets();
                } else if (cmd == "save") {
                    string filename;
                    cin >> filename;
                    save(filename);
                } else if (cmd == "quit") {
                    return;
                } else {
                    throw InvalidCommandError{};
                }
            } catch (InvalidCommandError e) {
                cout << "Invalid command - please try again." << endl;
            } catch (NextWithoutRollError e) {
                cout << "You must roll before ending your turn." << endl;
            } catch (InvalidPropertyNameError e) {
                cout << "Invalid property name: please try again." << endl;
            } catch (InvalidPlayerNameError e) {
                cout << "Invalid player name: please try again." << endl;
            } catch (TradeMoneyError e) {
                cout << "Cannot trade money." << endl;
            } catch (NotTradeablePropertyError e) {
                cout << "Property cannot be traded - other properties in block have improvements." << endl;
            }
            cout << endl;
        }
    }
}
