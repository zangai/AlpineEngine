#include "SFML/Graphics/Color.hpp"
#include "SFML/System.hpp"

#include "shared/Log.hpp"

#include "elements/progbar/ColorProgressBar.hpp"
#include "debug/Target.hpp"
#include "GUI.hpp"

using std::set;
using namespace alpine::gui;

GUI::GUI(void)
{
    m_elements = set<GuiElement*>();
    ColorProgressBar* progBar = new ColorProgressBar(this);
    progBar->setMaxProgress(5000);
    progBar->setProgress(0);
    progBar->setSize(1024,10);
    progBar->setPosition(0,758);
    progBar->setBackgroundColor4i(25,25,25,205);
    progBar->setForegroundColor4i(255,0,0,255);
    m_elements.insert(progBar);

    /*Label* label = new Label();
    m_elements.push_back(label);*/
}

GUI::~GUI(void)
{
    Log::outDebugFilter(LOG_FILTER_MEMLEAK, "GUI::~GUI");
    set<GuiElement*>::iterator iter;
    for( iter = m_elements.begin(); iter != m_elements.end(); )
    {
        delete (*iter);
        iter = m_elements.erase(iter);
    }
}

void GUI::render()
{
    set<GuiElement*>::iterator iter;
    for( iter = m_elements.begin(); iter != m_elements.end(); )
    {
        (*iter)->loop();
        (*iter)->render();
        if ( (*iter)->dispose() )
        {
            delete (*iter);
            iter = m_elements.erase(iter);
        }
        else
            ++iter;
    }
}

void GUI::add(GuiElement* elem)
{
	m_elements.insert(elem);
}

/*
* Handle ClickEvent from Main
*/
void GUI::clickEvent(sf::Event e)
{
	char* btn = "MOUSE_UNDEFINED";
	switch(e.MouseButton.Button)
	{
	    case sf::Mouse::Left:
		    btn = "MOUSE_LEFT";
		    break;
	    case sf::Mouse::Right:
		    btn = "MOUSE_RIGHT";
		    break;
        case sf::Mouse::Middle:
            btn = "MOUSE_MIDDLE";
            break;
	}
    Log::outDebugFilter(LOG_FILTER_INPUT, "Click Received: Button {%s} Position{%i, %i}", btn, e.MouseButton.X, e.MouseButton.Y);
	Target* target = new Target(this);
	target->setPosition(e.MouseButton.X-2,e.MouseButton.Y-2);
	target->setSize(5,5);
		
	if (e.MouseButton.Button == sf::Mouse::Left)
        target->setForegroundColor4i(255,0,0,255);
    else if(e.MouseButton.Button == sf::Mouse::Right)
        target->setForegroundColor4i(0,0,255,255);
    else if(e.MouseButton.Button == sf::Mouse::Middle)
        target->setForegroundColor4i(0,255,0,255);

    add(target);
}

