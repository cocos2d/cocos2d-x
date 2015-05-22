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
 * The TextBMFont control of Cocos UI, it rendered by LabelBMFont.
 * @class
 * @extends ccui.Widget
 *
 * @property {String}   string  - Content string of the label
 */
ccui.LabelBMFont = ccui.TextBMFont = ccui.Widget.extend(/** @lends ccui.TextBMFont# */{
    _labelBMFontRenderer: null,
    _fntFileHasInit: false,
    _fntFileName: "",
    _stringValue: "",
    _className: "TextBMFont",
    _labelBMFontRendererAdaptDirty: true,

    /**
     * Allocates and initializes a TextBMFont.                <br/>
     * Constructor of ccui.TextBMFont. override it to extend the construction behavior, remember to call "this._super()" in the extended "ctor" function.
     * @param {String} text
     * @param {String} filename
     * @example
     * // example
     * var uiLabelBMFont = new ccui.TextBMFont();
     */
    ctor: function (text, filename) {
        ccui.Widget.prototype.ctor.call(this);

        if(filename != undefined){
            this.setFntFile(filename);
            this.setString(text);
        }
    },

    _initRenderer: function () {
        this._labelBMFontRenderer = new cc.LabelBMFont();
        this.addProtectedChild(this._labelBMFontRenderer, ccui.TextBMFont.RENDERER_ZORDER, -1);
    },

    /**
     * Initializes a bitmap font atlas with an initial string and the FNT file
     * @param {String} fileName
     */
    setFntFile: function (fileName) {
        if (!fileName)
            return;
        this._fntFileName = fileName;

        this._fntFileHasInit = true;
        this._labelBMFontRenderer.initWithString(this._stringValue, fileName);
        this._updateContentSizeWithTextureSize(this._labelBMFontRenderer.getContentSize());
        this._labelBMFontRendererAdaptDirty = true;

        var _self = this;
        var locRenderer = _self._labelBMFontRenderer;
        if(!locRenderer._textureLoaded){
             locRenderer.addEventListener("load", function(){
                 _self.setFntFile(_self._fntFileName);
             });
        }
    },

    /**
     * Sets string value for TextBMFont
     * @deprecated since v3.0, please use setString instead.
     * @param {String} value
     */
    setText: function (value) {
        cc.log("Please use the setString");
        this.setString(value);
    },

    /**
     * Sets string value for TextBMFont
     * @param {String} value
     */
    setString: function (value) {
        if(value === this._labelBMFontRenderer.getString())
            return;
        this._stringValue = value;
        this._labelBMFontRenderer.setString(value);
        if (!this._fntFileHasInit)
            return;
        this._updateContentSizeWithTextureSize(this._labelBMFontRenderer.getContentSize());
        this._labelBMFontRendererAdaptDirty = true;
    },

    /**
     * Returns string value for TextBMFont.
     * @returns {String}
     */
    getString: function () {
        return this._stringValue;
    },

    /**
     * Returns the length of TextBMFont's string.
     * @returns {Number}
     */
    getStringLength: function(){
        return this._labelBMFontRenderer.getStringLength();
    },

    _onSizeChanged: function () {
        ccui.Widget.prototype._onSizeChanged.call(this);
        this._labelBMFontRendererAdaptDirty = true;
    },

    _adaptRenderers: function(){
        if (this._labelBMFontRendererAdaptDirty){
            this._labelBMFontScaleChangedWithSize();
            this._labelBMFontRendererAdaptDirty = false;
        }
    },

    /**
     * Returns TextBMFont's content size
     * @override
     * @returns {cc.Size}
     */
    getVirtualRendererSize: function(){
        return this._labelBMFontRenderer.getContentSize();
    },

    /**
     * Returns the renderer of TextBMFont
     * @override
     * @returns {cc.Node}
     */
    getVirtualRenderer: function () {
        return this._labelBMFontRenderer;
    },

    _labelBMFontScaleChangedWithSize: function () {
        var locRenderer = this._labelBMFontRenderer;
        if (this._ignoreSize)
            locRenderer.setScale(1.0);
        else {
            var textureSize = locRenderer.getContentSize();
            if (textureSize.width <= 0.0 || textureSize.height <= 0.0) {
                locRenderer.setScale(1.0);
                return;
            }
            locRenderer.setScaleX(this._contentSize.width / textureSize.width);
            locRenderer.setScaleY(this._contentSize.height / textureSize.height);
        }
        locRenderer.setPosition(this._contentSize.width / 2.0, this._contentSize.height / 2.0);
    },

    /**
     * Returns the "class name" of ccui.TextBMFont.
     * @returns {string}
     */
    getDescription: function () {
        return "TextBMFont";
    },

    _createCloneInstance: function () {
        return new ccui.TextBMFont();
    },

    _copySpecialProperties: function (labelBMFont) {
        this.setFntFile(labelBMFont._fntFileName);
        this.setString(labelBMFont._stringValue);
    }
});

var _p = ccui.TextBMFont.prototype;

// Extended properties
/** @expose */
_p.string;
cc.defineGetterSetter(_p, "string", _p.getString, _p.setString);

_p = null;

/**
 * allocates and initializes a UILabelBMFont.
 * @deprecated since v3.0, please use new ccui.TextBMFont() instead.
 * @return {ccui.TextBMFont}
 */
ccui.TextBMFont.create = function (text, filename) {
    return new ccui.TextBMFont(text, filename);
};

// Constants
/**
 * The zOrder value of TextBMFont's renderer.
 * @constant
 * @type {number}
 */
ccui.TextBMFont.RENDERER_ZORDER = -1;
