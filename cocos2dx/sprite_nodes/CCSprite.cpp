/****************************************************************************
Copyright (c) 2010-2012 cocos2d-x.org
Copyright (c) 2008-2010 Ricardo Quesada
Copyright (c) 2011      Zynga Inc.

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

#include "CCSpriteBatchNode.h"
#include "CCAnimation.h"
#include "CCAnimationCache.h"
#include "ccConfig.h"
#include "CCSprite.h"
#include "CCSpriteFrame.h"
#include "CCSpriteFrameCache.h"
#include "textures/CCTextureCache.h"
#include "draw_nodes/CCDrawingPrimitives.h"
#include "shaders/CCShaderCache.h"
#include "shaders/ccGLStateCache.h"
#include "shaders/CCGLProgram.h"
#include "CCDirector.h"
#include "cocoa/CCGeometry.h"
#include "textures/CCTexture2D.h"
#include "cocoa/CCAffineTransform.h"
#include "support/TransformUtils.h"
#include "support/CCProfiling.h"
// external
#include "kazmath/GL/matrix.h"
#include <string.h>

using namespace std;

NS_CC_BEGIN

#if CC_SPRITEBATCHNODE_RENDER_SUBPIXEL
#define RENDER_IN_SUBPIXEL
#else
#define RENDER_IN_SUBPIXEL(__ARGS__) (ceil(__ARGS__))
#endif

Sprite* Sprite::createWithTexture(Texture2D *texture)
{
    Sprite *sprite = new Sprite();
    if (sprite && sprite->initWithTexture(texture))
    {
        sprite->autorelease();
        return sprite;
    }
    CC_SAFE_DELETE(sprite);
    return NULL;
}

Sprite* Sprite::createWithTexture(Texture2D *texture, const Rect& rect)
{
    Sprite *sprite = new Sprite();
    if (sprite && sprite->initWithTexture(texture, rect))
    {
        sprite->autorelease();
        return sprite;
    }
    CC_SAFE_DELETE(sprite);
    return NULL;
}

Sprite* Sprite::create(const char *filename)
{
    Sprite *sprite = new Sprite();
    if (sprite && sprite->initWithFile(filename))
    {
        sprite->autorelease();
        return sprite;
    }
    CC_SAFE_DELETE(sprite);
    return NULL;
}

Sprite* Sprite::create(const char *filename, const Rect& rect)
{
    Sprite *sprite = new Sprite();
    if (sprite && sprite->initWithFile(filename, rect))
    {
        sprite->autorelease();
        return sprite;
    }
    CC_SAFE_DELETE(sprite);
    return NULL;
}

Sprite* Sprite::createWithSpriteFrame(SpriteFrame *pSpriteFrame)
{
    Sprite *sprite = new Sprite();
    if (pSpriteFrame && sprite && sprite->initWithSpriteFrame(pSpriteFrame))
    {
        sprite->autorelease();
        return sprite;
    }
    CC_SAFE_DELETE(sprite);
    return NULL;
}

Sprite* Sprite::createWithSpriteFrameName(const char *spriteFrameName)
{
    SpriteFrame *pFrame = SpriteFrameCache::getInstance()->getSpriteFrameByName(spriteFrameName);
    
#if COCOS2D_DEBUG > 0
    char msg[256] = {0};
    sprintf(msg, "Invalid spriteFrameName: %s", spriteFrameName);
    CCASSERT(pFrame != NULL, msg);
#endif
    
    return createWithSpriteFrame(pFrame);
}

Sprite* Sprite::create()
{
    Sprite *pSprite = new Sprite();
    if (pSprite && pSprite->init())
    {
        pSprite->autorelease();
        return pSprite;
    }
    CC_SAFE_DELETE(pSprite);
    return NULL;
}

bool Sprite::init(void)
{
    return initWithTexture(NULL, Rect::ZERO);
}

// designated initializer
bool Sprite::initWithTexture(Texture2D *texture, const Rect& rect, bool rotated)
{
    if (NodeRGBA::init())
    {
        _batchNode = NULL;
        
        _recursiveDirty = false;
        setDirty(false);
        
        _opacityModifyRGB = true;
        
        _blendFunc = BlendFunc::ALPHA_PREMULTIPLIED;
        
        _flipX = _flipY = false;
        
        // default transform anchor: center
        setAnchorPoint(Point(0.5f, 0.5f));
        
        // zwoptex default values
        _offsetPosition = Point::ZERO;
        
        _hasChildren = false;
        
        // clean the Quad
        memset(&_quad, 0, sizeof(_quad));
        
        // Atlas: Color
        Color4B tmpColor(255, 255, 255, 255);
        _quad.bl.colors = tmpColor;
        _quad.br.colors = tmpColor;
        _quad.tl.colors = tmpColor;
        _quad.tr.colors = tmpColor;
        
        // shader program
        setShaderProgram(ShaderCache::getInstance()->programForKey(GLProgram::SHADER_NAME_POSITION_TEXTURE_COLOR));
        
        // update texture (calls updateBlendFunc)
        setTexture(texture);
        setTextureRect(rect, rotated, rect.size);
        
        // by default use "Self Render".
        // if the sprite is added to a batchnode, then it will automatically switch to "batchnode Render"
        setBatchNode(NULL);
        
        return true;
    }
    else
    {
        return false;
    }
}

bool Sprite::initWithTexture(Texture2D *texture, const Rect& rect)
{
    return initWithTexture(texture, rect, false);
}

bool Sprite::initWithTexture(Texture2D *texture)
{
    CCASSERT(texture != NULL, "Invalid texture for sprite");

    Rect rect = Rect::ZERO;
    rect.size = texture->getContentSize();
    
    return initWithTexture(texture, rect);
}

bool Sprite::initWithFile(const char *filename)
{
    CCASSERT(filename != NULL, "Invalid filename for sprite");

    Texture2D *texture = TextureCache::getInstance()->addImage(filename);
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

bool Sprite::initWithFile(const char *filename, const Rect& rect)
{
    CCASSERT(filename != NULL, "");

    Texture2D *texture = TextureCache::getInstance()->addImage(filename);
    if (texture)
    {
        return initWithTexture(texture, rect);
    }

    // don't release here.
    // when load texture failed, it's better to get a "transparent" sprite then a crashed program
    // this->release(); 
    return false;
}

bool Sprite::initWithSpriteFrame(SpriteFrame *pSpriteFrame)
{
    CCASSERT(pSpriteFrame != NULL, "");

    bool bRet = initWithTexture(pSpriteFrame->getTexture(), pSpriteFrame->getRect());
    setDisplayFrame(pSpriteFrame);

    return bRet;
}

bool Sprite::initWithSpriteFrameName(const char *spriteFrameName)
{
    CCASSERT(spriteFrameName != NULL, "");

    SpriteFrame *pFrame = SpriteFrameCache::getInstance()->getSpriteFrameByName(spriteFrameName);
    return initWithSpriteFrame(pFrame);
}

// XXX: deprecated
/*
Sprite* Sprite::initWithCGImage(CGImageRef pImage)
{
    // todo
    // because it is deprecated, so we do not implement it

    return NULL;
}
*/

/*
Sprite* Sprite::initWithCGImage(CGImageRef pImage, const char *pszKey)
{
    CCASSERT(pImage != NULL);

    // XXX: possible bug. See issue #349. New API should be added
    Texture2D *texture = TextureCache::getInstance()->addCGImage(pImage, pszKey);

    const Size& size = texture->getContentSize();
    Rect rect = Rect(0 ,0, size.width, size.height);

    return initWithTexture(texture, rect);
}
*/

Sprite::Sprite(void)
: _shouldBeHidden(false),
_texture(NULL)
{
}

Sprite::~Sprite(void)
{
    CC_SAFE_RELEASE(_texture);
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

    Point relativeOffset = _unflippedOffsetPositionFromCenter;

    // issue #732
    if (_flipX)
    {
        relativeOffset.x = -relativeOffset.x;
    }
    if (_flipY)
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
        _quad.bl.vertices = Vertex3F(x1, y1, 0);
        _quad.br.vertices = Vertex3F(x2, y1, 0);
        _quad.tl.vertices = Vertex3F(x1, y2, 0);
        _quad.tr.vertices = Vertex3F(x2, y2, 0);
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

        if (_flipX)
        {
            CC_SWAP(top, bottom, float);
        }

        if (_flipY)
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

        if(_flipX)
        {
            CC_SWAP(left,right,float);
        }

        if(_flipY)
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

void Sprite::updateTransform(void)
{
    CCASSERT(_batchNode, "updateTransform is only valid when Sprite is being rendered using an SpriteBatchNode");

    // recalculate matrix only if it is dirty
    if( isDirty() ) {

        // If it is not visible, or one of its ancestors is not visible, then do nothing:
        if( !_visible || ( _parent && _parent != _batchNode && ((Sprite*)_parent)->_shouldBeHidden) )
        {
            _quad.br.vertices = _quad.tl.vertices = _quad.tr.vertices = _quad.bl.vertices = Vertex3F(0,0,0);
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
                _transformToBatch = AffineTransformConcat( getNodeToParentTransform() , ((Sprite*)_parent)->_transformToBatch );
            }

            //
            // calculate the Quad based on the Affine Matrix
            //

            Size size = _rect.size;

            float x1 = _offsetPosition.x;
            float y1 = _offsetPosition.y;

            float x2 = x1 + size.width;
            float y2 = y1 + size.height;
            float x = _transformToBatch.tx;
            float y = _transformToBatch.ty;

            float cr = _transformToBatch.a;
            float sr = _transformToBatch.b;
            float cr2 = _transformToBatch.d;
            float sr2 = -_transformToBatch.c;
            float ax = x1 * cr - y1 * sr2 + x;
            float ay = x1 * sr + y1 * cr2 + y;

            float bx = x2 * cr - y1 * sr2 + x;
            float by = x2 * sr + y1 * cr2 + y;

            float cx = x2 * cr - y2 * sr2 + x;
            float cy = x2 * sr + y2 * cr2 + y;

            float dx = x1 * cr - y2 * sr2 + x;
            float dy = x1 * sr + y2 * cr2 + y;

            _quad.bl.vertices = Vertex3F( RENDER_IN_SUBPIXEL(ax), RENDER_IN_SUBPIXEL(ay), _vertexZ );
            _quad.br.vertices = Vertex3F( RENDER_IN_SUBPIXEL(bx), RENDER_IN_SUBPIXEL(by), _vertexZ );
            _quad.tl.vertices = Vertex3F( RENDER_IN_SUBPIXEL(dx), RENDER_IN_SUBPIXEL(dy), _vertexZ );
            _quad.tr.vertices = Vertex3F( RENDER_IN_SUBPIXEL(cx), RENDER_IN_SUBPIXEL(cy), _vertexZ );
        }

        // MARMALADE CHANGE: ADDED CHECK FOR NULL, TO PERMIT SPRITES WITH NO BATCH NODE / TEXTURE ATLAS
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

#if CC_SPRITE_DEBUG_DRAW
    // draw bounding box
    Point vertices[4] = {
        Point( _quad.bl.vertices.x, _quad.bl.vertices.y ),
        Point( _quad.br.vertices.x, _quad.br.vertices.y ),
        Point( _quad.tr.vertices.x, _quad.tr.vertices.y ),
        Point( _quad.tl.vertices.x, _quad.tl.vertices.y ),
    };
    ccDrawPoly(vertices, 4, true);
#endif // CC_SPRITE_DEBUG_DRAW
}

// draw

void Sprite::draw(void)
{
    CC_PROFILER_START_CATEGORY(kProfilerCategorySprite, "CCSprite - draw");

    CCASSERT(!_batchNode, "If Sprite is being rendered by SpriteBatchNode, Sprite#draw SHOULD NOT be called");

    CC_NODE_DRAW_SETUP();
    
    GL::blendFunc( _blendFunc.src, _blendFunc.dst );

    GL::bindTexture2D( _texture->getName() );
    GL::enableVertexAttribs( GL::VERTEX_ATTRIB_FLAG_POS_COLOR_TEX );

#define kQuadSize sizeof(_quad.bl)
#ifdef EMSCRIPTEN
    long offset = 0;
    setGLBufferData(&_quad, 4 * kQuadSize, 0);
#else
    long offset = (long)&_quad;
#endif // EMSCRIPTEN

    // vertex
    int diff = offsetof( V3F_C4B_T2F, vertices);
    glVertexAttribPointer(GLProgram::VERTEX_ATTRIB_POSITION, 3, GL_FLOAT, GL_FALSE, kQuadSize, (void*) (offset + diff));

    // texCoods
    diff = offsetof( V3F_C4B_T2F, texCoords);
    glVertexAttribPointer(GLProgram::VERTEX_ATTRIB_TEX_COORDS, 2, GL_FLOAT, GL_FALSE, kQuadSize, (void*)(offset + diff));
    
    // color
    diff = offsetof( V3F_C4B_T2F, colors);
    glVertexAttribPointer(GLProgram::VERTEX_ATTRIB_COLOR, 4, GL_UNSIGNED_BYTE, GL_TRUE, kQuadSize, (void*)(offset + diff));


    glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);

    CHECK_GL_ERROR_DEBUG();


#if CC_SPRITE_DEBUG_DRAW == 1
    // draw bounding box
    Point vertices[4]={
        Point(_quad.tl.vertices.x,_quad.tl.vertices.y),
        Point(_quad.bl.vertices.x,_quad.bl.vertices.y),
        Point(_quad.br.vertices.x,_quad.br.vertices.y),
        Point(_quad.tr.vertices.x,_quad.tr.vertices.y),
    };
    ccDrawPoly(vertices, 4, true);
#elif CC_SPRITE_DEBUG_DRAW == 2
    // draw texture box
    Size s = this->getTextureRect().size;
    Point offsetPix = this->getOffsetPosition();
    Point vertices[4] = {
        Point(offsetPix.x,offsetPix.y), Point(offsetPix.x+s.width,offsetPix.y),
        Point(offsetPix.x+s.width,offsetPix.y+s.height), Point(offsetPix.x,offsetPix.y+s.height)
    };
    ccDrawPoly(vertices, 4, true);
#endif // CC_SPRITE_DEBUG_DRAW

    CC_INCREMENT_GL_DRAWS(1);

    CC_PROFILER_STOP_CATEGORY(kProfilerCategorySprite, "CCSprite - draw");
}

// Node overrides

void Sprite::addChild(Node* child)
{
    Node::addChild(child);
}

void Sprite::addChild(Node *child, int zOrder)
{
    Node::addChild(child, zOrder);
}

void Sprite::addChild(Node *child, int zOrder, int tag)
{
    CCASSERT(child != NULL, "Argument must be non-NULL");

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
    _hasChildren = true;
}

void Sprite::reorderChild(Node *child, int zOrder)
{
    CCASSERT(child != NULL, "");
    CCASSERT(_children->containsObject(child), "");

    if (zOrder == child->getZOrder())
    {
        return;
    }

    if( _batchNode && ! _reorderChildDirty)
    {
        setReorderChildDirtyRecursively();
        _batchNode->reorderBatch(true);
    }

    Node::reorderChild(child, zOrder);
}

void Sprite::removeChild(Node *child, bool bCleanup)
{
    if (_batchNode)
    {
        _batchNode->removeSpriteFromAtlas((Sprite*)(child));
    }

    Node::removeChild(child, bCleanup);
    
}

void Sprite::removeAllChildrenWithCleanup(bool bCleanup)
{
    if (_batchNode)
    {
        Object* pObject = NULL;
        CCARRAY_FOREACH(_children, pObject)
        {
            Sprite* child = dynamic_cast<Sprite*>(pObject);
            if (child)
            {
                _batchNode->removeSpriteFromAtlas(child);
            }
        }
    }

    Node::removeAllChildrenWithCleanup(bCleanup);
    
    _hasChildren = false;
}

void Sprite::sortAllChildren()
{
    if (_reorderChildDirty)
    {
        int i = 0, j = 0, length = _children->data->num;
        Node** x = (Node**)_children->data->arr;
        Node *tempItem = NULL;

        // insertion sort
        for(i=1; i<length; i++)
        {
            tempItem = x[i];
            j = i-1;

            //continue moving element downwards while zOrder is smaller or when zOrder is the same but orderOfArrival is smaller
            while(j>=0 && ( tempItem->getZOrder() < x[j]->getZOrder() || ( tempItem->getZOrder() == x[j]->getZOrder() && tempItem->getOrderOfArrival() < x[j]->getOrderOfArrival() ) ) )
            {
                x[j+1] = x[j];
                j = j-1;
            }
            x[j+1] = tempItem;
        }

        if ( _batchNode)
        {
            arrayMakeObjectsPerformSelector(_children, sortAllChildren, Sprite*);
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
        Node* pNode = (Node*)_parent;
        while (pNode && pNode != _batchNode)
        {
            ((Sprite*)pNode)->setReorderChildDirtyRecursively();
            pNode=pNode->getParent();
        }
    }
}


void Sprite::setDirtyRecursively(bool bValue)
{
    _recursiveDirty = bValue;
    setDirty(bValue);
    // recursively set dirty
    if (_hasChildren)
    {
        Object* pObject = NULL;
        CCARRAY_FOREACH(_children, pObject)
        {
            Sprite* child = dynamic_cast<Sprite*>(pObject);
            if (child)
            {
                child->setDirtyRecursively(true);
            }
        }
    }
}

// XXX HACK: optimization
#define SET_DIRTY_RECURSIVELY() {                                    \
                    if (_batchNode && ! _recursiveDirty) {    \
                        _recursiveDirty = true;                    \
                        setDirty(true);                              \
                        if ( _hasChildren)                        \
                            setDirtyRecursively(true);                \
                        }                                            \
                    }

void Sprite::setPosition(const Point& pos)
{
    Node::setPosition(pos);
    SET_DIRTY_RECURSIVELY();
}

void Sprite::setRotation(float fRotation)
{
    Node::setRotation(fRotation);
    SET_DIRTY_RECURSIVELY();
}

void Sprite::setRotationX(float fRotationX)
{
    Node::setRotationX(fRotationX);
    SET_DIRTY_RECURSIVELY();
}

void Sprite::setRotationY(float fRotationY)
{
    Node::setRotationY(fRotationY);
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

void Sprite::setVertexZ(float fVertexZ)
{
    Node::setVertexZ(fVertexZ);
    SET_DIRTY_RECURSIVELY();
}

void Sprite::setAnchorPoint(const Point& anchor)
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

void Sprite::setFlipX(bool bFlipX)
{
    if (_flipX != bFlipX)
    {
        _flipX = bFlipX;
        setTextureRect(_rect, _rectRotated, _contentSize);
    }
}

bool Sprite::isFlipX(void) const
{
    return _flipX;
}

void Sprite::setFlipY(bool bFlipY)
{
    if (_flipY != bFlipY)
    {
        _flipY = bFlipY;
        setTextureRect(_rect, _rectRotated, _contentSize);
    }
}

bool Sprite::isFlipY(void) const
{
    return _flipY;
}

//
// RGBA protocol
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
        if (_atlasIndex != kSpriteIndexNotInitialized)
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

void Sprite::setOpacity(GLubyte opacity)
{
    NodeRGBA::setOpacity(opacity);

    updateColor();
}

void Sprite::setColor(const Color3B& color3)
{
    NodeRGBA::setColor(color3);

    updateColor();
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

void Sprite::updateDisplayedColor(const Color3B& parentColor)
{
    NodeRGBA::updateDisplayedColor(parentColor);
    
    updateColor();
}

void Sprite::updateDisplayedOpacity(GLubyte opacity)
{
    NodeRGBA::updateDisplayedOpacity(opacity);
    
    updateColor();
}

// Frames

void Sprite::setDisplayFrame(SpriteFrame *pNewFrame)
{
    _unflippedOffsetPositionFromCenter = pNewFrame->getOffset();

    Texture2D *pNewTexture = pNewFrame->getTexture();
    // update texture before updating texture rect
    if (pNewTexture != _texture)
    {
        setTexture(pNewTexture);
    }

    // update rect
    _rectRotated = pNewFrame->isRotated();
    setTextureRect(pNewFrame->getRect(), _rectRotated, pNewFrame->getOriginalSize());
}

void Sprite::setDisplayFrameWithAnimationName(const char *animationName, int frameIndex)
{
    CCASSERT(animationName, "CCSprite#setDisplayFrameWithAnimationName. animationName must not be NULL");

    Animation *a = AnimationCache::getInstance()->animationByName(animationName);

    CCASSERT(a, "CCSprite#setDisplayFrameWithAnimationName: Frame not found");

    AnimationFrame* frame = static_cast<AnimationFrame*>( a->getFrames()->objectAtIndex(frameIndex) );

    CCASSERT(frame, "CCSprite#setDisplayFrame. Invalid frame");

    setDisplayFrame(frame->getSpriteFrame());
}

bool Sprite::isFrameDisplayed(SpriteFrame *pFrame) const
{
    Rect r = pFrame->getRect();

    return (r.equals(_rect) &&
            pFrame->getTexture()->getName() == _texture->getName() &&
            pFrame->getOffset().equals(_unflippedOffsetPositionFromCenter));
}

SpriteFrame* Sprite::displayFrame(void)
{
    return SpriteFrame::createWithTexture(_texture,
                                           CC_RECT_POINTS_TO_PIXELS(_rect),
                                           _rectRotated,
                                           CC_POINT_POINTS_TO_PIXELS(_unflippedOffsetPositionFromCenter),
                                           CC_SIZE_POINTS_TO_PIXELS(_contentSize));
}

SpriteBatchNode* Sprite::getBatchNode(void)
{
    return _batchNode;
}

void Sprite::setBatchNode(SpriteBatchNode *spriteBatchNode)
{
    _batchNode = spriteBatchNode; // weak reference

    // self render
    if( ! _batchNode ) {
        _atlasIndex = kSpriteIndexNotInitialized;
        setTextureAtlas(NULL);
        _recursiveDirty = false;
        setDirty(false);

        float x1 = _offsetPosition.x;
        float y1 = _offsetPosition.y;
        float x2 = x1 + _rect.size.width;
        float y2 = y1 + _rect.size.height;
        _quad.bl.vertices = Vertex3F( x1, y1, 0 );
        _quad.br.vertices = Vertex3F( x2, y1, 0 );
        _quad.tl.vertices = Vertex3F( x1, y2, 0 );
        _quad.tr.vertices = Vertex3F( x2, y2, 0 );

    } else {

        // using batch
        _transformToBatch = AffineTransformIdentity;
        setTextureAtlas(_batchNode->getTextureAtlas()); // weak ref
    }
}

// Texture protocol

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

/*
 * This array is the data of a white image with 2 by 2 dimension.
 * It's used for creating a default texture when sprite's texture is set to NULL.
 * Supposing codes as follows:
 *
 *   auto sp = new Sprite();
 *   sp->init();  // Texture was set to NULL, in order to make opacity and color to work correctly, we need to create a 2x2 white texture.
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

#define CC_2x2_WHITE_IMAGE_KEY  "cc_2x2_white_image"

void Sprite::setTexture(Texture2D *texture)
{
    // If batchnode, then texture id should be the same
    CCASSERT(! _batchNode || texture->getName() == _batchNode->getTexture()->getName(), "CCSprite: Batched sprites should use the same texture as the batchnode");
    // accept texture==nil as argument
    CCASSERT( !texture || dynamic_cast<Texture2D*>(texture), "setTexture expects a Texture2D. Invalid argument");
    
    if (NULL == texture)
    {
        // Gets the texture by key firstly.
        texture = TextureCache::getInstance()->textureForKey(CC_2x2_WHITE_IMAGE_KEY);
        
        // If texture wasn't in cache, create it from RAW data.
        if (NULL == texture)
        {
            Image* image = new Image();
            bool isOK = image->initWithImageData(cc_2x2_white_image, sizeof(cc_2x2_white_image), Image::Format::RAW_DATA, 2, 2, 8);
            CCASSERT(isOK, "The 2x2 empty texture was created unsuccessfully.");

            texture = TextureCache::getInstance()->addUIImage(image, CC_2x2_WHITE_IMAGE_KEY);
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

Texture2D* Sprite::getTexture(void) const
{
    return _texture;
}

NS_CC_END
