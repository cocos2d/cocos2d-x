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
 * <p>cc.AtlasNode is a subclass of cc.Node, it knows how to render a TextureAtlas object. </p>
 *
 * <p>If you are going to render a TextureAtlas consider subclassing cc.AtlasNode (or a subclass of cc.AtlasNode)</p>
 *
 * <p>All features from cc.Node are valid</p>
 *
 * <p>You can create a cc.AtlasNode with an Atlas file, the width, the height of each item and the quantity of items to render</p>
 *
 * @class
 * @extends cc.Node
 *
 * @param {String} tile
 * @param {Number} tileWidth
 * @param {Number} tileHeight
 * @param {Number} itemsToRender
 * @example
 * var node = new cc.AtlasNode("pathOfTile", 16, 16, 1);
 *
 * @property {cc.Texture2D}     texture         - Current used texture
 * @property {cc.TextureAtlas}  textureAtlas    - Texture atlas for cc.AtlasNode
 * @property {Number}           quadsToDraw     - Number of quads to draw
 */
cc.AtlasNode = cc.Node.extend(/** @lends cc.AtlasNode# */{
    textureAtlas: null,
    quadsToDraw: 0,

    //! chars per row
    _itemsPerRow: 0,
    //! chars per column
    _itemsPerColumn: 0,
    //! width of each char
    _itemWidth: 0,
    //! height of each char
    _itemHeight: 0,

    // protocol variables
    _opacityModifyRGB: false,
    _blendFunc: null,

    // This variable is only used for CCLabelAtlas FPS display. So plz don't modify its value.
    _ignoreContentScaleFactor: false,
    _className: "AtlasNode",

    _textureForCanvas: null,

    /**
     * <p>Constructor function, override it to extend the construction behavior, remember to call "this._super()" in the extended "ctor" function.</p>
     * @param {String} tile
     * @param {Number} tileWidth
     * @param {Number} tileHeight
     * @param {Number} itemsToRender
     */
    ctor: function (tile, tileWidth, tileHeight, itemsToRender) {
        cc.Node.prototype.ctor.call(this);
        this._blendFunc = {src: cc.BLEND_SRC, dst: cc.BLEND_DST};
        this._ignoreContentScaleFactor = false;
        itemsToRender !== undefined && this.initWithTileFile(tile, tileWidth, tileHeight, itemsToRender);
    },

    _createRenderCmd: function(){
        if(cc._renderType === cc._RENDER_TYPE_CANVAS)
            this._renderCmd = new cc.AtlasNode.CanvasRenderCmd(this);
        else
            this._renderCmd = new cc.AtlasNode.WebGLRenderCmd(this);
    },

    /**
     * Updates the Atlas (indexed vertex array).
     * Empty implementation, shall be overridden in subclasses
     * @function
     */
    updateAtlasValues: function () {
        cc.log(cc._LogInfos.AtlasNode_updateAtlasValues);
    },

    /**
     * Get color value of the atlas node
     * @function
     * @return {cc.Color}
     */
    getColor: function () {
        if (this._opacityModifyRGB)
            return this._renderCmd._colorUnmodified;
        return cc.Node.prototype.getColor.call(this);
    },

    /**
     * Set whether color should be changed with the opacity value,
     * if true, node color will change while opacity changes.
     * @function
     * @param {Boolean} value
     */
    setOpacityModifyRGB: function (value) {
        var oldColor = this.color;
        this._opacityModifyRGB = value;
        this.setColor(oldColor);
    },

    /**
     * Get whether color should be changed with the opacity value
     * @function
     * @return {Boolean}
     */
    isOpacityModifyRGB: function () {
        return this._opacityModifyRGB;
    },

    /**
     * Get node's blend function
     * @function
     * @return {cc.BlendFunc}
     */
    getBlendFunc: function () {
        return this._blendFunc;
    },

    /**
     * Set node's blend function
     * This function accept either cc.BlendFunc object or source value and destination value
     * @function
     * @param {Number | cc.BlendFunc} src
     * @param {Number} dst
     */
    setBlendFunc: function (src, dst) {
        if (dst === undefined)
            this._blendFunc = src;
        else
            this._blendFunc = {src: src, dst: dst};
    },

    /**
     * Set the atlas texture
     * @function
     * @param {cc.TextureAtlas} value The texture
     */
    setTextureAtlas: function (value) {
        this.textureAtlas = value;
    },

    /**
     * Get the atlas texture
     * @function
     * @return {cc.TextureAtlas}
     */
    getTextureAtlas: function () {
        return this.textureAtlas;
    },

    /**
     * Get the number of quads to be rendered
     * @function
     * @return {Number}
     */
    getQuadsToDraw: function () {
        return this.quadsToDraw;
    },

    /**
     * Set the number of quads to be rendered
     * @function
     * @param {Number} quadsToDraw
     */
    setQuadsToDraw: function (quadsToDraw) {
        this.quadsToDraw = quadsToDraw;
    },

    /**
     * Initializes an cc.AtlasNode object with an atlas texture file name, the width, the height of each tile and the quantity of tiles to render
     * @function
     * @param {String} tile             The atlas texture file name
     * @param {Number} tileWidth        The width of each tile
     * @param {Number} tileHeight       The height of each tile
     * @param {Number} itemsToRender    The quantity of tiles to be rendered
     * @return {Boolean}
     */
    initWithTileFile: function (tile, tileWidth, tileHeight, itemsToRender) {
        if (!tile)
            throw "cc.AtlasNode.initWithTileFile(): title should not be null";
        var texture = cc.textureCache.addImage(tile);
        return this.initWithTexture(texture, tileWidth, tileHeight, itemsToRender);
    },

    /**
     * Initializes an CCAtlasNode with an atlas texture, the width, the height of each tile and the quantity of tiles to render
     * @function
     * @param {cc.Texture2D} texture    The atlas texture
     * @param {Number} tileWidth        The width of each tile
     * @param {Number} tileHeight       The height of each tile
     * @param {Number} itemsToRender    The quantity of tiles to be rendered
     * @return {Boolean}
     */
    initWithTexture: function(texture, tileWidth, tileHeight, itemsToRender){
        return this._renderCmd.initWithTexture(texture, tileWidth, tileHeight, itemsToRender);
    },

    /**
     * Set node's color
     * @function
     * @param {cc.Color} color Color object created with cc.color(r, g, b).
     */
    setColor: function(color){
        this._renderCmd.setColor(color);
    },

    /**
     * Set node's opacity
     * @function
     * @param {Number} opacity The opacity value
     */
    setOpacity: function (opacity) {
        this._renderCmd.setOpacity(opacity);
    },

    /**
     * Get the current texture
     * @function
     * @return {cc.Texture2D}
     */
    getTexture: function(){
        return this._renderCmd.getTexture();
    },

    /**
     * Replace the current texture with a new one
     * @function
     * @param {cc.Texture2D} texture    The new texture
     */
    setTexture: function(texture){
        this._renderCmd.setTexture(texture);
    },

    _setIgnoreContentScaleFactor: function (ignoreContentScaleFactor) {
        this._ignoreContentScaleFactor = ignoreContentScaleFactor;
    }
});


var _p = cc.AtlasNode.prototype;
// Override properties
cc.defineGetterSetter(_p, "opacity", _p.getOpacity, _p.setOpacity);
cc.defineGetterSetter(_p, "color", _p.getColor, _p.setColor);

// Extended properties
/** @expose */
_p.texture;
cc.defineGetterSetter(_p, "texture", _p.getTexture, _p.setTexture);
/** @expose */
_p.textureAtlas;
/** @expose */
_p.quadsToDraw;

cc.EventHelper.prototype.apply(_p);

/**
 * Creates a cc.AtlasNode with an Atlas file the width and height of each item and the quantity of items to render
 * @deprecated since v3.0, please use new construction instead
 * @function
 * @static
 * @param {String} tile
 * @param {Number} tileWidth
 * @param {Number} tileHeight
 * @param {Number} itemsToRender
 * @return {cc.AtlasNode}
 */
cc.AtlasNode.create = function (tile, tileWidth, tileHeight, itemsToRender) {
    return new cc.AtlasNode(tile, tileWidth, tileHeight, itemsToRender);
};