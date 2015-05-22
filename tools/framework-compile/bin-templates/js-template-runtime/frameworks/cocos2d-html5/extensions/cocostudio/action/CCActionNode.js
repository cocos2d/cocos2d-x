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
 * The Cocostudio's action node, it contains action target, action frame list and current frame index.  it can be play action by calling playAciton.
 * @class
 * @extends ccs.Class
 */
ccs.ActionNode = ccs.Class.extend(/** @lends ccs.ActionNode# */{
    _currentFrameIndex: 0,
    _destFrameIndex: 0,
    _unitTime: 0,
    _actionTag: 0,
    _object: null,
    _actionSpawn: null,
    _action: null,
    _frameArray: null,
    _frameArrayNum: 0,

    /**
     * Construction of ccs.ActionNode
     */
    ctor: function () {
        this._currentFrameIndex = 0;
        this._destFrameIndex = 0;
        this._unitTime = 0.1;
        this._actionTag = 0;
        this._object = null;
        this._actionSpawn = null;
        this._action = null;
        this._frameArray = [];
        this._frameArrayNum = ccs.FRAME_TYPE_MAX;
        for (var i = 0; i < this._frameArrayNum; i++)
            this._frameArray.push([]);
    },

    /**
     *  Init properties with a json dictionary
     * @param {Object} dic
     * @param {Object} root
     */
    initWithDictionary: function (dic, root) {
        this.setActionTag(dic["ActionTag"]);
        var actionFrameList = dic["actionframelist"];
        for (var i = 0; i < actionFrameList.length; i++) {
            var actionFrameDic = actionFrameList[i];
            var frameIndex = actionFrameDic["frameid"];
            var frameTweenType = actionFrameDic["tweenType"];
            if(frameTweenType == null)
                frameTweenType = 0;
            var frameTweenParameterNum = actionFrameDic["tweenParameter"];

            var frameTweenParameter = [];
            for (var j = 0; j < frameTweenParameterNum; j++){
                var value = actionFrameDic["tweenParameter"][j];
                frameTweenParameter.push(value);
            }

            var actionFrame, actionArray;
            if (actionFrameDic["positionx"] !== undefined) {
                var positionX = actionFrameDic["positionx"];
                var positionY = actionFrameDic["positiony"];
                actionFrame = new ccs.ActionMoveFrame();
                actionFrame.frameIndex = frameIndex;
                actionFrame.setEasingType(frameTweenType);
                actionFrame.setEasingParameter(frameTweenParameter);
                actionFrame.setPosition(positionX, positionY);
                actionArray = this._frameArray[ccs.FRAME_TYPE_MOVE];
                actionArray.push(actionFrame);
            }

            if (actionFrameDic["scalex"] !== undefined) {
                var scaleX = actionFrameDic["scalex"];
                var scaleY = actionFrameDic["scaley"];
                actionFrame = new ccs.ActionScaleFrame();
                actionFrame.frameIndex = frameIndex;
                actionFrame.setEasingType(frameTweenType);
                actionFrame.setEasingParameter(frameTweenParameter);
                actionFrame.setScaleX(scaleX);
                actionFrame.setScaleY(scaleY);
                actionArray = this._frameArray[ccs.FRAME_TYPE_SCALE];
                actionArray.push(actionFrame);
            }

            if (actionFrameDic["rotation"] !== undefined) {
                var rotation = actionFrameDic["rotation"];
                actionFrame = new ccs.ActionRotationFrame();
                actionFrame.frameIndex = frameIndex;
                actionFrame.setEasingType(frameTweenType);
                actionFrame.setEasingParameter(frameTweenParameter);
                actionFrame.setRotation(rotation);
                actionArray = this._frameArray[ccs.FRAME_TYPE_ROTATE];
                actionArray.push(actionFrame);
            }

            if (actionFrameDic["opacity"] !== undefined) {
                var opacity = actionFrameDic["opacity"];
                actionFrame = new ccs.ActionFadeFrame();
                actionFrame.frameIndex = frameIndex;
                actionFrame.setEasingType(frameTweenType);
                actionFrame.setEasingParameter(frameTweenParameter);
                actionFrame.setOpacity(opacity);
                actionArray = this._frameArray[ccs.FRAME_TYPE_FADE];
                actionArray.push(actionFrame);
            }

            if (actionFrameDic["colorr"] !== undefined) {
                var colorR = actionFrameDic["colorr"];
                var colorG = actionFrameDic["colorg"];
                var colorB = actionFrameDic["colorb"];
                actionFrame = new ccs.ActionTintFrame();
                actionFrame.frameIndex = frameIndex;
                actionFrame.setEasingType(frameTweenType);
                actionFrame.setEasingParameter(frameTweenParameter);
                actionFrame.setColor(cc.color(colorR, colorG, colorB));
                actionArray = this._frameArray[ccs.FRAME_TYPE_TINT];
                actionArray.push(actionFrame);
            }
            actionFrameDic = null;
        }
        this._initActionNodeFromRoot(root);
    },

    _initActionNodeFromRoot: function (root) {
        if (root instanceof ccui.Widget) {
            var widget = ccui.helper.seekActionWidgetByActionTag(root, this.getActionTag());
            if (widget)
                this.setObject(widget);
        }
    },

    /**
     * Sets the time interval of frame.
     * @param {number} time
     */
    setUnitTime: function (time) {
        this._unitTime = time;
        this._refreshActionProperty();
    },

    /**
     * Returns the time interval of frame.
     * @returns {number}
     */
    getUnitTime: function () {
        return this._unitTime;
    },

    /**
     * Sets tag to ccs.ActionNode
     * @param {Number} tag
     */
    setActionTag: function (tag) {
        this._actionTag = tag;
    },

    /**
     * Returns the tag of ccs.ActionNode
     * @returns {number}
     */
    getActionTag: function () {
        return this._actionTag;
    },

    /**
     * Sets node which will run a action.
     * @param {Object} node
     */
    setObject: function (node) {
        this._object = node;
    },

    /**
     * Returns node which will run a action.
     * @returns {*}
     */
    getObject: function () {
        return this._object;
    },

    /**
     * Returns the target node of ccs.ActionNode
     * @returns {cc.Node}
     */
    getActionNode: function () {
        if (this._object instanceof cc.Node)
            return this._object;
        return null;
    },

    /**
     * Inserts an ActionFrame to ccs.ActionNode.
     * @param {number} index
     * @param {ccs.ActionFrame} frame
     */
    insertFrame: function (index, frame) {
        if (frame == null)
            return;
        var frameType = frame.frameType;
        var array = this._frameArray[frameType];
        array.splice(index, 0, frame);
    },

    /**
     * Pushes back an ActionFrame to ccs.ActionNode.
     * @param {ccs.ActionFrame} frame
     */
    addFrame: function (frame) {
        if (!frame)
            return;
        var frameType = frame.frameType;
        var array = this._frameArray[frameType];
        array.push(frame);
    },

    /**
     * Removes an ActionFrame from ccs.ActionNode.
     * @param {ccs.ActionFrame} frame
     */
    deleteFrame: function (frame) {
        if (frame == null)
            return;
        var frameType = frame.frameType;
        var array = this._frameArray[frameType];
        cc.arrayRemoveObject(array, frame);
    },

    /**
     * Removes all ActionFrames from ccs.ActionNode.
     */
    clearAllFrame: function () {
        for (var i = 0; i < this._frameArrayNum; i++)
            this._frameArray[i].length = 0;
    },

    _refreshActionProperty: function () {
        if (this._object === null)
            return null;
        var locSpawnArray = [];
        for (var i = 0; i < this._frameArrayNum; i++) {
            var locArray = this._frameArray[i];
            if (locArray.length <= 0)
                continue;
            var locSequenceArray = [];
            for (var j = 0; j < locArray.length; j++) {
                var locFrame = locArray[j];
                if (j !== 0) {
                    var locSrcFrame = locArray[j - 1];
                    var locDuration = (locFrame.frameIndex - locSrcFrame.frameIndex) * this.getUnitTime();
                    var locAction = locFrame.getAction(locDuration);
                    if(locAction)
                        locSequenceArray.push(locAction);
                }
            }
            if(locSequenceArray){
                var locSequence = cc.sequence(locSequenceArray);
                if (locSequence !== null)
                    locSpawnArray.push(locSequence);
            }
        }

        this._action = null;
        this._actionSpawn = cc.spawn(locSpawnArray);
        return this._actionSpawn;
    },

    /**
     * Plays ccs.ActionNode's action.
     * @param {cc.CallFunc} fun
     */
    playAction: function (fun) {
        if (this._object === null || this._actionSpawn === null)
            return;
        if(fun)
            this._action = cc.sequence(this._actionSpawn, fun);
        else
            this._action = cc.sequence(this._actionSpawn);
        this._runAction();
    },

    _runAction: function () {
        var node = this.getActionNode();
        if (node !== null && this._action !== null)
            node.runAction(this._action);
    },

    /**
     * Stops action.
     */
    stopAction: function () {
        var node = this.getActionNode();
        if (node !== null && this._action !== null) {
            if(!this._action.isDone())
                node.stopAction(this._action);
        }
    },

    /**
     * Returns index of first ActionFrame.
     * @returns {number}
     */
    getFirstFrameIndex: function () {
        var locFrameindex = 99999;
        var bFindFrame = false, locFrameArray = this._frameArray;
        for (var i = 0, len = this._frameArrayNum; i < len; i++) {
            var locArray = locFrameArray[i];
            if (locArray.length <= 0)
                continue;
            bFindFrame = true;
            var locFrameIndex = locArray[0].frameIndex;
            locFrameindex = locFrameindex > locFrameIndex ? locFrameIndex : locFrameindex;
        }
        if (!bFindFrame)
            locFrameindex = 0;
        return locFrameindex;
    },

    /**
     * Returns the index of last ccs.ActionFrame.
     * @returns {number}
     */
    getLastFrameIndex: function () {
        var locFrameindex = -1;
        var locIsFindFrame = false ,locFrameArray = this._frameArray;
        for (var i = 0, len = this._frameArrayNum; i < len; i++) {
            var locArray = locFrameArray[i];
            if (locArray.length <= 0)
                continue;
            locIsFindFrame = true;
            var locFrame = locArray[locArray.length - 1];
            var locFrameIndex = locFrame.frameIndex;
            locFrameindex = locFrameindex < locFrameIndex ? locFrameIndex : locFrameindex;
        }
        if (!locIsFindFrame)
            locFrameindex = 0;
        return locFrameindex;
    },

    /**
     * Updates action states to some time.
     * @param {Number} time
     * @returns {boolean}
     */
    updateActionToTimeLine: function (time) {
        var locIsFindFrame = false;
        var locUnitTime = this.getUnitTime();
        for (var i = 0; i < this._frameArrayNum; i++) {
            var locArray = this._frameArray[i];
            if (locArray === null)
                continue;

            for (var j = 0; j < locArray.length; j++) {
                var locFrame = locArray[j];
                if (locFrame.frameIndex * locUnitTime === time) {
                    this._easingToFrame(1.0, 1.0, locFrame);
                    locIsFindFrame = true;
                    break;
                } else if (locFrame.frameIndex * locUnitTime > time) {
                    if (j === 0) {
                        this._easingToFrame(1.0, 1.0, locFrame);
                        locIsFindFrame = false;
                    } else {
                        var locSrcFrame = locArray[j - 1];
                        var locDuration = (locFrame.frameIndex - locSrcFrame.frameIndex) * locUnitTime;
                        var locDelaytime = time - locSrcFrame.frameIndex * locUnitTime;
                        this._easingToFrame(locDuration, 1.0, locSrcFrame);
                        this._easingToFrame(locDuration, locDelaytime / locDuration, locFrame);
                        locIsFindFrame = true;
                    }
                    break;
                }
            }
        }
        return locIsFindFrame;
    },

    _easingToFrame: function (duration, delayTime, destFrame) {
        var action = destFrame.getAction(duration);
        var node = this.getActionNode();
        if (action == null || node == null)
            return;
        action.startWithTarget(node);
        action.update(delayTime);
    },

    /**
     * Returns if the action is done once time.
     * @returns {Boolean} that if the action is done once time
     */
    isActionDoneOnce: function () {
        if (this._action === null)
            return true;
        return this._action.isDone();
    }
});