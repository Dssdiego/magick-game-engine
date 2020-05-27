//
// Created by Diego Santos Seabra on 23/05/20.
//

#include "SDLRenderer.h"

const char TITLE[] = "Magick Game Engine";
const int SCREEN_WIDTH = 800;
const int SCREEN_HEIGHT = 600;

bool SDLRenderer::init()
{
    //Initialization flag
    bool success = true;

    //Initialize SDL
    if (SDL_Init(SDL_INIT_VIDEO) < 0)
    {
        printf("SDL could not initialize! SDL_Error: %s\n", SDL_GetError());
        success = false;

        isRunning = false;
    } else
    {
        //Create window
        window = SDL_CreateWindow(TITLE, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH,
                                  SCREEN_HEIGHT, SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE);
        if (window == nullptr)
        {
            printf("Window could not be created! SDL_Error: %s\n", SDL_GetError());
            success = false;
        } else
        {
            //Get window surface
            screenSurface = SDL_GetWindowSurface(window);
        }

        isRunning = true;
    }

    return success;
}

void SDLRenderer::render()
{
    //TODO: Render Content Here

    // Fill Screen with Blue Color
    SDL_FillRect( screenSurface, NULL, SDL_MapRGB( screenSurface->format, 0x00, 0x00, 0xFF ) );
    SDL_UpdateWindowSurface(window);
}

void SDLRenderer::handleEvents()
{
    SDL_Event event;
    SDL_PollEvent(&event);

    switch (event.type)
    {
        case SDL_QUIT:
            isRunning = false;
            break;
        default:
            break;
    }
}

void SDLRenderer::close()
{
    SDL_FreeSurface(screenSurface);

    //Destroy window
    SDL_DestroyWindow(window);

    //Quit SDL subsystems
    SDL_Quit();
}
