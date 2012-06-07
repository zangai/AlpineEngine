#include "MenuScene.hpp"
#include "../GFX.hpp"

void MenuScene::run()
{
    // Framerate cap at 15ms
    if ( parent->getClock()->GetElapsedTime()>0.015 )
    {
        // Placeholder
        parent->getClock()->Reset();
    }
}

void MenuScene::render()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    parent->getGui()->render();
    parent->getApp()->Display();
}
