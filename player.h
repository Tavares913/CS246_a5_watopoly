class Property;
class Residence;
class Gym;
class GooseNesting;
class GoToTims;
class CollectOSAP;
class DCTimsLine;
class CoopFee;
class Tuition;
class NeedlesHall;
class SLC;

class Player {
 public:
  void trade(Player &other, Property &give, Property &receive);
  void trade(Player &other, Property &give, int receive);
  void trade(Player &other, int give, Property &receive);
  void improve(Property **property);
  void deteriorate(Property **property);
  void mortgage(Property **property);
  void unmortgage(Property **property);
  void assets();
  void buyProperty(Property **property);
  void visit(Residence &residence);
  void visit(Gym &gym);
  void visit(GooseNesting &gooseNesting);
  void visit(GoToTims &goToTims);
  void visit(CollectOSAP &collectOSAP);
  void visit(DCTimsLine &dcTimsLine);
  void visit(CoopFee &coopFee);
  void visit(Tuition &tuition);
  void visit(NeedlesHall &needlesHall);
  void visit(SLC &slc);
};
