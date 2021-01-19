//
// Created by Diego Santos Seabra on 17/01/21.
//

#ifndef MAGICK_ENGINE_GRAPHICS_BACKEND_H
#define MAGICK_ENGINE_GRAPHICS_BACKEND_H

namespace GraphicsBackend
{
    // Initialize the system
    bool init();

    // Called every frame
    void frame();

    // Called during shutdown
    void shutdown();
}

#endif //MAGICK_ENGINE_GRAPHICS_BACKEND_H
