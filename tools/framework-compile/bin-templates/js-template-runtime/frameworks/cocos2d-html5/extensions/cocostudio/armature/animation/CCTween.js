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
 * The tween class for Armature.
 * @class
 * @extends ccs.ProcessBase
 *
 * @param {ccs.Bone} The bone to be animated
 *
 * @property {ccs.ArmatureAnimation}    animation   - The animation
 */
ccs.Tween = ccs.ProcessBase.extend(/** @lends ccs.Tween# */{
    _tweenData:null,
    _to:null,
    _from:null,
    _between:null,
    _movementBoneData:null,
    _bone:null,
    _frameTweenEasing:0,
    _betweenDuration:0,
    _totalDuration:0,
    _toIndex:0,
    _fromIndex:0,
    _animation:null,
    _passLastFrame:false,

    ctor:function (bone) {
        ccs.ProcessBase.prototype.ctor.call(this);
        this._frameTweenEasing = ccs.TweenType.LINEAR;

        ccs.Tween.prototype.init.call(this, bone);
    },

    /**
     * initializes a ccs.Tween with a CCBone
     * @param {ccs.Bone} bone
     * @return {Boolean}
     */
    init:function (bone) {
        this._from = new ccs.FrameData();
        this._between = new ccs.FrameData();

        this._bone = bone;
        this._tweenData = this._bone.getTweenData();
        this._tweenData.displayIndex = -1;

        this._animation = (this._bone !== null && this._bone.getArmature() !== null) ?
            this._bone.getArmature().getAnimation() :
            null;
        return true;
    },

    /**
     * Plays the tween.
     * @param {ccs.MovementBoneData} movementBoneData
     * @param {Number} durationTo
     * @param {Number} durationTween
     * @param {Boolean} loop
     * @param {ccs.TweenType} tweenEasing
     */
    play:function (movementBoneData, durationTo, durationTween, loop, tweenEasing) {
        ccs.ProcessBase.prototype.play.call(this, durationTo, durationTween, loop, tweenEasing);
        this._loopType = (loop)?ccs.ANIMATION_TYPE_TO_LOOP_FRONT:ccs.ANIMATION_TYPE_NO_LOOP;

        this._totalDuration = 0;
        this._betweenDuration = 0;
        this._fromIndex = this._toIndex = 0;

        var difMovement = movementBoneData !== this._movementBoneData;

        this.setMovementBoneData(movementBoneData);
        this._rawDuration = this._movementBoneData.duration;

        var nextKeyFrame = this._movementBoneData.getFrameData(0);
        this._tweenData.displayIndex = nextKeyFrame.displayIndex;

        if (this._bone.getArmature().getArmatureData().dataVersion >= ccs.CONST_VERSION_COMBINED)        {
            ccs.TransformHelp.nodeSub(this._tweenData, this._bone.getBoneData());
            this._tweenData.scaleX += 1;
            this._tweenData.scaleY += 1;
        }

        if (this._rawDuration === 0) {
            this._loopType = ccs.ANIMATION_TYPE_SINGLE_FRAME;
            if (durationTo === 0)
                this.setBetween(nextKeyFrame, nextKeyFrame);
            else
                this.setBetween(this._tweenData, nextKeyFrame);
            this._frameTweenEasing = ccs.TweenType.LINEAR;
        }
        else if (this._movementBoneData.frameList.length > 1) {
            this._durationTween = durationTween * this._movementBoneData.scale;
            if (loop && this._movementBoneData.delay !== 0)
                this.setBetween(this._tweenData, this.tweenNodeTo(this.updateFrameData(1 - this._movementBoneData.delay), this._between));
            else {
                if (!difMovement || durationTo === 0)
                    this.setBetween(nextKeyFrame, nextKeyFrame);
                else
                    this.setBetween(this._tweenData, nextKeyFrame);
            }
        }
        this.tweenNodeTo(0);
    },

    /**
     * Goes to specified frame and plays frame.
     * @param {Number} frameIndex
     */
    gotoAndPlay: function (frameIndex) {
        ccs.ProcessBase.prototype.gotoFrame.call(this, frameIndex);

        this._totalDuration = 0;
        this._betweenDuration = 0;
        this._fromIndex = this._toIndex = 0;

        this._isPlaying = true;
        this._isComplete = this._isPause = false;

        this._currentPercent = this._curFrameIndex / (this._rawDuration-1);
        this._currentFrame = this._nextFrameIndex * this._currentPercent;
    },

    /**
     * Goes to specified frame and pauses frame.
     * @param {Number} frameIndex
     */
    gotoAndPause: function (frameIndex) {
        this.gotoAndPlay(frameIndex);
        this.pause();
    },

    /**
     * update will call this handler, you can handle your logic here
     */
    updateHandler:function () {
        var locCurrentPercent = this._currentPercent == null ? 1 : this._currentPercent;
        var locLoopType = this._loopType;
        if (locCurrentPercent >= 1) {
            switch (locLoopType) {
                case ccs.ANIMATION_TYPE_SINGLE_FRAME:
                    locCurrentPercent = 1;
                    this._isComplete = true;
                    this._isPlaying = false;
                    break;
                case ccs.ANIMATION_TYPE_NO_LOOP:
                    locLoopType = ccs.ANIMATION_TYPE_MAX;
                    if (this._durationTween <= 0)
                        locCurrentPercent = 1;
                    else
                        locCurrentPercent = (locCurrentPercent - 1) * this._nextFrameIndex / this._durationTween;
                    if (locCurrentPercent >= 1) {
                        locCurrentPercent = 1;
                        this._isComplete = true;
                        this._isPlaying = false;
                        break;
                    } else {
                        this._nextFrameIndex = this._durationTween;
                        this._currentFrame = locCurrentPercent * this._nextFrameIndex;
                        this._totalDuration = 0;
                        this._betweenDuration = 0;
                        this._fromIndex = this._toIndex = 0;
                        break;
                    }
                case ccs.ANIMATION_TYPE_TO_LOOP_FRONT:
                    locLoopType = ccs.ANIMATION_TYPE_LOOP_FRONT;
                    this._nextFrameIndex = this._durationTween > 0 ? this._durationTween : 1;

                    if (this._movementBoneData.delay !== 0) {
                        this._currentFrame = (1 - this._movementBoneData.delay) * this._nextFrameIndex;
                        locCurrentPercent = this._currentFrame / this._nextFrameIndex;
                    } else {
                        locCurrentPercent = 0;
                        this._currentFrame = 0;
                    }

                    this._totalDuration = 0;
                    this._betweenDuration = 0;
                    this._fromIndex = this._toIndex = 0;
                    break;
                case ccs.ANIMATION_TYPE_MAX:
                    locCurrentPercent = 1;
                    this._isComplete = true;
                    this._isPlaying = false;
                    break;
                default:
                    this._currentFrame = ccs.fmodf(this._currentFrame, this._nextFrameIndex);
                    break;
            }
        }

        if (locCurrentPercent < 1 && locLoopType < ccs.ANIMATION_TYPE_TO_LOOP_BACK)
            locCurrentPercent = Math.sin(locCurrentPercent * cc.PI / 2);

        this._currentPercent = locCurrentPercent;
        this._loopType = locLoopType;

        if (locLoopType > ccs.ANIMATION_TYPE_TO_LOOP_BACK)
            locCurrentPercent = this.updateFrameData(locCurrentPercent);
        if (this._frameTweenEasing !== ccs.TweenType.TWEEN_EASING_MAX)
            this.tweenNodeTo(locCurrentPercent);
    },

    /**
     * Calculate the between value of _from and _to, and give it to between frame data
     * @param {ccs.FrameData} from
     * @param {ccs.FrameData} to
     * @param {Boolean} [limit=true]
     */
    setBetween:function (from, to, limit) {   //TODO set tweenColorTo to protected in v3.1
        if(limit === undefined)
            limit = true;
        do {
            if (from.displayIndex < 0 && to.displayIndex >= 0) {
                this._from.copy(to);
                this._between.subtract(to, to, limit);
                break;
            }
            if (to.displayIndex < 0 && from.displayIndex >= 0) {
                this._from.copy(from);
                this._between.subtract(to, to, limit);
                break;
            }
            this._from.copy(from);
            this._between.subtract(from, to, limit);
        } while (0);
        if (!from.isTween){
            this._tweenData.copy(from);
            this._tweenData.isTween = true;
        }
        this.arriveKeyFrame(from);
    },

    /**
     * Update display index and process the key frame event when arrived a key frame
     * @param {ccs.FrameData} keyFrameData
     */
    arriveKeyFrame:function (keyFrameData) {                         //TODO set tweenColorTo to protected in v3.1
        if (keyFrameData) {
            var locBone = this._bone;
            var displayManager = locBone.getDisplayManager();

            //! Change bone's display
            var displayIndex = keyFrameData.displayIndex;

            if (!displayManager.getForceChangeDisplay())
                displayManager.changeDisplayWithIndex(displayIndex, false);

            //! Update bone zorder, bone's zorder is determined by frame zorder and bone zorder
            this._tweenData.zOrder = keyFrameData.zOrder;
            locBone.updateZOrder();

            //! Update blend type
            this._bone.setBlendFunc(keyFrameData.blendFunc);

            var childAramture = locBone.getChildArmature();
            if (childAramture) {
                if (keyFrameData.movement !== "")
                    childAramture.getAnimation().play(keyFrameData.movement);
            }
        }
    },

    /**
     * According to the percent to calculate current CCFrameData with tween effect
     * @param {Number} percent
     * @param {ccs.FrameData} [node]
     * @return {ccs.FrameData}
     */
    tweenNodeTo:function (percent, node) {         //TODO set tweenColorTo to protected in v3.1
        if (!node)
            node = this._tweenData;

        var locFrom = this._from;
        var locBetween = this._between;
        if (!locFrom.isTween)
            percent = 0;
        node.x = locFrom.x + percent * locBetween.x;
        node.y = locFrom.y + percent * locBetween.y;
        node.scaleX = locFrom.scaleX + percent * locBetween.scaleX;
        node.scaleY = locFrom.scaleY + percent * locBetween.scaleY;
        node.skewX = locFrom.skewX + percent * locBetween.skewX;
        node.skewY = locFrom.skewY + percent * locBetween.skewY;

        this._bone.setTransformDirty(true);
        if (node && locBetween.isUseColorInfo)
            this.tweenColorTo(percent, node);

        return node;
    },

    /**
     * According to the percent to calculate current color with tween effect
     * @param {Number} percent
     * @param {ccs.FrameData} node
     */
    tweenColorTo:function(percent,node){    //TODO set tweenColorTo to protected in v3.1
        var locFrom = this._from;
        var locBetween = this._between;
        node.a = locFrom.a + percent * locBetween.a;
        node.r = locFrom.r + percent * locBetween.r;
        node.g = locFrom.g + percent * locBetween.g;
        node.b = locFrom.b + percent * locBetween.b;
        this._bone.updateColor();
    },

    /**
     * Calculate which frame arrived, and if current frame have event, then call the event listener
     * @param {Number} currentPercent
     * @return {Number}
     */
    updateFrameData:function (currentPercent) {                             //TODO set tweenColorTo to protected in v3.1
        if (currentPercent > 1 && this._movementBoneData.delay !== 0)
            currentPercent = ccs.fmodf(currentPercent,1);

        var playedTime = (this._rawDuration-1) * currentPercent;

        var from, to;
        var locTotalDuration = this._totalDuration,locBetweenDuration = this._betweenDuration, locToIndex = this._toIndex;
        // if play to current frame's front or back, then find current frame again
        if (playedTime < locTotalDuration || playedTime >= locTotalDuration + locBetweenDuration) {
            /*
             *  get frame length, if this._toIndex >= _length, then set this._toIndex to 0, start anew.
             *  this._toIndex is next index will play
             */
            var frames = this._movementBoneData.frameList;
            var length = frames.length;

            if (playedTime < frames[0].frameID){
                from = to = frames[0];
                this.setBetween(from, to);
                return this._currentPercent;
            }

            if (playedTime >= frames[length - 1].frameID) {
                // If _passLastFrame is true and playedTime >= frames[length - 1]->frameID, then do not need to go on.
                if (this._passLastFrame) {
                    from = to = frames[length - 1];
                    this.setBetween(from, to);
                    return this._currentPercent;
                }
                this._passLastFrame = true;
            } else
                this._passLastFrame = false;

            do {
                this._fromIndex = locToIndex;
                from = frames[this._fromIndex];
                locTotalDuration = from.frameID;

                locToIndex = this._fromIndex + 1;
                if (locToIndex >= length)
                    locToIndex = 0;
                to = frames[locToIndex];

                //! Guaranteed to trigger frame event
                if(from.strEvent && !this._animation.isIgnoreFrameEvent())
                    this._animation.frameEvent(this._bone, from.strEvent,from.frameID, playedTime);

                if (playedTime === from.frameID|| (this._passLastFrame && this._fromIndex === length-1))
                    break;
            } while  (playedTime < from.frameID || playedTime >= to.frameID);

            locBetweenDuration = to.frameID - from.frameID;
            this._frameTweenEasing = from.tweenEasing;
            this.setBetween(from, to, false);

            this._totalDuration = locTotalDuration;
            this._betweenDuration = locBetweenDuration;
            this._toIndex = locToIndex;
        }
        currentPercent = locBetweenDuration === 0 ? 0 : (playedTime - this._totalDuration) / this._betweenDuration;

        /*
         *  if frame tween easing equal to TWEEN_EASING_MAX, then it will not do tween.
         */
        var tweenType = (this._frameTweenEasing !== ccs.TweenType.LINEAR) ? this._frameTweenEasing : this._tweenEasing;
        if (tweenType !== ccs.TweenType.TWEEN_EASING_MAX && tweenType !== ccs.TweenType.LINEAR && !this._passLastFrame) {
            currentPercent = ccs.TweenFunction.tweenTo(currentPercent, tweenType, this._from.easingParams);
        }
        return currentPercent;
    },

    /**
     * Sets Armature animation to ccs.Tween.
     * @param {ccs.ArmatureAnimation} animation
     */
    setAnimation:function (animation) {
        this._animation = animation;
    },

    /**
     * Returns Armature animation of ccs.Tween.
     * @return {ccs.ArmatureAnimation}
     */
    getAnimation:function () {
        return this._animation;
    },

    /**
     * Sets movement bone data to ccs.Tween.
     * @param data
     */
    setMovementBoneData: function(data){
        this._movementBoneData = data;
    }
});

var _p = ccs.Tween.prototype;

// Extended properties
/** @expose */
_p.animation;
cc.defineGetterSetter(_p, "animation", _p.getAnimation, _p.setAnimation);

_p = null;

/**
 * Allocates and initializes a ArmatureAnimation.
 * @param {ccs.Bone} bone
 * @return {ccs.Tween}
 * @deprecated since v3.1, please use new construction instead
 */
ccs.Tween.create = function (bone) {
    return new ccs.Tween(bone);
};
