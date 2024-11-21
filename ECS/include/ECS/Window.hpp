#pragma once
#include <ECS/Config.hpp>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <memory>
#include <stdexcept>
#include <string>
#include <glm/glm.hpp>

namespace ECS
{
    class Window
    {
        public:
            // avoid implicit conversions. the constructor have only one argument asked for (title) and the other two have default values.
            // explicit keyword is used to avoid implicit conversions in order to avoid bugs.
            // else, the constructor can be used as conversion operator.
            explicit Window(int width = 500, int height = 600, const std::string& title = "Window");
            ~Window();
            Window(const Window&) = delete; // copy constructor is deleted
            Window& operator=(const Window&) = delete; // copy assignment operator is deleted
            Window& operator=(Window&&) = delete; // move assignment operator is deleted
            Window(Window&&) = delete; // move constructor is deleted

            void close();
            [[nodiscard]] bool isOpen() const;
            static void clear();
            void display();
            GLFWwindow *getGLFWWindow();
            void setBgColor(const glm::vec4 &color);
            [[nodiscard]] glm::vec4 getBgColor() const;

        private:
            std::unique_ptr<GLFWwindow, decltype(&glfwDestroyWindow)> m_window;
            glm::vec4 m_bgColor;
    };
}
