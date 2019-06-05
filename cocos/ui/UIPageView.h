/****************************************************************************
Copyright (c) 2013-2016 Chukong Technologies Inc.
Copyright (c) 2017-2018 Xiamen Yaji Software Co., Ltd.

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

#ifndef __UIPAGEVIEW_H__
#define __UIPAGEVIEW_H__

#include "ui/UIListView.h"
#include "ui/GUIExport.h"

/**
 * @addtogroup ui
 * @{
 */
NS_CC_BEGIN

namespace ui {

class PageViewIndicator;

/**
 *@brief Layout manager that allows the user to flip left & right and up & down through pages of data.
 *
 */
class CC_GUI_DLL PageView : public ListView
{
    
    DECLARE_CLASS_GUI_INFO
    
public:
    /**
     * Page turn event type.
     */
    enum class EventType
    {
        TURNING
    };
    
    /**
     * Touch direction type.
     */
    enum class TouchDirection
    {
        LEFT,
        RIGHT,
        UP,
        DOWN
    };

    /**
     * PageView page turn event callback.
     */
    typedef std::function<void(Ref*, EventType)> ccPageViewCallback;

    /**
     * Default constructor
     * @js ctor
     * @lua new
     */
    PageView();
    
    /**
     * Default destructor
     * @js NA
     * @lua NA
     */
    virtual ~PageView();
    
    /**
     * Create an empty PageView.
     *@return A PageView instance.
     */
    static PageView* create();

    /**
     * Changes direction
     *  Direction Direction::VERTICAL means vertical scroll, Direction::HORIZONTAL means horizontal scroll.
     * @param direction Set the page view's scroll direction.
     */
    virtual void setDirection(Direction direction) override;

    /**
     * Insert a page into the end of PageView.
     *
     * @param page Page to be inserted.
     */
    void addPage(Widget* page);

    /**
     * Insert a page into PageView at a given index.
     *
     * @param page  Page to be inserted.
     * @param idx   A given index.
     */
    void insertPage(Widget* page, int idx);

    /**
     * Remove a page of PageView.
     *
     * @param page  Page to be removed.
     */
    void removePage(Widget* page);

    /**
     * Remove a page at a given index of PageView.
     *
     * @param index  A given index.
     */
    void removePageAtIndex(ssize_t index);

    /**
     * @brief Remove all pages of the PageView.
     */
    void removeAllPages();
    
    /**
     * Scroll to a page with a given index.
     *
     * @param idx   A given index in the PageView. Index start from 0 to pageCount -1.
     */
    void scrollToPage(ssize_t idx);
    
    /**
     * Scroll to a page with a given index and with a given scroll time.
     *
     * @param idx   A given index in the PageView. Index start from 0 to pageCount -1.
     * @param time  Scroll time must be >= 0. Otherwise last set scroll time will be used.
     */
    void scrollToPage(ssize_t idx, float time);

    /**
     * Scroll to a page with a given index.
     *
     * @param itemIndex   A given index in the PageView. Index start from 0 to pageCount -1.
     */
    void scrollToItem(ssize_t itemIndex);
    
    /**
     * Scroll to a item with a given index and with a given scroll time.
     *
     * @param idx   A given index in the PageView. Index start from 0 to pageCount -1.
     * @param time  Scroll time must be >= 0. Otherwise last set scrolltime will be used.
     */
    void scrollToItem(ssize_t idx, float time);

    /**
     * Gets current displayed page index.
     * @return current page index.
     */
    ssize_t getCurrentPageIndex();

    /**
     * Jump to a page with a given index without scrolling.
     * This is the different between scrollToPage.
     *
     * @param index A given index in PageView. Index start from 0 to pageCount -1.
     */
    void setCurrentPageIndex(ssize_t index);

    /**
     * @brief Add a page turn callback to PageView, then when one page is turning, the callback will be called.
     *
     * @param callback A page turning callback.
     */
    void addEventListener(const ccPageViewCallback& callback);
    using ScrollView::addEventListener;
    //override methods
    virtual std::string getDescription() const override;

    /**
     * @brief Toggle page indicator enabled.
     *
     * @param enabled True if enable page indicator, false otherwise.
     */
    void setIndicatorEnabled(bool enabled);

    /**
     * @brief Query page indicator state.
     *
     * @return True if page indicator is enabled, false otherwise.
     */
    bool getIndicatorEnabled() const { return _indicator != nullptr; }

    /**
     * @brief Set the page indicator's position using anchor point.
     *
     * @param positionAsAnchorPoint The position as anchor point.
     */
    void setIndicatorPositionAsAnchorPoint(const Vec2& positionAsAnchorPoint);

    /**
     * @brief Get the page indicator's position as anchor point.
     *
     * @return positionAsAnchorPoint
     */
    const Vec2& getIndicatorPositionAsAnchorPoint() const;

    /**
     * @brief Set the page indicator's position in page view.
     *
     * @param position The position in page view
     */
    void setIndicatorPosition(const Vec2& position);
    
    /**
     * @brief Get the page indicator's position.
     *
     * @return positionAsAnchorPoint
     */
    const Vec2& getIndicatorPosition() const;

    /**
     * @brief Set space between page indicator's index nodes.
     *
     * @param spaceBetweenIndexNodes Space between nodes in pixel.
     */
    void setIndicatorSpaceBetweenIndexNodes(float spaceBetweenIndexNodes);

    /**
     * @brief Get the space between page indicator's index nodes.
     *
     * @return spaceBetweenIndexNodes
     */
    float getIndicatorSpaceBetweenIndexNodes() const;

    /**
     * @brief Set color of page indicator's selected index.
     *
     * @param color New color for selected (current) index.
     */
    void setIndicatorSelectedIndexColor(const Color3B& color);

    /**
     * @brief Get the color of page indicator's selected index.
     *
     * @return color
     */
    const Color3B& getIndicatorSelectedIndexColor() const;

    /**
     * @brief Set color of page indicator's index nodes.
     *
     * @param color New indicator node color.
     */
    void setIndicatorIndexNodesColor(const Color3B& color);
    
    /**
     * @brief Get the color of page indicator's index nodes.
     *
     * @return color
     */
    const Color3B& getIndicatorIndexNodesColor() const;
    
    /**
     * @brief Set opacity of page indicator's selected index.
     *
     * @param color New opacity for selected (current) index.
     */
    void setIndicatorSelectedIndexOpacity(uint8_t opacity);
    
    /**
     * @brief Get the opacity of page indicator's selected index.
     *
     * @return opacity
     */
    uint8_t getIndicatorSelectedIndexOpacity() const;
    
    /**
     * @brief Set opacity of page indicator's index nodes.
     *
     * @param opacity New indicator node opacity.
     */
    void setIndicatorIndexNodesOpacity(uint8_t opacity);
    
    /**
     * @brief Get the opacity of page indicator's index nodes.
     *
     * @return opacity
     */
    uint8_t getIndicatorIndexNodesOpacity() const;
    
    /**
     * @brief Set scale of page indicator's index nodes.
     *
     * @param indexNodesScale Scale of index nodes.
     */
    void setIndicatorIndexNodesScale(float indexNodesScale);
    
    /**
     * sets texture for index nodes.
     *
     * @param fileName   File name of texture.
     * @param resType    @see TextureResType .
     */
    void setIndicatorIndexNodesTexture(const std::string& texName,Widget::TextureResType texType = Widget::TextureResType::LOCAL);
    
    /**
     * @brief Get scale of page indicator's index nodes.
     *
     * @return indexNodesScale
     */
    float getIndicatorIndexNodesScale() const;

    void setAutoScrollStopEpsilon(float epsilon);

CC_CONSTRUCTOR_ACCESS:
    virtual bool init() override;

    //override methods
    virtual void doLayout() override;

protected:
    void pageTurningEvent();
    virtual float getAutoScrollStopEpsilon() const override;

    virtual void remedyLayoutParameter(Widget* item)override;
    virtual void moveInnerContainer(const Vec2& deltaMove, bool canStartBounceBack) override;
    virtual void onItemListChanged() override;
    virtual void onSizeChanged() override;
    virtual void handleReleaseLogic(Touch *touch) override;
    virtual void handlePressLogic(Touch *touch) override;

    virtual Widget* createCloneInstance() override;
    virtual void copySpecialProperties(Widget* model) override;

    void refreshIndicatorPosition();

protected:
    PageViewIndicator* _indicator;
    Vec2 _indicatorPositionAsAnchorPoint;

    ssize_t _currentPageIndex;

    float _childFocusCancelOffset;

    ccPageViewCallback _eventCallback;
    float _autoScrollStopEpsilon;
    ssize_t _previousPageIndex;
    bool _isTouchBegin;
};

}
NS_CC_END
// end of ui group
/// @}

#endif /* defined(__PageView__) */
