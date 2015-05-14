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
 * Timeline Frame.
 * base class
 * @class
 */
ccs.Frame = ccs.Class.extend({

    _frameIndex: null,
    _tween: null,
    _timeline: null,
    _node: null,
    _tweenType: null,
    _easingParam: null,

    ctor: function(){
        this._frameIndex = 0;
        this._tween = true;
        this._timeline = null;
        this._node = null;
        this._easingParam = [];
    },

    _emitEvent: function(){
        if (this._timeline){
            this._timeline.getActionTimeline()._emitFrameEvent(this);
        }
    },

    _cloneProperty: function(frame){
        this._frameIndex = frame.getFrameIndex();
        this._tween = frame.isTween();
        this._tweenType = frame.getTweenType();
        this.setEasingParams(frame.getEasingParams());
    },

    /**
     * Set the frame index
     * @param {number} frameIndex
     */
    setFrameIndex: function(frameIndex){
        this._frameIndex = frameIndex;
    },

    /**
     * Get the frame index
     * @returns {null}
     */
    getFrameIndex: function(){
        return this._frameIndex;
    },

    /**
     * Set timeline
     * @param timeline
     */
    setTimeline: function(timeline){
        this._timeline = timeline;
    },

    /**
     * Get timeline
     * @param timeline
     * @returns {ccs.timeline}
     */
    getTimeline: function(timeline){
        return this._timeline;
    },

    /**
     * Set Node
     * @param {cc.Node} node
     */
    setNode: function(node){
        this._node = node;
    },

    /**
     * gets the Node
     * @return node
     */
    getNode: function(){
        return this._node;
    },

    /**
     * set tween
     * @param tween
     */
    setTween: function(tween){
        this._tween = tween;
    },

    /**
     * Gets the tween
     * @returns {boolean | null}
     */
    isTween: function(){
        return this._tween;
    },

    /**
     * the execution of the callback
     * @override
     * @param {ccs.Frame} nextFrame
     */
    onEnter: function(nextFrame){ // = 0
    },

    /**
     * Each frame logic
     * @override
     * @param {number} percent
     */
    apply: function(percent){
        if(!this._tween)
            return;
        if(this._tweenType !== ccs.FrameEaseType.TWEEN_EASING_MAX  && this._tweenType !==  ccs.FrameEaseType.Linear)
            percent = this.tweenPercent(percent);
        this._onApply(percent);
    },

    _onApply: function(percent){

    },

    /**
     * to copy object with deep copy.
     * returns a clone of action.
     * @override
     * @return {ccs.Frame}
     */
    clone: function(){ // = 0
    },

    tweenPercent: function(percent){
        var func = ccs.Frame.tweenToMap[this._tweenType];
        if(func)
            return func(percent, this._easingParam);
        else
            return percent;
    },

    setEasingParams: function(easingParams){
        if(easingParams){
            this._easingParam.length = 0;
            for(var i=0; i<easingParams.length; i++)
                this._easingParam[i] = easingParams[i];
        }
    },

    getEasingParams: function(){
        return this._easingParam;
    },

    setTweenType: function(tweenType){
        this._tweenType = tweenType;
    },

    getTweenType: function(){
        return this._tweenType;
    },

    isEnterWhenPassed: function(){
        return this._enterWhenPassed;
    }
});

ccs.Frame.tweenToMap = {
    1: cc._easeSineInObj.easing,//Sine_EaseIn
    2: cc._easeSineOutObj.easing,//Sine_EaseOut
    3: cc._easeSineInOutObj.easing,//Sine_EaseInOut

    4: cc._easeQuadraticActionIn.easing,//Quad_EaseIn
    5: cc._easeQuadraticActionOut.easing,//Quad_EaseOut
    6: cc._easeQuadraticActionInOut.easing,//Quad_EaseInOut

    7: cc._easeCubicActionIn.easing, //Cubic_EaseIn
    8: cc._easeCubicActionOut.easing,//Cubic_EaseOut
    9: cc._easeCubicActionInOut.easing,//Cubic_EaseInOut

    10: cc._easeCubicActionIn.easing,//Cubic_EaseIn
    11: cc._easeCubicActionOut.easing,//Cubic_EaseOut
    12: cc._easeCubicActionInOut.easing,//Cubic_EaseInOut

    13: cc._easeQuinticActionIn.easing,//Quint_EaseIn
    14: cc._easeQuinticActionOut.easing,//Quint_EaseOut
    15: cc._easeQuinticActionInOut.easing,//Quint_EaseInOut

    16: cc._easeExponentialInObj.easing,//Expo_EaseIn
    17: cc._easeExponentialOutObj.easing,//Expo_EaseOut
    18: cc._easeExponentialInOutObj.easing,//Expo_EaseInOut

    19: cc._easeCircleActionIn.easing,//Circ_EaseIn
    20: cc._easeCircleActionOut.easing,//Circ_EaseOut
    21: cc._easeCircleActionInOut.easing,//Circ_EaseInOut

    22: function(time, easingParam){
        var period = 0.3;
        easingParam != null && ( period = easingParam[0] );
        return cc.easeElasticIn(period).easing(time);
    },//Elastic_EaesIn
    23: function(time, easingParam){
        var period = 0.3;
        easingParam != null && ( period = easingParam[0] );
        return cc.easeElasticOut(period).easing(time);
    },//Elastic_EaesOut
    24: function(time, easingParam){
        var period = 0.3;
        easingParam != null && ( period = easingParam[0] );
        return cc.easeElasticInOut(period).easing(time);
    },//Elastic_EaesInOut

    25: cc._easeBackInObj.easing, //Back_EaseIn
    26: cc._easeBackOutObj.easing, //Back_EaseOut
    27: cc._easeBackInOutObj.easing, //Back_EaseInOut

    28: cc._easeBounceInObj.easing, //Bounce_EaseIn
    29: cc._easeBounceOutObj.easing, //Bounce_EaseOut
    30: cc._easeBounceInOutObj.easing //Bounce_EaseInOut
};

/**
 * Visible frame
 * To control the display state
 * @class
 * @extend ccs.Frame
 */
ccs.VisibleFrame = ccs.Frame.extend({

    _visible: true,

    ctor: function(){
        ccs.Frame.prototype.ctor.call(this);
        this._visible = true;
    },

    /**
     * the execution of the callback
     * @param {ccs.Frame} nextFrame
     */
    onEnter: function(nextFrame){
        if(this._node)
            this._node.setVisible(this._visible);
    },

    /**
     * to copy object with deep copy.
     * returns a clone of action.
     * @return {ccs.VisibleFrame}
     */
    clone: function(){
        var frame = new ccs.VisibleFrame();
        frame.setVisible(this._visible);

        frame._cloneProperty(this);

        return frame;
    },

    /**
     * Set display state
     * @param {Boolean} visible
     */
    setVisible: function(visible){
        this._visible = visible;
    },

    /**
     * Get the display state
     * @returns {Boolean}
     */
    isVisible: function(){
        return this._visible;
    }

});

/**
 * Create the visible frame
 *
 * @deprecated v3.0, please use new ccs.VisibleFrame() instead.
 * @returns {ccs.VisibleFrame}
 */
ccs.VisibleFrame.create = function(){
    return new ccs.VisibleFrame();
};

/**
 * Texture frame
 * @class
 * @extend ccs.Frame
 */
ccs.TextureFrame = ccs.Frame.extend({

    _sprite: null,
    _textureName: null,

    ctor: function(){
        ccs.Frame.prototype.ctor.call(this);

        this._textureName = "";
    },

    /**
     * Set the node element to draw texture
     * @param {cc.Node} node
     */
    setNode: function(node){
        ccs.Frame.prototype.setNode.call(this, node);
        this._sprite = node;
    },

    /**
     * the execution of the callback
     * @param {ccs.Frame} nextFrame
     */
    onEnter: function(nextFrame){
        if(this._sprite){
            var spriteBlendFunc = this._sprite.getBlendFunc();
            var spriteFrame = cc.spriteFrameCache._spriteFrames[this._textureName];
            if(spriteFrame != null)
                this._sprite.setSpriteFrame(spriteFrame);
            else
                this._sprite.setTexture(this._textureName);

            if(this._sprite.getBlendFunc() !== spriteBlendFunc)
                this._sprite.setBlendFunc(spriteBlendFunc);
        }

    },

    /**
     * to copy object with deep copy.
     * returns a clone of action.
     * @return {ccs.TextureFrame}
     */
    clone: function(){
        var frame = new ccs.TextureFrame();
        frame.setTextureName(this._textureName);
        frame._cloneProperty(this);
        return frame;
    },

    /**
     * Set the texture name
     * @param {string} textureName
     */
    setTextureName: function(textureName){
        this._textureName = textureName;
    },

    /**
     * Gets the Texture name
     * @returns {null}
     */
    getTextureName: function(){
        return this._textureName;
    }

});

/**
 * Create the Texture frame
 *
 * @deprecated v3.0, please use new ccs.TextureFrame() instead.
 * @returns {ccs.TextureFrame}
 */
ccs.TextureFrame.create = function(){
    return new ccs.TextureFrame();
};

/**
 * Rotation Frame
 * @class
 * @extend ccs.Frame
 */
ccs.RotationFrame = ccs.Frame.extend({

    _rotation: null,
    _betwennRotation: null,

    ctor: function(){
        ccs.Frame.prototype.ctor.call(this);
        this._rotation = 0;
    },

    /**
     * the execution of the callback
     * @param {ccs.Frame} nextFrame
     */
    onEnter: function(nextFrame){
        if(!this._node)
            return;
        this._node.setRotation(this._rotation);

        if(this._tween){
            this._betwennRotation = nextFrame._rotation - this._rotation;
        }
    },

    /**
     * Each frame logic
     * @param {number} percent
     */
    _onApply: function(percent){
        if (this._betwennRotation !== 0){
            var rotation = this._rotation + percent * this._betwennRotation;
            this._node.setRotation(rotation);
        }
    },

    /**
     * to copy object with deep copy.
     * returns a clone of action.
     * @return {ccs.RotationFrame}
     */
    clone: function(){
        var frame = new ccs.RotationFrame();
        frame.setRotation(this._rotation);

        frame._cloneProperty(this);

        return frame;
    },

    /**
     * Set the rotation
     * @param {Number} rotation
     */
    setRotation: function(rotation){
        this._rotation = rotation;
    },

    /**
     * Gets the rotation
     * @returns {Number}
     */
    getRotation: function(){
        return this._rotation;
    }

});

/**
 * Create the Rotation frame
 *
 * @deprecated v3.0, please use new ccs.RotationFrame() instead.
 * @returns {ccs.RotationFrame}
 */
ccs.RotationFrame.create = function(){
    return new ccs.RotationFrame();
};

/**
 * Skew frame
 * @class
 * @extend ccs.Frame
 */
ccs.SkewFrame = ccs.Frame.extend({

    _skewX: null,
    _skewY: null,
    _betweenSkewX: null,
    _betweenSkewY: null,

    ctor: function(){
        ccs.Frame.prototype.ctor.call(this);
        this._skewX = 0;
        this._skewY = 0;
    },

    /**
     * the execution of the callback
     * @param {ccs.Frame} nextFrame
     */
    onEnter: function(nextFrame){
        if(!this._node)
            return;
        this._node.setSkewX(this._skewX);
        this._node.setSkewY(this._skewY);

        if(this._tween){
            this._betweenSkewX = nextFrame._skewX - this._skewX;
            this._betweenSkewY = nextFrame._skewY - this._skewY;
        }

    },

    /**
     * Each frame logic
     * @param {number} percent
     */
    _onApply: function(percent){
        if (this._betweenSkewX !== 0 || this._betweenSkewY !== 0)
        {
            var skewx = this._skewX + percent * this._betweenSkewX;
            var skewy = this._skewY + percent * this._betweenSkewY;

            this._node.setSkewX(skewx);
            this._node.setSkewY(skewy);
        }
    },

    /**
     * to copy object with deep copy.
     * returns a clone of action.
     * @return {ccs.SkewFrame}
     */
    clone: function(){
        var frame = new ccs.SkewFrame();
        frame.setSkewX(this._skewX);
        frame.setSkewY(this._skewY);

        frame._cloneProperty(this);

        return frame;
    },

    /**
     * Set the skew x
     * @param {Number} skewx
     */
    setSkewX: function(skewx){
        this._skewX = skewx;
    },

    /**
     * Gets the skew x
     * @returns {Number}
     */
    getSkewX: function(){
        return this._skewX;
    },

    /**
     * Set the skew y
     * @param {Number} skewy
     */
    setSkewY: function(skewy){
        this._skewY = skewy;
    },

    /**
     * Gets the skew y
     * @returns {Number}
     */
    getSkewY: function(){
        return this._skewY;
    }

});

/**
 * Create the Skew frame
 *
 * @deprecated v3.0, please use new ccs.SkewFrame() instead.
 * @returns {ccs.SkewFrame}
 */
ccs.SkewFrame.create = function(){
    return new ccs.SkewFrame();
};

/**
 * Rotation skew frame
 * @class
 * @extend ccs.SkewFrame
 */
ccs.RotationSkewFrame = ccs.SkewFrame.extend({

    /**
     * the execution of the callback
     * @param {ccs.Frame} nextFrame
     */
    onEnter: function(nextFrame){
        if(!this._node)
            return;
        this._node.setRotationX(this._skewX);
        this._node.setRotationY(this._skewY);

        if (this._tween){
            this._betweenSkewX = nextFrame._skewX - this._skewX;
            this._betweenSkewY = nextFrame._skewY - this._skewY;
        }

    },

    /**
     * Each frame logic
     * @param {number} percent
     */
    _onApply: function(percent){
        if (this._node && (this._betweenSkewX !== 0 || this._betweenSkewY !== 0)){
            var skewx = this._skewX + percent * this._betweenSkewX;
            var skewy = this._skewY + percent * this._betweenSkewY;

            this._node.setRotationX(skewx);
            this._node.setRotationY(skewy);
        }

    },

    /**
     * to copy object with deep copy.
     * returns a clone of action.
     * @return {ccs.RotationSkewFrame}
     */
    clone: function(){
        var frame = new ccs.RotationSkewFrame();
        frame.setSkewX(this._skewX);
        frame.setSkewY(this._skewY);

        frame._cloneProperty(this);

        return frame;

    }

});

/**
 * Create the RotationSkew frame
 *
 * @deprecated v3.0, please use new ccs.RotationSkewFrame() instead.
 * @returns {ccs.RotationSkewFrame}
 */
ccs.RotationSkewFrame.create = function(){
    return new ccs.RotationSkewFrame();
};

/**
 * Position frame
 * @class
 * @extend ccs.Frame
 */
ccs.PositionFrame = ccs.Frame.extend({

    _position: null,
    _betweenX: null,
    _betweenY: null,

    ctor: function(){
        ccs.Frame.prototype.ctor.call(this);
        this._position = cc.p(0, 0);
    },

    /**
     * the execution of the callback
     * @param {ccs.Frame} nextFrame
     */
    onEnter: function(nextFrame){
        if(!this._node)
            return;

        this._node.setPosition(this._position);

        if(this._tween){
            this._betweenX = nextFrame._position.x - this._position.x;
            this._betweenY = nextFrame._position.y - this._position.y;
        }
    },

    /**
     * Each frame logic
     * @param {number} percent
     */
    _onApply: function(percent){
        if (this._node && (this._betweenX !== 0 || this._betweenY !== 0)){
            var p = cc.p(0, 0);
            p.x = this._position.x + this._betweenX * percent;
            p.y = this._position.y + this._betweenY * percent;

            this._node.setPosition(p);
        }
    },

    /**
     * to copy object with deep copy.
     * returns a clone of action.
     * @return {ccs.PositionFrame}
     */
    clone: function(){
        var frame = new ccs.PositionFrame();
        frame.setPosition(this._position);

        frame._cloneProperty(this);

        return frame;
    },

    /**
     * Set the position
     * @param {cc.p} position
     */
    setPosition: function(position){
        this._position = position;
    },

    /**
     * gets the position
     * @returns {cc.p}
     */
    getPosition: function(){
        return this._position;
    },

    /**
     * Set the position x
     * @param {Number} x
     */
    setX: function(x){
        this._position.x = x;
    },

    /**
     * Gets the postion x
     * @returns {Number}
     */
    getX: function(){
        return this._position.x;
    },

    /**
     * Set the position y
     * @param {Number} y
     */
    setY: function(y){
        this._position.y = y;
    },

    /**
     * Gets the position y
     * @returns {Number}
     */
    getY: function(){
        return this._position.y;
    }

});

/**
 * Create the Position frame
 *
 * @deprecated v3.0, please use new ccs.PositionFrame() instead.
 * @returns {ccs.PositionFrame}
 */
ccs.PositionFrame.create = function(){
    return new ccs.PositionFrame();
};

/**
 * Scale frame
 * @class
 * @xtend ccs.Frame
 */
ccs.ScaleFrame = ccs.Frame.extend({

    _scaleX: null,
    _scaleY: null,
    _betweenScaleX: null,
    _betweenScaleY: null,

    ctor: function(){
        ccs.Frame.prototype.ctor.call(this);
        this._scaleX = 1;
        this._scaleY = 1;
    },

    /**
     * the execution of the callback
     * @param {ccs.Frame} nextFrame
     */
    onEnter: function(nextFrame){
        if(!this._node)
            return;
        this._node.setScaleX(this._scaleX);
        this._node.setScaleY(this._scaleY);

        if(this._tween){
            this._betweenScaleX = nextFrame._scaleX - this._scaleX;
            this._betweenScaleY = nextFrame._scaleY - this._scaleY;
        }

    },

    /**
     * Each frame logic
     * @param {number} percent
     */
    _onApply: function(percent){
        if (this._node && (this._betweenScaleX !== 0 || this._betweenScaleY !== 0)){
            var scaleX = this._scaleX + this._betweenScaleX * percent;
            var scaleY = this._scaleY + this._betweenScaleY * percent;

            this._node.setScaleX(scaleX);
            this._node.setScaleY(scaleY);
        }
    },

    /**
     * to copy object with deep copy.
     * returns a clone of action.
     * @return {ccs.ScaleFrame}
     */
    clone: function(){
        var frame = new ccs.ScaleFrame();
        frame.setScaleX(this._scaleX);
        frame.setScaleY(this._scaleY);

        frame._cloneProperty(this);

        return frame;

    },

    /**
     * Set the scale
     * @param {Number} scale
     */
    setScale: function(scale){
        this._scaleX = scale;
        this._scaleY = scale;
    },

    /**
     * Set the scale x
     * @param {Number} scaleX
     */
    setScaleX: function(scaleX){
        this._scaleX = scaleX;
    },

    /**
     * Gets the scale x
     * @returns {Number}
     */
    getScaleX: function(){
        return this._scaleX;
    },

    /**
     * Set the scale y
     * @param {Number} scaleY
     */
    setScaleY: function(scaleY){
        this._scaleY = scaleY;
    },

    /**
     * Gets the scale y
     * @returns {Number}
     */
    getScaleY: function(){
        return this._scaleY;
    }

});

/**
 * Create the Scale frame
 *
 * @deprecated v3.0, please use new ccs.ScaleFrame() instead.
 * @returns {ccs.ScaleFrame}
 */
ccs.ScaleFrame.create = function(){
    return new ccs.ScaleFrame();
};

/**
 * AnchorPoint frame
 * @class
 * @extend ccs.Frame
 */
ccs.AnchorPointFrame = ccs.Frame.extend({

    _anchorPoint: null,

    ctor: function(){
        ccs.Frame.prototype.ctor.call(this);
        this._anchorPoint = cc.p(0, 0);
    },

    /**
     * the execution of the callback
     * @param {ccs.Frame} nextFrame
     */
    onEnter: function(nextFrame){
        if(this._node)
            this._node.setAnchorPoint(this._anchorPoint);
    },

    /**
     * to copy object with deep copy.
     * returns a clone of action.
     * @return {ccs.AnchorPointFrame}
     */
    clone: function(){
        var frame = new ccs.AnchorPointFrame();
        frame.setAnchorPoint(this._anchorPoint);

        frame._cloneProperty(this);

        return frame;
    },

    /**
     * Set the anchor point
     * @param {cc.p} point
     */
    setAnchorPoint: function(point){
        this._anchorPoint = point;
    },

    /**
     * Gets the anchor point
     * @returns {cc.p}
     */
    getAnchorPoint: function(){
        return this._anchorPoint;
    }

});

/**
 * Create the AnchorPoint frame
 *
 * @deprecated v3.0, please use new ccs.AnchorPointFrame() instead.
 * @returns {ccs.AnchorPointFrame}
 */
ccs.AnchorPointFrame.create = function(){
    return new ccs.AnchorPointFrame();
};

/**
 * Static param
 * @namespace
 */
ccs.InnerActionType = {
    LoopAction : 0,
    NoLoopAction : 1,
    SingleFrame : 2
};

/**
 * Inner action frame
 * @class
 * @extend ccs.Frame
 */
ccs.InnerActionFrame = ccs.Frame.extend({

    _innerActionType: null,
    _startFrameIndex: null,

    _endFrameIndex:0,
    _singleFrameIndex: 0,
    _enterWithName: null,
    _animationName: "",

    ctor: function(){
        ccs.Frame.prototype.ctor.call(this);

        this._enterWithName = false;
        this._innerActionType = ccs.InnerActionType.LoopAction;
        this._startFrameIndex = 0;
    },

    /**
     * the execution of the callback
     * @param {ccs.Frame} nextFrame
     */
    onEnter: function(nextFrame){
        if(!this._node)  return;
        var innerActiontimeline = this._node.getActionByTag(this._node.getTag());
        if(!innerActiontimeline) return;
        if (ccs.InnerActionType.SingleFrame === this._innerActionType){
            innerActiontimeline.gotoFrameAndPause(this._singleFrameIndex);
            return;
        }

        var innerStart = this._startFrameIndex;
        var innerEnd = this._endFrameIndex;
        if (this._enterWithName){
            if (this._animationName === "-- ALL --"){
                innerStart = 0;
                innerEnd = innerActiontimeline.getDuration();
            } else if(innerActiontimeline.isAnimationInfoExists(this._animationName)) {
                var info = innerActiontimeline.getAnimationInfo(this._animationName);
                innerStart = info.startIndex;
                innerEnd = info.endIndex;
            }else{
                cc.log("Animation %s not exists!", this._animationName);
            }
        }

        var duration = this._timeline.getActionTimeline().getDuration();
        var odddiff = duration - this._frameIndex - innerEnd + innerStart;
        if (odddiff < 0){
            innerEnd += odddiff;
        }

        if (ccs.InnerActionType.NoLoopAction === this._innerActionType){
            innerActiontimeline.gotoFrameAndPlay(innerStart, innerEnd, false);
        }else if (ccs.InnerActionType.LoopAction === this._innerActionType){
            innerActiontimeline.gotoFrameAndPlay(innerStart, innerEnd, true);
        }
    },

    setAnimationName: function(animationName){
        this._animationName = animationName;
    },

    setSingleFrameIndex: function(frameIndex){
        this._singleFrameIndex = frameIndex;
    },

    getSingleFrameIndex: function(){
        return this._startFrameIndex;
    },

    setEnterWithName: function(isEnterWithName){
        this._enterWithName = isEnterWithName;
    },

    getEnterWithName: function(){
        return this._enterWithName;
    },

    /**
     * to copy object with deep copy.
     * returns a clone of action.
     * @return {ccs.InnerActionFrame}
     */
    clone: function(){
        var frame = new ccs.InnerActionFrame();
        frame.setInnerActionType(this._innerActionType);
        frame.setStartFrameIndex(this._startFrameIndex);
        frame.setEnterWithName(this._enterWithName);
        frame.setAnimationName(this._animationName);
        frame.setSingleFrameIndex(this._singleFrameIndex);

        frame._cloneProperty(this);

        return frame;

    },

    /**
     * Set the inner action type
     * @param {ccs.InnerActionType} type
     */
    setInnerActionType: function(type){
        this._innerActionType = type;
    },

    /**
     * Gets the inner action type
     * @returns {ccs.InnerActionType}
     */
    getInnerActionType: function(){
        return this._innerActionType;
    },

    /**
     * Set the start frame index
     * @param {Number} frameIndex
     */
    setStartFrameIndex: function(frameIndex){
        this._startFrameIndex = frameIndex;
    },

    /**
     * Get the start frame index
     * @returns {Number}
     */
    getStartFrameIndex: function(){
        return this._startFrameIndex;
    }

});

/**
 * Create the InnerAction frame
 *
 * @deprecated v3.0, please use new ccs.InnerActionFrame() instead.
 * @returns {ccs.InnerActionFrame}
 */
ccs.InnerActionFrame.create = function(){
    return new ccs.InnerActionFrame();
};

/**
 * Color frame
 * @class
 * @extend ccs.Frame
 */
ccs.ColorFrame = ccs.Frame.extend({

    _alpha: null,
    _color: null,

    _betweenAlpha: null,
    _betweenRed: null,
    _betweenGreen: null,
    _betweenBlue: null,

    ctor: function(){
        ccs.Frame.prototype.ctor.call(this);
        this._color = cc.color(255, 255, 255);
    },

    /**
     * the execution of the callback
     * @param {ccs.ColorFrame} nextFrame
     */
    onEnter: function(nextFrame){
        if(!this._node)
            return;
        this._node.setColor(this._color);
        if(this._tween){
            var color = nextFrame._color;
            this._betweenRed   = color.r - this._color.r;
            this._betweenGreen = color.g - this._color.g;
            this._betweenBlue  = color.b - this._color.b;
        }

    },

    /**
     * Each frame logic
     * @param {number} percent
     */
    _onApply: function(percent){
        if (this._node && this._tween && (this._betweenAlpha !== 0 || this._betweenRed !== 0 || this._betweenGreen !== 0 || this._betweenBlue !== 0)){

            var color = cc.color(255, 255, 255);
            color.r = this._color.r + this._betweenRed   * percent;
            color.g = this._color.g + this._betweenGreen * percent;
            color.b = this._color.b + this._betweenBlue  * percent;

            this._node.setColor(color);
            if(this._alpha !== null){
                var alpha = this._alpha + this._betweenAlpha * percent;
                this._node.setOpacity(alpha);
            }

        }
    },

    /**
     * to copy object with deep copy.
     * returns a clone of action.
     * @return {ccs.ColorFrame}
     */
    clone: function(){
        var frame = new ccs.ColorFrame();
        frame.setColor(this._color);
        frame._cloneProperty(this);
        return frame;
    },

    /**
     * Set the color
     * @param {cc.color} color
     */
    setColor: function(color){
        this._color = color;
    },

    /**
     * Gets the color
     * @returns {cc.color}
     */
    getColor: function(){
        return this._color;
    }

});

/**
 * Create the Color frame
 *
 * @deprecated v3.0, please use new ccs.ColorFrame() instead.
 * @returns {ccs.ColorFrame}
 */
ccs.ColorFrame.create = function(){
    return new ccs.ColorFrame();
};

/**
 * Alpha frame
 * @class
 * @extend ccs.Frame
 */
ccs.AlphaFrame = ccs.Frame.extend({

    _alpha: null,
    _betweenAlpha: null,

    ctor: function(){
        ccs.Frame.prototype.ctor.call(this);
        this._alpha = 255;
    },

    onEnter: function(nextFrame){
        if(!this._node)
            return;
        this._node.setOpacity(this._alpha);
        if(this._tween){
            this._betweenAlpha = nextFrame._alpha - this._alpha;
        }
    },

    _onApply: function(percent){
        if(!this._node)
            return;
        var alpha = this._alpha + this._betweenAlpha * percent;
        this._node.setOpacity(alpha);
    },

    /**
     * Set the alpha
     * @param {Number} alpha
     */
    setAlpha: function(alpha){
        this._alpha = alpha;
    },

    /**
     * Gets the alpha
     * @returns {Number}
     */
    getAlpha: function(){
        return this._alpha;
    },

    clone: function(){
        var frame = new ccs.AlphaFrame();
        frame.setAlpha(this._alpha);
        frame._cloneProperty(this);
        return frame;
    }
});

/**
 * Event frame
 * @class
 * @extend ccs.Frame
 */
ccs.EventFrame = ccs.Frame.extend({

    _event: null,

    ctor: function(){
        ccs.Frame.prototype.ctor.call(this);
        this._event = "";
    },

    /**
     * the execution of the callback
     * @param {ccs.Frame} nextFrame
     */
    onEnter: function(nextFrame){
        this._emitEvent();
    },

    /**
     * to copy object with deep copy.
     * returns a clone of action.
     * @return {ccs.EventFrame}
     */
    clone: function(){
        var frame = new ccs.EventFrame();
        frame.setEvent(this._event);

        frame._cloneProperty(this);

        return frame;
    },

    /**
     * Set the event
     * @param event
     */
    setEvent: function(event){
        this._event = event;
    },

    /**
     * Gets the event
     * @returns {null}
     */
    getEvent: function(){
        return this._event;
    }

});

/**
 * Create the Event frame
 *
 * @deprecated v3.0, please use new ccs.EventFrame() instead.
 * @returns {ccs.EventFrame}
 */
ccs.EventFrame.create = function(){
    return new ccs.EventFrame();
};

/**
 * zOrder frame
 * @class
 * @extend ccs.Frame
 */
ccs.ZOrderFrame = ccs.Frame.extend({

    _zorder: null,

    /**
     * the execution of the callback
     * @param {ccs.Frame} nextFrame
     */
    onEnter: function(nextFrame){
        if(this._node)
            this._node.setLocalZOrder(this._zorder);
    },

    /**
     * to copy object with deep copy.
     * returns a clone of action.
     * @return {ccs.ZOrderFrame}
     */
    clone: function(){
        var frame = new ccs.ZOrderFrame();
        frame.setZOrder(this._zorder);

        frame._cloneProperty(this);

        return frame;
    },

    /**
     * Set the zOrder
     * @param {Number} zorder
     */
    setZOrder: function(zorder){
        this._zorder = zorder;
    },

    /**
     * Gets the zOrder
     * @returns {Number}
     */
    getZOrder: function(){
        return this._zorder;
    }

});

/**
 * Create the ZOrder frame
 *
 * @deprecated v3.0, please use new ccs.ZOrderFrame() instead.
 * @returns {ccs.ZOrderFrame}
 */
ccs.ZOrderFrame.create = function(){
    return new ccs.ZOrderFrame();
};

ccs.BlendFuncFrame = ccs.Frame.extend({

    onEnter: function(nextFrame, currentFrameIndex){
        if(this._node)
            this._node.setBlendFunc(this._blendFunc);
    },

    clone: function(){
        var frame = new ccs.BlendFuncFrame();
        frame.setBlendFunc(this._blendFunc);
        frame.cloneProperty(this);
        return frame;
    }
});

ccs.BlendFuncFrame.create = function(){
    return new ccs.BlendFuncFrame();
};