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

#include "UIPageView.h"

NS_CC_EXT_BEGIN

UIPageView::UIPageView():
m_nCurPageIdx(0),
m_pages(NULL),
m_touchMoveDir(PAGEVIEW_TOUCHLEFT),
m_fTouchStartLocation(0.0f),
m_fTouchEndLocation(0.0f),
m_fTouchMoveStartLocation(0.0f),
movePagePoint(CCPointZero),
m_pLeftChild(NULL),
m_pRightChild(NULL),
m_fLeftBoundary(0.0f),
m_fRightBoundary(0.0f),
m_bIsAutoScrolling(false),
m_fAutoScrollDistance(0.0f),
m_fAutoScrollSpeed(0.0f),
m_nAutoScrollDir(0),
m_fChildFocusCancelOffset(5.0f),
m_pEventListener(NULL),
m_pfnEventSelector(NULL),
/*compatible*/
m_pPageTurningListener(NULL),
m_pfnPageTurningSelector(NULL)
    /************/
{
}

UIPageView::~UIPageView()
{
    m_pages->release();
}

UIPageView* UIPageView::create()
{
    UIPageView* widget = new UIPageView();
    if (widget && widget->init())
    {
        widget->autorelease();
        return widget;
    }
    CC_SAFE_DELETE(widget);
    return NULL;
}

bool UIPageView::init()
{
    if (Layout::init())
    {
        m_pages = CCArray::create();
        m_pages->retain();
        setClippingEnabled(true);
        setUpdateEnabled(true);
        return true;
    }
    return false;
}

void UIPageView::addWidgetToPage(UIWidget *widget, int pageIdx, bool forceCreate)
{
    if (!widget)
    {
        return;
    }
    int pageCount = m_pages->count();
    if (pageIdx < 0 || pageIdx >= pageCount)
    {
        if (forceCreate)
        {
            if (pageIdx > pageCount)
            {
                CCLOG("pageIdx is %d, it will be added as page id [%d]",pageIdx,pageCount);
            }
            Layout* newPage = createPage();
            newPage->addChild(widget);
            addPage(newPage);
        }
    }
    else
    {
        Layout * page = dynamic_cast<Layout*>(m_pages->objectAtIndex(pageIdx));
        if (page)
        {
            page->addChild(widget);
        }
    }
    
}

Layout* UIPageView::createPage()
{
    Layout* newPage = Layout::create();
    newPage->setSize(getSize());
    return newPage;
}

void UIPageView::addPage(Layout* page)
{
    if (!page)
    {
        return;
    }
    if (page->getWidgetType() != WidgetTypeContainer)
    {
        return;
    }
    if (m_pages->containsObject(page))
    {
        return;
    }
    CCSize pSize = page->getSize();
    CCSize pvSize = getSize();
    if (!pSize.equals(pvSize))
    {
        CCLOG("page size does not match pageview size, it will be force sized!");
        page->setSize(pvSize);
    }
    page->setPosition(ccp(getPositionXByIndex(m_pages->count()), 0));
    m_pages->addObject(page);
    addChild(page);
    updateBoundaryPages();
}

void UIPageView::insertPage(Layout* page, int idx)
{
    if (idx < 0)
    {
        return;
    }
    if (!page)
    {
        return;
    }
    if (page->getWidgetType() != WidgetTypeContainer)
    {
        return;
    }
    if (m_pages->containsObject(page))
    {
        return;
    }
    
    int pageCount = m_pages->count();
    if (idx >= pageCount)
    {
        addPage(page);
    }
    else
    {
        m_pages->insertObject(page, idx);
        page->setPosition(ccp(getPositionXByIndex(idx), 0));
        addChild(page);
        CCSize pSize = page->getSize();
        CCSize pvSize = getSize();
        if (!pSize.equals(pvSize))
        {
            CCLOG("page size does not match pageview size, it will be force sized!");
            page->setSize(pvSize);
        }
        ccArray* arrayPages = m_pages->data;
        int length = arrayPages->num;
        for (int i=(idx+1); i<length; i++) {
            UIWidget* behindPage = dynamic_cast<UIWidget*>(arrayPages->arr[i]);
            CCPoint formerPos = behindPage->getPosition();
            behindPage->setPosition(ccp(formerPos.x+getSize().width, 0));
        }
        updateBoundaryPages();
    }
}

void UIPageView::removePage(Layout* page)
{
    if (!page)
    {
        return;
    }
    removeChild(page);
    updateChildrenPosition();
    updateBoundaryPages();
}

void UIPageView::removePageAtIndex(int index)
{
    if (index < 0 || index >= (int)(m_pages->count()))
    {
        return;
    }
    Layout* page = dynamic_cast<Layout*>(m_pages->objectAtIndex(index));
    if (page)
    {
        removePage(page);
    }
}

void UIPageView::updateBoundaryPages()
{
    if (m_pages->count() <= 0)
    {
        m_pLeftChild = NULL;
        m_pRightChild = NULL;
    }
    m_pLeftChild = dynamic_cast<UIWidget*>(m_pages->objectAtIndex(0));
    m_pRightChild = dynamic_cast<UIWidget*>(m_pages->lastObject());
}

float UIPageView::getPositionXByIndex(int idx)
{
    return (getSize().width*(idx-m_nCurPageIdx));
}

bool UIPageView::addChild(UIWidget* widget)
{
    return Layout::addChild(widget);
}

bool UIPageView::removeChild(UIWidget* widget)
{
    if (m_pages->containsObject(widget))
    {
        m_pages->removeObject(widget);
        return Layout::removeChild(widget);
    }
    return false;
}

void UIPageView::onSizeChanged()
{
    Layout::onSizeChanged();
    m_fRightBoundary = getSize().width;
    updateChildrenSize();
    updateChildrenPosition();
}

void UIPageView::updateChildrenSize()
{
    if (!m_pages)
    {
        return;
    }
    
    CCSize selfSize = getSize();
    for (unsigned int i=0; i<m_pages->count(); i++)
    {
        Layout* page = dynamic_cast<Layout*>(m_pages->objectAtIndex(i));
        page->setSize(selfSize);
    }
}

void UIPageView::updateChildrenPosition()
{
    if (!m_pages)
    {
        return;
    }
    
    int pageCount = m_pages->data->num;
    if (pageCount <= 0)
    {
        m_nCurPageIdx = 0;
        return;
    }
    if (m_nCurPageIdx >= pageCount)
    {
        m_nCurPageIdx = pageCount-1;
    }
    float pageWidth = getSize().width;
    ccArray* arrayPages = m_pages->data;
    for (int i=0; i<pageCount; i++)
    {
        Layout* page = dynamic_cast<Layout*>(arrayPages->arr[i]);
        page->setPosition(ccp((i-m_nCurPageIdx)*pageWidth, 0));
    }
}

void UIPageView::removeAllChildren()
{
    m_pages->removeAllObjects();
    Layout::removeAllChildren();
}

void UIPageView::scrollToPage(int idx)
{
    if (idx < 0 || idx >= (int)(m_pages->count()))
    {
        return;
    }
    m_nCurPageIdx = idx;
    UIWidget* curPage = dynamic_cast<UIWidget*>(m_pages->objectAtIndex(idx));
    m_fAutoScrollDistance = -(curPage->getPosition().x);
    m_fAutoScrollSpeed = fabs(m_fAutoScrollDistance)/0.2f;
    m_nAutoScrollDir = m_fAutoScrollDistance > 0 ? 1 : 0;
    m_bIsAutoScrolling = true;
}

void UIPageView::update(float dt)
{
    if (m_bIsAutoScrolling)
    {
        switch (m_nAutoScrollDir)
        {
            case 0:
            {
                float step = m_fAutoScrollSpeed*dt;
                if (m_fAutoScrollDistance + step >= 0.0f)
                {
                    step = -m_fAutoScrollDistance;
                    m_fAutoScrollDistance = 0.0f;
                    m_bIsAutoScrolling = false;
                    pageTurningEvent();
                }
                else
                {
                    m_fAutoScrollDistance += step;
                }
                scrollPages(-step);
                break;
            }
                break;
            case 1:
            {
                float step = m_fAutoScrollSpeed*dt;
                if (m_fAutoScrollDistance - step <= 0.0f)
                {
                    step = m_fAutoScrollDistance;
                    m_fAutoScrollDistance = 0.0f;
                    m_bIsAutoScrolling = false;
                    pageTurningEvent();
                }
                else
                {
                    m_fAutoScrollDistance -= step;
                }
                scrollPages(step);
                break;
            }
            default:
                break;
        }
    }
}

bool UIPageView::onTouchBegan(const CCPoint &touchPoint)
{
    bool pass = Layout::onTouchBegan(touchPoint);
    handlePressLogic(touchPoint);
    return pass;
}

void UIPageView::onTouchMoved(const CCPoint &touchPoint)
{
    m_touchMovePos.x = touchPoint.x;
    m_touchMovePos.y = touchPoint.y;
    handleMoveLogic(touchPoint);
    if (m_pWidgetParent)
    {
        m_pWidgetParent->checkChildInfo(1,this,touchPoint);
    }
    moveEvent();
    if (!hitTest(touchPoint))
    {
        setFocused(false);
        onTouchEnded(touchPoint);
    }
}

void UIPageView::onTouchEnded(const CCPoint &touchPoint)
{
    Layout::onTouchEnded(touchPoint);
    handleReleaseLogic(touchPoint);
}

void UIPageView::movePages(float offset)
{
    ccArray* arrayPages = m_pages->data;
    int length = arrayPages->num;
    for (int i = 0; i < length; i++)
    {
        UIWidget* child = (UIWidget*)(arrayPages->arr[i]);
        movePagePoint.x = child->getPosition().x + offset;
        movePagePoint.y = child->getPosition().y;
        child->setPosition(movePagePoint);
    }
}

bool UIPageView::scrollPages(float touchOffset)
{
    if (m_pages->count() <= 0)
    {
        return false;
    }
    
    if (!m_pLeftChild || !m_pRightChild)
    {
        return false;
    }
    
    float realOffset = touchOffset;
    
    switch (m_touchMoveDir)
    {
        case PAGEVIEW_TOUCHLEFT: // left
            if (m_pRightChild->getRightInParent() + touchOffset <= m_fRightBoundary)
            {
                realOffset = m_fRightBoundary - m_pRightChild->getRightInParent();
                movePages(realOffset);
                return false;
            }
            break;
            
        case PAGEVIEW_TOUCHRIGHT: // right
            if (m_pLeftChild->getLeftInParent() + touchOffset >= m_fLeftBoundary)
            {
                realOffset = m_fLeftBoundary - m_pLeftChild->getLeftInParent();
                movePages(realOffset);
                return false;
            }
            break;
        default:
            break;
    }
    
    movePages(realOffset);
    return true;
}

void UIPageView::onTouchCancelled(const CCPoint &touchPoint)
{
    Layout::onTouchCancelled(touchPoint);
}

void UIPageView::handlePressLogic(const CCPoint &touchPoint)
{
    CCPoint nsp = m_pRenderer->convertToNodeSpace(touchPoint);
    m_fTouchMoveStartLocation = nsp.x;
    m_fTouchStartLocation = nsp.x;
}

void UIPageView::handleMoveLogic(const CCPoint &touchPoint)
{
    CCPoint nsp = m_pRenderer->convertToNodeSpace(touchPoint);
    float offset = 0.0;
    float moveX = nsp.x;
    offset = moveX - m_fTouchMoveStartLocation;
    m_fTouchMoveStartLocation = moveX;
    if (offset < 0)
    {
        m_touchMoveDir = PAGEVIEW_TOUCHLEFT;
    }
    else if (offset > 0)
    {
        m_touchMoveDir = PAGEVIEW_TOUCHRIGHT;
    }
    scrollPages(offset);
}

void UIPageView::handleReleaseLogic(const CCPoint &touchPoint)
{
    UIWidget* curPage = dynamic_cast<UIWidget*>(m_pages->objectAtIndex(m_nCurPageIdx));
    if (curPage)
    {
        CCPoint curPagePos = curPage->getPosition();
        int pageCount = m_pages->count();
        float curPageLocation = curPagePos.x;
        float pageWidth = getSize().width;
        float boundary = pageWidth/2.0f;
        if (curPageLocation <= -boundary)
        {
            if (m_nCurPageIdx >= pageCount-1)
            {
                scrollPages(-curPageLocation);
            }
            else
            {
                scrollToPage(m_nCurPageIdx+1);
            }
        }
        else if (curPageLocation >= boundary)
        {
            if (m_nCurPageIdx <= 0)
            {
                scrollPages(-curPageLocation);
            }
            else
            {
                scrollToPage(m_nCurPageIdx-1);
            }
        }
        else
        {
            scrollToPage(m_nCurPageIdx);
        }
    }
}

void UIPageView::checkChildInfo(int handleState,UIWidget* sender, const CCPoint &touchPoint)
{
    interceptTouchEvent(handleState, sender, touchPoint);
}

void UIPageView::interceptTouchEvent(int handleState, UIWidget *sender, const CCPoint &touchPoint)
{
    switch (handleState)
    {
        case 0:
            handlePressLogic(touchPoint);
            break;
        case 1:
        {
            float offset = 0;
            offset = fabs(sender->getTouchStartPos().x - touchPoint.x);
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
            break;
    }
}

void UIPageView::pageTurningEvent()
{
    /*Compatible*/
    if (m_pPageTurningListener && m_pfnPageTurningSelector)
    {
        (m_pPageTurningListener->*m_pfnPageTurningSelector)(this);
    }
    /************/
    if (m_pEventListener && m_pfnEventSelector)
    {
        (m_pEventListener->*m_pfnEventSelector)(this, PAGEVIEW_EVENT_TURNING);
    }
}

void UIPageView::addEventListener(CCObject *target, SEL_PageViewEvent selector)
{
    m_pEventListener = target;
    m_pfnEventSelector = selector;
}

/*Compatible*/
void UIPageView::addPageTurningEvent(CCObject *target, SEL_PageViewPageTurningEvent selector)
{
    m_pPageTurningListener = target;
    m_pfnPageTurningSelector = selector;
}
/************/

int UIPageView::getCurPageIndex() const
{
    return m_nCurPageIdx;
}

const char* UIPageView::getDescription() const
{
    return "PageView";
}

NS_CC_EXT_END