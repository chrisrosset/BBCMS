#ifndef __PARSER__
#define __PARSER__

#include "enums.h"
#include "command.h"

ParseError parseCommand(const std::string& cmdString, Cmd::Command** result);


#endif // __PARSER__

