#include "SFML/Window/OpenGL.hpp"
#include "SFML/Graphics/Color.hpp"

#include "ColorProgressBar.hpp"

using namespace alpine::gui;

void ColorProgressBar::render()
{
    glBegin(GL_QUADS);

        // Background
        glColor4f(float(m_backgroundColor.r) / 255.0f, float(m_backgroundColor.g) / 255.0f, float(m_backgroundColor.b) / 255.0f,float(m_backgroundColor.a) / 255.0f);

        glVertex3f(m_left                        , m_top                         , 0);
        glVertex3f(float(m_left) + float(m_width), m_top                         , 0);
        glVertex3f(float(m_left) + float(m_width), float(m_top) + float(m_height), 0);
        glVertex3f(m_left                        , float(m_top) + float(m_height), 0);

        // Foreground
        glColor4f(float(m_foregroundColor.r) / 255.0f, float(m_foregroundColor.g) / 255.0f, float(m_foregroundColor.b) / 255.0f,float(m_foregroundColor.a) / 255.0f);

        glVertex3f(m_left                                                                     , m_top           , 0);
        glVertex3f(float(m_left) + (float(m_width) / float(m_maxProgress)) * float(m_progress), m_top           , 0);
        glVertex3f(float(m_left) + (float(m_width) / float(m_maxProgress)) * float(m_progress), m_top + m_height, 0);
        glVertex3f(m_left                                                                     , m_top + m_height, 0);

    glEnd();
}

void ColorProgressBar::loop()
{
    if (m_progress < m_maxProgress)
        ++m_progress;
    else
        m_progress = 0;
}