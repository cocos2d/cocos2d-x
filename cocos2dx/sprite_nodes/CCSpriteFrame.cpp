/****************************************************************************
Copyright (c) 2010-2012 cocos2d-x.org
Copyright (c) 2008-2011 Ricardo Quesada
Copyright (c) 2011      Zynga Inc.

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
#include "textures/CCTextureCache.h"
#include "CCSpriteFrame.h"
#include "CCDirector.h"

NS_CC_BEGIN

// implementation of SpriteFrame

SpriteFrame* SpriteFrame::create(const char* filename, const Rect& rect)
{
    SpriteFrame *pSpriteFrame = new SpriteFrame();;
    pSpriteFrame->initWithTextureFilename(filename, rect);
    pSpriteFrame->autorelease();

    return pSpriteFrame;
}

SpriteFrame* SpriteFrame::createWithTexture(Texture2D *pobTexture, const Rect& rect)
{
    SpriteFrame *pSpriteFrame = new SpriteFrame();;
    pSpriteFrame->initWithTexture(pobTexture, rect);
    pSpriteFrame->autorelease();
    
    return pSpriteFrame;
}

SpriteFrame* SpriteFrame::createWithTexture(Texture2D* pobTexture, const Rect& rect, bool rotated, const Point& offset, const Size& originalSize)
{
    SpriteFrame *pSpriteFrame = new SpriteFrame();;
    pSpriteFrame->initWithTexture(pobTexture, rect, rotated, offset, originalSize);
    pSpriteFrame->autorelease();

    return pSpriteFrame;
}

SpriteFrame* SpriteFrame::create(const char* filename, const Rect& rect, bool rotated, const Point& offset, const Size& originalSize)
{
    SpriteFrame *pSpriteFrame = new SpriteFrame();;
    pSpriteFrame->initWithTextureFilename(filename, rect, rotated, offset, originalSize);
    pSpriteFrame->autorelease();

    return pSpriteFrame;
}

bool SpriteFrame::initWithTexture(Texture2D* pobTexture, const Rect& rect)
{
    Rect rectInPixels = CC_RECT_POINTS_TO_PIXELS(rect);
    return initWithTexture(pobTexture, rectInPixels, false, Point::ZERO, rectInPixels.size);
}

bool SpriteFrame::initWithTextureFilename(const char* filename, const Rect& rect)
{
    Rect rectInPixels = CC_RECT_POINTS_TO_PIXELS( rect );
    return initWithTextureFilename(filename, rectInPixels, false, Point::ZERO, rectInPixels.size);
}

bool SpriteFrame::initWithTexture(Texture2D* pobTexture, const Rect& rect, bool rotated, const Point& offset, const Size& originalSize)
{
    _texture = pobTexture;

    if (pobTexture)
    {
        pobTexture->retain();
    }

    _rectInPixels = rect;
    _rect = CC_RECT_PIXELS_TO_POINTS(rect);
    _offsetInPixels = offset;
    _offset = CC_POINT_PIXELS_TO_POINTS( _offsetInPixels );
    _originalSizeInPixels = originalSize;
    _originalSize = CC_SIZE_PIXELS_TO_POINTS( _originalSizeInPixels );
    _rotated = rotated;

    return true;
}

bool SpriteFrame::initWithTextureFilename(const char* filename, const Rect& rect, bool rotated, const Point& offset, const Size& originalSize)
{
    _texture = NULL;
    _textureFilename = filename;
    _rectInPixels = rect;
    _rect = CC_RECT_PIXELS_TO_POINTS( rect );
    _offsetInPixels = offset;
    _offset = CC_POINT_PIXELS_TO_POINTS( _offsetInPixels );
    _originalSizeInPixels = originalSize;
    _originalSize = CC_SIZE_PIXELS_TO_POINTS( _originalSizeInPixels );
    _rotated = rotated;

    return true;
}

SpriteFrame::~SpriteFrame(void)
{
    CCLOGINFO("cocos2d: deallocing %p", this);
    CC_SAFE_RELEASE(_texture);
}

SpriteFrame* SpriteFrame::clone() const
{
	// no copy constructor	
    SpriteFrame *copy = new SpriteFrame();
    copy->initWithTextureFilename(_textureFilename.c_str(), _rectInPixels, _rotated, _offsetInPixels, _originalSizeInPixels);
    copy->setTexture(_texture);
    return copy;
}

void SpriteFrame::setRect(const Rect& rect)
{
    _rect = rect;
    _rectInPixels = CC_RECT_POINTS_TO_PIXELS(_rect);
}

void SpriteFrame::setRectInPixels(const Rect& rectInPixels)
{
    _rectInPixels = rectInPixels;
    _rect = CC_RECT_PIXELS_TO_POINTS(rectInPixels);
}

const Point& SpriteFrame::getOffset() const
{
    return _offset;
}

void SpriteFrame::setOffset(const Point& offsets)
{
    _offset = offsets;
    _offsetInPixels = CC_POINT_POINTS_TO_PIXELS( _offset );
}

const Point& SpriteFrame::getOffsetInPixels() const
{
    return _offsetInPixels;
}

void SpriteFrame::setOffsetInPixels(const Point& offsetInPixels)
{
    _offsetInPixels = offsetInPixels;
    _offset = CC_POINT_PIXELS_TO_POINTS( _offsetInPixels );
}

void SpriteFrame::setTexture(Texture2D * texture)
{
    if( _texture != texture ) {
        CC_SAFE_RELEASE(_texture);
        CC_SAFE_RETAIN(texture);
        _texture = texture;
    }
}

Texture2D* SpriteFrame::getTexture(void)
{
    if( _texture ) {
        return _texture;
    }

    if( _textureFilename.length() > 0 ) {
        return TextureCache::getInstance()->addImage(_textureFilename.c_str());
    }
    // no texture or texture filename
    return NULL;
}

NS_CC_END

