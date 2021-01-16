//
// Created by Diego Santos Seabra on 16/01/21.
//

#ifndef MAGICK_ENGINE_VIRTUALBUTTON_H
#define MAGICK_ENGINE_VIRTUALBUTTON_H

#include "input.h"

class VirtualButton
{
private:
    struct KeyNode
    {
        Key key = Key::Unknown;

        bool down = false;
        bool pressed = false;
        bool released = false;

        void init(Key key);
        void update();
    };

    struct ButtonNode
    {
        int gamepadId = 0;
        Button button = Button::None;

        bool down = false;
        bool pressed = false;
        bool released = false;

        void init(int gamepadId, Button button);
        void update();
    };

    struct AxisNode
    {
        int gamepadId = 0;
        float threshold = 0;
        bool greaterThan = 0;
        Axis axis = Axis::None;

        bool down = false;
        bool pressed = false;
        bool released = false;

        void init(int gamepadId, Axis axis);
        void update();
    };

    KeyNode keys[Input::maxVirtualNodes];
    ButtonNode buttons[Input::maxVirtualNodes];
    AxisNode axes[Input::maxVirtualNodes];

    int keysLen = 0;
    int buttonsLen = 0;
    int axesLen = 0;

    float pressBuffer = 0;
    float releaseBuffer = 0;
    float repeatDelay = 0;
    float repeatInterval = 0;

    bool down = false;
    bool pressed = false;
    bool released = false;
    float lastPressTime = -1;
    float lastReleaseTime = -1;
    float repeatPressTime = -1;

public:
    VirtualButton &addKey(Key key);
    VirtualButton &addButton(int gamepadId, Button button);
    VirtualButton &addAxis(int gamepadId, Axis axis, float threshold, bool greaterThan);
    VirtualButton &repeat(float repeatDelay, float repeatInterval);
    VirtualButton &pressBuffer(float duration);
    VirtualButton &releaseBuffer(float duration);

    void update();
    bool down() const { return down };
    bool pressed() const { return pressed };
    bool released() const { return released };
    void clearPressBuffer() { lastPressTime = -1; pressed = false };
    void clearReleaseBuffer() { lastReleaseTime = -1; released = false };
};


#endif //MAGICK_ENGINE_VIRTUALBUTTON_H
