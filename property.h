#include<string>

class Player;

class Property: public Tile {
  string name;
  int purchaseCost;
  Player ownedBy;
  vector<Property  *> propertyBlock;
  vector<int> tuition;
 public:
  virtual int getTuition();
  virtual void visit(Player &player) = 0;
};
