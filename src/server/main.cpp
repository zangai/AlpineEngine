#include <iostream>

#include <boost/lambda/lambda.hpp>
#include <boost/asio.hpp>

#include "shared/debug.hpp"
#include "shared/opcode.hpp"
#include "shared/Log.hpp"

#include "AsyncServerSocket.hpp"
#include "Database.hpp"
#include "Server.hpp"

using namespace std;
using namespace boost::asio;
using boost::asio::ip::tcp;

//TODO Change all defines to not have starting/ending underscores as it's apparently reserved

int main(int argc, char *argv[])
{
    cout << "################################" << endl;
    cout << "#         Alpine Engine        #" << endl;
    cout << "#      Project PACKETSTORM     #" << endl;
    cout << "# Internal Development Release #" << endl;
    cout << "################################" << endl;

    Log::setLogLevel(LOG_LEVEL_DEBUG);

    if (argc != 2)
    {
        std::cerr << "Usage: alpine-server <port>" << std::endl;
        return 1;
    }

    Server server;
    server.launch(atoi(argv[1]));

    return 0;
}
