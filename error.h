#ifndef __ERROR_H__
#define __ERROR_H__

#include <string>

class Player;

class Error {
  public:
    virtual std::string getMessage() const = 0;
};

class InvalidCommandError : public Error {
  public:
    std::string getMessage() const override {
        return "Invalid command - please try again.";
    }
};

class InvalidPropertyNameError : public Error {
  public:
    std::string getMessage() const override {
        return "Invalid property name: please try again.";
    }
};

class InvalidPlayerNameError : public Error {
  public:
    std::string getMessage() const override {
        return "Invalid player name: please try again.";
    }
};

class NextWithoutRollError : public Error {
  public:
    std::string getMessage() const override {
        return "You must roll before ending your turn.";
    }
};

class AlreadyRolledError : public Error {
  public:
    std::string getMessage() const override {
        return "You have already rolled for this turn.";
    }
};

class NotEnoughMoneyError : public Error {
    Player *player;
    float amount;
    Player *payee;

  public:
    NotEnoughMoneyError(Player *player = nullptr, float amount = 0, Player *payee = nullptr) 
      : player{player}, amount{amount}, payee{payee} {}
    Player *getPlayer() const { return player; }
    bool owesMoney() const { return amount != 0; }
    float getAmount() const { return amount;}
    Player *getPayee() const { return payee; }
    std::string getMessage() const override {
        return "You do not have enough money. You owe " + (payee ? payee->getName() : "The Bank") + " $" + to_string(amount);
    }
};

class NotEnoughCupsError : public Error {
  public:
    std::string getMessage() const override {
        return "Not enough Tims cups!";
    }
};

class InvalidTradeError : public Error {
  public:
    std::string getMessage() const override {
        return "Invalid trade: ";
    }
};

class TradeMoneyError : public InvalidTradeError {
  public:
    std::string getMessage() const override {
        return InvalidTradeError::getMessage() + "cannot trade money.";
    }
};

class NotTradeablePropertyError : public InvalidTradeError {
  public:
    std::string getMessage() const override {
        return InvalidTradeError::getMessage() + "this property cannot be traded.";
    }
};

class NotEnoughMoneyForTradeError : public InvalidTradeError {
  public:
    std::string getMessage() const override {
        return InvalidTradeError::getMessage() + "not enough money for trade.";
    }
};

class PropertyWithImprovementsError : public NotTradeablePropertyError {
  public:
    std::string getMessage() const override {
        return NotTradeablePropertyError::getMessage() + "other properties in block have improvements.";
    }
};

class MortgagedPropertyError : public NotTradeablePropertyError {
  public:
    std::string getMessage() const override {
        return InvalidTradeError::getMessage() + "it has been mortgaged.";
    }
};

class NotOwnerTradeError : public NotTradeablePropertyError {
  public:
    std::string getMessage() const override {
        return InvalidTradeError::getMessage() + "not the owner.";
    }
};

class CannotImproveError : public Error {
  public:
    std::string getMessage() const override {
        return "Only Academic Buildings can be improved.";
    }
};

class MaxImprovementsError : public Error {
  public:
    std::string getMessage() const override {
        return "Maximum number of improvements reached!";
    }
};

class MinImprovementsError : public Error {
  public:
    std::string getMessage() const override {
        return "No improvements on building so cannot sell!";
    }
};

class NoMonopolyError : public Error {
  public:
    std::string getMessage() const override {
        return "Cannot improve buildings without a monopoly";
    }
};

class CannotMortgageWithImprovementsError : public Error {
  public:
    std::string getMessage() const override {
        return "Cannot mortgage a building that has improvements on it.";
    }
};

class NotOwnerError : public Error {
  public:
    std::string getMessage() const override {
        return "You do not own this property.";
    }
};

class AuctionError : public Error {};

class NonNumericRaiseAmountError : public AuctionError {
  public:
    std::string getMessage() const override {
        return "Please enter a number.";
    }
};

class NegativeRaiseAmountError : public AuctionError {
  public:
    std::string getMessage() const override {
        return "Please raise by a positive amount.";
    }
};

class TooHighRaiseAmountError : public AuctionError {
  public:
    std::string getMessage() const override {
        return "You cannot afford to raise by that much.";
    }
};

#endif
