#include "DebugScene.hpp"
#include "../GFX.hpp"

DebugScene::DebugScene(GFX* parent) : RenderScene(parent)
{

}

void DebugScene::run()
{
    // Framerate cap at 15ms
    if ( parent->getClock()->GetElapsedTime() > 0.015 )
    {
        // Placeholder
        parent->getClock()->Reset();
    }
}

void DebugScene::render()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    parent->getGui()->render();
    parent->getApp()->Display();
}
