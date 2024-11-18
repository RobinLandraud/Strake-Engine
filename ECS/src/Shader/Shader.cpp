#include <ECS/Shaders.hpp>

namespace ECS {
    Shader::Shader(const std::string &path, GLenum type) {
        std::ifstream file(path);
        if (!file.is_open()) {
            std::cerr << "Failed to open file: " << path << std::endl;
            return;
        }
        std::string source;
        std::string line;
        while (std::getline(file, line)) {
            source += line + '\n';
        }
        file.close();
        const char *src = source.c_str();
        m_shader = glCreateShader(type);
        glShaderSource(m_shader, 1, &src, nullptr);
        glCompileShader(m_shader);
        GLint success = 0;
        std::array<GLchar, 512> infoLog = {0};
        glGetShaderiv(m_shader, GL_COMPILE_STATUS, &success);
        if (success == 0) {
            glGetShaderInfoLog(m_shader, 512, nullptr, infoLog.data());
            std::cerr << "Failed to compile shader: " << path << std::endl;
            std::cerr << infoLog.data() << std::endl;
            return;
        }
    }

    Shader::~Shader() {
        glDeleteShader(m_shader);
    }

    GLuint Shader::getID() const {
        return m_shader;
    }
}