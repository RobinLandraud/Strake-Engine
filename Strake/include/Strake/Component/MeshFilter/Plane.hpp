#pragma once

#include <Strake/Component/MeshFilter/MeshFilter.hpp>

namespace Strake {
    class Plane : public MeshFilter
    {
        public:
            Plane(GameObject &parent);
    };
}