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
 * The text atlas control of Cocos UI.
 * @class
 * @extends ccui.Widget
 *
 * @property {String}   string  - Content string of the label
 */
ccui.TextAtlas = ccui.Widget.extend(/** @lends ccui.TextAtlas# */{
    _labelAtlasRenderer: null,
    _stringValue: "",
    _charMapFileName: "",
    _itemWidth: 0,
    _itemHeight: 0,
    _startCharMap: "",
    _className: "TextAtlas",
    _labelAtlasRendererAdaptDirty: null,

    /**
     * Allocates and initializes a UILabelAtlas.                  <br/>
     * Constructor of ccui.TextAtlas, override it to extend the construction behavior, remember to call "this._super()" in the extended "ctor" function.
     * @param {String} stringValue
     * @param {String} charMapFile
     * @param {number} itemWidth
     * @param {number} itemHeight
     * @param {String} startCharMap
     * @example
     * // example
     * var uiLabelAtlas = new ccui.TextAtlas();
     */
    ctor: function (stringValue, charMapFile, itemWidth, itemHeight, startCharMap) {
        ccui.Widget.prototype.ctor.call(this);
        startCharMap !== undefined && this.setProperty(stringValue, charMapFile, itemWidth, itemHeight, startCharMap);
    },

    _initRenderer: function () {
        this._labelAtlasRenderer = new cc.LabelAtlas();
        this._labelAtlasRenderer.setAnchorPoint(cc.p(0.5, 0.5));
        this.addProtectedChild(this._labelAtlasRenderer, ccui.TextAtlas.RENDERER_ZORDER, -1);
    },

    /**
     * initializes the UILabelAtlas with a string, a char map file(the atlas), the width and height of each element and the starting char of the atlas
     * @param {String} stringValue
     * @param {String} charMapFile
     * @param {number} itemWidth
     * @param {number} itemHeight
     * @param {String} startCharMap
     */
    setProperty: function (stringValue, charMapFile, itemWidth, itemHeight, startCharMap) {
        this._stringValue = stringValue;
        this._charMapFileName = charMapFile;
        this._itemWidth = itemWidth;
        this._itemHeight = itemHeight;
        this._startCharMap = startCharMap;

        this._labelAtlasRenderer.initWithString(
            stringValue,
            this._charMapFileName,
            this._itemWidth,
            this._itemHeight,
            this._startCharMap[0]
        );

        this._updateContentSizeWithTextureSize(this._labelAtlasRenderer.getContentSize());
        this._labelAtlasRendererAdaptDirty = true;
    },

    /**
     * Sets string value for ui text atlas.
     * @param {String} value
     */
    setString: function (value) {
        if(value === this._labelAtlasRenderer.getString())
            return;
        this._stringValue = value;
        this._labelAtlasRenderer.setString(value);
        this._updateContentSizeWithTextureSize(this._labelAtlasRenderer.getContentSize());
        this._labelAtlasRendererAdaptDirty = true;
    },

    /**
     * Sets string value for text atlas.
     * @deprecated since v3.0, please use setString instead.
     * @param {String} value
     */
    setStringValue: function (value) {
        cc.log("Please use the setString");
        this.setString(value);
    },

    /**
     * get string value for text atlas.
     * @deprecated since v3.0, please use getString instead.
     * @returns {String}
     */
    getStringValue: function () {
        cc.log("Please use the getString");
        return this.getString();
    },

    /**
     * get string value for ui text atlas.
     * @returns {String}
     */
    getString: function () {
        return this._labelAtlasRenderer.getString();
    },

    /**
     * Returns the length of string.
     * @returns {*|Number|long|int}
     */
    getStringLength: function(){
        return this._labelAtlasRenderer.getStringLength();
    },

    _onSizeChanged: function () {
        ccui.Widget.prototype._onSizeChanged.call(this);
        this._labelAtlasRendererAdaptDirty = true;
    },

    _adaptRenderers: function(){
        if (this._labelAtlasRendererAdaptDirty){
            this._labelAtlasScaleChangedWithSize();
            this._labelAtlasRendererAdaptDirty = false;
        }
    },

    /**
     * Returns the renderer's content size
     * @overrider
     * @returns {cc.Size}
     */
    getVirtualRendererSize: function(){
        return this._labelAtlasRenderer.getContentSize();
    },

    /**
     * Returns the renderer of ccui.TextAtlas.
     * @returns {cc.Node}
     */
    getVirtualRenderer: function () {
        return this._labelAtlasRenderer;
    },

    _labelAtlasScaleChangedWithSize: function () {
        var locRenderer = this._labelAtlasRenderer;
        if (this._ignoreSize) {
            locRenderer.setScale(1.0);
        } else {
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
     * Returns the "class name" of ccui.TextAtlas.
     * @returns {string}
     */
    getDescription: function () {
        return "LabelAtlas";
    },

    _copySpecialProperties: function (labelAtlas) {
        if (labelAtlas){
            this.setProperty(labelAtlas._stringValue, labelAtlas._charMapFileName, labelAtlas._itemWidth, labelAtlas._itemHeight, labelAtlas._startCharMap);
        }
    },

    _createCloneInstance: function () {
        return new ccui.TextAtlas();
    }
});

var _p = ccui.TextAtlas.prototype;

// Extended properties
/** @expose */
_p.string;
cc.defineGetterSetter(_p, "string", _p.getString, _p.setString);

_p = null;

/**
 * allocates and initializes a UILabelAtlas.
 * @deprecated since v3.0, please use new ccui.TextAtlas() instead.
 * @return {ccui.TextAtlas}
 */
ccui.TextAtlas.create = function (stringValue, charMapFile, itemWidth, itemHeight, startCharMap) {
    return new ccui.TextAtlas(stringValue, charMapFile, itemWidth, itemHeight, startCharMap);
};

// Constants
/**
 * The zOrder value of ccui.TextAtlas's renderer.
 * @type {number}
 */
ccui.TextAtlas.RENDERER_ZORDER = -1;