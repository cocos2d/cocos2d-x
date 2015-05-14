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
 * @ignore
 */
cc.CONTROL_STEPPER_PARTMINUS = 0;
cc.CONTROL_STEPPER_PARTPLUS = 1;
cc.CONTROL_STEPPER_PARTNONE = 2;
cc.CONTROL_STEPPER_LABELCOLOR_ENABLED = cc.color(55, 55, 55);
cc.CONTROL_STEPPER_LABELCOLOR_DISABLED = cc.color(147, 147, 147);
cc.CONTROL_STEPPER_LABELFONT = "CourierNewPSMT";
cc.AUTOREPEAT_DELTATIME = 0.15;
cc.AUTOREPEAT_INCREASETIME_INCREMENT = 12;

/**
 * ControlStepper: Stepper ui component.
 * @class
 * @extends cc.Control
 *
 * @property {Boolean}      wraps       - Indicate whether the stepper wraps
 * @property {Number}       value       - The value of the stepper control
 * @property {Number}       minValue    - The minimum value of the stepper control
 * @property {Number}       maxValue    - The maximum value of the stepper control
 * @property {Number}       stepValue   - The interval value for each step of the stepper control
 * @property {Boolean}      continuous  - <@readonly> Indicate whether the stepper value is continuous
 * @property {cc.Sprite}    minusSprite - The sprite for minus button of the stepper control
 * @property {cc.Sprite}    plusSprite  - The sprite for plus button of the stepper control
 * @property {cc.LabelTTF}  minusLabel  - The label for minus button of the stepper control
 * @property {cc.LabelTTF}  plusSLabel  - The label for plus button of the stepper control
 */
cc.ControlStepper = cc.Control.extend(/** @lends cc.ControlStepper# */{
    _minusSprite:null,
    _plusSprite:null,
    _minusLabel:null,
    _plusLabel:null,
    _value:0,
    _continuous:false,
    _autorepeat:false,
    _wraps:false,
    _minimumValue:0,
    _maximumValue:0,
    _stepValue:0,
    _touchInsideFlag:false,
    _touchedPart:cc.CONTROL_STEPPER_PARTNONE,
    _autorepeatCount:0,
    _className:"ControlStepper",
    ctor:function (minusSprite, plusSprite) {
        cc.Control.prototype.ctor.call(this);
        this._minusSprite = null;
        this._plusSprite = null;
        this._minusLabel = null;
        this._plusLabel = null;
        this._value = 0;
        this._continuous = false;
        this._autorepeat = false;
        this._wraps = false;
        this._minimumValue = 0;
        this._maximumValue = 0;
        this._stepValue = 0;
        this._touchInsideFlag = false;
        this._touchedPart = cc.CONTROL_STEPPER_PARTNONE;
        this._autorepeatCount = 0;

        plusSprite && this.initWithMinusSpriteAndPlusSprite(minusSprite, plusSprite);

    },

    initWithMinusSpriteAndPlusSprite:function (minusSprite, plusSprite) {
        if(!minusSprite)
            throw "cc.ControlStepper.initWithMinusSpriteAndPlusSprite(): Minus sprite should be non-null.";
        if(!plusSprite)
            throw "cc.ControlStepper.initWithMinusSpriteAndPlusSprite(): Plus sprite should be non-null.";

        if (this.init()) {
            // Set the default values
            this._autorepeat = true;
            this._continuous = true;
            this._minimumValue = 0;
            this._maximumValue = 100;
            this._value = 0;
            this._stepValue = 1;
            this._wraps = false;
            this.ignoreAnchorPointForPosition(false);

            // Add the minus components
            this.setMinusSprite(minusSprite);
            this._minusSprite.setPosition(minusSprite.getContentSize().width / 2, minusSprite.getContentSize().height / 2);
            this.addChild(this._minusSprite);

            this.setMinusLabel(new cc.LabelTTF("-", cc.CONTROL_STEPPER_LABELFONT, 40, cc.size(40, 40), cc.TEXT_ALIGNMENT_CENTER, cc.VERTICAL_TEXT_ALIGNMENT_CENTER));
            this._minusLabel.setColor(cc.CONTROL_STEPPER_LABELCOLOR_DISABLED);
            this._minusLabel.setPosition(this._minusSprite.getContentSize().width / 2, this._minusSprite.getContentSize().height / 2);
            this._minusSprite.addChild(this._minusLabel);

            // Add the plus components
            this.setPlusSprite(plusSprite);
            this._plusSprite.setPosition(minusSprite.getContentSize().width + plusSprite.getContentSize().width / 2,
                minusSprite.getContentSize().height / 2);
            this.addChild(this._plusSprite);

            this.setPlusLabel(new cc.LabelTTF("+", cc.CONTROL_STEPPER_LABELFONT, 40, cc.size(40, 40), cc.TEXT_ALIGNMENT_CENTER, cc.VERTICAL_TEXT_ALIGNMENT_CENTER));
            this._plusLabel.setColor(cc.CONTROL_STEPPER_LABELCOLOR_ENABLED);
            this._plusLabel.setPosition(this._plusSprite.getContentSize().width / 2, this._plusSprite.getContentSize().height / 2);
            this._plusSprite.addChild(this._plusLabel);

            // Defines the content size
            var maxRect = cc.ControlUtils.CCRectUnion(this._minusSprite.getBoundingBox(), this._plusSprite.getBoundingBox());
            this.setContentSize(this._minusSprite.getContentSize().width + this._plusSprite.getContentSize().height, maxRect.height);
            return true;
        }
        return false;
    },

//#pragma mark Properties

    setWraps: function (wraps) {
        this._wraps = wraps;

        if (this._wraps) {
            this._minusLabel.setColor(cc.CONTROL_STEPPER_LABELCOLOR_ENABLED);
            this._plusLabel.setColor(cc.CONTROL_STEPPER_LABELCOLOR_ENABLED);
        }

        this.setValue(this._value);
    },

	getWraps: function () {
		return this._wraps;
	},

    setMinimumValue:function (minimumValue) {
        if (minimumValue >= this._maximumValue)
            throw "cc.ControlStepper.setMinimumValue(): minimumValue should be numerically less than maximumValue.";

        this._minimumValue = minimumValue;
        this.setValue(this._value);
    },
	getMinimumValue: function () {
		return this._minimumValue;
	},

    setMaximumValue:function (maximumValue) {
        if (maximumValue <= this._minimumValue)
            throw "cc.ControlStepper.setMaximumValue(): maximumValue should be numerically less than maximumValue.";

        this._maximumValue = maximumValue;
        this.setValue(this._value);
    },
	getMaximumValue: function () {
		return this._maximumValue;
	},

    setValue:function (value) {
        this.setValueWithSendingEvent(value, true);
    },

    getValue:function () {
        return this._value;
    },

    setStepValue:function (stepValue) {
        if (stepValue <= 0)
            throw "cc.ControlStepper.setMaximumValue(): stepValue should be numerically greater than 0.";
        this._stepValue = stepValue;
    },

	getStepValue:function () {
		return this._stepValue;
	},

    isContinuous:function () {
        return this._continuous;
    },

    setValueWithSendingEvent:function (value, send) {
        if (value < this._minimumValue) {
            value = this._wraps ? this._maximumValue : this._minimumValue;
        } else if (value > this._maximumValue) {
            value = this._wraps ? this._minimumValue : this._maximumValue;
        }

        this._value = value;

        if (!this._wraps) {
            this._minusLabel.setColor((value === this._minimumValue) ? cc.CONTROL_STEPPER_LABELCOLOR_DISABLED : cc.CONTROL_STEPPER_LABELCOLOR_ENABLED);
            this._plusLabel.setColor((value === this._maximumValue) ? cc.CONTROL_STEPPER_LABELCOLOR_DISABLED : cc.CONTROL_STEPPER_LABELCOLOR_ENABLED);
        }

        if (send) {
            this.sendActionsForControlEvents(cc.CONTROL_EVENT_VALUECHANGED);
        }
    },

    startAutorepeat:function () {
        this._autorepeatCount = -1;
        this.schedule(this.update, cc.AUTOREPEAT_DELTATIME, cc.REPEAT_FOREVER, cc.AUTOREPEAT_DELTATIME * 3);
    },

    /** Stop the autorepeat. */
    stopAutorepeat:function () {
        this.unschedule(this.update);
    },

    update:function (dt) {
        this._autorepeatCount++;

        if ((this._autorepeatCount < cc.AUTOREPEAT_INCREASETIME_INCREMENT) && (this._autorepeatCount % 3) !== 0)
            return;

        if (this._touchedPart === cc.CONTROL_STEPPER_PARTMINUS) {
            this.setValueWithSendingEvent(this._value - this._stepValue, this._continuous);
        } else if (this._touchedPart === cc.CONTROL_STEPPER_PARTPLUS) {
            this.setValueWithSendingEvent(this._value + this._stepValue, this._continuous);
        }
    },

//#pragma mark CCControlStepper Private Methods

    updateLayoutUsingTouchLocation:function (location) {
        if (location.x < this._minusSprite.getContentSize().width
            && this._value > this._minimumValue) {
            this._touchedPart = cc.CONTROL_STEPPER_PARTMINUS;
            this._minusSprite.setColor(cc.color.GRAY);
            this._plusSprite.setColor(cc.color.WHITE);

        } else if (location.x >= this._minusSprite.getContentSize().width
            && this._value < this._maximumValue) {
            this._touchedPart = cc.CONTROL_STEPPER_PARTPLUS;
            this._minusSprite.setColor(cc.color.WHITE);
            this._plusSprite.setColor(cc.color.GRAY);

        } else {
            this._touchedPart = cc.CONTROL_STEPPER_PARTNONE;
            this._minusSprite.setColor(cc.color.WHITE);
            this._plusSprite.setColor(cc.color.WHITE);
        }
    },


    onTouchBegan:function (touch, event) {
        if (!this.isTouchInside(touch) || !this.isEnabled() || !this.isVisible()) {
            return false;
        }

        var location = this.getTouchLocation(touch);
        this.updateLayoutUsingTouchLocation(location);
        this._touchInsideFlag = true;

        if (this._autorepeat) {
            this.startAutorepeat();
        }

        return true;
    },

    onTouchMoved:function (touch, event) {
        if (this.isTouchInside(touch)) {
            var location = this.getTouchLocation(touch);
            this.updateLayoutUsingTouchLocation(location);

            if (!this._touchInsideFlag) {
                this._touchInsideFlag = true;

                if (this._autorepeat) {
                    this.startAutorepeat();
                }
            }
        } else {
            this._touchInsideFlag = false;
            this._touchedPart = cc.CONTROL_STEPPER_PARTNONE;
            this._minusSprite.setColor(cc.color.WHITE);
            this._plusSprite.setColor(cc.color.WHITE);
            if (this._autorepeat) {
                this.stopAutorepeat();
            }
        }
    },

    onTouchEnded:function (touch, event) {
        this._minusSprite.setColor(cc.color.WHITE);
        this._plusSprite.setColor(cc.color.WHITE);

        if (this._autorepeat) {
            this.stopAutorepeat();
        }

        if (this.isTouchInside(touch)) {
            var location = this.getTouchLocation(touch);
            this.setValue(this._value + ((location.x < this._minusSprite.getContentSize().width) ? (0.0 - this._stepValue) : this._stepValue));
        }
    },
    setMinusSprite:function (sprite) {
        this._minusSprite = sprite;
    },
    getMinusSprite:function () {
        return this._minusSprite;
    },
    setPlusSprite:function (sprite) {
        this._plusSprite = sprite;
    },
    getPlusSprite:function () {
        return this._plusSprite;
    },
    setMinusLabel:function (sprite) {
        this._minusLabel = sprite;
    },
    getMinusLabel:function () {
        return this._minusLabel;
    },
    setPlusLabel:function (sprite) {
        this._plusLabel = sprite;
    },
    getPlusLabel:function () {
        return this._plusLabel;
    }
});

var _p = cc.ControlStepper.prototype;

// Extedned properties
/** @expose */
_p.wraps;
cc.defineGetterSetter(_p, "wraps", _p.getWraps, _p.setWraps);
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
_p.stepValue;
cc.defineGetterSetter(_p, "stepValue", _p.getStepValue, _p.setStepValue);
/** @expose */
_p.continuous;
cc.defineGetterSetter(_p, "continuous", _p.isContinuous);
/** @expose */
_p.minusSprite;
cc.defineGetterSetter(_p, "minusSprite", _p.getMinusSprite, _p.setMinusSprite);
/** @expose */
_p.plusSprite;
cc.defineGetterSetter(_p, "plusSprite", _p.getPlusSprite, _p.setPlusSprite);
/** @expose */
_p.minusLabel;
cc.defineGetterSetter(_p, "minusLabel", _p.getMinusLabel, _p.setMinusLabel);
/** @expose */
_p.plusLabel;
cc.defineGetterSetter(_p, "plusLabel", _p.getPlusLabel, _p.setPlusLabel);

_p = null;

/**
 * Creates a cc.ControlStepper
 * @param {cc.Sprite} minusSprite
 * @param {cc.Sprite} plusSprite
 * @returns {ControlStepper}
 */
cc.ControlStepper.create = function (minusSprite, plusSprite) {
    return new cc.ControlStepper(minusSprite, plusSprite);
};