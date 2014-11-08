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

#include "2d/CCSpriteBatchNode.h"
#include "2d/CCAnimationCache.h"
#include "2d/CCSpriteFrame.h"
#include "2d/CCSpriteFrameCache.h"
#include "renderer/CCTextureCache.h"
#include "renderer/CCTexture2D.h"
#include "renderer/CCRenderer.h"
#include "base/CCDirector.h"

#include "deprecated/CCString.h"


NS_CC_BEGIN

#if CC_SPRITEBATCHNODE_RENDER_SUBPIXEL
#define RENDER_IN_SUBPIXEL
#else
#define RENDER_IN_SUBPIXEL(__ARGS__) (ceil(__ARGS__))
#endif

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
        return initWithTexture(texture, rect);
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
    CCASSERT(spriteFrame != nullptr, "");

    bool bRet = initWithTexture(spriteFrame->getTexture(), spriteFrame->getRect());
    setSpriteFrame(spriteFrame);

    return bRet;
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
        _offsetPosition = Vec2::ZERO;

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
: _batchNode(nullptr)
, _shouldBeHidden(false)
, _texture(nullptr)
, _insideBounds(true)
{
#if CC_SPRITE_DEBUG_DRAW
    _debugDrawNode = DrawNode::create();
    addChild(_debugDrawNode);
#endif //CC_SPRITE_DEBUG_DRAW
}

Sprite::~Sprite(void)
{
    CC_SAFE_RELEASE(_texture);
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
    rect.size = texture->getContentSize();
    setTextureRect(rect);
}

void Sprite::setTexture(Texture2D *texture)
{
    // If batchnode, then texture id should be the same
    CCASSERT(! _batchNode || texture->getName() == _batchNode->getTexture()->getName(), "CCSprite: Batched sprites should use the same texture as the batchnode");
    // accept texture==nil as argument
    CCASSERT( !texture || dynamic_cast<Texture2D*>(texture), "setTexture expects a Texture2D. Invalid argument");

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

    Vec2 relativeOffset = _unflippedOffsetPositionFromCenter;

    // issue #732
    if (_flippedX)
    {
        relativeOffset.x = -relativeOffset.x;
    }
    if (_flippedY)
    {
        relativeOffset.y = -relativeOffset.y;
    }

    _offsetPosition.x = relativeOffset.x + (_contentSize.width - _rect.size.width) / 2;
    _offsetPosition.y = relativeOffset.y + (_contentSize.height - _rect.size.height) / 2;

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
        float x1 = 0 + _offsetPosition.x;
        float y1 = 0 + _offsetPosition.y;
        float x2 = x1 + _rect.size.width;
        float y2 = y1 + _rect.size.height;

        // Don't update Z.
        _quad.bl.vertices = Vec3(x1, y1, 0);
        _quad.br.vertices = Vec3(x2, y1, 0);
        _quad.tl.vertices = Vec3(x1, y2, 0);
        _quad.tr.vertices = Vec3(x2, y2, 0);
    }
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
            CC_SWAP(top, bottom, float);
        }

        if (_flippedY)
        {
            CC_SWAP(left, right, float);
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
            CC_SWAP(left,right,float);
        }

        if(_flippedY)
        {
            CC_SWAP(top,bottom,float);
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
            _quad.br.vertices = _quad.tl.vertices = _quad.tr.vertices = _quad.bl.vertices = Vec3(0,0,0);
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

            _quad.bl.vertices = Vec3( RENDER_IN_SUBPIXEL(ax), RENDER_IN_SUBPIXEL(ay), _positionZ );
            _quad.br.vertices = Vec3( RENDER_IN_SUBPIXEL(bx), RENDER_IN_SUBPIXEL(by), _positionZ );
            _quad.tl.vertices = Vec3( RENDER_IN_SUBPIXEL(dx), RENDER_IN_SUBPIXEL(dy), _positionZ );
            _quad.tr.vertices = Vec3( RENDER_IN_SUBPIXEL(cx), RENDER_IN_SUBPIXEL(cy), _positionZ );
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
        // MARMALADE: CHANGED TO USE Node*
        // NOTE THAT WE HAVE ALSO DEFINED virtual Node::updateTransform()
        arrayMakeObjectsPerformSelector(_children, updateTransform, Sprite*);
    }*/
    Node::updateTransform();
}

// draw

void Sprite::draw(Renderer *renderer, const Mat4 &transform, uint32_t flags)
{
    // Don't do calculate the culling if the transform was not updated
    _insideBounds = (flags & FLAGS_TRANSFORM_DIRTY) ? renderer->checkVisibility(transform, _contentSize) : _insideBounds;

    if(_insideBounds)
    {
        _quadCommand.init(_globalZOrder, _texture->getName(), getGLProgramState(), _blendFunc, &_quad, 1, transform);
        renderer->addCommand(&_quadCommand);
#if CC_SPRITE_DEBUG_DRAW
        _debugDrawNode->clear();
        Vec2 vertices[4] = {
            Vec2( _quad.bl.vertices.x, _quad.bl.vertices.y ),
            Vec2( _quad.br.vertices.x, _quad.br.vertices.y ),
            Vec2( _quad.tr.vertices.x, _quad.tr.vertices.y ),
            Vec2( _quad.tl.vertices.x, _quad.tl.vertices.y ),
        };
        _debugDrawNode->drawPoly(vertices, 4, true, Color4F(1.0, 1.0, 1.0, 1.0));
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
        CCASSERT(childSprite->getTexture()->getName() == _textureAtlas->getTexture()->getName(), "");
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
        CCASSERT(childSprite->getTexture()->getName() == _textureAtlas->getTexture()->getName(), "");
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
        setTextureRect(_rect, _rectRotated, _contentSize);
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
        setTextureRect(_rect, _rectRotated, _contentSize);
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

    _quad.bl.colors = color4;
    _quad.br.colors = color4;
    _quad.tl.colors = color4;
    _quad.tr.colors = color4;

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

    CCASSERT(spriteFrame, "Invalid spriteFrameName");

    setSpriteFrame(spriteFrame);
}

void Sprite::setSpriteFrame(SpriteFrame *spriteFrame)
{
    _unflippedOffsetPositionFromCenter = spriteFrame->getOffset();

    Texture2D *texture = spriteFrame->getTexture();
    // update texture before updating texture rect
    if (texture != _texture)
    {
        setTexture(texture);
    }

    // update rect
    _rectRotated = spriteFrame->isRotated();
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
    return SpriteFrame::createWithTexture(_texture,
                                           CC_RECT_POINTS_TO_PIXELS(_rect),
                                           _rectRotated,
                                           CC_POINT_POINTS_TO_PIXELS(_unflippedOffsetPositionFromCenter),
                                           CC_SIZE_POINTS_TO_PIXELS(_contentSize));
}

SpriteBatchNode* Sprite::getBatchNode()
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
        _quad.bl.vertices = Vec3( x1, y1, 0 );
        _quad.br.vertices = Vec3( x2, y1, 0 );
        _quad.tl.vertices = Vec3( x1, y2, 0 );
        _quad.tr.vertices = Vec3( x2, y2, 0 );

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

NS_CC_END
