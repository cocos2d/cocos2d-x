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

namespace cocos2d { namespace extension { namespace armature {

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
    _parent = NULL;
    _armature = NULL;
    _childArmature = NULL;
    _boneData = NULL;
    _tween = NULL;
    _tween = NULL;
    _children = NULL;
    _displayManager = NULL;
    _ignoreMovementBoneData = false;
    _worldTransform = AffineTransformMake(1, 0, 0, 1, 0, 0);
    _transformDirty = true;
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
	_tween->setAnimation(_armature->getAnimation());
}


Armature *Bone::getArmature()
{
	return _armature;
}

void Bone::update(float delta)
{
    if (_parent)
        _transformDirty = _transformDirty || _parent->isTransformDirty();

    if (_transformDirty)
    {
        float cosX	= cos(_tweenData->skewX);
        float cosY	= cos(_tweenData->skewY);
        float sinX	= sin(_tweenData->skewX);
        float sinY  = sin(_tweenData->skewY);

        _worldTransform.a = _tweenData->scaleX * cosY;
        _worldTransform.b = _tweenData->scaleX * sinY;
        _worldTransform.c = _tweenData->scaleY * sinX;
        _worldTransform.d = _tweenData->scaleY * cosX;
        _worldTransform.tx = _tweenData->x;
        _worldTransform.ty = _tweenData->y;

        _worldTransform = AffineTransformConcat(getNodeToParentTransform(), _worldTransform);

        if(_parent)
        {
            _worldTransform = AffineTransformConcat(_worldTransform, _parent->_worldTransform);
        }
    }

    DisplayFactory::updateDisplay(this, _displayManager->getCurrentDecorativeDisplay(), delta, _transformDirty);

    Object *object = NULL;
    CCARRAY_FOREACH(_children, object)
    {
        Bone *childBone = static_cast<Bone *>(object);
        childBone->update(delta);
    }

    _transformDirty = false;
}


void Bone::updateDisplayedColor(const Color3B &parentColor)
{
    NodeRGBA::updateDisplayedColor(parentColor);
    updateColor();
}

void Bone::updateDisplayedOpacity(GLubyte parentOpacity)
{
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


void Bone::addChildBone(Bone *child)
{
    CCASSERT( NULL != child, "Argument must be non-nil");
    CCASSERT( NULL == child->_parent, "child already added. It can't be added again");

    if(!_children)
    {
        childrenAlloc();
    }

    if (_children->indexOfObject(child) == UINT_MAX)
    {
        _children->addObject(child);
        child->setParentBone(this);
    }
}

void Bone::removeChildBone(Bone *bone, bool recursion)
{
    if ( _children->indexOfObject(bone) != UINT_MAX )
    {
        if(recursion)
        {
            Array *_ccbones = bone->_children;
            Object *_object = NULL;
            CCARRAY_FOREACH(_ccbones, _object)
            {
                Bone *_ccBone = static_cast<Bone *>(_object);
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
    if (NULL != _parent)
    {
        _parent->removeChildBone(this, recursion);
    }
}

void Bone::setParentBone(Bone *parent)
{
    _parent = parent;
}

Bone *Bone::getParentBone()
{
    return _parent;
}

void Bone::childrenAlloc(void)
{
    CC_SAFE_DELETE(_children);
    _children = Array::createWithCapacity(4);
    _children->retain();
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

Array *Bone::getChildren()
{
    return _children;
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
	_transformDirty = dirty;
}

bool Bone::isTransformDirty()
{
	return _transformDirty;
}

AffineTransform Bone::nodeToArmatureTransform()
{
	return _worldTransform;
}

void Bone::addDisplay(DisplayData *_displayData, int _index)
{
    _displayManager->addDisplay(_displayData, _index);
}

void Bone::changeDisplayByIndex(int _index, bool _force)
{
    _displayManager->changeDisplayByIndex(_index, _force);
}

}}} // namespace cocos2d { namespace extension { namespace armature {
