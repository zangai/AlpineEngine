#ifndef _IFOREGROUNDCOLOR_HPP_
#define _IFOREGROUNDCOLOR_HPP_

#include "SFML/Graphics/Color.hpp"

class IForegroundColor
{
    public:
        IForegroundColor() : m_foregroundColor(0,0,0,0) {}
        void setForegroundColor3i(sf::Uint8 r, sf::Uint8 g, sf::Uint8 b)
        {
            m_foregroundColor = sf::Color(r,g,b,255);
        }
        void setForegroundColor4i(sf::Uint8 r, sf::Uint8 g, sf::Uint8 b, sf::Uint8 a)
        {
            m_foregroundColor = sf::Color(r,g,b,a);
        }

    protected:
        sf::Color m_foregroundColor;
};

#endif //_IBACKGROUNDCOLOR_HPP_