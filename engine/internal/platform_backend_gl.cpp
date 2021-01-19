//
// Created by Diego Santos Seabra on 16/01/21.
//

#include "platform_backend_gl.h"
#include "../input/input.h"
#include "../core/log.h"
#include "gui_backend.h"
#include "input_backend.h"
#include <SDL.h>
#include <SDL_opengl.h>
#include <imgui.h>
#include <imgui_impl_sdl.h>
#include <imgui_impl_opengl3.h>

SDL_Window *window = nullptr;
SDL_GLContext context = nullptr;
SDL_Joystick *joysticks[Input::maxControllers];
SDL_GameController *gamepads[Input::maxControllers];

bool PlatformBackend::init()
{
    // Get the SDL Version
    SDL_version version;
    SDL_GetVersion(&version);
    Log::print("SDL: %i.%i.%i", version.major, version.minor, version.patch);

    // Initialize SDL
//    if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_TIMER | SDL_INIT_EVENTS | SDL_INIT_JOYSTICK | SDL_INIT_GAMECONTROLLER) != 0)
    if (SDL_Init(SDL_INIT_EVERYTHING) != 0)
    {
        Log::error("Failed to initialize SDL");
        return false;
    }

    // SDL Flags
    int flags = SDL_WINDOW_RESIZABLE | SDL_WINDOW_SHOWN | SDL_WINDOW_OPENGL;

    // TODO: GL Context Flags (?)
    // TODO: Doublebuffer (?)
    // REVIEW: What about OpenGl major and minor properties? Are they necessary?
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);

    // TODO: Stencil, Depth, Multisample Buffers & Multisample Sample(?)

    // Create the window
    // FIXME: Window width and height (passed through config?)
    window = SDL_CreateWindow("Magick Engine", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 800, 600, flags);
    if (window == nullptr)
    {
        Log::error("Failed to create a window");
        return false;
    }
    context = SDL_GL_CreateContext(window);
    SDL_GL_MakeCurrent(window, context); // REVIEW: Make current context out of here?

    if (context == nullptr)
    {
        Log::error("Failed to make OpenGl context");
        return false;
    }

    // Get the OpenGL Version
    Log::print("OpenGL: %s", glGetString(GL_VERSION));

    // TODO: On Windows we need to scale the monitor for High DPI Displays

    // Window properties
    SDL_SetWindowResizable(window, SDL_TRUE);
    SDL_SetWindowMinimumSize(window, 256, 256);

    // Initialize imgui
//    if (GuiBackend::initOpenGl(window, context, GuiTheme::Dark))
//    {
//        Log::error("Failed to initialize ImGui");
//        return false;
//    }

    // Initialize imgui
    // TODO: Pass this to a backend
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO &io = ImGui::GetIO();
    (void) io;

    ImGui_ImplSDL2_InitForOpenGL(window, context);
    if (!ImGui_ImplOpenGL3_Init()) {
        Log::error("Failed to initialize ImGui");
        return false;
    }

    return true;
}

void PlatformBackend::frame(bool *engineExiting)
{
    // Create imgui frame
    GuiBackend::createFrame(window);

    // Update the mouse every frame
//    {
//        int winX, winY, x, y;
//        SDL_GetWindowPosition(window, &winX, &winY);
//        SDL_GetGlobalMouseState(&x, &y);

    // TODO: onMouseMove
//        InputBackend::onMouseMove((float) (x - winX), (float) (y - winY));
//        InputBackend::onMouseScreenMove((float) x, (float) y);
//    }

    // Poll Events
    SDL_Event event;
    while (SDL_PollEvent(&event))
    {
        if(event.type == SDL_QUIT){
            // TODO: Change this for a callback event (?)
            *engineExiting = true;
        }
        // TODO: Mouse Input
        // TODO: Keyboard Input
        // TODO: Gamepad Input
    }

    // Forward events to imgui
    GuiBackend::forwardEvent(event); // REVIEW
}

void PlatformBackend::present()
{
    // Swaps the back buffer with the current buffer, e.g. updates the screen
    SDL_GL_SwapWindow(window);

//    SDL_ShowWindow(window);

//    SDL_Delay(1.0 / 60.0); // Use floating point division, not integer
    // REVIEW: Implement SDL Show Window (Mac Black Screen ?)
}

void PlatformBackend::shutdown()
{
    if (window != nullptr)
    {
        SDL_DestroyWindow(window);
    }

    if (context != nullptr)
    {
        SDL_GL_DeleteContext(context);
    }

    SDL_Quit();
}

