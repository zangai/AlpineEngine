#ifndef _GAMESCENE_HPP_
#define _GAMESCENE_HPP_

#include "../RenderScene.hpp"

class GFX;

class GameScene : public RenderScene
{
    public:
        GameScene(GFX *parent);
        void run();
        void render();
};

#endif //_GAMESCENE_HPP_
