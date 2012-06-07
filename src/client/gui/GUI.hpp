#ifndef _GUI_HPP_
#define _GUI_HPP_
#include <SFML/Window/Event.hpp>

#include "elements/GuiElement.hpp"
#include "elements/progbar/ColorProgressBar.hpp"

#include <set>

using std::set;

namespace alpine {
    namespace gui {

        class GUI
        {
            public:
                GUI(void);
                ~GUI(void);
                virtual void render(void);

				void add(GuiElement* element);
                void remove(GuiElement* element);
				void clickEvent(sf::Event e);

            private:
                set<GuiElement*> m_elements;
        };

    }
}

#endif //_GUI_HPP_
