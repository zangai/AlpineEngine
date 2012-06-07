#ifndef _ILEFTCLICKABLE_HPP_
#define _ILEFTCLICKABLE_HPP_

#include "gui/Events.hpp"
#include "gui/elements/BaseElement.hpp"

namespace alpine
{
    namespace gui
    {

        class ILeftClickable : public virtual BaseElement
        {
            ILeftClickable() { m_flags += LEFTCLICK; }
        };

    }
}

#endif //_ILEFTCLICKABLE_HPP_