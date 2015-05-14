/****************************************************************************
 Copyright (c) 2008-2010 Ricardo Quesada
 Copyright (c) 2011-2012 cocos2d-x.org
 Copyright (c) 2013-2014 Chukong Technologies Inc.
 Copyright (c) 2009      Jason Booth

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
 * enum for jpg
 * @constant
 * @type Number
 */
cc.IMAGE_FORMAT_JPEG = 0;
/**
 * enum for png
 * @constant
 * @type Number
 */
cc.IMAGE_FORMAT_PNG = 1;
/**
 * enum for raw
 * @constant
 * @type Number
 */
cc.IMAGE_FORMAT_RAWDATA = 9;

/**
 * @param {Number} x
 * @return {Number}
 * Constructor
 */
cc.NextPOT = function (x) {
    x = x - 1;
    x = x | (x >> 1);
    x = x | (x >> 2);
    x = x | (x >> 4);
    x = x | (x >> 8);
    x = x | (x >> 16);
    return x + 1;
};

/**
 * cc.RenderTexture is a generic rendering target. To render things into it,<br/>
 * simply construct a render target, call begin on it, call visit on any cocos<br/>
 * scenes or objects to render them, and call end. For convenience, render texture<br/>
 * adds a sprite as it's display child with the results, so you can simply add<br/>
 * the render texture to your scene and treat it like any other CocosNode.<br/>
 * There are also functions for saving the render texture to disk in PNG or JPG format.
 * @class
 * @extends cc.Node
 *
 * @property {cc.Sprite}    sprite          - The sprite.
 * @property {cc.Sprite}    clearFlags      - Code for "auto" update.
 * @property {Number}       clearDepthVal   - Clear depth value.
 * @property {Boolean}      autoDraw        - Indicate auto draw mode activate or not.
 * @property {Number}       clearStencilVal - Clear stencil value.
 * @property {cc.Color}     clearColorVal   - Clear color value, valid only when "autoDraw" is true.
 */
cc.RenderTexture = cc.Node.extend(/** @lends cc.RenderTexture# */{
	sprite:null,

	//
	// <p>Code for "auto" update<br/>
	// Valid flags: GL_COLOR_BUFFER_BIT, GL_DEPTH_BUFFER_BIT, GL_STENCIL_BUFFER_BIT.<br/>
	// They can be OR'ed. Valid when "autoDraw is YES.</p>
	// @public
	//
	clearFlags:0,

	clearDepthVal:0,
	autoDraw:false,

    _texture:null,
    _pixelFormat:cc.Texture2D.PIXEL_FORMAT_RGBA8888,

    clearStencilVal:0,
    _clearColor:null,

    _className:"RenderTexture",

    /**
     * creates a RenderTexture object with width and height in Points and a pixel format, only RGB and RGBA formats are valid
     * Constructor of cc.RenderTexture for Canvas
     * @param {Number} width
     * @param {Number} height
     * @param {cc.IMAGE_FORMAT_JPEG|cc.IMAGE_FORMAT_PNG|cc.IMAGE_FORMAT_RAWDATA} format
     * @param {Number} depthStencilFormat
     * @example
     * // Example
     * var rt = new cc.RenderTexture(width, height, format, depthStencilFormat)
     * @function
     */
    ctor: function(width, height, format, depthStencilFormat){
        cc.Node.prototype.ctor.call(this);
        this._cascadeColorEnabled = true;
        this._cascadeOpacityEnabled = true;
        this._clearColor = new cc.Color(0,0,0,255);

        if(width !== undefined && height !== undefined) {
            format = format || cc.Texture2D.PIXEL_FORMAT_RGBA8888;
            depthStencilFormat = depthStencilFormat || 0;
            this.initWithWidthAndHeight(width, height, format, depthStencilFormat);
        }
        this.setAnchorPoint(0,0);
    },

    _createRenderCmd: function(){
        if(cc._renderType === cc._RENDER_TYPE_CANVAS)
            return new cc.RenderTexture.CanvasRenderCmd(this);
        else
            return new cc.RenderTexture.WebGLRenderCmd(this);
    },

    /**
     * Clear RenderTexture.
     * @function
     */
    cleanup: function(){
        cc.Node.prototype.onExit.call(this);
        this._renderCmd.cleanup();
    },

    /**
     * Gets the sprite
     * @return {cc.Sprite}
     */
    getSprite:function () {
        return this.sprite;
    },

    /**
     * Set the sprite
     * @param {cc.Sprite} sprite
     */
    setSprite:function (sprite) {
        this.sprite = sprite;
    },

    /**
     * Used for grab part of screen to a texture.
     * @param {cc.Point} rtBegin
     * @param {cc.Rect} fullRect
     * @param {cc.Rect} fullViewport
     */
    setVirtualViewport: function(rtBegin, fullRect, fullViewport){
         this._renderCmd.setVirtualViewport(rtBegin, fullRect, fullViewport);
    },

    /**
     * Initializes the instance of cc.RenderTexture
     * @function
     * @param {Number} width
     * @param {Number} height
     * @param {cc.IMAGE_FORMAT_JPEG|cc.IMAGE_FORMAT_PNG|cc.IMAGE_FORMAT_RAWDATA} [format]
     * @param {Number} [depthStencilFormat]
     * @return {Boolean}
     */
    initWithWidthAndHeight: function(width, height, format, depthStencilFormat){
        return this._renderCmd.initWithWidthAndHeight(width, height, format, depthStencilFormat);
    },

    /**
     * starts grabbing
     * @function
     */
    begin: function(){
        cc.renderer._turnToCacheMode(this.__instanceId);
        this._renderCmd.begin();
    },
    /**
     * starts rendering to the texture while clearing the texture first.<br/>
     * This is more efficient then calling -clear first and then -begin
     * @param {Number} r red 0-255
     * @param {Number} g green 0-255
     * @param {Number} b blue 0-255
     * @param {Number} a alpha 0-255 0 is transparent
     * @param {Number} [depthValue=]
     * @param {Number} [stencilValue=]
     */
    beginWithClear:function (r, g, b, a, depthValue, stencilValue) {
        //todo: only for WebGL?
        var gl = cc._renderContext;
        depthValue = depthValue || gl.COLOR_BUFFER_BIT;
        stencilValue = stencilValue || (gl.COLOR_BUFFER_BIT | gl.DEPTH_BUFFER_BIT);

        this._beginWithClear(r , g , b , a , depthValue, stencilValue, (gl.COLOR_BUFFER_BIT | gl.DEPTH_BUFFER_BIT | gl.STENCIL_BUFFER_BIT));
    },

    _beginWithClear: function(r, g, b, a, depthValue, stencilValue, flags){
        this.begin();
        this._renderCmd._beginWithClear(r, g, b, a, depthValue, stencilValue, flags);
    },

    /**
     * ends grabbing
     * @function
     */
    end: function(){
        this._renderCmd.end();
    },

    /**
     * clears the texture with a color
     * @param {Number|cc.Rect} r red 0-1
     * @param {Number} g green 0-1
     * @param {Number} b blue 0-1
     * @param {Number} a alpha 0-1
     */
    clear:function (r, g, b, a) {
        this.beginWithClear(r, g, b, a);
        this.end();
    },

    /**
     * clears the texture with rect.
     * @function
     * @param {number} x
     * @param {number} y
     * @param {number} width
     * @param {number} height
     */
    clearRect: function(x, y, width, height){
        this._renderCmd.clearRect(x, y, width, height);
    },

    /**
     * clears the texture with a specified depth value
     * @function
     * @param {Number} depthValue
     */
    clearDepth: function(depthValue){
        this._renderCmd.clearDepth(depthValue);
    },

    /**
     * clears the texture with a specified stencil value
     * @function
     * @param {Number} stencilValue
     */
    clearStencil: function(stencilValue) {
        this._renderCmd.clearStencil(stencilValue);
    },

    /**
     * Valid flags: GL_COLOR_BUFFER_BIT, GL_DEPTH_BUFFER_BIT, GL_STENCIL_BUFFER_BIT. They can be OR'ed. Valid when "autoDraw is YES.
     * @return {Number}
     */
    getClearFlags:function () {
        return this.clearFlags;
    },

    /**
     * Set the clearFlags
     * @param {Number} clearFlags
     */
    setClearFlags:function (clearFlags) {
        this.clearFlags = clearFlags;
    },

    /**
     * Clear color value. Valid only when "autoDraw" is true.
     * @function
     * @return {cc.Color}
     */
    getClearColor:function () {
        return this._clearColor;
    },

	/**
	 * Set the clear color value. Valid only when "autoDraw" is true.
	 * @function
	 * @param {cc.Color} clearColor The clear color
	 */
    setClearColor: function(clearColor){
        var locClearColor = this._clearColor;
        locClearColor.r = clearColor.r;
        locClearColor.g = clearColor.g;
        locClearColor.b = clearColor.b;
        locClearColor.a = clearColor.a;
        this._renderCmd.updateClearColor(clearColor);
    },

    /**
     * Value for clearDepth. Valid only when autoDraw is true.
     * @return {Number}
     */
    getClearDepth:function () {
        return this.clearDepthVal;
    },

    /**
     * Set value for clearDepth. Valid only when autoDraw is true.
     * @param {Number} clearDepth
     */
    setClearDepth:function (clearDepth) {
        this.clearDepthVal = clearDepth;
    },

    /**
     * Value for clear Stencil. Valid only when autoDraw is true
     * @return {Number}
     */
    getClearStencil:function () {
        return this.clearStencilVal;
    },

    /**
     * Set value for clear Stencil. Valid only when autoDraw is true
     * @return {Number}
     */
    setClearStencil:function (clearStencil) {
        this.clearStencilVal = clearStencil;
    },

    /**
     * When enabled, it will render its children into the texture automatically. Disabled by default for compatiblity reasons. <br/>
     * Will be enabled in the future.
     * @return {Boolean}
     */
    isAutoDraw:function () {
        return this.autoDraw;
    },

    /**
     * When enabled, it will render its children into the texture automatically. Disabled by default for compatiblity reasons. <br/>
     * Will be enabled in the future.
     * @return {Boolean}
     */
    setAutoDraw:function (autoDraw) {
        this.autoDraw = autoDraw;
    },

    //---- some stub functions for jsb
    /**
     * saves the texture into a file using JPEG format. The file will be saved in the Documents folder.
     * Returns YES if the operation is successful.
     * (doesn't support in HTML5)
     * @param {Number} filePath
     * @param {Number} format
     */
    saveToFile:function (filePath, format) {
        cc.log("saveToFile isn't supported on Cocos2d-Html5");
    },

    /**
     * creates a new CCImage from with the texture's data. Caller is responsible for releasing it by calling delete.
     * @return {*}
     */
    newCCImage:function(flipImage){
        cc.log("saveToFile isn't supported on cocos2d-html5");
        return null;
    },

    /**
     * Listen "come to background" message, and save render texture. It only has effect on Android.
     * @param {cc.Class} obj
     */
    listenToBackground:function (obj) { },

    /**
     * Listen "come to foreground" message and restore the frame buffer object. It only has effect on Android.
     * @param {cc.Class} obj
     */
    listenToForeground:function (obj) { }
});

var _p = cc.RenderTexture.prototype;
// Extended
/** @expose */
_p.clearColorVal;
cc.defineGetterSetter(_p, "clearColorVal", _p.getClearColor, _p.setClearColor);


/**
 * creates a RenderTexture object with width and height in Points and a pixel format, only RGB and RGBA formats are valid
 * @deprecated since v3.0 please use new cc.RenderTexture() instead.
 * @param {Number} width
 * @param {Number} height
 * @param {cc.IMAGE_FORMAT_JPEG|cc.IMAGE_FORMAT_PNG|cc.IMAGE_FORMAT_RAWDATA} format
 * @param {Number} depthStencilFormat
 * @return {cc.RenderTexture}
 */
cc.RenderTexture.create = function (width, height, format, depthStencilFormat) {
    return new cc.RenderTexture(width, height, format, depthStencilFormat);
};
