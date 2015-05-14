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
 */

/**
 * CCControlSwitch: Switch control ui component
 * @class
 * @extends cc.Control
 */
cc.ControlSwitch = cc.Control.extend(/** @lends cc.ControlSwitch# */{
    /** Sprite which represents the view. */
    _switchSprite:null,
    _initialTouchXPosition:0,

    _moved:false,
    /** A Boolean value that determines the off/on state of the switch. */
    _on:false,
    _className:"ControlSwitch",
    ctor:function (maskSprite, onSprite, offSprite, thumbSprite, onLabel, offLabel) {
        cc.Control.prototype.ctor.call(this);

        offLabel && this.initWithMaskSprite(maskSprite, onSprite, offSprite, thumbSprite, onLabel, offLabel);
    },

    /** Creates a switch with a mask sprite, on/off sprites for on/off states, a thumb sprite and an on/off labels. */
    initWithMaskSprite:function (maskSprite, onSprite, offSprite, thumbSprite, onLabel, offLabel) {
        if(!maskSprite)
            throw "cc.ControlSwitch.initWithMaskSprite(): maskSprite should be non-null.";
        if(!onSprite)
            throw "cc.ControlSwitch.initWithMaskSprite(): onSprite should be non-null.";
        if(!offSprite)
            throw "cc.ControlSwitch.initWithMaskSprite(): offSprite should be non-null.";
        if(!thumbSprite)
            throw "cc.ControlSwitch.initWithMaskSprite(): thumbSprite should be non-null.";
        if (this.init()) {
            this._on = true;

            this._switchSprite = new cc.ControlSwitchSprite();
            this._switchSprite.initWithMaskSprite(maskSprite, onSprite, offSprite, thumbSprite, onLabel, offLabel);
            this._switchSprite.setPosition(this._switchSprite.getContentSize().width / 2, this._switchSprite.getContentSize().height / 2);
            this.addChild(this._switchSprite);

            this.ignoreAnchorPointForPosition(false);
            this.setAnchorPoint(0.5, 0.5);
            this.setContentSize(this._switchSprite.getContentSize());
            return true;
        }
        return false;
    },

    setOn:function (isOn, animated) {
        animated = animated || false;
        this._on = isOn;
        var xPosition = (this._on) ? this._switchSprite.getOnPosition() : this._switchSprite.getOffPosition();
        if(animated){
            this._switchSprite.runAction(new cc.ActionTween(0.2, "sliderXPosition", this._switchSprite.getSliderXPosition(),xPosition));
        }else{
            this._switchSprite.setSliderXPosition(xPosition);
        }
        this.sendActionsForControlEvents(cc.CONTROL_EVENT_VALUECHANGED);
    },

    isOn:function () {
        return this._on;
    },

    hasMoved:function () {
        return this._moved;
    },

    setEnabled:function (enabled) {
        this._enabled = enabled;

        this._switchSprite.setOpacity((enabled) ? 255 : 128);
    },

    locationFromTouch:function (touch) {
        var touchLocation = touch.getLocation();                      // Get the touch position
        touchLocation = this.convertToNodeSpace(touchLocation);                  // Convert to the node space of this class

        return touchLocation;
    },

    onTouchBegan:function (touch, event) {
        if (!this.isTouchInside(touch)  || !this.isEnabled()|| !this.isVisible()) {
            return false;
        }

        this._moved = false;

        var location = this.locationFromTouch(touch);

        this._initialTouchXPosition = location.x - this._switchSprite.getSliderXPosition();

        this._switchSprite.getThumbSprite().setColor(cc.color.GRAY);
        this._switchSprite.needsLayout();

        return true;
    },

    onTouchMoved:function (touch, event) {
        var location = this.locationFromTouch(touch);
        location = cc.p(location.x - this._initialTouchXPosition, 0);

        this._moved = true;

        this._switchSprite.setSliderXPosition(location.x);
    },

    onTouchEnded:function (touch, event) {
        var location = this.locationFromTouch(touch);

        this._switchSprite.getThumbSprite().setColor(cc.color.WHITE);

        if (this.hasMoved()) {
            this.setOn(!(location.x < this._switchSprite.getContentSize().width / 2), true);
        } else {
            this.setOn(!this._on, true);
        }
    },

    onTouchCancelled:function (touch, event) {
        var location = this.locationFromTouch(touch);

        this._switchSprite.getThumbSprite().setColor(cc.color.WHITE);

        if (this.hasMoved()) {
            this.setOn(!(location.x < this._switchSprite.getContentSize().width / 2), true);
        } else {
            this.setOn(!this._on, true);
        }
    }
});

/** Creates a switch with a mask sprite, on/off sprites for on/off states and a thumb sprite.
 *  @deprecated
 */
cc.ControlSwitch.create = function (maskSprite, onSprite, offSprite, thumbSprite, onLabel, offLabel) {
    return new cc.ControlSwitch(maskSprite, onSprite, offSprite, thumbSprite, onLabel, offLabel);
};

/**
 * ControlSwitchSprite: Sprite switch control ui component
 * @class
 * @extends cc.Sprite
 *
 * @property {Number}           sliderX         - Slider's x position
 * @property {cc.Point}         onPos           - The position of slider when switch is on
 * @property {cc.Point}         offPos          - The position of slider when switch is off
 * @property {cc.Texture2D}     maskTexture     - The texture of the mask
 * @property {cc.Point}         texturePos      - The position of the texture
 * @property {cc.Point}         maskPos         - The position of the mask
 * @property {cc.Sprite}        onSprite        - The sprite of switch on
 * @property {cc.Sprite}        offSprite       - The sprite of switch off
 * @property {cc.Sprite}        thumbSprite     - The thumb sprite of the switch control
 * @property {cc.LabelTTF}      onLabel         - The sprite of switch on
 * @property {cc.LabelTTF}      offLabel        - The sprite of switch off
 * @property {Number}           onSideWidth     - <@readonly> The width of the on side of the switch control
 * @property {Number}           offSideWidth    - <@readonly> The width of the off side of the switch control
 */
cc.ControlSwitchSprite = cc.Sprite.extend({
    _sliderXPosition:0,
    _onPosition:0,
    _offPosition:0,

    _textureLocation:0,
    _maskLocation:0,
    _maskSize:null,

    _onSprite:null,
    _offSprite:null,
    _thumbSprite:null,
    _onLabel:null,
    _offLabel:null,
    _clipper:null,
    _stencil:null,
    _backRT:null,

    ctor:function () {
        cc.Sprite.prototype.ctor.call(this);
        this._sliderXPosition = 0;
        this._onPosition = 0;
        this._offPosition = 0;
        this._maskLocation = 0;
        this._maskSize = cc.size(0, 0);
        this._onSprite = null;
        this._offSprite = null;
        this._thumbSprite = null;
        this._onLabel = null;
        this._offLabel = null;
    },

    initWithMaskSprite:function (maskSprite, onSprite, offSprite, thumbSprite, onLabel, offLabel) {
        if (cc.Sprite.prototype.init.call(this)) {
            this.setSpriteFrame(maskSprite.displayFrame());
            // Sets the default values
            this._onPosition = 0;
            this._offPosition = -onSprite.getContentSize().width + thumbSprite.getContentSize().width / 2;
            this._sliderXPosition = this._onPosition;

            this.setOnSprite(onSprite);
            this.setOffSprite(offSprite);
            this.setThumbSprite(thumbSprite);
            this.setOnLabel(onLabel);
            this.setOffLabel(offLabel);

            // Set up the mask with the Mask shader
            this._stencil = maskSprite;
            var maskSize = this._maskSize = this._stencil.getContentSize();
            this._stencil.setPosition(0, 0);

            // Init clipper for mask
            this._clipper = new cc.ClippingNode();
            this._clipper.setAnchorPoint(0.5, 0.5);
            this._clipper.setPosition(maskSize.width / 2, maskSize.height / 2);
            this._clipper.setStencil(this._stencil);
            this.addChild(this._clipper);

            this._clipper.addChild(onSprite);
            this._clipper.addChild(offSprite);
            this._clipper.addChild(onLabel);
            this._clipper.addChild(offLabel);

            this.addChild(this._thumbSprite);

            this.needsLayout();
            return true;
        }
        return false;
    },

    needsLayout:function () {
        var maskSize = this._maskSize;
        this._onSprite.setPosition(
            this._onSprite.getContentSize().width / 2 + this._sliderXPosition - maskSize.width / 2,
            this._onSprite.getContentSize().height / 2 - maskSize.height / 2
        );
        this._offSprite.setPosition(
            this._onSprite.getContentSize().width + this._offSprite.getContentSize().width / 2 + this._sliderXPosition - maskSize.width / 2,
            this._offSprite.getContentSize().height / 2 - maskSize.height / 2
        );

        if (this._onLabel) {
            this._onLabel.setPosition(
                this._onSprite.getPositionX() - this._thumbSprite.getContentSize().width / 6,
                this._onSprite.getContentSize().height / 2 - maskSize.height / 2
            );
        }
        if (this._offLabel) {
            this._offLabel.setPosition(
                this._offSprite.getPositionX() + this._thumbSprite.getContentSize().width / 6,
                this._offSprite.getContentSize().height / 2 - maskSize.height / 2
            );
        }
        this._thumbSprite.setPosition(
            this._onSprite.getContentSize().width + this._sliderXPosition,
            this._maskSize.height / 2
        );
    },

    setSliderXPosition:function (sliderXPosition) {
        if (sliderXPosition <= this._offPosition) {
            // Off
            sliderXPosition = this._offPosition;
        } else if (sliderXPosition >= this._onPosition) {
            // On
            sliderXPosition = this._onPosition;
        }

        this._sliderXPosition = sliderXPosition;

        this.needsLayout();
    },
    getSliderXPosition:function () {
        return this._sliderXPosition;
    },

    _getOnSideWidth:function () {
        return this._onSprite.getContentSize().width;
    },

    _getOffSideWidth:function () {
        return this._offSprite.getContentSize().height;
    },

    updateTweenAction:function (value, key) {
        if (key === "sliderXPosition")
            this.setSliderXPosition(value);
    },

    setOnPosition:function (onPosition) {
        this._onPosition = onPosition;
    },
    getOnPosition:function () {
        return this._onPosition;
    },

    setOffPosition:function (offPosition) {
        this._offPosition = offPosition;
    },
    getOffPosition:function () {
        return this._offPosition;
    },

    setMaskTexture:function (maskTexture) {
        this._stencil.setTexture(maskTexture);
    },
    getMaskTexture:function () {
        return this._stencil.getTexture();
    },

    setTextureLocation:function (textureLocation) {
        this._textureLocation = textureLocation;
    },
    getTextureLocation:function () {
        return this._textureLocation;
    },

    setMaskLocation:function (maskLocation) {
        this._maskLocation = maskLocation;
    },
    getMaskLocation:function () {
        return this._maskLocation;
    },

    setOnSprite:function (onSprite) {
        this._onSprite = onSprite;
    },
    getOnSprite:function () {
        return this._onSprite;
    },

    setOffSprite:function (offSprite) {
        this._offSprite = offSprite;
    },
    getOffSprite:function () {
        return this._offSprite;
    },

    setThumbSprite:function (thumbSprite) {
        this._thumbSprite = thumbSprite;
    },
    getThumbSprite:function () {
        return this._thumbSprite;
    },

    setOnLabel:function (onLabel) {
        this._onLabel = onLabel;
    },
    getOnLabel:function () {
        return this._onLabel;
    },

    setOffLabel:function (offLabel) {
        this._offLabel = offLabel;
    },
    getOffLabel:function () {
        return this._offLabel;
    }
});

var _p = cc.ControlSwitchSprite.prototype;

/** @expose */
_p.sliderX;
cc.defineGetterSetter(_p, "sliderX", _p.getSliderXPosition, _p.setSliderXPosition);
/** @expose */
_p.onPos;
cc.defineGetterSetter(_p, "onPos", _p.getOnPosition, _p.setOnPosition);
/** @expose */
_p.offPos;
cc.defineGetterSetter(_p, "offPos", _p.getOffPosition, _p.setOffPosition);
/** @expose */
_p.maskTexture;
cc.defineGetterSetter(_p, "maskTexture", _p.getMaskTexture, _p.setMaskTexture);
/** @expose */
_p.maskPos;
cc.defineGetterSetter(_p, "maskPos", _p.getMaskLocation, _p.setMaskLocation);
/** @expose */
_p.onSprite;
cc.defineGetterSetter(_p, "onSprite", _p.getOnSprite, _p.setOnSprite);
/** @expose */
_p.offSprite;
cc.defineGetterSetter(_p, "offSprite", _p.getOffSprite, _p.setOffSprite);
/** @expose */
_p.thumbSprite;
cc.defineGetterSetter(_p, "thumbSprite", _p.getThumbSprite, _p.setThumbSprite);
/** @expose */
_p.onLabel;
cc.defineGetterSetter(_p, "onLabel", _p.getOnLabel, _p.setOnLabel);
/** @expose */
_p.offLabel;
cc.defineGetterSetter(_p, "offLabel", _p.getOffLabel, _p.setOffLabel);
/** @expose */
_p.onSideWidth;
cc.defineGetterSetter(_p, "onSideWidth", _p._getOnSideWidth);
/** @expose */
_p.offSideWidth;
cc.defineGetterSetter(_p, "offSideWidth", _p._getOffSideWidth);

_p = null;
