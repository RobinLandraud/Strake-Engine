#include <ECS/Shaders.hpp>

namespace ECS {
    ShaderProgram::ShaderProgram(const std::string &vertexPath, const std::string &fragmentPath) {
        Shader vertexShader(vertexPath, GL_VERTEX_SHADER);
        Shader fragmentShader(fragmentPath, GL_FRAGMENT_SHADER);
        m_program = glCreateProgram();
        glAttachShader(m_program, vertexShader.getID());
        glAttachShader(m_program, fragmentShader.getID());
        glLinkProgram(m_program);
        GLint success = 0;
        std::array<GLchar, 512> infoLog = {0};
        glGetProgramiv(m_program, GL_LINK_STATUS, &success);
        if (success == 0) {
            glGetProgramInfoLog(m_program, 512, nullptr, infoLog.data());
            std::cerr << "Failed to link shader program" << std::endl;
            std::cerr << infoLog.data() << std::endl;
            return;
        }
        glValidateProgram(m_program);
        glGetProgramiv(m_program, GL_VALIDATE_STATUS, &success);
        if (success == 0) {
            glGetProgramInfoLog(m_program, 512, nullptr, infoLog.data());
            std::cerr << "Failed to validate shader program" << std::endl;
            std::cerr << infoLog.data() << std::endl;
            return;
        }
    }

    ShaderProgram::~ShaderProgram() {
        glDeleteProgram(m_program);
    }

    void ShaderProgram::use() const {
        glUseProgram(m_program);
        GLenum error = glGetError();
        if (error != GL_NO_ERROR) {
            std::cerr << "OpenGL error: " << error << std::endl;
        }
    }

    float ShaderProgram::getUniformFloat(const std::string &name) const {
        GLint location = glGetUniformLocation(m_program, name.c_str());
        if (location == -1) {
            std::cerr << "Failed to find uniform: " << name << std::endl;
            return 0.0f;
        }
        float value;
        glGetUniformfv(m_program, location, &value);
        return value;
    }

    int ShaderProgram::getUniformInt(const std::string &name) const {
        GLint location = glGetUniformLocation(m_program, name.c_str());
        if (location == -1) {
            std::cerr << "Failed to find uniform: " << name << std::endl;
            return 0;
        }
        int value;
        glGetUniformiv(m_program, location, &value);
        return value;
    }

    glm::vec3 ShaderProgram::getUniformVec3(const std::string &name) const {
        GLint location = glGetUniformLocation(m_program, name.c_str());
        if (location == -1) {
            std::cerr << "Failed to find uniform: " << name << std::endl;
            return glm::vec3(0.0f);
        }
        glm::vec3 value;
        glGetUniformfv(m_program, location, &value[0]);
        return value;
    }

    void ShaderProgram::setUniform(const std::string &name, const glm::mat4 &value) const {
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

    void ShaderProgram::setUniform(const std::string &name, const glm::vec3 &value) const {
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

    void ShaderProgram::setUniform(const std::string &name, const glm::vec4 &value) const {
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

    void ShaderProgram::setUniform(const std::string &name, float value) const {
        GLint location = glGetUniformLocation(m_program, name.c_str());
        if (location == -1) {
            std::cerr << "Failed to find uniform: " << name << std::endl;
            return;
        }
        glUniform1f(location, value);
        GLenum error = glGetError();
        if (error != GL_NO_ERROR) {
            std::cerr << "Failed to set uniform: " << error << std::endl;
        }
    }

    void ShaderProgram::setUniform(const std::string &name, int value) const {
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

