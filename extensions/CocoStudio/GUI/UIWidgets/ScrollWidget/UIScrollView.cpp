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

#include "UIScrollView.h"

NS_CC_EXT_BEGIN

#define AUTOSCROLLMAXSPEED 1000.0f

const CCPoint SCROLLDIR_UP = CCPointMake(0.0f, 1.0f);
const CCPoint SCROLLDIR_DOWN = CCPointMake(0.0f, -1.0f);
const CCPoint SCROLLDIR_LEFT = CCPointMake(-1.0f, 0.0f);
const CCPoint SCROLLDIR_RIGHT = CCPointMake(1.0f, 0.0f);

UIScrollView::UIScrollView():
m_pInnerContainer(NULL),
m_eDirection(SCROLLVIEW_DIR_VERTICAL),
m_touchBeganPoint(CCPointZero),
m_touchMovedPoint(CCPointZero),
m_touchEndedPoint(CCPointZero),
m_touchMovingPoint(CCPointZero),
m_autoScrollDir(CCPointZero),
m_fTopBoundary(0.0f),
m_fBottomBoundary(0.0f),
m_fLeftBoundary(0.0f),
m_fRightBoundary(0.0f),
m_fBounceTopBoundary(0.0f),
m_fBounceBottomBoundary(0.0f),
m_fBounceLeftBoundary(0.0f),
m_fBounceRightBoundary(0.0f),
m_bAutoScroll(false),
m_fAutoScrollAddUpTime(0.0f),
m_fAutoScrollOriginalSpeed(0.0f),
m_fAutoScrollAcceleration(-1000.0f),
m_bIsAutoScrollSpeedAttenuated(false),
m_bNeedCheckAutoScrollDestination(false),
m_autoScrollDestination(CCPointZero),
m_bBePressed(false),
m_fSlidTime(0.0f),
moveChildPoint(CCPointZero),
m_fChildFocusCancelOffset(5.0f),
m_bLeftBounceNeeded(false),
m_bTopBounceNeeded(false),
m_bRightBounceNeeded(false),
m_bBottomBounceNeeded(false),
m_bBounceEnabled(false),
m_bBouncing(false),
m_bounceDir(CCPointZero),
m_fBounceOriginalSpeed(0.0f),
m_bInertiaScrollEnabled(true),
m_pScrollViewEventListener(NULL),
m_pfnScrollViewEventSelector(NULL),
/*******Compatible*******/
m_pScrollToTopListener(NULL),
m_pfnScrollToTopSelector(NULL),
m_pScrollToBottomListener(NULL),
m_pfnScrollToBottomSelector(NULL),
m_pScrollToLeftListener(NULL),
m_pfnScrollToLeftSelector(NULL),
m_pScrollToRightListener(NULL),
m_pfnScrollToRightSelector(NULL)
/************************/
{
}

UIScrollView::~UIScrollView()
{
    m_pScrollViewEventListener = NULL;
    m_pfnScrollViewEventSelector = NULL;
    m_pScrollToTopListener = NULL;
    m_pfnScrollToTopSelector = NULL;
    m_pScrollToBottomListener = NULL;
    m_pfnScrollToBottomSelector = NULL;
    m_pScrollToLeftListener = NULL;
    m_pfnScrollToLeftSelector = NULL;
    m_pScrollToRightListener = NULL;
    m_pfnScrollToRightSelector = NULL;
}

UIScrollView* UIScrollView::create()
{
    UIScrollView* widget = new UIScrollView();
    if (widget && widget->init())
    {
        widget->autorelease();
        return widget;
    }
    CC_SAFE_DELETE(widget);
    return NULL;
}

bool UIScrollView::init()
{
    if (UILayout::init())
    {
        setUpdateEnabled(true);
        setTouchEnabled(true);
        setClippingEnabled(true);
        m_pInnerContainer->setTouchEnabled(false);
        return true;
    }
    return false;
}

void UIScrollView::initRenderer()
{
    UILayout::initRenderer();
    m_pInnerContainer = UILayout::create();
    UILayout::addChild(m_pInnerContainer);
}

void UIScrollView::onSizeChanged()
{
    UILayout::onSizeChanged();
    m_fTopBoundary = m_size.height;
    m_fRightBoundary = m_size.width;
    float bounceBoundaryParameterX = m_size.width / 3.0f;
    float bounceBoundaryParameterY = m_size.height / 3.0f;
    m_fBounceTopBoundary = m_size.height - bounceBoundaryParameterY;
    m_fBounceBottomBoundary = bounceBoundaryParameterY;
    m_fBounceLeftBoundary = bounceBoundaryParameterX;
    m_fBounceRightBoundary = m_size.width - bounceBoundaryParameterX;
    CCSize innerSize = m_pInnerContainer->getSize();
    float orginInnerSizeWidth = innerSize.width;
    float orginInnerSizeHeight = innerSize.height;
    float innerSizeWidth = MAX(orginInnerSizeWidth, m_size.width);
    float innerSizeHeight = MAX(orginInnerSizeHeight, m_size.height);
    m_pInnerContainer->setSize(CCSizeMake(innerSizeWidth, innerSizeHeight));
    m_pInnerContainer->setPosition(ccp(0, m_size.height - m_pInnerContainer->getSize().height));
}

void UIScrollView::setInnerContainerSize(const cocos2d::CCSize &size)
{
    float innerSizeWidth = m_size.width;
    float innerSizeHeight = m_size.height;
    CCSize originalInnerSize = m_pInnerContainer->getSize();
    if (size.width < m_size.width)
    {
        CCLOG("Inner width <= scrollview width, it will be force sized!");
    }
    else
    {
        innerSizeWidth = size.width;
    }
    if (size.height < m_size.height)
    {
        CCLOG("Inner height <= scrollview height, it will be force sized!");
    }
    else
    {
        innerSizeHeight = size.height;
    }
    m_pInnerContainer->setSize(CCSizeMake(innerSizeWidth, innerSizeHeight));

    switch (m_eDirection)
    {
        case SCROLLVIEW_DIR_VERTICAL:
        {
            CCSize newInnerSize = m_pInnerContainer->getSize();
            float offset = originalInnerSize.height - newInnerSize.height;
            scrollChildren(0.0f, offset);
            break;
        }
        case SCROLLVIEW_DIR_HORIZONTAL:
        {
            if (m_pInnerContainer->getRightInParent() <= m_size.width)
            {
                CCSize newInnerSize = m_pInnerContainer->getSize();
                float offset = originalInnerSize.width - newInnerSize.width;
                scrollChildren(offset, 0.0f);
            }
            break;
        }
        case SCROLLVIEW_DIR_BOTH:
        {
            CCSize newInnerSize = m_pInnerContainer->getSize();
            float offsetY = originalInnerSize.height - newInnerSize.height;
            float offsetX = 0.0f;
            if (m_pInnerContainer->getRightInParent() <= m_size.width)
            {
                offsetX = originalInnerSize.width - newInnerSize.width;
            }
            scrollChildren(offsetX, offsetY);
            break;
        }
        default:
            break;
    }
}

const CCSize& UIScrollView::getInnerContainerSize() const
{
	return m_pInnerContainer->getSize();
}

bool UIScrollView::addChild(UIWidget* widget)
{
    return m_pInnerContainer->addChild(widget);
}

void UIScrollView::removeAllChildren()
{
    m_pInnerContainer->removeAllChildren();
}

bool UIScrollView::removeChild(UIWidget* child)
{
	return m_pInnerContainer->removeChild(child);
}

CCArray* UIScrollView::getChildren()
{
    return m_pInnerContainer->getChildren();
}

void UIScrollView::moveChildren(float offsetX, float offsetY)
{
    moveChildPoint = ccpAdd(m_pInnerContainer->getPosition(), ccp(offsetX, offsetY));
    m_pInnerContainer->setPosition(moveChildPoint);
}

void UIScrollView::autoScrollChildren(float dt)
{
    float lastTime = m_fAutoScrollAddUpTime;
    m_fAutoScrollAddUpTime += dt;
    if (m_bIsAutoScrollSpeedAttenuated)
    {
        float nowSpeed = m_fAutoScrollOriginalSpeed + m_fAutoScrollAcceleration * m_fAutoScrollAddUpTime;
        if (nowSpeed <= 0.0f)
        {
            stopAutoScrollChildren();
            checkNeedBounce();
        }
        else
        {
            float timeParam = lastTime * 2 + dt;
            float offset = (m_fAutoScrollOriginalSpeed + m_fAutoScrollAcceleration * timeParam * 0.5f) * dt;
            float offsetX = offset * m_autoScrollDir.x;
            float offsetY = offset * m_autoScrollDir.y;
            if (!scrollChildren(offsetX, offsetY))
            {
                stopAutoScrollChildren();
                checkNeedBounce();
            }
        }
    }
    else
    {
        if (m_bNeedCheckAutoScrollDestination)
        {
            float xOffset = m_autoScrollDir.x * dt * m_fAutoScrollOriginalSpeed;
            float yOffset = m_autoScrollDir.y * dt * m_fAutoScrollOriginalSpeed;
            bool notDone = checkCustomScrollDestination(&xOffset, &yOffset);
            bool scrollCheck = scrollChildren(xOffset, yOffset);
            if (!notDone || !scrollCheck)
            {
                stopAutoScrollChildren();
                checkNeedBounce();
            }
        }
        else
        {
            if (!scrollChildren(m_autoScrollDir.x * dt * m_fAutoScrollOriginalSpeed, m_autoScrollDir.y * dt * m_fAutoScrollOriginalSpeed))
            {
                stopAutoScrollChildren();
                checkNeedBounce();
            }
        }
    }
}

void UIScrollView::bounceChildren(float dt)
{
    if (m_fBounceOriginalSpeed <= 0.0f)
    {
        stopBounceChildren();
    }
    if (!bounceScrollChildren(m_bounceDir.x * dt * m_fBounceOriginalSpeed, m_bounceDir.y * dt * m_fBounceOriginalSpeed))
    {
        stopBounceChildren();
    }
}

bool UIScrollView::checkNeedBounce()
{
    if (!m_bBounceEnabled)
    {
        return false;
    }
    checkBounceBoundary();
    if (m_bTopBounceNeeded || m_bBottomBounceNeeded || m_bLeftBounceNeeded || m_bRightBounceNeeded)
    {
        if (m_bTopBounceNeeded && m_bLeftBounceNeeded)
        {
            CCPoint scrollVector = ccpSub(ccp(0.0f, m_size.height), ccp(m_pInnerContainer->getLeftInParent(), m_pInnerContainer->getTopInParent()));
            float orSpeed = scrollVector.getLength()/(0.2f);
            m_bounceDir = ccpNormalize(scrollVector);
            startBounceChildren(orSpeed);
        }
        else if (m_bTopBounceNeeded && m_bRightBounceNeeded)
        {
            CCPoint scrollVector = ccpSub(ccp(m_size.width, m_size.height), ccp(m_pInnerContainer->getRightInParent(), m_pInnerContainer->getTopInParent()));
            float orSpeed = scrollVector.getLength()/(0.2f);
            m_bounceDir = ccpNormalize(scrollVector);
            startBounceChildren(orSpeed);
        }
        else if (m_bBottomBounceNeeded && m_bLeftBounceNeeded)
        {
            CCPoint scrollVector = ccpSub(CCPointZero, ccp(m_pInnerContainer->getLeftInParent(), m_pInnerContainer->getBottomInParent()));
            float orSpeed = scrollVector.getLength()/(0.2f);
            m_bounceDir = ccpNormalize(scrollVector);
            startBounceChildren(orSpeed);
        }
        else if (m_bBottomBounceNeeded && m_bRightBounceNeeded)
        {
            CCPoint scrollVector = ccpSub(ccp(m_size.width, 0.0f), ccp(m_pInnerContainer->getRightInParent(), m_pInnerContainer->getBottomInParent()));
            float orSpeed = scrollVector.getLength()/(0.2f);
            m_bounceDir = ccpNormalize(scrollVector);
            startBounceChildren(orSpeed);
        }
        else if (m_bTopBounceNeeded)
        {
            CCPoint scrollVector = ccpSub(ccp(0.0f, m_size.height), ccp(0.0f, m_pInnerContainer->getTopInParent()));
            float orSpeed = scrollVector.getLength()/(0.2f);
            m_bounceDir = ccpNormalize(scrollVector);
            startBounceChildren(orSpeed);
        }
        else if (m_bBottomBounceNeeded)
        {
            CCPoint scrollVector = ccpSub(CCPointZero, ccp(0.0f, m_pInnerContainer->getBottomInParent()));
            float orSpeed = scrollVector.getLength()/(0.2f);
            m_bounceDir = ccpNormalize(scrollVector);
            startBounceChildren(orSpeed);
        }
        else if (m_bLeftBounceNeeded)
        {
            CCPoint scrollVector = ccpSub(CCPointZero, ccp(m_pInnerContainer->getLeftInParent(), 0.0f));
            float orSpeed = scrollVector.getLength()/(0.2f);
            m_bounceDir = ccpNormalize(scrollVector);
            startBounceChildren(orSpeed);
        }
        else if (m_bRightBounceNeeded)
        {
            CCPoint scrollVector = ccpSub(ccp(m_size.width, 0.0f), ccp(m_pInnerContainer->getRightInParent(), 0.0f));
            float orSpeed = scrollVector.getLength()/(0.2f);
            m_bounceDir = ccpNormalize(scrollVector);
            startBounceChildren(orSpeed);
        }
        return true;
    }
    return false;
}

void UIScrollView::checkBounceBoundary()
{
    float icBottomPos = m_pInnerContainer->getBottomInParent();
    if (icBottomPos > m_fBottomBoundary)
    {
        scrollToBottomEvent();
        m_bBottomBounceNeeded = true;
    }
    else
    {
        m_bBottomBounceNeeded = false;
    }
    float icTopPos = m_pInnerContainer->getTopInParent();
    if (icTopPos < m_fTopBoundary)
    {
        scrollToTopEvent();
        m_bTopBounceNeeded = true;
    }
    else
    {
        m_bTopBounceNeeded = false;
    }
    float icRightPos = m_pInnerContainer->getRightInParent();
    if (icRightPos < m_fRightBoundary)
    {
        scrollToRightEvent();
        m_bRightBounceNeeded = true;
    }
    else
    {
        m_bRightBounceNeeded = false;
    }
    float icLeftPos = m_pInnerContainer->getLeftInParent();
    if (icLeftPos > m_fLeftBoundary)
    {
        scrollToLeftEvent();
        m_bLeftBounceNeeded = true;
    }
    else
    {
        m_bLeftBounceNeeded = false;
    }
}

void UIScrollView::startBounceChildren(float v)
{
    m_fBounceOriginalSpeed = v;
    m_bBouncing = true;
}

void UIScrollView::stopBounceChildren()
{
    m_bBouncing = false;
    m_fBounceOriginalSpeed = 0.0f;
    m_bLeftBounceNeeded = false;
    m_bRightBounceNeeded = false;
    m_bTopBounceNeeded = false;
    m_bBottomBounceNeeded = false;
}

void UIScrollView::startAutoScrollChildrenWithOriginalSpeed(const CCPoint& dir, float v, bool attenuated, float acceleration)
{
    stopAutoScrollChildren();
    m_autoScrollDir = dir;
    m_bIsAutoScrollSpeedAttenuated = attenuated;
    m_fAutoScrollOriginalSpeed = v;
    m_bAutoScroll = true;
    m_fAutoScrollAcceleration = acceleration;
}

void UIScrollView::startAutoScrollChildrenWithDestination(const CCPoint& des, float time, bool attenuated)
{
    m_bNeedCheckAutoScrollDestination = false;
    m_autoScrollDestination = des;
    CCPoint dis = ccpSub(des, m_pInnerContainer->getPosition());
    CCPoint dir = ccpNormalize(dis);
    float orSpeed = 0.0f;
    float acceleration = -1000.0f;
    if (attenuated)
    {
        acceleration = (-(2 * dis.getLength())) / (time * time);
        orSpeed =  2 * dis.getLength() / time;
    }
    else
    {
        m_bNeedCheckAutoScrollDestination = true;
        orSpeed = dis.getLength() / time;
    }
    startAutoScrollChildrenWithOriginalSpeed(dir, orSpeed, attenuated, acceleration);
}

void UIScrollView::jumpToDestination(const cocos2d::CCPoint &des)
{
    float finalOffsetX = des.x;
    float finalOffsetY = des.y;
    switch (m_eDirection)
    {
        case SCROLLVIEW_DIR_VERTICAL:
            if (des.y <= 0)
            {
                finalOffsetY = MAX(des.y, m_size.height - m_pInnerContainer->getSize().height);
            }
            break;
        case SCROLLVIEW_DIR_HORIZONTAL:
            if (des.x <= 0)
            {
                finalOffsetX = MAX(des.x, m_size.width - m_pInnerContainer->getSize().width);
            }
            break;
        case SCROLLVIEW_DIR_BOTH:
            if (des.y <= 0)
            {
                finalOffsetY = MAX(des.y, m_size.height - m_pInnerContainer->getSize().height);
            }
            if (des.x <= 0)
            {
                finalOffsetX = MAX(des.x, m_size.width - m_pInnerContainer->getSize().width);
            }
            break;
        default:
            break;
    }
    m_pInnerContainer->setPosition(ccp(finalOffsetX, finalOffsetY));
}

void UIScrollView::stopAutoScrollChildren()
{
    m_bAutoScroll = false;
    m_fAutoScrollOriginalSpeed = 0.0f;
    m_fAutoScrollAddUpTime = 0.0f;
}

bool UIScrollView::bounceScrollChildren(float touchOffsetX, float touchOffsetY)
{
    bool scrollenabled = true;
    if (touchOffsetX > 0.0f && touchOffsetY > 0.0f) //first quadrant //bounce to top-right
    {
        float realOffsetX = touchOffsetX;
        float realOffsetY = touchOffsetY;
        float icRightPos = m_pInnerContainer->getRightInParent();
        if (icRightPos + realOffsetX >= m_fRightBoundary)
        {
            realOffsetX = m_fRightBoundary - icRightPos;
            bounceRightEvent();
            scrollenabled = false;
        }
        float icTopPos = m_pInnerContainer->getTopInParent();
        if (icTopPos + touchOffsetY >= m_fTopBoundary)
        {
            realOffsetY = m_fTopBoundary - icTopPos;
            bounceTopEvent();
            scrollenabled = false;
        }
        moveChildren(realOffsetX, realOffsetY);
    }
    else if(touchOffsetX < 0.0f && touchOffsetY > 0.0f) //second quadrant //bounce to top-left
    {
        float realOffsetX = touchOffsetX;
        float realOffsetY = touchOffsetY;
        float icLefrPos = m_pInnerContainer->getLeftInParent();
        if (icLefrPos + realOffsetX <= m_fLeftBoundary)
        {
            realOffsetX = m_fLeftBoundary - icLefrPos;
            bounceLeftEvent();
            scrollenabled = false;
        }
        float icTopPos = m_pInnerContainer->getTopInParent();
        if (icTopPos + touchOffsetY >= m_fTopBoundary)
        {
            realOffsetY = m_fTopBoundary - icTopPos;
            bounceTopEvent();
            scrollenabled = false;
        }
        moveChildren(realOffsetX, realOffsetY);
    }
    else if (touchOffsetX < 0.0f && touchOffsetY < 0.0f) //third quadrant //bounce to bottom-left
    {
        float realOffsetX = touchOffsetX;
        float realOffsetY = touchOffsetY;
        float icLefrPos = m_pInnerContainer->getLeftInParent();
        if (icLefrPos + realOffsetX <= m_fLeftBoundary)
        {
            realOffsetX = m_fLeftBoundary - icLefrPos;
            bounceLeftEvent();
            scrollenabled = false;
        }
        float icBottomPos = m_pInnerContainer->getBottomInParent();
        if (icBottomPos + touchOffsetY <= m_fBottomBoundary)
        {
            realOffsetY = m_fBottomBoundary - icBottomPos;
            bounceBottomEvent();
            scrollenabled = false;
        }
        moveChildren(realOffsetX, realOffsetY);
    }
    else if (touchOffsetX > 0.0f && touchOffsetY < 0.0f) //forth quadrant //bounce to bottom-right
    {
        float realOffsetX = touchOffsetX;
        float realOffsetY = touchOffsetY;
        float icRightPos = m_pInnerContainer->getRightInParent();
        if (icRightPos + realOffsetX >= m_fRightBoundary)
        {
            realOffsetX = m_fRightBoundary - icRightPos;
            bounceRightEvent();
            scrollenabled = false;
        }
        float icBottomPos = m_pInnerContainer->getBottomInParent();
        if (icBottomPos + touchOffsetY <= m_fBottomBoundary)
        {
            realOffsetY = m_fBottomBoundary - icBottomPos;
            bounceBottomEvent();
            scrollenabled = false;
        }
        moveChildren(realOffsetX, realOffsetY);
    }
    else if (touchOffsetX == 0.0f && touchOffsetY > 0.0f) // bounce to top
    {
        float realOffsetY = touchOffsetY;
        float icTopPos = m_pInnerContainer->getTopInParent();
        if (icTopPos + touchOffsetY >= m_fTopBoundary)
        {
            realOffsetY = m_fTopBoundary - icTopPos;
            bounceTopEvent();
            scrollenabled = false;
        }
        moveChildren(0.0f, realOffsetY);
    }
    else if (touchOffsetX == 0.0f && touchOffsetY < 0.0f) //bounce to bottom
    {
        float realOffsetY = touchOffsetY;
        float icBottomPos = m_pInnerContainer->getBottomInParent();
        if (icBottomPos + touchOffsetY <= m_fBottomBoundary)
        {
            realOffsetY = m_fBottomBoundary - icBottomPos;
            bounceBottomEvent();
            scrollenabled = false;
        }
        moveChildren(0.0f, realOffsetY);
    }
    else if (touchOffsetX > 0.0f && touchOffsetY == 0.0f) //bounce to right
    {
        float realOffsetX = touchOffsetX;
        float icRightPos = m_pInnerContainer->getRightInParent();
        if (icRightPos + realOffsetX >= m_fRightBoundary)
        {
            realOffsetX = m_fRightBoundary - icRightPos;
            bounceRightEvent();
            scrollenabled = false;
        }
        moveChildren(realOffsetX, 0.0f);
    }
    else if (touchOffsetX < 0.0f && touchOffsetY == 0.0f) //bounce to left
    {
        float realOffsetX = touchOffsetX;
        float icLeftPos = m_pInnerContainer->getLeftInParent();
        if (icLeftPos + realOffsetX <= m_fLeftBoundary)
        {
            realOffsetX = m_fLeftBoundary - icLeftPos;
            bounceLeftEvent();
            scrollenabled = false;
        }
        moveChildren(realOffsetX, 0.0f);
    }
    return scrollenabled;
}

bool UIScrollView::checkCustomScrollDestination(float* touchOffsetX, float* touchOffsetY)
{
    bool scrollenabled = true;
    switch (m_eDirection)
    {
        case SCROLLVIEW_DIR_VERTICAL: // vertical
        {
            if (m_autoScrollDir.y > 0)
            {
                float icBottomPos = m_pInnerContainer->getBottomInParent();
                if (icBottomPos + *touchOffsetY >= m_autoScrollDestination.y)
                {
                    *touchOffsetY = m_autoScrollDestination.y - icBottomPos;
                    scrollenabled = false;
                }
            }
            else
            {
                float icBottomPos = m_pInnerContainer->getBottomInParent();
                if (icBottomPos + *touchOffsetY <= m_autoScrollDestination.y)
                {
                    *touchOffsetY = m_autoScrollDestination.y - icBottomPos;
                    scrollenabled = false;
                }
            }
            break;
        }
        case SCROLLVIEW_DIR_HORIZONTAL: // horizontal
        {
            if (m_autoScrollDir.x > 0)
            {
                float icLeftPos = m_pInnerContainer->getLeftInParent();
                if (icLeftPos + *touchOffsetX >= m_autoScrollDestination.x)
                {
                    *touchOffsetX = m_autoScrollDestination.x - icLeftPos;
                    scrollenabled = false;
                }
            }
            else
            {
                float icLeftPos = m_pInnerContainer->getLeftInParent();
                if (icLeftPos + *touchOffsetX <= m_autoScrollDestination.x)
                {
                    *touchOffsetX = m_autoScrollDestination.x - icLeftPos;
                    scrollenabled = false;
                }
            }
            break;
        }
        case SCROLLVIEW_DIR_BOTH:
        {
            if (*touchOffsetX > 0.0f && *touchOffsetY > 0.0f) // up right
            {
                float icLeftPos = m_pInnerContainer->getLeftInParent();
                if (icLeftPos + *touchOffsetX >= m_autoScrollDestination.x)
                {
                    *touchOffsetX = m_autoScrollDestination.x - icLeftPos;
                    scrollenabled = false;
                }
                float icBottomPos = m_pInnerContainer->getBottomInParent();
                if (icBottomPos + *touchOffsetY >= m_autoScrollDestination.y)
                {
                    *touchOffsetY = m_autoScrollDestination.y - icBottomPos;
                    scrollenabled = false;
                }
            }
            else if (*touchOffsetX < 0.0f && *touchOffsetY > 0.0f) // up left
            {
                float icRightPos = m_pInnerContainer->getRightInParent();
                if (icRightPos + *touchOffsetX <= m_autoScrollDestination.x)
                {
                    *touchOffsetX = m_autoScrollDestination.x - icRightPos;
                    scrollenabled = false;
                }
                float icBottomPos = m_pInnerContainer->getBottomInParent();
                if (icBottomPos + *touchOffsetY >= m_autoScrollDestination.y)
                {
                    *touchOffsetY = m_autoScrollDestination.y - icBottomPos;
                    scrollenabled = false;
                }
            }
            else if (*touchOffsetX < 0.0f && *touchOffsetY < 0.0f) // down left
            {
                float icRightPos = m_pInnerContainer->getRightInParent();
                if (icRightPos + *touchOffsetX <= m_autoScrollDestination.x)
                {
                    *touchOffsetX = m_autoScrollDestination.x - icRightPos;
                    scrollenabled = false;
                }
                float icTopPos = m_pInnerContainer->getTopInParent();
                if (icTopPos + *touchOffsetY <= m_autoScrollDestination.y)
                {
                    *touchOffsetY = m_autoScrollDestination.y - icTopPos;
                    scrollenabled = false;
                }
            }
            else if (*touchOffsetX > 0.0f && *touchOffsetY < 0.0f) // down right
            {
                float icLeftPos = m_pInnerContainer->getLeftInParent();
                if (icLeftPos + *touchOffsetX >= m_autoScrollDestination.x)
                {
                    *touchOffsetX = m_autoScrollDestination.x - icLeftPos;
                    scrollenabled = false;
                }
                float icTopPos = m_pInnerContainer->getTopInParent();
                if (icTopPos + *touchOffsetY <= m_autoScrollDestination.y)
                {
                    *touchOffsetY = m_autoScrollDestination.y - icTopPos;
                    scrollenabled = false;
                }
            }
            else if (*touchOffsetX == 0.0f && *touchOffsetY > 0.0f) // up
            {
                float icBottomPos = m_pInnerContainer->getBottomInParent();
                if (icBottomPos + *touchOffsetY >= m_autoScrollDestination.y)
                {
                    *touchOffsetY = m_autoScrollDestination.y - icBottomPos;
                    scrollenabled = false;
                }
            }
            else if (*touchOffsetX < 0.0f && *touchOffsetY == 0.0f) // left
            {
                float icRightPos = m_pInnerContainer->getRightInParent();
                if (icRightPos + *touchOffsetX <= m_autoScrollDestination.x)
                {
                    *touchOffsetX = m_autoScrollDestination.x - icRightPos;
                    scrollenabled = false;
                }
            }
            else if (*touchOffsetX == 0.0f && *touchOffsetY < 0.0f) // down
            {
                float icTopPos = m_pInnerContainer->getTopInParent();
                if (icTopPos + *touchOffsetY <= m_autoScrollDestination.y)
                {
                    *touchOffsetY = m_autoScrollDestination.y - icTopPos;
                    scrollenabled = false;
                }
            }
            else if (*touchOffsetX > 0.0f && *touchOffsetY == 0.0f) // right
            {
                float icLeftPos = m_pInnerContainer->getLeftInParent();
                if (icLeftPos + *touchOffsetX >= m_autoScrollDestination.x)
                {
                    *touchOffsetX = m_autoScrollDestination.x - icLeftPos;
                    scrollenabled = false;
                }
            }
            break;
        }
        default:
            break;
    }
    return scrollenabled;
}

bool UIScrollView::scrollChildren(float touchOffsetX, float touchOffsetY)
{
    bool scrollenabled = true;
    scrollingEvent();
    switch (m_eDirection)
    {
        case SCROLLVIEW_DIR_VERTICAL: // vertical
        {
            float realOffset = touchOffsetY;
            if (m_bBounceEnabled)
            {
                float icBottomPos = m_pInnerContainer->getBottomInParent();
                if (icBottomPos + touchOffsetY >= m_fBounceBottomBoundary)
                {
                    realOffset = m_fBounceBottomBoundary - icBottomPos;
                    scrollToBottomEvent();
                    scrollenabled = false;
                }
                float icTopPos = m_pInnerContainer->getTopInParent();
                if (icTopPos + touchOffsetY <= m_fBounceTopBoundary)
                {
                    realOffset = m_fBounceTopBoundary - icTopPos;
                    scrollToTopEvent();
                    scrollenabled = false;
                }
            }
            else
            {
                float icBottomPos = m_pInnerContainer->getBottomInParent();
                if (icBottomPos + touchOffsetY >= m_fBottomBoundary)
                {
                    realOffset = m_fBottomBoundary - icBottomPos;
                    scrollToBottomEvent();
                    scrollenabled = false;
                }
                float icTopPos = m_pInnerContainer->getTopInParent();
                if (icTopPos + touchOffsetY <= m_fTopBoundary)
                {
                    realOffset = m_fTopBoundary - icTopPos;
                    scrollToTopEvent();
                    scrollenabled = false;
                }
            }
            moveChildren(0.0f, realOffset);
            break;
        }
        case SCROLLVIEW_DIR_HORIZONTAL: // horizontal
        {
            float realOffset = touchOffsetX;
            if (m_bBounceEnabled)
            {
                float icRightPos = m_pInnerContainer->getRightInParent();
                if (icRightPos + touchOffsetX <= m_fBounceRightBoundary)
                {
                    realOffset = m_fBounceRightBoundary - icRightPos;
                    scrollToRightEvent();
                    scrollenabled = false;
                }
                float icLeftPos = m_pInnerContainer->getLeftInParent();
                if (icLeftPos + touchOffsetX >= m_fBounceLeftBoundary)
                {
                    realOffset = m_fBounceLeftBoundary - icLeftPos;
                    scrollToLeftEvent();
                    scrollenabled = false;
                }
            }
            else
            {
                float icRightPos = m_pInnerContainer->getRightInParent();
                if (icRightPos + touchOffsetX <= m_fRightBoundary)
                {
                    realOffset = m_fRightBoundary - icRightPos;
                    scrollToRightEvent();
                    scrollenabled = false;
                }
                float icLeftPos = m_pInnerContainer->getLeftInParent();
                if (icLeftPos + touchOffsetX >= m_fLeftBoundary)
                {
                    realOffset = m_fLeftBoundary - icLeftPos;
                    scrollToLeftEvent();
                    scrollenabled = false;
                }
            }
            moveChildren(realOffset, 0.0f);
            break;
        }
        case SCROLLVIEW_DIR_BOTH:
        {
            float realOffsetX = touchOffsetX;
            float realOffsetY = touchOffsetY;
            if (m_bBounceEnabled)
            {
                if (touchOffsetX > 0.0f && touchOffsetY > 0.0f) // up right
                {
                    float icLeftPos = m_pInnerContainer->getLeftInParent();
                    if (icLeftPos + touchOffsetX >= m_fBounceLeftBoundary)
                    {
                        realOffsetX = m_fBounceLeftBoundary - icLeftPos;
                        scrollToLeftEvent();
                        scrollenabled = false;
                    }
                    float icBottomPos = m_pInnerContainer->getBottomInParent();
                    if (icBottomPos + touchOffsetY >= m_fBounceBottomBoundary)
                    {
                        realOffsetY = m_fBounceBottomBoundary - icBottomPos;
                        scrollToBottomEvent();
                        scrollenabled = false;
                    }
                }
                else if (touchOffsetX < 0.0f && touchOffsetY > 0.0f) // up left
                {
                    float icRightPos = m_pInnerContainer->getRightInParent();
                    if (icRightPos + touchOffsetX <= m_fBounceRightBoundary)
                    {
                        realOffsetX = m_fBounceRightBoundary - icRightPos;
                        scrollToRightEvent();
                        scrollenabled = false;
                    }
                    float icBottomPos = m_pInnerContainer->getBottomInParent();
                    if (icBottomPos + touchOffsetY >= m_fBounceBottomBoundary)
                    {
                        realOffsetY = m_fBounceBottomBoundary - icBottomPos;
                        scrollToBottomEvent();
                        scrollenabled = false;
                    }
                }
                else if (touchOffsetX < 0.0f && touchOffsetY < 0.0f) // down left
                {
                    float icRightPos = m_pInnerContainer->getRightInParent();
                    if (icRightPos + touchOffsetX <= m_fBounceRightBoundary)
                    {
                        realOffsetX = m_fBounceRightBoundary - icRightPos;
                        scrollToRightEvent();
                        scrollenabled = false;
                    }
                    float icTopPos = m_pInnerContainer->getTopInParent();
                    if (icTopPos + touchOffsetY <= m_fBounceTopBoundary)
                    {
                        realOffsetY = m_fBounceTopBoundary - icTopPos;
                        scrollToTopEvent();
                        scrollenabled = false;
                    }
                }
                else if (touchOffsetX > 0.0f && touchOffsetY < 0.0f) // down right
                {
                    float icLeftPos = m_pInnerContainer->getLeftInParent();
                    if (icLeftPos + touchOffsetX >= m_fBounceLeftBoundary)
                    {
                        realOffsetX = m_fBounceLeftBoundary - icLeftPos;
                        scrollToLeftEvent();
                        scrollenabled = false;
                    }
                    float icTopPos = m_pInnerContainer->getTopInParent();
                    if (icTopPos + touchOffsetY <= m_fBounceTopBoundary)
                    {
                        realOffsetY = m_fBounceTopBoundary - icTopPos;
                        scrollToTopEvent();
                        scrollenabled = false;
                    }
                }
                else if (touchOffsetX == 0.0f && touchOffsetY > 0.0f) // up
                {
                    float icBottomPos = m_pInnerContainer->getBottomInParent();
                    if (icBottomPos + touchOffsetY >= m_fBounceBottomBoundary)
                    {
                        realOffsetY = m_fBounceBottomBoundary - icBottomPos;
                        scrollToBottomEvent();
                        scrollenabled = false;
                    }
                }
                else if (touchOffsetX < 0.0f && touchOffsetY == 0.0f) // left
                {
                    float icRightPos = m_pInnerContainer->getRightInParent();
                    if (icRightPos + touchOffsetX <= m_fBounceRightBoundary)
                    {
                        realOffsetX = m_fBounceRightBoundary - icRightPos;
                        scrollToRightEvent();
                        scrollenabled = false;
                    }
                }
                else if (touchOffsetX == 0.0f && touchOffsetY < 0.0f) // down
                {
                    float icTopPos = m_pInnerContainer->getTopInParent();
                    if (icTopPos + touchOffsetY <= m_fBounceTopBoundary)
                    {
                        realOffsetY = m_fBounceTopBoundary - icTopPos;
                        scrollToTopEvent();
                        scrollenabled = false;
                    }
                }
                else if (touchOffsetX > 0.0f && touchOffsetY == 0.0f) // right
                {
                    float icLeftPos = m_pInnerContainer->getLeftInParent();
                    if (icLeftPos + touchOffsetX >= m_fBounceLeftBoundary)
                    {
                        realOffsetX = m_fBounceLeftBoundary - icLeftPos;
                        scrollToLeftEvent();
                        scrollenabled = false;
                    }
                }
            }
            else
            {
                if (touchOffsetX > 0.0f && touchOffsetY > 0.0f) // up right
                {
                    float icLeftPos = m_pInnerContainer->getLeftInParent();
                    if (icLeftPos + touchOffsetX >= m_fLeftBoundary)
                    {
                        realOffsetX = m_fLeftBoundary - icLeftPos;
                        scrollToLeftEvent();
                        scrollenabled = false;
                    }
                    float icBottomPos = m_pInnerContainer->getBottomInParent();
                    if (icBottomPos + touchOffsetY >= m_fBottomBoundary)
                    {
                        realOffsetY = m_fBottomBoundary - icBottomPos;
                        scrollToBottomEvent();
                        scrollenabled = false;
                    }
                }
                else if (touchOffsetX < 0.0f && touchOffsetY > 0.0f) // up left
                {
                    float icRightPos = m_pInnerContainer->getRightInParent();
                    if (icRightPos + touchOffsetX <= m_fRightBoundary)
                    {
                        realOffsetX = m_fRightBoundary - icRightPos;
                        scrollToRightEvent();
                        scrollenabled = false;
                    }
                    float icBottomPos = m_pInnerContainer->getBottomInParent();
                    if (icBottomPos + touchOffsetY >= m_fBottomBoundary)
                    {
                        realOffsetY = m_fBottomBoundary - icBottomPos;
                        scrollToBottomEvent();
                        scrollenabled = false;
                    }
                }
                else if (touchOffsetX < 0.0f && touchOffsetY < 0.0f) // down left
                {
                    float icRightPos = m_pInnerContainer->getRightInParent();
                    if (icRightPos + touchOffsetX <= m_fRightBoundary)
                    {
                        realOffsetX = m_fRightBoundary - icRightPos;
                        scrollToRightEvent();
                        scrollenabled = false;
                    }
                    float icTopPos = m_pInnerContainer->getTopInParent();
                    if (icTopPos + touchOffsetY <= m_fTopBoundary)
                    {
                        realOffsetY = m_fTopBoundary - icTopPos;
                        scrollToTopEvent();
                        scrollenabled = false;
                    }
                }
                else if (touchOffsetX > 0.0f && touchOffsetY < 0.0f) // down right
                {
                    float icLeftPos = m_pInnerContainer->getLeftInParent();
                    if (icLeftPos + touchOffsetX >= m_fLeftBoundary)
                    {
                        realOffsetX = m_fLeftBoundary - icLeftPos;
                        scrollToLeftEvent();
                        scrollenabled = false;
                    }
                    float icTopPos = m_pInnerContainer->getTopInParent();
                    if (icTopPos + touchOffsetY <= m_fTopBoundary)
                    {
                        realOffsetY = m_fTopBoundary - icTopPos;
                        scrollToTopEvent();
                        scrollenabled = false;
                    }
                }
                else if (touchOffsetX == 0.0f && touchOffsetY > 0.0f) // up
                {
                    float icBottomPos = m_pInnerContainer->getBottomInParent();
                    if (icBottomPos + touchOffsetY >= m_fBottomBoundary)
                    {
                        realOffsetY = m_fBottomBoundary - icBottomPos;
                        scrollToBottomEvent();
                        scrollenabled = false;
                    }
                }
                else if (touchOffsetX < 0.0f && touchOffsetY == 0.0f) // left
                {
                    float icRightPos = m_pInnerContainer->getRightInParent();
                    if (icRightPos + touchOffsetX <= m_fRightBoundary)
                    {
                        realOffsetX = m_fRightBoundary - icRightPos;
                        scrollToRightEvent();
                        scrollenabled = false;
                    }
                }
                else if (touchOffsetX == 0.0f && touchOffsetY < 0.0f) // down
                {
                    float icTopPos = m_pInnerContainer->getTopInParent();
                    if (icTopPos + touchOffsetY <= m_fTopBoundary)
                    {
                        realOffsetY = m_fTopBoundary - icTopPos;
                        scrollToTopEvent();
                        scrollenabled = false;
                    }
                }
                else if (touchOffsetX > 0.0f && touchOffsetY == 0.0f) // right
                {
                    float icLeftPos = m_pInnerContainer->getLeftInParent();
                    if (icLeftPos + touchOffsetX >= m_fLeftBoundary)
                    {
                        realOffsetX = m_fLeftBoundary - icLeftPos;
                        scrollToLeftEvent();
                        scrollenabled = false;
                    }
                }
            }
            moveChildren(realOffsetX, realOffsetY);
            break;
        }
        default:
            break;
    }
    return scrollenabled;
}

void UIScrollView::scrollToBottom(float time, bool attenuated)
{
    startAutoScrollChildrenWithDestination(ccp(m_pInnerContainer->getPosition().x, 0.0f), time, attenuated);
}

void UIScrollView::scrollToTop(float time, bool attenuated)
{
    startAutoScrollChildrenWithDestination(ccp(m_pInnerContainer->getPosition().x, m_size.height - m_pInnerContainer->getSize().height), time, attenuated);
}

void UIScrollView::scrollToLeft(float time, bool attenuated)
{
    startAutoScrollChildrenWithDestination(ccp(0.0f, m_pInnerContainer->getPosition().y), time, attenuated);
}

void UIScrollView::scrollToRight(float time, bool attenuated)
{
    startAutoScrollChildrenWithDestination(ccp(m_size.width - m_pInnerContainer->getSize().width, m_pInnerContainer->getPosition().y), time, attenuated);
}

void UIScrollView::scrollToTopLeft(float time, bool attenuated)
{
    if (m_eDirection != SCROLLVIEW_DIR_BOTH)
    {
        CCLOG("Scroll diretion is not both!");
        return;
    }
    startAutoScrollChildrenWithDestination(ccp(0.0f, m_size.height - m_pInnerContainer->getSize().height), time, attenuated);
}

void UIScrollView::scrollToTopRight(float time, bool attenuated)
{
    if (m_eDirection != SCROLLVIEW_DIR_BOTH)
    {
        CCLOG("Scroll diretion is not both!");
        return;
    }
    startAutoScrollChildrenWithDestination(ccp(m_size.width - m_pInnerContainer->getSize().width, m_size.height - m_pInnerContainer->getSize().height), time, attenuated);
}

void UIScrollView::scrollToBottomLeft(float time, bool attenuated)
{
    if (m_eDirection != SCROLLVIEW_DIR_BOTH)
    {
        CCLOG("Scroll diretion is not both!");
        return;
    }
    startAutoScrollChildrenWithDestination(CCPointZero, time, attenuated);
}

void UIScrollView::scrollToBottomRight(float time, bool attenuated)
{
    if (m_eDirection != SCROLLVIEW_DIR_BOTH)
    {
        CCLOG("Scroll diretion is not both!");
        return;
    }
    startAutoScrollChildrenWithDestination(ccp(m_size.width - m_pInnerContainer->getSize().width, 0.0f), time, attenuated);
}

void UIScrollView::scrollToPercentVertical(float percent, float time, bool attenuated)
{
    float minY = m_size.height - m_pInnerContainer->getSize().height;
    float h = - minY;
    startAutoScrollChildrenWithDestination(ccp(m_pInnerContainer->getPosition().x, minY + percent * h / 100.0f), time, attenuated);
}

void UIScrollView::scrollToPercentHorizontal(float percent, float time, bool attenuated)
{
    float w = m_pInnerContainer->getSize().width - m_size.width;
    startAutoScrollChildrenWithDestination(ccp(-(percent * w / 100.0f), m_pInnerContainer->getPosition().y), time, attenuated);
}

void UIScrollView::scrollToPercentBothDirection(const CCPoint& percent, float time, bool attenuated)
{
    if (m_eDirection != SCROLLVIEW_DIR_BOTH)
    {
        return;
    }
    float minY = m_size.height - m_pInnerContainer->getSize().height;
    float h = - minY;
    float w = m_pInnerContainer->getSize().width - m_size.width;
    startAutoScrollChildrenWithDestination(ccp(-(percent.x * w / 100.0f), minY + percent.y * h / 100.0f), time, attenuated);
}

void UIScrollView::jumpToBottom()
{
    jumpToDestination(ccp(m_pInnerContainer->getPosition().x, 0.0f));
}

void UIScrollView::jumpToTop()
{
    jumpToDestination(ccp(m_pInnerContainer->getPosition().x, m_size.height - m_pInnerContainer->getSize().height));
}

void UIScrollView::jumpToLeft()
{
    jumpToDestination(ccp(0.0f, m_pInnerContainer->getPosition().y));
}

void UIScrollView::jumpToRight()
{
    jumpToDestination(ccp(m_size.width - m_pInnerContainer->getSize().width, m_pInnerContainer->getPosition().y));
}

void UIScrollView::jumpToTopLeft()
{
    if (m_eDirection != SCROLLVIEW_DIR_BOTH)
    {
        CCLOG("Scroll diretion is not both!");
        return;
    }
    jumpToDestination(ccp(0.0f, m_size.height - m_pInnerContainer->getSize().height));
}

void UIScrollView::jumpToTopRight()
{
    if (m_eDirection != SCROLLVIEW_DIR_BOTH)
    {
        CCLOG("Scroll diretion is not both!");
        return;
    }
    jumpToDestination(ccp(m_size.width - m_pInnerContainer->getSize().width, m_size.height - m_pInnerContainer->getSize().height));
}

void UIScrollView::jumpToBottomLeft()
{
    if (m_eDirection != SCROLLVIEW_DIR_BOTH)
    {
        CCLOG("Scroll diretion is not both!");
        return;
    }
    jumpToDestination(CCPointZero);
}

void UIScrollView::jumpToBottomRight()
{
    if (m_eDirection != SCROLLVIEW_DIR_BOTH)
    {
        CCLOG("Scroll diretion is not both!");
        return;
    }
    jumpToDestination(ccp(m_size.width - m_pInnerContainer->getSize().width, 0.0f));
}

void UIScrollView::jumpToPercentVertical(float percent)
{
    float minY = m_size.height - m_pInnerContainer->getSize().height;
    float h = - minY;
    jumpToDestination(ccp(m_pInnerContainer->getPosition().x, minY + percent * h / 100.0f));
}

void UIScrollView::jumpToPercentHorizontal(float percent)
{
    float w = m_pInnerContainer->getSize().width - m_size.width;
    jumpToDestination(ccp(-(percent * w / 100.0f), m_pInnerContainer->getPosition().y));
}

void UIScrollView::jumpToPercentBothDirection(const CCPoint& percent)
{
    if (m_eDirection != SCROLLVIEW_DIR_BOTH)
    {
        return;
    }
    float minY = m_size.height - m_pInnerContainer->getSize().height;
    float h = - minY;
    float w = m_pInnerContainer->getSize().width - m_size.width;
    jumpToDestination(ccp(-(percent.x * w / 100.0f), minY + percent.y * h / 100.0f));
}

void UIScrollView::startRecordSlidAction()
{
    if (m_bAutoScroll)
    {
        stopAutoScrollChildren();
    }
    if (m_bBouncing)
    {
        stopBounceChildren();
    }
    m_fSlidTime = 0.0f;
}

void UIScrollView::endRecordSlidAction()
{
    if (!checkNeedBounce() && m_bInertiaScrollEnabled)
    {
        if (m_fSlidTime <= 0.016f)
        {
            return;
        }
        float totalDis = 0.0f;
        CCPoint dir;
        switch (m_eDirection)
        {
            case SCROLLVIEW_DIR_VERTICAL:
                totalDis = m_touchEndedPoint.y - m_touchBeganPoint.y;
                if (totalDis < 0.0f)
                {
                    dir = SCROLLDIR_DOWN;
                }
                else
                {
                    dir = SCROLLDIR_UP;
                }
                break;
            case SCROLLVIEW_DIR_HORIZONTAL:
                totalDis = m_touchEndedPoint.x - m_touchBeganPoint.x;
                if (totalDis < 0.0f)
                {
                    dir = SCROLLDIR_LEFT;
                }
                else
                {
                    dir = SCROLLDIR_RIGHT;
                }
                break;
            case SCROLLVIEW_DIR_BOTH:
            {
                CCPoint subVector = ccpSub(m_touchEndedPoint, m_touchBeganPoint);
                totalDis = subVector.getLength();
                dir = ccpNormalize(subVector);
                break;
            }
            default:
                break;
        }
        float orSpeed = MIN(fabs(totalDis)/(m_fSlidTime), AUTOSCROLLMAXSPEED);
        startAutoScrollChildrenWithOriginalSpeed(dir, orSpeed, true, -1000);
        m_fSlidTime = 0.0f;
    }
}

void UIScrollView::handlePressLogic(const CCPoint &touchPoint)
{        
    m_touchBeganPoint = m_pRenderer->convertToNodeSpace(touchPoint);
    m_touchMovingPoint = m_touchBeganPoint;    
    startRecordSlidAction();
    m_bBePressed = true;
}

void UIScrollView::handleMoveLogic(const CCPoint &touchPoint)
{
    m_touchMovedPoint = m_pRenderer->convertToNodeSpace(touchPoint);
    CCPoint delta = ccpSub(m_touchMovedPoint, m_touchMovingPoint);
    m_touchMovingPoint = m_touchMovedPoint;
    switch (m_eDirection)
    {
        case SCROLLVIEW_DIR_VERTICAL: // vertical
        {
            scrollChildren(0.0f, delta.y);
            break;
        }
        case SCROLLVIEW_DIR_HORIZONTAL: // horizontal
        {
            scrollChildren(delta.x, 0.0f);
            break;
        }
        case SCROLLVIEW_DIR_BOTH: // both
        {
            scrollChildren(delta.x, delta.y);
            break;
        }
        default:
            break;
    }
}

void UIScrollView::handleReleaseLogic(const CCPoint &touchPoint)
{
    m_touchEndedPoint = m_pRenderer->convertToNodeSpace(touchPoint);
    endRecordSlidAction();
    m_bBePressed = false;
}    

bool UIScrollView::onTouchBegan(const CCPoint &touchPoint)
{
    bool pass = UILayout::onTouchBegan(touchPoint);
    handlePressLogic(touchPoint);
    return pass;
}

void UIScrollView::onTouchMoved(const CCPoint &touchPoint)
{
    UILayout::onTouchMoved(touchPoint);
    handleMoveLogic(touchPoint);
}

void UIScrollView::onTouchEnded(const CCPoint &touchPoint)
{
    UILayout::onTouchEnded(touchPoint);
    handleReleaseLogic(touchPoint);
}

void UIScrollView::onTouchCancelled(const CCPoint &touchPoint)
{
    UILayout::onTouchCancelled(touchPoint);
    handleReleaseLogic(touchPoint);
}

void UIScrollView::onTouchLongClicked(const CCPoint &touchPoint)
{
    
}

void UIScrollView::update(float dt)
{
    if (m_bAutoScroll)
    {
        autoScrollChildren(dt);
    }
    if (m_bBouncing)
    {
        bounceChildren(dt);
    }
    recordSlidTime(dt);
}

void UIScrollView::recordSlidTime(float dt)
{
    if (m_bBePressed)
    {
        m_fSlidTime += dt;
    }
}

void UIScrollView::interceptTouchEvent(int handleState, UIWidget *sender, const CCPoint &touchPoint)
{
    switch (handleState)
    {
        case 0:
            handlePressLogic(touchPoint);
            break;
            
        case 1:
        {
            float offset = ccpSub(sender->getTouchStartPos(), touchPoint).getLength();
            if (offset > m_fChildFocusCancelOffset)
            {
                sender->setFocused(false);
                handleMoveLogic(touchPoint);
            }
        }
            break;
            
        case 2:
            handleReleaseLogic(touchPoint);
            break;
            
        case 3:
            handleReleaseLogic(touchPoint);
            break;
    }
}

void UIScrollView::checkChildInfo(int handleState,UIWidget* sender,const CCPoint &touchPoint)
{
    interceptTouchEvent(handleState, sender, touchPoint);
}

void UIScrollView::scrollToTopEvent()
{
    /*******Compatible*******/
    if (m_pScrollToTopListener && m_pfnScrollToTopSelector)
    {
        (m_pScrollToTopListener->*m_pfnScrollToTopSelector)(this);
    }
    /************************/
    if (m_pScrollViewEventListener && m_pfnScrollViewEventSelector)
    {
        (m_pScrollViewEventListener->*m_pfnScrollViewEventSelector)(this, SCROLLVIEW_EVENT_SCROLL_TO_TOP);
    }
}

void UIScrollView::scrollToBottomEvent()
{
    /*******Compatible*******/
    if (m_pScrollToBottomListener && m_pfnScrollToBottomSelector)
    {
        (m_pScrollToBottomListener->*m_pfnScrollToBottomSelector)(this);
    }
    /************************/
    if (m_pScrollViewEventListener && m_pfnScrollViewEventSelector)
    {
        (m_pScrollViewEventListener->*m_pfnScrollViewEventSelector)(this, SCROLLVIEW_EVENT_SCROLL_TO_BOTTOM);
    }
}

void UIScrollView::scrollToLeftEvent()
{
    /*******Compatible*******/
    if (m_pScrollToLeftListener && m_pfnScrollToLeftSelector)
    {
        (m_pScrollToLeftListener->*m_pfnScrollToLeftSelector)(this);
    }
    /************************/
    if (m_pScrollViewEventListener && m_pfnScrollViewEventSelector)
    {
        (m_pScrollViewEventListener->*m_pfnScrollViewEventSelector)(this, SCROLLVIEW_EVENT_SCROLL_TO_LEFT);
    }
}

void UIScrollView::scrollToRightEvent()
{
    /*******Compatible*******/
    if (m_pScrollToRightListener && m_pfnScrollToRightSelector)
    {
        (m_pScrollToRightListener->*m_pfnScrollToRightSelector)(this);
    }
    /************************/
    if (m_pScrollViewEventListener && m_pfnScrollViewEventSelector)
    {
        (m_pScrollViewEventListener->*m_pfnScrollViewEventSelector)(this, SCROLLVIEW_EVENT_SCROLL_TO_RIGHT);
    }
}

void UIScrollView::scrollingEvent()
{
    if (m_pScrollViewEventListener && m_pfnScrollViewEventSelector)
    {
        (m_pScrollViewEventListener->*m_pfnScrollViewEventSelector)(this, SCROLLVIEW_EVENT_SCROLLING);
    }
}

void UIScrollView::bounceTopEvent()
{
    if (m_pScrollViewEventListener && m_pfnScrollViewEventSelector)
    {
        (m_pScrollViewEventListener->*m_pfnScrollViewEventSelector)(this, SCROLLVIEW_EVENT_BOUNCE_TOP);
    }
}

void UIScrollView::bounceBottomEvent()
{
    if (m_pScrollViewEventListener && m_pfnScrollViewEventSelector)
    {
        (m_pScrollViewEventListener->*m_pfnScrollViewEventSelector)(this, SCROLLVIEW_EVENT_BOUNCE_BOTTOM);
    }
}

void UIScrollView::bounceLeftEvent()
{
    if (m_pScrollViewEventListener && m_pfnScrollViewEventSelector)
    {
        (m_pScrollViewEventListener->*m_pfnScrollViewEventSelector)(this, SCROLLVIEW_EVENT_BOUNCE_LEFT);
    }
}

void UIScrollView::bounceRightEvent()
{
    if (m_pScrollViewEventListener && m_pfnScrollViewEventSelector)
    {
        (m_pScrollViewEventListener->*m_pfnScrollViewEventSelector)(this, SCROLLVIEW_EVENT_BOUNCE_RIGHT);
    }
}

void UIScrollView::addEventListenerScrollView(CCObject *target, SEL_ScrollViewEvent selector)
{
    m_pScrollViewEventListener = target;
    m_pfnScrollViewEventSelector = selector;
}

/*******Compatible*******/
void UIScrollView::addScrollToTopEvent(CCObject *target, SEL_ScrollToTopEvent selector)
{
    m_pScrollToTopListener = target;
    m_pfnScrollToTopSelector = selector;
}

void UIScrollView::addScrollToBottomEvent(CCObject *target, SEL_ScrollToBottomEvent selector)
{
    m_pScrollToBottomListener = target;
    m_pfnScrollToBottomSelector = selector;
}

void UIScrollView::addScrollToLeftEvent(CCObject *target, SEL_ScrollToLeftEvent selector)
{
    m_pScrollToLeftListener = target;
    m_pfnScrollToLeftSelector = selector;
}

void UIScrollView::addScrollToRightEvent(CCObject *target, SEL_ScrollToRightEvent selector)
{
    m_pScrollToRightListener = target;
    m_pfnScrollToRightSelector = selector;
}
/************************/

void UIScrollView::setDirection(SCROLLVIEW_DIR dir)
{
    m_eDirection = dir;
}

SCROLLVIEW_DIR UIScrollView::getDirection()
{
    return m_eDirection;
}

void UIScrollView::setBounceEnabled(bool enabled)
{
    m_bBounceEnabled = enabled;
}

bool UIScrollView::isBounceEnabled() const
{
    return m_bBounceEnabled;
}

void UIScrollView::setInertiaScrollEnabled(bool enabled)
{
    m_bInertiaScrollEnabled = enabled;
}

bool UIScrollView::isInertiaScrollEnabled() const
{
    return m_bInertiaScrollEnabled;
}

UILayout* UIScrollView::getInnerContainer()
{
    return m_pInnerContainer;
}

void UIScrollView::setLayoutType(LayoutType type)
{
    m_pInnerContainer->setLayoutType(type);
}

LayoutType UIScrollView::getLayoutType() const
{
    return m_pInnerContainer->getLayoutType();
}

void UIScrollView::doLayout()
{
    m_pInnerContainer->doLayout();
}

const char* UIScrollView::getDescription() const
{
    return "ScrollView";
}

UIWidget* UIScrollView::createCloneInstance()
{
    return UIScrollView::create();
}

void UIScrollView::copyClonedWidgetChildren(UIWidget* model)
{
    UILayout::copyClonedWidgetChildren(model);
}

void UIScrollView::copySpecialProperties(UIWidget *widget)
{
    UIScrollView* scrollView = dynamic_cast<UIScrollView*>(widget);
    if (scrollView)
    {
        UILayout::copySpecialProperties(widget);
        setInnerContainerSize(scrollView->getInnerContainerSize());
        setDirection(scrollView->m_eDirection);
        setBounceEnabled(scrollView->m_bBounceEnabled);
        setInertiaScrollEnabled(scrollView->m_bInertiaScrollEnabled);
    }
}

NS_CC_EXT_END