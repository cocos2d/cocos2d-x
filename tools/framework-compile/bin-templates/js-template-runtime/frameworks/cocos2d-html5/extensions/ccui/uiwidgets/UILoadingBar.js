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
 * The LoadingBar control of Cocos UI.
 * @class
 * @extends ccui.Widget
 *
 * @property {ccui.LoadingBar.TYPE_LEFT | ccui.LoadingBar.TYPE_RIGHT}   direction   - The progress direction of loadingbar
 * @property {Number}               percent     - The current progress of loadingbar
 */
ccui.LoadingBar = ccui.Widget.extend(/** @lends ccui.LoadingBar# */{
    _direction: null,
    _percent: 100,
    _totalLength: 0,
    _barRenderer: null,
    _renderBarTexType: ccui.Widget.LOCAL_TEXTURE,
    _barRendererTextureSize: null,
    _scale9Enabled: false,
    _prevIgnoreSize: true,
    _capInsets: null,
    _textureFile: "",
    _isTextureLoaded: false,
    _className: "LoadingBar",
    _barRendererAdaptDirty: true,

    /**
     * allocates and initializes a UILoadingBar.                                                        <br/>
     * Constructor of ccui.LoadingBar, override it to extend the construction behavior, remember to call "this._super()" in the extended "ctor" function.
     * @param {string} textureName
     * @param {Number} percentage
     * @example
     * // example
     * var uiLoadingBar = new ccui.LoadingBar;
     */
    ctor: function (textureName, percentage) {
        this._direction = ccui.LoadingBar.TYPE_LEFT;
        this._barRendererTextureSize = cc.size(0, 0);
        this._capInsets = cc.rect(0, 0, 0, 0);
        ccui.Widget.prototype.ctor.call(this);

        if(textureName !== undefined)
            this.loadTexture(textureName);
        if(percentage !== undefined)
            this.setPercent(percentage);
    },

    _initRenderer: function () {
        //todo use Scale9Sprite
        this._barRenderer = new cc.Sprite();
        this.addProtectedChild(this._barRenderer, ccui.LoadingBar.RENDERER_ZORDER, -1);
        this._barRenderer.setAnchorPoint(0.0, 0.5);
    },

    /**
     * Changes the progress direction of LoadingBar.                           <br/>
     * LoadingBarTypeLeft means progress left to right, LoadingBarTypeRight otherwise.
     * @param {ccui.LoadingBar.TYPE_LEFT | ccui.LoadingBar.TYPE_RIGHT} dir
     */
    setDirection: function (dir) {
        if (this._direction === dir)
            return;
        this._direction = dir;
        switch (this._direction) {
            case ccui.LoadingBar.TYPE_LEFT:
                this._barRenderer.setAnchorPoint(0, 0.5);
                this._barRenderer.setPosition(0, this._contentSize.height*0.5);
                if (!this._scale9Enabled)
                    this._barRenderer.setFlippedX(false);
                break;
            case ccui.LoadingBar.TYPE_RIGHT:
                this._barRenderer.setAnchorPoint(1, 0.5);
                this._barRenderer.setPosition(this._totalLength,this._contentSize.height*0.5);
                if (!this._scale9Enabled)
                    this._barRenderer.setFlippedX(true);
                break;
        }
    },

    /**
     * Returns the progress direction of LoadingBar.                               <br/>
     * LoadingBarTypeLeft means progress left to right, LoadingBarTypeRight otherwise.
     * @returns {ccui.LoadingBar.TYPE_LEFT | ccui.LoadingBar.TYPE_RIGHT}
     */
    getDirection: function () {
        return this._direction;
    },

    /**
     * Loads texture for LoadingBar.
     * @param {String} texture
     * @param {ccui.Widget.LOCAL_TEXTURE|ccui.Widget.PLIST_TEXTURE} texType
     */
    loadTexture: function (texture, texType) {
        if (!texture)
            return;
        texType = texType || ccui.Widget.LOCAL_TEXTURE;
        this._renderBarTexType = texType;
        this._textureFile = texture;
        var barRenderer = this._barRenderer;

        var self = this;
        if(!barRenderer._textureLoaded){
            barRenderer.addEventListener("load", function(){
                self.loadTexture(self._textureFile, self._renderBarTexType);
                self._setPercent(self._percent);
            });
        }

        switch (this._renderBarTexType) {
            case ccui.Widget.LOCAL_TEXTURE:
                barRenderer.initWithFile(texture);
                break;
            case ccui.Widget.PLIST_TEXTURE:
                barRenderer.initWithSpriteFrameName(texture);
                break;
            default:
                break;
        }

        var bz = barRenderer.getContentSize();
        this._barRendererTextureSize.width = bz.width;
        this._barRendererTextureSize.height = bz.height;

        switch (this._direction) {
            case ccui.LoadingBar.TYPE_LEFT:
                barRenderer.setAnchorPoint(0,0.5);
                if (!this._scale9Enabled)
                    barRenderer.setFlippedX(false);
                break;
            case ccui.LoadingBar.TYPE_RIGHT:
                barRenderer.setAnchorPoint(1,0.5);
                if (!this._scale9Enabled)
                    barRenderer.setFlippedX(true);
                break;
        }
        if (this._scale9Enabled)
            barRenderer.setCapInsets(this._capInsets);

        this._updateChildrenDisplayedRGBA();
        this._barRendererScaleChangedWithSize();
        this._updateContentSizeWithTextureSize(this._barRendererTextureSize);
        this._barRendererAdaptDirty = true;
        this._findLayout();
    },

    /**
     * Sets if LoadingBar is using scale9 renderer.
     * @param {Boolean} enabled
     */
    setScale9Enabled: function (enabled) {
        //todo use setScale9Enabled
        if (this._scale9Enabled === enabled)
            return;
        this._scale9Enabled = enabled;
        this.removeProtectedChild(this._barRenderer);

        this._barRenderer = this._scale9Enabled ? new ccui.Scale9Sprite() : new cc.Sprite();

        this.loadTexture(this._textureFile, this._renderBarTexType);
        this.addProtectedChild(this._barRenderer, ccui.LoadingBar.RENDERER_ZORDER, -1);
        if (this._scale9Enabled) {
            var ignoreBefore = this._ignoreSize;
            this.ignoreContentAdaptWithSize(false);
            this._prevIgnoreSize = ignoreBefore;
        } else
            this.ignoreContentAdaptWithSize(this._prevIgnoreSize);
        this.setCapInsets(this._capInsets);
        this.setPercent(this._percent);
        this._barRendererAdaptDirty = true;
    },

    /**
     * Returns LoadingBar is using scale9 renderer or not..
     * @returns {Boolean}
     */
    isScale9Enabled: function () {
        return this._scale9Enabled;
    },

    /**
     * Sets capinsets for LoadingBar, if LoadingBar is using scale9 renderer.
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

        if (this._scale9Enabled)
            this._barRenderer.setCapInsets(capInsets);
    },

    /**
     * Returns cap insets for loadingBar.
     * @returns {cc.Rect}
     */
    getCapInsets: function () {
        return cc.rect(this._capInsets);
    },

    /**
     * The current progress of loadingBar
     * @param {number} percent   percent value from 1 to 100.
     */
    setPercent: function (percent) {
        if(percent > 100)
            percent = 100;
        if(percent < 0)
            percent = 0;
        if (percent === this._percent)
            return;
        this._percent = percent;
        this._setPercent(percent);
    },

    _setPercent: function(percent){
        if (this._totalLength <= 0)
            return;
        var res = this._percent / 100.0;

        if (this._scale9Enabled)
            this._setScale9Scale();
        else {
            var spriteRenderer = this._barRenderer;
            var rect = spriteRenderer.getTextureRect();
            rect.width = this._barRendererTextureSize.width * res;
            this._barRenderer.setTextureRect(
                cc.rect(
                    rect.x,
                    rect.y,
                    this._barRendererTextureSize.width * res,
                    this._barRendererTextureSize.height
                )
            );
        }
    },

    /**
     * Sets the contentSize of ccui.LoadingBar
     * @override
     * @param {Number|cc.Size} contentSize
     * @param {Number} [height]
     */
    setContentSize: function(contentSize, height){
        ccui.Widget.prototype.setContentSize.call(this, contentSize, height);
        this._totalLength = (height === undefined) ? contentSize.width : contentSize;
    },

    /**
     * Returns the progress direction of LoadingBar.
     * @returns {number} percent value from 1 to 100.
     */
    getPercent: function () {
        return this._percent;
    },

    _onSizeChanged: function () {
        ccui.Widget.prototype._onSizeChanged.call(this);
        this._barRendererAdaptDirty = true;
    },

    _adaptRenderers: function(){
        if (this._barRendererAdaptDirty){
            this._barRendererScaleChangedWithSize();
            this._barRendererAdaptDirty = false;
        }
    },

    /**
     * Ignore the LoadingBar's custom size,  if ignore is true that LoadingBar will ignore it's custom size, use renderer's content size, false otherwise.
     * @override
     * @param {Boolean}ignore
     */
    ignoreContentAdaptWithSize: function (ignore) {
        if (!this._scale9Enabled || (this._scale9Enabled && !ignore)) {
            ccui.Widget.prototype.ignoreContentAdaptWithSize.call(this, ignore);
            this._prevIgnoreSize = ignore;
        }
    },

    /**
     * Returns the texture size of renderer.
     * @returns {cc.Size|*}
     */
    getVirtualRendererSize:function(){
        return cc.size(this._barRendererTextureSize);
    },

    /**
     * Returns the renderer of ccui.LoadingBar
     * @override
     * @returns {cc.Node}
     */
    getVirtualRenderer: function () {
        return this._barRenderer;
    },

    _barRendererScaleChangedWithSize: function () {
        var locBarRender = this._barRenderer, locContentSize = this._contentSize;
        if(this._unifySize){
            this._totalLength = this._contentSize.width;
            this.setPercent(this._percent);
        }else if (this._ignoreSize) {
            if (!this._scale9Enabled) {
                this._totalLength = this._barRendererTextureSize.width;
                locBarRender.setScale(1.0);
            }
        } else {
            this._totalLength = locContentSize.width;
            if (this._scale9Enabled){
                this._setScale9Scale();
                locBarRender.setScale(1.0);
            } else {
                var textureSize = this._barRendererTextureSize;
                if (textureSize.width <= 0.0 || textureSize.height <= 0.0) {
                    locBarRender.setScale(1.0);
                    return;
                }
                var scaleX = locContentSize.width / textureSize.width;
                var scaleY = locContentSize.height / textureSize.height;
                locBarRender.setScaleX(scaleX);
                locBarRender.setScaleY(scaleY);
            }
        }
        switch (this._direction) {
            case ccui.LoadingBar.TYPE_LEFT:
                locBarRender.setPosition(0, locContentSize.height * 0.5);
                break;
            case ccui.LoadingBar.TYPE_RIGHT:
                locBarRender.setPosition(this._totalLength, locContentSize.height * 0.5);
                break;
            default:
                break;
        }
    },

    _setScale9Scale: function () {
        var width = (this._percent) / 100 * this._totalLength;
        this._barRenderer.setPreferredSize(cc.size(width, this._contentSize.height));
    },

    /**
     * Returns the "class name" of widget.
     * @returns {string}
     */
    getDescription: function () {
        return "LoadingBar";
    },

    _createCloneInstance: function () {
        return new ccui.LoadingBar();
    },

    _copySpecialProperties: function (loadingBar) {
        if(loadingBar instanceof ccui.LoadingBar){
            this._prevIgnoreSize = loadingBar._prevIgnoreSize;
            this.setScale9Enabled(loadingBar._scale9Enabled);
            this.loadTexture(loadingBar._textureFile, loadingBar._renderBarTexType);
            this.setCapInsets(loadingBar._capInsets);
            this.setPercent(loadingBar._percent);
            this.setDirection(loadingBar._direction);
        }
    }
});

var _p = ccui.LoadingBar.prototype;

// Extended properties
/** @expose */
_p.direction;
cc.defineGetterSetter(_p, "direction", _p.getDirection, _p.setDirection);
/** @expose */
_p.percent;
cc.defineGetterSetter(_p, "percent", _p.getPercent, _p.setPercent);

_p = null;

/**
 * Allocates and initializes a UILoadingBar.
 * @deprecated since v3.0, please use new ccui.LoadingBar() instead.
 * @param {string} textureName
 * @param {Number} percentage
 * @return {ccui.LoadingBar}
 */
ccui.LoadingBar.create = function (textureName, percentage) {
    return new ccui.LoadingBar(textureName, percentage);
};

// Constants
//loadingBar Type

/**
 * The left direction of ccui.LoadingBar.
 * @constant
 * @type {number}
 */
ccui.LoadingBar.TYPE_LEFT = 0;
/**
 * The right direction of ccui.LoadingBar.
 * @constant
 * @type {number}
 */
ccui.LoadingBar.TYPE_RIGHT = 1;

/**
 * The zOrder value of ccui.LoadingBar's renderer.
 * @constant
 * @type {number}
 */
ccui.LoadingBar.RENDERER_ZORDER = -1;