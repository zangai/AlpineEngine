#ifndef _IBACKGROUNDCOLOR_HPP_
#define _IBACKGROUNDCOLOR_HPP_

#include "SFML/Graphics/Color.hpp"

class IBackgroundColor
{
    public:
        IBackgroundColor() : m_backgroundColor(0,0,0,0) {}
        void setBackgroundColor3i(sf::Uint8 r, sf::Uint8 g, sf::Uint8 b)
        {
            m_backgroundColor = sf::Color(r,g,b,255);
        }
        void setBackgroundColor4i(sf::Uint8 r, sf::Uint8 g, sf::Uint8 b, sf::Uint8 a)
        {
            m_backgroundColor = sf::Color(r,g,b,a);
        }
    protected:
        sf::Color m_backgroundColor;
};

#endif //_IBACKGROUNDCOLOR_HPP_