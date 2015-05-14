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
 * The acceleration event
 * @class
 * @extends cc.Event
 */
cc.EventAcceleration = cc.Event.extend(/** @lends cc.EventAcceleration# */{
    _acc: null,
    ctor: function (acc) {
        cc.Event.prototype.ctor.call(this, cc.Event.ACCELERATION);
        this._acc = acc;
    }
});

/**
 * The keyboard event
 * @class
 * @extends cc.Event
 */
cc.EventKeyboard = cc.Event.extend(/** @lends cc.EventKeyboard# */{
    _keyCode: 0,
    _isPressed: false,
    ctor: function (keyCode, isPressed) {
        cc.Event.prototype.ctor.call(this, cc.Event.KEYBOARD);
        this._keyCode = keyCode;
        this._isPressed = isPressed;
    }
});


//Acceleration
cc._EventListenerAcceleration = cc.EventListener.extend({
    _onAccelerationEvent: null,

    ctor: function (callback) {
        this._onAccelerationEvent = callback;
        var selfPointer = this;
        var listener = function (event) {
            selfPointer._onAccelerationEvent(event._acc, event);
        };
        cc.EventListener.prototype.ctor.call(this, cc.EventListener.ACCELERATION, cc._EventListenerAcceleration.LISTENER_ID, listener);
    },

    checkAvailable: function () {

        cc.assert(this._onAccelerationEvent, cc._LogInfos._EventListenerAcceleration_checkAvailable);

        return true;
    },

    clone: function () {
        return new cc._EventListenerAcceleration(this._onAccelerationEvent);
    }
});

cc._EventListenerAcceleration.LISTENER_ID = "__cc_acceleration";

cc._EventListenerAcceleration.create = function (callback) {
    return new cc._EventListenerAcceleration(callback);
};


//Keyboard
cc._EventListenerKeyboard = cc.EventListener.extend({
    onKeyPressed: null,
    onKeyReleased: null,

    ctor: function () {
        var selfPointer = this;
        var listener = function (event) {
            if (event._isPressed) {
                if (selfPointer.onKeyPressed)
                    selfPointer.onKeyPressed(event._keyCode, event);
            } else {
                if (selfPointer.onKeyReleased)
                    selfPointer.onKeyReleased(event._keyCode, event);
            }
        };
        cc.EventListener.prototype.ctor.call(this, cc.EventListener.KEYBOARD, cc._EventListenerKeyboard.LISTENER_ID, listener);
    },

    clone: function () {
        var eventListener = new cc._EventListenerKeyboard();
        eventListener.onKeyPressed = this.onKeyPressed;
        eventListener.onKeyReleased = this.onKeyReleased;
        return eventListener;
    },

    checkAvailable: function () {
        if (this.onKeyPressed === null && this.onKeyReleased === null) {
            cc.log(cc._LogInfos._EventListenerKeyboard_checkAvailable);
            return false;
        }
        return true;
    }
});

cc._EventListenerKeyboard.LISTENER_ID = "__cc_keyboard";

cc._EventListenerKeyboard.create = function () {
    return new cc._EventListenerKeyboard();
};