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
 * Base class of all kinds of events.
 * @class
 * @extends cc.Class
 */
cc.Event = cc.Class.extend(/** @lends cc.Event# */{
    _type: 0,                                   //  Event type
    _isStopped: false,                         //< whether the event has been stopped.
    _currentTarget: null,                       //< Current target

    _setCurrentTarget: function (target) {
        this._currentTarget = target;
    },

    ctor: function (type) {
        this._type = type;
    },

    /**
     * Gets the event type
     * @function
     * @returns {Number}
     */
    getType: function () {
        return this._type;
    },

    /**
     * Stops propagation for current event
     * @function
     */
    stopPropagation: function () {
        this._isStopped = true;
    },

    /**
     * Checks whether the event has been stopped
     * @function
     * @returns {boolean}
     */
    isStopped: function () {
        return this._isStopped;
    },

    /**
     * <p>
     *     Gets current target of the event                                                            <br/>
     *     note: It only be available when the event listener is associated with node.                <br/>
     *          It returns 0 when the listener is associated with fixed priority.
     * </p>
     * @function
     * @returns {cc.Node}  The target with which the event associates.
     */
    getCurrentTarget: function () {
        return this._currentTarget;
    }
});

//event type
/**
 * The type code of Touch event.
 * @constant
 * @type {number}
 */
cc.Event.TOUCH = 0;
/**
 * The type code of Keyboard event.
 * @constant
 * @type {number}
 */
cc.Event.KEYBOARD = 1;
/**
 * The type code of Acceleration event.
 * @constant
 * @type {number}
 */
cc.Event.ACCELERATION = 2;
/**
 * The type code of Mouse event.
 * @constant
 * @type {number}
 */
cc.Event.MOUSE = 3;
/**
 * The type code of UI focus event.
 * @constant
 * @type {number}
 */
cc.Event.FOCUS = 4;
/**
 * The type code of Custom event.
 * @constant
 * @type {number}
 */
cc.Event.CUSTOM = 6;

/**
 * The Custom event
 * @class
 * @extends cc.Event
 */
cc.EventCustom = cc.Event.extend(/** @lends cc.EventCustom# */{
    _eventName: null,
    _userData: null,                                 // User data

    ctor: function (eventName) {
        cc.Event.prototype.ctor.call(this, cc.Event.CUSTOM);
        this._eventName = eventName;
    },

    /**
     * Sets user data
     * @param {*} data
     */
    setUserData: function (data) {
        this._userData = data;
    },

    /**
     * Gets user data
     * @returns {*}
     */
    getUserData: function () {
        return this._userData;
    },

    /**
     * Gets event name
     * @returns {String}
     */
    getEventName: function () {
        return this._eventName;
    }
});

/**
 * The mouse event
 * @class
 * @extends cc.Event
 */
cc.EventMouse = cc.Event.extend(/** @lends cc.EventMouse# */{
    _eventType: 0,
    _button: 0,
    _x: 0,
    _y: 0,
    _prevX: 0,
    _prevY: 0,
    _scrollX: 0,
    _scrollY: 0,

    ctor: function (eventType) {
        cc.Event.prototype.ctor.call(this, cc.Event.MOUSE);
        this._eventType = eventType;
    },

    /**
     * Sets scroll data
     * @param {number} scrollX
     * @param {number} scrollY
     */
    setScrollData: function (scrollX, scrollY) {
        this._scrollX = scrollX;
        this._scrollY = scrollY;
    },

    /**
     * Returns the x axis scroll value
     * @returns {number}
     */
    getScrollX: function () {
        return this._scrollX;
    },

    /**
     * Returns the y axis scroll value
     * @returns {number}
     */
    getScrollY: function () {
        return this._scrollY;
    },

    /**
     * Sets cursor location
     * @param {number} x
     * @param {number} y
     */
    setLocation: function (x, y) {
        this._x = x;
        this._y = y;
    },

	/**
	 * Returns cursor location
	 * @return {cc.Point} location
	 */
    getLocation: function () {
        return {x: this._x, y: this._y};
    },

	/**
	 * Returns the current cursor location in screen coordinates
	 * @return {cc.Point}
	 */
	getLocationInView: function() {
		return {x: this._x, y: cc.view._designResolutionSize.height - this._y};
	},

    _setPrevCursor: function (x, y) {
        this._prevX = x;
        this._prevY = y;
    },

    /**
     * Returns the delta distance from the previous location to current location
     * @return {cc.Point}
     */
    getDelta: function () {
        return {x: this._x - this._prevX, y: this._y - this._prevY};
    },

    /**
     * Returns the X axis delta distance from the previous location to current location
     * @return {Number}
     */
    getDeltaX: function () {
        return this._x - this._prevX;
    },

    /**
     * Returns the Y axis delta distance from the previous location to current location
     * @return {Number}
     */
    getDeltaY: function () {
        return this._y - this._prevY;
    },

    /**
     * Sets mouse button
     * @param {number} button
     */
    setButton: function (button) {
        this._button = button;
    },

    /**
     * Returns mouse button
     * @returns {number}
     */
    getButton: function () {
        return this._button;
    },

    /**
     * Returns location X axis data
     * @returns {number}
     */
    getLocationX: function () {
        return this._x;
    },

    /**
     * Returns location Y axis data
     * @returns {number}
     */
    getLocationY: function () {
        return this._y;
    }
});

//Different types of MouseEvent
/**
 * The none event code of  mouse event.
 * @constant
 * @type {number}
 */
cc.EventMouse.NONE = 0;
/**
 * The event type code of mouse down event.
 * @constant
 * @type {number}
 */
cc.EventMouse.DOWN = 1;
/**
 * The event type code of mouse up event.
 * @constant
 * @type {number}
 */
cc.EventMouse.UP = 2;
/**
 * The event type code of mouse move event.
 * @constant
 * @type {number}
 */
cc.EventMouse.MOVE = 3;
/**
 * The event type code of mouse scroll event.
 * @constant
 * @type {number}
 */
cc.EventMouse.SCROLL = 4;

/**
 * The tag of Mouse left button
 * @constant
 * @type {Number}
 */
cc.EventMouse.BUTTON_LEFT = 0;

/**
 * The tag of Mouse right button  (The right button number is 2 on browser)
 * @constant
 * @type {Number}
 */
cc.EventMouse.BUTTON_RIGHT = 2;

/**
 * The tag of Mouse middle button  (The right button number is 1 on browser)
 * @constant
 * @type {Number}
 */
cc.EventMouse.BUTTON_MIDDLE = 1;

/**
 * The tag of Mouse button 4
 * @constant
 * @type {Number}
 */
cc.EventMouse.BUTTON_4 = 3;

/**
 * The tag of Mouse button 5
 * @constant
 * @type {Number}
 */
cc.EventMouse.BUTTON_5 = 4;

/**
 * The tag of Mouse button 6
 * @constant
 * @type {Number}
 */
cc.EventMouse.BUTTON_6 = 5;

/**
 * The tag of Mouse button 7
 * @constant
 * @type {Number}
 */
cc.EventMouse.BUTTON_7 = 6;

/**
 * The tag of Mouse button 8
 * @constant
 * @type {Number}
 */
cc.EventMouse.BUTTON_8 = 7;

/**
 * The touch event
 * @class
 * @extends cc.Event
 */
cc.EventTouch = cc.Event.extend(/** @lends cc.EventTouch# */{
    _eventCode: 0,
    _touches: null,

    ctor: function (arr) {
        cc.Event.prototype.ctor.call(this, cc.Event.TOUCH);
        this._touches = arr || [];
    },

    /**
     * Returns event code
     * @returns {number}
     */
    getEventCode: function () {
        return this._eventCode;
    },

    /**
     * Returns touches of event
     * @returns {Array}
     */
    getTouches: function () {
        return this._touches;
    },

    _setEventCode: function (eventCode) {
        this._eventCode = eventCode;
    },

    _setTouches: function (touches) {
        this._touches = touches;
    }
});

/**
 * The maximum touch numbers
 * @constant
 * @type {Number}
 */
cc.EventTouch.MAX_TOUCHES = 5;

cc.EventTouch.EventCode = {BEGAN: 0, MOVED: 1, ENDED: 2, CANCELLED: 3};

/**
 * Focus change event for UI widget
 * @class
 * @extends cc.Event
 */
cc.EventFocus = cc.Event.extend(/** @lends cc.EventTouch# */{
    _widgetGetFocus: null,
    _widgetLoseFocus: null,
    /**
     * Constructor function.
     * @param {ccui.Widget} widgetLoseFocus
     * @param {ccui.Widget} widgetGetFocus
     */
    ctor: function(widgetLoseFocus, widgetGetFocus){
        cc.Event.prototype.ctor.call(this, cc.Event.FOCUS);
        this._widgetGetFocus = widgetGetFocus;
        this._widgetLoseFocus = widgetLoseFocus;
    }
});