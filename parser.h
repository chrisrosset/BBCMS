#ifndef __PARSER__
#define __PARSER__

#include "enums.h"
#include "command.h"

Error parseCommand(const std::string& cmdString, Cmd::Command** result);


#endif // __PARSER__

