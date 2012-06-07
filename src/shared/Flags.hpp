#ifndef _FLAGS_HPP_
#define _FLAGS_HPP_

#include <boost/cstdint.hpp>

using namespace boost;

class Flags
{
    private:
        uint32_t m_data;

    public:
        Flags(uint32_t flags);
        Flags() : m_data(0) {}
        bool operator==(uint32_t flag);
        bool operator!=(uint32_t flag);
        Flags& operator+=(uint32_t flag);
        Flags& operator-=(uint32_t flag);
        Flags& operator=(uint32_t flag);

        uint32_t getData();
};

#endif //_FLAGS_HPP_
