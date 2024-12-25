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
find_package(assimp REQUIRED)

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
add_library(Application STATIC
    src/Application/GameLoop.cpp
    src/Application/Application.cpp
)
add_library(Dispatcher STATIC src/Dispatcher/EventDispatcher.cpp)
add_library(Window STATIC src/Window/Window.cpp)
add_library(EventHandler STATIC src/Window/EventHandler.cpp)
add_library(GameObject STATIC src/GameObject/GameObject.cpp)

# ////////////////////////////////////////////////////////////////////////
# Component librarie
add_library(Component STATIC src/Component/Component.cpp)

add_library(Transform STATIC src/Component/Transform.cpp)
add_library(Camera STATIC src/Component/Camera.cpp)
add_library(Script STATIC src/Component/Script.cpp)
add_library(MeshFilter STATIC
    src/Component/MeshFilter.cpp
    src/Component/Cube.cpp
)
add_library(MeshRenderer STATIC src/Component/MeshRenderer.cpp)
add_library(Light STATIC src/Component/Lights.cpp)

target_link_libraries(Component PUBLIC
    Transform
    Camera
    Script
    MeshFilter
    MeshRenderer
    Light
)

# ////////////////////////////////////////////////////////////////////////

add_library(Scene STATIC src/Scene/Scene.cpp)
add_library(LightManager STATIC src/Managers/LightManager.cpp)

# dependencies for the libraries
target_link_libraries(Window PUBLIC Config)
target_link_libraries(Application PUBLIC Window)
target_link_libraries(Application PUBLIC Time)
target_link_libraries(Application PUBLIC Scene)
target_link_libraries(EventHandler PUBLIC Window)
target_link_libraries(Component PUBLIC GameObject)

target_link_libraries(Scene PUBLIC GameObject)
target_link_libraries(Scene PUBLIC Component)
target_link_libraries(Scene PUBLIC Camera)
target_link_libraries(Scene PUBLIC Transform)
target_link_libraries(Scene PUBLIC LightManager)

target_link_libraries(GameObject PUBLIC Script)
target_link_libraries(GameObject PUBLIC Scene)

target_link_libraries(Transform PUBLIC Component)
target_link_libraries(Camera PUBLIC Component)
target_link_libraries(Camera PUBLIC Transform)
target_link_libraries(Script PUBLIC Component)
target_link_libraries(MeshFilter PUBLIC Component)
target_link_libraries(MeshRenderer PUBLIC Component MeshFilter)

target_link_libraries(Application PUBLIC
    Threads::Threads
    GLEW::GLEW
    OpenGL::GL
    OpenGL::GLU
    glfw
    assimp::assimp
) # Window depends on SFML

add_library(ECS STATIC
    "src/init.cpp"
)

target_link_libraries(ECS PUBLIC
    Config
    Time
    Material
    Shader
    Window
    EventHandler
    Component
    LightManager
    Scene
    GameObject
    Dispatcher
    Application
)