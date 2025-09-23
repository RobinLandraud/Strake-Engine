#include <Strake/Component/Light/ShadowMap.hpp>

namespace Strake {
    ShadowMap::ShadowMap() :
        m_size(4096, 4096)
    {
        glGenFramebuffers(1, &m_shadowFBO);
        glGenTextures(1, &m_shadowMap);
        glBindTexture(GL_TEXTURE_2D, m_shadowMap);
        glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH_COMPONENT, m_size.x, m_size.y, 0, GL_DEPTH_COMPONENT, GL_FLOAT, nullptr);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_BORDER);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_BORDER);
        float borderColor[] = {1.0f, 1.0f, 1.0f, 1.0f};
        glTexParameterfv(GL_TEXTURE_2D, GL_TEXTURE_BORDER_COLOR, borderColor);
        glBindFramebuffer(GL_FRAMEBUFFER, m_shadowFBO);
        glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_TEXTURE_2D, m_shadowMap, 0);
        glDrawBuffer(GL_NONE);
        glReadBuffer(GL_NONE);
        glBindFramebuffer(GL_FRAMEBUFFER, 0);
        m_lightProjection = glm::ortho(-35.0f, 35.0f, -35.0f, 35.0f, 1.0f, 300.0f);
        // 300 for far plane
        // 1 for near plane
        // 35 for ortho size
    }

    ShadowMap::~ShadowMap() {
        glDeleteFramebuffers(1, &m_shadowFBO);
        glDeleteTextures(1, &m_shadowMap);
    }

    GLuint ShadowMap::getShadowMap() const {
        return m_shadowMap;
    }

    GLuint ShadowMap::getShadowFBO() const {
        return m_shadowFBO;
    }

    const glm::mat4 &ShadowMap::getLightProjection() const {
        return m_lightProjection;
    }

    glm::vec2 ShadowMap::getSize() const {
        return m_size;
    }

    void ShadowMap::bind() {
        glBindFramebuffer(GL_FRAMEBUFFER, m_shadowFBO);
        glClear(GL_DEPTH_BUFFER_BIT);
    }

    void ShadowMap::unbind() {
        glBindFramebuffer(GL_FRAMEBUFFER, 0);
    }

    void ShadowMap::addObject(GameObject &object) {
        m_objects.push_back(object);
    }

    const std::vector<std::reference_wrapper<GameObject>> &ShadowMap::getObjects() const {
        return m_objects;
    }

    void ShadowMap::clearObjects() {
        m_objects.clear();
    }
}