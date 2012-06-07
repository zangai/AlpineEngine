#ifndef _COLOPROGRESSBAR_HPP_
#define _COLOPROGRESSBAR_HPP_

#include "ProgressBar.hpp"
#include "gui/interfaces/IBackgroundColor.hpp"
#include "gui/interfaces/IForegroundColor.hpp"

namespace alpine {
    namespace gui {

        class ColorProgressBar : public ProgressBar, public IBackgroundColor, public IForegroundColor
        {
            public:
                ColorProgressBar(GUI* parent) : ProgressBar(parent) {}
                void render();
                void loop();
        };

    }
}

#endif //_COLORPROGRESSBAR_HPP_
