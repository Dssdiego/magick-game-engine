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

    int mKeysLen = 0;
    int mButtonsLen = 0;
    int mAxesLen = 0;

    float mPressBuffer = 0;
    float mReleaseBuffer = 0;
    float mRepeatDelay = 0;
    float mRepeatInterval = 0;

    bool mDown = false;
    bool mPressed = false;
    bool mReleased = false;
    float mLastPressTime = -1;
    float mLastReleaseTime = -1;
    float mRepeatPressTime = -1;

public:
    VirtualButton &addKey(Key key);
    VirtualButton &addButton(int gamepadId, Button button);
    VirtualButton &addAxis(int gamepadId, Axis axis, float threshold, bool greaterThan);
    VirtualButton &repeat(float repeatDelay, float repeatInterval);
    VirtualButton &pressBuffer(float duration);
    VirtualButton &releaseBuffer(float duration);

    void update();
    bool down() const { return mDown; };
    bool pressed() const { return mPressed; };
    bool released() const { return mReleased; };
    void clearPressBuffer() { mLastPressTime = -1; mPressed = false; };
    void clearReleaseBuffer() { mLastReleaseTime = -1; mReleased = false; };
};


#endif //MAGICK_ENGINE_VIRTUALBUTTON_H
