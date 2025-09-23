#pragma once

#include <Strake/Component/MeshFilter/MeshFilter.hpp>

namespace Strake
{
    class Sphere : public MeshFilter
    {
        public:
            Sphere(GameObject &parent, float radius = 0.5f, int sectorCount = 36, int stackCount = 18);
        private:
            const int m_sectorCount;
            const int m_stackCount;
            const float m_radius;
    };
}