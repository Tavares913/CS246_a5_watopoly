#include <string>
#include "tile.h"

using namespace std;

Tile::Tile(int location, string name) : location{location}, name{name} {}

int Tile::getLocation() const { return location; }

string Tile::getName() const { return name; }

Tile::~Tile() {}
