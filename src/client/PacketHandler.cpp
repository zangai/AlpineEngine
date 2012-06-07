#include "shared/Log.hpp"

#include "PacketHandler.hpp"
#include "Session.hpp"

void PacketHandler::pingHandler(PacketPtr packet, SessionPtr session)
{
    Log::outDebug("Received SMSG_PING");
    packet->setOpcode(CMSG_PONG);
    session->queue(packet);
}
