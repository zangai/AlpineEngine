#include "Flags.hpp"

Flags::Flags(uint32_t flags)
{
    m_data = flags;
}

bool Flags::operator==(uint32_t flag)
{
    return (flag & m_data) == flag;
}
bool Flags::operator!=(uint32_t flag)
{
    return (flag & m_data) != flag;
}
Flags& Flags::operator+=(uint32_t flag)
{
    m_data |= flag;
    return *this;
}
Flags& Flags::operator-=(uint32_t flag)
{
    m_data ^= flag;
    return *this;
}
Flags& Flags::operator=(uint32_t flag)
{
    m_data = flag;
    return *this;
}

uint32_t Flags::getData()
{
    return m_data;
}
