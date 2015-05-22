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
 * The ScrollView control of Cocos UI
 * @class
 * @extends ccui.Layout
 *
 * @property {Number}               innerWidth              - Inner container width of the scroll view
 * @property {Number}               innerHeight             - Inner container height of the scroll view
 * @property {ccui.ScrollView.DIR_NONE | ccui.ScrollView.DIR_VERTICAL | ccui.ScrollView.DIR_HORIZONTAL | ccui.ScrollView.DIR_BOTH}    direction               - Scroll direction of the scroll view
 * @property {Boolean}              bounceEnabled           - Indicate whether bounce is enabled
 * @property {Boolean}              inertiaScrollEnabled    - Indicate whether inertiaScroll is enabled
 */
ccui.ScrollView = ccui.Layout.extend(/** @lends ccui.ScrollView# */{
    _innerContainer: null,
    direction: null,
    _autoScrollDir: null,

    _topBoundary: 0,
    _bottomBoundary: 0,
    _leftBoundary: 0,
    _rightBoundary: 0,

    _bounceTopBoundary: 0,
    _bounceBottomBoundary: 0,
    _bounceLeftBoundary: 0,
    _bounceRightBoundary: 0,

    _autoScroll: false,
    _autoScrollAddUpTime: 0,

    _autoScrollOriginalSpeed: 0,
    _autoScrollAcceleration: 0,
    _isAutoScrollSpeedAttenuated: false,
    _needCheckAutoScrollDestination: false,
    _autoScrollDestination: null,

    _bePressed: false,
    _slidTime: 0,
    _moveChildPoint: null,
    _childFocusCancelOffset: 0,

    _leftBounceNeeded: false,
    _topBounceNeeded: false,
    _rightBounceNeeded: false,
    _bottomBounceNeeded: false,

    bounceEnabled: false,
    _bouncing: false,
    _bounceDir: null,
    _bounceOriginalSpeed: 0,
    inertiaScrollEnabled: false,

    _scrollViewEventListener: null,
    _scrollViewEventSelector: null,
    _className: "ScrollView",

    /**
     * Allocates and initializes a UIScrollView.
     * Constructor of ccui.ScrollView. override it to extend the construction behavior, remember to call "this._super()" in the extended "ctor" function.
     * @example
     * // example
     * var uiScrollView = new ccui.ScrollView();
     */
    ctor: function () {
        ccui.Layout.prototype.ctor.call(this);
        this.direction = ccui.ScrollView.DIR_NONE;
        this._autoScrollDir = cc.p(0, 0);

        this._autoScrollAcceleration = -1000;
        this._autoScrollDestination = cc.p(0, 0);
        this._slidTime = 0;
        this._moveChildPoint = cc.p(0, 0);
        this._childFocusCancelOffset = 5;
        this._bounceDir = cc.p(0, 0);
        this._bounceOriginalSpeed = 0;
        this.inertiaScrollEnabled = true;
        this.setTouchEnabled(true);
    },

    /**
     * Initializes a ccui.ScrollView. Please do not call this function by yourself, you should pass the parameters to constructor to initialize it.
     * @returns {boolean}
     */
    init: function () {
        if (ccui.Layout.prototype.init.call(this)) {
            this.setClippingEnabled(true);
            this._innerContainer.setTouchEnabled(false);
            return true;
        }
        return false;
    },

    /**
     * Calls the parent class' onEnter and schedules update function.
     * @override
     */
    onEnter: function () {
        ccui.Layout.prototype.onEnter.call(this);
        this.scheduleUpdate(true);
    },

    /**
     * When a widget is in a layout, you could call this method to get the next focused widget within a specified direction.             <br/>
     * If the widget is not in a layout, it will return itself
     *
     * @param {Number} direction the direction to look for the next focused widget in a layout
     * @param {ccui.Widget} current the current focused widget
     * @returns {ccui.Widget}
     */
    findNextFocusedWidget: function(direction, current){
        if (this.getLayoutType() === ccui.Layout.LINEAR_VERTICAL
            || this.getLayoutType() === ccui.Layout.LINEAR_HORIZONTAL) {
            return this._innerContainer.findNextFocusedWidget(direction, current);
        } else
            return ccui.Widget.prototype.findNextFocusedWidget.call(this, direction, current);
    },

    _initRenderer: function () {
        ccui.Layout.prototype._initRenderer.call(this);

        this._innerContainer = new ccui.Layout();
        this._innerContainer.setColor(cc.color(255,255,255));
        this._innerContainer.setOpacity(255);
        this._innerContainer.setCascadeColorEnabled(true);
        this._innerContainer.setCascadeOpacityEnabled(true);

        this.addProtectedChild(this._innerContainer, 1, 1);
    },

    _onSizeChanged: function () {
        ccui.Layout.prototype._onSizeChanged.call(this);
        var locSize = this._contentSize;
        this._topBoundary = locSize.height;
        this._rightBoundary = locSize.width;
        var bounceBoundaryParameterX = locSize.width / 3;
        var bounceBoundaryParameterY = locSize.height / 3;
        this._bounceTopBoundary = locSize.height - bounceBoundaryParameterY;
        this._bounceBottomBoundary = bounceBoundaryParameterY;
        this._bounceLeftBoundary = bounceBoundaryParameterX;
        this._bounceRightBoundary = locSize.width - bounceBoundaryParameterX;
        var innerSize = this._innerContainer.getContentSize();
        this._innerContainer.setContentSize(cc.size(Math.max(innerSize.width, locSize.width), Math.max(innerSize.height, locSize.height)));
        this._innerContainer.setPosition(0, locSize.height - this._innerContainer.getContentSize().height);
    },

    /**
     * Changes inner container size of ScrollView.     <br/>
     * Inner container size must be larger than or equal the size of ScrollView.
     * @param {cc.Size} size inner container size.
     */
    setInnerContainerSize: function (size) {
        var innerContainer = this._innerContainer;
        var locSize = this._contentSize;
        var innerSizeWidth = locSize.width, innerSizeHeight = locSize.height;
        var originalInnerSize = innerContainer.getContentSize();
        if (size.width < locSize.width)
            cc.log("Inner width <= ScrollView width, it will be force sized!");
        else
            innerSizeWidth = size.width;

        if (size.height < locSize.height)
            cc.log("Inner height <= ScrollView height, it will be force sized!");
        else
            innerSizeHeight = size.height;

        innerContainer.setContentSize(cc.size(innerSizeWidth, innerSizeHeight));
        var newInnerSize, offset;
        switch (this.direction) {
            case ccui.ScrollView.DIR_VERTICAL:
                newInnerSize = innerContainer.getContentSize();
                offset = originalInnerSize.height - newInnerSize.height;
                this._scrollChildren(0, offset);
                break;
            case ccui.ScrollView.DIR_HORIZONTAL:
                if (innerContainer.getRightBoundary() <= locSize.width) {
                    newInnerSize = innerContainer.getContentSize();
                    offset = originalInnerSize.width - newInnerSize.width;
                    this._scrollChildren(offset, 0);
                }
                break;
            case ccui.ScrollView.DIR_BOTH:
                newInnerSize = innerContainer.getContentSize();
                var offsetY = originalInnerSize.height - newInnerSize.height;
                var offsetX = (innerContainer.getRightBoundary() <= locSize.width) ? originalInnerSize.width - newInnerSize.width : 0;
                this._scrollChildren(offsetX, offsetY);
                break;
            default:
                break;
        }

        var innerSize = innerContainer.getContentSize();
        var innerPos = innerContainer.getPosition();
        var innerAP = innerContainer.getAnchorPoint();
        if (innerContainer.getLeftBoundary() > 0.0)
            innerContainer.setPosition(innerAP.x * innerSize.width, innerPos.y);
        if (innerContainer.getRightBoundary() < locSize.width)
            innerContainer.setPosition(locSize.width - ((1.0 - innerAP.x) * innerSize.width), innerPos.y);
        if (innerPos.y > 0.0)
            innerContainer.setPosition(innerPos.x, innerAP.y * innerSize.height);
        if (innerContainer.getTopBoundary() < locSize.height)
            innerContainer.setPosition(innerPos.x, locSize.height - (1.0 - innerAP.y) * innerSize.height);
    },

    _setInnerWidth: function (width) {
        var locW = this._contentSize.width,
            innerWidth = locW,
            container = this._innerContainer,
            oldInnerWidth = container.width;
        if (width < locW)
            cc.log("Inner width <= scrollview width, it will be force sized!");
        else
            innerWidth = width;
        container.width = innerWidth;

        switch (this.direction) {
            case ccui.ScrollView.DIR_HORIZONTAL:
            case ccui.ScrollView.DIR_BOTH:
                if (container.getRightBoundary() <= locW) {
                    var newInnerWidth = container.width;
                    var offset = oldInnerWidth - newInnerWidth;
                    this._scrollChildren(offset, 0);
                }
                break;
        }
        var innerAX = container.anchorX;
        if (container.getLeftBoundary() > 0.0)
            container.x = innerAX * innerWidth;
        if (container.getRightBoundary() < locW)
            container.x = locW - ((1.0 - innerAX) * innerWidth);
    },

    _setInnerHeight: function (height) {
        var locH = this._contentSize.height,
            innerHeight = locH,
            container = this._innerContainer,
            oldInnerHeight = container.height;
        if (height < locH)
            cc.log("Inner height <= scrollview height, it will be force sized!");
        else
            innerHeight = height;
        container.height = innerHeight;

        switch (this.direction) {
            case ccui.ScrollView.DIR_VERTICAL:
            case ccui.ScrollView.DIR_BOTH:
                var newInnerHeight = innerHeight;
                var offset = oldInnerHeight - newInnerHeight;
                this._scrollChildren(0, offset);
                break;
        }
        var innerAY = container.anchorY;
        if (container.getLeftBoundary() > 0.0)
            container.y = innerAY * innerHeight;
        if (container.getRightBoundary() < locH)
            container.y = locH - ((1.0 - innerAY) * innerHeight);
    },

    /**
     * Returns inner container size of ScrollView.     <br/>
     * Inner container size must be larger than or equal ScrollView's size.
     *
     * @return {cc.Size} inner container size.
     */
    getInnerContainerSize: function () {
        return this._innerContainer.getContentSize();
    },
    _getInnerWidth: function () {
        return this._innerContainer.width;
    },
    _getInnerHeight: function () {
        return this._innerContainer.height;
    },

    /**
     * Add child to ccui.ScrollView.
     * @param {cc.Node} widget
     * @param {Number} [zOrder]
     * @param {Number|string} [tag] tag or name
     * @returns {boolean}
     */
    addChild: function (widget, zOrder, tag) {
        if(!widget)
            return false;
        zOrder = zOrder || widget.getLocalZOrder();
        tag = tag || widget.getTag();
        return this._innerContainer.addChild(widget, zOrder, tag);
    },

    /**
     * Removes all children.
     */
    removeAllChildren: function () {
        this.removeAllChildrenWithCleanup(true);
    },

    /**
     * Removes all children.
     * @param {Boolean} cleanup
     */
    removeAllChildrenWithCleanup: function(cleanup){
        this._innerContainer.removeAllChildrenWithCleanup(cleanup);
    },

    /**
     * Removes widget child
     * @override
     * @param {ccui.Widget} child
     * @param {Boolean} cleanup
     * @returns {boolean}
     */
    removeChild: function (child, cleanup) {
        return this._innerContainer.removeChild(child, cleanup);
    },

    /**
     * Returns inner container's children
     * @returns {Array}
     */
    getChildren: function () {
        return this._innerContainer.getChildren();
    },

    /**
     * Gets the count of inner container's children
     * @returns {Number}
     */
    getChildrenCount: function () {
        return this._innerContainer.getChildrenCount();
    },

    /**
     * Gets a child from the container given its tag
     * @param {Number} tag
     * @returns {ccui.Widget}
     */
    getChildByTag: function (tag) {
        return this._innerContainer.getChildByTag(tag);
    },

    /**
     * Gets a child from the container given its name
     * @param {String} name
     * @returns {ccui.Widget}
     */
    getChildByName: function (name) {
        return this._innerContainer.getChildByName(name);
    },

    _moveChildren: function (offsetX, offsetY) {
        var locContainer = this._innerContainer;
        //var pos = this._innerContainer.getPosition();
        this._moveChildPoint.x = locContainer.x + offsetX;
        this._moveChildPoint.y = locContainer.y + offsetY;
        this._innerContainer.setPosition(this._moveChildPoint);
    },

    _autoScrollChildren: function (dt) {
        var lastTime = this._autoScrollAddUpTime;
        this._autoScrollAddUpTime += dt;
        if (this._isAutoScrollSpeedAttenuated) {
            var nowSpeed = this._autoScrollOriginalSpeed + this._autoScrollAcceleration * this._autoScrollAddUpTime;
            if (nowSpeed <= 0) {
                this._stopAutoScrollChildren();
                this._checkNeedBounce();
            } else {
                var timeParam = lastTime * 2 + dt;
                var offset = (this._autoScrollOriginalSpeed + this._autoScrollAcceleration * timeParam * 0.5) * dt;
                var offsetX = offset * this._autoScrollDir.x;
                var offsetY = offset * this._autoScrollDir.y;
                if (!this._scrollChildren(offsetX, offsetY)) {
                    this._stopAutoScrollChildren();
                    this._checkNeedBounce();
                }
            }
        } else {
            if (this._needCheckAutoScrollDestination) {
                var xOffset = this._autoScrollDir.x * dt * this._autoScrollOriginalSpeed;
                var yOffset = this._autoScrollDir.y * dt * this._autoScrollOriginalSpeed;
                var notDone = this._checkCustomScrollDestination(xOffset, yOffset);
                var scrollCheck = this._scrollChildren(xOffset, yOffset);
                if (!notDone || !scrollCheck) {
                    this._stopAutoScrollChildren();
                    this._checkNeedBounce();
                }
            } else {
                if (!this._scrollChildren(this._autoScrollDir.x * dt * this._autoScrollOriginalSpeed,
                        this._autoScrollDir.y * dt * this._autoScrollOriginalSpeed)) {
                    this._stopAutoScrollChildren();
                    this._checkNeedBounce();
                }
            }
        }
    },

    _bounceChildren: function (dt) {
        var locSpeed = this._bounceOriginalSpeed;
        var locBounceDir = this._bounceDir;
        if (locSpeed <= 0.0)
            this._stopBounceChildren();
        if (!this._bounceScrollChildren(locBounceDir.x * dt * locSpeed, locBounceDir.y * dt * locSpeed))
            this._stopBounceChildren();
    },

    _checkNeedBounce: function () {
        if (!this.bounceEnabled)
            return false;
        this._checkBounceBoundary();
        var locTopBounceNeeded = this._topBounceNeeded, locBottomBounceNeeded = this._bottomBounceNeeded,
            locLeftBounceNeeded = this._leftBounceNeeded, locRightBounceNeeded = this._rightBounceNeeded;

        if (locTopBounceNeeded || locBottomBounceNeeded || locLeftBounceNeeded || locRightBounceNeeded) {
            var scrollVector, orSpeed;
            var locContentSize = this._contentSize, locInnerContainer = this._innerContainer;
            if (locTopBounceNeeded && locLeftBounceNeeded) {
                scrollVector = cc.pSub(cc.p(0.0, locContentSize.height), cc.p(locInnerContainer.getLeftBoundary(), locInnerContainer.getTopBoundary()));
                orSpeed = cc.pLength(scrollVector) / 0.2;
                this._bounceDir = cc.pNormalize(scrollVector);
                this._startBounceChildren(orSpeed);
            } else if (locTopBounceNeeded && locRightBounceNeeded) {
                scrollVector = cc.pSub(cc.p(locContentSize.width, locContentSize.height), cc.p(locInnerContainer.getRightBoundary(), locInnerContainer.getTopBoundary()));
                orSpeed = cc.pLength(scrollVector) / 0.2;
                this._bounceDir = cc.pNormalize(scrollVector);
                this._startBounceChildren(orSpeed);
            } else if (locBottomBounceNeeded && locLeftBounceNeeded) {
                scrollVector = cc.pSub(cc.p(0, 0), cc.p(locInnerContainer.getLeftBoundary(), locInnerContainer.getBottomBoundary()));
                orSpeed = cc.pLength(scrollVector) / 0.2;
                this._bounceDir = cc.pNormalize(scrollVector);
                this._startBounceChildren(orSpeed);
            } else if (locBottomBounceNeeded && locRightBounceNeeded) {
                scrollVector = cc.pSub(cc.p(locContentSize.width, 0.0), cc.p(locInnerContainer.getRightBoundary(), locInnerContainer.getBottomBoundary()));
                orSpeed = cc.pLength(scrollVector) / 0.2;
                this._bounceDir = cc.pNormalize(scrollVector);
                this._startBounceChildren(orSpeed);
            } else if (locTopBounceNeeded) {
                scrollVector = cc.pSub(cc.p(0, locContentSize.height), cc.p(0.0, locInnerContainer.getTopBoundary()));
                orSpeed = cc.pLength(scrollVector) / 0.2;
                this._bounceDir = cc.pNormalize(scrollVector);
                this._startBounceChildren(orSpeed);
            } else if (locBottomBounceNeeded) {
                scrollVector = cc.pSub(cc.p(0, 0), cc.p(0.0, locInnerContainer.getBottomBoundary()));
                orSpeed = cc.pLength(scrollVector) / 0.2;
                this._bounceDir = cc.pNormalize(scrollVector);
                this._startBounceChildren(orSpeed);
            } else if (locLeftBounceNeeded) {
                scrollVector = cc.pSub(cc.p(0, 0), cc.p(locInnerContainer.getLeftBoundary(), 0.0));
                orSpeed = cc.pLength(scrollVector) / 0.2;
                this._bounceDir = cc.pNormalize(scrollVector);
                this._startBounceChildren(orSpeed);
            } else if (locRightBounceNeeded) {
                scrollVector = cc.pSub(cc.p(locContentSize.width, 0), cc.p(locInnerContainer.getRightBoundary(), 0.0));
                orSpeed = cc.pLength(scrollVector) / 0.2;
                this._bounceDir = cc.pNormalize(scrollVector);
                this._startBounceChildren(orSpeed);
            }
            return true;
        }
        return false;
    },

    _checkBounceBoundary: function () {
        var locContainer = this._innerContainer;
        var icBottomPos = locContainer.getBottomBoundary();
        if (icBottomPos > this._bottomBoundary) {
            this._scrollToBottomEvent();
            this._bottomBounceNeeded = true;
        } else
            this._bottomBounceNeeded = false;

        var icTopPos = locContainer.getTopBoundary();
        if (icTopPos < this._topBoundary) {
            this._scrollToTopEvent();
            this._topBounceNeeded = true;
        } else
            this._topBounceNeeded = false;

        var icRightPos = locContainer.getRightBoundary();
        if (icRightPos < this._rightBoundary) {
            this._scrollToRightEvent();
            this._rightBounceNeeded = true;
        } else
            this._rightBounceNeeded = false;

        var icLeftPos = locContainer.getLeftBoundary();
        if (icLeftPos > this._leftBoundary) {
            this._scrollToLeftEvent();
            this._leftBounceNeeded = true;
        } else
            this._leftBounceNeeded = false;
    },

    _startBounceChildren: function (v) {
        this._bounceOriginalSpeed = v;
        this._bouncing = true;
    },

    _stopBounceChildren: function () {
        this._bouncing = false;
        this._bounceOriginalSpeed = 0.0;
        this._leftBounceNeeded = false;
        this._rightBounceNeeded = false;
        this._topBounceNeeded = false;
        this._bottomBounceNeeded = false;
    },

    _startAutoScrollChildrenWithOriginalSpeed: function (dir, v, attenuated, acceleration) {
        this._stopAutoScrollChildren();
        this._autoScrollDir.x = dir.x;
        this._autoScrollDir.y = dir.y;
        this._isAutoScrollSpeedAttenuated = attenuated;
        this._autoScrollOriginalSpeed = v;
        this._autoScroll = true;
        this._autoScrollAcceleration = acceleration;
    },

    _startAutoScrollChildrenWithDestination: function (des, time, attenuated) {
        this._needCheckAutoScrollDestination = false;
        this._autoScrollDestination = des;
        var dis = cc.pSub(des, this._innerContainer.getPosition());
        var dir = cc.pNormalize(dis);
        var orSpeed = 0.0;
        var acceleration = -1000.0;
        var disLength = cc.pLength(dis);
        if (attenuated) {
            acceleration = -(2 * disLength) / (time * time);
            orSpeed = 2 * disLength / time;
        } else {
            this._needCheckAutoScrollDestination = true;
            orSpeed = disLength / time;
        }
        this._startAutoScrollChildrenWithOriginalSpeed(dir, orSpeed, attenuated, acceleration);
    },

    _jumpToDestination: function (dstX, dstY) {
        if (dstX.x !== undefined) {
            dstY = dstX.y;
            dstX = dstX.x;
        }
        var finalOffsetX = dstX;
        var finalOffsetY = dstY;
        switch (this.direction) {
            case ccui.ScrollView.DIR_VERTICAL:
                if (dstY <= 0)
                    finalOffsetY = Math.max(dstY, this._contentSize.height - this._innerContainer.getContentSize().height);
                break;
            case ccui.ScrollView.DIR_HORIZONTAL:
                if (dstX <= 0)
                    finalOffsetX = Math.max(dstX, this._contentSize.width - this._innerContainer.getContentSize().width);
                break;
            case ccui.ScrollView.DIR_BOTH:
                if (dstY <= 0)
                    finalOffsetY = Math.max(dstY, this._contentSize.height - this._innerContainer.getContentSize().height);
                if (dstX <= 0)
                    finalOffsetX = Math.max(dstX, this._contentSize.width - this._innerContainer.getContentSize().width);
                break;
            default:
                break;
        }
        this._innerContainer.setPosition(finalOffsetX, finalOffsetY);
    },

    _stopAutoScrollChildren: function () {
        this._autoScroll = false;
        this._autoScrollOriginalSpeed = 0;
        this._autoScrollAddUpTime = 0;
    },

    _bounceScrollChildren: function (touchOffsetX, touchOffsetY) {
        var scrollEnabled = true;
        var realOffsetX, realOffsetY, icRightPos, icTopPos, icBottomPos;
        var locContainer = this._innerContainer;
        if (touchOffsetX > 0.0 && touchOffsetY > 0.0){              //first quadrant //bounce to top-right
            realOffsetX = touchOffsetX;
            realOffsetY = touchOffsetY;
            icRightPos = locContainer.getRightBoundary();
            if (icRightPos + realOffsetX >= this._rightBoundary) {
                realOffsetX = this._rightBoundary - icRightPos;
                this._bounceRightEvent();
                scrollEnabled = false;
            }
            icTopPos = locContainer.getTopBoundary();
            if (icTopPos + touchOffsetY >= this._topBoundary) {
                realOffsetY = this._topBoundary - icTopPos;
                this._bounceTopEvent();
                scrollEnabled = false;
            }
            this._moveChildren(realOffsetX, realOffsetY);
        } else if (touchOffsetX < 0.0 && touchOffsetY > 0.0){       //second quadrant //bounce to top-left
            realOffsetX = touchOffsetX;
            realOffsetY = touchOffsetY;
            icLefrPos = locContainer.getLeftBoundary();
            if (icLefrPos + realOffsetX <= this._leftBoundary) {
                realOffsetX = this._leftBoundary - icLefrPos;
                this._bounceLeftEvent();
                scrollEnabled = false;
            }
            icTopPos = locContainer.getTopBoundary();
            if (icTopPos + touchOffsetY >= this._topBoundary) {
                realOffsetY = this._topBoundary - icTopPos;
                this._bounceTopEvent();
                scrollEnabled = false;
            }
            this._moveChildren(realOffsetX, realOffsetY);
        }else if (touchOffsetX < 0.0 && touchOffsetY < 0.0){ //third quadrant //bounce to bottom-left
            realOffsetX = touchOffsetX;
            realOffsetY = touchOffsetY;
            var icLefrPos = locContainer.getLeftBoundary();
            if (icLefrPos + realOffsetX <= this._leftBoundary) {
                realOffsetX = this._leftBoundary - icLefrPos;
                this._bounceLeftEvent();
                scrollEnabled = false;
            }
            icBottomPos = locContainer.getBottomBoundary();
            if (icBottomPos + touchOffsetY <= this._bottomBoundary) {
                realOffsetY = this._bottomBoundary - icBottomPos;
                this._bounceBottomEvent();
                scrollEnabled = false;
            }
            this._moveChildren(realOffsetX, realOffsetY);
        } else if (touchOffsetX > 0.0 && touchOffsetY < 0.0){ //forth quadrant //bounce to bottom-right
            realOffsetX = touchOffsetX;
            realOffsetY = touchOffsetY;
            icRightPos = locContainer.getRightBoundary();
            if (icRightPos + realOffsetX >= this._rightBoundary) {
                realOffsetX = this._rightBoundary - icRightPos;
                this._bounceRightEvent();
                scrollEnabled = false;
            }
            icBottomPos = locContainer.getBottomBoundary();
            if (icBottomPos + touchOffsetY <= this._bottomBoundary) {
                realOffsetY = this._bottomBoundary - icBottomPos;
                this._bounceBottomEvent();
                scrollEnabled = false;
            }
            this._moveChildren(realOffsetX, realOffsetY);
        } else if (touchOffsetX === 0.0 && touchOffsetY > 0.0){ // bounce to top
            realOffsetY = touchOffsetY;
            icTopPos = locContainer.getTopBoundary();
            if (icTopPos + touchOffsetY >= this._topBoundary) {
                realOffsetY = this._topBoundary - icTopPos;
                this._bounceTopEvent();
                scrollEnabled = false;
            }
            this._moveChildren(0.0, realOffsetY);
        } else if (touchOffsetX === 0.0 && touchOffsetY < 0.0) {//bounce to bottom
            realOffsetY = touchOffsetY;
            icBottomPos = locContainer.getBottomBoundary();
            if (icBottomPos + touchOffsetY <= this._bottomBoundary) {
                realOffsetY = this._bottomBoundary - icBottomPos;
                this._bounceBottomEvent();
                scrollEnabled = false;
            }
            this._moveChildren(0.0, realOffsetY);
        } else if (touchOffsetX > 0.0 && touchOffsetY === 0.0){ //bounce to right
            realOffsetX = touchOffsetX;
            icRightPos = locContainer.getRightBoundary();
            if (icRightPos + realOffsetX >= this._rightBoundary) {
                realOffsetX = this._rightBoundary - icRightPos;
                this._bounceRightEvent();
                scrollEnabled = false;
            }
            this._moveChildren(realOffsetX, 0.0);
        }else if (touchOffsetX < 0.0 && touchOffsetY === 0.0){ //bounce to left
            realOffsetX = touchOffsetX;
            var icLeftPos = locContainer.getLeftBoundary();
            if (icLeftPos + realOffsetX <= this._leftBoundary) {
                realOffsetX = this._leftBoundary - icLeftPos;
                this._bounceLeftEvent();
                scrollEnabled = false;
            }
            this._moveChildren(realOffsetX, 0.0);
        }
        return scrollEnabled;
    },

    _checkCustomScrollDestination: function (touchOffsetX, touchOffsetY) {
        var scrollEnabled = true;
        var icBottomPos, icLeftPos, icRightPos, icTopPos;
        var locContainer = this._innerContainer, locDestination = this._autoScrollDestination;
        switch (this.direction) {
            case ccui.ScrollView.DIR_VERTICAL:
                if (this._autoScrollDir.y > 0) {
                    icBottomPos = locContainer.getBottomBoundary();
                    if (icBottomPos + touchOffsetY >= locDestination.y) {
                        touchOffsetY = locDestination.y - icBottomPos;
                        scrollEnabled = false;
                    }
                } else {
                    icBottomPos = locContainer.getBottomBoundary();
                    if (icBottomPos + touchOffsetY <= locDestination.y) {
                        touchOffsetY = locDestination.y - icBottomPos;
                        scrollEnabled = false;
                    }
                }
                break;
            case ccui.ScrollView.DIR_HORIZONTAL:
                if (this._autoScrollDir.x > 0) {
                    icLeftPos = locContainer.getLeftBoundary();
                    if (icLeftPos + touchOffsetX >= locDestination.x) {
                        touchOffsetX = locDestination.x - icLeftPos;
                        scrollEnabled = false;
                    }
                } else {
                    icLeftPos = locContainer.getLeftBoundary();
                    if (icLeftPos + touchOffsetX <= locDestination.x) {
                        touchOffsetX = locDestination.x - icLeftPos;
                        scrollEnabled = false;
                    }
                }
                break;
            case ccui.ScrollView.DIR_BOTH:
                if (touchOffsetX > 0.0 && touchOffsetY > 0.0){ // up right
                    icLeftPos = locContainer.getLeftBoundary();
                    if (icLeftPos + touchOffsetX >= locDestination.x) {
                        touchOffsetX = locDestination.x - icLeftPos;
                        scrollEnabled = false;
                    }
                    icBottomPos = locContainer.getBottomBoundary();
                    if (icBottomPos + touchOffsetY >= locDestination.y) {
                        touchOffsetY = locDestination.y - icBottomPos;
                        scrollEnabled = false;
                    }
                } else if (touchOffsetX < 0.0 && touchOffsetY > 0.0){ // up left
                    icRightPos = locContainer.getRightBoundary();
                    if (icRightPos + touchOffsetX <= locDestination.x) {
                        touchOffsetX = locDestination.x - icRightPos;
                        scrollEnabled = false;
                    }
                    icBottomPos = locContainer.getBottomBoundary();
                    if (icBottomPos + touchOffsetY >= locDestination.y) {
                        touchOffsetY = locDestination.y - icBottomPos;
                        scrollEnabled = false;
                    }
                } else if (touchOffsetX < 0.0 && touchOffsetY < 0.0){ // down left
                    icRightPos = locContainer.getRightBoundary();
                    if (icRightPos + touchOffsetX <= locDestination.x) {
                        touchOffsetX = locDestination.x - icRightPos;
                        scrollEnabled = false;
                    }
                    icTopPos = locContainer.getTopBoundary();
                    if (icTopPos + touchOffsetY <= locDestination.y) {
                        touchOffsetY = locDestination.y - icTopPos;
                        scrollEnabled = false;
                    }
                } else if (touchOffsetX > 0.0 && touchOffsetY < 0.0){ // down right
                    icLeftPos = locContainer.getLeftBoundary();
                    if (icLeftPos + touchOffsetX >= locDestination.x) {
                        touchOffsetX = locDestination.x - icLeftPos;
                        scrollEnabled = false;
                    }
                    icTopPos = locContainer.getTopBoundary();
                    if (icTopPos + touchOffsetY <= locDestination.y) {
                        touchOffsetY = locDestination.y - icTopPos;
                        scrollEnabled = false;
                    }
                } else if (touchOffsetX === 0.0 && touchOffsetY > 0.0){ // up
                    icBottomPos = locContainer.getBottomBoundary();
                    if (icBottomPos + touchOffsetY >= locDestination.y) {
                        touchOffsetY = locDestination.y - icBottomPos;
                        scrollEnabled = false;
                    }
                } else if (touchOffsetX < 0.0 && touchOffsetY === 0.0){ // left
                    icRightPos = locContainer.getRightBoundary();
                    if (icRightPos + touchOffsetX <= locDestination.x) {
                        touchOffsetX = locDestination.x - icRightPos;
                        scrollEnabled = false;
                    }
                } else if (touchOffsetX === 0.0 && touchOffsetY < 0.0){ // down
                    icTopPos = locContainer.getTopBoundary();
                    if (icTopPos + touchOffsetY <= locDestination.y) {
                        touchOffsetY = locDestination.y - icTopPos;
                        scrollEnabled = false;
                    }
                } else if (touchOffsetX > 0.0 && touchOffsetY === 0.0){ // right
                    icLeftPos = locContainer.getLeftBoundary();
                    if (icLeftPos + touchOffsetX >= locDestination.x) {
                        touchOffsetX = locDestination.x - icLeftPos;
                        scrollEnabled = false;
                    }
                }
                break;
            default:
                break;
        }
        return scrollEnabled;
    },

    _scrollChildren: function (touchOffsetX, touchOffsetY) {
        var scrollEnabled = true;
        this._scrollingEvent();
        switch (this.direction) {
            case ccui.ScrollView.DIR_VERTICAL: // vertical
                scrollEnabled = this._scrollChildrenVertical(touchOffsetX, touchOffsetY);
                break;
            case ccui.ScrollView.DIR_HORIZONTAL: // horizontal
                scrollEnabled = this._scrollChildrenHorizontal(touchOffsetX, touchOffsetY);
                break;
            case ccui.ScrollView.DIR_BOTH:
                scrollEnabled = this._scrollChildrenBoth(touchOffsetX, touchOffsetY);
                break;
            default:
                break;
        }
        return scrollEnabled;
    },

    _scrollChildrenVertical: function(touchOffsetX, touchOffsetY){
        var realOffset = touchOffsetY;
        var scrollEnabled = true;
        var icBottomPos, icTopPos, locContainer = this._innerContainer;
        if (this.bounceEnabled) {
            icBottomPos = locContainer.getBottomBoundary();
            if (icBottomPos + touchOffsetY >= this._bounceBottomBoundary) {
                realOffset = this._bounceBottomBoundary - icBottomPos;
                this._scrollToBottomEvent();
                scrollEnabled = false;
            }
            icTopPos = locContainer.getTopBoundary();
            if (icTopPos + touchOffsetY <= this._bounceTopBoundary) {
                realOffset = this._bounceTopBoundary - icTopPos;
                this._scrollToTopEvent();
                scrollEnabled = false;

            }
        } else {
            icBottomPos = locContainer.getBottomBoundary();
            if (icBottomPos + touchOffsetY >= this._bottomBoundary){
                realOffset = this._bottomBoundary - icBottomPos;
                this._scrollToBottomEvent();
                scrollEnabled = false;
            }
            icTopPos = locContainer.getTopBoundary();
            if (icTopPos + touchOffsetY <= this._topBoundary) {
                realOffset = this._topBoundary - icTopPos;
                this._scrollToTopEvent();
                scrollEnabled = false;
            }
        }
        this._moveChildren(0.0, realOffset);
        return scrollEnabled;
    },

    _scrollChildrenHorizontal: function(touchOffsetX, touchOffestY){
        var scrollEnabled = true;
        var realOffset = touchOffsetX;
        var icRightPos, icLeftPos, locContainer = this._innerContainer;
        if (this.bounceEnabled){
            icRightPos = locContainer.getRightBoundary();
            if (icRightPos + touchOffsetX <= this._bounceRightBoundary) {
                realOffset = this._bounceRightBoundary - icRightPos;
                this._scrollToRightEvent();
                scrollEnabled = false;
            }
            icLeftPos = locContainer.getLeftBoundary();
            if (icLeftPos + touchOffsetX >= this._bounceLeftBoundary) {
                realOffset = this._bounceLeftBoundary - icLeftPos;
                this._scrollToLeftEvent();
                scrollEnabled = false;
            }
        } else {
            icRightPos = locContainer.getRightBoundary();
            if (icRightPos + touchOffsetX <= this._rightBoundary) {
                realOffset = this._rightBoundary - icRightPos;
                this._scrollToRightEvent();
                scrollEnabled = false;
            }
            icLeftPos = locContainer.getLeftBoundary();
            if (icLeftPos + touchOffsetX >= this._leftBoundary) {
                realOffset = this._leftBoundary - icLeftPos;
                this._scrollToLeftEvent();
                scrollEnabled = false;
            }
        }
        this._moveChildren(realOffset, 0.0);
        return scrollEnabled;
    },

    _scrollChildrenBoth: function (touchOffsetX, touchOffsetY) {
        var scrollEnabled = true;
        var realOffsetX = touchOffsetX;
        var realOffsetY = touchOffsetY;
        var icLeftPos, icBottomPos, icRightPos, icTopPos;
        var locContainer = this._innerContainer;
        if (this.bounceEnabled) {
            if (touchOffsetX > 0.0 && touchOffsetY > 0.0) { // up right
                icLeftPos = locContainer.getLeftBoundary();
                if (icLeftPos + touchOffsetX >= this._bounceLeftBoundary) {
                    realOffsetX = this._bounceLeftBoundary - icLeftPos;
                    this._scrollToLeftEvent();
                    scrollEnabled = false;
                }
                icBottomPos = locContainer.getBottomBoundary();
                if (icBottomPos + touchOffsetY >= this._bounceBottomBoundary) {
                    realOffsetY = this._bounceBottomBoundary - icBottomPos;
                    this._scrollToBottomEvent();
                    scrollEnabled = false;
                }
            } else if (touchOffsetX < 0.0 && touchOffsetY > 0.0) { // up left
                icRightPos = locContainer.getRightBoundary();
                if (icRightPos + touchOffsetX <= this._bounceRightBoundary) {
                    realOffsetX = this._bounceRightBoundary - icRightPos;
                    this._scrollToRightEvent();
                    scrollEnabled = false;
                }
                icBottomPos = locContainer.getBottomBoundary();
                if (icBottomPos + touchOffsetY >= this._bounceBottomBoundary) {
                    realOffsetY = this._bounceBottomBoundary - icBottomPos;
                    this._scrollToBottomEvent();
                    scrollEnabled = false;
                }
            } else if (touchOffsetX < 0.0 && touchOffsetY < 0.0) { // down left
                icRightPos = locContainer.getRightBoundary();
                if (icRightPos + touchOffsetX <= this._bounceRightBoundary) {
                    realOffsetX = this._bounceRightBoundary - icRightPos;
                    this._scrollToRightEvent();
                    scrollEnabled = false;
                }
                icTopPos = locContainer.getTopBoundary();
                if (icTopPos + touchOffsetY <= this._bounceTopBoundary) {
                    realOffsetY = this._bounceTopBoundary - icTopPos;
                    this._scrollToTopEvent();
                    scrollEnabled = false;
                }
            } else if (touchOffsetX > 0.0 && touchOffsetY < 0.0){ // down right
                icLeftPos = locContainer.getLeftBoundary();
                if (icLeftPos + touchOffsetX >= this._bounceLeftBoundary) {
                    realOffsetX = this._bounceLeftBoundary - icLeftPos;
                    this._scrollToLeftEvent();
                    scrollEnabled = false;
                }
                icTopPos = locContainer.getTopBoundary();
                if (icTopPos + touchOffsetY <= this._bounceTopBoundary) {
                    realOffsetY = this._bounceTopBoundary - icTopPos;
                    this._scrollToTopEvent();
                    scrollEnabled = false;
                }
            } else if (touchOffsetX === 0.0 && touchOffsetY > 0.0){ // up
                icBottomPos = locContainer.getBottomBoundary();
                if (icBottomPos + touchOffsetY >= this._bounceBottomBoundary) {
                    realOffsetY = this._bounceBottomBoundary - icBottomPos;
                    this._scrollToBottomEvent();
                    scrollEnabled = false;
                }
            } else if (touchOffsetX < 0.0 && touchOffsetY === 0.0){ // left
                icRightPos = locContainer.getRightBoundary();
                if (icRightPos + touchOffsetX <= this._bounceRightBoundary) {
                    realOffsetX = this._bounceRightBoundary - icRightPos;
                    this._scrollToRightEvent();
                    scrollEnabled = false;
                }
            } else if (touchOffsetX === 0.0 && touchOffsetY < 0.0){ // down
                icTopPos = locContainer.getTopBoundary();
                if (icTopPos + touchOffsetY <= this._bounceTopBoundary) {
                    realOffsetY = this._bounceTopBoundary - icTopPos;
                    this._scrollToTopEvent();
                    scrollEnabled = false;
                }
            } else if (touchOffsetX > 0.0 && touchOffsetY === 0.0){ // right
                icLeftPos = locContainer.getLeftBoundary();
                if (icLeftPos + touchOffsetX >= this._bounceLeftBoundary) {
                    realOffsetX = this._bounceLeftBoundary - icLeftPos;
                    this._scrollToLeftEvent();
                    scrollEnabled = false;
                }
            }
        } else {
            if (touchOffsetX > 0.0 && touchOffsetY > 0.0){ // up right
                icLeftPos = locContainer.getLeftBoundary();
                if (icLeftPos + touchOffsetX >= this._leftBoundary) {
                    realOffsetX = this._leftBoundary - icLeftPos;
                    this._scrollToLeftEvent();
                    scrollEnabled = false;
                }
                icBottomPos = locContainer.getBottomBoundary();
                if (icBottomPos + touchOffsetY >= this._bottomBoundary) {
                    realOffsetY = this._bottomBoundary - icBottomPos;
                    this._scrollToBottomEvent();
                    scrollEnabled = false;
                }
            } else if (touchOffsetX < 0.0 && touchOffsetY > 0.0){ // up left
                icRightPos = locContainer.getRightBoundary();
                if (icRightPos + touchOffsetX <= this._rightBoundary) {
                    realOffsetX = this._rightBoundary - icRightPos;
                    this._scrollToRightEvent();
                    scrollEnabled = false;
                }
                icBottomPos = locContainer.getBottomBoundary();
                if (icBottomPos + touchOffsetY >= this._bottomBoundary) {
                    realOffsetY = this._bottomBoundary - icBottomPos;
                    this._scrollToBottomEvent();
                    scrollEnabled = false;
                }
            } else if (touchOffsetX < 0.0 && touchOffsetY < 0.0){ // down left
                icRightPos = locContainer.getRightBoundary();
                if (icRightPos + touchOffsetX <= this._rightBoundary) {
                    realOffsetX = this._rightBoundary - icRightPos;
                    this._scrollToRightEvent();
                    scrollEnabled = false;
                }
                icTopPos = locContainer.getTopBoundary();
                if (icTopPos + touchOffsetY <= this._topBoundary) {
                    realOffsetY = this._topBoundary - icTopPos;
                    this._scrollToTopEvent();
                    scrollEnabled = false;
                }
            } else if (touchOffsetX > 0.0 && touchOffsetY < 0.0){ // down right
                icLeftPos = locContainer.getLeftBoundary();
                if (icLeftPos + touchOffsetX >= this._leftBoundary) {
                    realOffsetX = this._leftBoundary - icLeftPos;
                    this._scrollToLeftEvent();
                    scrollEnabled = false;
                }
                icTopPos = this._innerContainer.getTopBoundary();
                if (icTopPos + touchOffsetY <= this._topBoundary) {
                    realOffsetY = this._topBoundary - icTopPos;
                    this._scrollToTopEvent();
                    scrollEnabled = false;
                }
            } else if (touchOffsetX === 0.0 && touchOffsetY > 0.0) { // up
                icBottomPos = this._innerContainer.getBottomBoundary();
                if (icBottomPos + touchOffsetY >= this._bottomBoundary) {
                    realOffsetY = this._bottomBoundary - icBottomPos;
                    this._scrollToBottomEvent();
                    scrollEnabled = false;
                }
            } else if (touchOffsetX < 0.0 && touchOffsetY === 0.0){ // left
                icRightPos = this._innerContainer.getRightBoundary();
                if (icRightPos + touchOffsetX <= this._rightBoundary) {
                    realOffsetX = this._rightBoundary - icRightPos;
                    this._scrollToRightEvent();
                    scrollEnabled = false;
                }
            } else if (touchOffsetX === 0.0 && touchOffsetY < 0.0){  // down
                icTopPos = this._innerContainer.getTopBoundary();
                if (icTopPos + touchOffsetY <= this._topBoundary) {
                    realOffsetY = this._topBoundary - icTopPos;
                    this._scrollToTopEvent();
                    scrollEnabled = false;
                }
            }  else if (touchOffsetX > 0.0 && touchOffsetY === 0.0){ // right
                icLeftPos = this._innerContainer.getLeftBoundary();
                if (icLeftPos + touchOffsetX >= this._leftBoundary) {
                    realOffsetX = this._leftBoundary - icLeftPos;
                    this._scrollToLeftEvent();
                    scrollEnabled = false;
                }
            }
        }
        this._moveChildren(realOffsetX, realOffsetY);
        return scrollEnabled;
    },

    /**
     * Scroll inner container to bottom boundary of ScrollView.
     * @param {Number} time
     * @param {Boolean} attenuated
     */
    scrollToBottom: function (time, attenuated) {
        this._startAutoScrollChildrenWithDestination(cc.p(this._innerContainer.getPositionX(), 0), time, attenuated);
    },

    /**
     * Scroll inner container to top boundary of ScrollView.
     * @param {Number} time
     * @param {Boolean} attenuated
     */
    scrollToTop: function (time, attenuated) {
        this._startAutoScrollChildrenWithDestination(
            cc.p(this._innerContainer.getPositionX(), this._contentSize.height - this._innerContainer.getContentSize().height), time, attenuated);
    },

    /**
     * Scroll inner container to left boundary of ScrollView.
     * @param {Number} time
     * @param {Boolean} attenuated
     */
    scrollToLeft: function (time, attenuated) {
        this._startAutoScrollChildrenWithDestination(cc.p(0, this._innerContainer.getPositionY()), time, attenuated);
    },

    /**
     * Scroll inner container to right boundary of ScrollView.
     * @param {Number} time
     * @param {Boolean} attenuated
     */
    scrollToRight: function (time, attenuated) {
        this._startAutoScrollChildrenWithDestination(
            cc.p(this._contentSize.width - this._innerContainer.getContentSize().width, this._innerContainer.getPositionY()), time, attenuated);
    },

    /**
     * Scroll inner container to top and left boundary of ScrollView.
     * @param {Number} time
     * @param {Boolean} attenuated
     */
    scrollToTopLeft: function (time, attenuated) {
        if (this.direction !== ccui.ScrollView.DIR_BOTH) {
            cc.log("Scroll direction is not both!");
            return;
        }
        this._startAutoScrollChildrenWithDestination(cc.p(0, this._contentSize.height - this._innerContainer.getContentSize().height), time, attenuated);
    },

    /**
     * Scroll inner container to top and right boundary of ScrollView.
     * @param {Number} time
     * @param {Boolean} attenuated
     */
    scrollToTopRight: function (time, attenuated) {
        if (this.direction !== ccui.ScrollView.DIR_BOTH) {
            cc.log("Scroll direction is not both!");
            return;
        }
        var inSize = this._innerContainer.getContentSize();
        this._startAutoScrollChildrenWithDestination(cc.p(this._contentSize.width - inSize.width,
                this._contentSize.height - inSize.height), time, attenuated);
    },

    /**
     * Scroll inner container to bottom and left boundary of ScrollView.
     * @param {Number} time
     * @param {Boolean} attenuated
     */
    scrollToBottomLeft: function (time, attenuated) {
        if (this.direction !== ccui.ScrollView.DIR_BOTH) {
            cc.log("Scroll direction is not both!");
            return;
        }
        this._startAutoScrollChildrenWithDestination(cc.p(0, 0), time, attenuated);
    },

    /**
     * Scroll inner container to bottom and right boundary of ScrollView.
     * @param {Number} time
     * @param {Boolean} attenuated
     */
    scrollToBottomRight: function (time, attenuated) {
        if (this.direction !== ccui.ScrollView.DIR_BOTH) {
            cc.log("Scroll direction is not both!");
            return;
        }
        this._startAutoScrollChildrenWithDestination(cc.p(this._contentSize.width - this._innerContainer.getContentSize().width, 0), time, attenuated);
    },

    /**
     * Scroll inner container to vertical percent position of ScrollView.
     * @param {Number} percent
     * @param {Number} time
     * @param {Boolean} attenuated
     */
    scrollToPercentVertical: function (percent, time, attenuated) {
        var minY = this._contentSize.height - this._innerContainer.getContentSize().height;
        var h = -minY;
        this._startAutoScrollChildrenWithDestination(cc.p(this._innerContainer.getPositionX(), minY + percent * h / 100), time, attenuated);
    },

    /**
     * Scroll inner container to horizontal percent position of ScrollView.
     * @param {Number} percent
     * @param {Number} time
     * @param {Boolean} attenuated
     */
    scrollToPercentHorizontal: function (percent, time, attenuated) {
        var w = this._innerContainer.getContentSize().width - this._contentSize.width;
        this._startAutoScrollChildrenWithDestination(cc.p(-(percent * w / 100), this._innerContainer.getPositionY()), time, attenuated);
    },

    /**
     * Scroll inner container to both direction percent position of ScrollView.
     * @param {cc.Point} percent
     * @param {Number} time
     * @param {Boolean} attenuated
     */
    scrollToPercentBothDirection: function (percent, time, attenuated) {
        if (this.direction !== ccui.ScrollView.DIR_BOTH)
            return;
        var minY = this._contentSize.height - this._innerContainer.getContentSize().height;
        var h = -minY;
        var w = this._innerContainer.getContentSize().width - this._contentSize.width;
        this._startAutoScrollChildrenWithDestination(cc.p(-(percent.x * w / 100), minY + percent.y * h / 100), time, attenuated);
    },

    /**
     * Move inner container to bottom boundary of ScrollView.
     */
    jumpToBottom: function () {
        this._jumpToDestination(this._innerContainer.getPositionX(), 0);
    },

    /**
     * Move inner container to top boundary of ScrollView.
     */
    jumpToTop: function () {
        this._jumpToDestination(this._innerContainer.getPositionX(), this._contentSize.height - this._innerContainer.getContentSize().height);
    },

    /**
     * Move inner container to left boundary of ScrollView.
     */
    jumpToLeft: function () {
        this._jumpToDestination(0, this._innerContainer.getPositionY());
    },

    /**
     * Move inner container to right boundary of ScrollView.
     */
    jumpToRight: function () {
        this._jumpToDestination(this._contentSize.width - this._innerContainer.getContentSize().width, this._innerContainer.getPositionY());
    },

    /**
     * Move inner container to top and left boundary of ScrollView.
     */
    jumpToTopLeft: function () {
        if (this.direction !== ccui.ScrollView.DIR_BOTH) {
            cc.log("Scroll direction is not both!");
            return;
        }
        this._jumpToDestination(0, this._contentSize.height - this._innerContainer.getContentSize().height);
    },

    /**
     * Move inner container to top and right boundary of ScrollView.
     */
    jumpToTopRight: function () {
        if (this.direction !== ccui.ScrollView.DIR_BOTH) {
            cc.log("Scroll direction is not both!");
            return;
        }
        var inSize = this._innerContainer.getContentSize();
        this._jumpToDestination(this._contentSize.width - inSize.width, this._contentSize.height - inSize.height);
    },

    /**
     * Move inner container to bottom and left boundary of ScrollView.
     */
    jumpToBottomLeft: function () {
        if (this.direction !== ccui.ScrollView.DIR_BOTH) {
            cc.log("Scroll direction is not both!");
            return;
        }
        this._jumpToDestination(0, 0);
    },

    /**
     * Move inner container to bottom and right boundary of ScrollView.
     */
    jumpToBottomRight: function () {
        if (this.direction !== ccui.ScrollView.DIR_BOTH) {
            cc.log("Scroll direction is not both!");
            return;
        }
        this._jumpToDestination(this._contentSize.width - this._innerContainer.getContentSize().width, 0);
    },

    /**
     * Move inner container to vertical percent position of ScrollView.
     * @param {Number} percent The destination vertical percent, accept value between 0 - 100
     */
    jumpToPercentVertical: function (percent) {
        var minY = this._contentSize.height - this._innerContainer.getContentSize().height;
        var h = -minY;
        this._jumpToDestination(this._innerContainer.getPositionX(), minY + percent * h / 100);
    },

    /**
     * Move inner container to horizontal percent position of ScrollView.
     * @param {Number} percent The destination vertical percent, accept value between 0 - 100
     */
    jumpToPercentHorizontal: function (percent) {
        var w = this._innerContainer.getContentSize().width - this._contentSize.width;
        this._jumpToDestination(-(percent * w / 100), this._innerContainer.getPositionY());
    },

    /**
     * Move inner container to both direction percent position of ScrollView.
     * @param {cc.Point} percent The destination vertical percent, accept value between 0 - 100
     */
    jumpToPercentBothDirection: function (percent) {
        if (this.direction !== ccui.ScrollView.DIR_BOTH)
            return;
        var inSize = this._innerContainer.getContentSize();
        var minY = this._contentSize.height - inSize.height;
        var h = -minY;
        var w = inSize.width - this._contentSize.width;
        this._jumpToDestination(-(percent.x * w / 100), minY + percent.y * h / 100);
    },

    _startRecordSlidAction: function () {
        if (this._autoScroll)
            this._stopAutoScrollChildren();
        if (this._bouncing)
            this._stopBounceChildren();
        this._slidTime = 0.0;
    },

    _endRecordSlidAction: function () {
        if (!this._checkNeedBounce() && this.inertiaScrollEnabled) {
            if (this._slidTime <= 0.016)
                return;
            var totalDis = 0, dir;
            var touchEndPositionInNodeSpace = this.convertToNodeSpace(this._touchEndPosition);
            var touchBeganPositionInNodeSpace = this.convertToNodeSpace(this._touchBeganPosition);
            switch (this.direction) {
                case ccui.ScrollView.DIR_VERTICAL :
                    totalDis = touchEndPositionInNodeSpace.y - touchBeganPositionInNodeSpace.y;
                    dir = (totalDis < 0) ? ccui.ScrollView.SCROLLDIR_DOWN : ccui.ScrollView.SCROLLDIR_UP;
                    break;
                case ccui.ScrollView.DIR_HORIZONTAL:
                    totalDis = touchEndPositionInNodeSpace.x - touchBeganPositionInNodeSpace.x;
                    dir = totalDis < 0 ? ccui.ScrollView.SCROLLDIR_LEFT : ccui.ScrollView.SCROLLDIR_RIGHT;
                    break;
                case ccui.ScrollView.DIR_BOTH :
                    var subVector = cc.pSub(touchEndPositionInNodeSpace, touchBeganPositionInNodeSpace);
                    totalDis = cc.pLength(subVector);
                    dir = cc.pNormalize(subVector);
                    break;
                default:
                    dir = cc.p(0,0);
                    break;
            }
            var orSpeed = Math.min(Math.abs(totalDis) / (this._slidTime), ccui.ScrollView.AUTO_SCROLL_MAX_SPEED);
            this._startAutoScrollChildrenWithOriginalSpeed(dir, orSpeed, true, -1000);
            this._slidTime = 0;
        }
    },

    _handlePressLogic: function (touch) {
        this._startRecordSlidAction();
        this._bePressed = true;
    },

    _handleMoveLogic: function (touch) {
        var touchPositionInNodeSpace = this.convertToNodeSpace(touch.getLocation()),
            previousTouchPositionInNodeSpace = this.convertToNodeSpace(touch.getPreviousLocation());
        var delta = cc.pSub(touchPositionInNodeSpace, previousTouchPositionInNodeSpace);
        switch (this.direction) {
            case ccui.ScrollView.DIR_VERTICAL: // vertical
                this._scrollChildren(0.0, delta.y);
                break;
            case ccui.ScrollView.DIR_HORIZONTAL: // horizontal
                this._scrollChildren(delta.x, 0);
                break;
            case ccui.ScrollView.DIR_BOTH: // both
                this._scrollChildren(delta.x, delta.y);
                break;
            default:
                break;
        }
    },

    _handleReleaseLogic: function (touch) {
        this._endRecordSlidAction();
        this._bePressed = false;
    },

    /**
     * The touch began event callback handler of ccui.ScrollView.
     * @param {cc.Touch} touch
     * @param {cc.Event} event
     * @returns {boolean}
     */
    onTouchBegan: function (touch, event) {
        var pass = ccui.Layout.prototype.onTouchBegan.call(this, touch, event);
        if(!this._isInterceptTouch){
            if (this._hit)
                this._handlePressLogic(touch);
        }
        return pass;
    },

    /**
     * The touch moved event callback handler of ccui.ScrollView.
     * @param {cc.Touch} touch
     * @param {cc.Event} event
     */
    onTouchMoved: function (touch, event) {
        ccui.Layout.prototype.onTouchMoved.call(this, touch, event);
        if(!this._isInterceptTouch)
            this._handleMoveLogic(touch);
    },

    /**
     * The touch ended event callback handler of ccui.ScrollView.
     * @param {cc.Touch} touch
     * @param {cc.Event} event
     */
    onTouchEnded: function (touch, event) {
        ccui.Layout.prototype.onTouchEnded.call(this, touch, event);
        if(!this._isInterceptTouch)
            this._handleReleaseLogic(touch);
        this._isInterceptTouch = false;
    },

    /**
     * The touch canceled event callback of ccui.ScrollView.
     * @param {cc.Touch} touch
     * @param {cc.Event} event
     */
    onTouchCancelled: function (touch, event) {
        ccui.Layout.prototype.onTouchCancelled.call(this, touch, event);
        if (!this._isInterceptTouch)
            this.handleReleaseLogic(touch);
        this._isInterceptTouch = false;
    },

    /**
     * The update callback handler.
     * @param {Number} dt
     */
    update: function (dt) {
        if (this._autoScroll)
            this._autoScrollChildren(dt);
        if (this._bouncing)
            this._bounceChildren(dt);
        this._recordSlidTime(dt);
    },

    _recordSlidTime: function (dt) {
        if (this._bePressed)
            this._slidTime += dt;
    },

    /**
     * Intercept touch event, handle its child's touch event.
     * @override
     * @param {number} event event type
     * @param {ccui.Widget} sender
     * @param {cc.Touch} touch
     */
    interceptTouchEvent: function (event, sender, touch) {
        var touchPoint = touch.getLocation();
        switch (event) {
            case ccui.Widget.TOUCH_BEGAN:
                this._isInterceptTouch = true;
                this._touchBeganPosition.x = touchPoint.x;
                this._touchBeganPosition.y = touchPoint.y;
                this._handlePressLogic(touch);
                break;
            case ccui.Widget.TOUCH_MOVED:
                var offset = cc.pLength(cc.pSub(sender.getTouchBeganPosition(), touchPoint));
                this._touchMovePosition.x = touchPoint.x;
                this._touchMovePosition.y = touchPoint.y;
                if (offset > this._childFocusCancelOffset) {
                    sender.setHighlighted(false);
                    this._handleMoveLogic(touch);
                }
                break;
            case ccui.Widget.TOUCH_CANCELED:
            case ccui.Widget.TOUCH_ENDED:
                this._touchEndPosition.x = touchPoint.x;
                this._touchEndPosition.y = touchPoint.y;
                this._handleReleaseLogic(touch);
                if (sender.isSwallowTouches())
                    this._isInterceptTouch = false;
                break;
        }
    },

    _scrollToTopEvent: function () {
        if(this._scrollViewEventSelector){
            if (this._scrollViewEventListener)
                this._scrollViewEventSelector.call(this._scrollViewEventListener, this, ccui.ScrollView.EVENT_SCROLL_TO_TOP);
            else
                this._scrollViewEventSelector(this, ccui.ScrollView.EVENT_SCROLL_TO_TOP);
        }
        if(this._ccEventCallback)
            this._ccEventCallback(this, ccui.ScrollView.EVENT_SCROLL_TO_TOP);
    },

    _scrollToBottomEvent: function () {
        if(this._scrollViewEventSelector){
            if (this._scrollViewEventListener)
                this._scrollViewEventSelector.call(this._scrollViewEventListener, this, ccui.ScrollView.EVENT_SCROLL_TO_BOTTOM);
            else
                this._scrollViewEventSelector(this, ccui.ScrollView.EVENT_SCROLL_TO_BOTTOM);
        }
        if(this._ccEventCallback)
            this._ccEventCallback(this, ccui.ScrollView.EVENT_SCROLL_TO_BOTTOM);
    },

    _scrollToLeftEvent: function () {
        if(this._scrollViewEventSelector){
            if (this._scrollViewEventListener)
                this._scrollViewEventSelector.call(this._scrollViewEventListener, this, ccui.ScrollView.EVENT_SCROLL_TO_LEFT);
            else
                this._scrollViewEventSelector(this, ccui.ScrollView.EVENT_SCROLL_TO_LEFT);
        }
        if(this._ccEventCallback)
            this._ccEventCallback(this, ccui.ScrollView.EVENT_SCROLL_TO_LEFT);
    },

    _scrollToRightEvent: function () {
        if(this._scrollViewEventSelector){
            if (this._scrollViewEventListener)
                this._scrollViewEventSelector.call(this._scrollViewEventListener, this, ccui.ScrollView.EVENT_SCROLL_TO_RIGHT);
            else
                this._scrollViewEventSelector(this, ccui.ScrollView.EVENT_SCROLL_TO_RIGHT);
        }
        if(this._ccEventCallback)
            this._ccEventCallback(this, ccui.ScrollView.EVENT_SCROLL_TO_RIGHT);
    },

    _scrollingEvent: function () {
        if(this._scrollViewEventSelector){
            if (this._scrollViewEventListener)
                this._scrollViewEventSelector.call(this._scrollViewEventListener, this, ccui.ScrollView.EVENT_SCROLLING);
            else
                this._scrollViewEventSelector(this, ccui.ScrollView.EVENT_SCROLLING);
        }
        if(this._ccEventCallback)
            this._ccEventCallback(this, ccui.ScrollView.EVENT_SCROLLING);
    },

    _bounceTopEvent: function () {
        if(this._scrollViewEventSelector){
            if (this._scrollViewEventListener)
                this._scrollViewEventSelector.call(this._scrollViewEventListener, this, ccui.ScrollView.EVENT_BOUNCE_TOP);
            else
                this._scrollViewEventSelector(this, ccui.ScrollView.EVENT_BOUNCE_TOP);
        }
        if(this._ccEventCallback)
            this._ccEventCallback(this, ccui.ScrollView.EVENT_BOUNCE_TOP);
    },

    _bounceBottomEvent: function () {
        if(this._scrollViewEventSelector){
            if (this._scrollViewEventListener)
                this._scrollViewEventSelector.call(this._scrollViewEventListener, this, ccui.ScrollView.EVENT_BOUNCE_BOTTOM);
            else
                this._scrollViewEventSelector(this, ccui.ScrollView.EVENT_BOUNCE_BOTTOM);
        }
        if(this._ccEventCallback)
            this._ccEventCallback(this, ccui.ScrollView.EVENT_BOUNCE_BOTTOM);
    },

    _bounceLeftEvent: function () {
        if(this._scrollViewEventSelector){
            if (this._scrollViewEventListener)
                this._scrollViewEventSelector.call(this._scrollViewEventListener, this, ccui.ScrollView.EVENT_BOUNCE_LEFT);
            else
                this._scrollViewEventSelector(this, ccui.ScrollView.EVENT_BOUNCE_LEFT);
        }
        if(this._ccEventCallback)
            this._ccEventCallback(this, ccui.ScrollView.EVENT_BOUNCE_LEFT);
    },

    _bounceRightEvent: function () {
        if(this._scrollViewEventSelector){
            if (this._scrollViewEventListener)
                this._scrollViewEventSelector.call(this._scrollViewEventListener, this, ccui.ScrollView.EVENT_BOUNCE_RIGHT);
            else
                this._scrollViewEventSelector(this, ccui.ScrollView.EVENT_BOUNCE_RIGHT);
        }
        if(this._ccEventCallback)
            this._ccEventCallback(this, ccui.ScrollView.EVENT_BOUNCE_RIGHT);
    },

    /**
     * Adds callback function called ScrollView event triggered
     * @param {Function} selector
     * @param {Object} [target=]
     * @deprecated since v3.0, please use addEventListener instead.
     */
    addEventListenerScrollView: function (selector, target) {
        this.addEventListener(selector, target);
    },

    /**
     * Adds callback function called ScrollView event triggered
     * @param {Function} selector
     * @param {Object} [target=]
     */
    addEventListener: function(selector, target){
        this._scrollViewEventSelector = selector;
        this._scrollViewEventListener = target;
    },

    /**
     * Changes scroll direction of ScrollView.
     * @param {ccui.ScrollView.DIR_NONE | ccui.ScrollView.DIR_VERTICAL | ccui.ScrollView.DIR_HORIZONTAL | ccui.ScrollView.DIR_BOTH} dir
     *   Direction::VERTICAL means vertical scroll, Direction::HORIZONTAL means horizontal scroll
     */
    setDirection: function (dir) {
        this.direction = dir;
    },

    /**
     * Returns scroll direction of ScrollView.
     * @returns {ccui.ScrollView.DIR_NONE | ccui.ScrollView.DIR_VERTICAL | ccui.ScrollView.DIR_HORIZONTAL | ccui.ScrollView.DIR_BOTH}
     */
    getDirection: function () {
        return this.direction;
    },

    /**
     * Sets bounce enabled
     * @param {Boolean} enabled
     */
    setBounceEnabled: function (enabled) {
        this.bounceEnabled = enabled;
    },

    /**
     * Returns whether bounce is enabled
     * @returns {boolean}
     */
    isBounceEnabled: function () {
        return this.bounceEnabled;
    },

    /**
     * Sets inertiaScroll enabled
     * @param {boolean} enabled
     */
    setInertiaScrollEnabled: function (enabled) {
        this.inertiaScrollEnabled = enabled;
    },

    /**
     * Returns whether inertiaScroll is enabled
     * @returns {boolean}
     */
    isInertiaScrollEnabled: function () {
        return this.inertiaScrollEnabled;
    },

    /**
     * Gets inner container of ScrollView. Inner container is the container of ScrollView's children.
     * @returns {ccui.Layout}
     */
    getInnerContainer: function () {
        return this._innerContainer;
    },

    /**
     * Sets LayoutType of ccui.ScrollView.
     * @param {ccui.Layout.ABSOLUTE|ccui.Layout.LINEAR_VERTICAL|ccui.Layout.LINEAR_HORIZONTAL|ccui.Layout.RELATIVE} type
     */
    setLayoutType: function (type) {
        this._innerContainer.setLayoutType(type);
    },

    /**
     * Returns the layout type of ccui.ScrollView.
     * @returns {ccui.Layout.ABSOLUTE|ccui.Layout.LINEAR_VERTICAL|ccui.Layout.LINEAR_HORIZONTAL|ccui.Layout.RELATIVE}
     */
    getLayoutType: function () {
        return this._innerContainer.getLayoutType();
    },

    _doLayout: function () {
        if (!this._doLayoutDirty)
            return;
        this._doLayoutDirty = false;
    },

    /**
     * Returns the "class name" of ccui.ScrollView.
     * @returns {string}
     */
    getDescription: function () {
        return "ScrollView";
    },

    _createCloneInstance: function(){
        return new ccui.ScrollView();
    },

    _copyClonedWidgetChildren: function (model) {
        ccui.Layout.prototype._copyClonedWidgetChildren.call(this, model);
    },

    _copySpecialProperties: function (scrollView) {
        if(scrollView instanceof ccui.ScrollView) {
            ccui.Layout.prototype._copySpecialProperties.call(this, scrollView);
            this.setInnerContainerSize(scrollView.getInnerContainerSize());
            this.setDirection(scrollView.direction);
            this.setBounceEnabled(scrollView.bounceEnabled);
            this.setInertiaScrollEnabled(scrollView.inertiaScrollEnabled);
            this._scrollViewEventListener = scrollView._scrollViewEventListener;
            this._scrollViewEventSelector = scrollView._scrollViewEventSelector;
            this._ccEventCallback = scrollView._ccEventCallback;
        }
    },

    /**
     * Returns a node by tag
     * @param {Number} tag
     * @returns {cc.Node}
     * @deprecated  since v3.0, please use getChildByTag instead.
     */
    getNodeByTag: function (tag) {
        return this._innerContainer.getNodeByTag(tag);
    },

    /**
     * Returns all nodes of inner container
     * @returns {Array}
     * @deprecated since v3.0, please use getChildren instead.
     */
    getNodes: function () {
        return this._innerContainer.getNodes();
    },

    /**
     * Removes a node from ccui.ScrollView.
     * @param {cc.Node} node
     * @deprecated since v3.0, please use removeChild instead.
     */
    removeNode: function (node) {
        this._innerContainer.removeNode(node);
    },

    /**
     * Removes a node by tag
     * @param {Number} tag
     * @deprecated since v3.0, please use removeChildByTag instead.
     */
    removeNodeByTag: function (tag) {
        this._innerContainer.removeNodeByTag(tag);
    },

    /**
     * Remove all node from ccui.ScrollView.
     * @deprecated since v3.0, please use removeAllChildren instead.
     */
    removeAllNodes: function () {
        this._innerContainer.removeAllNodes();
    },

    /**
     * Add node for scrollView
     * @param {cc.Node} node
     * @param {Number} zOrder
     * @param {Number} tag
     * @deprecated since v3.0, please use addChild instead.
     */
    addNode: function (node, zOrder, tag) {
        this._innerContainer.addNode(node, zOrder, tag);
    }
});

var _p = ccui.ScrollView.prototype;

// Extended properties
/** @expose */
_p.innerWidth;
cc.defineGetterSetter(_p, "innerWidth", _p._getInnerWidth, _p._setInnerWidth);
/** @expose */
_p.innerHeight;
cc.defineGetterSetter(_p, "innerHeight", _p._getInnerHeight, _p._setInnerHeight);

_p = null;

/**
 * allocates and initializes a UIScrollView.
 * @deprecated since v3.0, please use new ccui.ScrollView() instead.
 * @return {ccui.ScrollView}
 */
ccui.ScrollView.create = function () {
    return new ccui.ScrollView();
};

// Constants
//ScrollView direction
/**
 * The none flag of ccui.ScrollView's direction.
 * @constant
 * @type {number}
 */
ccui.ScrollView.DIR_NONE = 0;
/**
 * The vertical flag of ccui.ScrollView's direction.
 * @constant
 * @type {number}
 */
ccui.ScrollView.DIR_VERTICAL = 1;
/**
 * The horizontal flag of ccui.ScrollView's direction.
 * @constant
 * @type {number}
 */
ccui.ScrollView.DIR_HORIZONTAL = 2;
/**
 * The both flag of ccui.ScrollView's direction.
 * @constant
 * @type {number}
 */
ccui.ScrollView.DIR_BOTH = 3;

//ScrollView event
/**
 * The flag scroll to top of ccui.ScrollView's event.
 * @constant
 * @type {number}
 */
ccui.ScrollView.EVENT_SCROLL_TO_TOP = 0;
/**
 * The flag scroll to bottom of ccui.ScrollView's event.
 * @constant
 * @type {number}
 */
ccui.ScrollView.EVENT_SCROLL_TO_BOTTOM = 1;
/**
 * The flag scroll to left of ccui.ScrollView's event.
 * @constant
 * @type {number}
 */
ccui.ScrollView.EVENT_SCROLL_TO_LEFT = 2;
/**
 * The flag scroll to right of ccui.ScrollView's event.
 * @constant
 * @type {number}
 */
ccui.ScrollView.EVENT_SCROLL_TO_RIGHT = 3;
/**
 * The scrolling flag of ccui.ScrollView's event.
 * @constant
 * @type {number}
 */
ccui.ScrollView.EVENT_SCROLLING = 4;
/**
 * The flag bounce top of ccui.ScrollView's event.
 * @constant
 * @type {number}
 */
ccui.ScrollView.EVENT_BOUNCE_TOP = 5;
/**
 * The flag bounce bottom of ccui.ScrollView's event.
 * @constant
 * @type {number}
 */
ccui.ScrollView.EVENT_BOUNCE_BOTTOM = 6;
/**
 * The flag bounce left of ccui.ScrollView's event.
 * @constant
 * @type {number}
 */
ccui.ScrollView.EVENT_BOUNCE_LEFT = 7;
/**
 * The flag bounce right of ccui.ScrollView's event.
 * @constant
 * @type {number}
 */
ccui.ScrollView.EVENT_BOUNCE_RIGHT = 8;

/**
 * The auto scroll max speed of ccui.ScrollView.
 * @constant
 * @type {number}
 */
ccui.ScrollView.AUTO_SCROLL_MAX_SPEED = 1000;

/**
 * @ignore
 */
ccui.ScrollView.SCROLLDIR_UP = cc.p(0, 1);
ccui.ScrollView.SCROLLDIR_DOWN = cc.p(0, -1);
ccui.ScrollView.SCROLLDIR_LEFT = cc.p(-1, 0);
ccui.ScrollView.SCROLLDIR_RIGHT = cc.p(1, 0);