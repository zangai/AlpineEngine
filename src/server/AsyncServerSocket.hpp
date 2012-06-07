#ifndef _ASYNCSERVERSOCKET_HPP_
#define _ASYNCSERVERSOCKET_HPP_

#include <iostream>
#include <set>

#include <boost/shared_ptr.hpp>
#include <boost/enable_shared_from_this.hpp>
#include <boost/asio.hpp>
#include <boost/cstdint.hpp>

#include "shared/packet.hpp"

class Session;
class Server;

using namespace boost::asio;
using namespace boost;
using namespace std;

using boost::asio::ip::tcp;

/**
 * Asynchronous server class
 * Handles the client connections and will route received data.
 */
class AsyncServerSocket
    : public boost::enable_shared_from_this<AsyncServerSocket>
{
    public:


        static boost::shared_ptr<AsyncServerSocket> create(uint16_t port, io_service& ioService, Server* server)
        {
            return boost::shared_ptr<AsyncServerSocket>(new AsyncServerSocket(port, ioService, server));
        }

        uint16_t getPort() { return m_port; }

        void listen();
        void sendToAll(boost::shared_ptr<Packet> packet);
        void disconnectHandler(boost::shared_ptr<Session> session);

        void acceptHandler(boost::shared_ptr<Session> session, const system::error_code& error);
    private:
        AsyncServerSocket(uint16_t port, io_service& ioService, Server* server)
            : m_port(port), m_acceptor(ioService, tcp::endpoint(tcp::v4(), m_port)), _sessionCount(0), m_server(server) {}

        uint16_t m_port;
        tcp::acceptor m_acceptor;
        std::set< boost::shared_ptr<Session> > _sessions;
        uint32_t _sessionCount;
        Server* m_server;
};

typedef boost::shared_ptr<AsyncServerSocket> AsyncServerSocketPtr;

#endif // _ASYNCSERVERSOCKET_HPP_
