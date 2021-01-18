#include <iostream>
#include <SDL.h>
#include <SDL_opengl.h>
#include <SDL_opengl_glext.h>
#include <imgui_impl_opengl3.h>
#include "engine/gui/imgui_impl_sdl.h"
#include "engine/core/log.h"

#define concat(first, second) first second

SDL_Window *window = nullptr;
SDL_GLContext context;
SDL_version version;
SDL_Event e;
GLuint program, vao, vbo;
int camX, camY;
int frames = 0, fps = 0;
bool darkTheme, lightTheme, classicTheme;
Uint32 startTime = 0;

const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;
const char *WINDOW_TITLE = "Magick Engine";

bool quit;

// Vertex Shader Code
static const GLchar *vertexShaderSource =
        "#version 330 core\n"
        "layout (location = 0) in vec3 aPos;\n"
        "void main()\n"
        "{\n"
        "   gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
        "}\0";

// Fragment Shader Code
static const GLchar *fragmentShaderSource =
        "#version 330 core\n"
        "out vec4 FragColor;\n"
        "void main() {\n"
        "    FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);\n"
        "}\n";

// Vertices to draw a triangle
// NOTE: This is 3D, could it be 2D?
static GLfloat vertices[] = {
        -0.5f, -0.5f, 0.0f, // left
        0.5f, -0.5f, 0.0f,  // right
        0.0f, 0.5f, 0.0f    // top
};

GLuint getShaderProgram(const char *vertexSource, const char *fragmentSource)
{
    GLchar log[512];
    GLint log_length, success;
    GLuint vertexShader, fragmentShader, shaderProgram;

    /* Vertex Shader */
    vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader, 1, &vertexShaderSource, nullptr);
    glCompileShader(vertexShader);
    glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
    glGetShaderiv(vertexShader, GL_INFO_LOG_LENGTH, &log_length);

//    if (log_length > 0)
//    {
//        glGetShaderInfoLog(vertexShader, log_length, nullptr, log);
//        printf("Vertex Shader Log: %s\n", log);
//    }

    if (!success)
    {
        printf("ERROR:: Vertex Shader Compile Error\n");
        exit(EXIT_FAILURE);
    }

    /* Fragment Shader */
    fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, &fragmentShaderSource, nullptr);
    glCompileShader(fragmentShader);

    glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
    glGetShaderiv(fragmentShader, GL_INFO_LOG_LENGTH, &log_length);

//    if (log_length > 0)
//    {
//        glGetShaderInfoLog(fragmentShader, log_length, nullptr, log);
//        printf("ERROR:: Fragment Shader Log: %s\n", log);
//    }

    if (!success)
    {
        printf("ERROR:: Fragment Shader Compile Error\n");
        exit(EXIT_FAILURE);
    }

    shaderProgram = glCreateProgram();
    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);
    glLinkProgram(shaderProgram);
    glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
    glGetProgramiv(shaderProgram, GL_INFO_LOG_LENGTH, &log_length);

//    if (log_length > 0)
//    {
//        glGetProgramInfoLog(shaderProgram, log_length, nullptr, log);
//        printf("Shader Link Log: %s\n", log);
//    }

    if (!success)
    {
        printf("ERROR:: Shader Link Error\n");
        exit(EXIT_FAILURE);
    }

    /* Cleanup */
    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);

    return shaderProgram;
}

void imgui_init()
{
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO &io = ImGui::GetIO();
    (void) io;

    // Setup Dear ImGui style
    if (darkTheme)
        ImGui::StyleColorsDark();

    if (classicTheme)
        ImGui::StyleColorsClassic();

    if (lightTheme)
        ImGui::StyleColorsLight();

    // Setup Platform/Renderer bindings
    // window is the SDL_Window*
    // context is the SDL_GLContext
    ImGui_ImplSDL2_InitForOpenGL(window, context);
    ImGui_ImplOpenGL3_Init();
}

void init()
{
    SDL_Init(SDL_INIT_EVERYTHING);
//    SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1); // REVIEW: When to use doublebuffer?
//    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
//    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 3);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
    window = SDL_CreateWindow(WINDOW_TITLE, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT,
                              SDL_WINDOW_OPENGL | SDL_WINDOW_SHOWN);
    context = SDL_GL_CreateContext(window);
    SDL_GL_MakeCurrent(window, context);
    SDL_GetVersion(&version);

    startTime = SDL_GetTicks();

    Log::print("OpenGL: %s\n", glGetString(GL_VERSION));
    Log::print("SDL: %i.%i.%i\n", version.major, version.minor, version.patch);

    program = getShaderProgram(vertexShaderSource, fragmentShaderSource);

    /* Buffers Setup */
//    glViewport(1000, 0, SCREEN_WIDTH, SCREEN_HEIGHT);

    glGenVertexArrays(1, &vao);
    glGenBuffers(1, &vbo);
    glBindVertexArray(vao);

    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void *) nullptr);
    glEnableVertexAttribArray(0);

    glBindBuffer(GL_ARRAY_BUFFER, 0);

    glBindVertexArray(0);

    imgui_init();
}

void handleKeys(unsigned char key)
{
    if (key == 'q')
    {
        quit = true;
    }

    if (key == 'd')
    {
        camX -= 10;
    }

    if (key == 'a')
    {
        camX += 10;
    }

    if (key == 'w')
    {
        camY -= 10;
    }

    if (key == 's')
    {
        camY += 10;
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

    // Forward to Imgui
    ImGui_ImplSDL2_ProcessEvent(&e);
    if (e.type == SDL_QUIT
        || (e.type == SDL_WINDOWEVENT
            && e.window.event == SDL_WINDOWEVENT_CLOSE
            && e.window.windowID == SDL_GetWindowID(window)))
    {
        quit = true;
    }
}

void update()
{ /* no need for update now */ }

void render()
{
    // ImGui Init Frame
    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplSDL2_NewFrame(window);
    ImGui::NewFrame();

    // Clears the screen
//    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
//    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glClear(GL_COLOR_BUFFER_BIT);

    // Camera movement
    glViewport(camX, camY, SCREEN_WIDTH, SCREEN_HEIGHT);

    // Draws the rectangle
    glUseProgram(program);
    glBindVertexArray(vao);
    glDrawArrays(GL_TRIANGLES, 0, 3);

    // TODO: Separate ImGui Menu Rendering
    if (ImGui::BeginMainMenuBar())
    {
        if (ImGui::BeginMenu("File"))
        {
            ImGui::MenuItem("Quit", nullptr, &quit);
            ImGui::EndMenu();
        }
    }
    ImGui::EndMainMenuBar();

    // ImGui Render
    ImGui::Render();
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

    // Swaps the back buffer with the current buffer, e.g. updates the screen
    SDL_GL_SwapWindow(window);
}

void clearMemory()
{
    // ImGui Cleanup
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplSDL2_Shutdown();
    ImGui::DestroyContext();

    // OpenGL Cleanup
    glDeleteVertexArrays(1, &vao);
    glDeleteBuffers(1, &vbo);
    glDeleteProgram(program);

    // SDL Cleanup
    SDL_StopTextInput();
    SDL_GL_DeleteContext(context);
    SDL_DestroyWindow(window);
    window = nullptr;
    context = nullptr;
    SDL_Quit();
}

int main(int argc, char *argv[])
{
    init();

    while (!quit)
    {
        ++frames;
        Uint32 elapsedMS = SDL_GetTicks();
        if (elapsedMS)
        { // Skip this the first frame
            double elapsedSeconds = elapsedMS / 1000.0; // Convert to seconds
            fps = (int) (frames / elapsedSeconds); // FPS is Frames / Seconds

            // Put the FPS counter in the window title
            char engine[64] = "Magick Engine | FPS: "; // make sure you allocate enough space to append the other string
            char fps_string[32];
            sprintf(fps_string, "%d", fps);
            strcat(engine, fps_string);
            SDL_SetWindowTitle(window, engine);
        }
        // REVIEW: Qual o motivo do delay?
        SDL_Delay(1.0 / 60.0); // Use floating point division, not integer

        handleInputs();
        render();
    }

    clearMemory();
}