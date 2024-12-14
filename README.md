<!-- SFML ECS README -->
<!-- PROJECT TITLE -->
<br />
<div align="center">
  <h3 align="center">Strake Engine</h3>
  <img src="https://lh3.googleusercontent.com/a/ACg8ocIsjIU3xM7l5ABRwugyCarsL4uCXD2IcIKEhLyz3cdW5tCOCyEd=s288-c-no" alt="Circular Image" width="150" height="150" style="border-radius: 50%; overflow: hidden;">
  <p align="center">
    A full designed GameObject Component System with OpenGL
    <br />
    <a href="https://github.com/RobinLandraud/SFML_ECS"><strong>" Explore the docs "</strong></a>
  </p>
</div>
<!-- TABLE OF CONTENTS -->
<details>
  <summary>Table of Contents</summary>
  <ol>
    <li>
      <a href="#about-the-project">About The Project</a>
      <ul>
        <li><a href="#built-with">Built With</a></li>
      </ul>
    </li>
    <li>
      <a href="#getting-started">Getting Started</a>
      <ul>
        <li><a href="#prerequisites">Prerequisites</a></li>
        <li><a href="#installation">Installation</a></li>
      </ul>
    </li>
    <li><a href="#usage">Usage</a></li>
    <li><a href="#roadmap">Roadmap</a></li>
    <li><a href="#license">License</a></li>
    <li><a href="#contact">Contact</a></li>
    <li><a href="#acknowledgments">Acknowledgments</a></li>
  </ol>
</details>

<!-- ABOUT THE PROJECT -->
## About The Project

With this project, I aimed to develop a comprehensive  GameObject Component System using Open Graphics Library (OpenGL). The goal is to create more stable and maintainable projects/games through a well-structured hierarchy that is both readable and easily modifiable.

Inspired by Unity, this ECS optimizes games automatically by updating entities at multiple frequency scales, ensuring efficient performance.

### Built With

Our engine is built using a combination of powerful and flexible technologies to provide a smooth and efficient experience for both developers and users. Key components include:

- **C++**: The core of the engine is written in C++, enabling high performance, low-level access, and flexibility for complex systems.
- **OpenGL**: For rendering, OpenGL is used to handle 2D and 3D graphics, allowing for smooth and immersive visuals.
- **GLEW**: **GLEW** (OpenGL Extension Wrangler) is used to manage OpenGL extensions, ensuring that the engine is compatible with a wide range of OpenGL features across different platforms.
- **GLM**: The **GLM** library is utilized for math operations, providing essential functions for handling vectors, matrices, and transformations in 3D space.
- **GLFW**: For managing windows, input, and context creation, **GLFW** provides a simple and cross-platform solution.
- **STB Image**: **STB Image** handles texture loading, making it easy to import and work with various image formats in our rendering pipeline.
- **CMake**: Our build system is powered by **CMake**, simplifying the process of building the engine and its dependencies across different platforms.

These technologies come together to create an engine that is both powerful and easy to extend, providing a solid foundation for game development, simulation, and other interactive applications.

## Getting Started

Follow these steps to set up and run the engine on your machine.

### Prerequisites

Before you begin, ensure you have the following installed:

> 💡 **Note for Windows Users:** Library management is handled using the **vcpkg** package manager. Refer to the Windows installation steps for details.

- **C++ Compiler**: A C++17 or later compatible compiler (e.g., GCC, Clang, or MSVC).
- **CMake**: A cross-platform build system. [CMake](https://cmake.org/).
- **OpenGL**: A modern OpenGL-compatible GPU and drivers.
- **GLEW**: OpenGL Extension Wrangler. [GLEW](http://glew.sourceforge.net/).
- **GLFW**: A library for window and input management. [GLFW](https://www.glfw.org/).
- **GLM**: Header-only math library. [GLM](https://github.com/g-truc/glm).
- **STB Image**: Header-only library for image loading. Typically included in the project.

Additionally, ensure you have:

- **Git**: For cloning the repository. [Git](https://git-scm.com/).

### Installation

1. **Clone the Repository**  
   Open your terminal or command prompt and run:
   ```bash
   git clone https://github.com/RobinLandraud/Strake-Engine
   cd Strake-Engine
   ```

2. **Install Dependencies**

   Ensure all prerequisite libraries are installed before compiling the project.

   - **On Linux**: Libraries are typically managed through your package manager and located via the `PATH` environment variable. Ensure all required libraries are properly installed and accessible.

   - **On Windows**: Dependencies are managed using **vcpkg**. You need to update the `vcpkg` variable in the `justfile` located in the root directory of the project. Set this variable to the path of your vcpkg installation to handle the prerequisite libraries. For example:
     ```bash
     vcpkg := "C:/path/to/vcpkg"
     ```

3. **Compile the Project**

   Once the dependencies are installed, you can proceed to compile the engine:

   - **On Linux**:  
     Open a terminal, navigate to the project directory, and build the project with justfile:
     ```bash
     just build
     ```
     After the build is complete, the executable will be available at the root of the project under the name **Strake.out**

   - **On Windows**:  
     Open a terminal or command prompt, navigate to the project directory, and build the project with justfile:
     ```bash
     just build-windows
     ```
     After the build is complete, the executable will be available at the root of the project under the name **Strake.exe**
---

These steps will ensure the engine is properly compiled and ready to run on your platform.

## Usage

To begin, we create a window and initialize the ECS system. You can set up your scene and add objects within it.
### 1. Create a window and initialize ECS

```bash
ECS::Window window(WIN_WIDTH, WIN_HEIGHT, "Strake Engine Example");
ECS::init();
```

### 2. Setup the singletons
```bash
ECS::EventHandler::init(window);
ECS::Time::init();
```

### 3. Create a material

```bash
ECS::Texture2D texture("path/to/image")
if (!textureBarel.isLoaded()) {
    std::cout << "Failed to load texture" << std::endl;
}
ECS::Material plasticMaterial;
metalicMaterial.addTexture(texture, "textureSampler");
metalicMaterial.setShininess(256.0f);
```

### 4. Create a Scene

```bash
ECS::Scene scene;
```

### 5. Add a Gameobject with Mesh

```bash
ECS::GameObject &object = scene.addGameObject("Cube");
object.getTransform().setLocalPosition(glm::vec3(x, y, z));
object.addComponent<ECS::Cube>();
object.addComponent<ECS::MeshRenderer>(metalicMaterial);
```

### 6. Add a Camera

```bash
ECS::GameObject &player = scene.addGameObject("Main Camera");
player.addComponent<ECS::Camera>();
ECS::Camera &cam = player.getComponent<ECS::Camera>();
cam.setProjection(45.0f, static_cast<float>(WIN_WIDTH) / static_cast<float>(WIN_HEIGHT), 0.1f, 100.0f);
player.getTransform().setLocalPosition(glm::vec3(x, y, z));
scene.setMainCamera(cam);
```

### 7. Create and add a Script

```bash
class CharacterController: public ECS::Script
{
    public:
        using ECS::Script::Script;
        void awake() override {
            transform = getParent().getTransform();
        }
        void update() override {
            const ECS::mouse_t &mouse = ECS::EventHandler::getMouse();
            ECS::Transform &transform = this->transform.value();
            if (ECS::EventHandler::isKeyHeld(ECS::Key::W)) {
                transform.translateLocal(glm::vec3(0.0f, 0.0f, m_speed * ECS::Time::getDeltaTime()));
            } else if (ECS::EventHandler::isKeyHeld(ECS::Key::S)) {
                transform.translateLocal(glm::vec3(0.0f, 0.0f, -m_speed * ECS::Time::getDeltaTime()));
            }
            ...
            float yaw = mouse.x;
            float roll = mouse.y;
            transform.setLocalRotation(glm::vec3(-roll, -yaw, 0.0f));
        }
    private:
        std::optional<std::reference_wrapper<ECS::Transform>> transform;
        const float m_speed = 10.0f;
};
```

```bash
player.addComponent<CharacterController>();
```

### 8. Run the Scene

```bash
scene.awake();
scene.start()
ECS::Loop loop(fps);
loop.run(window, scene, false);
```

### 9. Destroy the singletons

```bash
ECS::EventHandler::destroy();
ECS::Time::destroy();
```

### 10. Exit the engine

```bash
ECS::exit()
```

## Roadmap

### Current Features

- **Core Systems**:
  - **Event Handler**: Centralized system to manage and dispatch events.
  - **Shader Programs and Shaders**: Customizable shader pipeline to enhance visual effects.
  - **Materials**: Supports textures for customizable appearances.
  - **Scenes**: Manages hierarchical game objects and components.
  - **GameObjects and Components**: Core structure for building and organizing entities in the engine.
  - **Window Management**: Provides robust cross-platform window creation and handling.

- **Components**:
  - **Camera**: Fully functional component for rendering scenes.
  - **Transforms**: Supports local and global space transformations.
  - **Lights**: Includes point lights (with plans to add more types in the future).
  - **MeshFilter**: Handles 3D meshes, including default primitives (e.g., cubes) and support for OBJ file loading.
  - **MeshRenderer**: Renders 3D meshes with materials and lighting.
  - **Script Component**: Allows users to attach custom scripts to GameObjects as components.

- **Entity Component System (ECS)**:
  - Modular architecture with a game loop that includes the following lifecycle methods:
    - `awake()`: Called when a component is created or initialized.
    - `start()`: Called before the first frame update.
    - `update()`: Runs every frame for dynamic behaviors.
    - `fixedUpdate()`: Runs at a fixed interval for physics or time-sensitive updates.
    - `lateUpdate()`: Called after all `update()` calls, ensuring post-update adjustments.
    - `render()`: Responsible for rendering components such as meshes, lights, and cameras each frame.

### Upcoming Features

- **Basic Physics Engine**: Implement a simple physics engine for rigidbody movement, gravity, and collisions.
- **CollisionBox**: Add collision detection with basic bounding boxes for handling physical interactions.
- **Lighting**: Expand lighting system to support additional light types such as directional lights and spotlights.
- **Enhanced Transform API**: Improve the `Transform` class to provide better support for world space transformations and related methods.

### Milestones
- **v0.1**: Initial stable release with ECS and basic rendering

### License

Distributed under the MIT License. See [LICENSE](LICENSE) for more information.

### Contact

GitHub: [RobinLandraud](https://github.com/RobinLandraud)  
LinkedIn: [robin-landraud](https://www.linkedin.com/in/robin-landraud/)

### Acknowledgments

- OpenGL: For enabling cross-platform graphics rendering.
- GLEW: For handling OpenGL extensions.
- GLFW: For managing windows and input.
- GLM: For providing math utilities for 3D transformations.
- STB Image: For image loading and texture handling.
- CMake: For simplifying the build process across platforms.
