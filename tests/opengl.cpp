#include <iostream>
#include <cmath>
#include <glad/glad.h>
#include <GLFW/glfw3.h>

int main()
{
    if (!glfwInit())
    {
        std::cerr << "Failed to initialize GLFW" << std::endl;
        return -1;
    }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    //Two packages:
    // GLFW_OPENGL_CORE_PROFILE:
    //    - No fixed function pipeline
    //    - No immediate mode
    //    - No matrix stack
    //    - No compatibility with old OpenGL
    //    - Only modern OpenGL
    // GLFW_OPENGL_COMPAT_PROFILE:
    //    - Fixed function pipeline
    //    - Immediate mode
    //    - Matrix stack
    //    - Compatibility with old OpenGL
    //    - Both modern and old OpenGL

    //vertex shader of a triangle
    GLfloat vertices[] = {
        -0.5f, -0.5f * float(sqrt(3)) / 3, 0.0f, //lower left corner
        0.5f, -0.5f * float(sqrt(3)) / 3, 0.0f, //lower right corner
        0.0f, 0.5f * float(sqrt(3)) * 2 / 3, 0.0f, //upper middle corner
        -0.5f / 2, 0.5f * float(sqrt(3)) / 6, 0.0f, //middle left corner
        0.5f / 2, 0.5f * float(sqrt(3)) / 6, 0.0f, //middle right corner
        0.0f, -0.5f * float(sqrt(3)) / 3, 0.0f //lower middle corner
    };

    GLuint indices[] = {
        0, 3, 5, //lower left triangle
        3, 2, 4, //lower right triangle
        5, 4, 1 //upper triangle
    };

    GLFWwindow *window = glfwCreateWindow(800, 600, "Window", nullptr, nullptr);
    if (!window)
    {
        std::cerr << "Failed to create window" << std::endl;
        const char *description;
        glfwGetError(&description);
        std::cerr << description << std::endl;
        glfwTerminate(); // Free resources
        return -1;
    }
    glfwMakeContextCurrent(window);

    //there is two buffers in OpenGL called front buffer and back buffer:
    //front buffer is the one that is displayed
    //back buffer is the one that is being drawn
    //when we finish drawing, we swap the buffers
    //this is called double buffering
    //this is done to avoid flickering
    //flickering is when the screen is updated too fast
    //and the user can see the screen being updated
    //this is done by the function glfwSwapBuffers(window)


    // Load OpenGL functions using GLAD
    //(GLADloadproc is a function pointer)
    //(glfwGetProcAddress is a function that returns the address of an OpenGL function)
    if (gladLoadGLLoader((GLADloadproc)glfwGetProcAddress) == 0)
    {
        std::cerr << "Failed to initialize GLAD" << std::endl;
        glfwDestroyWindow(window); // Free resources for window
        glfwTerminate(); // Free resources
        return -1;
    }
    //glad is a library that loads OpenGL functions at runtime
    //this is done because OpenGL is a specification and not an implementation

    glViewport(0, 0, 800, 600); // Set the viewport size
    //viewport is the size of the surface that OpenGL will render to
    //the difference between the window size and the viewport size is that
    //the window size is the size of the window that the user sees
    //the viewport size is the size of the window that OpenGL will render to
    //if the window size is different from the viewport size, OpenGL will scale the image
    //this can cause distortion
    //to avoid this, we set the viewport size to the window size


    //  CREATE SHADER PROGRAM WITH VERTEX AND FRAGMENT SHADERS

    // Create a vertex shader
    GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER); // Create a vertex shader
    glShaderSource(vertexShader, 1, &vertexShaderSource, nullptr); // Set the source code of the vertex shader
    //1 is the number of strings in the source code
    //&vertexShaderSource is the source code of the vertex shader
    //nullptr is the length of the source code
    glCompileShader(vertexShader); // Compile the vertex shader


    // Create a fragment shader
    GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER); // Create a fragment shader
    glShaderSource(fragmentShader, 1, &fragmentShaderSource, nullptr); // Set the source code of the fragment shader
    glCompileShader(fragmentShader); // Compile the fragment shader

    // Create a shader program
    GLuint shaderProgram = glCreateProgram(); // Create a shader program
    glAttachShader(shaderProgram, vertexShader); // Attach the vertex shader to the shader program
    glAttachShader(shaderProgram, fragmentShader); // Attach the fragment shader to the shader program

    glLinkProgram(shaderProgram); // Link the shader program
    glDeleteShader(vertexShader); // Delete the vertex shader because it is no longer needed
    glDeleteShader(fragmentShader); // Delete the fragment shader because it is no longer needed

    //  CREATE VERTEX BUFFER OBJECT AND VERTEX ARRAY OBJECT

    // VAO: stores the state related to vertex attribute configurations, including the bindings to VBOs.
    // VBO: stores the vertex data.
    // EBO: stores the indices of the vertices. Stored in the VAO.

    // binding: when you bind a VBO to a VAO (when a VAO is bound), the VAO stores the association between the VBO and the vertex attribute.

    // Create a vertex buffer object (VBO)
    GLuint VBO;
    // Create a vertex array object (VAO)
    GLuint VAO;
    // Create a element buffer object (EBO)
    GLuint EBO;

    glGenVertexArrays(1, &VAO); // Generate a vertex array
    //1 is the number of vertex arrays
    //&VAO is the address of the vertex array
    glGenBuffers(1, &VBO); // Generate a buffer
    //1 is the number of buffers
    //&VBO is the address of the buffer
    glGenBuffers(1, &EBO); // Generate a buffer
    //1 is the number of buffers
    //&EBO is the address of the buffer

    glBindVertexArray(VAO); // Bind the vertex array
    // There is no type for the vertex array because it is a container for the vertex buffer objects

    glBindBuffer(GL_ARRAY_BUFFER, VBO); // Bind the buffer
    //GL_ARRAY_BUFFER is the type of buffer
    //VBO is the buffer
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW); // Copy the vertex data to the VBO
    //GL_ARRAY_BUFFER is the type of buffer
    //sizeof(vertices) is the size of the data
    //vertices is the data
    //GL_STATIC_DRAW is the usage of the data
    // There is three types of usage:
    // GL_STATIC_DRAW: The data will be modified once and used multiple times
    // GL_STREAM_DRAW: The data will be modified once but used few times
    // GL_DYNAMIC_DRAW: The data will be modified multiple times and used multiple times


    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO); // Bind the buffer
    //GL_ELEMENT_ARRAY_BUFFER is the type of buffer
    //EBO is the buffer
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW); // Copy the indices to the EBO
    //GL_ELEMENT_ARRAY_BUFFER is the type of buffer
    //sizeof(indices) is the size of the data
    //indices is the data
    //GL_STATIC_DRAW is the usage of the data

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void *)0); // Set the vertex attribute pointer so that OpenGl knows how to read the VBO
    // 0 is the position of the vertex attribute
    // 3 is the number of components in the vertex attribute
    // GL_FLOAT is the type of the vertex attribute
    // GL_FALSE is whether the data should be normalized
    // 3 * sizeof(float) is the stride of the vertex attribute
    // (void *)0 is the offset of the vertex attribute

    glEnableVertexAttribArray(0); // Enable the vertex attribute with the position 0

    glBindBuffer(GL_ARRAY_BUFFER, 0); // Unbind the buffer (optional) (VBO)
    glBindVertexArray(0); // Unbind the vertex array (optional) (VAO)
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0); // Unbind the buffer (optional) (EBO)
    // unbinded after the vertex array is unbinded because the vertex array stores the bindings to the buffers

    //When you bind an EBO while a VAO is bound, the EBO is stored in the VAO's state.
    //Unbinding the EBO after binding the VAO ensures that subsequent operations on the EBO do not affect the VAO's state.

    //unbinding VBO before VAO doesn't affect the VAO's state


    glClearColor(0.07f, 0.13f, 0.17f, 1.0f); // Set the clear color of the color buffer to a new color
    glClear(GL_COLOR_BUFFER_BIT); // Clear the color buffer (using the clear color)
    glfwSwapBuffers(window); // Swap the front and back buffers

    while (!glfwWindowShouldClose(window))
    {
        glClear(GL_COLOR_BUFFER_BIT); // Clear the color buffer (using the clear color)
        glUseProgram(shaderProgram); // Use the shader program
        glBindVertexArray(VAO); // Bind the vertex array
        //the vertex array in use is the one that is bound

        //glDrawArrays(GL_TRIANGLES, 0, 3); // Draw the triangle
        //GL_TRIANGLES is the mode of drawing
        //0 is the starting index
        //3 is the number of vertices
        //glDrawArrays don't use the EBO

        glDrawElements(GL_TRIANGLES, 9, GL_UNSIGNED_INT, 0);
        //GL_TRIANGLES is the mode of drawing
        //9 is the number of indices
        //GL_UNSIGNED_INT is the type of the indices
        //0 is the offset of the indices
        //glDrawElements use the EBO

        glfwSwapBuffers(window); // Swap the front and back buffers
        glfwPollEvents(); // Check for events
    }

    // Free resources
    glDeleteVertexArrays(1, &VAO); // Delete the vertex array
    glDeleteBuffers(1, &VBO); // Delete the buffer
    glDeleteBuffers(1, &EBO); // Delete the buffer
    glDeleteProgram(shaderProgram); // Delete the shader program

    glfwDestroyWindow(window); // Free resources for window
    glfwTerminate(); // Free resources
}