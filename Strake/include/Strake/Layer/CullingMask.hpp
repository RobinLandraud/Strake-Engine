#pragma once

#include <Strake/Layer/Layer.hpp>

namespace Strake {
    class CullingMask {
        public:
            CullingMask(); // default constructor
            CullingMask(const uint32_t mask); // constructor with mask
            ~CullingMask();

            CullingMask(const CullingMask &other); // copy constructor
            CullingMask& operator=(const CullingMask& mask); // copy assignment
            CullingMask(CullingMask &&other) = delete; // move constructor
            CullingMask& operator=(CullingMask&& mask) = delete; // move assignment

            CullingMask& operator|=(const CullingMask& mask); // bitwise OR assignment
            CullingMask& operator&=(const CullingMask& mask); // bitwise AND assignment
            CullingMask& operator^=(const CullingMask& mask); // bitwise XOR assignment

            void addLayer(Layer &layer);
            void removeLayer(Layer &layer);
            void clear();
            bool affectsLayer(Layer &layer) const;
        private:
            uint32_t m_mask;
    };
}