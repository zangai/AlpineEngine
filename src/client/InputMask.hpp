#pragma once
#include "SFML/System.hpp"
#include "SFML/Window.hpp"
#include "SFML/Graphics.hpp"

namespace alpine {

    class InputMask : sf::RenderWindow
    {
        public:
            InputMask(sf::RenderWindow& app);
            ~InputMask();

            sf::RenderWindow *app;
            enum Mask
            {
                ARROW,
                SPECIAL,
                FUNCTION
            };

            short int GetMask(Mask msk);

        private:
            short int ARROW_KEYS;    // UP,LEFT,DOWN,RIGHT
            short int SPECIAL_KEYS;  // CTRL_LEFT,ALT,ALTGR,CTRL_RIGHT
            short int FUNCTION_KEYS; // F1,F2,F3,F4,F5,F6,F7,F8,F9,F10,F11,F12
    };
};
