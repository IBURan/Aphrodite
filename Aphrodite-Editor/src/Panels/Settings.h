//
// Created by npchitman on 7/7/21.
//

#ifndef APHRODITE_SETTINGS_H
#define APHRODITE_SETTINGS_H

#include "Aphrodite/Core/Base.h"

namespace Aph::Editor {
    class Settings {
    public:
        void OnImGuiRender();

    private:
        float m_Time = 0.0f;

        float m_FpsValues[50];
        std::vector<float> m_FrameTimes;
    };
}// namespace Aph::Editor


#endif//APHRODITE_SETTINGS_H
