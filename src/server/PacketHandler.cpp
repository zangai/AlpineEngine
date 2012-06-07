#include "shared/Log.hpp"

#include "PacketHandler.hpp"
#include "Session.hpp"

void PacketHandler::pongHandler(boost::shared_ptr<Packet> packet, boost::shared_ptr<Session> session)
{
    Log::outDebug("Received CMSG_PONG");
}
