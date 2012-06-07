#ifndef _IRIGHTCLICKABLE_HPP_
#define _IRIGHTCLICKABLE_HPP_

#include "gui/Events.hpp"
#include "gui/elements/BaseElement.hpp"

namespace alpine
{
    namespace gui
    {

        class IRightClickable : public virtual BaseElement
        {
            ILeftClickable() { m_flags += RIGHTCLICK; }
        };

    }
}

#endif //_IRIGHTCLICKABLE_HPP_