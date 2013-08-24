#ifndef __ORDERSTORE__
#define __ORDERSTORE__


#include <boost/unordered_map.hpp>
#include "command.h"


class OrderStore
{
public:
    OrderStore();

    //Error aggress(Cmd::Aggress);
    //Error check(Cmd::Check);
    Error list(const Cmd::List& cmd, std::vector<Cmd::Post>&);
    Error post(Cmd::Post cmd, OrderId& id);
    Error revoke(const Cmd::Revoke& cmd);

private:
    boost::unordered_map<OrderId, Cmd::Post> store;
    OrderId counter;
};


#endif

