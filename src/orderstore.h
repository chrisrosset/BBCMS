#ifndef __ORDERSTORE__
#define __ORDERSTORE__


#include <boost/unordered_map.hpp>
#include "command.h"

// OrderStore model class
class OrderStore
{
public:
    OrderStore();

    Error aggress(const Cmd::Aggress& cmd, std::vector<Cmd::Post>& result);
    Error check(const Cmd::Check&, Cmd::Post& order);
    Error list(const Cmd::List& cmd,
            std::vector<std::pair<OrderId, Cmd::Post> >& result);
    Error post(Cmd::Post cmd, OrderId& id);
    Error revoke(const Cmd::Revoke& cmd);

private:
    boost::unordered_map<OrderId, Cmd::Post> store;
    OrderId counter;
};


#endif

