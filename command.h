#ifndef __COMMAND__
#define __COMMAND__

#include <vector>
#include "enums.h"


typedef int OrderId;

namespace Cmd
{

struct Command
{
    DealerId dealerId;
    virtual ~Command() {};

protected:
    Command(DealerId dId) : dealerId(dId) {};
};

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
};

struct Revoke : Command
{
    const OrderId orderId;

    Revoke(DealerId dId, OrderId oId) : Command(dId), orderId(oId) {};
};

struct Check : Command
{
    const OrderId orderId;

    Check(DealerId dId, OrderId oId) : Command(dId), orderId(oId) {};
};

struct List : Command
{
    const Commodity commodity;
    const DealerId  dId;

    List(DealerId clientId, Commodity c, DealerId listId)
        : Command(clientId), commodity(c), dId(listId) {};
};

struct Aggress : Command
{
    const std::vector<OrderId> orderIds;
    const std::vector<int> orderAmounts;

    Aggress(DealerId dId, std::vector<OrderId> oIds, std::vector<int> oAmts)
        : Command(dId), orderIds(oIds), orderAmounts(oAmts) {};
};

} // end namespace Cmd

#endif // __COMMAND__
