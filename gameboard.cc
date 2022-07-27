#include <vector>
#include <iostream>
#include <memory>
#include <cstdlib>
#include <string>
#include <utility>
#include <sstream>
#include "gameboard.h"
#include "display_messages.h"
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
#include "auction.h"
#include "error.h"

using namespace std;

Auction GameBoard::auction = Auction{};

unordered_map<PropertyBlock, vector<Property *>> GameBoard::propertyBlocks = unordered_map<PropertyBlock, vector<Property *>>();

GameBoard::GameBoard() : display{make_unique<Display>()} {
    initBoard();
}

void GameBoard::initBoard() {
    board.clear();

    // non-properties
    unique_ptr<CollectOSAP> collectOSAP = make_unique<CollectOSAP>(0, 200);
    unique_ptr<DCTimsLine> dcTimsLine = make_unique<DCTimsLine>(10);
    unique_ptr<SLC> slc1 = make_unique<SLC>(2, collectOSAP.get());
    unique_ptr<SLC> slc2 = make_unique<SLC>(17, collectOSAP.get());
    unique_ptr<SLC> slc3 = make_unique<SLC>(33, collectOSAP.get());
    unique_ptr<NeedlesHall> needlesHall1 = make_unique<NeedlesHall>(7);
    unique_ptr<NeedlesHall> needlesHall2 = make_unique<NeedlesHall>(22);
    unique_ptr<NeedlesHall> needlesHall3 = make_unique<NeedlesHall>(36);
    unique_ptr<Tuition> tuition = make_unique<Tuition>(4, 300, 0.1);
    unique_ptr<GooseNesting> gooseNesting = make_unique<GooseNesting>(20);
    unique_ptr<GoToTims> goToTims = make_unique<GoToTims>(30);
    unique_ptr<CoopFee> coopFee = make_unique<CoopFee>(38, 150);

    // properties
    // academic buildings
    unique_ptr<AcademicBuilding> al = make_unique<AcademicBuilding>(1, "AL", 40, PropertyBlock::Arts1, 50, vector<int>{2, 10, 30, 90, 160, 250});
    nameToProperties.insert({"AL", al.get()});
    unique_ptr<AcademicBuilding> ml = make_unique<AcademicBuilding>(3, "ML", 60, PropertyBlock::Arts1, 50, vector<int>{4, 20, 60, 180, 320, 450});
    nameToProperties.insert({"ML", ml.get()});
    propertyBlocks.insert({PropertyBlock::Arts1, {al.get(), ml.get()}});
    
    unique_ptr<AcademicBuilding> ech = make_unique<AcademicBuilding>(6, "ECH", 100, PropertyBlock::Arts2, 50, vector<int>{6, 30, 90, 270, 400, 550});
    nameToProperties.insert({"ECH", ech.get()});
    unique_ptr<AcademicBuilding> pas = make_unique<AcademicBuilding>(8, "PAS", 100, PropertyBlock::Arts2, 50, vector<int>{6, 30, 90, 270, 400, 550});
    nameToProperties.insert({"PAS", pas.get()});
    unique_ptr<AcademicBuilding> hh = make_unique<AcademicBuilding>(9, "HH", 120, PropertyBlock::Arts2, 50, vector<int>{8, 40, 100, 300, 450, 600});
    nameToProperties.insert({"HH", hh.get()});
    propertyBlocks.insert({PropertyBlock::Arts2, {ech.get(), pas.get(), hh.get()}});
    
    unique_ptr<AcademicBuilding> rch = make_unique<AcademicBuilding>(11, "RCH", 140, PropertyBlock::Eng, 100, vector<int>{10, 50, 150, 450, 625, 750});
    nameToProperties.insert({"RCH", rch.get()});
    unique_ptr<AcademicBuilding> dwe = make_unique<AcademicBuilding>(13, "DWE", 140, PropertyBlock::Eng, 100, vector<int>{10, 50, 150, 450, 625, 750});
    nameToProperties.insert({"DWE", dwe.get()});
    unique_ptr<AcademicBuilding> cph = make_unique<AcademicBuilding>(14, "CPH", 160, PropertyBlock::Eng, 100, vector<int>{12, 60, 180, 500, 700, 900});
    nameToProperties.insert({"CPH", cph.get()});
    propertyBlocks.insert({PropertyBlock::Eng, {rch.get(), dwe.get(), cph.get()}});
    
    unique_ptr<AcademicBuilding> lhi = make_unique<AcademicBuilding>(16, "LHI", 180, PropertyBlock::Health, 100, vector<int>{14, 70, 200, 550, 750, 950});
    nameToProperties.insert({"LHI", lhi.get()});
    unique_ptr<AcademicBuilding> bmh = make_unique<AcademicBuilding>(18, "BMH", 180, PropertyBlock::Health, 100, vector<int>{14, 70, 200, 550, 750, 950});
    nameToProperties.insert({"BMH", bmh.get()});
    unique_ptr<AcademicBuilding> opt = make_unique<AcademicBuilding>(19, "OPT", 200, PropertyBlock::Health, 100, vector<int>{16, 80, 220, 600, 800, 1000});
    nameToProperties.insert({"OPT", opt.get()});
    propertyBlocks.insert({PropertyBlock::Health, {lhi.get(), bmh.get(), opt.get()}});
    
    unique_ptr<AcademicBuilding> ev1 = make_unique<AcademicBuilding>(21, "EV1", 220, PropertyBlock::Env, 150, vector<int>{18, 90, 250, 700, 875, 1050});
    nameToProperties.insert({"EV1", ev1.get()});
    unique_ptr<AcademicBuilding> ev2 = make_unique<AcademicBuilding>(23, "EV2", 220, PropertyBlock::Env, 150, vector<int>{18, 90, 250, 700, 875, 1050});
    nameToProperties.insert({"EV2", ev2.get()});
    unique_ptr<AcademicBuilding> ev3 = make_unique<AcademicBuilding>(24, "EV3", 240, PropertyBlock::Env, 150, vector<int>{20, 100, 300, 750, 925, 1100});
    nameToProperties.insert({"EV3", ev3.get()});
    propertyBlocks.insert({PropertyBlock::Env, {ev1.get(), ev2.get(), ev3.get()}});
    
    unique_ptr<AcademicBuilding> phys = make_unique<AcademicBuilding>(26, "PHYS", 260, PropertyBlock::Sci1, 150, vector<int>{22, 110, 330, 800, 975, 1150});
    nameToProperties.insert({"PHYS", phys.get()});
    unique_ptr<AcademicBuilding> b1 = make_unique<AcademicBuilding>(27, "B1", 260, PropertyBlock::Sci1, 150, vector<int>{22, 110, 330, 800, 975, 1150});
    nameToProperties.insert({"B1", b1.get()});
    unique_ptr<AcademicBuilding> b2 = make_unique<AcademicBuilding>(29, "B2", 280, PropertyBlock::Sci1, 150, vector<int>{24, 120, 360, 850, 1025, 1200});
    nameToProperties.insert({"B2", b2.get()});
    propertyBlocks.insert({PropertyBlock::Sci1, {phys.get(), b1.get(), b2.get()}});
    
    unique_ptr<AcademicBuilding> eit = make_unique<AcademicBuilding>(31, "EIT", 300, PropertyBlock::Sci2, 200, vector<int>{26, 130, 390, 900, 1100, 1275});
    nameToProperties.insert({"EIT", eit.get()});
    unique_ptr<AcademicBuilding> esc = make_unique<AcademicBuilding>(32, "ESC", 300, PropertyBlock::Sci2, 200, vector<int>{26, 130, 390, 900, 1100, 1275});
    nameToProperties.insert({"ESC", esc.get()});
    unique_ptr<AcademicBuilding> c2 = make_unique<AcademicBuilding>(34, "C2", 320, PropertyBlock::Sci2, 200, vector<int>{28, 150, 450, 1000, 1200, 1400});
    nameToProperties.insert({"C2", c2.get()});
    propertyBlocks.insert({PropertyBlock::Sci2, {eit.get(), esc.get(), c2.get()}});
    
    unique_ptr<AcademicBuilding> mc = make_unique<AcademicBuilding>(37, "MC", 350, PropertyBlock::Math, 200, vector<int>{35, 175, 500, 1100, 1300, 1500});
    nameToProperties.insert({"MC", mc.get()});
    unique_ptr<AcademicBuilding> dc = make_unique<AcademicBuilding>(39, "DC", 400, PropertyBlock::Math, 200, vector<int>{50, 200, 600, 1400, 1700, 2000});
    nameToProperties.insert({"DC", dc.get()});
    propertyBlocks.insert({PropertyBlock::Math, {mc.get(), dc.get()}});

    // residences
    unique_ptr<Residence> mkv = make_unique<Residence>(5, "MKV", 200, PropertyBlock::ResidenceBlock, 25);
    nameToProperties.insert({"MKV", mkv.get()});
    unique_ptr<Residence> uwp = make_unique<Residence>(15, "UWP", 200, PropertyBlock::ResidenceBlock, 25);
    nameToProperties.insert({"UWP", uwp.get()});
    unique_ptr<Residence> v1 = make_unique<Residence>(25, "V1", 200, PropertyBlock::ResidenceBlock, 25);
    nameToProperties.insert({"V1", v1.get()});
    unique_ptr<Residence> rev = make_unique<Residence>(35, "REV", 200, PropertyBlock::ResidenceBlock, 25);
    nameToProperties.insert({"REV", rev.get()});
    propertyBlocks.insert({PropertyBlock::ResidenceBlock, {mkv.get(), uwp.get(), v1.get(), rev.get()}});

    // gyms
    unique_ptr<Gym> pac = make_unique<Gym>(12, "PAC", 150, PropertyBlock::GymBlock);
    nameToProperties.insert({"PAC", pac.get()});
    unique_ptr<Gym> cif = make_unique<Gym>(28, "CIF", 150, PropertyBlock::GymBlock);
    nameToProperties.insert({"CIF", cif.get()});
    propertyBlocks.insert({PropertyBlock::GymBlock, {pac.get(), cif.get()}});

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
    board.emplace_back(move(rev));
    board.emplace_back(move(needlesHall3));
    board.emplace_back(move(mc));
    board.emplace_back(move(coopFee));
    board.emplace_back(move(dc));
}

void GameBoard::initPlayers(vector<Player> &players) {
    for (auto &player : players) {
        unique_ptr<Player> playerPtr = make_unique<Player>(player);
        this->players.emplace_back(move(playerPtr));
        nameToPlayers.insert({player.getName(), playerPtr.get()});
    }
    auction.setPlayers(this->players);
}

Player &GameBoard::getCurPlayer() const {
    return *players[curPlayer];
}

void GameBoard::setCurPlayer(Player *player) {
    for (int i = 0; i < players.size(); ++i) {
        if (players[i].get() == player) {
            curPlayer = i;
            return;
        }
    }
}

void GameBoard::moveCurPlayer(int moveBy) {
    Player &curPlayer = getCurPlayer();
    int oldTile = curPlayer.getLocation();
    if (curPlayer.moveBy(moveBy)) curPlayer.visit(*board[0]);
    int newTile = curPlayer.getLocation();
    display->notify(PlayerMove{oldTile, newTile, curPlayer.getSymbol()});
    display->print();
    curPlayer.visit(*board[newTile]);
}

void GameBoard::next() {
    ++curPlayer;
    if (curPlayer == players.size()) curPlayer = 0;
}

Property &GameBoard::getPropertyByName(string propertyName) const {
    try {
        return *nameToProperties.at(propertyName);
    } catch (...) {
        throw InvalidPropertyNameError{};
    }
}

Player &GameBoard::getPlayerByName(string playerName) const {
    try {
        return *nameToPlayers.at(playerName);
    } catch (...) {
        throw InvalidPlayerNameError{};
    }
}

void GameBoard::buyImprovement(Player &p, string propertyName) {
    Property property = getPropertyByName(propertyName);
    p.buyImprovement(property);
    display->notify(Improvement{property.getLocation()});
}

void GameBoard::sellImprovement(Player &p, string propertyName) {
    Property property = getPropertyByName(propertyName);
    p.sellImprovement(property);
    display->notify(Unimprovement{property.getLocation()});
}

void GameBoard::buyProperty(Player &p, string propertyName) {
    if (!getPropertyByName(propertyName).getOwner()) {
        p.buyProperty(getPropertyByName(propertyName));
    }
}

void GameBoard::mortgage(Player &p, string propertyName) {
    p.mortgage(getPropertyByName(propertyName));
}

void GameBoard::unmortgage(Player &p, string propertyName) {
    p.unmortgage(getPropertyByName(propertyName));
}

void GameBoard::allAssets() {
    for (auto &p : players) {
        p->assets();
    }
}

void GameBoard::startAuction(Property *p) {
    auction.setProperty(p);
    auction.auction();
}

Trade GameBoard::createTrade(string otherPlayerName, string give, string receive) {
    Player *curPlayer = &getCurPlayer();
    Player *otherPlayer = &getPlayerByName(otherPlayerName);

    istringstream giveStream{give};
    float giveAmt = 0;
    Property *giveProperty = nullptr;
    bool giveMoney = false;
    if (!(giveStream >> giveAmt)) {
        giveProperty = &getPropertyByName(give);
        giveProperty->tradeable();
        if (giveProperty->getOwner() != curPlayer) throw NotOwnerTradeError{};
    } else giveMoney = true;

    istringstream receiveStream{receive};
    float receiveAmt = 0;
    Property *receiveProperty = nullptr;
    if (!(receiveStream >> receiveAmt)) {
        receiveProperty = &getPropertyByName(receive);
        receiveProperty->tradeable();
        if (receiveProperty->getOwner() != otherPlayer) throw NotOwnerTradeError{};
    } else {
        if (giveMoney) throw TradeMoneyError{};
    }

    return Trade{curPlayer, giveAmt, giveProperty, otherPlayer, receiveAmt, receiveProperty};
}

void GameBoard::trade(Trade &trade) {
    if (trade.giveProperty) trade.receiver->receiveProperty(*trade.giveProperty);
    else trade.receiver->receiveMoney(trade.giveAmt);
    if (trade.receiveProperty) trade.giver->receiveProperty(*trade.receiveProperty);
    else trade.giver->receiveMoney(trade.receiveAmt); 
}

void GameBoard::bankrupt(Player *player, Player *payee) {
    auto it = players.begin();
    for (; it != players.end(); ++it) {
        if (it->get() == player) break;
    }
    players.erase(it);
    player->bankrupt(payee);
}

bool GameBoard::checkWinner() const {
    if (players.size() == 1) {
        Display::printMessage("Woohoo! Player " + players[0]->getName() + " wins!");
        return true;
    }
    return false;
}
