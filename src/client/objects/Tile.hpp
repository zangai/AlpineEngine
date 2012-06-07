#ifndef _TILE_HPP_
#define _TILE_HPP_

#include <vector>
#include <iostream>

using std::vector;

class Tile
{
    public:
        Tile(int tile, int tileset) : m_tileId(tile), m_tilesetId(tileset)  { }
        Tile() {}

        void setTile(int tileId) { m_tileId = tileId; }
        void setTileset(int tilesetId) { m_tilesetId = tilesetId; }

        int getTile() { return m_tileId; }
        int getTileset() { return m_tilesetId; }
    private:
        int m_tileId;
        int m_tilesetId;
};

#endif //_TILE_HPP_
