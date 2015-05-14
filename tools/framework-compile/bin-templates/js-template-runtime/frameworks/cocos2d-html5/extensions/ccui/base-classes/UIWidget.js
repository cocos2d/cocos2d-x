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

ccui._FocusNavigationController = cc.Class.extend({
    _keyboardListener: null,
    _firstFocusedWidget: null,
    _enableFocusNavigation: false,
    _keyboardEventPriority: 1,

    enableFocusNavigation: function(flag){
        if (this._enableFocusNavigation === flag)
            return;

        this._enableFocusNavigation = flag;
        if (flag)
            this._addKeyboardEventListener();
        else
            this._removeKeyboardEventListener();
    },

    _setFirstFocsuedWidget: function(widget){
        this._firstFocusedWidget = widget;
    },

    _onKeyPressed: function(keyCode, event){
        if (this._enableFocusNavigation && this._firstFocusedWidget) {
            if (keyCode === cc.KEY.dpadDown) {
                this._firstFocusedWidget = this._firstFocusedWidget.findNextFocusedWidget(ccui.Widget.DOWN, this._firstFocusedWidget);
            }
            if (keyCode === cc.KEY.dpadUp){
                this._firstFocusedWidget = this._firstFocusedWidget.findNextFocusedWidget(ccui.Widget.UP, this._firstFocusedWidget);
            }
            if (keyCode === cc.KEY.dpadLeft) {
                this._firstFocusedWidget = this._firstFocusedWidget.findNextFocusedWidget(ccui.Widget.LEFT, this._firstFocusedWidget);
            }
            if (keyCode === cc.KEY.dpadRight) {
                this._firstFocusedWidget = this._firstFocusedWidget.findNextFocusedWidget(ccui.Widget.RIGHT, this._firstFocusedWidget);
            }
        }
    },

    _addKeyboardEventListener: function(){
        if (!this._keyboardListener) {
            this._keyboardListener = cc.EventListener.create({
                event: cc.EventListener.KEYBOARD,
                onKeyReleased: this._onKeyPressed.bind(this)
            });
            cc.eventManager.addListener(this._keyboardListener, this._keyboardEventPriority);
        }
    },

    _removeKeyboardEventListener: function(){
        if (this._keyboardListener) {
            cc.eventManager.removeEventListener(this._keyboardListener);
            this._keyboardListener = null;
        }
    }
});

ccui.__LAYOUT_COMPONENT_NAME = "__ui_layout";

/**
 * The base class for ccui controls and layout
 * @sample
 * var uiWidget = new ccui.Widget();
 * this.addChild(uiWidget);
 * @class
 * @extends ccui.ProtectedNode
 *
 * @property {Number}           xPercent        - Position x in percentage of width
 * @property {Number}           yPercent        - Position y in percentage of height
 * @property {Number}           widthPercent    - Width in percentage of parent width
 * @property {Number}           heightPercent   - Height in percentage of parent height
 * @property {ccui.Widget}      widgetParent    - <@readonly> The direct parent when it's a widget also, otherwise equals null
 * @property {Boolean}          enabled         - Indicate whether the widget is enabled
 * @property {Boolean}          focused         - Indicate whether the widget is focused
 * @property {ccui.Widget.SIZE_ABSOLUTE|ccui.Widget.SIZE_PERCENT}     sizeType        - The size type of the widget
 * @property {ccui.Widget.TYPE_WIDGET|ccui.Widget.TYPE_CONTAINER}   widgetType      - <@readonly> The type of the widget
 * @property {Boolean}          touchEnabled    - Indicate whether touch events are enabled
 * @property {Boolean}          updateEnabled   - Indicate whether the update function is scheduled
 * @property {Boolean}          bright          - Indicate whether the widget is bright
 * @property {String}           name            - The name of the widget
 * @property {Number}           actionTag       - The action tag of the widget
 */
ccui.Widget = ccui.ProtectedNode.extend(/** @lends ccui.Widget# */{
    _enabled: true,            ///< Highest control of widget
    _bright: true,             ///< is this widget bright
    _touchEnabled: false,       ///< is this widget touch endabled

    _brightStyle: null, ///< bright style

    _touchBeganPosition: null,    ///< touch began point
    _touchMovePosition: null,     ///< touch moved point
    _touchEndPosition: null,      ///< touch ended point

    _touchEventListener: null,
    _touchEventSelector: null,

    _name: "default",
    _widgetType: null,
    _actionTag: 0,
    _customSize: null,
    _layoutParameterDictionary: null,
    _layoutParameterType:0,

    _focused: false,
    _focusEnabled: true,

    _ignoreSize: false,
    _affectByClipping: false,

    _sizeType: null,
    _sizePercent: null,
    _positionType: null,
    _positionPercent: null,
    _hit: false,
    _nodes: null,
    _touchListener: null,
    _className: "Widget",
    _flippedX: false,
    _flippedY: false,
    _opacity: 255,
    _highlight: false,

    _touchEventCallback: null,
    _clickEventListener: null,

    _propagateTouchEvents: true,
    _unifySize: false,

    _callbackName: null,
    _callbackType: null,
    _usingLayoutComponent: false,

    /**
     * Constructor function, override it to extend the construction behavior, remember to call "this._super()" in the extended "ctor" function.
     * @function
     */
    ctor: function () {
        cc.ProtectedNode.prototype.ctor.call(this);
        this._brightStyle = ccui.Widget.BRIGHT_STYLE_NONE;
        this._touchBeganPosition = cc.p(0, 0);
        this._touchMovePosition = cc.p(0, 0);
        this._touchEndPosition = cc.p(0, 0);
        this._widgetType = ccui.Widget.TYPE_WIDGET;
        this._customSize = cc.size(0, 0);
        this._layoutParameterDictionary = {};
        this._sizeType = ccui.Widget.SIZE_ABSOLUTE;
        this._sizePercent = cc.p(0, 0);
        this._positionType = ccui.Widget.POSITION_ABSOLUTE;
        this._positionPercent = cc.p(0, 0);
        this._nodes = [];
        this._layoutParameterType = ccui.LayoutParameter.NONE;
        this.init();                        //TODO
    },

    /**
     * initializes state of widget. please do not call this function by yourself, you should pass the parameters to constructor to initialize it .
     * @returns {boolean}
     */
    init: function () {
        if (cc.ProtectedNode.prototype.init.call(this)) {
            this._layoutParameterDictionary = {};
            this._initRenderer();
            this.setBright(true);

            this.onFocusChanged = this.onFocusChange.bind(this);
            this.onNextFocusedWidget = null;
            this.setAnchorPoint(cc.p(0.5, 0.5));

            this.ignoreContentAdaptWithSize(true);
            return true;
        }
        return false;
    },

    /**
     * Calls updateSizeAndPosition and its parent's onEnter
     * @override
     */
    onEnter: function () {
        var locListener = this._touchListener;
        if (locListener && !locListener._isRegistered() && this._touchEnabled)
            cc.eventManager.addListener(locListener, this);
        if(!this._usingLayoutComponent)
            this.updateSizeAndPosition();
        cc.ProtectedNode.prototype.onEnter.call(this);
    },

    /**
     * Calls unscheduleUpdate and its parent's onExit
     * @override
     */
    onExit: function(){
        this.unscheduleUpdate();
        cc.ProtectedNode.prototype.onExit.call(this);
    },

    _getOrCreateLayoutComponent: function(){
        var layoutComponent = this.getComponent(ccui.__LAYOUT_COMPONENT_NAME);
        if (null == layoutComponent){
            layoutComponent = new ccui.LayoutComponent();
            this.addComponent(layoutComponent);
        }
        return layoutComponent;
    },

    /**
     * The direct parent when it's a widget also, otherwise equals null
     * @returns {ccui.Widget|null}
     */
    getWidgetParent: function () {
        var widget = this.getParent();
        if (widget instanceof ccui.Widget)
            return widget;
        return null;
    },

    _updateContentSizeWithTextureSize: function(size){
        if(this._unifySize){
            this.setContentSize(size);
            return;
        }
        this.setContentSize(this._ignoreSize ? size : this._customSize);
    },

    _isAncestorsEnabled: function(){
        var parentWidget = this._getAncensterWidget(this);
        if (parentWidget == null)
            return true;
        if (parentWidget && !parentWidget.isEnabled())
            return false;

        return parentWidget._isAncestorsEnabled();
    },

    /**
     * Allow widget touch events to propagate to its parents. Set false will disable propagation
     * @since v3.2
     * @param {Boolean} isPropagate
     */
    setPropagateTouchEvents: function(isPropagate){
        this._propagateTouchEvents = isPropagate;
    },

    /**
     * Return whether the widget is propagate touch events to its parents or not
     * @since v3.2
     * @returns {boolean}
     */
    isPropagateTouchEvents: function(){
        return this._propagateTouchEvents;
    },

    /**
     * Specify widget to swallow touches or not
     * @since v3.2
     * @param {Boolean} swallow
     */
    setSwallowTouches: function(swallow){
        if (this._touchListener)
            this._touchListener.setSwallowTouches(swallow);
    },

    /**
     * Return whether the widget is swallowing touch or not
     * @since v3.2
     * @returns {boolean}
     */
    isSwallowTouches: function(){
        if (this._touchListener){
            //return true;                           //todo need test
            return this._touchListener.isSwallowTouches();
        }
        return false;
    },

    _getAncensterWidget: function(node){
        if (null == node)
            return null;

        var parent = node.getParent();
        if (null == parent)
            return null;

        if (parent instanceof ccui.Widget)
            return parent;
        else
            return this._getAncensterWidget(parent.getParent());
    },

    _isAncestorsVisible: function(node){
        if (null == node)
            return true;

        var parent = node.getParent();

        if (parent && !parent.isVisible())
            return false;
        return this._isAncestorsVisible(parent);
    },

    _cleanupWidget: function(){
        //clean up _touchListener
        this._eventDispatcher.removeEventListener(this._touchListener);
        this._touchEnabled = false;
        this._touchListener = null;

        //cleanup focused widget and focus navigation controller
        if (ccui.Widget._focusedWidget === this){
            ccui.Widget._focusedWidget = null;
            ccui.Widget._focusNavigationController = null;
        }
    },

    /**
     * <p>
     *     Sets whether the widget is enabled                                                                                    <br/>
     *     true if the widget is enabled, widget may be touched , false if the widget is disabled, widget cannot be touched.     <br/>
     *     The default value is true, a widget is default to enabled
     * </p>
     * @param {Boolean} enabled
     */
    setEnabled: function (enabled) {
        this._enabled = enabled;
    },

    /**
     * initializes renderer of widget.
     */
    _initRenderer: function () {},

    /**
     * Sets _customSize of ccui.Widget, if ignoreSize is true, the content size is its renderer's contentSize, otherwise the content size is parameter.
     * and updates size percent by parent content size. At last, updates its children's size and position.
     * @param {cc.Size|Number} contentSize content size or width of content size
     * @param {Number} [height]
     * @override
     */
    setContentSize: function(contentSize, height){
        var locWidth = (height === undefined) ? contentSize.width : contentSize;
        var locHeight = (height === undefined) ? contentSize.height : height;
        cc.Node.prototype.setContentSize.call(this, locWidth, locHeight);

        this._customSize.width = locWidth;
        this._customSize.height = locHeight;
        if(this._unifySize){
            //unify size logic
        } else if (this._ignoreSize){
            this._contentSize = this.getVirtualRendererSize();
        }
        if (!this._usingLayoutComponent && this._running) {
            var widgetParent = this.getWidgetParent();
            var pSize = widgetParent ? widgetParent.getContentSize() : this._parent.getContentSize();
            this._sizePercent.x = (pSize.width > 0.0) ? locWidth / pSize.width : 0.0;
            this._sizePercent.y = (pSize.height > 0.0) ? locHeight / pSize.height : 0.0;
        }
        this._onSizeChanged();
    },

    _setWidth: function (w) {
        cc.Node.prototype._setWidth.call(this, w);
        this._customSize.width = w;
        if(this._unifySize){
            //unify size logic
        } else if (this._ignoreSize){
            this._contentSize = this.getVirtualRendererSize();
        }

        if (!this._usingLayoutComponent && this._running) {
            var widgetParent = this.getWidgetParent();
            var locWidth = widgetParent ? widgetParent.width : this._parent.width;
            this._sizePercent.x = locWidth > 0 ? this._customSize.width / locWidth : 0;
        }
        this._onSizeChanged();
    },
    _setHeight: function (h) {
        cc.Node.prototype._setHeight.call(this, h);
        this._customSize.height = h;
        if(this._unifySize){
            //unify size logic
        } else if (this._ignoreSize){
            this._contentSize = this.getVirtualRendererSize();
        }

        if (!this._usingLayoutComponent && this._running) {
            var widgetParent = this.getWidgetParent();
            var locH = widgetParent ? widgetParent.height : this._parent.height;
            this._sizePercent.y = locH > 0 ? this._customSize.height / locH : 0;
        }
        this._onSizeChanged();
    },

    /**
     * Changes the percent that is widget's percent size
     * @param {cc.Point} percent that is widget's percent size, width and height value from 0 to 1.
     */
    setSizePercent: function (percent) {
        if(this._usingLayoutComponent){
            var component = this._getOrCreateLayoutComponent();
            component.setUsingPercentContentSize(true);
            component.setPercentContentSize(percent);
            component.refreshLayout();            
            return;
        }

        this._sizePercent.x = percent.x;
        this._sizePercent.y = percent.y;
        var width = this._customSize.width, height = this._customSize.height;
        if (this._running) {
            var widgetParent = this.getWidgetParent();
            if (widgetParent) {
                width = widgetParent.width * percent.x;
                height = widgetParent.height * percent.y;
            } else {
                width = this._parent.width * percent.x;
                height = this._parent.height * percent.y;
            }
        }
        if (this._ignoreSize)
            this.setContentSize(this.getVirtualRendererSize());
        else
            this.setContentSize(width, height);

        this._customSize.width = width;
        this._customSize.height = height;
    },

    _setWidthPercent: function (percent) {
        this._sizePercent.x = percent;
        var width = this._customSize.width;
        if (this._running) {
            var widgetParent = this.getWidgetParent();
            width = (widgetParent ? widgetParent.width : this._parent.width) * percent;
        }
        if (this._ignoreSize)
            this._setWidth(this.getVirtualRendererSize().width);
        else
            this._setWidth(width);
        this._customSize.width = width;
    },
    _setHeightPercent: function (percent) {
        this._sizePercent.y = percent;
        var height = this._customSize.height;
        if (this._running) {
            var widgetParent = this.getWidgetParent();
            height = (widgetParent ? widgetParent.height : this._parent.height) * percent;
        }
        if (this._ignoreSize)
            this._setHeight(this.getVirtualRendererSize().height);
        else
            this._setHeight(height);
        this._customSize.height = height;
    },

    /**
     * updates its size by size type and its position by position type.
     * @param {cc.Size} [parentSize] parent size
     */
    updateSizeAndPosition: function (parentSize) {
        if(!parentSize){
            var widgetParent = this.getWidgetParent();
            if(widgetParent)
                parentSize = widgetParent.getLayoutSize();
            else
                parentSize = this._parent.getContentSize();
        }

        switch (this._sizeType) {
            case ccui.Widget.SIZE_ABSOLUTE:
                if(this._ignoreSize)
                    this.setContentSize(this.getVirtualRendererSize());
                else
                    this.setContentSize(this._customSize);
                this._sizePercent.x = (parentSize.width > 0) ? this._customSize.width / parentSize.width : 0;
                this._sizePercent.y = (parentSize.height > 0) ? this._customSize.height / parentSize.height : 0;
                break;
            case ccui.Widget.SIZE_PERCENT:
                var cSize = cc.size(parentSize.width * this._sizePercent.x , parentSize.height * this._sizePercent.y);
                if(this._ignoreSize)
                    this.setContentSize(this.getVirtualRendererSize());
                else
                    this.setContentSize(cSize);
                this._customSize.width = cSize.width;
                this._customSize.height = cSize.height;
                break;
            default:
                break;
        }
        this._onSizeChanged();
        var absPos = this.getPosition();
        switch (this._positionType) {
            case ccui.Widget.POSITION_ABSOLUTE:
                if (parentSize.width <= 0 || parentSize.height <= 0) {
                    this._positionPercent.x = this._positionPercent.y = 0;
                } else {
                    this._positionPercent.x = absPos.x / parentSize.width;
                    this._positionPercent.y = absPos.y / parentSize.height;
                }
                break;
            case ccui.Widget.POSITION_PERCENT:
                absPos = cc.p(parentSize.width * this._positionPercent.x, parentSize.height * this._positionPercent.y);
                break;
            default:
                break;
        }
        if(this._parent instanceof ccui.ImageView){
            var renderer = this._parent._imageRenderer;
            if(renderer && !renderer._textureLoaded)
                return;
        }
        this.setPosition(absPos);
    },

    /**TEXTURE_RES_TYPE
     * Changes the size type of widget.
     * @param {ccui.Widget.SIZE_ABSOLUTE|ccui.Widget.SIZE_PERCENT} type that is widget's size type
     */
    setSizeType: function (type) {
        this._sizeType = type;
        if (this._usingLayoutComponent) {
            var component = this._getOrCreateLayoutComponent();
            component.setUsingPercentContentSize(this._sizeType === ccui.SIZE_PERCENT);
        }
    },

    /**
     * Gets the size type of widget.
     * @returns {ccui.Widget.SIZE_ABSOLUTE|ccui.Widget.SIZE_PERCENT} that is widget's size type
     */
    getSizeType: function () {
        return this._sizeType;
    },

    /**
     * Ignore the widget size
     * @param {Boolean} ignore true that widget will ignore it's size, use texture size, false otherwise. Default value is true.
     */
    ignoreContentAdaptWithSize: function (ignore) {
        if(this._unifySize){
            this.setContentSize(this._customSize);
            return;
        }

        if(this._ignoreSize === ignore)
            return;

        this._ignoreSize = ignore;
        this.setContentSize( ignore ? this.getVirtualRendererSize() : this._customSize );
        //this._onSizeChanged();
    },

    /**
     * Gets whether ignore the content size (custom size)
     * @returns {boolean}  true that widget will ignore it's size, use texture size, false otherwise.
     */
    isIgnoreContentAdaptWithSize: function () {
        return this._ignoreSize;
    },

    /**
     * Get custom size of ccui.Widget
     * @returns {cc.Size}
     */
    getCustomSize: function () {
        return cc.size(this._customSize);
    },

    /**
     * Gets layout size of ccui.Widget.
     * @returns {cc.Size}
     */
    getLayoutSize: function(){
        return cc.size(this._contentSize);
    },

    /**
     * Returns size percent of ccui.Widget
     * @returns {cc.Point}
     */
    getSizePercent: function () {
        if(this._usingLayoutComponent){
            var component = this._getOrCreateLayoutComponent();
            this._sizePercent = component.getPercentContentSize();
        }
        return this._sizePercent;
    },
    _getWidthPercent: function () {
        return this._sizePercent.x;
    },
    _getHeightPercent: function () {
        return this._sizePercent.y;
    },

    /**
     *  Gets world position of ccui.Widget.
     * @returns {cc.Point} world position of ccui.Widget.
     */
    getWorldPosition: function () {
        return this.convertToWorldSpace(cc.p(this._anchorPoint.x * this._contentSize.width, this._anchorPoint.y * this._contentSize.height));
    },

    /**
     * Gets the Virtual Renderer of widget.
     * @returns {ccui.Widget}
     */
    getVirtualRenderer: function () {
        return this;
    },

    /**
     * Gets the content size of widget.  Content size is widget's texture size.
     */
    getVirtualRendererSize:function(){
        return cc.size(this._contentSize);
    },

    /**
     * call back function called when size changed.
     */
    _onSizeChanged: function () {
        if(!this._usingLayoutComponent){
            var locChildren =  this.getChildren();
            for (var i = 0, len = locChildren.length; i < len; i++) {
                var child = locChildren[i];
                if(child instanceof ccui.Widget)
                    child.updateSizeAndPosition();
            }
        }
    },

    /**
     * Sets whether the widget is touch enabled. The default value is false, a widget is default to touch disabled
     * @param {Boolean} enable  true if the widget is touch enabled, false if the widget is touch disabled.
     */
    setTouchEnabled: function (enable) {
        if (this._touchEnabled === enable)
            return;

        this._touchEnabled = enable;                                  //TODO need consider remove and re-add.
        if (this._touchEnabled) {
            if(!this._touchListener)
                this._touchListener = cc.EventListener.create({
                    event: cc.EventListener.TOUCH_ONE_BY_ONE,
                    swallowTouches: true,
                    onTouchBegan: this.onTouchBegan.bind(this),
                    onTouchMoved: this.onTouchMoved.bind(this),
                    onTouchEnded: this.onTouchEnded.bind(this)
                });
            cc.eventManager.addListener(this._touchListener, this);
        } else {
            cc.eventManager.removeListener(this._touchListener);
        }
    },

    /**
     * Returns whether or not touch is enabled.
     * @returns {boolean} true if the widget is touch enabled, false if the widget is touch disabled.
     */
    isTouchEnabled: function () {
        return this._touchEnabled;
    },

    /**
     * Determines if the widget is highlighted
     * @returns {boolean} true if the widget is highlighted, false if the widget is not highlighted .
     */
    isHighlighted: function(){
        return this._highlight;
    },

    /**
     * Sets whether the widget is highlighted. The default value is false, a widget is default to not highlighted
     * @param highlight true if the widget is highlighted, false if the widget is not highlighted.
     */
    setHighlighted:function(highlight){
        if (highlight === this._highlight)
            return;
        this._highlight = highlight;
        if (this._bright) {
            if (this._highlight)
                this.setBrightStyle(ccui.Widget.BRIGHT_STYLE_HIGH_LIGHT);
            else
                this.setBrightStyle(ccui.Widget.BRIGHT_STYLE_NORMAL);
        } else
            this._onPressStateChangedToDisabled();
    },

    /**
     * Determines if the widget is on focused
     * @returns {boolean} whether the widget is focused or not
     */
    isFocused: function () {
        return this._focused;
    },

    /**
     * Sets whether the widget is on focused
     * The default value is false, a widget is default to not on focused
     * @param {boolean} focus  pass true to let the widget get focus or pass false to let the widget lose focus
     */
    setFocused: function (focus) {
        this._focused = focus;
        //make sure there is only one focusedWidget
        if (focus){
            ccui.Widget._focusedWidget = this;
            if(ccui.Widget._focusNavigationController)
                ccui.Widget._focusNavigationController._setFirstFocsuedWidget(this);
        }
    },

    /**
     * returns whether the widget could accept focus.
     * @returns {boolean} true represent the widget could accept focus, false represent the widget couldn't accept focus
     */
    isFocusEnabled: function(){
        return this._focusEnabled;
    },

    /**
     * sets whether the widget could accept focus.
     * @param {Boolean} enable true represent the widget could accept focus, false represent the widget couldn't accept focus
     */
    setFocusEnabled: function(enable){
        this._focusEnabled = enable;
    },

    /**
     * <p>
     *     When a widget is in a layout, you could call this method to get the next focused widget within a specified direction. <br/>
     *     If the widget is not in a layout, it will return itself
     * </p>
     * @param direction the direction to look for the next focused widget in a layout
     * @param current  the current focused widget
     * @return  the next focused widget in a layout
     */
    findNextFocusedWidget: function( direction, current){
        if (null === this.onNextFocusedWidget || null == this.onNextFocusedWidget(direction) ) {
            var isLayout = current instanceof ccui.Layout;
            if (this.isFocused() || isLayout) {
                var layout = this.getParent();
                if (null === layout || !(layout instanceof ccui.Layout)){
                    //the outer layout's default behaviour is : loop focus
                    if (isLayout)
                        return current.findNextFocusedWidget(direction, current);
                    return current;
                } else
                    return layout.findNextFocusedWidget(direction, current);
            } else
                return current;
        } else {
            var getFocusWidget = this.onNextFocusedWidget(direction);
            this.dispatchFocusEvent(this, getFocusWidget);
            return getFocusWidget;
        }
    },

    /**
     * when a widget calls this method, it will get focus immediately.
     */
    requestFocus: function(){
        if (this === ccui.Widget._focusedWidget)
            return;
        this.dispatchFocusEvent(ccui.Widget._focusedWidget, this);
    },

    /**
     * no matter what widget object you call this method on , it will return you the exact one focused widget
     */
    getCurrentFocusedWidget: function(){
        return ccui.Widget._focusedWidget;
    },

    /**
     * <p>
     *    When a widget lose/get focus, this method will be called. Be Caution when you provide your own version,       <br/>
     *    you must call widget.setFocused(true/false) to change the focus state of the current focused widget;
     * </p>
     */
    onFocusChanged: null,

    /**
     * use this function to manually specify the next focused widget regards to each direction
     */
    onNextFocusedWidget: null,

    /**
     * Sends the touch event to widget's parent, its subclass will override it, e.g. ccui.ScrollView, ccui.PageView
     * @param {Number}  eventType
     * @param {ccui.Widget} sender
     * @param {cc.Touch} touch
     */
    interceptTouchEvent: function(eventType, sender, touch){
        var widgetParent = this.getWidgetParent();
        if (widgetParent)
            widgetParent.interceptTouchEvent(eventType,sender,touch);
    },

    /**
     * This method is called when a focus change event happens
     * @param {ccui.Widget} widgetLostFocus
     * @param {ccui.Widget} widgetGetFocus
     */
    onFocusChange: function(widgetLostFocus, widgetGetFocus){
        //only change focus when there is indeed a get&lose happens
        if (widgetLostFocus)
            widgetLostFocus.setFocused(false);
        if (widgetGetFocus)
            widgetGetFocus.setFocused(true);
    },

    /**
     * Dispatch a EventFocus through a EventDispatcher
     * @param {ccui.Widget} widgetLostFocus
     * @param {ccui.Widget} widgetGetFocus
     */
    dispatchFocusEvent: function(widgetLostFocus, widgetGetFocus){
        //if the widgetLoseFocus doesn't get focus, it will use the previous focused widget instead
        if (widgetLostFocus && !widgetLostFocus.isFocused())
            widgetLostFocus = ccui.Widget._focusedWidget;

        if (widgetGetFocus !== widgetLostFocus){
            if (widgetGetFocus && widgetGetFocus.onFocusChanged)
                widgetGetFocus.onFocusChanged(widgetLostFocus, widgetGetFocus);
            if (widgetLostFocus && widgetGetFocus.onFocusChanged)
                widgetLostFocus.onFocusChanged(widgetLostFocus, widgetGetFocus);
            cc.eventManager.dispatchEvent(new cc.EventFocus(widgetLostFocus, widgetGetFocus));
        }
    },

    /**
     *  Sets whether the widget is bright. The default value is true, a widget is default to bright
     * @param {Boolean} bright true if the widget is bright, false if the widget is dark.
     */
    setBright: function (bright) {
        this._bright = bright;
        if (this._bright) {
            this._brightStyle = ccui.Widget.BRIGHT_STYLE_NONE;
            this.setBrightStyle(ccui.Widget.BRIGHT_STYLE_NORMAL);
        } else
            this._onPressStateChangedToDisabled();
    },

    /**
     * To set the bright style of ccui.Widget.
     * @param {Number} style BRIGHT_NORMAL the widget is normal state, BRIGHT_HIGHLIGHT the widget is height light state.
     */
    setBrightStyle: function (style) {
        if (this._brightStyle === style)
            return;

        style = style || ccui.Widget.BRIGHT_STYLE_NORMAL;
        this._brightStyle = style;
        switch (this._brightStyle) {
            case ccui.Widget.BRIGHT_STYLE_NORMAL:
                this._onPressStateChangedToNormal();
                break;
            case ccui.Widget.BRIGHT_STYLE_HIGH_LIGHT:
                this._onPressStateChangedToPressed();
                break;
            default:
                break;
        }
    },

    _onPressStateChangedToNormal: function () {},

    _onPressStateChangedToPressed: function () {},

    _onPressStateChangedToDisabled: function () {},

    _updateChildrenDisplayedRGBA: function(){
        this.setColor(this.getColor());
        this.setOpacity(this.getOpacity());
    },

    /**
     * A call back function when widget lost of focus.
     */
    didNotSelectSelf: function () {},

    /**
     * <p>
     *    The callback of touch began event.                                                               <br/>
     *    If the bounding box of ccui.Widget contains the touch point, it will do the following things:    <br/>
     *      1. sets highlight state,                                                                       <br/>
     *      2. sends event to parent widget by interceptTouchEvent                                         <br/>
     *      3. calls the callback of touch began event.                                                    <br/>
     *      4. returns true,                                                                               <br/>
     *    otherwise returns false directly.                                                                <br/>
     * </p>
     * @override
     * @param {cc.Touch} touch
     * @param {cc.Event} event
     * @returns {boolean}
     */
    onTouchBegan: function (touch, event) {
        this._hit = false;
        if (this.isVisible() && this.isEnabled() && this._isAncestorsEnabled() && this._isAncestorsVisible(this) ){
            var touchPoint = touch.getLocation();
            this._touchBeganPosition.x = touchPoint.x;
            this._touchBeganPosition.y = touchPoint.y;
            if(this.hitTest(this._touchBeganPosition) && this.isClippingParentContainsPoint(this._touchBeganPosition))
                this._hit = true;
        }
        if (!this._hit) {
            return false;
        }
        this.setHighlighted(true);

        /*
         * Propagate touch events to its parents
         */
        if (this._propagateTouchEvents) {
            this.propagateTouchEvent(ccui.Widget.TOUCH_BEGAN, this, touch);
        }

        this._pushDownEvent();
        return true;
    },

    propagateTouchEvent: function(event, sender, touch){
        var widgetParent = this.getWidgetParent();
        if (widgetParent){
            widgetParent.interceptTouchEvent(event, sender, touch);
        }
    },

    /**
     * <p>
     *    The callback of touch moved event.                                                                                                <br/>
     *    It sets the highlight state by touch, sends event to parent widget by interceptTouchEvent and calls the callback of touch moved event.
     * </p>
     * @param {cc.Touch} touch
     * @param {cc.Event} event
     */
    onTouchMoved: function (touch, event) {
        var touchPoint = touch.getLocation();
        this._touchMovePosition.x = touchPoint.x;
        this._touchMovePosition.y = touchPoint.y;
        this.setHighlighted(this.hitTest(touchPoint));
        /*
         * Propagate touch events to its parents
         */
        if (this._propagateTouchEvents)
            this.propagateTouchEvent(ccui.Widget.TOUCH_MOVED, this, touch);
        this._moveEvent();
    },

    /**
     * <p>
     *      The callback of touch end event
     *      It sends event to parent widget by interceptTouchEvent,
     *      calls the callback of touch end event (highlight= true) or touch canceled event (highlight= false).
     *      sets the highlight state to false ,
     * </p>
     * @param touch
     * @param event
     */
    onTouchEnded: function (touch, event) {
        var touchPoint = touch.getLocation();
        this._touchEndPosition.x = touchPoint.x;
        this._touchEndPosition.y = touchPoint.y;
        /*
         * Propagate touch events to its parents
         */
        if (this._propagateTouchEvents)
            this.propagateTouchEvent(ccui.Widget.TOUCH_ENDED, this, touch);

        var highlight = this._highlight;
        this.setHighlighted(false);
        if (highlight)
            this._releaseUpEvent();
        else
            this._cancelUpEvent();
    },

    /**
     * A call back function called when widget is selected, and on touch canceled.
     * @param {cc.Point} touchPoint
     */
    onTouchCancelled: function (touchPoint) {
        this.setHighlighted(false);
        this._cancelUpEvent();
    },

    /**
     * A call back function called when widget is selected, and on touch long clicked.
     * @param {cc.Point} touchPoint
     */
    onTouchLongClicked: function (touchPoint) {
        this.longClickEvent();
    },

    //call back function called widget's state changed to dark.
    _pushDownEvent: function () {
        if (this._touchEventCallback)
            this._touchEventCallback(this, ccui.Widget.TOUCH_BEGAN);
        if (this._touchEventListener && this._touchEventSelector)
            this._touchEventSelector.call(this._touchEventListener, this, ccui.Widget.TOUCH_BEGAN);
    },

    _moveEvent: function () {
        if (this._touchEventCallback)
            this._touchEventCallback(this, ccui.Widget.TOUCH_MOVED);
        if (this._touchEventListener && this._touchEventSelector)
            this._touchEventSelector.call(this._touchEventListener, this, ccui.Widget.TOUCH_MOVED);
    },

    _releaseUpEvent: function () {
        if (this._touchEventCallback)
            this._touchEventCallback(this, ccui.Widget.TOUCH_ENDED);
        if (this._touchEventListener && this._touchEventSelector)
            this._touchEventSelector.call(this._touchEventListener, this, ccui.Widget.TOUCH_ENDED);
        if (this._clickEventListener)
            this._clickEventListener(this);
    },

    _cancelUpEvent: function () {
        if (this._touchEventCallback)
            this._touchEventCallback(this, ccui.Widget.TOUCH_CANCELED);
        if (this._touchEventListener && this._touchEventSelector)
            this._touchEventSelector.call(this._touchEventListener, this, ccui.Widget.TOUCH_CANCELED);
    },

    longClickEvent: function () {
        //TODO it will implement in v3.1
    },

    /**
     * Sets the touch event target/selector of the ccui.Widget
     * @param {Function} selector
     * @param {Object} target
     */
    addTouchEventListener: function (selector, target) {
        if(target === undefined)
            this._touchEventCallback = selector;
        else {
            this._touchEventSelector = selector;
            this._touchEventListener = target;
        }
    },

    addClickEventListener: function(callback){
        this._clickEventListener = callback;
    },

    /**
     * Checks a point if is in widget's space
     * @param {cc.Point} pt
     * @returns {boolean} true if the point is in widget's space, false otherwise.
     */
    hitTest: function (pt) {
        var bb = cc.rect(0,0, this._contentSize.width, this._contentSize.height);
        return cc.rectContainsPoint(bb, this.convertToNodeSpace(pt));
    },

    /**
     * returns whether clipping parent widget contains point.
     * @param {cc.Point} pt location point
     * @returns {Boolean}
     */
    isClippingParentContainsPoint: function(pt){
        this._affectByClipping = false;
        var parent = this.getParent();
        var clippingParent = null;
        while (parent) {
            if (parent instanceof ccui.Layout) {
                if (parent.isClippingEnabled()) {
                    this._affectByClipping = true;
                    clippingParent = parent;
                    break;
                }
            }
            parent = parent.getParent();
        }

        if (!this._affectByClipping)
            return true;

        if (clippingParent) {
            if (clippingParent.hitTest(pt))
                return clippingParent.isClippingParentContainsPoint(pt);
            return false;
        }
        return true;
    },

    /**
     * Calls the checkChildInfo of widget's parent, its subclass will override it.
     * @param {number} handleState
     * @param {ccui.Widget} sender
     * @param {cc.Point} touchPoint
     */
    checkChildInfo: function (handleState, sender, touchPoint) {
        var widgetParent = this.getWidgetParent();
        if (widgetParent)
            widgetParent.checkChildInfo(handleState, sender, touchPoint);
    },

    /**
     * Changes the position (x,y) of the widget .
     * The original point (0,0) is at the left-bottom corner of screen.
     * @override
     * @param {cc.Point|Number} pos
     * @param {Number} [posY]
     */
    setPosition: function (pos, posY) {
        if (!this._usingLayoutComponent && this._running) {
            var widgetParent = this.getWidgetParent();
            if (widgetParent) {
                var pSize = widgetParent.getContentSize();
                if (pSize.width <= 0 || pSize.height <= 0) {
                    this._positionPercent.x = 0;
                    this._positionPercent.y = 0;
                } else {
                    if (posY === undefined) {
                        this._positionPercent.x = pos.x / pSize.width;
                        this._positionPercent.y = pos.y / pSize.height;
                    } else {
                        this._positionPercent.x = pos / pSize.width;
                        this._positionPercent.y = posY / pSize.height;
                    }
                }
            }
        }

        cc.Node.prototype.setPosition.call(this, pos, posY);
        //this._positionType = ccui.Widget.POSITION_ABSOLUTE;
    },

    setPositionX: function (x) {
        if (this._running) {
            var widgetParent = this.getWidgetParent();
            if (widgetParent) {
                var pw = widgetParent.width;
                if (pw <= 0)
                    this._positionPercent.x = 0;
                else
                    this._positionPercent.x = x / pw;
            }
        }

        cc.Node.prototype.setPositionX.call(this, x);
    },
    setPositionY: function (y) {
        if (this._running) {
            var widgetParent = this.getWidgetParent();
            if (widgetParent) {
                var ph = widgetParent.height;
                if (ph <= 0)
                    this._positionPercent.y = 0;
                else
                    this._positionPercent.y = y / ph;
            }
        }

        cc.Node.prototype.setPositionY.call(this, y);
    },

    /**
     * Changes the position (x,y) of the widget
     * @param {cc.Point} percent
     */
    setPositionPercent: function (percent) {
        if (this._usingLayoutComponent){
            var component = this._getOrCreateLayoutComponent();
            component.setPositionPercentX(percent.x);
            component.setPositionPercentY(percent.y);
            component.refreshLayout();
            return;
        }else{
            this._setXPercent(percent.x);
            this._setYPercent(percent.y);
        }
        this._renderCmd.setDirtyFlag(cc.Node._dirtyFlags.transformDirty);
    },
    _setXPercent: function (percent) {
        if (this._usingLayoutComponent){
            var component = this._getOrCreateLayoutComponent();
            component.setPositionPercentX(percent.x);
            component.refreshLayout();
            return;
        }
        this._positionPercent.x = percent;
    },
    _setYPercent: function (percent) {
        if (this._usingLayoutComponent){
            var component = this._getOrCreateLayoutComponent();
            component.setPositionPercentY(percent.x);
            component.refreshLayout();
            return;
        }
        this._positionPercent.y = percent;
    },

    /**
     * Gets the percent (x,y) of the widget
     * @returns {cc.Point} The percent (x,y) of the widget in OpenGL coordinates
     */
    getPositionPercent: function () {
        if (this._usingLayoutComponent) {
            var component = this._getOrCreateLayoutComponent();
            this._positionPercent.x = component.getPositionPercentX();
            this._positionPercent.y = component.getPositionPercentY();
        }
        return cc.p(this._positionPercent);
    },

    _getXPercent: function () {
        if (this._usingLayoutComponent) {
            var component = this._getOrCreateLayoutComponent();
            this._positionPercent.x = component.getPositionPercentX();
            this._positionPercent.y = component.getPositionPercentY();
        }
        return this._positionPercent.x;
    },
    _getYPercent: function () {
        if (this._usingLayoutComponent) {
            var component = this._getOrCreateLayoutComponent();
            this._positionPercent.x = component.getPositionPercentX();
            this._positionPercent.y = component.getPositionPercentY();
        }
        return this._positionPercent.y;
    },

    /**
     * Changes the position type of the widget
     * @param {Number} type  the position type of widget
     */
    setPositionType: function (type) {
        this._positionType = type;
        if(this._usingLayoutComponent){
            var component = this._getOrCreateLayoutComponent();
            if (type === ccui.POSITION_ABSOLUTE){
                component.setPositionPercentXEnabled(false);
                component.setPositionPercentYEnabled(false);
            } else {
                component.setPositionPercentXEnabled(true);
                component.setPositionPercentYEnabled(true);
            }
        }
        this._renderCmd.setDirtyFlag(cc.Node._dirtyFlags.transformDirty);
    },

    /**
     * Gets the position type of the widget
     * @returns {Number} the position type of widget
     */
    getPositionType: function () {
        return this._positionType;
    },

    /**
     * Sets whether the widget should be flipped horizontally or not.
     * @param {Boolean} flipX true if the widget should be flipped horizontally, false otherwise.
     */
    setFlippedX: function (flipX) {
        var realScale = this.getScaleX();
        this._flippedX = flipX;
        this.setScaleX(realScale);
    },

    /**
     * <p>
     *   Returns the flag which indicates whether the widget is flipped horizontally or not.             <br/>
     *   It only flips the texture of the widget, and not the texture of the widget's children.          <br/>
     *   Also, flipping the texture doesn't alter the anchorPoint.                                       <br/>
     *   If you want to flip the anchorPoint too, and/or to flip the children too use:                   <br/>
     *   widget.setScaleX(sprite.getScaleX() * -1);
     * </p>
     * @returns {Boolean} true if the widget is flipped horizontally, false otherwise.
     */
    isFlippedX: function () {
        return this._flippedX;
    },

    /**
     * Sets whether the widget should be flipped vertically or not.
     * @param {Boolean} flipY  true if the widget should be flipped vertically, false otherwise.
     */
    setFlippedY: function (flipY) {
        var realScale = this.getScaleY();
        this._flippedY = flipY;
        this.setScaleY(realScale);
    },

    /**
     * <p>
     *     Return the flag which indicates whether the widget is flipped vertically or not.                <br/>
     *     It only flips the texture of the widget, and not the texture of the widget's children.          <br/>
     *     Also, flipping the texture doesn't alter the anchorPoint.                                       <br/>
     *     If you want to flip the anchorPoint too, and/or to flip the children too use:                   <br/>
     *     widget.setScaleY(widget.getScaleY() * -1);
     * </p>
     * @returns {Boolean} true if the widget is flipped vertically, false otherwise.
     */
    isFlippedY: function () {
        return this._flippedY;
    },

    _adaptRenderers: function(){},

    /**
     * Determines if the widget is bright
     * @returns {boolean} true if the widget is bright, false if the widget is dark.
     */
    isBright: function () {
        return this._bright;
    },

    /**
     * Determines if the widget is enabled
     * @returns {boolean}
     */
    isEnabled: function () {
        return this._enabled;
    },

    /**
     * Gets the left boundary position of this widget.
     * @returns {number}
     */
    getLeftBoundary: function () {
        return this.getPositionX() - this._getAnchorX() * this._contentSize.width;
    },

    /**
     * Gets the bottom boundary position of this widget.
     * @returns {number}
     */
    getBottomBoundary: function () {
        return this.getPositionY() - this._getAnchorY() * this._contentSize.height;
    },

    /**
     * Gets the right boundary position of this widget.
     * @returns {number}
     */
    getRightBoundary: function () {
        return this.getLeftBoundary() + this._contentSize.width;
    },

    /**
     * Gets the top boundary position of this widget.
     * @returns {number}
     */
    getTopBoundary: function () {
        return this.getBottomBoundary() + this._contentSize.height;
    },

    /**
     * Gets the position of touch began event.
     * @returns {cc.Point}
     */
    getTouchBeganPosition: function(){
         return cc.p(this._touchBeganPosition);
    },

    /**
     * Gets the position of touch moved event
     * @returns {cc.Point}
     */
    getTouchMovePosition: function(){
        return cc.p(this._touchMovePosition);
    },

    /**
     * Gets the position of touch end event
     * @returns {cc.Point}
     */
    getTouchEndPosition:function(){
        return cc.p(this._touchEndPosition);
    },

    /**
     * get widget type
     * @returns {ccui.Widget.TYPE_WIDGET|ccui.Widget.TYPE_CONTAINER}
     */
    getWidgetType: function () {
        return this._widgetType;
    },

    /**
     * Gets LayoutParameter of widget.
     * @param {ccui.LayoutParameter} parameter
     */
    setLayoutParameter: function (parameter) {
        if(!parameter)
            return;
        this._layoutParameterDictionary[parameter.getLayoutType()] = parameter;
        this._layoutParameterType = parameter.getLayoutType();
    },

    /**
     * Gets layout parameter
     * @param {ccui.LayoutParameter.NONE|ccui.LayoutParameter.LINEAR|ccui.LayoutParameter.RELATIVE} type
     * @returns {ccui.LayoutParameter}
     */
    getLayoutParameter: function (type) {
        type = type || this._layoutParameterType;
        return this._layoutParameterDictionary[type];
    },

    /**
     * Returns the "class name" of widget.
     * @returns {string}
     */
    getDescription: function () {
        return "Widget";
    },

    /**
     * Clones a new widget.
     * @returns {ccui.Widget}
     */
    clone: function () {
        var clonedWidget = this._createCloneInstance();
        clonedWidget._copyProperties(this);
        clonedWidget._copyClonedWidgetChildren(this);
        return clonedWidget;
    },

    _createCloneInstance: function () {
        return new ccui.Widget();
    },

    _copyClonedWidgetChildren: function (model) {
        var widgetChildren = model.getChildren();
        for (var i = 0; i < widgetChildren.length; i++) {
            var locChild = widgetChildren[i];
            if (locChild instanceof ccui.Widget)
                this.addChild(locChild.clone());
        }
    },

    _copySpecialProperties: function (model) {},

    _copyProperties: function (widget) {
        this.setEnabled(widget.isEnabled());
        this.setVisible(widget.isVisible());
        this.setBright(widget.isBright());
        this.setTouchEnabled(widget.isTouchEnabled());
        this.setLocalZOrder(widget.getLocalZOrder());
        this.setTag(widget.getTag());
        this.setName(widget.getName());
        this.setActionTag(widget.getActionTag());

        this._ignoreSize = widget._ignoreSize;

        this.setContentSize(widget._contentSize);
        this._customSize.width = widget._customSize.width;
        this._customSize.height = widget._customSize.height;

        this._copySpecialProperties(widget);
        this._sizeType = widget.getSizeType();
        this._sizePercent.x = widget._sizePercent.x;
        this._sizePercent.y = widget._sizePercent.y;

        this._positionType = widget._positionType;
        this._positionPercent.x = widget._positionPercent.x;
        this._positionPercent.y = widget._positionPercent.y;

        this.setPosition(widget.getPosition());
        this.setAnchorPoint(widget.getAnchorPoint());
        this.setScaleX(widget.getScaleX());
        this.setScaleY(widget.getScaleY());
        this.setRotation(widget.getRotation());
        this.setRotationX(widget.getRotationX());
        this.setRotationY(widget.getRotationY());
        this.setFlippedX(widget.isFlippedX());
        this.setFlippedY(widget.isFlippedY());
        this.setColor(widget.getColor());
        this.setOpacity(widget.getOpacity());

        this._touchEventCallback = widget._touchEventCallback;
        this._touchEventListener = widget._touchEventListener;
        this._touchEventSelector = widget._touchEventSelector;
        this._clickEventListener = widget._clickEventListener;
        this._focused = widget._focused;
        this._focusEnabled = widget._focusEnabled;
        this._propagateTouchEvents = widget._propagateTouchEvents;

        for (var key in widget._layoutParameterDictionary) {
            var parameter = widget._layoutParameterDictionary[key];
            if (parameter)
                this.setLayoutParameter(parameter.clone());
        }
        this._onSizeChanged();
    },

    /*temp action*/
    setActionTag: function (tag) {
        this._actionTag = tag;
    },

    getActionTag: function () {
        return this._actionTag;
    },

    /**
     * Gets the left boundary position of this widget.
     * @deprecated since v3.0, please use getLeftBoundary instead.
     * @returns {number}
     */
    getLeftInParent: function(){
        cc.log("getLeftInParent is deprecated. Please use getLeftBoundary instead.");
        return this.getLeftBoundary();
    },

    /**
     * Gets the bottom boundary position of this widget.
     * @deprecated since v3.0, please use getBottomBoundary instead.
     * @returns {number}
     */
    getBottomInParent: function(){
        cc.log("getBottomInParent is deprecated. Please use getBottomBoundary instead.");
        return this.getBottomBoundary();
    },

    /**
     * Gets the right boundary position of this widget.
     * @deprecated since v3.0, please use getRightBoundary instead.
     * @returns {number}
     */
    getRightInParent: function(){
        cc.log("getRightInParent is deprecated. Please use getRightBoundary instead.");
        return this.getRightBoundary();
    },

    /**
     * Gets the top boundary position of this widget.
     * @deprecated since v3.0, please use getTopBoundary instead.
     * @returns {number}
     */
    getTopInParent: function(){
        cc.log("getTopInParent is deprecated. Please use getTopBoundary instead.");
        return this.getTopBoundary();
    },

    /**
     * Gets the touch end point of widget when widget is selected.
     * @deprecated since v3.0, please use getTouchEndPosition instead.
     * @returns {cc.Point} the touch end point.
     */
    getTouchEndPos: function () {
        cc.log("getTouchEndPos is deprecated. Please use getTouchEndPosition instead.");
        return this.getTouchEndPosition();
    },

    /**
     *Gets the touch move point of widget when widget is selected.
     * @deprecated since v3.0, please use getTouchMovePosition instead.
     * @returns {cc.Point} the touch move point.
     */
    getTouchMovePos: function () {
        cc.log("getTouchMovePos is deprecated. Please use getTouchMovePosition instead.");
        return this.getTouchMovePosition();
    },

    /**
     * Checks a point if in parent's area.
     * @deprecated since v3.0, please use isClippingParentContainsPoint instead.
     * @param {cc.Point} pt
     * @returns {Boolean}
     */
    clippingParentAreaContainPoint: function (pt) {
        cc.log("clippingParentAreaContainPoint is deprecated. Please use isClippingParentContainsPoint instead.");
        this.isClippingParentContainsPoint(pt);
    },

    /**
     * Gets the touch began point of widget when widget is selected.
     * @deprecated since v3.0, please use getTouchBeganPosition instead.
     * @returns {cc.Point} the touch began point.
     */
    getTouchStartPos: function () {
        cc.log("getTouchStartPos is deprecated. Please use getTouchBeganPosition instead.");
        return this.getTouchBeganPosition();
    },

    /**
     * Changes the size that is widget's size
     * @deprecated since v3.0, please use setContentSize instead.
     * @param {cc.Size} size  that is widget's size
     */
    setSize: function (size) {
        this.setContentSize(size);
    },

    /**
     * Returns size of widget
     * @deprecated since v3.0, please use getContentSize instead.
     * @returns {cc.Size}
     */
    getSize: function () {
        return this.getContentSize();
    },

    /**
     * Adds a node for widget (this function is deleted in -x)
     * @param {cc.Node} node
     * @param {Number} zOrder
     * @param {Number} tag
     * @deprecated since v3.0, please use addChild instead.
     */
    addNode: function (node, zOrder, tag) {
        if (node instanceof ccui.Widget) {
            cc.log("Please use addChild to add a Widget.");
            return;
        }
        cc.Node.prototype.addChild.call(this, node, zOrder, tag);
        this._nodes.push(node);
    },

    /**
     * Gets node by tag
     * @deprecated since v3.0, please use getChildByTag instead.
     * @param {Number} tag
     * @returns {cc.Node}
     */
    getNodeByTag: function (tag) {
        var _nodes = this._nodes;
        for (var i = 0; i < _nodes.length; i++) {
            var node = _nodes[i];
            if (node && node.getTag() === tag) {
                return node;
            }
        }
        return null;
    },

    /**
     * Returns all children.
     * @deprecated since v3.0, please use getChildren instead.
     * @returns {Array}
     */
    getNodes: function () {
        return this._nodes;
    },

    /**
     * Removes a node from ccui.Widget
     * @deprecated since v3.0, please use removeChild instead.
     * @param {cc.Node} node
     * @param {Boolean} cleanup
     */
    removeNode: function (node, cleanup) {
        cc.Node.prototype.removeChild.call(this, node, cleanup);
        cc.arrayRemoveObject(this._nodes, node);
    },

    /**
     * Removes node by tag
     * @deprecated since v3.0, please use removeChildByTag instead.
     * @param {Number} tag
     * @param {Boolean} [cleanup]
     */
    removeNodeByTag: function (tag, cleanup) {
        var node = this.getChildByTag(tag);
        if (!node)
            cc.log("cocos2d: removeNodeByTag(tag = %d): child not found!", tag);
        else
            this.removeChild(node, cleanup);
    },

    /**
     * Removes all node
     * @deprecated since v3.0, please use removeAllChildren instead.
     */
    removeAllNodes: function () {
        for (var i = 0; i < this._nodes.length; i++) {
            var node = this._nodes[i];
            cc.Node.prototype.removeChild.call(this, node);
        }
        this._nodes.length = 0;
    },

    _findLayout: function(){
        cc.renderer.childrenOrderDirty = true;
        var layout = this._parent;
        while(layout){
            if(layout._doLayout){
                layout._doLayoutDirty = true;
                break;
            }else
                layout = layout._parent;
        }
    },

    /**
     * @since v3.2
     * @returns {boolean} true represent the widget use Unify Size, false represent the widget couldn't use Unify Size
     */
    isUnifySizeEnabled: function(){
        return this._unifySize;
    },

    /**
     * @since v3.2
     * @param {Boolean} enable enable Unify Size of a widget
     */
    setUnifySizeEnabled: function(enable){
        this._unifySize = enable;
    },

    //v3.3
    _ccEventCallback: null,
    /**
     * Set a event handler to the widget in order to use cocostudio editor and framework
     * @since v3.3
     * @param {function} callback
     */
    addCCSEventListener: function(callback){
        this._ccEventCallback = callback;
    },

    //override the scale functions.
    setScaleX: function(scaleX){
        if (this._flippedX)
            scaleX = scaleX * -1;
        cc.Node.prototype.setScaleX.call(this, scaleX);
    },
    setScaleY: function(scaleY){
        if (this._flippedY)
            scaleY = scaleY * -1;
        cc.Node.prototype.setScaleY.call(this, scaleY);
    },
    setScale: function(scaleX, scaleY){
        if(scaleY === undefined)
            scaleY = scaleX;
        this.setScaleX(scaleX);
        this.setScaleY(scaleY);
    },

    getScaleX: function(){
        var originalScale = cc.Node.prototype.getScaleX.call(this);
        if (this._flippedX)
            originalScale = originalScale * -1.0;
        return originalScale;
    },
    getScaleY: function(){
        var originalScale = cc.Node.prototype.getScaleY.call(this);
        if (this._flippedY)
            originalScale = originalScale * -1.0;
        return originalScale;
    },
    getScale: function(){
        if(this.getScaleX() === this.getScaleY())
            cc.log("Widget#scale. ScaleX != ScaleY. Don't know which one to return");
        return this.getScaleX();
    },

    /**
     * Sets callback name to widget.
     * @since v3.3
     * @param {String} callbackName
     */
    setCallbackName: function(callbackName){
        this._callbackName = callbackName;
    },

    /**
     * Gets callback name of widget
     * @since v3.3
     * @returns {String|Null}
     */
    getCallbackName: function(){
        return this._callbackName;
    },

    /**
     * Sets callback type to widget
     * @since v3.3
     * @param {String} callbackType
     */
    setCallbackType: function(callbackType){
        this._callbackType = callbackType;
    },

    /**
     * Gets callback type of widget
     * @since v3.3
     * @returns {String|null}
     */
    getCallbackType: function(){
        return this._callbackType;
    },

    /**
     * Whether enable layout component of a widget
     * @since v3.3
     * @param {Boolean} enable enable layout Component of a widget
     */
    setLayoutComponentEnabled: function(enable){
        this._usingLayoutComponent = enable;
    },

    /**
     * Returns whether enable layout component of a widget
     * @return {Boolean} true represent the widget use Layout Component, false represent the widget couldn't use Layout Component.
     */
    isLayoutComponentEnabled: function(){
        return this._usingLayoutComponent;
    },


    _createRenderCmd: function(){
        if(cc._renderType === cc._RENDER_TYPE_WEBGL)
            return new ccui.Widget.WebGLRenderCmd(this);
        else
            return new ccui.Widget.CanvasRenderCmd(this);
    }
});

var _p = ccui.Widget.prototype;

// Extended properties
/** @expose */
_p.xPercent;
cc.defineGetterSetter(_p, "xPercent", _p._getXPercent, _p._setXPercent);
/** @expose */
_p.yPercent;
cc.defineGetterSetter(_p, "yPercent", _p._getYPercent, _p._setYPercent);
/** @expose */
_p.widthPercent;
cc.defineGetterSetter(_p, "widthPercent", _p._getWidthPercent, _p._setWidthPercent);
/** @expose */
_p.heightPercent;
cc.defineGetterSetter(_p, "heightPercent", _p._getHeightPercent, _p._setHeightPercent);
/** @expose */
_p.widgetParent;
cc.defineGetterSetter(_p, "widgetParent", _p.getWidgetParent);
/** @expose */
_p.enabled;
cc.defineGetterSetter(_p, "enabled", _p.isEnabled, _p.setEnabled);
/** @expose */
_p.focused;
cc.defineGetterSetter(_p, "focused", _p.isFocused, _p.setFocused);
/** @expose */
_p.sizeType;
cc.defineGetterSetter(_p, "sizeType", _p.getSizeType, _p.setSizeType);
/** @expose */
_p.widgetType;
cc.defineGetterSetter(_p, "widgetType", _p.getWidgetType);
/** @expose */
_p.touchEnabled;
cc.defineGetterSetter(_p, "touchEnabled", _p.isTouchEnabled, _p.setTouchEnabled);
/** @expose */
_p.updateEnabled;
cc.defineGetterSetter(_p, "updateEnabled", _p.isUpdateEnabled, _p.setUpdateEnabled);
/** @expose */
_p.bright;
cc.defineGetterSetter(_p, "bright", _p.isBright, _p.setBright);
/** @expose */
_p.name;
cc.defineGetterSetter(_p, "name", _p.getName, _p.setName);
/** @expose */
_p.actionTag;
cc.defineGetterSetter(_p, "actionTag", _p.getActionTag, _p.setActionTag);
/** @expose */
_p.opacity;
cc.defineGetterSetter(_p, "opacity", _p.getOpacity, _p.setOpacity);

_p = null;

/**
 * allocates and initializes a UIWidget.
 * @deprecated
 * @return {ccui.Widget}
 */
ccui.Widget.create = function () {
    return new ccui.Widget();
};

ccui.Widget._focusedWidget = null;                        //both layout & widget will be stored in this variable
ccui.Widget._focusNavigationController = null;

/**
 * call this method with parameter true to enable the Android Dpad focus navigation feature
 * @note it doesn't implemented on Web
 * @param {Boolean} enable set true to enable dpad focus navigation, otherwise disable dpad focus navigation
 */
ccui.Widget.enableDpadNavigation = function(enable){
    if (enable){
        if (null == ccui.Widget._focusNavigationController) {
            ccui.Widget._focusNavigationController = new ccui._FocusNavigationController();
            if (ccui.Widget._focusedWidget) {
                ccui.Widget._focusNavigationController._setFirstFocsuedWidget(ccui.Widget._focusedWidget);
            }
        }
        ccui.Widget._focusNavigationController.enableFocusNavigation(true);
    } else {
        if(ccui.Widget._focusNavigationController){
            ccui.Widget._focusNavigationController.enableFocusNavigation(false);
            ccui.Widget._focusNavigationController = null;
        }
    }
};

/**
 * Gets the focused widget of current stage.
 * @function
 * @returns {null|ccui.Widget}
 */
ccui.Widget.getCurrentFocusedWidget = function(){
    return ccui.Widget._focusedWidget;
};

// Constants
//bright style
/**
 * None bright style of ccui.Widget.
 * @constant
 * @type {number}
 */
ccui.Widget.BRIGHT_STYLE_NONE = -1;
/**
 * Normal bright style of ccui.Widget.
 * @constant
 * @type {number}
 */
ccui.Widget.BRIGHT_STYLE_NORMAL = 0;
/**
 * Light bright style of ccui.Widget.
 * @constant
 * @type {number}
 */
ccui.Widget.BRIGHT_STYLE_HIGH_LIGHT = 1;

//widget type
/**
 * The type code of Widget for ccui controls.
 * @constant
 * @type {number}
 */
ccui.Widget.TYPE_WIDGET = 0;
/**
 * The type code of Container for ccui controls.
 * @constant
 * @type {number}
 */
ccui.Widget.TYPE_CONTAINER = 1;

//Focus Direction
/**
 * The left of Focus direction for ccui.Widget
 * @constant
 * @type {number}
 */
ccui.Widget.LEFT = 0;
/**
 * The right of Focus direction for ccui.Widget
 * @constant
 * @type {number}
 */
ccui.Widget.RIGHT = 1;
/**
 * The up of Focus direction for ccui.Widget
 * @constant
 * @type {number}
 */
ccui.Widget.UP = 2;
/**
 * The down of Focus direction for ccui.Widget
 * @constant
 * @type {number}
 */
ccui.Widget.DOWN = 3;

//texture resource type
/**
 * The image file texture type of ccui.Widget loads.
 * @constant
 * @type {number}
 */
ccui.Widget.LOCAL_TEXTURE = 0;
/**
 * The sprite frame texture type of ccui.Widget loads.
 * @constant
 * @type {number}
 */
ccui.Widget.PLIST_TEXTURE = 1;

//touch event type
/**
 * The touch began type of ccui.Widget's touch event
 * @constant
 * @type {number}
 */
ccui.Widget.TOUCH_BEGAN = 0;
/**
 * The touch moved type of ccui.Widget's touch event
 * @constant
 * @type {number}
 */
ccui.Widget.TOUCH_MOVED = 1;
/**
 * The touch end type of ccui.Widget's touch event
 * @constant
 * @type {number}
 */
ccui.Widget.TOUCH_ENDED = 2;
/**
 * The touch canceled type of ccui.Widget's touch event
 * @constant
 * @type {number}
 */
ccui.Widget.TOUCH_CANCELED = 3;

//size type
/**
 * The absolute of ccui.Widget's size type.
 * @constant
 * @type {number}
 */
ccui.Widget.SIZE_ABSOLUTE = 0;
/**
 * The percent of ccui.Widget's size type.
 * @constant
 * @type {number}
 */
ccui.Widget.SIZE_PERCENT = 1;

//position type
/**
 * The absolute of ccui.Widget's position type.
 * @constant
 * @type {number}
 */
ccui.Widget.POSITION_ABSOLUTE = 0;
/**
 * The percent of ccui.Widget's position type.
 * @constant
 * @type {number}
 */
ccui.Widget.POSITION_PERCENT = 1;
