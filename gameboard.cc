#include <vector>
#include <iostream>
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

GameBoard::GameBoard() : display{make_unique<Display>()} {
    initBoard();
}

void GameBoard::initBoard() {
    board.clear();
    unique_ptr<CollectOSAP> collectOSAP = make_unique<CollectOSAP>(0, 200);
    unique_ptr<DCTimsLine> dcTimsLine = make_unique<DCTimsLine>(10);
    this->dcTimsLine = dcTimsLine.get();
    
    // non-properties
    unique_ptr<SLC> slc1 = make_unique<SLC>(2, dcTimsLine.get(), collectOSAP.get());
    unique_ptr<SLC> slc2 = make_unique<SLC>(17, dcTimsLine.get(), collectOSAP.get());
    unique_ptr<SLC> slc3 = make_unique<SLC>(33, dcTimsLine.get(), collectOSAP.get());
    unique_ptr<NeedlesHall> needlesHall1 = make_unique<NeedlesHall>(7);
    unique_ptr<NeedlesHall> needlesHall2 = make_unique<NeedlesHall>(22);
    unique_ptr<NeedlesHall> needlesHall3 = make_unique<NeedlesHall>(36);
    unique_ptr<Tuition> tuition = make_unique<Tuition>(4, 300, 0.1);
    unique_ptr<GooseNesting> gooseNesting = make_unique<GooseNesting>(20);
    unique_ptr<GoToTims> goToTims = make_unique<GoToTims>(30, dcTimsLine.get());
    unique_ptr<CoopFee> coopFee = make_unique<CoopFee>(38, 150);

    // properties
    // academic buildings
    unique_ptr<AcademicBuilding> al = make_unique<AcademicBuilding>(1, "AL", 40, 50, vector<int>{2, 10, 30, 90, 160, 250});
    nameToProperties.insert({"AL", al.get()});
    unique_ptr<AcademicBuilding> ml = make_unique<AcademicBuilding>(3, "ML", 60, 50, vector<int>{4, 20, 60, 180, 320, 450});
    nameToProperties.insert({"ML", ml.get()});
    unique_ptr<AcademicBuilding> ech = make_unique<AcademicBuilding>(6, "ECH", 100, 50, vector<int>{6, 30, 90, 270, 400, 550});
    nameToProperties.insert({"ECH", ech.get()});
    unique_ptr<AcademicBuilding> pas = make_unique<AcademicBuilding>(8, "PAS", 100, 50, vector<int>{6, 30, 90, 270, 400, 550});
    nameToProperties.insert({"PAS", pas.get()});
    unique_ptr<AcademicBuilding> hh = make_unique<AcademicBuilding>(9, "HH", 120, 50, vector<int>{8, 40, 100, 300, 450, 600});
    nameToProperties.insert({"HH", hh.get()});
    unique_ptr<AcademicBuilding> rch = make_unique<AcademicBuilding>(11, "RCH", 140, 100, vector<int>{10, 50, 150, 450, 625, 750});
    nameToProperties.insert({"RCH", rch.get()});
    unique_ptr<AcademicBuilding> dwe = make_unique<AcademicBuilding>(13, "DWE", 140, 100, vector<int>{10, 50, 150, 450, 625, 750});
    nameToProperties.insert({"DWE", dwe.get()});
    unique_ptr<AcademicBuilding> cph = make_unique<AcademicBuilding>(14, "CPH", 160, 100, vector<int>{12, 60, 180, 500, 700, 900});
    nameToProperties.insert({"CPH", cph.get()});
    unique_ptr<AcademicBuilding> lhi = make_unique<AcademicBuilding>(16, "LHI", 180, 100, vector<int>{14, 70, 200, 550, 750, 950});
    nameToProperties.insert({"LHI", lhi.get()});
    unique_ptr<AcademicBuilding> bmh = make_unique<AcademicBuilding>(18, "BMH", 180, 100, vector<int>{14, 70, 200, 550, 750, 950});
    nameToProperties.insert({"BMH", bmh.get()});
    unique_ptr<AcademicBuilding> opt = make_unique<AcademicBuilding>(19, "OPT", 200, 100, vector<int>{16, 80, 220, 600, 800, 1000});
    nameToProperties.insert({"OPT", opt.get()});
    unique_ptr<AcademicBuilding> ev1 = make_unique<AcademicBuilding>(21, "EV1", 220, 150, vector<int>{18, 90, 250, 700, 875, 1050});
    nameToProperties.insert({"EV1", ev1.get()});
    unique_ptr<AcademicBuilding> ev2 = make_unique<AcademicBuilding>(23, "EV2", 220, 150, vector<int>{18, 90, 250, 700, 875, 1050});
    nameToProperties.insert({"EV2", ev2.get()});
    unique_ptr<AcademicBuilding> ev3 = make_unique<AcademicBuilding>(24, "EV3", 240, 150, vector<int>{20, 100, 300, 750, 925, 1100});
    nameToProperties.insert({"EV3", ev3.get()});
    unique_ptr<AcademicBuilding> phys = make_unique<AcademicBuilding>(26, "PHYS", 260, 150, vector<int>{22, 110, 330, 800, 975, 1150});
    nameToProperties.insert({"PHYS", phys.get()});
    unique_ptr<AcademicBuilding> b1 = make_unique<AcademicBuilding>(27, "B1", 260, 150, vector<int>{22, 110, 330, 800, 975, 1150});
    nameToProperties.insert({"B1", b1.get()});
    unique_ptr<AcademicBuilding> b2 = make_unique<AcademicBuilding>(29, "B2", 280, 150, vector<int>{24, 120, 360, 850, 1025, 1200});
    nameToProperties.insert({"B2", b2.get()});
    unique_ptr<AcademicBuilding> eit = make_unique<AcademicBuilding>(31, "EIT", 300, 200, vector<int>{26, 130, 390, 900, 1100, 1275});
    nameToProperties.insert({"EIT", eit.get()});
    unique_ptr<AcademicBuilding> esc = make_unique<AcademicBuilding>(32, "ESC", 300, 200, vector<int>{26, 130, 390, 900, 1100, 1275});
    nameToProperties.insert({"ESC", esc.get()});
    unique_ptr<AcademicBuilding> c2 = make_unique<AcademicBuilding>(34, "C2", 320, 200, vector<int>{28, 150, 450, 1000, 1200, 1400});
    nameToProperties.insert({"C2", c2.get()});
    unique_ptr<AcademicBuilding> mc = make_unique<AcademicBuilding>(37, "MC", 350, 200, vector<int>{35, 175, 500, 1100, 1300, 1500});
    nameToProperties.insert({"MC", mc.get()});
    unique_ptr<AcademicBuilding> dc = make_unique<AcademicBuilding>(39, "DC", 400, 200, vector<int>{50, 200, 600, 1400, 1700, 2000});
    nameToProperties.insert({"DC", dc.get()});

    // residences
    unique_ptr<Residence> mkv = make_unique<Residence>(5, "MKV", 200, 25);
    nameToProperties.insert({"MKV", mkv.get()});
    unique_ptr<Residence> uwp = make_unique<Residence>(15, "UWP", 200, 25);
    nameToProperties.insert({"UWP", uwp.get()});
    unique_ptr<Residence> v1 = make_unique<Residence>(25, "V1", 200, 25);
    nameToProperties.insert({"V1", v1.get()});
    unique_ptr<Residence> rev = make_unique<Residence>(35, "REV", 200, 25);
    nameToProperties.insert({"REV", rev.get()});

    // gyms
    unique_ptr<Gym> pac = make_unique<Gym>(12, "PAC", 150);
    nameToProperties.insert({"PAC", pac.get()});
    unique_ptr<Gym> cif = make_unique<Gym>(28, "CIF", 150);
    nameToProperties.insert({"CIF", cif.get()});

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

void GameBoard::moveCurPlayer(int moveBy) {
    // TODO check for doubles, etc
    (*curPlayer)->move(moveBy);
    board[(*curPlayer)->getLocation()]->visit(**curPlayer);
}

void GameBoard::next() {
    ++curPlayer;
    if (curPlayer == players.end()) curPlayer = players.begin();
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
    vector<Player *> players;
    for (auto &player : this->players) {
        players.emplace_back(player.get());
    }
    Auction a{players, p};
    a.auction();
}