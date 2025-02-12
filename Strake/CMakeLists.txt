set(CMAKE_MODULE_PATH ${CMAKE_SOURCE_DIR}/cmake)
set(CMAKE_CXX_STANDARD 20)
cmake_minimum_required(VERSION 3.10)
# Project name
project(Strake)
# Set the directory for Strake headers
include_directories(include)

# find_package(Threads REQUIRED)

set(CMAKE_TOOLCHAIN_FILE "./vcpkg/scripts/buildsystems/vcpkg.cmake" CACHE STRING "vcpkg toolchain file")

find_package(GLEW REQUIRED)
find_package(OpenGL REQUIRED)
find_package(glfw3 REQUIRED)
find_package(assimp REQUIRED)

add_library(Config STATIC
    src/Config/Config.cpp
)
add_library(Time STATIC
    src/Time/Time.cpp
)
add_library(Texture STATIC
    src/Texture/Texture.cpp
    src/Texture/Texture2D.cpp
    src/Texture/Texture3D.cpp
)
add_library(Material STATIC
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
add_library(Dispatcher STATIC
    src/Dispatcher/Event.cpp
    src/Dispatcher/EventDispatcher.cpp
)
add_library(Window STATIC
    src/Window/Window.cpp
)
add_library(EventHandler STATIC
    src/Window/EventHandler.cpp
)
add_library(GameObject STATIC
    src/GameObject/GameObject.cpp
)

# ////////////////////////////////////////////////////////////////////////
# Component librarie
add_library(Component STATIC
    src/Component/Component.cpp
    src/Component/Transform.cpp
    src/Component/Camera.cpp
    src/Component/Script.cpp
    src/Component/MeshFilter/MeshFilter.cpp
    src/Component/MeshFilter/Cube.cpp
    src/Component/MeshFilter/Plane.cpp
    src/Component/MeshFilter/Sphere.cpp
    src/Component/MeshFilter/Capsule.cpp
    src/Component/Renderer/Renderer.cpp
    src/Component/Renderer/MeshRenderer.cpp
    src/Component/Renderer/WireFrameRenderer.cpp
    src/Component/Light/Light.cpp
    src/Component/Light/DirectionalLight.cpp
    src/Component/Light/PointLight.cpp
    src/Component/Light/ShadowMap.cpp
    src/Component/Collider/Collider.cpp
    src/Component/Collider/BoxCollider.cpp
    src/Component/Collider/SphereCollider.cpp
)

# ////////////////////////////////////////////////////////////////////////

add_library(Scene STATIC src/Scene/Scene.cpp)
add_library(Managers STATIC
    src/Manager/LightManager.cpp
    src/Manager/RendererManager.cpp
    src/Manager/MaterialManager.cpp
    src/Manager/TextureManager.cpp
    src/Manager/SceneManager.cpp
    src/Manager/ScriptManager.cpp
    src/Manager/PhysicsManager/PhysicsManager.cpp
    src/Manager/PhysicsManager/ColliderManager.cpp
)

# dependencies for the libraries
target_link_libraries(Window PUBLIC Config)
target_link_libraries(Application PUBLIC Window)
target_link_libraries(Application PUBLIC Time)
target_link_libraries(Application PUBLIC Scene)
target_link_libraries(EventHandler PUBLIC Window)
target_link_libraries(Component PUBLIC GameObject)
target_link_libraries(Scene PUBLIC GameObject)
target_link_libraries(Scene PUBLIC Component)
target_link_libraries(Scene PUBLIC Managers)
target_link_libraries(GameObject PUBLIC Component)
target_link_libraries(GameObject PUBLIC Scene)
target_link_libraries(Component PUBLIC Texture)

target_link_libraries(Application PUBLIC
    Threads::Threads
    GLEW::GLEW
    OpenGL::GL
    OpenGL::GLU
    glfw
    assimp::assimp
) # Window depends on SFML

add_library(Strake STATIC
    "src/init.cpp"
)

target_link_libraries(Strake PUBLIC
    Config
    Time
    Material
    Shader
    Window
    EventHandler
    Component
    Managers
    Scene
    GameObject
    Dispatcher
    Application
)

# enable compile_commands.json
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# Set the path to the resources (Release/Debug folder depending on the build type)
if (WIN32)
    add_compile_definitions(RESOURCES_PATH="resources")
    if (CMAKE_BUILD_TYPE STREQUAL "Release")
        set(RESOURCES_PATH "${CMAKE_SOURCE_DIR}/Release/resources")
    else()
        set(RESOURCES_PATH "${CMAKE_SOURCE_DIR}/Debug/resources")
    endif()
    message("[X] RESOURCES_PATH set to: resources")
    add_custom_command(TARGET Strake POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E make_directory ${RESOURCES_PATH}
        COMMAND ${CMAKE_COMMAND} -E copy_directory
        ${CMAKE_CURRENT_SOURCE_DIR}/resources
        ${RESOURCES_PATH}
        COMMENT "[X] Copying resources directory to ${RESOURCES_PATH}"
    )
endif()