#include <sstream>
#include <iostream>
#include <string>
#include "watopoly.h"

using namespace std;

void invalidUsage(string cmd) {
    cout << "Usage: " << cmd << " [-load file] [-testing]" << endl;
}

int main(int argc, char *argv[]) {
    bool testing = false;
    string loadfile = "";

    for (int i = 1; i < argc; ++i) {
        string arg{argv[i]};
        if (arg == "-testing") testing = true;
        else if (arg == "-load") {
            if (++i == argc) {
                invalidUsage(argv[0]);
                return 1;
            }
            loadfile = argv[i];
        } else {
            invalidUsage(argv[0]);
            return 1;
        }
    }

    Watopoly game{loadfile, testing};
    game.play();
}