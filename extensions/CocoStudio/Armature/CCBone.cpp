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
    m_pTweenData = NULL;
    m_pParentBone = NULL;
    m_pArmature = NULL;
    m_pChildArmature = NULL;
    m_pBoneData = NULL;
    m_pTween = NULL;
    m_pTween = NULL;
    _children = NULL;
    m_pDisplayManager = NULL;
    m_bIgnoreMovementBoneData = false;
    m_tWorldTransform = AffineTransformMake(1, 0, 0, 1, 0, 0);
    m_bBoneTransformDirty = true;
    m_eBlendType = BLEND_NORMAL;
}


Bone::~Bone(void)
{
    CC_SAFE_DELETE(m_pTweenData);
    CC_SAFE_DELETE(_children);
    CC_SAFE_DELETE(m_pTween);
    CC_SAFE_DELETE(m_pDisplayManager);

    if(m_pBoneData)
    {
        m_pBoneData->release();
    }

    CC_SAFE_RELEASE(m_pChildArmature);
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
            m_strName = name;
        }

        CC_SAFE_DELETE(m_pTweenData);
        m_pTweenData = new FrameData();

        CC_SAFE_DELETE(m_pTween);
        m_pTween = new Tween();
        m_pTween->init(this);

        CC_SAFE_DELETE(m_pDisplayManager);
        m_pDisplayManager = new DisplayManager();
        m_pDisplayManager->init(this);


        bRet = true;
    }
    while (0);

    return bRet;
}

void Bone::setBoneData(BoneData *boneData)
{
    CCAssert(NULL != boneData, "_boneData must not be NULL");

    m_pBoneData = boneData;
    m_pBoneData->retain();

    m_strName = m_pBoneData->name;
    _ZOrder = m_pBoneData->zOrder;

    m_pDisplayManager->initDisplayList(boneData);
}

BoneData *Bone::getBoneData()
{
    return m_pBoneData;
}

void Bone::setArmature(Armature *armature)
{
    m_pArmature = armature;
    if (m_pArmature)
    {
        m_pTween->setAnimation(m_pArmature->getAnimation());
    }
}


Armature *Bone::getArmature()
{
    return m_pArmature;
}

void Bone::update(float delta)
{
    if (m_pParentBone)
        m_bBoneTransformDirty = m_bBoneTransformDirty || m_pParentBone->isTransformDirty();

    if (m_bBoneTransformDirty)
    {
        if (m_pArmature->getArmatureData()->dataVersion >= VERSION_COMBINED)
        {
            TransformHelp::nodeConcat(*m_pTweenData, *m_pBoneData);
            m_pTweenData->scaleX -= 1;
            m_pTweenData->scaleY -= 1;
        }

        TransformHelp::nodeToMatrix(*m_pTweenData, m_tWorldTransform);

        m_tWorldTransform = AffineTransformConcat(getNodeToParentTransform(), m_tWorldTransform);

        if(m_pParentBone)
        {
            m_tWorldTransform = AffineTransformConcat(m_tWorldTransform, m_pParentBone->m_tWorldTransform);
        }
    }

    DisplayFactory::updateDisplay(this, m_pDisplayManager->getCurrentDecorativeDisplay(), delta, m_bBoneTransformDirty || m_pArmature->getArmatureTransformDirty());

    Object *object = NULL;
    CCARRAY_FOREACH(_children, object)
    {
        Bone *childBone = (Bone *)object;
        childBone->update(delta);
    }

    m_bBoneTransformDirty = false;
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
    Node *display = m_pDisplayManager->getDisplayRenderNode();
    RGBAProtocol *protocol = dynamic_cast<RGBAProtocol *>(display);
    if(protocol != NULL)
    {
        protocol->setColor(Color3B(_displayedColor.r * m_pTweenData->r / 255, _displayedColor.g * m_pTweenData->g / 255, _displayedColor.b * m_pTweenData->b / 255));
        protocol->setOpacity(_displayedOpacity * m_pTweenData->a / 255);
    }
}

void Bone::updateZOrder()
{
    if (m_pArmature->getArmatureData()->dataVersion >= VERSION_COMBINED)
    {
        int zorder = m_pTweenData->zOrder + m_pBoneData->zOrder;
        setZOrder(zorder);
    }
    else
    {
        setZOrder(m_pTweenData->zOrder);
    }
}

void Bone::addChildBone(Bone *child)
{
    CCAssert( NULL != child, "Argument must be non-nil");
    CCAssert( NULL == child->m_pParentBone, "child already added. It can't be added again");

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
    if (NULL != m_pParentBone)
    {
        m_pParentBone->removeChildBone(this, recursion);
    }
}

void Bone::setParentBone(Bone *parent)
{
    m_pParentBone = parent;
}

Bone *Bone::getParentBone()
{
    return m_pParentBone;
}

void Bone::setChildArmature(Armature *armature)
{
    if (m_pChildArmature != armature)
    {
        CC_SAFE_RETAIN(armature);
        CC_SAFE_RELEASE(m_pChildArmature);
        m_pChildArmature = armature;
    }
}

Armature *Bone::getChildArmature()
{
    return m_pChildArmature;
}

Tween *Bone::getTween()
{
    return m_pTween;
}

void Bone::setZOrder(int zOrder)
{
    if (_ZOrder != zOrder)
        Node::setZOrder(zOrder);
}

void Bone::setTransformDirty(bool dirty)
{
    m_bBoneTransformDirty = dirty;
}

bool Bone::isTransformDirty()
{
    return m_bBoneTransformDirty;
}

AffineTransform Bone::getNodeToArmatureTransform() const
{
    return m_tWorldTransform;
}

AffineTransform Bone::getNodeToWorldTransform() const
{
    return AffineTransformConcat(m_tWorldTransform, m_pArmature->getNodeToWorldTransform());
}

Node *Bone::getDisplayRenderNode()
{
    return m_pDisplayManager->getDisplayRenderNode();
}

void Bone::addDisplay(DisplayData *displayData, int index)
{
    m_pDisplayManager->addDisplay(displayData, index);
}

void Bone::addDisplay(Node *display, int index)
{
    m_pDisplayManager->addDisplay(display, index);
}

void Bone::changeDisplayByIndex(int index, bool force)
{
    m_pDisplayManager->changeDisplayByIndex(index, force);
}

Array *Bone::getColliderBodyList()
{
    if (DecorativeDisplay *decoDisplay = m_pDisplayManager->getCurrentDecorativeDisplay())
    {
        if (ColliderDetector *detector = decoDisplay->getColliderDetector())
        {
            return detector->getColliderBodyList();
        }
    }
    return NULL;
}


NS_CC_EXT_ARMATURE_END
