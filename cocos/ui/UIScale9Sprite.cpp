/****************************************************************************
 Copyright (c) 2013-2014 Chukong Technologies Inc.

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

#include "UIScale9Sprite.h"
#include "2d/CCSprite.h"
#include "2d/CCSpriteFrameCache.h"
#include "base/CCVector.h"
#include "base/CCDirector.h"
#include "renderer/CCGLProgram.h"
#include "renderer/ccShaders.h"
#include "platform/CCImage.h"
#include "base/CCNinePatchImageParser.h"


NS_CC_BEGIN
namespace ui {

    Scale9Sprite::Scale9Sprite()
        : _spritesGenerated(false)
        , _spriteFrameRotated(false)
        , _positionsAreDirty(true)
        , _scale9Image(nullptr)
        , _topLeftSprite(nullptr)
        , _topSprite(nullptr)
        , _topRightSprite(nullptr)
        , _leftSprite(nullptr)
        , _centerSprite(nullptr)
        , _rightSprite(nullptr)
        , _bottomLeftSprite(nullptr)
        , _bottomSprite(nullptr)
        , _bottomRightSprite(nullptr)
        , _scale9Enabled(true)
        , _insetLeft(0)
        , _insetTop(0)
        , _insetRight(0)
        , _insetBottom(0)
        ,_flippedX(false)
        ,_flippedY(false)
        ,_isPatch9(false)
        ,_brightState(State::NORMAL)

    {
        this->setAnchorPoint(Vec2(0.5,0.5));
    }

    Scale9Sprite::~Scale9Sprite()
    {
        this->cleanupSlicedSprites();
        CC_SAFE_RELEASE(_scale9Image);
    }

    bool Scale9Sprite::initWithFile(const Rect& capInsets, const std::string& file)
    {
        bool pReturn = this->initWithFile(file, Rect::ZERO, capInsets);
        return pReturn;
    }

    bool Scale9Sprite::initWithFile(const std::string& file)
    {
        bool pReturn = this->initWithFile(file, Rect::ZERO);
        return pReturn;
    }
    bool Scale9Sprite::initWithSpriteFrame(SpriteFrame* spriteFrame,
                                           const Rect& capInsets)
    {
        Texture2D* texture = spriteFrame->getTexture();
        CCASSERT(texture != NULL, "CCTexture must be not nil");
        Sprite *sprite = Sprite::createWithSpriteFrame(spriteFrame);
        CCASSERT(sprite != NULL, "sprite must be not nil");
        bool pReturn = this->init(sprite,
                                  spriteFrame->getRect(),
                                  spriteFrame->isRotated(),
                                  spriteFrame->getOffset(),
                                  spriteFrame->getOriginalSize(),
                                  capInsets);
        return pReturn;
    }
    bool Scale9Sprite::initWithSpriteFrame(SpriteFrame* spriteFrame)
    {
        CCASSERT(spriteFrame != NULL, "Invalid spriteFrame for sprite");
        bool pReturn = this->initWithSpriteFrame(spriteFrame, Rect::ZERO);
        return pReturn;
    }
    bool Scale9Sprite::initWithSpriteFrameName(const std::string& spriteFrameName,
                                               const Rect& capInsets)
    {
        CCASSERT((SpriteFrameCache::getInstance()) != NULL,
                 "SpriteFrameCache::getInstance() must be non-NULL");

        SpriteFrame *frame = SpriteFrameCache::getInstance()->getSpriteFrameByName(spriteFrameName);
        CCASSERT(frame != NULL, "CCSpriteFrame must be non-NULL");

        if (NULL == frame) return false;
        bool pReturn = this->initWithSpriteFrame(frame, capInsets);
        return pReturn;
    }
    bool Scale9Sprite::initWithSpriteFrameName(const std::string& spriteFrameName)
    {
        bool pReturn = this->initWithSpriteFrameName(spriteFrameName, Rect::ZERO);
        return pReturn;
    }

    bool Scale9Sprite::init()
    {
        return this->init(NULL, Rect::ZERO, Rect::ZERO);
    }

    bool Scale9Sprite::init(Sprite* sprite, const Rect& rect, const Rect& capInsets)
    {
        return this->init(sprite, rect, false, capInsets);
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
        if(sprite)
        {
            auto texture = sprite->getTexture();
            auto spriteFrame = sprite->getSpriteFrame();
            Rect actualCapInsets = capInsets;

            if (texture->isContain9PatchInfo())
            {
                auto& parsedCapInset = texture->getSpriteFrameCapInset(spriteFrame);
                if(!parsedCapInset.equals(Rect::ZERO))
                {
                    this->_isPatch9 = true;
                    if(capInsets.equals(Rect::ZERO))
                    {
                        actualCapInsets = parsedCapInset;
                    }

                }
            }
           
            this->updateWithSprite(sprite,
                                   rect,
                                   rotated,
                                   offset,
                                   originalSize,
                                   actualCapInsets);
        }

        return true;
    }

    bool Scale9Sprite::initWithBatchNode(cocos2d::SpriteBatchNode *batchnode,
                                         const cocos2d::Rect &rect,
                                         bool rotated,
                                         const cocos2d::Rect &capInsets)
    {
        Sprite *sprite = Sprite::createWithTexture(batchnode->getTexture());
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
        Sprite *sprite = nullptr;
        sprite = Sprite::create(file);
        bool pReturn = this->init(sprite, rect, capInsets);
        return pReturn;
    }

    bool Scale9Sprite::initWithFile(const std::string& file, const Rect& rect)
    {
        bool pReturn = this->initWithFile(file, rect, Rect::ZERO);
        return pReturn;
    }

    Scale9Sprite* Scale9Sprite::create()
    {
        Scale9Sprite *pReturn = new (std::nothrow) Scale9Sprite();
        if (pReturn && pReturn->init())
        {
            pReturn->autorelease();
            return pReturn;
        }
        CC_SAFE_DELETE(pReturn);
        return NULL;
    }

    Scale9Sprite* Scale9Sprite::create(const std::string& file,
                                       const Rect& rect,
                                       const Rect& capInsets)
    {
        Scale9Sprite* pReturn = new (std::nothrow) Scale9Sprite();
        if ( pReturn && pReturn->initWithFile(file, rect, capInsets) )
        {
            pReturn->autorelease();
            return pReturn;
        }
        CC_SAFE_DELETE(pReturn);
        return NULL;
    }


    Scale9Sprite* Scale9Sprite::create(const std::string& file, const Rect& rect)
    {
        Scale9Sprite* pReturn = new (std::nothrow) Scale9Sprite();
        if ( pReturn && pReturn->initWithFile(file, rect) )
        {
            pReturn->autorelease();
            return pReturn;
        }
        CC_SAFE_DELETE(pReturn);
        return NULL;
    }



    Scale9Sprite* Scale9Sprite::create(const Rect& capInsets,
                                       const std::string& file)
    {
        Scale9Sprite* pReturn = new (std::nothrow) Scale9Sprite();
        if ( pReturn && pReturn->initWithFile(capInsets, file) )
        {
            pReturn->autorelease();
            return pReturn;
        }
        CC_SAFE_DELETE(pReturn);
        return NULL;
    }


    Scale9Sprite* Scale9Sprite::create(const std::string& file)
    {
        Scale9Sprite* pReturn = new (std::nothrow) Scale9Sprite();
        if ( pReturn && pReturn->initWithFile(file) )
        {
            pReturn->autorelease();
            return pReturn;
        }
        CC_SAFE_DELETE(pReturn);
        return NULL;
    }


    Scale9Sprite* Scale9Sprite::createWithSpriteFrame(SpriteFrame* spriteFrame,
                                                      const Rect& capInsets)
    {
        Scale9Sprite* pReturn = new (std::nothrow) Scale9Sprite();
        if ( pReturn && pReturn->initWithSpriteFrame(spriteFrame, capInsets) )
        {
            pReturn->autorelease();
            return pReturn;
        }
        CC_SAFE_DELETE(pReturn);
        return NULL;
    }

    Scale9Sprite* Scale9Sprite::createWithSpriteFrame(SpriteFrame* spriteFrame)
    {
        Scale9Sprite* pReturn = new (std::nothrow) Scale9Sprite();
        if ( pReturn && pReturn->initWithSpriteFrame(spriteFrame) )
        {
            pReturn->autorelease();
            return pReturn;
        }
        CC_SAFE_DELETE(pReturn);
        return NULL;
    }


    Scale9Sprite* Scale9Sprite::createWithSpriteFrameName(const std::string& spriteFrameName,
                                                          const Rect& capInsets)
    {
        Scale9Sprite* pReturn = new (std::nothrow) Scale9Sprite();
        if ( pReturn && pReturn->initWithSpriteFrameName(spriteFrameName, capInsets) )
        {
            pReturn->autorelease();
            return pReturn;
        }
        CC_SAFE_DELETE(pReturn);
        return NULL;
    }

    Scale9Sprite* Scale9Sprite::createWithSpriteFrameName(const std::string& spriteFrameName)
    {
        Scale9Sprite* pReturn = new (std::nothrow) Scale9Sprite();
        if ( pReturn && pReturn->initWithSpriteFrameName(spriteFrameName) )
        {
            pReturn->autorelease();
            return pReturn;
        }
        CC_SAFE_DELETE(pReturn);

        log("Could not allocate Scale9Sprite()");
        return NULL;

    }

    void Scale9Sprite::cleanupSlicedSprites()
    {
        if (_topLeftSprite && _topLeftSprite->isRunning())
        {
            _topLeftSprite->onExit();
        }
        if (_topSprite && _topSprite->isRunning())
        {
            _topSprite->onExit();
        }
        if (_topRightSprite && _topRightSprite->isRunning())
        {
            _topRightSprite->onExit();
        }

        if (_leftSprite && _leftSprite->isRunning())
        {
            _leftSprite->onExit();
        }

        if (_centerSprite && _centerSprite->isRunning())
        {
            _centerSprite->onExit();
        }

        if (_rightSprite && _rightSprite->isRunning())
        {
            _rightSprite->onExit();
        }

        if (_bottomLeftSprite && _bottomLeftSprite->isRunning())
        {
            _bottomLeftSprite->onExit();
        }

        if (_bottomRightSprite && _bottomRightSprite->isRunning())
        {
            _bottomRightSprite->onExit();
        }

        if (_bottomSprite && _bottomSprite->isRunning())
        {
            _bottomSprite->onExit();
        }

        CC_SAFE_RELEASE_NULL(_topLeftSprite);
        CC_SAFE_RELEASE_NULL(_topSprite);
        CC_SAFE_RELEASE_NULL(_topRightSprite);
        CC_SAFE_RELEASE_NULL(_leftSprite);
        CC_SAFE_RELEASE_NULL(_centerSprite);
        CC_SAFE_RELEASE_NULL(_rightSprite);
        CC_SAFE_RELEASE_NULL(_bottomLeftSprite);
        CC_SAFE_RELEASE_NULL(_bottomSprite);
        CC_SAFE_RELEASE_NULL(_bottomRightSprite);
    }


    void Scale9Sprite::setBlendFunc(const BlendFunc &blendFunc)
    {
        _blendFunc = blendFunc;
        applyBlendFunc();
    }
    const BlendFunc &Scale9Sprite::getBlendFunc() const
    {
        return _blendFunc;
    }

    void Scale9Sprite::updateBlendFunc(Texture2D *texture)
    {

        // it is possible to have an untextured sprite
        if (! texture || ! texture->hasPremultipliedAlpha())
        {
            _blendFunc = BlendFunc::ALPHA_NON_PREMULTIPLIED;
            setOpacityModifyRGB(false);
        }
        else
        {
            _blendFunc = BlendFunc::ALPHA_PREMULTIPLIED;
            setOpacityModifyRGB(true);
        }
    }

    void Scale9Sprite::applyBlendFunc()
    {
        if(_scale9Image)
            _scale9Image->setBlendFunc(_blendFunc);
        if(_topLeftSprite)
            _topLeftSprite->setBlendFunc(_blendFunc);
        if(_topSprite)
            _topSprite->setBlendFunc(_blendFunc);
        if(_topRightSprite)
            _topRightSprite->setBlendFunc(_blendFunc);
        if(_leftSprite)
            _leftSprite->setBlendFunc(_blendFunc);
        if(_centerSprite)
            _centerSprite->setBlendFunc(_blendFunc);
        if(_rightSprite)
            _rightSprite->setBlendFunc(_blendFunc);
        if(_bottomLeftSprite)
            _bottomLeftSprite->setBlendFunc(_blendFunc);
        if(_bottomSprite)
            _bottomSprite->setBlendFunc(_blendFunc);
        if(_bottomRightSprite)
            _bottomRightSprite->setBlendFunc(_blendFunc);
    }

    bool Scale9Sprite::updateWithBatchNode(cocos2d::SpriteBatchNode *batchnode,
                                           const cocos2d::Rect &originalRect,
                                           bool rotated,
                                           const cocos2d::Rect &capInsets)
    {
        Sprite *sprite = Sprite::createWithTexture(batchnode->getTexture());
        return this->updateWithSprite(sprite,
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

    static Rect intersectRect(const Rect &first, const Rect &second)
    {
        Rect ret;
        ret.origin.x = std::max(first.origin.x,second.origin.x);
        ret.origin.y = std::max(first.origin.y,second.origin.y);

        float rightRealPoint = std::min(first.origin.x + first.size.width,
                                        second.origin.x + second.size.width);
        float bottomRealPoint = std::min(first.origin.y + first.size.height,
                                         second.origin.y + second.size.height);

        ret.size.width = std::max(rightRealPoint - ret.origin.x, 0.0f);
        ret.size.height = std::max(bottomRealPoint - ret.origin.y, 0.0f);
        return ret;
    }

    bool Scale9Sprite::updateWithSprite(Sprite* sprite,
                                        const Rect& textureRect,
                                        bool rotated,
                                        const Vec2 &offset,
                                        const Size &originalSize,
                                        const Rect& capInsets)
    {
        GLubyte opacity = getOpacity();
        Color3B color = getColor();

        // Release old sprites
        this->cleanupSlicedSprites();
        _protectedChildren.clear();

        updateBlendFunc(sprite?sprite->getTexture():nullptr);

        if(nullptr != sprite)
        {
            if (nullptr == sprite->getSpriteFrame())
            {
                return false;
            }

            if (nullptr == _scale9Image)
            {
                _scale9Image = sprite;
                _scale9Image->retain();
            }
            else
            {
                _scale9Image->setSpriteFrame(sprite->getSpriteFrame());
            }
        }

        if (!_scale9Image)
        {
            return false;
        }

        SpriteFrame *spriteFrame = _scale9Image->getSpriteFrame();

        if (!spriteFrame)
        {
            return false;
        }

        Rect rect(textureRect);
        Size size(originalSize);
        
        _capInsets = capInsets;

        // If there is no given rect
        if ( rect.equals(Rect::ZERO) )
        {
            // Get the texture size as original
            Size textureSize = _scale9Image->getTexture()->getContentSize();

            rect = Rect(0, 0, textureSize.width, textureSize.height);
        }

        if( size.equals(Size::ZERO) )
        {
            size = rect.size;
        }

        // Set the given rect's size as original size
        _spriteRect = rect;
        _offset = offset;
        _spriteFrameRotated = rotated;
        _originalSize = size;
        _preferredSize = size;

        _capInsetsInternal = capInsets;

        if (_scale9Enabled)
        {
            this->createSlicedSprites();
        }

        applyBlendFunc();
        this->setState(_brightState);
        if(this->_isPatch9)
        {
            size.width = size.width - 2;
            size.height = size.height - 2;
        }
        this->setContentSize(size);

        if (_spritesGenerated)
        {
            // Restore color and opacity
            this->setOpacity(opacity);
            this->setColor(color);
        }
        _spritesGenerated = true;

        return true;
    }

    void Scale9Sprite::createSlicedSprites()
    {
        float width = _originalSize.width;
        float height = _originalSize.height;

        Vec2 offsetPosition(floor(_offset.x + (_originalSize.width - _spriteRect.size.width) / 2),
                            floor(_offset.y + (_originalSize.height - _spriteRect.size.height) / 2));

        // If there is no specified center region
        if ( _capInsetsInternal.equals(Rect::ZERO) )
        {
            // log("... cap insets not specified : using default cap insets ...");
            _capInsetsInternal = Rect(width /3, height /3, width /3, height /3);
        }

        Rect originalRect=_spriteRect;
        if(_spriteFrameRotated)
            originalRect = Rect(_spriteRect.origin.x - offsetPosition.y,
                                _spriteRect.origin.y - offsetPosition.x,
                                _originalSize.width, _originalSize.height);
        else
            originalRect = Rect(_spriteRect.origin.x - offsetPosition.x,
                                _spriteRect.origin.y - offsetPosition.y,
                                _originalSize.width, _originalSize.height);

        float leftWidth = _capInsetsInternal.origin.x;
        float centerWidth = _capInsetsInternal.size.width;
        float rightWidth = originalRect.size.width - (leftWidth + centerWidth);

        float topHeight = _capInsetsInternal.origin.y;
        float centerHeight = _capInsetsInternal.size.height;
        float bottomHeight = originalRect.size.height - (topHeight + centerHeight);

        // calculate rects

        // ... top row
        float x = 0.0;
        float y = 0.0;
        //why do we need pixelRect?
        Rect pixelRect = Rect(offsetPosition.x, offsetPosition.y,
                              _spriteRect.size.width, _spriteRect.size.height);

        // top left
        Rect leftTopBoundsOriginal = Rect(x, y, leftWidth, topHeight);
        Rect leftTopBounds = leftTopBoundsOriginal;

        // top center
        x += leftWidth;
        Rect centerTopBounds = Rect(x, y, centerWidth, topHeight);

        // top right
        x += centerWidth;
        Rect rightTopBounds = Rect(x, y, rightWidth, topHeight);

        // ... center row
        x = 0.0;
        y = 0.0;
        y += topHeight;

        // center left
        Rect leftCenterBounds = Rect(x, y, leftWidth, centerHeight);

        // center center
        x += leftWidth;
        Rect centerBoundsOriginal = Rect(x, y, centerWidth, centerHeight);
        Rect centerBounds = centerBoundsOriginal;

        // center right
        x += centerWidth;
        Rect rightCenterBounds = Rect(x, y, rightWidth, centerHeight);

        // ... bottom row
        x = 0.0;
        y = 0.0;
        y += topHeight;
        y += centerHeight;

        // bottom left
        Rect leftBottomBounds = Rect(x, y, leftWidth, bottomHeight);

        // bottom center
        x += leftWidth;
        Rect centerBottomBounds = Rect(x, y, centerWidth, bottomHeight);

        // bottom right
        x += centerWidth;
        Rect rightBottomBoundsOriginal = Rect(x, y, rightWidth, bottomHeight);
        Rect rightBottomBounds = rightBottomBoundsOriginal;

        if((_capInsetsInternal.origin.x + _capInsetsInternal.size.width) <= _originalSize.width
           || (_capInsetsInternal.origin.y + _capInsetsInternal.size.height) <= _originalSize.height)
            //in general case it is error but for legacy support we will check it
        {
            leftTopBounds = intersectRect(leftTopBounds, pixelRect);
            centerTopBounds = intersectRect(centerTopBounds, pixelRect);
            rightTopBounds = intersectRect(rightTopBounds, pixelRect);
            leftCenterBounds = intersectRect(leftCenterBounds, pixelRect);
            centerBounds = intersectRect(centerBounds, pixelRect);
            rightCenterBounds = intersectRect(rightCenterBounds, pixelRect);
            leftBottomBounds = intersectRect(leftBottomBounds, pixelRect);
            centerBottomBounds = intersectRect(centerBottomBounds, pixelRect);
            rightBottomBounds = intersectRect(rightBottomBounds, pixelRect);
        }
        else
            //it is error but for legacy turn off clip system
            CCLOG("Scale9Sprite capInsetsInternal > originalSize");

        Rect rotatedLeftTopBoundsOriginal = leftTopBoundsOriginal;
        Rect rotatedCenterBoundsOriginal = centerBoundsOriginal;
        Rect rotatedRightBottomBoundsOriginal = rightBottomBoundsOriginal;

        Rect rotatedCenterBounds = centerBounds;
        Rect rotatedRightBottomBounds = rightBottomBounds;
        Rect rotatedLeftBottomBounds = leftBottomBounds;
        Rect rotatedRightTopBounds = rightTopBounds;
        Rect rotatedLeftTopBounds = leftTopBounds;
        Rect rotatedRightCenterBounds = rightCenterBounds;
        Rect rotatedLeftCenterBounds = leftCenterBounds;
        Rect rotatedCenterBottomBounds = centerBottomBounds;
        Rect rotatedCenterTopBounds = centerTopBounds;

        if (!_spriteFrameRotated)
        {

            AffineTransform t = AffineTransform::IDENTITY;
            t = AffineTransformTranslate(t, originalRect.origin.x, originalRect.origin.y);

            rotatedLeftTopBoundsOriginal = RectApplyAffineTransform(rotatedLeftTopBoundsOriginal, t);
            rotatedCenterBoundsOriginal = RectApplyAffineTransform(rotatedCenterBoundsOriginal, t);
            rotatedRightBottomBoundsOriginal = RectApplyAffineTransform(rotatedRightBottomBoundsOriginal, t);

            rotatedCenterBounds = RectApplyAffineTransform(rotatedCenterBounds, t);
            rotatedRightBottomBounds = RectApplyAffineTransform(rotatedRightBottomBounds, t);
            rotatedLeftBottomBounds = RectApplyAffineTransform(rotatedLeftBottomBounds, t);
            rotatedRightTopBounds = RectApplyAffineTransform(rotatedRightTopBounds, t);
            rotatedLeftTopBounds = RectApplyAffineTransform(rotatedLeftTopBounds, t);
            rotatedRightCenterBounds = RectApplyAffineTransform(rotatedRightCenterBounds, t);
            rotatedLeftCenterBounds = RectApplyAffineTransform(rotatedLeftCenterBounds, t);
            rotatedCenterBottomBounds = RectApplyAffineTransform(rotatedCenterBottomBounds, t);
            rotatedCenterTopBounds = RectApplyAffineTransform(rotatedCenterTopBounds, t);


        }
        else
        {
            // set up transformation of coordinates
            // to handle the case where the sprite is stored rotated
            // in the spritesheet
            // log("rotated");

            AffineTransform t = AffineTransform::IDENTITY;

            t = AffineTransformTranslate(t, originalRect.size.height+originalRect.origin.x, originalRect.origin.y);
            t = AffineTransformRotate(t, 1.57079633f);

            leftTopBoundsOriginal = RectApplyAffineTransform(leftTopBoundsOriginal, t);
            centerBoundsOriginal = RectApplyAffineTransform(centerBoundsOriginal, t);
            rightBottomBoundsOriginal = RectApplyAffineTransform(rightBottomBoundsOriginal, t);

            centerBounds = RectApplyAffineTransform(centerBounds, t);
            rightBottomBounds = RectApplyAffineTransform(rightBottomBounds, t);
            leftBottomBounds = RectApplyAffineTransform(leftBottomBounds, t);
            rightTopBounds = RectApplyAffineTransform(rightTopBounds, t);
            leftTopBounds = RectApplyAffineTransform(leftTopBounds, t);
            rightCenterBounds = RectApplyAffineTransform(rightCenterBounds, t);
            leftCenterBounds = RectApplyAffineTransform(leftCenterBounds, t);
            centerBottomBounds = RectApplyAffineTransform(centerBottomBounds, t);
            centerTopBounds = RectApplyAffineTransform(centerTopBounds, t);

            rotatedLeftTopBoundsOriginal.origin = leftTopBoundsOriginal.origin;
            rotatedCenterBoundsOriginal.origin = centerBoundsOriginal.origin;
            rotatedRightBottomBoundsOriginal.origin = rightBottomBoundsOriginal.origin;

            rotatedCenterBounds.origin = centerBounds.origin;
            rotatedRightBottomBounds.origin = rightBottomBounds.origin;
            rotatedLeftBottomBounds.origin = leftBottomBounds.origin;
            rotatedRightTopBounds.origin = rightTopBounds.origin;
            rotatedLeftTopBounds.origin = leftTopBounds.origin;
            rotatedRightCenterBounds.origin = rightCenterBounds.origin;
            rotatedLeftCenterBounds.origin = leftCenterBounds.origin;
            rotatedCenterBottomBounds.origin = centerBottomBounds.origin;
            rotatedCenterTopBounds.origin = centerTopBounds.origin;


        }

        _topLeftSize = rotatedLeftTopBoundsOriginal.size;
        _centerSize = rotatedCenterBoundsOriginal.size;
        _bottomRightSize = rotatedRightBottomBoundsOriginal.size;
        if(_isPatch9)
        {
            _topLeftSize.width = _topLeftSize.width - 1;
            _topLeftSize.height = _topLeftSize.height - 1;
            _bottomRightSize.width = _bottomRightSize.width - 1;
            _bottomRightSize.height = _bottomRightSize.height - 1;
        }

        if(_spriteFrameRotated)
        {
            float offsetX = (rotatedCenterBounds.origin.x + rotatedCenterBounds.size.height/2)
                - (rotatedCenterBoundsOriginal.origin.x + rotatedCenterBoundsOriginal.size.height/2);
            float offsetY = (rotatedCenterBoundsOriginal.origin.y + rotatedCenterBoundsOriginal.size.width/2)
                - (rotatedCenterBounds.origin.y + rotatedCenterBounds.size.width/2);
            _centerOffset.x = -offsetY;
            _centerOffset.y = offsetX;
        }
        else
        {
            float offsetX = (rotatedCenterBounds.origin.x + rotatedCenterBounds.size.width/2)
                - (rotatedCenterBoundsOriginal.origin.x + rotatedCenterBoundsOriginal.size.width/2);
            float offsetY = (rotatedCenterBoundsOriginal.origin.y + rotatedCenterBoundsOriginal.size.height/2)
                - (rotatedCenterBounds.origin.y + rotatedCenterBounds.size.height/2);
            _centerOffset.x = offsetX;
            _centerOffset.y = offsetY;
        }

        //shrink the image size when it is 9-patch
        if(_isPatch9)
        {
            float offset = 1.0f;
            //Top left
            if(!_spriteFrameRotated)
            {
                rotatedLeftTopBounds.origin.x+=offset;
                rotatedLeftTopBounds.origin.y+=offset;
                rotatedLeftTopBounds.size.width-=offset;
                rotatedLeftTopBounds.size.height-=offset;
                //Center left
                rotatedLeftCenterBounds.origin.x+=offset;
                rotatedLeftCenterBounds.size.width-=offset;
                //Bottom left
                rotatedLeftBottomBounds.origin.x+=offset;
                rotatedLeftBottomBounds.size.width-=offset;
                rotatedLeftBottomBounds.size.height-=offset;
                //Top center
                rotatedCenterTopBounds.size.height-=offset;
                rotatedCenterTopBounds.origin.y+=offset;
                //Bottom center
                rotatedCenterBottomBounds.size.height-=offset;
                //Top right
                rotatedRightTopBounds.size.width-=offset;
                rotatedRightTopBounds.size.height-=offset;
                rotatedRightTopBounds.origin.y+=offset;
                //Center right
                rotatedRightCenterBounds.size.width-=offset;
                //Bottom right
                rotatedRightBottomBounds.size.width-=offset;
                rotatedRightBottomBounds.size.height-=offset;
            }
            else
            {
                //Top left
                rotatedLeftTopBounds.size.width-=offset;
                rotatedLeftTopBounds.size.height-=offset;
                rotatedLeftTopBounds.origin.y+=offset;
                //Center left
                rotatedLeftCenterBounds.origin.y+=offset;
                rotatedLeftCenterBounds.size.width-=offset;
                //Bottom left
                rotatedLeftBottomBounds.origin.x+=offset;
                rotatedLeftBottomBounds.origin.y+=offset;
                rotatedLeftBottomBounds.size.width-=offset;
                rotatedLeftBottomBounds.size.height-=offset;
                //Top center
                rotatedCenterTopBounds.size.height-=offset;
                //Bottom center
                rotatedCenterBottomBounds.size.height-=offset;
                rotatedCenterBottomBounds.origin.x+=offset;
                //Top right
                rotatedRightTopBounds.size.width-=offset;
                rotatedRightTopBounds.size.height-=offset;
                //Center right
                rotatedRightCenterBounds.size.width-=offset;
                //Bottom right
                rotatedRightBottomBounds.size.width-=offset;
                rotatedRightBottomBounds.size.height-=offset;
                rotatedRightBottomBounds.origin.x+=offset;
            }
        }

        // Centre
        if(rotatedCenterBounds.size.width > 0 && rotatedCenterBounds.size.height > 0 )
        {
            _centerSprite = Sprite::createWithTexture(_scale9Image->getTexture(),
                                                      rotatedCenterBounds,
                                                      _spriteFrameRotated);
            _centerSprite->retain();
            this->addProtectedChild(_centerSprite);
        }

        // Top
        if(rotatedCenterTopBounds.size.width > 0 && rotatedCenterTopBounds.size.height > 0 )
        {
            _topSprite = Sprite::createWithTexture(_scale9Image->getTexture(),
                                                   rotatedCenterTopBounds,
                                                   _spriteFrameRotated);
            _topSprite->retain();
            this->addProtectedChild(_topSprite);
        }

        // Bottom
        if(rotatedCenterBottomBounds.size.width > 0 && rotatedCenterBottomBounds.size.height > 0 )
        {
            _bottomSprite = Sprite::createWithTexture(_scale9Image->getTexture(),
                                                      rotatedCenterBottomBounds,
                                                      _spriteFrameRotated);
            _bottomSprite->retain();
            this->addProtectedChild(_bottomSprite);
        }

        // Left
        if(rotatedLeftCenterBounds.size.width > 0 && rotatedLeftCenterBounds.size.height > 0 )
        {
            _leftSprite = Sprite::createWithTexture(_scale9Image->getTexture(),
                                                    rotatedLeftCenterBounds,
                                                    _spriteFrameRotated);
            _leftSprite->retain();
            this->addProtectedChild(_leftSprite);
        }

        // Right
        if(rotatedRightCenterBounds.size.width > 0 && rotatedRightCenterBounds.size.height > 0 )
        {
            _rightSprite = Sprite::createWithTexture(_scale9Image->getTexture(),
                                                     rotatedRightCenterBounds,
                                                     _spriteFrameRotated);
            _rightSprite->retain();
            this->addProtectedChild(_rightSprite);
        }

        // Top left
        if(rotatedLeftTopBounds.size.width > 0 && rotatedLeftTopBounds.size.height > 0 )
        {
            _topLeftSprite = Sprite::createWithTexture(_scale9Image->getTexture(),
                                                       rotatedLeftTopBounds,
                                                       _spriteFrameRotated);
            _topLeftSprite->retain();
            this->addProtectedChild(_topLeftSprite);
        }

        // Top right
        if(rotatedRightTopBounds.size.width > 0 && rotatedRightTopBounds.size.height > 0 )
        {
            _topRightSprite = Sprite::createWithTexture(_scale9Image->getTexture(),
                                                        rotatedRightTopBounds,
                                                        _spriteFrameRotated);
            _topRightSprite->retain();
            this->addProtectedChild(_topRightSprite);
        }

        // Bottom left
        if(rotatedLeftBottomBounds.size.width > 0 && rotatedLeftBottomBounds.size.height > 0 )
        {
            _bottomLeftSprite = Sprite::createWithTexture(_scale9Image->getTexture(),
                                                          rotatedLeftBottomBounds,
                                                          _spriteFrameRotated);
            _bottomLeftSprite->retain();
            this->addProtectedChild(_bottomLeftSprite);
        }

        // Bottom right
        if(rotatedRightBottomBounds.size.width > 0 && rotatedRightBottomBounds.size.height > 0 )
        {
            _bottomRightSprite = Sprite::createWithTexture(_scale9Image->getTexture(),
                                                           rotatedRightBottomBounds,
                                                           _spriteFrameRotated);
            _bottomRightSprite->retain();
            this->addProtectedChild(_bottomRightSprite);
        }
    }

    void Scale9Sprite::setContentSize(const Size &size)
    {
        Node::setContentSize(size);
        this->_positionsAreDirty = true;
    }

    void Scale9Sprite::updatePositions()
    {
        Size size = this->_contentSize;

        float sizableWidth = size.width - _topLeftSize.width - _bottomRightSize.width;
        float sizableHeight = size.height - _topLeftSize.height - _bottomRightSize.height;

        float horizontalScale = sizableWidth/_centerSize.width;
        float verticalScale = sizableHeight/_centerSize.height;

        if(_centerSprite)
        {
            _centerSprite->setScaleX(horizontalScale);
            _centerSprite->setScaleY(verticalScale);
        }

        float rescaledWidth = _centerSize.width * horizontalScale;
        float rescaledHeight = _centerSize.height * verticalScale;

        float leftWidth = _topLeftSize.width;
        float bottomHeight = _bottomRightSize.height;

        Vec2 centerOffset(_centerOffset.x * horizontalScale, _centerOffset.y * verticalScale);

        // Position corners
        if(_bottomLeftSprite)
        {
            _bottomLeftSprite->setAnchorPoint(Vec2(1,1));
            _bottomLeftSprite->setPosition(leftWidth,bottomHeight);
        }
        if(_bottomRightSprite)
        {
            _bottomRightSprite->setAnchorPoint(Vec2(0,1));
            _bottomRightSprite->setPosition(leftWidth+rescaledWidth,bottomHeight);
        }
        if(_topLeftSprite)
        {
            _topLeftSprite->setAnchorPoint(Vec2(1,0));
            _topLeftSprite->setPosition(leftWidth, bottomHeight+rescaledHeight);
        }
        if(_topRightSprite)
        {
            _topRightSprite->setAnchorPoint(Vec2(0,0));
            _topRightSprite->setPosition(leftWidth+rescaledWidth, bottomHeight+rescaledHeight);
        }

        // Scale and position borders
        if(_leftSprite)
        {
            _leftSprite->setAnchorPoint(Vec2(1,0.5));
            _leftSprite->setPosition(leftWidth, bottomHeight+rescaledHeight/2 + centerOffset.y);
            _leftSprite->setScaleY(verticalScale);
        }
        if(_rightSprite)
        {
            _rightSprite->setAnchorPoint(Vec2(0,0.5));
            _rightSprite->setPosition(leftWidth+rescaledWidth,bottomHeight+rescaledHeight/2 + centerOffset.y);
            _rightSprite->setScaleY(verticalScale);
        }
        if(_topSprite)
        {
            _topSprite->setAnchorPoint(Vec2(0.5,0));
            _topSprite->setPosition(leftWidth+rescaledWidth/2 + centerOffset.x,bottomHeight+rescaledHeight);
            _topSprite->setScaleX(horizontalScale);
        }
        if(_bottomSprite)
        {
            _bottomSprite->setAnchorPoint(Vec2(0.5,1));
            _bottomSprite->setPosition(leftWidth+rescaledWidth/2 + centerOffset.x,bottomHeight);
            _bottomSprite->setScaleX(horizontalScale);
        }
        // Position centre
        if(_centerSprite)
        {
            _centerSprite->setAnchorPoint(Vec2(0.5,0.5));
            _centerSprite->setPosition(leftWidth+rescaledWidth/2 + centerOffset.x,
                                       bottomHeight+rescaledHeight/2 + centerOffset.y);
            _centerSprite->setScaleX(horizontalScale);
            _centerSprite->setScaleY(verticalScale);
        }
    }



    Scale9Sprite* Scale9Sprite::resizableSpriteWithCapInsets(const Rect& capInsets) const
    {
        Scale9Sprite* pReturn = new (std::nothrow) Scale9Sprite();
        if ( pReturn && pReturn->init(_scale9Image,
                                      _spriteRect,
                                      _spriteFrameRotated,
                                      _offset,
                                      _originalSize,
                                      _capInsets) )
        {
            pReturn->autorelease();
            return pReturn;
        }
        CC_SAFE_DELETE(pReturn);
        return NULL;
    }
    
    Scale9Sprite::State Scale9Sprite::getState()const
    {
        return _brightState;
    }

    void Scale9Sprite::setState(cocos2d::ui::Scale9Sprite::State state)
    {
        GLProgramState *glState = nullptr;
        switch (state)
        {
        case State::NORMAL:
        {
            glState = GLProgramState::getOrCreateWithGLProgramName(GLProgram::SHADER_NAME_POSITION_TEXTURE_COLOR_NO_MVP);
        }
        break;
        case State::GRAY:
        {
            glState = GLProgramState::getOrCreateWithGLProgramName(GLProgram::SHADER_NAME_POSITION_GRAYSCALE);
        }
        default:
            break;
        }
        
        if (nullptr != _scale9Image)
        {
            _scale9Image->setGLProgramState(glState);
        }

        if (_scale9Enabled)
        {
            for (auto& sp : _protectedChildren)
            {
                sp->setGLProgramState(glState);
            }
        }
        _brightState = state;
    }

/** sets the opacity.
    @warning If the texture has premultiplied alpha then, the R, G and B channels will be modifed.
    Values goes from 0 to 255, where 255 means fully opaque.
*/



    void Scale9Sprite::updateCapInset()
    {
        Rect insets;
        if (this->_insetLeft == 0 && this->_insetTop == 0 && this->_insetRight == 0 && this->_insetBottom == 0)
        {
            insets = Rect::ZERO;
        }
        else
        {
            insets = Rect(_insetLeft,
                          _insetTop,
                          _originalSize.width-_insetLeft-_insetRight,
                          _originalSize.height-_insetTop-_insetBottom);
        }
        this->setCapInsets(insets);
    }


    void Scale9Sprite::setSpriteFrame(SpriteFrame * spriteFrame, const Rect& capInsets)
    {
        Sprite * sprite = Sprite::createWithTexture(spriteFrame->getTexture());
        this->updateWithSprite(sprite,
                               spriteFrame->getRect(),
                               spriteFrame->isRotated(),
                               spriteFrame->getOffset(),
                               spriteFrame->getOriginalSize(),
                               capInsets);

        // Reset insets
        this->_insetLeft = capInsets.origin.x;
        this->_insetTop = capInsets.origin.y;
        this->_insetRight = _originalSize.width - _insetLeft - capInsets.size.width;
        this->_insetBottom = _originalSize.height - _insetTop - capInsets.size.height;
    }

    void Scale9Sprite::setPreferredSize(const Size& preferredSize)
    {
        this->setContentSize(preferredSize);
        this->_preferredSize = preferredSize;
    }


    void Scale9Sprite::setCapInsets(const Rect& capInsets)
    {
        Size contentSize = this->_contentSize;
        this->updateWithSprite(this->_scale9Image,
                               _spriteRect,
                               _spriteFrameRotated,
                               _offset,
                               _originalSize,
                               capInsets);
        this->_insetLeft = capInsets.origin.x;
        this->_insetTop = capInsets.origin.y;
        this->_insetRight = _originalSize.width - _insetLeft - capInsets.size.width;
        this->_insetBottom = _originalSize.height - _insetTop - capInsets.size.height;
        this->setContentSize(contentSize);
    }


    void Scale9Sprite::setInsetLeft(float insetLeft)
    {
        this->_insetLeft = insetLeft;
        this->updateCapInset();
    }

    void Scale9Sprite::setInsetTop(float insetTop)
    {
        this->_insetTop = insetTop;
        this->updateCapInset();
    }

    void Scale9Sprite::setInsetRight(float insetRight)
    {
        this->_insetRight = insetRight;
        this->updateCapInset();
    }

    void Scale9Sprite::setInsetBottom(float insetBottom)
    {
        this->_insetBottom = insetBottom;
        this->updateCapInset();
    }

    void Scale9Sprite::visit(Renderer *renderer, const Mat4 &parentTransform, uint32_t parentFlags)
    {

        // quick return if not visible. children won't be drawn.
        if (!_visible)
        {
            return;
        }

        uint32_t flags = processParentFlags(parentTransform, parentFlags);

        // IMPORTANT:
        // To ease the migration to v3.0, we still support the Mat4 stack,
        // but it is deprecated and your code should not rely on it
        Director* director = Director::getInstance();
        CCASSERT(nullptr != director, "Director is null when setting matrix stack");
        director->pushMatrix(MATRIX_STACK_TYPE::MATRIX_STACK_MODELVIEW);
        director->loadMatrix(MATRIX_STACK_TYPE::MATRIX_STACK_MODELVIEW, _modelViewTransform);

        int i = 0;      // used by _children
        int j = 0;      // used by _protectedChildren

        sortAllChildren();
        sortAllProtectedChildren();

        //
        // draw children and protectedChildren zOrder < 0
        //
        for( ; i < _children.size(); i++ )
        {
            auto node = _children.at(i);

            if ( node && node->getLocalZOrder() < 0 )
                node->visit(renderer, _modelViewTransform, flags);
            else
                break;
        }

        if (_scale9Enabled)
        {
            for( ; j < _protectedChildren.size(); j++ )
            {
                auto node = _protectedChildren.at(j);

                if ( node && node->getLocalZOrder() < 0 )
                    node->visit(renderer, _modelViewTransform, flags);
                else
                    break;
            }
        }
        else
        {
            if (_scale9Image && _scale9Image->getLocalZOrder() < 0 )
            {
                _scale9Image->visit(renderer, _modelViewTransform, flags);
            }
        }

        //
        // draw self
        //
        if (isVisitableByVisitingCamera())
            this->draw(renderer, _modelViewTransform, flags);

        //
        // draw children and protectedChildren zOrder >= 0
        //
        if (_scale9Enabled)
        {
            for(auto it=_protectedChildren.cbegin()+j; it != _protectedChildren.cend(); ++it)
                (*it)->visit(renderer, _modelViewTransform, flags);
        }
        else
        {
            if (_scale9Image && _scale9Image->getLocalZOrder() >= 0 )
            {
                _scale9Image->visit(renderer, _modelViewTransform, flags);
            }
        }


        for(auto it=_children.cbegin()+i; it != _children.cend(); ++it)
            (*it)->visit(renderer, _modelViewTransform, flags);

        // FIX ME: Why need to set _orderOfArrival to 0??
        // Please refer to https://github.com/cocos2d/cocos2d-x/pull/6920
        // setOrderOfArrival(0);

        director->popMatrix(MATRIX_STACK_TYPE::MATRIX_STACK_MODELVIEW);

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
        return _capInsets;
    }


    float Scale9Sprite::getInsetLeft()const
    {
        return this->_insetLeft;
    }

    float Scale9Sprite::getInsetTop()const
    {
        return this->_insetTop;
    }

    float Scale9Sprite::getInsetRight()const
    {
        return this->_insetRight;
    }

    float Scale9Sprite::getInsetBottom()const
    {
        return this->_insetBottom;
    }

    void Scale9Sprite::setScale9Enabled(bool enabled)
    {
        if (_scale9Enabled == enabled)
        {
            return;
        }
        _scale9Enabled = enabled;

        this->cleanupSlicedSprites();
        _protectedChildren.clear();

        //we must invalide the transform when toggling scale9enabled
        _transformUpdated = _transformDirty = _inverseDirty = true;

        if (_scale9Enabled)
        {
            if (_scale9Image)
            {
                this->updateWithSprite(this->_scale9Image,
                                       _spriteRect,
                                       _spriteFrameRotated,
                                       _offset,
                                       _originalSize,
                                       _capInsets);
            }
        }
        _positionsAreDirty = true;
    }

    bool Scale9Sprite::isScale9Enabled() const
    {
        return _scale9Enabled;
    }

    void Scale9Sprite::addProtectedChild(cocos2d::Node *child)
    {
        _reorderProtectedChildDirty = true;
        _protectedChildren.pushBack(child);
    }

    void Scale9Sprite::sortAllProtectedChildren()
    {
        if(this->_positionsAreDirty)
        {
            this->updatePositions();
            this->adjustScale9ImagePosition();
            this->_positionsAreDirty = false;
        }
        if( _reorderProtectedChildDirty )
        {
            std::sort( std::begin(_protectedChildren),
                       std::end(_protectedChildren),
                       nodeComparisonLess );
            _reorderProtectedChildDirty = false;
        }
    }

    void Scale9Sprite::adjustScale9ImagePosition()
    {
        if (_scale9Image)
        {
            _scale9Image->setPosition(_contentSize.width * _scale9Image->getAnchorPoint().x,
                                      _contentSize.height * _scale9Image->getAnchorPoint().y);
        }
    }

    void Scale9Sprite::setAnchorPoint(const cocos2d::Vec2 &position)
    {
        Node::setAnchorPoint(position);
        if (!_scale9Enabled)
        {
            if (_scale9Image)
            {
                _scale9Image->setAnchorPoint(position);
                _positionsAreDirty = true;
            }
        }
    }

    void Scale9Sprite::cleanup()
    {
#if CC_ENABLE_SCRIPT_BINDING
        if (_scriptType == kScriptTypeJavascript)
        {
            if (ScriptEngineManager::sendNodeEventToJSExtended(this, kNodeOnCleanup))
                return;
        }
#endif // #if CC_ENABLE_SCRIPT_BINDING
        
        Node::cleanup();
        // timers
        for( const auto &child: _protectedChildren)
            child->cleanup();
    }

    void Scale9Sprite::onEnter()
    {
#if CC_ENABLE_SCRIPT_BINDING
        if (_scriptType == kScriptTypeJavascript)
        {
            if (ScriptEngineManager::sendNodeEventToJSExtended(this, kNodeOnEnter))
                return;
        }
#endif
        Node::onEnter();
        for( const auto &child: _protectedChildren)
            child->onEnter();
    }

    void Scale9Sprite::onExit()
    {
#if CC_ENABLE_SCRIPT_BINDING
        if (_scriptType == kScriptTypeJavascript)
        {
            if (ScriptEngineManager::sendNodeEventToJSExtended(this, kNodeOnExit))
                return;
        }
#endif
        
        Node::onExit();
        for( const auto &child: _protectedChildren)
            child->onExit();
    }

    void Scale9Sprite::onEnterTransitionDidFinish()
    {
#if CC_ENABLE_SCRIPT_BINDING
        if (_scriptType == kScriptTypeJavascript)
        {
            if (ScriptEngineManager::sendNodeEventToJSExtended(this, kNodeOnEnterTransitionDidFinish))
                return;
        }
#endif
        
        Node::onEnterTransitionDidFinish();
        for( const auto &child: _protectedChildren)
            child->onEnterTransitionDidFinish();
    }

    void Scale9Sprite::onExitTransitionDidStart()
    {
#if CC_ENABLE_SCRIPT_BINDING
        if (_scriptType == kScriptTypeJavascript)
        {
            if (ScriptEngineManager::sendNodeEventToJSExtended(this, kNodeOnExitTransitionDidStart))
                return;
        }
#endif
        
        Node::onExitTransitionDidStart();
        for( const auto &child: _protectedChildren)
            child->onExitTransitionDidStart();
    }

    void Scale9Sprite::updateDisplayedColor(const cocos2d::Color3B &parentColor)
    {
        _displayedColor.r = _realColor.r * parentColor.r/255.0;
        _displayedColor.g = _realColor.g * parentColor.g/255.0;
        _displayedColor.b = _realColor.b * parentColor.b/255.0;
        updateColor();

        if (_scale9Image)
        {
            _scale9Image->updateDisplayedColor(_displayedColor);
        }

        for(const auto &child : _protectedChildren)
        {
            child->updateDisplayedColor(_displayedColor);
        }

        if (_cascadeColorEnabled)
        {
            for(const auto &child : _children)
            {
                child->updateDisplayedColor(_displayedColor);
            }
        }
    }

    void Scale9Sprite::updateDisplayedOpacity(GLubyte parentOpacity)
    {
        _displayedOpacity = _realOpacity * parentOpacity/255.0;
        updateColor();

        if (_scale9Image)
        {
            _scale9Image->updateDisplayedOpacity(_displayedOpacity);
        }

        for(auto child : _protectedChildren)
        {
            child->updateDisplayedOpacity(_displayedOpacity);
        }

        if (_cascadeOpacityEnabled)
        {
            for(auto child : _children)
            {
                child->updateDisplayedOpacity(_displayedOpacity);
            }
        }
    }

    void Scale9Sprite::disableCascadeColor()
    {
        for(auto child : _children)
        {
            child->updateDisplayedColor(Color3B::WHITE);
        }
        for(auto child : _protectedChildren)
        {
            child->updateDisplayedColor(Color3B::WHITE);
        }
        if (_scale9Image)
        {
            _scale9Image->updateDisplayedColor(Color3B::WHITE);
        }
    }

    void Scale9Sprite::disableCascadeOpacity()
    {
        _displayedOpacity = _realOpacity;

        for(auto child : _children){
            child->updateDisplayedOpacity(255);
        }

        for(auto child : _protectedChildren){
            child->updateDisplayedOpacity(255);
        }
    }

    Sprite* Scale9Sprite::getSprite()const
    {
        return _scale9Image;
    }

    void Scale9Sprite::setFlippedX(bool flippedX)
    {

        float realScale = this->getScaleX();
        _flippedX = flippedX;
        this->setScaleX(realScale);
    }

    void Scale9Sprite::setFlippedY(bool flippedY)
    {
        float realScale = this->getScaleY();
        _flippedY = flippedY;
        this->setScaleY(realScale);
    }

    bool Scale9Sprite::isFlippedX()const
    {
        return _flippedX;
    }

    bool Scale9Sprite::isFlippedY()const
    {
        return _flippedY;
    }

    void Scale9Sprite::setScaleX(float scaleX)
    {
        if (_flippedX) {
            scaleX = scaleX * -1;
        }
        Node::setScaleX(scaleX);
    }

    void Scale9Sprite::setScaleY(float scaleY)
    {
        if (_flippedY) {
            scaleY = scaleY * -1;
        }
        Node::setScaleY(scaleY);
    }

    void Scale9Sprite::setScale(float scale)
    {
        this->setScaleX(scale);
        this->setScaleY(scale);
        this->setScaleZ(scale);
    }

    void Scale9Sprite::setScale(float scaleX, float scaleY)
    {
        this->setScaleX(scaleX);
        this->setScaleY(scaleY);
    }

    float Scale9Sprite::getScaleX()const
    {
        float originalScale = Node::getScaleX();
        if (_flippedX)
        {
            originalScale = originalScale * -1.0;
        }
        return originalScale;
    }

    float Scale9Sprite::getScaleY()const
    {
        float originalScale = Node::getScaleY();
        if (_flippedY)
        {
            originalScale = originalScale * -1.0;
        }
        return originalScale;
    }

    float Scale9Sprite::getScale()const
    {
        CCASSERT(this->getScaleX() == this->getScaleY(),
                 "Scale9Sprite#scale. ScaleX != ScaleY. Don't know which one to return");
        return this->getScaleX();
    }

    void Scale9Sprite::setCameraMask(unsigned short mask, bool applyChildren)
    {
        Node::setCameraMask(mask, applyChildren);

        if(_scale9Image)
            _scale9Image->setCameraMask(mask,applyChildren);

        for(auto& iter: _protectedChildren)
        {
            iter->setCameraMask(mask);
        }
    }

}}
