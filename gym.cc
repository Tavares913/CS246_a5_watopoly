#include <utility>
#include <string>
#include "gym.h"
#include "property.h"
#include "watopoly.h"
#include "gameboard.h"

using namespace std;

Gym::Gym(int location, string name, int purchaseCost, PropertyBlock block) : Property{location, name, purchaseCost, block} {}

int Gym::getTuition() const {
    pair<int, int> roll = Watopoly::roll();
    int sumRoll = roll.first + roll.second;

    switch (getNumOwned()) {
        case 1:
            return sumRoll * 4;
        case 2:
            return sumRoll * 10;
        default:
            return 0;
    }
}
