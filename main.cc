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
        switch (argv[i]) {
            case "-tesing":
                testing = true;
                break;
            case "-load": 
                if (++i == argc) {
                    invalidUsage(argv[0]);
                    return 1;
                }
                loadfile = argv[i];
                break;
            default:
                invalidUsage(argv[0]);
                return 1;
        }
    }

    Watopoly game{loadfile, testing};
    game.play();
}