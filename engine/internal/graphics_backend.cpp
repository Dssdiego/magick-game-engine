//
// Created by Diego Santos Seabra on 19/01/21.
//

#include <SDL_opengl.h>
#include "graphics_backend.h"

bool GraphicsBackend::init()
{
    // REVIEW
    return true;
}

void GraphicsBackend::frame()
{
    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);
}

void GraphicsBackend::shutdown()
{
    // REVIEW
}
