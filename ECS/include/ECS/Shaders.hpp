//shader and shaderprogram classes

#ifndef ECS_SHADERS_HPP
#define ECS_SHADERS_HPP

#include <GL/glew.h>
#include <GL/glu.h>
#include <array>
#include <fstream>
#include <glm/glm.hpp>
#include <iostream>
#include <string>

namespace ECS {
    class Shader {
        public:
            Shader(const std::string &path, GLenum type);
            ~Shader();
            Shader(const Shader&) = delete;
            Shader& operator=(const Shader&) = delete;
            Shader& operator=(Shader&&) = delete;
            Shader(Shader&&) = delete;

            [[nodiscard]] GLuint getID() const;
        private:
            GLuint m_shader;
    };

    class ShaderProgram {
        public:
            ShaderProgram(const std::string &vertexPath, const std::string &fragmentPath);
            ~ShaderProgram();
            ShaderProgram(const ShaderProgram&) = delete;
            ShaderProgram& operator=(const ShaderProgram&) = delete;
            ShaderProgram& operator=(ShaderProgram&&) = delete;
            ShaderProgram(ShaderProgram&&) = delete;

            void use() const;
            void setUniform(const std::string &name, const glm::mat4 &value) const;
            void setUniform(const std::string &name, const glm::vec3 &value) const;
            void setUniform(const std::string &name, const glm::vec4 &value) const;
            void setUniform(const std::string &name, float value) const;
            void setUniform(const std::string &name, int value) const;
        private:
            GLuint m_program;
    };
}
#endif //ECS_SHADERS_HPP