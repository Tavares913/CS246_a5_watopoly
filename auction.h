#ifndef __AUCTION_H__
#define __AUCTION_H_
#include <vector>

class Player;
class Property;

class Auction {
    vector<Player *> players;
    Property *property;
    int curPlayer;
    int propPrice;

public:
    Auction(vector<Player *> players, Property *property);
    void nextPlayer();
    void auction();
};

#endif