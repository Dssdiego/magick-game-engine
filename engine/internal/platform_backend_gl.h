//
// Created by Diego Santos Seabra on 16/01/21.
//

#ifndef MAGICK_ENGINE_PLATFORM_BACKEND_GL_H
#define MAGICK_ENGINE_PLATFORM_BACKEND_GL_H

#include <cinttypes>

namespace PlatformBackend
{
    // Initialize the system
    bool init();

    // The time, in milliseconds, since the engine was started
    uint64_t time();

    // Called every frame
    void frame(bool *engineExiting);

    // Sleeps the current thread
    void sleep(int milliseconds);

    // Called to present the window contents
    void present();

    // Called during shutdown
    void shutdown();

}

#endif //MAGICK_ENGINE_PLATFORM_BACKEND_GL_H
