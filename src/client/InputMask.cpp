#include "InputMask.hpp"

namespace alpine {

    InputMask::InputMask(sf::RenderWindow& app)
    {
        this->app = &app;
    }

    InputMask::~InputMask(void)
    {
        this->app = NULL;
    }

    short int InputMask::GetMask(Mask msk)
    {
        const sf::Input& inputSrc = this->app->GetInput();
        short int retMask;
        switch(msk)
        {
            case ARROW:
                retMask = 0;
                retMask |= (short int)inputSrc.IsKeyDown(sf::Key::Up); retMask<<=1;
                retMask |= (short int)inputSrc.IsKeyDown(sf::Key::Left); retMask<<=1;
                retMask |= (short int)inputSrc.IsKeyDown(sf::Key::Down); retMask<<=1;
                retMask |= (short int)inputSrc.IsKeyDown(sf::Key::Right);
                return retMask;
                break;
            case FUNCTION:
                return (short int) inputSrc.IsKeyDown(sf::Key::Up);
                break;
            case SPECIAL:
                return (short int) inputSrc.IsKeyDown(sf::Key::Up);
                break;
            default:
                return 0;
                break;
        }
    }
};
