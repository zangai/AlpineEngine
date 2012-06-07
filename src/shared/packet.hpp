#ifndef _PACKET_HPP_
#define _PACKET_HPP_

#include <vector>
#include <iostream>
#include <cstring>
#include <iterator>
#include <cstdio>

#include <boost/detail/endian.hpp>
#include <boost/cstdint.hpp>
#include <boost/shared_ptr.hpp>
#include <boost/enable_shared_from_this.hpp>

#include "shared/Log.hpp"

using namespace boost;
using namespace std;

template <typename Type>
void swapBytes(Type &value)
{
    vector<uint8_t> split;
    copy((uint8_t*) &value, ((uint8_t*) &value) + sizeof(Type), back_inserter(split));

    uint8_t splitArray[sizeof(Type)];
    for(uint8_t i=0;i<sizeof(Type);++i)
        splitArray[i] = split[sizeof(Type)-i-1];

    memcpy(&value, &splitArray, sizeof(Type));
}

class Packet
    : public boost::enable_shared_from_this<Packet>
{
    public:
        Packet() : m_opcode(0), _rpos(0)
        {}

        static boost::shared_ptr<Packet> create()
        {
            return boost::shared_ptr<Packet>(new Packet());
        }

        uint16_t getOpcode() const { return m_opcode; }
        void setOpcode(uint16_t opcode) { m_opcode = opcode; }


        template <typename Type>
        Type read()
        {
            Type result;
            uint8_t *p = &_storage[_rpos];
            copy(p, p + sizeof(Type), (uint8_t*) &result);
            _rpos += sizeof(Type);

            #ifdef BOOST_LITTLE_ENDIAN
                swapBytes(result);
            #endif

            return result;
        }

        template <typename Type>
        Packet& add(Type value)
        {
            #ifdef BOOST_LITTLE_ENDIAN
                swapBytes(value);
            #endif
            copy((uint8_t*) &value, ((uint8_t*) &value) + sizeof(Type), back_inserter(_storage));
            return *this;
        }

        template <typename Type>
        void copyToByte(Type input, vector<uint8_t>&output)
        {
            #ifdef BOOST_LITTLE_ENDIAN
                swapBytes(input);
            #endif
            copy((uint8_t*) &input, ((uint8_t*) &input) + sizeof(Type), back_inserter(output));
        }

        vector<uint8_t> write();

        uint16_t parseHeader(vector<uint8_t> &source);
        void parseBody(vector<uint8_t> &source);

    protected:
        uint16_t m_opcode;
        std::vector<uint8_t> _storage;

        // Read position
        size_t _rpos;
};

typedef boost::shared_ptr<Packet> PacketPtr;

#endif // _PACKET_HPP_
