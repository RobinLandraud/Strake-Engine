#include <ECS/Window.hpp>

namespace ECS
{
    Window::Window( int width,  int height, const std::string& title)
        : m_window(sf::VideoMode(width, height), title)
    {
    }

    Window::~Window()
    {
        m_window.close();
    }

    void Window::close()
    {
        m_window.close();
    }

    bool Window::isOpen() const
    {
        return m_window.isOpen();
    }

    void Window::clear()
    {
        m_window.clear();
    }

    void Window::display()
    {
        m_window.display();
    }

    sf::RenderWindow& Window::getRenderWindow()
    {
        return m_window;
    }
}