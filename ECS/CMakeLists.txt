set(CMAKE_MODULE_PATH ${CMAKE_SOURCE_DIR}/cmake)
set(CMAKE_CXX_STANDARD 20)
cmake_minimum_required(VERSION 3.10)
# Project name
project(ECS)
# Set the directory for ECS headers
include_directories(include)

find_package(SFML 2.5 COMPONENTS system window graphics network audio REQUIRED)
find_package(Threads REQUIRED)
find_package(GLEW REQUIRED)
find_package(OpenGL REQUIRED)
find_package(glfw3 REQUIRED)

add_library(Config STATIC src/Config/Config.cpp)
add_library(Time STATIC src/Time/Time.cpp)
add_library(Texture STATIC
    src/Texture/Texture.cpp
    src/Texture/Texture2D.cpp
    src/Texture/Texture3D.cpp
)
add_library(Shader STATIC
    src/Shader/Shader.cpp
    src/Shader/ShaderProgram.cpp
)
add_library(Loop STATIC src/Loop/Loop.cpp)
add_library(Window STATIC src/Window/Window.cpp)
add_library(EventHandler STATIC src/Window/EventHandler.cpp)
add_library(GameObject STATIC src/GameObject/GameObject.cpp)
add_library(Component STATIC src/Component/Component.cpp)
add_library(Transform STATIC src/Component/Transform.cpp)
add_library(Camera STATIC src/Component/Camera.cpp)

# dependencies for the libraries
target_link_libraries(Window PUBLIC Config)
target_link_libraries(Loop PUBLIC Window)
target_link_libraries(Loop PUBLIC Time)
target_link_libraries(EventHandler PUBLIC Window)
target_link_libraries(Component PUBLIC GameObject)

target_link_libraries(Transform PUBLIC Component)
target_link_libraries(Camera PUBLIC Component)

target_link_libraries(Window PUBLIC
    sfml-system
    sfml-window
    sfml-graphics
    Threads::Threads
    GLEW::GLEW
    OpenGL::GL
    OpenGL::GLU
    glfw
) # Window depends on SFML

add_library(ECS STATIC
    "src/init.cpp"
)

target_link_libraries(ECS PUBLIC
    Config
    Time
    Texture
    Shader
    Loop
    Window
    EventHandler
    Component
    Transform
    Camera
)