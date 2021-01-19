//
// Created by Diego Santos Seabra on 17/01/21.
//

#ifndef MAGICK_ENGINE_MAGICK_H
#define MAGICK_ENGINE_MAGICK_H

// REVIEW: Separate this in a new file?
enum class Renderer
{
    None = -1,
    OpenGl,
    Metal,
    Vulkan
};

namespace Magick
{
    // Runs the engine
    bool run();

    // Returns wether the engine is runnning
    bool isRunnnig();

    // Exits the engine
    void exit();

    // Toggles fullscreen
    void fullscreen(bool enabled);

    // Returns the rendering API in use
    Renderer renderer();
}

#endif //MAGICK_ENGINE_MAGICK_H
