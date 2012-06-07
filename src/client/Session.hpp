#ifndef _SESSION_HPP_
#define _SESSION_HPP_

#include "shared/AsyncSocket.hpp"
#include "shared/opcode.hpp"
#include "PacketHandler.hpp"

using namespace boost::asio;
using namespace boost;
using namespace std;

using boost::asio::ip::tcp;

class Session;

typedef void (PacketHandler::*handlerPointer)(boost::shared_ptr<Packet>, boost::shared_ptr<Session>);

/**
 * Client session, contains references to the socket and various user related data
 */
class Session
    : public AsyncSocket
{
    public:
        tcp::socket& getSocket() { return m_socket; }

        static boost::shared_ptr<Session> create(io_service& ioService)
        {
            return boost::shared_ptr<Session>(new Session(ioService));
        }

        ~Session();
        bool connect(char* host, char* port);
        void disconnect();
    private:
        void handlePacket(boost::shared_ptr<Packet> packet);
        void disconnectHandler();

        Session(io_service& ioService);

        boost::shared_ptr<PacketHandler> _handler;
        std::map<uint16_t, handlerPointer> _handlers;
};

#endif //_SESSION_HPP_
