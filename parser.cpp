#include <sstream>
#include <string>
#include <vector>

#include <iostream>

#include "parser.h"
#include "enums.h"
#include "command.h"

Error parseAggress(DealerId dId, std::vector<std::string>& tokens, Cmd::Command** result)
{
    if(tokens.size() < 4 || tokens.size() % 2 != 0)
        return INVALID_MESSAGE;

    std::vector<std::pair<OrderId, int> > orders;
    OrderId curId;
    int curAmount;

    for(unsigned int i = 2; i < tokens.size(); i+= 2) {
        std::istringstream(tokens[i]) >> curId;
        std::istringstream(tokens[i+1]) >> curAmount;
        orders.push_back(std::make_pair(curId, curAmount));
    }

    *result = new Cmd::Aggress(dId, orders);
    return NO_ERROR;
}


Error parseCheck(DealerId dId, std::vector<std::string>& tokens, Cmd::Command** result)
{
    if(tokens.size() != 3)
        return INVALID_MESSAGE;

    OrderId oId;
    std::istringstream(tokens[2]) >> oId;

    *result = new Cmd::Check(dId, oId);
    return NO_ERROR;
}

Error parseList(DealerId dId, std::vector<std::string>& tokens, Cmd::Command** result)
{
    if(tokens.size() < 2 || tokens.size() > 5)
        return INVALID_MESSAGE;

    Commodity cmdt = _INVALID_COMMODITY;
    DealerId idToCheck = _INVALID_DEALER;

    if(tokens.size() > 2 && ((cmdt = parseCommodity(tokens[2])) == _INVALID_COMMODITY))
        return UNKNOWN_COMMODITY;

    if(tokens.size() == 4 && ((idToCheck = parseDealerId(tokens[3])) == _INVALID_DEALER))
        return UNKNOWN_DEALER;

    *result = new Cmd::List(dId, cmdt, idToCheck);
    return NO_ERROR;
}

Error parsePost(DealerId dId, std::vector<std::string>& tokens, Cmd::Command** result)
{
    if(tokens.size() != 6)
        return INVALID_MESSAGE;

    double price = 0;
    int amount   = 0;

    Side side    = parseSide(tokens[2]);
    if(side == _INVALID_SIDE)
        return INVALID_MESSAGE;

    Commodity cmdt = _INVALID_COMMODITY;
    if((cmdt = parseCommodity(tokens[3])) == _INVALID_COMMODITY)
        return UNKNOWN_COMMODITY;

    std::istringstream(tokens[4]) >> amount;
    std::istringstream(tokens[5]) >> price;

    *result = new Cmd::Post(dId, side, cmdt, amount, price);
    return NO_ERROR;
}

Error parseRevoke(DealerId dId, std::vector<std::string>& tokens, Cmd::Command** result)
{
    if(tokens.size() != 3)
        return INVALID_MESSAGE;

    OrderId oId;
    std::istringstream(tokens[2]) >> oId;

    *result = new Cmd::Revoke(dId, oId);
    return NO_ERROR;
}

std::vector<std::string> splitTokens(const std::string& stringToSplit)
{
    std::vector<std::string> tokens;
    size_t pos = 0;
    size_t lastPos = 0;

    while ((pos = stringToSplit.find_first_of(" \t", lastPos)) != std::string::npos) {
        tokens.push_back(stringToSplit.substr(lastPos, pos-lastPos));
        lastPos = pos + 1;
    }

    tokens.push_back(stringToSplit.substr(lastPos));
    return tokens;
}


Error parseCommand(const std::string& cmdString, Cmd::Command** result)
{
    if(cmdString.length() > 255)
        return INVALID_MESSAGE;

    std::vector<std::string> tokens = splitTokens(cmdString);
    if(tokens.size() < 2)
        return INVALID_MESSAGE;

    DealerId dId = parseDealerId(tokens[0]);
    if(dId == _INVALID_DEALER)
        return UNKNOWN_DEALER;

    CommandType type = parseCommandType(tokens[1]);

    Error e;
    switch(type) {
        case AGGRESS:
            e = parseAggress(dId, tokens, result);
            break;
        case CHECK:
            e = parseCheck(dId, tokens, result);
            break;
        case LIST:
            e = parseList(dId, tokens, result);
            break;
        case POST:
            e = parsePost(dId, tokens, result);
            break;
        case REVOKE:
            e = parseRevoke(dId, tokens, result);
            break;
        case _INVALID_COMMAND:
            e = INVALID_MESSAGE;
            break;
    }

    return e;
}



