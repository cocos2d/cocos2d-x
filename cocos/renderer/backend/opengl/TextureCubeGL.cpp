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


NS_CC_BEGIN


TextureCube* TextureCube::create(const std::string& positive_x, const std::string& negative_x,
    const std::string& positive_y, const std::string& negative_y,
    const std::string& positive_z, const std::string& negative_z)
{
    auto ret = new (std::nothrow) backend::TextureCubeGL();
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

TextureCubeGL::TextureCubeGL()
{
    CC_SAFE_RELEASE_NULL(_texture);
    auto descriptor = backend::TextureDescriptor();
    descriptor.textureType = TextureType::TEXTURE_CUBE;
    descriptor.textureUsage = TextureUsage::READ;
    descriptor.width = 4;
    descriptor.height = 4;
    _texture = new TextureCubeMapGL(descriptor);
}

bool TextureCubeGL::updateImageData(int side, Texture2D::PixelFormat format, int width, int height, unsigned char *data)
{
    TextureCubeMapGL *cube = static_cast<TextureCubeMapGL*>(_texture);
    return cube->updateImageData(side, format, width, height, data);
}


void TextureCubeGL::setTexParameters(const TexParams& texParams)
{
    TextureCubeMapGL *cube = static_cast<TextureCubeMapGL*>(_texture);
    cube->setTexParams(texParams);
}

CC_BACKEND_END
