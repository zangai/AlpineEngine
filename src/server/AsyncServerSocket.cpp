#include "AsyncServerSocket.hpp"
#include "Session.hpp"
#include "Server.hpp"

#include "shared/Log.hpp"

#include "boost/foreach.hpp"

/**
 * Start listening for connections
 * Executed when starting or after accepting a connection.
 */
void AsyncServerSocket::listen()
{

    // Get a pointer to a new session object
    boost::shared_ptr<Session> session = Session::create(m_acceptor.io_service(), shared_from_this(), m_server->_handler, m_server->_handlers);

    // Start an asynchronous accept request that will call acceptHandler
    m_acceptor.async_accept(session->getSocket(), boost::bind(&AsyncServerSocket::acceptHandler, this, session, boost::asio::placeholders::error));
}

void AsyncServerSocket::acceptHandler(boost::shared_ptr<Session> session, const system::error_code& error)
{
    // Todo: Make this useful
    if(error)
        return;

    Log::outNotice("Accepted connection from %s", session->getSocket().remote_endpoint().address().to_string().c_str());
    ++_sessionCount;
    _sessions.insert(session);

    // Initiates the session
    session->start();

    // Listen for a new connection
    listen();
}
void AsyncServerSocket::disconnectHandler(boost::shared_ptr<Session> session)
{
    Log::outNotice("Client disconnected, deleting reference");
    --_sessionCount;
    _sessions.erase(session);
}

/**
 * Send a packet to all connected clients
 */
void AsyncServerSocket::sendToAll(boost::shared_ptr<Packet> packet)
{
    BOOST_FOREACH(boost::shared_ptr<Session> session, _sessions)
        session->queue(packet);
}
