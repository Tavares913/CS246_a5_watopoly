#ifndef __AUCTION_H__
#define __AUCTION_H__

#include <vector>
#include <memory>

class Player;
class Property;

class Auction {
    std::vector<Player *> players;
    Property *property = nullptr;
    int curPlayer;
    int propPrice;

    void nextPlayer();

  public:
    void setPlayers(std::vector<std::unique_ptr<Player>> &players);
    void setProperty(Property *property);
    void auction();
};

#endif