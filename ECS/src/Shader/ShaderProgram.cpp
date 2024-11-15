#include <ECS/Shaders.hpp>

namespace ECS {
    ShaderProgram::ShaderProgram(const std::string &vertexPath, const std::string &fragmentPath) {
        Shader vertexShader(vertexPath, GL_VERTEX_SHADER);
        Shader fragmentShader(fragmentPath, GL_FRAGMENT_SHADER);
        m_program = glCreateProgram();
        glAttachShader(m_program, vertexShader.getID());
        glAttachShader(m_program, fragmentShader.getID());
        glLinkProgram(m_program);
        GLint success;
        glGetProgramiv(m_program, GL_LINK_STATUS, &success);
        if (!success) {
            GLchar infoLog[512];
            glGetProgramInfoLog(m_program, 512, nullptr, infoLog);
            std::cerr << "Failed to link shader program" << std::endl;
            std::cerr << infoLog << std::endl;
            return;
        }
        glValidateProgram(m_program);
        glGetProgramiv(m_program, GL_VALIDATE_STATUS, &success);
        if (!success) {
            GLchar infoLog[512];
            glGetProgramInfoLog(m_program, 512, nullptr, infoLog);
            std::cerr << "Failed to validate shader program" << std::endl;
            std::cerr << infoLog << std::endl;
            return;
        }
    }

    ShaderProgram::~ShaderProgram() {
        glDeleteProgram(m_program);
    }

    void ShaderProgram::use() {
        glUseProgram(m_program);
        GLenum error = glGetError();
        if (error != GL_NO_ERROR) {
            std::cerr << "OpenGL error: " << error << std::endl;
        }
    }

    void ShaderProgram::setUniform(const std::string &name, const glm::mat4 &value) {
        GLint location = glGetUniformLocation(m_program, name.c_str());
        if (location == -1) {
            std::cerr << "Failed to find uniform: " << name << std::endl;
            return;
        }
        glUniformMatrix4fv(location, 1, GL_FALSE, &value[0][0]);
        GLenum error = glGetError();
        if (error != GL_NO_ERROR) {
            std::cerr << "OpenGL error: " << error << std::endl;
        }
    }

    void ShaderProgram::setUniform(const std::string &name, const glm::vec3 &value) {
        GLint location = glGetUniformLocation(m_program, name.c_str());
        if (location == -1) {
            std::cerr << "Failed to find uniform: " << name << std::endl;
            return;
        }
        glUniform3fv(location, 1, &value[0]);
        GLenum error = glGetError();
        if (error != GL_NO_ERROR) {
            std::cerr << "OpenGL error: " << error << std::endl;
        }
    }

    void ShaderProgram::setUniform(const std::string &name, const glm::vec4 &value) {
        GLint location = glGetUniformLocation(m_program, name.c_str());
        if (location == -1) {
            std::cerr << "Failed to find uniform: " << name << std::endl;
            return;
        }
        glUniform4fv(location, 1, &value[0]);
        GLenum error = glGetError();
        if (error != GL_NO_ERROR) {
            std::cerr << "OpenGL error: " << error << std::endl;
        }
    }

    void ShaderProgram::setUniform(const std::string &name, float value) {
        GLint location = glGetUniformLocation(m_program, name.c_str());
        if (location == -1) {
            std::cerr << "Failed to find uniform: " << name << std::endl;
            return;
        }
        glUniform1f(location, value);
        GLenum error = glGetError();
        if (error != GL_NO_ERROR) {
            std::cerr << "OpenGL error: " << error << std::endl;
        }
    }

    void ShaderProgram::setUniform(const std::string &name, int value) {
        GLint location = glGetUniformLocation(m_program, name.c_str());
        if (location == -1) {
            std::cerr << "Failed to find uniform: " << name << std::endl;
            return;
        }
        glUniform1i(location, value);
        GLenum error = glGetError();
        if (error != GL_NO_ERROR) {
            std::cerr << "Shader OpenGL error: " << error << std::endl;
        }
    }
}

