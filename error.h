#ifndef __ERROR_H__
#define __ERROR_H__

class Error {};

class InvalidCommandError : public Error {};

class InvalidPropertyNameError : public Error {};

class InvalidPlayerNameError : public Error {};

class NextWithoutRollError : public Error {};

class NotEnoughMoneyError : public Error {};

class NotEnoughCupsError : public Error {};

class TradeMoneyError : public Error {};

class NotTradeablePropertyError : public Error {};

#endif