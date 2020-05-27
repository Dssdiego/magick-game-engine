//
// Created by Diego Santos Seabra on 23/05/20.
//

#include "GLFWRenderer.h"

const char TITLE[] = "Magick Game Engine";
const int WINDOW_WIDTH = 800;
const int WINDOW_HEIGHT = 600;

int GLFWRenderer::create()
{
    // Initialize the GLFW Library
    if (!glfwInit())
        return -1;

    // Create a windowed mode window and its OpenGL Context
    window = glfwCreateWindow(WINDOW_WIDTH, WINDOW_HEIGHT, TITLE, nullptr, nullptr);
    if (!window)
    {
        glfwTerminate();
        return -1;
    }

    // Make the window's context current
    glfwMakeContextCurrent(window);

    return 0;
}

void GLFWRenderer::render()
{
    while(!glfwWindowShouldClose(window)){
        // TODO: Render Anything Here

        handleEvents();

        glfwSwapBuffers(window); // Swap front and back buffers
        glfwPollEvents();        // Poll for process events
    }

    // GLFW Termination
    glfwTerminate();
}

void GLFWRenderer::handleEvents()
{
//    printf("%f", glfwGetTime());

}
