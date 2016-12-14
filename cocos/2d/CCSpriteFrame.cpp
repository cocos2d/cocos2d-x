/****************************************************************************
Copyright (c) 2008-2011 Ricardo Quesada
Copyright (c) 2010-2012 cocos2d-x.org
Copyright (c) 2011      Zynga Inc.
Copyright (c) 2013-2016 Chukong Technologies Inc.

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

#include "renderer/CCTextureCache.h"
#include "2d/CCSpriteFrame.h"
#include "base/CCDirector.h"
#include "platform/CCFileUtils.h"

NS_CC_BEGIN

// implementation of SpriteFrame

SpriteFrame* SpriteFrame::create(const std::string& filename, const Rect& rect)
{
    SpriteFrame *spriteFrame = new (std::nothrow) SpriteFrame();
    spriteFrame->initWithTextureFilename(filename, rect);
    spriteFrame->autorelease();

    return spriteFrame;
}

SpriteFrame* SpriteFrame::createWithTexture(Texture2D *texture, const Rect& rect)
{
    SpriteFrame *spriteFrame = new (std::nothrow) SpriteFrame();
    spriteFrame->initWithTexture(texture, rect);
    spriteFrame->autorelease();
    
    return spriteFrame;
}

SpriteFrame* SpriteFrame::createWithTexture(Texture2D* texture, const Rect& rect, bool rotated, const Vec2& offset, const Size& originalSize)
{
    SpriteFrame *spriteFrame = new (std::nothrow) SpriteFrame();
    if (spriteFrame && spriteFrame->initWithTexture(texture, rect, rotated, offset, originalSize)) {
        spriteFrame->autorelease();
        return spriteFrame;
    }

    delete spriteFrame;
    return nullptr;
}

SpriteFrame* SpriteFrame::create(const std::string& filename, const Rect& rect, bool rotated, const Vec2& offset, const Size& originalSize)
{
    SpriteFrame *spriteFrame = new (std::nothrow) SpriteFrame();
    if (spriteFrame && spriteFrame->initWithTextureFilename(filename, rect, rotated, offset, originalSize)) {
        spriteFrame->autorelease();
        return spriteFrame;
    }
    delete spriteFrame;
    return nullptr;
}

SpriteFrame::SpriteFrame()
: _rotated(false)
, _texture(nullptr)
{
}

bool SpriteFrame::initWithTexture(Texture2D* texture, const Rect& rect)
{
    Rect rectInPixels = CC_RECT_POINTS_TO_PIXELS(rect);
    return initWithTexture(texture, rectInPixels, false, Vec2::ZERO, rectInPixels.size);
}

bool SpriteFrame::initWithTextureFilename(const std::string& filename, const Rect& rect)
{
    Rect rectInPixels = CC_RECT_POINTS_TO_PIXELS( rect );
    return initWithTextureFilename(filename, rectInPixels, false, Vec2::ZERO, rectInPixels.size);
}

bool SpriteFrame::initWithTexture(Texture2D* texture, const Rect& rect, bool rotated, const Vec2& offset, const Size& originalSize)
{
    _texture = texture;

    if (texture)
    {
        texture->retain();
    }

    _rectInPixels = rect;
    _rect = CC_RECT_PIXELS_TO_POINTS(rect);
    _offsetInPixels = offset;
    _offset = CC_POINT_PIXELS_TO_POINTS( _offsetInPixels );
    _originalSizeInPixels = originalSize;
    _originalSize = CC_SIZE_PIXELS_TO_POINTS( _originalSizeInPixels );
    _rotated = rotated;
    _anchorPoint = Vec2(NAN, NAN);
    _centerRect = Rect(NAN, NAN, NAN, NAN);

    return true;
}

bool SpriteFrame::initWithTextureFilename(const std::string& filename, const Rect& rect, bool rotated, const Vec2& offset, const Size& originalSize)
{
    if (FileUtils::getInstance()->isFileExist(filename)) {
        _texture = nullptr;
        _textureFilename = filename;
        _rectInPixels = rect;
        _rect = CC_RECT_PIXELS_TO_POINTS( rect );
        _offsetInPixels = offset;
        _offset = CC_POINT_PIXELS_TO_POINTS( _offsetInPixels );
        _originalSizeInPixels = originalSize;
        _originalSize = CC_SIZE_PIXELS_TO_POINTS( _originalSizeInPixels );
        _rotated = rotated;
        _anchorPoint = Vec2(NAN, NAN);
        _centerRect = Rect(NAN, NAN, NAN, NAN);
        return true;
    }
    return false;
}

SpriteFrame::~SpriteFrame()
{
    CCLOGINFO("deallocing SpriteFrame: %p", this);
    CC_SAFE_RELEASE(_texture);
}

SpriteFrame* SpriteFrame::clone() const
{
	// no copy constructor	
    SpriteFrame *copy = new (std::nothrow) SpriteFrame();
    copy->initWithTexture(_texture, _rectInPixels, _rotated, _offsetInPixels, _originalSizeInPixels);
    copy->setPolygonInfo(_polygonInfo);
    copy->autorelease();
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

void SpriteFrame::setCenterRectInPixels(const Rect& centerRect)
{
    _centerRect = CC_RECT_PIXELS_TO_POINTS(centerRect);
}

bool SpriteFrame::hasCenterRect() const
{
    return !std::isnan(_centerRect.origin.x);
}

const Vec2& SpriteFrame::getOffset() const
{
    return _offset;
}

void SpriteFrame::setOffset(const Vec2& offsets)
{
    _offset = offsets;
    _offsetInPixels = CC_POINT_POINTS_TO_PIXELS( _offset );
}

const Vec2& SpriteFrame::getOffsetInPixels() const
{
    return _offsetInPixels;
}

void SpriteFrame::setOffsetInPixels(const Vec2& offsetInPixels)
{
    _offsetInPixels = offsetInPixels;
    _offset = CC_POINT_PIXELS_TO_POINTS( _offsetInPixels );
}

const Vec2& SpriteFrame::getAnchorPoint() const
{
    return _anchorPoint;
}

void SpriteFrame::setAnchorPoint(const Vec2& anchorPoint)
{
    _anchorPoint = anchorPoint;
}

bool SpriteFrame::hasAnchorPoint() const
{
    return !std::isnan(_anchorPoint.x);
}

void SpriteFrame::setTexture(Texture2D * texture)
{
    if( _texture != texture ) {
        CC_SAFE_RELEASE(_texture);
        CC_SAFE_RETAIN(texture);
        _texture = texture;
    }
}

Texture2D* SpriteFrame::getTexture()
{
    if( _texture ) {
        return _texture;
    }

    if( !_textureFilename.empty()) {
        return Director::getInstance()->getTextureCache()->addImage(_textureFilename);
    }
    // no texture or texture filename
    return nullptr;
}

void SpriteFrame::setPolygonInfo(const PolygonInfo &polygonInfo)
{
    _polygonInfo = polygonInfo;
}

const PolygonInfo& SpriteFrame::getPolygonInfo() const
{
    return _polygonInfo;
}

bool SpriteFrame::hasPolygonInfo() const
{
    return _polygonInfo.triangles.vertCount != 0;
}

NS_CC_END
