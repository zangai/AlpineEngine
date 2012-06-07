#include "AsyncSocket.hpp"
#include "Log.hpp"

/**
 * Queue a packet to be sent as soon as possible
 */
void AsyncSocket::queue(boost::shared_ptr<Packet> packet)
{
    Log::outDebug("Queueing packet with opcode %#06X", packet->getOpcode());

    bool writeInProgress = !_queue.empty();
    _queue.push_back(packet->write());

    if(!writeInProgress)
        write();

}
/**
 * Internal function, fired every time a packet has been send to send the next one
 */
void AsyncSocket::write()
{
    if(!_queue.empty())
        async_write(m_socket, buffer(&_queue.front()[0], _queue.front().size()),
            boost::bind(&AsyncSocket::writeHandler, shared_from_this(),
            boost::asio::placeholders::error, boost::asio::placeholders::bytes_transferred));
}
/**
 * Handles completed write calls, and initiates a new one if needed
 */
void AsyncSocket::writeHandler(const boost::system::error_code& errorCode, size_t bytesTransferred)
{
    if(errorCode)
    {
        disconnectHandler();
        return;
    }

    Log::outDebug("Transfered %u bytes to %s", bytesTransferred, m_socket.remote_endpoint().address().to_string().c_str());
    _queue.pop_front();
    write();
}

/**
 * Starts an asynchronous read for a packet header
 */
void AsyncSocket::readHeader()
{
    _buffer.resize(4);
    async_read(m_socket, buffer(&_buffer[0], 4),
        boost::bind(&AsyncSocket::readHeaderHandler, shared_from_this(), boost::asio::placeholders::error));
}
/**
 * Handles any received headers
 */
void AsyncSocket::readHeaderHandler(const boost::system::error_code& errorCode)
{
    if(errorCode)
    {
        disconnectHandler();
        return;
    }

    boost::shared_ptr<Packet> packet = Packet::create();
    uint16_t length = packet->parseHeader(_buffer);

    if(length == 0)
    {
        handlePacket(packet);
        return;
    }
    readBody(length, packet);
}

/**
 * Start an asynchronous read call for the packet body
 */
void AsyncSocket::readBody(uint16_t& length, boost::shared_ptr<Packet> packet)
{
    _buffer.resize(length);
    async_read(m_socket, buffer(&_buffer[0], length),
        boost::bind(&AsyncSocket::readBodyHandler, shared_from_this(), packet, boost::asio::placeholders::error));
}
/**
 * Handle the received packet body
 */
void AsyncSocket::readBodyHandler(boost::shared_ptr<Packet> packet, const boost::system::error_code& errorCode)
{
    if(errorCode)
    {
        disconnectHandler();
        return;
    }

    packet->parseBody(_buffer);
    handlePacket(packet);
    readHeader();
}
