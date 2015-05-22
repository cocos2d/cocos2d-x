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
 * The main class of Armature, it plays armature animation, manages and updates bones' state.
 * @class
 * @extends ccs.Node
 *
 * @property {ccs.Bone}                 parentBone      - The parent bone of the armature node
 * @property {ccs.ArmatureAnimation}    animation       - The animation
 * @property {ccs.ArmatureData}         armatureData    - The armature data
 * @property {String}                   name            - The name of the armature
 * @property {cc.SpriteBatchNode}       batchNode       - The batch node of the armature
 * @property {Number}                   version         - The version
 * @property {Object}                   body            - The body of the armature
 * @property {ccs.ColliderFilter}       colliderFilter  - <@writeonly> The collider filter of the armature
 */
ccs.Armature = ccs.Node.extend(/** @lends ccs.Armature# */{
    animation: null,
    armatureData: null,
    batchNode: null,
    _textureAtlas: null,
    _parentBone: null,
    _boneDic: null,
    _topBoneList: null,
    _armatureIndexDic: null,
    _offsetPoint: null,
    version: 0,
    _armatureTransformDirty: true,
    _body: null,
    _blendFunc: null,
    _className: "Armature",

    /**
     * Create a armature node.
     * Constructor of ccs.Armature
     * @param {String} name
     * @param {ccs.Bone} parentBone
     * @example
     * var armature = new ccs.Armature();
     */
    ctor: function (name, parentBone) {
        cc.Node.prototype.ctor.call(this);
        this._name = "";
        this._topBoneList = [];
        this._armatureIndexDic = {};
        this._offsetPoint = cc.p(0, 0);
        this._armatureTransformDirty = true;
        this._blendFunc = {src: cc.BLEND_SRC, dst: cc.BLEND_DST};
        name && ccs.Armature.prototype.init.call(this, name, parentBone);
    },

    /**
     * Initializes a CCArmature with the specified name and CCBone
     * @param {String} [name]
     * @param {ccs.Bone} [parentBone]
     * @return {Boolean}
     */
    init: function (name, parentBone) {
        cc.Node.prototype.init.call(this);
        if (parentBone)
            this._parentBone = parentBone;
        this.removeAllChildren();
        this.animation = new ccs.ArmatureAnimation();
        this.animation.init(this);

        this._boneDic = {};
        this._topBoneList.length = 0;

        //this._name = name || "";
        var armatureDataManager = ccs.armatureDataManager;

        var animationData;
        if (name !== "") {
            //animationData
            animationData = armatureDataManager.getAnimationData(name);
            cc.assert(animationData, "AnimationData not exist!");

            this.animation.setAnimationData(animationData);

            //armatureData
            var armatureData = armatureDataManager.getArmatureData(name);
            cc.assert(armatureData, "ArmatureData not exist!");

            this.armatureData = armatureData;

            //boneDataDic
            var boneDataDic = armatureData.getBoneDataDic();
            for (var key in boneDataDic) {
                var bone = this.createBone(String(key));

                //! init bone's  Tween to 1st movement's 1st frame
                do {
                    var movData = animationData.getMovement(animationData.movementNames[0]);
                    if (!movData) break;

                    var _movBoneData = movData.getMovementBoneData(bone.getName());
                    if (!_movBoneData || _movBoneData.frameList.length <= 0) break;

                    var frameData = _movBoneData.getFrameData(0);
                    if (!frameData) break;

                    bone.getTweenData().copy(frameData);
                    bone.changeDisplayWithIndex(frameData.displayIndex, false);
                } while (0);
            }

            this.update(0);
            this.updateOffsetPoint();
        } else {
            name = "new_armature";
            this.armatureData = new ccs.ArmatureData();
            this.armatureData.name = name;

            animationData = new ccs.AnimationData();
            animationData.name = name;

            armatureDataManager.addArmatureData(name, this.armatureData);
            armatureDataManager.addAnimationData(name, animationData);

            this.animation.setAnimationData(animationData);
        }

        this._renderCmd.initShaderCache();

        this.setCascadeOpacityEnabled(true);
        this.setCascadeColorEnabled(true);
        return true;
    },

    addChild: function (child, localZOrder, tag) {
        if(child instanceof ccui.Widget){
            cc.log("Armature doesn't support to add Widget as its child, it will be fix soon.");
            return;
        }
        cc.Node.prototype.addChild.call(this, child, localZOrder, tag);
    },

    /**
     * create a bone with name
     * @param {String} boneName
     * @return {ccs.Bone}
     */
    createBone: function (boneName) {
        var existedBone = this.getBone(boneName);
        if (existedBone)
            return existedBone;

        var boneData = this.armatureData.getBoneData(boneName);
        var parentName = boneData.parentName;

        var bone = null;
        if (parentName) {
            this.createBone(parentName);
            bone = new ccs.Bone(boneName);
            this.addBone(bone, parentName);
        } else {
            bone = new ccs.Bone(boneName);
            this.addBone(bone, "");
        }

        bone.setBoneData(boneData);
        bone.getDisplayManager().changeDisplayWithIndex(-1, false);
        return bone;
    },

    /**
     * Add a Bone to this Armature
     * @param {ccs.Bone} bone  The Bone you want to add to Armature
     * @param {String} parentName The parent Bone's name you want to add to. If it's  null, then set Armature to its parent
     */
    addBone: function (bone, parentName) {
        cc.assert(bone, "Argument must be non-nil");
        var locBoneDic = this._boneDic;
        if(bone.getName())
            cc.assert(!locBoneDic[bone.getName()], "bone already added. It can't be added again");

        if (parentName) {
            var boneParent = locBoneDic[parentName];
            if (boneParent)
                boneParent.addChildBone(bone);
            else
                this._topBoneList.push(bone);
        } else
            this._topBoneList.push(bone);
        bone.setArmature(this);

        locBoneDic[bone.getName()] = bone;
        this.addChild(bone);
    },

    /**
     * Remove a bone with the specified name. If recursion it will also remove child Bone recursively.
     * @param {ccs.Bone} bone The bone you want to remove
     * @param {Boolean} recursion Determine whether remove the bone's child  recursion.
     */
    removeBone: function (bone, recursion) {
        cc.assert(bone, "bone must be added to the bone dictionary!");

        bone.setArmature(null);
        bone.removeFromParent(recursion);
        cc.arrayRemoveObject(this._topBoneList, bone);

        delete  this._boneDic[bone.getName()];
        this.removeChild(bone, true);
    },

    /**
     * Gets a bone with the specified name
     * @param {String} name The bone's name you want to get
     * @return {ccs.Bone}
     */
    getBone: function (name) {
        return this._boneDic[name];
    },

    /**
     * Change a bone's parent with the specified parent name.
     * @param {ccs.Bone} bone The bone you want to change parent
     * @param {String} parentName The new parent's name
     */
    changeBoneParent: function (bone, parentName) {
        cc.assert(bone, "bone must be added to the bone dictionary!");

        var parentBone = bone.getParentBone();
        if (parentBone) {
            cc.arrayRemoveObject(parentBone.getChildren(), bone);
            bone.setParentBone(null);
        }

        if (parentName) {
            var boneParent = this._boneDic[parentName];
            if (boneParent) {
                boneParent.addChildBone(bone);
                cc.arrayRemoveObject(this._topBoneList, bone);
            } else
                this._topBoneList.push(bone);
        }
    },

    /**
     * Get CCArmature's bone dictionary
     * @return {Object} Armature's bone dictionary
     */
    getBoneDic: function () {
        return this._boneDic;
    },

    /**
     * Set contentSize and Calculate anchor point.
     */
    updateOffsetPoint: function () {
        // Set contentsize and Calculate anchor point.
        var rect = this.getBoundingBox();
        this.setContentSize(rect);
        var locOffsetPoint = this._offsetPoint;
        locOffsetPoint.x = -rect.x;
        locOffsetPoint.y = -rect.y;
        if (rect.width !== 0 && rect.height !== 0)
            this.setAnchorPoint(locOffsetPoint.x / rect.width, locOffsetPoint.y / rect.height);
    },

    getOffsetPoints: function(){
        return {x: this._offsetPoint.x, y: this._offsetPoint.y};
    },

    /**
     * Sets animation to this Armature
     * @param {ccs.ArmatureAnimation} animation
     */
    setAnimation: function (animation) {
        this.animation = animation;
    },

    /**
     * Gets the animation of this Armature.
     * @return {ccs.ArmatureAnimation}
     */
    getAnimation: function () {
        return this.animation;
    },

    /**
     * armatureTransformDirty getter
     * @returns {Boolean}
     */
    getArmatureTransformDirty: function () {
        return this._armatureTransformDirty;
    },

    /**
     * The update callback of ccs.Armature, it updates animation's state and updates bone's state.
     * @override
     * @param {Number} dt
     */
    update: function (dt) {
        this.animation.update(dt);
        var locTopBoneList = this._topBoneList;
        for (var i = 0; i < locTopBoneList.length; i++)
            locTopBoneList[i].update(dt);
        this._armatureTransformDirty = false;
    },

    /**
     * The callback when ccs.Armature enter stage.
     * @override
     */
    onEnter: function () {
        cc.Node.prototype.onEnter.call(this);
        this.scheduleUpdate();
    },

    /**
     * The callback when ccs.Armature exit stage.
     * @override
     */
    onExit: function () {
        cc.Node.prototype.onExit.call(this);
        this.unscheduleUpdate();
    },

    /**
     * This boundingBox will calculate all bones' boundingBox every time
     * @returns {cc.Rect}
     */
    getBoundingBox: function(){
        var minX, minY, maxX, maxY = 0;
        var first = true;

        var boundingBox = cc.rect(0, 0, 0, 0), locChildren = this._children;

        var len = locChildren.length;
        for (var i=0; i<len; i++) {
            var bone = locChildren[i];
            if (bone) {
                var r = bone.getDisplayManager().getBoundingBox();
                if (r.x === 0 && r.y === 0 && r.width === 0 && r.height === 0)
                    continue;

                if(first) {
                    minX = r.x;
                    minY = r.y;
                    maxX = r.x + r.width;
                    maxY = r.y + r.height;
                    first = false;
                } else {
                    minX = r.x < boundingBox.x ? r.x : boundingBox.x;
                    minY = r.y < boundingBox.y ? r.y : boundingBox.y;
                    maxX = r.x + r.width > boundingBox.x + boundingBox.width ?
                        r.x + r.width : boundingBox.x + boundingBox.width;
                    maxY = r.y + r.height > boundingBox.y + boundingBox.height ?
                        r.y + r.height : boundingBox.y + boundingBox.height;
                }

                boundingBox.x = minX;
                boundingBox.y = minY;
                boundingBox.width = maxX - minX;
                boundingBox.height = maxY - minY;
            }
        }
        return cc.rectApplyAffineTransform(boundingBox, this.getNodeToParentTransform());
    },

    /**
     * when bone  contain the point ,then return it.
     * @param {Number} x
     * @param {Number} y
     * @returns {ccs.Bone}
     */
    getBoneAtPoint: function (x, y) {
        var locChildren = this._children;
        for (var i = locChildren.length - 1; i >= 0; i--) {
            var child = locChildren[i];
            if (child instanceof ccs.Bone && child.getDisplayManager().containPoint(x, y))
                return child;
        }
        return null;
    },

    /**
     * Sets parent bone of this Armature
     * @param {ccs.Bone} parentBone
     */
    setParentBone: function (parentBone) {
        this._parentBone = parentBone;
        var locBoneDic = this._boneDic;
        for (var key in locBoneDic) {
            locBoneDic[key].setArmature(this);
        }
    },

    /**
     * Return parent bone of ccs.Armature.
     * @returns {ccs.Bone}
     */
    getParentBone: function () {
        return this._parentBone;
    },

    /**
     * draw contour
     */
    drawContour: function () {
        cc._drawingUtil.setDrawColor(255, 255, 255, 255);
        cc._drawingUtil.setLineWidth(1);
        var locBoneDic = this._boneDic;
        for (var key in locBoneDic) {
            var bone = locBoneDic[key];
            var detector = bone.getColliderDetector();
            if(!detector)
                continue;
            var bodyList = detector.getColliderBodyList();
            for (var i = 0; i < bodyList.length; i++) {
                var body = bodyList[i];
                var vertexList = body.getCalculatedVertexList();
                cc._drawingUtil.drawPoly(vertexList, vertexList.length, true);
            }
        }
    },

    setBody: function (body) {
        if (this._body === body)
            return;

        this._body = body;
        this._body.data = this;
        var child, displayObject, locChildren = this._children;
        for (var i = 0; i < locChildren.length; i++) {
            child = locChildren[i];
            if (child instanceof ccs.Bone) {
                var displayList = child.getDisplayManager().getDecorativeDisplayList();
                for (var j = 0; j < displayList.length; j++) {
                    displayObject = displayList[j];
                    var detector = displayObject.getColliderDetector();
                    if (detector)
                        detector.setBody(this._body);
                }
            }
        }
    },

    getShapeList: function () {
        if (this._body)
            return this._body.shapeList;
        return null;
    },

    getBody: function () {
        return this._body;
    },

    /**
     * Sets the blendFunc to ccs.Armature
     * @param {cc.BlendFunc|Number} blendFunc
     * @param {Number} [dst]
     */
    setBlendFunc: function (blendFunc, dst) {
        if(dst === undefined){
            this._blendFunc.src = blendFunc.src;
            this._blendFunc.dst = blendFunc.dst;
        } else {
            this._blendFunc.src = blendFunc;
            this._blendFunc.dst = dst;
        }
    },

    /**
     * Returns the blendFunc of ccs.Armature
     * @returns {cc.BlendFunc}
     */
    getBlendFunc: function () {
        return new cc.BlendFunc(this._blendFunc.src, this._blendFunc.dst);
    },

    /**
     * set collider filter
     * @param {ccs.ColliderFilter} filter
     */
    setColliderFilter: function (filter) {
        var locBoneDic = this._boneDic;
        for (var key in locBoneDic)
            locBoneDic[key].setColliderFilter(filter);
    },

    /**
     * Returns the armatureData of ccs.Armature
     * @return {ccs.ArmatureData}
     */
    getArmatureData: function () {
        return this.armatureData;
    },

    /**
     * Sets armatureData to this Armature
     * @param {ccs.ArmatureData} armatureData
     */
    setArmatureData: function (armatureData) {
        this.armatureData = armatureData;
    },

    getBatchNode: function () {
        return this.batchNode;
    },

    setBatchNode: function (batchNode) {
        this.batchNode = batchNode;
    },

    /**
     * version getter
     * @returns {Number}
     */
    getVersion: function () {
        return this.version;
    },

    /**
     * version setter
     * @param {Number} version
     */
    setVersion: function (version) {
        this.version = version;
    },

    _createRenderCmd: function(){
        if(cc._renderType === cc._RENDER_TYPE_CANVAS)
            return new ccs.Armature.CanvasRenderCmd(this);
        else
            return new ccs.Armature.WebGLRenderCmd(this);
    }
});

var _p = ccs.Armature.prototype;

/** @expose */
_p.parentBone;
cc.defineGetterSetter(_p, "parentBone", _p.getParentBone, _p.setParentBone);
/** @expose */
_p.body;
cc.defineGetterSetter(_p, "body", _p.getBody, _p.setBody);
/** @expose */
_p.colliderFilter;
cc.defineGetterSetter(_p, "colliderFilter", null, _p.setColliderFilter);

_p = null;

/**
 * Allocates an armature, and use the ArmatureData named name in ArmatureDataManager to initializes the armature.
 * @param {String} [name] Bone name
 * @param {ccs.Bone} [parentBone] the parent bone
 * @return {ccs.Armature}
 * @deprecated since v3.1, please use new construction instead
 */
ccs.Armature.create = function (name, parentBone) {
    return new ccs.Armature(name, parentBone);
};
