//
// Created by Diego Santos Seabra on 18/01/21.
//

#ifndef MAGICK_ENGINE_GUI_BACKEND_H
#define MAGICK_ENGINE_GUI_BACKEND_H

#include <SDL.h>

enum class GuiTheme {
    Dark,
    Classic,
    Light
};

namespace GuiBackend
{
    // Initialize the system
//    void init(GuiTheme theme);

    // Init for OpenGl
    bool initOpenGl(SDL_Window *window, SDL_GLContext context, GuiTheme theme);

    // Initialize the frame
    void createFrame(SDL_Window *window);

    // Render imgui content to the screen
    void render(bool *quit);

    // Changes the theme
//    void changeTheme();

    // Forward event
    void forwardEvent(SDL_Event event);

    // Cleanup
    void shutdown();
}

#endif //MAGICK_ENGINE_GUI_BACKEND_H
