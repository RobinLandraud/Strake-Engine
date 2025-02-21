#include <Strake/Component/UI/UI.hpp>
#include <Strake/Texture/Texture.hpp>

namespace Strake {
    class Image : public UI {
        public:
            Image(GameObject &parent, Texture &texture);
            ~Image();
            [[nodiscard]] Texture &getTexture() const;
        private:
            Texture &r_texture;
    };
}