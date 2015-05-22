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
 * The text control of Cocos UI.
 * @class
 * @extends ccui.Widget
 *
 * @property {Number}   boundingWidth       - Width of the bounding area of label, the real content width is limited by boundingWidth
 * @property {Number}   boundingHeight      - Height of the bounding area of label, the real content height is limited by boundingHeight
 * @property {String}   string              - The content string of the label
 * @property {Number}   stringLength        - <@readonly> The content string length of the label
 * @property {String}   font                - The label font with a style string: e.g. "18px Verdana"
 * @property {String}   fontName            - The label font name
 * @property {Number}   fontSize            - The label font size
 * @property {Number}   textAlign           - Horizontal Alignment of label, cc.TEXT_ALIGNMENT_LEFT|cc.TEXT_ALIGNMENT_CENTER|cc.TEXT_ALIGNMENT_RIGHT
 * @property {Number}   verticalAlign       - Vertical Alignment of label: cc.VERTICAL_TEXT_ALIGNMENT_TOP|cc.VERTICAL_TEXT_ALIGNMENT_CENTER|cc.VERTICAL_TEXT_ALIGNMENT_BOTTOM
 * @property {Boolean}  touchScaleEnabled   - Indicate whether the label will scale when touching
 */
ccui.Text = ccui.Widget.extend(/** @lends ccui.Text# */{
    _touchScaleChangeEnabled: false,
    _normalScaleValueX: 1,
    _normalScaleValueY: 1,
    _fontName: "Thonburi",
    _fontSize: 10,
    _onSelectedScaleOffset:0.5,
    _labelRenderer: "",
    _textAreaSize: null,
    _textVerticalAlignment: 0,
    _textHorizontalAlignment: 0,
    _className: "Text",
    _type: null,
    _labelRendererAdaptDirty: true,

    /**
     * allocates and initializes a UILabel.
     * Constructor of ccui.Text. override it to extend the construction behavior, remember to call "this._super()" in the extended "ctor" function.
     * @param {String} textContent
     * @param {String} fontName
     * @param {Number} fontSize
     * @example
     * // example
     * var uiLabel = new ccui.Text();
     */
    ctor: function (textContent, fontName, fontSize) {
        this._type = ccui.Text.Type.SYSTEM;
        this._textAreaSize = cc.size(0, 0);
        ccui.Widget.prototype.ctor.call(this);

        fontSize !== undefined && this.init(textContent, fontName, fontSize);

    },

    /**
     * Initializes a ccui.Text. Please do not call this function by yourself, you should pass the parameters to constructor to initialize it.
     * @param {String} textContent
     * @param {String} fontName
     * @param {Number} fontSize
     * @returns {boolean}
     * @override
     */
    init: function (textContent, fontName, fontSize) {
        if (ccui.Widget.prototype.init.call(this)) {
            if(arguments.length > 0){
                this.setFontName(fontName);
                this.setFontSize(fontSize);
                this.setString(textContent);
            }else{
                this.setFontName(this._fontName);
            }
            return true;
        }
        return false;
    },

    _initRenderer: function () {
        this._labelRenderer = new cc.LabelTTF();
        this.addProtectedChild(this._labelRenderer, ccui.Text.RENDERER_ZORDER, -1);
    },

    /**
     * Changes the  value of ccui.Text.
     * @deprecated since v3.0, please use setString() instead.
     * @param {String} text
     */
    setText: function (text) {
        cc.log("Please use the setString");
        this.setString(text);
    },

    /**
     * Changes the  value of ccui.Text.
     * @param {String} text
     */
    setString: function (text) {
        if(text === this._labelRenderer.getString())
            return;
        this._labelRenderer.setString(text);
        this._updateContentSizeWithTextureSize(this._labelRenderer.getContentSize());
        this._labelRendererAdaptDirty = true;
    },

    /**
     * Gets the string value of ccui.Text.
     * @deprecated since v3.0, please use getString instead.
     * @returns {String}
     */
    getStringValue: function () {
        cc.log("Please use the getString");
        return this._labelRenderer.getString();
    },

    /**
     * Gets the string value of ccui.Text.
     * @returns {String}
     */
    getString: function () {
        return this._labelRenderer.getString();
    },

    /**
     * Gets the string length of ccui.Text.
     * @returns {Number}
     */
    getStringLength: function () {
        return this._labelRenderer.getStringLength();
    },

    /**
     * Sets fontSize
     * @param {Number} size
     */
    setFontSize: function (size) {
        this._labelRenderer.setFontSize(size);
        this._fontSize = size;
        this._updateContentSizeWithTextureSize(this._labelRenderer.getContentSize());
        this._labelRendererAdaptDirty = true;
    },

    /**
     * Returns font Size of ccui.Text
     * @returns {Number}
     */
    getFontSize: function () {
        return this._fontSize;
    },

    /**
     * Sets font name
     * @return {String} name
     */
    setFontName: function (name) {
        this._fontName = name;
        this._labelRenderer.setFontName(name);
        this._updateContentSizeWithTextureSize(this._labelRenderer.getContentSize());
        this._labelRendererAdaptDirty = true;
    },

    /**
     * Returns font name of ccui.Text.
     * @returns {string}
     */
    getFontName: function () {
        return this._fontName;
    },

    _setFont: function (font) {
        var res = cc.LabelTTF._fontStyleRE.exec(font);
        if (res) {
            this._fontSize = parseInt(res[1]);
            this._fontName = res[2];
            this._labelRenderer._setFont(font);
            this._labelScaleChangedWithSize();
        }
    },
    _getFont: function () {
        return this._labelRenderer._getFont();
    },

    /**
     * Returns the type of ccui.Text.
     * @returns {null}
     */
    getType: function(){
        return  this._type;
    },

    /**
     * Sets text Area Size
     * @param {cc.Size} size
     */
    setTextAreaSize: function (size) {
        this._labelRenderer.setDimensions(size);
        if (!this._ignoreSize){
            this._customSize = size;
        }
        this._updateContentSizeWithTextureSize(this._labelRenderer.getContentSize());
        this._labelRendererAdaptDirty = true;
    },

    /**
     * Returns renderer's dimension.
     * @returns {cc.Size}
     */
    getTextAreaSize: function(){
        return this._labelRenderer.getDimensions();
    },

    /**
     * Sets Horizontal Alignment of cc.LabelTTF
     * @param {cc.TEXT_ALIGNMENT_LEFT|cc.TEXT_ALIGNMENT_CENTER|cc.TEXT_ALIGNMENT_RIGHT} alignment Horizontal Alignment
     */
    setTextHorizontalAlignment: function (alignment) {
        this._labelRenderer.setHorizontalAlignment(alignment);
        this._updateContentSizeWithTextureSize(this._labelRenderer.getContentSize());
        this._labelRendererAdaptDirty = true;
    },

    /**
     * Returns Horizontal Alignment of label
     * @returns {TEXT_ALIGNMENT_LEFT|TEXT_ALIGNMENT_CENTER|TEXT_ALIGNMENT_RIGHT}
     */
    getTextHorizontalAlignment: function () {
        return this._labelRenderer.getHorizontalAlignment();
    },

    /**
     * Sets Vertical Alignment of label
     * @param {cc.VERTICAL_TEXT_ALIGNMENT_TOP|cc.VERTICAL_TEXT_ALIGNMENT_CENTER|cc.VERTICAL_TEXT_ALIGNMENT_BOTTOM} alignment
     */
    setTextVerticalAlignment: function (alignment) {
        this._labelRenderer.setVerticalAlignment(alignment);
        this._updateContentSizeWithTextureSize(this._labelRenderer.getContentSize());
        this._labelRendererAdaptDirty = true;
    },

    /**
     * Gets text vertical alignment.
     * @returns {VERTICAL_TEXT_ALIGNMENT_TOP|VERTICAL_TEXT_ALIGNMENT_CENTER|VERTICAL_TEXT_ALIGNMENT_BOTTOM}
     */
    getTextVerticalAlignment: function () {
        return this._labelRenderer.getVerticalAlignment();
    },

    /**
     * Sets the touch scale enabled of label.
     * @param {Boolean} enable
     */
    setTouchScaleChangeEnabled: function (enable) {
        this._touchScaleChangeEnabled = enable;
    },

    /**
     * Gets the touch scale enabled of label.
     * @returns {Boolean}
     */
    isTouchScaleChangeEnabled: function () {
        return this._touchScaleChangeEnabled;
    },

    _onPressStateChangedToNormal: function () {
        if (!this._touchScaleChangeEnabled)
            return;
        this._labelRenderer.setScaleX(this._normalScaleValueX);
        this._labelRenderer.setScaleY(this._normalScaleValueY);
    },

    _onPressStateChangedToPressed: function () {
        if (!this._touchScaleChangeEnabled)
            return;
        this._labelRenderer.setScaleX(this._normalScaleValueX + this._onSelectedScaleOffset);
        this._labelRenderer.setScaleY(this._normalScaleValueY + this._onSelectedScaleOffset);
    },

    _onPressStateChangedToDisabled: function () {
    },

    _onSizeChanged: function () {
        ccui.Widget.prototype._onSizeChanged.call(this);
        this._labelRendererAdaptDirty = true;
    },

    _adaptRenderers: function(){
        if (this._labelRendererAdaptDirty) {
            this._labelScaleChangedWithSize();
            this._labelRendererAdaptDirty = false;
        }
    },

    /**
     * Returns the renderer's content size.
     * @override
     * @returns {cc.Size}
     */
    getVirtualRendererSize: function(){
        return this._labelRenderer.getContentSize();
    },

    /**
     * Returns the renderer of ccui.Text.
     * @returns {cc.Node}
     */
    getVirtualRenderer: function () {
        return this._labelRenderer;
    },

    //@since v3.3
    getAutoRenderSize: function(){
        var virtualSize = this._labelRenderer.getContentSize();
        if (!this._ignoreSize) {
            this._labelRenderer.setDimensions(0, 0);
            virtualSize = this._labelRenderer.getContentSize();
            this._labelRenderer.setDimensions(this._contentSize.width, this._contentSize.height);
        }
        return virtualSize;
    },

    _labelScaleChangedWithSize: function () {
        var locContentSize = this._contentSize;
        if (this._ignoreSize) {
            this._labelRenderer.setDimensions(0,0);
            this._labelRenderer.setScale(1.0);
            this._normalScaleValueX = this._normalScaleValueY = 1;
        } else {
            this._labelRenderer.setDimensions(cc.size(locContentSize.width, locContentSize.height));
            var textureSize = this._labelRenderer.getContentSize();
            if (textureSize.width <= 0.0 || textureSize.height <= 0.0) {
                this._labelRenderer.setScale(1.0);
                return;
            }
            var scaleX = locContentSize.width / textureSize.width;
            var scaleY = locContentSize.height / textureSize.height;
            this._labelRenderer.setScaleX(scaleX);
            this._labelRenderer.setScaleY(scaleY);
            this._normalScaleValueX = scaleX;
            this._normalScaleValueY = scaleY;
        }
        this._labelRenderer.setPosition(locContentSize.width / 2.0, locContentSize.height / 2.0);
    },

    /**
     * Returns the "class name" of ccui.Text.
     * @returns {string}
     */
    getDescription: function () {
        return "Label";
    },

    /**
     * Enables shadow style and sets color, offset and blur radius styles.
     * @param {cc.Color} shadowColor
     * @param {cc.Size} offset
     * @param {Number} blurRadius
     */
    enableShadow: function(shadowColor, offset, blurRadius){
        this._labelRenderer.enableShadow(shadowColor, offset, blurRadius);
    },

    /**
     * Enables outline style and sets outline's color and size.
     * @param {cc.Color} outlineColor
     * @param {cc.Size} outlineSize
     */
    enableOutline: function(outlineColor, outlineSize){
        this._labelRenderer.enableStroke(outlineColor, outlineSize);
    },

    /**
     * Enables glow color
     * @param glowColor
     */
    enableGlow: function(glowColor){
        if (this._type === ccui.Text.Type.TTF)
            this._labelRenderer.enableGlow(glowColor);
    },

    /**
     * Disables renderer's effect.
     */
    disableEffect: function(){
        if(this._labelRenderer.disableEffect)
            this._labelRenderer.disableEffect();
    },

    _createCloneInstance: function () {
        return new ccui.Text();
    },

    _copySpecialProperties: function (uiLabel) {
        if(uiLabel instanceof ccui.Text){
            this.setFontName(uiLabel._fontName);
            this.setFontSize(uiLabel.getFontSize());
            this.setString(uiLabel.getString());
            this.setTouchScaleChangeEnabled(uiLabel.touchScaleEnabled);
            this.setTextAreaSize(uiLabel._textAreaSize);
            this.setTextHorizontalAlignment(uiLabel._labelRenderer.getHorizontalAlignment());
            this.setTextVerticalAlignment(uiLabel._labelRenderer.getVerticalAlignment());
            this.setContentSize(uiLabel.getContentSize());
        }
    },

    _setBoundingWidth: function (value) {
        this._textAreaSize.width = value;
        this._labelRenderer._setBoundingWidth(value);
        this._labelScaleChangedWithSize();
    },
    _setBoundingHeight: function (value) {
        this._textAreaSize.height = value;
        this._labelRenderer._setBoundingHeight(value);
        this._labelScaleChangedWithSize();
    },
    _getBoundingWidth: function () {
        return this._textAreaSize.width;
    },
    _getBoundingHeight: function () {
        return this._textAreaSize.height;
    },

    _changePosition: function(){
        this._adaptRenderers();
    },

    setColor: function(color){
        cc.ProtectedNode.prototype.setColor.call(this, color);
        this._labelRenderer.setColor(color);
    },

    setTextColor: function(color){
        this._labelRenderer.setFontFillColor(color);
    },

    getTextColor: function(){
        return this._labelRenderer._getFillStyle();
    }
});

var _p = ccui.Text.prototype;

// Extended properties
/** @expose */
_p.boundingWidth;
cc.defineGetterSetter(_p, "boundingWidth", _p._getBoundingWidth, _p._setBoundingWidth);
/** @expose */
_p.boundingHeight;
cc.defineGetterSetter(_p, "boundingHeight", _p._getBoundingHeight, _p._setBoundingHeight);
/** @expose */
_p.string;
cc.defineGetterSetter(_p, "string", _p.getString, _p.setString);
/** @expose */
_p.stringLength;
cc.defineGetterSetter(_p, "stringLength", _p.getStringLength);
/** @expose */
_p.font;
cc.defineGetterSetter(_p, "font", _p._getFont, _p._setFont);
/** @expose */
_p.fontSize;
cc.defineGetterSetter(_p, "fontSize", _p.getFontSize, _p.setFontSize);
/** @expose */
_p.fontName;
cc.defineGetterSetter(_p, "fontName", _p.getFontName, _p.setFontName);
/** @expose */
_p.textAlign;
cc.defineGetterSetter(_p, "textAlign", _p.getTextHorizontalAlignment, _p.setTextHorizontalAlignment);
/** @expose */
_p.verticalAlign;
cc.defineGetterSetter(_p, "verticalAlign", _p.getTextVerticalAlignment, _p.setTextVerticalAlignment);

_p = null;

/**
 * allocates and initializes a UILabel.
 * @deprecated since v3.0, please use new ccui.Text() instead.
 * @return {ccui.Text}
 */
ccui.Label = ccui.Text.create = function (textContent, fontName, fontSize) {
    return new ccui.Text(textContent, fontName, fontSize);
};

/**
 * The zOrder value of ccui.Text's renderer.
 * @constant
 * @type {number}
 */
ccui.Text.RENDERER_ZORDER = -1;

/**
 * @ignore
 */
ccui.Text.Type = {
    SYSTEM: 0,
    TTF: 1
};