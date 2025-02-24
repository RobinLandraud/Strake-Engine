#pragma once

#include <Strake/Layer/Layer.hpp>
#include <Strake/Manager/LayerManager.hpp>

namespace Strake {
    class CullingMask {
        public:
            using MaskChangedCallback = std::function<void(int, bool)>;
            static constexpr uint32_t Everything = 0xFFFFFFFF;
            static constexpr uint32_t Nothing = 0x00000000;

            explicit CullingMask(const LayerManager &manager, const uint32_t mask = Everything); // constructor
            ~CullingMask();

            CullingMask(const CullingMask &other); // copy constructor
            CullingMask& operator=(const CullingMask& mask); // copy assignment
            CullingMask(CullingMask &&other) = delete; // move constructor
            CullingMask& operator=(CullingMask&& mask) = delete; // move assignment

            CullingMask& operator|=(const CullingMask& mask); // bitwise OR assignment
            CullingMask& operator&=(const CullingMask& mask); // bitwise AND assignment
            CullingMask& operator^=(const CullingMask& mask); // bitwise XOR assignment

            void addLayer(Layer &layer);
            void addLayer(int priority);
            void addLayer(const std::string &name);

            void removeLayer(Layer &layer);
            void removeLayer(int priority);
            void removeLayer(const std::string &name);

            void clear();

            bool hasLayer(Layer &layer) const;
            bool hasLayer(int priority) const;
            bool hasLayer(const std::string &name) const;

            [[nodiscard]] uint32_t getMask() const;

            void setOnMaskChanged(MaskChangedCallback onMaskChanged);

        private:
            uint32_t m_mask;
            const LayerManager &r_manager;
            MaskChangedCallback m_onMaskChanged;
    };
}