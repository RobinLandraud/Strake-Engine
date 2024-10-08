#include "shaders.hpp"

Shader::Shader(const std::string &vertexPath, const std::string &fragmentPath) :
    m_id(0),
    m_fileExt(["frag", "vert"])

{
    const std::string vertexCode = Shader::get_file_content(vertexPath);
    const std::string fragmentCode = Shader::get_file_content(fragmentPath);
    const char *vShaderCode = vertexCode.c_str();
    const char *fShaderCode = fragmentCode.c_str();
}

std::string Shader::get_file_content(std::string &filename)
{
    std::ifstream file;
    bool validExt = false;
    std::string ext = filename.substr(filename.find_last_of(".") + 1);
    for (int i = 0; i < m_fileExt.size(); i++)
    {
        if (ext == m_fileExt[i])
        {
            validExt = true;
            break;
        }
    }
    if (!validExt)
    {
        std::cerr << "Invalid file extension" << std::endl;
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
    glUseProgram(ID);
}

void Shader::delete_shader()
{
    glDeleteProgram(ID);
}