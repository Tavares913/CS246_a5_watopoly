#include <string>

class Player;

class Property : public Tile {
  string name;
  int purchaseCost;
  Player *owner = nullptr;
  vector<Property  *> propertyBlock;
  bool mortgaged;
 public:
  virtual int getTuition() const = 0;
  virtual void visit(Player &player) = 0;
  virtual void mortgage() { mortgaged = true; }
  void unmortgage() { mortgaged = false; }
  void setOwner(const Player *owner) { this->owner = owner; }
  Player *getOwner() const { return owner; }
  void setPropertyBlock(const vector<Property *> &propertyBlock) {
    this->propertyBlock = propertyBlock;
  }
  int getNumOwned() const {
    if (!owner) return 0;
    int numOwned = 0;
    for (auto property : propertyBlock) {
      if (property->owner == owner) ++numOwned;
    }
    return numOwned;
  }
  bool monopoly() const { return getNumOwned() == propertyBlock.size(); }
};
