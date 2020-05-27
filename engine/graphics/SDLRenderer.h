//
// Created by Diego Santos Seabra on 23/05/20.
//

#ifndef MAGICK_GAME_ENGINE_SDLRENDERER_H
#define MAGICK_GAME_ENGINE_SDLRENDERER_H

#include <SDL2/SDL.h>

class SDLRenderer
{
    SDL_Window *window;
    SDL_Surface *screenSurface;
public:
    bool isRunning;
    bool init();
    void handleEvents();
    void render();
    void close();
};


#endif //MAGICK_GAME_ENGINE_SDLRENDERER_H
