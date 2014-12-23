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
#include "ui/shaders/UIShaders.h"
#include "renderer/ccShaders.h"

NS_CC_BEGIN
namespace ui {
    
    Scale9Sprite::Scale9Sprite()
    : _spritesGenerated(false)
    , _spriteFrameRotated(false)
    , _positionsAreDirty(true)
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
    , _scale9Enabled(true)
    , _insetLeft(0)
    , _insetTop(0)
    , _insetRight(0)
    , _insetBottom(0)
    ,_flippedX(false)
    ,_flippedY(false)

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
        return init(sprite, rect, rotated, Vec2::ZERO, rect.size, capInsets);
    }
    
    bool Scale9Sprite::init(Sprite* sprite, const Rect& rect, bool rotated, const Vec2 &offset, const Size &originalSize, const Rect& capInsets)
    {
        if(sprite)
        {
            this->updateWithSprite(sprite, rect, rotated, offset, originalSize, capInsets);
        }
        
        return true;
    }
    
    bool Scale9Sprite::initWithBatchNode(cocos2d::SpriteBatchNode *batchnode, const cocos2d::Rect &rect, bool rotated, const cocos2d::Rect &capInsets)
    {
        Sprite *sprite = Sprite::createWithTexture(batchnode->getTexture());
        return init(sprite, rect, rotated, capInsets);
    }
    
    bool Scale9Sprite::initWithBatchNode(cocos2d::SpriteBatchNode *batchnode, const cocos2d::Rect &rect, const cocos2d::Rect &capInsets)
    {
        auto sprite = Sprite::createWithTexture(batchnode->getTexture());
        return init(sprite, rect, false, capInsets);
    }
    
#define    TRANSLATE_X(x, y, xtranslate) \
x+=xtranslate;                       \

#define    TRANSLATE_Y(x, y, ytranslate) \
y+=ytranslate;         \

    bool Scale9Sprite::updateWithBatchNode(cocos2d::SpriteBatchNode *batchnode, const cocos2d::Rect &originalRect, bool rotated, const cocos2d::Rect &capInsets)
    {
        Sprite *sprite = Sprite::createWithTexture(batchnode->getTexture());
        return this->updateWithSprite(sprite, originalRect, rotated, Vec2::ZERO, originalRect.size, capInsets);
    }
    
    bool Scale9Sprite::updateWithSprite(Sprite* sprite, const Rect& rect, bool rotated, const Rect& capInsets)
    {
        return updateWithSprite(sprite, rect, rotated, Vec2::ZERO, rect.size, capInsets);
    }
    
    static Rect intersectRect(const Rect &first, const Rect &second)
    {
        Rect ret;
        ret.origin.x = std::max(first.origin.x,second.origin.x);
        ret.origin.y = std::max(first.origin.y,second.origin.y);
        
        float rightRealPoint = std::min(first.origin.x + first.size.width, second.origin.x + second.size.width);
        float bottomRealPoint = std::min(first.origin.y + first.size.height, second.origin.y + second.size.height);
        
        ret.size.width = std::max(rightRealPoint - ret.origin.x, 0.0f);
        ret.size.height = std::max(bottomRealPoint - ret.origin.y, 0.0f);
        return ret;
    }
    
    bool Scale9Sprite::updateWithSprite(Sprite* sprite, const Rect& textureRect, bool rotated, const Vec2 &offset, const Size &originalSize, const Rect& capInsets)
    {
        GLubyte opacity = getOpacity();
        Color3B color = getColor();
        
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
        float w = _originalSize.width;
        float h = _originalSize.height;
        
        Vec2 offsetPosition(ceil(_offset.x + (_originalSize.width - _spriteRect.size.width) / 2), ceil(_offset.y + (_originalSize.height - _spriteRect.size.height) / 2));
        
        // If there is no specified center region
        if ( _capInsetsInternal.equals(Rect::ZERO) )
        {
            // log("... cap insets not specified : using default cap insets ...");
            _capInsetsInternal = Rect(w/3, h/3, w/3, h/3);
        }
        
        Rect originalRect;
        if(_spriteFrameRotated)
            originalRect = Rect(_spriteRect.origin.x - offsetPosition.y, _spriteRect.origin.y - offsetPosition.x, _originalSize.width, _originalSize.height);
        else
            originalRect = Rect(_spriteRect.origin.x - offsetPosition.x, _spriteRect.origin.y - offsetPosition.y, _originalSize.width, _originalSize.height);
        
        float left_w = _capInsetsInternal.origin.x;
        float center_w = _capInsetsInternal.size.width;
        float right_w = originalRect.size.width - (left_w + center_w);
        
        float top_h = _capInsetsInternal.origin.y;
        float center_h = _capInsetsInternal.size.height;
        float bottom_h = originalRect.size.height - (top_h + center_h);
        
        // calculate rects
        
        // ... top row
        float x = 0.0;
        float y = 0.0;
        
        Rect pixelRect = Rect(offsetPosition.x, offsetPosition.y, _spriteRect.size.width, _spriteRect.size.height);
        
        // top left
        Rect lefttopboundsorig = Rect(x, y, left_w, top_h);
        Rect lefttopbounds = lefttopboundsorig;
        
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
        Rect centerboundsorig = Rect(x, y, center_w, center_h);
        Rect centerbounds = centerboundsorig;
        
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
        Rect rightbottomboundsorig = Rect(x, y, right_w, bottom_h);
        Rect rightbottombounds = rightbottomboundsorig;
        
        if((_capInsetsInternal.origin.x + _capInsetsInternal.size.width) <= _originalSize.width
           || (_capInsetsInternal.origin.y + _capInsetsInternal.size.height) <= _originalSize.height)
        //in general case it is error but for legacy support we will check it
        {
            lefttopbounds = intersectRect(lefttopbounds, pixelRect);
            centertopbounds = intersectRect(centertopbounds, pixelRect);
            righttopbounds = intersectRect(righttopbounds, pixelRect);
            leftcenterbounds = intersectRect(leftcenterbounds, pixelRect);
            centerbounds = intersectRect(centerbounds, pixelRect);
            rightcenterbounds = intersectRect(rightcenterbounds, pixelRect);
            leftbottombounds = intersectRect(leftbottombounds, pixelRect);
            centerbottombounds = intersectRect(centerbottombounds, pixelRect);
            rightbottombounds = intersectRect(rightbottombounds, pixelRect);
        }
        else
            //it is error but for legacy turn off clip system
            CCLOG("Scale9Sprite capInsetsInternal > originalSize");
        
        Rect rotatedlefttopboundsorig = lefttopboundsorig;
        Rect rotatedcenterboundsorig = centerboundsorig;
        Rect rotatedrightbottomboundsorig = rightbottomboundsorig;
        
        Rect rotatedcenterbounds = centerbounds;
        Rect rotatedrightbottombounds = rightbottombounds;
        Rect rotatedleftbottombounds = leftbottombounds;
        Rect rotatedrighttopbounds = righttopbounds;
        Rect rotatedlefttopbounds = lefttopbounds;
        Rect rotatedrightcenterbounds = rightcenterbounds;
        Rect rotatedleftcenterbounds = leftcenterbounds;
        Rect rotatedcenterbottombounds = centerbottombounds;
        Rect rotatedcentertopbounds = centertopbounds;
        
        if (!_spriteFrameRotated)
        {
            
            AffineTransform t = AffineTransform::IDENTITY;
            t = AffineTransformTranslate(t, originalRect.origin.x, originalRect.origin.y);
            
            rotatedlefttopboundsorig = RectApplyAffineTransform(rotatedlefttopboundsorig, t);
            rotatedcenterboundsorig = RectApplyAffineTransform(rotatedcenterboundsorig, t);
            rotatedrightbottomboundsorig = RectApplyAffineTransform(rotatedrightbottomboundsorig, t);
            
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
            
            t = AffineTransformTranslate(t, originalRect.size.height+originalRect.origin.x, originalRect.origin.y);
            t = AffineTransformRotate(t, 1.57079633f);
            
            lefttopboundsorig = RectApplyAffineTransform(lefttopboundsorig, t);
            centerboundsorig = RectApplyAffineTransform(centerboundsorig, t);
            rightbottomboundsorig = RectApplyAffineTransform(rightbottomboundsorig, t);
            
            centerbounds = RectApplyAffineTransform(centerbounds, t);
            rightbottombounds = RectApplyAffineTransform(rightbottombounds, t);
            leftbottombounds = RectApplyAffineTransform(leftbottombounds, t);
            righttopbounds = RectApplyAffineTransform(righttopbounds, t);
            lefttopbounds = RectApplyAffineTransform(lefttopbounds, t);
            rightcenterbounds = RectApplyAffineTransform(rightcenterbounds, t);
            leftcenterbounds = RectApplyAffineTransform(leftcenterbounds, t);
            centerbottombounds = RectApplyAffineTransform(centerbottombounds, t);
            centertopbounds = RectApplyAffineTransform(centertopbounds, t);
            
            rotatedlefttopboundsorig.origin = lefttopboundsorig.origin;
            rotatedcenterboundsorig.origin = centerboundsorig.origin;
            rotatedrightbottomboundsorig.origin = rightbottomboundsorig.origin;
            
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
        
        _topLeftSize = rotatedlefttopboundsorig.size;
        _centerSize = rotatedcenterboundsorig.size;
        _bottomRightSize = rotatedrightbottomboundsorig.size;
        
        if(_spriteFrameRotated)
        {
            float offsetx = (rotatedcenterbounds.origin.x + rotatedcenterbounds.size.height/2) - (rotatedcenterboundsorig.origin.x + rotatedcenterboundsorig.size.height/2);
            float offsety = (rotatedcenterboundsorig.origin.y + rotatedcenterboundsorig.size.width/2)- (rotatedcenterbounds.origin.y + rotatedcenterbounds.size.width/2);
            _centerOffset.x = -offsety;
            _centerOffset.y = offsetx;
        }
        else
        {
            float offsetx = (rotatedcenterbounds.origin.x + rotatedcenterbounds.size.width/2) - (rotatedcenterboundsorig.origin.x + rotatedcenterboundsorig.size.width/2);
            float offsety = (rotatedcenterboundsorig.origin.y + rotatedcenterboundsorig.size.height/2)- (rotatedcenterbounds.origin.y + rotatedcenterbounds.size.height/2);
            _centerOffset.x = offsetx;
            _centerOffset.y = offsety;
        }
        
        // Centre
        if(rotatedcenterbounds.size.width > 0 && rotatedcenterbounds.size.height > 0 )
        {
            _centre = Sprite::createWithTexture(_scale9Image->getTexture(), rotatedcenterbounds, _spriteFrameRotated);
            _centre->retain();
            this->addProtectedChild(_centre);
        }
        
        // Top
        if(rotatedcentertopbounds.size.width > 0 && rotatedcentertopbounds.size.height > 0 )
        {
            _top = Sprite::createWithTexture(_scale9Image->getTexture(), rotatedcentertopbounds, _spriteFrameRotated);
            _top->retain();
            this->addProtectedChild(_top);
        }
        
        // Bottom
        if(rotatedcenterbottombounds.size.width > 0 && rotatedcenterbottombounds.size.height > 0 )
        {
            _bottom = Sprite::createWithTexture(_scale9Image->getTexture(), rotatedcenterbottombounds, _spriteFrameRotated);
            _bottom->retain();
            this->addProtectedChild(_bottom);
        }
        
        // Left
        if(rotatedleftcenterbounds.size.width > 0 && rotatedleftcenterbounds.size.height > 0 )
        {
            _left = Sprite::createWithTexture(_scale9Image->getTexture(), rotatedleftcenterbounds, _spriteFrameRotated);
            _left->retain();
            this->addProtectedChild(_left);
        }
        
        // Right
        if(rotatedrightcenterbounds.size.width > 0 && rotatedrightcenterbounds.size.height > 0 )
        {
            _right = Sprite::createWithTexture(_scale9Image->getTexture(), rotatedrightcenterbounds, _spriteFrameRotated);
            _right->retain();
            this->addProtectedChild(_right);
        }
        
        // Top left
        if(rotatedlefttopbounds.size.width > 0 && rotatedlefttopbounds.size.height > 0 )
        {
            _topLeft = Sprite::createWithTexture(_scale9Image->getTexture(), rotatedlefttopbounds, _spriteFrameRotated);
            _topLeft->retain();
            this->addProtectedChild(_topLeft);
        }
        
        // Top right
        if(rotatedrighttopbounds.size.width > 0 && rotatedrighttopbounds.size.height > 0 )
        {
            _topRight = Sprite::createWithTexture(_scale9Image->getTexture(), rotatedrighttopbounds, _spriteFrameRotated);
            _topRight->retain();
            this->addProtectedChild(_topRight);
        }
        
        // Bottom left
        if(rotatedleftbottombounds.size.width > 0 && rotatedleftbottombounds.size.height > 0 )
        {
            _bottomLeft = Sprite::createWithTexture(_scale9Image->getTexture(), rotatedleftbottombounds, _spriteFrameRotated);
            _bottomLeft->retain();
            this->addProtectedChild(_bottomLeft);
        }
        
        // Bottom right
        if(rotatedrightbottombounds.size.width > 0 && rotatedrightbottombounds.size.height > 0 )
        {
            _bottomRight = Sprite::createWithTexture(_scale9Image->getTexture(), rotatedrightbottombounds, _spriteFrameRotated);
            _bottomRight->retain();
            this->addProtectedChild(_bottomRight);
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
        
        if(_centre)
        {
            _centre->setScaleX(horizontalScale);
            _centre->setScaleY(verticalScale);
        }
        
        float rescaledWidth = _centerSize.width * horizontalScale;
        float rescaledHeight = _centerSize.height * verticalScale;
        
        float leftWidth = _topLeftSize.width;
        float bottomHeight = _bottomRightSize.height;
        
        Vec2 centerOffset(_centerOffset.x * horizontalScale, _centerOffset.y * verticalScale);
        
        // Position corners
        if(_bottomLeft)
        {
            _bottomLeft->setAnchorPoint(Vec2(1,1));
            _bottomLeft->setPosition(leftWidth,bottomHeight);
        }
        if(_bottomRight)
        {
            _bottomRight->setAnchorPoint(Vec2(0,1));
            _bottomRight->setPosition(leftWidth+rescaledWidth,bottomHeight);
        }
        if(_topLeft)
        {
            _topLeft->setAnchorPoint(Vec2(1,0));
            _topLeft->setPosition(leftWidth, bottomHeight+rescaledHeight);
        }
        if(_topRight)
        {
            _topRight->setAnchorPoint(Vec2(0,0));
            _topRight->setPosition(leftWidth+rescaledWidth, bottomHeight+rescaledHeight);
        }
        
        // Scale and position borders
        if(_left)
        {
            _left->setAnchorPoint(Vec2(1,0.5));
            _left->setPosition(leftWidth, bottomHeight+rescaledHeight/2 + centerOffset.y);
            _left->setScaleY(verticalScale);
        }
        if(_right)
        {
            _right->setAnchorPoint(Vec2(0,0.5));
            _right->setPosition(leftWidth+rescaledWidth,bottomHeight+rescaledHeight/2 + centerOffset.y);
            _right->setScaleY(verticalScale);
        }
        if(_top)
        {
            _top->setAnchorPoint(Vec2(0.5,0));
            _top->setPosition(leftWidth+rescaledWidth/2 + centerOffset.x,bottomHeight+rescaledHeight);
            _top->setScaleX(horizontalScale);
        }
        if(_bottom)
        {
            _bottom->setAnchorPoint(Vec2(0.5,1));
            _bottom->setPosition(leftWidth+rescaledWidth/2 + centerOffset.x,bottomHeight);
            _bottom->setScaleX(horizontalScale);
        }
        // Position centre
        if(_centre)
        {
            _centre->setAnchorPoint(Vec2(0.5,0.5));
            _centre->setPosition(leftWidth+rescaledWidth/2 + centerOffset.x, bottomHeight+rescaledHeight/2 + centerOffset.y);
            _centre->setScaleX(horizontalScale);
            _centre->setScaleY(verticalScale);
        }
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
        
        bool pReturn = this->init(sprite, spriteFrame->getRect(), spriteFrame->isRotated(), spriteFrame->getOffset(), spriteFrame->getOriginalSize(), capInsets);
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
    
    Scale9Sprite* Scale9Sprite::resizableSpriteWithCapInsets(const Rect& capInsets) const
    {
        Scale9Sprite* pReturn = new (std::nothrow) Scale9Sprite();
        if ( pReturn && pReturn->init(_scale9Image, _spriteRect, _spriteFrameRotated, _offset, _originalSize, _capInsets) )
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
                auto program = GLProgram::createWithByteArrays(ccPositionTextureColor_noMVP_vert,
                                                               ccUIGrayScale_frag);
                glState = GLProgramState::getOrCreateWithGLProgram(program);
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
                          _originalSize.width-_insetLeft-_insetRight,
                          _originalSize.height-_insetTop-_insetBottom);
        }
        this->setCapInsets(insets);
    }
    
    
    void Scale9Sprite::setSpriteFrame(SpriteFrame * spriteFrame, const Rect& capInsets)
    {
        Sprite * sprite = Sprite::createWithTexture(spriteFrame->getTexture());
        this->updateWithSprite(sprite, spriteFrame->getRect(), spriteFrame->isRotated(), spriteFrame->getOffset(), spriteFrame->getOriginalSize(), capInsets);
        
        // Reset insets
        this->_insetLeft = capInsets.origin.x;
        this->_insetTop = capInsets.origin.y;
        this->_insetRight = _originalSize.width - _insetLeft - capInsets.size.width;
        this->_insetBottom = _originalSize.height - _insetTop - capInsets.size.height;
    }
    
    void Scale9Sprite::setPreferredSize(const Size& preferedSize)
    {
        this->setContentSize(preferedSize);
        this->_preferredSize = preferedSize;
    }
    
    
    void Scale9Sprite::setCapInsets(const Rect& capInsets)
    {
        Size contentSize = this->_contentSize;
        this->updateWithSprite(this->_scale9Image, _spriteRect, _spriteFrameRotated, _offset, _originalSize, capInsets);
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
                this->updateWithSprite(this->_scale9Image, _spriteRect, _spriteFrameRotated, _offset, _originalSize, _capInsets);
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
        CCASSERT(this->getScaleX() == this->getScaleY(), "Scale9Sprite#scale. ScaleX != ScaleY. Don't know which one to return");
        return this->getScaleX();
    }
    
}}
