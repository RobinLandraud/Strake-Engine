#include <Strake/Component/UI/Image.hpp>

namespace Strake
{
    Image::Image(GameObject &parent, Texture &texture)
        : UI(parent), r_texture(texture)
    {
    }

    Image::~Image()
    {
    }

    Texture &Image::getTexture() const
    {
        return r_texture;
    }
}

