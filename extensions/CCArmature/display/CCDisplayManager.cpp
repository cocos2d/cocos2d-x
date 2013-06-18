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
	: _decoDisplayList(NULL)
	, _displayRenderNode(NULL)
    , _currentDecoDisplay(NULL)
    , _displayIndex(-1)
	, _forceChangeDisplay(false)
	, _visible(true)
    , _bone(NULL)
{
}

CCDisplayManager::~CCDisplayManager()
{
    CC_SAFE_DELETE(_decoDisplayList);

    if( _displayRenderNode )
    {
        _displayRenderNode->removeFromParentAndCleanup(true);
        if(_displayRenderNode->retainCount() > 0)
            CC_SAFE_RELEASE_NULL(_displayRenderNode);
    }

}

bool CCDisplayManager::init(CCBone *bone)
{
    bool ret = false;

    do
    {

        _bone = bone;

        initDisplayList(bone->getBoneData());

        ret = true;
    }
    while (0);

    return ret;
}


void CCDisplayManager::addDisplay(CCDisplayData *displayData, int index)
{
    CCDecorativeDisplay *decoDisplay = NULL;

    if(index >= 0 && (unsigned int)index < _decoDisplayList->count())
    {
        decoDisplay = (CCDecorativeDisplay *)_decoDisplayList->objectAtIndex(index);
    }
    else
    {
        decoDisplay = CCDecorativeDisplay::create();
        _decoDisplayList->addObject(decoDisplay);
    }

    CCDisplayFactory::addDisplay(_bone, decoDisplay, displayData);

    //! if changed display index is current display index, then change current display to the new display
    if(index == _displayIndex)
    {
        _displayIndex = -1;
        changeDisplayByIndex(index, false);
    }
}

void CCDisplayManager::removeDisplay(int index)
{
    _decoDisplayList->removeObjectAtIndex(index);

    if(index == _displayIndex)
    {
        setCurrentDecorativeDisplay(NULL);
    }
}

void CCDisplayManager::changeDisplayByIndex(int index, bool force)
{
    CCAssert( (_decoDisplayList ? index < (int)_decoDisplayList->count() : true), "the _index value is out of range");

    _forceChangeDisplay = force;

    //! If index is equal to current display index,then do nothing
    if ( _displayIndex == index)
        return;


    _displayIndex = index;

    //! If displayIndex < 0, it means you want to hide you display
    if (_displayIndex < 0)
    {
        if(_displayRenderNode)
        {
            _displayRenderNode->removeFromParentAndCleanup(true);
            setCurrentDecorativeDisplay(NULL);
        }
        return;
    }


    CCDecorativeDisplay *decoDisplay = (CCDecorativeDisplay *)_decoDisplayList->objectAtIndex(_displayIndex);

    setCurrentDecorativeDisplay(decoDisplay);
}

void CCDisplayManager::setCurrentDecorativeDisplay(CCDecorativeDisplay *decoDisplay)
{
#if ENABLE_PHYSICS_DETECT
    if (_currentDecoDisplay && _currentDecoDisplay->getColliderDetector())
    {
        _currentDecoDisplay->getColliderDetector()->setActive(false);
    }
#endif

    _currentDecoDisplay = decoDisplay;

#if ENABLE_PHYSICS_DETECT
    if (_currentDecoDisplay && _currentDecoDisplay->getColliderDetector())
    {
        _currentDecoDisplay->getColliderDetector()->setActive(true);
    }
#endif

    CCNode *displayRenderNode = _currentDecoDisplay == NULL ? NULL : _currentDecoDisplay->getDisplay();
    if (_displayRenderNode)
    {
        if (dynamic_cast<CCArmature *>(_displayRenderNode) != NULL)
        {
            _bone->setChildArmature(NULL);
        }

        _displayRenderNode->removeFromParentAndCleanup(true);
        _displayRenderNode->release();
    }

    _displayRenderNode = displayRenderNode;

    if(_displayRenderNode)
    {
        if (dynamic_cast<CCArmature *>(_displayRenderNode) != NULL)
        {
            _bone->setChildArmature((CCArmature *)_displayRenderNode);
        }
        _displayRenderNode->retain();
		_displayRenderNode->setVisible(_visible);
    }
}

CCNode *CCDisplayManager::getDisplayRenderNode()
{
    return _displayRenderNode;
}

int CCDisplayManager::getCurrentDisplayIndex()
{
    return _displayIndex;
}

CCDecorativeDisplay *CCDisplayManager::getCurrentDecorativeDisplay()
{
    return _currentDecoDisplay;
}

CCDecorativeDisplay *CCDisplayManager::getDecorativeDisplayByIndex( int index)
{
    return (CCDecorativeDisplay *)_decoDisplayList->objectAtIndex(index);
}

void CCDisplayManager::initDisplayList(CCBoneData *boneData)
{
    CC_SAFE_DELETE(_decoDisplayList);
    _decoDisplayList = CCArray::create();
    _decoDisplayList->retain();

    CS_RETURN_IF(!boneData);

    CCObject *object = NULL;
    CCArray *displayDataList = &boneData->displayDataList;
    CCARRAY_FOREACH(displayDataList, object)
    {
        CCDisplayData *displayData = (CCDisplayData *)object;

        CCDecorativeDisplay *decoDisplay = CCDecorativeDisplay::create();
        decoDisplay->setDisplayData(displayData);

        CCDisplayFactory::createDisplay(_bone, decoDisplay);

        _decoDisplayList->addObject(decoDisplay);
    }
}


bool CCDisplayManager::containPoint(CCPoint &point)
{
    if(!_visible || _displayIndex < 0)
    {
        return false;
    }

    bool ret = false;

    switch (_currentDecoDisplay->getDisplayData()->displayType)
    {
    case CS_DISPLAY_SPRITE:
    {
        /*
         *  First we first check if the point is in the sprite content rect. If false, then we continue to check
         *  the contour point. If this step is also false, then we can say the bone not contain this point.
         *
         */

        CCPoint outPoint = ccp(0, 0);

        CCSprite *sprite = (CCSprite *)_currentDecoDisplay->getDisplay();
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
    if(!_displayRenderNode)
        return;

    _visible = visible;
    _displayRenderNode->setVisible(visible);
}

bool CCDisplayManager::isVisible()
{
    return _visible;
}


CCSize CCDisplayManager::getContentSize()
{
    CS_RETURN_IF(!_displayRenderNode) CCSizeMake(0, 0);
    return _displayRenderNode->getContentSize();
}

CCRect CCDisplayManager::getBoundingBox()
{
    CS_RETURN_IF(!_displayRenderNode) CCRectMake(0, 0, 0, 0);
    return _displayRenderNode->boundingBox();
}


CCPoint CCDisplayManager::getAnchorPoint()
{
    CS_RETURN_IF(!_displayRenderNode) ccp(0, 0);
    return _displayRenderNode->getAnchorPoint();
}

CCPoint CCDisplayManager::getAnchorPointInPoints()
{
    CS_RETURN_IF(!_displayRenderNode) ccp(0, 0);
    return _displayRenderNode->getAnchorPointInPoints();
}


NS_CC_EXT_END
