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
 * IME Keyboard Notification Info structure
 * @param {cc.Rect} begin the soft keyboard rectangle when animatin begin
 * @param {cc.Rect} end the soft keyboard rectangle when animatin end
 * @param {Number} duration the soft keyboard animation duration
 */
cc.IMEKeyboardNotificationInfo = function (begin, end, duration) {
    this.begin = begin || cc.rect(0, 0, 0, 0);
    this.end = end || cc.rect(0, 0, 0, 0);
    this.duration = duration || 0;
};

/**
 * Input method editor delegate.
 * @class
 * @extends cc.Class
 */
cc.IMEDelegate = cc.Class.extend(/** @lends cc.IMEDelegate# */{
    /**
     * Constructor function, override it to extend the construction behavior, remember to call "this._super()" in the extended "ctor" function.
     */
    ctor:function () {
        cc.imeDispatcher.addDelegate(this);
    },
    /**
     * Remove delegate
     */
    removeDelegate:function () {
        cc.imeDispatcher.removeDelegate(this);
    },
    /**
     * Remove delegate
     * @return {Boolean}
     */
    attachWithIME:function () {
        return cc.imeDispatcher.attachDelegateWithIME(this);
    },
    /**
     * Detach with IME
     * @return {Boolean}
     */
    detachWithIME:function () {
        return cc.imeDispatcher.detachDelegateWithIME(this);
    },

    /**
     * Decide the delegate instance is ready for receive ime message or not.<br />
     * Called by CCIMEDispatcher.
     * @return {Boolean}
     */
    canAttachWithIME:function () {
        return false;
    },

    /**
     * When the delegate detach with IME, this method call by CCIMEDispatcher.
     */
    didAttachWithIME:function () {
    },

    /**
     * Decide the delegate instance can stop receive ime message or not.
     * @return {Boolean}
     */
    canDetachWithIME:function () {
        return false;
    },

    /**
     * When the delegate detach with IME, this method call by CCIMEDispatcher.
     */
    didDetachWithIME:function () {
    },

    /**
     * Called by CCIMEDispatcher when some text input from IME.
     */
    insertText:function (text, len) {
    },

    /**
     * Called by CCIMEDispatcher when user clicked the backward key.
     */
    deleteBackward:function () {
    },

    /**
     * Called by CCIMEDispatcher for get text which delegate already has.
     * @return {String}
     */
    getContentText:function () {
        return "";
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

/**
 * cc.imeDispatcher is a singleton object which manage input message dispatching.
 * @class
 * @name cc.imeDispatcher
 */
cc.IMEDispatcher = cc.Class.extend(/**  @lends cc.imeDispatcher# */{
    _domInputControl:null,
    impl:null,
    _currentInputString:"",
    _lastClickPosition:null,
    /**
     * Constructor function, override it to extend the construction behavior, remember to call "this._super()" in the extended "ctor" function.
     */
    ctor:function () {
        this.impl = new cc.IMEDispatcher.Impl();
        this._lastClickPosition = cc.p(0, 0);
    },

    init:function () {
        if (cc.sys.isMobile)
            return;
        this._domInputControl = cc.$("#imeDispatcherInput");
        if (!this._domInputControl) {
            this._domInputControl = cc.$new("input");
            this._domInputControl.setAttribute("type", "text");
            this._domInputControl.setAttribute("id", "imeDispatcherInput");
            this._domInputControl.resize(0.0, 0.0);
            this._domInputControl.translates(0, 0);
            this._domInputControl.style.opacity = "0";
            //this._domInputControl.style.filter = "alpha(opacity = 0)";
            this._domInputControl.style.fontSize = "1px";
            this._domInputControl.setAttribute('tabindex', 2);
            this._domInputControl.style.position = "absolute";
            this._domInputControl.style.top = 0;
            this._domInputControl.style.left = 0;
            document.body.appendChild(this._domInputControl);
        }
        var selfPointer = this;
        //add event listener
        cc._addEventListener(this._domInputControl, "input", function () {
            selfPointer._processDomInputString(selfPointer._domInputControl.value);
        }, false);
        cc._addEventListener(this._domInputControl, "keydown", function (e) {
            // ignore tab key
            if (e.keyCode === cc.KEY.tab) {
                e.stopPropagation();
                e.preventDefault();
            } else if (e.keyCode === cc.KEY.enter) {
                selfPointer.dispatchInsertText("\n", 1);
                e.stopPropagation();
                e.preventDefault();
            }
        }, false);

        if (/msie/i.test(navigator.userAgent)) {
            cc._addEventListener(this._domInputControl, "keyup", function (e) {
                if (e.keyCode === cc.KEY.backspace) {
                    selfPointer._processDomInputString(selfPointer._domInputControl.value);
                }
            }, false);
        }

        cc._addEventListener(window, 'mousedown', function (event) {
            var tx = event.pageX || 0;
            var ty = event.pageY || 0;

            selfPointer._lastClickPosition.x = tx;
            selfPointer._lastClickPosition.y = ty;
        }, false);
    },

    _processDomInputString:function (text) {
        var i, startPos;
        var len = this._currentInputString.length < text.length ? this._currentInputString.length : text.length;
        for (startPos = 0; startPos < len; startPos++) {
            if (text[startPos] !== this._currentInputString[startPos])
                break;
        }
        var delTimes = this._currentInputString.length - startPos;
        var insTimes = text.length - startPos;
        for (i = 0; i < delTimes; i++)
            this.dispatchDeleteBackward();

        for (i = 0; i < insTimes; i++)
            this.dispatchInsertText(text[startPos + i], 1);

        this._currentInputString = text;
    },

    /**
     * Dispatch the input text from ime
     * @param {String} text
     * @param {Number} len
     */
    dispatchInsertText:function (text, len) {
        if (!this.impl || !text || len <= 0)
            return;

        // there is no delegate attach with ime
        if (!this.impl._delegateWithIme)
            return;

        this.impl._delegateWithIme.insertText(text, len);
    },

    /**
     * Dispatch the delete backward operation
     */
    dispatchDeleteBackward:function () {
        if (!this.impl) {
            return;
        }

        // there is no delegate attach with ime
        if (!this.impl._delegateWithIme)
            return;

        this.impl._delegateWithIme.deleteBackward();
    },

    /**
     * Get the content text, which current CCIMEDelegate which attached with IME has.
     * @return {String}
     */
    getContentText:function () {
        if (this.impl && this.impl._delegateWithIme) {
            var pszContentText = this.impl._delegateWithIme.getContentText();
            return (pszContentText) ? pszContentText : "";
        }
        return "";
    },

    /**
     * Dispatch keyboard notification
     * @param {cc.IMEKeyboardNotificationInfo} info
     */
    dispatchKeyboardWillShow:function (info) {
        if (this.impl) {
            for (var i = 0; i < this.impl._delegateList.length; i++) {
                var delegate = this.impl._delegateList[i];
                if (delegate) {
                    delegate.keyboardWillShow(info);
                }
            }
        }
    },

    /**
     * Dispatch keyboard notification
     * @param {cc.IMEKeyboardNotificationInfo} info
     */
    dispatchKeyboardDidShow:function (info) {
        if (this.impl) {
            for (var i = 0; i < this.impl._delegateList.length; i++) {
                var delegate = this.impl._delegateList[i];
                if (delegate)
                    delegate.keyboardDidShow(info);
            }
        }
    },

    /**
     * Dispatch keyboard notification
     * @param {cc.IMEKeyboardNotificationInfo} info
     */
    dispatchKeyboardWillHide:function (info) {
        if (this.impl) {
            for (var i = 0; i < this.impl._delegateList.length; i++) {
                var delegate = this.impl._delegateList[i];
                if (delegate) {
                    delegate.keyboardWillHide(info);
                }
            }
        }
    },

    /**
     * Dispatch keyboard notification
     * @param {cc.IMEKeyboardNotificationInfo} info
     */
    dispatchKeyboardDidHide:function (info) {
        if (this.impl) {
            for (var i = 0; i < this.impl._delegateList.length; i++) {
                var delegate = this.impl._delegateList[i];
                if (delegate) {
                    delegate.keyboardDidHide(info);
                }
            }
        }
    },

    /**
     * Add delegate to concern ime msg
     * @param {cc.IMEDelegate} delegate
     * @example
     * //example
     * cc.imeDispatcher.addDelegate(this);
     */
    addDelegate:function (delegate) {
        if (!delegate || !this.impl)
            return;

        if (this.impl._delegateList.indexOf(delegate) > -1) {
            // delegate already in list
            return;
        }
        this.impl._delegateList.splice(0, 0, delegate);
    },

    /**
     * Attach the pDeleate with ime.
     * @param {cc.IMEDelegate} delegate
     * @return {Boolean} If the old delegate can detattach with ime and the new delegate can attach with ime, return true, otherwise return false.
     * @example
     * //example
     * var ret = cc.imeDispatcher.attachDelegateWithIME(this);
     */
    attachDelegateWithIME:function (delegate) {
        if (!this.impl || !delegate)
            return false;

        // if delegate is not in delegate list, return
        if (this.impl._delegateList.indexOf(delegate) === -1)
            return false;

        if (this.impl._delegateWithIme) {
            // if old delegate canDetachWithIME return false
            // or delegate canAttachWithIME return false,
            // do nothing.
            if (!this.impl._delegateWithIme.canDetachWithIME()
                || !delegate.canAttachWithIME())
                return false;

            // detach first
            var pOldDelegate = this.impl._delegateWithIme;
            this.impl._delegateWithIme = null;
            pOldDelegate.didDetachWithIME();

            this._focusDomInput(delegate);
            return true;
        }

        // havn't delegate attached with IME yet
        if (!delegate.canAttachWithIME())
            return false;

        this._focusDomInput(delegate);
        return true;
    },

    _focusDomInput:function (delegate) {
        if(cc.sys.isMobile){
            this.impl._delegateWithIme = delegate;
            delegate.didAttachWithIME();
            //prompt
            this._currentInputString = delegate.string || "";

            var tipMessage = delegate.getTipMessage ? delegate.getTipMessage() : "please enter your word:";
            var userInput = prompt(tipMessage, this._currentInputString);
            if(userInput != null)
                this._processDomInputString(userInput);
            this.dispatchInsertText("\n", 1);
        }else{
            this.impl._delegateWithIme = delegate;
            this._currentInputString = delegate.string || "";
            delegate.didAttachWithIME();
            this._domInputControl.focus();
            this._domInputControl.value = this._currentInputString;
            this._domInputControlTranslate();
        }
    },

    _domInputControlTranslate:function () {
        if (/msie/i.test(navigator.userAgent)) {
            this._domInputControl.style.left = this._lastClickPosition.x + "px";
            this._domInputControl.style.top = this._lastClickPosition.y + "px";
        } else {
            this._domInputControl.translates(this._lastClickPosition.x, this._lastClickPosition.y);
        }
    },

    /**
     * Detach the pDeleate with ime.
     * @param {cc.IMEDelegate} delegate
     * @return {Boolean} If the old delegate can detattach with ime and the new delegate can attach with ime, return true, otherwise return false.
     * @example
     * //example
     * var ret = cc.imeDispatcher.detachDelegateWithIME(this);
     */
    detachDelegateWithIME:function (delegate) {
        if (!this.impl || !delegate)
            return false;

        // if delegate is not the current delegate attached with ime, return
        if (this.impl._delegateWithIme !== delegate)
            return false;

        if (!delegate.canDetachWithIME())
            return false;

        this.impl._delegateWithIme = null;
        delegate.didDetachWithIME();
        cc._canvas.focus();
        return true;
    },

    /**
     * Remove the delegate from the delegates who concern ime msg
     * @param {cc.IMEDelegate} delegate
     * @example
     * //example
     * cc.imeDispatcher.removeDelegate(this);
     */
    removeDelegate:function (delegate) {
        if (!this.impl || !delegate)
            return;

        // if delegate is not in delegate list, return
        if (this.impl._delegateList.indexOf(delegate) === -1)
            return;

        if (this.impl._delegateWithIme) {
            if (delegate === this.impl._delegateWithIme) {
                this.impl._delegateWithIme = null;
            }
        }
        cc.arrayRemoveObject(this.impl._delegateList, delegate);
    },

    /**
     * Process keydown's keycode
     * @param {Number} keyCode
     * @example
     * //example
     * document.addEventListener("keydown", function (e) {
     *      cc.imeDispatcher.processKeycode(e.keyCode);
     * });
     */
    processKeycode:function (keyCode) {
        if (keyCode < 32) {
            if (keyCode === cc.KEY.backspace) {
                this.dispatchDeleteBackward();
            } else if (keyCode === cc.KEY.enter) {
                this.dispatchInsertText("\n", 1);
            } else if (keyCode === cc.KEY.tab) {
                //tab input
            } else if (keyCode === cc.KEY.escape) {
                //ESC input
            }
        } else if (keyCode < 255) {
            this.dispatchInsertText(String.fromCharCode(keyCode), 1);
        } else {
            //
        }
    }
});

/**
 * Create the cc.IMEDispatcher.Imp Object. <br />
 * This is the inner class...
 * @class
 * @extends cc.Class
 * @name cc.IMEDispatcher.Impl
 */
cc.IMEDispatcher.Impl = cc.Class.extend(/** @lends cc.IMEDispatcher.Impl# */{
    _delegateWithIme:null,
    _delegateList:null,
    /**
     * Constructor function, override it to extend the construction behavior, remember to call "this._super()" in the extended "ctor" function.
     */
    ctor:function () {
        this._delegateList = [];
    },
    /**
     * Find delegate
     * @param {cc.IMEDelegate} delegate
     * @return {Number|Null}
     */
    findDelegate:function (delegate) {
        for (var i = 0; i < this._delegateList.length; i++) {
            if (this._delegateList[i] === delegate)
                return i;
        }
        return null;
    }
});

// Initialize imeDispatcher singleton
cc.imeDispatcher = new cc.IMEDispatcher();

document.body ?
    cc.imeDispatcher.init() :
    cc._addEventListener(window, 'load', function () {
        cc.imeDispatcher.init();
    }, false);