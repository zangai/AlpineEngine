#ifndef _CHARACTER_HPP_
#define _CHARACTER_HPP_

#include <vector>
#include <list>

#include "SFML/Graphics.hpp"

#include "Tile.hpp"
#include "Resource.hpp"

class Character
{
    public:
        Character(Resource *res);
        ~Character(void);
        virtual void draw();
        void loop();
        void switchFoot();

        const enum {UP = 1, DOWN = 4, LEFT  = 7, RIGHT = 10};
        const enum {LEFTFOOT = 1, NOFOOT = 2, RIGHTFOOT = 3};

        bool isWalking() { return m_walking; }
        void setWalking(bool walking) { m_walking = walking; }

        int getDirection() { return m_direction; }
        void setDirection(int direction) { m_direction = direction; }

        void setX(int x) { m_x = x; }
        void setY(int y) { m_y = y; }

        int getY() { return m_y; }
        int getX() { return m_x; }

        vector< vector<Tile*> > m_tile;

    private:
        void setTileSize(int w, int h);
        void init();

        bool m_walking;

        int m_direction;

        int m_footforward;
        int m_footdir;
        int m_substepX;
        int m_substepY;

        int m_width;
        int m_height;
        int m_x;
        int m_y;

        void DrawIMG(int x, int y, int w, int h, int x2, int y2);

        Resource* m_resource;
};

#endif //_CHARACTER_HPP_
