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

#include "CCDisplayManager.h"
#include "../CCBone.h"
#include "../CCArmature.h"
#include "../utils/CCUtilMath.h"
#include "../display/CCSkin.h"

NS_CC_EXT_BEGIN

CCDisplayManager *CCDisplayManager::create(CCBone *bone)
{
    CCDisplayManager *pDisplayManager = new CCDisplayManager();
    if (pDisplayManager && pDisplayManager->init(bone))
    {
        pDisplayManager->autorelease();
        return pDisplayManager;
    }
    CC_SAFE_DELETE(pDisplayManager);
    return NULL;
}


CCDisplayManager::CCDisplayManager()
    : m_pDecoDisplayList(NULL)
    , m_pDisplayRenderNode(NULL)
    , m_pCurrentDecoDisplay(NULL)
    , m_iDisplayIndex(-1)
    , m_bForceChangeDisplay(false)
    , m_bVisible(true)
    , m_pBone(NULL)
{
}

CCDisplayManager::~CCDisplayManager()
{
    CC_SAFE_DELETE(m_pDecoDisplayList);

    if( m_pDisplayRenderNode )
    {
        m_pDisplayRenderNode->removeFromParentAndCleanup(true);
        if(m_pDisplayRenderNode->retainCount() > 0)
            CC_SAFE_RELEASE_NULL(m_pDisplayRenderNode);
    }

}

bool CCDisplayManager::init(CCBone *bone)
{
    bool ret = false;

    do
    {

        m_pBone = bone;

        initDisplayList(bone->getBoneData());

        ret = true;
    }
    while (0);

    return ret;
}


void CCDisplayManager::addDisplay(CCDisplayData *displayData, int index)
{
    CCDecorativeDisplay *decoDisplay = NULL;

    if(index >= 0 && (unsigned int)index < m_pDecoDisplayList->count())
    {
        decoDisplay = (CCDecorativeDisplay *)m_pDecoDisplayList->objectAtIndex(index);
    }
    else
    {
        decoDisplay = CCDecorativeDisplay::create();
        m_pDecoDisplayList->addObject(decoDisplay);
    }

    CCDisplayFactory::addDisplay(m_pBone, decoDisplay, displayData);

    //! if changed display index is current display index, then change current display to the new display
    if(index == m_iDisplayIndex)
    {
        m_iDisplayIndex = -1;
        changeDisplayByIndex(index, false);
    }
}

void CCDisplayManager::addDisplay(CCNode *display, int index)
{
    CCDecorativeDisplay *decoDisplay = NULL;

    if(index >= 0 && (unsigned int)index < m_pDecoDisplayList->count())
    {
        decoDisplay = (CCDecorativeDisplay *)m_pDecoDisplayList->objectAtIndex(index);
    }
    else
    {
        decoDisplay = CCDecorativeDisplay::create();
        m_pDecoDisplayList->addObject(decoDisplay);
    }

    CCDisplayData *displayData = NULL;
    if (CCSkin *skin = dynamic_cast<CCSkin *>(display))
    {
        skin->setBone(m_pBone);
        displayData = CCSpriteDisplayData::create();

        CCDisplayFactory::initSpriteDisplay(m_pBone, decoDisplay, skin->getDisplayName().c_str(), skin);

        if (CCSpriteDisplayData *spriteDisplayData = (CCSpriteDisplayData *)decoDisplay->getDisplayData())
        {
            skin->setSkinData(spriteDisplayData->skinData);
        }
        else
        {
            CCBaseData baseData;
            skin->setSkinData(baseData);
        }
    }
    else if (dynamic_cast<CCParticleSystemQuad *>(display))
    {
        displayData = CCParticleDisplayData::create();
    }
    else if(CCArmature *armature = dynamic_cast<CCArmature *>(display))
    {
        displayData = CCArmatureDisplayData::create();
        armature->setParentBone(m_pBone);
    }
    else
    {
        displayData = CCDisplayData::create();
    }

    decoDisplay->setDisplay(display);
    decoDisplay->setDisplayData(displayData);

    //! if changed display index is current display index, then change current display to the new display
    if(index == m_iDisplayIndex)
    {
        m_iDisplayIndex = -1;
        changeDisplayByIndex(index, false);
    }
}

void CCDisplayManager::removeDisplay(int index)
{
    m_pDecoDisplayList->removeObjectAtIndex(index);

    if(index == m_iDisplayIndex)
    {
        setCurrentDecorativeDisplay(NULL);
    }
}

CCArray *CCDisplayManager::getDecorativeDisplayList()
{
    return m_pDecoDisplayList;
}

void CCDisplayManager::changeDisplayByIndex(int index, bool force)
{
    CCAssert( (m_pDecoDisplayList ? index < (int)m_pDecoDisplayList->count() : true), "the _index value is out of range");

    m_bForceChangeDisplay = force;

    //! If index is equal to current display index,then do nothing
    if ( m_iDisplayIndex == index)
        return;


    m_iDisplayIndex = index;

    //! If displayIndex < 0, it means you want to hide you display
    if (m_iDisplayIndex < 0)
    {
        if(m_pDisplayRenderNode)
        {
            m_pDisplayRenderNode->removeFromParentAndCleanup(true);
            setCurrentDecorativeDisplay(NULL);
        }
        return;
    }


    CCDecorativeDisplay *decoDisplay = (CCDecorativeDisplay *)m_pDecoDisplayList->objectAtIndex(m_iDisplayIndex);

    setCurrentDecorativeDisplay(decoDisplay);
}

void CCDisplayManager::setCurrentDecorativeDisplay(CCDecorativeDisplay *decoDisplay)
{
#if ENABLE_PHYSICS_BOX2D_DETECT || ENABLE_PHYSICS_CHIPMUNK_DETECT
    if (m_pCurrentDecoDisplay && m_pCurrentDecoDisplay->getColliderDetector())
    {
        m_pCurrentDecoDisplay->getColliderDetector()->setActive(false);
    }
#endif

    m_pCurrentDecoDisplay = decoDisplay;

#if ENABLE_PHYSICS_BOX2D_DETECT || ENABLE_PHYSICS_CHIPMUNK_DETECT
    if (m_pCurrentDecoDisplay && m_pCurrentDecoDisplay->getColliderDetector())
    {
        m_pCurrentDecoDisplay->getColliderDetector()->setActive(true);
    }
#endif

    CCNode *displayRenderNode = m_pCurrentDecoDisplay == NULL ? NULL : m_pCurrentDecoDisplay->getDisplay();
    if (m_pDisplayRenderNode)
    {
        if (dynamic_cast<CCArmature *>(m_pDisplayRenderNode) != NULL)
        {
            m_pBone->setChildArmature(NULL);
        }
        m_pDisplayRenderNode->removeFromParentAndCleanup(true);
        m_pDisplayRenderNode->release();
    }

    m_pDisplayRenderNode = displayRenderNode;

    if(m_pDisplayRenderNode)
    {
        if (CCArmature *armature = dynamic_cast<CCArmature *>(m_pDisplayRenderNode))
        {
            m_pBone->setChildArmature(armature);
        }
        else if (CCParticleSystemQuad *particle = dynamic_cast<CCParticleSystemQuad *>(m_pDisplayRenderNode))
        {
            particle->resetSystem();
        }

        if (CCRGBAProtocol *rgbaProtocaol = dynamic_cast<CCRGBAProtocol *>(m_pDisplayRenderNode))
        {
            rgbaProtocaol->setColor(m_pBone->getColor());
            rgbaProtocaol->setOpacity(m_pBone->getOpacity());
        }

        m_pDisplayRenderNode->retain();
        m_pDisplayRenderNode->setVisible(m_bVisible);
    }
}

CCNode *CCDisplayManager::getDisplayRenderNode()
{
    return m_pDisplayRenderNode;
}

int CCDisplayManager::getCurrentDisplayIndex()
{
    return m_iDisplayIndex;
}

CCDecorativeDisplay *CCDisplayManager::getCurrentDecorativeDisplay()
{
    return m_pCurrentDecoDisplay;
}

CCDecorativeDisplay *CCDisplayManager::getDecorativeDisplayByIndex( int index)
{
    return (CCDecorativeDisplay *)m_pDecoDisplayList->objectAtIndex(index);
}

void CCDisplayManager::initDisplayList(CCBoneData *boneData)
{
    CC_SAFE_DELETE(m_pDecoDisplayList);
    m_pDecoDisplayList = CCArray::create();
    m_pDecoDisplayList->retain();

    CS_RETURN_IF(!boneData);

    CCObject *object = NULL;
    CCArray *displayDataList = &boneData->displayDataList;
    CCARRAY_FOREACH(displayDataList, object)
    {
        CCDisplayData *displayData = (CCDisplayData *)object;

        CCDecorativeDisplay *decoDisplay = CCDecorativeDisplay::create();
        decoDisplay->setDisplayData(displayData);

        CCDisplayFactory::createDisplay(m_pBone, decoDisplay);

        m_pDecoDisplayList->addObject(decoDisplay);
    }
}


bool CCDisplayManager::containPoint(CCPoint &point)
{
    if(!m_bVisible || m_iDisplayIndex < 0)
    {
        return false;
    }

    bool ret = false;

    switch (m_pCurrentDecoDisplay->getDisplayData()->displayType)
    {
    case CS_DISPLAY_SPRITE:
    {
        /*
         *  First we first check if the point is in the sprite content rect. If false, then we continue to check
         *  the contour point. If this step is also false, then we can say the bone not contain this point.
         *
         */

        CCPoint outPoint = ccp(0, 0);

        CCSprite *sprite = (CCSprite *)m_pCurrentDecoDisplay->getDisplay();
        sprite = (CCSprite *)sprite->getChildByTag(0);

        ret = CC_SPRITE_CONTAIN_POINT_WITH_RETURN(sprite, point, outPoint);

    }
    break;

    default:
        break;
    }
    return ret;
}

bool CCDisplayManager::containPoint(float x, float y)
{
    CCPoint p = ccp(x, y);
    return containPoint(p);
}


void CCDisplayManager::setVisible(bool visible)
{
    if(!m_pDisplayRenderNode)
        return;

    m_bVisible = visible;
    m_pDisplayRenderNode->setVisible(visible);
}

bool CCDisplayManager::isVisible()
{
    return m_bVisible;
}


CCSize CCDisplayManager::getContentSize()
{
    CS_RETURN_IF(!m_pDisplayRenderNode) CCSizeMake(0, 0);
    return m_pDisplayRenderNode->getContentSize();
}

CCRect CCDisplayManager::getBoundingBox()
{
    CS_RETURN_IF(!m_pDisplayRenderNode) CCRectMake(0, 0, 0, 0);
    return m_pDisplayRenderNode->boundingBox();
}


CCPoint CCDisplayManager::getAnchorPoint()
{
    CS_RETURN_IF(!m_pDisplayRenderNode) ccp(0, 0);
    return m_pDisplayRenderNode->getAnchorPoint();
}

CCPoint CCDisplayManager::getAnchorPointInPoints()
{
    CS_RETURN_IF(!m_pDisplayRenderNode) ccp(0, 0);
    return m_pDisplayRenderNode->getAnchorPointInPoints();
}


NS_CC_EXT_END
