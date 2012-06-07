#include "packet.hpp"

// Todo: Figure out if it's more efficient to use void read(string &result) instead of this
template <>
string Packet::read<string>()
{
    // Read the length from the packet
    size_t length = read<uint16_t>();
    Log::outDebug("String length is: %u", length);
    string result;

    // Pre-allocate the room to prevent re-allocations
    result.reserve(length);
    while (length--)
        result += read<char>();

    return result;
}
template <>
Packet& Packet::add(string value)
{
    // Save the length in the packet
    add(uint16_t(value.length()));
    for(size_t i=0; i< value.length(); ++i)
        add(value[i]);

    return *this;
}

vector<uint8_t> Packet::write()
{
    vector<uint8_t> result;
    copyToByte(m_opcode, result);
    copyToByte(uint16_t(_storage.size()), result);

    for (uint16_t i=0; i<_storage.size(); i++)
        result.push_back(_storage[i]);

    return result;
}

uint16_t Packet::parseHeader(vector<uint8_t> &source)
{
    uint8_t bytes[2];
    uint16_t length;

    #ifdef BOOST_LITTLE_ENDIAN
        // opcode
        bytes[0] = source[1];
        bytes[1] = source[0];
        memcpy(&m_opcode, &bytes, 2);

        // length
        bytes[0] = source[3];
        bytes[1] = source[2];
        memcpy(&length, &bytes, 2);
    #else
        memcpy(&m_opcode, &source[0], 2);
        memcpy(&length, &source[2], 2);
    #endif

    return length;
}

void Packet::parseBody(vector<uint8_t> &source)
{
    for(uint16_t i = 0; i < source.size(); ++i)
        _storage.push_back(source[i]);
}
