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
        
    }
    
    Scale9Sprite::~Scale9Sprite()
    {
        this->cleanupSlicedSprites();
        CC_SAFE_RELEASE(_scale9Image);
    }
    
    void Scale9Sprite::cleanupSlicedSprites()
    {
        CC_SAFE_RELEASE(_topLeft);
        CC_SAFE_RELEASE(_top);
        CC_SAFE_RELEASE(_topRight);
        CC_SAFE_RELEASE(_left);
        CC_SAFE_RELEASE(_centre);
        CC_SAFE_RELEASE(_right);
        CC_SAFE_RELEASE(_bottomLeft);
        CC_SAFE_RELEASE(_bottom);
        CC_SAFE_RELEASE(_bottomRight);
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
    
#define    TRANSLATE_X(x, y, xtranslate) \
x+=xtranslate;                       \

#define    TRANSLATE_Y(x, y, ytranslate) \
y+=ytranslate;                       \

    bool Scale9Sprite::updateWithSprite(Sprite* sprite, const Rect& originalRect, bool rotated, const Rect& capInsets)
    {
        GLubyte opacity = getOpacity();
        Color3B color = getColor();
        Rect rect(originalRect);
        
        // Release old sprites
        this->removeAllChildrenWithCleanup(true);
        
        this->cleanupSlicedSprites();
        
        
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
        
        _scale9Image->removeAllChildrenWithCleanup(true);
        
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
        
        this->createSlicedSprites(rect, rotated);
        
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
        
        if (!rotated) {
            // log("!rotated");
            
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
        this->addChild(_centre, 0);
        
        
        // Top
        _top = Sprite::createWithTexture(_scale9Image->getTexture(), rotatedcentertopbounds, rotated);
        _top->retain();
        this->addChild(_top, 1);
        
        // Bottom
        _bottom = Sprite::createWithTexture(_scale9Image->getTexture(), rotatedcenterbottombounds, rotated);
        _bottom->retain();
        this->addChild(_bottom, 1);
        
        // Left
        _left = Sprite::createWithTexture(_scale9Image->getTexture(), rotatedleftcenterbounds, rotated);
        _left->retain();
        this->addChild(_left, 1);
        
        // Right
        _right = Sprite::createWithTexture(_scale9Image->getTexture(), rotatedrightcenterbounds, rotated);
        _right->retain();
        this->addChild(_right, 1);
        
        // Top left
        _topLeft = Sprite::createWithTexture(_scale9Image->getTexture(), rotatedlefttopbounds, rotated);
        _topLeft->retain();
        this->addChild(_topLeft, 2);
        
        // Top right
        _topRight = Sprite::createWithTexture(_scale9Image->getTexture(), rotatedrighttopbounds, rotated);
        _topRight->retain();
        this->addChild(_topRight, 2);
        
        // Bottom left
        _bottomLeft = Sprite::createWithTexture(_scale9Image->getTexture(), rotatedleftbottombounds, rotated);
        _bottomLeft->retain();
        this->addChild(_bottomLeft, 2);
        
        // Bottom right
        _bottomRight = Sprite::createWithTexture(_scale9Image->getTexture(), rotatedrightbottombounds, rotated);
        _bottomRight->retain();
        this->addChild(_bottomRight, 2);
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
             (_centre))) {
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
        _bottomLeft->setPosition(Vec2(0,0));
        _bottomRight->setPosition(Vec2(leftWidth+rescaledWidth,0));
        _topLeft->setPosition(Vec2(0, bottomHeight+rescaledHeight));
        _topRight->setPosition(Vec2(leftWidth+rescaledWidth, bottomHeight+rescaledHeight));
        
        // Scale and position borders
        _left->setPosition(Vec2(0, bottomHeight));
        _left->setScaleY(verticalScale);
        _right->setPosition(Vec2(leftWidth+rescaledWidth,bottomHeight));
        _right->setScaleY(verticalScale);
        _bottom->setPosition(Vec2(leftWidth,0));
        _bottom->setScaleX(horizontalScale);
        _top->setPosition(Vec2(leftWidth,bottomHeight+rescaledHeight));
        _top->setScaleX(horizontalScale);
        
        // Position centre
        _centre->setPosition(Vec2(leftWidth, bottomHeight));
    }
    
    bool Scale9Sprite::initWithFile(const std::string& file, const Rect& rect,  const Rect& capInsets)
    {
        Sprite *sprite = Sprite::create(file);
        bool pReturn = this->init(sprite, rect, capInsets);
        return pReturn;
    }
    
    Scale9Sprite* Scale9Sprite::create(const std::string& file, const Rect& rect,  const Rect& capInsets)
    {
        Scale9Sprite* pReturn = new Scale9Sprite();
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
        Scale9Sprite* pReturn = new Scale9Sprite();
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
        Scale9Sprite* pReturn = new Scale9Sprite();
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
        Scale9Sprite* pReturn = new Scale9Sprite();
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
        Scale9Sprite* pReturn = new Scale9Sprite();
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
        Scale9Sprite* pReturn = new Scale9Sprite();
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
        Scale9Sprite* pReturn = new Scale9Sprite();
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
        Scale9Sprite* pReturn = new Scale9Sprite();
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
        Scale9Sprite* pReturn = new Scale9Sprite();
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
        Scale9Sprite *pReturn = new Scale9Sprite();
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

        if(this->_positionsAreDirty)
        {
            this->updatePositions();
            this->_positionsAreDirty = false;
        }
        
        Node::visit(renderer, parentTransform, parentFlags);
        
        if (_scale9Enabled)
        {
            //rendering the 9 sprites
        }
        else
        {
            if (_scale9Image)
            {
                _scale9Image->visit(renderer, parentTransform, parentFlags);
            }
        }
        
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
        _scale9Enabled = enabled;
    }
    
    bool Scale9Sprite::getScale9Enabled() const
    {
        return _scale9Enabled;
    }
}}