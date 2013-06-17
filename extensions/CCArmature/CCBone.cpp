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

CCBone *CCBone::create()
{

    CCBone *pBone = new CCBone();
    if (pBone && pBone->init())
    {
        pBone->autorelease();
        return pBone;
    }
    CC_SAFE_DELETE(pBone);
    return NULL;

}

CCBone *CCBone::create(const char *name)
{

    CCBone *pBone = new CCBone();
    if (pBone && pBone->init(name))
    {
        pBone->autorelease();
        return pBone;
    }
    CC_SAFE_DELETE(pBone);
    return NULL;
}

CCBone::CCBone()
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
    _worldTransform = CCAffineTransformMake(1, 0, 0, 1, 0, 0);
    _transformDirty = true;
}


CCBone::~CCBone(void)
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

bool CCBone::init()
{
    return CCBone::init(NULL);
}


bool CCBone::init(const char *name)
{
    bool bRet = false;
    do
    {

        if(NULL != name)
        {
            _name = name;
        }

        CC_SAFE_DELETE(_tweenData);
        _tweenData = new CCFrameData();

        CC_SAFE_DELETE(_tween);
        _tween = new CCTween();
        _tween->init(this);

        CC_SAFE_DELETE(_displayManager);
        _displayManager = new CCDisplayManager();
        _displayManager->init(this);


        bRet = true;
    }
    while (0);

    return bRet;
}

void CCBone::setBoneData(CCBoneData *boneData)
{
    CCAssert(NULL != boneData, "_boneData must not be NULL");

    _boneData = boneData;
    _boneData->retain();

    _name = _boneData->name;
    _ZOrder = _boneData->zOrder;

    _displayManager->initDisplayList(boneData);
}

CCBoneData *CCBone::getBoneData()
{
    return _boneData;
}

void CCBone::setArmature(CCArmature *armature)
{
	_armature = armature;
	_tween->setAnimation(_armature->getAnimation());
}


CCArmature *CCBone::getArmature()
{
	return _armature;
}

void CCBone::update(float delta)
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

        _worldTransform = CCAffineTransformConcat(nodeToParentTransform(), _worldTransform);

        if(_parent)
        {
            _worldTransform = CCAffineTransformConcat(_worldTransform, _parent->_worldTransform);
        }
    }

    CCDisplayFactory::updateDisplay(this, _displayManager->getCurrentDecorativeDisplay(), delta, _transformDirty);

    CCObject *object = NULL;
    CCARRAY_FOREACH(_children, object)
    {
        CCBone *childBone = (CCBone *)object;
        childBone->update(delta);
    }

    _transformDirty = false;
}


void CCBone::updateDisplayedColor(const ccColor3B &parentColor)
{
    CCNodeRGBA::updateDisplayedColor(parentColor);
    updateColor();
}

void CCBone::updateDisplayedOpacity(GLubyte parentOpacity)
{
    CCNodeRGBA::updateDisplayedOpacity(parentOpacity);
    updateColor();
}

void CCBone::updateColor()
{
    CCNode *display = _displayManager->getDisplayRenderNode();
    CCRGBAProtocol *protocol = dynamic_cast<CCRGBAProtocol *>(display);
    if(protocol != NULL)
    {
        protocol->setColor(ccc3(_displayedColor.r * _tweenData->r / 255, _displayedColor.g * _tweenData->g / 255, _displayedColor.b * _tweenData->b / 255));
        protocol->setOpacity(_displayedOpacity * _tweenData->a / 255);
    }
}


void CCBone::addChildBone(CCBone *child)
{
    CCAssert( NULL != child, "Argument must be non-nil");
    CCAssert( NULL == child->_parent, "child already added. It can't be added again");

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

void CCBone::removeChildBone(CCBone *bone, bool recursion)
{
    if ( _children->indexOfObject(bone) != UINT_MAX )
    {
        if(recursion)
        {
            CCArray *_ccbones = bone->_children;
            CCObject *_object = NULL;
            CCARRAY_FOREACH(_ccbones, _object)
            {
                CCBone *_ccBone = (CCBone *)_object;
                bone->removeChildBone(_ccBone, recursion);
            }
        }

        bone->setParentBone(NULL);

        bone->getDisplayManager()->setCurrentDecorativeDisplay(NULL);

        _children->removeObject(bone);
    }
}

void CCBone::removeFromParent(bool recursion)
{
    if (NULL != _parent)
    {
        _parent->removeChildBone(this, recursion);
    }
}

void CCBone::setParentBone(CCBone *parent)
{
    _parent = parent;
}

CCBone *CCBone::getParentBone()
{
    return _parent;
}

void CCBone::childrenAlloc(void)
{
    CC_SAFE_DELETE(_children);
    _children = CCArray::createWithCapacity(4);
    _children->retain();
}


void CCBone::setChildArmature(CCArmature *armature)
{
    if (_childArmature != armature)
    {
        CC_SAFE_RETAIN(armature);
        CC_SAFE_RELEASE(_childArmature);
        _childArmature = armature;
    }
}

CCArmature *CCBone::getChildArmature()
{
    return _childArmature;
}

CCArray *CCBone::getChildren()
{
    return _children;
}

CCTween *CCBone::getTween()
{
    return _tween;
}

void CCBone::setZOrder(int zOrder)
{
    if (_ZOrder != zOrder)
        CCNode::setZOrder(zOrder);
}

void CCBone::setTransformDirty(bool dirty)
{
	_transformDirty = dirty;
}

bool CCBone::isTransformDirty()
{
	return _transformDirty;
}

CCAffineTransform CCBone::nodeToArmatureTransform()
{
	return _worldTransform;
}

void CCBone::addDisplay(CCDisplayData *_displayData, int _index)
{
    _displayManager->addDisplay(_displayData, _index);
}

void CCBone::changeDisplayByIndex(int _index, bool _force)
{
    _displayManager->changeDisplayByIndex(_index, _force);
}

}}} // namespace cocos2d { namespace extension { namespace armature {
