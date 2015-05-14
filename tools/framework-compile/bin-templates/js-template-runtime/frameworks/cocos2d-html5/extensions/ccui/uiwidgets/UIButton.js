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
 * The button controls of Cocos UI.
 * @class
 * @extends ccui.Widget
 *
 * @property {String}   titleText               - The content string of the button title
 * @property {String}   titleFont               - The content string font of the button title
 * @property {Number}   titleFontSize           - The content string font size of the button title
 * @property {String}   titleFontName           - The content string font name of the button title
 * @property {cc.Color} titleFontColor          - The content string font color of the button title
 * @property {Boolean}  pressedActionEnabled    - Indicate whether button has zoom effect when clicked
 */
ccui.Button = ccui.Widget.extend(/** @lends ccui.Button# */{
    _buttonNormalRenderer: null,
    _buttonClickedRenderer: null,
    _buttonDisableRenderer: null,
    _titleRenderer: null,

    _normalFileName: "",
    _clickedFileName: "",
    _disabledFileName: "",

    _prevIgnoreSize: true,
    _scale9Enabled: false,

    _capInsetsNormal: null,
    _capInsetsPressed: null,
    _capInsetsDisabled: null,

    _normalTexType: ccui.Widget.LOCAL_TEXTURE,
    _pressedTexType: ccui.Widget.LOCAL_TEXTURE,
    _disabledTexType: ccui.Widget.LOCAL_TEXTURE,

    _normalTextureSize: null,
    _pressedTextureSize: null,
    _disabledTextureSize: null,

    pressedActionEnabled: false,
    _titleColor: null,
    _normalTextureScaleXInSize: 1,
    _normalTextureScaleYInSize: 1,
    _pressedTextureScaleXInSize: 1,
    _pressedTextureScaleYInSize: 1,

    _zoomScale: 0.1,

    _normalTextureLoaded: false,
    _pressedTextureLoaded: false,
    _disabledTextureLoaded: false,

    _className: "Button",
    _normalTextureAdaptDirty: true,
    _pressedTextureAdaptDirty: true,
    _disabledTextureAdaptDirty: true,

    _fontName: "Thonburi",
    _fontSize: 12,
    _type: 0,

    /**
     * Allocates and initializes a UIButton.
     * Constructor of ccui.Button. override it to extend the construction behavior, remember to call "this._super()" in the extended "ctor" function.
     * @param {String} normalImage
     * @param {String} [selectedImage=""]
     * @param {String} [disableImage=""]
     * @param {Number} [texType=ccui.Widget.LOCAL_TEXTURE]
     * @example
     * // example
     * var uiButton = new ccui.Button();
     */
    ctor: function (normalImage, selectedImage, disableImage, texType) {
        this._capInsetsNormal = cc.rect(0, 0, 0, 0);
        this._capInsetsPressed = cc.rect(0, 0, 0, 0);
        this._capInsetsDisabled = cc.rect(0, 0, 0, 0);
        this._normalTextureSize = cc.size(0, 0);
        this._pressedTextureSize = cc.size(0, 0);
        this._disabledTextureSize = cc.size(0, 0);
        this._titleColor = cc.color.WHITE;
        ccui.Widget.prototype.ctor.call(this);
        this.setTouchEnabled(true);
        this.init(normalImage, selectedImage, disableImage, texType);
    },

    /**
     * Initializes a button. please do not call this function by yourself, you should pass the parameters to constructor to initialize it.
     * @param {String} normalImage
     * @param {String} [selectedImage=""]
     * @param {String} [disableImage=""]
     * @param {Number} [texType=ccui.Widget.LOCAL_TEXTURE]
     * @returns {boolean}
     * @override
     */
    init: function (normalImage, selectedImage,disableImage, texType) {
        if (ccui.Widget.prototype.init.call(this)) {
            if(normalImage === undefined)
                return true;
            this.loadTextures(normalImage, selectedImage,disableImage, texType);
        }
        return false;
    },

    _initRenderer: function () {
        //todo create Scale9Sprite
        this._buttonNormalRenderer = new cc.Sprite();
        this._buttonClickedRenderer = new cc.Sprite();
        this._buttonDisableRenderer = new cc.Sprite();
        this._titleRenderer = new cc.LabelTTF("");
        this._titleRenderer.setAnchorPoint(0.5, 0.5);

        this.addProtectedChild(this._buttonNormalRenderer, ccui.Button.NORMAL_RENDERER_ZORDER, -1);
        this.addProtectedChild(this._buttonClickedRenderer, ccui.Button.PRESSED_RENDERER_ZORDER, -1);
        this.addProtectedChild(this._buttonDisableRenderer, ccui.Button.DISABLED_RENDERER_ZORDER, -1);
        this.addProtectedChild(this._titleRenderer, ccui.Button.TITLE_RENDERER_ZORDER, -1);
    },

    /**
     * Sets if button is using scale9 renderer.
     * @param {Boolean} able true that using scale9 renderer, false otherwise.
     */
    setScale9Enabled: function (able) {
        //todo create Scale9Sprite
        if (this._scale9Enabled === able)
            return;

        this._brightStyle = ccui.Widget.BRIGHT_STYLE_NONE;
        this._scale9Enabled = able;

        this.removeProtectedChild(this._buttonNormalRenderer);
        this.removeProtectedChild(this._buttonClickedRenderer);
        this.removeProtectedChild(this._buttonDisableRenderer);

        if (this._scale9Enabled) {
            this._buttonNormalRenderer = new ccui.Scale9Sprite();
            this._buttonClickedRenderer = new ccui.Scale9Sprite();
            this._buttonDisableRenderer = new ccui.Scale9Sprite();
        } else {
            this._buttonNormalRenderer = new cc.Sprite();
            this._buttonClickedRenderer = new cc.Sprite();
            this._buttonDisableRenderer = new cc.Sprite();
        }

        this._buttonClickedRenderer.setVisible(false);
        this._buttonDisableRenderer.setVisible(false);

        this.loadTextureNormal(this._normalFileName, this._normalTexType);
        this.loadTexturePressed(this._clickedFileName, this._pressedTexType);
        this.loadTextureDisabled(this._disabledFileName, this._disabledTexType);

        this.addProtectedChild(this._buttonNormalRenderer, ccui.Button.NORMAL_RENDERER_ZORDER, -1);
        this.addProtectedChild(this._buttonClickedRenderer, ccui.Button.PRESSED_RENDERER_ZORDER, -1);
        this.addProtectedChild(this._buttonDisableRenderer, ccui.Button.DISABLED_RENDERER_ZORDER, -1);
        if (this._scale9Enabled) {
            var ignoreBefore = this._ignoreSize;
            this.ignoreContentAdaptWithSize(false);
            this._prevIgnoreSize = ignoreBefore;
        } else {
            this.ignoreContentAdaptWithSize(this._prevIgnoreSize);
        }
        this.setCapInsetsNormalRenderer(this._capInsetsNormal);
        this.setCapInsetsPressedRenderer(this._capInsetsPressed);
        this.setCapInsetsDisabledRenderer(this._capInsetsDisabled);
        this.setBright(this._bright);

        this._normalTextureAdaptDirty = true;
        this._pressedTextureAdaptDirty = true;
        this._disabledTextureAdaptDirty = true;
    },

    /**
     *  Returns button is using scale9 renderer or not.
     * @returns {Boolean}
     */
    isScale9Enabled: function () {
        return this._scale9Enabled;
    },

    /**
     * Sets whether ignore the widget size
     * @param {Boolean} ignore true that widget will ignore it's size, use texture size, false otherwise. Default value is true.
     * @override
     */
    ignoreContentAdaptWithSize: function (ignore) {
        if(this._unifySize){
            this._updateContentSize();
            return;
        }
        if (!this._scale9Enabled || (this._scale9Enabled && !ignore)) {
            ccui.Widget.prototype.ignoreContentAdaptWithSize.call(this, ignore);
            this._prevIgnoreSize = ignore;
        }
    },

    /**
     * Returns the renderer size.
     * @returns {cc.Size}
     */
    getVirtualRendererSize: function(){
        if (this._unifySize)
            return this._getNormalSize();

        if (!this._normalTextureLoaded && this._titleRenderer.getString().length > 0) {
            return this._titleRenderer.getContentSize();
        }
        return cc.size(this._normalTextureSize);
    },

    /**
     * Load textures for button.
     * @param {String} normal normal state of texture's filename.
     * @param {String} selected  selected state of texture's filename.
     * @param {String} disabled  disabled state of texture's filename.
     * @param {ccui.Widget.LOCAL_TEXTURE|ccui.Widget.PLIST_TEXTURE} texType
     */
    loadTextures: function (normal, selected, disabled, texType) {
        this.loadTextureNormal(normal, texType);
        this.loadTexturePressed(selected, texType);
        this.loadTextureDisabled(disabled, texType);
    },

    /**
     * Load normal state texture for button.
     * @param {String} normal normal state of texture's filename.
     * @param {ccui.Widget.LOCAL_TEXTURE|ccui.Widget.PLIST_TEXTURE} texType
     */
    loadTextureNormal: function (normal, texType) {
        if (!normal)
            return;
        texType = texType || ccui.Widget.LOCAL_TEXTURE;
        this._normalFileName = normal;
        this._normalTexType = texType;

        var self = this;
        var normalRenderer = this._buttonNormalRenderer;
        if(!normalRenderer._textureLoaded){
            normalRenderer.addEventListener("load", function(){
                self.loadTextureNormal(self._normalFileName, self._normalTexType);
            });
        }
        switch (this._normalTexType){
            case ccui.Widget.LOCAL_TEXTURE:
                //SetTexture cannot load resource
                normalRenderer.initWithFile(normal);
                break;
            case ccui.Widget.PLIST_TEXTURE:
                //SetTexture cannot load resource
                normalRenderer.initWithSpriteFrameName(normal);
                break;
            default:
                break;
        }

        this._normalTextureSize = this._buttonNormalRenderer.getContentSize();
        this._updateChildrenDisplayedRGBA();
        if (this._unifySize){
            if (this._scale9Enabled){
                normalRenderer.setCapInsets(this._capInsetsNormal);
                this._updateContentSizeWithTextureSize(this._getNormalSize());
            }
        }else
            this._updateContentSizeWithTextureSize(this._normalTextureSize);

        this._normalTextureLoaded = true;
        this._normalTextureAdaptDirty = true;
        this._findLayout();
    },

    /**
     * Load selected state texture for button.
     * @param {String} selected selected state of texture's filename.
     * @param {ccui.Widget.LOCAL_TEXTURE|ccui.Widget.PLIST_TEXTURE} texType
     */
    loadTexturePressed: function (selected, texType) {
        if (!selected)
            return;
        texType = texType || ccui.Widget.LOCAL_TEXTURE;
        this._clickedFileName = selected;
        this._pressedTexType = texType;

        var self = this;
        var clickedRenderer = this._buttonClickedRenderer;
        if(!clickedRenderer._textureLoaded){
            clickedRenderer.addEventListener("load", function(){
                self.loadTexturePressed(self._clickedFileName, self._pressedTexType);
            });
        }

        switch (this._pressedTexType) {
            case ccui.Widget.LOCAL_TEXTURE:
                //SetTexture cannot load resource
                clickedRenderer.initWithFile(selected);
                break;
            case ccui.Widget.PLIST_TEXTURE:
                //SetTexture cannot load resource
                clickedRenderer.initWithSpriteFrameName(selected);
                break;
            default:
                break;
        }

        if (this._scale9Enabled)
            clickedRenderer.setCapInsets(this._capInsetsPressed);

        this._pressedTextureSize = this._buttonClickedRenderer.getContentSize();
        this._updateChildrenDisplayedRGBA();

        this._pressedTextureLoaded = true;
        this._pressedTextureAdaptDirty = true;
        this._findLayout();
    },

    /**
     * Load dark state texture for button.
     * @param {String} disabled disabled state of texture's filename.
     * @param {ccui.Widget.LOCAL_TEXTURE|ccui.Widget.PLIST_TEXTURE} texType
     */
    loadTextureDisabled: function (disabled, texType) {
        if (!disabled)
            return;

        texType = texType || ccui.Widget.LOCAL_TEXTURE;
        this._disabledFileName = disabled;
        this._disabledTexType = texType;

        var self = this;
        var disabledRenderer = this._buttonDisableRenderer;
        if(!disabledRenderer._textureLoaded){
            disabledRenderer.addEventListener("load", function() {
                self.loadTextureDisabled(self._disabledFileName, self._disabledTexType);
            });
        }

        switch (this._disabledTexType) {
            case ccui.Widget.LOCAL_TEXTURE:
                //SetTexture cannot load resource
                disabledRenderer.initWithFile(disabled);
                break;
            case ccui.Widget.PLIST_TEXTURE:
                //SetTexture cannot load resource
                disabledRenderer.initWithSpriteFrameName(disabled);
                break;
            default:
                break;
        }

        if (this._scale9Enabled)
            disabledRenderer.setCapInsets(this._capInsetsDisabled);

        this._disabledTextureSize = this._buttonDisableRenderer.getContentSize();
        this._updateChildrenDisplayedRGBA();

        this._disabledTextureLoaded = true;
        this._disabledTextureAdaptDirty = true;
        this._findLayout();
    },

    /**
     * Sets capinsets for button, if button is using scale9 renderer.
     * @param {cc.Rect} capInsets
     */
    setCapInsets: function (capInsets) {
        this.setCapInsetsNormalRenderer(capInsets);
        this.setCapInsetsPressedRenderer(capInsets);
        this.setCapInsetsDisabledRenderer(capInsets);
    },

    /**
     * Sets capinsets for button, if button is using scale9 renderer.
     * @param {cc.Rect} capInsets
     */
    setCapInsetsNormalRenderer: function (capInsets) {
        if(!capInsets)
            return;

        var x = capInsets.x, y = capInsets.y;
        var width = capInsets.width, height = capInsets.height;
        if (this._normalTextureSize.width < width){
            x = 0;
            width = 0;
        }
        if (this._normalTextureSize.height < height){
            y = 0;
            height = 0;
        }

        var locInsets = this._capInsetsNormal;
        locInsets.x = x;
        locInsets.y = y;
        locInsets.width = width;
        locInsets.height = height;

        if (!this._scale9Enabled)
            return;
        this._buttonNormalRenderer.setCapInsets(locInsets);
    },

    /**
     *  Returns normal renderer cap insets.
     * @returns {cc.Rect}
     */
    getCapInsetsNormalRenderer:function(){
        return cc.rect(this._capInsetsNormal);
    },

    /**
     * Sets capinsets for button, if button is using scale9 renderer.
     * @param {cc.Rect} capInsets
     */
    setCapInsetsPressedRenderer: function (capInsets) {
        if(!capInsets || !this._scale9Enabled)
            return;

        var x = capInsets.x, y = capInsets.y;
        var width = capInsets.width, height = capInsets.height;

        if (this._pressedTextureSize.width < width) {
            x = 0;
            width = 0;
        }
        if (this._pressedTextureSize.height < height) {
            y = 0;
            height = 0;
        }

        var locInsets = this._capInsetsPressed;
        locInsets.x = x;
        locInsets.y = y;
        locInsets.width = width;
        locInsets.height = height;

        this._buttonClickedRenderer.setCapInsets(locInsets);
    },

    /**
     *  Returns pressed renderer cap insets.
     * @returns {cc.Rect}
     */
    getCapInsetsPressedRenderer: function () {
        return cc.rect(this._capInsetsPressed);
    },

    /**
     * Sets capinsets for button, if button is using scale9 renderer.
     * @param {cc.Rect} capInsets
     */
    setCapInsetsDisabledRenderer: function (capInsets) {
        if(!capInsets || !this._scale9Enabled)
            return;

        var x = capInsets.x, y = capInsets.y;
        var width = capInsets.width, height = capInsets.height;

        if (this._disabledTextureSize.width < width) {
            x = 0;
            width = 0;
        }
        if (this._disabledTextureSize.height < height) {
            y = 0;
            height = 0;
        }

        var locInsets = this._capInsetsDisabled;
        locInsets.x = x;
        locInsets.y = y;
        locInsets.width = width;
        locInsets.height = height;

        this._buttonDisableRenderer.setCapInsets(locInsets);
    },

    /**
     * Returns disable renderer cap insets.
     * @returns {cc.Rect}
     */
    getCapInsetsDisabledRenderer: function () {
        return cc.rect(this._capInsetsDisabled);
    },

    _onPressStateChangedToNormal: function () {
        this._buttonNormalRenderer.setVisible(true);
        this._buttonClickedRenderer.setVisible(false);
        this._buttonDisableRenderer.setVisible(false);
        if (this._scale9Enabled)
            this._buttonNormalRenderer.setState( ccui.Scale9Sprite.state.NORMAL);
        if (this._pressedTextureLoaded) {
            if (this.pressedActionEnabled){
                this._buttonNormalRenderer.stopAllActions();
                this._buttonClickedRenderer.stopAllActions();
                //var zoomAction = cc.scaleTo(ccui.Button.ZOOM_ACTION_TIME_STEP, this._normalTextureScaleXInSize, this._normalTextureScaleYInSize);
                //fixme: the zoomAction will run in the next frame which will cause the _buttonNormalRenderer to a wrong scale
                //this._buttonNormalRenderer.runAction(zoomAction);
                this._buttonNormalRenderer.setScale(this._normalTextureScaleXInSize, this._normalTextureScaleYInSize);
                this._buttonClickedRenderer.setScale(this._pressedTextureScaleXInSize, this._pressedTextureScaleYInSize);

                this._titleRenderer.stopAllActions();
                if (this._unifySize){
                    var zoomTitleAction = cc.scaleTo(ccui.Button.ZOOM_ACTION_TIME_STEP, 1, 1);
                    this._titleRenderer.runAction(zoomTitleAction);
                }else{
                    this._titleRenderer.setScaleX(1);
                    this._titleRenderer.setScaleY(1);
                }
            }
        } else {
            this._buttonNormalRenderer.stopAllActions();
            this._buttonNormalRenderer.setScale(this._normalTextureScaleXInSize, this._normalTextureScaleYInSize);

            this._titleRenderer.stopAllActions();
            if (this._scale9Enabled)
                this._buttonNormalRenderer.setColor(cc.color.WHITE);

            this._titleRenderer.setScaleX(1);
            this._titleRenderer.setScaleY(1);
        }
    },

    _onPressStateChangedToPressed: function () {
        var locNormalRenderer = this._buttonNormalRenderer;
        if (this._scale9Enabled)
            locNormalRenderer.setState(ccui.Scale9Sprite.state.NORMAL);

        if (this._pressedTextureLoaded) {
            locNormalRenderer.setVisible(false);
            this._buttonClickedRenderer.setVisible(true);
            this._buttonDisableRenderer.setVisible(false);
            if (this.pressedActionEnabled) {
                locNormalRenderer.stopAllActions();
                this._buttonClickedRenderer.stopAllActions();
                var zoomAction = cc.scaleTo(ccui.Button.ZOOM_ACTION_TIME_STEP, this._pressedTextureScaleXInSize + this._zoomScale,
                        this._pressedTextureScaleYInSize + this._zoomScale);
                this._buttonClickedRenderer.runAction(zoomAction);
                locNormalRenderer.setScale(this._pressedTextureScaleXInSize + this._zoomScale, this._pressedTextureScaleYInSize + this._zoomScale);

                this._titleRenderer.stopAllActions();
                this._titleRenderer.runAction(cc.scaleTo(ccui.Button.ZOOM_ACTION_TIME_STEP, 1 + this._zoomScale, 1 + this._zoomScale));
            }
        } else {
            locNormalRenderer.setVisible(true);
            this._buttonClickedRenderer.setVisible(true);
            this._buttonDisableRenderer.setVisible(false);
            locNormalRenderer.stopAllActions();
            locNormalRenderer.setScale(this._normalTextureScaleXInSize + this._zoomScale, this._normalTextureScaleYInSize + this._zoomScale);

            this._titleRenderer.stopAllActions();
            this._titleRenderer.setScaleX(1 + this._zoomScale);
            this._titleRenderer.setScaleY(1 + this._zoomScale);
        }
    },

    _onPressStateChangedToDisabled: function () {
        //if disable resource is null
        if (!this._disabledTextureLoaded){
            if (this._normalTextureLoaded && this._scale9Enabled)
                this._buttonNormalRenderer.setState(ccui.Scale9Sprite.state.GRAY);
        }else{
            this._buttonNormalRenderer.setVisible(false);
            this._buttonDisableRenderer.setVisible(true);
        }

        this._buttonClickedRenderer.setVisible(false);
        this._buttonNormalRenderer.setScale(this._normalTextureScaleXInSize, this._normalTextureScaleYInSize);
        this._buttonClickedRenderer.setScale(this._pressedTextureScaleXInSize, this._pressedTextureScaleYInSize);
    },

    _updateContentSize: function(){
        if (this._unifySize){
            if (this._scale9Enabled)
                ccui.ProtectedNode.setContentSize(this._customSize);
            else{
                var s = this._getNormalSize();
                ccui.ProtectedNode.setContentSize(s);
            }
            this._onSizeChanged();
            return;
        }

        if (this._ignoreSize)
            this.setContentSize(this.getVirtualRendererSize());
    },

    _updateTexturesRGBA: function(){
        this._buttonNormalRenderer.setColor(this.getColor());
        this._buttonClickedRenderer.setColor(this.getColor());
        this._buttonDisableRenderer.setColor(this.getColor());

        this._buttonNormalRenderer.setOpacity(this.getOpacity());
        this._buttonClickedRenderer.setOpacity(this.getOpacity());
        this._buttonDisableRenderer.setOpacity(this.getOpacity());
    },

    _onSizeChanged: function () {
        ccui.Widget.prototype._onSizeChanged.call(this);
        this._updateTitleLocation();
        this._normalTextureAdaptDirty = true;
        this._pressedTextureAdaptDirty = true;
        this._disabledTextureAdaptDirty = true;
    },

    /**
     * Gets the Virtual Renderer of widget.
     * @returns {cc.Node}
     */
    getVirtualRenderer: function () {
        if (this._bright) {
            switch (this._brightStyle) {
                case ccui.Widget.BRIGHT_STYLE_NORMAL:
                    return this._buttonNormalRenderer;
                case ccui.Widget.BRIGHT_STYLE_HIGH_LIGHT:
                    return this._buttonClickedRenderer;
                default:
                    return null;
            }
        } else
            return this._buttonDisableRenderer;
    },

    _normalTextureScaleChangedWithSize: function () {
        if(this._ignoreSize && !this._unifySize){
            if(!this._scale9Enabled){
                this._buttonNormalRenderer.setScale(1);
                this._normalTextureScaleXInSize = this._normalTextureScaleYInSize = 1;
            }
        }else{
            if (this._scale9Enabled){
                this._buttonNormalRenderer.setPreferredSize(this._contentSize);
                this._normalTextureScaleXInSize = this._normalTextureScaleYInSize = 1;
                this._buttonNormalRenderer.setScale(this._normalTextureScaleXInSize, this._normalTextureScaleYInSize);
            }else{
                var textureSize = this._normalTextureSize;
                if (textureSize.width <= 0 || textureSize.height <= 0)
                {
                    this._buttonNormalRenderer.setScale(1);
                    return;
                }
                var scaleX = this._contentSize.width / textureSize.width;
                var scaleY = this._contentSize.height / textureSize.height;
                this._buttonNormalRenderer.setScaleX(scaleX);
                this._buttonNormalRenderer.setScaleY(scaleY);
                this._normalTextureScaleXInSize = scaleX;
                this._normalTextureScaleYInSize = scaleY;
            }
        }
        this._buttonNormalRenderer.setPosition(this._contentSize.width / 2, this._contentSize.height / 2);
    },

    _pressedTextureScaleChangedWithSize: function () {
        if (this._ignoreSize && !this._unifySize) {
            if (!this._scale9Enabled) {
                this._buttonClickedRenderer.setScale(1);
                this._pressedTextureScaleXInSize = this._pressedTextureScaleYInSize = 1;
            }
        } else {
            if (this._scale9Enabled) {
                this._buttonClickedRenderer.setPreferredSize(this._contentSize);
                this._pressedTextureScaleXInSize = this._pressedTextureScaleYInSize = 1;
                this._buttonClickedRenderer.setScale(this._pressedTextureScaleXInSize, this._pressedTextureScaleYInSize);
            } else {
                var textureSize = this._pressedTextureSize;
                if (textureSize.width <= 0 || textureSize.height <= 0) {
                    this._buttonClickedRenderer.setScale(1);
                    return;
                }
                var scaleX = this._contentSize.width / textureSize.width;
                var scaleY = this._contentSize.height / textureSize.height;
                this._buttonClickedRenderer.setScaleX(scaleX);
                this._buttonClickedRenderer.setScaleY(scaleY);
                this._pressedTextureScaleXInSize = scaleX;
                this._pressedTextureScaleYInSize = scaleY;
            }
        }
        this._buttonClickedRenderer.setPosition(this._contentSize.width / 2, this._contentSize.height / 2);
    },

    _disabledTextureScaleChangedWithSize: function () {
        if(this._ignoreSize && !this._unifySize){
            if (this._scale9Enabled)
                this._buttonDisableRenderer.setScale(1);
        }else {
            if (this._scale9Enabled){
                this._buttonDisableRenderer.setScale(1);
                this._buttonDisableRenderer.setPreferredSize(this._contentSize);
            }else{
                var textureSize = this._disabledTextureSize;
                if (textureSize.width <= 0 || textureSize.height <= 0) {
                    this._buttonDisableRenderer.setScale(1);
                    return;
                }
                var scaleX = this._contentSize.width / textureSize.width;
                var scaleY = this._contentSize.height / textureSize.height;
                this._buttonDisableRenderer.setScaleX(scaleX);
                this._buttonDisableRenderer.setScaleY(scaleY);
            }
        }
        this._buttonDisableRenderer.setPosition(this._contentSize.width / 2, this._contentSize.height / 2);
    },

    _adaptRenderers: function(){
        if (this._normalTextureAdaptDirty) {
            this._normalTextureScaleChangedWithSize();
            this._normalTextureAdaptDirty = false;
        }
        if (this._pressedTextureAdaptDirty) {
            this._pressedTextureScaleChangedWithSize();
            this._pressedTextureAdaptDirty = false;
        }
        if (this._disabledTextureAdaptDirty) {
            this._disabledTextureScaleChangedWithSize();
            this._disabledTextureAdaptDirty = false;
        }
    },

    _updateTitleLocation: function(){
        this._titleRenderer.setPosition(this._contentSize.width * 0.5, this._contentSize.height * 0.5);
    },

    /**
     * Changes if button can be clicked zoom effect.
     * @param {Boolean} enabled
     */
    setPressedActionEnabled: function (enabled) {
        this.pressedActionEnabled = enabled;
    },

    /**
     * Sets title text to ccui.Button
     * @param {String} text
     */
    setTitleText: function (text) {
        if(text === this.getTitleText())
            return;
        this._titleRenderer.setString(text);
        if (this._ignoreSize){
            var s = this.getVirtualRendererSize();
            this.setContentSize(s);
        }else{
            this._titleRenderer._renderCmd._updateTTF();
        }
    },

    /**
     * Returns title text of ccui.Button
     * @returns {String} text
     */
    getTitleText: function () {
        return this._titleRenderer.getString();
    },

    /**
     * Sets title color to ccui.Button.
     * @param {cc.Color} color
     */
    setTitleColor: function (color) {
        this._titleRenderer.setFontFillColor(color);
    },

    /**
     * Returns title color of ccui.Button
     * @returns {cc.Color}
     */
    getTitleColor: function () {
        return this._titleRenderer._getFillStyle();
    },

    /**
     * Sets title fontSize to ccui.Button
     * @param {cc.Size} size
     */
    setTitleFontSize: function (size) {
        this._titleRenderer.setFontSize(size);
        this._fontSize = size;
    },

    /**
     * Returns title fontSize of ccui.Button.
     * @returns {Number}
     */
    getTitleFontSize: function () {
        return this._titleRenderer.getFontSize();
    },

    /**
     * When user pressed the button, the button will zoom to a scale.
     * The final scale of the button  equals (button original scale + _zoomScale)
     * @since v3.2
     * @param scale
     */
    setZoomScale: function(scale){
        this._zoomScale = scale;
    },

    /**
     * Returns a zoom scale
     * @since v3.2
     * @returns {number}
     */
    getZoomScale: function(){
        return this._zoomScale;
    },

    /**
     * Returns the normalize of texture size
     * @since v3.3
     * @returns {cc.Size}
     */
    getNormalTextureSize: function(){
        return this._normalTextureSize;
    },

    /**
     * Sets title fontName to ccui.Button.
     * @param {String} fontName
     */
    setTitleFontName: function (fontName) {
        this._titleRenderer.setFontName(fontName);
        this._fontName = fontName;
    },

    /**
     * Get the title renderer.
     * title ttf object.
     * @returns {cc.LabelTTF}
     */
    getTitleRenderer: function(){
        return this._titleRenderer;
    },

    /**
     * Gets title fontName of ccui.Button.
     * @returns {String}
     */
    getTitleFontName: function () {
        return this._titleRenderer.getFontName();
    },

    _setTitleFont: function (font) {
        this._titleRenderer.font = font;
    },
    _getTitleFont: function () {
        return this._titleRenderer.font;
    },

    /**
     * Returns the "class name" of widget.
     * @override
     * @returns {string}
     */
    getDescription: function () {
        return "Button";
    },

    _createCloneInstance: function () {
        return new ccui.Button();
    },

    _copySpecialProperties: function (uiButton) {
        this._prevIgnoreSize = uiButton._prevIgnoreSize;
        this.setScale9Enabled(uiButton._scale9Enabled);
        this.loadTextureNormal(uiButton._normalFileName, uiButton._normalTexType);
        this.loadTexturePressed(uiButton._clickedFileName, uiButton._pressedTexType);
        this.loadTextureDisabled(uiButton._disabledFileName, uiButton._disabledTexType);
        this.setCapInsetsNormalRenderer(uiButton._capInsetsNormal);
        this.setCapInsetsPressedRenderer(uiButton._capInsetsPressed);
        this.setCapInsetsDisabledRenderer(uiButton._capInsetsDisabled);
        this.setTitleText(uiButton.getTitleText());
        this.setTitleFontName(uiButton.getTitleFontName());
        this.setTitleFontSize(uiButton.getTitleFontSize());
        this.setTitleColor(uiButton.getTitleColor());
        this.setPressedActionEnabled(uiButton.pressedActionEnabled);
        this.setZoomScale(uiButton._zoomScale);
    },

    setColor: function(color){
        cc.ProtectedNode.prototype.setColor.call(this, color);
        this._updateTexturesRGBA();
    },

    _getNormalSize: function(){
        var titleSize;
        if (this._titleRenderer !== null)
            titleSize = this._titleRenderer.getContentSize();

        var imageSize;
        if (this._buttonNormalRenderer !== null)
            imageSize = this._buttonNormalRenderer.getContentSize();
        var width = titleSize.width > imageSize.width ? titleSize.width : imageSize.width;
        var height = titleSize.height > imageSize.height ? titleSize.height : imageSize.height;

        return cc.size(width,height);
    }
});

var _p = ccui.Button.prototype;

// Extended properties
/** @expose */
_p.titleText;
cc.defineGetterSetter(_p, "titleText", _p.getTitleText, _p.setTitleText);
/** @expose */
_p.titleFont;
cc.defineGetterSetter(_p, "titleFont", _p._getTitleFont, _p._setTitleFont);
/** @expose */
_p.titleFontSize;
cc.defineGetterSetter(_p, "titleFontSize", _p.getTitleFontSize, _p.setTitleFontSize);
/** @expose */
_p.titleFontName;
cc.defineGetterSetter(_p, "titleFontName", _p.getTitleFontName, _p.setTitleFontName);
/** @expose */
_p.titleColor;
cc.defineGetterSetter(_p, "titleColor", _p.getTitleColor, _p.setTitleColor);

_p = null;

/**
 * allocates and initializes a UIButton.
 * @deprecated since v3.0, please use new ccui.Button() instead.
 * @param {string} [normalImage]    normal state texture name
 * @param {string} [selectedImage]  selected state texture name
 * @param {string} [disableImage]   disabled state texture name
 * @param {string} [texType]
 * @return {ccui.Button}
 */
ccui.Button.create = function (normalImage, selectedImage, disableImage, texType) {
    return new ccui.Button(normalImage, selectedImage, disableImage, texType);
};

// Constants
/**
 * The normal renderer's zOrder value of ccui.Button.
 * @constant
 * @type {number}
 */
ccui.Button.NORMAL_RENDERER_ZORDER = -2;
/**
 * The pressed renderer's zOrder value ccui.Button.
 * @constant
 * @type {number}
 */
ccui.Button.PRESSED_RENDERER_ZORDER = -2;
/**
 * The disabled renderer's zOrder value of ccui.Button.
 * @constant
 * @type {number}
 */
ccui.Button.DISABLED_RENDERER_ZORDER = -2;
/**
 * The title renderer's zOrder value of ccui.Button.
 * @constant
 * @type {number}
 */
ccui.Button.TITLE_RENDERER_ZORDER = -1;

/**
 * the zoom action time step of ccui.Button
 * @constant
 * @type {number}
 */
ccui.Button.ZOOM_ACTION_TIME_STEP = 0.05;

/**
 * @ignore
 */
ccui.Button.SYSTEM = 0;
ccui.Button.TTF = 1;
