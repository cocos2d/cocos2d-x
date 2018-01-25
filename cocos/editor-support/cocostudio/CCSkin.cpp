/****************************************************************************
Copyright (c) 2013-2016 Chukong Technologies Inc.
Copyright (c) 2017-2018 Xiamen Yaji Software Co., Ltd.

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

#include "2d/CCSpriteFrame.h"
#include "2d/CCSpriteFrameCache.h"
#include "base/CCDirector.h"
#include "renderer/CCRenderer.h"

#include "editor-support/cocostudio/CCSkin.h"
#include "editor-support/cocostudio/CCTransformHelp.h"
#include "editor-support/cocostudio/CCArmature.h"


using namespace cocos2d;

namespace cocostudio {

#if CC_SPRITEBATCHNODE_RENDER_SUBPIXEL
#define RENDER_IN_SUBPIXEL
#else
#define RENDER_IN_SUBPIXEL(__ARGS__) (ceil(__ARGS__))
#endif

Skin *Skin::create()
{
    Skin *skin = new (std::nothrow) Skin();
    if(skin && skin->init())
    {
        skin->autorelease();
        return skin;
    }
    CC_SAFE_DELETE(skin);
    return nullptr;
}

Skin *Skin::createWithSpriteFrameName(const std::string& pszSpriteFrameName)
{
    Skin *skin = new (std::nothrow) Skin();
    if(skin && skin->initWithSpriteFrameName(pszSpriteFrameName))
    {
        skin->autorelease();
        return skin;
    }
    CC_SAFE_DELETE(skin);
    return nullptr;
}

Skin *Skin::create(const std::string& pszFileName)
{
    Skin *skin = new (std::nothrow) Skin();
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
    _skinTransform = Mat4::IDENTITY;
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
        CCLOG("Can't find CCSpriteFrame with %s. Please check your .plist file", spriteFrameName.c_str());
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
    setRotationSkewX(CC_RADIANS_TO_DEGREES(_skinData.skewX));
    setRotationSkewY(CC_RADIANS_TO_DEGREES(-_skinData.skewY));
    setPosition(_skinData.x, _skinData.y);

    _skinTransform = getNodeToParentTransform();
    updateArmatureTransform();
}

const BaseData &Skin::getSkinData() const
{
    return _skinData;
}

void Skin::updateArmatureTransform()
{
    _transform = TransformConcat(_bone->getNodeToArmatureTransform(), _skinTransform);
//    if(_armature && _armature->getBatchNode())
//    {
//        _transform = TransformConcat(_transform, _armature->getNodeToParentTransform());
//    }
}

void Skin::updateTransform()
{
    // If it is not visible, or one of its ancestors is not visible, then do nothing:
    if( !_visible)
    {
        _quad.br.vertices.setZero();
        _quad.tl.vertices.setZero();
        _quad.tr.vertices.setZero();
        _quad.bl.vertices.setZero();
    }
    else
    {
        //
        // calculate the Quad based on the Affine Matrix
        //
        Mat4 transform = getNodeToParentTransform();

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
        
        float x = transform.m[12];
        float y = transform.m[13];

        float cr = transform.m[0];
        float sr = transform.m[1];
        float cr2 = transform.m[5];
        float sr2 = -transform.m[4];
        float ax = x1 * cr - y1 * sr2 + x;
        float ay = x1 * sr + y1 * cr2 + y;

        float bx = x2 * cr - y1 * sr2 + x;
        float by = x2 * sr + y1 * cr2 + y;

        float cx = x2 * cr - y2 * sr2 + x;
        float cy = x2 * sr + y2 * cr2 + y;

        float dx = x1 * cr - y2 * sr2 + x;
        float dy = x1 * sr + y2 * cr2 + y;

        _quad.bl.vertices.set(RENDER_IN_SUBPIXEL(ax), RENDER_IN_SUBPIXEL(ay), _positionZ);
        _quad.br.vertices.set(RENDER_IN_SUBPIXEL(bx), RENDER_IN_SUBPIXEL(by), _positionZ);
        _quad.tl.vertices.set(RENDER_IN_SUBPIXEL(dx), RENDER_IN_SUBPIXEL(dy), _positionZ);
        _quad.tr.vertices.set(RENDER_IN_SUBPIXEL(cx), RENDER_IN_SUBPIXEL(cy), _positionZ);
    }

    // MARMALADE CHANGE: ADDED CHECK FOR nullptr, TO PERMIT SPRITES WITH NO BATCH NODE / TEXTURE ATLAS
    if (_textureAtlas)
    {
        _textureAtlas->updateQuad(&_quad, _textureAtlas->getTotalQuads());
    }
}

Mat4 Skin::getNodeToWorldTransform() const
{
    return TransformConcat( _bone->getArmature()->getNodeToWorldTransform(), _transform);
}

Mat4 Skin::getNodeToWorldTransformAR() const
{
    Mat4 displayTransform = _transform;
    Vec2 anchorPoint =  _anchorPointInPoints;

    anchorPoint = PointApplyTransform(anchorPoint, displayTransform);

    displayTransform.m[12] = anchorPoint.x;
    displayTransform.m[13] = anchorPoint.y;

    return TransformConcat( _bone->getArmature()->getNodeToWorldTransform(),displayTransform);
}

void Skin::draw(Renderer *renderer, const Mat4 &/*transform*/, uint32_t flags)
{
    auto mv = Director::getInstance()->getMatrix(MATRIX_STACK_TYPE::MATRIX_STACK_MODELVIEW);

    // TODO: implement z order
    _quadCommand.init(_globalZOrder, 
        _texture, 
        getGLProgramState(), 
        _blendFunc, 
        &_quad, 
        1,
        mv, 
        flags);

    renderer->addCommand(&_quadCommand);
}

void Skin::setBone(Bone *bone)
{
    _bone = bone;
    if(Armature *armature = _bone->getArmature())
    {
        _armature = armature;
    }
}

Bone *Skin::getBone() const
{
    return _bone;
}

}
