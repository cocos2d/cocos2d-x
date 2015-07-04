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

#include "UIScrollViewBar.h"
#include "CCImage.h"
#include "2d/CCSprite.h"
#include "base/base64.h"

NS_CC_BEGIN

namespace ui {
    
static const char* HALF_CIRCLE_IMAGE = "iVBORw0KGgoAAAANSUhEUgAAAAwAAAAGCAMAAADAMI+zAAAAIVBMVEX///////////////////////////////////////////9/gMdvAAAAC3RSTlMAAgMLLFBTYWNkZuZhN4QAAAAvSURBVAjXRchBDgAgCAPBIi0q/3+wxBiZU7cAjJpTNBSPvMLrf7tqgPkR6hB2xzpFkgIfM9q/8QAAAABJRU5ErkJggg==";
static const char* BODY_IMAGE_1_PIXEL_HEIGHT = "iVBORw0KGgoAAAANSUhEUgAAAAwAAAABCAMAAADdNb8LAAAAA1BMVEX///+nxBvIAAAAAXRSTlNm5DccCwAAAApJREFUeAFjQAYAAA0AAWHNnKQAAAAASUVORK5CYII=";

static const Color3B DEFAULT_COLOR(52, 65, 87);
static const float DEFAULT_MARGIN = 20;
static const float DEFAULT_AUTO_HIDE_TIME = 0.2f;

static Sprite* createSpriteFromBase64(const char* base64String)
{
    unsigned char* decoded;
    int length = base64Decode((const unsigned char*) base64String, (unsigned int) strlen(base64String), &decoded);
    
    Image *image = new Image();
    bool imageResult = image->initWithImageData(decoded, length);
    CCASSERT(imageResult, "Failed to create image from base64!");
    free(decoded);
    
    Texture2D *pTexture = new Texture2D();
    pTexture->initWithImage(image);
    pTexture->setAliasTexParameters();
    image->release();
    
    return Sprite::createWithTexture(pTexture);
}
    
ScrollViewBar::ScrollViewBar(ScrollView* parent, ScrollView::Direction direction):
_parent(parent),
_direction(direction),
_upperHalfCircle(nullptr),
_lowerHalfCircle(nullptr),
_body(nullptr),
_touching(false),
_autoHideEnabled(true),
_autoHideTime(DEFAULT_AUTO_HIDE_TIME),
_autoHideRemainingTime(0)
{
    CCASSERT(parent != nullptr, "Parent scroll view must not be null!");
    CCASSERT(direction != ScrollView::Direction::BOTH, "Illegal scroll direction for scroll bar!");
    setCascadeColorEnabled(true);
    setCascadeOpacityEnabled(true);
    
    _positionFromCorner = Vec2(DEFAULT_MARGIN, DEFAULT_MARGIN);
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
    
    _upperHalfCircle = createSpriteFromBase64(HALF_CIRCLE_IMAGE);
    _upperHalfCircle->setAnchorPoint(Vec2::ANCHOR_MIDDLE_BOTTOM);
    addChild(_upperHalfCircle);
    
    _lowerHalfCircle = Sprite::createWithTexture(_upperHalfCircle->getTexture(), _upperHalfCircle->getTextureRect(), _upperHalfCircle->isTextureRectRotated());
    _lowerHalfCircle->setScaleY(-1);
    _lowerHalfCircle->setAnchorPoint(Vec2::ANCHOR_MIDDLE_BOTTOM);
    addChild(_lowerHalfCircle);
    
    _body = createSpriteFromBase64(BODY_IMAGE_1_PIXEL_HEIGHT);
    _body->setAnchorPoint(Vec2::ANCHOR_MIDDLE_BOTTOM);
    addChild(_body);
    
    setColor(DEFAULT_COLOR);
    
    if(_direction == ScrollView::Direction::HORIZONTAL)
    {
        setRotation(90);
    }
    
    if(_autoHideEnabled)
    {
        setOpacity(0);
    }
    return true;
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
    setOpacity(255);
}

float ScrollViewBar::getWidth() const
{
    return _body->getBoundingBox().size.width;
}

void ScrollViewBar::setLength(float length)
{
    float ratio = length / _body->getTextureRect().size.height;
    _body->setScaleY(ratio);
    _upperHalfCircle->setPositionY(_body->getPositionY() + length);
}

void ScrollViewBar::onEnter()
{
    ProtectedNode::onEnter();
    scheduleUpdate();
}

void ScrollViewBar::update(float deltaTime)
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
        this->setOpacity(255 * (_autoHideRemainingTime / _autoHideTime));
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
        setOpacity(255);
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
    
    float length = updateLength(innerContainerMeasure, scrollViewMeasure, outOfBoundaryValue);
    updatePosition(innerContainerMeasure, scrollViewMeasure, innerContainerPosition, outOfBoundaryValue, length);
}

float ScrollViewBar::updateLength(float innerContainerMeasure, float scrollViewMeasure, float outOfBoundaryValue)
{
    float denominatorValue = innerContainerMeasure;
    if(outOfBoundaryValue != 0)
    {
        // If it is out of boundary, the length of scroll bar gets shorter quickly.
        static const float GETTING_SHORTER_FACTOR = 20;
        denominatorValue += (outOfBoundaryValue > 0 ? outOfBoundaryValue : -outOfBoundaryValue) * GETTING_SHORTER_FACTOR;
    }
    
    float lengthRatio = scrollViewMeasure / denominatorValue;
    float marginForLength = (_direction == ScrollView::Direction::HORIZONTAL ? _positionFromCorner.x : _positionFromCorner.y);
    float length = fabsf(scrollViewMeasure - 2 * marginForLength) * lengthRatio;
    setLength(length);
    return length;
}

void ScrollViewBar::updatePosition(float innerContainerMeasure, float scrollViewMeasure, float innerContainerPosition, float outOfBoundaryValue, float length)
{
    float denominatorValue = innerContainerMeasure - scrollViewMeasure;
    if(outOfBoundaryValue != 0)
    {
        denominatorValue += fabs(outOfBoundaryValue);
    }
    
    float positionRatio = 0;
    if(denominatorValue != 0)
    {
        positionRatio = innerContainerPosition / denominatorValue;
        positionRatio = MAX(positionRatio, 0);
        positionRatio = MIN(positionRatio, 1);
    }
    float marginForLength = (_direction == ScrollView::Direction::HORIZONTAL ? _positionFromCorner.x : _positionFromCorner.y);
    float marginFromBoundary = (_direction == ScrollView::Direction::HORIZONTAL ? _positionFromCorner.y : _positionFromCorner.x);
    float position = (scrollViewMeasure - length - 2 * marginForLength) * positionRatio + marginForLength;
    if(_direction == ScrollView::Direction::VERTICAL)
    {
        setPosition(_parent->getContentSize().width - marginFromBoundary, position);
    }
    else if(_direction == ScrollView::Direction::HORIZONTAL)
    {
        setPosition(position, marginFromBoundary);
    }
}
}

NS_CC_END
