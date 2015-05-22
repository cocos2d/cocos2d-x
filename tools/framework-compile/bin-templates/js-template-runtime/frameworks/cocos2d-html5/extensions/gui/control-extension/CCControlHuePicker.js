/**
 *
 * Copyright (c) 2008-2010 Ricardo Quesada
 * Copyright (c) 2011-2012 cocos2d-x.org
 * Copyright (c) 2013-2014 Chukong Technologies Inc.
 *
 * Copyright 2012 Stewart Hamilton-Arrandale.
 * http://creativewax.co.uk
 *
 * Modified by Yannick Loriot.
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
 *
 * converted to Javascript / cocos2d-x by Angus C
 */

/**
 * ControlHuePicker: HUE picker ui component.
 * @class
 * @extends cc.Control
 *
 * @property {Number}       hue         - The hue value
 * @property {Number}       huePercent  - The hue value in percentage
 * @property {cc.Sprite}    background  - <@readonly> The background sprite
 * @property {cc.Sprite}    slider      - <@readonly> The slider sprite
 * @property {cc.Point}     startPos    - <@readonly> The start position of the picker
 */
cc.ControlHuePicker = cc.Control.extend(/** @lends cc.ControlHuePicker# */{
    _hue:0,
    _huePercentage:0,
    _background:null,
    _slider:null,
    _startPos:null,
    _className:"ControlHuePicker",

    /**
     * The constructor of cc.ControlHuePicker
     * @param {cc.Node} target
     * @param {cc.Point} pos position
     */
    ctor:function(target, pos) {
        cc.Control.prototype.ctor.call(this);
        pos && this.initWithTargetAndPos(target, pos);
    },

    //maunally put in the setters
    getHue:function () {
        return this._hue;
    },
    setHue:function (hueValue) {
        this._hue = hueValue;
        this.setHuePercentage(this._hue / 360.0);
    },

    getHuePercentage:function () {
        return this._huePercentage;
    },
    setHuePercentage:function (hueValueInPercent) {
        this._huePercentage = hueValueInPercent;
        this._hue = this._huePercentage * 360.0;

        // Clamp the position of the icon within the circle
        var backgroundBox = this._background.getBoundingBox();

        // Get the center point of the background image
        var centerX = this._startPos.x + backgroundBox.width * 0.5;
        var centerY = this._startPos.y + backgroundBox.height * 0.5;

        // Work out the limit to the distance of the picker when moving around the hue bar
        var limit = backgroundBox.width * 0.5 - 15.0;

        // Update angle
        var angleDeg = this._huePercentage * 360.0 - 180.0;
        var angle = cc.degreesToRadians(angleDeg);

        // Set new position of the slider
        var x = centerX + limit * Math.cos(angle);
        var y = centerY + limit * Math.sin(angle);
        this._slider.setPosition(x, y);
    },

    setEnabled:function (enabled) {
        cc.Control.prototype.setEnabled.call(this, enabled);
        if (this._slider) {
            this._slider.setOpacity(enabled ? 255 : 128);
        }
    },

    getBackground:function () {
        return this._background;
    },
    getSlider:function () {
        return this._slider;
    },
    getStartPos:function () {
        return this._startPos;
    },

    initWithTargetAndPos:function (target, pos) {
        if (cc.Control.prototype.init.call(this)) {
            // Add background and slider sprites
            this._background = cc.ControlUtils.addSpriteToTargetWithPosAndAnchor("huePickerBackground.png", target, pos, cc.p(0.0, 0.0));
            this._slider = cc.ControlUtils.addSpriteToTargetWithPosAndAnchor("colourPicker.png", target, pos, cc.p(0.5, 0.5));

            this._slider.setPosition(pos.x, pos.y + this._background.getBoundingBox().height * 0.5);
            this._startPos = pos;

            // Sets the default value
            this._hue = 0.0;
            this._huePercentage = 0.0;
            return true;
        } else
            return false;
    },

    _updateSliderPosition:function (location) {
        // Clamp the position of the icon within the circle
        var backgroundBox = this._background.getBoundingBox();

        // Get the center point of the background image
        var centerX = this._startPos.x + backgroundBox.width * 0.5;
        var centerY = this._startPos.y + backgroundBox.height * 0.5;

        // Work out the distance difference between the location and center
        var dx = location.x - centerX;
        var dy = location.y - centerY;

        // Update angle by using the direction of the location
        var angle = Math.atan2(dy, dx);
        var angleDeg = cc.radiansToDegrees(angle) + 180.0;

        // use the position / slider width to determin the percentage the dragger is at
        this.setHue(angleDeg);

        // send CCControl callback
        this.sendActionsForControlEvents(cc.CONTROL_EVENT_VALUECHANGED);
    },
    _checkSliderPosition:function (location) {
        // compute the distance between the current location and the center
        var distance = Math.sqrt(Math.pow(location.x + 10, 2) + Math.pow(location.y, 2));

        // check that the touch location is within the circle
        if (80 > distance && distance > 59)        {
            this._updateSliderPosition(location);
            return true;
        }
        return false;
    },

    onTouchBegan:function (touch, event) {
        if (!this.isEnabled() || !this.isVisible())        {
            return false;
        }
        var touchLocation = this.getTouchLocation(touch);

        // Check the touch position on the slider
        return this._checkSliderPosition(touchLocation);
    },
    onTouchMoved:function (touch, event) {
        // Get the touch location
        var touchLocation = this.getTouchLocation(touch);

        //small modification: this allows changing of the colour, even if the touch leaves the bounding area
        //this._updateSliderPosition(touchLocation);
        //this.sendActionsForControlEvents(cc.CONTROL_EVENT_VALUECHANGED);
        // Check the touch position on the slider
        this._checkSliderPosition(touchLocation);
    }
});

var _p = cc.ControlHuePicker.prototype;

// Extended properties
/** @expose */
_p.hue;
cc.defineGetterSetter(_p, "hue", _p.getHue, _p.setHue);
/** @expose */
_p.huePercent;
cc.defineGetterSetter(_p, "huePercent", _p.getHuePercentage, _p.setHuePercentage);
/** @expose */
_p.background;
cc.defineGetterSetter(_p, "background", _p.getBackground);
/** @expose */
_p.slider;
cc.defineGetterSetter(_p, "slider", _p.getSlider);
/** @expose */
_p.startPos;
cc.defineGetterSetter(_p, "startPos", _p.getStartPos);

_p = null;

/**
 * @deprecated
 * @param target
 * @param pos
 * @returns {ControlHuePicker}
 */
cc.ControlHuePicker.create = function (target, pos) {
    return new cc.ControlHuePicker(target, pos);
};