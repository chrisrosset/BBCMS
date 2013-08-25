#ifndef __OUTPUTBUILDER__
#define __OUTPUTBUILDER__

#include <string>
#include <vector>

#include "enums.h"
#include "command.h"


std::string buildAggressResponse(const std::vector<Cmd::Post>& result);
std::string buildCheckResponse(const Cmd::Check& c, const Cmd::Post& p);
std::string buildListResponse(std::vector<std::pair<OrderId, Cmd::Post> > result);
std::string buildPostResponse(OrderId id, const Cmd::Post& c);
std::string buildRevokeResponse(OrderId orderId);

#endif // __OUTPUTBUILDER__
