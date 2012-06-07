#include "boost/cstdint.hpp"
#include "SFML/Graphics.hpp"

#include "shared/Log.hpp"

#include "Layer.hpp"

CLayer::CLayer(Resource &res, uint8_t w, uint8_t h)
{
    this->resource = &res;
    init(w, h);
}

void CLayer::draw()
{
    for (uint8_t y = 0; y <= ( (uint8_t)tile.size()-1 ); y++)
    {
        for (uint8_t x = 0; x <= ( (uint8_t)tile[y].size()-1 ); x++)
        {
            DrawIMG(
                ( this->tile[y][x]->getTile() % 8 ),
                ( this->tile[y][x]->getTile() / 8 ),
                32, 32, (y*32), (x*32));
        }
    }
}

/**
 * Initialize the tile vectors
 */
void CLayer::init(uint8_t w, uint8_t h)
{
    tile.resize(w);
    for (uint8_t x = 0; x <=( (uint8_t)tile.size()-1 ); x++)
        tile[x].resize(h);

    for (uint8_t y = 0; y <= ( (uint8_t)tile.size()-1 ); y++)
    {
        for (uint8_t x = 0; x <= ( (uint8_t)tile[y].size()-1 ); x++)
            tile[y][x] = new Tile(8, 0);
    }
}

CLayer::~CLayer()
{
    Log::outDebugFilter(LOG_FILTER_MEMLEAK, "CLayer::~CLayer");
    for (uint8_t y = 0; y <= ( (uint8_t)tile.size()-1 ); y++)
    {
        for (uint8_t x = 0; x <= ( (uint8_t)tile[y].size()-1 ); x++)
            delete tile[y][x];
    }
}

void CLayer::DrawIMG(int x, int y, int w, int h, int x2, int y2)
{
    this->resource->images[0].Bind();
    GLfloat texXpos = (GLfloat)32.0f / resource->images[0].GetWidth();
    GLfloat texYpos = (GLfloat)32.0f / resource->images[0].GetHeight();

    glBegin(GL_QUADS);

    // lower left corner
    glTexCoord2f(texXpos*x, texYpos*(y+1));
    glVertex3f(x2+0.0f, y2+32.0f, 0.0f);

    // lower right corner
    glTexCoord2f(texXpos*(x+1), texYpos*(y+1));
    glVertex3f(x2+32.0f, y2+32.0f, 0.0f);

    // upper right corner
    glTexCoord2f(texXpos*(x+1), texYpos*y);
    glVertex3f(x2+32.0f, y2+0.0f, 0.0f);

    // upper left corner
    glTexCoord2f(texXpos*x, texYpos*y);
    glVertex3f(x2+0.0f, y2+0.0f, 0.0f);

    glEnd();
}
