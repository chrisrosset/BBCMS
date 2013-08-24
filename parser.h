#ifndef __PARSER__
#define __PARSER__

#include "enums.h"
#include "command.h"

// Parse command string into a corresponding subclass of Command type
Error parseCommand(const std::string& cmdString, Cmd::Command** result);

#endif // __PARSER__

