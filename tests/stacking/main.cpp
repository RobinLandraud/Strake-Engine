#include <GL/glew.h>
#include <SFML/OpenGL.hpp>
#include <GL/glu.h>
#include <SFML/Graphics.hpp>
#include <iostream>
#include <SFML/Window.hpp>
#include <vector>
#include <cmath>

// Function to set up OpenGL
void initOpenGL() {
    // Enable depth testing for 3D rendering
    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LESS);

    // Enable texturing
    glEnable(GL_TEXTURE_2D);

    // Enable blending
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA); // Set blending function

    // Set up a perspective projection
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(45.0f, 800.0f / 600.0f, 1.0f, 150.0f);
}

// Create the sprite stack VAO and VBOs
GLuint createSpriteStackVAO(const sf::Texture& texture, int numberOfLayers, float spriteWidth, float spriteHeight, float spacing, GLuint& vboID, GLuint& texCoordVBO) {
    GLuint vaoID;
    glGenVertexArrays(1, &vaoID);
    glBindVertexArray(vaoID);

    // Create a new VBO for vertices
    glGenBuffers(1, &vboID);
    glBindBuffer(GL_ARRAY_BUFFER, vboID);

    // Calculate the total number of vertices needed
    int totalVertices = 4 * numberOfLayers;
    std::vector<GLfloat> vertices(totalVertices * 3);  // 3 components per vertex (x, y, z)
    std::vector<GLfloat> texCoords(totalVertices * 2); // 2 components per texture coordinate

    // Fill the vertex buffer with sprite layer positions and texture coordinates
    for (int i = 0; i < numberOfLayers; ++i) {
        float x0 = -spriteWidth / 2;
        float x1 = spriteWidth / 2;
        float y0 = -spriteHeight / 2;
        float y1 = spriteHeight / 2;
        float z = i * spacing;

        // Vertex positions
        vertices[i * 12 + 0] = x0; vertices[i * 12 + 1] = y0; vertices[i * 12 + 2] = z; // Bottom-left
        vertices[i * 12 + 3] = x1; vertices[i * 12 + 4] = y0; vertices[i * 12 + 5] = z; // Bottom-right
        vertices[i * 12 + 6] = x1; vertices[i * 12 + 7] = y1; vertices[i * 12 + 8] = z; // Top-right
        vertices[i * 12 + 9] = x0; vertices[i * 12 + 10] = y1; vertices[i * 12 + 11] = z; // Top-left

        // Texture coordinates
        float u0 = (i * spriteWidth) / texture.getSize().x; // Left u-coordinate for current layer
        float u1 = ((i + 1) * spriteWidth) / texture.getSize().x; // Right u-coordinate for current layer
        texCoords[i * 8 + 0] = u0; texCoords[i * 8 + 1] = 0.0f; // Bottom-left
        texCoords[i * 8 + 2] = u1; texCoords[i * 8 + 3] = 0.0f; // Bottom-right
        texCoords[i * 8 + 4] = u1; texCoords[i * 8 + 5] = 1.0f; // Top-right
        texCoords[i * 8 + 6] = u0; texCoords[i * 8 + 7] = 1.0f; // Top-left
    }

    // Upload the vertex data to the VBO
    glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(GLfloat), vertices.data(), GL_STATIC_DRAW);
    glEnableClientState(GL_VERTEX_ARRAY);
    glVertexPointer(3, GL_FLOAT, 0, 0);

    // Create and upload the texture coordinate data to the VBO
    glGenBuffers(1, &texCoordVBO);
    glBindBuffer(GL_ARRAY_BUFFER, texCoordVBO);
    glBufferData(GL_ARRAY_BUFFER, texCoords.size() * sizeof(GLfloat), texCoords.data(), GL_STATIC_DRAW);
    glEnableClientState(GL_TEXTURE_COORD_ARRAY);
    glTexCoordPointer(2, GL_FLOAT, 0, 0);

    glBindVertexArray(0); // Unbind the VAO

    return vaoID;
}

// Function to render the sprite stack VAO
void renderSpriteStackVAO(GLuint vaoID, const sf::Texture& texture, int numberOfLayers) {
    // Bind the texture
    GLuint textureID = texture.getNativeHandle();
    glBindTexture(GL_TEXTURE_2D, textureID);

    // Bind the VAO
    glBindVertexArray(vaoID);

    // Draw the sprite stack
    glDrawArrays(GL_QUADS, 0, 4 * numberOfLayers);

    glBindVertexArray(0); // Unbind the VAO
}

int main() {

    // Create the window
    auto settings = sf::ContextSettings();
    settings.depthBits = 24;
    settings.stencilBits = 8;
    settings.antialiasingLevel = 0;
    settings.majorVersion = 3;
    settings.minorVersion = 1;
    settings.sRgbCapable = false;

    float carX = 0.0f; // Initial car X position
    float carY = 0.0f; // Initial car Y position
    const float carSpeed = 0.5f; // Car movement speed

    sf::RenderWindow window(sf::VideoMode(800, 600), "Sprite Stacking with OpenGL", sf::Style::Default, settings);
    window.setVerticalSyncEnabled(false);

    glewExperimental = GL_TRUE;
    if (glewInit() != GLEW_OK) {
        std::cerr << "Failed to initialize GLEW" << std::endl;
        return -1;
    }

    // Load the ground texture
    sf::Texture groundTexture;
    if (!groundTexture.loadFromFile("sprites/grass.png")) {
        std::cerr << "Failed to load ground texture" << std::endl;
        return -1;
    }
    // Create the sprite for the ground
    sf::Sprite groundSprite;
    groundSprite.setTexture(groundTexture);
    groundSprite.setPosition(0, 0); // Set position to the bottom of the window
    groundSprite.setScale(groundTexture.getSize().x / 800.0f, groundTexture.getSize().y / 600.0f); // Scale to window size

    // Initialize OpenGL settings
    initOpenGL();

    // Load the car sprite texture (sprite sheet)
    sf::Texture carTexture;
    if (!carTexture.loadFromFile("sprites/BlueCar.png")) {
        std::cerr << "Failed to load car texture" << std::endl;
        return -1;
    }

    // Create the sprite stack VAO and VBOs
    GLuint carVBO, carTexCoordVBO;
    GLuint carVAO = createSpriteStackVAO(carTexture, 9, carTexture.getSize().x / 9, carTexture.getSize().y, 0.6f, carVBO, carTexCoordVBO);

    // Parameters for the car sprite stack
    int numberOfLayers = 9;  // Number of layers in the sprite stack
    float spriteWidth = carTexture.getSize().x / numberOfLayers;  // Width of each layer
    float spriteHeight = carTexture.getSize().y;  // Height of each layer
    float layerSpacing = 0.6f;  // Distance between each sprite layer in 3D

    float rotationAngle = 0.0f;

    // Move the camera back to see the car
    glTranslatef(0.0f, 0.0f, -100.0f);  
    glRotatef(-35.0f, 1.0f, 0.0f, 0.0f);  // Rotate the car around the Y axis

    sf::Clock clock; // Create a clock
    const float targetFrameTime = 1.0f / 60.0f; // Target frame time for 60 FPS

    // Main loop
    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        // Clear the window with OpenGL
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        // Draw the ground sprite
        window.pushGLStates(); // Save the current OpenGL states
        window.draw(groundSprite);
        window.popGLStates(); // Restore the OpenGL states

        // Set up the modelview matrix
        glMatrixMode(GL_MODELVIEW);
        glLoadIdentity();

        float angleInRadians = rotationAngle * M_PI / 180.0f;
        float moveX = carSpeed * std::cos(angleInRadians);
        float moveY = carSpeed * std::sin(angleInRadians);
        int forward = 0;
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Z)) {
            carX += moveX;
            carY += moveY;
            forward = 1;
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
            carX -= moveX;
            carY -= moveY;
            forward = -1;
        }
        if (forward != 0 && sf::Keyboard::isKeyPressed(sf::Keyboard::Q)) {
            rotationAngle += 1.5f * forward;
        }
        if (forward != 0 && sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
            rotationAngle -= 1.5f * forward;
        }
        glTranslatef(carX, carY, 0.0f);  // Translate the car to its position
        glRotatef(rotationAngle, 0.0f, 0.0f, 1.0f);  // Rotate the car around the Z axis

        // Render the car sprite stack
        renderSpriteStackVAO(carVAO, carTexture, numberOfLayers);

        // Swap buffers to display the rendered image
        window.display();

        // Limit the frame rate
        sf::Time elapsedTime = clock.getElapsedTime();
        float frameTime = elapsedTime.asSeconds();
        if (frameTime < targetFrameTime) {
            sf::sleep(sf::seconds(targetFrameTime - frameTime));
        }
        clock.restart();
    }

    // Cleanup
    GLuint textureID = groundTexture.getNativeHandle();
    glDeleteTextures(1, &textureID);
    GLuint carTextureID = carTexture.getNativeHandle();
    glDeleteTextures(1, &carTextureID);
    glDeleteBuffers(1, &carVBO);
    glDeleteBuffers(1, &carTexCoordVBO);
    glDeleteVertexArrays(1, &carVAO);
    return 0;
}