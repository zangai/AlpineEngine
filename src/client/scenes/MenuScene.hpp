#ifndef _MENUSCENE_HPP_
#define _MENUSCENE_HPP_

#include "../RenderScene.hpp"

class GFX;

class MenuScene : public RenderScene
{
    public:
        MenuScene::MenuScene(GFX* parent) : RenderScene(parent) {}

        void run();
        void render();
};

#endif //_MENUSCENE_HPP_
