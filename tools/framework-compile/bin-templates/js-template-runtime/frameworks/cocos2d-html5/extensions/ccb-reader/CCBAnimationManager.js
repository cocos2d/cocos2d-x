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

cc.BuilderAnimationManagerDelegate = cc.Class.extend({
    completedAnimationSequenceNamed:function (name) {}
});

cc.BuilderAnimationManager = cc.Class.extend({
    _sequences:null,
    _nodeSequences:null,
    _baseValues:null,
    _autoPlaySequenceId:0,

    _rootNode:null,
    _owner:null,
    _rootContainerSize:null,

    _delegate:null,
    _runningSequence:null,

    _documentOutletNames:null,
    _documentOutletNodes:null,
    _documentCallbackNames:null,
    _documentCallbackNodes:null,
    _documentCallbackControlEvents:null,
    _documentControllerName:"",
    _lastCompletedSequenceName:"",
    _keyframeCallbacks:null,
    _keyframeCallFuncs:null,

    _animationCompleteCallbackFunc:null,
    _target:null,
    _jsControlled:false,

    ctor:function () {
        this._rootContainerSize = cc.size(0, 0);
        this.init();
    },

    init:function () {
        this._sequences = [];
        this._nodeSequences = new cc._Dictionary();
        this._baseValues = new cc._Dictionary();

        this._documentOutletNames = [];
        this._documentOutletNodes = [];
        this._documentCallbackNames = [];
        this._documentCallbackNodes = [];
        this._documentCallbackControlEvents = [];

        this._keyframeCallbacks = [];
        this._keyframeCallFuncs = {};

        return true;
    },

    getSequences:function () {
        return this._sequences;
    },

    setSequences:function(seqs){
        this._sequences = seqs;
    },

    getAutoPlaySequenceId:function () {
        return this._autoPlaySequenceId;
    },
    setAutoPlaySequenceId:function (autoPlaySequenceId) {
        this._autoPlaySequenceId = autoPlaySequenceId;
    },

    getRootNode:function () {
        return this._rootNode;
    },
    setRootNode:function (rootNode) {
        this._rootNode = rootNode;
    },

    getOwner:function () {
        return this._owner;
    },
    setOwner:function (owner) {
        this._owner = owner;
    },

    addDocumentCallbackNode:function(node){
        this._documentCallbackNodes.push(node);
    },

    addDocumentCallbackName:function(name){
        this._documentCallbackNames.push(name);
    },

    addDocumentCallbackControlEvents:function(controlEvents){
        this._documentCallbackControlEvents.push(controlEvents);
    },

    addDocumentOutletNode:function(node){
        this._documentOutletNodes.push(node);
    },

    addDocumentOutletName:function(name){
        this._documentOutletNames.push(name);
    },

    setDocumentControllerName:function(name){
        this._documentControllerName = name;
    },

    getDocumentControllerName:function(){
        return this._documentControllerName;
    },

    getDocumentCallbackNames:function(){
        return this._documentCallbackNames;
    },

    getDocumentCallbackNodes:function(){
        return this._documentCallbackNodes;
    },

    getDocumentCallbackControlEvents:function(){
        return this._documentCallbackControlEvents;
    },

    getDocumentOutletNames:function(){
        return this._documentOutletNames;
    },

    getDocumentOutletNodes:function(){
        return this._documentOutletNodes;
    },

    getLastCompletedSequenceName:function(){
        return this._lastCompletedSequenceName;
    },

    getKeyframeCallbacks:function(){
        return this._keyframeCallbacks;
    },

    getRootContainerSize:function () {
        return this._rootContainerSize;
    },
    setRootContainerSize:function (rootContainerSize) {
        this._rootContainerSize = cc.size(rootContainerSize.width, rootContainerSize.height);
    },

    getDelegate:function () {
        return this._delegate;
    },
    setDelegate:function (delegate) {
        this._delegate = delegate;
    },

    getRunningSequenceName:function () {
        if(this._runningSequence)
            return this._runningSequence.getName();
        return null;
    },

    getContainerSize:function (node) {
        if (node)
            return node.getContentSize();
        else
            return this._rootContainerSize;
    },

    addNode:function (node, seq) {
        this._nodeSequences.setObject(seq, node);
    },
    setBaseValue:function (value, node, propName) {
        var props = this._baseValues.objectForKey(node);
        if (!props) {
            props = new cc._Dictionary();
            this._baseValues.setObject(props, node);
        }
        props.setObject(value, propName);
    },

    moveAnimationsFromNode:function(fromNode,toNode){
        // Move base values
        var locBaseValues = this._baseValues;
        var baseValue = locBaseValues.objectForKey(fromNode);
        if(baseValue !== null) {
            locBaseValues.setObject(baseValue, toNode);
            locBaseValues.removeObjectForKey(fromNode);
        }

        // Move seqs
        var locNodeSequences = this._nodeSequences;
        var seqs = locNodeSequences.objectForKey(fromNode);
        if(seqs != null) {
            locNodeSequences.setObject(seqs, toNode);
            locNodeSequences.removeObjectForKey(fromNode);
        }
    },

    getActionForCallbackChannel:function(channel) {
        var lastKeyframeTime = 0;

        var actions = [];
        var keyframes = channel.getKeyframes();
        var numKeyframes = keyframes.length;

        for (var i = 0; i < numKeyframes; ++i) {
            var keyframe = keyframes[i];
            var timeSinceLastKeyframe = keyframe.getTime() - lastKeyframeTime;
            lastKeyframeTime = keyframe.getTime();
            if(timeSinceLastKeyframe > 0) {
                actions.push(cc.delayTime(timeSinceLastKeyframe));
            }

            var keyVal = keyframe.getValue();
            var selectorName = keyVal[0];
            var selectorTarget = keyVal[1];

            if(this._jsControlled) {
                var callbackName = selectorTarget + ":" + selectorName;    //add number to the stream
                var callback = this._keyframeCallFuncs[callbackName];

                if(callback != null)
                    actions.push(callback);
            } else {
                var target;
                if(selectorTarget === CCB_TARGETTYPE_DOCUMENTROOT)
                    target = this._rootNode;
                else if (selectorTarget === CCB_TARGETTYPE_OWNER)
                    target = this._owner;

                if(target != null) {
                    if(selectorName.length > 0) {
                        var selCallFunc = 0;

                        if(target.onResolveCCBCCCallFuncSelector != null)
                            selCallFunc = target.onResolveCCBCCCallFuncSelector(target, selectorName);
                        if(selCallFunc === 0)
                            cc.log("Skipping selector '" + selectorName + "' since no CCBSelectorResolver is present.");
                        else
                            actions.push(cc.callFunc(selCallFunc,target));
                    } else {
                        cc.log("Unexpected empty selector.");
                    }
                }
            }
        }
        if(actions.length < 1)
            return null;

        return cc.sequence(actions);
    },
    getActionForSoundChannel:function(channel) {
        var lastKeyframeTime = 0;

        var actions = [];
        var keyframes = channel.getKeyframes();
        var numKeyframes = keyframes.length;

        for (var i = 0; i < numKeyframes; ++i) {
            var keyframe = keyframes[i];
            var timeSinceLastKeyframe = keyframe.getTime() - lastKeyframeTime;
            lastKeyframeTime = keyframe.getTime();
            if(timeSinceLastKeyframe > 0) {
                actions.push(cc.delayTime(timeSinceLastKeyframe));
            }

            var keyVal = keyframe.getValue();
            var soundFile = cc.BuilderReader.getResourcePath() + keyVal[0];
            var pitch = parseFloat(keyVal[1]), pan = parseFloat(keyVal[2]), gain = parseFloat(keyVal[3]);
            actions.push(cc.BuilderSoundEffect.create(soundFile, pitch, pan, gain));
        }

        if(actions.length < 1)
            return null;

        return cc.sequence(actions);
    },

    runAnimationsForSequenceNamed:function(name){
        this.runAnimationsForSequenceIdTweenDuration(this._getSequenceId(name), 0);
    },

    runAnimationsForSequenceNamedTweenDuration:function(name, tweenDuration){
         this.runAnimationsForSequenceIdTweenDuration(this._getSequenceId(name), tweenDuration);
    },

    runAnimationsForSequenceIdTweenDuration:function(nSeqId, tweenDuration){
        if(nSeqId === -1)
            throw "cc.BuilderAnimationManager.runAnimationsForSequenceIdTweenDuration(): Sequence id should not be -1";
        tweenDuration = tweenDuration || 0;

        this._rootNode.stopAllActions();

        var allKeys = this._nodeSequences.allKeys();
        for(var i  = 0,len = allKeys.length  ; i< len;i++){
            var node = allKeys[i];
            node.stopAllActions();

            var seqs = this._nodeSequences.objectForKey(node);
            var seqNodeProps = seqs.objectForKey(nSeqId);
            var j;
            var seqNodePropNames = [];
            if(seqNodeProps){
                var propKeys = seqNodeProps.allKeys();
                for(j = 0; j < propKeys.length; j++){
                    var propName = propKeys[j];
                    var seqProp = seqNodeProps.objectForKey(propName);
                    seqNodePropNames.push(propName);

                    this._setFirstFrame(node, seqProp,tweenDuration);
                    this._runAction(node,seqProp,tweenDuration);
                }
            }

            var nodeBaseValues = this._baseValues.objectForKey(node);
            if(nodeBaseValues){
                var baseKeys = nodeBaseValues.allKeys();
                for(j = 0; j < baseKeys.length;j++){
                    var selBaseKey =  baseKeys[j];
                    if(seqNodePropNames.indexOf(selBaseKey) === -1){
                        var value = nodeBaseValues.objectForKey(selBaseKey);
                        if(value != null)
                            this._setAnimatedProperty(selBaseKey,node, value, tweenDuration);
                    }
                }
            }
        }

        // Make callback at end of sequence
        var seq = this._getSequence(nSeqId);
        var completeAction = cc.sequence(cc.delayTime(seq.getDuration() + tweenDuration),
            cc.callFunc(this._sequenceCompleted,this));
        this._rootNode.runAction(completeAction);

        // Playback callbacks and sounds
        var action;
        if (seq.getCallbackChannel()) {
            // Build sound actions for channel
            action = this.getActionForCallbackChannel(seq.getCallbackChannel());
            if (action) {
                this._rootNode.runAction(action);
            }
        }

        if (seq.getSoundChannel()) {
            // Build sound actions for channel
            action = this.getActionForSoundChannel(seq.getSoundChannel());
            if (action) {
                this._rootNode.runAction(action);
            }
        }
        // Set the running scene
        this._runningSequence = this._getSequence(nSeqId);
    },

    runAnimations:function (name, tweenDuration) {
        tweenDuration = tweenDuration || 0;
        var nSeqId;
        if(cc.isString(name))
            nSeqId = this._getSequenceId(name);
        else
            nSeqId = name;

        this.runAnimationsForSequenceIdTweenDuration(nSeqId, tweenDuration);
    },

    setAnimationCompletedCallback:function(target,callbackFunc){
        this._target = target;
        this._animationCompleteCallbackFunc = callbackFunc;
    },

    setCompletedAnimationCallback:function(target,callbackFunc){
        this.setAnimationCompletedCallback(target,callbackFunc);
    },
    setCallFunc:function(callFunc, callbackNamed) {
        this._keyframeCallFuncs[callbackNamed] = callFunc;
    },

    debug:function () {
    },

    _getBaseValue:function (node, propName) {
        var props = this._baseValues.objectForKey(node);
        if (props)
            return props.objectForKey(propName);
        return null;
    },

    _getSequenceId:function (sequenceName) {
        var element = null;
        var locSequences = this._sequences;
        for (var i = 0, len = locSequences.length; i < len; i++) {
            element = locSequences[i];
            if (element && element.getName() === sequenceName)
                return element.getSequenceId();
        }
        return -1;
    },

    _getSequence:function (sequenceId) {
        var element = null;
        var locSequences = this._sequences;
        for (var i = 0, len = locSequences.length; i < len; i++) {
            element = locSequences[i];
            if (element && element.getSequenceId() === sequenceId)
                return element;
        }
        return null;
    },

    _getAction:function (keyframe0, keyframe1, propName, node) {
        var duration = keyframe1.getTime() - (keyframe0 ? keyframe0.getTime() : 0);
        var getArr,type,getValueArr, x, y;

        if (propName === "rotation") {
            return cc.BuilderRotateTo.create(duration, keyframe1.getValue());
        } else if (propName === "rotationX") {
            return cc.BuilderRotateXTo.create(duration, keyframe1.getValue());
        } else if (propName === "rotationY") {
            return cc.BuilderRotateYTo.create(duration, keyframe1.getValue());
        } else if (propName === "opacity") {
            return cc.fadeTo(duration, keyframe1.getValue());
        } else if (propName === "color") {
            var selColor = keyframe1.getValue().getColor();
            return cc.tintTo(duration, selColor.r, selColor.g, selColor.b);
        } else if (propName === "visible") {
            var isVisible = keyframe1.getValue();
            if (isVisible) {
                return cc.sequence(cc.delayTime(duration), cc.show());
            } else {
                return cc.sequence(cc.delayTime(duration), cc.hide());
            }
        } else if (propName === "displayFrame") {
            return cc.sequence(cc.delayTime(duration), cc.BuilderSetSpriteFrame.create(keyframe1.getValue()));
        } else if(propName === "position"){
            getArr = this._getBaseValue(node,propName);
            type = getArr[2];

            //get relative position
            getValueArr = keyframe1.getValue();
            x = getValueArr[0];
            y = getValueArr[1];

            var containerSize = this.getContainerSize(node.getParent());

            var absPos = cc._getAbsolutePosition(x,y, type,containerSize,propName);

            return cc.moveTo(duration,absPos);
        } else if( propName === "scale"){
            getArr = this._getBaseValue(node,propName);
            type = getArr[2];

            //get relative position
            getValueArr = keyframe1.getValue();
            x = getValueArr[0];
            y = getValueArr[1];

            if(type === CCB_SCALETYPE_MULTIPLY_RESOLUTION){
                //TODO need to test
                var resolutionScale = cc.BuilderReader.getResolutionScale();
                x *= resolutionScale;
                y *= resolutionScale;
            }

            return cc.scaleTo(duration,x,y);
        } else if( propName === "skew") {
            //get relative position
            getValueArr = keyframe1.getValue();
            x = getValueArr[0];
            y = getValueArr[1];
            return cc.skewTo(duration,x,y);
        } else {
            cc.log("BuilderReader: Failed to create animation for property: " + propName);
        }
        return null;
    },

    _setAnimatedProperty:function (propName, node, value, tweenDuration) {
        if(tweenDuration > 0){
            // Create a fake keyframe to generate the action from
            var kf1 = new cc.BuilderKeyframe();
            kf1.setValue(value);
            kf1.setTime(tweenDuration);
            kf1.setEasingType(CCB_KEYFRAME_EASING_LINEAR);

            // Animate
            var tweenAction = this._getAction(null, kf1, propName, node);
            node.runAction(tweenAction);
        } else {
            // Just set the value
            var getArr, nType, x,y;
            if(propName === "position"){
                getArr = this._getBaseValue(node,propName);
                nType = getArr[2];

                x = value[0];
                y = value[1];
                node.setPosition(cc._getAbsolutePosition(x,y,nType, this.getContainerSize(node.getParent()),propName));
            }else if(propName === "scale"){
                getArr = this._getBaseValue(node,propName);
                nType = getArr[2];

                x = value[0];
                y = value[1];

                cc.setRelativeScale(node,x,y,nType,propName);
            } else if( propName === "skew") {
                x = value[0];
                y = value[1];
                node.setSkewX(x);
                node.setSkewY(y);
            }else {
                // [node setValue:value forKey:name];
                // TODO only handle rotation, opacity, displayFrame, color
                if(propName === "rotation"){
                    node.setRotation(value);
                }  else if(propName === "rotationX")
                {
                    node.setRotationSkewX(value);
                }else if(propName === "rotationY")
                {
                    node.setRotationSkewY(value);
                }else if(propName === "opacity"){
                    node.setOpacity(value);
                } else if(propName === "displayFrame"){
                    node.setSpriteFrame(value);
                } else if(propName === "color"){
                    var ccColor3B = value.getColor();
                    if(ccColor3B.r !== 255 || ccColor3B.g !== 255 || ccColor3B.b !== 255){
                        node.setColor(ccColor3B);
                    }
                } else if( propName === "visible"){
                    value = value || false;
                    node.setVisible(value);
                } else {
                    cc.log("unsupported property name is "+ propName);
                }
            }
        }
    },

    _setFirstFrame:function (node, seqProp, tweenDuration) {
        var keyframes = seqProp.getKeyframes();

        if (keyframes.length === 0) {
            // Use base value (no animation)
            var baseValue = this._getBaseValue(node, seqProp.getName());
            if(!baseValue)
                cc.log("cc.BuilderAnimationManager._setFirstFrame(): No baseValue found for property");
            this._setAnimatedProperty(seqProp.getName(), node, baseValue, tweenDuration);
        } else {
            // Use first keyframe
            var keyframe = keyframes[0];
            this._setAnimatedProperty(seqProp.getName(), node, keyframe.getValue(), tweenDuration);
        }
    },

    _getEaseAction:function (action, easingType, easingOpt) {
        if (easingType === CCB_KEYFRAME_EASING_LINEAR || easingType === CCB_KEYFRAME_EASING_INSTANT ) {
            return action;
        } else if (easingType === CCB_KEYFRAME_EASING_CUBIC_IN) {
            return action.easing(cc.easeIn(easingOpt));
        } else if (easingType === CCB_KEYFRAME_EASING_CUBIC_OUT) {
            return action.easing(cc.easeOut(easingOpt));
        } else if (easingType === CCB_KEYFRAME_EASING_CUBIC_INOUT) {
            return action.easing(cc.easeInOut(easingOpt));
        } else if (easingType === CCB_KEYFRAME_EASING_BACK_IN) {
            return action.easing(cc.easeBackIn());
        } else if (easingType === CCB_KEYFRAME_EASING_BACK_OUT) {
            return action.easing(cc.easeBackOut());
        } else if (easingType === CCB_KEYFRAME_EASING_BACK_INOUT) {
            return action.easing(cc.easeBackInOut());
        } else if (easingType === CCB_KEYFRAME_EASING_BOUNCE_IN) {
            return action.easing(cc.easeBounceIn());
        } else if (easingType === CCB_KEYFRAME_EASING_BOUNCE_OUT) {
            return action.easing(cc.easeBounceOut());
        } else if (easingType === CCB_KEYFRAME_EASING_BOUNCE_INOUT) {
            return action.easing(cc.easeBounceInOut());
        } else if (easingType === CCB_KEYFRAME_EASING_ELASTIC_IN) {
            return action.easing(cc.easeElasticIn(easingOpt));
        } else if (easingType === CCB_KEYFRAME_EASING_ELASTIC_OUT) {
            return action.easing(cc.easeElasticOut(easingOpt));
        } else if (easingType === CCB_KEYFRAME_EASING_ELASTIC_INOUT) {
            return action.easing(cc.easeElasticInOut(easingOpt));
        } else {
            cc.log("BuilderReader: Unkown easing type " + easingType);
            return action;
        }
    },

    _runAction:function (node, seqProp, tweenDuration) {
        var keyframes = seqProp.getKeyframes();
        var numKeyframes = keyframes.length;

        if (numKeyframes > 1) {
            // Make an animation!
            var actions = [];

            var keyframeFirst = keyframes[0];
            var timeFirst = keyframeFirst.getTime() + tweenDuration;

            if (timeFirst > 0) {
                actions.push(cc.delayTime(timeFirst));
            }

            for (var i = 0; i < numKeyframes - 1; ++i) {
                var kf0 = keyframes[i];
                var kf1 = keyframes[(i+1)];

                var action = this._getAction(kf0, kf1, seqProp.getName(), node);
                if (action) {
                    // Apply easing
                    action = this._getEaseAction(action, kf0.getEasingType(), kf0.getEasingOpt());
                    actions.push(action);
                }
            }

            node.runAction(cc.sequence(actions));
        }
    },

    _sequenceCompleted:function () {
        var locRunningSequence = this._runningSequence;

        var locRunningName = locRunningSequence.getName();

        if(this._lastCompletedSequenceName != locRunningSequence.getName()){
            this._lastCompletedSequenceName = locRunningSequence.getName();
        }

        var nextSeqId = locRunningSequence.getChainedSequenceId();
        this._runningSequence = null;

        if (nextSeqId !== -1)
            this.runAnimations(nextSeqId, 0);

        if (this._delegate)
            this._delegate.completedAnimationSequenceNamed(locRunningName);

        if(this._target && this._animationCompleteCallbackFunc){
            this._animationCompleteCallbackFunc.call(this._target);
        }
    }
});


cc.BuilderSetSpriteFrame = cc.ActionInstant.extend({
    _spriteFrame:null,

    initWithSpriteFrame:function (spriteFrame) {
        this._spriteFrame = spriteFrame;
        return true;
    },
    update:function (time) {
        this.target.setSpriteFrame(this._spriteFrame);
    }
});

cc.BuilderSetSpriteFrame.create = function (spriteFrame) {
    var ret = new cc.BuilderSetSpriteFrame();
    if (ret) {
        if (ret.initWithSpriteFrame(spriteFrame))
            return ret;
    }
    return null;
};

//
// cc.BuilderRotateTo
//
cc.BuilderRotateTo = cc.ActionInterval.extend({
    _startAngle:0,
    _dstAngle:0,
    _diffAngle:0,

    initWithDuration:function (duration, angle) {
        if (cc.ActionInterval.prototype.initWithDuration.call(this, duration)) {
            this._dstAngle = angle;
            return true;
        } else {
            return false;
        }
    },
    update:function (time) {
        this.target.setRotation(this._startAngle + (this._diffAngle * time));
    },

    startWithTarget:function (node) {
        cc.ActionInterval.prototype.startWithTarget.call(this, node);
        this._startAngle = this.target.getRotation();
        this._diffAngle = this._dstAngle - this._startAngle;
    }
});

cc.BuilderRotateTo.create = function (duration, angle) {
    var ret = new cc.BuilderRotateTo();
    if (ret) {
        if (ret.initWithDuration(duration, angle))
            return ret;
    }
    return null;
};

//
// cc.BuilderRotateXTo
//
cc.BuilderRotateXTo = cc.ActionInterval.extend({
    // TODO: rotationX is not implemented in HTML5
});

cc.BuilderRotateXTo.create = function (duration, angle) {
    throw "rotationX has not been implemented in cocos2d-html5";
};

//
// cc.BuilderRotateYTo
//
cc.BuilderRotateYTo = cc.ActionInterval.extend({
    // TODO: rotationX is not implemented in HTML5
});

cc.BuilderRotateYTo.create = function (duration, angle) {
    throw "rotationY has not been implemented in cocos2d-html5";
};

//
// cc.BuilderSoundEffect
//
cc.BuilderSoundEffect = cc.ActionInstant.extend({
    init:function(file) {
        this._file = file;
        return true;
    },
    update:function(dt) {
        cc.audioEngine.playEffect(this._file);
    }
});
cc.BuilderSoundEffect.create = function (file, pitch, pan, gain) {
    var ret = new cc.BuilderSoundEffect();
    if (ret && ret.init(file)) {
            return ret;
    }
    return null;
};

