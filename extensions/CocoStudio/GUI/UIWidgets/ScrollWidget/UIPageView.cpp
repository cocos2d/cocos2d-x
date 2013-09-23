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
_curPageIdx(0),
_pages(NULL),
_touchMoveDir(PAGEVIEW_TOUCHLEFT),
_touchStartLocation(0.0f),
_touchEndLocation(0.0f),
_touchMoveStartLocation(0.0f),
_movePagePoint(Point::ZERO),
_leftChild(NULL),
_rightChild(NULL),
_leftBoundary(0.0f),
_rightBoundary(0.0f),
_isAutoScrolling(false),
_autoScrollDistance(0.0f),
_autoScrollSpeed(0.0f),
_autoScrollDir(0),
_childFocusCancelOffset(5.0f),
_eventListener(NULL),
_eventSelector(NULL)
{
}

UIPageView::~UIPageView()
{
    _pages->release();
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
        _pages = CCArray::create();
        _pages->retain();
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
    int pageCount = _pages->count();
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
        Layout * page = dynamic_cast<Layout*>(_pages->getObjectAtIndex(pageIdx));
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
    if (_pages->containsObject(page))
    {
        return;
    }
    Size pSize = page->getSize();
    Size pvSize = getSize();
    if (!pSize.equals(pvSize))
    {
        CCLOG("page size does not match pageview size, it will be force sized!");
        page->setSize(pvSize);
    }
    page->setPosition(Point(getPositionXByIndex(_pages->count()), 0));
    _pages->addObject(page);
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
    if (_pages->containsObject(page))
    {
        return;
    }
    
    int pageCount = _pages->count();
    if (idx >= pageCount)
    {
        addPage(page);
    }
    else
    {
        _pages->insertObject(page, idx);
        page->setPosition(Point(getPositionXByIndex(idx), 0));
        addChild(page);
        Size pSize = page->getSize();
        Size pvSize = getSize();
        if (!pSize.equals(pvSize))
        {
            CCLOG("page size does not match pageview size, it will be force sized!");
            page->setSize(pvSize);
        }
        ccArray* arrayPages = _pages->data;
        int length = arrayPages->num;
        for (int i=(idx+1); i<length; i++) {
            UIWidget* behindPage = dynamic_cast<UIWidget*>(arrayPages->arr[i]);
            Point formerPos = behindPage->getPosition();
            behindPage->setPosition(Point(formerPos.x+getSize().width, 0));
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
    if (index < 0 || index >= (int)(_pages->count()))
    {
        return;
    }
    Layout* page = dynamic_cast<Layout*>(_pages->getObjectAtIndex(index));
    if (page)
    {
        removePage(page);
    }
}

void UIPageView::updateBoundaryPages()
{
    if (_pages->count() <= 0)
    {
        _leftChild = NULL;
        _rightChild = NULL;
    }
    _leftChild = dynamic_cast<UIWidget*>(_pages->getObjectAtIndex(0));
    _rightChild = dynamic_cast<UIWidget*>(_pages->getLastObject());
}

float UIPageView::getPositionXByIndex(int idx)
{
    return (getSize().width*(idx-_curPageIdx));
}

bool UIPageView::addChild(UIWidget* widget)
{
    return Layout::addChild(widget);
}

bool UIPageView::removeChild(UIWidget* widget)
{
    if (_pages->containsObject(widget))
    {
        _pages->removeObject(widget);
        return Layout::removeChild(widget);
    }
    return false;
}

void UIPageView::onSizeChanged()
{
    Layout::onSizeChanged();
    _rightBoundary = getSize().width;
    updateChildrenSize();
    updateChildrenPosition();
}

void UIPageView::updateChildrenSize()
{
    if (!_pages)
    {
        return;
    }
    
    Size selfSize = getSize();
    for (unsigned int i=0; i<_pages->count(); i++)
    {
        Layout* page = dynamic_cast<Layout*>(_pages->getObjectAtIndex(i));
        page->setSize(selfSize);
    }
}

void UIPageView::updateChildrenPosition()
{
    if (!_pages)
    {
        return;
    }
    
    int pageCount = _pages->data->num;
    if (pageCount <= 0)
    {
        _curPageIdx = 0;
        return;
    }
    if (_curPageIdx >= pageCount)
    {
        _curPageIdx = pageCount-1;
    }
    float pageWidth = getSize().width;
    ccArray* arrayPages = _pages->data;
    for (int i=0; i<pageCount; i++)
    {
        Layout* page = dynamic_cast<Layout*>(arrayPages->arr[i]);
        page->setPosition(Point((i-_curPageIdx)*pageWidth, 0));
    }
}

void UIPageView::removeAllChildren()
{
    _pages->removeAllObjects();
    Layout::removeAllChildren();
}

void UIPageView::scrollToPage(int idx)
{
    if (idx < 0 || idx >= (int)(_pages->count()))
    {
        return;
    }
    _curPageIdx = idx;
    UIWidget* curPage = dynamic_cast<UIWidget*>(_pages->getObjectAtIndex(idx));
    _autoScrollDistance = -(curPage->getPosition().x);
    _autoScrollSpeed = fabs(_autoScrollDistance)/0.2f;
    _autoScrollDir = _autoScrollDistance > 0 ? 1 : 0;
    _isAutoScrolling = true;
}

void UIPageView::update(float dt)
{
    if (_isAutoScrolling)
    {
        switch (_autoScrollDir)
        {
            case 0:
            {
                float step = _autoScrollSpeed*dt;
                if (_autoScrollDistance + step >= 0.0f)
                {
                    step = -_autoScrollDistance;
                    _autoScrollDistance = 0.0f;
                    _isAutoScrolling = false;
                    pageTurningEvent();
                }
                else
                {
                    _autoScrollDistance += step;
                }
                scrollPages(-step);
                break;
            }
                break;
            case 1:
            {
                float step = _autoScrollSpeed*dt;
                if (_autoScrollDistance - step <= 0.0f)
                {
                    step = _autoScrollDistance;
                    _autoScrollDistance = 0.0f;
                    _isAutoScrolling = false;
                    pageTurningEvent();
                }
                else
                {
                    _autoScrollDistance -= step;
                }
                scrollPages(step);
                break;
            }
            default:
                break;
        }
    }
}

bool UIPageView::onTouchBegan(const Point &touchPoint)
{
    bool pass = Layout::onTouchBegan(touchPoint);
    handlePressLogic(touchPoint);
    return pass;
}

void UIPageView::onTouchMoved(const Point &touchPoint)
{
    _touchMovePos.x = touchPoint.x;
    _touchMovePos.y = touchPoint.y;
    handleMoveLogic(touchPoint);
    if (_widgetParent)
    {
        _widgetParent->checkChildInfo(1,this,touchPoint);
    }
    moveEvent();
    if (!hitTest(touchPoint))
    {
        setFocused(false);
        onTouchEnded(touchPoint);
    }
}

void UIPageView::onTouchEnded(const Point &touchPoint)
{
    Layout::onTouchEnded(touchPoint);
    handleReleaseLogic(touchPoint);
}

void UIPageView::movePages(float offset)
{
    ccArray* arrayPages = _pages->data;
    int length = arrayPages->num;
    for (int i = 0; i < length; i++)
    {
        UIWidget* child = (UIWidget*)(arrayPages->arr[i]);
        _movePagePoint.x = child->getPosition().x + offset;
        _movePagePoint.y = child->getPosition().y;
        child->setPosition(_movePagePoint);
    }
}

bool UIPageView::scrollPages(float touchOffset)
{
    if (_pages->count() <= 0)
    {
        return false;
    }
    
    if (!_leftChild || !_rightChild)
    {
        return false;
    }
    
    float realOffset = touchOffset;
    
    switch (_touchMoveDir)
    {
        case PAGEVIEW_TOUCHLEFT: // left
            if (_rightChild->getRightInParent() + touchOffset <= _rightBoundary)
            {
                realOffset = _rightBoundary - _rightChild->getRightInParent();
                movePages(realOffset);
                return false;
            }
            break;
            
        case PAGEVIEW_TOUCHRIGHT: // right
            if (_leftChild->getLeftInParent() + touchOffset >= _leftBoundary)
            {
                realOffset = _leftBoundary - _leftChild->getLeftInParent();
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

void UIPageView::onTouchCancelled(const Point &touchPoint)
{
    Layout::onTouchCancelled(touchPoint);
}

void UIPageView::handlePressLogic(const Point &touchPoint)
{
    Point nsp = _renderer->convertToNodeSpace(touchPoint);
    _touchMoveStartLocation = nsp.x;
    _touchStartLocation = nsp.x;
}

void UIPageView::handleMoveLogic(const Point &touchPoint)
{
    Point nsp = _renderer->convertToNodeSpace(touchPoint);
    float offset = 0.0;
    float moveX = nsp.x;
    offset = moveX - _touchMoveStartLocation;
    _touchMoveStartLocation = moveX;
    if (offset < 0)
    {
        _touchMoveDir = PAGEVIEW_TOUCHLEFT;
    }
    else if (offset > 0)
    {
        _touchMoveDir = PAGEVIEW_TOUCHRIGHT;
    }
    scrollPages(offset);
}

void UIPageView::handleReleaseLogic(const Point &touchPoint)
{
    UIWidget* curPage = dynamic_cast<UIWidget*>(_pages->getObjectAtIndex(_curPageIdx));
    if (curPage)
    {
        Point curPagePos = curPage->getPosition();
        int pageCount = _pages->count();
        float curPageLocation = curPagePos.x;
        float pageWidth = getSize().width;
        float boundary = pageWidth/2.0f;
        if (curPageLocation <= -boundary)
        {
            if (_curPageIdx >= pageCount-1)
            {
                scrollPages(-curPageLocation);
            }
            else
            {
                scrollToPage(_curPageIdx+1);
            }
        }
        else if (curPageLocation >= boundary)
        {
            if (_curPageIdx <= 0)
            {
                scrollPages(-curPageLocation);
            }
            else
            {
                scrollToPage(_curPageIdx-1);
            }
        }
        else
        {
            scrollToPage(_curPageIdx);
        }
    }
}

void UIPageView::checkChildInfo(int handleState,UIWidget* sender, const Point &touchPoint)
{
    interceptTouchEvent(handleState, sender, touchPoint);
}

void UIPageView::interceptTouchEvent(int handleState, UIWidget *sender, const Point &touchPoint)
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
            if (offset > _childFocusCancelOffset)
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
    if (_eventListener && _eventSelector)
    {
        (_eventListener->*_eventSelector)(this, PAGEVIEW_EVENT_TURNING);
    }
}

void UIPageView::addEventListener(Object *target, SEL_PageViewEvent selector)
{
    _eventListener = target;
    _eventSelector = selector;
}

int UIPageView::getCurPageIndex() const
{
    return _curPageIdx;
}

const char* UIPageView::getDescription() const
{
    return "PageView";
}

NS_CC_EXT_END