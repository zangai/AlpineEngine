#include "GFX.hpp"
#include "RenderScene.hpp"

#include "scenes/GameScene.hpp"
#include "scenes/DebugScene.hpp"
#include "scenes/MenuScene.hpp"

GFX::~GFX(void)
{

}

int GFX::OnExecute()
{
    if(OnInit() == false)
        return -1;

    while (m_app->IsOpened())
    {
        sf::Event e;
        while (m_app->GetEvent(e))
            OnEvent(e);

        OnLoop();
        OnRender();

        while (m_app->GetEvent(e))
            OnEvent(e);
    }

    OnCleanup();

    return 1;
}

bool GFX::OnInit(void)
{
    m_gui       = new alpine::gui::GUI();
    m_scene     = new GameScene(this);
    m_app       = new sf::RenderWindow(sf::VideoMode(1024, 768, 32), "Alpine Engine", sf::Style::Resize);
    m_resource  = new Resource();
    m_clock     = new sf::Clock();
    m_inputMask = new alpine::InputMask(*m_app);

    m_clock->Reset();

    glEnable( GL_TEXTURE_2D);
    glEnable( GL_BLEND );
    glBlendFunc(GL_SRC_ALPHA,GL_ONE_MINUS_SRC_ALPHA);
    glClearColor( 0.0f, 0.0f, 0.0f, 0.0f );
    glViewport( 0, 0, m_app->GetWidth(), m_app->GetHeight() );
    glClear( GL_COLOR_BUFFER_BIT );
    glMatrixMode( GL_PROJECTION );
    glLoadIdentity();
    glOrtho(0.0f, m_app->GetWidth(), m_app->GetHeight(), 0.0f, -1.0f, 1.0f);
    glMatrixMode( GL_MODELVIEW );
    glLoadIdentity();

    m_app->SetActive();

    m_resource->LoadResources();

    m_world = new World(m_resource);
    m_world->init();

    return 1;
}

void GFX::OnLoop()
{
    m_scene->run();
}

void GFX::OnRender()
{
    m_scene->render();
}

void GFX::OnEvent(sf::Event e)
{
    if (e.Type == sf::Event::Closed)
        m_app->Close();

    // Escape key : exit
    if ((e.Type == sf::Event::KeyPressed) && (e.Key.Code == sf::Key::Escape))
        m_app->Close();

    // Resize event : adjust viewport
    if (e.Type == sf::Event::Resized)
        glViewport(0, 0, e.Size.Width, e.Size.Height);

	if (e.Type == sf::Event::MouseButtonPressed)
		m_gui->clickEvent(e);
}

void GFX::OnCleanup()
{
    delete m_gui;
    delete m_app;
    delete m_scene;
    delete m_world;
    delete m_resource;
    delete m_clock;
    delete m_inputMask;
}
