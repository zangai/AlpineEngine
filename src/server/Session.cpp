#include "shared/Log.hpp"

#include "Session.hpp"
#include "AsyncServerSocket.hpp"

Session::Session(io_service& ioService, boost::shared_ptr<AsyncServerSocket> server, boost::shared_ptr<PacketHandler> handler, std::map<uint16_t, handlerPointer>* handlers)
    : AsyncSocket(ioService), m_user(), _server(server), _handler(handler), _handlers(handlers)
{}

/**
 * Initiates various things in the session such as starting a read call for the first packet header
 */
void Session::start()
{
    readHeader();
}

/**
 * Handler for any incoming packets
 */
void Session::handlePacket(boost::shared_ptr<Packet> packet)
{
    if(!_handlers->count(packet->getOpcode()))
    {
        Log::outError("Unknown opcode %#06X", packet->getOpcode());
        return;
    }

    ((*_handler).*(*_handlers)[packet->getOpcode()])(packet, boost::static_pointer_cast<Session, AsyncSocket>(shared_from_this()));
}

/**
 * Handler for disconnection
 */
void Session::disconnectHandler()
{
    _server->disconnectHandler(static_pointer_cast<Session, AsyncSocket>(shared_from_this()));
}
