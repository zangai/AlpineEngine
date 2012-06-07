#ifndef _LABEL_HPP_
#define _LABEL_HPP_

#include <boost/cstdint.hpp>

#include "gui/GuiElement.hpp"
#include "gui/interfaces/leftClickable.hpp"

using namespace boost;

namespace alpine {
    namespace gui {

        class Label : public GuiElement, public ILeftClickable
        {
        };

    }
}

#endif //_LABEL_HPP_
