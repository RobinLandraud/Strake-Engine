set(CMAKE_MODULE_PATH ${CMAKE_SOURCE_DIR}/cmake)
set(CMAKE_CXX_STANDARD 20)
cmake_minimum_required(VERSION 3.10)
# Project name
project(ECS)
# Set the directory for ECS headers
include_directories(include)

find_package(SFML 2.5 COMPONENTS system window graphics network audio REQUIRED)

add_library(Time STATIC src/Time/Time.cpp)
add_library(Loop STATIC src/Loop/Loop.cpp)
add_library(Window STATIC src/Window/Window.cpp)
add_library(EventHandler STATIC src/Window/EventHandler.cpp)

# dependencies for the libraries
target_link_libraries(Loop PUBLIC Window)
target_link_libraries(Loop PUBLIC Time)
target_link_libraries(EventHandler PUBLIC Window)

target_link_libraries(Window PUBLIC
    sfml-system
    sfml-window
    sfml-graphics
) # Window depends on SFML

add_library(ECS STATIC
    "src/Config.cpp"
)

target_link_libraries(ECS PUBLIC Time Loop Window EventHandler)

# print ECS include directories
get_target_property(ECS_INCLUDES ECS INCLUDE_DIRECTORIES)
message("ECS include directories: ${ECS_INCLUDES}")