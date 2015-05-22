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
 * using image file to print text label on the screen, might be a bit slower than cc.Label, similar to cc.LabelBMFont
 * @class
 * @extends cc.AtlasNode
 *
 * @property {String}   string  - Content string of label
 *
 * @param {String} strText
 * @param {String} charMapFile  charMapFile or fntFile
 * @param {Number} [itemWidth=0]
 * @param {Number} [itemHeight=0]
 * @param {Number} [startCharMap=""]
 * @example
 * //creates the cc.LabelAtlas with a string, a char map file(the atlas), the width and height of each element and the starting char of the atlas
 * var myLabel = new cc.LabelAtlas('Text to display', 'CharMapfile.png', 12, 20, ' ')
 *
 * //creates the cc.LabelAtlas with a string, a fnt file
 * var myLabel = new cc.LabelAtlas('Text to display', 'CharMapFile.plist‘);
 */
cc.LabelAtlas = cc.AtlasNode.extend(/** @lends cc.LabelAtlas# */{
    //property String is Getter and Setter
    // string to render
    _string: null,
    // the first char in the charmap
    _mapStartChar: null,

    _textureLoaded: false,
    _className: "LabelAtlas",

    /**
     * <p>
     *  Constructor function, override it to extend the construction behavior, remember to call "this._super()" in the extended "ctor" function. <br />
     *  Create a label atlas. <br />
     *  It accepts two groups of parameters: <br/>
     * a) string, fntFile <br/>
     * b) label, textureFilename, width, height, startChar <br/>
     * </p>
     * @param {String} strText
     * @param {String} charMapFile  charMapFile or fntFile
     * @param {Number} [itemWidth=0]
     * @param {Number} [itemHeight=0]
     * @param {Number} [startCharMap=""]
     */
    ctor: function (strText, charMapFile, itemWidth, itemHeight, startCharMap) {
        cc.AtlasNode.prototype.ctor.call(this);

        this._renderCmd.setCascade();
        charMapFile && cc.LabelAtlas.prototype.initWithString.call(this, strText, charMapFile, itemWidth, itemHeight, startCharMap);
    },

    _createRenderCmd: function(){
        if(cc._renderType === cc._RENDER_TYPE_WEBGL)
            return new cc.LabelAtlas.WebGLRenderCmd(this);
        else
            return new cc.LabelAtlas.CanvasRenderCmd(this);
    },

    /**
     * Return  texture is loaded.
     * @returns {boolean}
     */
    textureLoaded: function () {
        return this._textureLoaded;
    },

    /**
     * Add texture loaded event listener.
     * @param {Function} callback
     * @param {cc.Node} target
     * @deprecated since 3.1, please use addEventListener instead
     */
    addLoadedEventListener: function (callback, target) {
        this.addEventListener("load", callback, target);
    },

    /**
     * <p>
     *  initializes the cc.LabelAtlas with a string, a char map file(the atlas), <br/>
     *  the width and height of each element and the starting char of the atlas <br/>
     *  It accepts two groups of parameters: <br/>
     * a) string, fntFile <br/>
     * b) label, textureFilename, width, height, startChar <br/>
     * </p>
     * @param {String} strText
     * @param {String|cc.Texture2D} charMapFile  charMapFile or fntFile or texture file
     * @param {Number} [itemWidth=0]
     * @param {Number} [itemHeight=0]
     * @param {Number} [startCharMap=""]
     * @return {Boolean} returns true on success
     */
    initWithString: function (strText, charMapFile, itemWidth, itemHeight, startCharMap) {
        var label = strText + "", textureFilename, width, height, startChar;
        if (itemWidth === undefined) {
            var dict = cc.loader.getRes(charMapFile);
            if (parseInt(dict["version"], 10) !== 1) {
                cc.log("cc.LabelAtlas.initWithString(): Unsupported version. Upgrade cocos2d version");
                return false;
            }

            textureFilename = cc.path.changeBasename(charMapFile, dict["textureFilename"]);
            var locScaleFactor = cc.contentScaleFactor();
            width = parseInt(dict["itemWidth"], 10) / locScaleFactor;
            height = parseInt(dict["itemHeight"], 10) / locScaleFactor;
            startChar = String.fromCharCode(parseInt(dict["firstChar"], 10));
        } else {
            textureFilename = charMapFile;
            width = itemWidth || 0;
            height = itemHeight || 0;
            startChar = startCharMap || " ";
        }

        var texture = null;
        if (textureFilename instanceof cc.Texture2D)
            texture = textureFilename;
        else
            texture = cc.textureCache.addImage(textureFilename);
        var locLoaded = texture.isLoaded();
        this._textureLoaded = locLoaded;
        if (!locLoaded) {
            this._string = label;
            texture.addEventListener("load", function (sender) {
                this.initWithTexture(texture, width, height, label.length);
                this.string = this._string;
                this.setColor(this._renderCmd._displayedColor);
                this.dispatchEvent("load");
            }, this);
        }
        if (this.initWithTexture(texture, width, height, label.length)) {
            this._mapStartChar = startChar;
            this.string = label;
            return true;
        }
        return false;
    },

    /**
     * Set the color.
     * @param {cc.Color} color3
     */
    setColor: function (color3) {
        cc.AtlasNode.prototype.setColor.call(this, color3);
        this._renderCmd.updateAtlasValues();
    },

    /**
     * return the text of this label
     * @return {String}
     */
    getString: function () {
        return this._string;
    },

    addChild: function(child, localZOrder, tag){
        this._renderCmd._addChild(child);
        cc.Node.prototype.addChild.call(this, child, localZOrder, tag);
    },

    /**
     * Atlas generation
     * @function
     */
    updateAtlasValues: function(){
        this._renderCmd.updateAtlasValues();
    },

    /**
     * set the display string
     * @function
     * @param {String} label
     */
    setString: function(label){
        label = String(label);
        var len = label.length;
        this._string = label;
        this.setContentSize(len * this._itemWidth, this._itemHeight);
        this._renderCmd.setString(label);

        this._renderCmd.updateAtlasValues();
        this.quadsToDraw = len;
    }
});

(function(){
    var proto = cc.LabelAtlas.prototype;
    // Override properties
    cc.defineGetterSetter(proto, "opacity", proto.getOpacity, proto.setOpacity);
    cc.defineGetterSetter(proto, "color", proto.getColor, proto.setColor);

    // Extended properties
    /** @expose */
    proto.string;
    cc.defineGetterSetter(proto, "string", proto.getString, proto.setString);
})();

/**
 * <p>
 *     Please use new cc.LabelAtlas instead. <br />
 *     Create a label atlas. <br />
 *     It accepts two groups of parameters:                                                            <br/>
 *         a) string, fntFile                                                                               <br/>
 *         b) label, textureFilename, width, height, startChar                                              <br/>
 * </p>
 * @deprecated since v3.0 please use new cc.LabelAtlas
 * @param {String} strText
 * @param {String} charMapFile  charMapFile or fntFile
 * @param {Number} [itemWidth=0]
 * @param {Number} [itemHeight=0]
 * @param {Number} [startCharMap=""]
 * @return {cc.LabelAtlas} returns the LabelAtlas object on success
 */
cc.LabelAtlas.create = function (strText, charMapFile, itemWidth, itemHeight, startCharMap) {
    return new cc.LabelAtlas(strText, charMapFile, itemWidth, itemHeight, startCharMap);
};

