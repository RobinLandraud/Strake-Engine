#include <ECS/Textures.hpp>

namespace ECS {
    Texture2D::Texture2D(const std::string &path) {
        glGenTextures(1, &m_texture);
        glBindTexture(GL_TEXTURE_2D, m_texture);

        // Set texture parameters
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR); // Use mipmap filtering
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

        int width = 0;
        int height = 0;
        int nrChannels = 0;
        unsigned char *data = stbi_load(path.c_str(), &width, &height, &nrChannels, 0);
        
        if (data != nullptr) {
            if (nrChannels == 1) {
                unsigned char* rgb_data = new unsigned char[width * height * 3];
                for (int i = 0; i < width * height; i++) {
                    rgb_data[i * 3] = data[i];
                    rgb_data[i * 3 + 1] = data[i];
                    rgb_data[i * 3 + 2] = data[i];
                }
                stbi_image_free(data);
                data = rgb_data;
                nrChannels = 3;
            }
            GLenum format = (nrChannels == 3) ? GL_RGB : GL_RGBA;
            glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, data);
            glGenerateMipmap(GL_TEXTURE_2D); // Generate mipmaps after loading the texture
        } else {
            std::cerr << "Failed to load texture at: " << path << std::endl; // Improved error message
            glDeleteTextures(1, &m_texture); // Delete the texture if it failed to load
            m_texture = 0; // Set the texture to 0
        }
        
        stbi_image_free(data); // Free the loaded data
    }

    void Texture2D::bind() {
        glBindTexture(GL_TEXTURE_2D, m_texture);
    }

    void Texture2D::unbind() {
        glBindTexture(GL_TEXTURE_2D, 0);
    }
}