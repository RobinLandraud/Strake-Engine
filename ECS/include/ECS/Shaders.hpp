//shader and shaderprogram classes

#ifndef ECS_SHADERS_HPP
#define ECS_SHADERS_HPP

#include <GL/glew.h>
#include <GL/glu.h>
#include <glm/glm.hpp>
#include <string>
#include <iostream>
#include <fstream>

namespace ECS {
    class Shader {
        public:
            Shader(const std::string &path, GLenum type);
            ~Shader();
            [[nodiscard]] const GLuint getID() const;
        private:
            GLuint m_shader;
    };

    class ShaderProgram {
        public:
            ShaderProgram(const std::string &vertexPath, const std::string &fragmentPath);
            ~ShaderProgram();
            void use();
            void setUniform(const std::string &name, const glm::mat4 &value);
            void setUniform(const std::string &name, const glm::vec3 &value);
            void setUniform(const std::string &name, const glm::vec4 &value);
            void setUniform(const std::string &name, const float value);
            void setUniform(const std::string &name, const int value);
        private:
            GLuint m_program;
    };
}
#endif //ECS_SHADERS_HPP