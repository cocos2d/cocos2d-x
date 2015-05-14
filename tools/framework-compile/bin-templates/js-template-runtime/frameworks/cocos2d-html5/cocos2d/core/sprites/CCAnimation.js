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
 *    cc.AnimationFrame
 *    A frame of the animation. It contains information like:
 *       - sprite frame name
 *       - # of delay units.
 *       - offset
 * </p>
 * @class
 * @extends cc.Class
 * @param spriteFrame
 * @param delayUnits
 * @param userInfo
 * @returns {AnimationFrame}
 */
cc.AnimationFrame = cc.Class.extend(/** @lends cc.AnimationFrame# */{
    _spriteFrame:null,
    _delayPerUnit:0,
    _userInfo:null,

    ctor:function (spriteFrame, delayUnits, userInfo) {
        this._spriteFrame = spriteFrame || null;
        this._delayPerUnit = delayUnits || 0;
        this._userInfo = userInfo || null;
    },

    /**
     * Create a new animation frame and copy all contents into it
     * @returns {AnimationFrame}
     */
    clone: function(){
        var frame = new cc.AnimationFrame();
        frame.initWithSpriteFrame(this._spriteFrame.clone(), this._delayPerUnit, this._userInfo);
        return frame;
    },

    /**
     * Create a new animation frame and copy all contents into it
     * @returns {AnimationFrame}
     */
    copyWithZone:function (pZone) {
        return cc.clone(this);
    },

    /**
     * Create a new animation frame and copy all contents into it
     * @returns {AnimationFrame}
     */
    copy:function (pZone) {
        var newFrame = new cc.AnimationFrame();
        newFrame.initWithSpriteFrame(this._spriteFrame.clone(), this._delayPerUnit, this._userInfo);
        return newFrame;
    },

    /**
     * initializes the animation frame with a spriteframe, number of delay units and a notification user info
     * @param {cc.SpriteFrame} spriteFrame
     * @param {Number} delayUnits
     * @param {object} userInfo
     */
    initWithSpriteFrame:function (spriteFrame, delayUnits, userInfo) {
        this._spriteFrame = spriteFrame;
        this._delayPerUnit = delayUnits;
        this._userInfo = userInfo;

        return true;
    },

    /**
     * Returns sprite frame to be used
     * @return {cc.SpriteFrame}
     */
    getSpriteFrame:function () {
        return this._spriteFrame;
    },

    /**
     * Sets sprite frame to be used
     * @param {cc.SpriteFrame} spriteFrame
     */
    setSpriteFrame:function (spriteFrame) {
        this._spriteFrame = spriteFrame;
    },

    /**
     * Returns how many units of time the frame takes getter
     * @return {Number}
     */
    getDelayUnits:function () {
        return this._delayPerUnit;
    },

    /**
     * Sets how many units of time the frame takes setter
     * @param delayUnits
     */
    setDelayUnits:function (delayUnits) {
        this._delayPerUnit = delayUnits;
    },

    /**
     * Returns the user custom information
     * @return {object}
     */
    getUserInfo:function () {
        return this._userInfo;
    },

    /**
     * Sets the user custom information
     * @param {object} userInfo
     */
    setUserInfo:function (userInfo) {
        this._userInfo = userInfo;
    }
});

/**
 * Creates an animation frame.
 * @deprecated since v3.0, please use the new construction instead
 * @param {cc.SpriteFrame} spriteFrame
 * @param {Number} delayUnits
 * @param {object} userInfo
 * @see cc.AnimationFrame
 */
cc.AnimationFrame.create = function(spriteFrame,delayUnits,userInfo){
    return new cc.AnimationFrame(spriteFrame,delayUnits,userInfo);
};

/**
 * <p>
 *     A cc.Animation object is used to perform animations on the cc.Sprite objects.<br/>
 *     <br/>
 *      The cc.Animation object contains cc.SpriteFrame objects, and a possible delay between the frames. <br/>
 *      You can animate a cc.Animation object by using the cc.Animate action.
 * </p>
 * @class
 * @extends cc.Class
 * @param {Array} frames
 * @param {Number} delay
 * @param {Number} [loops=1]
 *
 * @example
 * // 1. Creates an empty animation
 * var animation1 = new cc.Animation();
 *
 * // 2. Create an animation with sprite frames, delay and loops.
 * var spriteFrames = [];
 * var frame = cc.spriteFrameCache.getSpriteFrame("grossini_dance_01.png");
 * spriteFrames.push(frame);
 * var animation1 = new cc.Animation(spriteFrames);
 * var animation2 = new cc.Animation(spriteFrames, 0.2);
 * var animation2 = new cc.Animation(spriteFrames, 0.2, 2);
 *
 * // 3. Create an animation with animation frames, delay and loops.
 * var animationFrames = [];
 * var frame =  new cc.AnimationFrame();
 * animationFrames.push(frame);
 * var animation1 = new cc.Animation(animationFrames);
 * var animation2 = new cc.Animation(animationFrames, 0.2);
 * var animation3 = new cc.Animation(animationFrames, 0.2, 2);
 *
 * //create an animate with this animation
 * var action = cc.animate(animation1);
 *
 * //run animate
 * sprite.runAction(action);
 */
cc.Animation = cc.Class.extend(/** @lends cc.Animation# */{
    _frames:null,
    _loops:0,
    _restoreOriginalFrame:false,
    _duration:0,
    _delayPerUnit:0,
    _totalDelayUnits:0,

    ctor:function (frames, delay, loops) {
        this._frames = [];

		if (frames === undefined) {
			this.initWithSpriteFrames(null, 0);
		} else {
			var frame0 = frames[0];
			if(frame0){
				if (frame0 instanceof cc.SpriteFrame) {
					//init with sprite frames , delay and loops.
					this.initWithSpriteFrames(frames, delay, loops);
				}else if(frame0 instanceof cc.AnimationFrame) {
					//init with sprite frames , delay and loops.
					this.initWithAnimationFrames(frames, delay, loops);
				}
			}
		}
    },

    // attributes

    /**
     * Returns the array of animation frames
     * @return {Array}
     */
    getFrames:function () {
        return this._frames;
    },

    /**
     * Sets array of animation frames
     * @param {Array} frames
     */
    setFrames:function (frames) {
        this._frames = frames;
    },

    /**
     * Adds a frame to a cc.Animation, the frame will be added with one "delay unit".
     * @param {cc.SpriteFrame} frame
     */
    addSpriteFrame:function (frame) {
        var animFrame = new cc.AnimationFrame();

        animFrame.initWithSpriteFrame(frame, 1, null);
        this._frames.push(animFrame);
        // update duration
        this._totalDelayUnits++;
    },

    /**
     * Adds a frame with an image filename. Internally it will create a cc.SpriteFrame and it will add it. The frame will be added with one "delay unit".
     * @param {String} fileName
     */
    addSpriteFrameWithFile:function (fileName) {
        var texture = cc.textureCache.addImage(fileName);
        var rect = cc.rect(0, 0, 0, 0);
        rect.width = texture.width;
        rect.height = texture.height;
        var frame = new cc.SpriteFrame(texture, rect);
        this.addSpriteFrame(frame);
    },

    /**
     * Adds a frame with a texture and a rect. Internally it will create a cc.SpriteFrame and it will add it. The frame will be added with one "delay unit".
     * @param {cc.Texture2D} texture
     * @param {cc.Rect} rect
     */
    addSpriteFrameWithTexture:function (texture, rect) {
        var pFrame = new cc.SpriteFrame(texture, rect);
        this.addSpriteFrame(pFrame);
    },

    /**
     * Initializes a cc.Animation with cc.AnimationFrame, do not call this method yourself, please pass parameters to constructor to initialize.
     * @param {Array} arrayOfAnimationFrames
     * @param {Number} delayPerUnit
     * @param {Number} [loops=1]
     */
    initWithAnimationFrames:function (arrayOfAnimationFrames, delayPerUnit, loops) {
        cc.arrayVerifyType(arrayOfAnimationFrames, cc.AnimationFrame);

        this._delayPerUnit = delayPerUnit;
        this._loops = loops === undefined ? 1 : loops;
        this._totalDelayUnits = 0;

        var locFrames = this._frames;
        locFrames.length = 0;
        for (var i = 0; i < arrayOfAnimationFrames.length; i++) {
            var animFrame = arrayOfAnimationFrames[i];
            locFrames.push(animFrame);
            this._totalDelayUnits += animFrame.getDelayUnits();
        }

        return true;
    },

    /**
     * Clone the current animation
     * @return {cc.Animation}
     */
    clone: function(){
        var animation = new cc.Animation();
        animation.initWithAnimationFrames(this._copyFrames(), this._delayPerUnit, this._loops);
        animation.setRestoreOriginalFrame(this._restoreOriginalFrame);
        return animation;
    },

    /**
     * Clone the current animation
     * @return {cc.Animation}
     */
    copyWithZone:function (pZone) {
        var pCopy = new cc.Animation();
        pCopy.initWithAnimationFrames(this._copyFrames(), this._delayPerUnit, this._loops);
        pCopy.setRestoreOriginalFrame(this._restoreOriginalFrame);
        return pCopy;
    },

    _copyFrames:function(){
       var copyFrames = [];
        for(var i = 0; i< this._frames.length;i++)
            copyFrames.push(this._frames[i].clone());
        return copyFrames;
    },

    /**
     * Clone the current animation
     * @param pZone
     * @returns {cc.Animation}
     */
    copy:function (pZone) {
        return this.copyWithZone(null);
    },

    /**
     * Returns how many times the animation is going to loop. 0 means animation is not animated. 1, animation is executed one time, ...
     * @return {Number}
     */
    getLoops:function () {
        return this._loops;
    },

    /**
     * Sets how many times the animation is going to loop. 0 means animation is not animated. 1, animation is executed one time, ...
     * @param {Number} value
     */
    setLoops:function (value) {
        this._loops = value;
    },

    /**
     * Sets whether or not it shall restore the original frame when the animation finishes
     * @param {Boolean} restOrigFrame
     */
    setRestoreOriginalFrame:function (restOrigFrame) {
        this._restoreOriginalFrame = restOrigFrame;
    },

    /**
     * Returns whether or not it shall restore the original frame when the animation finishes
     * @return {Boolean}
     */
    getRestoreOriginalFrame:function () {
        return this._restoreOriginalFrame;
    },

    /**
     * Returns duration in seconds of the whole animation. It is the result of totalDelayUnits * delayPerUnit
     * @return {Number}
     */
    getDuration:function () {
        return this._totalDelayUnits * this._delayPerUnit;
    },

    /**
     * Returns delay in seconds of the "delay unit"
     * @return {Number}
     */
    getDelayPerUnit:function () {
        return this._delayPerUnit;
    },

    /**
     * Sets delay in seconds of the "delay unit"
     * @param {Number} delayPerUnit
     */
    setDelayPerUnit:function (delayPerUnit) {
        this._delayPerUnit = delayPerUnit;
    },

    /**
     * Returns total delay units of the cc.Animation.
     * @return {Number}
     */
    getTotalDelayUnits:function () {
        return this._totalDelayUnits;
    },

    /**
     * Initializes a cc.Animation with frames and a delay between frames, do not call this method yourself, please pass parameters to constructor to initialize.
     * @param {Array} frames
     * @param {Number} delay
     * @param {Number} [loops=1]
     */
    initWithSpriteFrames:function (frames, delay, loops) {
        cc.arrayVerifyType(frames, cc.SpriteFrame);
        this._loops = loops === undefined ? 1 : loops;
        this._delayPerUnit = delay || 0;
        this._totalDelayUnits = 0;

        var locFrames = this._frames;
        locFrames.length = 0;
        if (frames) {
            for (var i = 0; i < frames.length; i++) {
                var frame = frames[i];
                var animFrame = new cc.AnimationFrame();
                animFrame.initWithSpriteFrame(frame, 1, null);
                locFrames.push(animFrame);
            }
            this._totalDelayUnits += frames.length;
        }
        return true;
    },
    /**
     * <p>Currently JavaScript Bindings (JSB), in some cases, needs to use retain and release. This is a bug in JSB,
     * and the ugly workaround is to use retain/release. So, these 2 methods were added to be compatible with JSB.
     * This is a hack, and should be removed once JSB fixes the retain/release bug<br/>
     * You will need to retain an object if you created an engine object and haven't added it into the scene graph during the same frame.<br/>
     * Otherwise, JSB's native autorelease pool will consider this object a useless one and release it directly,<br/>
     * when you want to use it later, a "Invalid Native Object" error will be raised.<br/>
     * The retain function can increase a reference count for the native object to avoid it being released,<br/>
     * you need to manually invoke release function when you think this object is no longer needed, otherwise, there will be memory learks.<br/>
     * retain and release function call should be paired in developer's game code.</p>
     * @function
     * @see cc.Animation#release
     */
    retain:function () {
    },
    /**
     * <p>Currently JavaScript Bindings (JSB), in some cases, needs to use retain and release. This is a bug in JSB,
     * and the ugly workaround is to use retain/release. So, these 2 methods were added to be compatible with JSB.
     * This is a hack, and should be removed once JSB fixes the retain/release bug<br/>
     * You will need to retain an object if you created an engine object and haven't added it into the scene graph during the same frame.<br/>
     * Otherwise, JSB's native autorelease pool will consider this object a useless one and release it directly,<br/>
     * when you want to use it later, a "Invalid Native Object" error will be raised.<br/>
     * The retain function can increase a reference count for the native object to avoid it being released,<br/>
     * you need to manually invoke release function when you think this object is no longer needed, otherwise, there will be memory learks.<br/>
     * retain and release function call should be paired in developer's game code.</p>
     * @function
     * @see cc.Animation#retain
     */
    release:function () {
    }
});

/**
 * Creates an animation.
 * @deprecated since v3.0, please use new construction instead
 * @see cc.Animation
 * @param {Array} frames
 * @param {Number} delay
 * @param {Number} [loops=1]
 * @return {cc.Animation}
 */
cc.Animation.create = function (frames, delay, loops) {
    return new cc.Animation(frames, delay, loops);
};

/**
 * @deprecated since v3.0, please use new construction instead
 * @see cc.Animation
 * @type {Function}
 */
cc.Animation.createWithAnimationFrames = cc.Animation.create;