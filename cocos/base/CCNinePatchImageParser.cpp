/****************************************************************************
 Copyright (c) 2013-2015 Chukong Technologies Inc.

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
#include "CCNinePatchImageParser.h"
#include "platform/CCImage.h"
#include "base/CCDirector.h"

NS_CC_BEGIN

NinePatchImageParser::~NinePatchImageParser()
{

}


NinePatchImageParser::NinePatchImageParser(Image* image)
{
    this->_image = image;
    this->_imageFrame = Rect(0,0,image->getWidth(), image->getHeight());
    CCASSERT(image->getRenderFormat()==Texture2D::PixelFormat::RGBA8888,
             "unsupported format, currently only supports rgba8888");
    this->_isRotated = false;
}

NinePatchImageParser::NinePatchImageParser(Image* image, const Rect& frame, bool rotated)
{
    this->_image = image;
    CCASSERT(image->getRenderFormat()==Texture2D::PixelFormat::RGBA8888,
             "unsupported format, currently only supports rgba8888");
    this->_imageFrame = frame;
    this->_isRotated = rotated;
}

Rect NinePatchImageParser::parseCapInset() const
{
    unsigned char* data = _image->getData();
    int imageWidth = _image->getWidth();
    int imageHeight = _image->getHeight();
    int frameWidth = _imageFrame.size.width;
    if(_isRotated)
    {
        frameWidth = _imageFrame.size.height;
    }
    int topLineLeftOffset = (int)_imageFrame.origin.x;

    unsigned char lastPixel = *(data + (int)_imageFrame.origin.y * imageWidth * 4 + topLineLeftOffset * 4 + 3);
    int x1 = 0;
    int x2 = 0;

    for(int i = topLineLeftOffset; i < imageWidth ; i++)
    {
        unsigned char pixel = *(data + (int)_imageFrame.origin.y * imageWidth * 4 + i*4 +3);
        if(pixel != lastPixel)
        {
            if (pixel > 0)
            {
                x1 = (i - (int)_imageFrame.origin.x) % imageWidth;
            }
            else
            {
                x2 = (i - (int)_imageFrame.origin.x) % imageWidth;
                break;
            }
        }
        lastPixel = pixel;
    }

    int y1 = 0;
    int y2 = 0;

    int stepOffset = 0;
    if(_isRotated)
    {
        lastPixel = *(data + (int)(_imageFrame.origin.y * imageWidth * 4) + topLineLeftOffset * 4 + (frameWidth -1) * 4 +3);
        stepOffset = (topLineLeftOffset + frameWidth-1 ) * 4;
    }
    else
    {
        lastPixel = *(data + (int)(_imageFrame.origin.y * imageWidth * 4) + topLineLeftOffset * 4 +3);
        stepOffset = topLineLeftOffset * 4;
    }

    for(int i = _imageFrame.origin.y; i < imageHeight; i++)
    {
        unsigned char pixel = *(data + i * imageWidth * 4 + stepOffset + 3);
        if(pixel != lastPixel)
        {
            if(pixel > 0)
            {
                y1 = (i - (int)_imageFrame.origin.y);
            }
            else
            {
                y2 = (i - (int)_imageFrame.origin.y);
                break;
            }
        }
        lastPixel = pixel;
    }

    Rect capInsets;

    if(_isRotated)
    {
        capInsets =  Rect(y1, _imageFrame.size.height - x2 , y2 - y1, x2 - x1);
    }
    else
    {
        capInsets = Rect(x1, y1 , x2 - x1, y2 - y1);
    }
    capInsets = Rect(capInsets.origin.x / CC_CONTENT_SCALE_FACTOR(),
                     capInsets.origin.y / CC_CONTENT_SCALE_FACTOR(),
                     capInsets.size.width / CC_CONTENT_SCALE_FACTOR(),
                     capInsets.size.height / CC_CONTENT_SCALE_FACTOR());
    return capInsets;
}

void NinePatchImageParser::setSpriteFrameInfo( const cocos2d::Rect& frameRect, bool rotated )
{
    this->_imageFrame = frameRect;
    this->_isRotated = rotated;
}

bool NinePatchImageParser::isNinePatchImage(const std::string& filepath)
{
    size_t length = filepath.length();
    if(length <7 )
    {
        return false;
    }
    if(filepath.compare(length-6, 6, ".9.png") == 0)
    {
        return true;
    }
    else
    {
        return false;
    }
}

NS_CC_END
