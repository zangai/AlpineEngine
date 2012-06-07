#ifndef _SERVER_HPP_
#define	_SERVER_HPP_

#include "Session.hpp"
#include "AsyncServerSocket.hpp"
#include "Database.hpp"

class Server
{
    public:
        Server()
        {
            m_database = new Database("localhost", "root", "test", "alpine");

            _handler = PacketHandler::create(m_socket, m_database);
            _handlers = new std::map<uint16_t, handlerPointer>();

            (*_handlers)[CMSG_PONG]          = &PacketHandler::pongHandler;
            (*_handlers)[CMSG_SEND_LOGIN]    = &PacketHandler::loginHandler;
        }
        ~Server()
        {
            delete m_database;
            delete _handlers;
        }

        void launch(uint16_t port);

        boost::shared_ptr<PacketHandler> _handler;
        std::map<uint16_t, handlerPointer>* _handlers;

    private:
        Database* m_database;
        AsyncServerSocketPtr m_socket;
        boost::asio::io_service m_ioService;
};

#endif // _SERVER_HPP_

