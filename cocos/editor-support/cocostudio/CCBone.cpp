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

#include "cocostudio/CCBone.h"
#include "cocostudio/CCArmature.h"
#include "cocostudio/CCUtilMath.h"
#include "cocostudio/CCArmatureDataManager.h"
#include "cocostudio/CCTransformHelp.h"
#include "cocostudio/CCDisplayManager.h"

using namespace cocos2d;

namespace cocostudio {

Bone *Bone::create()
{

    Bone *pBone = new Bone();
    if (pBone && pBone->init())
    {
        pBone->autorelease();
        return pBone;
    }
    CC_SAFE_DELETE(pBone);
    return nullptr;

}

Bone *Bone::create(const char *name)
{

    Bone *pBone = new Bone();
    if (pBone && pBone->init(name))
    {
        pBone->autorelease();
        return pBone;
    }
    CC_SAFE_DELETE(pBone);
    return nullptr;
}

Bone::Bone()
{
    _tweenData = nullptr;
    _parentBone = nullptr;
    _armature = nullptr;
    _childArmature = nullptr;
    _boneData = nullptr;
    _tween = nullptr;
    _tween = nullptr;
    _children = nullptr;
    _displayManager = nullptr;
    _ignoreMovementBoneData = false;
    _worldTransform = AffineTransformMake(1, 0, 0, 1, 0, 0);
    _boneTransformDirty = true;
    _blendType = BLEND_NORMAL;
    _worldInfo = nullptr;

    _armatureParentBone = nullptr;
    _dataVersion = 0;
}


Bone::~Bone(void)
{
    CC_SAFE_DELETE(_tweenData);
    CC_SAFE_DELETE(_children);
    CC_SAFE_DELETE(_tween);
    CC_SAFE_DELETE(_displayManager);
    CC_SAFE_DELETE(_worldInfo);

    CC_SAFE_RELEASE_NULL(_boneData);

    CC_SAFE_RELEASE(_childArmature);
}

bool Bone::init()
{
    return Bone::init(nullptr);
}


bool Bone::init(const char *name)
{
    bool bRet = false;
    do
    {

        if(nullptr != name)
        {
            _name = name;
        }

        CC_SAFE_DELETE(_tweenData);
        _tweenData = new FrameData();

        CC_SAFE_DELETE(_tween);
        _tween = new Tween();
        _tween->init(this);

        CC_SAFE_DELETE(_displayManager);
        _displayManager = new DisplayManager();
        _displayManager->init(this);

        CC_SAFE_DELETE(_worldInfo);
        _worldInfo = new BaseData();

        CC_SAFE_DELETE(_boneData);
        _boneData  = new BoneData();

        bRet = true;
    }
    while (0);

    return bRet;
}

void Bone::setBoneData(BoneData *boneData)
{
    CCASSERT(nullptr != boneData, "_boneData must not be nullptr");

    if (_boneData != boneData)
    {
        CC_SAFE_RETAIN(boneData);
        CC_SAFE_RELEASE(_boneData);
        _boneData = boneData;
    }

    _name = _boneData->name;
    _ZOrder = _boneData->zOrder;

    _displayManager->initDisplayList(boneData);
}

BoneData *Bone::getBoneData() const
{
    return _boneData;
}

void Bone::setArmature(Armature *armature)
{
    _armature = armature;
    if (_armature)
    {
        _tween->setAnimation(_armature->getAnimation());
        _dataVersion = _armature->getArmatureData()->dataVersion;
        _armatureParentBone = _armature->getParentBone();
    }
    else
    {
        _armatureParentBone = nullptr;
    }
}


Armature *Bone::getArmature() const
{
    return _armature;
}

void Bone::update(float delta)
{
    if (_parentBone)
        _boneTransformDirty = _boneTransformDirty || _parentBone->isTransformDirty();

    if (_armatureParentBone && !_boneTransformDirty)
    {
        _boneTransformDirty = _armatureParentBone->isTransformDirty();
    }

    if (_boneTransformDirty)
    {
        if (_dataVersion >= VERSION_COMBINED)
        {
            TransformHelp::nodeConcat(*_tweenData, *_boneData);
            _tweenData->scaleX -= 1;
            _tweenData->scaleY -= 1;
        }

        _worldInfo->copy(_tweenData);

        _worldInfo->x = _tweenData->x + _position.x;
        _worldInfo->y = _tweenData->y + _position.y;
        _worldInfo->scaleX = _tweenData->scaleX * _scaleX;
        _worldInfo->scaleY = _tweenData->scaleY * _scaleY;
        _worldInfo->skewX = _tweenData->skewX + _skewX + _rotationX;
        _worldInfo->skewY = _tweenData->skewY + _skewY - _rotationY;

        if(_parentBone)
        {
            applyParentTransform(_parentBone);
        }
        else
        {
            if (_armatureParentBone)
            {
                applyParentTransform(_armatureParentBone);
            }
        }

        TransformHelp::nodeToMatrix(*_worldInfo, _worldTransform);

        if (_armatureParentBone)
        {
            _worldTransform = AffineTransformConcat(_worldTransform, _armature->getNodeToParentTransform());
        }
    }

    DisplayFactory::updateDisplay(this, delta, _boneTransformDirty || _armature->getArmatureTransformDirty());

    if (_children)
    {
        for(auto object : *_children)
        {
            Bone *childBone = (Bone *)object;
            childBone->update(delta);
        }
    }

    _boneTransformDirty = false;
}

void Bone::applyParentTransform(Bone *parent) 
{
    float x = _worldInfo->x;
    float y = _worldInfo->y;
    _worldInfo->x = x * parent->_worldTransform.a + y * parent->_worldTransform.c + parent->_worldInfo->x;
    _worldInfo->y = x * parent->_worldTransform.b + y * parent->_worldTransform.d + parent->_worldInfo->y;
    _worldInfo->scaleX = _worldInfo->scaleX * parent->_worldInfo->scaleX;
    _worldInfo->scaleY = _worldInfo->scaleY * parent->_worldInfo->scaleY;
    _worldInfo->skewX = _worldInfo->skewX + parent->_worldInfo->skewX;
    _worldInfo->skewY = _worldInfo->skewY + parent->_worldInfo->skewY;
}


void Bone::updateDisplayedColor(const Color3B &parentColor)
{
    _realColor = Color3B(255, 255, 255);
    NodeRGBA::updateDisplayedColor(parentColor);
    updateColor();
}

void Bone::updateDisplayedOpacity(GLubyte parentOpacity)
{
    _realOpacity = 255;
    NodeRGBA::updateDisplayedOpacity(parentOpacity);
    updateColor();
}

void Bone::setColor(const Color3B& color)
{
    NodeRGBA::setColor(color);
    updateColor();
}

void Bone::setOpacity(GLubyte opacity)
{
    NodeRGBA::setOpacity(opacity);
    updateColor();
}

void Bone::updateColor()
{
    Node *display = _displayManager->getDisplayRenderNode();
    RGBAProtocol *protocol = dynamic_cast<RGBAProtocol *>(display);
    if(protocol != nullptr)
    {
        protocol->setColor(Color3B(_displayedColor.r * _tweenData->r / 255, _displayedColor.g * _tweenData->g / 255, _displayedColor.b * _tweenData->b / 255));
        protocol->setOpacity(_displayedOpacity * _tweenData->a / 255);
    }
}

void Bone::updateZOrder()
{
    if (_dataVersion >= VERSION_COMBINED)
    {
        int zorder = _tweenData->zOrder + _boneData->zOrder;
        setZOrder(zorder);
    }
    else
    {
        setZOrder(_tweenData->zOrder);
    }
}

void Bone::addChildBone(Bone *child)
{
    CCASSERT( nullptr != child, "Argument must be non-nil");
    CCASSERT( nullptr == child->_parentBone, "child already added. It can't be added again");

    if(!_children)
    {
        _children = Array::createWithCapacity(4);
        _children->retain();
    }

    if (_children->getIndexOfObject(child) == CC_INVALID_INDEX)
    {
        _children->addObject(child);
        child->setParentBone(this);
    }
}

void Bone::removeChildBone(Bone *bone, bool recursion)
{
    if (_children && _children->getIndexOfObject(bone) != CC_INVALID_INDEX )
    {
        if(recursion)
        {
            Array *ccbones = bone->_children;
            
            for(auto object : *ccbones)
            {
                Bone *ccBone = (Bone *)object;
                bone->removeChildBone(ccBone, recursion);
            }
        }

        bone->setParentBone(nullptr);

        bone->getDisplayManager()->setCurrentDecorativeDisplay(nullptr);

        _children->removeObject(bone);
    }
}

void Bone::removeFromParent(bool recursion)
{
    if (nullptr != _parentBone)
    {
        _parentBone->removeChildBone(this, recursion);
    }
}

void Bone::setParentBone(Bone *parent)
{
    _parentBone = parent;
}

Bone *Bone::getParentBone()
{
    return _parentBone;
}

void Bone::setChildArmature(Armature *armature)
{
    if (_childArmature != armature)
    {
        if (armature == nullptr && _childArmature)
        {
            _childArmature->setParentBone(nullptr);
        }

        CC_SAFE_RETAIN(armature);
        CC_SAFE_RELEASE(_childArmature);
        _childArmature = armature;
    }
}

Armature *Bone::getChildArmature() const
{
    return _childArmature;
}

Tween *Bone::getTween()
{
    return _tween;
}

void Bone::setZOrder(int zOrder)
{
    if (_ZOrder != zOrder)
        Node::setZOrder(zOrder);
}

AffineTransform Bone::getNodeToArmatureTransform() const
{
    return _worldTransform;
}

AffineTransform Bone::getNodeToWorldTransform() const
{
    return AffineTransformConcat(_worldTransform, _armature->getNodeToWorldTransform());
}

Node *Bone::getDisplayRenderNode()
{
    return _displayManager->getDisplayRenderNode();
}

DisplayType Bone::getDisplayRenderNodeType()
{
    return _displayManager->getDisplayRenderNodeType();
}


void Bone::addDisplay(DisplayData *displayData, int index)
{
    _displayManager->addDisplay(displayData, index);
}

void Bone::addDisplay(Node *display, int index)
{
    _displayManager->addDisplay(display, index);
}

void Bone::removeDisplay(int index)
{
    _displayManager->removeDisplay(index);
}

void Bone::changeDisplayByIndex(int index, bool force)
{
    _displayManager->changeDisplayByIndex(index, force);
}

Array *Bone::getColliderBodyList()
{
    if (DecorativeDisplay *decoDisplay = _displayManager->getCurrentDecorativeDisplay())
    {
        if (ColliderDetector *detector = decoDisplay->getColliderDetector())
        {
            return detector->getColliderBodyList();
        }
    }
    return nullptr;
}



void Bone::setColliderFilter(ColliderFilter *filter)
{
    Array *array = _displayManager->getDecorativeDisplayList();

    for(auto object : *array)
    {
        DecorativeDisplay *decoDisplay = static_cast<DecorativeDisplay *>(object);
        if (ColliderDetector *detector = decoDisplay->getColliderDetector())
        {
            detector->setColliderFilter(filter);
        }
    }
}
ColliderFilter *Bone::getColliderFilter()
{
    if (DecorativeDisplay *decoDisplay = _displayManager->getCurrentDecorativeDisplay())
    {
        if (ColliderDetector *detector = decoDisplay->getColliderDetector())
        {
            return detector->getColliderFilter();
        }
    }
    return nullptr;
}


}
