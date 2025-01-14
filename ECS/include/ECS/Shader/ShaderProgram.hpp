#pragma once

#include <ECS/Shader/Shader.hpp>
#include <glm/glm.hpp>

namespace Strake {
    class ShaderProgram {
        public:
            ShaderProgram(const std::string &vertexPath, const std::string &fragmentPath);
            ~ShaderProgram();
            ShaderProgram(const ShaderProgram&) = delete;
            ShaderProgram& operator=(const ShaderProgram&) = delete;
            ShaderProgram& operator=(ShaderProgram&&) = delete;
            ShaderProgram(ShaderProgram&&) = delete;

            float getUniformFloat(const std::string &name) const;
            int getUniformInt(const std::string &name) const;
            glm::vec3 getUniformVec3(const std::string &name) const;
            glm::mat4 getUniformMat4(const std::string &name) const;

            void use() const;
            void unuse() const;
            void setUniform(const std::string &name, const glm::mat4 &value) const;
            void setUniform(const std::string &name, const glm::vec3 &value) const;
            void setUniform(const std::string &name, const glm::vec4 &value) const;
            void setUniform(const std::string &name, float value) const;
            void setUniform(const std::string &name, int value) const;
        private:
            GLuint m_program;
    };
}