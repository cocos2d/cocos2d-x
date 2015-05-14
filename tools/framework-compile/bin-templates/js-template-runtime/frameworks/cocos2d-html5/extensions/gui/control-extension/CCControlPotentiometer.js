/**
 * Copyright (c) 2008-2010 Ricardo Quesada
 * Copyright (c) 2011-2012 cocos2d-x.org
 * Copyright (c) 2013-2014 Chukong Technologies Inc.
 *
 * http://www.cocos2d-x.org
 *
 * Copyright 2012 Yannick Loriot. All rights reserved.
 * http://yannickloriot.com
 * 
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 * 
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 * 
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 * THE SOFTWARE.
 *
 */

/**
 * CCControlPotentiometer: Potentiometer control for Cocos2D.
 * @class
 * @extends cc.Control
 *
 * @property {Number}           value           - The current value of the potentionmeter
 * @property {Number}           minValue        - The minimum value of the potentionmeter
 * @property {Number}           maxValue        - The maximum value of the potentionmeter
 * @property {cc.ProgressTimer} progressTimer   - The progress timer of the potentionmeter
 * @property {cc.Sprite}        thumbSprite     - The thumb sprite of the potentionmeter
 * @property {cc.Point}         prevLocation    - The previous location of the potentionmeter
 */
cc.ControlPotentiometer = cc.Control.extend(/** @lends cc.ControlPotentiometer# */{
    _thumbSprite:null,
    _progressTimer:null,
    _previousLocation:null,
    /** Contains the receiver’s current value. */
    _value:0,
    /** Contains the minimum value of the receiver.
     * The default value of this property is 0.0. */
    _minimumValue:0,
    /** Contains the maximum value of the receiver.
     * The default value of this property is 1.0. */
    _maximumValue:1,
    _className:"ControlPotentiometer",

    ctor:function (backgroundFile, progressFile, thumbFile) {
        cc.Control.prototype.ctor.call(this);
        if (thumbFile != undefined) {
            // Prepare track for potentiometer
            var backgroundSprite = new cc.Sprite(backgroundFile);

            // Prepare thumb for potentiometer
            var thumbSprite = new cc.Sprite(thumbFile);

            // Prepare progress for potentiometer
            var progressTimer = new cc.ProgressTimer(new cc.Sprite(progressFile));
            this.initWithTrackSprite_ProgressTimer_ThumbSprite(backgroundSprite, progressTimer, thumbSprite);
        }
    },

    /**
     *
     * @param {cc.Sprite} trackSprite
     * @param {cc.ProgressTimer}  progressTimer
     * @param {cc.Sprite}  thumbSprite
     * @return {Boolean}
     */
    initWithTrackSprite_ProgressTimer_ThumbSprite:function (trackSprite, progressTimer, thumbSprite) {
        if (this.init()) {
            this.setProgressTimer(progressTimer);
            this.setThumbSprite(thumbSprite);
            this._thumbSprite.setPosition(progressTimer.getPosition());

            this.addChild(thumbSprite, 2);
            this.addChild(progressTimer, 1);
            this.addChild(trackSprite);

            this.setContentSize(trackSprite.getContentSize());

            // Init default values
            this._minimumValue = 0.0;
            this._maximumValue = 1.0;
            this.setValue(this._minimumValue);
            return true;
        }
        return false;
    },

    setEnabled:function (enabled) {
        this.setEnabled(enabled);
        if (this._thumbSprite !== null) {
            this._thumbSprite.setOpacity((enabled) ? 255 : 128);
        }
    },

    setValue:function (value) {
        // set new value with sentinel
        if (value < this._minimumValue) {
            value = this._minimumValue;
        }

        if (value > this._maximumValue) {
            value = this._maximumValue;
        }

        this._value = value;

        // Update thumb and progress position for new value
        var percent = (value - this._minimumValue) / (this._maximumValue - this._minimumValue);
        this._progressTimer.setPercentage(percent * 100.0);
        this._thumbSprite.setRotation(percent * 360.0);

        this.sendActionsForControlEvents(cc.CONTROL_EVENT_VALUECHANGED);
    },

    getValue:function () {
        return this._value;
    },

    setMinimumValue:function (minimumValue) {
        this._minimumValue = minimumValue;

        if (this._minimumValue >= this._maximumValue) {
            this._maximumValue = this._minimumValue + 1.0;
        }

        this.setValue(this._maximumValue);
    },

    getMinimumValue:function () {
        return this._minimumValue;
    },

    setMaximumValue:function (maximumValue) {
        this._maximumValue = maximumValue;

        if (this._maximumValue <= this._minimumValue) {
            this._minimumValue = this._maximumValue - 1.0;
        }

        this.setValue(this._minimumValue);
    },

    getMaximumValue:function () {
        return this._maximumValue;
    },

    isTouchInside:function (touch) {
        var touchLocation = this.getTouchLocation(touch);

        var distance = this.distanceBetweenPointAndPoint(this._progressTimer.getPosition(), touchLocation);

        return distance < Math.min(this.getContentSize().width / 2, this.getContentSize().height / 2);
    },

    onTouchBegan:function (touch, event) {
        if (!this.isTouchInside(touch) || !this.isEnabled() || !this.isVisible()) {
            return false;
        }

        this._previousLocation = this.getTouchLocation(touch);

        this.potentiometerBegan(this._previousLocation);

        return true;
    },

    onTouchMoved:function (touch, event) {
        var location = this.getTouchLocation(touch);

        this.potentiometerMoved(location);
    },

    onTouchEnded:function (touch, event) {
        this.potentiometerEnded(cc.p(0, 0));
    },

    /**
     * the distance between the point1 and point2
     * @param {cc.Point} point1
     * @param {cc.Point}  point2
     * @return {Number}
     */
    distanceBetweenPointAndPoint:function (point1, point2) {
        var dx = point1.x - point2.x;
        var dy = point1.y - point2.y;
        return Math.sqrt(dx * dx + dy * dy);
    },

    /**
     * the angle in degree between line1 and line2.
     * @param {cc.Point}  beginLineA
     * @param {cc.Point}  endLineA
     * @param {cc.Point}  beginLineB
     * @param {cc.Point}  endLineB
     * @return {Number}
     */
    angleInDegreesBetweenLineFromPoint_toPoint_toLineFromPoint_toPoint:function (beginLineA, endLineA, beginLineB, endLineB) {
        var a = endLineA.x - beginLineA.x;
        var b = endLineA.y - beginLineA.y;
        var c = endLineB.x - beginLineB.x;
        var d = endLineB.y - beginLineB.y;

        var atanA = Math.atan2(a, b);
        var atanB = Math.atan2(c, d);

        // convert radiants to degrees
        return (atanA - atanB) * 180 / Math.PI;
    },

    potentiometerBegan:function (location) {
        this.setSelected(true);
        this.getThumbSprite().setColor(cc.color.GRAY);
    },

    potentiometerMoved:function (location) {
        var angle = this.angleInDegreesBetweenLineFromPoint_toPoint_toLineFromPoint_toPoint(this._progressTimer.getPosition(), location, this._progressTimer.getPosition(), this._previousLocation);

        // fix value, if the 12 o'clock position is between location and previousLocation
        if (angle > 180) {
            angle -= 360;
        }
        else if (angle < -180) {
            angle += 360;
        }

        this.setValue(this._value + angle / 360.0 * (this._maximumValue - this._minimumValue));

        this._previousLocation = location;
    },

    potentiometerEnded:function (location) {
        this.getThumbSprite().setColor(cc.color.WHITE);
        this.setSelected(false);
    },
    setThumbSprite:function (sprite) {
        this._thumbSprite = sprite;
    },
    getThumbSprite:function () {
        return this._thumbSprite;
    },
    setProgressTimer:function (sprite) {
        this._progressTimer = sprite;
    },
    getProgressTimer:function () {
        return this._progressTimer;
    },
    setPreviousLocation:function (point) {
        this._previousLocation = point;
    },
    getPreviousLocation:function () {
        return this._previousLocation;
    }
});

var _p = cc.ControlPotentiometer.prototype;

// Extended properties
/** @expose */
_p.value;
cc.defineGetterSetter(_p, "value", _p.getValue, _p.setValue);
/** @expose */
_p.minValue;
cc.defineGetterSetter(_p, "minValue", _p.getMinimumValue, _p.setMinimumValue);
/** @expose */
_p.maxValue;
cc.defineGetterSetter(_p, "maxValue", _p.getMaximumValue, _p.setMaximumValue);
/** @expose */
_p.progressTimer;
cc.defineGetterSetter(_p, "progressTimer", _p.getProgressTimer, _p.setProgressTimer);
/** @expose */
_p.thumbSprite;
cc.defineGetterSetter(_p, "thumbSprite", _p.getThumbSprite, _p.setThumbSprite);
/** @expose */
_p.prevLocation;
cc.defineGetterSetter(_p, "prevLocation", _p.getPreviousLocation, _p.setPreviousLocation);

_p = null;

/**
 * @deprecated
 * @param backgroundFile
 * @param progressFile
 * @param thumbFile
 * @returns {ControlPotentiometer}
 */
cc.ControlPotentiometer.create = function (backgroundFile, progressFile, thumbFile) {
    return new cc.ControlPotentiometer(backgroundFile, progressFile, thumbFile);
};