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

NS_CC_EXT_BEGIN

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
    m_pTweenData = NULL;
    m_pParentBone = NULL;
    m_pArmature = NULL;
    m_pChildArmature = NULL;
    m_pBoneData = NULL;
    m_pTween = NULL;
    m_pTween = NULL;
    m_pChildren = NULL;
    m_pDisplayManager = NULL;
    m_bIgnoreMovementBoneData = false;
    m_tWorldTransform = CCAffineTransformMake(1, 0, 0, 1, 0, 0);
    m_bBoneTransformDirty = true;
    m_tWorldInfo = NULL;
    m_pArmatureParentBone = NULL;
    m_fDataVersion = 0;
    m_sBlendFunc.src = CC_BLEND_SRC;
    m_sBlendFunc.dst = CC_BLEND_DST;
    m_bBlendDirty = false;
}


CCBone::~CCBone(void)
{
    CC_SAFE_DELETE(m_pTweenData);
    CC_SAFE_DELETE(m_pChildren);
    CC_SAFE_DELETE(m_pTween);
    CC_SAFE_DELETE(m_pDisplayManager);
    CC_SAFE_DELETE(m_tWorldInfo);

    CC_SAFE_RELEASE_NULL(m_pBoneData);

    CC_SAFE_RELEASE(m_pChildArmature);
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
            m_strName = name;
        }

        CC_SAFE_DELETE(m_pTweenData);
        m_pTweenData = new CCFrameData();

        CC_SAFE_DELETE(m_pTween);
        m_pTween = new CCTween();
        m_pTween->init(this);

        CC_SAFE_DELETE(m_pDisplayManager);
        m_pDisplayManager = new CCDisplayManager();
        m_pDisplayManager->init(this);

        CC_SAFE_DELETE(m_tWorldInfo);
        m_tWorldInfo = new CCBaseData();

        CC_SAFE_DELETE(m_pBoneData);
        m_pBoneData  = new CCBoneData();

        bRet = true;
    }
    while (0);

    return bRet;
}

void CCBone::setBoneData(CCBoneData *boneData)
{
    CCAssert(NULL != boneData, "_boneData must not be NULL");

    if (m_pBoneData != boneData)
    {
        CC_SAFE_RETAIN(boneData);
        CC_SAFE_RELEASE(m_pBoneData);
        m_pBoneData = boneData;
    }

    m_strName = m_pBoneData->name;
    m_nZOrder = m_pBoneData->zOrder;

    m_pDisplayManager->initDisplayList(boneData);
}

CCBoneData *CCBone::getBoneData()
{
    return m_pBoneData;
}

void CCBone::setArmature(CCArmature *armature)
{
    m_pArmature = armature;
    if (m_pArmature)
    {
        m_pTween->setAnimation(m_pArmature->getAnimation());
        m_fDataVersion = m_pArmature->getArmatureData()->dataVersion;
        m_pArmatureParentBone = m_pArmature->getParentBone();
    }
    else
    {
        m_pArmatureParentBone = NULL;
    }
}


CCArmature *CCBone::getArmature()
{
    return m_pArmature;
}

void CCBone::update(float delta)
{
    if (m_pParentBone)
        m_bBoneTransformDirty = m_bBoneTransformDirty || m_pParentBone->isTransformDirty();

    if (m_pArmatureParentBone && !m_bBoneTransformDirty)
    {
        m_bBoneTransformDirty = m_pArmatureParentBone->isTransformDirty();
    }

    if (m_bBoneTransformDirty)
    {
        if (m_fDataVersion >= VERSION_COMBINED)
        {
            CCTransformHelp::nodeConcat(*m_pTweenData, *m_pBoneData);
            m_pTweenData->scaleX -= 1;
            m_pTweenData->scaleY -= 1;
        }

        m_tWorldInfo->x = m_pTweenData->x + m_obPosition.x;
        m_tWorldInfo->y = m_pTweenData->y + m_obPosition.y;
        m_tWorldInfo->scaleX = m_pTweenData->scaleX * m_fScaleX;
        m_tWorldInfo->scaleY = m_pTweenData->scaleY * m_fScaleY;
        m_tWorldInfo->skewX = m_pTweenData->skewX + m_fSkewX + m_fRotationX;
        m_tWorldInfo->skewY = m_pTweenData->skewY + m_fSkewY - m_fRotationY;

        if(m_pParentBone)
        {
            applyParentTransform(m_pParentBone);
        }
        else
        {
            if (m_pArmatureParentBone)
            {
                applyParentTransform(m_pArmatureParentBone);
            }
        }

        CCTransformHelp::nodeToMatrix(*m_tWorldInfo, m_tWorldTransform);

        if (m_pArmatureParentBone)
        {
            m_tWorldTransform = CCAffineTransformConcat(m_tWorldTransform, m_pArmature->nodeToParentTransform());
        }
    }

    CCDisplayFactory::updateDisplay(this, delta, m_bBoneTransformDirty || m_pArmature->getArmatureTransformDirty());

    CCObject *object = NULL;
    CCARRAY_FOREACH(m_pChildren, object)
    {
        CCBone *childBone = (CCBone *)object;
        childBone->update(delta);
    }

    m_bBoneTransformDirty = false;
}

void CCBone::applyParentTransform(CCBone *parent)
{
    float x = m_tWorldInfo->x;
    float y = m_tWorldInfo->y;
    m_tWorldInfo->x = x * parent->m_tWorldTransform.a + y * parent->m_tWorldTransform.c + parent->m_tWorldInfo->x;
    m_tWorldInfo->y = x * parent->m_tWorldTransform.b + y * parent->m_tWorldTransform.d + parent->m_tWorldInfo->y;
    m_tWorldInfo->scaleX = m_tWorldInfo->scaleX * parent->m_tWorldInfo->scaleX;
    m_tWorldInfo->scaleY = m_tWorldInfo->scaleY * parent->m_tWorldInfo->scaleY;
    m_tWorldInfo->skewX = m_tWorldInfo->skewX + parent->m_tWorldInfo->skewX;
    m_tWorldInfo->skewY = m_tWorldInfo->skewY + parent->m_tWorldInfo->skewY;
}

void CCBone::updateDisplayedColor(const ccColor3B &parentColor)
{
    _realColor = ccc3(255, 255, 255);
    CCNodeRGBA::updateDisplayedColor(parentColor);
    updateColor();
}

void CCBone::updateDisplayedOpacity(GLubyte parentOpacity)
{
    _realOpacity = 255;
    CCNodeRGBA::updateDisplayedOpacity(parentOpacity);
    updateColor();
}

void CCBone::setColor(const ccColor3B &color)
{
    CCNodeRGBA::setColor(color);
    updateColor();
}

void CCBone::setOpacity(GLubyte opacity)
{
    CCNodeRGBA::setOpacity(opacity);
    updateColor();
}

void CCBone::updateColor()
{
    CCNode *display = m_pDisplayManager->getDisplayRenderNode();
    CCRGBAProtocol *protocol = dynamic_cast<CCRGBAProtocol *>(display);
    if(protocol != NULL)
    {
        protocol->setColor(ccc3(_displayedColor.r * m_pTweenData->r / 255, _displayedColor.g * m_pTweenData->g / 255, _displayedColor.b * m_pTweenData->b / 255));
        protocol->setOpacity(_displayedOpacity * m_pTweenData->a / 255);
    }
}

void CCBone::updateZOrder()
{
    if (m_fDataVersion >= VERSION_COMBINED)
    {
        int zorder = m_pTweenData->zOrder + m_pBoneData->zOrder;
        setZOrder(zorder);
    }
    else
    {
        setZOrder(m_pTweenData->zOrder);
    }
}

void CCBone::addChildBone(CCBone *child)
{
    CCAssert( NULL != child, "Argument must be non-nil");
    CCAssert( NULL == child->m_pParentBone, "child already added. It can't be added again");

    if(!m_pChildren)
    {
        m_pChildren = CCArray::createWithCapacity(4);
        m_pChildren->retain();
    }

    if (m_pChildren->indexOfObject(child) == UINT_MAX)
    {
        m_pChildren->addObject(child);
        child->setParentBone(this);
    }
}

void CCBone::removeChildBone(CCBone *bone, bool recursion)
{
    if ( m_pChildren->indexOfObject(bone) != UINT_MAX )
    {
        if(recursion)
        {
            CCArray *_ccbones = bone->m_pChildren;
            CCObject *_object = NULL;
            CCARRAY_FOREACH(_ccbones, _object)
            {
                CCBone *_ccBone = (CCBone *)_object;
                bone->removeChildBone(_ccBone, recursion);
            }
        }

        bone->setParentBone(NULL);

        bone->getDisplayManager()->setCurrentDecorativeDisplay(NULL);

        m_pChildren->removeObject(bone);
    }
}

void CCBone::removeFromParent(bool recursion)
{
    if (NULL != m_pParentBone)
    {
        m_pParentBone->removeChildBone(this, recursion);
    }
}

void CCBone::setParentBone(CCBone *parent)
{
    m_pParentBone = parent;
}

CCBone *CCBone::getParentBone()
{
    return m_pParentBone;
}

void CCBone::setChildArmature(CCArmature *armature)
{
    if (m_pChildArmature != armature)
    {
        if (armature == NULL && m_pChildArmature)
        {
            m_pChildArmature->setParentBone(NULL);
        }

        CC_SAFE_RETAIN(armature);
        CC_SAFE_RELEASE(m_pChildArmature);
        m_pChildArmature = armature;
    }
}

CCArmature *CCBone::getChildArmature()
{
    return m_pChildArmature;
}

CCTween *CCBone::getTween()
{
    return m_pTween;
}

void CCBone::setBlendFunc(const ccBlendFunc& blendFunc)
{
    if (m_sBlendFunc.src != blendFunc.src || m_sBlendFunc.dst != blendFunc.dst)
    {
        m_sBlendFunc = blendFunc;
        m_bBlendDirty = true;
    }
}

void CCBone::setZOrder(int zOrder)
{
    if (m_nZOrder != zOrder)
        CCNode::setZOrder(zOrder);
}


CCAffineTransform CCBone::nodeToArmatureTransform()
{
    return m_tWorldTransform;
}

CCAffineTransform CCBone::nodeToWorldTransform()
{
    return CCAffineTransformConcat(m_tWorldTransform, m_pArmature->nodeToWorldTransform());
}

CCNode *CCBone::getDisplayRenderNode()
{
    return m_pDisplayManager->getDisplayRenderNode();
}

DisplayType CCBone::getDisplayRenderNodeType()
{
    return m_pDisplayManager->getDisplayRenderNodeType();
}

void CCBone::addDisplay(CCDisplayData *displayData, int index)
{
    m_pDisplayManager->addDisplay(displayData, index);
}

void CCBone::addDisplay(CCNode *display, int index)
{
    m_pDisplayManager->addDisplay(display, index);
}

void CCBone::removeDisplay(int index)
{
    m_pDisplayManager->removeDisplay(index);
}

void CCBone::changeDisplayByIndex(int index, bool force)
{
    changeDisplayWithIndex(index, force);
}

void CCBone::changeDisplayByName(const char *name, bool force)
{
    changeDisplayWithName(name, force);
}

void CCBone::changeDisplayWithIndex(int index, bool force)
{
    m_pDisplayManager->changeDisplayWithIndex(index, force);
}

void CCBone::changeDisplayWithName(const char *name, bool force)
{
    m_pDisplayManager->changeDisplayWithName(name, force);
}


CCArray *CCBone::getColliderBodyList()
{
    if (CCDecorativeDisplay *decoDisplay = m_pDisplayManager->getCurrentDecorativeDisplay())
    {
        if (CCColliderDetector *detector = decoDisplay->getColliderDetector())
        {
            return detector->getColliderBodyList();
        }
    }
    return NULL;
}

#if ENABLE_PHYSICS_BOX2D_DETECT || ENABLE_PHYSICS_CHIPMUNK_DETECT
void CCBone::setColliderFilter(CCColliderFilter *filter)
{
    CCArray *array = m_pDisplayManager->getDecorativeDisplayList();
    CCObject *object = NULL;
    CCARRAY_FOREACH(array, object)
    {
        CCDecorativeDisplay *decoDisplay = static_cast<CCDecorativeDisplay *>(object);
        if (CCColliderDetector *detector = decoDisplay->getColliderDetector())
        {
            detector->setColliderFilter(filter);
        }
    }
}
CCColliderFilter *CCBone::getColliderFilter()
{
    if (CCDecorativeDisplay *decoDisplay = m_pDisplayManager->getCurrentDecorativeDisplay())
    {
        if (CCColliderDetector *detector = decoDisplay->getColliderDetector())
        {
            return detector->getColliderFilter();
        }
    }
    return NULL;
}
#endif


NS_CC_EXT_END
