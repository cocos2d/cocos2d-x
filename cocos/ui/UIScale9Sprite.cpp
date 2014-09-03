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

NS_CC_BEGIN
namespace ui {
    
    Scale9Sprite::Scale9Sprite()
    : _spritesGenerated(false)
    , _spriteFrameRotated(false)
    , _positionsAreDirty(false)
    , _scale9Image(nullptr)
    , _topLeft(nullptr)
    , _top(nullptr)
    , _topRight(nullptr)
    , _left(nullptr)
    , _centre(nullptr)
    , _right(nullptr)
    , _bottomLeft(nullptr)
    , _bottom(nullptr)
    , _bottomRight(nullptr)
    , _insetLeft(0)
    , _insetTop(0)
    , _insetRight(0)
    , _insetBottom(0),
    _scale9Enabled(true)
    {
        this->setAnchorPoint(Vec2(0.5,0.5));
    }
    
    Scale9Sprite::~Scale9Sprite()
    {
        this->cleanupSlicedSprites();
        CC_SAFE_RELEASE(_scale9Image);
    }
    
    void Scale9Sprite::cleanupSlicedSprites()
    {
        if (_topLeft && _topLeft->isRunning())
        {
            _topLeft->onExit();
        }
        if (_top && _top->isRunning())
        {
            _top->onExit();
        }
        if (_topRight && _topRight->isRunning())
        {
            _topRight->onExit();
        }
        
        if (_left && _left->isRunning())
        {
            _left->onExit();
        }
        
        if (_centre && _centre->isRunning())
        {
            _centre->onExit();
        }
        
        if (_right && _right->isRunning())
        {
            _right->onExit();
        }
        
        if (_bottomLeft && _bottomLeft->isRunning())
        {
            _bottomLeft->onExit();
        }
        
        if (_bottomRight && _bottomRight->isRunning())
        {
            _bottomRight->onExit();
        }
        
        if (_bottom && _bottom->isRunning())
        {
            _bottom->onExit();
        }
        
        CC_SAFE_RELEASE_NULL(_topLeft);
        CC_SAFE_RELEASE_NULL(_top);
        CC_SAFE_RELEASE_NULL(_topRight);
        CC_SAFE_RELEASE_NULL(_left);
        CC_SAFE_RELEASE_NULL(_centre);
        CC_SAFE_RELEASE_NULL(_right);
        CC_SAFE_RELEASE_NULL(_bottomLeft);
        CC_SAFE_RELEASE_NULL(_bottom);
        CC_SAFE_RELEASE_NULL(_bottomRight);
    }
    
    bool Scale9Sprite::init()
    {
        return this->init(NULL, Rect::ZERO, Rect::ZERO);
    }
    
    bool Scale9Sprite::init(Sprite* sprite, const Rect& rect, const Rect& capInsets)
    {
        return this->init(sprite, rect, false, capInsets);
    }
    
    bool Scale9Sprite::init(Sprite* sprite, const Rect& rect, bool rotated, const Rect& capInsets)
    {
        if(sprite)
        {
            this->updateWithSprite(sprite, rect, rotated, capInsets);
        }
        this->setCascadeColorEnabled(true);
        this->setCascadeOpacityEnabled(true);
        this->setAnchorPoint(Vec2(0.5f, 0.5f));
        this->_positionsAreDirty = true;
        
        return true;
    }
    
    bool Scale9Sprite::initWithBatchNode(cocos2d::SpriteBatchNode *batchnode, const cocos2d::Rect &rect, bool rotated, const cocos2d::Rect &capInsets)
    {
        Sprite *sprite = Sprite::createWithTexture(batchnode->getTexture());
        return init(sprite, rect, rotated, capInsets);
    }
    
    bool Scale9Sprite::initWithBatchNode(cocos2d::SpriteBatchNode *batchnode, const cocos2d::Rect &rect, const cocos2d::Rect &capInsets)
    {
        return initWithBatchNode(batchnode, rect, false, capInsets);
    }
    
#define    TRANSLATE_X(x, y, xtranslate) \
x+=xtranslate;                       \

#define    TRANSLATE_Y(x, y, ytranslate) \
y+=ytranslate;         \

    bool Scale9Sprite::updateWithBatchNode(cocos2d::SpriteBatchNode *batchnode, const cocos2d::Rect &originalRect, bool rotated, const cocos2d::Rect &capInsets)
    {
        Sprite *sprite = Sprite::createWithTexture(batchnode->getTexture());
        return this->updateWithSprite(sprite, originalRect, rotated, capInsets);
    }

    bool Scale9Sprite::updateWithSprite(Sprite* sprite, const Rect& originalRect, bool rotated, const Rect& capInsets)
    {
        GLubyte opacity = getOpacity();
        Color3B color = getColor();
        Rect rect(originalRect);
        
        // Release old sprites
        this->cleanupSlicedSprites();
        _protectedChildren.clear();
        
        if(this->_scale9Image != sprite)
        {
            CC_SAFE_RELEASE(this->_scale9Image);
            _scale9Image = sprite;
            CC_SAFE_RETAIN(_scale9Image);
        }
        
        if (!_scale9Image)
        {
            return false;
        }
        
        _capInsets = capInsets;
        _spriteFrameRotated = rotated;
        
        // If there is no given rect
        if ( rect.equals(Rect::ZERO) )
        {
            // Get the texture size as original
            Size textureSize = _scale9Image->getTexture()->getContentSize();
            
            rect = Rect(0, 0, textureSize.width, textureSize.height);
        }
        
        // Set the given rect's size as original size
        _spriteRect = rect;
        _originalSize = rect.size;
        _preferredSize = _originalSize;
        _capInsetsInternal = capInsets;
        
        if (_scale9Enabled)
        {
            this->createSlicedSprites(rect, rotated);
        }
        
        this->setContentSize(rect.size);
        
        if (_spritesGenerated)
        {
            // Restore color and opacity
            this->setOpacity(opacity);
            this->setColor(color);
        }
        _spritesGenerated = true;
        
        return true;
    }
    
    void Scale9Sprite::createSlicedSprites(const Rect& rect, bool rotated)
    {
        float w = rect.size.width;
        float h = rect.size.height;
        
        // If there is no specified center region
        if ( _capInsetsInternal.equals(Rect::ZERO) )
        {
            // log("... cap insets not specified : using default cap insets ...");
            _capInsetsInternal = Rect(w/3, h/3, w/3, h/3);
        }
        
        float left_w = _capInsetsInternal.origin.x;
        float center_w = _capInsetsInternal.size.width;
        float right_w = rect.size.width - (left_w + center_w);
        
        float top_h = _capInsetsInternal.origin.y;
        float center_h = _capInsetsInternal.size.height;
        float bottom_h = rect.size.height - (top_h + center_h);
        
        // calculate rects
        
        // ... top row
        float x = 0.0;
        float y = 0.0;
        
        // top left
        Rect lefttopbounds = Rect(x, y, left_w, top_h);
        
        // top center
        TRANSLATE_X(x, y, left_w);
        Rect centertopbounds = Rect(x, y, center_w, top_h);
        
        // top right
        TRANSLATE_X(x, y, center_w);
        Rect righttopbounds = Rect(x, y, right_w, top_h);
        
        // ... center row
        x = 0.0;
        y = 0.0;
        TRANSLATE_Y(x, y, top_h);
        
        // center left
        Rect leftcenterbounds = Rect(x, y, left_w, center_h);
        
        // center center
        TRANSLATE_X(x, y, left_w);
        Rect centerbounds = Rect(x, y, center_w, center_h);
        
        // center right
        TRANSLATE_X(x, y, center_w);
        Rect rightcenterbounds = Rect(x, y, right_w, center_h);
        
        // ... bottom row
        x = 0.0;
        y = 0.0;
        TRANSLATE_Y(x, y, top_h);
        TRANSLATE_Y(x, y, center_h);
        
        // bottom left
        Rect leftbottombounds = Rect(x, y, left_w, bottom_h);
        
        // bottom center
        TRANSLATE_X(x, y, left_w);
        Rect centerbottombounds = Rect(x, y, center_w, bottom_h);
        
        // bottom right
        TRANSLATE_X(x, y, center_w);
        Rect rightbottombounds = Rect(x, y, right_w, bottom_h);
        
        
        Rect rotatedcenterbounds = centerbounds;
        Rect rotatedrightbottombounds = rightbottombounds;
        Rect rotatedleftbottombounds = leftbottombounds;
        Rect rotatedrighttopbounds = righttopbounds;
        Rect rotatedlefttopbounds = lefttopbounds;
        Rect rotatedrightcenterbounds = rightcenterbounds;
        Rect rotatedleftcenterbounds = leftcenterbounds;
        Rect rotatedcenterbottombounds = centerbottombounds;
        Rect rotatedcentertopbounds = centertopbounds;
        
        if (!rotated)
        {
            
            AffineTransform t = AffineTransform::IDENTITY;
            t = AffineTransformTranslate(t, rect.origin.x, rect.origin.y);
            
            rotatedcenterbounds = RectApplyAffineTransform(rotatedcenterbounds, t);
            rotatedrightbottombounds = RectApplyAffineTransform(rotatedrightbottombounds, t);
            rotatedleftbottombounds = RectApplyAffineTransform(rotatedleftbottombounds, t);
            rotatedrighttopbounds = RectApplyAffineTransform(rotatedrighttopbounds, t);
            rotatedlefttopbounds = RectApplyAffineTransform(rotatedlefttopbounds, t);
            rotatedrightcenterbounds = RectApplyAffineTransform(rotatedrightcenterbounds, t);
            rotatedleftcenterbounds = RectApplyAffineTransform(rotatedleftcenterbounds, t);
            rotatedcenterbottombounds = RectApplyAffineTransform(rotatedcenterbottombounds, t);
            rotatedcentertopbounds = RectApplyAffineTransform(rotatedcentertopbounds, t);
            
            
        } else {
            // set up transformation of coordinates
            // to handle the case where the sprite is stored rotated
            // in the spritesheet
            // log("rotated");
            
            AffineTransform t = AffineTransform::IDENTITY;
            
            t = AffineTransformTranslate(t, rect.size.height+rect.origin.x, rect.origin.y);
            t = AffineTransformRotate(t, 1.57079633f);
            
            centerbounds = RectApplyAffineTransform(centerbounds, t);
            rightbottombounds = RectApplyAffineTransform(rightbottombounds, t);
            leftbottombounds = RectApplyAffineTransform(leftbottombounds, t);
            righttopbounds = RectApplyAffineTransform(righttopbounds, t);
            lefttopbounds = RectApplyAffineTransform(lefttopbounds, t);
            rightcenterbounds = RectApplyAffineTransform(rightcenterbounds, t);
            leftcenterbounds = RectApplyAffineTransform(leftcenterbounds, t);
            centerbottombounds = RectApplyAffineTransform(centerbottombounds, t);
            centertopbounds = RectApplyAffineTransform(centertopbounds, t);
            
            rotatedcenterbounds.origin = centerbounds.origin;
            rotatedrightbottombounds.origin = rightbottombounds.origin;
            rotatedleftbottombounds.origin = leftbottombounds.origin;
            rotatedrighttopbounds.origin = righttopbounds.origin;
            rotatedlefttopbounds.origin = lefttopbounds.origin;
            rotatedrightcenterbounds.origin = rightcenterbounds.origin;
            rotatedleftcenterbounds.origin = leftcenterbounds.origin;
            rotatedcenterbottombounds.origin = centerbottombounds.origin;
            rotatedcentertopbounds.origin = centertopbounds.origin;
            
            
        }
        
        
        // Centre
        _centre = Sprite::createWithTexture(_scale9Image->getTexture(), rotatedcenterbounds, rotated);
        _centre->retain();
        this->addProtectedChild(_centre);
        
        
        // Top
        _top = Sprite::createWithTexture(_scale9Image->getTexture(), rotatedcentertopbounds, rotated);
        _top->retain();
        this->addProtectedChild(_top);
        
        // Bottom
        _bottom = Sprite::createWithTexture(_scale9Image->getTexture(), rotatedcenterbottombounds, rotated);
        _bottom->retain();
        this->addProtectedChild(_bottom);
        
        // Left
        _left = Sprite::createWithTexture(_scale9Image->getTexture(), rotatedleftcenterbounds, rotated);
        _left->retain();
        this->addProtectedChild(_left);
        
        // Right
        _right = Sprite::createWithTexture(_scale9Image->getTexture(), rotatedrightcenterbounds, rotated);
        _right->retain();
        this->addProtectedChild(_right);
        
        // Top left
        _topLeft = Sprite::createWithTexture(_scale9Image->getTexture(), rotatedlefttopbounds, rotated);
        _topLeft->retain();
        this->addProtectedChild(_topLeft);
        
        // Top right
        _topRight = Sprite::createWithTexture(_scale9Image->getTexture(), rotatedrighttopbounds, rotated);
        _topRight->retain();
        this->addProtectedChild(_topRight);
        
        // Bottom left
        _bottomLeft = Sprite::createWithTexture(_scale9Image->getTexture(), rotatedleftbottombounds, rotated);
        _bottomLeft->retain();
        this->addProtectedChild(_bottomLeft);
        
        // Bottom right
        _bottomRight = Sprite::createWithTexture(_scale9Image->getTexture(), rotatedrightbottombounds, rotated);
        _bottomRight->retain();
        this->addProtectedChild(_bottomRight);
    }
    
    void Scale9Sprite::setContentSize(const Size &size)
    {
        Node::setContentSize(size);
        this->_positionsAreDirty = true;
    }
    
    void Scale9Sprite::updatePositions()
    {
        // Check that instances are non-NULL
        if(!((_topLeft) &&
             (_topRight) &&
             (_bottomRight) &&
             (_bottomLeft) &&
             (_centre)))
        {
            // if any of the above sprites are NULL, return
            return;
        }
        
        Size size = this->_contentSize;
        
        float sizableWidth = size.width - _topLeft->getContentSize().width - _topRight->getContentSize().width;
        float sizableHeight = size.height - _topLeft->getContentSize().height - _bottomRight->getContentSize().height;
        
        float horizontalScale = sizableWidth/_centre->getContentSize().width;
        float verticalScale = sizableHeight/_centre->getContentSize().height;
        
        _centre->setScaleX(horizontalScale);
        _centre->setScaleY(verticalScale);
        
        float rescaledWidth = _centre->getContentSize().width * horizontalScale;
        float rescaledHeight = _centre->getContentSize().height * verticalScale;
        
        float leftWidth = _bottomLeft->getContentSize().width;
        float bottomHeight = _bottomLeft->getContentSize().height;
        
        _bottomLeft->setAnchorPoint(Vec2(0,0));
        _bottomRight->setAnchorPoint(Vec2(0,0));
        _topLeft->setAnchorPoint(Vec2(0,0));
        _topRight->setAnchorPoint(Vec2(0,0));
        _left->setAnchorPoint(Vec2(0,0));
        _right->setAnchorPoint(Vec2(0,0));
        _top->setAnchorPoint(Vec2(0,0));
        _bottom->setAnchorPoint(Vec2(0,0));
        _centre->setAnchorPoint(Vec2(0,0));
        
        // Position corners
        _bottomLeft->setPosition(0,0);
        _bottomRight->setPosition(leftWidth+rescaledWidth,0);
        _topLeft->setPosition(0, bottomHeight+rescaledHeight);
        _topRight->setPosition(leftWidth+rescaledWidth, bottomHeight+rescaledHeight);
        
        // Scale and position borders
        _left->setPosition(0, bottomHeight);
        _left->setScaleY(verticalScale);
        _right->setPosition(leftWidth+rescaledWidth,bottomHeight);
        _right->setScaleY(verticalScale);
        _bottom->setPosition(leftWidth,0);
        _bottom->setScaleX(horizontalScale);
        _top->setPosition(leftWidth,bottomHeight+rescaledHeight);
        _top->setScaleX(horizontalScale);
        
        // Position centre
        _centre->setPosition(leftWidth, bottomHeight);
    }
    
    bool Scale9Sprite::initWithFile(const std::string& file, const Rect& rect,  const Rect& capInsets)
    {
        Sprite *sprite = Sprite::create(file);
        bool pReturn = this->init(sprite, rect, capInsets);
        return pReturn;
    }
    
    Scale9Sprite* Scale9Sprite::create(const std::string& file, const Rect& rect,  const Rect& capInsets)
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
    
    bool Scale9Sprite::initWithFile(const std::string& file, const Rect& rect)
    {
        bool pReturn = this->initWithFile(file, rect, Rect::ZERO);
        return pReturn;
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
    
    
    bool Scale9Sprite::initWithFile(const Rect& capInsets, const std::string& file)
    {
        bool pReturn = this->initWithFile(file, Rect::ZERO, capInsets);
        return pReturn;
    }
    
    Scale9Sprite* Scale9Sprite::create(const Rect& capInsets, const std::string& file)
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
    
    bool Scale9Sprite::initWithFile(const std::string& file)
    {
        bool pReturn = this->initWithFile(file, Rect::ZERO);
        return pReturn;
        
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
    
    bool Scale9Sprite::initWithSpriteFrame(SpriteFrame* spriteFrame, const Rect& capInsets)
    {
        Texture2D* texture = spriteFrame->getTexture();
        CCASSERT(texture != NULL, "CCTexture must be not nil");
        
        Sprite *sprite = Sprite::createWithSpriteFrame(spriteFrame);
        CCASSERT(sprite != NULL, "sprite must be not nil");
        
        bool pReturn = this->init(sprite, spriteFrame->getRect(), spriteFrame->isRotated(), capInsets);
        return pReturn;
    }
    
    Scale9Sprite* Scale9Sprite::createWithSpriteFrame(SpriteFrame* spriteFrame, const Rect& capInsets)
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
    bool Scale9Sprite::initWithSpriteFrame(SpriteFrame* spriteFrame)
    {
        CCASSERT(spriteFrame != NULL, "Invalid spriteFrame for sprite");
        bool pReturn = this->initWithSpriteFrame(spriteFrame, Rect::ZERO);
        return pReturn;
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
    
    bool Scale9Sprite::initWithSpriteFrameName(const std::string& spriteFrameName, const Rect& capInsets)
    {
        CCASSERT((SpriteFrameCache::getInstance()) != NULL, "SpriteFrameCache::getInstance() must be non-NULL");
        
        SpriteFrame *frame = SpriteFrameCache::getInstance()->getSpriteFrameByName(spriteFrameName);
        CCASSERT(frame != NULL, "CCSpriteFrame must be non-NULL");
        
        if (NULL == frame) return false;
        
        bool pReturn = this->initWithSpriteFrame(frame, capInsets);
        return pReturn;
    }
    
    Scale9Sprite* Scale9Sprite::createWithSpriteFrameName(const std::string& spriteFrameName, const Rect& capInsets)
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
    
    bool Scale9Sprite::initWithSpriteFrameName(const std::string& spriteFrameName)
    {
        bool pReturn = this->initWithSpriteFrameName(spriteFrameName, Rect::ZERO);
        return pReturn;
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
    
    Scale9Sprite* Scale9Sprite::resizableSpriteWithCapInsets(const Rect& capInsets)
    {
        Scale9Sprite* pReturn = new (std::nothrow) Scale9Sprite();
        if ( pReturn && pReturn->init(_scale9Image, _spriteRect, capInsets) )
        {
            pReturn->autorelease();
            return pReturn;
        }
        CC_SAFE_DELETE(pReturn);
        return NULL;
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
    
    /** sets the opacity.
     @warning If the the texture has premultiplied alpha then, the R, G and B channels will be modifed.
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
                          _spriteRect.size.width-_insetLeft-_insetRight,
                          _spriteRect.size.height-_insetTop-_insetBottom);
        }
        this->setCapInsets(insets);
    }
    
    
    void Scale9Sprite::setSpriteFrame(SpriteFrame * spriteFrame)
    {
        Sprite * sprite = Sprite::createWithTexture(spriteFrame->getTexture());
        this->updateWithSprite(sprite, spriteFrame->getRect(), spriteFrame->isRotated(), Rect::ZERO);
        
        // Reset insets
        this->_insetLeft = 0;
        this->_insetTop = 0;
        this->_insetRight = 0;
        this->_insetBottom = 0;
    }
    
    void Scale9Sprite::setPreferredSize(const Size& preferedSize)
    {
        this->setContentSize(preferedSize);
        this->_preferredSize = preferedSize;
    }
    
    
    void Scale9Sprite::setCapInsets(const Rect& capInsets)
    {
        Size contentSize = this->_contentSize;
        this->updateWithSprite(this->_scale9Image, this->_spriteRect, _spriteFrameRotated, capInsets);
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
        CCASSERT(nullptr != director, "Director is null when seting matrix stack");
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
            if (_scale9Image)
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
            if (_scale9Image)
            {
                _scale9Image->visit(renderer, _modelViewTransform, flags);
            }
        }
        
        
        for(auto it=_children.cbegin()+i; it != _children.cend(); ++it)
            (*it)->visit(renderer, _modelViewTransform, flags);
        
        // reset for next frame
        _orderOfArrival = 0;
        
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
        
        if (_scale9Enabled)
        {
            if (_scale9Image)
            {
                this->updateWithSprite(this->_scale9Image,
                                       this->_spriteRect,
                                       _spriteFrameRotated, _capInsets);
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
            std::sort( std::begin(_protectedChildren), std::end(_protectedChildren), nodeComparisonLess );
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
        Node::onExit();
        for( const auto &child: _protectedChildren)
            child->onExit();
    }
    
    void Scale9Sprite::onEnterTransitionDidFinish()
    {
        Node::onEnterTransitionDidFinish();
        for( const auto &child: _protectedChildren)
            child->onEnterTransitionDidFinish();
    }
    
    void Scale9Sprite::onExitTransitionDidStart()
    {
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
        _flippedX = flippedX;
        if (_scale9Enabled)
        {
            this->setScaleX(-1);
        }
        else
        {
            if (_scale9Image)
            {
                _scale9Image->setFlippedX(flippedX);
            }
        }
    }
    
    void Scale9Sprite::setFlippedY(bool flippedY)
    {
        _flippedY = flippedY;
        if (_scale9Enabled)
        {
            this->setScaleY(-1);
        }
        else
        {
            if (_scale9Image)
            {
                _scale9Image->setFlippedY(flippedY);
            }
        }
    }
    
    bool Scale9Sprite::isFlippedX()const
    {
        return _flippedX;
    }
    
    bool Scale9Sprite::isFlippedY()const
    {
        return _flippedY;
    }
}}
