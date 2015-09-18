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
_isAutoScrolling(false),
_autoScrollDistance(0.0f),
_autoScrollSpeed(0.0f),
_autoScrollDirection(AutoScrollDirection::LEFT),
_direction(Direction::HORIZONTAL),
_curPageIdx(-1),
_touchMoveDirection(TouchDirection::LEFT),
_leftBoundaryChild(nullptr),
_rightBoundaryChild(nullptr),
_leftBoundary(0.0f),
_rightBoundary(0.0f),
_customScrollThreshold(0.0),
_usingCustomScrollThreshold(false),
_childFocusCancelOffset(5.0f),
_pageViewEventListener(nullptr),
_pageViewEventSelector(nullptr),
_eventCallback(nullptr)
{
    this->setTouchEnabled(true);
}

PageView::~PageView()
{
    _pageViewEventListener = nullptr;
    _pageViewEventSelector = nullptr;
}

PageView* PageView::create()
{
    PageView* widget = new (std::nothrow) PageView();
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
    newPage->setContentSize(getContentSize());
    return newPage;
}

void PageView::addPage(Layout* page)
{
    if (!page || _pages.contains(page))
    {
        return;
    }

    
    addChild(page);
    _pages.pushBack(page);
    if (_curPageIdx == -1)
    {
        _curPageIdx = 0;
    }
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
        addChild(page);
        if(_curPageIdx == -1)
        {
            _curPageIdx = 0;
        }
    }
    
    _doLayoutDirty = true;
}


void PageView::removePage(Layout* page)
{
    if (!page)
    {
        return;
    }
    removeChild(page);
    _pages.eraseObject(page);
    auto pageCount = _pages.size();
    if (_curPageIdx >= pageCount)
    {
        _curPageIdx = pageCount - 1;
    }

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
        removeChild(node);
    }
    _pages.clear();
    _curPageIdx = -1;
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
    return (getContentSize().width * (idx-_curPageIdx));
}
    
float PageView::getPositionYByIndex(ssize_t idx)const
{
    return (getContentSize().height * (idx-_curPageIdx));
}

void PageView::onSizeChanged()
{
    Layout::onSizeChanged();
    if (_direction == Direction::HORIZONTAL)
    {
        _rightBoundary = getContentSize().width;
    }
    else
    {
        _rightBoundary = getContentSize().height;
    }
    
    _doLayoutDirty = true;
}

void PageView::updateAllPagesSize()
{
    Size selfSize = getContentSize();
    for (auto& page : _pages)
    {
        page->setContentSize(selfSize);
    }
}

void PageView::updateAllPagesPosition()
{
    ssize_t pageCount = this->getPageCount();
    
    if (pageCount <= 0)
    {
        _curPageIdx = -1;
        return;
    }
    
    if (_curPageIdx >= pageCount)
    {
        _curPageIdx = pageCount-1;
    }
    // If the layout is dirty, don't trigger auto scroll
    _isAutoScrolling = false;

    for (int i=0; i<pageCount; i++)
    {
        Layout* page = _pages.at(i);
        Vec2 newPosition;

        if (_direction == Direction::HORIZONTAL)
        {
            float pageWidth = getContentSize().width;
            newPosition =  Vec2((i-_curPageIdx) * pageWidth, 0);
        }
        else if(_direction == Direction::VERTICAL)
        {
            float pageHeight = getContentSize().height;
            newPosition = Vec2(0,(i-_curPageIdx) * pageHeight * -1);

        }
        page->setPosition(newPosition);
    }
}

void PageView::setCurPageIndex( ssize_t index )
{
    if (index < 0 || index >= this->getPageCount())
    {
        return;
    }
    _curPageIdx = index;
    _doLayoutDirty = true;
}

void PageView::scrollToPage(ssize_t idx)
{
    if (idx < 0 || idx >= this->getPageCount())
    {
        return;
    }
    _curPageIdx = idx;
    Layout* curPage = _pages.at(idx);
    if (_direction == Direction::HORIZONTAL)
    {
        _autoScrollDistance = -(curPage->getPosition().x);
        if (_autoScrollDistance > 0)
        {
            _autoScrollDirection = AutoScrollDirection::RIGHT;
        }
        else
        {
            _autoScrollDirection = AutoScrollDirection::LEFT;
        }
    }
    else if(_direction == Direction::VERTICAL)
    {
        _autoScrollDistance = -curPage->getPosition().y;
        if (_autoScrollDistance > 0)
        {
            _autoScrollDirection = AutoScrollDirection::DOWN;
        }
        else
        {
            _autoScrollDirection = AutoScrollDirection::UP;
        }
    }
    _autoScrollSpeed = fabs(_autoScrollDistance)/0.2f;
    _isAutoScrolling = true;
}
    
void PageView::setDirection(cocos2d::ui::PageView::Direction direction)
{
    this->_direction = direction;
}
    
PageView::Direction PageView::getDirection()const
{
    return this->_direction;
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
        float step = _autoScrollSpeed*dt;
        int  sign = 1;
        switch (_autoScrollDirection)
        {
            case AutoScrollDirection::LEFT:
            case AutoScrollDirection::UP:
            {
                if (_autoScrollDistance + step >= 0.0f)
                {
                    step = -_autoScrollDistance;
                    _isAutoScrolling = false;
                    _autoScrollDistance = 0.0f;
                }
                else
                {
                    _autoScrollDistance += step;
                }
                sign = -1;
                break;
            }
                break;
            case AutoScrollDirection::RIGHT:
            case AutoScrollDirection::DOWN:
            {
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
                break;
            }
            default:
                break;
        }
        
        if (_direction == Direction::HORIZONTAL)
        {
            scrollPages(Vec2(step * sign, 0));
        }
        else
        {
            scrollPages(Vec2(0, step * sign));
        }

        if (!_isAutoScrolling)
        {
            pageTurningEvent();
        }
    }

bool PageView::onTouchBegan(Touch *touch, Event *unusedEvent)
{
    bool pass = Layout::onTouchBegan(touch, unusedEvent);
    return pass;
}

void PageView::onTouchMoved(Touch *touch, Event *unusedEvent)
{
    Layout::onTouchMoved(touch, unusedEvent);
    if (!_isInterceptTouch)
    {
        handleMoveLogic(touch);
    }
}

void PageView::onTouchEnded(Touch *touch, Event *unusedEvent)
{
    Layout::onTouchEnded(touch, unusedEvent);
    if (!_isInterceptTouch)
    {
        handleReleaseLogic(touch);
    }
    _isInterceptTouch = false;
}
    
void PageView::onTouchCancelled(Touch *touch, Event *unusedEvent)
{
    Layout::onTouchCancelled(touch, unusedEvent);
    if (!_isInterceptTouch)
    {
        handleReleaseLogic(touch);
    }
    _isInterceptTouch = false;
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

void PageView::movePages(Vec2 offset)
{
    for (auto& page : this->getPages())
    {
        Vec2 oldPosition = page->getPosition();
        page->setPosition(oldPosition + offset);
    }
}

bool PageView::scrollPages(Vec2 touchOffset)
{
    if (this->getPageCount() <= 0)
    {
        return false;
    }
    
    if (!_leftBoundaryChild || !_rightBoundaryChild)
    {
        return false;
    }
    
    Vec2 realOffset = touchOffset;
    
    switch (_touchMoveDirection)
    {
        case TouchDirection::LEFT: // left
            if (_rightBoundaryChild->getRightBoundary() + touchOffset.x <= _rightBoundary)
            {
                realOffset.x = _rightBoundary - _rightBoundaryChild->getRightBoundary();
                realOffset.y = 0;
                movePages(realOffset);
                return false;
            }
            break;
            
        case TouchDirection::RIGHT: // right
            if (_leftBoundaryChild->getLeftBoundary() + touchOffset.x >= _leftBoundary)
            {
                realOffset.x = _leftBoundary - _leftBoundaryChild->getLeftBoundary();
                realOffset.y = 0;
                movePages(realOffset);
                return false;
            }
            break;
        case TouchDirection::UP:
        {
            if (_rightBoundaryChild->getBottomBoundary() + touchOffset.y >= _leftBoundary)
            {
                realOffset.y = _leftBoundary - _rightBoundaryChild->getBottomBoundary();
                realOffset.x = 0;
                movePages(realOffset);
                return false;
            }
           
        }break;
        case TouchDirection::DOWN:
        {
            if (_leftBoundaryChild->getTopBoundary() + touchOffset.y <= _rightBoundary)
            {
                realOffset.y = _rightBoundary - _leftBoundaryChild->getTopBoundary();
                realOffset.x = 0;
                movePages(realOffset);
                return false;
            }
        }break;
        default:
            break;
    }
    
    movePages(realOffset);
    return true;
}


void PageView::handleMoveLogic(Touch *touch)
{
    Vec2 touchPoint = touch->getLocation();
    
    Vec2 offset;
    offset = touchPoint - touch->getPreviousLocation();

    if (_direction == Direction::HORIZONTAL)
    {
        if (offset.x < 0)
        {
            _touchMoveDirection = TouchDirection::LEFT;
        }
        else if (offset.x > 0)
        {
            _touchMoveDirection = TouchDirection::RIGHT;
        }
        offset.y = 0;
    }
    else
    {
        offset.x = 0;
        if(offset.y > 0)
        {
            _touchMoveDirection = TouchDirection::UP;
        }
        else if(offset.y < 0)
        {
            _touchMoveDirection = TouchDirection::DOWN;
        }
    }
   
    scrollPages(offset);
}
    
void PageView::setCustomScrollThreshold(float threshold)
{
    CCASSERT(threshold > 0, "Invalid threshold!");
    _customScrollThreshold = threshold;
    this->setUsingCustomScrollThreshold(true);
}

float PageView::getCustomScrollThreshold()const
{
    return _customScrollThreshold;
}
    
void PageView::setUsingCustomScrollThreshold(bool flag)
{
    _usingCustomScrollThreshold = flag;
}
    
bool PageView::isUsingCustomScrollThreshold()const
{
    return _usingCustomScrollThreshold;
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
        
        auto contentSize = getContentSize();
       
        float moveBoundray = 0.0f;
        float scrollDistance;
        if (_direction == Direction::HORIZONTAL)
        {
            curPagePos.y = 0;
            moveBoundray = curPagePos.x;
            scrollDistance = contentSize.width / 2.0;
        }
        else if(_direction == Direction::VERTICAL)
        {
            curPagePos.x = 0;
            moveBoundray = curPagePos.y;
            scrollDistance  = contentSize.height / 2.0;
        }

        if (!_usingCustomScrollThreshold)
        {
            _customScrollThreshold = scrollDistance;
        }
        float boundary = _customScrollThreshold;
        
        if (_direction == Direction::HORIZONTAL)
        {
            if (moveBoundray <= -boundary)
            {
                if (_curPageIdx >= pageCount-1)
                {
                    scrollPages(curPagePos);
                }
                else
                {
                    scrollToPage(_curPageIdx+1);
                }
            }
            else if (moveBoundray >= boundary)
            {
                if (_curPageIdx <= 0)
                {
                    scrollPages(curPagePos);
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
        else if(_direction == Direction::VERTICAL)
        {
            if (moveBoundray >= boundary)
            {
                if (_curPageIdx >= pageCount-1)
                {
                    scrollPages(curPagePos);
                }
                else
                {
                    scrollToPage(_curPageIdx+1);
                }
            }
            else if (moveBoundray <= -boundary)
            {
                if (_curPageIdx <= 0)
                {
                    scrollPages(curPagePos);
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
}


void PageView::interceptTouchEvent(TouchEventType event, Widget *sender, Touch *touch)
{
    if (!_touchEnabled)
    {
        Layout::interceptTouchEvent(event, sender, touch);
        return;
    }
    Vec2 touchPoint = touch->getLocation();
    
    switch (event)
    {
        case TouchEventType::BEGAN:
        {
            _touchBeganPosition = touch->getLocation();
            _isInterceptTouch = true;
        }
        break;
        case TouchEventType::MOVED:
        {
            float offset = 0;
            if (_direction == Direction::HORIZONTAL)
            {
                offset = fabs(sender->getTouchBeganPosition().x - touchPoint.x);
            }
            else if(_direction == Direction::VERTICAL)
            {
                offset = fabs(sender->getTouchBeganPosition().y - touchPoint.y);
            }
            _touchMovePosition = touch->getLocation();
            if (offset > _childFocusCancelOffset)
            {
                sender->setHighlighted(false);
                handleMoveLogic(touch);
            }
        }
        break;
        case TouchEventType::CANCELED:
        case TouchEventType::ENDED:
        {
            _touchEndPosition = touch->getLocation();
            handleReleaseLogic(touch);
            if (sender->isSwallowTouches())
            {
                _isInterceptTouch = false;
            }
        }
            break;
    }
}

void PageView::pageTurningEvent()
{
    this->retain();
    if (_pageViewEventListener && _pageViewEventSelector)
    {
        (_pageViewEventListener->*_pageViewEventSelector)(this, PAGEVIEW_EVENT_TURNING);
    }
    if (_eventCallback)
    {
        _eventCallback(this,EventType::TURNING);
    }
    if (_ccEventCallback)
    {
        _ccEventCallback(this, static_cast<int>(EventType::TURNING));
    }
    this->release();
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
        _ccEventCallback = pageView->_ccEventCallback;
        _pageViewEventListener = pageView->_pageViewEventListener;
        _pageViewEventSelector = pageView->_pageViewEventSelector;
        _usingCustomScrollThreshold = pageView->_usingCustomScrollThreshold;
        _customScrollThreshold = pageView->_customScrollThreshold;
        _direction = pageView->_direction;
    }
}

}

NS_CC_END
