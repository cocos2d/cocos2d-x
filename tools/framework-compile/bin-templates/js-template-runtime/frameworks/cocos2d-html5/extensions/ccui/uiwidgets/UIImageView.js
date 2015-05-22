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
 * The ImageView control of Cocos GUI
 * @class
 * @extends ccui.Widget
 */
ccui.ImageView = ccui.Widget.extend(/** @lends ccui.ImageView# */{
    _scale9Enabled: false,
    _prevIgnoreSize: true,
    _capInsets: null,
    _imageRenderer: null,
    _textureFile: "",
    _imageTexType: ccui.Widget.LOCAL_TEXTURE,
    _imageTextureSize: null,
    _className:"ImageView",
    _imageRendererAdaptDirty: true,

    /**
     * allocates and initializes a ccui.ImageView.
     * Constructor of ccui.ImageView, override it to extend the construction behavior, remember to call "this._super()" in the extended "ctor" function.
     * @param {String} imageFileName
     * @param {Number} [texType==ccui.Widget.LOCAL_TEXTURE]
     * @example
     * // example
     * var uiImageView = new ccui.ImageView;
     */
    ctor: function (imageFileName, texType) {
        this._capInsets = cc.rect(0,0,0,0);
        this._imageTextureSize = cc.size(this._capInsets.width, this._capInsets.height);
        ccui.Widget.prototype.ctor.call(this);
        texType = texType === undefined ? 0 : texType;
        this.init(imageFileName, texType);
    },

    /**
     * Initializes an imageView. please do not call this function by yourself, you should pass the parameters to constructor to initialize it.
     * @param {String} imageFileName
     * @param {Number} [texType==ccui.Widget.LOCAL_TEXTURE]
     * @returns {boolean}
     */
    init: function(imageFileName, texType){
        if(ccui.Widget.prototype.init.call(this)){
            if(imageFileName === undefined)
                this._imageTexType = ccui.Widget.LOCAL_TEXTURE;
            else
                this.loadTexture(imageFileName, texType);
            return true;
        }
        return false;
    },

    _initRenderer: function () {
        //todo create Scale9Sprite and setScale9Enabled(false)
        this._imageRenderer = new cc.Sprite();
        this.addProtectedChild(this._imageRenderer, ccui.ImageView.RENDERER_ZORDER, -1);
    },

    setRotation: function(rotate){
        this._imageRenderer.setRotation(rotate);
    },

    /**
     * Loads textures for button.
     * @param {String} fileName
     * @param {ccui.Widget.LOCAL_TEXTURE|ccui.Widget.PLIST_TEXTURE} texType
     */
    loadTexture: function (fileName, texType) {
        //todo use this code when _initRenderer use Scale9Sprite
        //if (!fileName || (this._textureFile == fileName && this._imageTexType == texType)) {
        if (!fileName) {
            return;
        }
        var self = this;
        texType = texType || ccui.Widget.LOCAL_TEXTURE;
        this._textureFile = fileName;
        this._imageTexType = texType;
        var imageRenderer = self._imageRenderer;

        if(!imageRenderer._textureLoaded){
            imageRenderer.addEventListener("load", function(){
                self.loadTexture(self._textureFile, self._imageTexType);
            });
        }

        switch (self._imageTexType) {
            case ccui.Widget.LOCAL_TEXTURE:
                if(self._scale9Enabled){
                    imageRenderer.initWithFile(fileName);
                    imageRenderer.setCapInsets(self._capInsets);
                }else{
                    //SetTexture cannot load resource
                    imageRenderer.initWithFile(fileName);
                }
                break;
            case ccui.Widget.PLIST_TEXTURE:
                if(self._scale9Enabled){
                    imageRenderer.initWithSpriteFrameName(fileName);
                    imageRenderer.setCapInsets(self._capInsets);
                }else{
                    //SetTexture cannot load resource
                    imageRenderer.initWithSpriteFrameName(fileName);
                }
                break;
            default:
                break;
        }

        self._imageTextureSize = imageRenderer.getContentSize();

        this._updateChildrenDisplayedRGBA();

        self._updateContentSizeWithTextureSize(self._imageTextureSize);
        self._imageRendererAdaptDirty = true;
        self._findLayout();

    },

    /**
     * Sets texture rect
     * @param {cc.Rect} rect
     */
    setTextureRect: function (rect) {
        if (!this._scale9Enabled)
            this._imageRenderer.setTextureRect(rect);
    },

    /**
     * Sets if button is using scale9 renderer.
     * @param {Boolean} able
     */
    setScale9Enabled: function (able) {
        //todo setScale9Enabled
        if (this._scale9Enabled === able)
            return;

        this._scale9Enabled = able;
        this.removeProtectedChild(this._imageRenderer);
        this._imageRenderer = null;
        if (this._scale9Enabled) {
            this._imageRenderer = new ccui.Scale9Sprite();
        } else {
            this._imageRenderer = new cc.Sprite();
        }
        this.loadTexture(this._textureFile, this._imageTexType);
        this.addProtectedChild(this._imageRenderer, ccui.ImageView.RENDERER_ZORDER, -1);
        if (this._scale9Enabled) {
            var ignoreBefore = this._ignoreSize;
            this.ignoreContentAdaptWithSize(false);
            this._prevIgnoreSize = ignoreBefore;
        } else
            this.ignoreContentAdaptWithSize(this._prevIgnoreSize);
        this.setCapInsets(this._capInsets);
        this._imageRendererAdaptDirty = true;
    },

    /**
     * Returns ImageView is using scale9 renderer or not.
     * @returns {Boolean}
     */
    isScale9Enabled:function(){
        return this._scale9Enabled;
    },

    /**
     * Ignore the imageView's custom size, true that imageView will ignore it's custom size, use renderer's content size, false otherwise.
     * @override
     * @param {Boolean} ignore
     */
    ignoreContentAdaptWithSize: function (ignore) {
        if (!this._scale9Enabled || (this._scale9Enabled && !ignore)) {
            ccui.Widget.prototype.ignoreContentAdaptWithSize.call(this, ignore);
            this._prevIgnoreSize = ignore;
        }
    },

    /**
     * Sets capinsets for button, if button is using scale9 renderer.
     * @param {cc.Rect} capInsets
     */
    setCapInsets: function (capInsets) {
        if(!capInsets)
            return;
        var locInsets = this._capInsets;
        locInsets.x = capInsets.x;
        locInsets.y = capInsets.y;
        locInsets.width = capInsets.width;
        locInsets.height = capInsets.height;

        if (!this._scale9Enabled)
            return;
        this._imageRenderer.setCapInsets(capInsets);
    },

    /**
     * Returns cap insets of ccui.ImageView.
     * @returns {cc.Rect}
     */
    getCapInsets:function(){
        return cc.rect(this._capInsets);
    },

    _onSizeChanged: function () {
        ccui.Widget.prototype._onSizeChanged.call(this);
        this._imageRendererAdaptDirty = true;
    },

    _adaptRenderers: function(){
        if (this._imageRendererAdaptDirty){
            this._imageTextureScaleChangedWithSize();
            this._imageRendererAdaptDirty = false;
        }
    },

    /**
     * Returns the image's texture size.
     * @returns {cc.Size}
     */
    getVirtualRendererSize: function(){
        return cc.size(this._imageTextureSize);
    },

    /**
     * Returns the renderer of ccui.ImageView
     * @override
     * @returns {cc.Node}
     */
    getVirtualRenderer: function () {
        return this._imageRenderer;
    },

    _imageTextureScaleChangedWithSize: function () {
        if (this._ignoreSize) {
            if (!this._scale9Enabled)
                this._imageRenderer.setScale(1.0);
        } else {
            if (this._scale9Enabled){
                this._imageRenderer.setPreferredSize(this._contentSize);
                this._imageRenderer.setScale(1);
            } else {
                var textureSize = this._imageTextureSize;
                if (textureSize.width <= 0.0 || textureSize.height <= 0.0) {
                    this._imageRenderer.setScale(1.0);
                    return;
                }
                this._imageRenderer.setScaleX(this._contentSize.width / textureSize.width);
                this._imageRenderer.setScaleY(this._contentSize.height / textureSize.height);
            }
        }
        this._imageRenderer.setPosition(this._contentSize.width / 2.0, this._contentSize.height / 2.0);
    },

    /**
     * Returns the "class name" of ccui.ImageView.
     * @override
     * @returns {string}
     */
    getDescription: function () {
        return "ImageView";
    },

    _createCloneInstance:function(){
        return new ccui.ImageView();
    },

    _copySpecialProperties: function (imageView) {
        if(imageView instanceof ccui.ImageView){
            this._prevIgnoreSize = imageView._prevIgnoreSize;
            this.setScale9Enabled(imageView._scale9Enabled);
            this.loadTexture(imageView._textureFile, imageView._imageTexType);
            this.setCapInsets(imageView._capInsets);
        }
    },
    /**
     * Sets _customSize of ccui.Widget, if ignoreSize is true, the content size is its renderer's contentSize, otherwise the content size is parameter.
     * and updates size percent by parent content size. At last, updates its children's size and position.
     * @param {cc.Size|Number} contentSize content size or width of content size
     * @param {Number} [height]
     * @override
     */
    setContentSize: function(contentSize, height){
        if(height != null)
            contentSize = cc.size(contentSize, height);
        ccui.Widget.prototype.setContentSize.call(this, contentSize);
        if(!this._scale9Enabled){
            var iContentSize = this._imageRenderer.getContentSize();
            this._imageRenderer.setScaleX(contentSize.width / iContentSize.width);
            this._imageRenderer.setScaleY(contentSize.height / iContentSize.height);
        }else{
            this._imageRenderer.setContentSize(contentSize);
        }

    }

});

/**
 * Allocates and initializes a UIImageView.
 * @deprecated since v3.0, please use new ccui.ImageView() instead.
 * @param {string} imageFileName
 * @param {Number} texType
 * @return {ccui.ImageView}
 */
ccui.ImageView.create = function (imageFileName, texType) {
    return new ccui.ImageView(imageFileName, texType);
};

// Constants
/**
 * The zOrder value of ccui.ImageView's renderer.
 * @constant
 * @type {number}
 */
ccui.ImageView.RENDERER_ZORDER = -1;