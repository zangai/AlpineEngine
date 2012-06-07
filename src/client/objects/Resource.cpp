#include "Resource.hpp"

void Resource::LoadResources()
{
    printf("Loading Textures ...\n");
    sf::Image tmpImg;

    tmpImg.LoadFromFile("res/gfx/Tiles0.bmp");
    tmpImg.CreateMaskFromColor(sf::Color::Black);
    images.push_back(tmpImg);

    tmpImg.LoadFromFile("res/gfx/Sprites.bmp");
    tmpImg.CreateMaskFromColor(sf::Color::Magenta);
    images.push_back(tmpImg);
}
