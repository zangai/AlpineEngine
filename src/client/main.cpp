#include <iostream>

#include "shared/debug.hpp"
#include "shared/packet.hpp"
#include "shared/opcode.hpp"
#include "shared/Log.hpp"
#include "shared/Flags.hpp"

#include "SFML/System.hpp"
#include "SFML/Window.hpp"

#include "boost/asio.hpp"
#include <boost/thread.hpp>

#include "Session.hpp"
#include "GFX.hpp"

using namespace std;
//using namespace boost::asio;
//using boost::asio::ip::tcp;

int main(int argc, char* argv[])
{
    cout << "################################" << endl;
    cout << "#         Alpine Engine        #" << endl;
    cout << "#      Project PACKETSTORM     #" << endl;
    cout << "# Internal Development Release #" << endl;
    cout << "################################" << endl;

    Log::setLogLevel(LOG_LEVEL_DEBUG);
    Log::setFilters(LOG_FILTER_MEMLEAK | LOG_FILTER_INPUT);

    try
    {
        /*if (argc != 4)
        {
            std::cerr << "Usage: client <nickname> <host> <port>" << std::endl;
            return 1;
        }*/

        //io_service ioService;
        //io_service::work* idleWork = new io_service::work(ioService);
        //boost::thread threadIOService(boost::bind(&boost::asio::io_service::run, &ioService));

        GFX gfxApp;
        gfxApp.OnExecute();

        /*
        Flags flagger(192);
        if(flagger == 64)
            std::cout << "64 is true" << std::endl;
        if(flagger == 128)
            std::cout << "128 is true" << std::endl;

        flagger += 32;
        flagger -= 64;

        if(flagger != 64)
            std::cout << "64 is false" << std::endl;
        if(flagger == 32)
            std::cout << "32 is true" << std::endl;

        if(flagger == 128 | 32)
            std::cout << "160 is true" << std::endl;

        std::cout << flagger.getData();
        */

        /*
        boost::shared_ptr<Session> session = Session::create(ioService);
        if(!session->connect(argv[2], argv[3]))
            return 0;

        // Send Nickname
        boost::shared_ptr<Packet> packet = Packet::create();
        packet->setOpcode(CMSG_NICKNAME_SEND);
        packet->add<string>(std::string(argv[1]));
        session->queue(packet);
        packet.reset();

        char message[256];

        while(std::cin.getline(message,256))
        {
            boost::shared_ptr<Packet> packet = Packet::create();
            packet->setOpcode(CMSG_MESSAGE_SEND);
            packet->add<string>(std::string(message));
            session->queue(packet);
            packet.reset();
        }*/

        //threadIOService.join();
    }
    catch (std::exception& e)
    {
        Log::outError("%s (%u)", e.what());
    }

    return 0;
}