#include <iostream>
#include <istream>
#include <boost/shared_ptr.hpp>

#include "enums.h"
#include "command.h"
#include "parser.h"
#include "orderstore.h"

// functions for providing output Views

std::string buildAggressResponse(const std::vector<Cmd::Post>& result)
{
    std::stringstream ss;
    for(std::vector<Cmd::Post>::const_iterator it = result.begin();
            it != result.end(); ++it) {
        ss << (it->side == BUY ? "BOUGHT" : "SOLD") << " "
           << it->amount << " "
           << commodityToString(it->commodity) << " @ "
           << it->price << " FROM "
           << dealerIdToString(it->dealerId) << std::endl;
    }

    return ss.str();
}

std::string buildCheckResponse(const Cmd::Check& c, const Cmd::Post& p)
{
    std::stringstream ss;
    ss << c.orderId << " ";

    if(p.amount > 0)
        ss << p.toString();
    else
        ss << "HAS BEEN FILLED";

    ss << std::endl;
    return ss.str();
}

std::string buildListResponse(std::vector<std::pair<OrderId, Cmd::Post> > result)
{
    std::stringstream ss;
    for(unsigned int i = 0; i < result.size(); ++i) {
        ss << result[i].first << " "
           << result[i].second.toString()
           << std::endl;
    }
    return ss.str();
}

std::string buildPostResponse(OrderId id, const Cmd::Post& c)
{
    std::stringstream ss;
    ss << id << " " << c.toString() << " HAS BEEN POSTED" << std::endl;
    return ss.str();
}

std::string buildRevokeResponse(OrderId orderId)
{
    std::stringstream ss;
    ss << orderId << " HAS BEEN REVOKED" << std::endl;
    return ss.str();
}

////

void despatchCommand(OrderStore& store, Cmd::Command* ptr)
{
    if(Cmd::Aggress * c = dynamic_cast<Cmd::Aggress*>(ptr)) {
        std::vector<Cmd::Post> result;
        Error e = store.aggress(*c, result);

        if(e == NO_ERROR) {
            std::cout << buildAggressResponse(result);
        } else {
            std::cout << errorToString(e) << std::endl;
        }
    } else if(Cmd::Check * c = dynamic_cast<Cmd::Check*>(ptr)) {
        Cmd::Post p;
        Error e = store.check(*c, p);

        if(e == NO_ERROR) {
            std::cout << buildCheckResponse(*c, p);
        } else {
            std::cout << errorToString(e) << std::endl;
        }
    } else if(Cmd::List * c = dynamic_cast<Cmd::List*>(ptr)) {

        std::vector<std::pair<OrderId, Cmd::Post> > result;
        Error e = store.list(*c, result);

        if (e == NO_ERROR) {
            std::cout << buildListResponse(result);
        } else {
            std::cout << errorToString(e) << std::endl;
        }

    } else if(Cmd::Post * c = dynamic_cast<Cmd::Post*>(ptr)) {
        OrderId id = -1;
        Error e = store.post(*c, id);
        if(e == NO_ERROR) {
            std::cout << buildPostResponse(id, *c);
        } else {
            std::cout << errorToString(e) << std::endl;
        }

    } else if(Cmd::Revoke * c = dynamic_cast<Cmd::Revoke*>(ptr)) {
        Error e = store.revoke(*c);

        if(e == NO_ERROR) {
            std::cout << buildRevokeResponse(c->orderId);
        } else {
            std::cout << errorToString(e) << std::endl;
        }
    }
}


int main(int argc, char* argv[])
{
    OrderStore store;
    std::string temp;

    while(true) {
        char cstr[257];
        std::cin.get(cstr, 257);

        std::string input = cstr;
        std::cout << input << std::endl;
        if(input.length() > 255) {
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cerr << "INVALID MESSAGE" << std::endl;
        } else if(input.length() == 0) {
            return 0;
        }

        std::getline(std::cin, temp);

        Cmd::Command* ptr = 0;

        // parse and perform error detection
        Error e = parseCommand(input, &ptr);
        if(e == NO_ERROR) {
            despatchCommand(store, ptr);
        } else {
            std::cout << errorToString(e) << std::endl;
        }

        if(ptr != 0)
            delete ptr;
    }
}

