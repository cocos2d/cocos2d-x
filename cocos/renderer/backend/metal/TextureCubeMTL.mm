#include "TextureCubeMTL.h"
#include "renderer/CCTextureCube.h"
#include <cassert>

NS_CC_BEGIN

TextureCube* TextureCube::create(const std::string& positive_x, const std::string& negative_x,
                                 const std::string& positive_y, const std::string& negative_y,
                                 const std::string& positive_z, const std::string& negative_z)
{
    auto ret = new (std::nothrow) backend::TextureCubeMapMTL();
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

bool TextureCubeMapMTL::init(const std::string& positive_x, const std::string& negative_x,
                            const std::string& positive_y, const std::string& negative_y,
                            const std::string& positive_z, const std::string& negative_z)
{
    _imgPath[0] = positive_x;
    _imgPath[1] = negative_x;
    _imgPath[2] = positive_y;
    _imgPath[3] = negative_y;
    _imgPath[4] = positive_z;
    _imgPath[5] = negative_z;
    //TODO: arnold
    assert(false);
    return false;
}

void TextureCubeMapMTL::setTexParameters(const TexParams& texParams)
{
    //TODO: arnold
    assert(false);
}

CC_BACKEND_END
