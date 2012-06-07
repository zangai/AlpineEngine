#include "shared/Log.hpp"

#include "PacketHandler.hpp"
#include "Session.hpp"

void PacketHandler::messageHandler(boost::shared_ptr<Packet> packet, boost::shared_ptr<Session> session)
{
    Log::outDebug("Received SMSG_MESSAGE_SEND");
    cout << packet->read<string>() << ": ";
    cout << packet->read<string>() << endl;
}
