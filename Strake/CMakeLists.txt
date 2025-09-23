set(CMAKE_MODULE_PATH ${CMAKE_SOURCE_DIR}/cmake)
set(CMAKE_CXX_STANDARD 20)
cmake_minimum_required(VERSION 3.10)

###############################################################
### Policy settings
###############################################################
cmake_policy(SET CMP0072 NEW) # FindOpenGL prefers GLVND by default when available

# Project name
project(Strake)
# Set the directory for Strake headers
include_directories(include)

# find_package(Threads REQUIRED)

find_package(GLEW REQUIRED)
find_package(OpenGL REQUIRED)
find_package(glfw3 REQUIRED)
find_package(assimp REQUIRED)
find_package(glm CONFIG REQUIRED)

add_library(Strake STATIC
    "src/init.cpp"
)
add_library(Config STATIC
    src/Config/Config.cpp
)
add_library(Time STATIC
    src/Time/Time.cpp
)
add_library(Dispatcher STATIC
    src/Dispatcher/Event.cpp
    src/Dispatcher/EventDispatcher.cpp
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
add_library(Window STATIC
    src/Window/Window.cpp
)
add_library(EventHandler STATIC
    src/Window/EventHandler.cpp
)
add_library(GameObject STATIC
    src/GameObject/GameObject.cpp
)
add_library(Layer STATIC
    src/Layer/Layer.cpp
    src/Layer/CullingMask.cpp
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
    src/Component/UI/UI.cpp
    src/Component/UI/Image.cpp
)

# ////////////////////////////////////////////////////////////////////////

add_library(Scene STATIC src/Scene/Scene.cpp)
add_library(Managers STATIC
    src/Manager/LayerManager.cpp
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

target_link_libraries(Layer PUBLIC
    glm::glm
)

target_link_libraries(Shader PUBLIC
    GLEW::GLEW
)

target_link_libraries(Texture PUBLIC
    GLEW::GLEW
)

target_link_libraries(Application PUBLIC
    Managers
    Window
    Time
    Scene
    Strake # use strake .cpp for init
)

target_link_libraries(Window PUBLIC
    Config
    GLEW::GLEW
) # Config have no dependency
target_link_libraries(EventHandler PUBLIC Window)

target_link_libraries(Managers PUBLIC
    Dispatcher
    Component
    GameObject
    Layer
    Material
    Scene
    Texture
)
target_link_libraries(Material PUBLIC
    Shader # no dependency
    Texture # no dependency
)
target_link_libraries(Scene PUBLIC
    GameObject
    Managers
    Component
)
target_link_libraries(Component PUBLIC
    GameObject
    Dispatcher
)
target_link_libraries(GameObject PUBLIC
    Dispatcher
    Layer # don't have dependency
)

target_link_libraries(Application PUBLIC
    Threads::Threads
    GLEW::GLEW
    OpenGL::GL
    OpenGL::GLU
    glfw
    assimp::assimp
    glm::glm
) # Window depends on SFML

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
    Layer 
)

# enable compile_commands.json
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

if(NOT DEFINED STRAKE_RESOURCES)
    message("[X] STRAKE_RESOURCES not defined, using default path")
    set(STRAKE_RESOURCES "${CMAKE_CURRENT_SOURCE_DIR}/resources")
endif()

add_compile_definitions(RESOURCES_PATH="${STRAKE_RESOURCES}")