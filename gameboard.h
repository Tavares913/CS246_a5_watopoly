#ifndef __GAMEBOARD_H__
#define __GAMEBOARD_H__

#include <memory>
#include <vector>
#include <unordered_map>
#include <string>
#include "subject.h"
#include "player.h"
#include "tile.h"
#include "display.h"
#include "auction.h"

class Property;
class Watopoly;
struct Trade {
    Player *giver = nullptr;
    float giveAmt;
    Property *giveProperty = nullptr;
    Player *receiver = nullptr;
    float receiveAmt;
    Property *receiveProperty = nullptr;
};

enum PropertyBlock {
    Arts1, Arts2, Eng, Health, Env, Sci1, Sci2, Math, ResidenceBlock, GymBlock
};

class GameBoard : public Subject {
    static Auction auction;
    int curPlayer = 0;
    std::vector<std::unique_ptr<Player>> players;
    std::vector<std::unique_ptr<Tile>> board;
    std::unordered_map<std::string, Property *> nameToProperties;
    std::unordered_map<std::string, Player *> nameToPlayers;
    std::unique_ptr<Display> display;
    bool testing;

    void initBoard();
    Property &getPropertyByName(std::string propertyName) const;
    Player &getPlayerByName(std::string playerName) const;

  public:
    static const int NUM_TILES = 40;
    static const int DC_TIMS_LOCATION = 10;
    static std::unordered_map<PropertyBlock, std::vector<Property *>> propertyBlocks;

    GameBoard();
    void initPlayers(std::vector<Player> &players);
    Player &getCurPlayer() const;
    void moveCurPlayer(int moveBy);
    void next();
    void buyImprovement(Player &p, std::string propertyName);
    void sellImprovement(Player &p, std::string propertyName);
    void allAssets();
    void buyProperty(Player &p, std::string propertyName);
    void mortgage(Player &p, std::string propertyName);
    void unmortgage(Player &p, std::string propertyName);
    static void startAuction(Property *p);
    Trade createTrade(std::string otherPlayerName, std::string give, std::string receive);
    void trade(Trade trade);
    void bankrupt(Player *player, Player *payee = nullptr);
    bool checkWinner() const;

    friend class Watopoly;
};

#endif