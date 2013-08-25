#ifndef __ENUMS__
#define __ENUMS__

#include <string>

enum DealerId
{
    DB,
    JPM,
    UBS,
    RBC,
    BARX,
    MS,
    CITI,
    BOFA,
    RBS,
    HSBC,

    // special values
    _EMPTY,
    _INVALID_DEALER
};

DealerId parseDealerId(std::string& input);
std::string dealerIdToString(DealerId input);

enum Side
{
    BUY,
    SELL,
    _INVALID_SIDE
};

Side parseSide(std::string& input);
std::string sideToString(Side input);

enum Commodity
{
    GOLD,
    SILV,
    PORK,
    OIL,
    RICE,
    _INVALID_COMMODITY
};

Commodity parseCommodity(std::string& input);
std::string commodityToString(Commodity input);

enum CommandType
{
    AGGRESS,
    LIST,
    POST,
    REVOKE,
    CHECK,
    _INVALID_COMMAND
};

CommandType parseCommandType(std::string& input);

enum Error
{
    UNAUTHORIZED,
    UNKNOWN_ORDER,
    UNKNOWN_DEALER,
    UNKNOWN_COMMODITY,
    INVALID_MESSAGE,
    NO_ERROR
};

std::string errorToString(Error input);

#endif // __ENUMS__

