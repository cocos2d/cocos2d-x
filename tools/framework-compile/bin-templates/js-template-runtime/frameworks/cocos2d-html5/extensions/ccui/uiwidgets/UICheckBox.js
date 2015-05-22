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
 * The CheckBox control of Cocos UI.
 * @class
 * @extends ccui.Widget
 *
 * @property {Boolean}  selected    - Indicate whether the check box has been selected
 */
ccui.CheckBox = ccui.Widget.extend(/** @lends ccui.CheckBox# */{
    _backGroundBoxRenderer: null,
    _backGroundSelectedBoxRenderer: null,
    _frontCrossRenderer: null,
    _backGroundBoxDisabledRenderer: null,
    _frontCrossDisabledRenderer: null,

    _isSelected: true,

    _checkBoxEventListener: null,
    _checkBoxEventSelector:null,

    _backGroundTexType: ccui.Widget.LOCAL_TEXTURE,
    _backGroundSelectedTexType: ccui.Widget.LOCAL_TEXTURE,
    _frontCrossTexType: ccui.Widget.LOCAL_TEXTURE,
    _backGroundDisabledTexType: ccui.Widget.LOCAL_TEXTURE,
    _frontCrossDisabledTexType: ccui.Widget.LOCAL_TEXTURE,

    _backGroundFileName: "",
    _backGroundSelectedFileName: "",
    _frontCrossFileName: "",
    _backGroundDisabledFileName: "",
    _frontCrossDisabledFileName: "",
    _className: "CheckBox",

    _zoomScale: 0.1,
    _backgroundTextureScaleX: 0.1,
    _backgroundTextureScaleY: 0.1,

    _backGroundBoxRendererAdaptDirty:true,
    _backGroundSelectedBoxRendererAdaptDirty:true,
    _frontCrossRendererAdaptDirty: true,
    _backGroundBoxDisabledRendererAdaptDirty: true,
    _frontCrossDisabledRendererAdaptDirty: true,

    /**
     * allocates and initializes a UICheckBox.
     * Constructor of ccui.CheckBox, override it to extend the construction behavior, remember to call "this._super()" in the extended "ctor" function.
     * @param {String} backGround
     * @param {String} backGroundSelected
     * @param {String} cross
     * @param {String} backGroundDisabled
     * @param {String} frontCrossDisabled
     * @param {Number} [texType=ccui.Widget.LOCAL_TEXTURE]
     * @example
     * // example
     * var uiCheckBox = new ccui.CheckBox();
     */
    ctor: function (backGround, backGroundSelected,cross,backGroundDisabled,frontCrossDisabled,texType) {
        ccui.Widget.prototype.ctor.call(this);
        this.setTouchEnabled(true);
        var strNum = 0;
        for(var i=0; i<arguments.length; i++){
            var type = typeof arguments[i];
            if(type === "string"){
                if(isNaN(arguments[i] - 0))
                    strNum++;
                else{
                    texType = arguments[i];
                    arguments[i] = undefined;
                }

            }else if(type === "number")
                strNum++;
        }
        switch(strNum){
            case 2:
                texType = cross;
                cross = backGroundSelected;
                backGroundSelected = undefined;
        }
        texType = texType === undefined ? 0 : texType;
        this.init(backGround, backGroundSelected,cross,backGroundDisabled,frontCrossDisabled,texType);
    },

    /**
     * Initializes a checkBox. please do not call this function by yourself, you should pass the parameters to constructor to initialize it.
     * @param {String} backGround
     * @param {String} backGroundSelected
     * @param {String} cross
     * @param {String} backGroundDisabled
     * @param {String} frontCrossDisabled
     * @param {Number} [texType=ccui.Widget.LOCAL_TEXTURE]
     * @returns {boolean}
     * @override
     */
    init: function (backGround, backGroundSelected, cross, backGroundDisabled, frontCrossDisabled, texType) {
        if (ccui.Widget.prototype.init.call(this)) {
            this._isSelected = true;
            this.setSelected(false);
            this.loadTextures(backGround, backGroundSelected, cross, backGroundDisabled, frontCrossDisabled, texType);
            return true;
        }
        return false;
    },

    _initRenderer: function () {
        this._backGroundBoxRenderer = new cc.Sprite();
        this._backGroundSelectedBoxRenderer = new cc.Sprite();
        this._frontCrossRenderer = new cc.Sprite();
        this._backGroundBoxDisabledRenderer = new cc.Sprite();
        this._frontCrossDisabledRenderer = new cc.Sprite();

        this.addProtectedChild(this._backGroundBoxRenderer, ccui.CheckBox.BOX_RENDERER_ZORDER, -1);
        this.addProtectedChild(this._backGroundSelectedBoxRenderer, ccui.CheckBox.BOX_SELECTED_RENDERER_ZORDER, -1);
        this.addProtectedChild(this._frontCrossRenderer, ccui.CheckBox.FRONT_CROSS_RENDERER_ZORDER, -1);
        this.addProtectedChild(this._backGroundBoxDisabledRenderer, ccui.CheckBox.BOX_DISABLED_RENDERER_ZORDER, -1);
        this.addProtectedChild(this._frontCrossDisabledRenderer, ccui.CheckBox.FRONT_CROSS_DISABLED_RENDERER_ZORDER, -1);
    },

    /**
     * Loads textures for checkbox.
     * @param {String} backGround
     * @param {String} backGroundSelected
     * @param {String} cross
     * @param {String} backGroundDisabled
     * @param {String} frontCrossDisabled
     * @param {ccui.Widget.LOCAL_TEXTURE|ccui.Widget.PLIST_TEXTURE} texType
     */
    loadTextures: function (backGround, backGroundSelected, cross, backGroundDisabled, frontCrossDisabled, texType) {
        backGround && this.loadTextureBackGround(backGround, texType);
        backGroundSelected && this.loadTextureBackGroundSelected(backGroundSelected, texType);
        cross && this.loadTextureFrontCross(cross, texType);
        backGroundDisabled && this.loadTextureBackGroundDisabled(backGroundDisabled, texType);
        frontCrossDisabled && this.loadTextureFrontCrossDisabled(frontCrossDisabled, texType);
    },

    /**
     * Loads background texture for checkbox.
     * @param {String} backGround background filename
     * @param {ccui.Widget.LOCAL_TEXTURE|ccui.Widget.PLIST_TEXTURE} texType
     */
    loadTextureBackGround: function (backGround, texType) {
        if (!backGround)
            return;

        texType = texType || ccui.Widget.LOCAL_TEXTURE;
        this._backGroundFileName = backGround;
        this._backGroundTexType = texType;

        var bgBoxRenderer = this._backGroundBoxRenderer;
        if(!bgBoxRenderer._textureLoaded){
            bgBoxRenderer.addEventListener("load", function(){
                this._updateContentSizeWithTextureSize(this._backGroundBoxRenderer.getContentSize());
                this.loadTextureBackGround(this._backGroundFileName, this._backGroundTexType);
            }, this);
        }else{
            this._backGroundBoxRenderer.setContentSize(this._customSize);
        }

        switch (this._backGroundTexType) {
            case ccui.Widget.LOCAL_TEXTURE:
                //SetTexture cannot load resource
                bgBoxRenderer.initWithFile(backGround);
                break;
            case ccui.Widget.PLIST_TEXTURE:
                //SetTexture cannot load resource
                bgBoxRenderer.initWithSpriteFrameName(backGround);
                break;
            default:
                break;
        }

        this._updateChildrenDisplayedRGBA();

        this._updateContentSizeWithTextureSize(this._backGroundBoxRenderer.getContentSize());
        this._backGroundBoxRendererAdaptDirty = true;
        this._findLayout();
    },

    /**
     * Loads selected state of background texture for checkbox.
     * @param {String} backGroundSelected
     * @param {ccui.Widget.LOCAL_TEXTURE|ccui.Widget.PLIST_TEXTURE} texType
     */
    loadTextureBackGroundSelected: function (backGroundSelected, texType) {
        if (!backGroundSelected)
            return;

        texType = texType || ccui.Widget.LOCAL_TEXTURE;
        this._backGroundSelectedFileName = backGroundSelected;
        this._backGroundSelectedTexType = texType;

        var backGroundSelectedBoxRenderer = this._backGroundSelectedBoxRenderer;
        if(!backGroundSelectedBoxRenderer._textureLoaded){
            backGroundSelectedBoxRenderer.addEventListener("load", function(){
                this.loadTextureBackGroundSelected(this._backGroundSelectedFileName, this._backGroundSelectedTexType);
            }, this);
        }

        switch (this._backGroundSelectedTexType) {
            case ccui.Widget.LOCAL_TEXTURE:
                //SetTexture cannot load resource
                backGroundSelectedBoxRenderer.initWithFile(backGroundSelected);
                break;
            case ccui.Widget.PLIST_TEXTURE:
                //SetTexture cannot load resource
                backGroundSelectedBoxRenderer.initWithSpriteFrameName(backGroundSelected);
                break;
            default:
                break;
        }


        this._updateChildrenDisplayedRGBA();

        this._backGroundSelectedBoxRendererAdaptDirty = true;
        this._findLayout();
    },

    /**
     * Loads cross texture for checkbox.
     * @param {String} cross
     * @param {ccui.Widget.LOCAL_TEXTURE|ccui.Widget.PLIST_TEXTURE} texType
     */
    loadTextureFrontCross: function (cross, texType) {
        if (!cross)
            return;
        texType = texType || ccui.Widget.LOCAL_TEXTURE;
        this._frontCrossFileName = cross;
        this._frontCrossTexType = texType;

        var self = this;
        var frontCrossRenderer = this._frontCrossRenderer;
        if(!frontCrossRenderer._textureLoaded){
            frontCrossRenderer.addEventListener("load", function(){
                this.loadTextureFrontCross(this._frontCrossFileName, this._frontCrossTexType);
            }, this);
        }

        switch (this._frontCrossTexType) {
            case ccui.Widget.LOCAL_TEXTURE:
                //SetTexture cannot load resource
                frontCrossRenderer.initWithFile(cross);
                break;
            case ccui.Widget.PLIST_TEXTURE:
                //SetTexture cannot load resource
                frontCrossRenderer.initWithSpriteFrameName(cross);
                break;
            default:
                break;
        }

        this._updateChildrenDisplayedRGBA();

        this._frontCrossRendererAdaptDirty = true;
        this._findLayout();
    },

    /**
     * Loads disabled state of backGround texture for checkbox.
     * @param {String} backGroundDisabled
     * @param {ccui.Widget.LOCAL_TEXTURE|ccui.Widget.PLIST_TEXTURE} texType
     */
    loadTextureBackGroundDisabled: function (backGroundDisabled, texType) {
        if (!backGroundDisabled)
            return;
        texType = texType || ccui.Widget.LOCAL_TEXTURE;
        this._backGroundDisabledFileName = backGroundDisabled;
        this._backGroundDisabledTexType = texType;

        var self = this;
        var backGroundBoxDisabledRenderer = this._backGroundBoxDisabledRenderer;
        if(!backGroundBoxDisabledRenderer._textureLoaded){
            backGroundBoxDisabledRenderer.addEventListener("load", function(){
                this.loadTextureBackGroundDisabled(this._backGroundDisabledFileName, this._backGroundDisabledTexType);
            }, this);
        }

        switch (this._backGroundDisabledTexType) {
            case ccui.Widget.LOCAL_TEXTURE:
                //SetTexture cannot load resource
                backGroundBoxDisabledRenderer.initWithFile(backGroundDisabled);
                break;
            case ccui.Widget.PLIST_TEXTURE:
                //SetTexture cannot load resource
                backGroundBoxDisabledRenderer.initWithSpriteFrameName(backGroundDisabled);
                break;
            default:
                break;
        }

        this._updateChildrenDisplayedRGBA();

        this._backGroundBoxDisabledRendererAdaptDirty = true;
        this._findLayout();
    },

    /**
     * Loads frontCrossDisabled texture for checkbox.
     * @param {String} frontCrossDisabled
     * @param {ccui.Widget.LOCAL_TEXTURE|ccui.Widget.PLIST_TEXTURE} texType
     */
    loadTextureFrontCrossDisabled: function (frontCrossDisabled, texType) {
        if (!frontCrossDisabled)
            return;
        texType = texType || ccui.Widget.LOCAL_TEXTURE;
        this._frontCrossDisabledFileName = frontCrossDisabled;
        this._frontCrossDisabledTexType = texType;

        var self = this;
        var frontCrossDisabledRenderer = this._frontCrossDisabledRenderer;
        if(!frontCrossDisabledRenderer._textureLoaded){
            frontCrossDisabledRenderer.addEventListener("load", function(){
                this.loadTextureFrontCrossDisabled(this._frontCrossDisabledFileName, this._frontCrossDisabledTexType);
            }, this);
        }

        switch (this._frontCrossDisabledTexType) {
            case ccui.Widget.LOCAL_TEXTURE:
                //SetTexture cannot load resource
                frontCrossDisabledRenderer.initWithFile(frontCrossDisabled);
                break;
            case ccui.Widget.PLIST_TEXTURE:
                //SetTexture cannot load resource
                frontCrossDisabledRenderer.initWithSpriteFrameName(frontCrossDisabled);
                break;
            default:
                break;
        }

        this._updateChildrenDisplayedRGBA();

        this._frontCrossDisabledRendererAdaptDirty = true;
        this._findLayout();
    },

    _onPressStateChangedToNormal: function () {
        this._backGroundBoxRenderer.setVisible(true);
        this._backGroundSelectedBoxRenderer.setVisible(false);
        this._backGroundBoxDisabledRenderer.setVisible(false);
        this._frontCrossDisabledRenderer.setVisible(false);

        this._backGroundBoxRenderer.setScale(this._backgroundTextureScaleX, this._backgroundTextureScaleY);
        this._frontCrossRenderer.setScale(this._backgroundTextureScaleX, this._backgroundTextureScaleY);

        if (this._isSelected)
            this._frontCrossRenderer.setVisible(true);
    },

    _onPressStateChangedToPressed: function () {
        if (!this._backGroundSelectedFileName){
            this._backGroundBoxRenderer.setScale(this._backgroundTextureScaleX + this._zoomScale, this._backgroundTextureScaleY + this._zoomScale);
            this._frontCrossRenderer.setScale(this._backgroundTextureScaleX + this._zoomScale, this._backgroundTextureScaleY + this._zoomScale);
        }else{
            this._backGroundBoxRenderer.setVisible(false);
            this._backGroundSelectedBoxRenderer.setVisible(true);
            this._backGroundBoxDisabledRenderer.setVisible(false);
            this._frontCrossDisabledRenderer.setVisible(false);
        }
    },

    _onPressStateChangedToDisabled: function () {
        if (this._backGroundDisabledFileName && this._frontCrossDisabledFileName){
            this._backGroundBoxRenderer.setVisible(false);
            this._backGroundBoxDisabledRenderer.setVisible(true);
        }

        this._backGroundSelectedBoxRenderer.setVisible(false);
        this._frontCrossRenderer.setVisible(false);
        this._backGroundBoxRenderer.setScale(this._backgroundTextureScaleX, this._backgroundTextureScaleY);
        this._frontCrossRenderer.setScale(this._backgroundTextureScaleX, this._backgroundTextureScaleY);

        if (this._isSelected) {
            this._frontCrossDisabledRenderer.setVisible(true);
        }
    },

    setZoomScale: function(scale){
        this._zoomScale = scale;
    },

    getZoomScale: function(){
        return this._zoomScale;
    },

    /**
     * @deprecated since v3.1, please use setSelected.
     */
    setSelectedState: function(selected){
        this.setSelected(selected);
    },

    /**
     * Sets the selected state to ccui.CheckBox
     * @param {Boolean} selected
     */
    setSelected: function (selected) {
        if (selected === this._isSelected)
            return;
        this._isSelected = selected;
        this._frontCrossRenderer.setVisible(this._isSelected);
    },

    /**
     * @deprecated since v3.1, please use isSelected.
     */
    getSelectedState: function(){
        return this.isSelected();
    },

    /**
     * Returns the selected state of ccui.CheckBox.
     * @returns {boolean}
     */
    isSelected: function () {
        return this._isSelected;
    },

    _selectedEvent: function () {
        if(this._checkBoxEventSelector){
            if (this._checkBoxEventListener)
                this._checkBoxEventSelector.call(this._checkBoxEventListener, this, ccui.CheckBox.EVENT_SELECTED);
            else
                this._checkBoxEventSelector(this, ccui.CheckBox.EVENT_SELECTED);
        }
    },

    _unSelectedEvent: function () {
        if(this._checkBoxEventSelector){
            if (this._checkBoxEventListener)
                this._checkBoxEventSelector.call(this._checkBoxEventListener, this, ccui.CheckBox.EVENT_UNSELECTED);
            else
                this._checkBoxEventSelector(this, ccui.CheckBox.EVENT_UNSELECTED);
        }
    },

    _releaseUpEvent: function(){
        ccui.Widget.prototype._releaseUpEvent.call(this);
        if (this._isSelected){
            this.setSelected(false);
            this._unSelectedEvent();
        } else {
            this.setSelected(true);
            this._selectedEvent();
        }
    },

    /**
     * add event listener to ccui.CheckBox. it would called when checkbox is selected or unselected.
     * @param {Function} selector
     * @param {Object} [target=]
     * @deprecated since v3.0, please use addEventListener instead.
     */
    addEventListenerCheckBox: function (selector, target) {
        this.addEventListener(selector, target);
    },

    /**
     * add a call back function would called when checkbox is selected or unselected.
     * @param {Function} selector
     * @param {Object} [target=]
     */
    addEventListener: function(selector, target){
        this._checkBoxEventSelector = selector;
        this._checkBoxEventListener = target;
    },

    /**
     * Returns the content size of Renderer.
     * @returns {cc.Size}
     */
    getVirtualRendererSize: function(){
        return this._backGroundBoxRenderer.getContentSize();
    },

    _onSizeChanged: function () {
        ccui.Widget.prototype._onSizeChanged.call(this);
        this._backGroundBoxRendererAdaptDirty = true;
        this._backGroundSelectedBoxRendererAdaptDirty = true;
        this._frontCrossRendererAdaptDirty = true;
        this._backGroundBoxDisabledRendererAdaptDirty = true;
        this._frontCrossDisabledRendererAdaptDirty = true;
    },

    /**
     * override "getVirtualRenderer" method of widget.
     * @override
     * @returns {cc.Node} the renderer of ccui.CheckBox.
     */
    getVirtualRenderer: function () {
        return this._backGroundBoxRenderer;
    },

    _backGroundTextureScaleChangedWithSize: function () {
        var locRenderer = this._backGroundBoxRenderer, locContentSize = this._contentSize;
        if (this._ignoreSize){
            locRenderer.setScale(1.0);
            this._backgroundTextureScaleX = this._backgroundTextureScaleY = 1;
        }else{
            var textureSize = locRenderer.getContentSize();
            if (textureSize.width <= 0.0 || textureSize.height <= 0.0){
                locRenderer.setScale(1.0);
                this._backgroundTextureScaleX = this._backgroundTextureScaleY = 1;
                return;
            }
            var scaleX = locContentSize.width / textureSize.width;
            var scaleY = locContentSize.height / textureSize.height;
            this._backgroundTextureScaleX = scaleX;
            this._backgroundTextureScaleY = scaleY;
            locRenderer.setScaleX(scaleX);
            locRenderer.setScaleY(scaleY);
        }
        locRenderer.setPosition(locContentSize.width * 0.5, locContentSize.height * 0.5);
    },

    _backGroundSelectedTextureScaleChangedWithSize: function () {
        var locRenderer = this._backGroundSelectedBoxRenderer, locContentSize = this._contentSize;
        if (this._ignoreSize)
            locRenderer.setScale(1.0);
        else {
            var textureSize = locRenderer.getContentSize();
            if (textureSize.width <= 0.0 || textureSize.height <= 0.0) {
                locRenderer.setScale(1.0);
                return;
            }
            var scaleX = locContentSize.width / textureSize.width;
            var scaleY = locContentSize.height / textureSize.height;
            locRenderer.setScaleX(scaleX);
            locRenderer.setScaleY(scaleY);
        }
        locRenderer.setPosition(locContentSize.width * 0.5, locContentSize.height * 0.5);
    },

    _frontCrossTextureScaleChangedWithSize: function () {
        var locRenderer = this._frontCrossRenderer, locContentSize = this._contentSize;
        if (this._ignoreSize)
            locRenderer.setScale(1.0);
        else {
            var textureSize = locRenderer.getContentSize();
            if (textureSize.width <= 0.0 || textureSize.height <= 0.0) {
                locRenderer.setScale(1.0);
                return;
            }
            var scaleX = locContentSize.width / textureSize.width;
            var scaleY = locContentSize.height / textureSize.height;
            locRenderer.setScaleX(scaleX);
            locRenderer.setScaleY(scaleY);
        }
        locRenderer.setPosition(locContentSize.width * 0.5, locContentSize.height * 0.5);
    },

    _backGroundDisabledTextureScaleChangedWithSize: function () {
        var locRenderer = this._backGroundBoxDisabledRenderer, locContentSize = this._contentSize;
        if (this._ignoreSize)
            locRenderer.setScale(1.0);
        else {
            var textureSize = locRenderer.getContentSize();
            if (textureSize.width <= 0.0 || textureSize.height <= 0.0) {
                locRenderer.setScale(1.0);
                return;
            }
            var scaleX = locContentSize.width / textureSize.width;
            var scaleY = locContentSize.height / textureSize.height;
            locRenderer.setScaleX(scaleX);
            locRenderer.setScaleY(scaleY);
        }
        locRenderer.setPosition(locContentSize.width * 0.5, locContentSize.height * 0.5);
    },

    _frontCrossDisabledTextureScaleChangedWithSize: function () {
        var locRenderer = this._frontCrossDisabledRenderer, locContentSize = this._contentSize;
        if (this._ignoreSize) {
            locRenderer.setScale(1.0);
        } else {
            var textureSize = locRenderer.getContentSize();
            if (textureSize.width <= 0.0 || textureSize.height <= 0.0) {
                locRenderer.setScale(1.0);
                return;
            }
            var scaleX = locContentSize.width / textureSize.width;
            var scaleY = locContentSize.height / textureSize.height;
            locRenderer.setScaleX(scaleX);
            locRenderer.setScaleY(scaleY);
        }
        locRenderer.setPosition(locContentSize.width * 0.5, locContentSize.height * 0.5);
    },

    /**
     * Returns the "class name" of widget.
     * @override
     * @returns {string}
     */
    getDescription: function () {
        return "CheckBox";
    },

    _createCloneInstance: function () {
        return new ccui.CheckBox();
    },

    _copySpecialProperties: function (uiCheckBox) {
        if (uiCheckBox instanceof ccui.CheckBox) {
            this.loadTextureBackGround(uiCheckBox._backGroundFileName, uiCheckBox._backGroundTexType);
            this.loadTextureBackGroundSelected(uiCheckBox._backGroundSelectedFileName, uiCheckBox._backGroundSelectedTexType);
            this.loadTextureFrontCross(uiCheckBox._frontCrossFileName, uiCheckBox._frontCrossTexType);
            this.loadTextureBackGroundDisabled(uiCheckBox._backGroundDisabledFileName, uiCheckBox._backGroundDisabledTexType);
            this.loadTextureFrontCrossDisabled(uiCheckBox._frontCrossDisabledFileName, uiCheckBox._frontCrossDisabledTexType);
            this.setSelected(uiCheckBox._isSelected);
            this._checkBoxEventListener = uiCheckBox._checkBoxEventListener;
            this._checkBoxEventSelector = uiCheckBox._checkBoxEventSelector;
            this._ccEventCallback = uiCheckBox._ccEventCallback;
            this._zoomScale = uiCheckBox._zoomScale;
            this._backgroundTextureScaleX = uiCheckBox._backgroundTextureScaleX;
            this._backgroundTextureScaleY = uiCheckBox._backgroundTextureScaleY;
        }
    },

    _adaptRenderers: function(){
        if (this._backGroundBoxRendererAdaptDirty){
            this._backGroundTextureScaleChangedWithSize();
            this._backGroundBoxRendererAdaptDirty = false;
        }
        if (this._backGroundSelectedBoxRendererAdaptDirty) {
            this._backGroundSelectedTextureScaleChangedWithSize();
            this._backGroundSelectedBoxRendererAdaptDirty = false;
        }
        if (this._frontCrossRendererAdaptDirty){
            this._frontCrossTextureScaleChangedWithSize();
            this._frontCrossRendererAdaptDirty = false;
        }
        if (this._backGroundBoxDisabledRendererAdaptDirty) {
            this._backGroundDisabledTextureScaleChangedWithSize();
            this._backGroundBoxDisabledRendererAdaptDirty = false;
        }
        if (this._frontCrossDisabledRendererAdaptDirty) {
            this._frontCrossDisabledTextureScaleChangedWithSize();
            this._frontCrossDisabledRendererAdaptDirty = false;
        }
    }
});

var _p = ccui.CheckBox.prototype;

// Extended properties
/** @expose */
_p.selected;
cc.defineGetterSetter(_p, "selected", _p.isSelected, _p.setSelected);

_p = null;

/**
 * allocates and initializes a UICheckBox.
 * @deprecated since v3.0, please use new ccui.CheckBox() instead.
 * @param {string} [backGround]     backGround texture.
 * @param {string} [backGroundSeleted]  backGround selected state texture.
 * @param {string} [cross]  cross texture.
 * @param {string} [backGroundDisabled]   cross dark state texture.
 * @param {string} [frontCrossDisabled]   cross dark state texture.
 * @param {Number} [texType]
 * @return {ccui.CheckBox}
 * @example
 * // example
 * var uiCheckBox = new ccui.CheckBox();
 */
ccui.CheckBox.create = function (backGround, backGroundSeleted, cross, backGroundDisabled, frontCrossDisabled, texType) {
    return new ccui.CheckBox(backGround, backGroundSeleted,cross,backGroundDisabled,frontCrossDisabled,texType);
};

// Constants
//CheckBoxEvent type
/**
 * The selected state of ccui.CheckBox's event.
 * @constant
 * @type {number}
 */
ccui.CheckBox.EVENT_SELECTED = 0;
/**
 * The unselected state of ccui.CheckBox's event.
 * @constant
 * @type {number}
 */
ccui.CheckBox.EVENT_UNSELECTED = 1;

//Render zorder
/**
 * The normal background renderer's zOrder
 * @constant
 * @type {number}
 */
ccui.CheckBox.BOX_RENDERER_ZORDER = -1;
/**
 * The selected Background renderer's zOrder
 * @constant
 * @type {number}
 */
ccui.CheckBox.BOX_SELECTED_RENDERER_ZORDER = -1;
/**
 * The disabled Background renderer's zOrder
 * @constant
 * @type {number}
 */
ccui.CheckBox.BOX_DISABLED_RENDERER_ZORDER = -1;
/**
 * The normal front renderer's zOrder
 * @constant
 * @type {number}
 */
ccui.CheckBox.FRONT_CROSS_RENDERER_ZORDER = -1;
/**
 * The disabled front renderer's zOrder
 * @constant
 * @type {number}
 */
ccui.CheckBox.FRONT_CROSS_DISABLED_RENDERER_ZORDER = -1;
