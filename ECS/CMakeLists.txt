set(CMAKE_MODULE_PATH ${CMAKE_SOURCE_DIR}/cmake)
set(CMAKE_CXX_STANDARD 20)
cmake_minimum_required(VERSION 3.10)
# Project name
project(ECS)
# Set the directory for ECS headers
include_directories(include)

# find_package(Threads REQUIRED)

set(CMAKE_TOOLCHAIN_FILE "./vcpkg/scripts/buildsystems/vcpkg.cmake" CACHE STRING "vcpkg toolchain file")

find_package(GLEW REQUIRED)
find_package(OpenGL REQUIRED)
find_package(glfw3 REQUIRED)

add_library(Config STATIC src/Config/Config.cpp)
add_library(Time STATIC src/Time/Time.cpp)
add_library(Material STATIC
    src/Material/Texture.cpp
    src/Material/Texture2D.cpp
    src/Material/Texture3D.cpp
    src/Material/Material.cpp
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
add_library(Script STATIC src/Component/Script.cpp)
add_library(MeshFilter STATIC
    src/Component/MeshFilter.cpp
    src/Component/Cube.cpp
)
add_library(MeshRenderer STATIC src/Component/MeshRenderer.cpp)
add_library(Scene STATIC src/Scene/Scene.cpp)

# dependencies for the libraries
target_link_libraries(Window PUBLIC Config)
target_link_libraries(Loop PUBLIC Window)
target_link_libraries(Loop PUBLIC Time)
target_link_libraries(Loop PUBLIC Scene)
target_link_libraries(EventHandler PUBLIC Window)
target_link_libraries(Component PUBLIC GameObject)

target_link_libraries(Scene PUBLIC GameObject)
target_link_libraries(Scene PUBLIC Component)
target_link_libraries(Scene PUBLIC Camera)
target_link_libraries(Scene PUBLIC Transform)

target_link_libraries(GameObject PUBLIC Script)

target_link_libraries(Transform PUBLIC Component)
target_link_libraries(Camera PUBLIC Component)
target_link_libraries(Camera PUBLIC Transform)
target_link_libraries(Script PUBLIC Component)
target_link_libraries(MeshFilter PUBLIC Component)
target_link_libraries(MeshRenderer PUBLIC Component MeshFilter)

target_link_libraries(Window PUBLIC
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
    Material
    Shader
    Loop
    Window
    EventHandler
    Component
    Transform
    Camera
    Script
    MeshFilter
    MeshRenderer
    Scene
    GameObject
)