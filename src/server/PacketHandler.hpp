#ifndef _PACKETHANDLER_HPP_
#define _PACKETHANDLER_HPP_

#include <boost/shared_ptr.hpp>
#include <boost/enable_shared_from_this.hpp>

#include "shared/ObjectAccessor.hpp"
#include "shared/packet.hpp"

#include "AsyncServerSocket.hpp"
#include "Database.hpp"

class Session;
typedef boost::shared_ptr<Session> SessionPtr;

class PacketHandler
    : public boost::enable_shared_from_this<PacketHandler>
{
    public:
        static boost::shared_ptr<PacketHandler> create(boost::shared_ptr<AsyncServerSocket> server, Database* database)
        {
            return boost::shared_ptr<PacketHandler>(new PacketHandler(server, database));
        }

        void pongHandler(PacketPtr, SessionPtr);
        void loginHandler(PacketPtr, SessionPtr);
    private:
        PacketHandler(boost::shared_ptr<AsyncServerSocket> server, Database* database)
            : _server(server), m_database(database) {};

        ObjectAccessor<Session>::pointer _sessions;
        boost::shared_ptr<AsyncServerSocket> _server;

        Database* m_database;
};

#endif //_PACKETHANDLER_HPP_
