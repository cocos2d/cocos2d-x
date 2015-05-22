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
 * @ignore
 */
//it's a private class, it's a renderer of ccui.TextField.
ccui._TextFieldRenderer = cc.TextFieldTTF.extend({
    _maxLengthEnabled: false,
    _maxLength: 0,
    _passwordEnabled: false,
    _passwordStyleText: "",
    _attachWithIME: false,
    _detachWithIME: false,
    _insertText: false,
    _deleteBackward: false,
    _className: "_TextFieldRenderer",

    ctor: function () {
        cc.TextFieldTTF.prototype.ctor.call(this);
        this._maxLengthEnabled = false;
        this._maxLength = 0;
        this._passwordEnabled = false;
        this._passwordStyleText = "*";
        this._attachWithIME = false;
        this._detachWithIME = false;
        this._insertText = false;
        this._deleteBackward = false;
    },

    onEnter: function () {
        cc.TextFieldTTF.prototype.onEnter.call(this);
        cc.TextFieldTTF.prototype.setDelegate.call(this, this);
    },

    onTextFieldAttachWithIME: function (sender) {
        this.setAttachWithIME(true);
        return false;
    },

    onTextFieldInsertText: function (sender, text, len) {
        if (len === 1 && text === "\n")
            return false;

        this.setInsertText(true);
        return (this._maxLengthEnabled) && (cc.TextFieldTTF.prototype.getCharCount.call(this) >= this._maxLength);
    },

    onTextFieldDeleteBackward: function (sender, delText, nLen) {
        this.setDeleteBackward(true);
        return false;
    },

    onTextFieldDetachWithIME: function (sender) {
        this.setDetachWithIME(true);
        return false;
    },

    insertText: function (text, len) {
        var input_text = text;

        if (text !== "\n"){
            if (this._maxLengthEnabled){
                var text_count = this.getString().length;
                if (text_count >= this._maxLength){
                    // password
                    if (this._passwordEnabled)
                        this.setPasswordText(this.getString());
                    return;
                }
            }
        }
        cc.TextFieldTTF.prototype.insertText.call(this, input_text, len);

        // password
        if (this._passwordEnabled && cc.TextFieldTTF.prototype.getCharCount.call(this) > 0)
            this.setPasswordText(this.getString());
    },

    deleteBackward: function () {
        cc.TextFieldTTF.prototype.deleteBackward.call(this);

        if (cc.TextFieldTTF.prototype.getCharCount.call(this) > 0 && this._passwordEnabled)
            this.setPasswordText(this._inputText);
    },

    openIME: function () {
        cc.TextFieldTTF.prototype.attachWithIME.call(this);
    },

    closeIME: function () {
        cc.TextFieldTTF.prototype.detachWithIME.call(this);
    },

    setMaxLengthEnabled: function (enable) {
        this._maxLengthEnabled = enable;
    },

    isMaxLengthEnabled: function () {
        return this._maxLengthEnabled;
    },

    setMaxLength: function (length) {
        this._maxLength = length;
    },

    getMaxLength: function () {
        return this._maxLength;
    },

    getCharCount: function () {
        return cc.TextFieldTTF.prototype.getCharCount.call(this);
    },

    setPasswordEnabled: function (enable) {
        this._passwordEnabled = enable;
    },

    isPasswordEnabled: function () {
        return this._passwordEnabled;
    },

    setPasswordStyleText: function (styleText) {
        if (styleText.length > 1)
            return;
        var header = styleText.charCodeAt(0);
        if (header < 33 || header > 126)
            return;
        this._passwordStyleText = styleText;
    },

    setPasswordText: function (text) {
        var tempStr = "";
        var text_count = text.length;
        var max = text_count;

        if (this._maxLengthEnabled && text_count > this._maxLength)
            max = this._maxLength;

        for (var i = 0; i < max; ++i)
            tempStr += this._passwordStyleText;

        cc.LabelTTF.prototype.setString.call(this, tempStr);
    },

    setAttachWithIME: function (attach) {
        this._attachWithIME = attach;
    },

    getAttachWithIME: function () {
        return this._attachWithIME;
    },

    setDetachWithIME: function (detach) {
        this._detachWithIME = detach;
    },

    getDetachWithIME: function () {
        return this._detachWithIME;
    },

    setInsertText: function (insert) {
        this._insertText = insert;
    },

    getInsertText: function () {
        return this._insertText;
    },

    setDeleteBackward: function (deleteBackward) {
        this._deleteBackward = deleteBackward;
    },

    getDeleteBackward: function () {
        return this._deleteBackward;
    },

    onDraw: function (sender) {
        return false;
    }
});

ccui._TextFieldRenderer.create = function (placeholder, fontName, fontSize) {
    var ret = new ccui._TextFieldRenderer();
    if (ret && ret.initWithString("", fontName, fontSize)) {
        if (placeholder)
            ret.setPlaceHolder(placeholder);
        return ret;
    }
    return null;
};

/**
 *
 * @class
 * @extends ccui.Widget
 *
 * @property {String}   string              - The content string of the label
 * @property {String}   placeHolder         - The place holder of the text field
 * @property {String}   font                - The text field font with a style string: e.g. "18px Verdana"
 * @property {String}   fontName            - The text field font name
 * @property {Number}   fontSize            - The text field font size
 * @property {Boolean}  maxLengthEnabled    - Indicate whether max length limit is enabled
 * @property {Number}   maxLength           - The max length of the text field
 * @property {Boolean}  passwordEnabled     - Indicate whether the text field is for entering password
 */
ccui.TextField = ccui.Widget.extend(/** @lends ccui.TextField# */{
    _textFieldRenderer: null,
    _touchWidth: 0,
    _touchHeight: 0,
    _useTouchArea: false,
    _textFieldEventListener: null,
    _textFieldEventSelector: null,
    _passwordStyleText: "",
    _textFieldRendererAdaptDirty: true,
    _fontName: "",
    _fontSize: 12,

    _ccEventCallback: null,

    /**
     * allocates and initializes a UITextField.
     * Constructor of ccui.TextField. override it to extend the construction behavior, remember to call "this._super()" in the extended "ctor" function.
     * @param {string} placeholder
     * @param {string} fontName
     * @param {Number} fontSize
     * @example
     * // example
     * var uiTextField = new ccui.TextField();
     */
    ctor: function (placeholder, fontName, fontSize) {
        ccui.Widget.prototype.ctor.call(this);
        if (fontName)
            this.setFontName(fontName);
        if (fontSize)
            this.setFontSize(fontSize);
        if (placeholder)
            this.setPlaceHolder(placeholder);
    },

    /**
     * Initializes a ccui.TextField. Please do not call this function by yourself, you should pass the parameters to constructor to initialize it.
     * @returns {boolean}
     * @override
     */
    init: function(){
        if(ccui.Widget.prototype.init.call(this)){
            this.setTouchEnabled(true);
            return true;
        }
        return false;
    },

    /**
     * Calls parent class' onEnter and schedules update function.
     * @override
     */
    onEnter: function () {
        ccui.Widget.prototype.onEnter.call(this);
        this.scheduleUpdate();
    },

    _initRenderer: function () {
        this._textFieldRenderer = ccui._TextFieldRenderer.create("input words here", "Thonburi", 20);
        this.addProtectedChild(this._textFieldRenderer, ccui.TextField.RENDERER_ZORDER, -1);
    },

    /**
     * Sets touch size of ccui.TextField.
     * @param {cc.Size} size
     */
    setTouchSize: function (size) {
        this._touchWidth = size.width;
        this._touchHeight = size.height;
    },

    /**
     * Sets whether use touch area.
     * @param enable
     */
    setTouchAreaEnabled: function(enable){
        this._useTouchArea = enable;
    },

    /**
     * Checks a point if is in ccui.TextField's space
     * @param {cc.Point} pt
     * @returns {boolean}
     */
    hitTest: function(pt){
        if (this._useTouchArea) {
            var nsp = this.convertToNodeSpace(pt);
            var bb = cc.rect(
                -this._touchWidth * this._anchorPoint.x,
                -this._touchHeight * this._anchorPoint.y,
                this._touchWidth, this._touchHeight
            );

            return ( nsp.x >= bb.x && nsp.x <= bb.x + bb.width &&
                nsp.y >= bb.y && nsp.y <= bb.y + bb.height );
        } else
            return ccui.Widget.prototype.hitTest.call(this, pt);
    },

    /**
     * Returns touch size of ccui.TextField.
     * @returns {cc.Size}
     */
    getTouchSize: function () {
        return cc.size(this._touchWidth, this._touchHeight);
    },

    /**
     *  Changes the string value of textField.
     * @deprecated since v3.0, please use setString instead.
     * @param {String} text
     */
    setText: function (text) {
        cc.log("Please use the setString");
        this.setString(text);
    },

    /**
     *  Changes the string value of textField.
     * @param {String} text
     */
    setString: function (text) {
        if (text == null)
            return;

        text = String(text);
        if (this.isMaxLengthEnabled())
            text = text.substr(0, this.getMaxLength());
        if (this.isPasswordEnabled()) {
            this._textFieldRenderer.setPasswordText(text);
            this._textFieldRenderer.setString("");
            this._textFieldRenderer.insertText(text, text.length);
        } else
            this._textFieldRenderer.setString(text);
        this._textFieldRendererAdaptDirty = true;
        this._updateContentSizeWithTextureSize(this._textFieldRenderer.getContentSize());
    },

    /**
     * Sets the placeholder string. <br />
     * display this string if string equal "".
     * @param {String} value
     */
    setPlaceHolder: function (value) {
        this._textFieldRenderer.setPlaceHolder(value);
        this._textFieldRendererAdaptDirty = true;
        this._updateContentSizeWithTextureSize(this._textFieldRenderer.getContentSize());
    },

    /**
     * Returns the placeholder string.
     * @returns {String}
     */
    getPlaceHolder: function () {
        return this._textFieldRenderer.getPlaceHolder();
    },

    /**
     * Returns the color of ccui.TextField's place holder.
     * @returns {cc.Color}
     */
    getPlaceHolderColor: function(){
        return this._textFieldRenderer.getPlaceHolderColor();
    },

    /**
     * Sets the place holder color to ccui.TextField.
     * @param color
     */
    setPlaceHolderColor: function(color){
        this._textFieldRenderer.setColorSpaceHolder(color);
    },

    /**
     * Sets the text color to ccui.TextField
     * @param textColor
     */
    setTextColor: function(textColor){
        this._textFieldRenderer.setTextColor(textColor);
    },

    /**
     * Sets font size for ccui.TextField.
     * @param {Number} size
     */
    setFontSize: function (size) {
        this._textFieldRenderer.setFontSize(size);
        this._fontSize = size;
        this._textFieldRendererAdaptDirty = true;
        this._updateContentSizeWithTextureSize(this._textFieldRenderer.getContentSize());
    },

    /**
     * Gets font size of ccui.TextField.
     * @return {Number} size
     */
    getFontSize: function () {
        return this._fontSize;
    },

    /**
     * Sets font name for ccui.TextField
     * @param {String} name
     */
    setFontName: function (name) {
        this._textFieldRenderer.setFontName(name);
        this._fontName = name;
        this._textFieldRendererAdaptDirty = true;
        this._updateContentSizeWithTextureSize(this._textFieldRenderer.getContentSize());
    },

    /**
     * Returns font name of ccui.TextField.
     * @return {String} font name
     */
    getFontName: function () {
        return this._fontName;
    },

    /**
     * detach with IME
     */
    didNotSelectSelf: function () {
        this._textFieldRenderer.detachWithIME();
    },

    /**
     * Returns textField string value
     * @deprecated since v3.0, please use getString instead.
     * @returns {String}
     */
    getStringValue: function () {
        cc.log("Please use the getString");
        return this.getString();
    },

    /**
     * Returns string value of ccui.TextField.
     * @returns {String}
     */
    getString: function () {
        return this._textFieldRenderer.getString();
    },

    /**
     * Returns the length of ccui.TextField.
     * @returns {Number}
     */
    getStringLength: function(){
        return this._textFieldRenderer.getStringLength();
    },

    /**
     * The touch began event callback handler.
     * @param {cc.Point} touchPoint
     */
    onTouchBegan: function (touchPoint, unusedEvent) {
        var self = this;
        var pass = ccui.Widget.prototype.onTouchBegan.call(self, touchPoint, unusedEvent);
        if (self._hit) {
            setTimeout(function(){
                self._textFieldRenderer.attachWithIME();
            }, 0);
        }else{
            setTimeout(function(){
                self._textFieldRenderer.detachWithIME();
            }, 0);
        }
        return pass;
    },

    /**
     * Sets Whether to open string length limit for ccui.TextField.
     * @param {Boolean} enable
     */
    setMaxLengthEnabled: function (enable) {
        this._textFieldRenderer.setMaxLengthEnabled(enable);
    },

    /**
     * Returns Whether to open string length limit.
     * @returns {Boolean}
     */
    isMaxLengthEnabled: function () {
        return this._textFieldRenderer.isMaxLengthEnabled();
    },

    /**
     * Sets the max length of ccui.TextField. Only when you turn on the string length limit, it is valid.
     * @param {number} length
     */
    setMaxLength: function (length) {
        this._textFieldRenderer.setMaxLength(length);
        this.setString(this.getString());
    },

    /**
     * Returns the max length of ccui.TextField.
     * @returns {number} length
     */
    getMaxLength: function () {
        return this._textFieldRenderer.getMaxLength();
    },

    /**
     * Sets whether to open setting string as password character.
     * @param {Boolean} enable
     */
    setPasswordEnabled: function (enable) {
        this._textFieldRenderer.setPasswordEnabled(enable);
    },

    /**
     * Returns whether to open setting string as password character.
     * @returns {Boolean}
     */
    isPasswordEnabled: function () {
        return this._textFieldRenderer.isPasswordEnabled();
    },

    /**
     * Sets the password style character, Only when you turn on setting string as password character, it is valid.
     * @param styleText
     */
    setPasswordStyleText: function(styleText){
        this._textFieldRenderer.setPasswordStyleText(styleText);
        this._passwordStyleText = styleText;

        this.setString(this.getString());
    },

    /**
     * Returns the password style character.
     * @returns {String}
     */
    getPasswordStyleText: function () {
        return this._passwordStyleText;
    },

    update: function (dt) {
        if (this.getDetachWithIME()) {
            this._detachWithIMEEvent();
            this.setDetachWithIME(false);
        }
        if (this.getAttachWithIME()) {
            this._attachWithIMEEvent();
            this.setAttachWithIME(false);
        }
        if (this.getInsertText()) {
            this._textFieldRendererAdaptDirty = true;
            this._updateContentSizeWithTextureSize(this._textFieldRenderer.getContentSize());

            this._insertTextEvent();
            this.setInsertText(false);
        }
        if (this.getDeleteBackward()) {
            this._textFieldRendererAdaptDirty = true;
            this._updateContentSizeWithTextureSize(this._textFieldRenderer.getContentSize());

            this._deleteBackwardEvent();
            this.setDeleteBackward(false);
        }
    },

    /**
     * Returns whether attach with IME.
     * @returns {Boolean}
     */
    getAttachWithIME: function () {
        return this._textFieldRenderer.getAttachWithIME();
    },

    /**
     * Sets attach with IME.
     * @param {Boolean} attach
     */
    setAttachWithIME: function (attach) {
        this._textFieldRenderer.setAttachWithIME(attach);
    },

    /**
     * Returns whether detach with IME.
     * @returns {Boolean}
     */
    getDetachWithIME: function () {
        return this._textFieldRenderer.getDetachWithIME();
    },

    /**
     * Sets detach with IME.
     * @param {Boolean} detach
     */
    setDetachWithIME: function (detach) {
        this._textFieldRenderer.setDetachWithIME(detach);
    },

    /**
     * Returns insertText string of ccui.TextField.
     * @returns {String}
     */
    getInsertText: function () {
        return this._textFieldRenderer.getInsertText();
    },

    /**
     * Sets insertText string to ccui.TextField.
     * @param {String} insertText
     */
    setInsertText: function (insertText) {
        this._textFieldRenderer.setInsertText(insertText);
    },

    /**
     * Returns the delete backward of ccui.TextField.
     * @returns {Boolean}
     */
    getDeleteBackward: function () {
        return this._textFieldRenderer.getDeleteBackward();
    },

    /**
     * Sets the delete backward of ccui.TextField.
     * @param {Boolean} deleteBackward
     */
    setDeleteBackward: function (deleteBackward) {
        this._textFieldRenderer.setDeleteBackward(deleteBackward);
    },

    _attachWithIMEEvent: function () {
        if(this._textFieldEventSelector){
            if (this._textFieldEventListener)
                this._textFieldEventSelector.call(this._textFieldEventListener, this, ccui.TextField.EVENT_ATTACH_WITH_IME);
            else
                this._textFieldEventSelector(this, ccui.TextField.EVENT_ATTACH_WITH_IME);
        }
        if (this._ccEventCallback){
            this._ccEventCallback(this, ccui.TextField.EVENT_ATTACH_WITH_IME);
        }
    },

    _detachWithIMEEvent: function () {
        if(this._textFieldEventSelector){
            if (this._textFieldEventListener)
                this._textFieldEventSelector.call(this._textFieldEventListener, this, ccui.TextField.EVENT_DETACH_WITH_IME);
            else
                this._textFieldEventSelector(this, ccui.TextField.EVENT_DETACH_WITH_IME);
        }
        if (this._ccEventCallback)
            this._ccEventCallback(this, ccui.TextField.EVENT_DETACH_WITH_IME);
    },

    _insertTextEvent: function () {
        if(this._textFieldEventSelector){
            if (this._textFieldEventListener)
                this._textFieldEventSelector.call(this._textFieldEventListener, this, ccui.TextField.EVENT_INSERT_TEXT);
            else
                this._textFieldEventSelector(this, ccui.TextField.EVENT_INSERT_TEXT);          //eventCallback
        }
        if (this._ccEventCallback)
            this._ccEventCallback(this, ccui.TextField.EVENT_INSERT_TEXT);
    },

    _deleteBackwardEvent: function () {
        if(this._textFieldEventSelector){
            if (this._textFieldEventListener)
                this._textFieldEventSelector.call(this._textFieldEventListener, this, ccui.TextField.EVENT_DELETE_BACKWARD);
            else
                this._textFieldEventSelector(this, ccui.TextField.EVENT_DELETE_BACKWARD);         //eventCallback
        }
        if (this._ccEventCallback)
            this._ccEventCallback(this, ccui.TextField.EVENT_DELETE_BACKWARD);
    },

    /**
     * Adds event listener to cuci.TextField.
     * @param {Object} [target=]
     * @param {Function} selector
     * @deprecated since v3.0, please use addEventListener instead.
     */
    addEventListenerTextField: function (selector, target) {
        this.addEventListener(selector, target);
    },

    /**
     * Adds event listener callback.
     * @param {Object} [target=]
     * @param {Function} selector
     */
    addEventListener: function(selector, target){
        this._textFieldEventSelector = selector;        //when target is undefined, _textFieldEventSelector is ccEventCallback.
        this._textFieldEventListener = target;
    },

    _onSizeChanged: function () {
        ccui.Widget.prototype._onSizeChanged.call(this);
        this._textFieldRendererAdaptDirty = true;
    },

    _adaptRenderers: function(){
        if (this._textFieldRendererAdaptDirty) {
            this._textfieldRendererScaleChangedWithSize();
            this._textFieldRendererAdaptDirty = false;
        }
    },

    _textfieldRendererScaleChangedWithSize: function () {
        if (!this._ignoreSize)
            this._textFieldRenderer.setDimensions(this._contentSize);
        this._textFieldRenderer.setPosition(this._contentSize.width / 2, this._contentSize.height / 2);
    },

    //@since v3.3
    getAutoRenderSize: function(){
        var virtualSize = this._textFieldRenderer.getContentSize();
        if (!this._ignoreSize) {
            this._textFieldRenderer.setDimensions(0, 0);
            virtualSize = this._textFieldRenderer.getContentSize();
            this._textFieldRenderer.setDimensions(this._contentSize.width, this._contentSize.height);
        }
        return virtualSize;
    },

    /**
     * Returns the ccui.TextField's content size.
     * @returns {cc.Size}
     */
    getVirtualRendererSize: function(){
        return this._textFieldRenderer.getContentSize();
    },

    /**
     * Returns the renderer of ccui.TextField.
     * @returns {cc.Node}
     */
    getVirtualRenderer: function () {
        return this._textFieldRenderer;
    },

    /**
     * Returns the "class name" of ccui.TextField.
     * @returns {string}
     */
    getDescription: function () {
        return "TextField";
    },

    /**
     * Open keyboard and receive input text.
     * @return {Boolean}
     */
    attachWithIME: function () {
        this._textFieldRenderer.attachWithIME();
    },

    _createCloneInstance: function () {
        return new ccui.TextField();
    },

    _copySpecialProperties: function (textField) {
        this.setString(textField._textFieldRenderer.getString());
        this.setPlaceHolder(textField.getString());
        this.setFontSize(textField._textFieldRenderer.getFontSize());
        this.setFontName(textField._textFieldRenderer.getFontName());
        this.setMaxLengthEnabled(textField.isMaxLengthEnabled());
        this.setMaxLength(textField.getMaxLength());
        this.setPasswordEnabled(textField.isPasswordEnabled());
        this.setPasswordStyleText(textField._passwordStyleText);
        this.setAttachWithIME(textField.getAttachWithIME());
        this.setDetachWithIME(textField.getDetachWithIME());
        this.setInsertText(textField.getInsertText());
        this.setDeleteBackward(textField.getDeleteBackward());
        this._ccEventCallback = textField._ccEventCallback;
        this._textFieldEventListener = textField._textFieldEventListener;
        this._textFieldEventSelector = textField._textFieldEventSelector;
    },

    /**
     * Sets the text area size to ccui.TextField.
     * @param {cc.Size} size
     */
    setTextAreaSize: function(size){
        this.setContentSize(size);
    },

    /**
     * Sets the text horizontal alignment of ccui.TextField.
     * @param alignment
     */
    setTextHorizontalAlignment: function(alignment){
        this._textFieldRenderer.setHorizontalAlignment(alignment);
    },

    /**
     * Sets the text vertical alignment of ccui.TextField.
     * @param alignment
     */
    setTextVerticalAlignment: function(alignment){
        this._textFieldRenderer.setVerticalAlignment(alignment);
    },
    _setFont: function (font) {
        this._textFieldRenderer._setFont(font);
        this._textFieldRendererAdaptDirty = true;
    },

    _getFont: function () {
        return this._textFieldRenderer._getFont();
    },

    _changePosition: function(){
        this._adaptRenderers();
    }
});

/**
 * Creates a ccui.TextField.
 * @deprecated since v3.0, please use new ccui.TextField() instead.
 * @param {String} placeholder
 * @param {String} fontName
 * @param {Number} fontSize
 * @returns {ccui.TextField}
 */
ccui.TextField.create = function(placeholder, fontName, fontSize){
    return new ccui.TextField(placeholder, fontName, fontSize);
};

var _p = ccui.TextField.prototype;

// Extended properties
/** @expose */
_p.string;
cc.defineGetterSetter(_p, "string", _p.getString, _p.setString);
/** @expose */
_p.placeHolder;
cc.defineGetterSetter(_p, "placeHolder", _p.getPlaceHolder, _p.setPlaceHolder);
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
_p.maxLengthEnabled;
cc.defineGetterSetter(_p, "maxLengthEnabled", _p.isMaxLengthEnabled, _p.setMaxLengthEnabled);
/** @expose */
_p.maxLength;
cc.defineGetterSetter(_p, "maxLength", _p.getMaxLength, _p.setMaxLength);
/** @expose */
_p.passwordEnabled;
cc.defineGetterSetter(_p, "passwordEnabled", _p.isPasswordEnabled, _p.setPasswordEnabled);

_p = null;

// Constants
//TextField event
/**
 * The attach with IME event flag of ccui.TextField
 * @constant
 * @type {number}
 */
ccui.TextField.EVENT_ATTACH_WITH_IME = 0;
/**
 * The detach with IME event flag of ccui.TextField
 * @constant
 * @type {number}
 */
ccui.TextField.EVENT_DETACH_WITH_IME = 1;
/**
 * The insert text event flag of ccui.TextField
 * @constant
 * @type {number}
 */
ccui.TextField.EVENT_INSERT_TEXT = 2;
/**
 * The delete backward event flag of ccui.TextField
 * @constant
 * @type {number}
 */
ccui.TextField.EVENT_DELETE_BACKWARD = 3;

/**
 * The zOrder value of ccui.TextField's renderer.
 * @constant
 * @type {number}
 */
ccui.TextField.RENDERER_ZORDER = -1;