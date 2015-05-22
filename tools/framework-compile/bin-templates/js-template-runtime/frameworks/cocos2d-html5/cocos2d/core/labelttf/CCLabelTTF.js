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

/**
 * <p>cc.LabelTTF is a subclass of cc.TextureNode that knows how to render text labels with system font or a ttf font file<br/>
 * All features from cc.Sprite are valid in cc.LabelTTF<br/>
 * cc.LabelTTF objects are slow for js-binding on mobile devices.<br/>
 * Consider using cc.LabelAtlas or cc.LabelBMFont instead.<br/>
 * You can create a cc.LabelTTF from a font name, alignment, dimension and font size or a cc.FontDefinition object.</p>
 * @class
 * @extends cc.Sprite
 *
 * @param {String} text
 * @param {String|cc.FontDefinition} [fontName="Arial"]
 * @param {Number} [fontSize=16]
 * @param {cc.Size} [dimensions=cc.size(0,0)]
 * @param {Number} [hAlignment=cc.TEXT_ALIGNMENT_LEFT]
 * @param {Number} [vAlignment=cc.VERTICAL_TEXT_ALIGNMENT_TOP]
 * @example
 * var myLabel = new cc.LabelTTF('label text',  'Times New Roman', 32, cc.size(320,32), cc.TEXT_ALIGNMENT_LEFT);
 *
 * var fontDef = new cc.FontDefinition();
 * fontDef.fontName = "Arial";
 * fontDef.fontSize = "32";
 * var myLabel = new cc.LabelTTF('label text',  fontDef);
 *
 * @property {String}       string          - Content string of label
 * @property {Number}       textAlign       - Horizontal Alignment of label: cc.TEXT_ALIGNMENT_LEFT|cc.TEXT_ALIGNMENT_CENTER|cc.TEXT_ALIGNMENT_RIGHT
 * @property {Number}       verticalAlign   - Vertical Alignment of label: cc.VERTICAL_TEXT_ALIGNMENT_TOP|cc.VERTICAL_TEXT_ALIGNMENT_CENTER|cc.VERTICAL_TEXT_ALIGNMENT_BOTTOM
 * @property {Number}       fontSize        - Font size of label
 * @property {String}       fontName        - Font name of label
 * @property {String}       font            - The label font with a style string: e.g. "18px Verdana"
 * @property {Number}       boundingWidth   - Width of the bounding box of label, the real content width is limited by boundingWidth
 * @property {Number}       boundingHeight  - Height of the bounding box of label, the real content height is limited by boundingHeight
 * @property {cc.Color}     fillStyle       - The fill color
 * @property {cc.Color}     strokeStyle     - The stroke color
 * @property {Number}       lineWidth       - The line width for stroke
 * @property {Number}       shadowOffsetX   - The x axis offset of shadow
 * @property {Number}       shadowOffsetY   - The y axis offset of shadow
 * @property {Number}       shadowOpacity   - The opacity of shadow
 * @property {Number}       shadowBlur      - The blur size of shadow
 */
cc.LabelTTF = cc.Sprite.extend(/** @lends cc.LabelTTF# */{
    _dimensions: null,
    _hAlignment: cc.TEXT_ALIGNMENT_CENTER,
    _vAlignment: cc.VERTICAL_TEXT_ALIGNMENT_TOP,
    _fontName: null,
    _fontSize: 0.0,
    _string: "",
    _originalText: null,

    // font shadow
    _shadowEnabled: false,
    _shadowOffset: null,
    _shadowOpacity: 0,
    _shadowBlur: 0,
    _shadowColor: null,

    // font stroke
    _strokeEnabled: false,
    _strokeColor: null,
    _strokeSize: 0,

    // font tint
    _textFillColor: null,

    _strokeShadowOffsetX: 0,
    _strokeShadowOffsetY: 0,
    _needUpdateTexture: false,

    _lineWidths: null,
    _className: "LabelTTF",

    //for web
    _fontStyle: "normal",
    _fontWeight: "normal",
    _lineHeight: "normal",

    /**
     * Initializes the cc.LabelTTF with a font name, alignment, dimension and font size, do not call it by yourself,
     * you should pass the correct arguments in constructor to initialize the label.
     * @param {String} label string
     * @param {String} fontName
     * @param {Number} fontSize
     * @param {cc.Size} [dimensions=]
     * @param {Number} [hAlignment=]
     * @param {Number} [vAlignment=]
     * @return {Boolean} return false on error
     */
    initWithString: function (label, fontName, fontSize, dimensions, hAlignment, vAlignment) {
        var strInfo;
        if (label)
            strInfo = label + "";
        else
            strInfo = "";

        fontSize = fontSize || 16;
        dimensions = dimensions || cc.size(0, 0/*fontSize*/);
        hAlignment = hAlignment || cc.TEXT_ALIGNMENT_LEFT;
        vAlignment = vAlignment || cc.VERTICAL_TEXT_ALIGNMENT_TOP;

        this._opacityModifyRGB = false;
        this._dimensions = cc.size(dimensions.width, dimensions.height);
        this._fontName = fontName || "Arial";
        this._hAlignment = hAlignment;
        this._vAlignment = vAlignment;

        this._fontSize = fontSize;
        this._renderCmd._setFontStyle(this._fontName, fontSize, this._fontStyle, this._fontWeight);
        this.string = strInfo;
        this._renderCmd._setColorsString();
        this._renderCmd._updateTexture();
        this._setUpdateTextureDirty();
        return true;
    },

    _setUpdateTextureDirty: function () {
        this._needUpdateTexture = true;
        this._renderCmd.setDirtyFlag(cc.Node._dirtyFlags.textDirty);
    },

    ctor: function (text, fontName, fontSize, dimensions, hAlignment, vAlignment) {
        cc.Sprite.prototype.ctor.call(this);

        this._dimensions = cc.size(0, 0);
        this._hAlignment = cc.TEXT_ALIGNMENT_LEFT;
        this._vAlignment = cc.VERTICAL_TEXT_ALIGNMENT_TOP;
        this._opacityModifyRGB = false;
        this._fontName = "Arial";

        this._shadowEnabled = false;
        this._shadowOffset = cc.p(0, 0);
        this._shadowOpacity = 0;
        this._shadowBlur = 0;

        this._strokeEnabled = false;
        this._strokeColor = cc.color(255, 255, 255, 255);
        this._strokeSize = 0;

        this._textFillColor = cc.color(255, 255, 255, 255);
        this._strokeShadowOffsetX = 0;
        this._strokeShadowOffsetY = 0;
        this._needUpdateTexture = false;

        this._lineWidths = [];
        this._renderCmd._setColorsString();
        this._textureLoaded = true;

        if (fontName && fontName instanceof cc.FontDefinition) {
            this.initWithStringAndTextDefinition(text, fontName);
        } else {
            cc.LabelTTF.prototype.initWithString.call(this, text, fontName, fontSize, dimensions, hAlignment, vAlignment);
        }
    },

    init: function () {
        return this.initWithString(" ", this._fontName, this._fontSize);
    },

    description: function () {
        return "<cc.LabelTTF | FontName =" + this._fontName + " FontSize = " + this._fontSize.toFixed(1) + ">";
    },

    getLineHeight: function () {
        return !this._lineHeight || this._lineHeight.charAt ?
            this._renderCmd._getFontClientHeight() :
            this._lineHeight || this._renderCmd._getFontClientHeight();
    },

    setLineHeight: function (lineHeight) {
        this._lineHeight = lineHeight;
    },

    /**
     * Returns the text of the label
     * @return {String}
     */
    getString: function () {
        return this._string;
    },

    /**
     * Returns Horizontal Alignment of cc.LabelTTF
     * @return {cc.TEXT_ALIGNMENT_LEFT|cc.TEXT_ALIGNMENT_CENTER|cc.TEXT_ALIGNMENT_RIGHT}
     */
    getHorizontalAlignment: function () {
        return this._hAlignment;
    },

    /**
     * Returns Vertical Alignment of cc.LabelTTF
     * @return {cc.VERTICAL_TEXT_ALIGNMENT_TOP|cc.VERTICAL_TEXT_ALIGNMENT_CENTER|cc.VERTICAL_TEXT_ALIGNMENT_BOTTOM}
     */
    getVerticalAlignment: function () {
        return this._vAlignment;
    },

    /**
     * Returns the dimensions of cc.LabelTTF, the dimension is the maximum size of the label, set it so that label will automatically change lines when necessary.
     * @see cc.LabelTTF#setDimensions, cc.LabelTTF#boundingWidth and cc.LabelTTF#boundingHeight
     * @return {cc.Size}
     */
    getDimensions: function () {
        return cc.size(this._dimensions);
    },

    /**
     * Returns font size of cc.LabelTTF
     * @return {Number}
     */
    getFontSize: function () {
        return this._fontSize;
    },

    /**
     * Returns font name of cc.LabelTTF
     * @return {String}
     */
    getFontName: function () {
        return this._fontName;
    },

    /**
     * Initializes the CCLabelTTF with a font name, alignment, dimension and font size, do not call it by yourself, you should pass the correct arguments in constructor to initialize the label.
     * @param {String} text
     * @param {cc.FontDefinition} textDefinition
     * @return {Boolean}
     */
    initWithStringAndTextDefinition: function (text, textDefinition) {
        // prepare everything needed to render the label
        this._updateWithTextDefinition(textDefinition, false);
        // set the string
        this.string = text;
        return true;
    },

    /**
     * Sets the text definition used by this label
     * @param {cc.FontDefinition} theDefinition
     */
    setTextDefinition: function (theDefinition) {
        if (theDefinition)
            this._updateWithTextDefinition(theDefinition, true);
    },

    /**
     * Extract the text definition used by this label
     * @return {cc.FontDefinition}
     */
    getTextDefinition: function () {
        return this._prepareTextDefinition(false);
    },

    /**
     * Enable or disable shadow for the label
     * @param {cc.Color | Number} a Color or The x axis offset of the shadow
     * @param {cc.Size | Number} b Size or The y axis offset of the shadow
     * @param {Number} c The blur size of the shadow or The opacity of the shadow (0 to 1)
     * @param {null | Number} d Null or The blur size of the shadow
     * @example
     *   old:
     *     labelttf.enableShadow(shadowOffsetX, shadowOffsetY, shadowOpacity, shadowBlur);
     *   new:
     *     labelttf.enableShadow(shadowColor, offset, blurRadius);
     */
    enableShadow: function (a, b, c, d) {
        if (a.r != null && a.g != null && a.b != null && a.a != null) {
            this._enableShadow(a, b, c);
        } else {
            this._enableShadowNoneColor(a, b, c, d)
        }
    },

    _enableShadowNoneColor: function (shadowOffsetX, shadowOffsetY, shadowOpacity, shadowBlur) {
        shadowOpacity = shadowOpacity || 0.5;
        if (false === this._shadowEnabled)
            this._shadowEnabled = true;

        var locShadowOffset = this._shadowOffset;
        if (locShadowOffset && (locShadowOffset.x !== shadowOffsetX) || (locShadowOffset._y !== shadowOffsetY)) {
            locShadowOffset.x = shadowOffsetX;
            locShadowOffset.y = shadowOffsetY;
        }

        if (this._shadowOpacity !== shadowOpacity) {
            this._shadowOpacity = shadowOpacity;
        }
        this._renderCmd._setColorsString();

        if (this._shadowBlur !== shadowBlur)
            this._shadowBlur = shadowBlur;
        this._setUpdateTextureDirty();
    },

    _enableShadow: function (shadowColor, offset, blurRadius) {
        if (!this._shadowColor) {
            this._shadowColor = cc.color(255, 255, 255, 128);
        }
        this._shadowColor.r = shadowColor.r;
        this._shadowColor.g = shadowColor.g;
        this._shadowColor.b = shadowColor.b;

        var x, y, a, b;
        x = offset.width || offset.x || 0;
        y = offset.height || offset.y || 0;
        a = (shadowColor.a != null) ? (shadowColor.a / 255) : 0.5;
        b = blurRadius;

        this._enableShadowNoneColor(x, y, a, b);
    },

    _getShadowOffsetX: function () {
        return this._shadowOffset.x;
    },
    _setShadowOffsetX: function (x) {
        if (false === this._shadowEnabled)
            this._shadowEnabled = true;

        if (this._shadowOffset.x !== x) {
            this._shadowOffset.x = x;
            this._setUpdateTextureDirty();
        }
    },

    _getShadowOffsetY: function () {
        return this._shadowOffset._y;
    },
    _setShadowOffsetY: function (y) {
        if (false === this._shadowEnabled)
            this._shadowEnabled = true;

        if (this._shadowOffset._y !== y) {
            this._shadowOffset._y = y;
            this._setUpdateTextureDirty();
        }
    },

    _getShadowOffset: function () {
        return cc.p(this._shadowOffset.x, this._shadowOffset.y);
    },
    _setShadowOffset: function (offset) {
        if (false === this._shadowEnabled)
            this._shadowEnabled = true;

        if (this._shadowOffset.x !== offset.x || this._shadowOffset.y !== offset.y) {
            this._shadowOffset.x = offset.x;
            this._shadowOffset.y = offset.y;
            this._setUpdateTextureDirty();
        }
    },

    _getShadowOpacity: function () {
        return this._shadowOpacity;
    },
    _setShadowOpacity: function (shadowOpacity) {
        if (false === this._shadowEnabled)
            this._shadowEnabled = true;

        if (this._shadowOpacity !== shadowOpacity) {
            this._shadowOpacity = shadowOpacity;
            this._renderCmd._setColorsString();
            this._setUpdateTextureDirty();
        }
    },

    _getShadowBlur: function () {
        return this._shadowBlur;
    },
    _setShadowBlur: function (shadowBlur) {
        if (false === this._shadowEnabled)
            this._shadowEnabled = true;

        if (this._shadowBlur !== shadowBlur) {
            this._shadowBlur = shadowBlur;
            this._setUpdateTextureDirty();
        }
    },

    /**
     * Disable shadow rendering
     */
    disableShadow: function () {
        if (this._shadowEnabled) {
            this._shadowEnabled = false;
            this._setUpdateTextureDirty();
        }
    },

    /**
     * Enable label stroke with stroke parameters
     * @param {cc.Color} strokeColor The color of stroke
     * @param {Number} strokeSize The size of stroke
     */
    enableStroke: function (strokeColor, strokeSize) {
        if (this._strokeEnabled === false)
            this._strokeEnabled = true;

        var locStrokeColor = this._strokeColor;
        if ((locStrokeColor.r !== strokeColor.r) || (locStrokeColor.g !== strokeColor.g) || (locStrokeColor.b !== strokeColor.b)) {
            locStrokeColor.r = strokeColor.r;
            locStrokeColor.g = strokeColor.g;
            locStrokeColor.b = strokeColor.b;
            this._renderCmd._setColorsString();
        }

        if (this._strokeSize !== strokeSize)
            this._strokeSize = strokeSize || 0;
        this._setUpdateTextureDirty();
    },

    _getStrokeStyle: function () {
        return this._strokeColor;
    },
    _setStrokeStyle: function (strokeStyle) {
        if (this._strokeEnabled === false)
            this._strokeEnabled = true;

        var locStrokeColor = this._strokeColor;
        if ((locStrokeColor.r !== strokeStyle.r) || (locStrokeColor.g !== strokeStyle.g) || (locStrokeColor.b !== strokeStyle.b)) {
            locStrokeColor.r = strokeStyle.r;
            locStrokeColor.g = strokeStyle.g;
            locStrokeColor.b = strokeStyle.b;
            this._renderCmd._setColorsString();
            this._setUpdateTextureDirty();
        }
    },

    _getLineWidth: function () {
        return this._strokeSize;
    },
    _setLineWidth: function (lineWidth) {
        if (this._strokeEnabled === false)
            this._strokeEnabled = true;
        if (this._strokeSize !== lineWidth) {
            this._strokeSize = lineWidth || 0;
            this._setUpdateTextureDirty();
        }
    },

    /**
     * Disable label stroke
     */
    disableStroke: function () {
        if (this._strokeEnabled) {
            this._strokeEnabled = false;
            this._setUpdateTextureDirty();
        }
    },

    /**
     * Sets the text fill color
     * @function
     * @param {cc.Color} fillColor The fill color of the label
     */
    setFontFillColor: function (fillColor) {
        var locTextFillColor = this._textFillColor;
        if (locTextFillColor.r !== fillColor.r || locTextFillColor.g !== fillColor.g || locTextFillColor.b !== fillColor.b) {
            locTextFillColor.r = fillColor.r;
            locTextFillColor.g = fillColor.g;
            locTextFillColor.b = fillColor.b;
            this._renderCmd._setColorsString();
            this._needUpdateTexture = true;
        }
    },

    _getFillStyle: function () {
        return this._textFillColor;
    },

    //set the text definition for this label
    _updateWithTextDefinition: function (textDefinition, mustUpdateTexture) {
        if (textDefinition.fontDimensions) {
            this._dimensions.width = textDefinition.boundingWidth;
            this._dimensions.height = textDefinition.boundingHeight;
        } else {
            this._dimensions.width = 0;
            this._dimensions.height = 0;
        }

        this._hAlignment = textDefinition.textAlign;
        this._vAlignment = textDefinition.verticalAlign;

        this._fontName = textDefinition.fontName;
        this._fontSize = textDefinition.fontSize || 12;

        if(textDefinition.lineHeight)
            this._lineHeight = textDefinition.lineHeight
        else
            this._lineHeight = this._fontSize;

        this._renderCmd._setFontStyle(textDefinition);


        // shadow
        if (textDefinition.shadowEnabled)
            this.enableShadow(textDefinition.shadowOffsetX,
                textDefinition.shadowOffsetY,
                textDefinition.shadowOpacity,
                textDefinition.shadowBlur);

        // stroke
        if (textDefinition.strokeEnabled)
            this.enableStroke(textDefinition.strokeStyle, textDefinition.lineWidth);

        // fill color
        this.setFontFillColor(textDefinition.fillStyle);

        if (mustUpdateTexture)
            this._renderCmd._updateTexture();
        var flags = cc.Node._dirtyFlags;
        this._renderCmd.setDirtyFlag(flags.colorDirty|flags.opacityDirty|flags.textDirty);
    },

    _prepareTextDefinition: function (adjustForResolution) {
        var texDef = new cc.FontDefinition();

        if (adjustForResolution) {
            texDef.fontSize = this._fontSize;
            texDef.boundingWidth = cc.contentScaleFactor() * this._dimensions.width;
            texDef.boundingHeight = cc.contentScaleFactor() * this._dimensions.height;
        } else {
            texDef.fontSize = this._fontSize;
            texDef.boundingWidth = this._dimensions.width;
            texDef.boundingHeight = this._dimensions.height;
        }

        texDef.fontName = this._fontName;
        texDef.textAlign = this._hAlignment;
        texDef.verticalAlign = this._vAlignment;

        // stroke
        if (this._strokeEnabled) {
            texDef.strokeEnabled = true;
            var locStrokeColor = this._strokeColor;
            texDef.strokeStyle = cc.color(locStrokeColor.r, locStrokeColor.g, locStrokeColor.b);
            texDef.lineWidth = this._strokeSize;
        } else
            texDef.strokeEnabled = false;

        // shadow
        if (this._shadowEnabled) {
            texDef.shadowEnabled = true;
            texDef.shadowBlur = this._shadowBlur;
            texDef.shadowOpacity = this._shadowOpacity;

            texDef.shadowOffsetX = (adjustForResolution ? cc.contentScaleFactor() : 1) * this._shadowOffset.x;
            texDef.shadowOffsetY = (adjustForResolution ? cc.contentScaleFactor() : 1) * this._shadowOffset.y;
        } else
            texDef._shadowEnabled = false;

        // text tint
        var locTextFillColor = this._textFillColor;
        texDef.fillStyle = cc.color(locTextFillColor.r, locTextFillColor.g, locTextFillColor.b);
        return texDef;
    },

    /**
     * Changes the text content of the label
     * @warning Changing the string is as expensive as creating a new cc.LabelTTF. To obtain better performance use cc.LabelAtlas
     * @param {String} text Text content for the label
     */
    setString: function (text) {
        text = String(text);
        if (this._originalText !== text) {
            this._originalText = text + "";

            this._updateString();

            // Force update
            this._setUpdateTextureDirty();
            this._renderCmd.setDirtyFlag(cc.Node._dirtyFlags.transformDirty);
        }
    },
    _updateString: function () {
        if ((!this._string || this._string === "") && this._string !== this._originalText)
            cc.renderer.childrenOrderDirty = true;
        this._string = this._originalText;
    },

    /**
     * Sets Horizontal Alignment of cc.LabelTTF
     * @param {cc.TEXT_ALIGNMENT_LEFT|cc.TEXT_ALIGNMENT_CENTER|cc.TEXT_ALIGNMENT_RIGHT} alignment Horizontal Alignment
     */
    setHorizontalAlignment: function (alignment) {
        if (alignment !== this._hAlignment) {
            this._hAlignment = alignment;
            // Force update
            this._setUpdateTextureDirty();
        }
    },

    /**
     * Sets Vertical Alignment of cc.LabelTTF
     * @param {cc.VERTICAL_TEXT_ALIGNMENT_TOP|cc.VERTICAL_TEXT_ALIGNMENT_CENTER|cc.VERTICAL_TEXT_ALIGNMENT_BOTTOM} verticalAlignment
     */
    setVerticalAlignment: function (verticalAlignment) {
        if (verticalAlignment !== this._vAlignment) {
            this._vAlignment = verticalAlignment;

            // Force update
            this._setUpdateTextureDirty();
        }
    },

    /**
     * Set Dimensions of cc.LabelTTF, the dimension is the maximum size of the label, set it so that label will automatically change lines when necessary.
     * @param {cc.Size|Number} dim dimensions or width of dimensions
     * @param {Number} [height] height of dimensions
     */
    setDimensions: function (dim, height) {
        var width;
        if (height === undefined) {
            width = dim.width;
            height = dim.height;
        } else
            width = dim;

        if (width !== this._dimensions.width || height !== this._dimensions.height) {
            this._dimensions.width = width;
            this._dimensions.height = height;
            this._updateString();
            // Force update
            this._setUpdateTextureDirty();
        }
    },

    _getBoundingWidth: function () {
        return this._dimensions.width;
    },
    _setBoundingWidth: function (width) {
        if (width !== this._dimensions.width) {
            this._dimensions.width = width;
            this._updateString();
            // Force update
            this._setUpdateTextureDirty();
        }
    },

    _getBoundingHeight: function () {
        return this._dimensions.height;
    },
    _setBoundingHeight: function (height) {
        if (height !== this._dimensions.height) {
            this._dimensions.height = height;
            this._updateString();
            // Force update
            this._setUpdateTextureDirty();
        }
    },

    /**
     * Sets font size of cc.LabelTTF
     * @param {Number} fontSize
     */
    setFontSize: function (fontSize) {
        if (this._fontSize !== fontSize) {
            this._fontSize = fontSize;
            this._renderCmd._setFontStyle(this._fontName, this._fontSize, this._fontStyle, this._fontWeight);
            // Force update
            this._setUpdateTextureDirty();
        }
    },

    /**
     * Sets font name of cc.LabelTTF
     * @param {String} fontName
     */
    setFontName: function (fontName) {
        if (this._fontName && this._fontName !== fontName) {
            this._fontName = fontName;
            this._renderCmd._setFontStyle(this._fontName, this._fontSize, this._fontStyle, this._fontWeight);
            // Force update
            this._setUpdateTextureDirty();
        }
    },

    _getFont: function () {
        return this._renderCmd._getFontStyle();
    },
    _setFont: function (fontStyle) {
        var res = cc.LabelTTF._fontStyleRE.exec(fontStyle);
        if (res) {
            this._fontSize = parseInt(res[1]);
            this._fontName = res[2];
            this._renderCmd._setFontStyle(this._fontName, this._fontSize, this._fontStyle, this._fontWeight);

            // Force update
            this._setUpdateTextureDirty();
        }
    },

    /**
     * Returns the actual content size of the label, the content size is the real size that the label occupied while dimension is the outer bounding box of the label.
     * @returns {cc.Size} The content size
     */
    getContentSize: function () {
        if (this._needUpdateTexture)
            this._renderCmd._updateTTF();
        return cc.Sprite.prototype.getContentSize.call(this);
    },

    _getWidth: function () {
        if (this._needUpdateTexture)
            this._renderCmd._updateTTF();
        return cc.Sprite.prototype._getWidth.call(this);
    },
    _getHeight: function () {
        if (this._needUpdateTexture)
            this._renderCmd._updateTTF();
        return cc.Sprite.prototype._getHeight.call(this);
    },

    setTextureRect: function (rect, rotated, untrimmedSize) {
        //set needConvert to false
        cc.Sprite.prototype.setTextureRect.call(this, rect, rotated, untrimmedSize, false);
    },

    _createRenderCmd: function () {
        if (cc._renderType === cc._RENDER_TYPE_CANVAS)
            return new cc.LabelTTF.CanvasRenderCmd(this);
        else
            return new cc.LabelTTF.WebGLRenderCmd(this);
    },

    //For web only
    _setFontStyle: function(fontStyle){
        if (this._fontStyle !== fontStyle) {
            this._fontStyle = fontStyle;
            this._renderCmd._setFontStyle(this._fontName, this._fontSize, this._fontStyle, this._fontWeight);
            this._setUpdateTextureDirty();
        }
    },

    _getFontStyle: function(){
        return this._fontStyle;
    },

    _setFontWeight: function(fontWeight){
        if (this._fontWeight !== fontWeight) {
            this._fontWeight = fontWeight;
            this._renderCmd._setFontStyle(this._fontName, this._fontSize, this._fontStyle, this._fontWeight);
            this._setUpdateTextureDirty();
        }
    },

    _getFontWeight: function(){
        return this._fontWeight;
    }
});

cc.assert(cc.isFunction(cc._tmp.PrototypeLabelTTF), cc._LogInfos.MissingFile, "LabelTTFPropertyDefine.js");
cc._tmp.PrototypeLabelTTF();
delete cc._tmp.PrototypeLabelTTF;

// Only support style in this format: "18px Verdana" or "18px 'Helvetica Neue'"
cc.LabelTTF._fontStyleRE = /^(\d+)px\s+['"]?([\w\s\d]+)['"]?$/;

/**
 * creates a cc.LabelTTF from a font name, alignment, dimension and font size
 * @deprecated since v3.0, please use the new construction instead
 * @see cc.LabelTTF
 * @static
 * @param {String} text
 * @param {String|cc.FontDefinition} [fontName="Arial"]
 * @param {Number} [fontSize=16]
 * @param {cc.Size} [dimensions=cc.size(0,0)]
 * @param {Number} [hAlignment=cc.TEXT_ALIGNMENT_LEFT]
 * @param {Number} [vAlignment=cc.VERTICAL_TEXT_ALIGNMENT_TOP]
 * @return {cc.LabelTTF|Null}
 */
cc.LabelTTF.create = function (text, fontName, fontSize, dimensions, hAlignment, vAlignment) {
    return new cc.LabelTTF(text, fontName, fontSize, dimensions, hAlignment, vAlignment);
};

/**
 * @deprecated since v3.0, please use the new construction instead
 * @function
 * @static
 */
cc.LabelTTF.createWithFontDefinition = cc.LabelTTF.create;

if (cc.USE_LA88_LABELS)
    cc.LabelTTF._SHADER_PROGRAM = cc.SHADER_POSITION_TEXTURECOLOR;
else
    cc.LabelTTF._SHADER_PROGRAM = cc.SHADER_POSITION_TEXTUREA8COLOR;

cc.LabelTTF.__labelHeightDiv = cc.newElement("div");
cc.LabelTTF.__labelHeightDiv.style.fontFamily = "Arial";
cc.LabelTTF.__labelHeightDiv.style.position = "absolute";
cc.LabelTTF.__labelHeightDiv.style.left = "-100px";
cc.LabelTTF.__labelHeightDiv.style.top = "-100px";
cc.LabelTTF.__labelHeightDiv.style.lineHeight = "normal";

document.body ?
    document.body.appendChild(cc.LabelTTF.__labelHeightDiv) :
    cc._addEventListener(window, 'load', function () {
        this.removeEventListener('load', arguments.callee, false);
        document.body.appendChild(cc.LabelTTF.__labelHeightDiv);
    }, false);

cc.LabelTTF.__getFontHeightByDiv = function (fontName, fontSize) {

    if(fontName instanceof cc.FontDefinition){
        /** @type cc.FontDefinition */
        var fontDef = fontName;
        var clientHeight = cc.LabelTTF.__fontHeightCache[fontDef._getCanvasFontStr()];
        if (clientHeight > 0) return clientHeight;
        var labelDiv = cc.LabelTTF.__labelHeightDiv;
        labelDiv.innerHTML = "ajghl~!";
        labelDiv.style.fontFamily = fontDef.fontName;
        labelDiv.style.fontSize = fontDef.fontSize + "px";
        labelDiv.style.fontStyle = fontDef.fontStyle;
        labelDiv.style.fontWeight = fontDef.fontWeight;

        clientHeight = labelDiv.clientHeight;
        cc.LabelTTF.__fontHeightCache[fontDef._getCanvasFontStr()] = clientHeight;
        labelDiv.innerHTML = "";
        return clientHeight;
    }

    //Default
    var clientHeight = cc.LabelTTF.__fontHeightCache[fontName + "." + fontSize];
    if (clientHeight > 0) return clientHeight;
    var labelDiv = cc.LabelTTF.__labelHeightDiv;
    labelDiv.innerHTML = "ajghl~!";
    labelDiv.style.fontFamily = fontName;
    labelDiv.style.fontSize = fontSize + "px";
    clientHeight = labelDiv.clientHeight;
    cc.LabelTTF.__fontHeightCache[fontName + "." + fontSize] = clientHeight;
    labelDiv.innerHTML = "";
    return clientHeight;

};

cc.LabelTTF.__fontHeightCache = {};