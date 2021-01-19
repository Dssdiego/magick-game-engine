//
// Created by Diego Santos Seabra on 16/01/21.
//

#ifndef MAGICK_ENGINE_INPUT_BACKEND_H
#define MAGICK_ENGINE_INPUT_BACKEND_H

#include <cinttypes>
#include "../input/input.h"
#include "../math/point.h"

namespace InputBackend
{
    void init();
    void frame();

    void onMouseMove(float x, float y);
    void onMouseScreenMove(float x, float y);
    void onMouseDown(MouseButton button);
    void onMouseUp(MouseButton button);
    void onMouseWheel(Point wheel);

    void onKeyDown(Key key);
    void onKeyUp(Key key);

    void onControllerConnect(int index, const char *name, int isGamePad, int buttonCount, uint16_t vendor, uint16_t, uint16_t product, uint16_t version);
    void onControllerDisconnect(int index);

    void onButtonDown(int index, int button); // REVIEW: Should use the button interface?
    void onButtonUp(int index, int button); // REVIEW: Should use the button interface?

    void onAxisMove(int index, int axis, float value); // REVIEW: Should use the axis interface?
}

#endif //MAGICK_ENGINE_INPUT_BACKEND_H
