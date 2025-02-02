#include <Strake/Window/Window.hpp>
#include <Strake/Window/EventHandler.hpp>
#include <Strake/Time/Time.hpp>
#include <iostream>

namespace Strake
{
    Window::Window( int width, int height, const std::string& title) :
        m_window(nullptr, glfwDestroyWindow),
        m_bgColor(0.0f, 0.0f, 0.0f, 1.0f),
        m_width(width),
        m_height(height),
        m_cursorEnabled(false)
    {
        GLint majorVersion, minorVersion;

        if (glfwInit() == 0) {
            std::cout << "Failed to initialize GLFW" << std::endl;
            throw std::runtime_error("Failed to initialize GLFW");
        }
        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, ECS_GLFW_VERSION_MAJOR);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, ECS_GLFW_VERSION_MINOR);
        glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

        m_window.reset(glfwCreateWindow(m_width, m_height, title.c_str(), nullptr, nullptr));
        if (!m_window)
        {
            std::cout << "Failed to create window" << std::endl;
            glfwTerminate();
            throw std::runtime_error("Failed to create window");
        }
        glfwMakeContextCurrent(m_window.get());
        glfwSwapInterval(0); // Disable VSync
        
        glewExperimental = GL_TRUE;
        if (glewInit() != GLEW_OK)
        {
            std::cout << "Failed to initialize GLEW" << std::endl;
            glfwTerminate();
            throw std::runtime_error("Failed to initialize GLEW");
        }

        glGetIntegerv(GL_MAJOR_VERSION, &majorVersion);
        glGetIntegerv(GL_MINOR_VERSION, &minorVersion);
        if (majorVersion < ECS_GLFW_VERSION_MAJOR || (majorVersion == ECS_GLFW_VERSION_MAJOR && minorVersion < ECS_GLFW_VERSION_MINOR))
        {
            std::cout << "OpenGL version is not supported" << std::endl;
            std::cout << "OpenGL version: " << majorVersion << "." << minorVersion << std::endl;
            std::cout << "Supported version: " << ECS_GLFW_VERSION_MAJOR << "." << ECS_GLFW_VERSION_MINOR << std::endl;
            glfwTerminate();
            throw std::runtime_error("OpenGL version is not supported");
        }

        glfwGetFramebufferSize(m_window.get(), &m_width, &m_height);
        glViewport(0, 0, m_width, m_height);
        glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
        glfwSetInputMode(m_window.get(), GLFW_CURSOR, GLFW_CURSOR_DISABLED);

        // Initialize the event handler and time singletons
        EventHandler::init(*this);
        Time::init();
    }

    Window::~Window()
    {
        glfwDestroyWindow(m_window.get());
        //destroy singletons
        EventHandler::destroy();
        Time::destroy();
    }

    int Window::getWidth() const
    {
        return m_width;
    }

    int Window::getHeight() const
    {
        return m_height;
    }

    void Window::close()
    {
        glfwSetWindowShouldClose(m_window.get(), GLFW_TRUE);
    }

    bool Window::isOpen() const
    {
        return glfwWindowShouldClose(m_window.get()) == 0;
    }

    void Window::clear()
    {
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    }

    void Window::display()
    {
        glfwSwapBuffers(m_window.get());
    }

    GLFWwindow *Window::getGLFWWindow()
    {
        return m_window.get();
    }

    void Window::setBgColor(const glm::vec4 &color)
    {
        m_bgColor = color;
        glClearColor(color.r, color.g, color.b, color.a);
    }

    glm::vec4 Window::getBgColor() const
    {
        return m_bgColor;
    }

    void Window::setCursorEnabled(bool enabled)
    {
        m_cursorEnabled = enabled;
        if (enabled == true) {
            glfwSetInputMode(m_window.get(), GLFW_CURSOR, GLFW_CURSOR_NORMAL);
        } else {
            glfwSetInputMode(m_window.get(), GLFW_CURSOR, GLFW_CURSOR_DISABLED);
        }
    }

    bool Window::isCursorEnabled() const
    {
        return m_cursorEnabled;
    }
}