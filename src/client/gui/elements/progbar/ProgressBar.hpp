#ifndef _PROGRESSBAR_HPP_
#define _PROGRESSBAR_HPP_

#include <boost/cstdint.hpp>
#include "../GuiElement.hpp"

using namespace boost;

namespace alpine {
    namespace gui {

        class ProgressBar : public GuiElement
        {
            public:
                ProgressBar(GUI* parent) : m_progress(0), m_maxProgress(0), GuiElement(parent) {}

                void setProgress(uint16_t progress);
                uint16_t getProgress() { return m_progress; }

                void setMaxProgress(uint16_t maxProgress) { m_maxProgress = maxProgress; }
                uint16_t getMaxProgress() { return m_maxProgress; }

            protected:
                uint16_t m_progress;
                uint16_t m_maxProgress;
        };

    }
}
#endif //_PROGRESSBAR_HPP_
