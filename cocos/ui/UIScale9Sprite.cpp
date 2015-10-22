/****************************************************************************
 Copyright (c) 2013-2015 Chukong Technologies Inc.
 Copyright (c) 2013-2015 zilongshanren

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
#include "2d/CCSpriteFrameCache.h"
#include "base/CCDirector.h"
#include "renderer/CCTextureCache.h"


NS_CC_BEGIN
namespace ui {
    Scale9Sprite* Scale9Sprite::create()
    {
        Scale9Sprite *sprite = new (std::nothrow) Scale9Sprite();
        if (sprite && sprite->init())
        {
            sprite->autorelease();
            return sprite;
        }
        CC_SAFE_DELETE(sprite);
        return nullptr;
    }
    
    
    Scale9Sprite* Scale9Sprite::create(const std::string& filename, const Rect& rect)
    {
        Scale9Sprite *sprite = new (std::nothrow) Scale9Sprite();
        if (sprite && sprite->initWithFile(filename, rect))
        {
            sprite->autorelease();
            return sprite;
        }
        CC_SAFE_DELETE(sprite);
        return nullptr;
    }
    
    Scale9Sprite* Scale9Sprite::create(const std::string& filename)
    {
        Scale9Sprite *sprite = new (std::nothrow) Scale9Sprite();
        if (sprite && sprite->initWithFile(filename))
        {
            sprite->autorelease();
            return sprite;
        }
        CC_SAFE_DELETE(sprite);
        return nullptr;
    }
    
    Scale9Sprite* Scale9Sprite::createWithSpriteFrame(SpriteFrame *spriteFrame)
    {
        Scale9Sprite *sprite = new (std::nothrow) Scale9Sprite();
        if (sprite && spriteFrame && sprite->initWithSpriteFrame(spriteFrame))
        {
            sprite->autorelease();
            return sprite;
        }
        CC_SAFE_DELETE(sprite);
        return nullptr;
    }
    
    Scale9Sprite* Scale9Sprite::createWithSpriteFrameName(const std::string& spriteFrameName)
    {
        SpriteFrame *frame = SpriteFrameCache::getInstance()->getSpriteFrameByName(spriteFrameName);
        
#if COCOS2D_DEBUG > 0
        char msg[256] = {0};
        sprintf(msg, "Invalid spriteFrameName: %s", spriteFrameName.c_str());
        CCASSERT(frame != nullptr, msg);
#endif
        
        return createWithSpriteFrame(frame);
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
    
    bool Scale9Sprite::initWithSpriteFrameName(const std::string& spriteFrameName,
                                         const Rect& capInsets)
    {
        CCASSERT(spriteFrameName.size() > 0, "Invalid spriteFrameName");
        
        SpriteFrame *frame = SpriteFrameCache::getInstance()->getSpriteFrameByName(spriteFrameName);
        return initWithSpriteFrame(frame, capInsets);
    }
    
    bool Scale9Sprite::initWithSpriteFrame(SpriteFrame* spriteFrame,
                                     const Rect& capInsets)
    {
        CCASSERT(spriteFrame != nullptr, "spriteFrame can't be nullptr!");
        
        bool bRet = initWithTexture(spriteFrame->getTexture(), spriteFrame->getRect());
        setSpriteFrame(spriteFrame);
        setCapInsets(capInsets);
        
        return bRet;
    }
    
    bool Scale9Sprite::initWithFile(const Rect& capInsets, const std::string& file)
    {
        bool pReturn = this->initWithFile(file, Rect::ZERO, capInsets);
        return pReturn;
    }
    
    
    bool Scale9Sprite::initWithFile(const std::string& filename, const Rect& rect,  const Rect& capInsets)
    {
        CCASSERT(filename.size()>0, "Invalid filename");
        
        Texture2D *texture = Director::getInstance()->getTextureCache()->addImage(filename);
        if (texture)
        {
            
            bool ret = initWithTexture(texture, rect);
            this->setCapInsets(capInsets);
            return ret;
        }
        
        // don't release here.
        // when load texture failed, it's better to get a "transparent" sprite then a crashed program
        // this->release();
        return false;
    }
    
    Scale9Sprite::Scale9Sprite()
    {
        this->setType(Type::Sliced);
    }
    
    Scale9Sprite::~Scale9Sprite()
    {
        
    }
    
    void Scale9Sprite::setScale9Enabled(bool enabled)
    {
        if(enabled)
        {
            this->setType(Type::Sliced);
        }
        else
        {
            this->setType(Type::Simple);
        }
    }
    
    bool Scale9Sprite::isScale9Enabled()const
    {
        return _type == Type::Sliced;
    }
    
    Scale9Sprite* Scale9Sprite::getSprite()
    {
        return this;
    }
    
    Size Scale9Sprite::getPreferredSize()const
    {
        return this->_preferredSize;
    }
    
    void Scale9Sprite::setPreferredSize(const cocos2d::Size &size)
    {
        Sprite::setContentSize(size);
    }
    
    Scale9Sprite* Scale9Sprite::resizableSpriteWithCapInsets(const Rect& capInsets) const
    {
        Scale9Sprite* pReturn = new (std::nothrow) Scale9Sprite();
        if ( pReturn && pReturn->initWithTexture(_texture))
        {
            pReturn->setCapInsets(capInsets);
            pReturn->autorelease();
            return pReturn;
        }
        CC_SAFE_DELETE(pReturn);
        return NULL;
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
        // updateBlendFunc(sprite?sprite->getTexture():nullptr);
        
        this->setSpriteFrame(sprite->getSpriteFrame());
        _offsetPosition = offset;
        this->setTextureRect(textureRect, rotated, originalSize);
        this->setCapInsets(capInsets);
        
        //change texture should reset program state.
        this->setState(_brightState);
        return true;
    }
    
    void Scale9Sprite::setSpriteFrame(SpriteFrame * spriteFrame, const Rect& capInsets)
    {
        this->setSpriteFrame(spriteFrame);
        this->setCapInsets(capInsets);
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

}

NS_CC_END