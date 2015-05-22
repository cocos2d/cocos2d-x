/****************************************************************************
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
 * ActionTimelineData
 * @name ccs.ActionTimelineData
 * @extend ccs.Class
 * @class
 *
 */
ccs.ActionTimelineData = ccs.Class.extend({

    _actionTag: 0,

    ctor: function(actionTag){
        this._init(actionTag);
    },

    _init: function(actionTag){
        this._actionTag = actionTag;
        return true;
    },

    /**
     * Set the action tag.
     * @param {number} actionTag
     */
    setActionTag: function(actionTag){
        this._actionTag = actionTag;
    },

    /**
     * Gets the action tag.
     */
    getActionTag: function(){
        return this._actionTag;
    }

});

ccs.ObjectExtensionData = ccs.Class.extend({

    _customProperty: null,
    _timelineData: null,

    ctor: function(){
        this._timelineData = new ccs.ActionTimelineData(0);
        return true;
    },

    setActionTag: function(actionTag){
        this._timelineData.setActionTag(actionTag);
    },

    getActionTag: function(){
        return this._timelineData.getActionTag();
    }
});

ccs.ObjectExtensionData.create = function(){
    return new ccs.ObjectExtensionData();
};

/**
 * Create new ActionTimelineData.
 *
 * @deprecated v3.0, please use new ccs.ActionTimelineData() instead.
 *
 * @name ccs.ActionTimelineData.create
 * @function
 * @param actionTag
 * @returns {ccs.ActionTimelineData}
 */
ccs.ActionTimelineData.create = function(actionTag){
    return new ccs.ActionTimelineData(actionTag);
};


/**
 * ActionTimeline
 * @class
 * @extend cc.Action
 *
 * @property gotoFrameAndPlay
 * @property gotoFrameAndPause
 */
ccs.ActionTimeline = cc.Action.extend({

    _timelineMap: null,
    _timelineList: null,
    _duration: 0,
    _time: null,
    _timeSpeed: 1,
    _frameInternal: 1/60,
    _playing: false,
    _currentFrame: 0,
    _startFrame: 0,
    _endFrame: 0,
    _loop: null,
    _frameEventListener: null,
    _animationInfos: null,

    ctor: function(){
        cc.Action.prototype.ctor.call(this);
        this._timelineMap = {};
        this._timelineList = [];
        this._animationInfos = {};
        this.init();
    },

    _gotoFrame: function(frameIndex){
        var size = this._timelineList.length;
        for(var i = 0; i < size; i++)
        {
            this._timelineList[i]._gotoFrame(frameIndex);
        }
    },

    _stepToFrame: function(frameIndex){
        var size = this._timelineList.length;
        for(var i = 0; i < size; i++){
            this._timelineList[i]._stepToFrame(frameIndex);
        }
    },

    //emit frame event, call it when enter a frame
    _emitFrameEvent: function(frame){
        if(this._frameEventListener){
            this._frameEventListener(frame);
        }
    },

    init: function(){
        return true;
    },

    /**
     * Goto the specified frame index, and start playing from this index.
     * @param startIndex The animation will play from this index.
     * @param [endIndex=] The animation will end at this index.
     * @param [currentFrameIndex=] set current frame index.
     * @param [loop=] Whether or not the animation need loop.
     */
    gotoFrameAndPlay: function(startIndex, endIndex, currentFrameIndex, loop){
        //Consolidation parameters
        var i = 0,
            argLen = arguments.length;
        var num = [],
            bool;
        for(i; i<argLen; i++){
            if(typeof arguments[i] === "boolean"){
                bool = arguments[i];
            }else{
                num.push(arguments[i]);
            }
        }
        startIndex = num[0];
        endIndex = num[1] || this._duration;
        currentFrameIndex = num[2] || startIndex;
        loop = bool!=null ? bool : true;

        this._startFrame = startIndex;
        this._endFrame = endIndex;
        this._currentFrame = currentFrameIndex;
        this._loop = loop;
        this._time = this._currentFrame * this._frameInternal;

        this.resume();
        this._gotoFrame(this._currentFrame);
    },

    /**
     * Goto the specified frame index, and pause at this index.
     * @param startIndex The animation will pause at this index.
     */
    gotoFrameAndPause: function(startIndex){
        this._startFrame = this._currentFrame = startIndex;
        this._time       = this._currentFrame * this._frameInternal;

        this.pause();
        this._gotoFrame(this._currentFrame);
    },

    /**
     * Pause the animation.
     */
    pause: function(){
        this._playing = false;
    },

    /**
     * Resume the animation.
     */
    resume: function(){
        this._playing = true;
    },

    /**
     * Whether or not Action is playing.
     */
    isPlaying: function(){
        return this._playing;
    },

    /**
     * Set the animation speed, this will speed up or slow down the speed.
     * @param {number} speed
     */
    setTimeSpeed: function(speed){
        this._timeSpeed = speed;
    },

    /**
     * Get current animation speed.
     * @returns {number}
     */
    getTimeSpeed: function(){
        return this._timeSpeed;
    },

    /**
     * duration of the whole action
     * @param {number} duration
     */
    setDuration: function(duration){
        this._duration = duration;
    },

    /**
     * Get current animation duration.
     * @returns {number}
     */
    getDuration: function(){
        return this._duration;
    },

    /**
     * Start frame index of this action
     * @returns {number}
     */
    getStartFrame: function(){
        return this._startFrame;
    },

    /**
     * End frame of this action.
     * When action play to this frame, if action is not loop, then it will stop,
     * or it will play from start frame again.
     * @returns {number}
     */
    getEndFrame: function(){
        return this._endFrame;
    },

    /**
     * Set current frame index, this will cause action plays to this frame.
     */
    setCurrentFrame: function(frameIndex){
        if (frameIndex >= this._startFrame && frameIndex >= this._endFrame){
            this._currentFrame = frameIndex;
            this._time = this._currentFrame * this._frameInternal;
        }else{
            cc.log("frame index is not between start frame and end frame");
        }

    },

    /**
     * Get current frame.
     * @returns {number}
     */
    getCurrentFrame: function(){
        return this._currentFrame;
    },

    /**
     * add Timeline to ActionTimeline
     * @param {ccs.Timeline} timeline
     */
    addTimeline: function(timeline){
        var tag = timeline.getActionTag();
        if (!this._timelineMap[tag]) {
            this._timelineMap[tag] = [];
        }

        if (!this._timelineMap[tag].some(function(item){
            if(item === timeline)
                return true;
        })) {
            this._timelineList.push(timeline);
            this._timelineMap[tag].push(timeline);
            timeline.setActionTimeline(this);
        }

    },

    /**
     * remove Timeline to ActionTimeline
     * @param {ccs.Timeline} timeline
     */
    removeTimeline: function(timeline){
        var tag = timeline.getActionTag();
        if (this._timelineMap[tag]) {
            if(this._timelineMap[tag].some(function(item){
                if(item === timeline)
                    return true;
            })) {
                cc.arrayRemoveObject(this._timelineMap[tag], timeline);
                cc.arrayRemoveObject(this._timelineList, timeline);
                timeline.setActionTimeline(null);
            }
        }
    },

    /**
     * Gets the timeline list
     * @returns {array | null}
     */
    getTimelines: function(){
        return this._timelineList;
    },

    /**
     * Set the Frame event
     * @param {function} listener
     */
    setFrameEventCallFunc: function(listener){
        this._frameEventListener = listener;
    },

    /**
     * remove event
     */
    clearFrameEventCallFunc: function(){
        this._frameEventListener = null;
    },

    /**
     * Clone this timeline
     * @returns {ccs.ActionTimeline}
     */
    clone: function(){
        var newAction = new ccs.ActionTimeline();
        newAction.setDuration(this._duration);
        newAction.setTimeSpeed(this._timeSpeed);

        for (var a in this._timelineMap){
            var timelines = this._timelineMap[a];
            for(var b in timelines)
            {
                var timeline = timelines[b];
                var newTimeline = timeline.clone();
                newAction.addTimeline(newTimeline);
            }
        }

        return newAction;

    },

    /**
     * Reverse is not defined;
     * @returns {null}
     */
    reverse: function(){
        return null;
    },

    /**
     * Stepping of this time line.
     * @param {number} delta
     */
    step: function(delta){
        if (!this._playing || this._timelineMap.length === 0 || this._duration === 0)
        {
            return;
        }

        this._time += delta * this._timeSpeed;
        this._currentFrame = this._time / this._frameInternal | 0;

        this._stepToFrame(this._currentFrame);

        if(this._time > this._endFrame * this._frameInternal){
            this._playing = this._loop;
            if(!this._playing)
                this._time = this._endFrame * this._frameInternal;
            else
                this.gotoFrameAndPlay(this._startFrame, this._endFrame, this._loop);
        }

    },

    _foreachNodeDescendant: function(parent, callback){
        callback(parent);

        var children = parent.getChildren();
        for (var i=0; i<children.length; i++)
        {
            var child = children[i];
            this._foreachNodeDescendant(child, callback);
        }
    },

    /**
     * start with node.
     * @param {cc.Node} target
     */
    startWithTarget: function(target){
        cc.Action.prototype.startWithTarget.call(this, target);

        var self = this;
        var callback = function(child){
            var data = child.getUserObject();

            if(data) {
                var actionTag = data.getActionTag();
                if(self._timelineMap[actionTag]) {
                    var timelines = self._timelineMap[actionTag];
                    for (var i=0; i<timelines.length; i++) {
                        var timeline = timelines[i];
                        timeline.setNode(child);
                    }
                }
            }
        };

        this._foreachNodeDescendant(target, callback);
    },

    /**
     * Whether or not complete
     * @returns {boolean}
     */
    isDone: function(){
        return false;
    },

    /**
     * @param {String} name
     * @param {Boolean} loop
     */
    play: function(name, loop){
        var info = this._animationInfos[name];
        if (!info)
            return cc.log("Can't find animation info for %s", name);

        this.gotoFrameAndPlay(info.startIndex, info.endIndex, loop);
    },

    /**
     * Add animationInfo
     * @param {Object} info
     */
    addAnimationInfo: function(info){
        this._animationInfos[info.name] = info;
    },

    /**
     * Remove animationInfo
     * @param {String} name
     */
    removeAnimationInfo: function(name){
        delete this._animationInfos[name];
    },

    isAnimationInfoExists: function(name){
        return this._animationInfos[name];
    },

    getAnimationInfo: function(name){
        return this._animationInfos[name];
    }
});

/**
 * create new ActionTimeline
 *
 * @deprecated v3.0, please use new ccs.ActionTimeline() instead.
 *
 * @name ccs.ActionTimeline.create
 * @function
 * @returns {ccs.ActionTimeline}
 */
ccs.ActionTimeline.create = function(){
    return new ccs.ActionTimeline();
};
