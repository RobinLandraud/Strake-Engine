#pragma once

#include <Strake/Component/MeshFilter/MeshFilter.hpp>

namespace Strake {
    class Capsule : public MeshFilter
    {
        public:
            Capsule(GameObject &parent, float radius = 0.5f, float height = 1.0f, int sectorCount = 36, int stackCount = 18);
        private:
            const int m_sectorCount;
            const int m_stackCount;
            const float m_radius;
            const float m_height;
    };
}