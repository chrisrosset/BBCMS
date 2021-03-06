#ifndef __COMMAND__
#define __COMMAND__

#include <vector>
#include "enums.h"
#include <sstream>

typedef int OrderId;

// Cmd namespace with command definitions
namespace Cmd
{

// Base Command struct inherited by all types of commands
struct Command
{
    DealerId dealerId;
    virtual ~Command() {};

protected:
    Command(DealerId dId) : dealerId(dId) {};
};

// Post command
struct Post : Command
{
    Side side;
    Commodity commodity;
    int amount;
    double price;

    Post()
        : Command(_INVALID_DEALER), side(BUY), commodity(_INVALID_COMMODITY),
            amount(0), price(0) {};
    Post(DealerId dId, Side s, Commodity cmdt, int amt, double p)
        : Command(dId), side(s), commodity(cmdt), amount(amt), price(p) {};
    Post(const Post& o)
        : Command(o.dealerId), side(o.side), commodity(o.commodity),
            amount(o.amount), price(o.price) {};

    std::string toString() const {
        std::stringstream ss;
        ss << dealerIdToString(dealerId) << " "
           << sideToString(side) << " "
           << commodityToString(commodity) << " "
           << amount << " "
           << price;
        return ss.str();
    }
};

// Revoke command
struct Revoke : Command
{
    const OrderId orderId;

    Revoke(DealerId dId, OrderId oId) : Command(dId), orderId(oId) {};
};

// Check command
struct Check : Command
{
    const OrderId orderId;

    Check(DealerId dId, OrderId oId) : Command(dId), orderId(oId) {};
};

// List command
struct List : Command
{
    const Commodity commodityFilter;
    const DealerId  dealerFilter;

    List(DealerId clientId, Commodity c, DealerId listId)
        : Command(clientId), commodityFilter(c), dealerFilter(listId) {};
};

// Aggress command
struct Aggress : Command
{
    const std::vector<std::pair<OrderId, int> > orders;

    Aggress(DealerId dId, std::vector<std::pair<OrderId, int> > o)
        : Command(dId), orders(o) {};
};

} // end namespace Cmd

#endif // __COMMAND__
