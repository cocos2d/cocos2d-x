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

NS_CC_EXT_ARMATURE_BEGIN

DisplayManager *DisplayManager::create(Bone *bone)
{
    DisplayManager *pDisplayManager = new DisplayManager();
    if (pDisplayManager && pDisplayManager->init(bone))
    {
        pDisplayManager->autorelease();
        return pDisplayManager;
    }
    CC_SAFE_DELETE(pDisplayManager);
    return NULL;
}


DisplayManager::DisplayManager()
    : m_pDecoDisplayList(NULL)
    , m_pDisplayRenderNode(NULL)
    , m_pCurrentDecoDisplay(NULL)
    , m_iDisplayIndex(-1)
    , m_bForceChangeDisplay(false)
    , m_bVisible(true)
    , m_pBone(NULL)
{
}

DisplayManager::~DisplayManager()
{
    CC_SAFE_DELETE(m_pDecoDisplayList);

    if( m_pDisplayRenderNode )
    {
        m_pDisplayRenderNode->removeFromParentAndCleanup(true);
        if(m_pDisplayRenderNode->retainCount() > 0)
            CC_SAFE_RELEASE_NULL(m_pDisplayRenderNode);
    }

}

bool DisplayManager::init(Bone *bone)
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


void DisplayManager::addDisplay(DisplayData *displayData, int index)
{
    DecorativeDisplay *decoDisplay = NULL;

    if(index >= 0 && (unsigned int)index < m_pDecoDisplayList->count())
    {
        decoDisplay = (DecorativeDisplay *)m_pDecoDisplayList->getObjectAtIndex(index);
    }
    else
    {
        decoDisplay = DecorativeDisplay::create();
        m_pDecoDisplayList->addObject(decoDisplay);
    }

    DisplayFactory::addDisplay(m_pBone, decoDisplay, displayData);

    //! if changed display index is current display index, then change current display to the new display
    if(index == m_iDisplayIndex)
    {
        m_iDisplayIndex = -1;
        changeDisplayByIndex(index, false);
    }
}

void DisplayManager::addDisplay(Node *display, int index)
{
    DecorativeDisplay *decoDisplay = NULL;

    if(index >= 0 && (unsigned int)index < m_pDecoDisplayList->count())
    {
        decoDisplay = (DecorativeDisplay *)m_pDecoDisplayList->getObjectAtIndex(index);
    }
    else
    {
        decoDisplay = DecorativeDisplay::create();
        m_pDecoDisplayList->addObject(decoDisplay);
    }

    DisplayData *displayData = NULL;
    if (Skin *skin = dynamic_cast<Skin *>(display))
    {
        skin->setBone(m_pBone);
        displayData = SpriteDisplayData::create();

        DisplayFactory::initSpriteDisplay(m_pBone, decoDisplay, skin->getDisplayName().c_str(), skin);

        if (SpriteDisplayData *spriteDisplayData = (SpriteDisplayData *)decoDisplay->getDisplayData())
        {
            skin->setSkinData(spriteDisplayData->skinData);
        }
        else
        {
            BaseData baseData;
            skin->setSkinData(baseData);
        }
    }
    else if (dynamic_cast<ParticleSystemQuad *>(display))
    {
        displayData = ParticleDisplayData::create();
    }
    else if(Armature *armature = dynamic_cast<Armature *>(display))
    {
        displayData = ArmatureDisplayData::create();
        armature->setParentBone(m_pBone);
    }
    else
    {
        displayData = DisplayData::create();
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

void DisplayManager::removeDisplay(int index)
{
    m_pDecoDisplayList->removeObjectAtIndex(index);

    if(index == m_iDisplayIndex)
    {
        setCurrentDecorativeDisplay(NULL);
    }
}

Array *DisplayManager::getDecorativeDisplayList()
{
    return m_pDecoDisplayList;
}

void DisplayManager::changeDisplayByIndex(int index, bool force)
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


    DecorativeDisplay *decoDisplay = (DecorativeDisplay *)m_pDecoDisplayList->getObjectAtIndex(m_iDisplayIndex);

    setCurrentDecorativeDisplay(decoDisplay);
}

void DisplayManager::setCurrentDecorativeDisplay(DecorativeDisplay *decoDisplay)
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

    Node *displayRenderNode = m_pCurrentDecoDisplay == NULL ? NULL : m_pCurrentDecoDisplay->getDisplay();
    if (m_pDisplayRenderNode)
    {
        if (dynamic_cast<Armature *>(m_pDisplayRenderNode) != NULL)
        {
            m_pBone->setChildArmature(NULL);
        }
        m_pDisplayRenderNode->removeFromParentAndCleanup(true);
        m_pDisplayRenderNode->release();
    }

    m_pDisplayRenderNode = displayRenderNode;

    if(m_pDisplayRenderNode)
    {
        if (Armature *armature = dynamic_cast<Armature *>(m_pDisplayRenderNode))
        {
            m_pBone->setChildArmature(armature);
        }
        else if (ParticleSystemQuad *particle = dynamic_cast<ParticleSystemQuad *>(m_pDisplayRenderNode))
        {
            particle->resetSystem();
        }

        if (RGBAProtocol *rgbaProtocaol = dynamic_cast<RGBAProtocol *>(m_pDisplayRenderNode))
        {
			rgbaProtocaol->setColor(m_pBone->getDisplayedColor());
			rgbaProtocaol->setOpacity(m_pBone->getDisplayedOpacity());
        }

        m_pDisplayRenderNode->retain();
        m_pDisplayRenderNode->setVisible(m_bVisible);
    }
}

Node *DisplayManager::getDisplayRenderNode()
{
    return m_pDisplayRenderNode;
}

int DisplayManager::getCurrentDisplayIndex()
{
    return m_iDisplayIndex;
}

DecorativeDisplay *DisplayManager::getCurrentDecorativeDisplay()
{
    return m_pCurrentDecoDisplay;
}

DecorativeDisplay *DisplayManager::getDecorativeDisplayByIndex( int index)
{
    return (DecorativeDisplay *)m_pDecoDisplayList->getObjectAtIndex(index);
}

void DisplayManager::initDisplayList(BoneData *boneData)
{
    CC_SAFE_DELETE(m_pDecoDisplayList);
    m_pDecoDisplayList = Array::create();
    m_pDecoDisplayList->retain();

    CS_RETURN_IF(!boneData);

    Object *object = NULL;
    Array *displayDataList = &boneData->displayDataList;
    CCARRAY_FOREACH(displayDataList, object)
    {
        DisplayData *displayData = (DisplayData *)object;

        DecorativeDisplay *decoDisplay = DecorativeDisplay::create();
        decoDisplay->setDisplayData(displayData);

        DisplayFactory::createDisplay(m_pBone, decoDisplay);

        m_pDecoDisplayList->addObject(decoDisplay);
    }
}


bool DisplayManager::containPoint(Point &point)
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

        Point outPoint = Point(0, 0);

        Sprite *sprite = (Sprite *)m_pCurrentDecoDisplay->getDisplay();
        sprite = (Sprite *)sprite->getChildByTag(0);

        ret = CC_SPRITE_CONTAIN_POINT_WITH_RETURN(sprite, point, outPoint);

    }
    break;

    default:
        break;
    }
    return ret;
}

bool DisplayManager::containPoint(float x, float y)
{
    Point p = Point(x, y);
    return containPoint(p);
}


void DisplayManager::setVisible(bool visible)
{
    if(!m_pDisplayRenderNode)
        return;

    m_bVisible = visible;
    m_pDisplayRenderNode->setVisible(visible);
}

bool DisplayManager::isVisible()
{
    return m_bVisible;
}


Size DisplayManager::getContentSize()
{
    CS_RETURN_IF(!m_pDisplayRenderNode) Size(0, 0);
    return m_pDisplayRenderNode->getContentSize();
}

Rect DisplayManager::getBoundingBox()
{
    CS_RETURN_IF(!m_pDisplayRenderNode) Rect(0, 0, 0, 0);
    return m_pDisplayRenderNode->getBoundingBox();
}


Point DisplayManager::getAnchorPoint()
{
    CS_RETURN_IF(!m_pDisplayRenderNode) Point(0, 0);
    return m_pDisplayRenderNode->getAnchorPoint();
}

Point DisplayManager::getAnchorPointInPoints()
{
    CS_RETURN_IF(!m_pDisplayRenderNode) Point(0, 0);
    return m_pDisplayRenderNode->getAnchorPointInPoints();
}


NS_CC_EXT_ARMATURE_END
