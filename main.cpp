#include <iostream>

#include "enums.h"
#include "command.h"
#include "parser.h"
#include "orderstore.h"

void despatchCommand(OrderStore& store, Cmd::Command* ptr)
{
    if(Cmd::Check * c = dynamic_cast<Cmd::Check*>(ptr)) {
        std::cout << "CHECK COMMAND"<< std::endl;
    } else if(Cmd::List * c = dynamic_cast<Cmd::List*>(ptr)) {
        ;
    } else if(Cmd::Post * c = dynamic_cast<Cmd::Post*>(ptr)) {
        OrderId id = -1;
        Error e = store.post(*c, id);
        if(e == NO_ERROR) {
            std::cout << id << " "
                      << dealerIdToString(c->dealerId) << " "
                      << sideToString(c->side) << " "
                      << commodityToString(c->commodity) << " "
                      << c->amount << " "
                      << c->price << " HAS BEEN POSTED"
                      << std::endl;
        } else {
            std::cout << "THERE BE AN ERROR IN THIS BIATCH" << std::endl;
        }
    } else if(Cmd::Revoke * c = dynamic_cast<Cmd::Revoke*>(ptr)) {
        std::cout << "REVOKE COMMAND"<< std::endl;
    } else {
        std::cout << "UNIMPLEMENTED COMMAND"<< std::endl;
    }
}

int main()
{
    OrderStore store;
    std::string input;

    while(1) {
        std::getline(std::cin, input);
        if(input.length() == 0)
            return 0;


        Cmd::Command* ptr = 0;

        // parse and perform error detection
        switch( parseCommand(input, &ptr) ) {
            case INVALID_MESSAGE:
                std::cerr << "Invalid message." << std::endl;
                break;
            case UNKNOWN_DEALER:
                std::cerr << "Unknown dealer." << std::endl;
                break;
            case NO_ERROR:
                despatchCommand(store, ptr);
        }

        if(ptr != 0)
            delete ptr;
    }

}






























