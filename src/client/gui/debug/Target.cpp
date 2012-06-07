#include "Target.hpp"
#include "gui/GUI.hpp"

#include "SFML/Window/OpenGL.hpp"
#include "SFML/Graphics/Color.hpp"

using namespace alpine::gui;

Target::~Target()
{
	
}

void Target::render()
{
    glBegin(GL_QUADS);

        // Foreground
        glColor4f(float(m_foregroundColor.r) / 255.0f, float(m_foregroundColor.g) / 255.0f, float(m_foregroundColor.b) / 255.0f,float(m_foregroundColor.a) / 255.0f);

        glVertex3f(m_left                         , m_top                         , 0);
        glVertex3f(float(m_left) + float(m_width) , m_top                         , 0);
        glVertex3f(float(m_left) + float(m_width) , float(m_top) + float(m_height), 0);
        glVertex3f(m_left                         , float(m_top) + float(m_height), 0);

    glEnd();
}

void Target::loop() {
	m_lifetime--;
	if (m_lifetime == 0)
        m_dispose = true;
}
