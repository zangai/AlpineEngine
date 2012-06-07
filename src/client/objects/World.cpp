#include <cstdio>
#include <cstdlib>

#include "shared/Log.hpp"

#include "World.hpp"

World::World(Resource* res)
{
    m_resource = res;
}

World::~World()
{
    Log::outDebugFilter(LOG_FILTER_MEMLEAK, "World::~World");
    delete m_player;
    for ( int i = 0; i<=( (int)m_map.size()-1 ); i++ )
    {
        for ( int j = 0; j<=( (int) m_map[i].size()-1 ); j++)
            delete m_map[i][j];
    }
}

void World::init()
{
    m_map.resize(1);
    for ( int i = 0; i<=( (int)m_map.size()-1 ); i++ )
        m_map[i].resize(1);

    for ( int i = 0; i<=( (int)m_map.size()-1 ); i++ )
    {
        for ( int j = 0; j<=( (int)m_map[i].size()-1 ); j++ )
        {
            m_map[i][j] = new Map(m_resource, 32, 24);
        }
    }

    m_player = new Player(m_resource, 24);
    m_player->setX(2);
    m_player->setY(2);
}

void World::draw()
{
    // clear color
    glColor4f(1.0f,1.0f,1.0f,1.0f);

    m_resource->images[0].Bind();
    m_map[0][0]->draw();
    m_player->draw();

    //unbind texture
    glBindTexture(GL_TEXTURE_2D, NULL);
}

void World::draw(int tex1, int tex2)
{

}
