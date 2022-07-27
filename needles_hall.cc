#include <cstdlib>
#include "needles_hall.h"
#include "player.h"

using namespace std;

NeedlesHall::NeedlesHall(int location) : NonProperty{location, "Needles Hall"} {}

void NeedlesHall::visit(Player &p) {
    int timsCupChance = rand() % 100;
    if (timsCupChance == 0) {
        p.receiveTimsCup();
    }

    int randNum = rand() % 18;
    int moneyToAdd = 0;
    
    if (randNum < 1) {
        moneyToAdd = -200;
    } else if (randNum < 3) {
        moneyToAdd = -100;
    } else if (randNum < 6) {
        moneyToAdd = -50;
    } else if (randNum <  12) {
        moneyToAdd = 25;
    } else if (randNum < 15) {
        moneyToAdd = 50;
    } else if (randNum < 17) {
        moneyToAdd = 100;
    } else if (randNum < 18) {
        moneyToAdd = 200;
    }

    p.receiveMoney(moneyToAdd);
}
