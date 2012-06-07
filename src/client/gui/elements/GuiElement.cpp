#include "GuiElement.hpp"

using namespace alpine::gui;

void GuiElement::setPosition(int16_t left, int16_t top)
{
    m_left = left;
    m_top = top;
}
void GuiElement::setSize (uint16_t width, uint16_t height)
{
    m_width = width;
    m_height = height;
}
