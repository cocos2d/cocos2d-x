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

//animation type
/**
 * The animation just have one frame
 * @constant
 * @type {number}
 */
ccs.ANIMATION_TYPE_SINGLE_FRAME = -4;
/**
 * The animation isn't loop
 * @constant
 * @type {number}
 */
ccs.ANIMATION_TYPE_NO_LOOP = -3;
/**
 * The animation to loop from front
 * @constant
 * @type {number}
 */
ccs.ANIMATION_TYPE_TO_LOOP_FRONT = -2;
/**
 * The animation to loop from back
 * @constant
 * @type {number}
 */
ccs.ANIMATION_TYPE_TO_LOOP_BACK = -1;
/**
 * The animation loop from front
 * @constant
 * @type {number}
 */
ccs.ANIMATION_TYPE_LOOP_FRONT = 0;
/**
 * The animation loop from back
 * @constant
 * @type {number}
 */
ccs.ANIMATION_TYPE_LOOP_BACK = 1;
/**
 * The animation max
 * @constant
 * @type {number}
 */
ccs.ANIMATION_TYPE_MAX = 2;

/**
 * The Base Process class for Cocostudio.
 * @class
 * @extends ccs.Class
 *
 * @property {Number}   currentFrameIndex   - <@readonly> The current frame's index
 * @property {Boolean}  paused              - <@readonly> Indicate whether the process is paused
 * @property {Boolean}  completed           - <@readonly> Indicate whether the process is done
 * @property {Number}   currentPercent      - <@readonly> The current percentage of the process
 * @property {Number}   rawDuration         - <@readonly> The duration
 * @property {Number}   loop                - <@readonly> The number of loop
 * @property {Number}   tweenEasing         - <@readonly> The tween easing
 * @property {Number}   animationInterval   - The animation internal
 * @property {Number}   processScale        - The process scale
 * @property {Boolean}  playing             - <@readonly> Indicate whether the process is playing
 */
ccs.ProcessBase = ccs.Class.extend(/** @lends ccs.ProcessBase# */{
    _processScale: 1,
    _isComplete: true,
    _isPause: true,
    _isPlaying: false,
    _currentPercent: 0.0,
    _rawDuration: 0,
    _loopType: 0,
    _tweenEasing: 0,
    animationInternal: null,
    _currentFrame: 0,
    _durationTween: 0,
    _nextFrameIndex: 0,
    _curFrameIndex: null,
    _isLoopBack: false,

    /**
     * Constructor of ccs.ProcessBase
     */
    ctor: function () {
        this._processScale = 1;
        this._isComplete = true;
        this._isPause = true;
        this._isPlaying = false;
        this._currentFrame = 0;
        this._currentPercent = 0.0;
        this._durationTween = 0;
        this._rawDuration = 0;
        this._loopType = ccs.ANIMATION_TYPE_LOOP_BACK;
        this._tweenEasing = ccs.TweenType.LINEAR;
        this.animationInternal = 1 / 60;
        this._curFrameIndex = 0;
        this._durationTween = 0;
        this._isLoopBack = false;
    },

    /**
     * Pauses the Process
     */
    pause: function () {
        this._isPause = true;
        this._isPlaying = false;
    },

    /**
     * Resumes the Process
     */
    resume: function () {
        this._isPause = false;
        this._isPlaying = true;
    },

    /**
     * Stops the Process
     */
    stop: function () {
        this._isComplete = true;
        this._isPlaying = false;
    },

    /**
     * Plays animation by animation name.
     * @param {Number} durationTo The frames between two animation changing-over.
     *         It's meaning is changing to this animation need how many frames
     *         -1 : use the value from MovementData get from flash design panel
     * @param {Number} durationTween  The frame count you want to play in the game.
     *         if  _durationTween is 80, then the animation will played 80 frames in a loop
     *         -1 : use the value from MovementData get from flash design panel
     * @param {Number} loop Whether the animation is loop
     *         loop < 0 : use the value from MovementData get from flash design panel
     *         loop = 0 : this animation is not loop
     *         loop > 0 : this animation is loop
     * @param {Number} tweenEasing  Tween easing is used for calculate easing effect
     *          TWEEN_EASING_MAX : use the value from MovementData get from flash design panel
     *          -1 : fade out
     *          0  : line
     *          1  : fade in
     *          2  : fade in and out
     */
    play: function (durationTo, durationTween, loop, tweenEasing) {
        this._isComplete = false;
        this._isPause = false;
        this._isPlaying = true;
        this._currentFrame = 0;
        /*
         *  Set m_iTotalFrames to durationTo, it is used for change tween between two animation.
         *  When changing end, m_iTotalFrames will be set to _durationTween
         */
        this._nextFrameIndex = durationTo;
        this._tweenEasing = tweenEasing;
    },

    /**
     * Update process' state.
     * @param {Number} dt
     */
    update: function (dt) {
        if (this._isComplete || this._isPause)
            return;

        /*
         *  Fileter the m_iDuration <=0 and dt >1
         *  If dt>1, generally speaking  the reason is the device is stuck.
         */
        if (this._rawDuration <= 0 || dt > 1)
            return;

        var locNextFrameIndex = this._nextFrameIndex === undefined ? 0 : this._nextFrameIndex;
        var locCurrentFrame = this._currentFrame;
        if (locNextFrameIndex <= 0) {
            this._currentPercent = 1;
            locCurrentFrame = 0;
        } else {
            /*
             *  update currentFrame, every update add the frame passed.
             *  dt/this.animationInternal determine it is not a frame animation. If frame speed changed, it will not make our
             *  animation speed slower or quicker.
             */
            locCurrentFrame += this._processScale * (dt / this.animationInternal);
            this._currentPercent = locCurrentFrame / locNextFrameIndex;

            /*
             *	if currentFrame is bigger or equal than this._nextFrameIndex, then reduce it util currentFrame is
             *  smaller than this._nextFrameIndex
             */
            locCurrentFrame = ccs.fmodf(locCurrentFrame, locNextFrameIndex);
        }
        this._currentFrame = locCurrentFrame;
        this.updateHandler();
    },

    /**
     * Goes to specified frame by frameIndex.
     * @param {Number} frameIndex
     */
    gotoFrame: function (frameIndex) {
        var locLoopType = this._loopType;
        if (locLoopType === ccs.ANIMATION_TYPE_NO_LOOP)
            locLoopType = ccs.ANIMATION_TYPE_MAX;
        else if (locLoopType === ccs.ANIMATION_TYPE_TO_LOOP_FRONT)
            locLoopType = ccs.ANIMATION_TYPE_LOOP_FRONT;
        this._loopType = locLoopType;
        this._curFrameIndex = frameIndex;
        this._nextFrameIndex = this._durationTween;
    },

    /**
     * Returns the index of current frame.
     * @return {Number}
     */
    getCurrentFrameIndex: function () {
        this._curFrameIndex = (this._rawDuration - 1) * this._currentPercent;
        return this._curFrameIndex;
    },

    /**
     * Updates will call this handler, you can handle your logic here
     */
    updateHandler: function () {
        //override
    },

    /**
     * Returns whether the animation is pause
     * @returns {boolean}
     */
    isPause: function () {
        return this._isPause;
    },

    /**
     * Returns whether the animation is complete
     * @returns {boolean}
     */
    isComplete: function () {
        return this._isComplete;
    },

    /**
     * Returns current percent of ccs.ProcessBase
     * @returns {number}
     */
    getCurrentPercent: function () {
        return this._currentPercent;
    },

    /**
     * Returns the raw duration of ccs.ProcessBase
     * @returns {number}
     */
    getRawDuration: function () {
        return this._rawDuration;
    },

    /**
     * Returns loop type of ccs.ProcessBase
     * @returns {number}
     */
    getLoop: function () {
        return this._loopType;
    },

    /**
     * Returns tween easing of ccs.ProcessBase
     * @returns {number}
     */
    getTweenEasing: function () {
        return this._tweenEasing;
    },

    /**
     * Returns animation interval of ccs.ProcessBase
     * @returns {number}
     */
    getAnimationInternal: function () {            //TODO rename getAnimationInternal to getAnimationInterval in v3.1
        return this.animationInternal;
    },

    /**
     * Sets animation interval to ccs.ProcessBase.
     * @param animationInternal
     */
    setAnimationInternal: function (animationInternal) {
        this.animationInternal = animationInternal;
    },

    /**
     * Returns process scale
     * @returns {number}
     */
    getProcessScale: function () {
        return this._processScale;
    },

    /**
     * Sets process scale
     * @param processScale
     */
    setProcessScale: function (processScale) {
        this._processScale = processScale;
    },

    /**
     * Returns whether the animation is playing
     * @returns {boolean}
     */
    isPlaying: function () {
        return this._isPlaying;
    }
});

var _p = ccs.ProcessBase.prototype;

// Extended properties
/** @expose */
_p.currentFrameIndex;
cc.defineGetterSetter(_p, "currentFrameIndex", _p.getCurrentFrameIndex);
/** @expose */
_p.paused;
cc.defineGetterSetter(_p, "paused", _p.isPause);
/** @expose */
_p.completed;
cc.defineGetterSetter(_p, "completed", _p.isComplete);
/** @expose */
_p.currentPercent;
cc.defineGetterSetter(_p, "currentPercent", _p.getCurrentPercent);
/** @expose */
_p.rawDuration;
cc.defineGetterSetter(_p, "rawDuration", _p.getRawDuration);
/** @expose */
_p.loop;
cc.defineGetterSetter(_p, "loop", _p.getLoop);
/** @expose */
_p.tweenEasing;
cc.defineGetterSetter(_p, "tweenEasing", _p.getTweenEasing);
/** @expose */
_p.playing;
cc.defineGetterSetter(_p, "playing", _p.isPlaying);

_p = null;
