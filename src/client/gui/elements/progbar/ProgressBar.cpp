#include "ProgressBar.hpp"

using namespace alpine::gui;

void ProgressBar::setProgress(uint16_t progress)
{
    if(progress > m_maxProgress)
        return;

    m_progress = progress;
}
