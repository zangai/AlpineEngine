#include <cstdio>
#include <cstdlib>

#include "SFML/Window.hpp"
#include "SFML/Graphics.hpp"

#include "shared/Log.hpp"

#include "Character.hpp"

Character::Character(Resource *res) :
    m_walking(false), m_substepX(0), m_substepY(0), m_direction(DOWN), m_footforward(2), m_footdir(1), m_resource(res)
{
    setTileSize(1,2);
    init();
}

void Character::setTileSize(int w, int h)
{
    m_tile.resize(w);
    for ( int i = 0; i <= ( (int)m_tile.size()-1 ); i++ )
        m_tile[i].resize(h);
}

void Character::init()
{
    for ( int i = 0; i <= ( (int)m_tile.size()-1 ); i++ )
    {
        for ( int j = 0; j <= ( (int)m_tile[i].size()-1 ); j++ )
        {
            m_tile[i][j] = new Tile();
        }
    }
}

Character::~Character(void)
{
    Log::outDebugFilter(LOG_FILTER_MEMLEAK, "Character::~Character");
    for ( int i = 0; i <= ( (int)m_tile.size()-1 ); i++ )
    {
        for ( int j = 0; j <= ( (int)m_tile[i].size()-1 ); j++ )
        {
            delete m_tile[i][j];
        }
    }
}

void Character::draw()
{
    for ( int i = 0; i <= ( (int)m_tile.size()-1 ); i++ )
    {
        for ( int j = 0; j <= ( (int)m_tile[i].size()-1 ); j++ )
        {
            DrawIMG(
                //this->tileset1,
                m_direction + (m_footforward - 2),
                m_tile[i][j]->getTile() / 16,
                32, 32, ( m_x * 32 ) + m_substepX, ( ( m_y * 32 ) + ( j * 32 ) ) + m_substepY );
        }
    }
}

void Character::loop()
{
    if (m_walking)
    {
        switch(m_direction) {
            case UP:
                m_substepY-=2;
                if (m_substepY%16==0) { switchFoot(); }
                if (m_substepY == -32) { m_y--; m_substepY = 0; m_walking = false;  m_footforward = NOFOOT;}
                break;
            case LEFT:
                m_substepX-=2;
                if (m_substepX%16==0) { switchFoot(); }
                if (m_substepX == -32) { m_x--; m_substepX = 0; m_walking = false;  m_footforward = NOFOOT;}
                break;
            case RIGHT:
                m_substepX+=2;
                if (m_substepX%16==0) { switchFoot(); }
                if (m_substepX == 32) { m_x++; m_substepX = 0; m_walking = false;  m_footforward = NOFOOT;}
                break;
            case DOWN:
                m_substepY+=2;
                if (m_substepY%16==0) { switchFoot(); }
                if (m_substepY == 32) { m_y++; m_substepY = 0; m_walking = false; m_footforward = NOFOOT;}
                break;
        }
    }
}

void Character::switchFoot()
{
    switch(m_footdir)
    {
        case 0:
            switch(m_footforward)
            {
                case RIGHTFOOT:
                    m_footdir = 1;
                    m_footforward = NOFOOT;
                    break;
                case NOFOOT:
                    m_footforward = RIGHTFOOT;
                    break;
                case LEFTFOOT:
                    m_footforward = NOFOOT;
                    break;
            }
            break;
        case 1:
            switch(m_footforward)
            {
                case RIGHTFOOT:
                    m_footforward = NOFOOT;
                    break;
                case NOFOOT:
                    m_footforward = LEFTFOOT;
                    break;
                case LEFTFOOT:
                    m_footdir = 0;
                    m_footforward = NOFOOT;
                    break;
            }
            break;
    }
}

void Character::DrawIMG(int x, int y, int w, int h, int x2, int y2)
{
    m_resource->images[1].Bind();
    GLfloat texXpos = (GLfloat)32 / m_resource->images[1].GetWidth();
    GLfloat texYpos = (GLfloat)32 / m_resource->images[1].GetHeight();

    float layer = 0.5f;

    glBegin(GL_QUADS);

    // ..
    // x.
    glTexCoord2f(texXpos*x, texYpos*(y+1));
    glVertex3f(x2+0.0f, y2+32.0f, layer);

    // ..
    // .x
    glTexCoord2f(texXpos*(x+1), texYpos*(y+1));
    glVertex3f(x2+32.0f, y2+32.0f, layer);

    // .x
    // ..
    glTexCoord2f(texXpos*(x+1), texYpos*y);
    glVertex3f(x2+32.0f, y2+0.0f, layer);

    // x.
    // ..
    glTexCoord2f(texXpos*x, texYpos*y);
    glVertex3f(x2+0.0f, y2+0.0f, layer);

    glEnd();
}
