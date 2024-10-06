#include <SFML/Graphics.hpp>

int main()
{
    sf::RenderWindow window(sf::VideoMode(800, 600), "SFML Holes with Shaders");
    window.setVerticalSyncEnabled(false);

    sf::RenderTexture target;
    if (!target.create(window.getSize().x, window.getSize().y))
        return -1;

    sf::Texture texture;
    if (!texture.loadFromFile("texture.jpg"))
        return -1;
    sf::Sprite sprite(texture);
    sf::Vector2u windowSize = target.getSize();
    sf::Vector2u textureSize = texture.getSize();
    float scaleX = static_cast<float>(windowSize.x) / textureSize.x;
    float scaleY = static_cast<float>(windowSize.y) / textureSize.y;
    sprite.setScale(scaleX, scaleY);

    sf::Texture texture2;
    if (!texture2.loadFromFile("texture2.jpg"))
        return -1;
    sf::Sprite sprite2(texture2);
    sf::Vector2u textureSize2 = texture2.getSize();
    float scaleX2 = static_cast<float>(windowSize.x) / textureSize2.x;
    float scaleY2 = static_cast<float>(windowSize.y) / textureSize2.y;
    sprite2.setScale(scaleX2, scaleY2);

    target.draw(sprite);
    target.display();

    // Load the shader
    sf::Shader shader;
    if (!shader.loadFromFile("mouse_visibility.frag", sf::Shader::Fragment))
        return -1;

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        // Draw a point where the mouse is clicked
        if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
        {
            sf::Vertex point(sf::Vector2f(sf::Mouse::getPosition(window)), sf::Color::Transparent);
            target.draw(&point, 1, sf::Points, sf::BlendNone);
            target.display();
        }

        // Get mouse position in normalized coordinates
        sf::Vector2i mousePos = sf::Mouse::getPosition(window);
        sf::Vector2f normalizedMousePos(
            static_cast<float>(mousePos.x) / window.getSize().x,
            1.0f - (static_cast<float>(mousePos.y) / window.getSize().y) // Invert Y here
        );

        // Calculate aspect ratios
        float aspectRatioX = static_cast<float>(window.getSize().x) / window.getSize().y;
        float aspectRatioY = static_cast<float>(window.getSize().y) / window.getSize().y; // This will always be 1.0

        shader.setUniform("texture", target.getTexture());
        shader.setUniform("mousePos", normalizedMousePos);
        shader.setUniform("radius", 0.1f); // Keep the radius uniform
        shader.setUniform("aspectRatio", sf::Vector2f(aspectRatioX, aspectRatioY)); // Set aspect ratios

        window.clear();

        // Create a sprite for the target texture
        sf::Sprite sprite(target.getTexture());

        // Draw the sprite with the shader
        window.draw(sprite2);
        window.draw(sprite, &shader);
        window.display();
    }

    return 0;
}
