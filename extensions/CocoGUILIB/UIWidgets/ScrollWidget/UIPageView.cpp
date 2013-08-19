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
m_pLeftChild(NULL),
m_pRightChild(NULL),
m_fLeftBoundary(0.0f),
m_fRightBoundary(0.0f),
m_bIsAutoScrolling(false),
m_fAutoScrollDistance(0.0f),
m_fAutoScrollSpeed(0.0f),
m_nAutoScrollDir(0),
m_fChildFocusCancelOffset(5.0f),
/* gui mark */
m_pPageTurningListener(NULL),
m_pfnPageTurningSelector(NULL)
/**/
{
    m_WidgetName = WIDGET_PAGEVIEW;
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
        return widget;
    }
    CC_SAFE_DELETE(widget);
    return NULL;
}

bool UIPageView::init()
{
    if (UIPanel::init())
    {
        m_pages = CCArray::create();
        m_pages->retain();
        setClippingEnable(true);
        setUpdateEnable(true);
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
//                pageIdx = pageCount;
            }
            UIPanel* newPage = createPage();
            newPage->addChild(widget);
            addPage(newPage);
        }
    }
    else
    {
        UIContainerWidget * page = dynamic_cast<UIContainerWidget*>(m_pages->objectAtIndex(pageIdx));
        if (page)
        {
            page->addChild(widget);
        }
    }
    
}

UIPanel* UIPageView::createPage()
{
    UIPanel* newPage = UIPanel::create();
    newPage->setSize(getContentSize());
    return newPage;
}

void UIPageView::addPage(UIContainerWidget* page)
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
    CCSize pSize = page->getContentSize();
    CCSize pvSize = getContentSize();
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

void UIPageView::insertPage(UIContainerWidget* page, int idx)
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
        CCSize pSize = page->getContentSize();
        CCSize pvSize = getContentSize();
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
            behindPage->setPosition(ccp(formerPos.x+getWidth(), 0));
        }
        updateBoundaryPages();
    }
}

void UIPageView::removePage(UIContainerWidget* page, bool cleanup)
{
    if (!page)
    {
        return;
    }
    removeChild(page, cleanup);
    updateChildrenPosition();
    updateBoundaryPages();
}

void UIPageView::removePageAtIndex(int index, bool cleanup)
{
    if (index < 0 || index >= m_pages->count())
    {
        return;
    }
    UIContainerWidget* page = dynamic_cast<UIContainerWidget*>(m_pages->objectAtIndex(index));
    if (page)
    {
        removePage(page, cleanup);
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
    return (getWidth()*(idx-m_nCurPageIdx));
}

bool UIPageView::addChild(UIWidget* widget)
{
    return UIPanel::addChild(widget);
}

bool UIPageView::removeChild(UIWidget* widget, bool cleanup)
{
    if (m_pages->containsObject(widget))
    {
        m_pages->removeObject(widget);
        return UIPanel::removeChild(widget, cleanup);
    }
    return false;
}

void UIPageView::setSize(const CCSize &size)
{
    UIPanel::setSize(size);
    m_fRightBoundary = getWidth();
    updateChildrenSize();
    updateChildrenPosition();
}

void UIPageView::updateChildrenSize()
{
    if (!m_pages)
    {
        return;
    }
    
    CCSize selfSize = getContentSize();
    for (int i=0; i<m_pages->count(); i++)
    {
        UIContainerWidget* page = dynamic_cast<UIContainerWidget*>(m_pages->objectAtIndex(i));
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
    float pageWidth = getWidth();
    ccArray* arrayPages = m_pages->data;
    for (int i=0; i<pageCount; i++)
    {
        UIContainerWidget* page = dynamic_cast<UIContainerWidget*>(arrayPages->arr[i]);
        page->setPosition(ccp((i-m_nCurPageIdx)*pageWidth, 0));
    }
}

void UIPageView::removeAllChildrenAndCleanUp(bool cleanup)
{
    m_pages->removeAllObjects();
    UIPanel::removeAllChildrenAndCleanUp(cleanup);
}

void UIPageView::scrollToPage(int idx)
{
    if (idx < 0 || idx >= m_pages->count())
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
                    /* gui mark */
                    pageTurningEvent();
                    /**/
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
                    /* gui mark */
                    pageTurningEvent();
                    /**/
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

void UIPageView::onTouchBegan(const CCPoint &touchPoint)
{
    UIPanel::onTouchBegan(touchPoint);
    handlePressLogic(touchPoint);
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
    if (!pointAtSelfBody(touchPoint))
    {
        setFocus(false);
        onTouchEnded(touchPoint);
    }
}

void UIPageView::onTouchEnded(const CCPoint &touchPoint)
{
    UIPanel::onTouchEnded(touchPoint);
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
        child->setVisible(checkChildVisibleInParent(this, child));
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
            if (m_pRightChild->getRelativeRightPos() + touchOffset <= m_fRightBoundary)
            {
                realOffset = m_fRightBoundary - m_pRightChild->getRelativeRightPos();
                movePages(realOffset);
                return false;
            }
            break;
            
        case PAGEVIEW_TOUCHRIGHT: // right
            if (m_pLeftChild->getRelativeLeftPos() + touchOffset >= m_fLeftBoundary)
            {
                realOffset = m_fLeftBoundary - m_pLeftChild->getRelativeLeftPos();
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
    UIPanel::onTouchCancelled(touchPoint);
}

void UIPageView::handlePressLogic(const CCPoint &touchPoint)
{
    CCPoint nsp = m_pRender->convertToNodeSpace(touchPoint);
    m_fTouchMoveStartLocation = nsp.x;
    m_fTouchStartLocation = nsp.x;
//    startRecordSlidAction();
}

void UIPageView::handleMoveLogic(const CCPoint &touchPoint)
{
    CCPoint nsp = m_pRender->convertToNodeSpace(touchPoint);
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
        float pageWidth = getWidth();
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
//    CCLOG("cur page idx == %d",m_nCurPageIdx);
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
                sender->setFocus(false);
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

/* gui mark */
void UIPageView::pageTurningEvent()
{
    if (m_pPageTurningListener && m_pfnPageTurningSelector)
    {
        (m_pPageTurningListener->*m_pfnPageTurningSelector)(this);
    }
}

void UIPageView::addPageTurningEvent(CCObject *target, SEL_PageViewPageTurningEvent selector)
{
    m_pPageTurningListener = target;
    m_pfnPageTurningSelector = selector;
}

int UIPageView::getPage()
{
    return m_nCurPageIdx;
}
/**/

NS_CC_EXT_END