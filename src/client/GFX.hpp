#ifndef _GFX_HPP_
#define _GFX_HPP_

#include "SFML/System.hpp"
#include "SFML/Graphics.hpp"

#include "GUI/GUI.hpp"
#include "objects/Resource.hpp"
#include "objects/World.hpp"
#include "InputMask.hpp"

class RenderScene;

class GFX
{
    public:
        GFX(void) : m_scene(0), m_app(0), m_clock(0), m_inputMask(0), m_resource(0), m_world(0), m_gui(0) {}
        ~GFX(void);

        bool OnInit();
        void OnEvent(sf::Event event);
        void OnLoop();
        void OnRender();
        void OnCleanup();
        int OnExecute();

        RenderScene* getScene() { return m_scene; }
        sf::RenderWindow* getApp() { return m_app; }
        sf::Clock* getClock() { return m_clock; }
        alpine::InputMask* getInputMask() { return m_inputMask; }
        alpine::gui::GUI* getGui() { return m_gui; }
        World* getWorld() { return m_world; }

        Flags& getArrows() { return m_arrows; }
        
    private:
        RenderScene* m_scene;
        sf::RenderWindow* m_app;
        sf::Clock* m_clock;
        alpine::InputMask* m_inputMask;
        World* m_world;
        Resource* m_resource;
        alpine::gui::GUI* m_gui;
        Flags m_arrows;
};

#endif // _GFX_HPP_
