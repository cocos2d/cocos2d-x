/****************************************************************************
 Copyright (c) 2011-2012 cocos2d-x.org
 Copyright (c) 2013-2014 Chukong Technologies Inc.
 Copyright (c) 2014 Shengxiang Chen (Nero Chan)

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
 * @ignore
 */
sp._atlasPage_createTexture_webGL = function (self, path) {
    var texture = cc.textureCache.addImage(path);
    self.rendererObject = new cc.TextureAtlas(texture, 128);
    self.width = texture.getPixelsWide();
    self.height = texture.getPixelsHigh();
};

sp._atlasPage_createTexture_canvas = function(self, path) {
    self._texture = cc.textureCache.addImage(path);
};

sp._atlasPage_disposeTexture = function (self) {
    self.rendererObject.release();
};

sp._atlasLoader = {
    spAtlasFile:null,
    setAtlasFile:function(spAtlasFile){
        this.spAtlasFile = spAtlasFile;
    },
    load:function(page, line, spAtlas){
        var texturePath = cc.path.join(cc.path.dirname(this.spAtlasFile), line);
        if (cc._renderType === cc._RENDER_TYPE_WEBGL)
            sp._atlasPage_createTexture_webGL(page,texturePath);
        else
            sp._atlasPage_createTexture_canvas(page,texturePath);
    },
    unload:function(obj){
    }
};

/**
 * The event type of spine skeleton animation. It contains event types: START(0), END(1), COMPLETE(2), EVENT(3).
 * @constant
 * @type {{START: number, END: number, COMPLETE: number, EVENT: number}}
 */
sp.ANIMATION_EVENT_TYPE = {
    START: 0,
    END: 1,
    COMPLETE: 2,
    EVENT: 3
};

sp.TrackEntryListeners = function(startListener, endListener, completeListener, eventListener){
    this.startListener = startListener || null;
    this.endListener = endListener || null;
    this.completeListener = completeListener || null;
    this.eventListener = eventListener || null;
};

sp.TrackEntryListeners.getListeners = function(entry){
    if(!entry.rendererObject){
        entry.rendererObject = new sp.TrackEntryListeners();
        entry.listener = sp.trackEntryCallback;
    }
    return entry.rendererObject;
};

sp.trackEntryCallback = function(state, trackIndex, type, event, loopCount) {
    state.rendererObject.onTrackEntryEvent(trackIndex, type, event, loopCount);
};

/**
 * The skeleton animation of spine. It updates animation's state and skeleton's world transform.
 * @class
 * @extends sp.Skeleton
 * @example
 * var spineBoy = new sp.SkeletonAnimation('res/skeletons/spineboy.json', 'res/skeletons/spineboy.atlas');
 * this.addChild(spineBoy, 4);
 */
sp.SkeletonAnimation = sp.Skeleton.extend(/** @lends sp.SkeletonAnimation# */{
    _state: null,
    _target: null,
    _callback: null,

    _ownsAnimationStateData: false,
    _startListener: null,
    _endListener: null,
    _completeListener: null,
    _eventListener: null,

    /**
     * Initializes a sp.SkeletonAnimation. please do not call this function by yourself, you should pass the parameters to constructor to initialize it.
     * @override
     */
    init: function () {
        sp.Skeleton.prototype.init.call(this);
        this._ownsAnimationStateData = true;
        this.setAnimationStateData(new spine.AnimationStateData(this._skeleton.data));
    },

    /**
     * Sets animation state data to sp.SkeletonAnimation.
     * @param {spine.AnimationStateData} stateData
     */
    setAnimationStateData: function (stateData) {
        var state = new spine.AnimationState(stateData);
        state.rendererObject = this;
        state.onStart = this._onAnimationStateStart.bind(this);
        state.onComplete = this._onAnimationStateComplete.bind(this);
        state.onEnd = this._onAnimationStateEnd.bind(this);
        state.onEvent = this._onAnimationStateEvent.bind(this);
        this._state = state;
    },

    /**
     * Mix applies all keyframe values, interpolated for the specified time and mixed with the current values.  <br/>
     * @param {String} fromAnimation
     * @param {String} toAnimation
     * @param {Number} duration
     */
    setMix: function (fromAnimation, toAnimation, duration) {
        this._state.data.setMixByName(fromAnimation, toAnimation, duration);
    },

    /**
     * Sets event listener of sp.SkeletonAnimation.
     * @param {Object} target
     * @param {Function} callback
     */
    setAnimationListener: function (target, callback) {
        this._target = target;
        this._callback = callback;
    },

    /**
     * Set the current animation. Any queued animations are cleared.
     * @param {Number} trackIndex
     * @param {String} name
     * @param {Boolean} loop
     * @returns {spine.TrackEntry|null}
     */
    setAnimation: function (trackIndex, name, loop) {
        var animation = this._skeleton.data.findAnimation(name);
        if (!animation) {
            cc.log("Spine: Animation not found: " + name);
            return null;
        }
        return this._state.setAnimation(trackIndex, animation, loop);
    },

    /**
     * Adds an animation to be played delay seconds after the current or last queued animation.
     * @param {Number} trackIndex
     * @param {String} name
     * @param {Boolean} loop
     * @param {Number} [delay=0]
     * @returns {spine.TrackEntry|null}
     */
    addAnimation: function (trackIndex, name, loop, delay) {
        delay = delay == null ? 0 : delay;
        var animation = this._skeleton.data.findAnimation(name);
        if (!animation) {
            cc.log("Spine: Animation not found:" + name);
            return null;
        }
        return this._state.addAnimation(trackIndex, animation, loop, delay);
    },

    /**
     * Returns track entry by trackIndex.
     * @param trackIndex
     * @returns {spine.TrackEntry|null}
     */
    getCurrent: function (trackIndex) {
        return this._state.getCurrent(trackIndex);
    },

    /**
     * Clears all tracks of animation state.
     */
    clearTracks: function () {
        this._state.clearTracks();
    },

    /**
     * Clears track of animation state by trackIndex.
     * @param {Number} trackIndex
     */
    clearTrack: function (trackIndex) {
        this._state.clearTrack(trackIndex);
    },

    /**
     * Update will be called automatically every frame if "scheduleUpdate" is called when the node is "live".
     * It updates animation's state and skeleton's world transform.
     * @param {Number} dt Delta time since last update
     * @override
     */
    update: function (dt) {
        this._super(dt);
        dt *= this._timeScale;
        this._state.update(dt);
        this._state.apply(this._skeleton);
        this._skeleton.updateWorldTransform();
        this._renderCmd._updateChild();
    },

    /**
     * Set the start event listener.
     * @param {function} listener
     */
    setStartListener: function(listener){
        this._startListener = listener;
    },

    /**
     * Set the end event listener.
     * @param {function} listener
     */
    setEndListener: function(listener) {
        this._endListener = listener;
    },

    setCompleteListener: function(listener) {
        this._completeListener = listener;
    },

    setEventListener: function(listener){
        this._eventListener = listener;
    },

    setTrackStartListener: function(entry, listener){
        sp.TrackEntryListeners.getListeners(entry).startListener = listener;
    },

    setTrackEndListener: function(entry, listener){
        sp.TrackEntryListeners.getListeners(entry).endListener = listener;
    },

    setTrackCompleteListener: function(entry, listener){
        sp.TrackEntryListeners.getListeners(entry).completeListener = listener;
    },

    setTrackEventListener: function(entry, listener){
        sp.TrackEntryListeners.getListeners(entry).eventListener = listener;
    },

    onTrackEntryEvent: function(traceIndex, type, event, loopCount){
        var entry = this._state.getCurrent(traceIndex);
        if(!entry.rendererObject)
            return;
        var listeners = entry.rendererObject;
        switch (type){
            case sp.ANIMATION_EVENT_TYPE.START:
                if(listeners.startListener)
                    listeners.startListener(traceIndex);
                break;
            case sp.ANIMATION_EVENT_TYPE.END:
                if(listeners.endListener)
                    listeners.endListener(traceIndex);
                break;
            case sp.ANIMATION_EVENT_TYPE.COMPLETE:
                if(listeners.completeListener)
                    listeners.completeListener(traceIndex, loopCount);
                break;
            case sp.ANIMATION_EVENT_TYPE.EVENT:
                if(listeners.eventListener)
                    listeners.eventListener(traceIndex, event);
                break;
        }
    },

    onAnimationStateEvent: function(trackIndex, type, event, loopCount) {
        switch(type){
            case sp.ANIMATION_EVENT_TYPE.START:
                if(this._startListener)
                    this._startListener(trackIndex);
                break;
            case sp.ANIMATION_EVENT_TYPE.END:
                if(this._endListener)
                    this._endListener(trackIndex);
                break;
            case sp.ANIMATION_EVENT_TYPE.COMPLETE:
                if(this._completeListener)
                    this._completeListener(trackIndex, loopCount);
                break;
            case sp.ANIMATION_EVENT_TYPE.EVENT:
                if(this._eventListener)
                    this._eventListener(trackIndex, event);
                break;
        }
    },

    getState: function(){
        return this._state;
    },

    _onAnimationStateStart: function (trackIndex) {
        this._animationStateCallback(trackIndex, sp.ANIMATION_EVENT_TYPE.START, null, 0);
    },
    _onAnimationStateEnd: function (trackIndex) {
        this._animationStateCallback(trackIndex, sp.ANIMATION_EVENT_TYPE.END, null, 0);
    },
    _onAnimationStateComplete: function (trackIndex, count) {
        this._animationStateCallback(trackIndex, sp.ANIMATION_EVENT_TYPE.COMPLETE, null, count);
    },
    _onAnimationStateEvent: function (trackIndex, event) {
        this._animationStateCallback(trackIndex, sp.ANIMATION_EVENT_TYPE.EVENT, event, 0);
    },
    _animationStateCallback: function (trackIndex, type, event, loopCount) {
        this.onAnimationStateEvent(trackIndex, type, event, loopCount);
        if (this._target && this._callback) {
            this._callback.call(this._target, this, trackIndex, type, event, loopCount)
        }
    }
});

/**
 * Creates a skeleton animation object.
 * @deprecated since v3.0, please use new sp.SkeletonAnimation(skeletonDataFile, atlasFile, scale) instead.
 * @param {spine.SkeletonData|String} skeletonDataFile
 * @param {String|spine.Atlas|spine.SkeletonData} atlasFile atlas filename or atlas data or owns SkeletonData
 * @param {Number} [scale] scale can be specified on the JSON or binary loader which will scale the bone positions, image sizes, and animation translations.
 * @returns {sp.Skeleton}
 */
sp.SkeletonAnimation.create = function (skeletonDataFile, atlasFile/* or atlas*/, scale) {
    return new sp.SkeletonAnimation(skeletonDataFile, atlasFile, scale);
};