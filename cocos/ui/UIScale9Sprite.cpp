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
#include "2d/CCSpriteBatchNode.h"
#include "renderer/CCRenderer.h"


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
    
    Scale9Sprite* Scale9Sprite::create(const Rect& capInsets, const std::string& file)
    {
        Scale9Sprite *sprite = new (std::nothrow) Scale9Sprite();
        if (sprite && sprite->initWithFile(file))
        {
            sprite->setCapInsets(capInsets);
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
    
    bool Scale9Sprite::initWithBatchNode(cocos2d::SpriteBatchNode *batchnode,
                                               const cocos2d::Rect &rect,
                                               bool rotated,
                                               const cocos2d::Rect &capInsets)
    {
        Sprite *sprite = Scale9Sprite::createWithTexture(batchnode->getTexture());
        return updateWithSprite(sprite, rect, false, capInsets);
    }
    
    bool Scale9Sprite::initWithBatchNode(cocos2d::SpriteBatchNode *batchnode,
                                               const cocos2d::Rect &rect,
                                               const cocos2d::Rect &capInsets)
    {
        auto sprite = Scale9Sprite::createWithTexture(batchnode->getTexture());
        return updateWithSprite(sprite, rect, false, capInsets);
    }
    
    bool Scale9Sprite::updateWithBatchNode(cocos2d::SpriteBatchNode *batchnode,
                                                 const cocos2d::Rect &originalRect,
                                                 bool rotated,
                                                 const cocos2d::Rect &capInsets)
    {
        Sprite *sprite = Scale9Sprite::createWithTexture(batchnode->getTexture());
        return this->updateWithSprite(sprite,
                                      originalRect,
                                      rotated,
                                      Vec2::ZERO,
                                      originalRect.size,
                                      capInsets);
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
    :_type(Type::Simple)
    , _insetLeft(0.0f)
    , _insetRight(0.0f)
    , _insetBottom(0.0f)
    , _insetTop(0.0f)
    , _brightState(State::NORMAL)
    , _sliceVertices(nullptr)
    , _sliceIndices(nullptr)
    , _isPatch9(false)
    {
        this->setType(Type::Sliced);
    }
    
    Scale9Sprite::~Scale9Sprite()
    {
        CC_SAFE_DELETE_ARRAY(_sliceIndices);
        CC_SAFE_DELETE_ARRAY(_sliceVertices);
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
        Scale9Sprite::setContentSize(size);
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

    void Scale9Sprite::setType(Type type)
    {
        if (_type == type)
        {
            return;
        }

        this->_type = type;
        if (type == Type::Simple)
        {
            _polyInfo.setQuad(&this->_quad);
            Node::setContentSize(_originalSize);
        }
        else
        {
            this->setContentSize(_preferredSize);
        }
    }

    Scale9Sprite::Type Scale9Sprite::getType()const
    {
        return this->_type;
    }


    void Scale9Sprite::setCapInsets(const cocos2d::Rect &rect)
    {
        if (rect.equals(_capInsetsInternal))
        {
            return;
        }
        float originalWidthInPixel = _originalSize.width;
        float originalHeightInPixel = _originalSize.height;
        this->_insetLeft = rect.origin.x;
        this->_insetTop = rect.origin.y;
        this->_insetRight = originalWidthInPixel - this->_insetLeft - rect.size.width;
        this->_insetBottom = originalHeightInPixel - this->_insetTop - rect.size.height;
        _capInsetsInternal = rect;

        this->caculatePolygonInfo();
    }

    Rect Scale9Sprite::getCapInsets()const
    {
        return _capInsetsInternal;
    }

    Scale9Sprite::State Scale9Sprite::getState()const
    {
        return this->_brightState;
    }

    void Scale9Sprite::setState(Scale9Sprite::State state)
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

        this->setGLProgramState(glState);
        _brightState = state;
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

    void Scale9Sprite::updateCapInset()
    {
        //capInset are in points not pixels
        float originalWidthInPixel = _originalSize.width;
        float originalHeightInPixel = _originalSize.height;
        Rect insets = Rect(_insetLeft,
                           _insetTop,
                           originalWidthInPixel - _insetLeft-_insetRight,
                           originalHeightInPixel - _insetTop-_insetBottom);
        this->setCapInsets(insets);
    }
 
    void Scale9Sprite::caculatePolygonInfo()
    {
        if (_type == Type::Sliced)
        {
            Texture2D *tex = _batchNode ? _textureAtlas->getTexture() : _texture;

            if (tex == nullptr || _isDefaultTexture)
            {
                return;
            }
            
            if (_texture->isContain9PatchInfo())
            {
                auto& parsedCapInset = _texture->getSpriteFrameCapInset(this->getSpriteFrame());
                if(!parsedCapInset.equals(Rect::ZERO))
                {
                    this->_isPatch9 = true;
                    _capInsetsInternal = parsedCapInset;
                }
            }
            
            auto capInsets = CC_RECT_POINTS_TO_PIXELS(_capInsetsInternal);
            auto textureRect = CC_RECT_POINTS_TO_PIXELS(_rect);
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

            auto uv = this->caculateUV(tex, capInsets, spriteRectSize);
            auto vertices = this->caculateVertices(capInsets, spriteRectSize);
            auto triangles = this->caculateTriangles(uv, vertices);

            this->_polyInfo.setTriangles(triangles);
        }
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
    std::vector<Vec2> Scale9Sprite::caculateUV(Texture2D *tex,
                                               const Rect& capInsets,
                                               const Size& spriteRectSize)
    {
        auto atlasWidth = tex->getPixelsWide();
        auto atlasHeight = tex->getPixelsHigh();

        //caculate texture coordinate
        float leftWidth = 0, centerWidth = 0, rightWidth = 0;
        float topHeight = 0, centerHeight = 0, bottomHeight = 0;
        
        if (_rectRotated)
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

        auto textureRect = CC_RECT_POINTS_TO_PIXELS(_rect);
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
        if (_rectRotated)
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
        
        std::vector<Vec2> uvCoordinates = {Vec2(u0,v3), Vec2(u1,v2), Vec2(u2,v1), Vec2(u3,v0)};
        
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
    std::vector<Vec2> Scale9Sprite::caculateVertices(const Rect& capInsets,
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
        
        std::vector<Vec2> vertices = {Vec2(x0,y0), Vec2(x1,y1), Vec2(x2,y2), Vec2(x3,y3)};
        return vertices;
    }

    TrianglesCommand::Triangles Scale9Sprite::caculateTriangles(const std::vector<Vec2>& uv,
                                                                const std::vector<Vec2>& vertices)
    {
        const unsigned short slicedTotalVertexCount = 16;
        const unsigned short slicedTotalIndices = 54;
        CC_SAFE_DELETE_ARRAY(_sliceVertices);
        CC_SAFE_DELETE_ARRAY(_sliceIndices);
        
        _sliceVertices = new V3F_C4B_T2F[slicedTotalVertexCount];
        _sliceIndices = new unsigned short[slicedTotalIndices];
        
        unsigned short indicesStart = 0;
        const unsigned short indicesOffset = 6;
        const unsigned short quadIndices[]={4,0,5, 1,5,0};
        
        Color4B color4( _displayedColor.r,
                       _displayedColor.g,
                       _displayedColor.b,
                       _displayedOpacity );
        
        // special opacity for premultiplied textures
        if (_opacityModifyRGB)
        {
            color4.r *= _displayedOpacity/255.0f;
            color4.g *= _displayedOpacity/255.0f;
            color4.b *= _displayedOpacity/255.0f;
        }
        
        for (int j = 0; j <= 3; ++j)
        {
            for (int i = 0; i <= 3; ++i)
            {
                V3F_C4B_T2F vertextData;
                vertextData.vertices.x = vertices[i].x;
                vertextData.vertices.y = vertices[j].y;
                
                if (_rectRotated)
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
                
                if (i < 3 && j < 3)
                {
                    memcpy(_sliceIndices + indicesStart, quadIndices, indicesOffset * sizeof(unsigned short));
                    
                    for (int k = 0; k  < indicesOffset; ++k)
                    {
                        unsigned short actualIndex = (i  + j * 3) * indicesOffset;
                        _sliceIndices[k + actualIndex] = _sliceIndices[k + actualIndex] + j * 4 + i;
                    }
                    indicesStart = indicesStart + indicesOffset;
                }
                
                memcpy(_sliceVertices + i + j * 4, &vertextData, sizeof(V3F_C4B_T2F));
            }
        }
        
        TrianglesCommand::Triangles triangles;
        triangles.vertCount = slicedTotalVertexCount;
        triangles.indexCount = slicedTotalIndices;
        triangles.verts = _sliceVertices;
        triangles.indices = _sliceIndices;
        
        return triangles;
    }

    void Scale9Sprite::setContentSize(const cocos2d::Size &size)
    {
        Node::setContentSize(size);
        
        _preferredSize = size;
        this->caculatePolygonInfo();
    }
    
    const Size& Scale9Sprite::getContentSize()const
    {
        if(_type == Type::Sliced)
        {
            return _preferredSize;
        }
        return _contentSize;
    }

}

NS_CC_END





