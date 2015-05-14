/****************************************************************************
 Copyright (c) 2008-2010 Ricardo Quesada
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

//CONSTANTS:

/**
 * Horizontal center and vertical center.
 * @constant
 * @type Number
 */
cc.ALIGN_CENTER = 0x33;

/**
 * Horizontal center and vertical top.
 * @constant
 * @type Number
 */
cc.ALIGN_TOP = 0x13;

/**
 * Horizontal right and vertical top.
 * @constant
 * @type Number
 */
cc.ALIGN_TOP_RIGHT = 0x12;

/**
 * Horizontal right and vertical center.
 * @constant
 * @type Number
 */
cc.ALIGN_RIGHT = 0x32;

/**
 * Horizontal right and vertical bottom.
 * @constant
 * @type Number
 */
cc.ALIGN_BOTTOM_RIGHT = 0x22;

/**
 * Horizontal center and vertical bottom.
 * @constant
 * @type Number
 */
cc.ALIGN_BOTTOM = 0x23;

/**
 * Horizontal left and vertical bottom.
 * @constant
 * @type Number
 */
cc.ALIGN_BOTTOM_LEFT = 0x21;

/**
 * Horizontal left and vertical center.
 * @constant
 * @type Number
 */
cc.ALIGN_LEFT = 0x31;

/**
 * Horizontal left and vertical top.
 * @constant
 * @type Number
 */
cc.ALIGN_TOP_LEFT = 0x11;
//----------------------Possible texture pixel formats----------------------------


// By default PVR images are treated as if they don't have the alpha channel premultiplied
cc.PVRHaveAlphaPremultiplied_ = false;

//cc.Texture2DWebGL move to TextureWebGL.js

if (cc._renderType === cc._RENDER_TYPE_CANVAS) {

    /**
     * <p>
     * This class allows to easily create OpenGL or Canvas 2D textures from images, text or raw data.                                    <br/>
     * The created cc.Texture2D object will always have power-of-two dimensions.                                                <br/>
     * Depending on how you create the cc.Texture2D object, the actual image area of the texture might be smaller than the texture dimensions <br/>
     *  i.e. "contentSize" != (pixelsWide, pixelsHigh) and (maxS, maxT) != (1.0, 1.0).                                           <br/>
     * Be aware that the content of the generated textures will be upside-down! </p>
     * @name cc.Texture2D
     * @class
     * @extends cc.Class
     *
     * @property {WebGLTexture}     name            - <@readonly> WebGLTexture Object
     * @property {Number}           defaultPixelFormat - The default pixel format
     * @property {Number}           pixelFormat     - <@readonly> Pixel format of the texture
     * @property {Number}           pixelsWidth     - <@readonly> Width in pixels
     * @property {Number}           pixelsHeight    - <@readonly> Height in pixels
     * @property {Number}           width           - Content width in points
     * @property {Number}           height          - Content height in points
     * @property {cc.GLProgram}     shaderProgram   - The shader program used by drawAtPoint and drawInRect
     * @property {Number}           maxS            - Texture max S
     * @property {Number}           maxT            - Texture max T
     */
    cc.Texture2D = cc.Class.extend(/** @lends cc.Texture2D# */{
        _contentSize: null,
        _textureLoaded: false,
        _htmlElementObj: null,
        url: null,
        _pattern: null,

        ctor: function () {
            this._contentSize = cc.size(0, 0);
            this._textureLoaded = false;
            this._htmlElementObj = null;
            this._pattern = "";
        },

        /**
         * get width in pixels
         * @return {Number}
         */
        getPixelsWide: function () {
            return this._contentSize.width;
        },

        /**
         * get height of in pixels
         * @return {Number}
         */
        getPixelsHigh: function () {
            return this._contentSize.height;
        },

        /**
         * get content size
         * @returns {cc.Size}
         */
        getContentSize: function () {
            var locScaleFactor = cc.contentScaleFactor();
            return cc.size(this._contentSize.width / locScaleFactor, this._contentSize.height / locScaleFactor);
        },

        _getWidth: function () {
            return this._contentSize.width / cc.contentScaleFactor();
        },
        _getHeight: function () {
            return this._contentSize.height / cc.contentScaleFactor();
        },

        /**
         * get content size in pixels
         * @returns {cc.Size}
         */
        getContentSizeInPixels: function () {
            return this._contentSize;
        },

        /**
         * init with HTML element
         * @param {HTMLImageElement|HTMLCanvasElement} element
         */
        initWithElement: function (element) {
            if (!element)
                return;
            this._htmlElementObj = element;
            this._contentSize.width = element.width;
            this._contentSize.height = element.height;
            this._textureLoaded = true;
        },

        /**
         * HTMLElement Object getter
         * @return {HTMLImageElement|HTMLCanvasElement}
         */
        getHtmlElementObj: function () {
            return this._htmlElementObj;
        },

        /**
         * check whether texture is loaded
         * @returns {boolean}
         */
        isLoaded: function () {
            return this._textureLoaded;
        },

        /**
         * handle loaded texture
         */
        handleLoadedTexture: function () {
            var self = this;
            if (self._textureLoaded) return;
            if (!self._htmlElementObj) {
                var img = cc.loader.getRes(self.url);
                if (!img) return;
                self.initWithElement(img);
            }

            var locElement = self._htmlElementObj;
            self._contentSize.width = locElement.width;
            self._contentSize.height = locElement.height;

            //dispatch load event to listener.
            self.dispatchEvent("load");
        },

        /**
         * description of cc.Texture2D
         * @returns {string}
         */
        description: function () {
            return "<cc.Texture2D | width = " + this._contentSize.width + " height " + this._contentSize.height + ">";
        },

        initWithData: function (data, pixelFormat, pixelsWide, pixelsHigh, contentSize) {
            //support only in WebGl rendering mode
            return false;
        },

        initWithImage: function (uiImage) {
            //support only in WebGl rendering mode
            return false;
        },

        initWithString: function (text, fontName, fontSize, dimensions, hAlignment, vAlignment) {
            //support only in WebGl rendering mode
            return false;
        },

        releaseTexture: function () {
            cc.loader.release(this.url);
        },

        getName: function () {
            //support only in WebGl rendering mode
            return null;
        },

        getMaxS: function () {
            //support only in WebGl rendering mode
            return 1;
        },

        setMaxS: function (maxS) {
            //support only in WebGl rendering mode
        },

        getMaxT: function () {
            return 1;
        },

        setMaxT: function (maxT) {
            //support only in WebGl rendering mode
        },

        getPixelFormat: function () {
            //support only in WebGl rendering mode
            return null;
        },

        getShaderProgram: function () {
            //support only in WebGl rendering mode
            return null;
        },

        setShaderProgram: function (shaderProgram) {
            //support only in WebGl rendering mode
        },

        hasPremultipliedAlpha: function () {
            //support only in WebGl rendering mode
            return false;
        },

        hasMipmaps: function () {
            //support only in WebGl rendering mode
            return false;
        },

        releaseData: function (data) {
            //support only in WebGl rendering mode
            data = null;
        },

        keepData: function (data, length) {
            //support only in WebGl rendering mode
            return data;
        },

        drawAtPoint: function (point) {
            //support only in WebGl rendering mode
        },

        drawInRect: function (rect) {
            //support only in WebGl rendering mode
        },

        /**
         * init with ETC file
         * @warning does not support on HTML5
         */
        initWithETCFile: function (file) {
            cc.log(cc._LogInfos.Texture2D_initWithETCFile);
            return false;
        },

        /**
         * init with PVR file
         * @warning does not support on HTML5
         */
        initWithPVRFile: function (file) {
            cc.log(cc._LogInfos.Texture2D_initWithPVRFile);
            return false;
        },

        /**
         * init with PVRTC data
         * @warning does not support on HTML5
         */
        initWithPVRTCData: function (data, level, bpp, hasAlpha, length, pixelFormat) {
            cc.log(cc._LogInfos.Texture2D_initWithPVRTCData);
            return false;
        },

        setTexParameters: function (texParams, magFilter, wrapS, wrapT) {
            if(magFilter !== undefined)
                texParams = {minFilter: texParams, magFilter: magFilter, wrapS: wrapS, wrapT: wrapT};

            if(texParams.wrapS === cc.REPEAT && texParams.wrapT === cc.REPEAT){
                this._pattern = "repeat";
                return;
            }

            if(texParams.wrapS === cc.REPEAT ){
                this._pattern = "repeat-x";
                return;
            }

            if(texParams.wrapT === cc.REPEAT){
                this._pattern = "repeat-y";
                return;
            }

            this._pattern = "";
        },

        setAntiAliasTexParameters: function () {
            //support only in WebGl rendering mode
        },

        setAliasTexParameters: function () {
            //support only in WebGl rendering mode
        },

        generateMipmap: function () {
            //support only in WebGl rendering mode
        },

        stringForFormat: function () {
            //support only in WebGl rendering mode
            return "";
        },

        bitsPerPixelForFormat: function (format) {
            //support only in WebGl rendering mode
            return -1;
        },

        /**
         * add listener for loaded event
         * @param {Function} callback
         * @param {cc.Node} target
         * @deprecated since 3.1, please use addEventListener instead
         */
        addLoadedEventListener: function (callback, target) {
            this.addEventListener("load", callback, target);
        },

        /**
         * remove listener from listeners by target
         * @param {cc.Node} target
         */
        removeLoadedEventListener: function (target) {
            this.removeEventListener("load", target);
        },

        //hack for gray effect
        _grayElementObj: null,
        _backupElement: null,
        _isGray: false,
        _switchToGray: function(toGray){
            if(!this._textureLoaded || this._isGray === toGray)
                return;
            this._isGray = toGray;
            if(this._isGray){
                this._backupElement = this._htmlElementObj;
                if(!this._grayElementObj)
                     this._grayElementObj = cc.Texture2D._generateGrayTexture(this._htmlElementObj);
                this._htmlElementObj = this._grayElementObj;
            } else {
                if(this._backupElement !== null)
                    this._htmlElementObj = this._backupElement;
            }
        }
    });

    cc.Texture2D._generateGrayTexture = function(texture, rect, renderCanvas){
        if (texture === null)
            return null;
        renderCanvas = renderCanvas || cc.newElement("canvas");
        rect = rect || cc.rect(0, 0, texture.width, texture.height);
        renderCanvas.width = rect.width;
        renderCanvas.height = rect.height;

        var context = renderCanvas.getContext("2d");
        context.drawImage(texture, rect.x, rect.y, rect.width, rect.height, 0, 0, rect.width, rect.height);
        var imgData = context.getImageData(0, 0, rect.width, rect.height);
        var data = imgData.data;
        for (var i = 0, len = data.length; i < len; i += 4) {
            data[i] = data[i + 1] = data[i + 2] = 0.34 * data[i] + 0.5 * data[i + 1] + 0.16 * data[i + 2];
        }
        context.putImageData(imgData, 0, 0);
        return renderCanvas;
    };

} else {
    cc.assert(cc.isFunction(cc._tmp.WebGLTexture2D), cc._LogInfos.MissingFile, "TexturesWebGL.js");
    cc._tmp.WebGLTexture2D();
    delete cc._tmp.WebGLTexture2D;
}

cc.EventHelper.prototype.apply(cc.Texture2D.prototype);

cc.assert(cc.isFunction(cc._tmp.PrototypeTexture2D), cc._LogInfos.MissingFile, "TexturesPropertyDefine.js");
cc._tmp.PrototypeTexture2D();
delete cc._tmp.PrototypeTexture2D;