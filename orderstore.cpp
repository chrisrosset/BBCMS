#include <vector>
#include <boost/unordered_map.hpp>

#include "command.h"
#include "orderstore.h"

OrderStore::OrderStore()
    : counter(0)
{
}


Error OrderStore::aggress(const Cmd::Aggress& cmd, std::vector<Cmd::Post>& result)
{
    boost::unordered_map<OrderId, Cmd::Post> temp = store;

    for(std::vector<std::pair<OrderId, int> >::const_iterator it = cmd.orders.begin();
            it != cmd.orders.end(); ++it) {

        // check if the order id is valid
        if(temp.find(it->first) == temp.end())
            return UNKNOWN_ORDER;

        Cmd::Post *post = &temp.find(it->first)->second;

        // aggress only if there's enough left in the order to progress
        if(post->amount - it->second >= 0) {
            post->amount -= it->second;
            result.push_back(Cmd::Post(post->dealerId,
                                       post->side,
                                       post->commodity,
                                       it->second,
                                       post->price));
        } else {
            return INVALID_MESSAGE;
        }
    }

    store = temp;
    return NO_ERROR;
}



Error OrderStore::check(const Cmd::Check& cmd, Cmd::Post& order)
{
    // if id does not exist
    if(store.find(cmd.orderId) == store.end())
        return UNKNOWN_ORDER;

    // check if the transaction was ordered by the original poster
    if(cmd.dealerId != store[cmd.orderId].dealerId)
        return UNAUTHORIZED;

    order = store[cmd.orderId];
    return NO_ERROR;
}


Error OrderStore::list(const Cmd::List& cmd,
                       std::vector<std::pair<OrderId, Cmd::Post> >& result)
{
    for(boost::unordered_map<OrderId, Cmd::Post>::iterator it = store.begin();
            it != store.end(); ++it) {

        Cmd::Post cur = it->second;
        if((cmd.commodityFilter == _INVALID_COMMODITY
            && cmd.dealerFilter == _INVALID_DEALER) ||
           (cmd.commodityFilter == cur.commodity
            && cmd.dealerFilter == _INVALID_DEALER) ||
           (cmd.commodityFilter == cur.commodity
            && cmd.dealerFilter == cur.dealerId)) {

            result.push_back(std::make_pair(it->first, cur));
        }
    }

    return NO_ERROR;
}


Error OrderStore::post(Cmd::Post cmd, OrderId& id)
{
    id = ++counter;
    std::pair<OrderId, Cmd::Post> x(id, cmd);
    store.insert(x);
    return NO_ERROR;
}


Error OrderStore::revoke(const Cmd::Revoke& cmd)
{
    // if id does not exist
    if(store.find(cmd.orderId) == store.end())
        return UNKNOWN_ORDER;

    // check if the transaction was ordered by the original poster
    if(cmd.dealerId != store[cmd.orderId].dealerId)
        return UNAUTHORIZED;

    store.erase(cmd.orderId);
    return NO_ERROR;
}
