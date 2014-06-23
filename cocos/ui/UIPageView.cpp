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
_touchMoveDirection(TouchDirection::LEFT),
_leftBoundaryChild(nullptr),
_rightBoundaryChild(nullptr),
_leftBoundary(0.0f),
_rightBoundary(0.0f),
_isAutoScrolling(false),
_autoScrollDistance(0.0f),
_autoScrollSpeed(0.0f),
_autoScrollDirection(AutoScrollDirection::LEFT),
_childFocusCancelOffset(5.0f),
_pageViewEventListener(nullptr),
_pageViewEventSelector(nullptr),
_eventCallback(nullptr)
{
}

PageView::~PageView()
{
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
#if CC_ENABLE_SCRIPT_BINDING
    if (_scriptType == kScriptTypeJavascript)
    {
        if (ScriptEngineManager::sendNodeEventToJSExtended(this, kNodeOnEnter))
            return;
    }
#endif
    
    Layout::onEnter();
    scheduleUpdate();
}

bool PageView::init()
{
    if (Layout::init())
    {
        setClippingEnabled(true);
        return true;
    }
    return false;
}

void PageView::addWidgetToPage(Widget *widget, ssize_t pageIdx, bool forceCreate)
{
    if (!widget || pageIdx < 0)
    {
        return;
    }
   
    ssize_t pageCount = this->getPageCount();
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
        Node * page = _pages.at(pageIdx);
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
    if (!page || _pages.contains(page))
    {
        return;
    }

    
    addProtectedChild(page);
    _pages.pushBack(page);
    
    _doLayoutDirty = true;
}

void PageView::insertPage(Layout* page, int idx)
{
    if (idx < 0 || !page || _pages.contains(page))
    {
        return;
    }
   
    
    ssize_t pageCount = this->getPageCount();
    if (idx >= pageCount)
    {
        addPage(page);
    }
    else
    {
        _pages.insert(idx, page);
        addProtectedChild(page);
        
    }
    
    _doLayoutDirty = true;
}

void PageView::removePage(Layout* page)
{
    if (!page)
    {
        return;
    }
    removeProtectedChild(page);
    _pages.eraseObject(page);
    
    _doLayoutDirty = true;
}

void PageView::removePageAtIndex(ssize_t index)
{
    if (index < 0 || index >= this->getPages().size())
    {
        return;
    }
    Layout* page = _pages.at(index);
    removePage(page);
}
    
void PageView::removeAllPages()
{
    for(const auto& node : _pages)
    {
        removeProtectedChild(node);
    }
    _pages.clear();
}

void PageView::updateBoundaryPages()
{
    if (_pages.size() <= 0)
    {
        _leftBoundaryChild = nullptr;
        _rightBoundaryChild = nullptr;
        return;
    }
    _leftBoundaryChild = _pages.at(0);
    _rightBoundaryChild = _pages.at(this->getPageCount()-1);
}

ssize_t PageView::getPageCount()const
{
    return _pages.size();
}

float PageView::getPositionXByIndex(ssize_t idx)const
{
    return (getSize().width * (idx-_curPageIdx));
}

void PageView::onSizeChanged()
{
    Layout::onSizeChanged();
    _rightBoundary = getSize().width;
    
    _doLayoutDirty = true;
}

void PageView::updateAllPagesSize()
{
    Size selfSize = getSize();
    for (auto& page : _pages)
    {
        page->setSize(selfSize);
    }
}

void PageView::updateAllPagesPosition()
{
    ssize_t pageCount = this->getPageCount();
    
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
        page->setPosition(Vec2((i-_curPageIdx) * pageWidth, 0));
        
    }
}


void PageView::scrollToPage(ssize_t idx)
{
    if (idx < 0 || idx >= this->getPageCount())
    {
        return;
    }
    _curPageIdx = idx;
    Layout* curPage = _pages.at(idx);
    _autoScrollDistance = -(curPage->getPosition().x);
    _autoScrollSpeed = fabs(_autoScrollDistance)/0.2f;
    _autoScrollDirection = _autoScrollDistance > 0 ? AutoScrollDirection::RIGHT : AutoScrollDirection::LEFT;
    _isAutoScrolling = true;
}

void PageView::update(float dt)
{
    if (_isAutoScrolling)
    {
        this->autoScroll(dt);
    }
}
    
void PageView::autoScroll(float dt)
    {
        switch (_autoScrollDirection)
        {
            case AutoScrollDirection::LEFT:
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
            case AutoScrollDirection::RIGHT:
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

bool PageView::onTouchBegan(Touch *touch, Event *unusedEvent)
{
    bool pass = Layout::onTouchBegan(touch, unusedEvent);
    if (_hitted)
    {
        handlePressLogic(touch);
    }
    return pass;
}

void PageView::onTouchMoved(Touch *touch, Event *unusedEvent)
{
    handleMoveLogic(touch);
    Widget* widgetParent = getWidgetParent();
    if (widgetParent)
    {
        widgetParent->interceptTouchEvent(TouchEventType::MOVED,this,touch);
    }
    moveEvent();
}

void PageView::onTouchEnded(Touch *touch, Event *unusedEvent)
{
    Layout::onTouchEnded(touch, unusedEvent);
    handleReleaseLogic(touch);
}
    
void PageView::onTouchCancelled(Touch *touch, Event *unusedEvent)
{
    Layout::onTouchCancelled(touch, unusedEvent);
    handleReleaseLogic(touch);
}

void PageView::doLayout()
{
    if (!_doLayoutDirty)
    {
        return;
    }
    
    updateAllPagesPosition();
    updateAllPagesSize();
    updateBoundaryPages();

    
    _doLayoutDirty = false;
}

void PageView::movePages(float offset)
{
    for (auto& page : this->getPages())
    {
        page->setPosition(Vec2(page->getPosition().x + offset,
                               page->getPosition().y));
    }
}

bool PageView::scrollPages(float touchOffset)
{
    if (this->getPageCount() <= 0)
    {
        return false;
    }
    
    if (!_leftBoundaryChild || !_rightBoundaryChild)
    {
        return false;
    }
    
    float realOffset = touchOffset;
    
    switch (_touchMoveDirection)
    {
        case TouchDirection::LEFT: // left

            if (_rightBoundaryChild->getRightBoundary() + touchOffset <= _rightBoundary)
            {
                realOffset = _rightBoundary - _rightBoundaryChild->getRightBoundary();
                movePages(realOffset);
                return false;
            }
            break;
            
        case TouchDirection::RIGHT: // right

            if (_leftBoundaryChild->getLeftBoundary() + touchOffset >= _leftBoundary)
            {
                realOffset = _leftBoundary - _leftBoundaryChild->getLeftBoundary();
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

void PageView::handlePressLogic(Touch *touch)
{
    //no-op
}

void PageView::handleMoveLogic(Touch *touch)
{
    Vec2 touchPoint = touch->getLocation();
    
    float offset = 0.0;
    offset = touchPoint.x - touch->getPreviousLocation().x;
    
    if (offset < 0)
    {
        _touchMoveDirection = TouchDirection::LEFT;
    }
    else if (offset > 0)
    {
        _touchMoveDirection = TouchDirection::RIGHT;
    }
    scrollPages(offset);
}

void PageView::handleReleaseLogic(Touch *touch)
{
    if (this->getPageCount() <= 0)
    {
        return;
    }
    Widget* curPage = dynamic_cast<Widget*>(this->getPages().at(_curPageIdx));
    if (curPage)
    {
        Vec2 curPagePos = curPage->getPosition();
        ssize_t pageCount = this->getPageCount();
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


void PageView::interceptTouchEvent(TouchEventType event, Widget *sender, Touch *touch)
{
    Vec2 touchPoint = touch->getLocation();
    
    switch (event)
    {
        case TouchEventType::BEGAN:
            handlePressLogic(touch);
            break;
        case TouchEventType::MOVED:
        {
            float offset = 0;
            offset = fabs(sender->getTouchBeganPosition().x - touchPoint.x);
            if (offset > _childFocusCancelOffset)
            {
                sender->setHighlighted(false);
                handleMoveLogic(touch);
            }
        }
            break;
        case TouchEventType::CANCELED:
        case TouchEventType::ENDED:
            handleReleaseLogic(touch);
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
    if (index < 0 || index >= this->getPages().size())
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
    auto modelPages = static_cast<PageView*>(model)->getPages();
    for (auto& page : modelPages)
    {
        addPage(static_cast<Layout*>(page->clone()));
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
