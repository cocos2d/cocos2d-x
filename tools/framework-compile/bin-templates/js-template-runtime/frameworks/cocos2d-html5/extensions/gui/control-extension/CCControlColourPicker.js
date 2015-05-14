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
 * THE SOFTWARE. *
 *
 */

/**
 * ControlColourPicker: color picker ui component.
 * @class
 * @extends cc.Control
 *
 * @property {cc.Sprite}  background   - <@readonly> The background sprite
 */
cc.ControlColourPicker = cc.Control.extend(/** @lends cc.ControlColourPicker# */{
    _hsv:null,
    _colourPicker:null,
    _huePicker:null,

    _background:null,
    _className:"ControlColourPicker",
    ctor:function () {
        cc.Control.prototype.ctor.call(this);
        this.init();
    },
    hueSliderValueChanged:function (sender, controlEvent) {
        this._hsv.h = sender.getHue();

        // Update the value
        var rgb = cc.ControlUtils.RGBfromHSV(this._hsv);
        cc.Control.prototype.setColor.call(this,cc.color(0 | (rgb.r * 255), 0 | (rgb.g * 255), 0 | (rgb.b * 255)));

        // Send CCControl callback
        this.sendActionsForControlEvents(cc.CONTROL_EVENT_VALUECHANGED);
        this._updateControlPicker();
    },

    colourSliderValueChanged:function (sender, controlEvent) {
        this._hsv.s = sender.getSaturation();
        this._hsv.v = sender.getBrightness();


        // Update the value
        var rgb = cc.ControlUtils.RGBfromHSV(this._hsv);
        cc.Control.prototype.setColor.call(this,cc.color(0 | (rgb.r * 255), 0 | (rgb.g * 255), 0 | (rgb.b * 255)));

        // Send CCControl callback
        this.sendActionsForControlEvents(cc.CONTROL_EVENT_VALUECHANGED);
    },

    setColor:function (color) {
        cc.Control.prototype.setColor.call(this,color);
        //this._colorValue = color;
        var rgba = new cc.RGBA();
        rgba.r = color.r / 255.0;
        rgba.g = color.g / 255.0;
        rgba.b = color.b / 255.0;
        rgba.a = 1.0;

        this._hsv = cc.ControlUtils.HSVfromRGB(rgba);
        this._updateHueAndControlPicker();
    },

    getBackground:function () {
        return this._background;
    },

    init:function () {
        if (cc.Control.prototype.init.call(this)) {
            // Cache the sprites
            cc.spriteFrameCache.addSpriteFrames(res.CCControlColourPickerSpriteSheet_plist);

            // Create the sprite batch node
            var spriteSheet = new cc.SpriteBatchNode(res.CCControlColourPickerSpriteSheet_png);
            this.addChild(spriteSheet);

          /*// MIPMAP
            //TODO WebGL code
            var params = [gl.LINEAR_MIPMAP_NEAREST, gl.LINEAR, gl.REPEAT, gl.CLAMP_TO_EDGE];
            spriteSheet.getTexture().setAliasTexParameters();
            spriteSheet.getTexture().setTexParameters(params);
            spriteSheet.getTexture().generateMipmap();*/

            // Init default color
            this._hsv = new cc.HSV(0, 0, 0);

            // Add image
            this._background = cc.ControlUtils.addSpriteToTargetWithPosAndAnchor("menuColourPanelBackground.png", spriteSheet, cc.p(0,0), cc.p(0.5, 0.5));

            var backgroundPointZero = cc.pSub(this._background.getPosition(),
                cc.p(this._background.getContentSize().width / 2, this._background.getContentSize().height / 2));

            // Setup panels . currently hard-coded...
            var hueShift = 8;
            var colourShift = 28;

            this._huePicker = new cc.ControlHuePicker(spriteSheet, cc.p(backgroundPointZero.x + hueShift, backgroundPointZero.y + hueShift));
            this._colourPicker = new cc.ControlSaturationBrightnessPicker(spriteSheet, cc.p(backgroundPointZero.x + colourShift, backgroundPointZero.y + colourShift));

            // Setup events
            this._huePicker.addTargetWithActionForControlEvents(this, this.hueSliderValueChanged, cc.CONTROL_EVENT_VALUECHANGED);
            this._colourPicker.addTargetWithActionForControlEvents(this, this.colourSliderValueChanged, cc.CONTROL_EVENT_VALUECHANGED);

            // Set defaults
            this._updateHueAndControlPicker();
            this.addChild(this._huePicker);
            this.addChild(this._colourPicker);

            // Set content size
            this.setContentSize(this._background.getContentSize());
            return true;
        }
        else
            return false;
    },

    _updateControlPicker:function () {
        this._huePicker.setHue(this._hsv.h);
        this._colourPicker.updateWithHSV(this._hsv);
    },

    _updateHueAndControlPicker:function () {
        this._huePicker.setHue(this._hsv.h);
        this._colourPicker.updateWithHSV(this._hsv);
        this._colourPicker.updateDraggerWithHSV(this._hsv);
    },
    setEnabled:function (enabled) {
        cc.Control.prototype.setEnabled.call(this, enabled);
        if (this._huePicker !== null) {
            this._huePicker.setEnabled(enabled);
        }
        if (this._colourPicker) {
            this._colourPicker.setEnabled(enabled);
        }
    },
    onTouchBegan:function () {
        //ignore all touches, handled by children
        return false;
    }
});

var _p = cc.ControlColourPicker.prototype;

// Extended properties
/** @expose */
_p.background;
cc.defineGetterSetter(_p, "background", _p.getBackground);

_p = null;

/**
 * @deprecated
 * @returns {ControlColourPicker}
 */
cc.ControlColourPicker.create = function () {
    return new cc.ControlColourPicker();
};

// compatible with NPM
var res = res || {};
res.CCControlColourPickerSpriteSheet_plist = res.CCControlColourPickerSpriteSheet_plist || "res/extensions/CCControlColourPickerSpriteSheet.plist";
res.CCControlColourPickerSpriteSheet_png = res.CCControlColourPickerSpriteSheet_png || "res/extensions/CCControlColourPickerSpriteSheet.png";