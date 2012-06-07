#include "shared/Log.hpp"

#include "GameScene.hpp"
#include "../GFX.hpp"

GameScene::GameScene(GFX* parent) : RenderScene(parent)
{

}

void GameScene::run()
{
    parent->getArrows() = parent->getInputMask()->GetMask(alpine::InputMask::ARROW);

    // Framerate cap at 15ms
    if ( parent->getClock()->GetElapsedTime() > 0.015 )
    {
        parent->getClock()->Reset();
        parent->getWorld()->getPlayer()->loop();
        if ( parent->getArrows() == 0x08 ) // if 1xxx (UP)
        {
            if ( !parent->getWorld()->getPlayer()->isWalking() )
            {
                parent->getWorld()->getPlayer()->setWalking(true);
                parent->getWorld()->getPlayer()->setDirection( parent->getWorld()->getPlayer()->UP );
            }
        }
        if ( parent->getArrows() == 0x04) // if x1xx (LEFT)
        {
            if ( !parent->getWorld()->getPlayer()->isWalking() )
            {
                parent->getWorld()->getPlayer()->setWalking(true);
                parent->getWorld()->getPlayer()->setDirection( parent->getWorld()->getPlayer()->LEFT );
            }
        }
        if ( parent->getArrows() == 0x02) // if xx1x (DOWN)
        {
            if ( !parent->getWorld()->getPlayer()->isWalking() )
            {
                parent->getWorld()->getPlayer()->setWalking(true);
                parent->getWorld()->getPlayer()->setDirection( parent->getWorld()->getPlayer()->DOWN );
            }
        }
        if ( parent->getArrows() == 0x01) // if xxx1 (RIGHT)
        {
            if ( !parent->getWorld()->getPlayer()->isWalking() )
            {
                parent->getWorld()->getPlayer()->setWalking(true);
                parent->getWorld()->getPlayer()->setDirection( parent->getWorld()->getPlayer()->RIGHT );
            }
        }
    }
    else
    {
        // printf_s("%f\n", parent->Clock->GetElapsedTime());
    }
}

void GameScene::render()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    parent->getWorld()->draw();
    parent->getGui()->render();
    parent->getApp()->Display();
}
