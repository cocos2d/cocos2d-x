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

//Action frame type
/**
 * The flag move action type of Cocostudio frame.
 * @constant
 * @type {number}
 */
ccs.FRAME_TYPE_MOVE = 0;
/**
 * The flag scale action type of Cocostudio frame.
 * @constant
 * @type {number}
 */
ccs.FRAME_TYPE_SCALE = 1;
/**
 * The flag rotate action type of Cocostudio frame.
 * @constant
 * @type {number}
 */
ccs.FRAME_TYPE_ROTATE = 2;
/**
 * The flag tint action type of Cocostudio frame.
 * @constant
 * @type {number}
 */
ccs.FRAME_TYPE_TINT = 3;
/**
 * The flag fade action type of Cocostudio frame.
 * @constant
 * @type {number}
 */
ccs.FRAME_TYPE_FADE = 4;
/**
 * The max flag of Cocostudio frame.
 * @constant
 * @type {number}
 */
ccs.FRAME_TYPE_MAX = 5;

/**
 * The ease type of Cocostudio frame.
 * @constant
 * @type {Object}
 */
ccs.FrameEaseType = {
    Custom : -1,

    Linear : 0,

    Sine_EaseIn : 1,
    Sine_EaseOut : 2,
    Sine_EaseInOut : 3,

    Quad_EaseIn : 4,
    Quad_EaseOut : 5,
    Quad_EaseInOut : 6,

    Cubic_EaseIn : 7,
    Cubic_EaseOut : 8,
    Cubic_EaseInOut : 9,

    Quart_EaseIn : 10,
    Quart_EaseOut : 11,
    Quart_EaseInOut : 12,

    Quint_EaseIn : 13,
    Quint_EaseOut : 14,
    Quint_EaseInOut : 15,

    Expo_EaseIn : 16,
    Expo_EaseOut : 17,
    Expo_EaseInOut : 18,

    Circ_EaseIn : 19,
    Circ_EaseOut : 20,
    Circ_EaseInOut : 21,

    Elastic_EaseIn : 22,
    Elastic_EaseOut : 23,
    Elastic_EaseInOut : 24,

    Back_EaseIn : 25,
    Back_EaseOut : 26,
    Back_EaseInOut : 27,

    Bounce_EaseIn : 28,
    Bounce_EaseOut : 29,
    Bounce_EaseInOut : 30,

    TWEEN_EASING_MAX: 1000
};


/**
 * The action frame of Cocostudio. It's the base class of ccs.ActionMoveFrame, ccs.ActionScaleFrame etc.
 * @class
 * @extends ccs.Class
 *
 * @property {Number}               frameType               - frame type of ccs.ActionFrame
 * @property {Number}               easingType              - easing type of ccs.ActionFrame
 * @property {Number}               frameIndex              - frame index of ccs.ActionFrame
 * @property {Number}               time                    - time of ccs.ActionFrame
 */
ccs.ActionFrame = ccs.Class.extend(/** @lends ccs.ActionFrame# */{
    frameType: 0,
    easingType: 0,
    frameIndex: 0,
    _Parameter: null,
    time: 0,

    /**
     * The constructor of cc.ActionFrame.
     */
    ctor: function () {
        this.frameType = 0;
        this.easingType = ccs.FrameEaseType.Linear;
        this.frameIndex = 0;
        this.time = 0;
    },

    /**
     * Returns the action of ActionFrame. its subClass need override it.
     * @param {number} duration the duration time of ActionFrame
     * @param {ccs.ActionFrame} srcFrame source frame.
     * @returns {null}
     */
    getAction: function (duration, srcFrame) {
        cc.log("Need a definition of <getAction> for ActionFrame");
        return null;
    },

    _getEasingAction : function (action) {
        if (action === null) {
            console.error("Action cannot be null!");
            return null;
        }

        var resultAction;
        switch (this.easingType) {
            case ccs.FrameEaseType.Custom:
                break;
            case ccs.FrameEaseType.Linear:
                resultAction = action;
                break;
            case ccs.FrameEaseType.Sine_EaseIn:
                resultAction = action.easing(cc.easeSineIn());
                break;
            case ccs.FrameEaseType.Sine_EaseOut:
                resultAction = action.easing(cc.easeSineOut());
                break;
            case ccs.FrameEaseType.Sine_EaseInOut:
                resultAction = action.easing(cc.easeSineInOut());
                break;
            case ccs.FrameEaseType.Quad_EaseIn:
                resultAction = action.easing(cc.easeQuadraticActionIn());
                break;
            case ccs.FrameEaseType.Quad_EaseOut:
                resultAction = action.easing(cc.easeQuadraticActionOut());
                break;
            case ccs.FrameEaseType.Quad_EaseInOut:
                resultAction = action.easing(cc.easeQuadraticActionInOut());
                break;
            case ccs.FrameEaseType.Cubic_EaseIn:
                resultAction = action.easing(cc.easeCubicActionIn());
                break;
            case ccs.FrameEaseType.Cubic_EaseOut:
                resultAction = action.easing(cc.easeCubicActionOut());
                break;
            case ccs.FrameEaseType.Cubic_EaseInOut:
                resultAction = action.easing(cc.easeCubicActionInOut());
                break;
            case ccs.FrameEaseType.Quart_EaseIn:
                resultAction = action.easing(cc.easeQuarticActionIn());
                break;
            case ccs.FrameEaseType.Quart_EaseOut:
                resultAction = action.easing(cc.easeQuarticActionOut());
                break;
            case ccs.FrameEaseType.Quart_EaseInOut:
                resultAction = action.easing(cc.easeQuarticActionInOut());
                break;
            case ccs.FrameEaseType.Quint_EaseIn:
                resultAction = action.easing(cc.easeQuinticActionIn());
                break;
            case ccs.FrameEaseType.Quint_EaseOut:
                resultAction = action.easing(cc.easeQuinticActionOut());
                break;
            case ccs.FrameEaseType.Quint_EaseInOut:
                resultAction = action.easing(cc.easeQuinticActionInOut());
                break;
            case ccs.FrameEaseType.Expo_EaseIn:
                resultAction = action.easing(cc.easeExponentialIn());
                break;
            case ccs.FrameEaseType.Expo_EaseOut:
                resultAction = action.easing(cc.easeExponentialOut());
                break;
            case ccs.FrameEaseType.Expo_EaseInOut:
                resultAction = action.easing(cc.easeExponentialInOut());
                break;
            case ccs.FrameEaseType.Circ_EaseIn:
                resultAction = action.easing(cc.easeCircleActionIn());
                break;
            case ccs.FrameEaseType.Circ_EaseOut:
                resultAction = action.easing(cc.easeCircleActionOut());
                break;
            case ccs.FrameEaseType.Circ_EaseInOut:
                resultAction = action.easing(cc.easeCircleActionInOut());
                break;
            case ccs.FrameEaseType.Elastic_EaseIn:
                resultAction = action.easing(cc.easeElasticIn());
                break;
            case ccs.FrameEaseType.Elastic_EaseOut:
                resultAction = action.easing(cc.easeElasticOut());
                break;
            case ccs.FrameEaseType.Elastic_EaseInOut:
                resultAction = action.easing(cc.easeElasticInOut());
                break;
            case ccs.FrameEaseType.Back_EaseIn:
                resultAction = action.easing(cc.easeBackIn());
                break;
            case ccs.FrameEaseType.Back_EaseOut:
                resultAction = action.easing(cc.easeBackOut());
                break;
            case ccs.FrameEaseType.Back_EaseInOut:
                resultAction = action.easing(cc.easeBackInOut());
                break;
            case ccs.FrameEaseType.Bounce_EaseIn:
                resultAction = action.easing(cc.easeBounceIn());
                break;
            case ccs.FrameEaseType.Bounce_EaseOut:
                resultAction = action.easing(cc.easeBounceOut());
                break;
            case ccs.FrameEaseType.Bounce_EaseInOut:
                resultAction = action.easing(cc.easeBounceInOut());
                break;
        }

        return resultAction;
    },

    /**
     * Sets the easing parameter to action frame.
     * @param {Array} parameter
     */
    setEasingParameter: function(parameter){
        this._Parameter = [];
        for(var i=0;i<parameter.length;i++)
            this._Parameter.push(parameter[i]);
    },

    /**
     * Sets the easing type to ccs.ActionFrame
     * @param {Number} easingType
     */
    setEasingType: function(easingType){
        this.easingType = easingType;
    }
});

/**
 * The Cocostudio's move action frame.
 * @class
 * @extends ccs.ActionFrame
 */
ccs.ActionMoveFrame = ccs.ActionFrame.extend(/** @lends ccs.ActionMoveFrame# */{
    _position: null,
    /**
     * Construction of ccs.ActionMoveFrame
     */
    ctor: function () {
        ccs.ActionFrame.prototype.ctor.call(this);
        this._position = cc.p(0, 0);
        this.frameType = ccs.FRAME_TYPE_MOVE;
    },

    /**
     * Changes the move action position.
     * @param {cc.Point|Number} pos
     * @param {Number} y
     */
    setPosition: function (pos, y) {
        if (y === undefined) {
            this._position.x = pos.x;
            this._position.y = pos.y;
        } else {
            this._position.x = pos;
            this._position.y = y;
        }
    },

    /**
     * Returns the move action position.
     * @returns {cc.Point}
     */
    getPosition: function () {
        return this._position;
    },

    /**
     * Returns the CCAction of ActionFrame.
     * @param {number} duration
     * @returns {cc.MoveTo}
     */
    getAction: function (duration) {
        return this._getEasingAction(cc.moveTo(duration, this._position));
    }
});

/**
 * The Cocostudio's scale action frame
 * @class
 * @extends ccs.ActionFrame
 */
ccs.ActionScaleFrame = ccs.ActionFrame.extend(/** @lends ccs.ActionScaleFrame# */{
    _scaleX: 1,
    _scaleY: 1,
    /**
     * Construction of ccs.ActionScaleFrame
     */
    ctor: function () {
        ccs.ActionFrame.prototype.ctor.call(this);
        this._scaleX = 1;
        this._scaleY = 1;
        this.frameType = ccs.FRAME_TYPE_SCALE;
    },

    /**
     * Changes the scale action scaleX.
     * @param {number} scaleX
     */
    setScaleX: function (scaleX) {
        this._scaleX = scaleX;
    },

    /**
     * Returns the scale action scaleX.
     * @returns {number}
     */
    getScaleX: function () {
        return this._scaleX;
    },

    /**
     * Changes the scale action scaleY.
     * @param {number} scaleY
     */
    setScaleY: function (scaleY) {
        this._scaleY = scaleY;
    },

    /**
     * Returns the scale action scaleY.
     * @returns {number}
     */
    getScaleY: function () {
        return this._scaleY;
    },

    /**
     * Returns the action of ActionFrame.
     * @param {number} duration
     * @returns {cc.ScaleTo}
     */
    getAction: function (duration) {
        return this._getEasingAction(cc.scaleTo(duration, this._scaleX, this._scaleY));
    }
});

/**
 * The Cocostudio's rotation action frame.
 * @class
 * @extends ccs.ActionFrame
 */
ccs.ActionRotationFrame = ccs.ActionFrame.extend(/** @lends ccs.ActionRotationFrame# */{
    _rotation: 0,
    /**
     * Construction of ccs.ActionRotationFrame
     */
    ctor: function () {
        ccs.ActionFrame.prototype.ctor.call(this);
        this._rotation = 0;
        this.frameType = ccs.FRAME_TYPE_ROTATE;
    },

    /**
     * Changes rotate action rotation.
     * @param {number} rotation
     */
    setRotation: function (rotation) {
        this._rotation = rotation;
    },

    /**
     * Returns the rotate action rotation.
     * @returns {number}
     */
    getRotation: function () {
        return this._rotation;
    },

    /**
     * Returns the CCAction of ActionFrame.
     * @param {number} duration
     * @param {cc.ActionFrame} [srcFrame]
     * @returns {cc.RotateTo}
     */
    getAction: function (duration, srcFrame) {
        if(srcFrame === undefined)
            return this._getEasingAction(cc.rotateTo(duration, this._rotation));
        else {
            if (!(srcFrame instanceof cc.ActionRotationFrame))
                return this.getAction(duration);
            else{
                var diffRotation = this._rotation - srcFrame._rotation;
                return this._getEasingAction(cc.rotateBy(duration,diffRotation));
            }
        }
    }
});

/**
 * The Cocostudio's fade action frame.
 * @class
 * @extends ccs.ActionFrame
 */
ccs.ActionFadeFrame = ccs.ActionFrame.extend(/** @lends ccs.ActionFadeFrame# */{
    _opacity: 255,
    /**
     * Construction of ccs.ActionFadeFrame
     */
    ctor: function () {
        ccs.ActionFrame.prototype.ctor.call(this);
        this._opacity = 255;
        this.frameType = ccs.FRAME_TYPE_FADE;
    },

    /**
     * Changes the fade action opacity.
     * @param {number} opacity
     */
    setOpacity: function (opacity) {
        this._opacity = opacity;
    },

    /**
     * Returns the fade action opacity.
     * @returns {number}
     */
    getOpacity: function () {
        return this._opacity;
    },

    /**
     * Returns a fade action with easing.
     * @param {Number} duration
     * @returns {cc.FadeTo}
     */
    getAction: function (duration) {
        return this._getEasingAction(cc.fadeTo(duration, this._opacity));
    }
});

/**
 * The Cocostudio's tint action frame.
 * @class
 * @extends ccs.ActionFrame
 */
ccs.ActionTintFrame = ccs.ActionFrame.extend(/** @lends ccs.ActionTintFrame# */{
    _color: null,
    /**
     * Construction of ccs.ActionTintFrame
     */
    ctor: function () {
        ccs.ActionFrame.prototype.ctor.call(this);
        this._color = cc.color(255, 255, 255, 255);
        this.frameType = ccs.FRAME_TYPE_TINT;
    },

    /**
     * Changes the tint action color.
     * @param {cc.Color} color
     */
    setColor: function (color) {
        var locColor = this._color;
        locColor.r = color.r;
        locColor.g = color.g;
        locColor.b = color.b;
    },

    /**
     * Returns the color of tint action.
     * @returns {cc.Color}
     */
    getColor: function () {
        var locColor = this._color;
        return cc.color(locColor.r, locColor.g, locColor.b, locColor.a);
    },

    /**
     * Returns a tint action with easing.
     * @param duration
     * @returns {cc.TintTo}
     */
    getAction: function (duration) {
        return this._getEasingAction(cc.tintTo(duration, this._color.r, this._color.g, this._color.b));
    }
});