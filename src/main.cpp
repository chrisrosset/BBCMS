#include <iostream>
#include <istream>
#include <boost/shared_ptr.hpp>
#include <boost/asio.hpp>

#include "enums.h"
#include "command.h"
#include "parser.h"
#include "orderstore.h"
#include "outputbuilder.h"


////

// Commodity Market System Controller - coordinate parsed input
// and provide output in the form of system messages
std::string despatchCommand(OrderStore& store, Cmd::Command* ptr)
{
    std::stringstream ss;
    if(Cmd::Aggress * c = dynamic_cast<Cmd::Aggress*>(ptr)) {
        std::vector<Cmd::Post> result;
        Error e = store.aggress(*c, result);

        if(e == NO_ERROR) {
            ss << buildAggressResponse(result);
        } else {
            ss << errorToString(e) << std::endl;
        }
    } else if(Cmd::Check * c = dynamic_cast<Cmd::Check*>(ptr)) {
        Cmd::Post p;
        Error e = store.check(*c, p);

        if(e == NO_ERROR) {
            ss << buildCheckResponse(*c, p);
        } else {
            ss << errorToString(e) << std::endl;
        }
    } else if(Cmd::List * c = dynamic_cast<Cmd::List*>(ptr)) {

        std::vector<std::pair<OrderId, Cmd::Post> > result;
        Error e = store.list(*c, result);

        if (e == NO_ERROR) {
            ss << buildListResponse(result);
        } else {
            ss << errorToString(e) << std::endl;
        }
    } else if(Cmd::Post * c = dynamic_cast<Cmd::Post*>(ptr)) {
        OrderId id = -1;
        Error e = store.post(*c, id);

        if(e == NO_ERROR) {
            ss << buildPostResponse(id, *c);
        } else {
            ss << errorToString(e) << std::endl;
        }
    } else if(Cmd::Revoke * c = dynamic_cast<Cmd::Revoke*>(ptr)) {
        Error e = store.revoke(*c);

        if(e == NO_ERROR) {
            ss << buildRevokeResponse(c->orderId);
        } else {
            ss << errorToString(e) << std::endl;
        }
    }

    return ss.str();
}


int controlTcp(unsigned int port)
{
    if(port > 65535) {
        std::cerr << "Invalid port number" << std::endl;
        return 1;
    }

    try {
        using boost::asio::ip::tcp;

        boost::asio::io_service io_service;
        tcp::endpoint endpoint(tcp::v4(), port);
        tcp::acceptor acceptor(io_service, endpoint);

        tcp::iostream stream;
        boost::system::error_code ec;
        acceptor.accept(*stream.rdbuf(), ec);

        OrderStore store;
        std::string temp;

        while(true) {
            char cstr[257] = "";
            stream.get(cstr, 257);

            std::string input = cstr;
            stream << input << std::endl;
            if(stream.eof() || 0 == input.length()) {
                return 0;
            } else if(input.length() > 255) {
                // proceed to ignore the rest of the invalid long msg
                stream.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                stream << "INVALID_MESSAGE" << std::endl;
            }

            std::getline(stream, temp);

            // parse and perform error detection
            Cmd::Command* ptr = 0;
            Error e = parseCommand(input, &ptr);
            if(e == NO_ERROR) {
                std::string a = despatchCommand(store, ptr);
                stream << a;
                std::cout << a;
            } else {
                stream << errorToString(e) << std::endl;
            }

            if(ptr != 0)
                delete ptr;
        }
    } catch(std::exception& e) {
        std::cerr << e.what() << std::endl;
        return 1;
    }
}

int controlStdio()
{
    OrderStore store;
    std::string temp;

    while(true) {
        char cstr[257] = "";
        stream.get(cstr, 257);

        std::string input = cstr;
        stream << input << std::endl;
        if(stream.eof() || 0 == input.length()) {
            return 0;
        } else if(input.length() > 255) {
            // proceed to ignore the rest of the invalid long msg
            stream.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            stream << "INVALID_MESSAGE" << std::endl;
        }

        std::getline(stream, temp);

        // parse and perform error detection
        Cmd::Command* ptr = 0;
        Error e = parseCommand(input, &ptr);
        if(e == NO_ERROR) {
            std::string a = despatchCommand(store, ptr);
            stream << a;
            std::cout << a;
        } else {
            stream << errorToString(e) << std::endl;
        }

        if(ptr != 0)
            delete ptr;
    }
}


int main(int argc, char* argv[])
{
    if (argc == 2 && 0 == strcmp(argv[1], "base")) {
        return controlStdio();
    } else if (argc == 3 && 0 == strcmp(argv[1], "ext1")) {
        int port = strtol(argv[2], 0, 10);
        return controlTcp(port);
    } else if (argc == 3 && 0 == strcmp(argv[1], "ext2")) {
        return 1;
    } else {
        std::cout << "BBCMS help" << std::endl
                  << std::endl
                  << "\t ./cms               - display this message\n"
                  << "\t ./cms base          - run with stdio as IO\n"
                  << "\t ./cms ext1 <port>   - run with tcp on <port> as IO\n"
                  << "\t ./cms ext2 <port>   - not implemented\n";
        return 0;
    }
}

