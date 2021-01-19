//
// Created by Diego Santos Seabra on 18/01/21.
//

#include <imgui.h>
#include <imgui_impl_sdl.h>
#include <imgui_impl_opengl3.h>
#include "gui_backend.h"

SDL_Window *gWindow = nullptr;
SDL_GLContext gContext = nullptr;

void init(GuiTheme theme)
{
    // Create the imgui context
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO &io = ImGui::GetIO();
    (void) io;

    // Setup imgui theme
    switch (theme)
    {
        case GuiTheme::Dark:
            ImGui::StyleColorsDark();
            break;
        case GuiTheme::Light:
            ImGui::StyleColorsClassic();
            break;
        case GuiTheme::Classic:
            ImGui::StyleColorsLight();
            break;
    }
}

bool GuiBackend::initOpenGl(SDL_Window *window, SDL_GLContext context, GuiTheme theme)
{
    // Create context and set the theme
//    init(theme);
    gWindow = window;
    gContext = context;

//    IMGUI_CHECKVERSION();
//    ImGui::CreateContext();
//    ImGuiIO &io = ImGui::GetIO();
//    (void) io;

    // Setup imgui theme
    switch (theme)
    {
        case GuiTheme::Dark:
            ImGui::StyleColorsDark();
            break;
        case GuiTheme::Light:
            ImGui::StyleColorsClassic();
            break;
        case GuiTheme::Classic:
            ImGui::StyleColorsLight();
            break;
    }

    // Setup Platform/Renderer bindings
    ImGui_ImplSDL2_InitForOpenGL(gWindow, gContext);
    ImGui_ImplOpenGL3_Init();
    return true;
}

void GuiBackend::createFrame(SDL_Window *window)
{
    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplSDL2_NewFrame(window);
    ImGui::NewFrame();
}

void GuiBackend::render(bool *quit)
{
    // Creates the menu
    if (ImGui::BeginMainMenuBar())
    {
        if (ImGui::BeginMenu("File"))
        {
            ImGui::MenuItem("Quit", nullptr, quit);
            ImGui::EndMenu();
        }
    }
    ImGui::EndMainMenuBar();

    // Render
    ImGui::Render();
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
}

void GuiBackend::forwardEvent(SDL_Event event)
{
    ImGui_ImplSDL2_ProcessEvent(&event);
}

void GuiBackend::shutdown()
{
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplSDL2_Shutdown();
    ImGui::DestroyContext();
}

