#ifndef __PROPERTY_H__
#define __PROPERTY_H__
#include <string>
#include "tile.h"

class Player;

class Property : public Tile {
  string name;
  int purchaseCost;
  Player *owner = nullptr;
  vector<Property *> propertyBlock;
  bool mortgaged;

 public:
   Property(string name, int purchaseCost);
   virtual int getTuition() const = 0;
   virtual void visit(Player &player) = 0;
   virtual void mortgage();
   void unmortgage();
   void setOwner(const Player *owner);
   Player *getOwner() const;
   void setPropertyBlock(const vector<Property *> &propertyBlock);
   int getNumOwned() const;
   bool monopoly() const;
   void visit(Player &player) {
    if (getOwner()) {
      int tuition = getTuition();
      p.payPlayer(tuition, *getOwner());
      return;
    }

    p.offerProperty(*this);
  }
};

#endif