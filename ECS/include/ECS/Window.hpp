#include "SFML/Graphics.hpp"

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
            void close();
            bool isOpen() const;
            void clear();
            void display();
            sf::RenderWindow& getRenderWindow();

        private:
            sf::RenderWindow m_window;
    };
}
