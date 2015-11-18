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
        , _scale9Image(nullptr)
        , _scale9Enabled(true)
        , _insetLeft(0)
        , _insetTop(0)
        , _insetRight(0)
        , _insetBottom(0)
        ,_flippedX(false)
        ,_flippedY(false)
        ,_isPatch9(false)
        ,_brightState(State::NORMAL)
        ,_nonSliceSpriteAnchor(Vec2::ANCHOR_MIDDLE)
        ,_sliceVertices(nullptr)
        ,_sliceIndices(nullptr)
        ,_sliceSpriteDirty(false)
        ,_renderingType(RenderingType::SLICE)
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
        bool ret = true;
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

            ret = this->updateWithSprite(sprite,
                                         rect,
                                         rotated,
                                         offset,
                                         originalSize,
                                         actualCapInsets);
        }

        return ret;
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
        CC_SAFE_DELETE_ARRAY(_sliceIndices);
        CC_SAFE_DELETE_ARRAY(_sliceVertices);
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
        else
        {
            CC_SAFE_RELEASE_NULL(_scale9Image);
        }

        if (!_scale9Image)
        {
            return false;
        }

        Rect rect(textureRect);
        Size size(originalSize);
        
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
        _spriteFrameRotated = rotated;
        _originalSize = size;
        _preferredSize = size;

        _capInsetsInternal = capInsets;

        if (_scale9Enabled)
        {
            _scale9Image->setAnchorPoint(Vec2::ZERO);
            _scale9Image->setPosition(Vec2::ZERO);
            _sliceSpriteDirty = true;
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
    
    void Scale9Sprite::configureSimpleModeRendering()
    {
        this->setInsetTop(0);
        this->setInsetBottom(0);
        this->setInsetLeft(0);
        this->setInsetRight(0);
    }

    void Scale9Sprite::createSlicedSprites()
    {
        //todo create sliced sprite
        if (_scale9Enabled)
        {
            Texture2D *tex = _scale9Image ? _scale9Image->getTexture() : nullptr;

            if (tex == nullptr)
            {
                return;
            }
            
            if (_renderingType == RenderingType::SIMPLE)
            {
                this->configureSimpleModeRendering();
            }

            auto capInsets = CC_RECT_POINTS_TO_PIXELS(_capInsetsInternal);
            auto textureRect = CC_RECT_POINTS_TO_PIXELS(_spriteRect);
            auto spriteRectSize = CC_SIZE_POINTS_TO_PIXELS(_originalSize);

            //handle .9.png
            if (_isPatch9)
            {
                spriteRectSize = Size(spriteRectSize.width - 2, spriteRectSize.height-2);
            }


            if(capInsets.equals(Rect::ZERO))
            {
                capInsets = Rect(spriteRectSize.width/3, spriteRectSize.height/3,
                                 spriteRectSize.width/3, spriteRectSize.height/3);
            }

            auto uv = this->calculateUV(tex, capInsets, spriteRectSize);
            auto vertices = this->calculateVertices(capInsets, spriteRectSize);
            auto triangles = this->calculateTriangles(uv, vertices);

            _scale9Image->getPolygonInfo().setTriangles(triangles);
        }
    }

    void Scale9Sprite::setContentSize(const Size &size)
    {
        if (_contentSize.equals(size))
        {
            return;
        }
        Node::setContentSize(size);
        _preferredSize = size;
        _sliceSpriteDirty = true;
        this->adjustNoneScale9ImagePosition();
    }

    Scale9Sprite* Scale9Sprite::resizableSpriteWithCapInsets(const Rect& capInsets) const
    {
        Scale9Sprite* pReturn = new (std::nothrow) Scale9Sprite();
        if ( pReturn && pReturn->init(_scale9Image,
                                      _spriteRect,
                                      _spriteFrameRotated,
                                      Vec2::ZERO,
                                      _originalSize,
                                      capInsets) )
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

        _brightState = state;
    }

/** sets the opacity.
    @warning If the texture has premultiplied alpha then, the R, G and B channels will be modifed.
    Values goes from 0 to 255, where 255 means fully opaque.
*/



    void Scale9Sprite::updateCapInset()
    {
        Rect insets;
        insets = Rect(_insetLeft,
                      _insetTop,
                      _originalSize.width-_insetLeft-_insetRight,
                      _originalSize.height-_insetTop-_insetBottom);
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
    }


    void Scale9Sprite::setCapInsets(const Rect& capInsets)
    {
        Size contentSize = this->_contentSize;
        this->updateWithSprite(this->_scale9Image,
                               _spriteRect,
                               _spriteFrameRotated,
                               Vec2::ZERO,
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
        if (_scale9Enabled && _sliceSpriteDirty) {
            this->createSlicedSprites();
            _sliceSpriteDirty = false;
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

        sortAllChildren();

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

        if (_scale9Image && _scale9Image->getLocalZOrder() < 0 )
        {
            _scale9Image->visit(renderer, _modelViewTransform, flags);
        }
        

        //
        // draw self
        //
        if (isVisitableByVisitingCamera())
            this->draw(renderer, _modelViewTransform, flags);

        //
        // draw children and protectedChildren zOrder >= 0
        //
        if (_scale9Image && _scale9Image->getLocalZOrder() >= 0 )
        {
            _scale9Image->visit(renderer, _modelViewTransform, flags);
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
        return _capInsetsInternal;
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

        //we must invalide the transform when toggling scale9enabled
        _transformUpdated = _transformDirty = _inverseDirty = true;

        if (_scale9Enabled)
        {
            if (_scale9Image)
            {
                this->updateWithSprite(this->_scale9Image,
                                       _spriteRect,
                                       _spriteFrameRotated,
                                       Vec2::ZERO,
                                       _originalSize,
                                       _capInsetsInternal);
            }
        }
        else
        {
            if (_scale9Image)
            {
                auto quad = _scale9Image->getQuad();
                PolygonInfo polyInfo;
                polyInfo.setQuad(&quad);
                _scale9Image->setPolygonInfo(polyInfo);
            }
          
        }
        this->adjustNoneScale9ImagePosition();
    }

    bool Scale9Sprite::isScale9Enabled() const
    {
        return _scale9Enabled;
    }
    
    void Scale9Sprite::setAnchorPoint(const cocos2d::Vec2 &position)
    {
        Node::setAnchorPoint(position);
        if (!_scale9Enabled)
        {
            if (_scale9Image)
            {
                _nonSliceSpriteAnchor = position;
                _scale9Image->setAnchorPoint(position);
                this->adjustNoneScale9ImagePosition();
            }
        }
    }

    void Scale9Sprite::adjustNoneScale9ImagePosition()
    {
        if (_scale9Image)
        {
            if (!_scale9Enabled) {
                _scale9Image->setAnchorPoint(_nonSliceSpriteAnchor);
                _scale9Image->setPosition(_contentSize.width * _scale9Image->getAnchorPoint().x,
                                          _contentSize.height * _scale9Image->getAnchorPoint().y);

            }
        }
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
    std::vector<Vec2> Scale9Sprite::calculateUV(Texture2D *tex,
                                               const Rect& capInsets,
                                               const Size& spriteRectSize)
    {
        auto atlasWidth = tex->getPixelsWide();
        auto atlasHeight = tex->getPixelsHigh();

        //caculate texture coordinate
        float leftWidth = 0, centerWidth = 0, rightWidth = 0;
        float topHeight = 0, centerHeight = 0, bottomHeight = 0;

        if (_spriteFrameRotated)
        {
            rightWidth = capInsets.origin.y;
            centerWidth = capInsets.size.height;
            leftWidth = spriteRectSize.height - centerWidth - rightWidth;

            topHeight = capInsets.origin.x;
            centerHeight = capInsets.size.width;
            bottomHeight = spriteRectSize.width - (topHeight + centerHeight);
        }
        else
        {
            leftWidth = capInsets.origin.x;
            centerWidth = capInsets.size.width;
            rightWidth = spriteRectSize.width - (leftWidth + centerWidth);

            topHeight = capInsets.origin.y;
            centerHeight = capInsets.size.height;
            bottomHeight =spriteRectSize.height - (topHeight + centerHeight);
        }

        auto textureRect = CC_RECT_POINTS_TO_PIXELS(_spriteRect);
        //handle .9.png
        if (_isPatch9)
        {
            //This magic number is used to avoiding artifact with .9.png format.
            float offset = 1.3f;
            textureRect = Rect(textureRect.origin.x +  offset,
                               textureRect.origin.y +  offset,
                               textureRect.size.width - 2,
                               textureRect.size.height - 2);
        }

        //uv computation should take spritesheet into account.
        float u0, u1, u2, u3;
        float v0, v1, v2, v3;
        if (_spriteFrameRotated)
        {
            u0 = textureRect.origin.x / atlasWidth;
            u1 = (leftWidth + textureRect.origin.x) / atlasWidth;
            u2 = (leftWidth + centerWidth + textureRect.origin.x) / atlasWidth;
            u3 = (textureRect.origin.x + textureRect.size.height) / atlasWidth;

            v3 = textureRect.origin.y / atlasHeight;
            v2 = (topHeight + textureRect.origin.y) / atlasHeight;
            v1 = (topHeight + centerHeight + textureRect.origin.y) / atlasHeight;
            v0 = (textureRect.origin.y + textureRect.size.width) / atlasHeight;
        }
        else
        {
            u0 = textureRect.origin.x / atlasWidth;
            u1 = (leftWidth + textureRect.origin.x) / atlasWidth;
            u2 = (leftWidth + centerWidth + textureRect.origin.x) / atlasWidth;
            u3 = (textureRect.origin.x + textureRect.size.width) / atlasWidth;

            v0 = textureRect.origin.y / atlasHeight;
            v1 = (topHeight + textureRect.origin.y) / atlasHeight;
            v2 = (topHeight + centerHeight + textureRect.origin.y) / atlasHeight;
            v3 = (textureRect.origin.y + textureRect.size.height) / atlasHeight;
        }

        
        std::vector<Vec2> uvCoordinates;
        if (_renderingType == RenderingType::SIMPLE)
        {
            uvCoordinates = {Vec2(u0,v3), Vec2(u3,v0)};
        }
        else
        {
            uvCoordinates = {Vec2(u0,v3), Vec2(u1,v2), Vec2(u2,v1), Vec2(u3,v0)};
        }

        return uvCoordinates;
    }

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
    std::vector<Vec2> Scale9Sprite::calculateVertices(const Rect& capInsets,
                                                     const Size& spriteRectSize)
    {
        float leftWidth = 0, centerWidth = 0, rightWidth = 0;
        float topHeight = 0, centerHeight = 0, bottomHeight = 0;

        leftWidth = capInsets.origin.x;
        centerWidth = capInsets.size.width;
        rightWidth = spriteRectSize.width - (leftWidth + centerWidth);

        topHeight = capInsets.origin.y;
        centerHeight = capInsets.size.height;
        bottomHeight = spriteRectSize.height - (topHeight + centerHeight);


        leftWidth = leftWidth / CC_CONTENT_SCALE_FACTOR();
        rightWidth = rightWidth / CC_CONTENT_SCALE_FACTOR();
        topHeight = topHeight / CC_CONTENT_SCALE_FACTOR();
        bottomHeight = bottomHeight / CC_CONTENT_SCALE_FACTOR();
        float sizableWidth = _preferredSize.width - leftWidth - rightWidth;
        float sizableHeight = _preferredSize.height - topHeight - bottomHeight;
        float x0,x1,x2,x3;
        float y0,y1,y2,y3;
        if(sizableWidth >= 0)
        {
            x0 = 0;
            x1 = leftWidth;
            x2 = leftWidth + sizableWidth;
            x3 = _preferredSize.width;
        }
        else
        {
            float xScale = _preferredSize.width / (leftWidth + rightWidth);
            x0 = 0;
            x1 = x2 = leftWidth * xScale;
            x3 = (leftWidth + rightWidth) * xScale;
        }

        if(sizableHeight >= 0)
        {
            y0 = 0;
            y1 = bottomHeight;
            y2 = bottomHeight + sizableHeight;
            y3 = _preferredSize.height;
        }
        else
        {
            float yScale = _preferredSize.height / (topHeight + bottomHeight);
            y0 = 0;
            y1 = y2= bottomHeight * yScale;
            y3 = (bottomHeight + topHeight) * yScale;
        }

        std::vector<Vec2> vertices;
        
        if (_renderingType == RenderingType::SIMPLE)
        {
            vertices = {Vec2(x0,y0), Vec2(x3,y3)};
        }
        else
        {
           vertices = {Vec2(x0,y0), Vec2(x1,y1), Vec2(x2,y2), Vec2(x3,y3)};
        }
        return vertices;
    }

    TrianglesCommand::Triangles Scale9Sprite::calculateTriangles(const std::vector<Vec2>& uv,
                                                                const std::vector<Vec2>& vertices)
    {
        const unsigned short slicedTotalVertexCount = powf(uv.size(),2);
        const unsigned short slicedTotalIndices = 6 * powf(uv.size() -1, 2);
        CC_SAFE_DELETE_ARRAY(_sliceVertices);
        CC_SAFE_DELETE_ARRAY(_sliceIndices);

        _sliceVertices = new V3F_C4B_T2F[slicedTotalVertexCount];
        _sliceIndices = new unsigned short[slicedTotalIndices];

        unsigned short indicesStart = 0;
        const unsigned short indicesOffset = 6;
        const unsigned short sliceQuadIndices[] = {4,0,5, 1,5,0};
        const unsigned short simpleQuadIndices[] = {0,1,2, 3,2,1};
        

        Color4B color4 = Color4B(_scale9Image->getDisplayedColor());
        int vertexCount = (int)(vertices.size() - 1);

        for (int j = 0; j <= vertexCount; ++j)
        {
            for (int i = 0; i <= vertexCount; ++i)
            {
                V3F_C4B_T2F vertextData;
                vertextData.vertices.x = vertices[i].x;
                vertextData.vertices.y = vertices[j].y;

                if (_spriteFrameRotated)
                {
                    vertextData.texCoords.u = uv[j].x;
                    vertextData.texCoords.v = uv[i].y;
                }
                else
                {
                    vertextData.texCoords.u = uv[i].x;
                    vertextData.texCoords.v = uv[j].y;
                }

                vertextData.colors = color4;
                
                //if slice mode
                if (_renderingType == RenderingType::SLICE)
                {
                    memcpy(_sliceVertices + i + j * 4, &vertextData, sizeof(V3F_C4B_T2F));
                }
                else
                {
                    memcpy(_sliceVertices + i + j * 2, &vertextData, sizeof(V3F_C4B_T2F));
                }
            }
        }
        
        if (_renderingType == RenderingType::SLICE)
        {
            for (int j = 0; j <= vertexCount; ++j)
            {
                for (int i = 0; i <= vertexCount; ++i)
                {
                    if (i < 3 && j < 3)
                    {
                        memcpy(_sliceIndices + indicesStart, sliceQuadIndices, indicesOffset * sizeof(unsigned short));
                        
                        for (int k = 0; k  < indicesOffset; ++k)
                        {
                            unsigned short actualIndex = (i  + j * 3) * indicesOffset;
                            _sliceIndices[k + actualIndex] = _sliceIndices[k + actualIndex] + j * 4 + i;
                        }
                        indicesStart = indicesStart + indicesOffset;
                    }
                    
                }
            }
        }
        
        if (_renderingType == RenderingType::SIMPLE)
        {
            memcpy(_sliceIndices, simpleQuadIndices, indicesOffset * sizeof(unsigned short));
        }

        TrianglesCommand::Triangles triangles;
        triangles.vertCount = slicedTotalVertexCount;
        triangles.indexCount = slicedTotalIndices;
        triangles.verts = _sliceVertices;
        triangles.indices = _sliceIndices;

        return triangles;
    }
    
    void Scale9Sprite::setRenderingType(cocos2d::ui::Scale9Sprite::RenderingType type)
    {
        if (_renderingType == type)
        {
            return;
        }
        _renderingType = type;
        _sliceSpriteDirty = true;
    }
    
    Scale9Sprite::RenderingType Scale9Sprite::getRenderingType()const
    {
        return _renderingType;
    }

    void Scale9Sprite::resetRender()
    {
        // Release old sprites
        this->cleanupSlicedSprites();

        CC_SAFE_RELEASE_NULL(this->_scale9Image);
    }

}}
