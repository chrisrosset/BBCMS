#ifndef __ENUMS__
#define __ENUMS__

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

enum Side
{
    BUY,
    SELL
};

enum Commodity
{
    GOLD,
    SILV,
    PORK,
    OIL,
    RICE
};

enum CommandType
{
    AGGRESS,
    LIST,
    POST,
    REVOKE,
    CHECK,
    _INVALID_COMMAND
};

enum ParseError
{
    UNKNOWN_ORDER,
    UNKNOWN_DEALER,
    UNKNOWN_COMMODITY,
    INVALID_MESSAGE
};

#endif // __ENUMS__
