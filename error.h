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
    float amount;
    Player *payee;

  public:
    NotEnoughMoneyError(float amount = 0, Player *payee = nullptr) : amount{amount}, payee{payee} {}
    bool owesMoney() { return amount != 0; }
    float getAmount() { return amount;}
    Player *getPayee() { return payee; }
    std::string getMessage() const override {
        return "You do not have enough money. You owe " + payee ? payee->getName() : "The Bank" + " $" + to_string(amount);
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
        return InvalidTradeError::getMessage() + "this property cannot be traded - ";
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

#endif