#include <boost/cstdint.hpp>

#include "shared/Log.hpp"

#include "Session.hpp"

Session::Session(io_service& ioService) : AsyncSocket(ioService)
{
    _handler = PacketHandler::create();

    _handlers[SMSG_PING]         = &PacketHandler::pingHandler;
    _handlers[SMSG_MESSAGE_SEND] = &PacketHandler::messageHandler;
}
Session::~Session()
{
    //TODO: Fix _handlers memory leak;
}

/**
 * Connect to the server
 */
bool Session::connect(char* host, char* port)
{
    Log::outNotice("Attempting to connect with %s:%s", host, port);
    try
    {
        tcp::resolver resolver(m_socket.get_io_service());
        tcp::resolver::query query(host, port);
        tcp::resolver::iterator endpoint_iterator = resolver.resolve(query);
        tcp::resolver::iterator end;

        boost::system::error_code error = error::host_not_found;

        while (error && endpoint_iterator != end)
        {
            m_socket.close();
            m_socket.connect(*endpoint_iterator++, error);
        }
        if (error)
            throw boost::system::system_error(error);
    }
    catch(boost::system::system_error& e)
    {
        Log::outError("%s (%u)", e.what(), e.code());
        return false;
    }
    Log::outNotice("Connected with %s:%s", host, port);
    readHeader();
    return true;
}

/**
 * Disconnect from the server
 */
void Session::disconnect()
{
    m_socket.get_io_service().post(boost::bind(&Session::disconnectHandler, this));
}

/**
 * Handler for disconnection
 */
void Session::disconnectHandler()
{
    m_socket.close();
}

/**
 * Handler for packets
 */
void Session::handlePacket(boost::shared_ptr<Packet> packet)
{
    if(!_handlers.count(packet->getOpcode()))
    {
        Log::outError("Unknown opcode %#06X", packet->getOpcode());
        return;
    }

    ((*_handler).*_handlers[packet->getOpcode()])(packet, boost::static_pointer_cast<Session, AsyncSocket>(shared_from_this()));
}
