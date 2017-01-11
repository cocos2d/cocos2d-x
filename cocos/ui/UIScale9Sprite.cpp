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

Scale9Sprite* Scale9Sprite::create(const std::string& filename, const Rect& rect, const Rect& capInsets)
{
    Scale9Sprite* ret = new (std::nothrow) Scale9Sprite();
    if (ret && ret->initWithFile(filename, rect, capInsets))
    {
        ret->autorelease();
        return ret;
    }
    CC_SAFE_DELETE(ret);
    return nullptr;
}

Scale9Sprite* Scale9Sprite::create(const std::string& filename, const Rect& rect)
{
    return create(filename, rect, Rect::ZERO);
}

Scale9Sprite* Scale9Sprite::create(const Rect& capInsets, const std::string& file)
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

Scale9Sprite* Scale9Sprite::create(const std::string& fileaname)
{
    return create(Rect::ZERO, fileaname);
}

Scale9Sprite* Scale9Sprite::createWithSpriteFrame(SpriteFrame* spriteFrame, const Rect& capInsets)
{
    Scale9Sprite* ret = new (std::nothrow) Scale9Sprite();
    if (ret && ret->initWithSpriteFrame(spriteFrame, capInsets))
    {
        ret->autorelease();
        return ret;
    }
    CC_SAFE_DELETE(ret);
    return nullptr;
}

Scale9Sprite* Scale9Sprite::createWithSpriteFrame(SpriteFrame* spriteFrame)
{
    return createWithSpriteFrame(spriteFrame, Rect::ZERO);
}

Scale9Sprite* Scale9Sprite::createWithSpriteFrameName(const std::string& spriteFrameName, const Rect& capInsets)
{
    Scale9Sprite* ret = new (std::nothrow) Scale9Sprite();
    if (ret && ret->initWithSpriteFrameName(spriteFrameName, capInsets))
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
    if (ret && ret->initWithSpriteFrameName(spriteFrameName, Rect::ZERO))
    {
        ret->autorelease();
        return ret;
    }
    CC_SAFE_DELETE(ret);

    log("Could not allocate Scale9Sprite()");
    return nullptr;
}

Scale9Sprite::Scale9Sprite()
: _brightState(State::NORMAL)
, _renderingType(RenderingType::SLICE)
, _insetLeft(0)
, _insetTop(0)
, _insetRight(0)
, _insetBottom(0)
, _isPatch9(false)
{
}

Scale9Sprite::~Scale9Sprite()
{
}

bool Scale9Sprite::initWithFile(const Rect& capInsets, const std::string& file)
{
    // calls super
    bool ret = Sprite::initWithFile(file);
    setupSlice9(getTexture(), capInsets);
    return ret;
}

bool Scale9Sprite::initWithFile(const std::string& filename)
{
    // calls super
    bool ret = Sprite::initWithFile(filename);
    setupSlice9(getTexture(), Rect::ZERO);
    return ret;
}

bool Scale9Sprite::initWithFile(const std::string& filename, const Rect& rect)
{
    // calls super
    bool ret = Sprite::initWithFile(filename, rect);
    setupSlice9(getTexture(), Rect::ZERO);
    return ret;
}

bool Scale9Sprite::initWithSpriteFrame(SpriteFrame* spriteFrame, const Rect& capInsets)
{
    // calls super
    bool ret = Sprite::initWithSpriteFrame(spriteFrame);
    setupSlice9(getTexture(), capInsets);
    return ret;
}

bool Scale9Sprite::initWithSpriteFrameName(const std::string& spriteFrameName, const Rect& capInsets)
{
    // calls super
    bool ret = Sprite::initWithSpriteFrameName(spriteFrameName);
    setupSlice9(getTexture(), capInsets);
    return ret;
}

bool Scale9Sprite::initWithSpriteFrameName(const std::string& spriteFrameName)
{
    // calls super
    bool ret = Sprite::initWithSpriteFrameName(spriteFrameName);
    setupSlice9(getTexture(), Rect::ZERO);
    return ret;
}

bool Scale9Sprite::init()
{
    // calls super
    bool ret = Sprite::init();
    setupSlice9(getTexture(), Rect::ZERO);
    return ret;
}

bool Scale9Sprite::init(Sprite* sprite, const Rect& rect, const Rect& capInsets)
{
    return init(sprite, rect, false, capInsets);
}

bool Scale9Sprite::init(Sprite* sprite, const Rect& rect, bool rotated, const Rect& capInsets)
{
    return init(sprite, rect, rotated, Vec2::ZERO, rect.size, capInsets);
}

bool Scale9Sprite::init(Sprite* sprite, const Rect& origRect, bool rotated, const Vec2 &offset, const Size &originalSize, const Rect& capInsets)
{
    bool ret = false;

    Rect rect(origRect);

    if (sprite) {
        auto texture = sprite->getTexture();

        if (origRect.equals(Rect::ZERO))
            rect.size = texture->getContentSize();

        auto spriteFrame = SpriteFrame::createWithTexture(texture, rect, rotated, offset, originalSize);
        ret = initWithSpriteFrame(spriteFrame);

        setupSlice9(texture, capInsets);
    } else {
        ret = initWithTexture(nullptr, rect, rotated);
        setupSlice9(nullptr, capInsets);
    }
    return ret;
}

bool Scale9Sprite::initWithBatchNode(SpriteBatchNode *batchnode, const Rect &rect, bool rotated, const Rect &capInsets)
{
    auto sprite = Sprite::createWithTexture(batchnode->getTexture());
    return init(sprite, rect, rotated, capInsets);
}

bool Scale9Sprite::initWithFile(const std::string& filename, const Rect& rect, const Rect& capInsets)
{
    // calls super
    bool ret = false;
    if (!rect.equals(Rect::ZERO))
    {
        ret = Sprite::initWithFile(filename, rect);
    }
    else // if rect is zero, use the whole texture size.
    {
        ret = Sprite::initWithFile(filename);
    }

    setupSlice9(getTexture(), capInsets);
    return ret;
}

bool Scale9Sprite::initWithBatchNode(SpriteBatchNode *batchnode, const Rect &rect, const Rect &capInsets)
{
    auto sprite = Sprite::createWithTexture(batchnode->getTexture());
    return init(sprite, rect, false, capInsets);
}

bool Scale9Sprite::updateWithBatchNode(SpriteBatchNode *batchnode, const Rect &originalRect, bool rotated, const Rect &capInsets)
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
    SpriteFrame *spriteframe = SpriteFrame::createWithTexture(sprite->getTexture(),
                                                              CC_RECT_POINTS_TO_PIXELS(textureRect),
                                                              rotated,
                                                              CC_POINT_POINTS_TO_PIXELS(offset),
                                                              CC_SIZE_POINTS_TO_PIXELS(originalSize));
    setSpriteFrame(spriteframe);
    setCapInsets(capInsets);
    return true;
}

Scale9Sprite* Scale9Sprite::resizableSpriteWithCapInsets(const Rect& capInsets) const
{
    // FIXME: there are no test cases for this method
    Scale9Sprite* ret = new (std::nothrow) Scale9Sprite();
    if (ret && ret->init(const_cast<Scale9Sprite*>(this),
                         _rect,
                         _rectRotated,
                         Vec2::ZERO,
                         _originalContentSize,
                         capInsets) )
    {
        ret->autorelease();
        return ret;
    }
    CC_SAFE_DELETE(ret);
    return nullptr;
}

Scale9Sprite::State Scale9Sprite::getState() const
{
    return _brightState;
}

void Scale9Sprite::setState(Scale9Sprite::State state)
{
    if (_brightState != state) {
        _brightState = state;

        GLProgramState *glState = nullptr;
        switch (state)
        {
            case State::NORMAL:
                glState = GLProgramState::getOrCreateWithGLProgramName(GLProgram::SHADER_NAME_POSITION_TEXTURE_COLOR_NO_MVP, getTexture());
                break;
            case State::GRAY:
                glState = GLProgramState::getOrCreateWithGLProgramName(GLProgram::SHADER_NAME_POSITION_GRAYSCALE, getTexture());
            default:
                break;
        }

        setGLProgramState(glState);
        _brightState = state;
    }
}

void Scale9Sprite::setSpriteFrame(SpriteFrame * spriteFrame, const Rect& capInsets)
{
    setSpriteFrame(spriteFrame);
    setCapInsets(capInsets);
}

void Scale9Sprite::setPreferredSize(const Size& preferredSize)
{
    setContentSize(preferredSize);
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
    if (_renderingType == RenderingType::SLICE)
    {
        Rect capInsets(_insetLeft,
                       _insetTop,
                       _originalContentSize.width - _insetRight - _insetLeft,
                       _originalContentSize.height - _insetBottom -_insetTop);
        setCapInsets(capInsets);
    }
}

Size Scale9Sprite::getOriginalSize() const
{
    return _originalContentSize;
}

Size Scale9Sprite::getPreferredSize() const
{
    return getContentSize();
}

float Scale9Sprite::getInsetLeft() const
{
    return _insetLeft;
}

float Scale9Sprite::getInsetTop() const
{
    return _insetTop;
}

float Scale9Sprite::getInsetRight() const
{
    return _insetRight;
}

float Scale9Sprite::getInsetBottom() const
{
    return _insetBottom;
}

void Scale9Sprite::setScale9Enabled(bool enabled)
{
    if (_renderMode == RenderMode::POLYGON) {
        CCLOGWARN("Scale9Sprite::setScale9Enabled() can't be called when using POLYGON render modes");
        return;
    }

    RenderingType type = enabled ? RenderingType::SLICE : RenderingType::SIMPLE;
    setRenderingType(type);

    // only enable strech when scale9 is enabled
    // for backward compatibiliy, since Sprite streches the texture no matter the rendering type
    setStrechEnabled(enabled);
}

bool Scale9Sprite::isScale9Enabled() const
{
    return (_renderingType == RenderingType::SLICE);
}

Sprite* Scale9Sprite::getSprite()
{
    return this;
}

/**
 * @brief Returns a copy of the Scale9Sprite
 */
void Scale9Sprite::copyTo(Scale9Sprite* copy) const
{
    copy->initWithSpriteFrame(getSpriteFrame(), getCapInsets());

    copy->setRenderingType(_renderingType);
    copy->setScale9Enabled(isScale9Enabled());
    copy->_isPatch9 = _isPatch9;
    copy->_brightState = _brightState;

    // these properties should be part of Sprite::clone() (or Node::clone())
    // but cloning is not supported on those nodes
    copy->setContentSize(getContentSize());
    copy->setPosition(getPosition());
    copy->setScale(getScaleX(), getScaleY());
    copy->setRotation(getRotation());
    copy->setRotationSkewX(getRotationSkewX());
    copy->setRotationSkewY(getRotationSkewY());
    copy->setColor(getColor());
    copy->setOpacity(getOpacity());
    copy->_originalContentSize = _originalContentSize;
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
    if (_renderMode == RenderMode::POLYGON) {
        CCLOGWARN("Scale9Sprite::setRenderingType() can't be called when using POLYGON render modes");
        return;
    }
    if (_renderingType != type) {
        _renderingType = type;
        if (_renderingType == RenderingType::SIMPLE) {
            setCenterRectNormalized(Rect(0,0,1,1));
        } else {
            updateCapInset();
        }
    }
}

Scale9Sprite::RenderingType Scale9Sprite::getRenderingType() const
{
    return _renderingType;
}

void Scale9Sprite::resetRender()
{
    // nothing. keeping it to be backwards compatible
}

void Scale9Sprite::setupSlice9(Texture2D* texture, const Rect& capInsets)
{
    if (texture && texture->isContain9PatchInfo()) {
        auto& parsedCapInset = texture->getSpriteFrameCapInset(getSpriteFrame());

        if(!parsedCapInset.equals(Rect::ZERO))
        {
            // adjust texture rect. 1.3f seems to be the magic number
            // to avoid artifacts
            auto rect = getTextureRect();
            rect.origin.x += 1.3f;
            rect.origin.y += 1.3f;
            rect.size.width -= 2.0f;
            rect.size.height -= 2.0f;
            setTextureRect(rect);

            // and after adjusting the texture, set the new cap insets
            _isPatch9 = true;
            setCapInsets(parsedCapInset);
        }
    }

    if (!_isPatch9)
    {
        setCapInsets(capInsets);
    }
}

void Scale9Sprite::setCapInsets(const cocos2d::Rect &insetsCopy)
{
    Rect insets = insetsCopy;

    // When Insets == Zero --> we should use a 1/3 of its untrimmed size
    if (insets.equals(Rect::ZERO)) {
        insets = Rect( _originalContentSize.width / 3.0f,
                      _originalContentSize.height / 3.0f,
                      _originalContentSize.width / 3.0f,
                      _originalContentSize.height / 3.0f);
    }

    // emulate invalid insets. shouldn't be supported, but the original code supported it.
    if (insets.origin.x > _originalContentSize.width)
        insets.origin.x = 0;
    if (insets.origin.y > _originalContentSize.height)
        insets.origin.y = 0;
    if (insets.size.width > _originalContentSize.width)
        insets.size.width = 1;
    if (insets.size.height > _originalContentSize.height)
        insets.size.height = 1;

    _insetLeft = insets.origin.x;
    _insetTop = insets.origin.y;
    _insetRight = _originalContentSize.width - _insetLeft - insets.size.width;
    _insetBottom = _originalContentSize.height - _insetTop - insets.size.height;


    // we have to convert from untrimmed to trimmed
    // Sprite::setCenterRect is using trimmed values (to be compatible with Cocos Creator)
    // Scale9Sprite::setCapInsects uses untrimmed values (which makes more sense)

    // use _rect coordinates. recenter origin to calculate the
    // intersecting rectangle
    // can't use _offsetPosition since it is calculated using bottom-left as origin,
    // and the center rect is calculated using top-left
    insets.origin.x -= (_originalContentSize.width - _rect.size.width) / 2 + _unflippedOffsetPositionFromCenter.x;
    insets.origin.y -= (_originalContentSize.height - _rect.size.height) / 2 - _unflippedOffsetPositionFromCenter.y;

    // intersecting rectangle
    const float x1 = std::max(insets.origin.x, 0.0f);
    const float y1 = std::max(insets.origin.y, 0.0f);
    const float x2 = std::min(insets.origin.x + insets.size.width, 0.0f + _rect.size.width);
    const float y2 = std::min(insets.origin.y + insets.size.height, 0.0f + _rect.size.height);

    // centerRect uses the trimmed frame origin as 0,0.
    // so, recenter inset rect
    insets.setRect(x1,
                   y1,
                   x2 - x1,
                   y2 - y1);

    // Only update center rect while in slice mode.
    if (_renderingType == RenderingType::SLICE && _renderMode != RenderMode::POLYGON)
    {
        setCenterRect(insets);
    }
}

Rect Scale9Sprite::getCapInsets() const
{
    return getCenterRect();
}
