#ifndef __DISPLAY_H__
#define __DISPLAY_H__

#include <vector>
#include <string>
#include "tile_print.h"
#include "display_messages.h"

struct PlayerMove;
struct Improvement;
struct Unimprovement;

class Display {
    std::vector<std::vector<TilePrint>> display;

  public:
    Display();
    static void printMessage(std::string message, bool endLine = true);
    void print();
    void notify(PlayerMove p);
    void notify(Improvement i);
    void notify(Unimprovement u);
};

#endif
