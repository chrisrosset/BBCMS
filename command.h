#ifndef __ORDER__
#define __ORDER__

#include <vector>
#include "enums.h"


typedef unsigned int OrderId;

namespace Cmd
{

struct Command
{
    const DealerId dealerId;

protected:
    Command(DealerId dId) : dealerId(dId) {};
};

struct Post : Command
{
    const Side side;
    const Commodity commodity;
    const int amount;
    const double price;

    Post(DealerId dId, Side s, Commodity cmdt, int amt, double p)
        : Command(dId), side(s), commodity(cmdt), amount(amt), price(p) {};
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

#endif // __ORDER__
