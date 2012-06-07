#ifndef _DEBUGSCENE_HPP_
#define _DEBUGSCENE_HPP_

#include "../RenderScene.hpp"

class GFX;

class DebugScene : public RenderScene
{
    public:
        DebugScene(GFX *parent);
        void run();
        void render();
};

#endif //_DEBUGSCENE_HPP_
