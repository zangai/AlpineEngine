#ifndef _DEBUG_TARGET_H
#define _DEBUG_TARGET_H

#include "SFML/Graphics/Color.hpp"

#include "gui/elements/GuiElement.hpp"
#include "gui/interfaces/IForegroundColor.hpp"

namespace alpine {
    namespace gui {

        class Target : public GuiElement, public IForegroundColor
        {
            public:
                Target(GUI* parent) : m_lifetime(10), GuiElement(parent) {}
				~Target();
                void render();
				void loop();
            private:
				int m_lifetime;
        };

    }
}

#endif //_DEBUG_TARGET_HPP_
