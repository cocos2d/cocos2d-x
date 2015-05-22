/****************************************************************************
 Copyright (c) 2011-2012 cocos2d-x.org
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

/**
 * The PageView control of Cocos UI.
 * @class
 * @extends ccui.Layout
 * @exmaple
 * var pageView = new ccui.PageView();
 * pageView.setTouchEnabled(true);
 * pageView.addPage(new ccui.Layout());
 * this.addChild(pageView);
 */
ccui.PageView = ccui.Layout.extend(/** @lends ccui.PageView# */{
    _curPageIdx: 0,
    _pages: null,
    _touchMoveDirection: null,
    _touchStartLocation: 0,
    _touchMoveStartLocation: 0,
    _movePagePoint: null,
    _leftBoundaryChild: null,
    _rightBoundaryChild: null,
    _leftBoundary: 0,
    _rightBoundary: 0,

    _isAutoScrolling: false,
    _autoScrollDistance: 0,
    _autoScrollSpeed: 0,
    _autoScrollDirection: 0,

    _childFocusCancelOffset: 0,
    _pageViewEventListener: null,
    _pageViewEventSelector: null,
    _className:"PageView",
    //v3.2
    _customScrollThreshold: 0,
    _usingCustomScrollThreshold: false,

    /**
     * Allocates and initializes a UIPageView.
     * Constructor of ccui.PageView. please do not call this function by yourself, you should pass the parameters to constructor to initialize it .
     * @example
     * // example
     * var uiPageView = new ccui.PageView();
     */
    ctor: function () {
        ccui.Layout.prototype.ctor.call(this);
        this._pages = [];
        this._touchMoveDirection = ccui.PageView.TOUCH_DIR_LEFT;

        this._movePagePoint = null;
        this._leftBoundaryChild = null;
        this._rightBoundaryChild = null;

        this._childFocusCancelOffset = 5;
        this._pageViewEventListener = null;
        this._pageViewEventSelector = null;
        this.setTouchEnabled(true);
    },

    /**
     * Initializes a ccui.PageView. Please do not call this function by yourself, you should pass the parameters to constructor to initialize it.
     * @returns {boolean}
     */
    init: function () {
        if (ccui.Layout.prototype.init.call(this)) {
            this.setClippingEnabled(true);
            return true;
        }
        return false;
    },

    /**
     * Calls the parent class' onEnter and schedules update function.
     * @override
     */
    onEnter:function(){
        ccui.Layout.prototype.onEnter.call(this);
        this.scheduleUpdate(true);
    },

    /**
     * Add a widget to a page of PageView.
     * @param {ccui.Widget} widget widget to be added to PageView.
     * @param {number} pageIdx index of page.
     * @param {Boolean} forceCreate if force create and there is no page exist, PageView would create a default page for adding widget.
     */
    addWidgetToPage: function (widget, pageIdx, forceCreate) {
        if (!widget || pageIdx < 0)
            return;

        var pageCount = this._getPageCount();
        if (pageIdx < 0 || pageIdx >= pageCount) {
            if (forceCreate) {
                if (pageIdx > pageCount)
                    cc.log("pageIdx is %d, it will be added as page id [%d]", pageIdx, pageCount);
                var newPage = this._createPage();
                newPage.addChild(widget);
                this.addPage(newPage);
            }
        } else {
            var page = this._pages[pageIdx];
            if (page)
                page.addChild(widget);
        }
    },

    _createPage: function () {
        var newPage = new ccui.Layout();
        newPage.setContentSize(this.getContentSize());
        return newPage;
    },

    /**
     * Adds a page to ccui.PageView.
     * @param {ccui.Layout} page
     */
    addPage: function (page) {
        if (!page || this._pages.indexOf(page) !== -1)
            return;

        this.addChild(page);
        this._pages.push(page);
        this._doLayoutDirty = true;
    },

    /**
     * Inserts a page in the specified location.
     * @param {ccui.Layout} page page to be added to PageView.
     * @param {Number} idx index
     */
    insertPage: function (page, idx) {
        if (idx < 0 || !page || this._pages.indexOf(page) !== -1)
            return;

        var pageCount = this._getPageCount();
        if (idx >= pageCount)
            this.addPage(page);
        else {
            this._pages[idx] = page;
            this.addChild(page);
        }
        this._doLayoutDirty = true;
    },

    /**
     * Removes a page from PageView.
     * @param {ccui.Layout} page
     */
    removePage: function (page) {
        if (!page)
            return;
        this.removeChild(page);
        var index = this._pages.indexOf(page);
        if(index > -1)
            this._pages.splice(index, 1);
        this._doLayoutDirty = true;
    },

    /**
     * Removes a page at index of PageView.
     * @param {number} index
     */
    removePageAtIndex: function (index) {
        if (index < 0 || index >= this._pages.length)
            return;
        var page = this._pages[index];
        if (page)
            this.removePage(page);
    },

    /**
     * Removes all pages from PageView
     */
    removeAllPages: function(){
        var locPages = this._pages;
        for(var i = 0, len = locPages.length; i < len; i++)
            this.removeChild(locPages[i]);
        this._pages.length = 0;
    },

    _updateBoundaryPages: function () {
        var locPages = this._pages;
        if (locPages.length <= 0) {
            this._leftBoundaryChild = null;
            this._rightBoundaryChild = null;
            return;
        }
        this._leftBoundaryChild = locPages[0];
        this._rightBoundaryChild = locPages[locPages.length - 1];
    },

    _getPageCount: function(){
        return this._pages.length;
    },

    /**
     * Get x position by index
     * @param {number} idx
     * @returns {number}
     */
    _getPositionXByIndex: function (idx) {
        return (this.getContentSize().width * (idx - this._curPageIdx));
    },

    _onSizeChanged: function () {
        ccui.Layout.prototype._onSizeChanged.call(this);
        this._rightBoundary = this.getContentSize().width;
        this._doLayoutDirty = true;
    },

    _updateAllPagesSize: function(){
        var selfSize = this.getContentSize();
        var locPages = this._pages;
        for (var i = 0, len = locPages.length; i < len; i++)
            locPages[i].setContentSize(selfSize);
    },

    _updateAllPagesPosition: function(){
        var pageCount = this._getPageCount();
        if (pageCount <= 0) {
            this._curPageIdx = 0;
            return;
        }

        if (this._curPageIdx >= pageCount)
            this._curPageIdx = pageCount-1;

        var pageWidth = this.getContentSize().width;
        var locPages = this._pages;
        for (var i=0; i< pageCount; i++)
            locPages[i].setPosition(cc.p((i - this._curPageIdx) * pageWidth, 0));
    },

    /**
     * scroll PageView to index.
     * @param {number} idx index of page.
     */
    scrollToPage: function (idx) {
        if (idx < 0 || idx >= this._pages.length)
            return;
        this._curPageIdx = idx;
        var curPage = this._pages[idx];
        this._autoScrollDistance = -(curPage.getPosition().x);
        this._autoScrollSpeed = Math.abs(this._autoScrollDistance) / 0.2;
        this._autoScrollDirection = this._autoScrollDistance > 0 ? ccui.PageView.DIRECTION_RIGHT : ccui.PageView.DIRECTION_LEFT;
        this._isAutoScrolling = true;
    },

    /**
     * Called once per frame. Time is the number of seconds of a frame interval.
     * @override
     * @param {Number} dt
     */
    update: function (dt) {
        if (this._isAutoScrolling)
            this._autoScroll(dt);
    },

    /**
     * Does nothing. ccui.PageView's layout type is ccui.Layout.ABSOLUTE.
     * @override
     * @param {Number} type
     */
    setLayoutType:function(type){
    },

    /**
     * Returns the layout type of ccui.PageView. it's always ccui.Layout.ABSOLUTE.
     * @returns {number}
     */
    getLayoutType: function(){
        return ccui.Layout.ABSOLUTE;
    },

    _autoScroll: function(dt){
        var step;
        switch (this._autoScrollDirection) {
            case ccui.PageView.DIRECTION_LEFT:
                step = this._autoScrollSpeed * dt;
                if (this._autoScrollDistance + step >= 0.0) {
                    step = -this._autoScrollDistance;
                    this._autoScrollDistance = 0.0;
                    this._isAutoScrolling = false;
                } else
                    this._autoScrollDistance += step;
                this._scrollPages(-step);
                if(!this._isAutoScrolling)
                    this._pageTurningEvent();
                break;
                break;
            case ccui.PageView.DIRECTION_RIGHT:
                step = this._autoScrollSpeed * dt;
                if (this._autoScrollDistance - step <= 0.0) {
                    step = this._autoScrollDistance;
                    this._autoScrollDistance = 0.0;
                    this._isAutoScrolling = false;
                } else
                    this._autoScrollDistance -= step;
                this._scrollPages(step);
                if(!this._isAutoScrolling)
                    this._pageTurningEvent();
                break;
            default:
                break;
        }
    },

    /**
     * The touch moved event callback handler of ccui.PageView.
     * @override
     * @param {cc.Touch} touch
     * @param {cc.Event} event
     */
    onTouchMoved: function (touch, event) {
        ccui.Layout.prototype.onTouchMoved.call(this, touch, event);
        if (!this._isInterceptTouch)
            this._handleMoveLogic(touch);
    },

    /**
     * The touch ended event callback handler of ccui.PageView.
     * @override
     * @param {cc.Touch} touch
     * @param {cc.Event} event
     */
    onTouchEnded: function (touch, event) {
        ccui.Layout.prototype.onTouchEnded.call(this, touch, event);
        if (!this._isInterceptTouch)
            this._handleReleaseLogic(touch);
        this._isInterceptTouch = false;
    },

    /**
     * The touch canceled event callback handler of ccui.PageView.
     * @param {cc.Touch} touch
     * @param {cc.Event} event
     */
    onTouchCancelled: function (touch, event) {
        ccui.Layout.prototype.onTouchCancelled.call(this, touch, event);
        if (!this._isInterceptTouch)
            this._handleReleaseLogic(touch);
        this._isInterceptTouch = false;
    },

    _doLayout: function(){
        if (!this._doLayoutDirty)
            return;

        this._updateAllPagesPosition();
        this._updateAllPagesSize();
        this._updateBoundaryPages();
        this._doLayoutDirty = false;
    },

    _movePages: function (offset) {
        var arrayPages = this._pages;
        var length = arrayPages.length;
        for (var i = 0; i < length; i++) {
            var child = arrayPages[i];
            //var pos = child.getPosition();
            //child.setPosition(pos.x + offset, pos.y);
            child.setPositionX(child.getPositionX() + offset);
        }
    },

    _scrollPages: function (touchOffset) {
        if (this._pages.length <= 0)
            return false;
        if (!this._leftBoundaryChild || !this._rightBoundaryChild)
            return false;

        var realOffset = touchOffset;
        switch (this._touchMoveDirection) {
            case ccui.PageView.TOUCH_DIR_LEFT: // left
                var rightBoundary = this._rightBoundaryChild.getRightBoundary();
                if (rightBoundary + touchOffset <= this._rightBoundary) {
                    realOffset = this._rightBoundary - rightBoundary;
                    this._movePages(realOffset);
                    return false;
                }
                break;
            case ccui.PageView.TOUCH_DIR_RIGHT: // right
                var leftBoundary = this._leftBoundaryChild.getLeftBoundary();
                if (leftBoundary + touchOffset >= this._leftBoundary) {
                    realOffset = this._leftBoundary - leftBoundary;
                    this._movePages(realOffset);
                    return false;
                }
                break;
            default:
                break;
        }

        this._movePages(realOffset);
        return true;
    },

    _handleMoveLogic: function (touch) {
        var offset = touch.getLocation().x - touch.getPreviousLocation().x;
        if (offset < 0)
            this._touchMoveDirection = ccui.PageView.TOUCH_DIR_LEFT;
        else if (offset > 0)
            this._touchMoveDirection = ccui.PageView.TOUCH_DIR_RIGHT;
        this._scrollPages(offset);
    },

    /**
     * Set custom scroll threshold to page view. If you don't specify the value, the pageView will scroll when half page view width reached.
     * @since v3.2
     * @param threshold
     */
    setCustomScrollThreshold: function(threshold){
        cc.assert(threshold>0, "Invalid threshold!");
        this._customScrollThreshold = threshold;
        this.setUsingCustomScrollThreshold(true);
    },

    /**
     * Returns user defined scroll page threshold.
     * @since v3.2
     */
    getCustomScrollThreshold: function(){
        return this._customScrollThreshold;
    },

    /**
     * Set using user defined scroll page threshold or not. If you set it to false, then the default scroll threshold is pageView.width / 2.
     * @since v3.2
     */
    setUsingCustomScrollThreshold: function(flag){
        this._usingCustomScrollThreshold = flag;
    },

    /**
     * Queries whether we are using user defined scroll page threshold or not
     */
    isUsingCustomScrollThreshold: function(){
        return this._usingCustomScrollThreshold;
    },

    _handleReleaseLogic: function (touchPoint) {
        if (this._pages.length <= 0)
            return;
        var curPage = this._pages[this._curPageIdx];
        if (curPage) {
            var curPagePos = curPage.getPosition();
            var pageCount = this._pages.length;
            var curPageLocation = curPagePos.x;
            var pageWidth = this.getSize().width;
            if (!this._usingCustomScrollThreshold)
                this._customScrollThreshold = pageWidth / 2.0;
            var boundary = this._customScrollThreshold;
            if (curPageLocation <= -boundary) {
                if (this._curPageIdx >= pageCount - 1)
                    this._scrollPages(-curPageLocation);
                else
                    this.scrollToPage(this._curPageIdx + 1);
            } else if (curPageLocation >= boundary) {
                if (this._curPageIdx <= 0)
                    this._scrollPages(-curPageLocation);
                else
                    this.scrollToPage(this._curPageIdx - 1);
            } else
                this.scrollToPage(this._curPageIdx);
        }
    },

    /**
     * Intercept touch event, handle its child's touch event.
     * @param {Number} eventType event type
     * @param {ccui.Widget} sender
     * @param {cc.Touch} touch
     */
    interceptTouchEvent: function (eventType, sender, touch) {
        var touchPoint = touch.getLocation();
        switch (eventType) {
            case ccui.Widget.TOUCH_BEGAN:
                this._touchBeganPosition.x = touchPoint.x;
                this._touchBeganPosition.y = touchPoint.y;
                this._isInterceptTouch = true;
                break;
            case ccui.Widget.TOUCH_MOVED:
                this._touchMovePosition.x = touchPoint.x;
                this._touchMovePosition.y = touchPoint.y;
                var offset = 0;
                offset = Math.abs(sender.getTouchBeganPosition().x - touchPoint.x);
                if (offset > this._childFocusCancelOffset) {
                    sender.setHighlighted(false);
                    this._handleMoveLogic(touch);
                }
                break;
            case ccui.Widget.TOUCH_ENDED:
            case ccui.Widget.TOUCH_CANCELED:
                this._touchEndPosition.x = touchPoint.x;
                this._touchEndPosition.y = touchPoint.y;
                this._handleReleaseLogic(touch);
                if (sender.isSwallowTouches())
                    this._isInterceptTouch = false;
                break;
        }
    },

    _pageTurningEvent: function () {
        if(this._pageViewEventSelector){
            if (this._pageViewEventListener)
                this._pageViewEventSelector.call(this._pageViewEventListener, this, ccui.PageView.EVENT_TURNING);
            else
                this._pageViewEventSelector(this, ccui.PageView.EVENT_TURNING);
        }
        if(this._ccEventCallback)
            this._ccEventCallback(this, ccui.PageView.EVENT_TURNING);
    },

    /**
     * Adds event listener to ccui.PageView.
     * @param {Function} selector
     * @param {Object} [target=]
     * @deprecated since v3.0, please use addEventListener instead.
     */
    addEventListenerPageView: function (selector, target) {
        this.addEventListener(selector, target);
    },

    /**
     * Adds event listener to ccui.PageView.
     * @param {Function} selector
     * @param {Object} [target=]
     */
    addEventListener: function(selector, target){
        this._pageViewEventSelector = selector;
        this._pageViewEventListener = target;
    },

    /**
     * Returns current page index
     * @returns {number}
     */
    getCurPageIndex: function () {
        return this._curPageIdx;
    },

    /**
     * Returns all pages of PageView
     * @returns {Array}
     */
    getPages:function(){
        return this._pages;
    },

    /**
     * Returns a page from PageView by index
     * @param {Number} index
     * @returns {ccui.Layout}
     */
    getPage: function(index){
        if (index < 0 || index >= this._pages.length)
            return null;
        return this._pages[index];
    },

    /**
     * Returns the "class name" of ccui.PageView.
     * @returns {string}
     */
    getDescription: function () {
        return "PageView";
    },

    _createCloneInstance: function () {
        return new ccui.PageView();
    },

    _copyClonedWidgetChildren: function (model) {
        var arrayPages = model.getPages();
        for (var i = 0; i < arrayPages.length; i++) {
            var page = arrayPages[i];
            this.addPage(page.clone());
        }
    },

    _copySpecialProperties: function (pageView) {
        ccui.Layout.prototype._copySpecialProperties.call(this, pageView);
        this._ccEventCallback = pageView._ccEventCallback;
        this._pageViewEventListener = pageView._pageViewEventListener;
        this._pageViewEventSelector = pageView._pageViewEventSelector;
        this._usingCustomScrollThreshold = pageView._usingCustomScrollThreshold;
        this._customScrollThreshold = pageView._customScrollThreshold;
    }
});
/**
 * allocates and initializes a UIPageView.
 * @deprecated since v3.0, please use new ccui.PageView() instead.
 * @return {ccui.PageView}
 */
ccui.PageView.create = function () {
    return new ccui.PageView();
};

// Constants
//PageView event
/**
 * The turning flag of ccui.PageView's event.
 * @constant
 * @type {number}
 */
ccui.PageView.EVENT_TURNING = 0;

//PageView touch direction
/**
 * The left flag of ccui.PageView's touch direction.
 * @constant
 * @type {number}
 */
ccui.PageView.TOUCH_DIR_LEFT = 0;
/**
 * The right flag of ccui.PageView's touch direction.
 * @constant
 * @type {number}
 */
ccui.PageView.TOUCH_DIR_RIGHT = 1;

//PageView auto scroll direction
/**
 * The right flag of ccui.PageView's auto scroll direction.
 * @constant
 * @type {number}
 */
ccui.PageView.DIRECTION_LEFT = 0;
/**
 * The right flag of ccui.PageView's auto scroll direction.
 * @constant
 * @type {number}
 */
ccui.PageView.DIRECTION_RIGHT = 1;
