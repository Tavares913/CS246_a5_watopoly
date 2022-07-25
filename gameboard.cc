#include <vector>
#include <memory>
#include <cstdlib>
#include <string>
#include <utility>
#include "gameboard.h"
#include "tile.h"
#include "auction.h"
#include "player.h"
#include "display.h"
#include "collect_osap.h"
#include "dc_tims_line.h"
#include "slc.h"
#include "needles_hall.h"
#include "tuition.h"
#include "goose_nesting.h"
#include "go_to_tims.h"
#include "coop_fee.h"
#include "academic_building.h"
#include "gym.h"
#include "residence.h"
#include "property.h"

using namespace std;

GameBoard::GameBoard(bool testing) : display{make_unique<Display>()}, testing{testing} {
    initBoard();
}

void GameBoard::initBoard() {
    board.resize(30);
    unique_ptr<Tile> collectOSAP = make_unique<CollectOSAP>(0, 200);
    unique_ptr<Tile> dcTimsLine = make_unique<DCTimsLine>(10);
    this->dcTimsLine = dcTimsLine.get();

    
    // non-properties
    unique_ptr<Tile> slc1 = make_unique<SLC>(2, dcTimsLine.get(), collectOSAP.get());
    unique_ptr<Tile> slc2 = make_unique<SLC>(17, dcTimsLine.get(), collectOSAP.get());
    unique_ptr<Tile> slc3 = make_unique<SLC>(33, dcTimsLine.get(), collectOSAP.get());
    unique_ptr<Tile> needlesHall1 = make_unique<NeedlesHall>(7);
    unique_ptr<Tile> needlesHall2 = make_unique<NeedlesHall>(22);
    unique_ptr<Tile> needlesHall3 = make_unique<NeedlesHall>(36);
    unique_ptr<Tile> tuition = make_unique<Tuition>(4, 300, 0.1);
    unique_ptr<Tile> gooseNesting = make_unique<GooseNesting>(20);
    unique_ptr<Tile> goToTims = make_unique<GoToTims>(30, dcTimsLine.get());
    unique_ptr<Tile> coopFee = make_unique<CoopFee>(38, 150);

    // properties
    // academic buildings
    unique_ptr<Tile> al = make_unique<AcademicBuilding>(1, "AL", 40, 50, {2, 10, 30, 90, 160, 250});
    unique_ptr<Tile> ml = make_unique<AcademicBuilding>(3, "ML", 60, 50, {4, 20, 60, 180, 320, 450});
    unique_ptr<Tile> ech = make_unique<AcademicBuilding>(6, "ECH", 100, 50, {6, 30, 90, 270, 400, 550});
    unique_ptr<Tile> pas = make_unique<AcademicBuilding>(8, "PAS", 100, 50, {6, 30, 90, 270, 400, 550});
    unique_ptr<Tile> hh = make_unique<AcademicBuilding>(9, "HH", 120, 50, {8, 40, 100, 300, 450, 600});
    unique_ptr<Tile> rch = make_unique<AcademicBuilding>(11, "RCH", 140, 100, {10, 50, 150, 450, 625, 750});
    unique_ptr<Tile> dwe = make_unique<AcademicBuilding>(13, "DWE", 140, 100, {10, 50, 150, 450, 625, 750});
    unique_ptr<Tile> cph = make_unique<AcademicBuilding>(14, "CPH", 160, 100, {12, 60, 180, 500, 700, 900});
    unique_ptr<Tile> lhi = make_unique<AcademicBuilding>(16, "LHI", 180, 100, {14, 70, 200, 550, 750, 950});
    unique_ptr<Tile> bmh = make_unique<AcademicBuilding>(18, "BMH", 180, 100, {14, 70, 200, 550, 750, 950});
    unique_ptr<Tile> opt = make_unique<AcademicBuilding>(19, "OPT", 200, 100, {16, 80, 220, 600, 800, 1000});
    unique_ptr<Tile> ev1 = make_unique<AcademicBuilding>(21, "EV1", 220, 150, {18, 90, 250, 700, 875, 1050});
    unique_ptr<Tile> ev2 = make_unique<AcademicBuilding>(23, "EV2", 220, 150, {18, 90, 250, 700, 875, 1050});
    unique_ptr<Tile> ev3 = make_unique<AcademicBuilding>(24, "EV3", 240, 150, {20, 100, 300, 750, 925, 1100});
    unique_ptr<Tile> phys = make_unique<AcademicBuilding>(26, "PHYS", 260, 150, {22, 110, 330, 800, 975, 1150});
    unique_ptr<Tile> b1 = make_unique<AcademicBuilding>(27, "B1", 260, 150, {22, 110, 330, 800, 975, 1150});
    unique_ptr<Tile> b2 = make_unique<AcademicBuilding>(29, "B2", 280, 150, {24, 120, 360, 850, 1025, 1200});
    unique_ptr<Tile> eit = make_unique<AcademicBuilding>(31, "EIT", 300, 200, {26, 130, 390, 900, 1100, 1275});
    unique_ptr<Tile> esc = make_unique<AcademicBuilding>(32, "ESC", 300, 200, {26, 130, 390, 900, 1100, 1275});
    unique_ptr<Tile> c2 = make_unique<AcademicBuilding>(34, "C2", 320, 200, {28, 150, 450, 1000, 1200, 1400});
    unique_ptr<Tile> mc = make_unique<AcademicBuilding>(37, "MC", 350, 200, {35, 175, 500, 1100, 1300, 1500});
    unique_ptr<Tile> dc = make_unique<AcademicBuilding>(39, "DC", 400, 200, {50, 200, 600, 1400, 1700, 2000});

    // residences
    unique_ptr<Tile> mkv = make_unique<Residence>(5, "MKV", 200, 25);
    unique_ptr<Tile> uwp = make_unique<Residence>(15, "UWP", 200, 25);
    unique_ptr<Tile> v1 = make_unique<Residence>(25, "V1", 200, 25);
    unique_ptr<Tile> rev = make_unique<Residence>(35, "REV", 200, 25);

    // gyms
    unique_ptr<Tile> pac = make_unique<Gym>(12, "PAC", 150);
    unique_ptr<Tile> cif = make_unique<Gym>(28, "CIF", 150);

    for (auto &property : vector<unique_ptr<Property>>{
        al, ml, ech, pas, hh, rch, dwe, cph, lhi, bmh, opt, ev1, ev2, ev3, phys, 
        b1, b2, eit, esc, c2, mc, dc, mkv, uwp, v1, rev, pac, cif
    }) {
        nameToProperties.insert({property->getName(), property.get()})
    }

    board.emplace_back(move(collectOSAP));
    board.emplace_back(move(al));
    board.emplace_back(move(slc1));
    board.emplace_back(move(ml));
    board.emplace_back(move(tuition));
    board.emplace_back(move(mkv));
    board.emplace_back(move(ech));
    board.emplace_back(move(needlesHall1));
    board.emplace_back(move(pas));
    board.emplace_back(move(hh));
    board.emplace_back(move(dcTimsLine));
    board.emplace_back(move(rch));
    board.emplace_back(move(pac));
    board.emplace_back(move(dwe));
    board.emplace_back(move(cph));
    board.emplace_back(move(uwp));
    board.emplace_back(move(lhi));
    board.emplace_back(move(slc2));
    board.emplace_back(move(bmh));
    board.emplace_back(move(opt));
    board.emplace_back(move(gooseNesting));
    board.emplace_back(move(ev1));
    board.emplace_back(move(needlesHall2));
    board.emplace_back(move(ev2));
    board.emplace_back(move(ev3));
    board.emplace_back(move(v1));
    board.emplace_back(move(phys));
    board.emplace_back(move(b1));
    board.emplace_back(move(cif));
    board.emplace_back(move(b2));
    board.emplace_back(move(goToTims));
    board.emplace_back(move(eit));
    board.emplace_back(move(esc));
    board.emplace_back(move(slc3));
    board.emplace_back(move(c2));
    board.emplace_back(move(needlesHall3));
    board.emplace_back(move(mc));
    board.emplace_back(move(coopFee));
    board.emplace_back(move(dc));
}

static pair<int, int> GameBoard::roll() {
    int die1 = rand() % 6 + 1;
    int die2 = rand() % 6 + 1;
    return pair<int, int>{die1, die2};
}

static string &GameBoard::getChoice(const string &message, const vector<string> &validChoices) const {
    while (true) {
        cout << message << " ";
        cout << "(";
        bool addDelimiter = false;
        for (auto &choice : validChoices) {
            if (addDelimiter) cout << "/";
            cout << choice;
            addDelimiter = true;
        }
        cout << ") ";
        string c;
        cin >> c;
        if (find(validChoices.begin(), validChoices.end(), c) != validChoices.end()) {
            return c;
        }
        cout << "Invalid choice, please try again." << endl;
    }
}

void GameBoard::moveCurPlayer() {
    pair<int, int> roll = roll();
    // TODO check for doubles, etc
    players[curPlayer]->move(roll.first + roll.second);
    next();
}

void GameBoard::next() {
    if (curPlayer == players.size() - 1) {
        curPlayer = 0;
    } else {
        ++curPlayer;
    }
}

void GameBoard::buyImprovement(Player &p, string propertyName) {
    p.buyImprovement(*nameToProperties[propertyName]);
}

void GameBoard::sellImprovement(Player &p, string propertyName) {
    p.sellImprovement(*nameToProperties[propertyName]);
}

void GameBoard::allAssets() {
    for (auto &p : players) {
        p->assets();
    }
}

void GameBoard::buyProperty(Player &p, string propertyName) {
    if (!nameToProperties[propertyName]->getOwner()) {
        p.buyProperty(*nameToProperties[propertyName]);
    }
}

void GameBoard::mortgage(Player &p, string propertyName) {
    p.mortgage(*nameToProperties[propertyName]);
}

void GameBoard::unmortgage(Player &p, string propertyName) {
    p.unmortgage(*nameToProperties[propertyName]);
}

void GameBoard::auction(Property *p) {
    Auction a{players, p};
    a.auction();
}