/****************************************************************************
 Copyright (c) 2015 Chukong Technologies Inc.
 
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

#include "renderer/ccGLStateCache.h"

NS_CC_BEGIN

unsigned char* getImageData(Image* img, Texture2D::PixelFormat&  ePixFmt)
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
        ePixFmt = Texture2D::PixelFormat::DEFAULT;
    }
    else
    {
        if (uBPP >= 8)
        {
            ePixFmt = Texture2D::PixelFormat::RGB888;
        }
        else
        {
            ePixFmt = Texture2D::PixelFormat::RGB565;
        }
    }

    // Repack the pixel data into the right format
    unsigned int uLen = nWidth * nHeight;

    if (ePixFmt == Texture2D::PixelFormat::RGB565)
    {
        if (bHasAlpha)
        {
            // Convert "RRRRRRRRRGGGGGGGGBBBBBBBBAAAAAAAA" to "RRRRRGGGGGGBBBBB"
            inPixel32 = (unsigned int*)img->getData();
            pTmpData = new (std::nothrow) unsigned char[nWidth * nHeight * 2];
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
            pTmpData = new (std::nothrow) unsigned char[nWidth * nHeight * 2];
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

    if (bHasAlpha && ePixFmt == Texture2D::PixelFormat::RGB888)
    {
        // Convert "RRRRRRRRRGGGGGGGGBBBBBBBBAAAAAAAA" to "RRRRRRRRGGGGGGGGBBBBBBBB"
        inPixel32 = (unsigned int*)img->getData();

        pTmpData = new (std::nothrow) unsigned char[nWidth * nHeight * 3];
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

    GLuint handle;
    glGenTextures(1, &handle);

    GL::bindTextureN(0, handle, GL_TEXTURE_CUBE_MAP);

    for (int i = 0; i < 6; i++)
    {
        Image* img = images[i];

        Texture2D::PixelFormat  ePixelFmt;
        unsigned char*          pData = getImageData(img, ePixelFmt);
        if (ePixelFmt == Texture2D::PixelFormat::RGBA8888 || ePixelFmt == Texture2D::PixelFormat::DEFAULT)
        {
            glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i,
                         0,                  // level
                         GL_RGBA,            // internal format
                         img->getWidth(),    // width
                         img->getHeight(),   // height
                         0,                  // border
                         GL_RGBA,            // format
                         GL_UNSIGNED_BYTE,   // type
                         pData);             // pixel data
        }
        else if (ePixelFmt == Texture2D::PixelFormat::RGB888)
        {
            glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i,
                         0,                  // level
                         GL_RGB,             // internal format
                         img->getWidth(),    // width
                         img->getHeight(),   // height
                         0,                  // border
                         GL_RGB,             // format
                         GL_UNSIGNED_BYTE,   // type
                         pData);             // pixel data
        }

        if (pData != img->getData())
            delete[] pData;
    }

    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

    _name = handle;

    GL::bindTextureN(0, 0, GL_TEXTURE_CUBE_MAP);

    for (auto img: images)
    {
        CC_SAFE_RELEASE(img);
    }

    return true;
}

void TextureCube::setTexParameters(const TexParams& texParams)
{
    CCASSERT(_name != 0, __FUNCTION__);

    GL::bindTextureN(0, _name, GL_TEXTURE_CUBE_MAP);

    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, texParams.minFilter);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, texParams.magFilter);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, texParams.wrapS);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, texParams.wrapT);

    GL::bindTextureN(0, 0, GL_TEXTURE_CUBE_MAP);
}

bool TextureCube::reloadTexture()
{
    return init(_imgPath[0], _imgPath[1], _imgPath[2], _imgPath[3], _imgPath[4], _imgPath[5]);
}

NS_CC_END
