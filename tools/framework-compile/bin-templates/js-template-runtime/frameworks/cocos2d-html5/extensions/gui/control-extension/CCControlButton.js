/**
 * CCControlButton.m
 *
 * Copyright (c) 2008-2010 Ricardo Quesada
 * Copyright (c) 2011-2012 cocos2d-x.org
 * Copyright (c) 2013-2014 Chukong Technologies Inc.
 * Copyright 2011 Yannick Loriot.
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
 * @ignore
 */
cc.CONTROL_ZOOM_ACTION_TAG = 0xCCCB0001;

/**
 * CCControlButton: Button control for Cocos2D.
 * @class
 * @extends cc.Control
 *
 * @property {Boolean}  adjustBackgroundImage   - Indicate whether the background image will be adjusted
 * @property {Boolean}  zoomOnTouchDown         - Indicate whether the button will be zoomed while touch down
 * @property {cc.Size}  preferredSize           - The preferred size of the control button
 * @property {Boolean}  labelAnchor             - The anchor point for the label of the control button
 */
cc.ControlButton = cc.Control.extend(/** @lends cc.ControlButton# */{
    _doesAdjustBackgroundImage: false,
    zoomOnTouchDown: false,
    _preferredSize: null,
    _labelAnchorPoint: null,
    _currentTitle: null,
    _currentTitleColor: null,
    _titleLabel: null,
    _backgroundSprite: null,
    _opacity: 0,
    _isPushed: false,
    _titleDispatchTable: null,
    _titleColorDispatchTable: null,
    _titleLabelDispatchTable: null,
    _backgroundSpriteDispatchTable: null,
    _parentInited: false,

    _marginV: 0,
    _marginH: 0,
    _className: "ControlButton",

    ctor: function (label, backgroundSprite, fontSize) {
        cc.Control.prototype.ctor.call(this);
        this._preferredSize = cc.size(0, 0);
        this._labelAnchorPoint = cc.p(0, 0);
        this._currentTitle = "";
        this._currentTitleColor = cc.color.WHITE;
        this._titleDispatchTable = {};
        this._titleColorDispatchTable = {};
        this._titleLabelDispatchTable = {};
        this._backgroundSpriteDispatchTable = {};

        if(fontSize != undefined)
            this.initWithTitleAndFontNameAndFontSize(label, backgroundSprite, fontSize);
        else if(backgroundSprite != undefined)
            this.initWithLabelAndBackgroundSprite(label, backgroundSprite);
        else if(label != undefined)
            this.initWithBackgroundSprite(label);
        else
            this.init();
    },

    init: function () {
        return this.initWithLabelAndBackgroundSprite(new cc.LabelTTF("", "Arial", 12), new cc.Scale9Sprite());
    },

    needsLayout: function () {
        if (!this._parentInited) {
            return;
        }
        // Hide the background and the label
        if (this._titleLabel)
            this._titleLabel.setVisible(false);
        if (this._backgroundSprite)
            this._backgroundSprite.setVisible(false);

        // Update anchor of all labels
        this.setLabelAnchorPoint(this._labelAnchorPoint);

        // Update the label to match with the current state
        //CC_SAFE_RELEASE(this._currentTitle)
        var locState = this._state;

        this._currentTitle = this.getTitleForState(locState);
        this._currentTitleColor = this.getTitleColorForState(locState);
        this._titleLabel = this.getTitleLabelForState(locState);

        var label = this._titleLabel;
        if (label && label.setString)
            label.setString(this._currentTitle);
        if (label)
            label.setColor(this._currentTitleColor);

        var locContentSize = this.getContentSize();
        if (label)
            label.setPosition(locContentSize.width / 2, locContentSize.height / 2);

        // Update the background sprite
        this._backgroundSprite = this.getBackgroundSpriteForState(locState);
        var locBackgroundSprite = this._backgroundSprite;
        if (locBackgroundSprite)
            locBackgroundSprite.setPosition(locContentSize.width / 2, locContentSize.height / 2);

        // Get the title label size
        var titleLabelSize = cc.size(0, 0);
        if (label) {
            var boundingBox = label.getBoundingBox();
            titleLabelSize.width = boundingBox.width;
            titleLabelSize.height = boundingBox.height;
        }
        // Adjust the background image if necessary
        if (this._doesAdjustBackgroundImage) {
            // Add the margins
            if (locBackgroundSprite)
                locBackgroundSprite.setContentSize(titleLabelSize.width + this._marginH * 2, titleLabelSize.height + this._marginV * 2);
        } else {
            //TODO: should this also have margins if one of the preferred sizes is relaxed?
            if (locBackgroundSprite) {
                var preferredSize = locBackgroundSprite.getPreferredSize();
                preferredSize = cc.size(preferredSize.width, preferredSize.height);
                if (preferredSize.width <= 0)
                    preferredSize.width = titleLabelSize.width;
                if (preferredSize.height <= 0)
                    preferredSize.height = titleLabelSize.height;

                locBackgroundSprite.setContentSize(preferredSize);
            }
        }

        // Set the content size
        var rectTitle = label ? label.getBoundingBox() : cc.rect(0, 0, 0, 0);
        var rectBackground = locBackgroundSprite ? locBackgroundSprite.getBoundingBox() : cc.rect(0, 0, 0, 0);
        var maxRect = cc.rectUnion(rectTitle, rectBackground);
        this.setContentSize(maxRect.width, maxRect.height);
        locContentSize = this.getContentSize();
        if (label) {
            label.setPosition(locContentSize.width / 2, locContentSize.height / 2);
            label.setVisible(true);
        }
        if (locBackgroundSprite) {
            locBackgroundSprite.setPosition(locContentSize.width / 2, locContentSize.height / 2);
            locBackgroundSprite.setVisible(true);
        }
    },

    initWithLabelAndBackgroundSprite: function (label, backgroundSprite) {
        if (!label)
            throw "cc.ControlButton.initWithLabelAndBackgroundSprite(): label should be non-null";
        if (!backgroundSprite)
            throw "cc.ControlButton.initWithLabelAndBackgroundSprite(): backgroundSprite should be non-null";
        if (cc.Control.prototype.init.call(this, true)) {
            this._parentInited = true;

            // Initialize the button state tables
            this._titleDispatchTable = {};
            this._titleColorDispatchTable = {};
            this._titleLabelDispatchTable = {};
            this._backgroundSpriteDispatchTable = {};

            this._isPushed = false;
            this.zoomOnTouchDown = true;

            this._currentTitle = null;

            // Adjust the background image by default
            this.setAdjustBackgroundImage(true);
            this.setPreferredSize(cc.size(0, 0));

            // Zooming button by default
            this.zoomOnTouchDown = true;

            // Set the default anchor point
            this.ignoreAnchorPointForPosition(false);
            this.setAnchorPoint(0.5, 0.5);

            // Set the nodes
            this._titleLabel = label;
            this._backgroundSprite = backgroundSprite;

            // Set the default color and opacity
            this.setOpacity(255);
            this.setOpacityModifyRGB(true);

            // Initialize the dispatch table
            var tempString = label.getString();
            //tempString.autorelease();
            this.setTitleForState(tempString, cc.CONTROL_STATE_NORMAL);
            this.setTitleColorForState(label.getColor(), cc.CONTROL_STATE_NORMAL);
            this.setTitleLabelForState(label, cc.CONTROL_STATE_NORMAL);
            this.setBackgroundSpriteForState(backgroundSprite, cc.CONTROL_STATE_NORMAL);

            this._state = cc.CONTROL_STATE_NORMAL;

            //default margins
            this._marginH = 24;
            this._marginV = 12;

            this._labelAnchorPoint = cc.p(0.5, 0.5);

            this.setPreferredSize(cc.size(0, 0));

            // Layout update
            this.needsLayout();
            return true;
        }//couldn't init the CCControl
        else
            return false;
    },

    initWithTitleAndFontNameAndFontSize: function (title, fontName, fontSize) {
        var label = new cc.LabelTTF(title, fontName, fontSize);
        return this.initWithLabelAndBackgroundSprite(label, new cc.Scale9Sprite());
    },

    initWithBackgroundSprite: function (sprite) {
        var label = new cc.LabelTTF("", "Arial", 30);//
        return this.initWithLabelAndBackgroundSprite(label, sprite);
    },

    /**
     * Adjust the background image. YES by default. If the property is set to NO, the background will use the prefered size of the background image.
     * @return {Boolean}
     */
    doesAdjustBackgroundImage: function () {
        return this._doesAdjustBackgroundImage;
    },

    setAdjustBackgroundImage: function (adjustBackgroundImage) {
        this._doesAdjustBackgroundImage = adjustBackgroundImage;
        this.needsLayout();
    },

    /** Adjust the button zooming on touchdown. Default value is YES. */
    getZoomOnTouchDown: function () {
        return this.zoomOnTouchDown;
    },

    setZoomOnTouchDown: function (zoomOnTouchDown) {
        return this.zoomOnTouchDown = zoomOnTouchDown;
    },

    /** The prefered size of the button, if label is larger it will be expanded. */
    getPreferredSize: function () {
        return this._preferredSize;
    },

    setPreferredSize: function (size) {
        if (size.width === 0 && size.height === 0) {
            this._doesAdjustBackgroundImage = true;
        } else {
            this._doesAdjustBackgroundImage = false;
            var locTable = this._backgroundSpriteDispatchTable;
            for (var itemKey in locTable)
                locTable[itemKey].setPreferredSize(size);
        }
        this._preferredSize = size;
        this.needsLayout();
    },

    getLabelAnchorPoint: function () {
        return this._labelAnchorPoint;
    },
    setLabelAnchorPoint: function (labelAnchorPoint) {
        this._labelAnchorPoint = labelAnchorPoint;
        if (this._titleLabel)
            this._titleLabel.setAnchorPoint(labelAnchorPoint);
    },

    /**
     * The current title that is displayed on the button.
     * @return {string}
     */
    _getCurrentTitle: function () {
        return this._currentTitle;
    },

    /** The current color used to display the title. */
    _getCurrentTitleColor: function () {
        return this._currentTitleColor;
    },

    /* Override setter to affect a background sprite too */
    getOpacity: function () {
        return this._opacity;
    },

    setOpacity: function (opacity) {
        // XXX fixed me if not correct
        cc.Control.prototype.setOpacity.call(this, opacity);
        /*this._opacity = opacity;
         var controlChildren = this.getChildren();
         for (var i = 0; i < controlChildren.length; i++) {
         var selChild = controlChildren[i];
         if (selChild)
         selChild.setOpacity(opacity);
         }*/
        var locTable = this._backgroundSpriteDispatchTable;
        for (var itemKey in locTable)
            locTable[itemKey].setOpacity(opacity);
    },

    setColor: function (color) {
        cc.Control.prototype.setColor.call(this, color);
        var locTable = this._backgroundSpriteDispatchTable;
        for (var key in locTable)
            locTable[key].setColor(color);
    },

    getColor: function () {
        var locRealColor = this._realColor;
        return cc.color(locRealColor.r, locRealColor.g, locRealColor.b, locRealColor.a);
    },


    /** Flag to know if the button is currently pushed.  */
    isPushed: function () {
        return this._isPushed;
    },

    /* Define the button margin for Top/Bottom edge */
    _getVerticalMargin: function () {
        return this._marginV;
    },
    /* Define the button margin for Left/Right edge */
    _getHorizontalOrigin: function () {
        return this._marginH;
    },

    /**
     * set the margins at once (so we only have to do one call of needsLayout)
     * @param {Number} marginH
     * @param {Number} marginV
     */
    setMargins: function (marginH, marginV) {
        this._marginV = marginV;
        this._marginH = marginH;
        this.needsLayout();
    },

    setEnabled: function (enabled) {
        cc.Control.prototype.setEnabled.call(this, enabled);
        this.needsLayout();
    },
    setSelected: function (enabled) {
        cc.Control.prototype.setSelected.call(this, enabled);
        this.needsLayout();
    },

    setHighlighted: function (enabled) {
        this._state = enabled ? cc.CONTROL_STATE_HIGHLIGHTED : cc.CONTROL_STATE_NORMAL;

        cc.Control.prototype.setHighlighted.call(this, enabled);
        var action = this.getActionByTag(cc.CONTROL_ZOOM_ACTION_TAG);
        if (action)
            this.stopAction(action);

        //this.needsLayout();// needn't
        if (this.zoomOnTouchDown) {
            var scaleValue = (this.isHighlighted() && this.isEnabled() && !this.isSelected()) ? 1.1 : 1.0;
            var zoomAction = cc.scaleTo(0.05, scaleValue);
            zoomAction.setTag(cc.CONTROL_ZOOM_ACTION_TAG);
            this.runAction(zoomAction);
        }
    },

    onTouchBegan: function (touch, event) {
        if (!this.isTouchInside(touch) || !this.isEnabled() || !this.isVisible() || !this.hasVisibleParents())
            return false;

        this._isPushed = true;
        this.setHighlighted(true);
        this.sendActionsForControlEvents(cc.CONTROL_EVENT_TOUCH_DOWN);
        return true;
    },

    onTouchMoved: function (touch, event) {
        if (!this._enabled || !this._isPushed || this._selected) {
            if (this._highlighted)
                this.setHighlighted(false);
            return;
        }

        var isTouchMoveInside = this.isTouchInside(touch);
        if (isTouchMoveInside && !this._highlighted) {
            this.setHighlighted(true);
            this.sendActionsForControlEvents(cc.CONTROL_EVENT_TOUCH_DRAG_ENTER);
        } else if (isTouchMoveInside && this._highlighted) {
            this.sendActionsForControlEvents(cc.CONTROL_EVENT_TOUCH_DRAG_INSIDE);
        } else if (!isTouchMoveInside && this._highlighted) {
            this.setHighlighted(false);
            this.sendActionsForControlEvents(cc.CONTROL_EVENT_TOUCH_DRAG_EXIT);
        } else if (!isTouchMoveInside && !this._highlighted) {
            this.sendActionsForControlEvents(cc.CONTROL_EVENT_TOUCH_DRAG_OUTSIDE);
        }
    },
    onTouchEnded: function (touch, event) {
        this._isPushed = false;
        this.setHighlighted(false);

        if (this.isTouchInside(touch)) {
            this.sendActionsForControlEvents(cc.CONTROL_EVENT_TOUCH_UP_INSIDE);
        } else {
            this.sendActionsForControlEvents(cc.CONTROL_EVENT_TOUCH_UP_OUTSIDE);
        }
    },

    onTouchCancelled: function (touch, event) {
        this._isPushed = false;
        this.setHighlighted(false);
        this.sendActionsForControlEvents(cc.CONTROL_EVENT_TOUCH_CANCEL);
    },

    /**
     * Returns the title used for a state.
     *
     * @param {Number} state The state that uses the title. Possible values are described in "CCControlState".
     * @return {string} The title for the specified state.
     */
    getTitleForState: function (state) {
        var locTable = this._titleDispatchTable;
        if (locTable) {
            if (locTable[state])
                return locTable[state];
            return locTable[cc.CONTROL_STATE_NORMAL];
        }
        return "";
    },

    /**
     * <p>
     * Sets the title string to use for the specified state.                                                  <br/>
     * If a property is not specified for a state, the default is to use the CCButtonStateNormal value.
     * </p>
     * @param {string} title The title string to use for the specified state.
     * @param {Number} state The state that uses the specified title. The values are described in "CCControlState".
     */
    setTitleForState: function (title, state) {
        this._titleDispatchTable[state] = title || "";

        // If the current state if equal to the given state we update the layout
        if (this.getState() === state)
            this.needsLayout();
    },

    /**
     * Returns the title color used for a state.
     *
     * @param {Number} state The state that uses the specified color. The values are described in "CCControlState".
     * @return {cc.Color} The color of the title for the specified state.
     */
    getTitleColorForState: function (state) {
        var colorObject = this._titleColorDispatchTable[state];
        if (colorObject)
            return colorObject;
        colorObject = this._titleColorDispatchTable[cc.CONTROL_STATE_NORMAL];
        if (colorObject)
            return colorObject;
        return cc.color.WHITE;
    },

    /**
     * Sets the color of the title to use for the specified state.
     *
     * @param {cc.Color} color The color of the title to use for the specified state.
     * @param {Number} state The state that uses the specified color. The values are described in "CCControlState".
     */
    setTitleColorForState: function (color, state) {
        //ccColor3B* colorValue=&color;
        this._titleColorDispatchTable[state] = color;

        // If the current state if equal to the given state we update the layout
        if (this.getState() === state)
            this.needsLayout();
    },

    /**
     * Returns the title label used for a state.
     *
     * @param state The state that uses the title label. Possible values are described in "CCControlState".
     * @return {cc.Node} the title label used for a state.
     */
    getTitleLabelForState: function (state) {
        var locTable = this._titleLabelDispatchTable;
        if (locTable[state])
            return locTable[state];

        return locTable[cc.CONTROL_STATE_NORMAL];
    },

    /**
     * <p>Sets the title label to use for the specified state.                                          <br/>
     * If a property is not specified for a state, the default is to use the CCButtonStateNormal value. </p>
     *
     * @param {cc.Node} titleLabel The title label to use for the specified state.
     * @param {Number} state The state that uses the specified title. The values are described in "CCControlState".
     */
    setTitleLabelForState: function (titleLabel, state) {
        var locTable = this._titleLabelDispatchTable;
        if (locTable[state]) {
            var previousLabel = locTable[state];
            if (previousLabel)
                this.removeChild(previousLabel, true);
        }

        locTable[state] = titleLabel;
        titleLabel.setVisible(false);
        titleLabel.setAnchorPoint(0.5, 0.5);
        this.addChild(titleLabel, 1);

        // If the current state if equal to the given state we update the layout
        if (this.getState() === state)
            this.needsLayout();
    },

    /**
     * Sets the title TTF filename to use for the specified state.
     * @param {string} fntFile
     * @param {Number} state
     */
    setTitleTTFForState: function (fntFile, state) {
        var title = this.getTitleForState(state);
        if (!title)
            title = "";
        this.setTitleLabelForState(new cc.LabelTTF(title, fntFile, 12), state);
    },

    /**
     * return the title TTF filename to use for the specified state.
     * @param {Number} state
     * @returns {string}
     */
    getTitleTTFForState: function (state) {
        var labelTTF = this.getTitleLabelForState(state);
        if ((labelTTF != null) && (labelTTF instanceof  cc.LabelTTF)) {
            return labelTTF.getFontName();
        } else {
            return "";
        }
    },

    /**
     * @param {Number} size
     * @param {Number} state
     */
    setTitleTTFSizeForState: function (size, state) {
        var labelTTF = this.getTitleLabelForState(state);
        if ((labelTTF != null) && (labelTTF instanceof  cc.LabelTTF)) {
            labelTTF.setFontSize(size);
        }
    },

    /**
     * return the font size of LabelTTF to use for the specified state
     * @param {Number} state
     * @returns {Number}
     */
    getTitleTTFSizeForState: function (state) {
        var labelTTF = this.getTitleLabelForState(state);
        if ((labelTTF != null) && (labelTTF instanceof  cc.LabelTTF)) {
            return labelTTF.getFontSize();
        }
        return 0;
    },

    /**
     * Sets the font of the label, changes the label to a CCLabelBMFont if necessary.
     * @param {string} fntFile The name of the font to change to
     * @param {Number} state The state that uses the specified fntFile. The values are described in "CCControlState".
     */
    setTitleBMFontForState: function (fntFile, state) {
        var title = this.getTitleForState(state);
        if (!title)
            title = "";
        this.setTitleLabelForState(new cc.LabelBMFont(title, fntFile), state);
    },

    getTitleBMFontForState: function (state) {
        var labelBMFont = this.getTitleLabelForState(state);
        if ((labelBMFont != null) && (labelBMFont instanceof  cc.LabelBMFont)) {
            return labelBMFont.getFntFile();
        }
        return "";
    },

    /**
     * Returns the background sprite used for a state.
     *
     * @param {Number} state The state that uses the background sprite. Possible values are described in "CCControlState".
     */
    getBackgroundSpriteForState: function (state) {
        var locTable = this._backgroundSpriteDispatchTable;
        if (locTable[state]) {
            return locTable[state];
        }
        return locTable[cc.CONTROL_STATE_NORMAL];
    },

    /**
     * Sets the background sprite to use for the specified button state.
     *
     * @param {Scale9Sprite} sprite The background sprite to use for the specified state.
     * @param {Number} state The state that uses the specified image. The values are described in "CCControlState".
     */
    setBackgroundSpriteForState: function (sprite, state) {
        var locTable = this._backgroundSpriteDispatchTable;
        if (locTable[state]) {
            var previousSprite = locTable[state];
            if (previousSprite)
                this.removeChild(previousSprite, true);
        }

        locTable[state] = sprite;
        sprite.setVisible(false);
        sprite.setAnchorPoint(0.5, 0.5);
        this.addChild(sprite);

        var locPreferredSize = this._preferredSize;
        if (locPreferredSize.width !== 0 || locPreferredSize.height !== 0) {
            sprite.setPreferredSize(locPreferredSize);
        }

        // If the current state if equal to the given state we update the layout
        if (this._state === state)
            this.needsLayout();
    },

    /**
     * Sets the background spriteFrame to use for the specified button state.
     *
     * @param {SpriteFrame} spriteFrame The background spriteFrame to use for the specified state.
     * @param {Number} state The state that uses the specified image. The values are described in "CCControlState".
     */
    setBackgroundSpriteFrameForState: function (spriteFrame, state) {
        var sprite = cc.Scale9Sprite.createWithSpriteFrame(spriteFrame);
        this.setBackgroundSpriteForState(sprite, state);
    }
});

var _p = cc.ControlButton.prototype;

// Extended properties
/** @expose */
_p.adjustBackground;
cc.defineGetterSetter(_p, "adjustBackground", _p.getAdjustBackgroundImage, _p.setAdjustBackgroundImage);
/** @expose */
_p.preferredSize;
cc.defineGetterSetter(_p, "preferredSize", _p.getPreferredSize, _p.setPreferredSize);
/** @expose */
_p.labelAnchor;
cc.defineGetterSetter(_p, "labelAnchor", _p.getLabelAnchorPoint, _p.setLabelAnchorPoint);

_p = null;

/**
 * @deprecated
 * @param label
 * @param backgroundSprite
 * @param fontSize
 * @returns {ControlButton}
 */
cc.ControlButton.create = function (label, backgroundSprite, fontSize) {
    return new cc.ControlButton(label, backgroundSprite, fontSize);
};


