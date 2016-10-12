/****************************************************************************
Copyright (c) 2013-2016 Chukong Technologies Inc.

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

#include "editor-support/cocostudio/CCDisplayManager.h"
#include "editor-support/cocostudio/CCBone.h"
#include "editor-support/cocostudio/CCArmature.h"
#include "editor-support/cocostudio/CCUtilMath.h"
#include "editor-support/cocostudio/CCSkin.h"

#include "2d/CCParticleSystemQuad.h"

using namespace cocos2d;

namespace cocostudio {

DisplayManager *DisplayManager::create(Bone *bone)
{
    DisplayManager *pDisplayManager = new (std::nothrow) DisplayManager();
    if (pDisplayManager && pDisplayManager->init(bone))
    {
        pDisplayManager->autorelease();
        return pDisplayManager;
    }
    CC_SAFE_DELETE(pDisplayManager);
    return nullptr;
}


DisplayManager::DisplayManager()
    : _displayRenderNode(nullptr)
    , _displayType(CS_DISPLAY_MAX)
    , _currentDecoDisplay(nullptr)
    , _displayIndex(-1)
    , _forceChangeDisplay(false)
    , _visible(true)
    , _bone(nullptr)
{
}

DisplayManager::~DisplayManager()
{
    _decoDisplayList.clear();

    if( _displayRenderNode )
    {
        _displayRenderNode->removeFromParentAndCleanup(true);
        if(_displayRenderNode->getReferenceCount() > 0)
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
    DecorativeDisplay *decoDisplay = nullptr;

    if( (index >= 0) && (index < _decoDisplayList.size()) )
    {
        decoDisplay = (DecorativeDisplay *)_decoDisplayList.at(index);
    }
    else
    {
        decoDisplay = DecorativeDisplay::create();
        _decoDisplayList.pushBack(decoDisplay);
    }

    DisplayFactory::addDisplay(_bone, decoDisplay, displayData);

    //! if changed display index is current display index, then change current display to the new display
    if(index == _displayIndex)
    {
        _displayIndex = -1;
        changeDisplayWithIndex(index, false);
    }
}

void DisplayManager::addDisplay(Node *display, int index)
{
    DecorativeDisplay *decoDisplay = nullptr;

    if( (index >= 0) && (index < _decoDisplayList.size()) )
    {
        decoDisplay = _decoDisplayList.at(index);
    }
    else
    {
        decoDisplay = DecorativeDisplay::create();
        _decoDisplayList.pushBack(decoDisplay);
    }

    DisplayData *displayData = nullptr;
    if (Skin *skin = dynamic_cast<Skin *>(display))
    {
        skin->setBone(_bone);
        displayData = SpriteDisplayData::create();

        DisplayFactory::initSpriteDisplay(_bone, decoDisplay, skin->getDisplayName().c_str(), skin);

        if (SpriteDisplayData *spriteDisplayData = (SpriteDisplayData *)decoDisplay->getDisplayData())
        {
            skin->setSkinData(spriteDisplayData->skinData);
            ((SpriteDisplayData *)displayData)->skinData = spriteDisplayData->skinData;
        }
        else
        {
            bool find = false;

            for (long i = _decoDisplayList.size()-2; i>=0; i--)
            {
                DecorativeDisplay *dd = _decoDisplayList.at(i);
                SpriteDisplayData *sdd = static_cast<SpriteDisplayData*>(dd->getDisplayData());
                if (sdd)
                {
                    find = true;
                    skin->setSkinData(sdd->skinData);
                    static_cast<SpriteDisplayData*>(displayData)->skinData = sdd->skinData;
                    break;
                }
            }

            if (!find)
            {
                BaseData baseData;
                skin->setSkinData(baseData);
            }
        }
    }
    else if (dynamic_cast<ParticleSystemQuad *>(display))
    {
        displayData = ParticleDisplayData::create();

        display->removeFromParent();
        display->cleanup();
        
        Armature *armature = _bone->getArmature();
        if (armature)
        {
            display->setParent(armature);
        }
    }
    else if(Armature *armature = dynamic_cast<Armature *>(display))
    {
        displayData = ArmatureDisplayData::create();
        displayData->displayName = armature->getName();
        armature->setParentBone(_bone);
    }
    else
    {
        displayData = DisplayData::create();
    }

    decoDisplay->setDisplay(display);
    decoDisplay->setDisplayData(displayData);

    //! if changed display index is current display index, then change current display to the new display
    if(index == _displayIndex)
    {
        _displayIndex = -1;
        changeDisplayWithIndex(index, false);
    }
}

void DisplayManager::removeDisplay(int index)
{
    if(index == _displayIndex)
    {
        setCurrentDecorativeDisplay(nullptr);
        _displayIndex = -1;
    }

    _decoDisplayList.erase(index);
}

const cocos2d::Vector<DecorativeDisplay*>& DisplayManager::getDecorativeDisplayList() const
{
    return _decoDisplayList;
}

void DisplayManager::changeDisplayWithIndex(int index, bool force)
{
    CCASSERT( index < (int)_decoDisplayList.size(), "the _index value is out of range");

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
            setCurrentDecorativeDisplay(nullptr);
        }
        return;
    }


    DecorativeDisplay *decoDisplay = (DecorativeDisplay *)_decoDisplayList.at(_displayIndex);

    setCurrentDecorativeDisplay(decoDisplay);
}

void DisplayManager::changeDisplayWithName(const std::string& name, bool force)
{
    for (int i = 0; i<_decoDisplayList.size(); i++)
    {
        if (_decoDisplayList.at(i)->getDisplayData()->displayName == name)
        {
            changeDisplayWithIndex(i, force);
            break;
        }
    }
}

void DisplayManager::setCurrentDecorativeDisplay(DecorativeDisplay *decoDisplay)
{
#if ENABLE_PHYSICS_BOX2D_DETECT || ENABLE_PHYSICS_CHIPMUNK_DETECT || ENABLE_PHYSICS_SAVE_CALCULATED_VERTEX
    if (_currentDecoDisplay && _currentDecoDisplay->getColliderDetector())
    {
        _currentDecoDisplay->getColliderDetector()->setActive(false);
    }
#endif

    _currentDecoDisplay = decoDisplay;

#if ENABLE_PHYSICS_BOX2D_DETECT || ENABLE_PHYSICS_CHIPMUNK_DETECT || ENABLE_PHYSICS_SAVE_CALCULATED_VERTEX
    if (_currentDecoDisplay && _currentDecoDisplay->getColliderDetector())
    {
        _currentDecoDisplay->getColliderDetector()->setActive(true);
    }
#endif

    Node *displayRenderNode = _currentDecoDisplay == nullptr ? nullptr : _currentDecoDisplay->getDisplay();
    if (_displayRenderNode)
    {
        if (dynamic_cast<Armature *>(_displayRenderNode) != nullptr)
        {
            _bone->setChildArmature(nullptr);
        }
        _displayRenderNode->removeFromParentAndCleanup(true);
        _displayRenderNode->release();
    }

    _displayRenderNode = displayRenderNode;

    if(_displayRenderNode)
    {
        if (Armature *armature = dynamic_cast<Armature *>(_displayRenderNode))
        {
            _bone->setChildArmature(armature);
            armature->setParentBone(_bone);
        }
        else if (ParticleSystemQuad *particle = dynamic_cast<ParticleSystemQuad *>(_displayRenderNode))
        {
            particle->resetSystem();
        }

        _displayRenderNode->setColor(_bone->getDisplayedColor());
        _displayRenderNode->setOpacity(_bone->getDisplayedOpacity());

        _displayRenderNode->retain();
        _displayRenderNode->setVisible(_visible);

        _displayType = _currentDecoDisplay->getDisplayData()->displayType;
    }
    else
    {
        _displayType =  CS_DISPLAY_MAX;
    }
}

Node *DisplayManager::getDisplayRenderNode() const
{
    return _displayRenderNode;
}


DisplayType DisplayManager::getDisplayRenderNodeType() const
{
    return _displayType;
}

int DisplayManager::getCurrentDisplayIndex() const
{
    return _displayIndex;
}

DecorativeDisplay *DisplayManager::getCurrentDecorativeDisplay() const
{
    return _currentDecoDisplay;
}

DecorativeDisplay *DisplayManager::getDecorativeDisplayByIndex( int index) const
{
    return _decoDisplayList.at(index);
}

void DisplayManager::initDisplayList(BoneData *boneData)
{
    _decoDisplayList.clear();

    CS_RETURN_IF(!boneData);

    for(auto& object : boneData->displayDataList)
    {
        DisplayData *displayData = static_cast<DisplayData *>(object);

        DecorativeDisplay *decoDisplay = DecorativeDisplay::create();
        decoDisplay->setDisplayData(displayData);

        DisplayFactory::createDisplay(_bone, decoDisplay);

        _decoDisplayList.pushBack(decoDisplay);
    }
}


bool DisplayManager::containPoint(Vec2 &point)
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

        Vec2 outPoint;

        Sprite *sprite = (Sprite *)_currentDecoDisplay->getDisplay();
        Sprite *child = (Sprite *)sprite->getChildByTag(0);
        if(nullptr != child)
            sprite = child;

        if (nullptr != sprite)
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
    Vec2 p(x, y);
    return containPoint(p);
}


void DisplayManager::setVisible(bool visible)
{
    if(!_displayRenderNode)
        return;

    _visible = visible;
    _displayRenderNode->setVisible(visible);
}

bool DisplayManager::isVisible() const
{
    return _visible;
}


Size DisplayManager::getContentSize() const
{
    CS_RETURN_IF(!_displayRenderNode) Size(0, 0);
    return _displayRenderNode->getContentSize();
}

Rect DisplayManager::getBoundingBox() const
{
    CS_RETURN_IF(!_displayRenderNode) Rect(0, 0, 0, 0);
    return _displayRenderNode->getBoundingBox();
}


Vec2 DisplayManager::getAnchorPoint() const
{
    CS_RETURN_IF(!_displayRenderNode) Vec2(0, 0);
    return _displayRenderNode->getAnchorPoint();
}

Vec2 DisplayManager::getAnchorPointInPoints() const
{
    CS_RETURN_IF(!_displayRenderNode) Vec2(0, 0);
    return _displayRenderNode->getAnchorPointInPoints();
}


}
