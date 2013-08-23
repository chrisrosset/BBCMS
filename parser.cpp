#include <sstream>
#include <string>
#include <vector>

#include <iostream>

#include "parser.h"
#include "enums.h"
#include "command.h"

ParseError parseCheck(DealerId dId, std::vector<std::string>& tokens, Cmd::Command** result)
{
    if(tokens.size() != 3)
        return INVALID_MESSAGE;

    OrderId oId;
    std::istringstream(tokens[2]) >> oId;

    *result = new Cmd::Check(dId, oId);
}

DealerId parseDealerId(std::string& input)
{
    DealerId result = _INVALID_DEALER;

    if     (input == "DB"  ) { result = DB   ; }
    else if(input == "JPM" ) { result = JPM  ; }
    else if(input == "UBS" ) { result = UBS  ; }
    else if(input == "RBC" ) { result = RBC  ; }
    else if(input == "BARX") { result = BARX ; }
    else if(input == "MS " ) { result = MS   ; }
    else if(input == "CITI") { result = CITI ; }
    else if(input == "BOFA") { result = BOFA ; }
    else if(input == "RBS" ) { result = RBS  ; }
    else if(input == "HSBC") { result = HSBC ; }

    return result;
}

CommandType parseCommandType(std::string& input)
{
    CommandType result;

    if     (input == "LIST"  ) { result = LIST   ; }
    else if(input == "AGGRESS" ) { result = AGGRESS  ; }
    else if(input == "CHECK" ) { result = CHECK  ; }
    else if(input == "REVOKE" ) { result = REVOKE; }
    else if(input == "POST") { result = POST ; }
    else { result = _INVALID_COMMAND; }

    return result;
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


ParseError parseCommand(const std::string& cmdString, Cmd::Command** result)
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
    if(type == _INVALID_COMMAND)
        return INVALID_MESSAGE;

    switch(type) {
        //case AGGRESS:

        //    break;
        case CHECK:
            std::cout << "CHECK ONE TWO" << std::endl;
            return parseCheck(dId, tokens, result);
            break;
        //case LIST:

        //    break;
        //case POST:

        //    break;
        //case REVOKE:

        //    break;
    }
}



