#include <Strake/Layer/CullingMask.hpp>

namespace Strake {
    CullingMask::CullingMask() :
        m_mask(0)
    {
    }

    CullingMask::CullingMask(const uint32_t mask) {
        m_mask = mask;
    }

    CullingMask::CullingMask(const CullingMask& mask) {
        m_mask = mask.m_mask;
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
    }

    void CullingMask::removeLayer(Layer& layer) {
        m_mask &= ~layer.getBitMask();
    }

    void CullingMask::clear() {
        m_mask = 0;
    }

    bool CullingMask::affectsLayer(Layer& layer) const {
        return (m_mask & layer.getBitMask()) != 0;
    }
}