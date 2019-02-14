#include "TextureCubeMTL.h"
#include "renderer/CCTextureCube.h"
#include <cassert>

NS_CC_BEGIN

TextureCube* TextureCube::create(const std::string& positive_x, const std::string& negative_x,
                                 const std::string& positive_y, const std::string& negative_y,
                                 const std::string& positive_z, const std::string& negative_z)
{
    auto ret = new (std::nothrow) backend::TextureCubeMTL();
    if (ret && ret->init(positive_x, negative_x, positive_y, negative_y, positive_z, negative_z))
    {
        ret->autorelease();
        return ret;
    }
    CC_SAFE_DELETE(ret);
    return nullptr;
}

NS_CC_END

CC_BACKEND_BEGIN

bool TextureCubeMTL::updateImageData(int side, Texture2D::PixelFormat format, int width, int height, unsigned char *data)
{
    //TODO: arnold
    assert(false);
    return false;
}

void TextureCubeMTL::setTexParameters(const TexParams& texParams)
{
    //TODO: arnold
    assert(false);
}

CC_BACKEND_END
