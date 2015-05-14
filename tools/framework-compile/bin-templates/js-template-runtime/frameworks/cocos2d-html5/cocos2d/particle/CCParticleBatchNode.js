/**
 * Copyright (c) 2008-2010 Ricardo Quesada
 * Copyright (c) 2011-2012 cocos2d-x.org
 * Copyright (c) 2013-2014 Chukong Technologies Inc.
 * Copyright (C) 2009 Matt Oswald
 * Copyright (c) 2011 Marco Tillemans
 *
 * http://www.cocos2d-x.org
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 * THE SOFTWARE.
 *
 */

/**
 * paticle default capacity
 * @constant
 * @type Number
 */
cc.PARTICLE_DEFAULT_CAPACITY = 500;

/**
 * <p>
 *    cc.ParticleBatchNode is like a batch node: if it contains children, it will draw them in 1 single OpenGL call  <br/>
 *    (often known as "batch draw").  </br>
 *
 *    A cc.ParticleBatchNode can reference one and only one texture (one image file, one texture atlas).<br/>
 *    Only the cc.ParticleSystems that are contained in that texture can be added to the cc.SpriteBatchNode.<br/>
 *    All cc.ParticleSystems added to a cc.SpriteBatchNode are drawn in one OpenGL ES draw call.<br/>
 *    If the cc.ParticleSystems are not added to a cc.ParticleBatchNode then an OpenGL ES draw call will be needed for each one, which is less efficient.</br>
 *
 *    Limitations:<br/>
 *    - At the moment only cc.ParticleSystem is supported<br/>
 *    - All systems need to be drawn with the same parameters, blend function, aliasing, texture<br/>
 *
 *    Most efficient usage<br/>
 *    - Initialize the ParticleBatchNode with the texture and enough capacity for all the particle systems<br/>
 *    - Initialize all particle systems and add them as child to the batch node<br/>
 * </p>
 * @class
 * @extends cc.ParticleSystem
 * @param {String|cc.Texture2D} fileImage
 * @param {Number} capacity
 *
 * @property {cc.Texture2D|HTMLImageElement|HTMLCanvasElement}  texture         - The used texture
 * @property {cc.TextureAtlas}                                  textureAtlas    - The texture atlas used for drawing the quads
 *
 * @example
 * 1.
 * //Create a cc.ParticleBatchNode with image path  and capacity
 * var particleBatchNode = new cc.ParticleBatchNode("res/grossini_dance.png",30);
 *
 * 2.
 * //Create a cc.ParticleBatchNode with a texture and capacity
 * var texture = cc.TextureCache.getInstance().addImage("res/grossini_dance.png");
 * var particleBatchNode = new cc.ParticleBatchNode(texture, 30);
 */
cc.ParticleBatchNode = cc.Node.extend(/** @lends cc.ParticleBatchNode# */{
	textureAtlas:null,
    //the blend function used for drawing the quads
    _blendFunc:null,
    _className:"ParticleBatchNode",

    /**
     * initializes the particle system with the name of a file on disk (for a list of supported formats look at the cc.Texture2D class), a capacity of particles
     * Constructor of cc.ParticleBatchNode
     * @param {String|cc.Texture2D} fileImage
     * @param {Number} capacity
     * @example
     * 1.
     * //Create a cc.ParticleBatchNode with image path  and capacity
     * var particleBatchNode = new cc.ParticleBatchNode("res/grossini_dance.png",30);
     *
     * 2.
     * //Create a cc.ParticleBatchNode with a texture and capacity
     * var texture = cc.TextureCache.getInstance().addImage("res/grossini_dance.png");
     * var particleBatchNode = new cc.ParticleBatchNode(texture, 30);
     */
    ctor:function (fileImage, capacity) {
        cc.Node.prototype.ctor.call(this);
        this._blendFunc = {src:cc.BLEND_SRC, dst:cc.BLEND_DST};
        if (cc.isString(fileImage)) {
            this.init(fileImage, capacity);
        } else if (fileImage instanceof cc.Texture2D) {
            this.initWithTexture(fileImage, capacity);
        }
    },

    _createRenderCmd: function(){
        if(cc._renderType === cc._RENDER_TYPE_CANVAS)
            return new cc.ParticleBatchNode.CanvasRenderCmd(this);
        else
            return new cc.ParticleBatchNode.WebGLRenderCmd(this);
    },

    /**
     * initializes the particle system with cc.Texture2D, a capacity of particles
     * @param {cc.Texture2D|HTMLImageElement|HTMLCanvasElement} texture
     * @param {Number} capacity
     * @return {Boolean}
     */
    initWithTexture:function (texture, capacity) {
        this.textureAtlas = new cc.TextureAtlas();
        this.textureAtlas.initWithTexture(texture, capacity);

        // no lazy alloc in this node
        this._children.length = 0;

        this._renderCmd._initWithTexture();
        return true;
    },

    /**
     * initializes the particle system with the name of a file on disk (for a list of supported formats look at the cc.Texture2D class), a capacity of particles
     * @param {String} fileImage
     * @param {Number} capacity
     * @return {Boolean}
     */
    initWithFile:function (fileImage, capacity) {
        var tex = cc.textureCache.addImage(fileImage);
        return this.initWithTexture(tex, capacity);
    },

    /**
     * initializes the particle system with the name of a file on disk (for a list of supported formats look at the cc.Texture2D class), a capacity of particles
     * @param {String} fileImage
     * @param {Number} capacity
     * @return {Boolean}
     */
    init:function (fileImage, capacity) {
        var tex = cc.textureCache.addImage(fileImage);
        return this.initWithTexture(tex, capacity);
    },

    /**
     * Add a child into the cc.ParticleBatchNode
     * @param {cc.ParticleSystem} child
     * @param {Number} zOrder
     * @param {Number} tag
     */
    addChild:function (child, zOrder, tag) {
        if(!child)
            throw "cc.ParticleBatchNode.addChild() : child should be non-null";
        if(!(child instanceof cc.ParticleSystem))
            throw "cc.ParticleBatchNode.addChild() : only supports cc.ParticleSystem as children";
        zOrder = (zOrder == null) ? child.zIndex : zOrder;
        tag = (tag == null) ? child.tag : tag;

        if(child.getTexture() !== this.textureAtlas.texture)
            throw "cc.ParticleSystem.addChild() : the child is not using the same texture id";

        // If this is the 1st children, then copy blending function
        var childBlendFunc = child.getBlendFunc();
        if (this._children.length === 0)
            this.setBlendFunc(childBlendFunc);
        else{
            if((childBlendFunc.src !== this._blendFunc.src) || (childBlendFunc.dst !== this._blendFunc.dst)){
                cc.log("cc.ParticleSystem.addChild() : Can't add a ParticleSystem that uses a different blending function");
                return;
            }
        }

        //no lazy sorting, so don't call super addChild, call helper instead
        var pos = this._addChildHelper(child, zOrder, tag);

        //get new atlasIndex
        var atlasIndex = 0;

        if (pos !== 0) {
            var p = this._children[pos - 1];
            atlasIndex = p.getAtlasIndex() + p.getTotalParticles();
        } else
            atlasIndex = 0;

        this.insertChild(child, atlasIndex);

        // update quad info
        child.setBatchNode(this);
    },

    /**
     * Inserts a child into the cc.ParticleBatchNode
     * @param {cc.ParticleSystem} pSystem
     * @param {Number} index
     */
    insertChild:function (pSystem, index) {
        var totalParticles = pSystem.getTotalParticles();
        var locTextureAtlas = this.textureAtlas;
        var totalQuads = locTextureAtlas.totalQuads;
        pSystem.setAtlasIndex(index);
        if (totalQuads + totalParticles > locTextureAtlas.getCapacity()) {
            this._increaseAtlasCapacityTo(totalQuads + totalParticles);
            // after a realloc empty quads of textureAtlas can be filled with gibberish (realloc doesn't perform calloc), insert empty quads to prevent it
            locTextureAtlas.fillWithEmptyQuadsFromIndex(locTextureAtlas.getCapacity() - totalParticles, totalParticles);
        }

        // make room for quads, not necessary for last child
        if (pSystem.getAtlasIndex() + totalParticles !== totalQuads)
            locTextureAtlas.moveQuadsFromIndex(index, index + totalParticles);

        // increase totalParticles here for new particles, update method of particlesystem will fill the quads
        locTextureAtlas.increaseTotalQuadsWith(totalParticles);
        this._updateAllAtlasIndexes();
    },

    /**
     * @param {cc.ParticleSystem} child
     * @param {Boolean} cleanup
     */
    removeChild:function (child, cleanup) {
        // explicit nil handling
        if (child == null)
            return;

        if(!(child instanceof cc.ParticleSystem))
            throw "cc.ParticleBatchNode.removeChild(): only supports cc.ParticleSystem as children";
        if(this._children.indexOf(child) === -1){
            cc.log("cc.ParticleBatchNode.removeChild(): doesn't contain the sprite. Can't remove it");
            return;
        }

        cc.Node.prototype.removeChild.call(this, child, cleanup);

        var locTextureAtlas = this.textureAtlas;
        // remove child helper
        locTextureAtlas.removeQuadsAtIndex(child.getAtlasIndex(), child.getTotalParticles());

        // after memmove of data, empty the quads at the end of array
        locTextureAtlas.fillWithEmptyQuadsFromIndex(locTextureAtlas.totalQuads, child.getTotalParticles());

        // paticle could be reused for self rendering
        child.setBatchNode(null);

        this._updateAllAtlasIndexes();
    },

    /**
     * Reorder will be done in this function, no "lazy" reorder to particles
     * @param {cc.ParticleSystem} child
     * @param {Number} zOrder
     */
    reorderChild:function (child, zOrder) {
        if(!child)
            throw "cc.ParticleBatchNode.reorderChild(): child should be non-null";
        if(!(child instanceof cc.ParticleSystem))
            throw "cc.ParticleBatchNode.reorderChild(): only supports cc.QuadParticleSystems as children";
        if(this._children.indexOf(child) === -1){
            cc.log("cc.ParticleBatchNode.reorderChild(): Child doesn't belong to batch");
            return;
        }

        if (zOrder === child.zIndex)
            return;

        // no reordering if only 1 child
        if (this._children.length > 1) {
            var getIndexes = this._getCurrentIndex(child, zOrder);

            if (getIndexes.oldIndex !== getIndexes.newIndex) {
                // reorder m_pChildren.array
                this._children.splice(getIndexes.oldIndex, 1)
                this._children.splice(getIndexes.newIndex, 0, child);

                // save old altasIndex
                var oldAtlasIndex = child.getAtlasIndex();

                // update atlas index
                this._updateAllAtlasIndexes();

                // Find new AtlasIndex
                var newAtlasIndex = 0;
                var locChildren = this._children;
                for (var i = 0; i < locChildren.length; i++) {
                    var pNode = locChildren[i];
                    if (pNode === child) {
                        newAtlasIndex = child.getAtlasIndex();
                        break;
                    }
                }

                // reorder textureAtlas quads
                this.textureAtlas.moveQuadsFromIndex(oldAtlasIndex, child.getTotalParticles(), newAtlasIndex);

                child.updateWithNoTime();
            }
        }
        child._setLocalZOrder(zOrder);
    },

    /**
     * @param {Number} index
     * @param {Boolean} doCleanup
     */
    removeChildAtIndex:function (index, doCleanup) {
        this.removeChild(this._children[i], doCleanup);
    },

    /**
     * @param {Boolean} doCleanup
     */
    removeAllChildren:function (doCleanup) {
        var locChildren = this._children;
        for (var i = 0; i < locChildren.length; i++) {
            locChildren[i].setBatchNode(null);
        }
        cc.Node.prototype.removeAllChildren.call(this, doCleanup);
        this.textureAtlas.removeAllQuads();
    },

    /**
     * disables a particle by inserting a 0'd quad into the texture atlas
     * @param {Number} particleIndex
     */
    disableParticle:function (particleIndex) {
        var quad = this.textureAtlas.quads[particleIndex];
        quad.br.vertices.x = quad.br.vertices.y = quad.tr.vertices.x = quad.tr.vertices.y =
            quad.tl.vertices.x = quad.tl.vertices.y = quad.bl.vertices.x = quad.bl.vertices.y = 0.0;
        this.textureAtlas._setDirty(true);
    },

    /**
     * returns the used texture
     * @return {cc.Texture2D}
     */
    getTexture:function () {
        return this.textureAtlas.texture;
    },

    /**
     * sets a new texture. it will be retained
     * @param {cc.Texture2D} texture
     */
    setTexture:function (texture) {
        this.textureAtlas.texture = texture;

        // If the new texture has No premultiplied alpha, AND the blendFunc hasn't been changed, then update it
        var locBlendFunc = this._blendFunc;
        if (texture && !texture.hasPremultipliedAlpha() && ( locBlendFunc.src === cc.BLEND_SRC && locBlendFunc.dst === cc.BLEND_DST )) {
            locBlendFunc.src = cc.SRC_ALPHA;
            locBlendFunc.dst = cc.ONE_MINUS_SRC_ALPHA;
        }
    },

    /**
     * set the blending function used for the texture
     * @param {Number|Object} src
     * @param {Number} dst
     */
    setBlendFunc:function (src, dst) {
        if (dst === undefined){
            this._blendFunc.src = src.src;
            this._blendFunc.dst = src.dst;
        } else{
            this._blendFunc.src = src;
            this._blendFunc.src = dst;
        }
    },

    /**
     * returns the blending function used for the texture
     * @return {cc.BlendFunc}
     */
    getBlendFunc:function () {
        return new cc.BlendFunc(this._blendFunc.src, this._blendFunc.dst);
    },

    _updateAllAtlasIndexes:function () {
        var index = 0;
        var locChildren = this._children;
        for (var i = 0; i < locChildren.length; i++) {
            var child = locChildren[i];
            child.setAtlasIndex(index);
            index += child.getTotalParticles();
        }
    },

    _increaseAtlasCapacityTo:function (quantity) {
        cc.log("cocos2d: cc.ParticleBatchNode: resizing TextureAtlas capacity from [" + this.textureAtlas.getCapacity()
            + "] to [" + quantity + "].");

        if (!this.textureAtlas.resizeCapacity(quantity)) {
            // serious problems
            cc.log("cc.ParticleBatchNode._increaseAtlasCapacityTo() : WARNING: Not enough memory to resize the atlas");
        }
    },

    _searchNewPositionInChildrenForZ:function (z) {
        var locChildren = this._children;
        var count = locChildren.length;
        for (var i = 0; i < count; i++) {
            if (locChildren[i].zIndex > z)
                return i;
        }
        return count;
    },

    _getCurrentIndex:function (child, z) {
        var foundCurrentIdx = false;
        var foundNewIdx = false;

        var newIndex = 0;
        var oldIndex = 0;

        var minusOne = 0, locChildren = this._children;
        var count = locChildren.length;
        for (var i = 0; i < count; i++) {
            var pNode = locChildren[i];
            // new index
            if (pNode.zIndex > z && !foundNewIdx) {
                newIndex = i;
                foundNewIdx = true;

                if (foundCurrentIdx && foundNewIdx)
                    break;
            }
            // current index
            if (child === pNode) {
                oldIndex = i;
                foundCurrentIdx = true;
                if (!foundNewIdx)
                    minusOne = -1;
                if (foundCurrentIdx && foundNewIdx)
                    break;
            }
        }
        if (!foundNewIdx)
            newIndex = count;
        newIndex += minusOne;
        return {newIndex:newIndex, oldIndex:oldIndex};
    },

    //
    // <p>
    //     don't use lazy sorting, reordering the particle systems quads afterwards would be too complex                                    <br/>
    //     XXX research whether lazy sorting + freeing current quads and calloc a new block with size of capacity would be faster           <br/>
    //     XXX or possibly using vertexZ for reordering, that would be fastest                                                              <br/>
    //     this helper is almost equivalent to CCNode's addChild, but doesn't make use of the lazy sorting                                  <br/>
    // </p>
    // @param {cc.ParticleSystem} child
    // @param {Number} z
    // @param {Number} aTag
    // @return {Number}
    // @private
    //
    _addChildHelper:function (child, z, aTag) {
        if(!child)
            throw "cc.ParticleBatchNode._addChildHelper(): child should be non-null";
        if(child.parent){
            cc.log("cc.ParticleBatchNode._addChildHelper(): child already added. It can't be added again");
            return null;
        }


        if (!this._children)
            this._children = [];

        //don't use a lazy insert
        var pos = this._searchNewPositionInChildrenForZ(z);

        this._children.splice(pos, 0, child);
        child.tag = aTag;
        child._setLocalZOrder(z);
        child.parent = this;
        if (this._running) {
            child.onEnter();
            child.onEnterTransitionDidFinish();
        }
        return pos;
    },

    _updateBlendFunc:function () {
        if (!this.textureAtlas.texture.hasPremultipliedAlpha()) {
            this._blendFunc.src = cc.SRC_ALPHA;
            this._blendFunc.dst = cc.ONE_MINUS_SRC_ALPHA;
        }
    },

    /**
     * return the texture atlas used for drawing the quads
     * @return {cc.TextureAtlas}
     */
    getTextureAtlas:function () {
        return this.textureAtlas;
    },

    /**
     * set the texture atlas used for drawing the quads
     * @param {cc.TextureAtlas} textureAtlas
     */
    setTextureAtlas:function (textureAtlas) {
        this.textureAtlas = textureAtlas;
    }
});

var _p = cc.ParticleBatchNode.prototype;

// Extended properties
/** @expose */
_p.texture;
cc.defineGetterSetter(_p, "texture", _p.getTexture, _p.setTexture);


/**
 * initializes the particle system with the name of a file on disk (for a list of supported formats look at the cc.Texture2D class), a capacity of particles
 * @deprecated since v3.0 please use new cc.ParticleBatchNode(filename, capacity) instead.
 * @param {String|cc.Texture2D} fileImage
 * @param {Number} capacity
 * @return {cc.ParticleBatchNode}
 */
cc.ParticleBatchNode.create = function (fileImage, capacity) {
    return new cc.ParticleBatchNode(fileImage, capacity);
};
