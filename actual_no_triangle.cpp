//
// Created by Diego Santos Seabra on 10/01/21.
//

#define GL_GLEXT_PROTOTYPES

#include <iostream>
#include <SDL.h>
#include <SDL_opengl.h>
#include <SDL_opengl_glext.h>

SDL_Window *window = nullptr;
SDL_GLContext context;
SDL_version version;
SDL_Event e;

const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;
const char *WINDOW_TITLE = "Magick Engine";

bool quit;

void init()
{
    SDL_Init(SDL_INIT_EVERYTHING);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 2);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 1);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
    window = SDL_CreateWindow(WINDOW_TITLE, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT,
                              SDL_WINDOW_OPENGL | SDL_WINDOW_SHOWN);
    context = SDL_GL_CreateContext(window);
    SDL_GetVersion(&version);

    printf("OpenGL: %s\n", glGetString(GL_VERSION));
    printf("SDL: %i.%i.%i\n", version.major, version.minor, version.patch);
}

void handleKeys(unsigned char key)
{
    if (key == 'q')
    {
        quit = true;
    }
}

void handleInputs()
{
    SDL_PollEvent(&e);
    if (e.type == SDL_QUIT)
    {
        quit = true;
    }

    if (e.type == SDL_TEXTINPUT)
    {
        handleKeys(e.text.text[0]);
    }
}

void update()
{}

void render()
{
    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
//    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    float vertices[] = {
            -0.5f, -0.5f, 0.0f,
            0.5f, -0.5f, 0.0f,
            0.0f, 0.5f, 0.0f
    };

    GLuint vertexShader;
    GLuint fragmentShader;

    // Creates the vertex shader
    const char *vertexShaderSource = "#version 330 core\n"
                                     "layout (location = 0) in vec3 aPos;\n"
                                     "void main()\n"
                                     "{\n"
                                     "   gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
                                     "}\0";
    vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
    glCompileShader(vertexShader);

    int success;
    char infoLog[512];
    glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);

    if (!success)
    {
        glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
        printf("ERROR: Vertex Shader Compilation Failed: %s\n", infoLog);
    }

    // Creates the fragment shader
    const char *fragmentShaderSource = "#version 330 core\n"
                                       "out vec4 FragColor;\n"
                                       "void main()\n"
                                       "{\n"
                                       "   FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);\n"
                                       "}\0";
    fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
    glCompileShader(fragmentShader);

    glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);

    if (!success)
    {
        glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
        printf("ERROR: Fragment Shader Compilation Failed: %s\n", infoLog);
    }

    // Creates the shader program
    GLuint shaderProgram;
    shaderProgram = glCreateProgram();
    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);
    glLinkProgram(shaderProgram);

    glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
    if (!success)
    {
        glGetProgramInfoLog(shaderProgram, 512, NULL, infoLog);
        printf("ERROR: Shader Program Compilation Failed: %s\n", infoLog);
    }

    GLuint vao, vbo;
    glGenVertexArrays(1, &vao);
    glGenBuffers(1, &vbo);
    glBindVertexArray(vao);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glUseProgram(shaderProgram);
    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);
    glBindVertexArray(vao);
    glDrawArrays(GL_TRIANGLES, 0, 3);

//    glGenBuffers(1, &VBO);
//    glBindBuffer(GL_ARRAY_BUFFER, VBO);
//    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

//    glGenBuffers();

    // Swaps the back buffer with the current buffer
    // e.g. updates the screen
    SDL_GL_SwapWindow(window);
}

void clearMemory()
{
    SDL_StopTextInput();
    SDL_DestroyWindow(window);
    SDL_GL_DeleteContext(context);
    window = nullptr;
    context = nullptr;
    SDL_Quit();
}

int main(int argc, char *argv[])
{
    init();

    while (!quit)
    {
        handleInputs();
        render();
    }

    clearMemory();
}