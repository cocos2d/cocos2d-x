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
#include "base/CCNinePatchImageParser.h"
#include "platform/CCImage.h"
#include "base/CCDirector.h"

NS_CC_BEGIN

NinePatchImageParser::~NinePatchImageParser()
{

}

NinePatchImageParser::NinePatchImageParser()
:_image(nullptr)
,_imageFrame(Rect::ZERO)
,_isRotated(false)
{

}


NinePatchImageParser::NinePatchImageParser(Image* image)
:_image(image)
,_imageFrame(Rect::ZERO)
,_isRotated(false)
{
    this->_imageFrame = Rect(0,0,image->getWidth(), image->getHeight());
    CCASSERT(image->getRenderFormat()==Texture2D::PixelFormat::RGBA8888,
             "unsupported format, currently only supports rgba8888");
}

NinePatchImageParser::NinePatchImageParser(Image* image, const Rect& frame, bool rotated)
:_image(image)
,_imageFrame(frame)
,_isRotated(rotated)
{
    CCASSERT(image->getRenderFormat()==Texture2D::PixelFormat::RGBA8888,
             "unsupported format, currently only supports rgba8888");
}

int NinePatchImageParser::getFrameHeight()const
{
    if (_isRotated)
    {
        return _imageFrame.size.width;
    }
    return _imageFrame.size.height;
}

int NinePatchImageParser::getFrameWidth()const
{
    if (_isRotated)
    {
        return _imageFrame.size.height;
    }
    return _imageFrame.size.width;
}

int NinePatchImageParser::getPixelOriginOffset(Direction direction)const
{
    int imageWidth = _image->getWidth();
    int frameWidth = this->getFrameWidth();
    
    int topLineLeftOffset = (int)_imageFrame.origin.y * imageWidth * 4 + (int)_imageFrame.origin.x * 4;
    if(direction == Direction::HORIZONTAL)
    {
        return topLineLeftOffset;
    }
    else
    {
        if(_isRotated)
        {
            return topLineLeftOffset + (frameWidth - 1) * 4;
        }
        else
        {
            return topLineLeftOffset;
        }
    }
}

Vec2 NinePatchImageParser::parseHorizontalMargin()const
{
    unsigned char* data = _image->getData();
    
    data = data + this->getPixelOriginOffset(Direction::HORIZONTAL);
    unsigned char lastPixel = *(data + 3);
    int x1 = 0;
    int x2 = 0;
    
    int length = _imageFrame.origin.x + this->getFrameWidth();
    for(int i = (int)_imageFrame.origin.x; i <= length ; i++)
    {
        unsigned char pixel = *(data + (i - (int)_imageFrame.origin.x) * 4 +3);
        if(pixel != lastPixel)
        {
            if (pixel > 0)
            {
                x1 = (i - (int)_imageFrame.origin.x);
            }
            else
            {
                x2 = (i - (int)_imageFrame.origin.x);
                break;
            }
        }
        lastPixel = pixel;
    }
    return Vec2(x1,x2);
}

Vec2 NinePatchImageParser::parseVerticalMargin()const
{
    unsigned char* data = _image->getData();
    int imageWidth = _image->getWidth();
    
    int y1 = 0;
    int y2 = 0;
    
    data = data + this->getPixelOriginOffset(Direction::VERTICAL);
    unsigned char lastPixel = *(data + 3);
    
    int length = (int)(_imageFrame.origin.y + this->getFrameHeight());
    for(int i = _imageFrame.origin.y; i <= length; i++)
    {
        unsigned char pixel = *(data + (i - (int)_imageFrame.origin.y) * imageWidth * 4 + 3);
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
    return Vec2(y1,y2);
}

Rect NinePatchImageParser::parseCapInset() const
{
    Rect capInsets;
    Vec2 horizontalLine = this->parseHorizontalMargin();
    Vec2 verticalLine = this->parseVerticalMargin();
    
    if(_isRotated)
    {
        capInsets =  Rect(verticalLine.y,
                          _imageFrame.size.height - horizontalLine.y,
                          verticalLine.y - verticalLine.x,
                          horizontalLine.y - horizontalLine.x);
    }
    else
    {
        capInsets = Rect(horizontalLine.x,
                         verticalLine.x,
                         horizontalLine.y - horizontalLine.x,
                         verticalLine.y - verticalLine.x);
    }
    
    capInsets = CC_RECT_PIXELS_TO_POINTS(capInsets);
    return capInsets;
}

void NinePatchImageParser::setSpriteFrameInfo(Image* image, const cocos2d::Rect& frameRect, bool rotated )
{
    this->_image = image;
    CCASSERT(image->getRenderFormat()==Texture2D::PixelFormat::RGBA8888,
             "unsupported format, currently only supports rgba8888");
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
