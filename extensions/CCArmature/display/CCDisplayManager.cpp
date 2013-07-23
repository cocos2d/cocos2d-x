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

namespace cocos2d { namespace extension { namespace armature {

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
	: _decoDisplayList(NULL)
	, _displayRenderNode(NULL)
    , _currentDecoDisplay(NULL)
    , _displayIndex(-1)
	, _forceChangeDisplay(false)
	, _visible(true)
    , _bone(NULL)
{
}

DisplayManager::~DisplayManager()
{
    CC_SAFE_DELETE(_decoDisplayList);

    if( _displayRenderNode )
    {
        _displayRenderNode->removeFromParentAndCleanup(true);
        if(_displayRenderNode->retainCount() > 0)
            CC_SAFE_RELEASE_NULL(_displayRenderNode);
    }

}

bool DisplayManager::init(Bone *bone)
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


void DisplayManager::addDisplay(DisplayData *displayData, int index)
{
    DecorativeDisplay *decoDisplay = NULL;

    if(index >= 0 && (unsigned int)index < _decoDisplayList->count())
    {
        decoDisplay = (DecorativeDisplay *)_decoDisplayList->objectAtIndex(index);
    }
    else
    {
        decoDisplay = DecorativeDisplay::create();
        _decoDisplayList->addObject(decoDisplay);
    }

    DisplayFactory::addDisplay(_bone, decoDisplay, displayData);

    //! if changed display index is current display index, then change current display to the new display
    if(index == _displayIndex)
    {
        _displayIndex = -1;
        changeDisplayByIndex(index, false);
    }
}

void DisplayManager::removeDisplay(int index)
{
    _decoDisplayList->removeObjectAtIndex(index);

    if(index == _displayIndex)
    {
        setCurrentDecorativeDisplay(NULL);
    }
}

void DisplayManager::changeDisplayByIndex(int index, bool force)
{
    CCASSERT( (_decoDisplayList ? index < (int)_decoDisplayList->count() : true), "the _index value is out of range");

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


    DecorativeDisplay *decoDisplay = (DecorativeDisplay *)_decoDisplayList->objectAtIndex(_displayIndex);

    setCurrentDecorativeDisplay(decoDisplay);
}

void DisplayManager::setCurrentDecorativeDisplay(DecorativeDisplay *decoDisplay)
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

    Node *displayRenderNode = _currentDecoDisplay == NULL ? NULL : _currentDecoDisplay->getDisplay();
    if (_displayRenderNode)
    {
        if (dynamic_cast<Armature *>(_displayRenderNode) != NULL)
        {
            _bone->setChildArmature(NULL);
        }

        _displayRenderNode->removeFromParentAndCleanup(true);
        _displayRenderNode->release();
    }

    _displayRenderNode = displayRenderNode;

    if(_displayRenderNode)
    {
        if (dynamic_cast<Armature *>(_displayRenderNode) != NULL)
        {
            _bone->setChildArmature((Armature *)_displayRenderNode);
        }
        _displayRenderNode->retain();
		_displayRenderNode->setVisible(_visible);
    }
}

Node *DisplayManager::getDisplayRenderNode()
{
    return _displayRenderNode;
}

int DisplayManager::getCurrentDisplayIndex()
{
    return _displayIndex;
}

DecorativeDisplay *DisplayManager::getCurrentDecorativeDisplay()
{
    return _currentDecoDisplay;
}

DecorativeDisplay *DisplayManager::getDecorativeDisplayByIndex( int index)
{
    return (DecorativeDisplay *)_decoDisplayList->objectAtIndex(index);
}

void DisplayManager::initDisplayList(BoneData *boneData)
{
    CC_SAFE_DELETE(_decoDisplayList);
    _decoDisplayList = Array::create();
    _decoDisplayList->retain();

    CS_RETURN_IF(!boneData);

    Object *object = NULL;
    Array *displayDataList = &boneData->displayDataList;
    CCARRAY_FOREACH(displayDataList, object)
    {
        DisplayData *displayData = static_cast<DisplayData *>(object);

        DecorativeDisplay *decoDisplay = DecorativeDisplay::create();
        decoDisplay->setDisplayData(displayData);

        DisplayFactory::createDisplay(_bone, decoDisplay);

        _decoDisplayList->addObject(decoDisplay);
    }
}


bool DisplayManager::containPoint(Point &point)
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

        Point outPoint = Point(0, 0);

        Sprite *sprite = (Sprite *)_currentDecoDisplay->getDisplay();
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
    if(!_displayRenderNode)
        return;

    _visible = visible;
    _displayRenderNode->setVisible(visible);
}

bool DisplayManager::isVisible()
{
    return _visible;
}


Size DisplayManager::getContentSize()
{
    CS_RETURN_IF(!_displayRenderNode) Size(0, 0);
    return _displayRenderNode->getContentSize();
}

Rect DisplayManager::getBoundingBox()
{
    CS_RETURN_IF(!_displayRenderNode) Rect(0, 0, 0, 0);
    return _displayRenderNode->getBoundingBox();
}


Point DisplayManager::getAnchorPoint()
{
    CS_RETURN_IF(!_displayRenderNode) Point(0, 0);
    return _displayRenderNode->getAnchorPoint();
}

Point DisplayManager::getAnchorPointInPoints()
{
    CS_RETURN_IF(!_displayRenderNode) Point(0, 0);
    return _displayRenderNode->getAnchorPointInPoints();
}


}}} // namespace cocos2d { namespace extension { namespace armature {
