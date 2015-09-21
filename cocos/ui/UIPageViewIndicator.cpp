/****************************************************************************
Copyright (c) 2015 Neo Kim (neo.kim@neofect.com)

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

#include "UIPageViewIndicator.h"
#include "2d/CCSprite.h"
#include "base/ccUtils.h"

static const char* CIRCLE_IMAGE = "iVBORw0KGgoAAAANSUhEUgAAABAAAAAQCAMAAAAoLQ9TAAAATlBMVEX///////////////////////////////////////////////////////////////////////////////////////////////////////+QPFRFAAAAGXRSTlMAFBYXUFVWf4GEhYjNz9DR0u/x8vP09fj+spJk/AAAAGFJREFUeNptzkkOgCAMQNGCgoAToEz3v6iVNNoY364/aQF+CbOltEwCyBhaF0aaayO1FxHbI95bpjEOw8qDx1B4KN9wYti/K5aHGYNkzx4SkHo/pqDTJ13UQAbrc/ZugD8XjW0OTSlBlOwAAAAASUVORK5CYII=";

NS_CC_BEGIN

static const float SPACE_BETWEEN_INDEX_NODES_DEFAULT = 23;

namespace ui {

PageViewIndicator* PageViewIndicator::create()
{
    PageViewIndicator* node = new (std::nothrow) PageViewIndicator();
    if (node && node->init())
    {
        node->autorelease();
        return node;
    }
    CC_SAFE_DELETE(node);
    return nullptr;
}

PageViewIndicator::PageViewIndicator()
: _currentIndexNode(nullptr)
, _spaceBetweenIndexNodes(SPACE_BETWEEN_INDEX_NODES_DEFAULT)
{
}

PageViewIndicator::~PageViewIndicator()
{
}

bool PageViewIndicator::init()
{
    _currentIndexNode = (Node*) utils::createSpriteFromBase64(CIRCLE_IMAGE);
    _currentIndexNode->setVisible(false);
    addProtectedChild(_currentIndexNode);
    return true;
}

void PageViewIndicator::indicate(int index)
{
    CCASSERT(index >= 0 && index < _indexNodes.size(), "");
    _currentIndexNode->setPosition(_indexNodes.at(index)->getPosition());
}

void PageViewIndicator::rearrange()
{
    if(_indexNodes.empty())
    {
        return;
    }

//    bool bHorizon = m_eContainerDirection == CONTAINER_HORIZONTAL;
    bool horizontal = true;

    // Positions
    Size indexNodeSize = _indexNodes.at(0)->getContentSize();
    float sizeValue = (horizontal ? indexNodeSize.width : indexNodeSize.height);

    float posValue = -sizeValue / 2;
    for(auto indexNode : _indexNodes) {
        posValue += sizeValue + _spaceBetweenIndexNodes;
        Vec2 position;
        if(horizontal)
        {
            position = Vec2(posValue, indexNodeSize.height / 2.0f);
        }
        else
        {
            position = Vec2(indexNodeSize.width / 2.0f, posValue);
        }
        indexNode->setPosition(position);
    }

}

void PageViewIndicator::setSpaceBetweenIndexNodes(float spaceBetweenIndexNodes)
{
    if(_spaceBetweenIndexNodes == spaceBetweenIndexNodes)
    {
        return;
    }
    _spaceBetweenIndexNodes = spaceBetweenIndexNodes;
    rearrange();
}

void PageViewIndicator::increaseNumberOfPages()
{
    Sprite* indexNode = utils::createSpriteFromBase64(CIRCLE_IMAGE);
    indexNode->setOpacity(255 * 0.3f);
    addProtectedChild(indexNode);
    _indexNodes.pushBack(indexNode);
    rearrange();

    if(_indexNodes.size() == 1) {
        _currentIndexNode->setVisible(true);
        indicate(0);
    }
}

void PageViewIndicator::decreaseNumberOfPages()
{
    (*(_indexNodes.end() - 1))->removeFromParent();
    _indexNodes.erase(_indexNodes.end() - 1);
    rearrange();

    if(_indexNodes.empty())
    {
        _currentIndexNode->setVisible(false);
    }
}

void PageViewIndicator::clear()
{
    for(auto indexNode : _indexNodes)
    {
        removeProtectedChild(indexNode);
    }
    _indexNodes.clear();
    _currentIndexNode->setVisible(false);
}

}

NS_CC_END
