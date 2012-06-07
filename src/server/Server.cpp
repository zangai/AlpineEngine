#include "Server.hpp"

void Server::launch(uint16_t port)
{
    m_socket = AsyncServerSocket::create(port, m_ioService, this);
    m_socket->listen();
    Log::outNotice("Started listening on port %u", m_socket->getPort());

    m_database->connect();
    m_ioService.run();
}