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

#include "ui/UIScrollViewBar.h"
#include "platform/CCImage.h"
#include "2d/CCSprite.h"
#include "base/ccUtils.h"

NS_CC_BEGIN

namespace ui {
    
static const char* HALF_CIRCLE_IMAGE = "iVBORw0KGgoAAAANSUhEUgAAAAwAAAAGCAMAAADAMI+zAAAAJ1BMVEX///////////////////////////////////////////////////9Ruv0SAAAADHRSTlMABgcbbW7Hz9Dz+PmlcJP5AAAAMElEQVR4AUXHwQ2AQAhFwYcLH1H6r1djzDK3ASxUpTBeK/uTCyz7dx54b44m4p5cD1MwAooEJyk3AAAAAElFTkSuQmCC";
static const char* BODY_IMAGE_1_PIXEL_HEIGHT = "iVBORw0KGgoAAAANSUhEUgAAAAwAAAABCAMAAADdNb8LAAAAA1BMVEX///+nxBvIAAAACklEQVR4AWNABgAADQABYc2cpAAAAABJRU5ErkJggg==";

static const char* HALF_CIRCLE_IMAGE_KEY = "/__halfCircleImage";
static const char* BODY_IMAGE_1_PIXEL_HEIGHT_KEY = "/__bodyImage";

static const Color3B DEFAULT_COLOR(52, 65, 87);
static const float DEFAULT_MARGIN = 20;
static const float DEFAULT_AUTO_HIDE_TIME = 0.2f;
static const float DEFAULT_SCROLLBAR_OPACITY = 0.4f;

ScrollViewBar::ScrollViewBar(ScrollView* parent, ScrollView::Direction direction):
_parent(parent),
_direction(direction),
_upperHalfCircle(nullptr),
_lowerHalfCircle(nullptr),
_body(nullptr),
_opacity(255 * DEFAULT_SCROLLBAR_OPACITY),
_marginFromBoundary(DEFAULT_MARGIN),
_marginForLength(DEFAULT_MARGIN),
_touching(false),
_autoHideEnabled(true),
_autoHideTime(DEFAULT_AUTO_HIDE_TIME),
_autoHideRemainingTime(0)
{
    CCASSERT(parent != nullptr, "Parent scroll view must not be null!");
    CCASSERT(direction != ScrollView::Direction::BOTH, "Illegal scroll direction for scroll bar!");
    setCascadeColorEnabled(true);
    setCascadeOpacityEnabled(true);
}

ScrollViewBar::~ScrollViewBar()
{
}

ScrollViewBar* ScrollViewBar::create(ScrollView* parent, ScrollView::Direction direction)
{
    ScrollViewBar* node = new (std::nothrow) ScrollViewBar(parent, direction);
    if (node && node->init())
    {
        node->autorelease();
        return node;
    }
    CC_SAFE_DELETE(node);
    return nullptr;
}

bool ScrollViewBar::init()
{
    if (!ProtectedNode::init())
    {
        return false;
    }
    
    _upperHalfCircle = utils::createSpriteFromBase64Cached(HALF_CIRCLE_IMAGE, HALF_CIRCLE_IMAGE_KEY);
    _upperHalfCircle->setAnchorPoint(Vec2::ANCHOR_MIDDLE_BOTTOM);
    addProtectedChild(_upperHalfCircle);
    
    _lowerHalfCircle = Sprite::createWithTexture(_upperHalfCircle->getTexture(), _upperHalfCircle->getTextureRect(), _upperHalfCircle->isTextureRectRotated());
    _lowerHalfCircle->setScaleY(-1);
    _lowerHalfCircle->setAnchorPoint(Vec2::ANCHOR_MIDDLE_BOTTOM);
    addProtectedChild(_lowerHalfCircle);
    
    _body = utils::createSpriteFromBase64Cached(BODY_IMAGE_1_PIXEL_HEIGHT, BODY_IMAGE_1_PIXEL_HEIGHT_KEY);
    _body->setAnchorPoint(Vec2::ANCHOR_MIDDLE_BOTTOM);
    addProtectedChild(_body);
    
    setColor(DEFAULT_COLOR);
    onScrolled(Vec2::ZERO);
    ProtectedNode::setOpacity(0);
    _autoHideRemainingTime = 0.0f;

    if(_direction == ScrollView::Direction::HORIZONTAL)
    {
        setRotation(90);
    }
    return true;
}
    
void ScrollViewBar::setPositionFromCorner(const Vec2& positionFromCorner)
{
    if(_direction == ScrollView::Direction::VERTICAL)
    {
        _marginForLength = positionFromCorner.y;
        _marginFromBoundary = positionFromCorner.x;
    }
    else
    {
        _marginForLength = positionFromCorner.x;
        _marginFromBoundary = positionFromCorner.y;
    }
}

Vec2 ScrollViewBar::getPositionFromCorner() const
{
    if(_direction == ScrollView::Direction::VERTICAL)
    {
        return Vec2(_marginFromBoundary, _marginForLength);
    }
    else
    {
        return Vec2(_marginForLength, _marginFromBoundary);
    }
}

void ScrollViewBar::setWidth(float width)
{
    float scale = width / _body->getContentSize().width;
    _body->setScaleX(scale);
    _upperHalfCircle->setScale(scale);
    _lowerHalfCircle->setScale(-scale);
}

void ScrollViewBar::setAutoHideEnabled(bool autoHideEnabled)
{
    _autoHideEnabled = autoHideEnabled;
    if (!_autoHideEnabled && !_touching && _autoHideRemainingTime <= 0)
    {
        ProtectedNode::setOpacity(_opacity);
    }
    else
        ProtectedNode::setOpacity(0);
}

float ScrollViewBar::getWidth() const
{
    return _body->getBoundingBox().size.width;
}

void ScrollViewBar::updateLength(float length)
{
    float ratio = length / _body->getTextureRect().size.height;
    _body->setScaleY(ratio);
    _upperHalfCircle->setPositionY(_body->getPositionY() + length);
}

void ScrollViewBar::onEnter()
{
#if CC_ENABLE_SCRIPT_BINDING
    if (_scriptType == kScriptTypeJavascript)
    {
        if (ScriptEngineManager::sendNodeEventToJSExtended(this, kNodeOnEnter))
            return;
    }
#endif
    
    ProtectedNode::onEnter();
    scheduleUpdate();
}

void ScrollViewBar::update(float deltaTime)
{
    processAutoHide(deltaTime);
}
    
void ScrollViewBar::processAutoHide(float deltaTime)
{
   if(!_autoHideEnabled || _autoHideRemainingTime <= 0)
    {
        return;
    }
    else if(_touching)
    {
        // If it is touching, don't auto hide.
        return;
    }
        
    _autoHideRemainingTime -= deltaTime;
    if(_autoHideRemainingTime <= _autoHideTime)
    {
        _autoHideRemainingTime = MAX(0, _autoHideRemainingTime);
        ProtectedNode::setOpacity(_opacity * (_autoHideRemainingTime / _autoHideTime));
    }
}

void ScrollViewBar::onTouchBegan()
{
    if(!_autoHideEnabled)
    {
        return;
    }
    _touching = true;
}

void ScrollViewBar::onTouchEnded()
{
    if(!_autoHideEnabled)
    {
        return;
    }
    _touching = false;
    
    if(_autoHideRemainingTime <= 0)
    {
        // If the remaining time is 0, it means that it didn't moved after touch started so scroll bar is not showing.
        return;
    }
    _autoHideRemainingTime = _autoHideTime;
}

void ScrollViewBar::onScrolled(const Vec2& outOfBoundary)
{
    if(_autoHideEnabled)
    {
        _autoHideRemainingTime = _autoHideTime;
        ProtectedNode::setOpacity(_opacity);
    }
    
    Layout* innerContainer = _parent->getInnerContainer();
    
    float innerContainerMeasure = 0;
    float scrollViewMeasure = 0;
    float outOfBoundaryValue = 0;
    float innerContainerPosition = 0;
    if(_direction == ScrollView::Direction::VERTICAL)
    {
        innerContainerMeasure = innerContainer->getContentSize().height;
        scrollViewMeasure = _parent->getContentSize().height;
        outOfBoundaryValue = outOfBoundary.y;
        innerContainerPosition = -innerContainer->getPositionY();
    }
    else if(_direction == ScrollView::Direction::HORIZONTAL)
    {
        innerContainerMeasure = innerContainer->getContentSize().width;
        scrollViewMeasure = _parent->getContentSize().width;
        outOfBoundaryValue = outOfBoundary.x;
        innerContainerPosition = -innerContainer->getPositionX();
    }
    
    float length = calculateLength(innerContainerMeasure, scrollViewMeasure, outOfBoundaryValue);
    Vec2 position = calculatePosition(innerContainerMeasure, scrollViewMeasure, innerContainerPosition, outOfBoundaryValue, length);
    updateLength(length);
    setPosition(position);
}

float ScrollViewBar::calculateLength(float innerContainerMeasure, float scrollViewMeasure, float outOfBoundaryValue)
{
    float denominatorValue = innerContainerMeasure;
    if(outOfBoundaryValue != 0)
    {
        // If it is out of boundary, the length of scroll bar gets shorter quickly.
        static const float GETTING_SHORTER_FACTOR = 20;
        denominatorValue += (outOfBoundaryValue > 0 ? outOfBoundaryValue : -outOfBoundaryValue) * GETTING_SHORTER_FACTOR;
    }
    
    float lengthRatio = scrollViewMeasure / denominatorValue;
    return fabsf(scrollViewMeasure - 2 * _marginForLength) * lengthRatio;
}

Vec2 ScrollViewBar::calculatePosition(float innerContainerMeasure, float scrollViewMeasure, float innerContainerPosition, float outOfBoundaryValue, float length)
{
    float denominatorValue = innerContainerMeasure - scrollViewMeasure;
    if(outOfBoundaryValue != 0)
    {
        denominatorValue += std::abs(outOfBoundaryValue);
    }
    
    float positionRatio = 0;
    if(denominatorValue != 0)
    {
        positionRatio = innerContainerPosition / denominatorValue;
        positionRatio = MAX(positionRatio, 0);
        positionRatio = MIN(positionRatio, 1);
    }
    float position = (scrollViewMeasure - length - 2 * _marginForLength) * positionRatio + _marginForLength;
    if(_direction == ScrollView::Direction::VERTICAL)
    {
        return Vec2(_parent->getContentSize().width - _marginFromBoundary, position);
    }
    else
    {
        return Vec2(position, _marginFromBoundary);
    }
}
}

NS_CC_END
