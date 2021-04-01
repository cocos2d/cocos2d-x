/****************************************************************************
 Copyright (c) 2015-2016 Chukong Technologies Inc.
 Copyright (c) 2017-2018 Xiamen Yaji Software Co., Ltd.
 
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

#include "renderer/CCTextureCube.h"
#include "platform/CCImage.h"
#include "platform/CCFileUtils.h"
#include "renderer/backend/Texture.h"
#include "renderer/backend/Device.h"
#include "renderer/CCTextureUtils.h"

NS_CC_BEGIN

unsigned char* getImageData(Image* img, backend::PixelFormat&  ePixFmt)
{
    unsigned char*    pTmpData = img->getData();
    unsigned int*     inPixel32 = nullptr;
    unsigned char*    inPixel8 = nullptr;
    unsigned short*   outPixel16 = nullptr;
    bool              bHasAlpha = img->hasAlpha();
    size_t            uBPP = img->getBitPerPixel();

    int               nWidth = img->getWidth();
    int               nHeight = img->getHeight();

    // compute pixel format
    if (bHasAlpha)
    {
        ePixFmt = backend::PixelFormat::DEFAULT;
    }
    else
    {
        if (uBPP >= 8)
        {
            ePixFmt = backend::PixelFormat::RGB888;
        }
        else
        {
            ePixFmt = backend::PixelFormat::RGB565;
        }
    }

    // Repack the pixel data into the right format
    unsigned int uLen = nWidth * nHeight;

    if (ePixFmt == backend::PixelFormat::RGB565)
    {
        if (bHasAlpha)
        {
            // Convert "RRRRRRRRRGGGGGGGGBBBBBBBBAAAAAAAA" to "RRRRRGGGGGGBBBBB"
            inPixel32 = (unsigned int*)img->getData();
            pTmpData = (unsigned char *)malloc(nWidth * nHeight * 2);
            outPixel16 = (unsigned short*)pTmpData;

            for (unsigned int i = 0; i < uLen; ++i, ++inPixel32)
            {
                *outPixel16++ =
                    ((((*inPixel32 >> 0) & 0xFF) >> 3) << 11) |  // R
                    ((((*inPixel32 >> 8) & 0xFF) >> 2) << 5) |  // G
                    ((((*inPixel32 >> 16) & 0xFF) >> 3) << 0);    // B
            }
        }
        else
        {
            // Convert "RRRRRRRRGGGGGGGGBBBBBBBB" to "RRRRRGGGGGGBBBBB"
            pTmpData = (unsigned char *)malloc(nWidth * nHeight * 2);
            outPixel16 = (unsigned short*)pTmpData;
            inPixel8 = (unsigned char*)img->getData();

            for (unsigned int i = 0; i < uLen; ++i)
            {
                unsigned char R = *inPixel8++;
                unsigned char G = *inPixel8++;
                unsigned char B = *inPixel8++;

                *outPixel16++ =
                    ((R >> 3) << 11) |  // R
                    ((G >> 2) << 5) |  // G
                    ((B >> 3) << 0);    // B
            }
        }
    }

    if (bHasAlpha && ePixFmt == backend::PixelFormat::RGB888)
    {
        // Convert "RRRRRRRRRGGGGGGGGBBBBBBBBAAAAAAAA" to "RRRRRRRRGGGGGGGGBBBBBBBB"
        inPixel32 = (unsigned int*)img->getData();

        pTmpData = (unsigned char*)malloc(nWidth * nHeight * 3);
        unsigned char* outPixel8 = pTmpData;

        for (unsigned int i = 0; i < uLen; ++i, ++inPixel32)
        {
            *outPixel8++ = (*inPixel32 >> 0) & 0xFF; // R
            *outPixel8++ = (*inPixel32 >> 8) & 0xFF; // G
            *outPixel8++ = (*inPixel32 >> 16) & 0xFF; // B
        }
    }

    return pTmpData;
}

Image* createImage(const std::string& path)
{
    // Split up directory and filename
    // MUTEX:
    // Needed since addImageAsync calls this method from a different thread

    std::string fullpath = FileUtils::getInstance()->fullPathForFilename(path);
    if (fullpath.size() == 0)
    {
        return nullptr;
    }

    // all images are handled by UIImage except PVR extension that is handled by our own handler
    Image* image = nullptr;
    do
    {
        image = new (std::nothrow) Image();
        CC_BREAK_IF(nullptr == image);

        bool bRet = image->initWithImageFile(fullpath);
        CC_BREAK_IF(!bRet);
    }
    while (0);

    return image;
}

TextureCube::TextureCube()
{
    _imgPath.resize(6);
}

TextureCube::~TextureCube()
{
    CC_SAFE_RELEASE_NULL(_texture);
}

TextureCube* TextureCube::create(const std::string& positive_x, const std::string& negative_x,
                                 const std::string& positive_y, const std::string& negative_y,
                                 const std::string& positive_z, const std::string& negative_z)
{
    auto ret = new (std::nothrow) TextureCube();
    if (ret && ret->init(positive_x, negative_x, positive_y, negative_y, positive_z, negative_z))
    {
        ret->autorelease();
        return ret;
    }
    CC_SAFE_DELETE(ret);
    return nullptr;
}

bool TextureCube::init(const std::string& positive_x, const std::string& negative_x,
                       const std::string& positive_y, const std::string& negative_y,
                       const std::string& positive_z, const std::string& negative_z)
{
    _imgPath[0] = positive_x;
    _imgPath[1] = negative_x;
    _imgPath[2] = positive_y;
    _imgPath[3] = negative_y;
    _imgPath[4] = positive_z;
    _imgPath[5] = negative_z;

    std::vector<Image*> images(6);

    images[0] = createImage(positive_x);
    images[1] = createImage(negative_x);
    images[2] = createImage(positive_y);
    images[3] = createImage(negative_y);
    images[4] = createImage(positive_z);
    images[5] = createImage(negative_z);

    int imageSize = images[0]->getHeight();
    for (int i = 0; i < 6; i++)
    {
        Image* img = images[i];
        if(img->getWidth() != img->getHeight())
        {
            CCASSERT(false, "TextureCubemap: width should be equal to height!");
            return false;
        }
        if(imageSize != img->getWidth())
        {
            CCASSERT(imageSize == img->getWidth(), "TextureCubmap: texture of each face should have same dimension");
            return false;
        }
    }

    backend::TextureDescriptor textureDescriptor;
    textureDescriptor.width = textureDescriptor.height = imageSize;
    textureDescriptor.textureType = backend::TextureType::TEXTURE_CUBE;
    textureDescriptor.samplerDescriptor.minFilter = backend::SamplerFilter::LINEAR;
    textureDescriptor.samplerDescriptor.magFilter = backend::SamplerFilter::LINEAR;
    textureDescriptor.samplerDescriptor.sAddressMode = backend::SamplerAddressMode::CLAMP_TO_EDGE;
    textureDescriptor.samplerDescriptor.tAddressMode = backend::SamplerAddressMode::CLAMP_TO_EDGE;
    _texture = static_cast<backend::TextureCubemapBackend*>(backend::Device::getInstance()->newTexture(textureDescriptor));
    CCASSERT(_texture != nullptr, "TextureCubemap: texture can not be nullptr");

    for (int i = 0; i < 6; i++)
    {
        Image* img = images[i];

        backend::PixelFormat  ePixelFmt;
        unsigned char*          pData = getImageData(img, ePixelFmt);
        uint8_t *cData = nullptr;
        uint8_t *useData = pData;

        //convert pixel format to RGBA
        if (ePixelFmt != backend::PixelFormat::RGBA8888 && ePixelFmt != backend::PixelFormat::DEFAULT)
        {
            size_t len = 0;
            backend::PixelFormatUtils::convertDataToFormat(pData, img->getDataLen(), ePixelFmt, backend::PixelFormat::RGBA8888, &cData, &len);
            if (cData != pData) //convert error
            {
                useData = cData;
            }
            else
            {
                CCASSERT(false, "error: CubeMap texture may be incorrect, failed to convert pixel format data to RGBA8888");
            }
        }

        _texture->updateFaceData(static_cast<backend::TextureCubeFace>(i), useData);
        
        if (cData != pData)
            free(cData);

        if (pData != img->getData())
            free(pData);
    }

    for (auto img: images)
    {
        CC_SAFE_RELEASE(img);
    }

    return true;
}

void TextureCube::setTexParameters(const Texture2D::TexParams& texParams)
{
    _texture->updateSamplerDescriptor(texParams);
}

bool TextureCube::reloadTexture()
{
    return init(_imgPath[0], _imgPath[1], _imgPath[2], _imgPath[3], _imgPath[4], _imgPath[5]);
}

NS_CC_END
