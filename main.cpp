#include <iostream>

#include "enums.h"
#include "command.h"
#include "parser.h"


int main()
{
    Cmd::Post p(JPM, BUY, GOLD, 1000, 6.66);

    std::cout << p.price << std::endl;
    Cmd::Command* ptr;

    std::cout << ptr << std::endl;
    std::string testStr("DB CHECK 1");

    parseCommand(testStr, &ptr);
    std::cout << ptr->dealerId << std::endl;


}

