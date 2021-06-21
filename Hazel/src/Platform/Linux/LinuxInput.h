//
// Created by npchitman on 6/1/21.
//

#ifndef HAZEL_ENGINE_LINUXINPUT_H
#define HAZEL_ENGINE_LINUXINPUT_H

#include "Hazel/Input.h"

namespace Hazel {
    class LinuxInput : public Input {
    protected:
        virtual bool IsKeyPressedImpl(int keycode) override;

        virtual bool IsMouseButtonPressedImpl(int button) override;

        virtual std::pair<float, float> GetMousePositionImpl() override;

        virtual float GetMouseXImpl() override;

        virtual float GetMouseYImpl() override;
    };
}// namespace Hazel

#endif// HAZEL_ENGINE_LINUXINPUT_H