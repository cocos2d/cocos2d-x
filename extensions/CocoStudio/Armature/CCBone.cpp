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

#include "CCBone.h"
#include "CCArmature.h"
#include "utils/CCUtilMath.h"
#include "utils/CCArmatureDataManager.h"
#include "utils/CCTransformHelp.h"
#include "display/CCDisplayManager.h"

NS_CC_EXT_ARMATURE_BEGIN

Bone *Bone::create()
{

    Bone *pBone = new Bone();
    if (pBone && pBone->init())
    {
        pBone->autorelease();
        return pBone;
    }
    CC_SAFE_DELETE(pBone);
    return NULL;

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
    return NULL;
}

Bone::Bone()
{
    _tweenData = NULL;
    _parentBone = NULL;
    _armature = NULL;
    _childArmature = NULL;
    _boneData = NULL;
    _tween = NULL;
    _tween = NULL;
    _children = NULL;
    _displayManager = NULL;
    _ignoreMovementBoneData = false;
    _worldTransform = AffineTransformMake(1, 0, 0, 1, 0, 0);
    _boneTransformDirty = true;
    _blendType = BLEND_NORMAL;
}


Bone::~Bone(void)
{
    CC_SAFE_DELETE(_tweenData);
    CC_SAFE_DELETE(_children);
    CC_SAFE_DELETE(_tween);
    CC_SAFE_DELETE(_displayManager);

    if(_boneData)
    {
        _boneData->release();
    }

    CC_SAFE_RELEASE(_childArmature);
}

bool Bone::init()
{
    return Bone::init(NULL);
}


bool Bone::init(const char *name)
{
    bool bRet = false;
    do
    {

        if(NULL != name)
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


        bRet = true;
    }
    while (0);

    return bRet;
}

void Bone::setBoneData(BoneData *boneData)
{
    CCASSERT(NULL != boneData, "_boneData must not be NULL");

    _boneData = boneData;
    _boneData->retain();

    _name = _boneData->name;
    _ZOrder = _boneData->zOrder;

    _displayManager->initDisplayList(boneData);
}

BoneData *Bone::getBoneData()
{
    return _boneData;
}

void Bone::setArmature(Armature *armature)
{
    _armature = armature;
    if (_armature)
    {
        _tween->setAnimation(_armature->getAnimation());
    }
}


Armature *Bone::getArmature()
{
    return _armature;
}

void Bone::update(float delta)
{
    if (_parentBone)
        _boneTransformDirty = _boneTransformDirty || _parentBone->isTransformDirty();

    if (_boneTransformDirty)
    {
        if (_armature->getArmatureData()->dataVersion >= VERSION_COMBINED)
        {
            TransformHelp::nodeConcat(*_tweenData, *_boneData);
            _tweenData->scaleX -= 1;
            _tweenData->scaleY -= 1;
        }

        TransformHelp::nodeToMatrix(*_tweenData, _worldTransform);

        _worldTransform = AffineTransformConcat(getNodeToParentTransform(), _worldTransform);

        if(_parentBone)
        {
            _worldTransform = AffineTransformConcat(_worldTransform, _parentBone->_worldTransform);
        }
    }

    DisplayFactory::updateDisplay(this, _displayManager->getCurrentDecorativeDisplay(), delta, _boneTransformDirty || _armature->getArmatureTransformDirty());

    Object *object = NULL;
    CCARRAY_FOREACH(_children, object)
    {
        Bone *childBone = (Bone *)object;
        childBone->update(delta);
    }

    _boneTransformDirty = false;
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

void Bone::updateColor()
{
    Node *display = _displayManager->getDisplayRenderNode();
    RGBAProtocol *protocol = dynamic_cast<RGBAProtocol *>(display);
    if(protocol != NULL)
    {
        protocol->setColor(Color3B(_displayedColor.r * _tweenData->r / 255, _displayedColor.g * _tweenData->g / 255, _displayedColor.b * _tweenData->b / 255));
        protocol->setOpacity(_displayedOpacity * _tweenData->a / 255);
    }
}

void Bone::updateZOrder()
{
    if (_armature->getArmatureData()->dataVersion >= VERSION_COMBINED)
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
    CCASSERT( NULL != child, "Argument must be non-nil");
    CCASSERT( NULL == child->_parentBone, "child already added. It can't be added again");

    if(!_children)
    {
        _children = Array::createWithCapacity(4);
        _children->retain();
    }

    if (_children->getIndexOfObject(child) == UINT_MAX)
    {
        _children->addObject(child);
        child->setParentBone(this);
    }
}

void Bone::removeChildBone(Bone *bone, bool recursion)
{
    if ( _children->getIndexOfObject(bone) != UINT_MAX )
    {
        if(recursion)
        {
            Array *_ccbones = bone->_children;
            Object *_object = NULL;
            CCARRAY_FOREACH(_ccbones, _object)
            {
                Bone *_ccBone = (Bone *)_object;
                bone->removeChildBone(_ccBone, recursion);
            }
        }

        bone->setParentBone(NULL);

        bone->getDisplayManager()->setCurrentDecorativeDisplay(NULL);

        _children->removeObject(bone);
    }
}

void Bone::removeFromParent(bool recursion)
{
    if (NULL != _parentBone)
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
        CC_SAFE_RETAIN(armature);
        CC_SAFE_RELEASE(_childArmature);
        _childArmature = armature;
    }
}

Armature *Bone::getChildArmature()
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

void Bone::setTransformDirty(bool dirty)
{
    _boneTransformDirty = dirty;
}

bool Bone::isTransformDirty()
{
    return _boneTransformDirty;
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

void Bone::addDisplay(DisplayData *displayData, int index)
{
    _displayManager->addDisplay(displayData, index);
}

void Bone::addDisplay(Node *display, int index)
{
    _displayManager->addDisplay(display, index);
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
    return NULL;
}


NS_CC_EXT_ARMATURE_END
