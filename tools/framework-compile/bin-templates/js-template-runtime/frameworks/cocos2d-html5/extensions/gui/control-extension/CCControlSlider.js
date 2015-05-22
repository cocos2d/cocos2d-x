/**
 *
 * Copyright (c) 2008-2010 Ricardo Quesada
 * Copyright (c) 2011-2012 cocos2d-x.org
 * Copyright (c) 2013-2014 Chukong Technologies Inc.
 *
 * Copyright 2011 Yannick Loriot. All rights reserved.
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
 * @ignore
 */
cc.SLIDER_MARGIN_H = 24;
cc.SLIDER_MARGIN_V = 8;

/**
 * ControlSlider: Slider ui component.
 * @class
 * @extends cc.Control
 *
 * @property {Number}       value               - The value of the slider
 * @property {Number}       minValue            - The minimum value of the slider
 * @property {Number}       maxValue            - The maximum value of the slider
 * @property {Number}       minAllowedValue     - The minimum allowed value of the slider
 * @property {Number}       maxAllowedValue     - The maximum allowed value of the slider
 * @property {Number}       thumbSprite         - <@readonly> Brightness value of the picker
 * @property {cc.Sprite}    progressSprite      - <@readonly> The background sprite
 * @property {cc.Sprite}    backgroundSprite    - <@readonly> The overlay sprite
 */
cc.ControlSlider = cc.Control.extend(/** @lends cc.ControlSlider# */{
    _value:0,
    _minimumValue:0,
    _maximumValue:0,
    _minimumAllowedValue:0,
    _maximumAllowedValue:0,

    _thumbSprite:null,
    _progressSprite:null,
    _backgroundSprite:null,
    _className:"ControlSlider",

    ctor:function (bgFile, progressFile, thumbFile) {
        cc.Control.prototype.ctor.call(this);
        if (thumbFile != undefined) {
            // Prepare background for slider
            var bgSprite = new cc.Sprite(bgFile);

            // Prepare progress for slider
            var progressSprite = new cc.Sprite(progressFile);

            // Prepare thumb (menuItem) for slider
            var thumbSprite = new cc.Sprite(thumbFile);

            this.initWithSprites(bgSprite, progressSprite, thumbSprite);
        }
    },

    getValue:function () {
        return this._value;
    },
    setValue:function (value) {
        //clamp between the two bounds
        value = Math.max(value, this._minimumValue);
        value = Math.min(value, this._maximumValue);
        this._value = value;
        this.needsLayout();
        this.sendActionsForControlEvents(cc.CONTROL_EVENT_VALUECHANGED);
    },

    getMinimumValue:function () {
        return this._minimumValue;
    },
    setMinimumValue:function (minimumValue) {
        this._minimumValue = minimumValue;
        this._minimumAllowedValue = minimumValue;
        if (this._minimumValue >= this._maximumValue)
            this._maximumValue = this._minimumValue + 1.0;
        this.setValue(this._value);
    },

    getMaximumValue:function () {
        return this._maximumValue;
    },
    setMaximumValue:function (maximumValue) {
        this._maximumValue = maximumValue;
        this._maximumAllowedValue = maximumValue;
        if (this._maximumValue <= this._minimumValue)
            this._minimumValue = this._maximumValue - 1.0;
        this.setValue(this._value);
    },
    isTouchInside:function (touch) {
        var touchLocation = touch.getLocation();
        touchLocation = this.getParent().convertToNodeSpace(touchLocation);

        var rect = this.getBoundingBox();
        rect.width += this._thumbSprite.getContentSize().width;
        rect.x -= this._thumbSprite.getContentSize().width / 2;

        return cc.rectContainsPoint(rect, touchLocation);
    },
    locationFromTouch:function (touch) {
        var touchLocation = touch.getLocation();                      // Get the touch position
        touchLocation = this.convertToNodeSpace(touchLocation);                  // Convert to the node space of this class

        if (touchLocation.x < 0) {
            touchLocation.x = 0;
        } else if (touchLocation.x > this._backgroundSprite.getContentSize().width) {
            touchLocation.x = this._backgroundSprite.getContentSize().width;
        }

        return touchLocation;
    },
    getMinimumAllowedValue:function () {
        return this._minimumAllowedValue;
    },
    setMinimumAllowedValue:function (val) {
        this._minimumAllowedValue = val;
    },

    getMaximumAllowedValue:function () {
        return this._maximumAllowedValue;
    },

    setMaximumAllowedValue:function (val) {
        this._maximumAllowedValue = val;
    },

    getThumbSprite:function () {
        return this._thumbSprite;
    },
    getProgressSprite:function () {
        return this._progressSprite;
    },
    getBackgroundSprite:function () {
        return this._backgroundSprite;
    },

    /**
     * Initializes a slider with a background sprite, a progress bar and a thumb
     * item.
     *
     * @param {cc.Sprite} backgroundSprite  CCSprite, that is used as a background.
     * @param {cc.Sprite} progressSprite    CCSprite, that is used as a progress bar.
     * @param {cc.Sprite} thumbSprite         CCMenuItem, that is used as a thumb.
     */
    initWithSprites:function (backgroundSprite, progressSprite, thumbSprite) {
        if (cc.Control.prototype.init.call(this)) {
            this.ignoreAnchorPointForPosition(false);

            this._backgroundSprite = backgroundSprite;
            this._progressSprite = progressSprite;
            this._thumbSprite = thumbSprite;

            // Defines the content size
            var maxRect = cc.ControlUtils.CCRectUnion(backgroundSprite.getBoundingBox(), thumbSprite.getBoundingBox());
            this.setContentSize(maxRect.width, maxRect.height);

            // Add the slider background
            this._backgroundSprite.setAnchorPoint(0.5, 0.5);
            this._backgroundSprite.setPosition(maxRect.width / 2, maxRect.height / 2);
            this.addChild(this._backgroundSprite);

            // Add the progress bar
            this._progressSprite.setAnchorPoint(0.0, 0.5);
            this._progressSprite.setPosition(0, maxRect.height / 2);
            this.addChild(this._progressSprite);

            // Add the slider thumb
            this._thumbSprite.setPosition(0, maxRect.height / 2);
            this.addChild(this._thumbSprite);

            // Init default values
            this._minimumValue = 0.0;
            this._maximumValue = 1.0;
            this.setValue(this._minimumValue);
            return true;
        } else
            return false;
    },

    setEnabled:function (enabled) {
        cc.Control.prototype.setEnabled.call(this, enabled);
        if (this._thumbSprite) {
            this._thumbSprite.setOpacity(enabled ? 255 : 128);
        }
    },

    sliderBegan:function (location) {
        this.setSelected(true);
        this._thumbSprite.setColor(cc.color.GRAY);
        this.setValue(this.valueForLocation(location));
    },
    sliderMoved:function (location) {
        this.setValue(this.valueForLocation(location));
    },
    sliderEnded:function (location) {
        if (this.isSelected()) {
            this.setValue(this.valueForLocation(this._thumbSprite.getPosition()));
        }
        this._thumbSprite.setColor(cc.color.WHITE);
        this.setSelected(false);
    },

    getTouchLocationInControl:function (touch) {
        var touchLocation = touch.getLocation();                      // Get the touch position
        touchLocation = this.convertToNodeSpace(touchLocation);         // Convert to the node space of this class

        if (touchLocation.x < 0) {
            touchLocation.x = 0;
        } else if (touchLocation.x > this._backgroundSprite.getContentSize().width + cc.SLIDER_MARGIN_H) {
            touchLocation.x = this._backgroundSprite.getContentSize().width + cc.SLIDER_MARGIN_H;
        }
        return touchLocation;
    },

    onTouchBegan:function (touch, event) {
        if (!this.isTouchInside(touch)|| !this.isEnabled() || !this.isVisible())
            return false;

        var location = this.locationFromTouch(touch);
        this.sliderBegan(location);
        return true;
    },
    onTouchMoved:function (touch, event) {
        var location = this.locationFromTouch(touch);
        this.sliderMoved(location);
    },
    onTouchEnded:function (touch, event) {
        this.sliderEnded(cc.p(0,0));
    },
    needsLayout:function(){
        var percent = (this._value - this._minimumValue) / (this._maximumValue - this._minimumValue);
        this._thumbSprite.setPositionX(percent * this._backgroundSprite.getContentSize().width);

        // Stretches content proportional to newLevel
        var textureRect = this._progressSprite.getTextureRect();
        textureRect = cc.rect(textureRect.x, textureRect.y, this._thumbSprite.getPositionX(), textureRect.height);
        this._progressSprite.setTextureRect(textureRect, this._progressSprite.isTextureRectRotated());
        this._thumbSprite._renderCmd.transform(this._renderCmd);
    },
    /** Returns the value for the given location. */
    valueForLocation:function (location) {
        var percent = location.x / this._backgroundSprite.getContentSize().width;
        return Math.max(Math.min(this._minimumValue + percent * (this._maximumValue - this._minimumValue), this._maximumAllowedValue), this._minimumAllowedValue);
    }
});

var _p = cc.ControlSlider.prototype;

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
_p.minAllowedValue;
cc.defineGetterSetter(_p, "minAllowedValue", _p.getMinimumAllowedValue, _p.setMinimumAllowedValue);
/** @expose */
_p.maxAllowedValue;
cc.defineGetterSetter(_p, "maxAllowedValue", _p.getMaximumAllowedValue, _p.setMaximumAllowedValue);
/** @expose */
_p.thumbSprite;
cc.defineGetterSetter(_p, "thumbSprite", _p.getThumbSprite);
/** @expose */
_p.progressSprite;
cc.defineGetterSetter(_p, "progressSprite", _p.getProgressSprite);
/** @expose */
_p.backgroundSprite;
cc.defineGetterSetter(_p, "backgroundSprite", _p.getBackgroundSprite);

_p = null;

/**
 * Creates a slider with a given background sprite and a progress bar and a
 * thumb item.
 * @deprecated
 * @see cc.ControlSlider
 */
cc.ControlSlider.create = function (bgFile, progressFile, thumbFile) {
    return new cc.ControlSlider(bgFile, progressFile, thumbFile);
};