/****************************************************************************
Copyright (c) 2019 Xiamen Yaji Software Co., Ltd.

http://www.cocos2d-x.org

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in
all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
THE SOFTWARE.
 ****************************************************************************/

#include "TextureCubeGL.h"
#include "renderer/CCTextureCube.h"
#include "renderer/backend/Texture.h"
#include "renderer/backend/opengl/TextureGL.h"
#include "base/ccMacros.h"
#include "platform/CCImage.h"
#include "platform/CCFileUtils.h"


NS_CC_BEGIN




TextureCube* TextureCube::create(const std::string& positive_x, const std::string& negative_x,
    const std::string& positive_y, const std::string& negative_y,
    const std::string& positive_z, const std::string& negative_z)
{
    auto ret = new (std::nothrow) backend::TextureCubeMapGL();
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

bool TextureCubeMapGL::init(const std::string& positive_x, const std::string& negative_x,
                       const std::string& positive_y, const std::string& negative_y,
                       const std::string& positive_z, const std::string& negative_z)
{
    _imgPath[0] = positive_x;
    _imgPath[1] = negative_x;
    _imgPath[2] = positive_y;
    _imgPath[3] = negative_y;
    _imgPath[4] = positive_z;
    _imgPath[5] = negative_z;
    CC_SAFE_RELEASE_NULL(_texture);

    auto descriptor = backend::TextureDescriptor();
    descriptor.textureType = TextureType::TEXTURE_CUBE;
    descriptor.textureUsage = TextureUsage::READ;
    descriptor.width = 4;
    descriptor.height = 4;
    _texture = new TextureCubeGL(descriptor);

    return ((TextureCubeGL*)_texture)->init(positive_x, negative_x, positive_y, negative_y, positive_z, 
        negative_z);
}

void TextureCubeMapGL::setTexParameters(const TexParams& texParams)
{
    glActiveTexture(GL_TEXTURE0);

    glBindTexture(GL_TEXTURE_CUBE_MAP, ((TextureGL*)_texture)->getHandler());
    CHECK_GL_ERROR_DEBUG();

    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, texParams.minFilter);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, texParams.magFilter);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, texParams.wrapS);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, texParams.wrapT);
    CHECK_GL_ERROR_DEBUG();

    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_CUBE_MAP, 0);
}

CC_BACKEND_END
