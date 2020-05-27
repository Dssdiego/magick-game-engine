cmake_minimum_required(VERSION 3.15)
project(magick_game_engine)

set(CMAKE_CXX_STANDARD 20)

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake")

#add_subdirectory(vendor)
#add_subdirectory(vendor/GLEW)
#add_subdirectory(IMGUI)

#include_directories(${PROJECT_SOURCE_DIR}/vendor)
#include_directories(vendor/GLFW/include)
#include_directories(vendor/IMGUI)

# Includes all files from the "engine" and "game" folder
file(GLOB SOURCES
        "engine/*.cpp"
        "engine/graphics/*.cpp"
        "engine/audio/*.cpp"
        "engine/input/*.cpp"
        "engine/math/*.cpp"
        "engine/utils/*.cpp"
        "game/*.cpp"
        )

# glfw
find_package(glfw3 REQUIRED)
include_directories(${GLFW_INCLUDE_DIRS})
link_libraries(${GLFW_LIBRARY_DIRS})

# opengl
find_package(OpenGL REQUIRED)
include_directories(${OPENGL_INCLUDE_DIRS})

# SDL2
find_package(SDL2 REQUIRED)

include_directories(${SDL2_INCLUDE_DIR})

# glew
#find_package(GLEW REQUIRED)
#include_directories(${GLEW_INCLUDE_DIRS})

#add_library(imgui STATIC vendor/IMGUI)

add_executable(magick_game_engine game/game.cpp ${SOURCES})

target_link_libraries(magick_game_engine glfw ${GLFW_LIBRARIES} ${SDL2_LIBRARY})
