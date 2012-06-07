#ifndef _LAYER_HPP_
#define _LAYER_HPP_

#include <vector>

#include "boost/cstdint.hpp"

#include "Tile.hpp"
#include "Resource.hpp"

using namespace boost;
using namespace std;

class CLayer
{
    public:
        CLayer(Resource &res, uint8_t w, uint8_t h);
        ~CLayer();
        void draw();
        void init(uint8_t w, uint8_t h);

    private:
        Resource *resource;
        vector< vector<Tile*> > tile;
        void DrawIMG(int x, int y, int w, int h, int x2, int y2);
};

#endif //_LAYER_HPP_
