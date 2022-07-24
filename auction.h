#ifndef __AUCTION_H__
#define __AUCTION_H__

#include <vector>

class Player;
class Property;

class Auction {
    std::vector<Player *> players;
    Property *property;
    int curPlayer;
    int propPrice;

  public:
    Auction(std::vector<Player *> &players, Property *property);
    void nextPlayer();
    void auction();
};

#endif