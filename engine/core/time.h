//
// Created by Diego Santos Seabra on 17/01/21.
//

#ifndef MAGICK_ENGINE_TIME_H
#define MAGICK_ENGINE_TIME_H

#include <cinttypes>

struct Time
{
    // Uptime, in milliseconds
    static uint64_t milliseconds;

    // Uptime, in seconds
    static float elapsed;

    // Previous frame uptime, in seconds
    static float elapsedPrevious;

    // Delta time from last frame
    static float delta;

    // Time the engine should pause for
    static float pauseTimer;

    // Pauses the engine for the given time
    static void pauseFor(float time);

    // Returns true on the given time interval
    static bool onInterval(float time, float delta, float interval, float offset);

    // Returns true on the given time interval
    static bool onInterval(float delta, float interval, float offset);

    // Returns true on the given time interval
    static bool onInterval(float interval, float offset = 0);

    // Returns true when the given timestamp is passed
    static bool onTime(float time, float timestamp);

    // Returns true between time intervals
    static bool betweenInterval(float time, float interval, float offset);

    // Returns true between time intervals
    static bool betweenInterval(float interval, float offset = 0);
};

#endif //MAGICK_ENGINE_TIME_H
