#ifndef _Resource_HPP_
#define _Resource_HPP_

#include <vector>

#include "SFML/Graphics.hpp"

class Resource
{
    public:
        void LoadResources();
        std::vector<sf::Image> images;
};

#endif //_Resource_HPP_
