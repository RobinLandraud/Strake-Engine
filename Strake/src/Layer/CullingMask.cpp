#include <Strake/Layer/CullingMask.hpp>

namespace Strake {

    CullingMask::CullingMask(const LayerManager &manager, const uint32_t mask) :
        r_manager(manager),
        m_mask(mask),
        m_onMaskChanged(nullptr)
    {
    }

    CullingMask::~CullingMask() {
    }

    CullingMask& CullingMask::operator=(const CullingMask& mask) {
        m_mask = mask.m_mask;
        return *this;
    }

    CullingMask& CullingMask::operator|=(const CullingMask& mask) {
        m_mask |= mask.m_mask;
        return *this;
    }


    CullingMask& CullingMask::operator&=(const CullingMask& mask) {
        m_mask &= mask.m_mask;
        return *this;
    }

    CullingMask& CullingMask::operator^=(const CullingMask& mask) {
        m_mask ^= mask.m_mask;
        return *this;
    }

    void CullingMask::addLayer(Layer& layer) {
        m_mask |= layer.getBitMask();
        m_onMaskChanged(layer.getPriority(), true);
    }

    void CullingMask::addLayer(int priority) {
        m_mask |= (1 << priority);
        m_onMaskChanged(priority, true);
    }

    void CullingMask::addLayer(const std::string& name) {
        const Layer& layer = r_manager.getLayer(name);
        m_mask |= layer.getBitMask();
        m_onMaskChanged(layer.getPriority(), true);
    }

    void CullingMask::removeLayer(Layer& layer) {
        m_mask &= ~layer.getBitMask();
        m_onMaskChanged(layer.getPriority(), false);
    }

    void CullingMask::removeLayer(int priority) {
        m_mask &= ~(1 << priority);
        m_onMaskChanged(priority, false);
    }

    void CullingMask::removeLayer(const std::string& name) {
        const Layer& layer = r_manager.getLayer(name);
        m_mask &= ~layer.getBitMask();
        m_onMaskChanged(layer.getPriority(), false);
    }

    void CullingMask::clear() {
        m_mask = Nothing;
        m_onMaskChanged(-1, false);
    }

    bool CullingMask::hasLayer(Layer& layer) const {
        return (m_mask & layer.getBitMask()) != 0;
    }

    bool CullingMask::hasLayer(int priority) const {
        return (m_mask & (1 << priority)) != 0;
    }

    bool CullingMask::hasLayer(const std::string& name) const {
        const Layer& layer = r_manager.getLayer(name);
        return (m_mask & layer.getBitMask()) != 0;
    }

    uint32_t CullingMask::getMask() const {
        return m_mask;
    }

    void CullingMask::setOnMaskChanged(MaskChangedCallback onMaskChanged) {
        m_onMaskChanged = onMaskChanged;
        for (int i = 0; i < 32; i++) {
            if ((m_mask & (1 << i)) != 0) {
                m_onMaskChanged(i, true);
            }
        }
    }
}