#ifndef _GUIELEMENT_HPP_
#define _GUIELEMENT_HPP_

#include "boost/cstdint.hpp"

#include "BaseElement.hpp"

using namespace boost;

namespace alpine
{
    namespace gui
    {
        class GUI;

        class GuiElement : public virtual BaseElement
        {
            public:
                GuiElement(GUI* parent)
                    : m_left(0), m_top(0), m_width(0), m_height(0), m_visible(false), m_dispose(false), m_parent(parent) {}
                virtual void render() = 0;
                virtual void loop() = 0;

                bool dispose() { return m_dispose; }
                void setPosition(int16_t left, int16_t top);
                void setSize (uint16_t width, uint16_t height);
            protected:
                int16_t m_left;
                int16_t m_top;

                uint16_t m_width;
                uint16_t m_height;

                GUI* m_parent;

                bool m_visible;
                bool m_dispose;
        };

    }
}

#endif //_GUIELEMENT_HPP_
