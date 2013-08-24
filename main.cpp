#include <iostream>
#include <boost/shared_ptr.hpp>

#include "enums.h"
#include "command.h"
#include "parser.h"
#include "orderstore.h"

void despatchCommand(OrderStore& store, Cmd::Command* ptr)
{
    if(Cmd::Check * c = dynamic_cast<Cmd::Check*>(ptr)) {
        std::cout << "CHECK COMMAND"<< std::endl;
    } else if(Cmd::List * c = dynamic_cast<Cmd::List*>(ptr)) {

        std::vector<std::pair<OrderId, Cmd::Post> > result;

        Error e = store.list(*c, result);
        if (e == NO_ERROR) {
            for(int i = 0; i < result.size(); ++i) {
                std::cout << result[i].first << " "
                          << result[i].second.toString() 
                          << std::endl;
            }
        } else {
            std::cout << "Error in despatchCommand for Cmd::List" << std::endl;
        }

    } else if(Cmd::Post * c = dynamic_cast<Cmd::Post*>(ptr)) {

        OrderId id = -1;
        Error e = store.post(*c, id);
        if(e == NO_ERROR) {
            std::cout << id << " "
                      << c->toString() 
                      << " HAS BEEN POSTED"
                      << std::endl;
        } else {
            std::cout << "THERE BE AN ERROR IN THIS BIATCH" << std::endl;
        }

    } else if(Cmd::Revoke * c = dynamic_cast<Cmd::Revoke*>(ptr)) {
        
        switch(store.revoke(*c)) {
            case UNKNOWN_ORDER:
                std::cout << "UNKNOWN_ORDER";
                break;
            case UNAUTHORIZED:
                std::cout << "UNAUTHORIZED";
                break;
            case NO_ERROR:
                std::cout << c->orderId << " HAS BEEN REVOKED" << std::endl;
                break;
        }
        
    } else {
        std::cout << "UNIMPLEMENTED COMMAND"<< std::endl;
    }
}

int main(int argc, char* argv[])
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






























