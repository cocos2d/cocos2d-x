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
 * <p>cc.Sprite is a 2d image ( http://en.wikipedia.org/wiki/Sprite_(computer_graphics) )  <br/>
 *
 * cc.Sprite can be created with an image, or with a sub-rectangle of an image.  <br/>
 *
 * If the parent or any of its ancestors is a cc.SpriteBatchNode then the following features/limitations are valid   <br/>
 *    - Features when the parent is a cc.BatchNode: <br/>
 *        - MUCH faster rendering, specially if the cc.SpriteBatchNode has many children. All the children will be drawn in a single batch.  <br/>
 *
 *    - Limitations   <br/>
 *        - Camera is not supported yet (eg: CCOrbitCamera action doesn't work)  <br/>
 *        - GridBase actions are not supported (eg: CCLens, CCRipple, CCTwirl) <br/>
 *        - The Alias/Antialias property belongs to CCSpriteBatchNode, so you can't individually set the aliased property.  <br/>
 *        - The Blending function property belongs to CCSpriteBatchNode, so you can't individually set the blending function property. <br/>
 *        - Parallax scroller is not supported, but can be simulated with a "proxy" sprite.        <br/>
 *
 *  If the parent is an standard cc.Node, then cc.Sprite behaves like any other cc.Node:      <br/>
 *    - It supports blending functions    <br/>
 *    - It supports aliasing / antialiasing    <br/>
 *    - But the rendering will be slower: 1 draw per children.   <br/>
 *
 * The default anchorPoint in cc.Sprite is (0.5, 0.5). </p>
 * @class
 * @extends cc.Node
 *
 * @param {String|cc.SpriteFrame|HTMLImageElement|cc.Texture2D} fileName  The string which indicates a path to image file, e.g., "scene1/monster.png".
 * @param {cc.Rect} rect  Only the contents inside rect of pszFileName's texture will be applied for this sprite.
 * @param {Boolean} [rotated] Whether or not the texture rectangle is rotated.
 * @example
 *
 * 1.Create a sprite with image path and rect
 * var sprite1 = new cc.Sprite("res/HelloHTML5World.png");
 * var sprite2 = new cc.Sprite("res/HelloHTML5World.png",cc.rect(0,0,480,320));
 *
 * 2.Create a sprite with a sprite frame name. Must add "#" before frame name.
 * var sprite = new cc.Sprite('#grossini_dance_01.png');
 *
 * 3.Create a sprite with a sprite frame
 * var spriteFrame = cc.spriteFrameCache.getSpriteFrame("grossini_dance_01.png");
 * var sprite = new cc.Sprite(spriteFrame);
 *
 * 4.Create a sprite with an existing texture contained in a CCTexture2D object
 *      After creation, the rect will be the size of the texture, and the offset will be (0,0).
 * var texture = cc.textureCache.addImage("HelloHTML5World.png");
 * var sprite1 = new cc.Sprite(texture);
 * var sprite2 = new cc.Sprite(texture, cc.rect(0,0,480,320));
 *
 * @property {Boolean}              dirty               - Indicates whether the sprite needs to be updated.
 * @property {Boolean}              flippedX            - Indicates whether or not the sprite is flipped on x axis.
 * @property {Boolean}              flippedY            - Indicates whether or not the sprite is flipped on y axis.
 * @property {Number}               offsetX             - <@readonly> The offset position on x axis of the sprite in texture. Calculated automatically by editors like Zwoptex.
 * @property {Number}               offsetY             - <@readonly> The offset position on x axis of the sprite in texture. Calculated automatically by editors like Zwoptex.
 * @property {Number}               atlasIndex          - The index used on the TextureAtlas.
 * @property {cc.Texture2D}         texture             - Texture used to render the sprite.
 * @property {Boolean}              textureRectRotated  - <@readonly> Indicate whether the texture rectangle is rotated.
 * @property {cc.TextureAtlas}      textureAtlas        - The weak reference of the cc.TextureAtlas when the sprite is rendered using via cc.SpriteBatchNode.
 * @property {cc.SpriteBatchNode}   batchNode           - The batch node object if this sprite is rendered by cc.SpriteBatchNode.
 * @property {cc.V3F_C4B_T2F_Quad}  quad                - <@readonly> The quad (tex coords, vertex coords and color) information.
 */
cc.Sprite = cc.Node.extend(/** @lends cc.Sprite# */{
	dirty:false,
	atlasIndex:0,
    textureAtlas:null,

    _batchNode:null,
    _recursiveDirty:null, //Whether all of the sprite's children needs to be updated
    _hasChildren:null, //Whether the sprite contains children
    _shouldBeHidden:false, //should not be drawn because one of the ancestors is not visible
    _transformToBatch:null,

    //
    // Data used when the sprite is self-rendered
    //
    _blendFunc:null, //It's required for CCTextureProtocol inheritance
    _texture:null, //cc.Texture2D object that is used to render the sprite

    //
    // Shared data
    //
    // texture
    _rect:null, //Rectangle of cc.Texture2D
    _rectRotated:false, //Whether the texture is rotated

    // Offset Position (used by Zwoptex)
    _offsetPosition:null, // absolute
    _unflippedOffsetPositionFromCenter:null,

    _opacityModifyRGB:false,

    // image is flipped
    _flippedX:false, //Whether the sprite is flipped horizontally or not.
    _flippedY:false, //Whether the sprite is flipped vertically or not.

    _textureLoaded:false,
    _className:"Sprite",

    ctor: function (fileName, rect, rotated) {
        var self = this;
        cc.Node.prototype.ctor.call(self);
        self._shouldBeHidden = false;
        self._offsetPosition = cc.p(0, 0);
        self._unflippedOffsetPositionFromCenter = cc.p(0, 0);
        self._blendFunc = {src: cc.BLEND_SRC, dst: cc.BLEND_DST};
        self._rect = cc.rect(0, 0, 0, 0);

        self._softInit(fileName, rect, rotated);
    },

    /**
     * Returns whether the texture have been loaded
     * @returns {boolean}
     */
    textureLoaded:function(){
        return this._textureLoaded;
    },

    /**
     * Add a event listener for texture loaded event.
     * @param {Function} callback
     * @param {Object} target
     * @deprecated since 3.1, please use addEventListener instead
     */
    addLoadedEventListener:function(callback, target){
        this.addEventListener("load", callback, target);
    },

    /**
     * Returns whether or not the Sprite needs to be updated in the Atlas
     * @return {Boolean} True if the sprite needs to be updated in the Atlas, false otherwise.
     */
    isDirty:function () {
        return this.dirty;
    },

    /**
     * Makes the sprite to be updated in the Atlas.
     * @param {Boolean} bDirty
     */
    setDirty:function (bDirty) {
        this.dirty = bDirty;
    },

    /**
     * Returns whether or not the texture rectangle is rotated.
     * @return {Boolean}
     */
    isTextureRectRotated:function () {
        return this._rectRotated;
    },

    /**
     * Returns the index used on the TextureAtlas.
     * @return {Number}
     */
    getAtlasIndex:function () {
        return this.atlasIndex;
    },

    /**
     * Sets the index used on the TextureAtlas.
     * @warning Don't modify this value unless you know what you are doing
     * @param {Number} atlasIndex
     */
    setAtlasIndex:function (atlasIndex) {
        this.atlasIndex = atlasIndex;
    },

    /**
     * Returns the rect of the cc.Sprite in points
     * @return {cc.Rect}
     */
    getTextureRect:function () {
        return cc.rect(this._rect);
    },

    /**
     * Returns the weak reference of the cc.TextureAtlas when the sprite is rendered using via cc.SpriteBatchNode
     * @return {cc.TextureAtlas}
     */
    getTextureAtlas:function () {
        return this.textureAtlas;
    },

    /**
     * Sets the weak reference of the cc.TextureAtlas when the sprite is rendered using via cc.SpriteBatchNode
     * @param {cc.TextureAtlas} textureAtlas
     */
    setTextureAtlas:function (textureAtlas) {
        this.textureAtlas = textureAtlas;
    },

    /**
     * Returns the offset position of the sprite. Calculated automatically by editors like Zwoptex.
     * @return {cc.Point}
     */
    getOffsetPosition:function () {
        return cc.p(this._offsetPosition);
    },

	_getOffsetX: function () {
		return this._offsetPosition.x;
	},
	_getOffsetY: function () {
		return this._offsetPosition.y;
	},

    /**
     * Returns the blend function
     * @return {cc.BlendFunc}
     */
    getBlendFunc:function () {
        return this._blendFunc;
    },

    /**
     * Initializes a sprite with a SpriteFrame. The texture and rect in SpriteFrame will be applied on this sprite.<br/>
     * Please pass parameters to the constructor to initialize the sprite, do not call this function yourself,
     * @param {cc.SpriteFrame} spriteFrame A CCSpriteFrame object. It should includes a valid texture and a rect
     * @return {Boolean}  true if the sprite is initialized properly, false otherwise.
     */
    initWithSpriteFrame:function (spriteFrame) {
        cc.assert(spriteFrame, cc._LogInfos.Sprite_initWithSpriteFrame);

        if(!spriteFrame.textureLoaded()){
            //add event listener
            this._textureLoaded = false;
            spriteFrame.addEventListener("load", this._renderCmd._spriteFrameLoadedCallback, this);
        }

        //TODO
        var rotated = cc._renderType === cc._RENDER_TYPE_CANVAS ? false : spriteFrame._rotated;
        var ret = this.initWithTexture(spriteFrame.getTexture(), spriteFrame.getRect(), rotated);
        this.setSpriteFrame(spriteFrame);

        return ret;
    },

    /**
     * Initializes a sprite with a sprite frame name. <br/>
     * A cc.SpriteFrame will be fetched from the cc.SpriteFrameCache by name.  <br/>
     * If the cc.SpriteFrame doesn't exist it will raise an exception. <br/>
     * Please pass parameters to the constructor to initialize the sprite, do not call this function yourself.
     * @param {String} spriteFrameName A key string that can fected a valid cc.SpriteFrame from cc.SpriteFrameCache
     * @return {Boolean} true if the sprite is initialized properly, false otherwise.
     * @example
     * var sprite = new cc.Sprite();
     * sprite.initWithSpriteFrameName("grossini_dance_01.png");
     */
    initWithSpriteFrameName:function (spriteFrameName) {
        cc.assert(spriteFrameName, cc._LogInfos.Sprite_initWithSpriteFrameName);
        var frame = cc.spriteFrameCache.getSpriteFrame(spriteFrameName);
        cc.assert(frame, spriteFrameName + cc._LogInfos.Sprite_initWithSpriteFrameName1);
        return this.initWithSpriteFrame(frame);
    },

    /**
     * Tell the sprite to use batch node render.
     * @param {cc.SpriteBatchNode} batchNode
     */
    useBatchNode:function (batchNode) {
        this.textureAtlas = batchNode.getTextureAtlas(); // weak ref
        this._batchNode = batchNode;
    },

    /**
     * <p>
     *    set the vertex rect.<br/>
     *    It will be called internally by setTextureRect.                           <br/>
     *    Useful if you want to create 2x images from SD images in Retina Display.  <br/>
     *    Do not call it manually. Use setTextureRect instead.  <br/>
     *    (override this method to generate "double scale" sprites)
     * </p>
     * @param {cc.Rect} rect
     */
    setVertexRect:function (rect) {
        var locRect = this._rect;
        locRect.x = rect.x;
        locRect.y = rect.y;
        locRect.width = rect.width;
        locRect.height = rect.height;
    },

    /**
     * Sort all children of this sprite node.
     * @override
     */
    sortAllChildren:function () {
        if (this._reorderChildDirty) {
            var _children = this._children;

            // insertion sort
            var len = _children.length, i, j, tmp;
            for(i=1; i<len; i++){
                tmp = _children[i];
                j = i - 1;

                //continue moving element downwards while zOrder is smaller or when zOrder is the same but mutatedIndex is smaller
                while(j >= 0){
                    if(tmp._localZOrder < _children[j]._localZOrder){
                        _children[j+1] = _children[j];
                    }else if(tmp._localZOrder === _children[j]._localZOrder && tmp.arrivalOrder < _children[j].arrivalOrder){
                        _children[j+1] = _children[j];
                    }else{
                        break;
                    }
                    j--;
                }
                _children[j+1] = tmp;
            }

            if (this._batchNode) {
                this._arrayMakeObjectsPerformSelector(_children, cc.Node._stateCallbackType.sortAllChildren);
            }

            //don't need to check children recursively, that's done in visit of each child
            this._reorderChildDirty = false;
        }

    },

    /**
     * Reorders a child according to a new z value.  (override cc.Node )
     * @param {cc.Node} child
     * @param {Number} zOrder
     * @override
     */
    reorderChild:function (child, zOrder) {
        cc.assert(child, cc._LogInfos.Sprite_reorderChild_2);
        if(this._children.indexOf(child) === -1){
            cc.log(cc._LogInfos.Sprite_reorderChild);
            return;
        }

        if (zOrder === child.zIndex)
            return;

        if (this._batchNode && !this._reorderChildDirty) {
            this._setReorderChildDirtyRecursively();
            this._batchNode.reorderBatch(true);
        }
        cc.Node.prototype.reorderChild.call(this, child, zOrder);
    },

    /**
     * Removes a child from the sprite.
     * @param child
     * @param cleanup  whether or not cleanup all running actions
     * @override
     */
    removeChild:function (child, cleanup) {
        if (this._batchNode)
            this._batchNode.removeSpriteFromAtlas(child);
        cc.Node.prototype.removeChild.call(this, child, cleanup);
    },

    /**
     * Sets whether the sprite is visible or not.
     * @param {Boolean} visible
     * @override
     */
    setVisible:function (visible) {
        cc.Node.prototype.setVisible.call(this, visible);
        this._renderCmd.setDirtyRecursively(true);
    },

    /**
     * Removes all children from the container.
     * @param cleanup whether or not cleanup all running actions
     * @override
     */
    removeAllChildren:function (cleanup) {
        var locChildren = this._children, locBatchNode = this._batchNode;
        if (locBatchNode && locChildren != null) {
            for (var i = 0, len = locChildren.length; i < len; i++)
                locBatchNode.removeSpriteFromAtlas(locChildren[i]);
        }

        cc.Node.prototype.removeAllChildren.call(this, cleanup);
        this._hasChildren = false;
    },

    //
    // cc.Node property overloads
    //

    /**
     * Sets whether ignore anchor point for positioning
     * @param {Boolean} relative
     * @override
     */
    ignoreAnchorPointForPosition:function (relative) {
        if(this._batchNode){
            cc.log(cc._LogInfos.Sprite_ignoreAnchorPointForPosition);
            return;
        }
        cc.Node.prototype.ignoreAnchorPointForPosition.call(this, relative);
    },

    /**
     * Sets whether the sprite should be flipped horizontally or not.
     * @param {Boolean} flippedX true if the sprite should be flipped horizontally, false otherwise.
     */
    setFlippedX:function (flippedX) {
        if (this._flippedX !== flippedX) {
            this._flippedX = flippedX;
            this.setTextureRect(this._rect, this._rectRotated, this._contentSize);
            this.setNodeDirty(true);
        }
    },

    /**
     * Sets whether the sprite should be flipped vertically or not.
     * @param {Boolean} flippedY true if the sprite should be flipped vertically, false otherwise.
     */
    setFlippedY:function (flippedY) {
        if (this._flippedY !== flippedY) {
            this._flippedY = flippedY;
            this.setTextureRect(this._rect, this._rectRotated, this._contentSize);
            this.setNodeDirty(true);
        }
    },

    /**
     * <p>
     * Returns the flag which indicates whether the sprite is flipped horizontally or not.                      <br/>
     *                                                                                                              <br/>
     * It only flips the texture of the sprite, and not the texture of the sprite's children.                       <br/>
     * Also, flipping the texture doesn't alter the anchorPoint.                                                    <br/>
     * If you want to flip the anchorPoint too, and/or to flip the children too use:                                <br/>
     *      sprite.setScaleX(sprite.getScaleX() * -1);  <p/>
     * @return {Boolean} true if the sprite is flipped horizontally, false otherwise.
     */
    isFlippedX:function () {
        return this._flippedX;
    },

    /**
     * <p>
     *     Return the flag which indicates whether the sprite is flipped vertically or not.                         <br/>
     *                                                                                                              <br/>
     *      It only flips the texture of the sprite, and not the texture of the sprite's children.                  <br/>
     *      Also, flipping the texture doesn't alter the anchorPoint.                                               <br/>
     *      If you want to flip the anchorPoint too, and/or to flip the children too use:                           <br/>
     *         sprite.setScaleY(sprite.getScaleY() * -1); <p/>
     * @return {Boolean} true if the sprite is flipped vertically, false otherwise.
     */
    isFlippedY:function () {
        return this._flippedY;
    },

    //
    // RGBA protocol
    //
    /**
     * Sets whether opacity modify color or not.
     * @function
     * @param {Boolean} modify
     */
    setOpacityModifyRGB: function (modify) {
        if (this._opacityModifyRGB !== modify) {
            this._opacityModifyRGB = modify;
            this._renderCmd._setColorDirty();
        }
    },

    /**
     * Returns whether opacity modify color or not.
     * @return {Boolean}
     */
    isOpacityModifyRGB:function () {
        return this._opacityModifyRGB;
    },

    // Animation

    /**
     * Changes the display frame with animation name and index.<br/>
     * The animation name will be get from the CCAnimationCache
     * @param {String} animationName
     * @param {Number} frameIndex
     */
    setDisplayFrameWithAnimationName:function (animationName, frameIndex) {
        cc.assert(animationName, cc._LogInfos.Sprite_setDisplayFrameWithAnimationName_3);

        var cache = cc.animationCache.getAnimation(animationName);
        if(!cache){
            cc.log(cc._LogInfos.Sprite_setDisplayFrameWithAnimationName);
            return;
        }
        var animFrame = cache.getFrames()[frameIndex];
        if(!animFrame){
            cc.log(cc._LogInfos.Sprite_setDisplayFrameWithAnimationName_2);
            return;
        }
        this.setSpriteFrame(animFrame.getSpriteFrame());
    },

    /**
     * Returns the batch node object if this sprite is rendered by cc.SpriteBatchNode
     * @returns {cc.SpriteBatchNode|null} The cc.SpriteBatchNode object if this sprite is rendered by cc.SpriteBatchNode, null if the sprite isn't used batch node.
     */
    getBatchNode:function () {
        return this._batchNode;
    },

    _setReorderChildDirtyRecursively:function () {
        //only set parents flag the first time
        if (!this._reorderChildDirty) {
            this._reorderChildDirty = true;
            var pNode = this._parent;
            while (pNode && pNode !== this._batchNode) {
                pNode._setReorderChildDirtyRecursively();
                pNode = pNode.parent;
            }
        }
    },

    // CCTextureProtocol
    /**
     * Returns the texture of the sprite node
     * @returns {cc.Texture2D}
     */
    getTexture:function () {
        return this._texture;
    },

	_softInit: function (fileName, rect, rotated) {
		if (fileName === undefined)
			cc.Sprite.prototype.init.call(this);
		else if (cc.isString(fileName)) {
			if (fileName[0] === "#") {
				// Init with a sprite frame name
				var frameName = fileName.substr(1, fileName.length - 1);
				var spriteFrame = cc.spriteFrameCache.getSpriteFrame(frameName);
				if (spriteFrame)
					this.initWithSpriteFrame(spriteFrame);
				else
					cc.log("%s does not exist", fileName);
			} else {
				// Init  with filename and rect
				cc.Sprite.prototype.init.call(this, fileName, rect);
			}
		} else if (typeof fileName === "object") {
			if (fileName instanceof cc.Texture2D) {
				// Init  with texture and rect
				this.initWithTexture(fileName, rect, rotated);
			} else if (fileName instanceof cc.SpriteFrame) {
				// Init with a sprite frame
				this.initWithSpriteFrame(fileName);
			} else if ((fileName instanceof HTMLImageElement) || (fileName instanceof HTMLCanvasElement)) {
				// Init with a canvas or image element
				var texture2d = new cc.Texture2D();
				texture2d.initWithElement(fileName);
				texture2d.handleLoadedTexture();
				this.initWithTexture(texture2d);
			}
		}
	},

    /**
     * Returns the quad (tex coords, vertex coords and color) information.
     * @return {cc.V3F_C4B_T2F_Quad|null} Returns a cc.V3F_C4B_T2F_Quad object when render mode is WebGL, returns null when render mode is Canvas.
     */
    getQuad:function () {
        return this._renderCmd.getQuad();
    },

    /**
     * conforms to cc.TextureProtocol protocol
     * @function
     * @param {Number|cc.BlendFunc} src
     * @param {Number} dst
     */
    setBlendFunc: function (src, dst) {
        var locBlendFunc = this._blendFunc;
        if (dst === undefined) {
            locBlendFunc.src = src.src;
            locBlendFunc.dst = src.dst;
        } else {
            locBlendFunc.src = src;
            locBlendFunc.dst = dst;
        }
        this._renderCmd.updateBlendFunc(locBlendFunc);
    },

    /**
     * Initializes an empty sprite with nothing init.<br/>
     * Please pass parameters to the constructor to initialize the sprite, do not call this function yourself.
     * @function
     * @return {Boolean}
     */
    init: function () {
        var _t = this;
        if (arguments.length > 0)
            return _t.initWithFile(arguments[0], arguments[1]);

        cc.Node.prototype.init.call(_t);
        _t.dirty = _t._recursiveDirty = false;

        _t._blendFunc.src = cc.BLEND_SRC;
        _t._blendFunc.dst = cc.BLEND_DST;

        _t.texture = null;
        _t._flippedX = _t._flippedY = false;

        // default transform anchor: center
        _t.anchorX = 0.5;
        _t.anchorY = 0.5;

        // zwoptex default values
        _t._offsetPosition.x = 0;
        _t._offsetPosition.y = 0;
        _t._hasChildren = false;

        this._renderCmd._init();
        // updated in "useSelfRender"
        // Atlas: TexCoords
        _t.setTextureRect(cc.rect(0, 0, 0, 0), false, cc.size(0, 0));
        return true;
    },

    /**
     * <p>
     *     Initializes a sprite with an image filename.<br/>
     *
     *     This method will find pszFilename from local file system, load its content to CCTexture2D,<br/>
     *     then use CCTexture2D to create a sprite.<br/>
     *     After initialization, the rect used will be the size of the image. The offset will be (0,0).<br/>
     *     Please pass parameters to the constructor to initialize the sprite, do not call this function yourself.
     * </p>
     * @param {String} filename The path to an image file in local file system
     * @param {cc.Rect} rect The rectangle assigned the content area from texture.
     * @return {Boolean} true if the sprite is initialized properly, false otherwise.
     */
    initWithFile:function (filename, rect) {
        cc.assert(filename, cc._LogInfos.Sprite_initWithFile);

        var tex = cc.textureCache.getTextureForKey(filename);
        if (!tex) {
            tex = cc.textureCache.addImage(filename);
            return this.initWithTexture(tex, rect || cc.rect(0, 0, tex._contentSize.width, tex._contentSize.height));
        } else {
            if (!rect) {
                var size = tex.getContentSize();
                rect = cc.rect(0, 0, size.width, size.height);
            }
            return this.initWithTexture(tex, rect);
        }
    },

    /**
     * Initializes a sprite with a texture and a rect in points, optionally rotated.  <br/>
     * After initialization, the rect used will be the size of the texture, and the offset will be (0,0).<br/>
     * Please pass parameters to the constructor to initialize the sprite, do not call this function yourself.
     * @function
     * @param {cc.Texture2D|HTMLImageElement|HTMLCanvasElement} texture A pointer to an existing CCTexture2D object. You can use a CCTexture2D object for many sprites.
     * @param {cc.Rect} [rect] Only the contents inside rect of this texture will be applied for this sprite.
     * @param {Boolean} [rotated] Whether or not the texture rectangle is rotated.
     * @param {Boolean} [counterclockwise=true] Whether or not the texture rectangle rotation is counterclockwise (texture package is counterclockwise, spine is clockwise).
     * @return {Boolean} true if the sprite is initialized properly, false otherwise.
     */
    initWithTexture: function (texture, rect, rotated, counterclockwise) {
        var _t = this;
        cc.assert(arguments.length !== 0, cc._LogInfos.CCSpriteBatchNode_initWithTexture);

        rotated = rotated || false;
        texture = this._renderCmd._handleTextureForRotatedTexture(texture, rect, rotated, counterclockwise);

        if (!cc.Node.prototype.init.call(_t))
            return false;

        _t._batchNode = null;
        _t._recursiveDirty = false;
        _t.dirty = false;
        _t._opacityModifyRGB = true;

        _t._blendFunc.src = cc.BLEND_SRC;
        _t._blendFunc.dst = cc.BLEND_DST;

        _t._flippedX = _t._flippedY = false;

        // default transform anchor: center
        _t.setAnchorPoint(0.5, 0.5);

        // zwoptex default values
        _t._offsetPosition.x = 0;
        _t._offsetPosition.y = 0;
        _t._hasChildren = false;

        this._renderCmd._init();

        var locTextureLoaded = texture.isLoaded();
        _t._textureLoaded = locTextureLoaded;

        if (!locTextureLoaded) {
            _t._rectRotated = rotated;
            if (rect) {
                _t._rect.x = rect.x;
                _t._rect.y = rect.y;
                _t._rect.width = rect.width;
                _t._rect.height = rect.height;
            }
            if(_t.texture)
                _t.texture.removeEventListener("load", _t);
            texture.addEventListener("load", _t._renderCmd._textureLoadedCallback, _t);
            _t.texture = texture;
            return true;
        }

        if (!rect)
            rect = cc.rect(0, 0, texture.width, texture.height);

        this._renderCmd._checkTextureBoundary(texture, rect, rotated);

        _t.texture = texture;
        _t.setTextureRect(rect, rotated);

        // by default use "Self Render".
        // if the sprite is added to a batchnode, then it will automatically switch to "batchnode Render"
        _t.setBatchNode(null);
        return true;
    },

    /**
     * Updates the texture rect of the CCSprite in points.
     * @function
     * @param {cc.Rect} rect a rect of texture
     * @param {Boolean} [rotated] Whether or not the texture is rotated
     * @param {cc.Size} [untrimmedSize] The original pixels size of the texture
     */
    setTextureRect: function (rect, rotated, untrimmedSize, needConvert) {
        var _t = this;
        _t._rectRotated = rotated || false;
        _t.setContentSize(untrimmedSize || rect);

        _t.setVertexRect(rect);
        _t._renderCmd._setTextureCoords(rect, needConvert);

        var relativeOffsetX = _t._unflippedOffsetPositionFromCenter.x, relativeOffsetY = _t._unflippedOffsetPositionFromCenter.y;
        if (_t._flippedX)
            relativeOffsetX = -relativeOffsetX;
        if (_t._flippedY)
            relativeOffsetY = -relativeOffsetY;
        var locRect = _t._rect;
        _t._offsetPosition.x = relativeOffsetX + (_t._contentSize.width - locRect.width) / 2;
        _t._offsetPosition.y = relativeOffsetY + (_t._contentSize.height - locRect.height) / 2;

        // rendering using batch node
        if (_t._batchNode) {
            // update dirty, don't update _recursiveDirty
            _t.dirty = true;
        } else {
            // self rendering
            // Atlas: Vertex
            this._renderCmd._resetForBatchNode();
        }
    },

    // BatchNode methods
    /**
     * Updates the quad according the the rotation, position, scale values.
     * @function
     */
    updateTransform: function(){
        this._renderCmd.updateTransform();
    },

    /**
     * Add child to sprite (override cc.Node)
     * @function
     * @param {cc.Sprite} child
     * @param {Number} localZOrder  child's zOrder
     * @param {String} [tag] child's tag
     * @override
     */
    addChild: function (child, localZOrder, tag) {
        cc.assert(child, cc._LogInfos.CCSpriteBatchNode_addChild_2);

        if (localZOrder == null)
            localZOrder = child._localZOrder;
        if (tag == null)
            tag = child.tag;

        if(this._renderCmd._setBatchNodeForAddChild(child)){
            //cc.Node already sets isReorderChildDirty_ so this needs to be after batchNode check
            cc.Node.prototype.addChild.call(this, child, localZOrder, tag);
            this._hasChildren = true;
        }
    },

    // Frames
    /**
     * Sets a new sprite frame to the sprite.
     * @function
     * @param {cc.SpriteFrame|String} newFrame
     */
    setSpriteFrame: function (newFrame) {
        var _t = this;
        if(cc.isString(newFrame)){
            newFrame = cc.spriteFrameCache.getSpriteFrame(newFrame);
            cc.assert(newFrame, cc._LogInfos.Sprite_setSpriteFrame)
        }

        this.setNodeDirty(true);

        var frameOffset = newFrame.getOffset();
        _t._unflippedOffsetPositionFromCenter.x = frameOffset.x;
        _t._unflippedOffsetPositionFromCenter.y = frameOffset.y;

        // update rect
        var pNewTexture = newFrame.getTexture();
        var locTextureLoaded = newFrame.textureLoaded();
        if (!locTextureLoaded) {
            _t._textureLoaded = false;
            newFrame.addEventListener("load", function (sender) {
                _t._textureLoaded = true;
                var locNewTexture = sender.getTexture();
                if (locNewTexture !== _t._texture)
                    _t.texture = locNewTexture;
                _t.setTextureRect(sender.getRect(), sender.isRotated(), sender.getOriginalSize());
                _t.dispatchEvent("load");
                _t.setColor(_t.color);
            }, _t);
        }else{
            // update texture before updating texture rect
            if (pNewTexture !== _t._texture)
                _t.texture = pNewTexture;
            _t.setTextureRect(newFrame.getRect(), newFrame.isRotated(), newFrame.getOriginalSize());
        }
        this._renderCmd._updateForSetSpriteFrame(pNewTexture);
    },

    /**
     * Sets a new display frame to the sprite.
     * @param {cc.SpriteFrame|String} newFrame
     * @deprecated
     */
    setDisplayFrame: function(newFrame){
        cc.log(cc._LogInfos.Sprite_setDisplayFrame);
        this.setSpriteFrame(newFrame);
    },

    /**
     * Returns whether or not a cc.SpriteFrame is being displayed
     * @function
     * @param {cc.SpriteFrame} frame
     * @return {Boolean}
     */
    isFrameDisplayed: function(frame){
        return this._renderCmd.isFrameDisplayed(frame);
    },

    /**
     * Returns the current displayed frame.
     * @deprecated since 3.4, please use getSpriteFrame instead
     * @return {cc.SpriteFrame}
     */
    displayFrame: function () {
        return this.getSpriteFrame();
    },

    /**
     * Returns the current displayed frame.
     * @return {cc.SpriteFrame}
     */
    getSpriteFrame: function () {
        return new cc.SpriteFrame(this._texture,
            cc.rectPointsToPixels(this._rect),
            this._rectRotated,
            cc.pointPointsToPixels(this._unflippedOffsetPositionFromCenter),
            cc.sizePointsToPixels(this._contentSize));
    },

    /**
     * Sets the batch node to sprite
     * @function
     * @param {cc.SpriteBatchNode|null} spriteBatchNode
     * @example
     *  var batch = new cc.SpriteBatchNode("Images/grossini_dance_atlas.png", 15);
     *  var sprite = new cc.Sprite(batch.texture, cc.rect(0, 0, 57, 57));
     *  batch.addChild(sprite);
     *  layer.addChild(batch);
     */
    setBatchNode:function (spriteBatchNode) {
        var _t = this;
        _t._batchNode = spriteBatchNode; // weak reference

        // self render
        if (!_t._batchNode) {
            _t.atlasIndex = cc.Sprite.INDEX_NOT_INITIALIZED;
            _t.textureAtlas = null;
            _t._recursiveDirty = false;
            _t.dirty = false;

            this._renderCmd._resetForBatchNode();
        } else {
            // using batch
            _t._transformToBatch = cc.affineTransformIdentity();
            _t.textureAtlas = _t._batchNode.getTextureAtlas(); // weak ref
        }
    },

    // CCTextureProtocol
    /**
     * Sets the texture of sprite
     * @function
     * @param {cc.Texture2D|String} texture
     */
    setTexture: function (texture) {
        if(!texture)
            return this._renderCmd._setTexture(null);

        if(cc.isString(texture)){
            texture = cc.textureCache.addImage(texture);

            if(!texture._textureLoaded){
                texture.addEventListener("load", function(){
                    this._clearRect();
                    this._renderCmd._setTexture(texture);
                    this._changeRectWithTexture(texture.getContentSize());
                    this.setColor(this._realColor);
                    this._textureLoaded = true;
                }, this);
            }else{
                this._clearRect();
                this._renderCmd._setTexture(texture);
                this._changeRectWithTexture(texture.getContentSize());
                this.setColor(this._realColor);
                this._textureLoaded = true;
            }
        }else{
            // CCSprite: setTexture doesn't work when the sprite is rendered using a CCSpriteSheet
            cc.assert(texture instanceof cc.Texture2D, cc._LogInfos.Sprite_setTexture_2);
            this._clearRect();
            this._changeRectWithTexture(texture.getContentSize());
            this._renderCmd._setTexture(texture);
        }
    },

    _clearRect: function(){
        var texture = this._texture;
        if(texture){
            var textureRect = texture._contentSize;
            var spriteRect = this._rect;
            if(
                textureRect.width === spriteRect.width &&
                textureRect.height === spriteRect.height
            )
                spriteRect.width = spriteRect.height = 0;
        }
    },

    _changeRectWithTexture: function(rect){
        if(!rect || (!rect.width && !rect.height)) return;
        var textureRect = this.getTextureRect();
        if(textureRect.height || textureRect.width) return;
        rect.x = rect.x || 0;
        rect.y = rect.y || 0;
        rect.width = rect.width || 0;
        rect.height = rect.height || 0;
        this.setTextureRect(rect);
    },

    _createRenderCmd: function(){
        if(cc._renderType === cc._RENDER_TYPE_CANVAS)
            return new cc.Sprite.CanvasRenderCmd(this);
        else
            return new cc.Sprite.WebGLRenderCmd(this);
    }
});

/**
 * Create a sprite with image path or frame name or texture or spriteFrame.
 * @deprecated since v3.0, please use new construction instead
 * @see cc.Sprite
 * @param {String|cc.SpriteFrame|HTMLImageElement|cc.Texture2D} fileName  The string which indicates a path to image file, e.g., "scene1/monster.png".
 * @param {cc.Rect} rect  Only the contents inside rect of pszFileName's texture will be applied for this sprite.
 * @param {Boolean} [rotated] Whether or not the texture rectangle is rotated.
 * @return {cc.Sprite} A valid sprite object
 */
cc.Sprite.create = function (fileName, rect, rotated) {
    return new cc.Sprite(fileName, rect, rotated);
};

/**
 * @deprecated since v3.0, please use new construction instead
 * @see cc.Sprite
 * @function
 */
cc.Sprite.createWithTexture = cc.Sprite.create;

/**
 * @deprecated since v3.0, please use new construction instead
 * @see cc.Sprite
 * @function
 */
cc.Sprite.createWithSpriteFrameName = cc.Sprite.create;

/**
 * @deprecated since v3.0, please use new construction instead
 * @see cc.Sprite
 * @function
 */
cc.Sprite.createWithSpriteFrame = cc.Sprite.create;
/**
 * cc.Sprite invalid index on the cc.SpriteBatchNode
 * @constant
 * @type {Number}
 */
cc.Sprite.INDEX_NOT_INITIALIZED = -1;

cc.EventHelper.prototype.apply(cc.Sprite.prototype);

cc.assert(cc.isFunction(cc._tmp.PrototypeSprite), cc._LogInfos.MissingFile, "SpritesPropertyDefine.js");
cc._tmp.PrototypeSprite();
delete cc._tmp.PrototypeSprite;