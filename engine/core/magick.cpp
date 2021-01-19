//
// Created by Diego Santos Seabra on 17/01/21.
//

#include "magick.h"
#include "../internal/platform_backend_gl.h"
#include "../internal/graphics_backend.h"
#include "log.h"
#include "../internal/input_backend.h"
#include "../internal/gui_backend.h"

namespace
{
    bool engineRunning = true;
    bool engineExiting = false;
}

bool Magick::run()
{
    // Initialize the system
    if (!PlatformBackend::init())
    {
        Log::error("Failed to initialize platform module");
        return false;
    }

    // Initialize graphics
    GraphicsBackend::init();

    // Input
    InputBackend::init();

    // Main loop
    while (!engineExiting)
    {
        // Poll system events
        PlatformBackend::frame(&engineExiting);

        // Render
        {
            GraphicsBackend::frame();
            GuiBackend::render(&engineExiting);
            PlatformBackend::present();
        }
    }

    // Shutdown
    GuiBackend::shutdown();
    GraphicsBackend::shutdown();
    PlatformBackend::shutdown();

    // Clear static state
    engineRunning = false;
    engineExiting = false;
    // TODO: Time

    return true;
}

void Magick::exit()
{
    if (!engineExiting && engineRunning)
        engineExiting = true;
}


