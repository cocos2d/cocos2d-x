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
 * The Bone of Armature, it has bone data, display manager and transform data for armature.
 * @class
 * @extends ccs.Node
 *
 * @param {String} [name] The name of the bone
 * @example
 *
 * var bone = new ccs.Bone("head");
 *
 * @property {ccs.BoneData}         boneData                - The bone data
 * @property {ccs.Armature}         armature                - The armature
 * @property {ccs.Bone}             parentBone              - The parent bone
 * @property {ccs.Armature}         childArmature           - The child armature
 * @property {Array}                childrenBone            - <@readonly> All children bones
 * @property {ccs.Tween}            tween                   - <@readonly> Tween
 * @property {ccs.FrameData}        tweenData               - <@readonly> The tween data
 * @property {ccs.ColliderFilter}   colliderFilter          - The collider filter
 * @property {ccs.DisplayManager}   displayManager          - The displayManager
 * @property {Boolean}              ignoreMovementBoneData  - Indicate whether force the bone to show When CCArmature play a animation and there isn't a CCMovementBoneData of this bone in this CCMovementData.
 * @property {String}               name                    - The name of the bone
 * @property {Boolean}              blendDirty              - Indicate whether the blend is dirty
 *
 */
ccs.Bone = ccs.Node.extend(/** @lends ccs.Bone# */{
    _boneData: null,
    _armature: null,
    _childArmature: null,
    _displayManager: null,
    ignoreMovementBoneData: false,
    _tween: null,
    _tweenData: null,
    _parentBone: null,
    _boneTransformDirty: false,
    _worldTransform: null,
    _blendFunc: null,
    blendDirty: false,
    _worldInfo: null,
    _armatureParentBone: null,
    _dataVersion: 0,
    _className: "Bone",

    ctor: function (name) {
        cc.Node.prototype.ctor.call(this);
        this._tweenData = null;
        this._parentBone = null;
        this._armature = null;
        this._childArmature = null;
        this._boneData = null;
        this._tween = null;
        this._displayManager = null;
        this.ignoreMovementBoneData = false;

        this._worldTransform = cc.affineTransformMake(1, 0, 0, 1, 0, 0);
        this._boneTransformDirty = true;
        this._blendFunc = new cc.BlendFunc(cc.BLEND_SRC, cc.BLEND_DST);
        this.blendDirty = false;
        this._worldInfo = null;

        this._armatureParentBone = null;
        this._dataVersion = 0;

        ccs.Bone.prototype.init.call(this, name);
    },

    /**
     * Initializes a ccs.Bone with the specified name
     * @param {String} name bone name
     * @return {Boolean}
     */
    init: function (name) {
//        cc.Node.prototype.init.call(this);
        if (name)
            this._name = name;
        this._tweenData = new ccs.FrameData();

        this._tween = new ccs.Tween(this);

        this._displayManager = new ccs.DisplayManager(this);

        this._worldInfo = new ccs.BaseData();
        this._boneData = new ccs.BaseData();

        return true;
    },

    /**
     * Sets the boneData to ccs.Bone.
     * @param {ccs.BoneData} boneData
     */
    setBoneData: function (boneData) {
        cc.assert(boneData, "_boneData must not be null");

        if(this._boneData !== boneData)
            this._boneData = boneData;

        this.setName(this._boneData.name);
        this._localZOrder = this._boneData.zOrder;
        this._displayManager.initDisplayList(boneData);
    },

    /**
     * Returns boneData of ccs.Bone.
     * @return {ccs.BoneData}
     */
    getBoneData: function () {
        return this._boneData;
    },

    /**
     * Sets the armature reference to ccs.Bone.
     * @param {ccs.Armature} armature
     */
    setArmature: function (armature) {
        this._armature = armature;
        if (armature) {
            this._tween.setAnimation(this._armature.getAnimation());
            this._dataVersion = this._armature.getArmatureData().dataVersion;
            this._armatureParentBone = this._armature.getParentBone();
        } else
            this._armatureParentBone = null;
    },

    /**
     * Returns the armature reference of ccs.Bone.
     * @return {ccs.Armature}
     */
    getArmature: function () {
        return this._armature;
    },

    /**
     * Updates worldTransform by tween data and updates display state
     * @param {Number} delta
     */
    update: function (delta) {
        if (this._parentBone)
            this._boneTransformDirty = this._boneTransformDirty || this._parentBone.isTransformDirty();

        if (this._armatureParentBone && !this._boneTransformDirty)
            this._boneTransformDirty = this._armatureParentBone.isTransformDirty();

        if (this._boneTransformDirty){
            var locTweenData = this._tweenData;
            if (this._dataVersion >= ccs.CONST_VERSION_COMBINED){
                ccs.TransformHelp.nodeConcat(locTweenData, this._boneData);
                locTweenData.scaleX -= 1;
                locTweenData.scaleY -= 1;
            }

            var locWorldInfo = this._worldInfo;
            locWorldInfo.copy(locTweenData);
            locWorldInfo.x = locTweenData.x + this._position.x;
            locWorldInfo.y = locTweenData.y + this._position.y;
            locWorldInfo.scaleX = locTweenData.scaleX * this._scaleX;
            locWorldInfo.scaleY = locTweenData.scaleY * this._scaleY;
            locWorldInfo.skewX = locTweenData.skewX + this._skewX + cc.degreesToRadians(this._rotationX);
            locWorldInfo.skewY = locTweenData.skewY + this._skewY - cc.degreesToRadians(this._rotationY);

            if(this._parentBone)
                this._applyParentTransform(this._parentBone);
            else {
                if (this._armatureParentBone)
                    this._applyParentTransform(this._armatureParentBone);
            }

            ccs.TransformHelp.nodeToMatrix(locWorldInfo, this._worldTransform);
            if (this._armatureParentBone)
                this._worldTransform = cc.affineTransformConcat(this._worldTransform, this._armature.getNodeToParentTransform());            //TODO TransformConcat
        }

        ccs.displayFactory.updateDisplay(this, delta, this._boneTransformDirty || this._armature.getArmatureTransformDirty());
        for(var i=0; i<this._children.length; i++) {
            var childBone = this._children[i];
            childBone.update(delta);
        }
        this._boneTransformDirty = false;
    },

    _applyParentTransform: function (parent) {
        var locWorldInfo = this._worldInfo;
        var locParentWorldTransform = parent._worldTransform;
        var locParentWorldInfo = parent._worldInfo;
        var x = locWorldInfo.x;
        var y = locWorldInfo.y;
        locWorldInfo.x = x * locParentWorldTransform.a + y * locParentWorldTransform.c + locParentWorldInfo.x;
        locWorldInfo.y = x * locParentWorldTransform.b + y * locParentWorldTransform.d + locParentWorldInfo.y;
        locWorldInfo.scaleX = locWorldInfo.scaleX * locParentWorldInfo.scaleX;
        locWorldInfo.scaleY = locWorldInfo.scaleY * locParentWorldInfo.scaleY;
        locWorldInfo.skewX = locWorldInfo.skewX + locParentWorldInfo.skewX;
        locWorldInfo.skewY = locWorldInfo.skewY + locParentWorldInfo.skewY;
    },

    /**
     * Sets BlendFunc to ccs.Bone.
     * @param {cc.BlendFunc|Number} blendFunc blendFunc or src of blendFunc
     * @param {Number} [dst] dst of blendFunc
     */
    setBlendFunc: function (blendFunc, dst) {
        var locBlendFunc = this._blendFunc, srcValue, dstValue;
        if(dst === undefined){
            srcValue = blendFunc.src;
            dstValue = blendFunc.dst;
        } else {
            srcValue = blendFunc;
            dstValue = dst;
        }
        if (locBlendFunc.src !== srcValue || locBlendFunc.dst !== dstValue) {
            locBlendFunc.src = srcValue;
            locBlendFunc.dst = dstValue;
            this.blendDirty = true;
        }
    },

    /**
     * Updates display color
     */
    updateColor: function () {
        var display = this._displayManager.getDisplayRenderNode();
        if (display !== null) {
            var cmd = this._renderCmd;
            display.setColor(
                cc.color(
                        cmd._displayedColor.r * this._tweenData.r / 255,
                        cmd._displayedColor.g * this._tweenData.g / 255,
                        cmd._displayedColor.b * this._tweenData.b / 255));
            display.setOpacity(cmd._displayedOpacity * this._tweenData.a / 255);
        }
    },

    /**
     * Updates display zOrder
     */
    updateZOrder: function () {
        if (this._armature.getArmatureData().dataVersion >= ccs.CONST_VERSION_COMBINED) {
            this.setLocalZOrder(this._tweenData.zOrder + this._boneData.zOrder);
        } else {
            this.setLocalZOrder(this._tweenData.zOrder);
        }
    },

    /**
     * Adds a child to this bone, and it will let this child call setParent(ccs.Bone) function to set self to it's parent
     * @param {ccs.Bone} child
     */
    addChildBone: function (child) {
        cc.assert(child, "Argument must be non-nil");
        cc.assert(!child.parentBone, "child already added. It can't be added again");

        if (this._children.indexOf(child) < 0) {
            this._children.push(child);
            child.setParentBone(this);
        }
    },

    /**
     * Removes a child bone
     * @param {ccs.Bone} bone
     * @param {Boolean} recursion
     */
    removeChildBone: function (bone, recursion) {
        if (this._children.length > 0 && this._children.getIndex(bone) !== -1 ) {
            if(recursion) {
                var ccbones = bone._children;
                for(var i=0; i<ccbones.length; i++){
                    var ccBone = ccbones[i];
                    bone.removeChildBone(ccBone, recursion);
                }
            }

            bone.setParentBone(null);
            bone.getDisplayManager().setCurrentDecorativeDisplay(null);
            cc.arrayRemoveObject(this._children, bone);
        }
    },

    /**
     * Removes itself from its parent ccs.Bone.
     * @param {Boolean} recursion
     */
    removeFromParent: function (recursion) {
        if (this._parentBone)
            this._parentBone.removeChildBone(this, recursion);
    },

    /**
     * Sets parent bone to ccs.Bone.
     * If _parent is NUll, then also remove this bone from armature.
     * It will not set the ccs.Armature, if you want to add the bone to a ccs.Armature, you should use ccs.Armature.addBone(bone, parentName).
     * @param {ccs.Bone}  parent  the parent bone.
     */
    setParentBone: function (parent) {
        this._parentBone = parent;
    },

    /**
     * Returns the parent bone of ccs.Bone.
     * @returns {ccs.Bone}
     */
    getParentBone: function(){
        return this._parentBone;
    },

    /**
     * Sets ccs.Bone's child armature
     * @param {ccs.Armature} armature
     */
    setChildArmature: function (armature) {
        if (this._childArmature !== armature) {
            if (armature == null && this._childArmature)
                this._childArmature.setParentBone(null);
            this._childArmature = armature;
        }
    },

    /**
     * Returns ccs.Bone's child armature.
     * @return {ccs.Armature}
     */
    getChildArmature: function () {
        return this._childArmature;
    },

    /**
     * Return the tween of ccs.Bone
     * @return {ccs.Tween}
     */
    getTween: function () {
        return this._tween;
    },

    /**
     * Sets the local zOrder to ccs.Bone.
     * @param {Number} zOrder
     */
    setLocalZOrder: function (zOrder) {
        if (this._localZOrder !== zOrder)
            cc.Node.prototype.setLocalZOrder.call(this, zOrder);
    },

    /**
     * Return the worldTransform of ccs.Bone.
     * @returns {cc.AffineTransform}
     */
    getNodeToArmatureTransform: function(){
        return this._worldTransform;
    },

    /**
     * Returns the world transform of ccs.Bone.
     * @override
     * @returns {cc.AffineTransform}
     */
    getNodeToWorldTransform: function(){
        return cc.affineTransformConcat(this._worldTransform, this._armature.getNodeToWorldTransform());
    },

    /**
     * Returns the display render node.
     * @returns {cc.Node}
     */
    getDisplayRenderNode: function () {
        return this._displayManager.getDisplayRenderNode();
    },

    /**
     * Returns the type of display render node
     * @returns {Number}
     */
    getDisplayRenderNodeType: function () {
        return this._displayManager.getDisplayRenderNodeType();
    },

    /**
     * Add display and use  _displayData init the display.
     * If index already have a display, then replace it.
     * If index is current display index, then also change display to _index
     * @param {ccs.DisplayData} displayData it include the display information, like DisplayType.
     *          If you want to create a sprite display, then create a CCSpriteDisplayData param
     *@param {Number}    index the index of the display you want to replace or add to
     *          -1 : append display from back
     */
    addDisplay: function (displayData, index) {
        index = index || 0;
        return this._displayManager.addDisplay(displayData, index);
    },

    /**
     * Removes display by index.
     * @param {Number} index display renderer's index
     */
    removeDisplay: function (index) {
        this._displayManager.removeDisplay(index);
    },

    /**
     * Changes display by index
     * @deprecated since v3.0, please use changeDisplayWithIndex instead.
     * @param {Number} index
     * @param {Boolean} force
     */
    changeDisplayByIndex: function (index, force) {
        cc.log("changeDisplayByIndex is deprecated. Use changeDisplayWithIndex instead.");
        this.changeDisplayWithIndex(index, force);
    },

    /**
     * Changes display by name
     * @deprecated since v3.0, please use changeDisplayWithName instead.
     * @param {String} name
     * @param {Boolean} force
     */
    changeDisplayByName: function(name, force){
        cc.log("changeDisplayByName is deprecated. Use changeDisplayWithName instead.");
        this.changeDisplayWithName(name, force);
    },

    /**
     * Changes display with index
     * @param {Number} index
     * @param {Boolean} force
     */
    changeDisplayWithIndex: function (index, force) {
        this._displayManager.changeDisplayWithIndex(index, force);
    },

    /**
     * Changes display with name
     * @param {String} name
     * @param {Boolean} force
     */
    changeDisplayWithName: function (name, force) {
        this._displayManager.changeDisplayWithName(name, force);
    },

    /**
     * Returns the collide detector of ccs.Bone.
     * @returns {*}
     */
    getColliderDetector: function(){
        var decoDisplay = this._displayManager.getCurrentDecorativeDisplay();
        if (decoDisplay){
            var detector = decoDisplay.getColliderDetector();
            if (detector)
                return detector;
        }
        return null;
    },

    /**
     * Sets collider filter to ccs.Bone.
     * @param {ccs.ColliderFilter} filter
     */
    setColliderFilter: function (filter) {
        var displayList = this._displayManager.getDecorativeDisplayList();
        for (var i = 0; i < displayList.length; i++) {
            var locDecoDisplay = displayList[i];
            var locDetector = locDecoDisplay.getColliderDetector();
            if (locDetector)
                locDetector.setColliderFilter(filter);
        }
    },

    /**
     * Returns collider filter of ccs.Bone.
     * @returns {cc.ColliderFilter}
     */
    getColliderFilter: function () {
        var decoDisplay = this.displayManager.getCurrentDecorativeDisplay();
        if (decoDisplay) {
            var detector = decoDisplay.getColliderDetector();
            if (detector)
                return detector.getColliderFilter();
        }
        return null;
    },

    /**
     * Sets ccs.Bone's transform dirty flag.
     * @param {Boolean} dirty
     */
    setTransformDirty: function (dirty) {
        this._boneTransformDirty = dirty;
    },

    /**
     * Returns ccs.Bone's transform dirty flag whether is dirty.
     * @return {Boolean}
     */
    isTransformDirty: function () {
        return this._boneTransformDirty;
    },

    /**
     * displayManager dirty getter
     * @return {ccs.DisplayManager}
     */
    getDisplayManager: function () {
        return this._displayManager;
    },

    /**
     *    When CCArmature play a animation, if there is not a CCMovementBoneData of this bone in this CCMovementData, this bone will hide.   <br/>
     *    Set IgnoreMovementBoneData to true, then this bone will also show.
     * @param {Boolean} bool
     */
    setIgnoreMovementBoneData: function (bool) {
        this._ignoreMovementBoneData = bool;
    },

    /**
     * Returns whether is ignore movement bone data.
     * @returns {Boolean}
     */
    isIgnoreMovementBoneData: function(){
        return this._ignoreMovementBoneData;
    },

    /**
     * Returns the blendFunc of ccs.Bone.
     * @return {cc.BlendFunc}
     */
    getBlendFunc: function () {
        return new cc.BlendFunc(this._blendFunc.src, this._blendFunc.dst);
    },

    /**
     * Sets blend dirty flag
     * @param {Boolean} dirty
     */
    setBlendDirty: function (dirty) {
        this._blendDirty = dirty;
    },

    /**
     * Returns the blend dirty flag whether is dirty.
     * @returns {Boolean|*|ccs.Bone._blendDirty}
     */
    isBlendDirty: function () {
        return this._blendDirty;
    },

    /**
     * Returns the tweenData of ccs.Bone.
     * @return {ccs.FrameData}
     */
    getTweenData: function () {
        return this._tweenData;
    },

    /**
     * Returns the world information of ccs.Bone.
     * @returns {ccs.BaseData}
     */
    getWorldInfo: function(){
        return this._worldInfo;
    },

    /**
     * Returns the children of ccs.Bone
     * @return {Array}
     * @deprecated since v3.0, please use getChildren instead.
     */
    getChildrenBone: function () {
        return this._children;
    },

    /**
     * Returns the worldTransform of ccs.Bone.
     * @return {cc.AffineTransform}
     * @deprecated since v3.0, please use getNodeToArmatureTransform instead.
     */
    nodeToArmatureTransform: function () {
        return this.getNodeToArmatureTransform();
    },

    /**
     * @deprecated
     * Returns the world affine transform matrix. The matrix is in Pixels.
     * @returns {cc.AffineTransform}
     */
    nodeToWorldTransform: function () {
        return this.getNodeToWorldTransform();
    },

    /**
     * Returns the collider body list in this bone.
     * @returns {Array|null}
     * @deprecated since v3.0, please use getColliderDetector to get a delector, and calls its getColliderBodyList instead.
     */
    getColliderBodyList: function () {
        var detector = this.getColliderDetector();
        if(detector)
            return detector.getColliderBodyList();
        return null;
    },

    /**
     * Returns whether is ignore movement bone data.
     * @return {Boolean}
     * @deprecated since v3.0, please isIgnoreMovementBoneData instead.
     */
    getIgnoreMovementBoneData: function () {
        return this.isIgnoreMovementBoneData();
    },

    _createRenderCmd: function(){
        if(cc._renderType === cc._RENDER_TYPE_CANVAS)
            return new ccs.Bone.CanvasRenderCmd(this);
        else
            return new ccs.Bone.WebGLRenderCmd(this);
    }
});

var _p = ccs.Bone.prototype;

// Extended properties
/** @expose */
_p.boneData;
cc.defineGetterSetter(_p, "boneData", _p.getBoneData, _p.setBoneData);
/** @expose */
_p.armature;
cc.defineGetterSetter(_p, "armature", _p.getArmature, _p.setArmature);
/** @expose */
_p.childArmature;
cc.defineGetterSetter(_p, "childArmature", _p.getChildArmature, _p.setChildArmature);
/** @expose */
_p.childrenBone;
cc.defineGetterSetter(_p, "childrenBone", _p.getChildrenBone);
/** @expose */
_p.tween;
cc.defineGetterSetter(_p, "tween", _p.getTween);
/** @expose */
_p.tweenData;
cc.defineGetterSetter(_p, "tweenData", _p.getTweenData);
/** @expose */
_p.colliderFilter;
cc.defineGetterSetter(_p, "colliderFilter", _p.getColliderFilter, _p.setColliderFilter);

_p = null;

/**
 * Allocates and initializes a bone.
 * @return {ccs.Bone}
 * @deprecated since v3.1, please use new construction instead
 */
ccs.Bone.create = function (name) {
    return new ccs.Bone(name);
};

ccs.Bone.RenderCmd = {
    _updateColor: function(){
        var node = this._node;
        var display = node._displayManager.getDisplayRenderNode();
        if (display !== null) {
            var displayCmd = display._renderCmd;
            display.setColor(cc.color( node._tweenData.r, node._tweenData.g, node._tweenData.g));
            display.setOpacity(node._tweenData.a);
            displayCmd._syncDisplayColor(this._displayedColor);
            displayCmd._syncDisplayOpacity(this._displayedOpacity);
            displayCmd._updateColor();
        }
    }
};

(function(){
    ccs.Bone.CanvasRenderCmd  = function(renderable){
        cc.Node.CanvasRenderCmd.call(this, renderable);
        this._needDraw = false;
    };

    var proto = ccs.Bone.CanvasRenderCmd.prototype = Object.create(cc.Node.CanvasRenderCmd.prototype);
    cc.inject(ccs.Bone.RenderCmd, proto);
    proto.constructor = ccs.Bone.CanvasRenderCmd;
})();

(function(){
    if(!cc.Node.WebGLRenderCmd)
        return;
    ccs.Bone.WebGLRenderCmd = function(renderable){
        cc.Node.WebGLRenderCmd.call(this, renderable);
        this._needDraw = false;
    };

    var proto = ccs.Bone.WebGLRenderCmd.prototype = Object.create(cc.Node.WebGLRenderCmd.prototype);
    cc.inject(ccs.Bone.RenderCmd, proto);
    proto.constructor = ccs.Bone.WebGLRenderCmd;
})();
