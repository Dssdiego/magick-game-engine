//
// Created by Diego Santos Seabra on 23/05/20.
//

#ifndef MAGICK_GAME_ENGINE_GLFWRENDERER_H
#define MAGICK_GAME_ENGINE_GLFWRENDERER_H

#include <string>
#include <GLFW/glfw3.h>

class GLFWRenderer
{
public:
    GLFWwindow *window;
    int create();
    void render();
    void handleEvents();
};


#endif //MAGICK_GAME_ENGINE_GLFWRENDERER_H
