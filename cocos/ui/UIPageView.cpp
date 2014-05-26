/****************************************************************************
Copyright (c) 2013-2014 Chukong Technologies Inc.

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

#include "ui/UIPageView.h"

NS_CC_BEGIN

namespace ui {
    
IMPLEMENT_CLASS_GUI_INFO(PageView)

PageView::PageView():
_curPageIdx(0),
_touchMoveDir(TouchDirection::LEFT),
_touchStartLocation(0.0f),
_touchMoveStartLocation(0.0f),
_movePagePoint(Vec2::ZERO),
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
_pageViewEventSelector(nullptr),
_eventCallback(nullptr)
{
}

PageView::~PageView()
{
    _pages.clear();
    _pageViewEventListener = nullptr;
    _pageViewEventSelector = nullptr;
}

PageView* PageView::create()
{
    PageView* widget = new PageView();
    if (widget && widget->init())
    {
        widget->autorelease();
        return widget;
    }
    CC_SAFE_DELETE(widget);
    return nullptr;
}
    
void PageView::onEnter()
{
    Layout::onEnter();
    scheduleUpdate();
}

bool PageView::init()
{
    if (Layout::init())
    {
        setClippingEnabled(true);
        setTouchEnabled(true);
        return true;
    }
    return false;
}

void PageView::addWidgetToPage(Widget *widget, ssize_t pageIdx, bool forceCreate)
{
    if (!widget)
    {
        return;
    }
    if (pageIdx < 0)
    {
        return;
    }
    ssize_t pageCount = _pages.size();
    if (pageIdx < 0 || pageIdx >= pageCount)
    {
        if (forceCreate)
        {
            if (pageIdx > pageCount)
            {
                CCLOG("pageIdx is %d, it will be added as page id [%d]",static_cast<int>(pageIdx),static_cast<int>(pageCount));
            }
            Layout* newPage = createPage();
            newPage->addChild(widget);
            addPage(newPage);
        }
    }
    else
    {
        Layout * page = _pages.at(pageIdx);
        page->addChild(widget);
    }
}

Layout* PageView::createPage()
{
    Layout* newPage = Layout::create();
    newPage->setSize(getSize());
    return newPage;
}

void PageView::addPage(Layout* page)
{
    if (!page)
    {
        return;
    }
    
    if (_pages.contains(page))
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
    page->setPosition(Vec2(getPositionXByIndex(_pages.size()), 0));
    _pages.pushBack(page);
    addChild(page);
    updateBoundaryPages();
}

void PageView::insertPage(Layout* page, int idx)
{
    if (idx < 0)
    {
        return;
    }
    if (!page)
    {
        return;
    }
  
    if (_pages.contains(page))
    {
        return;
    }
    
    ssize_t pageCount = _pages.size();
    if (idx >= pageCount)
    {
        addPage(page);
    }
    else
    {
        _pages.insert(idx, page);
        page->setPosition(Vec2(getPositionXByIndex(idx), 0));
        addChild(page);
        Size pSize = page->getSize();
        Size pvSize = getSize();
        if (!pSize.equals(pvSize))
        {
            CCLOG("page size does not match pageview size, it will be force sized!");
            page->setSize(pvSize);
        }
        ssize_t length = _pages.size();
        for (ssize_t i=(idx+1); i<length; i++){
            Widget* behindPage = _pages.at(i);
            Vec2 formerPos = behindPage->getPosition();
            behindPage->setPosition(Vec2(formerPos.x+getSize().width, 0));
        }
        updateBoundaryPages();
    }
}

void PageView::removePage(Layout* page)
{
    if (!page)
    {
        return;
    }
    removeChild(page);
    updateChildrenPosition();
    updateBoundaryPages();
}

void PageView::removePageAtIndex(ssize_t index)
{
    if (index < 0 || index >= _pages.size())
    {
        return;
    }
    Layout* page = _pages.at(index);
    removePage(page);
}
    
void PageView::removeAllPages()
{
    removeAllChildren();
}

void PageView::updateBoundaryPages()
{
    if (_pages.size() <= 0)
    {
        _leftChild = nullptr;
        _rightChild = nullptr;
        return;
    }
    _leftChild = _pages.at(0);
    _rightChild = _pages.at(_pages.size()-1);
}

float PageView::getPositionXByIndex(ssize_t idx)
{
    return (getSize().width*(idx-_curPageIdx));
}
    
void PageView::addChild(Node *child)
{
    Layout::addChild(child);
}

void PageView::addChild(Node * child, int zOrder)
{
    Layout::addChild(child, zOrder);
}

void PageView::addChild(Node *child, int zOrder, int tag)
{
    Layout::addChild(child, zOrder, tag);
}

void PageView::removeChild(Node *child, bool cleanup)
{
    if (_pages.contains(static_cast<Layout*>(child)))
    {
        _pages.eraseObject(static_cast<Layout*>(child));
    }
    Layout::removeChild(child, cleanup);
}

void PageView::onSizeChanged()
{
    Layout::onSizeChanged();
    _rightBoundary = getSize().width;
    updateChildrenSize();
    updateChildrenPosition();
}

void PageView::updateChildrenSize()
{
    Size selfSize = getSize();
    for (auto& page : _pages)
    {
        page->setSize(selfSize);
    }
}

void PageView::updateChildrenPosition()
{
    ssize_t pageCount = _pages.size();
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
    for (int i=0; i<pageCount; i++)
    {
        Layout* page = _pages.at(i);
        page->setPosition(Vec2((i-_curPageIdx)*pageWidth, 0));
    }
}

void PageView::removeAllChildren()
{
    removeAllChildrenWithCleanup(true);
}
    
void PageView::removeAllChildrenWithCleanup(bool cleanup)
{
    _pages.clear();
    Layout::removeAllChildrenWithCleanup(cleanup);
}

void PageView::scrollToPage(ssize_t idx)
{
    if (idx < 0 || idx >= _pages.size())
    {
        return;
    }
    _curPageIdx = idx;
    Widget* curPage = _pages.at(idx);
    _autoScrollDistance = -(curPage->getPosition().x);
    _autoScrollSpeed = fabs(_autoScrollDistance)/0.2f;
    _autoScrollDir = _autoScrollDistance > 0 ? 1 : 0;
    _isAutoScrolling = true;
}

void PageView::update(float dt)
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

bool PageView::onTouchBegan(Touch *touch, Event *unusedEvent)
{
    bool pass = Layout::onTouchBegan(touch, unusedEvent);
    if (_hitted)
    {
        handlePressLogic(touch->getLocation());
    }
    return pass;
}

void PageView::onTouchMoved(Touch *touch, Event *unusedEvent)
{
    _touchMovePos = touch->getLocation();
    handleMoveLogic(_touchMovePos);
    Widget* widgetParent = getWidgetParent();
    if (widgetParent)
    {
        widgetParent->checkChildInfo(1,this,_touchMovePos);
    }
    moveEvent();
}

void PageView::onTouchEnded(Touch *touch, Event *unusedEvent)
{
    Layout::onTouchEnded(touch, unusedEvent);
    handleReleaseLogic(_touchEndPos);
}
    
void PageView::onTouchCancelled(Touch *touch, Event *unusedEvent)
{
    Layout::onTouchCancelled(touch, unusedEvent);
    handleReleaseLogic(touch->getLocation());
}

void PageView::movePages(float offset)
{
    for (auto& page : _pages)
    {
        _movePagePoint.x = page->getPosition().x + offset;
        _movePagePoint.y = page->getPosition().y;
        page->setPosition(_movePagePoint);
    }
}

bool PageView::scrollPages(float touchOffset)
{
    if (_pages.size() <= 0)
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
        case TouchDirection::LEFT: // left
            if (_rightChild->getRightInParent() + touchOffset <= _rightBoundary)
            {
                realOffset = _rightBoundary - _rightChild->getRightInParent();
                movePages(realOffset);
                return false;
            }
            break;
            
        case TouchDirection::RIGHT: // right
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

void PageView::handlePressLogic(const Vec2 &touchPoint)
{
    Vec2 nsp = convertToNodeSpace(touchPoint);
    _touchMoveStartLocation = nsp.x;
    _touchStartLocation = nsp.x;
}

void PageView::handleMoveLogic(const Vec2 &touchPoint)
{
    Vec2 nsp = convertToNodeSpace(touchPoint);
    float offset = 0.0;
    float moveX = nsp.x;
    offset = moveX - _touchMoveStartLocation;
    _touchMoveStartLocation = moveX;
    if (offset < 0)
    {
        _touchMoveDir = TouchDirection::LEFT;
    }
    else if (offset > 0)
    {
        _touchMoveDir = TouchDirection::RIGHT;
    }
    scrollPages(offset);
}

void PageView::handleReleaseLogic(const Vec2 &touchPoint)
{
    if (_pages.size() <= 0)
    {
        return;
    }
    Widget* curPage = _pages.at(_curPageIdx);
    if (curPage)
    {
        Vec2 curPagePos = curPage->getPosition();
        ssize_t pageCount = _pages.size();
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

void PageView::checkChildInfo(int handleState,Widget* sender, const Vec2 &touchPoint)
{
    interceptTouchEvent(handleState, sender, touchPoint);
}

void PageView::interceptTouchEvent(int handleState, Widget *sender, const Vec2 &touchPoint)
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
                sender->setHighlighted(false);
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

void PageView::pageTurningEvent()
{
    if (_pageViewEventListener && _pageViewEventSelector)
    {
        (_pageViewEventListener->*_pageViewEventSelector)(this, PAGEVIEW_EVENT_TURNING);
    }
    if (_eventCallback) {
        _eventCallback(this,EventType::TURNING);
    }
}

void PageView::addEventListenerPageView(Ref *target, SEL_PageViewEvent selector)
{
    _pageViewEventListener = target;
    _pageViewEventSelector = selector;
}
    
void PageView::addEventListener(const ccPageViewCallback& callback)
{
    _eventCallback = callback;
}

ssize_t PageView::getCurPageIndex() const
{
    return _curPageIdx;
}

Vector<Layout*>& PageView::getPages()
{
    return _pages;
}
    
Layout* PageView::getPage(ssize_t index)
{
    if (index < 0 || index >= _pages.size())
    {
        return nullptr;
    }
    return _pages.at(index);
}

std::string PageView::getDescription() const
{
    return "PageView";
}

Widget* PageView::createCloneInstance()
{
    return PageView::create();
}

void PageView::copyClonedWidgetChildren(Widget* model)
{
    auto& modelPages = static_cast<PageView*>(model)->getPages();
    for (auto& page : modelPages)
    {
        addPage(dynamic_cast<Layout*>(page->clone()));
    }
}

void PageView::copySpecialProperties(Widget *widget)
{
    PageView* pageView = dynamic_cast<PageView*>(widget);
    if (pageView)
    {
        Layout::copySpecialProperties(widget);
        _eventCallback = pageView->_eventCallback;
        _pageViewEventListener = pageView->_pageViewEventListener;
        _pageViewEventSelector = pageView->_pageViewEventSelector;
    }
}

}

NS_CC_END
