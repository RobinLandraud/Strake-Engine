#include <myGL/Shaders.hpp>

const std::array<std::string, 2> Shader::m_fileExt = {"frag", "vert"};

Shader::Shader(const std::string &vertexPath, const std::string &fragmentPath)
    : m_id(0)
{
    const std::string vertexCode = Shader::get_file_content(vertexPath);
    const std::string fragmentCode = Shader::get_file_content(fragmentPath);
    const char *vShaderCode = vertexCode.c_str();
    const char *fShaderCode = fragmentCode.c_str();

    //  CREATE SHADER PROGRAM WITH VERTEX AND FRAGMENT SHADERS

    // Create a vertex shader
    GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER); // Create a vertex shader
    glShaderSource(vertexShader, 1, &vShaderCode, nullptr); // Set the source code of the vertex shader
    //1 is the number of strings in the source code
    //&vShaderCode is the source code of the vertex shader
    //nullptr is the length of the source code
    glCompileShader(vertexShader); // Compile the vertex shader

    // Create a fragment shader
    GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER); // Create a fragment shader
    glShaderSource(fragmentShader, 1, &fShaderCode, nullptr); // Set the source code of the fragment shader
    glCompileShader(fragmentShader); // Compile the fragment shader
    // Create a shader program
    m_id = glCreateProgram(); // Create a shader program
    
    glAttachShader(m_id, vertexShader); // Attach the vertex shader to the shader program
    glAttachShader(m_id, fragmentShader); // Attach the fragment shader to the shader program
    
    glLinkProgram(m_id); // Link the shader program
    
    glDeleteShader(vertexShader); // Delete the vertex shader because it is no longer needed
    glDeleteShader(fragmentShader); // Delete the fragment shader because it is no longer needed
}

std::string Shader::get_file_content(const std::string &filename)
{
    std::ifstream file;
    bool validExt = false;
    std::string ext = filename.substr(filename.find_last_of(".") + 1);
    for (int i = 0; i < m_fileExt.size(); i++)
    {
        if (ext == m_fileExt.at(i))
        {
            validExt = true;
            break;
        }
    }
    if (!validExt)
    {
        std::cout << "Invalid file extension" << std::endl;
        return "";
    }

    file.exceptions(std::ifstream::failbit | std::ifstream::badbit);
    try
    {
        file.open(filename);
        std::stringstream stream;
        stream << file.rdbuf();
        file.close();
        return stream.str();
    }
    catch (std::ifstream::failure e)
    {
        std::cerr << "Failed to read file: " << filename << std::endl;
        std::cerr << "Error code: " << errno << std::endl;
        return "";
    }
}

void Shader::activate()
{
    glUseProgram(m_id);
}

void Shader::delete_shader()
{
    glDeleteProgram(m_id);
}

GLuint Shader::getID()
{
    return m_id;
}