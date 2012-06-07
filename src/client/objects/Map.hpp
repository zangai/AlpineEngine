#ifndef _Map_HPP_
#define _Map_HPP_

#include <vector>

#include "boost/cstdint.hpp"

#include "Layer.hpp"
#include "Resource.hpp"

using namespace boost;
using std::vector;

class Map
{
    public:
        Map(Resource *res) : m_resource(res) {}
        Map(Resource *res, uint8_t w, uint8_t h);
        ~Map();
        virtual void draw();
    private:
        void DrawIMG(int x, int y, int w, int h, int x2, int y2);
        //void DrawIMG(sf::Image tileset, int x, int y, int w, int h, int x2, int y2);
        Resource* m_resource;
        vector<CLayer*> m_layers;
};

#endif //_Map_HPP_
