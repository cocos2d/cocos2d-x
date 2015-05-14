/****************************************************************************
 Copyright (c) 2008-2010 Ricardo Quesada
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
 * Text field delegate
 * @class
 * @extends cc.Class
 */
cc.TextFieldDelegate = cc.Class.extend(/** @lends cc.TextFieldDelegate# */{
    /**
     * If the sender doesn't want to attach with IME, return true;
     * @param {cc.TextFieldTTF} sender
     * @return {Boolean}
     */
    onTextFieldAttachWithIME:function (sender) {
        return false;
    },

    /**
     * If the sender doesn't want to detach with IME, return true;
     * @param {cc.TextFieldTTF} sender
     * @return {Boolean}
     */
    onTextFieldDetachWithIME:function (sender) {
        return false;
    },

    /**
     * If the sender doesn't want to insert the text, return true;
     * @param {cc.TextFieldTTF} sender
     * @param {String} text
     * @param {Number} len
     * @return {Boolean}
     */
    onTextFieldInsertText:function (sender, text, len) {
        return false
    },

    /**
     * If the sender doesn't want to delete the delText, return true;
     * @param {cc.TextFieldTTF} sender
     * @param {String} delText
     * @param {Number} len
     * @return {Boolean}
     */
    onTextFieldDeleteBackward:function (sender, delText, len) {
        return false;
    },

    /**
     * If doesn't want draw sender as default, return true.
     * @param {cc.TextFieldTTF} sender
     * @return {Boolean}
     */
    onDraw:function (sender) {
        return false;
    }
});

/**
 * A simple text input field with TTF font.
 * @class
 * @extends cc.LabelTTF
 *
 * @property {cc.Node}      delegate            - Delegate
 * @property {Number}       charCount           - <@readonly> Characators count
 * @property {String}       placeHolder         - Place holder for the field
 * @property {cc.Color}     colorSpaceHolder
 *
 * @param {String} placeholder
 * @param {cc.Size} dimensions
 * @param {Number} alignment
 * @param {String} fontName
 * @param {Number} fontSize
 *
 * @example
 * //example
 * // When five parameters
 * var textField = new cc.TextFieldTTF("<click here for input>", cc.size(100,50), cc.TEXT_ALIGNMENT_LEFT,"Arial", 32);
 * // When three parameters
 * var textField = new cc.TextFieldTTF("<click here for input>", "Arial", 32);
 */
cc.TextFieldTTF = cc.LabelTTF.extend(/** @lends cc.TextFieldTTF# */{
	delegate:null,
	colorSpaceHolder:null,

    _colorText: null,
    _lens:null,
    _inputText:"",
    _placeHolder:"",
    _charCount:0,
    _className:"TextFieldTTF",

    /**
     * Constructor function, override it to extend the construction behavior, remember to call "this._super()" in the extended "ctor" function. <br />
     * creates a cc.TextFieldTTF from a fontName, alignment, dimension and font size.
     * @param {String} placeholder
     * @param {cc.Size} dimensions
     * @param {Number} alignment
     * @param {String} fontName
     * @param {Number} fontSize
     */
    ctor:function (placeholder, dimensions, alignment, fontName, fontSize) {
        this.colorSpaceHolder = cc.color(127, 127, 127);
        this._colorText = cc.color(255,255,255, 255);
        cc.imeDispatcher.addDelegate(this);
        cc.LabelTTF.prototype.ctor.call(this);

        if(fontSize !== undefined){
            this.initWithPlaceHolder("", dimensions, alignment, fontName, fontSize);
            if(placeholder)
                this.setPlaceHolder(placeholder);
        }else if(fontName === undefined && alignment !== undefined){
            this.initWithString("", arguments[1], arguments[2]);
            if(placeholder)
                this.setPlaceHolder(placeholder);
        }
    },

    /**
     * Gets the delegate.
     * @return {cc.Node}
     */
    getDelegate:function () {
        return this.delegate;
    },

    /**
     * Set the delegate.
     * @param {cc.Node} value
     */
    setDelegate:function (value) {
        this.delegate = value;
    },

    /**
     * Gets the char count.
     * @return {Number}
     */
    getCharCount:function () {
        return this._charCount;
    },

    /**
     * Returns the color of space holder.
     * @return {cc.Color}
     */
    getColorSpaceHolder:function () {
        return cc.color(this.colorSpaceHolder);
    },

    /**
     * Sets the color of space holder.
     * @param {cc.Color} value
     */
    setColorSpaceHolder:function (value) {
        this.colorSpaceHolder.r = value.r;
        this.colorSpaceHolder.g = value.g;
        this.colorSpaceHolder.b = value.b;
        this.colorSpaceHolder.a = cc.isUndefined(value.a) ? 255 : value.a;
        if(!this._inputText.length)
            this.setColor(this.colorSpaceHolder);
    },

    /**
     * Sets the color of cc.TextFieldTTF's text.
     * @param {cc.Color} textColor
     */
    setTextColor:function(textColor){
        this._colorText.r = textColor.r;
        this._colorText.g = textColor.g;
        this._colorText.b = textColor.b;
        this._colorText.a = cc.isUndefined(textColor.a) ? 255 : textColor.a;
        if(this._inputText.length)
            this.setColor(this._colorText);
    },

    /**
     * Initializes the cc.TextFieldTTF with a font name, alignment, dimension and font size
     * @param {String} placeholder
     * @param {cc.Size} dimensions
     * @param {Number} alignment
     * @param {String} fontName
     * @param {Number} fontSize
     * @return {Boolean}
     * @example
     * //example
     * var  textField = new cc.TextFieldTTF();
     * // When five parameters
     * textField.initWithPlaceHolder("<click here for input>", cc.size(100,50), cc.TEXT_ALIGNMENT_LEFT,"Arial", 32);
     * // When three parameters
     * textField.initWithPlaceHolder("<click here for input>", "Arial", 32);
     */
    initWithPlaceHolder:function (placeholder, dimensions, alignment, fontName, fontSize) {
        switch (arguments.length) {
            case 5:
                if (placeholder)
                    this.setPlaceHolder(placeholder);
                return this.initWithString(this._placeHolder,fontName, fontSize, dimensions, alignment);
                break;
            case 3:
                if (placeholder)
                    this.setPlaceHolder(placeholder);
                return this.initWithString(this._placeHolder, arguments[1], arguments[2]);
                break;
            default:
                throw "Argument must be non-nil ";
                break;
        }
    },

    /**
     * Input text property
     * @param {String} text
     */
    setString:function (text) {
        text = String(text);
        this._inputText = text || "";

        // if there is no input text, display placeholder instead
        if (!this._inputText.length){
            cc.LabelTTF.prototype.setString.call(this, this._placeHolder);
            this.setColor(this.colorSpaceHolder);
        } else {
            cc.LabelTTF.prototype.setString.call(this,this._inputText);
            this.setColor(this._colorText);
        }
        if(cc._renderType === cc._RENDER_TYPE_CANVAS)
            this._renderCmd._updateTexture();
        this._charCount = this._inputText.length;
    },

    /**
     * Gets the string
     * @return {String}
     */
    getString:function () {
        return this._inputText;
    },

    /**
     * Set the place holder. <br />
     * display this string if string equal "".
     * @param {String} text
     */
    setPlaceHolder:function (text) {
        this._placeHolder = text || "";
        if (!this._inputText.length) {
            cc.LabelTTF.prototype.setString.call(this,this._placeHolder);
            this.setColor(this.colorSpaceHolder);
        }
    },

    /**
     * Gets the place holder. <br />
     * default display string.
     * @return {String}
     */
    getPlaceHolder:function () {
        return this._placeHolder;
    },

    /**
     * Render function using the canvas 2d context or WebGL context, internal usage only, please do not call this function.
     * @param {CanvasRenderingContext2D | WebGLRenderingContext} ctx The render context
     */
    draw:function (ctx) {
        //console.log("size",this._contentSize);
        var context = ctx || cc._renderContext;
        if (this.delegate && this.delegate.onDraw(this))
            return;

        cc.LabelTTF.prototype.draw.call(this, context);
    },

    /**
     * Recursive method that visit its children and draw them.
     * @param {CanvasRenderingContext2D|WebGLRenderingContext} ctx
     */
    visit: function(ctx){
        this._super(ctx);
    },

    //////////////////////////////////////////////////////////////////////////
    // CCIMEDelegate interface
    //////////////////////////////////////////////////////////////////////////
    /**
     * Open keyboard and receive input text.
     * @return {Boolean}
     */
    attachWithIME:function () {
        return cc.imeDispatcher.attachDelegateWithIME(this);
    },

    /**
     * End text input  and close keyboard.
     * @return {Boolean}
     */
    detachWithIME:function () {
        return cc.imeDispatcher.detachDelegateWithIME(this);
    },

    /**
     * Return whether to allow attach with IME.
     * @return {Boolean}
     */
    canAttachWithIME:function () {
        return (this.delegate) ? (!this.delegate.onTextFieldAttachWithIME(this)) : true;
    },

    /**
     * When the delegate detach with IME, this method call by CCIMEDispatcher.
     */
    didAttachWithIME:function () {
    },

    /**
     * Return whether to allow detach with IME.
     * @return {Boolean}
     */
    canDetachWithIME:function () {
        return (this.delegate) ? (!this.delegate.onTextFieldDetachWithIME(this)) : true;
    },

    /**
     * When the delegate detach with IME, this method call by CCIMEDispatcher.
     */
    didDetachWithIME:function () {
    },

    /**
     * Delete backward
     */
    deleteBackward:function () {
        var strLen = this._inputText.length;
        if (strLen === 0)
            return;

        // get the delete byte number
        var deleteLen = 1;    // default, erase 1 byte

        if (this.delegate && this.delegate.onTextFieldDeleteBackward(this, this._inputText[strLen - deleteLen], deleteLen)) {
            // delegate don't want delete backward
            return;
        }

        // if delete all text, show space holder string
        if (strLen <= deleteLen) {
            this._inputText = "";
            this._charCount = 0;
            cc.LabelTTF.prototype.setString.call(this,this._placeHolder);
            this.setColor(this.colorSpaceHolder);
            return;
        }

        // set new input text
        this.string = this._inputText.substring(0, strLen - deleteLen);
    },

    /**
     *  Remove delegate
     */
    removeDelegate:function () {
        cc.imeDispatcher.removeDelegate(this);
    },

    _tipMessage: "please enter your word:",
    /**
     * Sets the input tip message to show on mobile browser.  (mobile Web only)
     * @param {string} tipMessage
     */
    setTipMessage: function (tipMessage) {
        if (tipMessage == null)
            return;
        this._tipMessage = tipMessage;
    },

    /**
     * Gets the input tip message to show on mobile browser.   (mobile Web only)
     * @returns {string}
     */
    getTipMessage: function () {
        return this._tipMessage;
    },

    /**
     * Append the text. <br />
     * Input the character.
     * @param {String} text
     * @param {Number} len
     */
    insertText:function (text, len) {
        var sInsert = text;

        // insert \n means input end
        var pos = sInsert.indexOf('\n');
        if (pos > -1) {
            sInsert = sInsert.substring(0, pos);
        }

        if (sInsert.length > 0) {
            if (this.delegate && this.delegate.onTextFieldInsertText(this, sInsert, sInsert.length)) {
                // delegate doesn't want insert text
                return;
            }

            var sText = this._inputText + sInsert;
            this._charCount = sText.length;
            this.string = sText;
        }

        if (pos === -1)
            return;

        // '\n' has inserted,  let delegate process first
        if (this.delegate && this.delegate.onTextFieldInsertText(this, "\n", 1))
            return;

        // if delegate hasn't process, detach with ime as default
        this.detachWithIME();
    },

    /**
     * Gets the input text.
     * @return {String}
     */
    getContentText:function () {
        return this._inputText;
    },

    //////////////////////////////////////////////////////////////////////////
    // keyboard show/hide notification
    //////////////////////////////////////////////////////////////////////////
    keyboardWillShow:function (info) {
    },
    keyboardDidShow:function (info) {
    },
    keyboardWillHide:function (info) {
    },
    keyboardDidHide:function (info) {
    }
});

var _p = cc.TextFieldTTF.prototype;

// Extended properties
/** @expose */
_p.charCount;
cc.defineGetterSetter(_p, "charCount", _p.getCharCount);
/** @expose */
_p.placeHolder;
cc.defineGetterSetter(_p, "placeHolder", _p.getPlaceHolder, _p.setPlaceHolder);

/**
 * Please use new TextFieldTTF instead. <br />
 * Creates a cc.TextFieldTTF from a fontName, alignment, dimension and font size.
 * @deprecated since v3.0 Please use new TextFieldTTF instead.
 * @param {String} placeholder
 * @param {cc.Size} dimensions
 * @param {Number} alignment
 * @param {String} fontName
 * @param {Number} fontSize
 * @return {cc.TextFieldTTF|Null}
 */
cc.TextFieldTTF.create = function (placeholder, dimensions, alignment, fontName, fontSize) {
    return new cc.TextFieldTTF(placeholder, dimensions, alignment, fontName, fontSize);
};

