#include <Strake/Component/Component.hpp>

namespace Strake {
    Component::Component(
        GameObject &parent
        )
        : r_parent(parent)
    {
    }

    void Component::setDerivedType(const std::type_index &type) {
        m_derivedType = type;
    }

    std::type_index Component::getDerivedType() const {
        return m_derivedType;
    }

    GameObject &Component::getParent() const {
        return r_parent;
    }
}