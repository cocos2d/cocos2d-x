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
#include "ui/UIPageViewIndicator.h"

NS_CC_BEGIN

namespace ui {
    
IMPLEMENT_CLASS_GUI_INFO(PageView)

PageView::PageView():
_indicator(nullptr),
_currentPageIndex(-1),
_customScrollThreshold(0.0),
_usingCustomScrollThreshold(false),
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
    PageView* widget = new (std::nothrow) PageView();
    if (widget && widget->init())
    {
        widget->autorelease();
        return widget;
    }
    CC_SAFE_DELETE(widget);
    return nullptr;
}
    
bool PageView::init()
{
    if (ListView::init())
    {
        _indicator = PageViewIndicator::create();
        addProtectedChild(_indicator, 10000);
        
        setDirection(ListView::Direction::HORIZONTAL);
        setMagneticType(MagneticType::CENTER);
		setScrollBarEnabled(false);
        return true;
    }
    return false;
}

void PageView::addWidgetToPage(Widget *widget, ssize_t pageIdx, bool forceCreate)
{
	insertCustomItem(widget, pageIdx);
}

void PageView::addPage(Layout* page)
{
	pushBackCustomItem(page);
}

void PageView::insertPage(Layout* page, int idx)
{
	insertCustomItem(page, idx);
}

void PageView::removePage(Layout* page)
{
	removeItem(getIndex(page));
}

void PageView::removePageAtIndex(ssize_t index)
{
	removeItem(index);
}
    
void PageView::removeAllPages()
{
	removeAllItems();
}

void PageView::setCurPageIndex( ssize_t index )
{
    setCurrentPageIndex(index);
}

void PageView::setCurrentPageIndex(ssize_t index)
{
    jumpToItem(index, Vec2::ANCHOR_MIDDLE, Vec2::ANCHOR_MIDDLE);
}

void PageView::scrollToPage(ssize_t idx)
{
	scrollToItem(idx, Vec2::ANCHOR_MIDDLE, Vec2::ANCHOR_MIDDLE);
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

void PageView::moveInnerContainer(const Vec2& deltaMove, bool canStartBounceBack)
{
    ListView::moveInnerContainer(deltaMove, canStartBounceBack);
    _currentPageIndex = getIndex(getCenterItemInCurrentView());
    _indicator->indicate(_currentPageIndex);
}

void PageView::onItemListChanged()
{
    ListView::onItemListChanged();
    ssize_t index = getIndex(getCenterItemInCurrentView());
    _indicator->reset(_items.size(), index);
}

void PageView::onSizeChanged()
{
    ListView::onSizeChanged();
    _indicator->setPosition(Vec2(getContentSize() / 2) + Vec2(0, -50));
}

void PageView::handleReleaseLogic(Touch *touch)
{
    // Use `ScrollView` method in order to avoid `startMagneticScroll()` by `ListView`.
    ScrollView::handleReleaseLogic(touch);

    if(_items.empty())
    {
        return;
    }

    Vec2 touchMoveVelocity = flattenVectorByDirection(calculateTouchMoveVelocity());

    static const float THRESHOLD = 500;
    CCLOG("handleReleaseLogic() touchMoveVelocity.length()=%.2f", touchMoveVelocity.length());
    if(touchMoveVelocity.length() < THRESHOLD)
    {
        startMagneticScroll();
    }
    else
    {
        Widget* currentPage = getItem(_currentPageIndex);
        Vec2 destination = calculateItemDestination(Vec2::ANCHOR_MIDDLE, currentPage, Vec2::ANCHOR_MIDDLE);
        Vec2 deltaToCurrentpage;
        deltaToCurrentpage = destination - getInnerContainerPosition();
        deltaToCurrentpage = flattenVectorByDirection(deltaToCurrentpage);

        if(touchMoveVelocity.x * deltaToCurrentpage.x > 0 || touchMoveVelocity.y * deltaToCurrentpage.y > 0)
        {
            startMagneticScroll();
        }
        else
        {
            if(touchMoveVelocity.x < 0 || touchMoveVelocity.y > 0)
            {
                ++_currentPageIndex;
            }
            else
            {
                --_currentPageIndex;
            }
            _currentPageIndex = MIN(_currentPageIndex, _items.size());
            _currentPageIndex = MAX(_currentPageIndex, 0);
            scrollToItem(_currentPageIndex, Vec2::ANCHOR_MIDDLE, Vec2::ANCHOR_MIDDLE);
        }
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
	Widget* widget = ListView::getCenterItemInCurrentView();
	return getIndex(widget);
}

Vector<Layout*>& PageView::getPages()
{
	CCASSERT(false, "This method is obsolete!");

    // Temporary code to keep backward compatibility.
    static Vector<Layout*> pages;
	pages.clear();
	for(Widget* widget : getItems())
	{
		pages.pushBack(dynamic_cast<Layout*>(widget));
	}
	return pages;
}

Layout* PageView::getPage(ssize_t index)
{
    if (index < 0 || index >= this->getPages().size())
    {
        return nullptr;
    }

    // Temporary code to keep backward compatibility.
    static Vector<Layout*> pages;
	pages.clear();
	for(Widget* widget : getItems())
	{
		pages.pushBack(dynamic_cast<Layout*>(widget));
	}
    return pages.at(index);
}

std::string PageView::getDescription() const
{
    return "PageView";
}

Widget* PageView::createCloneInstance()
{
    return PageView::create();
}

void PageView::copySpecialProperties(Widget *widget)
{
    PageView* pageView = dynamic_cast<PageView*>(widget);
    if (pageView)
    {
        ListView::copySpecialProperties(widget);
        _eventCallback = pageView->_eventCallback;
        _ccEventCallback = pageView->_ccEventCallback;
        _pageViewEventListener = pageView->_pageViewEventListener;
        _pageViewEventSelector = pageView->_pageViewEventSelector;
        _usingCustomScrollThreshold = pageView->_usingCustomScrollThreshold;
        _customScrollThreshold = pageView->_customScrollThreshold;
    }
}

}

NS_CC_END
