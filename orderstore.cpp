#include "command.h"
#include "orderstore.h"

OrderStore::OrderStore()
    : counter(0)
{
}

//Error OrderStore::aggress(Cmd::Aggress);
//Error OrderStore::check(Cmd::Check);
Error OrderStore::list(const Cmd::List& cmd, std::vector<Cmd::Post>& result)
{
    for(boost::unordered_map<OrderId, Cmd::Post>::iterator it = store.begin();
            it != store.end(); ++it) {

        Cmd::Post cur = it->second;

        if((cmd.commodity == _INVALID_COMMODITY && cmd.dealerId == _INVALID_DEALER) ||
           (cmd.commodity == cur.commodity && cmd.dealerId == _INVALID_DEALER) ||
           (cmd.commodity == cur.commodity && cmd.dealerId == cur.dealerId)) {
            result.push_back(cur);
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

    store.erase(cmd.dealerId);
    return NO_ERROR;
}






















































































