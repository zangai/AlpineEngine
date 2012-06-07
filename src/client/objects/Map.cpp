#include "SFML/Window.hpp"
#include "SFML/Graphics.hpp"

#include "shared/Log.hpp"

#include "Map.hpp"
#include "Layer.hpp"

Map::Map(Resource *res, uint8_t w, uint8_t h) :
    m_resource(res)
{
    for(int layer = 0; layer < 3; ++layer)
        m_layers.push_back( new CLayer(*res, w, h) );
};

void Map::draw()
{
    for( int layer = 0; layer < m_layers.size(); ++layer )
        m_layers[layer]->draw();
}

Map::~Map()
{
    Log::outDebugFilter(LOG_FILTER_MEMLEAK, "Map::~Map");
    for( int layer = 0; layer < m_layers.size(); ++layer )
        delete m_layers[layer];
}
