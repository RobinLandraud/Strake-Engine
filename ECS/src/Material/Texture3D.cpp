#include <ECS/Textures.hpp>

namespace ECS {
    Texture3D::Texture3D(const std::vector<std::string> &paths) {
        glGenTextures(1, &m_texture);
        glBindTexture(GL_TEXTURE_3D, m_texture);

        // Set texture parameters
        glTexParameteri(GL_TEXTURE_3D, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_3D, GL_TEXTURE_WRAP_T, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_3D, GL_TEXTURE_WRAP_R, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_3D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR); // Use linear mipmap filtering
        glTexParameteri(GL_TEXTURE_3D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

        int width = 0;
        int height = 0;
        int nrChannels = 0;
        unsigned char *data = nullptr;

        for (int i = 0; i < paths.size(); i++) {
            data = stbi_load(paths[i].c_str(), &width, &height, &nrChannels, 0);
            if (data != nullptr) {
                GLenum format = (nrChannels == 3) ? GL_RGB : GL_RGBA;
                
                // Load texture data into the 3D texture
                glTexImage3D(GL_TEXTURE_3D, 0, format, width, height, i+1, 0, format, GL_UNSIGNED_BYTE, data);
            } else {
                std::cerr << "Failed to load texture at: " << paths[i] << std::endl;
                glDeleteTextures(1, &m_texture);
                m_texture = 0;
            }
            stbi_image_free(data);
        }

        // Generate mipmaps after loading all layers
        glGenerateMipmap(GL_TEXTURE_3D);
    }
}