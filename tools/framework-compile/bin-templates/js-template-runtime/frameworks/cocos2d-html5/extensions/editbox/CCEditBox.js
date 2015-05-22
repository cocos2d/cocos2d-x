/****************************************************************************
 Copyright (c) 2011-2012 cocos2d-x.org
 Copyright (c) 2013-2014 Chukong Technologies Inc.
 Copyright (c) 2012 James Chen

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
 * @constant
 * @type Number
 */
cc.KEYBOARD_RETURNTYPE_DEFAULT = 0;

/**
 * @constant
 * @type Number
 */
cc.KEYBOARD_RETURNTYPE_DONE = 1;

/**
 * @constant
 * @type Number
 */
cc.KEYBOARD_RETURNTYPE_SEND = 2;

/**
 * @constant
 * @type Number
 */
cc.KEYBOARD_RETURNTYPE_SEARCH = 3;

/**
 * @constant
 * @type Number
 */
cc.KEYBOARD_RETURNTYPE_GO = 4;

/**
 * The EditBoxInputMode defines the type of text that the user is allowed * to enter.
 * @constant
 * @type Number
 */
cc.EDITBOX_INPUT_MODE_ANY = 0;

/**
 * The user is allowed to enter an e-mail address.
 * @constant
 * @type Number
 */
cc.EDITBOX_INPUT_MODE_EMAILADDR = 1;

/**
 * The user is allowed to enter an integer value.
 * @constant
 * @type Number
 */
cc.EDITBOX_INPUT_MODE_NUMERIC = 2;

/**
 * The user is allowed to enter a phone number.
 * @constant
 * @type Number
 */
cc.EDITBOX_INPUT_MODE_PHONENUMBER = 3;

/**
 * The user is allowed to enter a URL.
 * @constant
 * @type Number
 */
cc.EDITBOX_INPUT_MODE_URL = 4;

/**
 * The user is allowed to enter a real number value.
 * This extends kEditBoxInputModeNumeric by allowing a decimal point.
 * @constant
 * @type Number
 */
cc.EDITBOX_INPUT_MODE_DECIMAL = 5;

/**
 * The user is allowed to enter any text, except for line breaks.
 * @constant
 * @type Number
 */
cc.EDITBOX_INPUT_MODE_SINGLELINE = 6;

/**
 * Indicates that the text entered is confidential data that should be
 * obscured whenever possible. This implies EDIT_BOX_INPUT_FLAG_SENSITIVE.
 * @constant
 * @type Number
 */
cc.EDITBOX_INPUT_FLAG_PASSWORD = 0;

/**
 * Indicates that the text entered is sensitive data that the
 * implementation must never store into a dictionary or table for use
 * in predictive, auto-completing, or other accelerated input schemes.
 * A credit card number is an example of sensitive data.
 * @constant
 * @type Number
 */
cc.EDITBOX_INPUT_FLAG_SENSITIVE = 1;

/**
 * This flag is a hint to the implementation that during text editing,
 * the initial letter of each word should be capitalized.
 * @constant
 * @type Number
 */
cc.EDITBOX_INPUT_FLAG_INITIAL_CAPS_WORD = 2;

/**
 * This flag is a hint to the implementation that during text editing,
 * the initial letter of each sentence should be capitalized.
 * @constant
 * @type Number
 */
cc.EDITBOX_INPUT_FLAG_INITIAL_CAPS_SENTENCE = 3;

/**
 * Capitalize all characters automatically.
 * @constant
 * @type Number
 */
cc.EDITBOX_INPUT_FLAG_INITIAL_CAPS_ALL_CHARACTERS = 4;

/**
 * @class
 * @extends cc.Class
 */
cc.EditBoxDelegate = cc.Class.extend({
    /**
     * This method is called when an edit box gains focus after keyboard is shown.
     * @param {cc.EditBox} sender
     */
    editBoxEditingDidBegin: function (sender) {
    },

    /**
     * This method is called when an edit box loses focus after keyboard is hidden.
     * @param {cc.EditBox} sender
     */
    editBoxEditingDidEnd: function (sender) {
    },

    /**
     * This method is called when the edit box text was changed.
     * @param {cc.EditBox} sender
     * @param {String} text
     */
    editBoxTextChanged: function (sender, text) {
    },

    /**
     * This method is called when the return button was pressed or the outside area of keyboard was touched.
     * @param {cc.EditBox} sender
     */
    editBoxReturn: function (sender) {
    }
});

/**
 * <p>cc.EditBox is a brief Class for edit box.<br/>
 * You can use this widget to gather small amounts of text from the user.</p>
 *
 * @class
 * @extends cc.ControlButton
 *
 * @property {String}   string                  - Content string of edit box
 * @property {String}   maxLength               - Max length of the content string
 * @property {String}   font                    - <@writeonly> Config font of edit box
 * @property {String}   fontName                - <@writeonly> Config font name of edit box
 * @property {Number}   fontSize                - <@writeonly> Config font size of edit box
 * @property {cc.Color} fontColor               - <@writeonly> Config font color of edit box
 * @property {String}   placeHolder             - Place holder of edit box
 * @property {String}   placeHolderFont         - <@writeonly> Config font of place holder
 * @property {String}   placeHolderFontName     - <@writeonly> Config font name of place holder
 * @property {Number}   placeHolderFontSize     - <@writeonly> Config font size of place holder
 * @property {cc.Color} placeHolderFontColor    - <@writeonly> Config font color of place holder
 * @property {Number}   inputFlag               - <@writeonly> Input flag of edit box, one of the EditBoxInputFlag constants. e.g.cc.EDITBOX_INPUT_FLAG_PASSWORD
 * @property {Object}   delegate                - <@writeonly> Delegate of edit box
 * @property {Number}   inputMode               - <@writeonly> Input mode of the edit box. Value should be one of the EditBoxInputMode constants.
 * @property {Number}   returnType              - <@writeonly> Return type of edit box, value should be one of the KeyboardReturnType constants.
 *
 */
cc.EditBox = cc.ControlButton.extend({
    _domInputSprite: null,

    _delegate: null,
    _editBoxInputMode: cc.EDITBOX_INPUT_MODE_ANY,
    _editBoxInputFlag: cc.EDITBOX_INPUT_FLAG_SENSITIVE,
    _keyboardReturnType: cc.KEYBOARD_RETURNTYPE_DEFAULT,

    _text: "",
    _placeholderText: "",
    _textColor: null,
    _placeholderColor: null,
    _maxLength: 50,
    _adjustHeight: 18,

    _edTxt: null,
    _edFontSize: 14,
    _edFontName: "Arial",

    _placeholderFontName: "",
    _placeholderFontSize: 14,

    _tooltip: false,
    _className: "EditBox",

    /**
     * constructor of cc.EditBox
     * @param {cc.Size} size
     * @param {cc.Scale9Sprite} normal9SpriteBg
     * @param {cc.Scale9Sprite} press9SpriteBg
     * @param {cc.Scale9Sprite} disabled9SpriteBg
     */
    ctor: function (size, normal9SpriteBg, press9SpriteBg, disabled9SpriteBg) {
        cc.ControlButton.prototype.ctor.call(this);

        this._textColor = cc.color.WHITE;
        this._placeholderColor = cc.color.GRAY;
        this.setContentSize(size);
        var tmpDOMSprite = this._domInputSprite = new cc.Sprite();
        tmpDOMSprite.draw = function () {};  //redefine draw function
        this.addChild(tmpDOMSprite);
        var selfPointer = this;
        var tmpEdTxt = this._edTxt = cc.newElement("input");
        tmpEdTxt.type = "text";
        tmpEdTxt.style.fontSize = this._edFontSize + "px";
        tmpEdTxt.style.color = "#000000";
        tmpEdTxt.style.border = 0;
        tmpEdTxt.style.background = "transparent";
        //tmpEdTxt.style.paddingLeft = "2px";
        tmpEdTxt.style.width = "100%";
        tmpEdTxt.style.height = "100%";
        tmpEdTxt.style.active = 0;
        tmpEdTxt.style.outline = "medium";
        tmpEdTxt.style.padding = "0";
        var onCanvasClick = function() { tmpEdTxt.blur();};
        
        // TODO the event listener will be remove when EditBox removes from parent.
        cc._addEventListener(tmpEdTxt, "input", function () {
            if (selfPointer._delegate && selfPointer._delegate.editBoxTextChanged)
                selfPointer._delegate.editBoxTextChanged(selfPointer, this.value);
        });
        cc._addEventListener(tmpEdTxt, "keypress", function (e) {
            if (e.keyCode === cc.KEY.enter) {
                e.stopPropagation();
                e.preventDefault();
                cc._canvas.focus();
            }
        });
        cc._addEventListener(tmpEdTxt, "focus", function () {
            if (this.value === selfPointer._placeholderText) {
                this.value = "";
                this.style.fontSize = selfPointer._edFontSize + "px";
                this.style.color = cc.colorToHex(selfPointer._textColor);
                if (selfPointer._editBoxInputFlag === cc.EDITBOX_INPUT_FLAG_PASSWORD)
                    selfPointer._edTxt.type = "password";
                else
                    selfPointer._edTxt.type = "text";
            }
            if (selfPointer._delegate && selfPointer._delegate.editBoxEditingDidBegin)
                selfPointer._delegate.editBoxEditingDidBegin(selfPointer);
            cc._addEventListener(cc._canvas, "click", onCanvasClick);
        });
        cc._addEventListener(tmpEdTxt, "blur", function () {
            if (this.value === "") {
                this.value = selfPointer._placeholderText;
                this.style.fontSize = selfPointer._placeholderFontSize + "px";
                this.style.color = cc.colorToHex(selfPointer._placeholderColor);
                selfPointer._edTxt.type = "text";
            }
            if (selfPointer._delegate && selfPointer._delegate.editBoxEditingDidEnd)
                selfPointer._delegate.editBoxEditingDidEnd(selfPointer);
            if (selfPointer._delegate && selfPointer._delegate.editBoxReturn)
                selfPointer._delegate.editBoxReturn(selfPointer);
            cc._canvas.removeEventListener('click', onCanvasClick);
        });

        cc.DOM.convert(tmpDOMSprite);
        tmpDOMSprite.dom.appendChild(tmpEdTxt);
        tmpDOMSprite.dom.showTooltipDiv = false;
        tmpDOMSprite.dom.style.width = (size.width - 6) + "px";
        tmpDOMSprite.dom.style.height = (size.height - 6) + "px";

        //this._domInputSprite.dom.style.borderWidth = "1px";
        //this._domInputSprite.dom.style.borderStyle = "solid";
        //this._domInputSprite.dom.style.borderRadius = "8px";
        tmpDOMSprite.canvas.remove();

        if (this.initWithSizeAndBackgroundSprite(size, normal9SpriteBg)) {
            if (press9SpriteBg)
                this.setBackgroundSpriteForState(press9SpriteBg, cc.CONTROL_STATE_HIGHLIGHTED);
            if (disabled9SpriteBg)
                this.setBackgroundSpriteForState(disabled9SpriteBg, cc.CONTROL_STATE_DISABLED);
        }
    },

    /**
     * Set the font.
     * @param {String} fontName  The font name.
     * @param {Number} fontSize  The font size.
     */
    setFont: function (fontName, fontSize) {
        this._edFontSize = fontSize;
        this._edFontName = fontName;
        this._setFontToEditBox();
    },

    _setFont: function (fontStyle) {
        var res = cc.LabelTTF._fontStyleRE.exec(fontStyle);
        if (res) {
            this._edFontSize = parseInt(res[1]);
            this._edFontName = res[2];
            this._setFontToEditBox();
        }
    },

    /**
     * set fontName
     * @param {String} fontName
     */
    setFontName: function (fontName) {
        this._edFontName = fontName;
        this._setFontToEditBox();
    },

    /**
     * set fontSize
     * @param {Number} fontSize
     */
    setFontSize: function (fontSize) {
        this._edFontSize = fontSize;
        this._setFontToEditBox();
    },

    _setFontToEditBox: function () {
        if (this._edTxt.value !== this._placeholderText) {
            this._edTxt.style.fontFamily = this._edFontName;
            this._edTxt.style.fontSize = this._edFontSize + "px";
            if (this._editBoxInputFlag === cc.EDITBOX_INPUT_FLAG_PASSWORD)
                this._edTxt.type = "password";
            else
                this._edTxt.type = "text";
        }
    },

    /**
     *  Set the text entered in the edit box.
     * @deprecated
     * @param {string} text The given text.
     */
    setText: function (text) {
        cc.log("Please use the setString");
        this.setString(text);
    },

    /**
     *  Set the text entered in the edit box.
     * @param {string} text The given text.
     */
    setString: function (text) {
        if (text != null) {
            if (text === "") {
                this._edTxt.value = this._placeholderText;
                this._edTxt.style.color = cc.colorToHex(this._placeholderColor);
                this._edTxt.type = "text";
            } else {
                this._edTxt.value = text;
                this._edTxt.style.color = cc.colorToHex(this._textColor);
                if (this._editBoxInputFlag === cc.EDITBOX_INPUT_FLAG_PASSWORD)
                    this._edTxt.type = "password";
                else
                    this._edTxt.type = "text";
            }
        }
    },

    /**
     * Set the font color of the widget's text.
     * @param {cc.Color} color
     */
    setFontColor: function (color) {
        this._textColor = color;
        if (this._edTxt.value !== this._placeholderText) {
            this._edTxt.style.color = cc.colorToHex(color);
        }
    },

    /**
     * <p>
     * Sets the maximum input length of the edit box. <br/>
     * Setting this value enables multiline input mode by default.
     * </p>
     * @param {Number} maxLength The maximum length.
     */
    setMaxLength: function (maxLength) {
        if (!isNaN(maxLength) && maxLength > 0) {
            this._maxLength = maxLength;
            this._edTxt.maxLength = maxLength;
        }
    },

    /**
     * Gets the maximum input length of the edit box.
     * @return {Number} Maximum input length.
     */
    getMaxLength: function () {
        return this._maxLength;
    },

    /**
     * Set a text in the edit box that acts as a placeholder when an edit box is empty.
     * @param {string} text The given text.
     */
    setPlaceHolder: function (text) {
        if (text != null) {
            var oldPlaceholderText = this._placeholderText;
            this._placeholderText = text;
            if (this._edTxt.value === oldPlaceholderText) {
                this._edTxt.value = text;
                this._edTxt.style.color = cc.colorToHex(this._placeholderColor);
                this._setPlaceholderFontToEditText();
            }
        }
    },

    /**
     * Set the placeholder's font.
     * @param {String} fontName
     * @param {Number} fontSize
     */
    setPlaceholderFont: function (fontName, fontSize) {
        this._placeholderFontName = fontName;
        this._placeholderFontSize = fontSize;
        this._setPlaceholderFontToEditText();
    },
    _setPlaceholderFont: function (fontStyle) {
        var res = cc.LabelTTF._fontStyleRE.exec(fontStyle);
        if (res) {
            this._placeholderFontName = res[2];
            this._placeholderFontSize = parseInt(res[1]);
            this._setPlaceholderFontToEditText();
        }
    },

    /**
     * Set the placeholder's fontName.
     * @param {String} fontName
     */
    setPlaceholderFontName: function (fontName) {
        this._placeholderFontName = fontName;
        this._setPlaceholderFontToEditText();
    },

    /**
     * Set the placeholder's fontSize.
     * @param {Number} fontSize
     */
    setPlaceholderFontSize: function (fontSize) {
        this._placeholderFontSize = fontSize;
        this._setPlaceholderFontToEditText();
    },

    _setPlaceholderFontToEditText: function () {
        if (this._edTxt.value === this._placeholderText) {
            this._edTxt.style.fontFamily = this._placeholderFontName;
            this._edTxt.style.fontSize = this._placeholderFontSize + "px";
            this._edTxt.type = "text";
        }
    },

    /**
     * Set the font color of the placeholder text when the edit box is empty.
     * @param {cc.Color} color
     */
    setPlaceholderFontColor: function (color) {
        this._placeholderColor = color;
        if (this._edTxt.value === this._placeholderText) {
            this._edTxt.style.color = cc.colorToHex(color);
        }
    },

    /**
     * Set the input flags that are to be applied to the edit box.
     * @param {Number} inputFlag One of the EditBoxInputFlag constants.
     * e.g.cc.EDITBOX_INPUT_FLAG_PASSWORD
     */
    setInputFlag: function (inputFlag) {
        this._editBoxInputFlag = inputFlag;
        if ((this._edTxt.value !== this._placeholderText) && (inputFlag === cc.EDITBOX_INPUT_FLAG_PASSWORD))
            this._edTxt.type = "password";
        else
            this._edTxt.type = "text";
    },

    /**
     * Gets the  input string of the edit box.
     * @deprecated
     * @return {string}
     */
    getText: function () {
        cc.log("Please use the getString");
        return this._edTxt.value;
    },

    /**
     * Gets the  input string of the edit box.
     * @return {string}
     */
    getString: function () {
        if(this._edTxt.value === this._placeholderText)
            return "";
        return this._edTxt.value;
    },

    /**
     * Init edit box with specified size.
     * @param {cc.Size} size
     * @param {cc.Color | cc.Scale9Sprite} normal9SpriteBg
     */
    initWithSizeAndBackgroundSprite: function (size, normal9SpriteBg) {
        if (this.initWithBackgroundSprite(normal9SpriteBg)) {
            this._domInputSprite.x = 3;
            this._domInputSprite.y = 3;

            this.setZoomOnTouchDown(false);
            this.setPreferredSize(size);
            this.x = 0;
            this.y = 0;
            this._addTargetWithActionForControlEvent(this, this.touchDownAction, cc.CONTROL_EVENT_TOUCH_UP_INSIDE);
            return true;
        }
        return false;
    },

    /* override functions */
    /**
     * Set the delegate for edit box.
     * @param {cc.EditBoxDelegate} delegate
     */
    setDelegate: function (delegate) {
        this._delegate = delegate;
    },

    /**
     * Get a text in the edit box that acts as a placeholder when an
     * edit box is empty.
     * @return {String}
     */
    getPlaceHolder: function () {
        return this._placeholderText;
    },

    /**
     * Set the input mode of the edit box.
     * @param {Number} inputMode One of the EditBoxInputMode constants.
     */
    setInputMode: function (inputMode) {
        this._editBoxInputMode = inputMode;
    },

    /**
     * Set the return type that are to be applied to the edit box.
     * @param {Number} returnType One of the CCKeyboardReturnType constants.
     */
    setReturnType: function (returnType) {
        this._keyboardReturnType = returnType;
    },

    keyboardWillShow: function (info) {
        var rectTracked = cc.EditBox.getRect(this);
        // some adjustment for margin between the keyboard and the edit box.
        rectTracked.y -= 4;
        // if the keyboard area doesn't intersect with the tracking node area, nothing needs to be done.
        if (!rectTracked.intersectsRect(info.end)) {
            cc.log("needn't to adjust view layout.");
            return;
        }

        // assume keyboard at the bottom of screen, calculate the vertical adjustment.
        this._adjustHeight = info.end.getMaxY() - rectTracked.getMinY();
        // CCLOG("CCEditBox:needAdjustVerticalPosition(%f)", m_fAdjustHeight);

        //callback
    },
    keyboardDidShow: function (info) {
    },
    keyboardWillHide: function (info) {
        //if (m_pEditBoxImpl != NULL) {
        //    m_pEditBoxImpl->doAnimationWhenKeyboardMove(info.duration, -m_fAdjustHeight);
        //}
    },
    keyboardDidHide: function (info) {
    },

    touchDownAction: function (sender, controlEvent) {
        //this._editBoxImpl.openKeyboard();
    },

    /**
     * @warning HTML5 Only
     * @param {cc.Size} size
     * @param {cc.color} bgColor
     */
    initWithBackgroundColor: function (size, bgColor) {
        this._edWidth = size.width;
        this.dom.style.width = this._edWidth.toString() + "px";
        this._edHeight = size.height;
        this.dom.style.height = this._edHeight.toString() + "px";
        this.dom.style.backgroundColor = cc.colorToHex(bgColor);
    }
});

var _p = cc.EditBox.prototype;

// Extended properties
/** @expose */
_p.font;
cc.defineGetterSetter(_p, "font", null, _p._setFont);
/** @expose */
_p.fontName;
cc.defineGetterSetter(_p, "fontName", null, _p.setFontName);
/** @expose */
_p.fontSize;
cc.defineGetterSetter(_p, "fontSize", null, _p.setFontSize);
/** @expose */
_p.fontColor;
cc.defineGetterSetter(_p, "fontColor", null, _p.setFontColor);
/** @expose */
_p.string;
cc.defineGetterSetter(_p, "string", _p.getString, _p.setString);
/** @expose */
_p.maxLength;
cc.defineGetterSetter(_p, "maxLength", _p.getMaxLength, _p.setMaxLength);
/** @expose */
_p.placeHolder;
cc.defineGetterSetter(_p, "placeHolder", _p.getPlaceHolder, _p.setPlaceHolder);
/** @expose */
_p.placeHolderFont;
cc.defineGetterSetter(_p, "placeHolderFont", null, _p._setPlaceholderFont);
/** @expose */
_p.placeHolderFontName;
cc.defineGetterSetter(_p, "placeHolderFontName", null, _p.setPlaceholderFontName);
/** @expose */
_p.placeHolderFontSize;
cc.defineGetterSetter(_p, "placeHolderFontSize", null, _p.setPlaceholderFontSize);
/** @expose */
_p.placeHolderFontColor;
cc.defineGetterSetter(_p, "placeHolderFontColor", null, _p.setPlaceholderFontColor);
/** @expose */
_p.inputFlag;
cc.defineGetterSetter(_p, "inputFlag", null, _p.setInputFlag);
/** @expose */
_p.delegate;
cc.defineGetterSetter(_p, "delegate", null, _p.setDelegate);
/** @expose */
_p.inputMode;
cc.defineGetterSetter(_p, "inputMode", null, _p.setInputMode);
/** @expose */
_p.returnType;
cc.defineGetterSetter(_p, "returnType", null, _p.setReturnType);

_p = null;

/**
 * get the rect of a node in world coordinate frame
 * @function
 * @param {cc.Node} node
 * @return {cc.Rect}
 */
cc.EditBox.getRect = function (node) {
    var contentSize = node.getContentSize();
    var rect = cc.rect(0, 0, contentSize.width, contentSize.height);
    return cc.rectApplyAffineTransform(rect, node.getNodeToWorldTransform());
};

/**
 * create a edit box with size and background-color or
 * @deprecated since v3.0, please use new cc.EditBox(size, normal9SpriteBg, press9SpriteBg, disabled9SpriteBg) instead
 * @param {cc.Size} size
 * @param {cc.Scale9Sprite } normal9SpriteBg
 * @param {cc.Scale9Sprite } [press9SpriteBg]
 * @param {cc.Scale9Sprite } [disabled9SpriteBg]
 * @return {cc.EditBox}
 */
cc.EditBox.create = function (size, normal9SpriteBg, press9SpriteBg, disabled9SpriteBg) {
    return new cc.EditBox(size, normal9SpriteBg, press9SpriteBg, disabled9SpriteBg);
};




