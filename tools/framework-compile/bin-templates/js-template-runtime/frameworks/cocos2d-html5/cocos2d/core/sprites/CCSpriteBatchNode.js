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
 * <p>
 *     A cc.SpriteBatchNode can reference one and only one texture (one image file, one texture atlas).<br/>
 *     Only the cc.Sprites that are contained in that texture can be added to the cc.SpriteBatchNode.<br/>
 *     All cc.Sprites added to a cc.SpriteBatchNode are drawn in one WebGL draw call. <br/>
 *     If the cc.Sprites are not added to a cc.SpriteBatchNode then an WebGL draw call will be needed for each one, which is less efficient. <br/>
 *     <br/>
 *     Limitations:<br/>
 *       - The only object that is accepted as child (or grandchild, grand-grandchild, etc...) is cc.Sprite or any subclass of cc.Sprite. <br/>
 *          eg: particles, labels and layer can't be added to a cc.SpriteBatchNode. <br/>
 *       - Either all its children are Aliased or Antialiased. It can't be a mix. <br/>
 *          This is because "alias" is a property of the texture, and all the sprites share the same texture. </br>
 * </p>
 * @class
 * @extends cc.Node
 *
 * @param {String|cc.Texture2D} fileImage
 * @param {Number} capacity
 * @example
 *
 * // 1. create a SpriteBatchNode with image path
 * var spriteBatchNode = new cc.SpriteBatchNode("res/animations/grossini.png", 50);
 *
 * // 2. create a SpriteBatchNode with texture
 * var texture = cc.textureCache.addImage("res/animations/grossini.png");
 * var spriteBatchNode = new cc.SpriteBatchNode(texture,50);
 *
 * @property {cc.TextureAtlas}  textureAtlas    - The texture atlas
 * @property {Array}            descendants     - <@readonly> Descendants of sprite batch node
 */
cc.SpriteBatchNode = cc.Node.extend(/** @lends cc.SpriteBatchNode# */{
    _blendFunc: null,
    // all descendants: chlidren, gran children, etc...
    _descendants: null,
    _className: "SpriteBatchNode",

    ctor: function (fileImage, capacity) {
        cc.Node.prototype.ctor.call(this);
        this._descendants = [];
        this._blendFunc = new cc.BlendFunc(cc.BLEND_SRC, cc.BLEND_DST);

        var texture2D;
        capacity = capacity || cc.SpriteBatchNode.DEFAULT_CAPACITY;
        if (cc.isString(fileImage)) {
            texture2D = cc.textureCache.getTextureForKey(fileImage);
            if (!texture2D)
                texture2D = cc.textureCache.addImage(fileImage);
        }else if (fileImage instanceof cc.Texture2D)
            texture2D = fileImage;

        texture2D && this.initWithTexture(texture2D, capacity);
    },

    /**
     * <p>
     *    This is the opposite of "addQuadFromSprite.<br/>
     *    It add the sprite to the children and descendants array, but it doesn't update add it to the texture atlas<br/>
     * </p>
     * @param {cc.Sprite} child
     * @param {Number} z zOrder
     * @param {Number} aTag
     * @return {cc.SpriteBatchNode}
     */
    addSpriteWithoutQuad: function (child, z, aTag) {
        cc.assert(child, cc._LogInfos.SpriteBatchNode_addSpriteWithoutQuad_2);

        if (!(child instanceof cc.Sprite)) {
            cc.log(cc._LogInfos.SpriteBatchNode_addSpriteWithoutQuad);
            return null;
        }

        // quad index is Z
        child.atlasIndex = z;

        // XXX: optimize with a binary search
        var i = 0, len, locDescendants = this._descendants;
        if (locDescendants && locDescendants.length > 0) {
            for (i = 0, len = locDescendants.length; i < len; i++) {
                var obj = locDescendants[i];
                if (obj && (obj.atlasIndex >= z))
                    break;
            }
        }
        locDescendants.splice(i, 0, child);

        // IMPORTANT: Call super, and not self. Avoid adding it to the texture atlas array
        cc.Node.prototype.addChild.call(this, child, z, aTag);

        //#issue 1262 don't use lazy sorting, tiles are added as quads not as sprites, so sprites need to be added in order
        this.reorderBatch(false);
        return this;
    },

    // property
    /**
     * Return TextureAtlas of cc.SpriteBatchNode
     * @return {cc.TextureAtlas}
     */
    getTextureAtlas: function () {
        return this._renderCmd.getTextureAtlas();
    },

    /**
     * TextureAtlas of cc.SpriteBatchNode setter
     * @param {cc.TextureAtlas} textureAtlas
     */
    setTextureAtlas: function (textureAtlas) {
        this._renderCmd.getTextureAtlas(textureAtlas);
    },

    /**
     * Return Descendants of cc.SpriteBatchNode
     * @return {Array}
     */
    getDescendants: function () {
        return this._descendants;
    },

    /**
     * <p>
     *    Initializes a cc.SpriteBatchNode with a file image (.png, .jpeg, .pvr, etc) and a capacity of children.<br/>
     *    The capacity will be increased in 33% in runtime if it run out of space.<br/>
     *    The file will be loaded using the TextureMgr.<br/>
     *    Please pass parameters to constructor to initialize the sprite batch node, do not call this function yourself.
     * </p>
     * @param {String} fileImage
     * @param {Number} capacity
     * @return {Boolean}
     */
    initWithFile: function (fileImage, capacity) {
        var texture2D = cc.textureCache.getTextureForKey(fileImage);
        if (!texture2D)
            texture2D = cc.textureCache.addImage(fileImage);
        return this.initWithTexture(texture2D, capacity);
    },

    _setNodeDirtyForCache: function () {
        if(this._renderCmd && this._renderCmd._setNodeDirtyForCache)
            this._renderCmd._setNodeDirtyForCache();
    },

    /**
     * <p>
     *    initializes a cc.SpriteBatchNode with a file image (.png, .jpeg, .pvr, etc) and a capacity of children.<br/>
     *    The capacity will be increased in 33% in runtime if it run out of space.<br/>
     *    The file will be loaded using the TextureMgr.<br/>
     *    Please pass parameters to constructor to initialize the sprite batch node, do not call this function yourself.
     * </p>
     * @param {String} fileImage
     * @param {Number} capacity
     * @return {Boolean}
     */
    init: function (fileImage, capacity) {
        var texture2D = cc.textureCache.getTextureForKey(fileImage);
        if (!texture2D)
            texture2D = cc.textureCache.addImage(fileImage);
        return this.initWithTexture(texture2D, capacity);
    },

    /**
     * Increase Atlas Capacity
     */
    increaseAtlasCapacity: function () {
        this._renderCmd.increaseAtlasCapacity();
    },

    /**
     * Removes a child given a certain index. It will also cleanup the running actions depending on the cleanup parameter.
     * @warning Removing a child from a cc.SpriteBatchNode is very slow
     * @param {Number} index
     * @param {Boolean} doCleanup
     */
    removeChildAtIndex: function (index, doCleanup) {
        this.removeChild(this._children[index], doCleanup);
    },

    /**
     * Rebuild index in order for child
     * @param {cc.Sprite} pobParent
     * @param {Number} index
     * @return {Number}
     */
    rebuildIndexInOrder: function (pobParent, index) {
        var children = pobParent.children;
        if (children && children.length > 0) {
            for (var i = 0; i < children.length; i++) {
                var obj = children[i];
                if (obj && (obj.zIndex < 0))
                    index = this.rebuildIndexInOrder(obj, index);
            }
        }
        // ignore self (batch node)
        if (!pobParent === this) {
            pobParent.atlasIndex = index;
            index++;
        }
        if (children && children.length > 0) {
            for (i = 0; i < children.length; i++) {
                obj = children[i];
                if (obj && (obj.zIndex >= 0))
                    index = this.rebuildIndexInOrder(obj, index);
            }
        }
        return index;
    },

    /**
     * Returns highest atlas index in child
     * @param {cc.Sprite} sprite
     * @return {Number}
     */
    highestAtlasIndexInChild: function (sprite) {
        var children = sprite.children;

        if (!children || children.length === 0)
            return sprite.atlasIndex;
        else
            return this.highestAtlasIndexInChild(children[children.length - 1]);
    },

    /**
     * Returns lowest atlas index in child
     * @param {cc.Sprite} sprite
     * @return {Number}
     */
    lowestAtlasIndexInChild: function (sprite) {
        var children = sprite.children;
        if (!children || children.length === 0)
            return sprite.atlasIndex;
        else
            return this.lowestAtlasIndexInChild(children[children.length - 1]);
    },

    /**
     * Returns atlas index for child
     * @param {cc.Sprite} sprite
     * @param {Number} nZ
     * @return {Number}
     */
    atlasIndexForChild: function (sprite, nZ) {
        var selParent = sprite.parent;
        var brothers = selParent.children;
        var childIndex = brothers.indexOf(sprite);

        // ignore parent Z if parent is spriteSheet
        var ignoreParent = selParent === this;
        var previous = null;
        if (childIndex > 0 && childIndex < cc.UINT_MAX)
            previous = brothers[childIndex - 1];

        // first child of the sprite sheet
        if (ignoreParent) {
            if (childIndex === 0)
                return 0;
            return this.highestAtlasIndexInChild(previous) + 1;
        }

        // parent is a cc.Sprite, so, it must be taken into account
        // first child of an cc.Sprite ?
        if (childIndex === 0) {
            // less than parent and brothers
            if (nZ < 0)
                return selParent.atlasIndex;
            else
                return selParent.atlasIndex + 1;
        } else {
            // previous & sprite belong to the same branch
            if ((previous.zIndex < 0 && nZ < 0) || (previous.zIndex >= 0 && nZ >= 0))
                return this.highestAtlasIndexInChild(previous) + 1;

            // else (previous < 0 and sprite >= 0 )
            return selParent.atlasIndex + 1;
        }
    },

    /**
     * Sprites use this to start sortChildren, don't call this manually
     * @param {Boolean} reorder
     */
    reorderBatch: function (reorder) {
        this._reorderChildDirty = reorder;
    },

    /**
     * Sets the source and destination blending function for the texture
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
     * Returns the blending function used for the texture
     * @return {cc.BlendFunc}
     */
    getBlendFunc: function () {
        return new cc.BlendFunc(this._blendFunc.src,this._blendFunc.dst);
    },

    /**
     * Reorder children (override reorderChild of cc.Node)
     * @override
     * @param {cc.Sprite} child
     * @param {Number} zOrder
     */
    reorderChild: function (child, zOrder) {
        cc.assert(child, cc._LogInfos.SpriteBatchNode_reorderChild_2);
        if (this._children.indexOf(child) === -1) {
            cc.log(cc._LogInfos.SpriteBatchNode_reorderChild);
            return;
        }
        if (zOrder === child.zIndex)
            return;

        //set the z-order and sort later
        cc.Node.prototype.reorderChild.call(this, child, zOrder);
        //this.setNodeDirty();
    },

    /**
     * Removes a child from cc.SpriteBatchNode (override removeChild of cc.Node)
     * @param {cc.Sprite} child
     * @param {Boolean} cleanup
     */
    removeChild: function (child, cleanup) {
        // explicit null handling
        if (child == null)
            return;
        if (this._children.indexOf(child) === -1) {
            cc.log(cc._LogInfos.SpriteBatchNode_removeChild);
            return;
        }

        // cleanup before removing
        this.removeSpriteFromAtlas(child);
        cc.Node.prototype.removeChild.call(this, child, cleanup);
    },

    /**
     * <p>
     *   Updates a quad at a certain index into the texture atlas. The CCSprite won't be added into the children array.                 <br/>
     *   This method should be called only when you are dealing with very big AtlasSrite and when most of the cc.Sprite won't be updated.<br/>
     *   For example: a tile map (cc.TMXMap) or a label with lots of characters (BitmapFontAtlas)<br/>
     * </p>
     * @function
     * @param {cc.Sprite} sprite
     * @param {Number} index
     */
    updateQuadFromSprite: function (sprite, index) {
        cc.assert(sprite, cc._LogInfos.CCSpriteBatchNode_updateQuadFromSprite_2);
        if (!(sprite instanceof cc.Sprite)) {
            cc.log(cc._LogInfos.CCSpriteBatchNode_updateQuadFromSprite);
            return;
        }
        this._renderCmd.checkAtlasCapacity();

        //
        // update the quad directly. Don't add the sprite to the scene graph
        //
        sprite.batchNode = this;
        sprite.atlasIndex = index;
        sprite.dirty = true;
        // UpdateTransform updates the textureAtlas quad
        sprite.updateTransform();
    },

    /**
     * <p>
     *    Inserts a quad at a certain index into the texture atlas. The cc.Sprite won't be added into the children array.                    <br/>
     *    This method should be called only when you are dealing with very big AtlasSprite and when most of the cc.Sprite won't be updated.  <br/>
     *    For example: a tile map (cc.TMXMap) or a label with lots of characters (cc.LabelBMFont)
     * </p>
     * @function
     * @param {cc.Sprite} sprite
     * @param {Number} index
     */
    insertQuadFromSprite: function (sprite, index) {
        cc.assert(sprite, cc._LogInfos.CCSpriteBatchNode_insertQuadFromSprite_2);
        if (!(sprite instanceof cc.Sprite)) {
            cc.log(cc._LogInfos.CCSpriteBatchNode_insertQuadFromSprite);
            return;
        }
        this._renderCmd.insertQuad(sprite, index);

        //
        // update the quad directly. Don't add the sprite to the scene graph
        //
        sprite.batchNode = this;
        sprite.atlasIndex = index;

        // XXX: updateTransform will update the textureAtlas too, using updateQuad.
        // XXX: so, it should be AFTER the insertQuad
        sprite.dirty = true;
        sprite.updateTransform();
        this._renderCmd.cutting(sprite, index);
    },

    /**
     * <p>
     *    Initializes a cc.SpriteBatchNode with a texture2d and capacity of children.<br/>
     *    The capacity will be increased in 33% in runtime if it run out of space.<br/>
     *    Please pass parameters to constructor to initialize the sprite batch node, do not call this function yourself.
     * </p>
     * @function
     * @param {cc.Texture2D} tex
     * @param {Number} [capacity]
     * @return {Boolean}
     */
    initWithTexture: function (tex, capacity) {
        this._children.length = 0;
        this._descendants.length = 0;

        capacity = capacity || cc.SpriteBatchNode.DEFAULT_CAPACITY;
        this._renderCmd.initWithTexture(tex, capacity);
        return true;
    },

    /**
     * Insert a child
     * @param {cc.Sprite} sprite The child sprite
     * @param {Number} index The insert index
     */
    insertChild: function (sprite, index) {
        //TODO WebGL only        ?
        sprite.batchNode = this;
        sprite.atlasIndex = index;
        sprite.dirty = true;

        this._renderCmd.insertQuad(sprite, index);
        this._descendants.splice(index, 0, sprite);

        // update indices
        var i = index + 1, locDescendant = this._descendants;
        if (locDescendant && locDescendant.length > 0) {
            for (; i < locDescendant.length; i++)
                locDescendant[i].atlasIndex++;
        }

        // add children recursively
        var locChildren = sprite.children, child, l;
        if (locChildren) {
            for (i = 0, l = locChildren.length || 0; i < l; i++) {
                child = locChildren[i];
                if (child) {
                    var getIndex = this.atlasIndexForChild(child, child.zIndex);
                    this.insertChild(child, getIndex);
                }
            }
        }
    },

    /**
     * Add child at the end, faster than insert child
     * @function
     * @param {cc.Sprite} sprite
     */
    appendChild: function (sprite) {
        this._reorderChildDirty = true;
        sprite.batchNode = this;
        sprite.dirty = true;

        this._descendants.push(sprite);
        var index = this._descendants.length - 1;

        sprite.atlasIndex = index;
        this._renderCmd.insertQuad(sprite, index);

        // add children recursively
        var children = sprite.children;
        for (var i = 0, l = children.length || 0; i < l; i++)
            this.appendChild(children[i]);
    },

    /**
     * Removes sprite from TextureAtlas
     * @function
     * @param {cc.Sprite} sprite
     */
    removeSpriteFromAtlas: function (sprite) {
        this._renderCmd.removeQuadAtIndex(sprite.atlasIndex);

        // Cleanup sprite. It might be reused (issue #569)
        sprite.batchNode = null;
        var locDescendants = this._descendants;
        var index = locDescendants.indexOf(sprite);
        if (index !== -1) {
            locDescendants.splice(index, 1);

            // update all sprites beyond this one
            var len = locDescendants.length;
            for (; index < len; ++index) {
                var s = locDescendants[index];
                s.atlasIndex--;
            }
        }

        // remove children recursively
        var children = sprite.children;
        if (children) {
            for (var i = 0, l = children.length || 0; i < l; i++)
                children[i] && this.removeSpriteFromAtlas(children[i]);
        }
    },
    // CCTextureProtocol
    /**
     * Returns texture of the sprite batch node
     * @function
     * @return {cc.Texture2D}
     */
    getTexture: function () {
        return this._renderCmd.getTexture();
    },

    /**
     * Sets the texture of the sprite batch node.
     * @function
     * @param {cc.Texture2D} texture
     */
    setTexture: function(texture){
        this._renderCmd.setTexture(texture);
    },

    /**
     * Add child to the sprite batch node (override addChild of cc.Node)
     * @function
     * @override
     * @param {cc.Sprite} child
     * @param {Number} [zOrder]
     * @param {Number} [tag]
     */
    addChild: function (child, zOrder, tag) {
        cc.assert(child != null, cc._LogInfos.CCSpriteBatchNode_addChild_3);

        if(!this._renderCmd.isValidChild(child))
            return;

        zOrder = (zOrder == null) ? child.zIndex : zOrder;
        tag = (tag == null) ? child.tag : tag;
        cc.Node.prototype.addChild.call(this, child, zOrder, tag);
        this.appendChild(child);
        //this.setNodeDirty();
    },

    /**
     * Removes all children from the container and do a cleanup all running actions depending on the cleanup parameter. <br/>
     * (override removeAllChildren of cc.Node)
     * @function
     * @param {Boolean} cleanup
     */
    removeAllChildren: function (cleanup) {
        // Invalidate atlas index. issue #569
        // useSelfRender should be performed on all descendants. issue #1216
        var locDescendants = this._descendants;
        if (locDescendants && locDescendants.length > 0) {
            for (var i = 0, len = locDescendants.length; i < len; i++) {
                if (locDescendants[i])
                    locDescendants[i].batchNode = null;
            }
        }
        cc.Node.prototype.removeAllChildren.call(this, cleanup);
        this._descendants.length = 0;
        this._renderCmd.removeAllQuads();
    },

    /**
     * Sort all children nodes (override draw of cc.Node)
     */
    sortAllChildren: function () {
        if (this._reorderChildDirty) {
            var childrenArr = this._children;
            var i, j = 0, length = childrenArr.length, tempChild;
            //insertion sort
            for (i = 1; i < length; i++) {
                var tempItem = childrenArr[i];
                j = i - 1;
                tempChild = childrenArr[j];

                //continue moving element downwards while zOrder is smaller or when zOrder is the same but mutatedIndex is smaller
                while (j >= 0 && ( tempItem._localZOrder < tempChild._localZOrder ||
                    ( tempItem._localZOrder === tempChild._localZOrder && tempItem.arrivalOrder < tempChild.arrivalOrder ))) {
                    childrenArr[j + 1] = tempChild;
                    j = j - 1;
                    tempChild = childrenArr[j];
                }
                childrenArr[j + 1] = tempItem;
            }

            //sorted now check all children
            if (childrenArr.length > 0) {
                //first sort all children recursively based on zOrder
                this._arrayMakeObjectsPerformSelector(childrenArr, cc.Node._stateCallbackType.sortAllChildren);
                this._renderCmd.updateChildrenAtlasIndex(childrenArr);
            }
            this._reorderChildDirty = false;
        }
    },

    _createRenderCmd: function(){
        if(cc._renderType === cc._RENDER_TYPE_CANVAS)
            return new cc.SpriteBatchNode.CanvasRenderCmd(this);
        else
            return new cc.SpriteBatchNode.WebGLRenderCmd(this);
    }
});

var _p = cc.SpriteBatchNode.prototype;

// Override properties
cc.defineGetterSetter(_p, "texture", _p.getTexture, _p.setTexture);
cc.defineGetterSetter(_p, "textureAtlas", _p.getTextureAtlas, _p.setTextureAtlas);

// Extended properties
/** @expose */
_p.descendants;
cc.defineGetterSetter(_p, "descendants", _p.getDescendants);


/**
 * @constant
 * @type Number
 */
cc.SpriteBatchNode.DEFAULT_CAPACITY = 29;

/**
 * <p>
 *    creates a cc.SpriteBatchNodeCanvas with a file image (.png, .jpg etc) with a default capacity of 29 children.<br/>
 *    The capacity will be increased in 33% in runtime if it run out of space.<br/>
 *    The file will be loaded using the TextureMgr.<br/>
 * </p>
 * @deprecated since v3.0, please use new construction instead
 * @see cc.SpriteBatchNode
 * @param {String|cc.Texture2D} fileImage
 * @param {Number} capacity
 * @return {cc.SpriteBatchNode}
 */
cc.SpriteBatchNode.create = function (fileImage, capacity) {
    return new cc.SpriteBatchNode(fileImage, capacity);
};

/**
 * @deprecated since v3.0, please use new construction instead
 * @see cc.SpriteBatchNode
 * @function
 */
cc.SpriteBatchNode.createWithTexture = cc.SpriteBatchNode.create;