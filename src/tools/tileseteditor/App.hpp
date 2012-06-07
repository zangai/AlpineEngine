#ifndef _APP_HPP_
#define _APP_HPP_

#include "SFML/System.hpp"
#include "SFML/Graphics.hpp"

using namespace std;

class App
{
    public:
        App(void) : RenderWin(0), Clock(0) {}
        ~App(void);

        bool OnInit();
        void OnEvent(sf::Event event);
        void OnLoop();
        void OnRender();
        void OnCleanup();
        int OnExecute();

		void handleCommand(string com);
		void termOutput(char* msg);

        sf::RenderWindow *RenderWin;
        sf::Clock *Clock;
};

#endif // _APP_HPP_
