cmake_minimum_required(VERSION 3.17)
project(magick_engine)

set(CMAKE_CXX_STANDARD 14)

# Packaging
#include(InstallRequiredSystemLibraries)
#set(CPACK_PACKAGE_DESCRIPTION_SUMMARY "Magick Engine")
#set(CPACK_PACKAGE_VENDOR "Diego S. Seabra")
#set(CPACK_PACKAGE_VERSION_MAJOR "0")
#set(CPACK_PACKAGE_VERSION_MINOR "1")
#set(CPACK_PACKAGE_VERSION_PATCH "0")
#set(CPACK_PACKAGE_INSTALL_DIRECTORY "CMake ${CMake_VERSION_MAJOR}.${CMake_VERSION_MINOR}")
#set(CPACK_CMAKE_GENERATOR "ZIP")
#set(CPACK_GENERATOR "STGZ;TGZ")
#include(CPack)

# SDL2
find_package(SDL2 REQUIRED)
include_directories(${SDL2_INCLUDE_DIRS})
#message(STATUS "SDL2 <<${SDL2_INCLUDE_DIRS}>>")

# OpenGL
find_package(OpenGL REQUIRED)
include_directories(${OPENGL_INCLUDE_DIR})
#message(STATUS "OpenGL <<${OPENGL_INCLUDE_DIR}>>")

add_library(imgui
        engine/gui/imgui.cpp
        engine/gui/imgui_draw.cpp
        engine/gui/imgui_widgets.cpp

        engine/gui/imgui_impl_sdl.cpp
        engine/gui/imgui_impl_opengl3.cpp
        )

target_include_directories(imgui PUBLIC ${SDL2_INCLUDE_DIRS})
target_include_directories(imgui PUBLIC engine/gui)
target_compile_definitions(imgui PUBLIC IMGUI_IMPL_OPENGL_LOADER_CUSTOM=<SDL_opengl.h>  GL_GLEXT_PROTOTYPES=1)

add_executable(magick_engine MACOSX_BUNDLE
        main.cpp

        engine/core/magick.cpp
        engine/core/log.cpp
        engine/core/time.cpp

        engine/graphics/rect.cpp

        engine/input/input.cpp
        engine/input/virtualbutton.cpp

        engine/internal/graphics_backend.cpp
        engine/internal/gui_backend.cpp
        engine/internal/input_backend.h
        engine/internal/platform_backend_gl.cpp

        engine/math/point.cpp
        engine/math/vec2.cpp
        )

#message(STATUS "SDL2 Libs <<${SDL2_LIBRARIES}>>")
target_link_libraries(magick_engine ${SDL2_LIBRARIES})
#message(STATUS "OpenGL Libs <<${OPENGL_LIBRARIES}>>")
target_link_libraries(${CMAKE_PROJECT_NAME} ${OPENGL_LIBRARIES})
target_link_libraries(magick_engine imgui)
