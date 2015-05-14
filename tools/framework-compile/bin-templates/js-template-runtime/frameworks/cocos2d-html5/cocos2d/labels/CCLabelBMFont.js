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

 Use any of these editors to generate BMFonts:
 http://glyphdesigner.71squared.com/ (Commercial, Mac OS X)
 http://www.n4te.com/hiero/hiero.jnlp (Free, Java)
 http://slick.cokeandcode.com/demos/hiero.jnlp (Free, Java)
 http://www.angelcode.com/products/bmfont/ (Free, Windows only)
 ****************************************************************************/
/**
 * @constant
 * @type Number
 */
cc.LABEL_AUTOMATIC_WIDTH = -1;

/**
 * <p>cc.LabelBMFont is a subclass of cc.SpriteBatchNode.</p>
 *
 * <p>Features:<br/>
 * <ul><li>- Treats each character like a cc.Sprite. This means that each individual character can be:</li>
 * <li>- rotated</li>
 * <li>- scaled</li>
 * <li>- translated</li>
 * <li>- tinted</li>
 * <li>- change the opacity</li>
 * <li>- It can be used as part of a menu item.</li>
 * <li>- anchorPoint can be used to align the "label"</li>
 * <li>- Supports AngelCode text format</li></ul></p>
 *
 * <p>Limitations:<br/>
 * - All inner characters are using an anchorPoint of (0.5, 0.5) and it is not recommend to change it
 * because it might affect the rendering</p>
 *
 * <p>cc.LabelBMFont implements the protocol cc.LabelProtocol, like cc.Label and cc.LabelAtlas.<br/>
 * cc.LabelBMFont has the flexibility of cc.Label, the speed of cc.LabelAtlas and all the features of cc.Sprite.<br/>
 * If in doubt, use cc.LabelBMFont instead of cc.LabelAtlas / cc.Label.</p>
 *
 * <p>Supported editors:<br/>
 * http://glyphdesigner.71squared.com/ (Commercial, Mac OS X)<br/>
 * http://www.n4te.com/hiero/hiero.jnlp (Free, Java)<br/>
 * http://slick.cokeandcode.com/demos/hiero.jnlp (Free, Java)<br/>
 * http://www.angelcode.com/products/bmfont/ (Free, Windows only)</p>
 * @class
 * @extends cc.SpriteBatchNode
 *
 * @property {String}   string          - Content string of label
 * @property {Number}   textAlign       - Horizontal Alignment of label, cc.TEXT_ALIGNMENT_LEFT|cc.TEXT_ALIGNMENT_CENTER|cc.TEXT_ALIGNMENT_RIGHT
 * @property {Number}   boundingWidth   - Width of the bounding box of label, the real content width is limited by boundingWidth
 *
 * @param {String} str
 * @param {String} fntFile
 * @param {Number} [width=-1]
 * @param {Number} [alignment=cc.TEXT_ALIGNMENT_LEFT]
 * @param {cc.Point} [imageOffset=cc.p(0,0)]
 *
 * @example
 * // Example 01
 * var label1 = new cc.LabelBMFont("Test case", "test.fnt");
 *
 * // Example 02
 * var label2 = new cc.LabelBMFont("test case", "test.fnt", 200, cc.TEXT_ALIGNMENT_LEFT);
 *
 * // Example 03
 * var label3 = new cc.LabelBMFont("This is a \n test case", "test.fnt", 200, cc.TEXT_ALIGNMENT_LEFT, cc.p(0,0));
 */
cc.LabelBMFont = cc.SpriteBatchNode.extend(/** @lends cc.LabelBMFont# */{
    //property string is Getter and Setter.
    //property textAlign is Getter and Setter.
    //property boundingWidth is Getter and Setter.
    _opacityModifyRGB: false,

    _string: "",
    _config: null,

    // name of fntFile
    _fntFile: "",

    // initial string without line breaks
    _initialString: "",

    // alignment of all lines
    _alignment: cc.TEXT_ALIGNMENT_CENTER,

    // max width until a line break is added
    _width: -1,
    _lineBreakWithoutSpaces: false,
    _imageOffset: null,

    _reusedChar: null,

    _textureLoaded: false,
    _className: "LabelBMFont",

    _createRenderCmd: function(){
        if(cc._renderType === cc._RENDER_TYPE_WEBGL)
            return new cc.LabelBMFont.WebGLRenderCmd(this);
        else
            return new cc.LabelBMFont.CanvasRenderCmd(this);
    },

    _setString: function (newString, needUpdateLabel) {
        if (!needUpdateLabel) {
            this._string = newString;
        } else {
            this._initialString = newString;
        }
        var locChildren = this._children;
        if (locChildren) {
            for (var i = 0; i < locChildren.length; i++) {
                var selNode = locChildren[i];
                if (selNode)
                    selNode.setVisible(false);
            }
        }
        if (this._textureLoaded) {
            this.createFontChars();
            if (needUpdateLabel)
                this.updateLabel();
        }
    },

    /**
     * Constructor function, override it to extend the construction behavior, remember to call "this._super()" in the extended "ctor" function. <br />
     * creates a bitmap font atlas with an initial string and the FNT file.
     * @param {String} str
     * @param {String} fntFile
     * @param {Number} [width=-1]
     * @param {Number} [alignment=cc.TEXT_ALIGNMENT_LEFT]
     * @param {cc.Point} [imageOffset=cc.p(0,0)]
     */
    ctor: function (str, fntFile, width, alignment, imageOffset) {
        cc.SpriteBatchNode.prototype.ctor.call(this);
        this._imageOffset = cc.p(0, 0);
        this._reusedChar = [];
        this._cascadeColorEnabled = true;
        this._cascadeOpacityEnabled = true;
        this.initWithString(str, fntFile, width, alignment, imageOffset);
    },

    /**
     * return  texture is loaded
     * @returns {boolean}
     */
    textureLoaded: function () {
        return this._textureLoaded;
    },

    /**
     * add texture loaded event listener. <br />
     * Will execute the callback in the loaded.
     * @param {Function} callback
     * @param {Object} target
     * @deprecated since 3.1, please use addEventListener instead
     */
    addLoadedEventListener: function (callback, target) {
        this.addEventListener("load", callback, target);
    },

    /**
     * Conforms to cc.RGBAProtocol protocol.
     * @return {Boolean}
     */
    isOpacityModifyRGB: function () {
        return this._opacityModifyRGB;
    },

    /**
     * Set whether to support cc.RGBAProtocol protocol
     * @param {Boolean} opacityModifyRGB
     */
    setOpacityModifyRGB: function (opacityModifyRGB) {
        this._opacityModifyRGB = opacityModifyRGB;
        var locChildren = this._children;
        if (locChildren) {
            for (var i = 0; i < locChildren.length; i++) {
                var node = locChildren[i];
                if (node)
                    node.opacityModifyRGB = this._opacityModifyRGB;
            }
        }
    },

    _changeTextureColor: function () {
        this._renderCmd._changeTextureColor();
    },

    /**
     * Initialization of the node, please do not call this function by yourself, you should pass the parameters to constructor to initialize it .
     */
    init: function () {
        return this.initWithString(null, null, null, null, null);
    },

    /**
     * init a bitmap font atlas with an initial string and the FNT file
     * @param {String} str
     * @param {String} fntFile
     * @param {Number} [width=-1]
     * @param {Number} [alignment=cc.TEXT_ALIGNMENT_LEFT]
     * @param {cc.Point} [imageOffset=cc.p(0,0)]
     * @return {Boolean}
     */
    initWithString: function (str, fntFile, width, alignment, imageOffset) {
        var self = this, theString = str || "";
        var cmd = this._renderCmd;

        if (self._config)
            cc.log("cc.LabelBMFont.initWithString(): re-init is no longer supported");

        var texture;
        if (fntFile) {
            var newConf = cc.loader.getRes(fntFile);
            if (!newConf) {
                cc.log("cc.LabelBMFont.initWithString(): Impossible to create font. Please check file");
                return false;
            }

            self._config = newConf;
            self._fntFile = fntFile;
            texture = cc.textureCache.addImage(newConf.atlasName);
            var locIsLoaded = texture.isLoaded();
            self._textureLoaded = locIsLoaded;
            if (!locIsLoaded) {
                texture.addEventListener("load", function (sender) {
                    var self1 = this;
                    self1._textureLoaded = true;
                    //reset the LabelBMFont
                    self1.initWithTexture(sender, self1._initialString.length);
                    self1.setString(self1._initialString, true);
                    self1.dispatchEvent("load");
                }, self);
            }
        } else {
            texture = new cc.Texture2D();
            var image = new Image();
            texture.initWithElement(image);
            self._textureLoaded = false;
        }

        if (self.initWithTexture(texture, theString.length)) {
            self._alignment = alignment || cc.TEXT_ALIGNMENT_LEFT;
            self._imageOffset = imageOffset || cc.p(0, 0);
            self._width = (width == null) ? -1 : width;

            self._realOpacity = 255;
            self._realColor = cc.color(255, 255, 255, 255);

            self._contentSize.width = 0;
            self._contentSize.height = 0;

            self.setAnchorPoint(0.5, 0.5);

            this._renderCmd._initBatchTexture();

            self.setString(theString, true);
            return true;
        }
        return false;
    },

    /**
     * updates the font chars based on the string to render
     */
    createFontChars: function () {
        var self = this;
        var cmd = this._renderCmd;
        var locTexture = cmd._texture || self.textureAtlas.texture;

        var nextFontPositionX = 0;

        var tmpSize = cc.size(0, 0);

        var longestLine = 0;

        var quantityOfLines = 1;

        var locStr = self._string;
        var stringLen = locStr ? locStr.length : 0;

        if (stringLen === 0)
            return;

        var i, locCfg = self._config, locKerningDict = locCfg.kerningDict,
            locCommonH = locCfg.commonHeight, locFontDict = locCfg.fontDefDictionary;
        for (i = 0; i < stringLen - 1; i++) {
            if (locStr.charCodeAt(i) === 10) quantityOfLines++;
        }

        var totalHeight = locCommonH * quantityOfLines;
        var nextFontPositionY = -(locCommonH - locCommonH * quantityOfLines);

        var prev = -1;
        for (i = 0; i < stringLen; i++) {
            var key = locStr.charCodeAt(i);
            if (key === 0) continue;

            if (key === 10) {
                //new line
                nextFontPositionX = 0;
                nextFontPositionY -= locCfg.commonHeight;
                continue;
            }

            var kerningAmount = locKerningDict[(prev << 16) | (key & 0xffff)] || 0;
            var fontDef = locFontDict[key];
            if (!fontDef) {
                cc.log("cocos2d: LabelBMFont: character not found " + locStr[i]);
                continue;
            }

            var rect = cc.rect(fontDef.rect.x, fontDef.rect.y, fontDef.rect.width, fontDef.rect.height);
            rect = cc.rectPixelsToPoints(rect);
            rect.x += self._imageOffset.x;
            rect.y += self._imageOffset.y;

            var fontChar = self.getChildByTag(i);

            if(!fontChar){
                fontChar = new cc.Sprite();
                fontChar.initWithTexture(locTexture, rect, false);
                fontChar._newTextureWhenChangeColor = true;
                this.addChild(fontChar, 0, i);
            }else{
                this._renderCmd._updateCharTexture(fontChar, rect, key);
            }

            // Apply label properties
            fontChar.opacityModifyRGB = this._opacityModifyRGB;
            this._renderCmd._updateCharColorAndOpacity(fontChar);

            var yOffset = locCfg.commonHeight - fontDef.yOffset;
            var fontPos = cc.p(nextFontPositionX + fontDef.xOffset + fontDef.rect.width * 0.5 + kerningAmount,
                nextFontPositionY + yOffset - rect.height * 0.5 * cc.contentScaleFactor());
            fontChar.setPosition(cc.pointPixelsToPoints(fontPos));

            // update kerning
            nextFontPositionX += fontDef.xAdvance + kerningAmount;
            prev = key;

            if (longestLine < nextFontPositionX)
                longestLine = nextFontPositionX;
        }

        //If the last character processed has an xAdvance which is less that the width of the characters image, then we need
        // to adjust the width of the string to take this into account, or the character will overlap the end of the bounding box
        if(fontDef && fontDef.xAdvance < fontDef.rect.width)
            tmpSize.width = longestLine - fontDef.xAdvance + fontDef.rect.width;
        else
            tmpSize.width = longestLine;
        tmpSize.height = totalHeight;
        self.setContentSize(cc.sizePixelsToPoints(tmpSize));
    },

    /**
     * Update String. <br />
     * Only update this label display string.
     * @param {Boolean} fromUpdate
     */
    updateString: function (fromUpdate) {
        var self = this;
        var locChildren = self._children;
        if (locChildren) {
            for (var i = 0, li = locChildren.length; i < li; i++) {
                var node = locChildren[i];
                if (node) node.visible = false;
            }
        }
        if (self._config)
            self.createFontChars();

        if (!fromUpdate)
            self.updateLabel();
    },

    /**
     * Gets the text of this label
     * @return {String}
     */
    getString: function () {
        return this._initialString;
    },

    /**
     * Set the text
     * @param {String} newString
     * @param {Boolean|null} needUpdateLabel
     */
    setString: function (newString, needUpdateLabel) {
        newString = String(newString);
        if (needUpdateLabel == null)
            needUpdateLabel = true;
        if (newString == null || !cc.isString(newString))
            newString = newString + "";

        this._initialString = newString;
        this._setString(newString, needUpdateLabel);
    },

    _setStringForSetter: function (newString) {
        this.setString(newString, false);
    },

    /**
     * Set the text. <br />
     * Change this Label display string.
     * @deprecated since v3.0 please use .setString
     * @param label
     */
    setCString: function (label) {
        this.setString(label, true);
    },

    // calc the text all with in a line
    _getCharsWidth:function (startIndex, endIndex) {
        if (endIndex <= 0)
        {
            return 0;
        }
        var curTextFirstSprite = this.getChildByTag(startIndex);
        var curTextLastSprite = this.getChildByTag(startIndex + endIndex);
        return this._getLetterPosXLeft(curTextLastSprite) - this._getLetterPosXLeft(curTextFirstSprite);
    },

    _checkWarp:function (strArr, i, maxWidth, initStringWrapNum) {
        var self = this;
        var text = strArr[i];
        var curLength = 0;
        for (var strArrIndex = 0; strArrIndex < i; strArrIndex++)
        {
            curLength += strArr[strArrIndex].length;
        }

        curLength = curLength + i - initStringWrapNum; // add the wrap line num

        var allWidth = self._getCharsWidth(curLength, strArr[i].length - 1);

        if (allWidth > maxWidth && text.length > 1) {
            var fuzzyLen = text.length * ( maxWidth / allWidth ) | 0;
            var tmpText = text.substr(fuzzyLen);
            var width = allWidth - this._getCharsWidth(curLength + fuzzyLen, tmpText.length - 1);
            var sLine;
            var pushNum = 0;

            //Increased while cycle maximum ceiling. default 100 time
            var checkWhile = 0;

            //Exceeded the size
            while (width > maxWidth && checkWhile++ < 100) {
                fuzzyLen *= maxWidth / width;
                fuzzyLen = fuzzyLen | 0;
                tmpText = text.substr(fuzzyLen);
                width = allWidth - this._getCharsWidth(curLength + fuzzyLen, tmpText.length - 1);
            }

            checkWhile = 0;

            //Find the truncation point
            while (width < maxWidth && checkWhile++ < 100) {
                if (tmpText) {
                    var exec = cc.LabelTTF._wordRex.exec(tmpText);
                    pushNum = exec ? exec[0].length : 1;
                    sLine = tmpText;
                }
                if (self._lineBreakWithoutSpaces) {
                    pushNum = 0;
                }
                fuzzyLen = fuzzyLen + pushNum;
                tmpText = text.substr(fuzzyLen);
                width = allWidth - this._getCharsWidth(curLength + fuzzyLen, tmpText.length - 1);
            }

            fuzzyLen -= pushNum;
            if (fuzzyLen === 0) {
                fuzzyLen = 1;
                sLine = sLine.substr(1);
            }

            var sText = text.substr(0, fuzzyLen), result;

            //symbol in the first
            if (cc.LabelTTF.wrapInspection) {
                if (cc.LabelTTF._symbolRex.test(sLine || tmpText)) {
                    result = cc.LabelTTF._lastWordRex.exec(sText);
                    pushNum = result ? result[0].length : 0;
                    if (self._lineBreakWithoutSpaces) {
                        pushNum = 0;
                    }
                    fuzzyLen -= pushNum;

                    sLine = text.substr(fuzzyLen);
                    sText = text.substr(0, fuzzyLen);
                }
            }

            //To judge whether a English words are truncated
            if (cc.LabelTTF._firsrEnglish.test(sLine)) {
                result = cc.LabelTTF._lastEnglish.exec(sText);
                if (result && sText !== result[0]) {
                    pushNum = result[0].length;
                    if (self._lineBreakWithoutSpaces) {
                        pushNum = 0;
                    }
                    fuzzyLen -= pushNum;
                    sLine = text.substr(fuzzyLen);
                    sText = text.substr(0, fuzzyLen);
                }
            }
            strArr[i] = sLine || tmpText;
            strArr.splice(i, 0, sText);
        }
    },

    /**
     * Update Label. <br />
     * Update this Label display string and more...
     */
    updateLabel: function () {
        var self = this;
        self.string = self._initialString;
        var i, j, characterSprite;
        // process string
        // Step 1: Make multiline
        if (self._width > 0) {
            var stringArr = self.string.split('\n');
            var wrapString = "";
            var newWrapNum = 0;
            var oldArrLength = 0;
            for (i = 0; i < stringArr.length; i++) {
                oldArrLength = stringArr.length;
                this._checkWarp(stringArr, i, self._width * this._scaleX, newWrapNum);
                if (oldArrLength < stringArr.length) {
                    newWrapNum++;
                }
                if (i > 0)
                {
                    wrapString += "\n";
                }
                wrapString += stringArr[i];
            }
            wrapString = wrapString + String.fromCharCode(0);
            self._setString(wrapString, false);
        }

        // Step 2: Make alignment
        if (self._alignment !== cc.TEXT_ALIGNMENT_LEFT) {
            i = 0;

            var lineNumber = 0;
            var strlen = self._string.length;
            var last_line = [];

            for (var ctr = 0; ctr < strlen; ctr++) {
                if (self._string[ctr].charCodeAt(0) === 10 || self._string[ctr].charCodeAt(0) === 0) {
                    var lineWidth = 0;
                    var line_length = last_line.length;
                    // if last line is empty we must just increase lineNumber and work with next line
                    if (line_length === 0) {
                        lineNumber++;
                        continue;
                    }
                    var index = i + line_length - 1 + lineNumber;
                    if (index < 0) continue;

                    var lastChar = self.getChildByTag(index);
                    if (lastChar == null)
                        continue;
                    lineWidth = lastChar.getPositionX() + lastChar._getWidth() / 2;

                    var shift = 0;
                    switch (self._alignment) {
                        case cc.TEXT_ALIGNMENT_CENTER:
                            shift = self.width / 2 - lineWidth / 2;
                            break;
                        case cc.TEXT_ALIGNMENT_RIGHT:
                            shift = self.width - lineWidth;
                            break;
                        default:
                            break;
                    }

                    if (shift !== 0) {
                        for (j = 0; j < line_length; j++) {
                            index = i + j + lineNumber;
                            if (index < 0) continue;
                            characterSprite = self.getChildByTag(index);
                            if (characterSprite)
                                characterSprite.x += shift;
                        }
                    }

                    i += line_length;
                    lineNumber++;

                    last_line.length = 0;
                    continue;
                }
                last_line.push(self._string[i]);
            }
        }
    },

    /**
     * Set text alignment.
     * @param {Number} alignment
     */
    setAlignment: function (alignment) {
        this._alignment = alignment;
        this.updateLabel();
    },

    _getAlignment: function () {
        return this._alignment;
    },

    /**
     * Set the bounding width. <br />
     * max with display width. The exceeding string will be wrapping.
     * @param {Number} width
     */
    setBoundingWidth: function (width) {
        this._width = width;
        this.updateLabel();
    },

    _getBoundingWidth: function () {
        return this._width;
    },

    /**
     * Set the param to change English word warp according to whether the space. <br />
     * default is false.
     * @param {Boolean}  breakWithoutSpace
     */
    setLineBreakWithoutSpace: function (breakWithoutSpace) {
        this._lineBreakWithoutSpaces = breakWithoutSpace;
        this.updateLabel();
    },

    /**
     * Set scale. <br />
     * Input a number, will be decrease or increase the font size. <br />
     * @param {Number} scale
     * @param {Number} [scaleY=null] default is scale
     */
    setScale: function (scale, scaleY) {
        cc.Node.prototype.setScale.call(this, scale, scaleY);
        this.updateLabel();
    },

    /**
     * Set scale of x. <br />
     * Input a number, will be decrease or increase the font size. <br />
     * Horizontal scale.
     * @param {Number} scaleX
     */
    setScaleX: function (scaleX) {
        cc.Node.prototype.setScaleX.call(this, scaleX);
        this.updateLabel();
    },

    /**
     * Set scale of x. <br />
     * Input a number, will be decrease or increase the font size. <br />
     * Longitudinal scale.
     * @param {Number} scaleY
     */
    setScaleY: function (scaleY) {
        cc.Node.prototype.setScaleY.call(this, scaleY);
        this.updateLabel();
    },

    /**
     * set fnt file path. <br />
     * Change the fnt file path.
     * @param {String} fntFile
     */
    setFntFile: function (fntFile) {
        var self = this;
        if (fntFile != null && fntFile !== self._fntFile) {
            var newConf = cc.loader.getRes(fntFile);

            if (!newConf) {
                cc.log("cc.LabelBMFont.setFntFile() : Impossible to create font. Please check file");
                return;
            }

            self._fntFile = fntFile;
            self._config = newConf;

            var texture = cc.textureCache.addImage(newConf.atlasName);
            var locIsLoaded = texture.isLoaded();
            self._textureLoaded = locIsLoaded;
            self.texture = texture;
            this._renderCmd._updateFntFileTexture();
            if (!locIsLoaded) {
                texture.addEventListener("load", function (sender) {
                    var self1 = this;
                    self1._textureLoaded = true;
                    self1.texture = sender;
                    self1.createFontChars();
                    self1._changeTextureColor();
                    self1.updateLabel();

                    self1.dispatchEvent("load");
                }, self);
            } else {
                self.createFontChars();
            }
        }
    },

    /**
     * Return the fnt file path.
     * @return {String}
     */
    getFntFile: function () {
        return this._fntFile;
    },

    setTexture: function(texture){
        this._renderCmd.setTexture(texture);
    },

    /**
     * Set the AnchorPoint of the labelBMFont. <br />
     * In order to change the location of label.
     * @override
     * @param {cc.Point|Number} point The anchor point of labelBMFont or The anchor point.x of labelBMFont.
     * @param {Number} [y] The anchor point.y of labelBMFont.
     */
    setAnchorPoint: function (point, y) {
        cc.Node.prototype.setAnchorPoint.call(this, point, y);
        this.updateLabel();
    },

    _setAnchorX: function (x) {
        cc.Node.prototype._setAnchorX.call(this, x);
        this.updateLabel();
    },

    _setAnchorY: function (y) {
        cc.Node.prototype._setAnchorY.call(this, y);
        this.updateLabel();
    },

    _atlasNameFromFntFile: function (fntFile) {},

    _kerningAmountForFirst: function (first, second) {
        var ret = 0;
        var key = (first << 16) | (second & 0xffff);
        if (this._configuration.kerningDictionary) {
            var element = this._configuration.kerningDictionary[key.toString()];
            if (element)
                ret = element.amount;
        }
        return ret;
    },

    _getLetterPosXLeft: function (sp) {
        return sp.getPositionX() * this._scaleX - (sp._getWidth() * this._scaleX * sp._getAnchorX());
    },

    _getLetterPosXRight: function (sp) {
        return sp.getPositionX() * this._scaleX + (sp._getWidth() * this._scaleX * sp._getAnchorX());
    },

    //Checking whether the character is a whitespace
    _isspace_unicode: function(ch){
        ch = ch.charCodeAt(0);
        return  ((ch >= 9 && ch <= 13) || ch === 32 || ch === 133 || ch === 160 || ch === 5760
            || (ch >= 8192 && ch <= 8202) || ch === 8232 || ch === 8233 || ch === 8239
            || ch === 8287 || ch === 12288)
    },

    _utf8_trim_ws: function(str){
        var len = str.length;

        if (len <= 0)
            return;

        var last_index = len - 1;

        // Only start trimming if the last character is whitespace..
        if (this._isspace_unicode(str[last_index])) {
            for (var i = last_index - 1; i >= 0; --i) {
                if (this._isspace_unicode(str[i])) {
                    last_index = i;
                }
                else {
                    break;
                }
            }
            this._utf8_trim_from(str, last_index);
        }
    },

    //Trims str st str=[0, index) after the operation.
    //Return value: the trimmed string.
    _utf8_trim_from: function(str, index){
        var len = str.length;
        if (index >= len || index < 0)
            return;
        str.splice(index, len);
    }
});

(function(){
    var p = cc.LabelBMFont.prototype;
    cc.EventHelper.prototype.apply(p);

    /** @expose */
    p.string;
    cc.defineGetterSetter(p, "string", p.getString, p._setStringForSetter);
    /** @expose */
    p.boundingWidth;
    cc.defineGetterSetter(p, "boundingWidth", p._getBoundingWidth, p.setBoundingWidth);
    /** @expose */
    p.textAlign;
    cc.defineGetterSetter(p, "textAlign", p._getAlignment, p.setAlignment);
})();

/**
 * creates a bitmap font atlas with an initial string and the FNT file
 * @deprecated since v3.0 please use new cc.LabelBMFont
 * @param {String} str
 * @param {String} fntFile
 * @param {Number} [width=-1]
 * @param {Number} [alignment=cc.TEXT_ALIGNMENT_LEFT]
 * @param {cc.Point} [imageOffset=cc.p(0,0)]
 * @return {cc.LabelBMFont|Null}
 */
cc.LabelBMFont.create = function (str, fntFile, width, alignment, imageOffset) {
    return new cc.LabelBMFont(str, fntFile, width, alignment, imageOffset);
};

cc._fntLoader = {
    INFO_EXP: /info [^\n]*(\n|$)/gi,
    COMMON_EXP: /common [^\n]*(\n|$)/gi,
    PAGE_EXP: /page [^\n]*(\n|$)/gi,
    CHAR_EXP: /char [^\n]*(\n|$)/gi,
    KERNING_EXP: /kerning [^\n]*(\n|$)/gi,
    ITEM_EXP: /\w+=[^ \r\n]+/gi,
    INT_EXP: /^[\-]?\d+$/,

    _parseStrToObj: function (str) {
        var arr = str.match(this.ITEM_EXP);
        var obj = {};
        if (arr) {
            for (var i = 0, li = arr.length; i < li; i++) {
                var tempStr = arr[i];
                var index = tempStr.indexOf("=");
                var key = tempStr.substring(0, index);
                var value = tempStr.substring(index + 1);
                if (value.match(this.INT_EXP)) value = parseInt(value);
                else if (value[0] === '"') value = value.substring(1, value.length - 1);
                obj[key] = value;
            }
        }
        return obj;
    },

    /**
     * Parse Fnt string.
     * @param fntStr
     * @param url
     * @returns {{}}
     */
    parseFnt: function (fntStr, url) {
        var self = this, fnt = {};
        //padding
        var infoObj = self._parseStrToObj(fntStr.match(self.INFO_EXP)[0]);
        var paddingArr = infoObj["padding"].split(",");
        var padding = {
            left: parseInt(paddingArr[0]),
            top: parseInt(paddingArr[1]),
            right: parseInt(paddingArr[2]),
            bottom: parseInt(paddingArr[3])
        };

        //common
        var commonObj = self._parseStrToObj(fntStr.match(self.COMMON_EXP)[0]);
        fnt.commonHeight = commonObj["lineHeight"];
        if (cc._renderType === cc._RENDER_TYPE_WEBGL) {
            var texSize = cc.configuration.getMaxTextureSize();
            if (commonObj["scaleW"] > texSize.width || commonObj["scaleH"] > texSize.height)
                cc.log("cc.LabelBMFont._parseCommonArguments(): page can't be larger than supported");
        }
        if (commonObj["pages"] !== 1) cc.log("cc.LabelBMFont._parseCommonArguments(): only supports 1 page");

        //page
        var pageObj = self._parseStrToObj(fntStr.match(self.PAGE_EXP)[0]);
        if (pageObj["id"] !== 0) cc.log("cc.LabelBMFont._parseImageFileName() : file could not be found");
        fnt.atlasName = cc.path.changeBasename(url, pageObj["file"]);

        //char
        var charLines = fntStr.match(self.CHAR_EXP);
        var fontDefDictionary = fnt.fontDefDictionary = {};
        for (var i = 0, li = charLines.length; i < li; i++) {
            var charObj = self._parseStrToObj(charLines[i]);
            var charId = charObj["id"];
            fontDefDictionary[charId] = {
                rect: {x: charObj["x"], y: charObj["y"], width: charObj["width"], height: charObj["height"]},
                xOffset: charObj["xoffset"],
                yOffset: charObj["yoffset"],
                xAdvance: charObj["xadvance"]
            };
        }

        //kerning
        var kerningDict = fnt.kerningDict = {};
        var kerningLines = fntStr.match(self.KERNING_EXP);
        if (kerningLines) {
            for (var i = 0, li = kerningLines.length; i < li; i++) {
                var kerningObj = self._parseStrToObj(kerningLines[i]);
                kerningDict[(kerningObj["first"] << 16) | (kerningObj["second"] & 0xffff)] = kerningObj["amount"];
            }
        }
        return fnt;
    },

    /**
     * load the fnt
     * @param realUrl
     * @param url
     * @param res
     * @param cb
     */
    load: function (realUrl, url, res, cb) {
        var self = this;
        cc.loader.loadTxt(realUrl, function (err, txt) {
            if (err) return cb(err);
            cb(null, self.parseFnt(txt, url));
        });
    }
};
cc.loader.register(["fnt"], cc._fntLoader);
