//
// Created by Diego Santos Seabra on 10/01/21.
//

// code nicked mainly from here:
// http://lazyfoo.net/tutorials/SDL/50_SDL_and_opengl_2/index.php


/* to compile

    ### installation on ubuntu
    # install compiler etc
    sudo apt-get install --yes software-properties-common g++ make
    # install sdl2
    sudo apt-get install --yes libsdl2-dev
    # install opengl
    sudo apt-get install --yes freeglut3-dev

    # compile with
    g++ main.cpp -I /usr/include/SDL2/ -lSDL2  -lGL

    ## installation on mac
    # install xcode with command line tools
    # install sdl2*.dmg, put everything in ~/Library/Frameworks

    # compile with with g++ (or with clang++)
    g++ main.cpp -I ~/Library/Frameworks/SDL2.framework/Headers -I OpenGL -framework SDL2  -F ~/Library/Frameworks -framework OpenGL

*/

//#define GL_GLEXT_PROTOTYPES
//#define GL3_PROTOTYPES

#include <SDL.h>
#include <SDL_opengl.h>
#include <stdio.h>
#include <SDL_opengl_glext.h>


//Screen dimension constants
const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;


//Main loop flag
bool quit = false;

//Starts up SDL, creates window, and initializes OpenGL
bool init();

//Initializes matrices and clear color
bool initGL();

//Input handler
void handleKeys(unsigned char key, int x, int y);

//Per frame update
void update();

//Renders quad to the screen
void render();

//Frees media and shuts down SDL
void close();

//The window we'll be rendering to
SDL_Window *gWindow = nullptr;

//OpenGL context
SDL_GLContext gContext;

// Remder Flags
bool gRotate = false;
//bool gRenderQuad = true;

bool init()
{
    //Initialization flag
    bool success = true;

    //Initialize SDL
    if (SDL_Init(SDL_INIT_VIDEO) != 0)
    {
        printf("SDL could not initialize! SDL Error: %s\n", SDL_GetError());
        success = false;
    } else
    {
        //Use OpenGL 2.1
//        SDL_GL_SetAttribute( SDL_GL_CONTEXT_MAJOR_VERSION, 3 );
//        SDL_GL_SetAttribute( SDL_GL_CONTEXT_MINOR_VERSION, 3 );
        SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_COMPATIBILITY);
//        SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);

        //Create window
        gWindow = SDL_CreateWindow("Magick Engine", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH,
                                   SCREEN_HEIGHT, SDL_WINDOW_OPENGL | SDL_WINDOW_SHOWN);

//        gRenderer = SDL_CreateRenderer(gWindow, -1, SDL_RENDERER_ACCELERATED);

        if (gWindow == nullptr)
        {
            printf("Window could not be created! SDL Error: %s\n", SDL_GetError());
            success = false;
        } else
        {
            //Create context
            gContext = SDL_GL_CreateContext(gWindow);
            if (gContext == nullptr)
            {
                printf("OpenGL context could not be created! SDL Error: %s\n", SDL_GetError());
                success = false;
            } else
            {
                //Use Vsync
                if (SDL_GL_SetSwapInterval(1) < 0)
                {
                    printf("Warning: Unable to set VSync! SDL Error: %s\n", SDL_GetError());
                }

                //Initialize OpenGL
                if (!initGL())
                {
                    printf("Unable to initialize OpenGL!\n");
                    success = false;
                }
            }
        }
    }

    return success;
}

bool initGL()
{
    bool success = true;
    GLenum error = GL_NO_ERROR;

    //Initialize Projection Matrix
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    SDL_version version;
    SDL_GetVersion(&version);

    printf("SDL: %i.%i.%i\n", version.major, version.minor, version.patch);
    printf("OpenGL Version: %s\n", glGetString(GL_VERSION));

    //Check for error
    error = glGetError();
    if (error != GL_NO_ERROR)
    {
        success = false;
    }

    //Initialize Modelview Matrix
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    //Check for error
    error = glGetError();
    if (error != GL_NO_ERROR)
    {
        success = false;
    }

    //Initialize clear color
    glClearColor(0.f, 0.f, 0.f, 1.f);

    //Check for error
    error = glGetError();
    if (error != GL_NO_ERROR)
    {
        success = false;
    }

    return success;
}

void handleKeys(unsigned char key, int x, int y)
{
    if (key == 'q')
    {
        quit = true;
    }

    if (key == 'r')
    {
        gRotate = true;
    }
}

void update()
{
    //No per frame update needed
}

void render()
{
    //Clear color buffer
    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    // Available only on opengl 3.3
    // REVIEW: Como usar sdl2 com opengl 3.3?
//    unsigned int vbo;
//    glGenBuffers(1, &vbo);

    // Quad Example
//    glBegin(GL_QUADS);
//    glColor4f(1.0f,0.0f,0.0f,1.0f);
//    glVertex2f(-0.5f, -0.5f);
//    glVertex2f(-0.5f, 0.5f);
//    glVertex2f(0.5f, 0.5f);
//    glVertex2f(0.5f, -0.5f);
//    glEnd();

    //Rotate
    if (gRotate)
        glRotatef(0.8f, 0.0f, 1.0f, 0.0f);    // Rotate around the Y axis
//    glRotatef(0.2f, 1.0f, 1.0f, 1.0f);
//    glColor3f(1.0f, 0.5f, 0.0f);

    // Triangle Example
    glBegin(GL_TRIANGLES);
    glColor3f(0.0f, 1.0f, 0.0f);
    glVertex2f(-0.5f, -0.5f);
    glVertex2f(0.5f, -0.5f);
    glVertex2f(0.0f, 0.5f);
    glEnd();

//    glBegin(GL_TRIANGLES);
//    glColor3f(1.0f, 0.5f, 0.0f);
//    glVertex2f(0.5f, 0.5f);
//    glVertex2f(0.5f, -0.5f);
//    glVertex2f(0.0f, 0.5f);
//    glEnd();
}

void close()
{
    //Destroy window
    SDL_DestroyWindow(gWindow);
//    SDL_DestroyRenderer(gRenderer);
    gWindow = nullptr;
//    gRenderer = nullptr;

    //Quit SDL subsystems
    SDL_Quit();
}

int main(int argc, char *args[])
{
    //Start up SDL and create window
    if (!init())
    {
        printf("Failed to initialize!\n");
    } else
    {

        //Event handler
        SDL_Event e;

        //Enable text input
        SDL_StartTextInput();

        //While application is running
        while (!quit)
        {
            //Handle events on queue
            while (SDL_PollEvent(&e) != 0)
            {
                //User requests quit
                if (e.type == SDL_QUIT)
                {
                    quit = true;
                }
                    //Handle keypress with current mouse position
                else if (e.type == SDL_TEXTINPUT)
                {
                    int x = 0, y = 0;
                    SDL_GetMouseState(&x, &y);
                    handleKeys(e.text.text[0], x, y);
                }
            }

            //Render
            render();

            // Swaps the back buffer to the current buffer
            // e.g. updates the screen
            SDL_GL_SwapWindow(gWindow);
        }

        //Disable text input
        SDL_StopTextInput();
    }

    //Free resources and close SDL
    close();

    return 0;
}