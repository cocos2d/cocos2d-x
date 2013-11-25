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

#include "gui/UIPageView.h"

namespace gui {

UIPageView::UIPageView():
_curPageIdx(0),
_pages(nullptr),
_touchMoveDir(PAGEVIEW_TOUCHLEFT),
_touchStartLocation(0.0f),
_touchMoveStartLocation(0.0f),
_movePagePoint(cocos2d::Point::ZERO),
_leftChild(nullptr),
_rightChild(nullptr),
_leftBoundary(0.0f),
_rightBoundary(0.0f),
_isAutoScrolling(false),
_autoScrollDistance(0.0f),
_autoScrollSpeed(0.0f),
_autoScrollDir(0),
_childFocusCancelOffset(5.0f),
_pageViewEventListener(nullptr),
_pageViewEventSelector(nullptr)
{
}

UIPageView::~UIPageView()
{
    _pages->removeAllObjects();
    CC_SAFE_RELEASE(_pages);
    _pageViewEventListener = nullptr;
    _pageViewEventSelector = nullptr;
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
    return nullptr;
}

bool UIPageView::init()
{
    if (UILayout::init())
    {
        _pages = cocos2d::Array::create();
        _pages->retain();
        setClippingEnabled(true);
        setUpdateEnabled(true);
        setTouchEnabled(true);
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
    if (pageIdx < 0)
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
            UILayout* newPage = createPage();
            newPage->addChild(widget);
            addPage(newPage);
        }
    }
    else
    {
        UILayout * page = dynamic_cast<UILayout*>(_pages->getObjectAtIndex(pageIdx));
        if (page)
        {
            page->addChild(widget);
        }
    }
}

UILayout* UIPageView::createPage()
{
    UILayout* newPage = UILayout::create();
    newPage->setSize(getSize());
    return newPage;
}

void UIPageView::addPage(UILayout* page)
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
    cocos2d::Size pSize = page->getSize();
    cocos2d::Size pvSize = getSize();
    if (!pSize.equals(pvSize))
    {
        CCLOG("page size does not match pageview size, it will be force sized!");
        page->setSize(pvSize);
    }
    page->setPosition(cocos2d::Point(getPositionXByIndex(_pages->count()), 0));
    _pages->addObject(page);
    addChild(page);
    updateBoundaryPages();
}

void UIPageView::insertPage(UILayout* page, int idx)
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
        page->setPosition(cocos2d::Point(getPositionXByIndex(idx), 0));
        addChild(page);
        cocos2d::Size pSize = page->getSize();
        cocos2d::Size pvSize = getSize();
        if (!pSize.equals(pvSize))
        {
            CCLOG("page size does not match pageview size, it will be force sized!");
            page->setSize(pvSize);
        }
        cocos2d::ccArray* arrayPages = _pages->data;
        int length = arrayPages->num;
        for (int i=(idx+1); i<length; i++) {
            UIWidget* behindPage = dynamic_cast<UIWidget*>(arrayPages->arr[i]);
            cocos2d::Point formerPos = behindPage->getPosition();
            behindPage->setPosition(cocos2d::Point(formerPos.x+getSize().width, 0));
        }
        updateBoundaryPages();
    }
}

void UIPageView::removePage(UILayout* page)
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
    UILayout* page = dynamic_cast<UILayout*>(_pages->getObjectAtIndex(index));
    if (page)
    {
        removePage(page);
    }
}
    
void UIPageView::removeAllPages()
{
    removeAllChildren();
}

void UIPageView::updateBoundaryPages()
{
    if (_pages->count() <= 0)
    {
        _leftChild = nullptr;
        _rightChild = nullptr;
        return;
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
    return UILayout::addChild(widget);
}

bool UIPageView::removeChild(UIWidget* widget)
{
    if (_pages->containsObject(widget))
    {
        _pages->removeObject(widget);
    }
    return UILayout::removeChild(widget);
}

void UIPageView::onSizeChanged()
{
    UILayout::onSizeChanged();
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
    
    cocos2d::Size selfSize = getSize();
    for (long i=0; i<_pages->count(); i++)
    {
        UILayout* page = dynamic_cast<UILayout*>(_pages->getObjectAtIndex(i));
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
    cocos2d::ccArray* arrayPages = _pages->data;
    for (int i=0; i<pageCount; i++)
    {
        UILayout* page = dynamic_cast<UILayout*>(arrayPages->arr[i]);
        page->setPosition(cocos2d::Point((i-_curPageIdx)*pageWidth, 0));
    }
}

void UIPageView::removeAllChildren()
{
    _pages->removeAllObjects();
    UILayout::removeAllChildren();
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
                }
                else
                {
                    _autoScrollDistance += step;
                }
                scrollPages(-step);
                if (!_isAutoScrolling)
                {
                    pageTurningEvent();
                }
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
                }
                else
                {
                    _autoScrollDistance -= step;
                }
                scrollPages(step);
                if (!_isAutoScrolling)
                {
                    pageTurningEvent();
                }
                break;
            }
            default:
                break;
        }
    }
}

bool UIPageView::onTouchBegan(const cocos2d::Point &touchPoint)
{
    bool pass = UILayout::onTouchBegan(touchPoint);
    handlePressLogic(touchPoint);
    return pass;
}

void UIPageView::onTouchMoved(const cocos2d::Point &touchPoint)
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

void UIPageView::onTouchEnded(const cocos2d::Point &touchPoint)
{
    UILayout::onTouchEnded(touchPoint);
    handleReleaseLogic(touchPoint);
}

void UIPageView::movePages(float offset)
{
    cocos2d::ccArray* arrayPages = _pages->data;
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

void UIPageView::onTouchCancelled(const cocos2d::Point &touchPoint)
{
    UILayout::onTouchCancelled(touchPoint);
}

void UIPageView::handlePressLogic(const cocos2d::Point &touchPoint)
{
    cocos2d::Point nsp = _renderer->convertToNodeSpace(touchPoint);
    _touchMoveStartLocation = nsp.x;
    _touchStartLocation = nsp.x;
}

void UIPageView::handleMoveLogic(const cocos2d::Point &touchPoint)
{
    cocos2d::Point nsp = _renderer->convertToNodeSpace(touchPoint);
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

void UIPageView::handleReleaseLogic(const cocos2d::Point &touchPoint)
{
    if (_pages->count() <= 0)
    {
        return;
    }
    UIWidget* curPage = dynamic_cast<UIWidget*>(_pages->getObjectAtIndex(_curPageIdx));
    if (curPage)
    {
        cocos2d::Point curPagePos = curPage->getPosition();
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

void UIPageView::checkChildInfo(int handleState,UIWidget* sender, const cocos2d::Point &touchPoint)
{
    interceptTouchEvent(handleState, sender, touchPoint);
}

void UIPageView::interceptTouchEvent(int handleState, UIWidget *sender, const cocos2d::Point &touchPoint)
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
    if (_pageViewEventListener && _pageViewEventSelector)
    {
        (_pageViewEventListener->*_pageViewEventSelector)(this, PAGEVIEW_EVENT_TURNING);
    }
}

void UIPageView::addEventListenerPageView(cocos2d::Object *target, SEL_PageViewEvent selector)
{
    _pageViewEventListener = target;
    _pageViewEventSelector = selector;
}

int UIPageView::getCurPageIndex() const
{
    return _curPageIdx;
}

cocos2d::Array* UIPageView::getPages()
{
    return _pages;
}
    
UILayout* UIPageView::getPage(int index)
{
    if (index < 0 || index >= (int)(_pages->count()))
    {
        return nullptr;
    }
    return (UILayout*)_pages->getObjectAtIndex(index);
}

const char* UIPageView::getDescription() const
{
    return "PageView";
}

UIWidget* UIPageView::createCloneInstance()
{
    return UIPageView::create();
}

void UIPageView::copyClonedWidgetChildren(UIWidget* model)
{
    cocos2d::ccArray* arrayPages = dynamic_cast<UIPageView*>(model)->getPages()->data;
    int length = arrayPages->num;
    for (int i=0; i<length; i++)
    {
        UILayout* page = (UILayout*)(arrayPages->arr[i]);
        addPage(dynamic_cast<UILayout*>(page->clone()));
    }
}

void UIPageView::copySpecialProperties(UIWidget *widget)
{
    UIPageView* pageView = dynamic_cast<UIPageView*>(widget);
    if (pageView)
    {
        UILayout::copySpecialProperties(widget);
    }
}

}