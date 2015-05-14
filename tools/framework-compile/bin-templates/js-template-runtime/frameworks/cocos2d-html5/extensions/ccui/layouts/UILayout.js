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
 * ccui.Layout is the base class of  ccui.PageView and ccui.ScrollView, it does layout by layout manager
 *  and clips area by its _clippingStencil when clippingEnabled is true.
 * @class
 * @extends ccui.Widget
 *
 * @property {Boolean}                  clippingEnabled - Indicate whether clipping is enabled
 * @property {ccui.Layout.CLIPPING_STENCIL|ccui.Layout.CLIPPING_SCISSOR}   clippingType
 * @property {ccui.Layout.ABSOLUTE|ccui.Layout.LINEAR_VERTICAL|ccui.Layout.LINEAR_HORIZONTAL|ccui.Layout.RELATIVE}  layoutType
 *
 */
ccui.Layout = ccui.Widget.extend(/** @lends ccui.Layout# */{
    _clippingEnabled: false,
    _backGroundScale9Enabled: null,
    _backGroundImage: null,
    _backGroundImageFileName: null,
    _backGroundImageCapInsets: null,
    _colorType: null,
    _bgImageTexType: ccui.Widget.LOCAL_TEXTURE,
    _colorRender: null,
    _gradientRender: null,
    _color: null,
    _startColor: null,
    _endColor: null,
    _alongVector: null,
    _opacity: 255,
    _backGroundImageTextureSize: null,
    _layoutType: null,
    _doLayoutDirty: true,
    _clippingRectDirty: true,
    _clippingType: null,
    _clippingStencil: null,
    _scissorRectDirty: false,
    _clippingRect: null,
    _clippingParent: null,
    _className: "Layout",
    _backGroundImageColor: null,
    _finalPositionX: 0,
    _finalPositionY: 0,

    _backGroundImageOpacity:0,

    _loopFocus: false,                                                          //whether enable loop focus or not
    __passFocusToChild: true,                                                  //on default, it will pass the focus to the next nearest widget
    _isFocusPassing:false,                                                      //when finding the next focused widget, use this variable to pass focus between layout & widget
    _isInterceptTouch: false,

    /**
     * Allocates and initializes an UILayout.
     * Constructor of ccui.Layout
     * @function
     * @example
     * // example
     * var uiLayout = new ccui.Layout();
     */
    ctor: function () {
        this._layoutType = ccui.Layout.ABSOLUTE;
        this._widgetType = ccui.Widget.TYPE_CONTAINER;
        this._clippingType = ccui.Layout.CLIPPING_STENCIL;
        this._colorType = ccui.Layout.BG_COLOR_NONE;

        ccui.Widget.prototype.ctor.call(this);
        this._backGroundImageCapInsets = cc.rect(0, 0, 0, 0);

        this._color = cc.color(255, 255, 255, 255);
        this._startColor = cc.color(255, 255, 255, 255);
        this._endColor = cc.color(255, 255, 255, 255);
        this._alongVector = cc.p(0, -1);
        this._backGroundImageTextureSize = cc.size(0, 0);

        this._clippingRect = cc.rect(0, 0, 0, 0);
        this._backGroundImageColor = cc.color(255, 255, 255, 255);
    },

    /**
     * Calls its parent's onEnter, and calls its clippingStencil's onEnter if clippingStencil isn't null.
     * @override
     */
    onEnter: function(){
        ccui.Widget.prototype.onEnter.call(this);
        if (this._clippingStencil)
            this._clippingStencil.onEnter();
        this._doLayoutDirty = true;
        this._clippingRectDirty = true;
    },

    /**
     *  Calls its parent's onExit, and calls its clippingStencil's onExit if clippingStencil isn't null.
     *  @override
     */
    onExit: function(){
        ccui.Widget.prototype.onExit.call(this);
        if (this._clippingStencil)
            this._clippingStencil.onExit();
    },

    /**
     * If a layout is loop focused which means that the focus movement will be inside the layout
     * @param {Boolean} loop pass true to let the focus movement loop inside the layout
     */
    setLoopFocus: function(loop){
        this._loopFocus = loop;
    },

    /**
     * Gets whether enable focus loop
     * @returns {boolean}  If focus loop is enabled, then it will return true, otherwise it returns false. The default value is false.
     */
    isLoopFocus: function(){
        return this._loopFocus;
    },

    /**
     * Specifies whether the layout pass its focus to its child
     * @param pass To specify whether the layout pass its focus to its child
     */
    setPassFocusToChild: function(pass){
        this.__passFocusToChild = pass;
    },

    /**
     * Returns whether the layout will pass the focus to its children or not. The default value is true
     * @returns {boolean} To query whether the layout will pass the focus to its children or not. The default value is true
     */
    isPassFocusToChild: function(){
        return this.__passFocusToChild;
    },

    /**
     * When a widget is in a layout, you could call this method to get the next focused widget within a specified direction.
     * If the widget is not in a layout, it will return itself
     * @param {Number} direction the direction to look for the next focused widget in a layout
     * @param {ccui.Widget} current the current focused widget
     * @returns {ccui.Widget} return the index of widget in the layout
     */
    findNextFocusedWidget: function(direction, current){
        if (this._isFocusPassing || this.isFocused()) {
            var parent = this.getParent();
            this._isFocusPassing = false;
            if (this.__passFocusToChild) {
                var w = this._passFocusToChild(direction, current);
                if (w instanceof ccui.Layout && parent) {
                    parent._isFocusPassing = true;
                    return parent.findNextFocusedWidget(direction, this);
                }
                return w;
            }

            if (null == parent || !(parent instanceof ccui.Layout))
                return this;
            parent._isFocusPassing = true;
            return parent.findNextFocusedWidget(direction, this);
        } else if(current.isFocused() || current instanceof ccui.Layout) {
            if (this._layoutType === ccui.Layout.LINEAR_HORIZONTAL) {
                switch (direction){
                    case ccui.Widget.LEFT:
                        return this._getPreviousFocusedWidget(direction, current);
                    break;
                    case ccui.Widget.RIGHT:
                        return this._getNextFocusedWidget(direction, current);
                    break;
                    case ccui.Widget.DOWN:
                    case ccui.Widget.UP:
                        if (this._isLastWidgetInContainer(this, direction)){
                            if (this._isWidgetAncestorSupportLoopFocus(current, direction))
                                return ccui.Widget.prototype.findNextFocusedWidget.call(this, direction, this);
                            return current;
                        } else {
                            return ccui.Widget.prototype.findNextFocusedWidget.call(this, direction, this);
                        }
                    break;
                    default:
                        cc.assert(0, "Invalid Focus Direction");
                        return current;
                }
            } else if (this._layoutType === ccui.Layout.LINEAR_VERTICAL) {
                switch (direction){
                    case ccui.Widget.LEFT:
                    case ccui.Widget.RIGHT:
                        if (this._isLastWidgetInContainer(this, direction)) {
                            if (this._isWidgetAncestorSupportLoopFocus(current, direction))
                                return ccui.Widget.prototype.findNextFocusedWidget.call(this, direction, this);
                            return current;
                        }
                        else
                            return ccui.Widget.prototype.findNextFocusedWidget.call(this, direction, this);
                     break;
                    case ccui.Widget.DOWN:
                        return this._getNextFocusedWidget(direction, current);
                        break;
                    case ccui.Widget.UP:
                        return this._getPreviousFocusedWidget(direction, current);
                        break;
                    default:
                        cc.assert(0, "Invalid Focus Direction");
                        return current;
                }
            } else {
                cc.assert(0, "Un Supported Layout type, please use VBox and HBox instead!!!");
                return current;
            }
        } else
            return current;
    },

    /**
     * To specify a user-defined functor to decide which child widget of the layout should get focused
     * @function
     * @param {Number} direction
     * @param {ccui.Widget} current
     */
    onPassFocusToChild: null,

    /**
     * override "init" method of widget. please do not call this function by yourself, you should pass the parameters to constructor to initialize it.
     * @returns {boolean}
     * @override
     */
    init: function () {
        if (ccui.Widget.prototype.init.call(this)) {
            this.ignoreContentAdaptWithSize(false);
            this.setContentSize(cc.size(0, 0));
            this.setAnchorPoint(0, 0);
            this.onPassFocusToChild  = this._findNearestChildWidgetIndex.bind(this);
            return true;
        }
        return false;
    },

    /**
     * Adds a widget to the container.
     * @param {ccui.Widget} widget
     * @param {Number} [zOrder]
     * @param {Number|string} [tag] tag or name
     * @override
     */
    addChild: function (widget, zOrder, tag) {
        if ((widget instanceof ccui.Widget)) {
            this._supplyTheLayoutParameterLackToChild(widget);
        }
        ccui.Widget.prototype.addChild.call(this, widget, zOrder, tag);
        this._doLayoutDirty = true;
    },

    /**
     * Removes child widget from ccui.Layout, and sets the layout dirty flag to true.
     * @param {ccui.Widget} widget
     * @param {Boolean} [cleanup=true]
     * @override
     */
    removeChild: function (widget, cleanup) {
        ccui.Widget.prototype.removeChild.call(this, widget, cleanup);
        this._doLayoutDirty = true;
    },

    /**
     * Removes all children from the container with a cleanup, and sets the layout dirty flag to true.
     * @param {Boolean} cleanup
     */
    removeAllChildren: function (cleanup) {
        ccui.Widget.prototype.removeAllChildren.call(this, cleanup);
        this._doLayoutDirty = true;
    },

    /**
     * Removes all children from the container, do a cleanup to all running actions depending on the cleanup parameter,
     * and sets the layout dirty flag to true.
     * @param {Boolean} cleanup true if all running actions on all children nodes should be cleanup, false otherwise.
     */
    removeAllChildrenWithCleanup: function(cleanup){
        ccui.Widget.prototype.removeAllChildrenWithCleanup.call(this, cleanup);
        this._doLayoutDirty = true;
    },

    /**
     * Gets if layout is clipping enabled.
     * @returns {Boolean} if layout is clipping enabled.
     */
    isClippingEnabled: function () {
        return this._clippingEnabled;
    },

    /**
     * <p>
     *     Calls adaptRenderers (its subclass will override it.) and do layout.
     *     If clippingEnabled is true, it will clip/scissor area.
     * </p>
     * @override
     * @param {cc.Node.RenderCmd} [parentCmd]
     */
    visit: function (parentCmd) {
        if (!this._visible)
            return;
        this._adaptRenderers();
        this._doLayout();

        if (this._clippingEnabled) {
            switch (this._clippingType) {
                case ccui.Layout.CLIPPING_STENCIL:
                    this._renderCmd.stencilClippingVisit(parentCmd);
                    break;
                case ccui.Layout.CLIPPING_SCISSOR:
                    this._renderCmd.scissorClippingVisit(parentCmd);
                    break;
                default:
                    break;
            }
        } else
            ccui.Widget.prototype.visit.call(this, parentCmd);
    },

    /**
     * Changes if layout can clip it's content and locChild.
     * If you really need this, please enable it. But it would reduce the rendering efficiency.
     * @param {Boolean} able clipping enabled.
     */
    setClippingEnabled: function (able) {
        if (able === this._clippingEnabled)
            return;
        this._clippingEnabled = able;
        switch (this._clippingType) {
            case ccui.Layout.CLIPPING_STENCIL:
                if (able){
                    this._clippingStencil = new cc.DrawNode();
                    this._renderCmd.rebindStencilRendering(this._clippingStencil);
                    if (this._running)
                        this._clippingStencil.onEnter();
                    this._setStencilClippingSize(this._contentSize);
                } else {
                    if (this._running && this._clippingStencil)
                        this._clippingStencil.onExit();
                    this._clippingStencil = null;
                }
                break;
            default:
                break;
        }
    },

    /**
     * Sets clipping type to ccui.Layout
     * @param {ccui.Layout.CLIPPING_STENCIL|ccui.Layout.CLIPPING_SCISSOR} type
     */
    setClippingType: function (type) {
        if (type === this._clippingType)
            return;
        if(cc._renderType === cc._RENDER_TYPE_CANVAS && type === ccui.Layout.CLIPPING_SCISSOR){
            cc.log("Only supports STENCIL on canvas mode.");
            return;
        }
        var clippingEnabled = this.isClippingEnabled();
        this.setClippingEnabled(false);
        this._clippingType = type;
        this.setClippingEnabled(clippingEnabled);
    },

    /**
     * Gets clipping type of ccui.Layout
     * @returns {ccui.Layout.CLIPPING_STENCIL|ccui.Layout.CLIPPING_SCISSOR}
     */
    getClippingType: function () {
        return this._clippingType;
    },

    _setStencilClippingSize: function (size) {
        if (this._clippingEnabled && this._clippingType === ccui.Layout.CLIPPING_STENCIL) {
            var rect = [];
            rect[0] = cc.p(0, 0);
            rect[1] = cc.p(size.width, 0);
            rect[2] = cc.p(size.width, size.height);
            rect[3] = cc.p(0, size.height);
            var green = cc.color.GREEN;
            this._clippingStencil.clear();
            this._clippingStencil.drawPoly(rect, 4, green, 0, green);
        }
    },

    _getClippingRect: function () {
        if (this._clippingRectDirty) {
            var worldPos = this.convertToWorldSpace(cc.p(0, 0));
            var t = this.getNodeToWorldTransform();
            var scissorWidth = this._contentSize.width * t.a;
            var scissorHeight = this._contentSize.height * t.d;
            var parentClippingRect;
            var parent = this;

            while (parent) {
                parent = parent.getParent();
                if (parent && parent instanceof ccui.Layout && parent.isClippingEnabled()) {
                    this._clippingParent = parent;
                    break;
                }
            }

            if (this._clippingParent) {
                parentClippingRect = this._clippingParent._getClippingRect();
                var finalX = worldPos.x - (scissorWidth * this._anchorPoint.x);
                var finalY = worldPos.y - (scissorHeight * this._anchorPoint.y);
                var finalWidth = scissorWidth;
                var finalHeight = scissorHeight;

                var leftOffset = worldPos.x - parentClippingRect.x;
                if (leftOffset < 0) {
                    finalX = parentClippingRect.x;
                    finalWidth += leftOffset;
                }
                var rightOffset = (worldPos.x + scissorWidth) - (parentClippingRect.x + parentClippingRect.width);
                if (rightOffset > 0)
                    finalWidth -= rightOffset;
                var topOffset = (worldPos.y + scissorHeight) - (parentClippingRect.y + parentClippingRect.height);
                if (topOffset > 0)
                    finalHeight -= topOffset;
                var bottomOffset = worldPos.y - parentClippingRect.y;
                if (bottomOffset < 0) {
                    finalY = parentClippingRect.x;
                    finalHeight += bottomOffset;
                }
                if (finalWidth < 0)
                    finalWidth = 0;
                if (finalHeight < 0)
                    finalHeight = 0;
                this._clippingRect.x = finalX;
                this._clippingRect.y = finalY;
                this._clippingRect.width = finalWidth;
                this._clippingRect.height = finalHeight;
            } else {
                this._clippingRect.x = worldPos.x - (scissorWidth * this._anchorPoint.x);
                this._clippingRect.y = worldPos.y - (scissorHeight * this._anchorPoint.y);
                this._clippingRect.width = scissorWidth;
                this._clippingRect.height = scissorHeight;
            }
            this._clippingRectDirty = false;
        }
        return this._clippingRect;
    },

    _onSizeChanged: function () {
        ccui.Widget.prototype._onSizeChanged.call(this);
        var locContentSize = this._contentSize;
        this._setStencilClippingSize(locContentSize);
        this._doLayoutDirty = true;
        this._clippingRectDirty = true;
        if (this._backGroundImage) {
            this._backGroundImage.setPosition(locContentSize.width * 0.5, locContentSize.height * 0.5);
            if (this._backGroundScale9Enabled && this._backGroundImage instanceof ccui.Scale9Sprite)
                this._backGroundImage.setPreferredSize(locContentSize);
        }
        if (this._colorRender)
            this._colorRender.setContentSize(locContentSize);
        if (this._gradientRender)
            this._gradientRender.setContentSize(locContentSize);
    },

    /**
     * Sets background image use scale9 renderer.
     * @param {Boolean} able  true that use scale9 renderer, false otherwise.
     */
    setBackGroundImageScale9Enabled: function (able) {
        if (this._backGroundScale9Enabled === able)
            return;
        this.removeProtectedChild(this._backGroundImage);
        this._backGroundImage = null;
        this._backGroundScale9Enabled = able;
        this._addBackGroundImage();
        this.setBackGroundImage(this._backGroundImageFileName, this._bgImageTexType);
        this.setBackGroundImageCapInsets(this._backGroundImageCapInsets);
    },

    /**
     * Get whether background image is use scale9 renderer.
     * @returns {Boolean}
     */
    isBackGroundImageScale9Enabled: function () {
        return this._backGroundScale9Enabled;
    },

    /**
     * Sets a background image for layout
     * @param {String} fileName
     * @param {ccui.Widget.LOCAL_TEXTURE|ccui.Widget.PLIST_TEXTURE} texType
     */
    setBackGroundImage: function (fileName, texType) {
        if (!fileName)
            return;
        texType = texType || ccui.Widget.LOCAL_TEXTURE;
        if (this._backGroundImage === null){
            this._addBackGroundImage();
            this.setBackGroundImageScale9Enabled(this._backGroundScale9Enabled);
        }
        this._backGroundImageFileName = fileName;
        this._bgImageTexType = texType;
        var locBackgroundImage = this._backGroundImage;
        switch (this._bgImageTexType) {
            case ccui.Widget.LOCAL_TEXTURE:
                locBackgroundImage.initWithFile(fileName);
                break;
            case ccui.Widget.PLIST_TEXTURE:
                locBackgroundImage.initWithSpriteFrameName(fileName);
                break;
            default:
                break;
        }
        if (this._backGroundScale9Enabled)
            locBackgroundImage.setPreferredSize(this._contentSize);

        this._backGroundImageTextureSize = locBackgroundImage.getContentSize();
        locBackgroundImage.setPosition(this._contentSize.width * 0.5, this._contentSize.height * 0.5);
        this._updateBackGroundImageColor();
    },

    /**
     * Sets a background image CapInsets for layout, if the background image is a scale9 render.
     * @param {cc.Rect} capInsets capinsets of background image.
     */
    setBackGroundImageCapInsets: function (capInsets) {
        if(!capInsets)
            return;
        var locInsets = this._backGroundImageCapInsets;
        locInsets.x = capInsets.x;
        locInsets.y = capInsets.y;
        locInsets.width = capInsets.width;
        locInsets.height = capInsets.height;
        if (this._backGroundScale9Enabled)
            this._backGroundImage.setCapInsets(capInsets);
    },

    /**
     * Gets background image capinsets of ccui.Layout.
     * @returns {cc.Rect}
     */
    getBackGroundImageCapInsets: function () {
        return cc.rect(this._backGroundImageCapInsets);
    },

    _supplyTheLayoutParameterLackToChild: function (locChild) {
        if (!locChild) {
            return;
        }
        switch (this._layoutType) {
            case ccui.Layout.ABSOLUTE:
                break;
            case ccui.Layout.LINEAR_HORIZONTAL:
            case ccui.Layout.LINEAR_VERTICAL:
                var layoutParameter = locChild.getLayoutParameter(ccui.LayoutParameter.LINEAR);
                if (!layoutParameter)
                    locChild.setLayoutParameter(new ccui.LinearLayoutParameter());
                break;
            case ccui.Layout.RELATIVE:
                var layoutParameter = locChild.getLayoutParameter(ccui.LayoutParameter.RELATIVE);
                if (!layoutParameter)
                    locChild.setLayoutParameter(new ccui.RelativeLayoutParameter());
                break;
            default:
                break;
        }
    },

    _addBackGroundImage: function () {
        var contentSize = this._contentSize;
        if (this._backGroundScale9Enabled) {
            this._backGroundImage = new ccui.Scale9Sprite();
            this._backGroundImage.setPreferredSize(contentSize);
        } else
            this._backGroundImage = new cc.Sprite();
        this.addProtectedChild(this._backGroundImage, ccui.Layout.BACKGROUND_IMAGE_ZORDER, -1);
        this._backGroundImage.setPosition(contentSize.width * 0.5, contentSize.height * 0.5);
    },

    /**
     * Remove the background image of ccui.Layout.
     */
    removeBackGroundImage: function () {
        if (!this._backGroundImage)
            return;
        this.removeProtectedChild(this._backGroundImage);
        this._backGroundImage = null;
        this._backGroundImageFileName = "";
        this._backGroundImageTextureSize.width = 0;
        this._backGroundImageTextureSize.height = 0;
    },

    /**
     * Sets Color Type for ccui.Layout.
     * @param {ccui.Layout.BG_COLOR_NONE|ccui.Layout.BG_COLOR_SOLID|ccui.Layout.BG_COLOR_GRADIENT} type
     */
    setBackGroundColorType: function (type) {
        if (this._colorType === type)
            return;
        switch (this._colorType) {
            case ccui.Layout.BG_COLOR_NONE:
                if (this._colorRender) {
                    this.removeProtectedChild(this._colorRender);
                    this._colorRender = null;
                }
                if (this._gradientRender) {
                    this.removeProtectedChild(this._gradientRender);
                    this._gradientRender = null;
                }
                break;
            case ccui.Layout.BG_COLOR_SOLID:
                if (this._colorRender) {
                    this.removeProtectedChild(this._colorRender);
                    this._colorRender = null;
                }
                break;
            case ccui.Layout.BG_COLOR_GRADIENT:
                if (this._gradientRender) {
                    this.removeProtectedChild(this._gradientRender);
                    this._gradientRender = null;
                }
                break;
            default:
                break;
        }
        this._colorType = type;
        switch (this._colorType) {
            case ccui.Layout.BG_COLOR_NONE:
                break;
            case ccui.Layout.BG_COLOR_SOLID:
                this._colorRender = new cc.LayerColor();
                this._colorRender.setContentSize(this._contentSize);
                this._colorRender.setOpacity(this._opacity);
                this._colorRender.setColor(this._color);
                this.addProtectedChild(this._colorRender, ccui.Layout.BACKGROUND_RENDERER_ZORDER, -1);
                break;
            case ccui.Layout.BG_COLOR_GRADIENT:
                this._gradientRender = new cc.LayerGradient(cc.color(255, 0, 0, 255), cc.color(0, 255, 0, 255));
                this._gradientRender.setContentSize(this._contentSize);
                this._gradientRender.setOpacity(this._opacity);
                this._gradientRender.setStartColor(this._startColor);
                this._gradientRender.setEndColor(this._endColor);
                this._gradientRender.setVector(this._alongVector);
                this.addProtectedChild(this._gradientRender, ccui.Layout.BACKGROUND_RENDERER_ZORDER, -1);
                break;
            default:
                break;
        }
    },

    /**
     * Get background color type of ccui.Layout.
     * @returns {ccui.Layout.BG_COLOR_NONE|ccui.Layout.BG_COLOR_SOLID|ccui.Layout.BG_COLOR_GRADIENT}
     */
    getBackGroundColorType: function () {
        return this._colorType;
    },

    /**
     * Sets background color for layout, if color type is Layout.COLOR_SOLID
     * @param {cc.Color} color
     * @param {cc.Color} [endColor]
     */
    setBackGroundColor: function (color, endColor) {
        if (!endColor) {
            this._color.r = color.r;
            this._color.g = color.g;
            this._color.b = color.b;
            if (this._colorRender)
                this._colorRender.setColor(color);
        } else {
            this._startColor.r = color.r;
            this._startColor.g = color.g;
            this._startColor.b = color.b;
            if (this._gradientRender)
                this._gradientRender.setStartColor(color);

            this._endColor.r = endColor.r;
            this._endColor.g = endColor.g;
            this._endColor.b = endColor.b;
            if (this._gradientRender)
                this._gradientRender.setEndColor(endColor);
        }
    },

    /**
     * Gets background color of ccui.Layout, if color type is Layout.COLOR_SOLID.
     * @returns {cc.Color}
     */
    getBackGroundColor: function () {
        var tmpColor = this._color;
        return cc.color(tmpColor.r, tmpColor.g, tmpColor.b, tmpColor.a);
    },

    /**
     * Gets background start color of ccui.Layout
     * @returns {cc.Color}
     */
    getBackGroundStartColor: function () {
        var tmpColor = this._startColor;
        return cc.color(tmpColor.r, tmpColor.g, tmpColor.b, tmpColor.a);
    },

    /**
     * Gets background end color of ccui.Layout
     * @returns {cc.Color}
     */
    getBackGroundEndColor: function () {
        var tmpColor = this._endColor;
        return cc.color(tmpColor.r, tmpColor.g, tmpColor.b, tmpColor.a);
    },

    /**
     * Sets background opacity to ccui.Layout.
     * @param {number} opacity
     */
    setBackGroundColorOpacity: function (opacity) {
        this._opacity = opacity;
        switch (this._colorType) {
            case ccui.Layout.BG_COLOR_NONE:
                break;
            case ccui.Layout.BG_COLOR_SOLID:
                this._colorRender.setOpacity(opacity);
                break;
            case ccui.Layout.BG_COLOR_GRADIENT:
                this._gradientRender.setOpacity(opacity);
                break;
            default:
                break;
        }
    },

    /**
     * Get background opacity value of ccui.Layout.
     * @returns {Number}
     */
    getBackGroundColorOpacity: function () {
        return this._opacity;
    },

    /**
     * Sets background color vector for layout, if color type is Layout.COLOR_GRADIENT
     * @param {cc.Point} vector
     */
    setBackGroundColorVector: function (vector) {
        this._alongVector.x = vector.x;
        this._alongVector.y = vector.y;
        if (this._gradientRender) {
            this._gradientRender.setVector(vector);
        }
    },

    /**
     *  Gets background color vector of ccui.Layout, if color type is Layout.COLOR_GRADIENT
     * @returns {cc.Point}
     */
    getBackGroundColorVector: function () {
        return this._alongVector;
    },

    /**
     * Sets backGround image color
     * @param {cc.Color} color
     */
    setBackGroundImageColor: function (color) {
        this._backGroundImageColor.r = color.r;
        this._backGroundImageColor.g = color.g;
        this._backGroundImageColor.b = color.b;

        this._updateBackGroundImageColor();
    },

    /**
     * Sets backGround image Opacity
     * @param {Number} opacity
     */
    setBackGroundImageOpacity: function (opacity) {
        this._backGroundImageColor.a = opacity;
        this.getBackGroundImageColor();
    },

    /**
     * Gets backGround image color
     * @returns {cc.Color}
     */
    getBackGroundImageColor: function () {
        var color = this._backGroundImageColor;
        return cc.color(color.r, color.g, color.b, color.a);
    },

    /**
     * Gets backGround image opacity
     * @returns {Number}
     */
    getBackGroundImageOpacity: function () {
        return this._backGroundImageColor.a;
    },

    _updateBackGroundImageColor: function () {
        if(this._backGroundImage)
            this._backGroundImage.setColor(this._backGroundImageColor);
    },

    /**
     * Gets background image texture size.
     * @returns {cc.Size}
     */
    getBackGroundImageTextureSize: function () {
        return this._backGroundImageTextureSize;
    },

    /**
     * Sets LayoutType to ccui.Layout, LayoutManager will do layout by layout type..
     * @param {ccui.Layout.ABSOLUTE|ccui.Layout.LINEAR_VERTICAL|ccui.Layout.LINEAR_HORIZONTAL|ccui.Layout.RELATIVE} type
     */
    setLayoutType: function (type) {
        this._layoutType = type;
        var layoutChildrenArray = this._children;
        var locChild = null;
        for (var i = 0; i < layoutChildrenArray.length; i++) {
            locChild = layoutChildrenArray[i];
            if(locChild instanceof ccui.Widget)
                this._supplyTheLayoutParameterLackToChild(locChild);
        }
        this._doLayoutDirty = true;
    },

    /**
     * Gets LayoutType of ccui.Layout.
     * @returns {null}
     */
    getLayoutType: function () {
        return this._layoutType;
    },

    /**
     * request to refresh widget layout, it will do layout at visit calls
     */
    requestDoLayout: function () {
        this._doLayoutDirty = true;
    },

    _doLayout: function () {
        if (!this._doLayoutDirty)
            return;

        this.sortAllChildren();

        var executant = ccui.getLayoutManager(this._layoutType);
        if (executant)
            executant._doLayout(this);
        this._doLayoutDirty = false;
    },

    _getLayoutContentSize: function(){
        return this.getContentSize();
    },

    _getLayoutElements: function(){
        return this.getChildren();
    },

    _updateBackGroundImageOpacity: function(){
        if (this._backGroundImage)
            this._backGroundImage.setOpacity(this._backGroundImageOpacity);
    },

    _updateBackGroundImageRGBA: function(){
        if (this._backGroundImage) {
            this._backGroundImage.setColor(this._backGroundImageColor);
            this._backGroundImage.setOpacity(this._backGroundImageOpacity);
        }
    },

    /**
     * Gets the content size of the layout, it will accumulate all its children's content size
     * @returns {cc.Size}
     * @private
     */
    _getLayoutAccumulatedSize: function(){
        var children = this.getChildren();
        var  layoutSize = cc.size(0, 0);
        var widgetCount = 0, locSize;
        for(var i = 0, len = children.length; i < len; i++) {
            var layout = children[i];
            if (null !== layout && layout instanceof ccui.Layout){
                locSize = layout._getLayoutAccumulatedSize();
                layoutSize.width += locSize.width;
                layoutSize.height += locSize.height;
            } else {
                if (layout instanceof ccui.Widget) {
                    widgetCount++;
                    var m = layout.getLayoutParameter().getMargin();
                    locSize = layout.getContentSize();
                    layoutSize.width += locSize.width +  (m.right + m.left) * 0.5;
                    layoutSize.height += locSize.height +  (m.top + m.bottom) * 0.5;
                }
            }
        }

        //substract extra size
        var type = this.getLayoutType();
        if (type === ccui.Layout.LINEAR_HORIZONTAL)
            layoutSize.height = layoutSize.height - layoutSize.height/widgetCount * (widgetCount-1);

        if (type === ccui.Layout.LINEAR_VERTICAL)
            layoutSize.width = layoutSize.width - layoutSize.width/widgetCount * (widgetCount-1);
        return layoutSize;
    },

    /**
     * When the layout get focused, it the layout pass the focus to its child, it will use this method to determine which child      <br/>
     * will get the focus.  The current algorithm to determine which child will get focus is nearest-distance-priority algorithm
     * @param {Number} direction next focused widget direction
     * @param {ccui.Widget} baseWidget
     * @returns {Number}
     * @private
     */
    _findNearestChildWidgetIndex: function(direction, baseWidget){
        if (baseWidget == null || baseWidget === this)
            return this._findFirstFocusEnabledWidgetIndex();

        var index = 0, locChildren = this.getChildren();
        var count = locChildren.length, widgetPosition;

        var distance = cc.FLT_MAX, found = 0;
        if (direction === ccui.Widget.LEFT || direction === ccui.Widget.RIGHT || direction === ccui.Widget.DOWN || direction === ccui.Widget.UP) {
            widgetPosition = this._getWorldCenterPoint(baseWidget);
            while (index < count) {
                var w = locChildren[index];
                if (w && w instanceof ccui.Widget && w.isFocusEnabled()) {
                    var length = (w instanceof ccui.Layout)? w._calculateNearestDistance(baseWidget)
                        : cc.pLength(cc.pSub(this._getWorldCenterPoint(w), widgetPosition));
                    if (length < distance){
                        found = index;
                        distance = length;
                    }
                }
                index++;
            }
            return found;
        }
        cc.log("invalid focus direction!");
        return 0;
    },

    /**
     * When the layout get focused, it the layout pass the focus to its child, it will use this method to determine which child
     * will get the focus.  The current algorithm to determine which child will get focus is farthest-distance-priority algorithm
     * @param {Number} direction next focused widget direction
     * @param {ccui.Widget} baseWidget
     * @returns {Number} The index of child widget in the container
     * @private
     */
    _findFarthestChildWidgetIndex: function(direction, baseWidget){
        if (baseWidget == null || baseWidget === this)
            return this._findFirstFocusEnabledWidgetIndex();

        var index = 0, locChildren = this.getChildren();
        var count = locChildren.length;

        var distance = -cc.FLT_MAX, found = 0;
        if (direction === ccui.Widget.LEFT || direction === ccui.Widget.RIGHT || direction === ccui.Widget.DOWN || direction === ccui.Widget.UP) {
            var widgetPosition =  this._getWorldCenterPoint(baseWidget);
            while (index <  count) {
                var w = locChildren[index];
                if (w && w instanceof ccui.Widget && w.isFocusEnabled()) {
                    var length = (w instanceof ccui.Layout)?w._calculateFarthestDistance(baseWidget)
                        : cc.pLength(cc.pSub(this._getWorldCenterPoint(w), widgetPosition));
                    if (length > distance){
                        found = index;
                        distance = length;
                    }
                }
                index++;
            }
            return  found;
        }
        cc.log("invalid focus direction!!!");
        return 0;
    },

    /**
     * calculate the nearest distance between the baseWidget and the children of the layout
     * @param {ccui.Widget} baseWidget the base widget which will be used to calculate the distance between the layout's children and itself
     * @returns {Number} return the nearest distance between the baseWidget and the layout's children
     * @private
     */
    _calculateNearestDistance: function(baseWidget){
        var distance = cc.FLT_MAX;
        var widgetPosition =  this._getWorldCenterPoint(baseWidget);
        var locChildren = this._children;

        for (var i = 0, len = locChildren.length; i < len; i++) {
            var widget = locChildren[i], length;
            if (widget instanceof ccui.Layout)
                length = widget._calculateNearestDistance(baseWidget);
            else {
                if (widget instanceof ccui.Widget && widget.isFocusEnabled())
                    length = cc.pLength(cc.pSub(this._getWorldCenterPoint(widget), widgetPosition));
                else
                    continue;
            }
            if (length < distance)
                distance = length;
        }
        return distance;
    },

    /**
     * calculate the farthest distance between the baseWidget and the children of the layout
     * @param baseWidget
     * @returns {number}
     * @private
     */
    _calculateFarthestDistance:function(baseWidget){
        var distance = -cc.FLT_MAX;
        var widgetPosition =  this._getWorldCenterPoint(baseWidget);
        var locChildren = this._children;

        for (var i = 0, len = locChildren.length; i < len; i++) {
            var layout = locChildren[i];
            var length;
            if (layout instanceof ccui.Layout)
                length = layout._calculateFarthestDistance(baseWidget);
            else {
                if (layout instanceof ccui.Widget && layout.isFocusEnabled()) {
                    var wPosition = this._getWorldCenterPoint(layout);
                    length = cc.pLength(cc.pSub(wPosition, widgetPosition));
                } else
                    continue;
            }

            if (length > distance)
                distance = length;
        }
        return distance;
    },

    /**
     * when a layout pass the focus to it's child, use this method to determine which algorithm to use, nearest or farthest distance algorithm or not
     * @param direction
     * @param baseWidget
     * @private
     */
    _findProperSearchingFunctor: function(direction, baseWidget){
        if (baseWidget == null)
            return;

        var previousWidgetPosition = this._getWorldCenterPoint(baseWidget);
        var widgetPosition = this._getWorldCenterPoint(this._findFirstNonLayoutWidget());
        if (direction === ccui.Widget.LEFT) {
            this.onPassFocusToChild = (previousWidgetPosition.x > widgetPosition.x) ? this._findNearestChildWidgetIndex.bind(this)
                : this._findFarthestChildWidgetIndex.bind(this);
        } else if (direction === ccui.Widget.RIGHT) {
            this.onPassFocusToChild = (previousWidgetPosition.x > widgetPosition.x) ? this._findFarthestChildWidgetIndex.bind(this)
                : this._findNearestChildWidgetIndex.bind(this);
        }else if(direction === ccui.Widget.DOWN) {
            this.onPassFocusToChild = (previousWidgetPosition.y > widgetPosition.y) ? this._findNearestChildWidgetIndex.bind(this)
                : this._findFarthestChildWidgetIndex.bind(this);
        }else if(direction === ccui.Widget.UP) {
            this.onPassFocusToChild = (previousWidgetPosition.y < widgetPosition.y) ? this._findNearestChildWidgetIndex.bind(this)
                : this._findFarthestChildWidgetIndex.bind(this);
        }else
            cc.log("invalid direction!");
    },

    /**
     * find the first non-layout widget in this layout
     * @returns {ccui.Widget}
     * @private
     */
    _findFirstNonLayoutWidget:function(){
        var locChildren = this._children;
        for(var i = 0, len = locChildren.length; i < len; i++) {
            var child = locChildren[i];
            if (child instanceof ccui.Layout){
                var widget = child._findFirstNonLayoutWidget();
                if(widget)
                    return widget;
            } else{
                if (child instanceof ccui.Widget)
                    return child;
            }
        }
        return null;
    },

    /**
     * find the first focus enabled widget index in the layout, it will recursive searching the child widget
     * @returns {number}
     * @private
     */
    _findFirstFocusEnabledWidgetIndex: function(){
        var index = 0, locChildren = this.getChildren();
        var count = locChildren.length;
        while (index < count) {
            var w = locChildren[index];
            if (w && w instanceof ccui.Widget && w.isFocusEnabled())
                return index;
            index++;
        }
        return 0;
    },

    /**
     * find a focus enabled child Widget in the layout by index
     * @param index
     * @returns {*}
     * @private
     */
    _findFocusEnabledChildWidgetByIndex: function(index){
        var widget = this._getChildWidgetByIndex(index);
        if (widget){
            if (widget.isFocusEnabled())
                return widget;
            index = index + 1;
            return this._findFocusEnabledChildWidgetByIndex(index);
        }
        return null;
    },

    /**
     * get the center point of a widget in world space
     * @param {ccui.Widget} widget
     * @returns {cc.Point}
     * @private
     */
    _getWorldCenterPoint: function(widget){
        //FIXEDME: we don't need to calculate the content size of layout anymore
        var widgetSize = widget instanceof ccui.Layout ? widget._getLayoutAccumulatedSize() :  widget.getContentSize();
        return widget.convertToWorldSpace(cc.p(widgetSize.width /2, widgetSize.height /2));
    },

    /**
     * this method is called internally by nextFocusedWidget. When the dir is Right/Down, then this method will be called
     * @param {Number} direction
     * @param {ccui.Widget} current the current focused widget
     * @returns {ccui.Widget} the next focused widget
     * @private
     */
    _getNextFocusedWidget: function(direction, current){
        var nextWidget = null, locChildren = this._children;
        var  previousWidgetPos = locChildren.indexOf(current);
        previousWidgetPos = previousWidgetPos + 1;
        if (previousWidgetPos < locChildren.length) {
            nextWidget = this._getChildWidgetByIndex(previousWidgetPos);
            //handle widget
            if (nextWidget) {
                if (nextWidget.isFocusEnabled()) {
                    if (nextWidget instanceof ccui.Layout) {
                        nextWidget._isFocusPassing = true;
                        return nextWidget.findNextFocusedWidget(direction, nextWidget);
                    } else {
                        this.dispatchFocusEvent(current, nextWidget);
                        return nextWidget;
                    }
                } else
                    return this._getNextFocusedWidget(direction, nextWidget);
            } else
                return current;
        } else {
            if (this._loopFocus) {
                if (this._checkFocusEnabledChild()) {
                    previousWidgetPos = 0;
                    nextWidget = this._getChildWidgetByIndex(previousWidgetPos);
                    if (nextWidget.isFocusEnabled()) {
                        if (nextWidget instanceof ccui.Layout) {
                            nextWidget._isFocusPassing = true;
                            return nextWidget.findNextFocusedWidget(direction, nextWidget);
                        } else {
                            this.dispatchFocusEvent(current, nextWidget);
                            return nextWidget;
                        }
                    } else
                        return this._getNextFocusedWidget(direction, nextWidget);
                } else
                    return (current instanceof ccui.Layout) ? current : ccui.Widget._focusedWidget;
            } else{
                if (this._isLastWidgetInContainer(current, direction)){
                    if (this._isWidgetAncestorSupportLoopFocus(this, direction))
                        return ccui.Widget.prototype.findNextFocusedWidget.call(this, direction, this);
                    return (current instanceof ccui.Layout) ? current : ccui.Widget._focusedWidget;
                } else
                    return ccui.Widget.prototype.findNextFocusedWidget.call(this, direction, this);
            }
        }
    },

    /**
     * this method is called internally by nextFocusedWidget. When the dir is Left/Up, then this method will be called
     * @param direction
     * @param {ccui.Widget} current the current focused widget
     * @returns {ccui.Widget} the next focused widget
     * @private
     */
    _getPreviousFocusedWidget: function(direction, current){
        var nextWidget = null, locChildren = this._children;
        var previousWidgetPos = locChildren.indexOf(current);
        previousWidgetPos = previousWidgetPos - 1;
        if (previousWidgetPos >= 0){
            nextWidget = this._getChildWidgetByIndex(previousWidgetPos);
            if (nextWidget.isFocusEnabled()) {
                if (nextWidget instanceof ccui.Layout){
                    nextWidget._isFocusPassing = true;
                    return nextWidget.findNextFocusedWidget(direction, nextWidget);
                }
                this.dispatchFocusEvent(current, nextWidget);
                return nextWidget;
            } else
                return this._getPreviousFocusedWidget(direction, nextWidget);       //handling the disabled widget, there is no actual focus lose or get, so we don't need any envet
        }else {
            if (this._loopFocus){
                if (this._checkFocusEnabledChild()) {
                    previousWidgetPos = locChildren.length -1;
                    nextWidget = this._getChildWidgetByIndex(previousWidgetPos);
                    if (nextWidget.isFocusEnabled()){
                        if (nextWidget instanceof ccui.Layout){
                            nextWidget._isFocusPassing = true;
                            return nextWidget.findNextFocusedWidget(direction, nextWidget);
                        } else {
                            this.dispatchFocusEvent(current, nextWidget);
                            return nextWidget;
                        }
                    } else
                        return this._getPreviousFocusedWidget(direction, nextWidget);
                } else
                    return (current instanceof ccui.Layout) ? current : ccui.Widget._focusedWidget;
            } else {
                if (this._isLastWidgetInContainer(current, direction)) {
                    if (this._isWidgetAncestorSupportLoopFocus(this, direction))
                        return ccui.Widget.prototype.findNextFocusedWidget.call(this, direction, this);
                    return (current instanceof ccui.Layout) ? current : ccui.Widget._focusedWidget;
                } else
                    return ccui.Widget.prototype.findNextFocusedWidget.call(this, direction, this);
            }
        }
    },

    /**
     * find the nth element in the _children array. Only the Widget descendant object will be returned
     * @param {Number} index
     * @returns {ccui.Widget}
     * @private
     */
    _getChildWidgetByIndex: function (index) {
        var locChildren = this._children;
        var size = locChildren.length, count = 0, oldIndex = index;
        while (index < size) {
            var firstChild = locChildren[index];
            if (firstChild && firstChild instanceof ccui.Widget)
                return firstChild;
            count++;
            index++;
        }

        var begin = 0;
        while (begin < oldIndex) {
            var child = locChildren[begin];
            if (child && child instanceof ccui.Widget)
                return child;
            count++;
            begin++;
        }
        return null;
    },

    /**
     * whether it is the last element according to all their parents
     * @param {ccui.Widget} widget
     * @param {Number} direction
     * @returns {Boolean}
     * @private
     */
    _isLastWidgetInContainer:function(widget, direction){
        var parent = widget.getParent();
        if (parent == null || !(parent instanceof ccui.Layout))
            return true;

        var container = parent.getChildren();
        var index = container.indexOf(widget);
        if (parent.getLayoutType() === ccui.Layout.LINEAR_HORIZONTAL) {
            if (direction === ccui.Widget.LEFT) {
                if (index === 0)
                    return this._isLastWidgetInContainer(parent, direction);
                else
                    return false;
            }
            if (direction === ccui.Widget.RIGHT) {
                if (index === container.length - 1)
                    return this._isLastWidgetInContainer(parent, direction);
                else
                    return false;
            }
            if (direction === ccui.Widget.DOWN)
                return this._isLastWidgetInContainer(parent, direction);

            if (direction === ccui.Widget.UP)
                return this._isLastWidgetInContainer(parent, direction);
        } else if(parent.getLayoutType() === ccui.Layout.LINEAR_VERTICAL){
            if (direction === ccui.Widget.UP){
                if (index === 0)
                    return this._isLastWidgetInContainer(parent, direction);
                else
                    return false;
            }
            if (direction === ccui.Widget.DOWN) {
                if (index === container.length - 1)
                    return this._isLastWidgetInContainer(parent, direction);
                else
                    return false;
            }
            if (direction === ccui.Widget.LEFT)
                return this._isLastWidgetInContainer(parent, direction);

            if (direction === ccui.Widget.RIGHT)
                return this._isLastWidgetInContainer(parent, direction);
        } else {
            cc.log("invalid layout Type");
            return false;
        }
    },

    /**
     * Lookup any parent widget with a layout type as the direction, if the layout is loop focused, then return true, otherwise it returns false.
     * @param {ccui.Widget} widget
     * @param {Number} direction
     * @returns {Boolean}
     * @private
     */
    _isWidgetAncestorSupportLoopFocus: function(widget, direction){
        var parent = widget.getParent();
        if (parent == null || !(parent instanceof ccui.Layout))
            return false;
        if (parent.isLoopFocus()) {
            var layoutType = parent.getLayoutType();
            if (layoutType === ccui.Layout.LINEAR_HORIZONTAL) {
                if (direction === ccui.Widget.LEFT || direction === ccui.Widget.RIGHT)
                    return true;
                else
                    return this._isWidgetAncestorSupportLoopFocus(parent, direction);
            }
            if (layoutType === ccui.Layout.LINEAR_VERTICAL){
                if (direction === ccui.Widget.DOWN || direction === ccui.Widget.UP)
                    return true;
                else
                    return this._isWidgetAncestorSupportLoopFocus(parent, direction);
            } else{
                cc.assert(0, "invalid layout type");
                return false;
            }
        } else
            return this._isWidgetAncestorSupportLoopFocus(parent, direction);
    },

    /**
     * pass the focus to the layout's next focus enabled child
     * @param {Number} direction
     * @param {ccui.Widget} current
     * @returns {ccui.Widget}
     * @private
     */
    _passFocusToChild: function(direction, current){
        if (this._checkFocusEnabledChild()) {
            var previousWidget = ccui.Widget.getCurrentFocusedWidget();
            this._findProperSearchingFunctor(direction, previousWidget);
            var index = this.onPassFocusToChild(direction, previousWidget);

            var widget = this._getChildWidgetByIndex(index);
            if (widget instanceof ccui.Layout) {
                widget._isFocusPassing = true;
                return widget.findNextFocusedWidget(direction, widget);
            } else {
                this.dispatchFocusEvent(current, widget);
                return widget;
            }
        }else
            return this;
    },

    /**
     * If there are no focus enabled child in the layout, it will return false, otherwise it returns true
     * @returns {boolean}
     * @private
     */
    _checkFocusEnabledChild: function(){
        var locChildren = this._children;
        for(var i = 0, len = locChildren.length; i < len; i++){
            var widget = locChildren[i];
            if (widget && widget instanceof ccui.Widget && widget.isFocusEnabled())
                return true;
        }
        return false;
    },

    /**
     * Returns the "class name" of widget.
     * @returns {string}
     */
    getDescription: function () {
        return "Layout";
    },

    _createCloneInstance: function () {
        return new ccui.Layout();
    },

    _copyClonedWidgetChildren: function (model) {
        ccui.Widget.prototype._copyClonedWidgetChildren.call(this, model);
    },

    _copySpecialProperties: function (layout) {
        if(!(layout instanceof  ccui.Layout))
            return;
        this.setBackGroundImageScale9Enabled(layout._backGroundScale9Enabled);
        this.setBackGroundImage(layout._backGroundImageFileName, layout._bgImageTexType);
        this.setBackGroundImageCapInsets(layout._backGroundImageCapInsets);
        this.setBackGroundColorType(layout._colorType);
        this.setBackGroundColor(layout._color);
        this.setBackGroundColor(layout._startColor, layout._endColor);
        this.setBackGroundColorOpacity(layout._opacity);
        this.setBackGroundColorVector(layout._alongVector);
        this.setLayoutType(layout._layoutType);
        this.setClippingEnabled(layout._clippingEnabled);
        this.setClippingType(layout._clippingType);
        this._loopFocus = layout._loopFocus;
        this.__passFocusToChild = layout.__passFocusToChild;
        this._isInterceptTouch = layout._isInterceptTouch;
    },

    /**
     * force refresh widget layout
     */
    forceDoLayout: function(){
        this.requestDoLayout();
        this._doLayout();
    },

    _createRenderCmd: function(){
        if(cc._renderType === cc._RENDER_TYPE_WEBGL)
            return new ccui.Layout.WebGLRenderCmd(this);
        else
            return new ccui.Layout.CanvasRenderCmd(this);
    }
});

var _p = ccui.Layout.prototype;

// Extended properties
/** @expose */
_p.clippingEnabled;
cc.defineGetterSetter(_p, "clippingEnabled", _p.isClippingEnabled, _p.setClippingEnabled);
/** @expose */
_p.clippingType;
cc.defineGetterSetter(_p, "clippingType", null, _p.setClippingType);
/** @expose */
_p.layoutType;
cc.defineGetterSetter(_p, "layoutType", _p.getLayoutType, _p.setLayoutType);

_p = null;

/**
 * allocates and initializes a UILayout.
 * @deprecated since v3.0, please use new ccui.Layout() instead.
 * @return {ccui.Layout}
 */
ccui.Layout.create = function () {
    return new ccui.Layout();
};

// Constants

//layoutBackGround color type
/**
 * The None of ccui.Layout's background color type
 * @constant
 * @type {number}
 */
ccui.Layout.BG_COLOR_NONE = 0;
/**
 * The solid of ccui.Layout's background color type, it will use a LayerColor to draw the background.
 * @constant
 * @type {number}
 */
ccui.Layout.BG_COLOR_SOLID = 1;
/**
 * The gradient of ccui.Layout's background color type, it will use a LayerGradient to draw the background.
 * @constant
 * @type {number}
 */
ccui.Layout.BG_COLOR_GRADIENT = 2;

//Layout type
/**
 * The absolute of ccui.Layout's layout type.
 * @type {number}
 * @constant
 */
ccui.Layout.ABSOLUTE = 0;
/**
 * The vertical of ccui.Layout's layout type.
 * @type {number}
 * @constant
 */
ccui.Layout.LINEAR_VERTICAL = 1;
/**
 * The horizontal of ccui.Layout's layout type.
 * @type {number}
 * @constant
 */
ccui.Layout.LINEAR_HORIZONTAL = 2;
/**
 * The relative of ccui.Layout's layout type.
 * @type {number}
 * @constant
 */
ccui.Layout.RELATIVE = 3;

//Layout clipping type
/**
 * The stencil of ccui.Layout's clipping type.
 * @type {number}
 * @constant
 */
ccui.Layout.CLIPPING_STENCIL = 0;
/**
 * The scissor of ccui.Layout's clipping type.
 * @type {number}
 * @constant
 */
ccui.Layout.CLIPPING_SCISSOR = 1;

/**
 * The zOrder value of ccui.Layout's image background.
 * @type {number}
 * @constant
 */
ccui.Layout.BACKGROUND_IMAGE_ZORDER = -2;
/**
 * The zOrder value of ccui.Layout's color background.
 * @type {number}
 * @constant
 */
ccui.Layout.BACKGROUND_RENDERER_ZORDER = -2;