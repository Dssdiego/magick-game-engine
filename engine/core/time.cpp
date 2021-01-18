//
// Created by Diego Santos Seabra on 17/01/21.
//

#include "time.h"
#include <cmath>

uint64_t Time::milliseconds = 0;
float Time::elapsed = 0;
float Time::delta = 0;
float Time::elapsedPrevious = 0;
float Time::pauseTimer = 0;

// Separate a value into its integer and fractional components
// Not available on OpenGL 3.3, so implemented here
float modf(float x, float m)
{
    return x - (int)(x / m) * m;
}

void Time::pauseFor(float time)
{
    if (time >= pauseTimer)
    {
        pauseTimer = time;
    }
}

bool Time::onInterval(float time, float delta, float interval, float offset)
{
    return floor((time - offset - delta) / interval) < floor((time - offset) / interval);
}

bool Time::onInterval(float delta, float interval, float offset)
{
    return Time::onInterval(Time::elapsed, delta, interval, offset);
}

bool Time::onInterval(float interval, float offset)
{
    return Time::onInterval(Time::elapsed, Time::delta, interval, offset);
}

bool Time::onTime(float time, float timestamp)
{
    return time >= timestamp && time - Time::delta < timestamp;
}

bool Time::betweenInterval(float time, float interval, float offset)
{
    return modf(time - offset, interval * 2) >= interval;
}

bool Time::betweenInterval(float interval, float offset)
{
    return betweenInterval(Time::elapsed, interval, offset);
}

