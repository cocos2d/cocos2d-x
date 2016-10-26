/****************************************************************************
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

#include "ui/UIScale9Sprite.h"
#include "2d/CCSprite.h"
#include "2d/CCSpriteFrameCache.h"
#include "base/CCVector.h"
#include "base/CCDirector.h"
#include "base/ccUTF8.h"
#include "renderer/CCGLProgram.h"
#include "renderer/ccShaders.h"
#include "platform/CCImage.h"
#include "base/CCNinePatchImageParser.h"
#include "2d/CCDrawNode.h"
#include "2d/CCCamera.h"
#include "renderer/CCRenderer.h"

using namespace cocos2d;
using namespace cocos2d::ui;

Scale9Sprite::Scale9Sprite()
{
#if CC_SPRITE_DEBUG_DRAW
    _debugDrawNode = DrawNode::create();
    addChild(_debugDrawNode);
#endif //CC_SPRITE_DEBUG_DRAW
}

Scale9Sprite::~Scale9Sprite()
{
}

bool Scale9Sprite::initWithFile(const Rect& capInsets, const std::string& file)
{
    return initWithFile(file, Rect::ZERO, capInsets);
}

bool Scale9Sprite::initWithSpriteFrame(SpriteFrame* spriteFrame,
                                       const Rect& capInsets)
{
    bool ret = false;
    do {
        Texture2D* texture = spriteFrame->getTexture();
        CCASSERT(texture != nullptr, "Texture2D must be not null");
        if(texture == nullptr) break;
        
        Sprite *sprite = Sprite::createWithSpriteFrame(spriteFrame);
        CCASSERT(sprite != nullptr, "Sprite must be not null");
        if(sprite == nullptr) break;
        
        ret = init(sprite,
                                  spriteFrame->getRect(),
                                  spriteFrame->isRotated(),
                                  spriteFrame->getOffset(),
                                  spriteFrame->getOriginalSize(),
                                  capInsets);
    } while (false);
    
    return ret;
}

bool Scale9Sprite::initWithSpriteFrameName(const std::string& spriteFrameName,
                                           const Rect& capInsets)
{

    bool ret = initWithSpriteFrameName(spriteFrameName);
    setCapInsets(capInsets);
    return ret;
}

bool Scale9Sprite::init()
{
    return init(nullptr, Rect::ZERO, Rect::ZERO);
}

bool Scale9Sprite::init(Sprite* sprite, const Rect& rect, const Rect& capInsets)
{
    return init(sprite, rect, false, capInsets);
}

bool Scale9Sprite::init(Sprite* sprite,
                        const Rect& rect,
                        bool rotated,
                        const Rect& capInsets)
{
    return init(sprite, rect, rotated, Vec2::ZERO, rect.size, capInsets);
}

bool Scale9Sprite::init(Sprite* sprite,
                        const Rect& rect,
                        bool rotated,
                        const Vec2 &offset,
                        const Size &originalSize,
                        const Rect& capInsets)
{
    bool ret = false;
    if (sprite) {
        auto texture = sprite->getTexture();
        auto spriteFrame = SpriteFrame::createWithTexture(texture, rect, rotated, offset, originalSize);
        ret = initWithSpriteFrame(spriteFrame);
    } else {
        ret = initWithTexture(nullptr, rect, rotated);
    }
    setCapInsets(capInsets);
    return ret;

}

bool Scale9Sprite::initWithBatchNode(cocos2d::SpriteBatchNode *batchnode,
                                     const cocos2d::Rect &rect,
                                     bool rotated,
                                     const cocos2d::Rect &capInsets)
{
    auto sprite = Sprite::createWithTexture(batchnode->getTexture());
    return init(sprite, rect, rotated, capInsets);
}

bool Scale9Sprite::initWithBatchNode(cocos2d::SpriteBatchNode *batchnode,
                                     const cocos2d::Rect &rect,
                                     const cocos2d::Rect &capInsets)
{
    auto sprite = Sprite::createWithTexture(batchnode->getTexture());
    return init(sprite, rect, false, capInsets);
}
bool Scale9Sprite::initWithFile(const std::string& file,
                                const Rect& rect,
                                const Rect& capInsets)
{
    auto ret = initWithFile(file, rect);
    setCapInsets(capInsets);
    return ret;
}

Scale9Sprite* Scale9Sprite::create()
{
    Scale9Sprite *ret = new (std::nothrow) Scale9Sprite();
    if (ret && ret->init())
    {
        ret->autorelease();
        return ret;
    }
    CC_SAFE_DELETE(ret);
    return nullptr;
}

Scale9Sprite* Scale9Sprite::create(const std::string& file,
                                   const Rect& rect,
                                   const Rect& capInsets)
{
    Scale9Sprite* ret = new (std::nothrow) Scale9Sprite();
    if (ret && ret->initWithFile(file, rect, capInsets))
    {
        ret->autorelease();
        return ret;
    }
    CC_SAFE_DELETE(ret);
    return nullptr;
}


Scale9Sprite* Scale9Sprite::create(const std::string& file, const Rect& rect)
{
    Scale9Sprite* ret = new (std::nothrow) Scale9Sprite();
    if (ret && ret->initWithFile(file, rect))
    {
        ret->autorelease();
        return ret;
    }
    CC_SAFE_DELETE(ret);
    return nullptr;
}



Scale9Sprite* Scale9Sprite::create(const Rect& capInsets,
                                   const std::string& file)
{
    Scale9Sprite* ret = new (std::nothrow) Scale9Sprite();
    if (ret && ret->initWithFile(capInsets, file))
    {
        ret->autorelease();
        return ret;
    }
    CC_SAFE_DELETE(ret);
    return nullptr;
}


Scale9Sprite* Scale9Sprite::create(const std::string& file)
{
    Scale9Sprite* ret = new (std::nothrow) Scale9Sprite();
    if (ret && ret->initWithFile(file) )
    {
        ret->autorelease();
        return ret;
    }
    CC_SAFE_DELETE(ret);
    return nullptr;
}


Scale9Sprite* Scale9Sprite::createWithSpriteFrame(SpriteFrame* spriteFrame,
                                                  const Rect& capInsets)
{
    Scale9Sprite* ret = new (std::nothrow) Scale9Sprite();
    if (ret && ret->initWithSpriteFrame(spriteFrame, capInsets) )
    {
        ret->autorelease();
        return ret;
    }
    CC_SAFE_DELETE(ret);
    return nullptr;
}

Scale9Sprite* Scale9Sprite::createWithSpriteFrame(SpriteFrame* spriteFrame)
{
    Scale9Sprite* ret = new (std::nothrow) Scale9Sprite();
    if (ret && ret->initWithSpriteFrame(spriteFrame) )
    {
        ret->autorelease();
        return ret;
    }
    CC_SAFE_DELETE(ret);
    return nullptr;
}

Scale9Sprite* Scale9Sprite::createWithSpriteFrameName(const std::string& spriteFrameName,
                                                      const Rect& capInsets)
{
    Scale9Sprite* ret = new (std::nothrow) Scale9Sprite();
    if (ret && ret->initWithSpriteFrameName(spriteFrameName, capInsets) )
    {
        ret->autorelease();
        return ret;
    }
    CC_SAFE_DELETE(ret);
    return nullptr;
}

Scale9Sprite* Scale9Sprite::createWithSpriteFrameName(const std::string& spriteFrameName)
{
    Scale9Sprite* ret = new (std::nothrow) Scale9Sprite();
    if (ret && ret->initWithSpriteFrameName(spriteFrameName) )
    {
        ret->autorelease();
        return ret;
    }
    CC_SAFE_DELETE(ret);

    log("Could not allocate Scale9Sprite()");
    return nullptr;
}

bool Scale9Sprite::updateWithBatchNode(cocos2d::SpriteBatchNode *batchnode,
                                       const cocos2d::Rect &originalRect,
                                       bool rotated,
                                       const cocos2d::Rect &capInsets)
{
    Sprite *sprite = Sprite::createWithTexture(batchnode->getTexture());
    return updateWithSprite(sprite,
                                  originalRect,
                                  rotated,
                                  Vec2::ZERO,
                                  originalRect.size,
                                  capInsets);
}

bool Scale9Sprite::updateWithSprite(Sprite* sprite,
                                    const Rect& rect,
                                    bool rotated,
                                    const Rect& capInsets)
{
    return updateWithSprite(sprite, rect, rotated, Vec2::ZERO, rect.size, capInsets);
}

bool Scale9Sprite::updateWithSprite(Sprite* sprite,
                                    const Rect& textureRect,
                                    bool rotated,
                                    const Vec2 &offset,
                                    const Size &originalSize,
                                    const Rect& capInsets)
{
    // FIXME
    return true;
}

Scale9Sprite* Scale9Sprite::resizableSpriteWithCapInsets(const Rect& capInsets) const
{
    // FIXME
    return nullptr;
}

Scale9Sprite::State Scale9Sprite::getState() const
{
    return _brightState;
}

void Scale9Sprite::setState(Scale9Sprite::State state)
{
    // FIXME
}

void Scale9Sprite::setSpriteFrame(SpriteFrame * spriteFrame, const Rect& capInsets)
{
    // FIXME
}

void Scale9Sprite::setPreferredSize(const Size& preferredSize)
{
    setContentSize(preferredSize);
}

void Scale9Sprite::setCapInsets(const Rect& capInsets)
{
    _capInsetsInternal = capInsets;
    setCenterRect(capInsets);
}

void Scale9Sprite::setInsetLeft(float insetLeft)
{
    _insetLeft = insetLeft;
    updateCapInset();
}

void Scale9Sprite::setInsetTop(float insetTop)
{
    _insetTop = insetTop;
    updateCapInset();
}

void Scale9Sprite::setInsetRight(float insetRight)
{
    _insetRight = insetRight;
    updateCapInset();
}

void Scale9Sprite::setInsetBottom(float insetBottom)
{
    _insetBottom = insetBottom;
    updateCapInset();
}

void Scale9Sprite::updateCapInset()
{
    Rect centerRect(_insetLeft, _insetTop, _insetRight-_insetLeft, _insetBottom-_insetTop);
    setCenterRect(centerRect);
}

Size Scale9Sprite::getOriginalSize()const
{
    return _originalSize;
}

Size Scale9Sprite::getPreferredSize() const
{
    return _preferredSize;
}

Rect Scale9Sprite::getCapInsets()const
{
    return _capInsetsInternal;
}

float Scale9Sprite::getInsetLeft()const
{
    return _insetLeft;
}

float Scale9Sprite::getInsetTop()const
{
    return _insetTop;
}

float Scale9Sprite::getInsetRight()const
{
    return _insetRight;
}

float Scale9Sprite::getInsetBottom()const
{
    return _insetBottom;
}

void Scale9Sprite::setScale9Enabled(bool enabled)
{
    // FIXME
}

bool Scale9Sprite::isScale9Enabled() const
{
    // FIXME
    return true;
}

Sprite* Scale9Sprite::getSprite()
{
    return this;
}

// (0,0)  O = capInsets.origin
// v0----------------------
// |        |      |      |
// |        |      |      |
// v1-------O------+------|
// |        |      |      |
// |        |      |      |
// v2-------+------+------|
// |        |      |      |
// |        |      |      |
// v3-------------------- (1,1)  (texture coordinate is flipped)
// u0       u1     u2     u3

//
// y3----------------------(preferedSize.width, preferedSize.height)
// |        |      |      |
// |        |      |      |
// y2-------O------+------|
// |        |      |      |
// |        |      |      |
// y1-------+------+------|
// |        |      |      |
// |        |      |      |
//x0,y0--------------------
//         x1     x2     x3

void Scale9Sprite::setRenderingType(Scale9Sprite::RenderingType type)
{
    // FIXME
    _renderingType = type;
}

Scale9Sprite::RenderingType Scale9Sprite::getRenderingType()const
{
    return _renderingType;
}

void Scale9Sprite::resetRender()
{
    // FIXME
}

