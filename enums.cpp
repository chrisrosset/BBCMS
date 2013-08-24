#include <string>
#include "enums.h"

DealerId parseDealerId(std::string& input)
{
    if     (input == "DB"  ) { return DB   ; }
    else if(input == "JPM" ) { return JPM  ; }
    else if(input == "UBS" ) { return UBS  ; }
    else if(input == "RBC" ) { return RBC  ; }
    else if(input == "BARX") { return BARX ; }
    else if(input == "MS " ) { return MS   ; }
    else if(input == "CITI") { return CITI ; }
    else if(input == "BOFA") { return BOFA ; }
    else if(input == "RBS" ) { return RBS  ; }
    else if(input == "HSBC") { return HSBC ; }
    else { return _INVALID_DEALER; }
}

std::string dealerIdToString(DealerId input)
{
    if     (input == DB  ) { return "DB"  ; }
    else if(input == JPM ) { return "JPM" ; }
    else if(input == UBS ) { return "UBS" ; }
    else if(input == RBC ) { return "RBC" ; }
    else if(input == BARX) { return "BARX"; }
    else if(input == MS  ) { return "MS"  ; }
    else if(input == CITI) { return "CITI"; }
    else if(input == BOFA) { return "BOFA"; }
    else if(input == RBS ) { return "RBS" ; }
    else if(input == HSBC) { return "HSBC"; }
    else { return "INVALID ID"; }
}

CommandType parseCommandType(std::string& input)
{
    if     (input == "LIST"    ) { return LIST   ; }
    else if(input == "AGGRESS" ) { return AGGRESS; }
    else if(input == "CHECK"   ) { return CHECK  ; }
    else if(input == "REVOKE"  ) { return REVOKE ; }
    else if(input == "POST"    ) { return POST   ; }
    else { return _INVALID_COMMAND; }
}

Commodity parseCommodity(std::string& input)
{
    if     (input == "GOLD") { return GOLD; }
    else if(input == "OIL" ) { return OIL ; }
    else if(input == "PORK") { return PORK; }
    else if(input == "RICE") { return RICE; }
    else if(input == "SILV") { return SILV; }
    else { return _INVALID_COMMODITY; }
}

std::string commodityToString(Commodity input)
{
    if     (input == GOLD) { return "GOLD"; }
    else if(input == OIL ) { return "OIL" ; }
    else if(input == PORK) { return "PORK"; }
    else if(input == RICE) { return "RICE"; }
    else if(input == SILV) { return "SILV"; }
    else { return "INVALID_COMMODITY"; }
}

Side parseSide(std::string& input)
{
    if     (input == "BUY") { return BUY; }
    else if(input == "SELL" ) { return SELL; }
    else  { return _INVALID_SIDE; }
}

std::string sideToString(Side input)
{
    if     (input == BUY ) { return "BUY"  ; }
    else if(input == SELL) { return "SELL"; }
    else { return "INVALID SIDE"; }
}

