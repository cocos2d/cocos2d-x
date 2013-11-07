/****************************************************************************
Copyright (c) 2013 cocos2d-x.org

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

#include "cocostudio/CCSkin.h"
#include "cocostudio/CCTransformHelp.h"
#include "cocostudio/CCSpriteFrameCacheHelper.h"
#include "cocostudio/CCArmature.h"

using namespace cocos2d;

namespace cocostudio {

#if CC_SPRITEBATCHNODE_RENDER_SUBPIXEL
#define RENDER_IN_SUBPIXEL
#else
#define RENDER_IN_SUBPIXEL(__ARGS__) (ceil(__ARGS__))
#endif

#define SET_VERTEX3F(_v_, _x_, _y_, _z_) (_v_).x = (_x_); (_v_).y = (_y_); (_v_).z = (_z_);

Skin *Skin::create()
{
    Skin *skin = new Skin();
    if(skin && skin->init())
    {
        skin->autorelease();
        return skin;
    }
    CC_SAFE_DELETE(skin);
    return nullptr;
}

Skin *Skin::createWithSpriteFrameName(const char *pszSpriteFrameName)
{
    Skin *skin = new Skin();
    if(skin && skin->initWithSpriteFrameName(pszSpriteFrameName))
    {
        skin->autorelease();
        return skin;
    }
    CC_SAFE_DELETE(skin);
    return nullptr;
}

Skin *Skin::create(const char *pszFileName)
{
    Skin *skin = new Skin();
    if(skin && skin->initWithFile(pszFileName))
    {
        skin->autorelease();
        return skin;
    }
    CC_SAFE_DELETE(skin);
    return nullptr;
}

Skin::Skin()
    : _bone(nullptr)
    , _armature(nullptr)
    , _displayName("")
{
    _skinTransform = AffineTransformIdentity;
}

bool Skin::initWithSpriteFrameName(const std::string& spriteFrameName)
{
    CCAssert(spriteFrameName != "", "");

    SpriteFrame *pFrame = SpriteFrameCache::getInstance()->getSpriteFrameByName(spriteFrameName);
    bool ret = true;

    if (pFrame != nullptr)
    {
        ret = initWithSpriteFrame(pFrame);
    }
    else
    {
        CCLOG("Cann't find CCSpriteFrame with %s. Please check your .plist file", spriteFrameName.c_str());
        ret = false;
    }

    _displayName = spriteFrameName;

    return ret;
}

bool Skin::initWithFile(const std::string& filename)
{
    bool ret = Sprite::initWithFile(filename);

    _displayName = filename;

    return ret;
}

void Skin::setSkinData(const BaseData &var)
{
    _skinData = var;

    setScaleX(_skinData.scaleX);
    setScaleY(_skinData.scaleY);
    setRotationX(CC_RADIANS_TO_DEGREES(_skinData.skewX));
    setRotationY(CC_RADIANS_TO_DEGREES(-_skinData.skewY));
    setPosition(Point(_skinData.x, _skinData.y));

    _skinTransform = getNodeToParentTransform();
    updateArmatureTransform();
}

const BaseData &Skin::getSkinData() const
{
    return _skinData;
}

void Skin::updateArmatureTransform()
{
    _transform = AffineTransformConcat(_skinTransform, _bone->getNodeToArmatureTransform());
    if(_armature && _armature->getBatchNode())
    {
        _transform = AffineTransformConcat(_transform, _armature->getNodeToParentTransform());
    }
}

void Skin::updateTransform()
{
    // If it is not visible, or one of its ancestors is not visible, then do nothing:
    if( !_visible)
    {
        _quad.br.vertices = _quad.tl.vertices = _quad.tr.vertices = _quad.bl.vertices = Vertex3F(0, 0, 0);
    }
    else
    {
        //
        // calculate the Quad based on the Affine Matrix
        //

        Size &size = _rect.size;

        float x1 = _offsetPosition.x;
        float y1 = _offsetPosition.y;

        float x2 = x1 + size.width;
        float y2 = y1 + size.height;

        float x = _transform.tx;
        float y = _transform.ty;

        float cr = _transform.a;
        float sr = _transform.b;
        float cr2 = _transform.d;
        float sr2 = -_transform.c;
        float ax = x1 * cr - y1 * sr2 + x;
        float ay = x1 * sr + y1 * cr2 + y;

        float bx = x2 * cr - y1 * sr2 + x;
        float by = x2 * sr + y1 * cr2 + y;

        float cx = x2 * cr - y2 * sr2 + x;
        float cy = x2 * sr + y2 * cr2 + y;

        float dx = x1 * cr - y2 * sr2 + x;
        float dy = x1 * sr + y2 * cr2 + y;

        SET_VERTEX3F( _quad.bl.vertices, RENDER_IN_SUBPIXEL(ax), RENDER_IN_SUBPIXEL(ay), _vertexZ );
        SET_VERTEX3F( _quad.br.vertices, RENDER_IN_SUBPIXEL(bx), RENDER_IN_SUBPIXEL(by), _vertexZ );
        SET_VERTEX3F( _quad.tl.vertices, RENDER_IN_SUBPIXEL(dx), RENDER_IN_SUBPIXEL(dy), _vertexZ );
        SET_VERTEX3F( _quad.tr.vertices, RENDER_IN_SUBPIXEL(cx), RENDER_IN_SUBPIXEL(cy), _vertexZ );
    }

    // MARMALADE CHANGE: ADDED CHECK FOR nullptr, TO PERMIT SPRITES WITH NO BATCH NODE / TEXTURE ATLAS
    if (_textureAtlas)
    {
        _textureAtlas->updateQuad(&_quad, _textureAtlas->getTotalQuads());
    }
}

AffineTransform Skin::getNodeToWorldTransform() const
{
    return AffineTransformConcat(_transform, _bone->getArmature()->getNodeToWorldTransform());
}

AffineTransform Skin::getNodeToWorldTransformAR() const
{
    AffineTransform displayTransform = _transform;
    Point anchorPoint =  _anchorPointInPoints;

    anchorPoint = PointApplyAffineTransform(anchorPoint, displayTransform);

    displayTransform.tx = anchorPoint.x;
    displayTransform.ty = anchorPoint.y;

    return AffineTransformConcat(displayTransform, _bone->getArmature()->getNodeToWorldTransform());
}

void Skin::setBone(Bone *bone)
{
    _bone = bone;
    if(Armature *armature = _bone->getArmature())
    {
        _armature = armature;
        TextureAtlas *atlas = armature->getTexureAtlasWithTexture(_texture);
        setTextureAtlas(atlas);
    }
}

Bone *Skin::getBone() const
{
    return _bone;
}

}
