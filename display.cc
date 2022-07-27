#include "display.h"
#include "display_messages.h"
#include "tile_print.h"
#include <vector>
#include <string>
#include <iostream>

using namespace std;

Display::Display() : display{} {
    vector<TilePrint> curRow;

    // first row of the board
    curRow.emplace_back("Goose Nesting");
    curRow.emplace_back("EV1", true);
    curRow.emplace_back("NEEDLES HALL");
    curRow.emplace_back("EV2", true);
    curRow.emplace_back("EV3", true);
    curRow.emplace_back("V1");
    curRow.emplace_back("PHYS", true);
    curRow.emplace_back("B1", true);
    curRow.emplace_back("CIF");
    curRow.emplace_back("B2", true);
    curRow.emplace_back("GO TO TIMS", false, true);
    display.emplace_back(curRow);
    curRow.clear();

    // second row of the board
    curRow.emplace_back("OPT", true, true);
    for (int i = 0; i < 8; ++i) {
        curRow.emplace_back("BLANK", false, false, true);
    }
    curRow.emplace_back("BLANK", false, false, true, false, true);
    curRow.emplace_back("EIT", true, true);
    display.emplace_back(curRow);
    curRow.clear();

    // third row of the board
    curRow.emplace_back("BMH", true, true);
    for (int i = 0; i < 8; ++i) {
        curRow.emplace_back("BLANK", false, false, true);
    }
    curRow.emplace_back("BLANK", false, false, true, false, true);
    curRow.emplace_back("ESC", true, true);
    display.emplace_back(curRow);
    curRow.clear();

    // fourth row of the board
    curRow.emplace_back("SLC", false, true);
    for (int i = 0; i < 8; ++i) {
        curRow.emplace_back("BLANK", false, false, true);
    }
    curRow.emplace_back("BLANK", false, false, true, false, true);
    curRow.emplace_back("SLC", false, true);
    display.emplace_back(curRow);
    curRow.clear();

    // fifth row of the board
    curRow.emplace_back("LHI", true, true);
    for (int i = 0; i < 8; ++i) {
        curRow.emplace_back("BLANK", false, false, true);
    }
    curRow.emplace_back("BLANK", false, false, true, false, true);
    curRow.emplace_back("C2", true, true);
    display.emplace_back(curRow);
    curRow.clear();

    // sixth row of the board
    curRow.emplace_back("UWP", false, true);
    for (int i = 0; i < 8; ++i) {
        curRow.emplace_back("BLANK", false, false, true);
    }
    curRow.emplace_back("BLANK", false, false, true, false, true);
    curRow.emplace_back("REV", false, true);
    display.emplace_back(curRow);
    curRow.clear();

    // seventh row of the board
    curRow.emplace_back("CPH", true, true);
    for (int i = 0; i < 8; ++i) {
        curRow.emplace_back("BLANK", false, false, true);
    }
    curRow.emplace_back("BLANK", false, false, true, false, true);
    curRow.emplace_back("NEEDLES HALL", false, true);
    display.emplace_back(curRow);
    curRow.clear();

    // eigth row of the board
    curRow.emplace_back("DWE", true, true);
    for (int i = 0; i < 8; ++i) {
        curRow.emplace_back("BLANK", false, false, true);
    }
    curRow.emplace_back("BLANK", false, false, true, false, true);
    curRow.emplace_back("MC", true, true);
    display.emplace_back(curRow);
    curRow.clear();

    // ninth row of the board
    curRow.emplace_back("PAC", false, true);
    for (int i = 0; i < 8; ++i) {
        curRow.emplace_back("BLANK", false, false, true);
    }
    curRow.emplace_back("BLANK", false, false, true, false, true);
    curRow.emplace_back("COOP FEE", false, true);
    display.emplace_back(curRow);
    curRow.clear();

    // tenth row of the board
    curRow.emplace_back("RCH", true, true);
    for (int i = 0; i < 8; ++i) {
        curRow.emplace_back("BLANK", false, false, true, true);
    }
    curRow.emplace_back("BLANK", false, false, true, true, true);
    curRow.emplace_back("DC", true, true);
    display.emplace_back(curRow);
    curRow.clear();

    // eleventh row of the board
    curRow.emplace_back("DC Tims Line");
    curRow.emplace_back("HH", true);
    curRow.emplace_back("PAS", true);
    curRow.emplace_back("NEEDLES HALL");
    curRow.emplace_back("ECH", true);
    curRow.emplace_back("MKV");
    curRow.emplace_back("TUITION");
    curRow.emplace_back("ML", true);
    curRow.emplace_back("SLC");
    curRow.emplace_back("AL", true);
    curRow.emplace_back("COLLECT OSAP", false, true);
    display.emplace_back(curRow);
    curRow.clear();
    
}

void Display::print() {
    for (int i = 0; i < 1; ++i) {
        for (int row = 1; row <= 7; ++row) {
            if (row == 1) cout << "_";
            for (int j = 0; j < 11; ++j) {
                cout << display[i][j].getRow(row);
            }
            cout << endl;
        }
    }
    for (int i = 1; i < 10; ++i) {
        for (int row = 2; row <= 7; ++row) {
            for (int j = 0; j < 11; ++j) {
                cout << display[i][j].getRow(row);
            }
            cout << endl;
        }
    }
    for (int i = 10; i < 11; ++i) {
        for (int row = 2; row <= 7; ++row) {
            if (row == 1) cout << "_";
            for (int j = 0; j < 11; ++j) {
                cout << display[i][j].getRow(row);
            }
            cout << endl;
        }
    }
}

void Display::printMessage(string message, bool endLine) {
    cout << message;
    if (endLine) cout << endl;
}

pair<int, int> mapTileLocToDisplay(int tileLocation) {
    int coord1 = 0;
    int coord2 = 0;
    if (tileLocation < 10) {
        coord1 = 10;
        coord2 = 10 - tileLocation;
    } else if (tileLocation < 20) {
        coord1 = 10 - tileLocation % 10;
        coord2 = 0;
    } else if (tileLocation < 30) {
        coord1 = 0;
        coord2 = tileLocation % 10;
    } else if (tileLocation < 40) {
        coord1 = tileLocation % 10;
        coord2 = 10;
    }

    return pair<int, int>(coord1, coord2);
}

void Display::notify(PlayerMove pm) {
    pair<int, int> oldCoords = mapTileLocToDisplay(pm.oldTile);
    pair<int, int> newCoords = mapTileLocToDisplay(pm.newTile);

    display[oldCoords.first][oldCoords.second].removePlayer(pm.who);
    display[newCoords.first][newCoords.second].addPlayer(pm.who);

}

void Display::notify(Improvement i) {
    pair<int, int> coords = mapTileLocToDisplay(i.tile);
    display[coords.first][coords.second].improve();
}

void Display::notify(Unimprovement u) {
    pair<int, int> coords = mapTileLocToDisplay(u.tile);
    display[coords.first][coords.second].unimprove();
}