#ifndef __AUCTION_H__
#define __AUCTION_H__

#include <vector>
#include <memory>

class Player;
class Property;

class Auction {
    std::vector<Player *> players;
    std::vector<int> withdrawnPlayers;
    Property *property = nullptr;
    int curPlayer;
    int propPrice;

    void nextPlayer();
    Player &curWinner() const;

  public:
    void setPlayers(std::vector<std::unique_ptr<Player>> &players);
    void setProperty(Property *property);
    void auction(int curPlayerIdx = 0);
};

#endif
