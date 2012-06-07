#ifndef _ASYNCSOCKET_HPP_
#define _ASYNCSOCKET_HPP_

#include <deque>

#include <boost/bind.hpp>
#include <boost/shared_ptr.hpp>
#include <boost/enable_shared_from_this.hpp>
#include <boost/asio.hpp>

#include "shared/packet.hpp"

using namespace boost::asio;
using namespace boost;
using namespace std;

using boost::asio::ip::tcp;

class AsyncSocket
    : public boost::enable_shared_from_this<AsyncSocket>
{
    public:
        void queue(boost::shared_ptr<Packet> packet);

    protected:
        AsyncSocket(io_service& ioService) : m_socket(ioService) {}
        ~AsyncSocket() { m_socket.close(); }

        void write();
        void writeHandler(const boost::system::error_code& errorCode, size_t bytesTransferred);

        void readHeader();
        void readHeaderHandler(const boost::system::error_code& errorCode);

        void readBody(uint16_t& length, boost::shared_ptr<Packet> packet);
        void readBodyHandler(boost::shared_ptr<Packet> packet, const boost::system::error_code& errorCode);

        virtual void handlePacket(boost::shared_ptr<Packet> packet) = 0;
        virtual void disconnectHandler() = 0;

        tcp::socket m_socket;
        deque< vector<uint8_t> > _queue;
        vector<uint8_t> _buffer;
};

#endif // _ASYNCSOCKET_HPP_
