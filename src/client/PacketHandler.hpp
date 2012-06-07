#ifndef _PACKETHANDLER_HPP_
#define _PACKETHANDLER_HPP_

#include "shared/packet.hpp"

#include <boost/shared_ptr.hpp>
#include <boost/enable_shared_from_this.hpp>

class Session;

class PacketHandler
    : public boost::enable_shared_from_this<PacketHandler>
{
    public:
        static boost::shared_ptr<PacketHandler> create()
        {
            return boost::shared_ptr<PacketHandler>(new PacketHandler());
        }

        void pingHandler(boost::shared_ptr<Packet> packet, boost::shared_ptr<Session> session);
        void messageHandler(boost::shared_ptr<Packet> packet, boost::shared_ptr<Session> session);
    private:
        PacketHandler() {};
};

#endif //_PACKETHANDLER_HPP_
