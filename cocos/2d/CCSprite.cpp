/****************************************************************************
Copyright (c) 2008-2010 Ricardo Quesada
Copyright (c) 2010-2012 cocos2d-x.org
Copyright (c) 2011      Zynga Inc.
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

#include "2d/CCSprite.h"

#include <algorithm>

#include "2d/CCSpriteBatchNode.h"
#include "2d/CCAnimationCache.h"
#include "2d/CCSpriteFrame.h"
#include "2d/CCSpriteFrameCache.h"
#include "renderer/CCTextureCache.h"
#include "renderer/CCTexture2D.h"
#include "renderer/CCRenderer.h"
#include "base/CCDirector.h"
#include "2d/CCCamera.h"

#include "deprecated/CCString.h"

NS_CC_BEGIN

// MARK: create, init, dealloc
Sprite* Sprite::createWithTexture(Texture2D *texture)
{
    Sprite *sprite = new (std::nothrow) Sprite();
    if (sprite && sprite->initWithTexture(texture))
    {
        sprite->autorelease();
        return sprite;
    }
    CC_SAFE_DELETE(sprite);
    return nullptr;
}

Sprite* Sprite::createWithTexture(Texture2D *texture, const Rect& rect, bool rotated)
{
    Sprite *sprite = new (std::nothrow) Sprite();
    if (sprite && sprite->initWithTexture(texture, rect, rotated))
    {
        sprite->autorelease();
        return sprite;
    }
    CC_SAFE_DELETE(sprite);
    return nullptr;
}

Sprite* Sprite::create(const std::string& filename)
{
    Sprite *sprite = new (std::nothrow) Sprite();
    if (sprite && sprite->initWithFile(filename))
    {
        sprite->autorelease();
        return sprite;
    }
    CC_SAFE_DELETE(sprite);
    return nullptr;
}

Sprite* Sprite::create(const PolygonInfo& info)
{
    Sprite *sprite = new (std::nothrow) Sprite();
    if(sprite && sprite->initWithPolygon(info))
    {
        sprite->autorelease();
        return sprite;
    }
    CC_SAFE_DELETE(sprite);
    return nullptr;
}

Sprite* Sprite::create(const std::string& filename, const Rect& rect)
{
    Sprite *sprite = new (std::nothrow) Sprite();
    if (sprite && sprite->initWithFile(filename, rect))
    {
        sprite->autorelease();
        return sprite;
    }
    CC_SAFE_DELETE(sprite);
    return nullptr;
}

Sprite* Sprite::createWithSpriteFrame(SpriteFrame *spriteFrame)
{
    Sprite *sprite = new (std::nothrow) Sprite();
    if (sprite && spriteFrame && sprite->initWithSpriteFrame(spriteFrame))
    {
        sprite->autorelease();
        return sprite;
    }
    CC_SAFE_DELETE(sprite);
    return nullptr;
}

Sprite* Sprite::createWithSpriteFrameName(const std::string& spriteFrameName)
{
    SpriteFrame *frame = SpriteFrameCache::getInstance()->getSpriteFrameByName(spriteFrameName);

#if COCOS2D_DEBUG > 0
    char msg[256] = {0};
    sprintf(msg, "Invalid spriteFrameName: %s", spriteFrameName.c_str());
    CCASSERT(frame != nullptr, msg);
#endif

    return createWithSpriteFrame(frame);
}

Sprite* Sprite::create()
{
    Sprite *sprite = new (std::nothrow) Sprite();
    if (sprite && sprite->init())
    {
        sprite->autorelease();
        return sprite;
    }
    CC_SAFE_DELETE(sprite);
    return nullptr;
}

bool Sprite::init(void)
{
    return initWithTexture(nullptr, Rect::ZERO );
}

bool Sprite::initWithTexture(Texture2D *texture)
{
    CCASSERT(texture != nullptr, "Invalid texture for sprite");

    Rect rect = Rect::ZERO;
    rect.size = texture->getContentSize();

    return initWithTexture(texture, rect);
}

bool Sprite::initWithTexture(Texture2D *texture, const Rect& rect)
{
    return initWithTexture(texture, rect, false);
}

bool Sprite::initWithFile(const std::string& filename)
{
    CCASSERT(filename.size()>0, "Invalid filename for sprite");
    
    Texture2D *texture = Director::getInstance()->getTextureCache()->addImage(filename);
    if (texture)
    {
        Rect rect = Rect::ZERO;
        rect.size = texture->getContentSize();
        return initWithTexture(texture, rect);
    }
    
    // don't release here.
    // when load texture failed, it's better to get a "transparent" sprite then a crashed program
    // this->release();
    return false;
}


bool Sprite::initWithFile(const std::string &filename, const Rect& rect)
{
    CCASSERT(filename.size()>0, "Invalid filename");
    
    Texture2D *texture = Director::getInstance()->getTextureCache()->addImage(filename);
    if (texture)
    {
        
        bool ret = initWithTexture(texture, rect);
        return ret;
    }
    
    // don't release here.
    // when load texture failed, it's better to get a "transparent" sprite then a crashed program
    // this->release();
    return false;
}

bool Sprite::initWithSpriteFrameName(const std::string& spriteFrameName)
{
    CCASSERT(spriteFrameName.size() > 0, "Invalid spriteFrameName");
    
    SpriteFrame *frame = SpriteFrameCache::getInstance()->getSpriteFrameByName(spriteFrameName);
    return initWithSpriteFrame(frame);
}



bool Sprite::initWithSpriteFrame(SpriteFrame *spriteFrame)
{
    CCASSERT(spriteFrame != nullptr, "spriteFrame can't be nullptr!");
    
    bool bRet = initWithTexture(spriteFrame->getTexture(), spriteFrame->getRect());
    setSpriteFrame(spriteFrame);
    
    return bRet;

}

bool Sprite::initWithPolygon(const cocos2d::PolygonInfo &info)
{
    Texture2D *texture = Director::getInstance()->getTextureCache()->addImage(info.filename);
    bool res = false;
    if(initWithTexture(texture))
    {
        _polyInfo = info;
        setContentSize(_polyInfo.rect.size/Director::getInstance()->getContentScaleFactor());
        res = true;
    }
    return res;
}

// designated initializer
bool Sprite::initWithTexture(Texture2D *texture, const Rect& rect, bool rotated)
{
    bool result;
    if (Node::init())
    {
        _batchNode = nullptr;

        _recursiveDirty = false;
        setDirty(false);

        _opacityModifyRGB = true;

        _blendFunc = BlendFunc::ALPHA_PREMULTIPLIED;

        _flippedX = _flippedY = false;

        // default transform anchor: center
        setAnchorPoint(Vec2(0.5f, 0.5f));

        // zwoptex default values
        _offsetPosition.setZero();

        // clean the Quad
        memset(&_quad, 0, sizeof(_quad));

        // Atlas: Color
        _quad.bl.colors = Color4B::WHITE;
        _quad.br.colors = Color4B::WHITE;
        _quad.tl.colors = Color4B::WHITE;
        _quad.tr.colors = Color4B::WHITE;

        // shader state
        setGLProgramState(GLProgramState::getOrCreateWithGLProgramName(GLProgram::SHADER_NAME_POSITION_TEXTURE_COLOR_NO_MVP));

        // update texture (calls updateBlendFunc)
        setTexture(texture);
        setTextureRect(rect, rotated, rect.size);

        // by default use "Self Render".
        // if the sprite is added to a batchnode, then it will automatically switch to "batchnode Render"
        setBatchNode(nullptr);
        result = true;
    }
    else
    {
        result = false;
    }
    _recursiveDirty = true;
    setDirty(true);
    return result;
}

Sprite::Sprite(void)
: _type(Type::Simple)
, _brightState(State::NORMAL)
, _capInsetsDirty(false)
, _isPatch9(false)
, _insetLeft(0.0f)
, _insetRight(0.0f)
, _insetTop(0.0f)
, _insetBottom(0.0f)
, _batchNode(nullptr)
, _textureAtlas(nullptr)
, _shouldBeHidden(false)
, _texture(nullptr)
, _spriteFrame(nullptr)
, _insideBounds(true)
, _sliceVertices(nullptr)
, _sliceIndices(nullptr)
, _isDefaultTexture(false)
{
#if CC_SPRITE_DEBUG_DRAW
    _debugDrawNode = DrawNode::create();
    addChild(_debugDrawNode);
#endif //CC_SPRITE_DEBUG_DRAW
}

Sprite::~Sprite(void)
{
    CC_SAFE_RELEASE(_spriteFrame);
    CC_SAFE_RELEASE(_texture);
    CC_SAFE_DELETE_ARRAY(_sliceIndices);
    CC_SAFE_DELETE_ARRAY(_sliceVertices);
}

/*
 * Texture methods
 */

/*
 * This array is the data of a white image with 2 by 2 dimension.
 * It's used for creating a default texture when sprite's texture is set to nullptr.
 * Supposing codes as follows:
 *
 *   auto sp = new (std::nothrow) Sprite();
 *   sp->init();  // Texture was set to nullptr, in order to make opacity and color to work correctly, we need to create a 2x2 white texture.
 *
 * The test is in "TestCpp/SpriteTest/Sprite without texture".
 */
static unsigned char cc_2x2_white_image[] = {
    // RGBA8888
    0xFF, 0xFF, 0xFF, 0xFF,
    0xFF, 0xFF, 0xFF, 0xFF,
    0xFF, 0xFF, 0xFF, 0xFF,
    0xFF, 0xFF, 0xFF, 0xFF
};

#define CC_2x2_WHITE_IMAGE_KEY  "/cc_2x2_white_image"

// MARK: texture
void Sprite::setTexture(const std::string &filename)
{
    Texture2D *texture = Director::getInstance()->getTextureCache()->addImage(filename);
    setTexture(texture);

    Rect rect = Rect::ZERO;
    if (texture)
        rect.size = texture->getContentSize();
    setTextureRect(rect);
}

void Sprite::setTexture(Texture2D *texture)
{
    // If batchnode, then texture id should be the same
    CCASSERT(! _batchNode || (texture &&  texture->getName() == _batchNode->getTexture()->getName()), "CCSprite: Batched sprites should use the same texture as the batchnode");
    // accept texture==nil as argument
    CCASSERT( !texture || dynamic_cast<Texture2D*>(texture), "setTexture expects a Texture2D. Invalid argument");
    _isDefaultTexture = false;
    if (texture == nullptr)
    {
        // Gets the texture by key firstly.
        texture = Director::getInstance()->getTextureCache()->getTextureForKey(CC_2x2_WHITE_IMAGE_KEY);

        // If texture wasn't in cache, create it from RAW data.
        if (texture == nullptr)
        {
            Image* image = new (std::nothrow) Image();
            bool isOK = image->initWithRawData(cc_2x2_white_image, sizeof(cc_2x2_white_image), 2, 2, 8);
            CC_UNUSED_PARAM(isOK);
            CCASSERT(isOK, "The 2x2 empty texture was created unsuccessfully.");

            texture = Director::getInstance()->getTextureCache()->addImage(image, CC_2x2_WHITE_IMAGE_KEY);
            CC_SAFE_RELEASE(image);
        }
    }
    //the originalSize is valid when sprite is not in atlas
    _originalSize = texture->getContentSize();
    
    auto  defaultTexture = Director::getInstance()->getTextureCache()->getTextureForKey(CC_2x2_WHITE_IMAGE_KEY);
    
    // If texture wasn't in cache, create it from RAW data.
    if (defaultTexture != nullptr)
    {
        GLuint defaultTextureName =  defaultTexture->getName();
        if (defaultTextureName == texture->getName())
        {
            _isDefaultTexture = true;
        }
    }

    if (!_batchNode && _texture != texture)
    {
        CC_SAFE_RETAIN(texture);
        CC_SAFE_RELEASE(_texture);
        _texture = texture;
        updateBlendFunc();
    }
}

Texture2D* Sprite::getTexture() const
{
    return _texture;
}

void Sprite::setTextureRect(const Rect& rect)
{
    setTextureRect(rect, false, rect.size);
}

void Sprite::setTextureRect(const Rect& rect, bool rotated, const Size& untrimmedSize)
{
    _rectRotated = rotated;

    setContentSize(untrimmedSize);
    setVertexRect(rect);
    setTextureCoords(rect);

    float relativeOffsetX = _unflippedOffsetPositionFromCenter.x;
    float relativeOffsetY = _unflippedOffsetPositionFromCenter.y;

    // issue #732
    if (_flippedX)
    {
        relativeOffsetX = -relativeOffsetX;
    }
    if (_flippedY)
    {
        relativeOffsetY = -relativeOffsetY;
    }

    _offsetPosition.x = relativeOffsetX + (_contentSize.width - _rect.size.width) / 2;
    _offsetPosition.y = relativeOffsetY + (_contentSize.height - _rect.size.height) / 2;

    // rendering using batch node
    if (_batchNode)
    {
        // update dirty_, don't update recursiveDirty_
        setDirty(true);
    }
    else
    {
        // self rendering

        // Atlas: Vertex
        float x1 = 0.0f + _offsetPosition.x;
        float y1 = 0.0f + _offsetPosition.y;
        float x2 = x1 + _rect.size.width;
        float y2 = y1 + _rect.size.height;

        // Don't update Z.
        _quad.bl.vertices.set(x1, y1, 0.0f);
        _quad.br.vertices.set(x2, y1, 0.0f);
        _quad.tl.vertices.set(x1, y2, 0.0f);
        _quad.tr.vertices.set(x2, y2, 0.0f);
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

    _polyInfo.setQuad(&_quad);
}

// override this method to generate "double scale" sprites
void Sprite::setVertexRect(const Rect& rect)
{
    _rect = rect;
}

void Sprite::setTextureCoords(Rect rect)
{
    rect = CC_RECT_POINTS_TO_PIXELS(rect);

    Texture2D *tex = _batchNode ? _textureAtlas->getTexture() : _texture;
    if (! tex)
    {
        return;
    }

    float atlasWidth = (float)tex->getPixelsWide();
    float atlasHeight = (float)tex->getPixelsHigh();

    float left, right, top, bottom;

    if (_rectRotated)
    {
#if CC_FIX_ARTIFACTS_BY_STRECHING_TEXEL
        left    = (2*rect.origin.x+1)/(2*atlasWidth);
        right   = left+(rect.size.height*2-2)/(2*atlasWidth);
        top     = (2*rect.origin.y+1)/(2*atlasHeight);
        bottom  = top+(rect.size.width*2-2)/(2*atlasHeight);
#else
        left    = rect.origin.x/atlasWidth;
        right   = (rect.origin.x+rect.size.height) / atlasWidth;
        top     = rect.origin.y/atlasHeight;
        bottom  = (rect.origin.y+rect.size.width) / atlasHeight;
#endif // CC_FIX_ARTIFACTS_BY_STRECHING_TEXEL

        if (_flippedX)
        {
            std::swap(top, bottom);
        }

        if (_flippedY)
        {
            std::swap(left, right);
        }

        _quad.bl.texCoords.u = left;
        _quad.bl.texCoords.v = top;
        _quad.br.texCoords.u = left;
        _quad.br.texCoords.v = bottom;
        _quad.tl.texCoords.u = right;
        _quad.tl.texCoords.v = top;
        _quad.tr.texCoords.u = right;
        _quad.tr.texCoords.v = bottom;
    }
    else
    {
#if CC_FIX_ARTIFACTS_BY_STRECHING_TEXEL
        left    = (2*rect.origin.x+1)/(2*atlasWidth);
        right    = left + (rect.size.width*2-2)/(2*atlasWidth);
        top        = (2*rect.origin.y+1)/(2*atlasHeight);
        bottom    = top + (rect.size.height*2-2)/(2*atlasHeight);
#else
        left    = rect.origin.x/atlasWidth;
        right    = (rect.origin.x + rect.size.width) / atlasWidth;
        top        = rect.origin.y/atlasHeight;
        bottom    = (rect.origin.y + rect.size.height) / atlasHeight;
#endif // ! CC_FIX_ARTIFACTS_BY_STRECHING_TEXEL

        if(_flippedX)
        {
            std::swap(left, right);
        }

        if(_flippedY)
        {
            std::swap(top, bottom);
        }

        _quad.bl.texCoords.u = left;
        _quad.bl.texCoords.v = bottom;
        _quad.br.texCoords.u = right;
        _quad.br.texCoords.v = bottom;
        _quad.tl.texCoords.u = left;
        _quad.tl.texCoords.v = top;
        _quad.tr.texCoords.u = right;
        _quad.tr.texCoords.v = top;
    }
}

// MARK: visit, draw, transform

void Sprite::updateTransform(void)
{
    CCASSERT(_batchNode, "updateTransform is only valid when Sprite is being rendered using an SpriteBatchNode");

    // recalculate matrix only if it is dirty
    if( isDirty() ) {

        // If it is not visible, or one of its ancestors is not visible, then do nothing:
        if( !_visible || ( _parent && _parent != _batchNode && static_cast<Sprite*>(_parent)->_shouldBeHidden) )
        {
            _quad.br.vertices.setZero();
            _quad.tl.vertices.setZero();
            _quad.tr.vertices.setZero();
            _quad.bl.vertices.setZero();
            _shouldBeHidden = true;
        }
        else
        {
            _shouldBeHidden = false;

            if( ! _parent || _parent == _batchNode )
            {
                _transformToBatch = getNodeToParentTransform();
            }
            else
            {
                CCASSERT( dynamic_cast<Sprite*>(_parent), "Logic error in Sprite. Parent must be a Sprite");
                const Mat4 &nodeToParent = getNodeToParentTransform();
                Mat4 &parentTransform = static_cast<Sprite*>(_parent)->_transformToBatch;
                _transformToBatch = parentTransform * nodeToParent;
            }

            //
            // calculate the Quad based on the Affine Matrix
            //

            Size &size = _rect.size;

            float x1 = _offsetPosition.x;
            float y1 = _offsetPosition.y;

            float x2 = x1 + size.width;
            float y2 = y1 + size.height;

            if (_flippedX)
            {
                std::swap(x1, x2);
            }
            if (_flippedY)
            {
                std::swap(y1, y2);
            }

            float x = _transformToBatch.m[12];
            float y = _transformToBatch.m[13];

            float cr = _transformToBatch.m[0];
            float sr = _transformToBatch.m[1];
            float cr2 = _transformToBatch.m[5];
            float sr2 = -_transformToBatch.m[4];
            float ax = x1 * cr - y1 * sr2 + x;
            float ay = x1 * sr + y1 * cr2 + y;

            float bx = x2 * cr - y1 * sr2 + x;
            float by = x2 * sr + y1 * cr2 + y;

            float cx = x2 * cr - y2 * sr2 + x;
            float cy = x2 * sr + y2 * cr2 + y;

            float dx = x1 * cr - y2 * sr2 + x;
            float dy = x1 * sr + y2 * cr2 + y;

            _quad.bl.vertices.set(SPRITE_RENDER_IN_SUBPIXEL(ax), SPRITE_RENDER_IN_SUBPIXEL(ay), _positionZ);
            _quad.br.vertices.set(SPRITE_RENDER_IN_SUBPIXEL(bx), SPRITE_RENDER_IN_SUBPIXEL(by), _positionZ);
            _quad.tl.vertices.set(SPRITE_RENDER_IN_SUBPIXEL(dx), SPRITE_RENDER_IN_SUBPIXEL(dy), _positionZ);
            _quad.tr.vertices.set(SPRITE_RENDER_IN_SUBPIXEL(cx), SPRITE_RENDER_IN_SUBPIXEL(cy), _positionZ);
        }

        // MARMALADE CHANGE: ADDED CHECK FOR nullptr, TO PERMIT SPRITES WITH NO BATCH NODE / TEXTURE ATLAS
        if (_textureAtlas)
        {
            _textureAtlas->updateQuad(&_quad, _atlasIndex);
        }

        _recursiveDirty = false;
        setDirty(false);
    }

    // MARMALADE CHANGED
    // recursively iterate over children
/*    if( _hasChildren )
    {
         MARMALADE: CHANGED TO USE Node*
         NOTE THAT WE HAVE ALSO DEFINED virtual Node::updateTransform()
        arrayMakeObjectsPerformSelector(_children, updateTransform, Sprite*);
    }*/
    Node::updateTransform();
}

void Sprite::caculateSlicedVertices()
{
    if (_type == Type::Sliced) {
        CCLOG("draw sliced sprite");
        if (_texture == nullptr || _isDefaultTexture)
        {
            return;
        }
        auto textureSize = _texture->getContentSize();
        
        this->updateBlendFunc();
        //caculate texture coordinate
        float leftWidth = 0, centerWidth = 0, rightWidth = 0;
        float topHeight = 0, centerHeight = 0, bottomHeight = 0;
        auto capInsets = _capInsetsInternal;
        auto textureRect = _rect;
        auto spriteRectSize = _originalSize;
        if(capInsets.equals(Rect::ZERO))
        {
            capInsets = Rect(_originalSize.width/3, _originalSize.height/3,
                             _originalSize.width/3, _originalSize.height/3);
        }
        
        //handle .9.png
        if (_isPatch9)
        {
            float offset = 1;
            if (_rectRotated) {
                textureRect = Rect(textureRect.origin.x,
                                 textureRect.origin.y + 2,
                                 textureRect.size.width,
                                 textureRect.size.height - 2);
            }else{
                textureRect = Rect(textureRect.origin.x +  offset,
                                 textureRect.origin.y +  offset,
                                 textureRect.size.width,
                                 textureRect.size.height);
            }
            spriteRectSize = Size(spriteRectSize.width - 2, spriteRectSize.height-2);
        }

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

        //uv computation should take spritesheet into account.
        float u0, u1, u2, u3;
        float v0, v1, v2, v3;


        if (_rectRotated)
        {
            u0 = textureRect.origin.x / textureSize.width;
            u1 = (leftWidth + textureRect.origin.x) / textureSize.width;
            u2 = (leftWidth + centerWidth + textureRect.origin.x) / textureSize.width;
            u3 = (textureRect.origin.x + textureRect.size.height) / textureSize.width;

            v3 = textureRect.origin.y / textureSize.height;
            v2 = (topHeight + textureRect.origin.y) / textureSize.height;
            v1 = (topHeight + centerHeight + textureRect.origin.y) / textureSize.height;
            v0 = (textureRect.origin.y + textureRect.size.width) / textureSize.height;
        }
        else
        {
            u0 = textureRect.origin.x / textureSize.width;
            u1 = (leftWidth + textureRect.origin.x) / textureSize.width;
            u2 = (leftWidth + centerWidth + textureRect.origin.x) / textureSize.width;
            u3 = (textureRect.origin.x + textureRect.size.width) / textureSize.width;

            v0 = textureRect.origin.y / textureSize.height;
            v1 = (topHeight + textureRect.origin.y) / textureSize.height;
            v2 = (topHeight + centerHeight + textureRect.origin.y) / textureSize.height;
            v3 = (textureRect.origin.y + textureRect.size.height) / textureSize.height;
        }

        std::vector<float> uvRow = {u0, u1, u2, u3};
        std::vector<float> uvColumn = {v3, v2, v1, v0};

        // Recalculate the sizable info
        if(_rectRotated)
        {
            leftWidth = capInsets.origin.x;
            centerWidth = capInsets.size.width;
            rightWidth = spriteRectSize.width - (leftWidth + centerWidth);

            topHeight = capInsets.origin.y;
            centerHeight = capInsets.size.height;
            bottomHeight =spriteRectSize.height - (topHeight + centerHeight);
        }

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

        float row[4] = { x0, x1, x2, x3};
        float colum[4] = {y0, y1, y2, y3};


        const unsigned short slicedTotalVertexCount = 16;
        const unsigned short slicedTotalVertices = 54;
        CC_SAFE_DELETE_ARRAY(_sliceVertices);
        CC_SAFE_DELETE_ARRAY(_sliceIndices);
        
        _sliceVertices = new V3F_C4B_T2F[slicedTotalVertexCount];
        _sliceIndices = new unsigned short[slicedTotalVertices];

        unsigned short indicesStart = 0;
        const unsigned short indicesOffset = 6;
        const unsigned short quadIndices[]={4,0,5, 1,5,0};

        Color4B color4( _displayedColor.r, _displayedColor.g, _displayedColor.b, _displayedOpacity );

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
                vertextData.vertices.x = row[i];
                vertextData.vertices.y = colum[j];

                if (_rectRotated)
                {
                    vertextData.texCoords.u = uvRow[j];
                    vertextData.texCoords.v = uvColumn[i];
                }
                else
                {
                    vertextData.texCoords.u = uvRow[i];
                    vertextData.texCoords.v = uvColumn[j];
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

        this->_polyInfo.reset();
        this->_polyInfo.triangles.vertCount = slicedTotalVertexCount;
        this->_polyInfo.triangles.indexCount = slicedTotalVertices;
        this->_polyInfo.triangles.verts = _sliceVertices;
        this->_polyInfo.triangles.indices = _sliceIndices;
    }
}

// draw

void Sprite::draw(Renderer *renderer, const Mat4 &transform, uint32_t flags)
{
#if CC_USE_CULLING
    // Don't do calculate the culling if the transform was not updated
    auto visitingCamera = Camera::getVisitingCamera();
    auto defaultCamera = Camera::getDefaultCamera();
    if (visitingCamera == defaultCamera) {
        _insideBounds = ((flags & FLAGS_TRANSFORM_DIRTY)|| visitingCamera->isViewProjectionUpdated()) ? renderer->checkVisibility(transform, _contentSize) : _insideBounds;
    }
    else
    {
        _insideBounds = renderer->checkVisibility(transform, _contentSize);
    }

    if(_insideBounds)
#endif
    {
        if (_capInsetsDirty) {
            this->caculateSlicedVertices();
            _capInsetsDirty = false;
        }
        _trianglesCommand.init(_globalZOrder, _texture->getName(), getGLProgramState(), _blendFunc, _polyInfo.triangles, transform, flags);
        renderer->addCommand(&_trianglesCommand);

#if  0//CC_SPRITE_DEBUG_DRAW
        _debugDrawNode->clear();
        auto count = _polyInfo.triangles.indexCount/3;
        auto indices = _polyInfo.triangles.indices;
        auto verts = _polyInfo.triangles.verts;
        for(ssize_t i = 0; i < count; i++)
        {
            //draw 3 lines
            Vec3 from =verts[indices[i*3]].vertices;
            Vec3 to = verts[indices[i*3+1]].vertices;
            _debugDrawNode->drawLine(Vec2(from.x, from.y), Vec2(to.x,to.y), Color4F::RED);

            from =verts[indices[i*3+1]].vertices;
            to = verts[indices[i*3+2]].vertices;
            _debugDrawNode->drawLine(Vec2(from.x, from.y), Vec2(to.x,to.y), Color4F::RED);

            from =verts[indices[i*3+2]].vertices;
            to = verts[indices[i*3]].vertices;
            _debugDrawNode->drawLine(Vec2(from.x, from.y), Vec2(to.x,to.y), Color4F::RED);
        }
#endif //CC_SPRITE_DEBUG_DRAW
    }
}

// MARK: visit, draw, transform

void Sprite::addChild(Node *child, int zOrder, int tag)
{
    CCASSERT(child != nullptr, "Argument must be non-nullptr");

    if (_batchNode)
    {
        Sprite* childSprite = dynamic_cast<Sprite*>(child);
        CCASSERT( childSprite, "CCSprite only supports Sprites as children when using SpriteBatchNode");
        CCASSERT(childSprite->getTexture()->getName() == _textureAtlas->getTexture()->getName(), "childSprite's texture name should be equal to _textureAtlas's texture name!");
        //put it in descendants array of batch node
        _batchNode->appendChild(childSprite);

        if (!_reorderChildDirty)
        {
            setReorderChildDirtyRecursively();
        }
    }
    //CCNode already sets isReorderChildDirty_ so this needs to be after batchNode check
    Node::addChild(child, zOrder, tag);
}

void Sprite::addChild(Node *child, int zOrder, const std::string &name)
{
    CCASSERT(child != nullptr, "Argument must be non-nullptr");

    if (_batchNode)
    {
        Sprite* childSprite = dynamic_cast<Sprite*>(child);
        CCASSERT( childSprite, "CCSprite only supports Sprites as children when using SpriteBatchNode");
        CCASSERT(childSprite->getTexture()->getName() == _textureAtlas->getTexture()->getName(),
                 "childSprite's texture name should be equal to _textureAtlas's texture name.");
        //put it in descendants array of batch node
        _batchNode->appendChild(childSprite);

        if (!_reorderChildDirty)
        {
            setReorderChildDirtyRecursively();
        }
    }
    //CCNode already sets isReorderChildDirty_ so this needs to be after batchNode check
    Node::addChild(child, zOrder, name);
}

void Sprite::reorderChild(Node *child, int zOrder)
{
    CCASSERT(child != nullptr, "child must be non null");
    CCASSERT(_children.contains(child), "child does not belong to this");

    if( _batchNode && ! _reorderChildDirty)
    {
        setReorderChildDirtyRecursively();
        _batchNode->reorderBatch(true);
    }

    Node::reorderChild(child, zOrder);
}

void Sprite::removeChild(Node *child, bool cleanup)
{
    if (_batchNode)
    {
        _batchNode->removeSpriteFromAtlas((Sprite*)(child));
    }

    Node::removeChild(child, cleanup);
}

void Sprite::removeAllChildrenWithCleanup(bool cleanup)
{
    if (_batchNode)
    {
        for(const auto &child : _children) {
            Sprite* sprite = dynamic_cast<Sprite*>(child);
            if (sprite)
            {
                _batchNode->removeSpriteFromAtlas(sprite);
            }
        }
    }

    Node::removeAllChildrenWithCleanup(cleanup);
}

void Sprite::sortAllChildren()
{
    if (_reorderChildDirty)
    {
        std::sort(std::begin(_children), std::end(_children), nodeComparisonLess);

        if ( _batchNode)
        {
            for(const auto &child : _children)
                child->sortAllChildren();
        }

        _reorderChildDirty = false;
    }
}

//
// Node property overloads
// used only when parent is SpriteBatchNode
//

void Sprite::setReorderChildDirtyRecursively(void)
{
    //only set parents flag the first time
    if ( ! _reorderChildDirty )
    {
        _reorderChildDirty = true;
        Node* node = static_cast<Node*>(_parent);
        while (node && node != _batchNode)
        {
            static_cast<Sprite*>(node)->setReorderChildDirtyRecursively();
            node=node->getParent();
        }
    }
}

void Sprite::setDirtyRecursively(bool bValue)
{
    _recursiveDirty = bValue;
    setDirty(bValue);

    for(const auto &child: _children) {
        Sprite* sp = dynamic_cast<Sprite*>(child);
        if (sp)
        {
            sp->setDirtyRecursively(true);
        }
    }
}

// FIXME: HACK: optimization
#define SET_DIRTY_RECURSIVELY() {                       \
                    if (! _recursiveDirty) {            \
                        _recursiveDirty = true;         \
                        setDirty(true);                 \
                        if (!_children.empty())         \
                            setDirtyRecursively(true);  \
                        }                               \
                    }

void Sprite::setPosition(const Vec2& pos)
{
    Node::setPosition(pos);
    SET_DIRTY_RECURSIVELY();
}

void Sprite::setPosition(float x, float y)
{
    Node::setPosition(x, y);
    SET_DIRTY_RECURSIVELY();
}

void Sprite::setRotation(float rotation)
{
    Node::setRotation(rotation);

    SET_DIRTY_RECURSIVELY();
}

void Sprite::setRotationSkewX(float fRotationX)
{
    Node::setRotationSkewX(fRotationX);
    SET_DIRTY_RECURSIVELY();
}

void Sprite::setRotationSkewY(float fRotationY)
{
    Node::setRotationSkewY(fRotationY);
    SET_DIRTY_RECURSIVELY();
}

void Sprite::setSkewX(float sx)
{
    Node::setSkewX(sx);
    SET_DIRTY_RECURSIVELY();
}

void Sprite::setSkewY(float sy)
{
    Node::setSkewY(sy);
    SET_DIRTY_RECURSIVELY();
}

void Sprite::setScaleX(float scaleX)
{
    Node::setScaleX(scaleX);
    SET_DIRTY_RECURSIVELY();
}

void Sprite::setScaleY(float scaleY)
{
    Node::setScaleY(scaleY);
    SET_DIRTY_RECURSIVELY();
}

void Sprite::setScale(float fScale)
{
    Node::setScale(fScale);
    SET_DIRTY_RECURSIVELY();
}

void Sprite::setScale(float scaleX, float scaleY)
{
    Node::setScale(scaleX, scaleY);
    SET_DIRTY_RECURSIVELY();
}

void Sprite::setPositionZ(float fVertexZ)
{
    Node::setPositionZ(fVertexZ);
    SET_DIRTY_RECURSIVELY();
}

void Sprite::setContentSize(const cocos2d::Size &size)
{
    Node::setContentSize(size);
    
    if (!_preferredSize.equals(size))
    {
        _preferredSize = size;
        //TODO: content size change should only update vetices, the texture uv are not changed.
        _capInsetsDirty = true;
    }
   
}

const Size& Sprite::getContentSize()const
{
    if(_type == Type::Sliced)
    {
        return _preferredSize;
    }
    return _contentSize;
}

void Sprite::setAnchorPoint(const Vec2& anchor)
{
    Node::setAnchorPoint(anchor);
    SET_DIRTY_RECURSIVELY();
}

void Sprite::ignoreAnchorPointForPosition(bool value)
{
    CCASSERT(! _batchNode, "ignoreAnchorPointForPosition is invalid in Sprite");
    Node::ignoreAnchorPointForPosition(value);
}

void Sprite::setVisible(bool bVisible)
{
    Node::setVisible(bVisible);
    SET_DIRTY_RECURSIVELY();
}

void Sprite::setFlippedX(bool flippedX)
{
    if (_flippedX != flippedX)
    {
        _flippedX = flippedX;
        if(_type == Type::Simple)
        {
            for (ssize_t i = 0; i < _polyInfo.triangles.vertCount; i++) {
                auto& v = _polyInfo.triangles.verts[i].vertices;
                v.x = _contentSize.width -v.x;
            }
            if (_textureAtlas) {
                setDirty(true);
            }
        }
        else if(_type == Type::Sliced)
        {
            this->setScaleX(flippedX ? -1 : 1);
        }
    }
}

bool Sprite::isFlippedX(void) const
{
    return _flippedX;
}

void Sprite::setFlippedY(bool flippedY)
{
    if (_flippedY != flippedY)
    {
        _flippedY = flippedY;
        if(_type == Type::Simple)
        {
            for (ssize_t i = 0; i < _polyInfo.triangles.vertCount; i++) {
                auto& v = _polyInfo.triangles.verts[i].vertices;
                v.y = _contentSize.height -v.y;
            }
            if (_textureAtlas) {
                setDirty(true);
            }
        }
        else if(_type == Type::Sliced)
        {
            this->setScaleY(flippedY ? -1 : 1);
        }
    }
}

bool Sprite::isFlippedY(void) const
{
    return _flippedY;
}

//
// MARK: RGBA protocol
//

void Sprite::updateColor(void)
{
    Color4B color4( _displayedColor.r, _displayedColor.g, _displayedColor.b, _displayedOpacity );

    // special opacity for premultiplied textures
    if (_opacityModifyRGB)
    {
        color4.r *= _displayedOpacity/255.0f;
        color4.g *= _displayedOpacity/255.0f;
        color4.b *= _displayedOpacity/255.0f;
    }

    for (ssize_t i = 0; i < _polyInfo.triangles.vertCount; i++) {
        _polyInfo.triangles.verts[i].colors = color4;
    }

    // renders using batch node
    if (_batchNode)
    {
        if (_atlasIndex != INDEX_NOT_INITIALIZED)
        {
            _textureAtlas->updateQuad(&_quad, _atlasIndex);
        }
        else
        {
            // no need to set it recursively
            // update dirty_, don't update recursiveDirty_
            setDirty(true);
        }
    }

    // self render
    // do nothing
}

void Sprite::setOpacityModifyRGB(bool modify)
{
    if (_opacityModifyRGB != modify)
    {
        _opacityModifyRGB = modify;
        updateColor();
    }
}

bool Sprite::isOpacityModifyRGB(void) const
{
    return _opacityModifyRGB;
}

// MARK: Frames

void Sprite::setSpriteFrame(const std::string &spriteFrameName)
{
    SpriteFrameCache *cache = SpriteFrameCache::getInstance();
    SpriteFrame *spriteFrame = cache->getSpriteFrameByName(spriteFrameName);

    CCASSERT(spriteFrame, std::string("Invalid spriteFrameName :").append(spriteFrameName).c_str());

    setSpriteFrame(spriteFrame);
}

void Sprite::setSpriteFrame(SpriteFrame *spriteFrame)
{
    // retain the sprite frame
    // do not removed by SpriteFrameCache::removeUnusedSpriteFrames
    if (_spriteFrame != spriteFrame)
    {
        CC_SAFE_RELEASE(_spriteFrame);
        _spriteFrame = spriteFrame;
        spriteFrame->retain();
    }
    _unflippedOffsetPositionFromCenter = spriteFrame->getOffset();

    Texture2D *texture = spriteFrame->getTexture();
    // update texture before updating texture rect
    if (texture != _texture)
    {
        setTexture(texture);
    }

    // update rect
    _rectRotated = spriteFrame->isRotated();
    _originalSize = spriteFrame->getOriginalSize();
    setTextureRect(spriteFrame->getRect(), _rectRotated, spriteFrame->getOriginalSize());
}


void Sprite::setDisplayFrameWithAnimationName(const std::string& animationName, ssize_t frameIndex)
{
    CCASSERT(animationName.size()>0, "CCSprite#setDisplayFrameWithAnimationName. animationName must not be nullptr");

    Animation *a = AnimationCache::getInstance()->getAnimation(animationName);

    CCASSERT(a, "CCSprite#setDisplayFrameWithAnimationName: Frame not found");

    AnimationFrame* frame = a->getFrames().at(frameIndex);

    CCASSERT(frame, "CCSprite#setDisplayFrame. Invalid frame");

    setSpriteFrame(frame->getSpriteFrame());
}

bool Sprite::isFrameDisplayed(SpriteFrame *frame) const
{
    Rect r = frame->getRect();

    return (r.equals(_rect) &&
            frame->getTexture()->getName() == _texture->getName() &&
            frame->getOffset().equals(_unflippedOffsetPositionFromCenter));
}

SpriteFrame* Sprite::getSpriteFrame() const
{
    if(nullptr != this->_spriteFrame)
    {
        return this->_spriteFrame;
    }
    return SpriteFrame::createWithTexture(_texture,
                                           CC_RECT_POINTS_TO_PIXELS(_rect),
                                           _rectRotated,
                                           CC_POINT_POINTS_TO_PIXELS(_unflippedOffsetPositionFromCenter),
                                           CC_SIZE_POINTS_TO_PIXELS(_contentSize));
}

SpriteBatchNode* Sprite::getBatchNode() const
{
    return _batchNode;
}

void Sprite::setBatchNode(SpriteBatchNode *spriteBatchNode)
{
    _batchNode = spriteBatchNode; // weak reference

    // self render
    if( ! _batchNode ) {
        _atlasIndex = INDEX_NOT_INITIALIZED;
        setTextureAtlas(nullptr);
        _recursiveDirty = false;
        setDirty(false);

        float x1 = _offsetPosition.x;
        float y1 = _offsetPosition.y;
        float x2 = x1 + _rect.size.width;
        float y2 = y1 + _rect.size.height;
        _quad.bl.vertices.set( x1, y1, 0 );
        _quad.br.vertices.set(x2, y1, 0);
        _quad.tl.vertices.set(x1, y2, 0);
        _quad.tr.vertices.set(x2, y2, 0);

    } else {

        // using batch
        _transformToBatch = Mat4::IDENTITY;
        setTextureAtlas(_batchNode->getTextureAtlas()); // weak ref
    }
}

// MARK: Texture protocol

void Sprite::updateBlendFunc(void)
{
    CCASSERT(! _batchNode, "CCSprite: updateBlendFunc doesn't work when the sprite is rendered using a SpriteBatchNode");

    // it is possible to have an untextured sprite
    if (! _texture || ! _texture->hasPremultipliedAlpha())
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

std::string Sprite::getDescription() const
{
    int texture_id = -1;
    if( _batchNode )
        texture_id = _batchNode->getTextureAtlas()->getTexture()->getName();
    else
        texture_id = _texture->getName();
    return StringUtils::format("<Sprite | Tag = %d, TextureID = %d>", _tag, texture_id );
}

PolygonInfo Sprite::getPolygonInfo() const
{
    return _polyInfo;
}

void Sprite::setPolygonInfo(const PolygonInfo& info)
{
    _polyInfo = info;
}

void Sprite::setType(Type type)
{
    if (_type == type) {
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
        //TODO: optimize the operation
        this->setContentSize(_preferredSize);
        _capInsetsDirty = true;
    }
}

Sprite::Type Sprite::getType()const
{
    return this->_type;
}


void Sprite::setCapInsets(const cocos2d::Rect &rect)
{
    this->_insetLeft = rect.origin.x;
    this->_insetTop = rect.origin.y;
    this->_insetRight = _originalSize.width - this->_insetLeft - rect.size.width;
    this->_insetBottom = _originalSize.height - this->_insetTop - rect.size.height;
    _capInsetsInternal = rect;

    _capInsetsDirty = true;
}

Rect Sprite::getCapInsets()const
{
    return _capInsetsInternal;
}

Sprite::State Sprite::getState()const
{
    return this->_brightState;
}

void Sprite::setState(Sprite::State state)
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

Size Sprite::getOriginalSize() const
{
    return this->_originalSize;
}

float Sprite::getInsetLeft()const
{
    return this->_insetLeft;
}

float Sprite::getInsetTop()const
{
    return this->_insetTop;
}

float Sprite::getInsetRight()const
{
    return this->_insetRight;
}

float Sprite::getInsetBottom()const
{
    return this->_insetBottom;
}


void Sprite::setInsetLeft(float insetLeft)
{
    this->_insetLeft = insetLeft;
    this->updateCapInset();
}

void Sprite::setInsetTop(float insetTop)
{
    this->_insetTop = insetTop;
    this->updateCapInset();
}

void Sprite::setInsetRight(float insetRight)
{
    this->_insetRight = insetRight;
    this->updateCapInset();
}

void Sprite::setInsetBottom(float insetBottom)
{
    this->_insetBottom = insetBottom;
    this->updateCapInset();
}

void Sprite::updateCapInset()
{
    Rect insets = Rect(_insetLeft,
                      _insetTop,
                      _originalSize.width-_insetLeft-_insetRight,
                      _originalSize.height-_insetTop-_insetBottom);
    this->setCapInsets(insets);
}

NS_CC_END
