#include <ECS/Window.hpp>

namespace ECS
{
    Window::Window( int width, int height, const std::string& title) :
        m_window(nullptr, glfwDestroyWindow),
        m_bgColor(0.0f, 0.0f, 0.0f, 1.0f),
        m_width(width),
        m_height(height)
    {
        if (glfwInit() == 0) {
            throw std::runtime_error("Failed to initialize GLFW");
        }
        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, ECS_GLFW_VERSION_MAJOR);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, ECS_GLFW_VERSION_MINOR);
        glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
        m_window.reset(glfwCreateWindow(width, height, title.c_str(), nullptr, nullptr));
        if (!m_window)
        {
            glfwTerminate();
            throw std::runtime_error("Failed to create window");
        }
        glfwMakeContextCurrent(m_window.get());
        glewExperimental = GL_TRUE;
        if (glewInit() != GLEW_OK)
        {
            throw std::runtime_error("Failed to initialize GLEW");
        }
        glfwGetFramebufferSize(m_window.get(), &width, &height);
        glViewport(0, 0, width, height);
        glEnable(GL_BLEND);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
        glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
        //glfwSetInputMode(m_window.get(), GLFW_CURSOR, GLFW_CURSOR_DISABLED); // Hide cursor
    }

    Window::~Window()
    {
        glfwDestroyWindow(m_window.get());
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
}