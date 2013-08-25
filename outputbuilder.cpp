#include "outputbuilder.h"

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

    if(p.amount > 0) {
        ss << p.toString();
   } else {
        ss << "HAS BEEN FILLED";
   }

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
