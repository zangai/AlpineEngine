#ifndef _CWORLD_HPP_
#define _CWORLD_HPP_

#include <vector>

#include "Map.hpp"
#include "Player.hpp"
#include "Resource.hpp"

using std::vector;

class World
{
    public:
        World() {}
        World(Resource* res);
        ~World();
        void init();
        void draw();
        void draw(int tex1, int text2);
        void DrawIMG(int x, int y, int w, int h, int x2, int y2);

        vector < vector <Map*> > getMap() { return m_map; }
        Player* getPlayer() { return m_player; }

    private:
        vector < vector <Map*> > m_map;
        Player* m_player;
        Resource* m_resource;
};

#endif //_CWORLD_HPP_