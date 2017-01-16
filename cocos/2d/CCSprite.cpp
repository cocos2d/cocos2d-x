/****************************************************************************
Copyright (c) 2008-2010 Ricardo Quesada
Copyright (c) 2010-2012 cocos2d-x.org
Copyright (c) 2011      Zynga Inc.
Copyright (c) 2013-2016 Chukong Technologies Inc.

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
#include "base/ccUTF8.h"
#include "2d/CCCamera.h"

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

bool Sprite::init()
{
    initWithTexture(nullptr, Rect::ZERO);

    return true;
}

bool Sprite::initWithTexture(Texture2D *texture)
{
    CCASSERT(texture != nullptr, "Invalid texture for sprite");

    Rect rect = Rect::ZERO;
    if (texture) {
        rect.size = texture->getContentSize();
    }

    return initWithTexture(texture, rect, false);
}

bool Sprite::initWithTexture(Texture2D *texture, const Rect& rect)
{
    return initWithTexture(texture, rect, false);
}

bool Sprite::initWithFile(const std::string& filename)
{
    if (filename.empty())
    {
        CCLOG("Call Sprite::initWithFile with blank resource filename.");
        return false;
    }

    _fileName = filename;
    _fileType = 0;

    Texture2D *texture = _director->getTextureCache()->addImage(filename);
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
    CCASSERT(!filename.empty(), "Invalid filename");
    if (filename.empty())
    {
        return false;
    }

    _fileName = filename;
    _fileType = 0;

    Texture2D *texture = _director->getTextureCache()->addImage(filename);
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
    CCASSERT(!spriteFrameName.empty(), "Invalid spriteFrameName");
    if (spriteFrameName.empty())
    {
        return false;
    }

    _fileName = spriteFrameName;
    _fileType = 1;

    SpriteFrame *frame = SpriteFrameCache::getInstance()->getSpriteFrameByName(spriteFrameName);
    return initWithSpriteFrame(frame);
}

bool Sprite::initWithSpriteFrame(SpriteFrame *spriteFrame)
{
    CCASSERT(spriteFrame != nullptr, "spriteFrame can't be nullptr!");
    if (spriteFrame == nullptr)
    {
        return false;
    }

    bool ret = initWithTexture(spriteFrame->getTexture(), spriteFrame->getRect(), spriteFrame->isRotated());
    setSpriteFrame(spriteFrame);

    return ret;
}

bool Sprite::initWithPolygon(const cocos2d::PolygonInfo &info)
{
    bool ret = false;

    Texture2D *texture = _director->getTextureCache()->addImage(info.getFilename());
    if(texture && initWithTexture(texture))
    {
        _polyInfo = info;
        _renderMode = RenderMode::POLYGON;
        Node::setContentSize(_polyInfo.getRect().size / _director->getContentScaleFactor());
        ret = true;
    }

    return ret;
}

// designated initializer
bool Sprite::initWithTexture(Texture2D *texture, const Rect& rect, bool rotated)
{
    bool result = false;
    if (Node::init())
    {
        _batchNode = nullptr;

        _recursiveDirty = false;
        setDirty(false);

        _opacityModifyRGB = true;

        _blendFunc = BlendFunc::ALPHA_PREMULTIPLIED;

        _flippedX = _flippedY = false;

        // default transform anchor: center
        setAnchorPoint(Vec2::ANCHOR_MIDDLE);

        // zwoptex default values
        _offsetPosition.setZero();

        // clean the Quad
        memset(&_quad, 0, sizeof(_quad));

        // Atlas: Color
        _quad.bl.colors = Color4B::WHITE;
        _quad.br.colors = Color4B::WHITE;
        _quad.tl.colors = Color4B::WHITE;
        _quad.tr.colors = Color4B::WHITE;

        // update texture (calls updateBlendFunc)
        setTexture(texture);
        setTextureRect(rect, rotated, rect.size);

        // by default use "Self Render".
        // if the sprite is added to a batchnode, then it will automatically switch to "batchnode Render"
        setBatchNode(nullptr);
        result = true;
    }

    _recursiveDirty = true;
    setDirty(true);

    return result;
}

Sprite::Sprite(void)
: _batchNode(nullptr)
, _textureAtlas(nullptr)
, _shouldBeHidden(false)
, _texture(nullptr)
, _spriteFrame(nullptr)
, _insideBounds(true)
, _centerRectNormalized(0,0,1,1)
, _renderMode(RenderMode::QUAD)
, _quads(nullptr)
, _strechFactor(Vec2::ONE)
, _originalContentSize(Size::ZERO)
, _strechEnabled(true)
{
#if CC_SPRITE_DEBUG_DRAW
    _debugDrawNode = DrawNode::create();
    addChild(_debugDrawNode);
#endif //CC_SPRITE_DEBUG_DRAW
}

Sprite::~Sprite()
{
    CC_SAFE_FREE(_quads);
    CC_SAFE_RELEASE(_spriteFrame);
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
    _unflippedOffsetPositionFromCenter = Vec2::ZERO;
    Rect rect = Rect::ZERO;
    if (texture)
        rect.size = texture->getContentSize();
    setTextureRect(rect);
}

void Sprite::setTexture(Texture2D *texture)
{
    setGLProgramState(GLProgramState::getOrCreateWithGLProgramName(GLProgram::SHADER_NAME_POSITION_TEXTURE_COLOR_NO_MVP, texture));

    // If batchnode, then texture id should be the same
    CCASSERT(! _batchNode || (texture &&  texture->getName() == _batchNode->getTexture()->getName()), "CCSprite: Batched sprites should use the same texture as the batchnode");
    // accept texture==nil as argument
    CCASSERT( !texture || dynamic_cast<Texture2D*>(texture), "setTexture expects a Texture2D. Invalid argument");

    if (texture == nullptr)
    {
        // Gets the texture by key firstly.
        texture = _director->getTextureCache()->getTextureForKey(CC_2x2_WHITE_IMAGE_KEY);

        // If texture wasn't in cache, create it from RAW data.
        if (texture == nullptr)
        {
            Image* image = new (std::nothrow) Image();
            bool CC_UNUSED isOK = image->initWithRawData(cc_2x2_white_image, sizeof(cc_2x2_white_image), 2, 2, 8);
            CCASSERT(isOK, "The 2x2 empty texture was created unsuccessfully.");

            texture = _director->getTextureCache()->addImage(image, CC_2x2_WHITE_IMAGE_KEY);
            CC_SAFE_RELEASE(image);
        }
    }

    if ((_renderMode != RenderMode::QUAD_BATCHNODE) && (_texture != texture))
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

    Node::setContentSize(untrimmedSize);
    _originalContentSize = untrimmedSize;

    setVertexRect(rect);
    updateStretchFactor();
    updatePoly();
}

void Sprite::updatePoly()
{
    // There are 3 cases:
    //
    // A) a non 9-sliced, non streched
    //    contentsize doesn't not affect the streching, since there is no streching
    //    this was the original behavior, and we keep it for backwards compatibility reasons
    //    When non-streching is enabled, we have to change the offset in order to "fill the empty" space at the
    //    left-top of the texture
    // B) non 9-sliced, streched
    //    the texture is streched to the content size
    // C) 9-sliced, streched
    //    the sprite is 9-sliced and streched.
    if (_renderMode == RenderMode::QUAD || _renderMode == RenderMode::QUAD_BATCHNODE) {
        setTextureCoords(_rect, &_quad);
        Rect copyRect;
        if (_strechEnabled) {
            // case B)
            copyRect = Rect(0, 0, _rect.size.width * _strechFactor.x, _rect.size.height * _strechFactor.y);
        } else {
            // case A)
            // modify origin to put the sprite in the correct offset
            copyRect = Rect((_contentSize.width - _originalContentSize.width) / 2.0f,
                            (_contentSize.height - _originalContentSize.height) / 2.0f,
                            _rect.size.width,
                            _rect.size.height);
        }
        setVertexCoords(copyRect, &_quad);
        _polyInfo.setQuad(&_quad);

    } else if (_renderMode == RenderMode::SLICE9) {
        // case C)

        // How the texture is split
        //
        //  u,v: are the texture coordinates
        //  w,h: are the width and heights
        //
        //      w0    w1   w2
        // v2 +----+------+--+
        //    |    |      |  |
        //    |    |      |  |
        //    | 6  |   7  | 8|  h2
        //    |    |      |  |
        // v1 +----+------+--|
        //    |    |      |  |
        //    | 3  |   4  | 5|  h1
        // v0 +----+------+--|
        //    |    |      |  |
        //    | 0  |   1  | 2|  h0
        //    |    |      |  |
        //    +----+------+--+
        //    u0   u1    u2
        //
        //
        //  and when the texture is rotated, it will get transformed.
        //  not only the rects have a different position, but also u,v
        //  points to the bottom-left and not top-right of the texture
        //  so some swaping/origin/reordering needs to be done in order
        //  to support rotated slice-9 correctly
        //
        //       w0    w1     w2
        // v2 +------+----+--------+
        //    |      |    |        |
        //    |   0  |  3 |    6   | h2
        // v1 +------+----+--------+
        //    |      |    |        |
        //    |   1  |  4 |    7   | h1
        //    |      |    |        |
        // v0 +------+----+--------+
        //    |   2  |  5 |    8   | h0
        //    +------+----+--------+
        //    u0      u1     u2


        // center rect
        float cx1 = _centerRectNormalized.origin.x;
        float cy1 = _centerRectNormalized.origin.y;
        float cx2 = _centerRectNormalized.origin.x + _centerRectNormalized.size.width;
        float cy2 = _centerRectNormalized.origin.y + _centerRectNormalized.size.height;

        // "O"riginal rect
        const float oox = _rect.origin.x;
        const float ooy = _rect.origin.y;
        float osw = _rect.size.width;
        float osh = _rect.size.height;

        if (_rectRotated) {
            std::swap(cx1, cy1);
            std::swap(cx2, cy2);

            // when the texture is rotated, then the centerRect starts from the "bottom" (left)
            // but when it is not rotated, it starts from the top, so invert it
            cy2 = 1 - cy2;
            cy1 = 1 - cy1;
            std::swap(cy1, cy2);
            std::swap(osw, osh);
        }

        //
        // textCoords Data: Y must be inverted.
        //
        const float w0 = osw * cx1;
        const float w1 = osw * (cx2-cx1);
        const float w2 = osw * (1-cx2);
        const float h0 = osh * cy1;
        const float h1 = osh * (cy2-cy1);
        const float h2 = osh * (1-cy2);

        const float u0 = oox;
        const float u1 = u0 + w0;
        const float u2 = u1 + w1;
        const float v2 = ooy;
        const float v1 = v2 + h2;
        const float v0 = v1 + h1;


        const Rect texRects_normal[9] = {
            Rect(u0, v0,    w0, h0),   // bottom-left
            Rect(u1, v0,    w1, h0),   // bottom
            Rect(u2, v0,    w2, h0),   // bottom-right

            Rect(u0, v1,    w0, h1),   // left
            Rect(u1, v1,    w1, h1),   // center
            Rect(u2, v1,    w2, h1),   // right

            Rect(u0, v2,    w0, h2),   // top-left
            Rect(u1, v2,    w1, h2),   // top
            Rect(u2, v2,    w2, h2),   // top-right
        };

        // swap width and height because setTextureCoords()
        // will expects the hight and width to be swapped
        const Rect texRects_rotated[9] = {
            Rect(u0, v2,    h2, w0),        // top-left
            Rect(u0, v1,    h1, w0),        // left
            Rect(u0, v0,    h0, w0),        // bottom-left

            Rect(u1, v2,    h2, w1),        // top
            Rect(u1, v1,    h1, w1),        // center
            Rect(u1, v0,    h0, w1),        // bottom

            Rect(u2, v2,    h2, w2),        // top-right
            Rect(u2, v1,    h1, w2),        // right
            Rect(u2, v0,    h0, w2),        // bottom-right
        };

        const Rect* texRects = _rectRotated ? texRects_rotated : texRects_normal;

        //
        // vertex Data.
        //

        // reset center rect since it is altered when when the texture
        // is rotated
        cx1 = _centerRectNormalized.origin.x;
        cy1 = _centerRectNormalized.origin.y;
        cx2 = _centerRectNormalized.origin.x + _centerRectNormalized.size.width;
        cy2 = _centerRectNormalized.origin.y + _centerRectNormalized.size.height;
        if (_rectRotated)
            std::swap(osw, osh);

        // sizes
        float x0_s = osw * cx1;
        float x1_s = osw * (cx2-cx1) * _strechFactor.x;
        float x2_s = osw * (1-cx2);
        float y0_s = osh * cy1;
        float y1_s = osh * (cy2-cy1) * _strechFactor.y;
        float y2_s = osh * (1-cy2);


        // avoid negative size:
        if (_contentSize.width < x0_s + x2_s) {
            x2_s = x0_s = _contentSize.width / 2;
        }

        if  (_contentSize.height < y0_s + y2_s) {
            y2_s = y0_s = _contentSize.height / 2;
        }


        // is it flipped?
        // swap sizes to calculate offset correctly
        if (_flippedX)
            std::swap(x0_s, x2_s);
        if (_flippedY)
            std::swap(y0_s, y2_s);

        // origins
        float x0 = 0;
        float x1 = x0 + x0_s;
        float x2 = x1 + x1_s;
        float y0 = 0;
        float y1 = y0 + y0_s;
        float y2 = y1 + y1_s;

        // swap origin, but restore size to its original value
        if (_flippedX) {
            std::swap(x0, x2);
            std::swap(x0_s, x2_s);
        }
        if (_flippedY) {
            std::swap(y0, y2);
            std::swap(y0_s, y2_s);
        }

        const Rect verticesRects[9] = {
            Rect(x0, y0,  x0_s, y0_s),      // bottom-left
            Rect(x1, y0,  x1_s, y0_s),      // bottom
            Rect(x2, y0,  x2_s, y0_s),      // bottom-right

            Rect(x0, y1,  x0_s, y1_s),      // left
            Rect(x1, y1,  x1_s, y1_s),      // center
            Rect(x2, y1,  x2_s, y1_s),      // right

            Rect(x0, y2,  x0_s, y2_s),      // top-left
            Rect(x1, y2,  x1_s, y2_s),      // top
            Rect(x2, y2,  x2_s, y2_s),      // top-right
        };

        for (int i=0; i<9; ++i) {
            setTextureCoords(texRects[i], &_quads[i]);
            setVertexCoords(verticesRects[i], &_quads[i]);
        }
        _polyInfo.setQuads(_quads, 9);
    }
}

void Sprite::setCenterRectNormalized(const cocos2d::Rect &rectTopLeft)
{
    if (_renderMode != RenderMode::QUAD && _renderMode != RenderMode::SLICE9) {
        CCLOGWARN("Warning: Sprite::setCenterRectNormalized() only works with QUAD and SLICE9 render modes");
        return;
    }

    // FIMXE: Rect is has origin on top-left (like text coordinate).
    // but all the logic has been done using bottom-left as origin. So it is easier to invert Y
    // here, than in the rest of the places... but it is not as clean.
    Rect rect(rectTopLeft.origin.x, 1 - rectTopLeft.origin.y - rectTopLeft.size.height, rectTopLeft.size.width, rectTopLeft.size.height);
    if (!_centerRectNormalized.equals(rect)) {
        _centerRectNormalized = rect;

        // convert it to 1-slice
        if (rect.equals(Rect(0,0,1,1))) {
            _renderMode = RenderMode::QUAD;
            free(_quads);
            _quads = nullptr;
        }
        else
        {
            // convert it to 9-slice if it isn't already
            if (_renderMode != RenderMode::SLICE9) {
                _renderMode = RenderMode::SLICE9;
                _quads = (V3F_C4B_T2F_Quad*) malloc(sizeof(*_quads) * 9);

                for (int i=0; i<9; ++i) {
                    _quads[i].bl.colors = Color4B::WHITE;
                    _quads[i].br.colors = Color4B::WHITE;
                    _quads[i].tl.colors = Color4B::WHITE;
                    _quads[i].tr.colors = Color4B::WHITE;
                }
            }
        }

        updateStretchFactor();
        updatePoly();
        updateColor();
    }
}

void Sprite::setCenterRect(const cocos2d::Rect &rectInPoints)
{
    if (_renderMode != RenderMode::QUAD && _renderMode != RenderMode::SLICE9) {
        CCLOGWARN("Warning: Sprite::setCenterRect() only works with QUAD and SLICE9 render modes");
        return;
    }

    if (!_originalContentSize.equals(Size::ZERO))
    {
        Rect rect = rectInPoints;

        const float x = rect.origin.x / _rect.size.width;
        const float y = rect.origin.y / _rect.size.height;
        const float w = rect.size.width / _rect.size.width;
        const float h = rect.size.height / _rect.size.height;
        setCenterRectNormalized(Rect(x,y,w,h));
    }
}

Rect Sprite::getCenterRectNormalized() const
{
    // FIXME: _centerRectNormalized is in bottom-left coords, but should converted to top-left
    Rect ret(_centerRectNormalized.origin.x,
             1 - _centerRectNormalized.origin.y - _centerRectNormalized.size.height,
             _centerRectNormalized.size.width,
             _centerRectNormalized.size.height);
    return ret;
}

Rect Sprite::getCenterRect() const
{
    Rect rect = getCenterRectNormalized();
    rect.origin.x *= _rect.size.width;
    rect.origin.y *= _rect.size.height;
    rect.size.width *= _rect.size.width;
    rect.size.height *= _rect.size.height;
    return rect;
}

// override this method to generate "double scale" sprites
void Sprite::setVertexRect(const Rect& rect)
{
    _rect = rect;
}

void Sprite::setTextureCoords(const Rect& rectInPoints)
{
    setTextureCoords(rectInPoints, &_quad);
}

void Sprite::setTextureCoords(const Rect& rectInPoints, V3F_C4B_T2F_Quad* outQuad)
{
    Texture2D *tex = (_renderMode == RenderMode::QUAD_BATCHNODE) ? _textureAtlas->getTexture() : _texture;
    if (tex == nullptr)
    {
        return;
    }

    const auto rectInPixels = CC_RECT_POINTS_TO_PIXELS(rectInPoints);

    const float atlasWidth = (float)tex->getPixelsWide();
    const float atlasHeight = (float)tex->getPixelsHigh();

    float rw = rectInPixels.size.width;
    float rh = rectInPixels.size.height;

    // if the rect is rotated, it means that the frame is rotated 90 degrees (clockwise) and:
    //  - rectInpoints: origin will be the bottom-left of the frame (and not the top-right)
    //  - size: represents the unrotated texture size
    //
    // so what we have to do is:
    //  - swap texture width and height
    //  - take into account the origin
    //  - flip X instead of Y when flipY is enabled
    //  - flip Y instead of X when flipX is enabled

    if (_rectRotated)
        std::swap(rw, rh);

#if CC_FIX_ARTIFACTS_BY_STRECHING_TEXEL
    float left    = (2*rectInPixels.origin.x+1) / (2*atlasWidth);
    float right   = left+(rw*2-2) / (2*atlasWidth);
    float top     = (2*rectInPixels.origin.y+1) / (2*atlasHeight);
    float bottom  = top+(rh*2-2) / (2*atlasHeight);
#else
    float left    = rectInPixels.origin.x / atlasWidth;
    float right   = (rectInPixels.origin.x + rw) / atlasWidth;
    float top     = rectInPixels.origin.y / atlasHeight;
    float bottom  = (rectInPixels.origin.y + rh) / atlasHeight;
#endif // CC_FIX_ARTIFACTS_BY_STRECHING_TEXEL


    if ((_flippedX && !_rectRotated) || (_flippedY && _rectRotated))
    {
        std::swap(left, right);
    }

    if ((_flippedY && !_rectRotated) || (_flippedX && _rectRotated))
    {
        std::swap(top, bottom);
    }

    if (_rectRotated)
    {
        outQuad->bl.texCoords.u = left;
        outQuad->bl.texCoords.v = top;
        outQuad->br.texCoords.u = left;
        outQuad->br.texCoords.v = bottom;
        outQuad->tl.texCoords.u = right;
        outQuad->tl.texCoords.v = top;
        outQuad->tr.texCoords.u = right;
        outQuad->tr.texCoords.v = bottom;
    }
    else
    {
        outQuad->bl.texCoords.u = left;
        outQuad->bl.texCoords.v = bottom;
        outQuad->br.texCoords.u = right;
        outQuad->br.texCoords.v = bottom;
        outQuad->tl.texCoords.u = left;
        outQuad->tl.texCoords.v = top;
        outQuad->tr.texCoords.u = right;
        outQuad->tr.texCoords.v = top;
    }
}

void Sprite::setVertexCoords(const Rect& rect, V3F_C4B_T2F_Quad* outQuad)
{
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

    _offsetPosition.x = relativeOffsetX + (_originalContentSize.width - _rect.size.width) / 2;
    _offsetPosition.y = relativeOffsetY + (_originalContentSize.height - _rect.size.height) / 2;

    // FIXME: Streching should be applied to the "offset" as well
    // but probably it should be calculated in the caller function. It will be tidier
    if (_renderMode == RenderMode::QUAD) {
        _offsetPosition.x *= _strechFactor.x;
        _offsetPosition.y *= _strechFactor.y;
    }

    // rendering using batch node
    if (_renderMode == RenderMode::QUAD_BATCHNODE)
    {
        // update dirty_, don't update recursiveDirty_
        setDirty(true);
    }
    else
    {
        // self rendering

        // Atlas: Vertex
        const float x1 = 0.0f + _offsetPosition.x + rect.origin.x;
        const float y1 = 0.0f + _offsetPosition.y + rect.origin.y;
        const float x2 = x1 + rect.size.width;
        const float y2 = y1 + rect.size.height;

        // Don't update Z.
        outQuad->bl.vertices.set(x1, y1, 0.0f);
        outQuad->br.vertices.set(x2, y1, 0.0f);
        outQuad->tl.vertices.set(x1, y2, 0.0f);
        outQuad->tr.vertices.set(x2, y2, 0.0f);
    }
}


// MARK: visit, draw, transform

void Sprite::updateTransform(void)
{
    CCASSERT(_renderMode == RenderMode::QUAD_BATCHNODE, "updateTransform is only valid when Sprite is being rendered using an SpriteBatchNode");

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
            setTextureCoords(_rect);
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
    if (_texture == nullptr)
    {
        return;
    }

#if CC_USE_CULLING
    // Don't calculate the culling if the transform was not updated
    auto visitingCamera = Camera::getVisitingCamera();
    auto defaultCamera = Camera::getDefaultCamera();
    if (visitingCamera == defaultCamera) {
        _insideBounds = ((flags & FLAGS_TRANSFORM_DIRTY) || visitingCamera->isViewProjectionUpdated()) ? renderer->checkVisibility(transform, _contentSize) : _insideBounds;
    }
    else
    {
        // XXX: this always return true since
        _insideBounds = renderer->checkVisibility(transform, _contentSize);
    }

    if(_insideBounds)
#endif
    {
        _trianglesCommand.init(_globalZOrder,
                               _texture,
                               getGLProgramState(),
                               _blendFunc,
                               _polyInfo.triangles,
                               transform,
                               flags);

        renderer->addCommand(&_trianglesCommand);

#if CC_SPRITE_DEBUG_DRAW
        _debugDrawNode->clear();
        auto count = _polyInfo.triangles.indexCount/3;
        auto indices = _polyInfo.triangles.indices;
        auto verts = _polyInfo.triangles.verts;
        for(ssize_t i = 0; i < count; i++)
        {
            //draw 3 lines
            Vec3 from =verts[indices[i*3]].vertices;
            Vec3 to = verts[indices[i*3+1]].vertices;
            _debugDrawNode->drawLine(Vec2(from.x, from.y), Vec2(to.x,to.y), Color4F::WHITE);

            from =verts[indices[i*3+1]].vertices;
            to = verts[indices[i*3+2]].vertices;
            _debugDrawNode->drawLine(Vec2(from.x, from.y), Vec2(to.x,to.y), Color4F::WHITE);

            from =verts[indices[i*3+2]].vertices;
            to = verts[indices[i*3]].vertices;
            _debugDrawNode->drawLine(Vec2(from.x, from.y), Vec2(to.x,to.y), Color4F::WHITE);
        }
#endif //CC_SPRITE_DEBUG_DRAW
    }
}

// MARK: visit, draw, transform

void Sprite::addChild(Node *child, int zOrder, int tag)
{
    CCASSERT(child != nullptr, "Argument must be non-nullptr");
    if (child == nullptr)
    {
        return;
    }

    if (_renderMode == RenderMode::QUAD_BATCHNODE)
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
    if (child == nullptr)
    {
        return;
    }

    if (_renderMode == RenderMode::QUAD_BATCHNODE)
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

    if ((_renderMode == RenderMode::QUAD_BATCHNODE) && ! _reorderChildDirty)
    {
        setReorderChildDirtyRecursively();
        _batchNode->reorderBatch(true);
    }

    Node::reorderChild(child, zOrder);
}

void Sprite::removeChild(Node *child, bool cleanup)
{
    if (_renderMode == RenderMode::QUAD_BATCHNODE)
    {
        _batchNode->removeSpriteFromAtlas((Sprite*)(child));
    }

    Node::removeChild(child, cleanup);
}

void Sprite::removeAllChildrenWithCleanup(bool cleanup)
{
    if (_renderMode == RenderMode::QUAD_BATCHNODE)
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
        sortNodes(_children);

        if (_renderMode == RenderMode::QUAD_BATCHNODE)
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

void Sprite::setIgnoreAnchorPointForPosition(bool value)
{
    CCASSERT(_renderMode != RenderMode::QUAD_BATCHNODE, "setIgnoreAnchorPointForPosition is invalid in Sprite");
    Node::setIgnoreAnchorPointForPosition(value);
}

void Sprite::setVisible(bool bVisible)
{
    Node::setVisible(bVisible);
    SET_DIRTY_RECURSIVELY();
}

void Sprite::setContentSize(const Size& size)
{
    if (_renderMode == RenderMode::QUAD_BATCHNODE || _renderMode == RenderMode::POLYGON)
        CCLOGWARN("Sprite::setContentSize() doesn't strech the sprite when using BATCHNODE or POLYGON render modes");

    Node::setContentSize(size);

    updateStretchFactor();
    updatePoly();
}

void Sprite::setStrechEnabled(bool enabled)
{
    if (_strechEnabled != enabled) {
        _strechEnabled = enabled;

        // disabled centerrect / number of slices if disabled
        if (!enabled)
            setCenterRectNormalized(Rect(0,0,1,1));

        updateStretchFactor();
        updatePoly();
    }
}

bool Sprite::isStrechEnabled() const
{
    return _strechEnabled;
}

void Sprite::updateStretchFactor()
{
    const Size size = getContentSize();

    if (_renderMode == RenderMode::QUAD)
    {
        // If strech is disabled, calculate the strech anyway
        // since it is needed to calculate the offset
        const float x_factor = size.width / _originalContentSize.width;
        const float y_factor = size.height / _originalContentSize.height;

        _strechFactor = Vec2(std::max(0.0f, x_factor),
                             std::max(0.0f, y_factor));
    }
    else if (_renderMode == RenderMode::SLICE9)
    {
        const float x1 = _rect.size.width * _centerRectNormalized.origin.x;
        const float x2 = _rect.size.width * _centerRectNormalized.size.width;
        const float x3 = _rect.size.width * (1 - _centerRectNormalized.origin.x - _centerRectNormalized.size.width);

        const float y1 = _rect.size.height * _centerRectNormalized.origin.y;
        const float y2 = _rect.size.height * _centerRectNormalized.size.height;
        const float y3 = _rect.size.height * (1 - _centerRectNormalized.origin.y - _centerRectNormalized.size.height);

        // adjustedSize = the new _rect size
        const float adjustedWidth = size.width - (_originalContentSize.width - _rect.size.width);
        const float adjustedHeight = size.height - (_originalContentSize.height - _rect.size.height);

        const float x_factor = (adjustedWidth - x1 - x3) / x2;
        const float y_factor = (adjustedHeight - y1 - y3) / y2;

        _strechFactor = Vec2(std::max(0.0f, x_factor),
                             std::max(0.0f, y_factor));
    }

    // else:
    // Do nothing if renderMode is Polygon
}

void Sprite::setFlippedX(bool flippedX)
{
    if (_flippedX != flippedX)
    {
        _flippedX = flippedX;

        if (_renderMode == RenderMode::QUAD_BATCHNODE)
        {
            setDirty(true);
        }
        else if (_renderMode == RenderMode::POLYGON)
        {
            for (ssize_t i = 0; i < _polyInfo.triangles.vertCount; i++) {
                auto& v = _polyInfo.triangles.verts[i].vertices;
                v.x = _contentSize.width -v.x;
            }
        }
        else
        {
            // RenderMode:: Quad or Slice9
            updatePoly();
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

        if (_renderMode == RenderMode::QUAD_BATCHNODE)
        {
            setDirty(true);
        }
        else if (_renderMode == RenderMode::POLYGON)
        {
            for (ssize_t i = 0; i < _polyInfo.triangles.vertCount; i++) {
                auto& v = _polyInfo.triangles.verts[i].vertices;
                v.y = _contentSize.height -v.y;
            }
        }
        else
        {
            // RenderMode:: Quad or Slice9
            updatePoly();
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

    // related to issue #17116
    // when switching from Quad to Slice9, the color will be obtained from _quad
    // so it is important to update _quad colors as well.
    _quad.bl.colors = _quad.tl.colors = _quad.br.colors = _quad.tr.colors = color4;

    // renders using batch node
    if (_renderMode == RenderMode::QUAD_BATCHNODE)
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
    CCASSERT(!spriteFrameName.empty(), "spriteFrameName must not be empty");
    if (spriteFrameName.empty())
    {
        return;
    }

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
    setTextureRect(spriteFrame->getRect(), _rectRotated, spriteFrame->getOriginalSize());

    if (spriteFrame->hasPolygonInfo())
    {
        _polyInfo = spriteFrame->getPolygonInfo();
        _renderMode = RenderMode::POLYGON;
    }
    if (spriteFrame->hasAnchorPoint())
    {
        setAnchorPoint(spriteFrame->getAnchorPoint());
    }
    if (spriteFrame->hasCenterRect())
    {
        setCenterRect(spriteFrame->getCenterRect());
    }
}

void Sprite::setDisplayFrameWithAnimationName(const std::string& animationName, ssize_t frameIndex)
{
    CCASSERT(!animationName.empty(), "CCSprite#setDisplayFrameWithAnimationName. animationName must not be nullptr");
    if (animationName.empty())
    {
        return;
    }

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
                                          CC_SIZE_POINTS_TO_PIXELS(_originalContentSize));
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
        _renderMode = RenderMode::QUAD;
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
        _renderMode = RenderMode::QUAD_BATCHNODE;
        _transformToBatch = Mat4::IDENTITY;
        setTextureAtlas(_batchNode->getTextureAtlas()); // weak ref
    }
}

// MARK: Texture protocol

void Sprite::updateBlendFunc(void)
{
    CCASSERT(_renderMode != RenderMode::QUAD_BATCHNODE, "CCSprite: updateBlendFunc doesn't work when the sprite is rendered using a SpriteBatchNode");

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
    if (_renderMode == RenderMode::QUAD_BATCHNODE)
        texture_id = _batchNode->getTextureAtlas()->getTexture()->getName();
    else
        texture_id = _texture->getName();
    return StringUtils::format("<Sprite | Tag = %d, TextureID = %d>", _tag, texture_id );
}

const PolygonInfo& Sprite::getPolygonInfo() const
{
    return _polyInfo;
}

void Sprite::setPolygonInfo(const PolygonInfo& info)
{
    _polyInfo = info;
    _renderMode = RenderMode::POLYGON;
}

NS_CC_END
