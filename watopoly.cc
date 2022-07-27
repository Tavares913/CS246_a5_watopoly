#include <iostream>
#include <fstream>
#include <sstream>
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
#include "display.h"
#include "error.h"

using namespace std;

Watopoly::Watopoly(string loadfile, bool testing) : testing{testing} {
    if (loadfile != "") load(loadfile);
    else initPlayers();
}

unordered_map<char, string> Watopoly::playerPieces = {
    {'G', "Goose"}, {'B', "GRTBus"}, {'D', "TimHortonsDoughnut"}, {'T', "PinkTie"},
    {'P', "Professor"}, {'S', "Student"}, {'$', "Money"}, {'L', "Laptop"}
};

pair<int, int> Watopoly::roll(int die1, int die2) {
    if (!die1 || !die2) {
        die1 = rand() % 6 + 1;
        die2 = rand() % 6 + 1;
    }
    return pair<int, int>{die1, die2};
}

string Watopoly::getChoice(const string &message, const vector<string> &validChoices) {
    while (true) {
        ostringstream messageBuilder{};
        messageBuilder << message << " ";
        messageBuilder << "(";
        bool addDelimiter = false;
        for (auto &choice : validChoices) {
            if (addDelimiter) messageBuilder << "/";
            messageBuilder << choice;
            addDelimiter = true;
        }
        messageBuilder << ") ";
        Display::printMessage(messageBuilder.str(), false);
        string c;
        cin >> c;
        if (find(validChoices.begin(), validChoices.end(), c) != validChoices.end()) {
            return c;
        }
        Display::printMessage("Invalid choice, please try again.");
    }
}

void Watopoly::initPlayers() {
    int numPlayers;
    string curPlayerName;
    char curPlayerSymbol;

    Display::printMessage("How many players are playing? ", false);
    cin >> numPlayers;

    vector<Player> players;
    for (int i = 0; i < numPlayers; ++i) {
        while (true) {
            ostringstream piecesMessageBuilder{};
            piecesMessageBuilder << "The following pieces are available to choose from: ";
            for (auto &piece : playerPieces) piecesMessageBuilder << piece.first << "  ";
            Display::printMessage(piecesMessageBuilder.str());

            Display::printMessage("Player " + to_string(i + 1) + " - choose your piece: ", false);
            cin >> curPlayerSymbol;

            try {
                curPlayerName = playerPieces.at(curPlayerSymbol);
                playerPieces.erase(curPlayerSymbol);
                players.emplace_back(Player{curPlayerName, curPlayerSymbol});
                break;
            } catch (...) {
                Display::printMessage("That piece is not available. Please try again.");
            }
        }
    }
    gameboard.initPlayers(players);
}

void Watopoly::load(string filename) {
    ifstream readFile{filename};

    // players
    int numPlayers;
    string playerName;
    char playerSymbol;
    float money;
    int location;
    int timsCups;
    bool inTimsLine;
    int numTurnsInTimsLine;

    readFile >> numPlayers;
    vector<Player> players;
    for (int i = 0; i < numPlayers; ++i) {
        readFile >> playerName;
        replace(playerName.begin(), playerName.end(), '_', ' ');
        readFile >> playerSymbol;
        readFile >> timsCups;
        readFile >> money;
        readFile >> location;

        inTimsLine = false;
        numTurnsInTimsLine = 0;
        if (location == gameboard.DC_TIMS_LOCATION) {
            readFile >> inTimsLine;
            if (inTimsLine) readFile >> numTurnsInTimsLine;
        }

        players.emplace_back(
            Player{playerName, playerSymbol, money, location, timsCups, inTimsLine, numTurnsInTimsLine}
        );
    }
    gameboard.initPlayers(players);
    Display::printMessage("Loaded " + to_string(numPlayers) + " players.");

    // properties
    string propertyName;
    string ownerName;
    int numImprovements;

    for (int i = 0; i < gameboard.nameToProperties.size(); ++i) {
        readFile >> propertyName;
        readFile >> ownerName;
        readFile >> numImprovements;

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

    readFile.close();
    Display::printMessage("Game load complete!");
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
    Display::printMessage("Saved to " + filename);
}

void Watopoly::play() {
    Display::printMessage("Welcome to Watopoly!");
    NotEnoughMoneyError notEnoughMoney;
    while (true) {
        string cmd;
        if (gameboard.checkWinner()) return;
        Player &curPlayer = gameboard.getCurPlayer();
        Display::printMessage(curPlayer.getName() + "'s turn.");
        bool hasRolled = false;
        int numDoubles = 0;
        while (true) {
            if (notEnoughMoney.owesMoney()) {
                try {
                    curPlayer.spendMoney(notEnoughMoney.getAmount());
                    if (notEnoughMoney.getPayee()) {
                        notEnoughMoney.getPayee()->receiveMoney(notEnoughMoney.getAmount());
                    }
                    notEnoughMoney = NotEnoughMoneyError{};
                } catch (NotEnoughMoneyError &e) {}
            }
            Display::printMessage("Enter command: ", false);
            string cmd;
            cin >> cmd;
            try {
                if (cin.fail()) return;
                if (cmd == "roll") {
                    if (hasRolled) throw AlreadyRolledError{};
                    else {
                        int die1 = 0;
                        int die2 = 0;
                        if (testing) {
                            string actualRoll;
                            getline(cin, actualRoll);
                            istringstream rollStream{actualRoll};
                            if (rollStream >> die1) {
                                rollStream >> die2;
                            }
                        }
                        pair<int, int> roll = this->roll(die1, die2);
                        Display::printMessage("You rolled " + to_string(roll.first) + " and " + to_string(roll.second) + "." );
                        if (roll.first == roll.second) {
                            if (curPlayer.leaveTimsLine()) hasRolled = true;
                            ++numDoubles;
                            if (numDoubles == 3) {
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
                    if (notEnoughMoney.owesMoney()) throw notEnoughMoney;
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

                    Trade tradeObj = gameboard.createTrade(tradeWith, give, receive);

                    string response = getChoice(
                        "Player " + tradeWith + ": Accept trade?",
                        {"accept", "reject"}
                    );
                    if (response == "accept") gameboard.trade(tradeObj);
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
                    if (!notEnoughMoney.owesMoney()) throw InvalidCommandError{};
                    try {
                        gameboard.bankrupt(&curPlayer, notEnoughMoney.getPayee());
                        gameboard.next();
                        notEnoughMoney = NotEnoughMoneyError{};
                    } catch (NotEnoughMoneyError &e) {
                        notEnoughMoney = e;
                        gameboard.setCurPlayer(e.getPlayer());
                    }
                    break;
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
            } catch (NotEnoughMoneyError &e) {
                Display::printMessage(e.getMessage());
                notEnoughMoney = e;
            } catch (Error &e) {
                Display::printMessage(e.getMessage());
            }
        }
    }
}
