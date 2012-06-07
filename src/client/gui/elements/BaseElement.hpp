#ifndef _GUIBASEELEMENT_HPP_
#define _GUIBASEELEMENT_HPP_

#include "shared/Flags.hpp"

namespace alpine
{
    namespace gui
    {

        class BaseElement
        {
            public:
                BaseElement() : m_flags(0) {}

                /** Event Functions **/
                virtual void leftClick(void) {};
                virtual void reftClick(void) {};

                virtual Flags getFlags() { return m_flags; }
            protected:
                Flags m_flags;
        };

    }
}

#endif //_BASEELEMENT_HPP_