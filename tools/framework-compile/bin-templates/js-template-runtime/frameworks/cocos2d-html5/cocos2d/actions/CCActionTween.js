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
 *
 * @class
 * @extends cc.Class
 */
cc.ActionTweenDelegate = cc.Class.extend(/** @lends cc.ActionTweenDelegate */{

    /**
     * Update Tween Action.
     * @param value
     * @param key
     */
    updateTweenAction:function(value, key){}
});

/**
 * cc.ActionTween
 * cc.ActionTween is an action that lets you update any property of an object.
 *
 * @class
 * @extends cc.ActionInterval
 * @example
 * //For example, if you want to modify the "width" property of a target from 200 to 300 in 2 seconds, then:
 *  var modifyWidth = cc.actionTween(2,"width",200,300)
 *  target.runAction(modifyWidth);
 *
 * //Another example: cc.ScaleTo action could be rewriten using cc.PropertyAction:
 * // scaleA and scaleB are equivalents
 * var scaleA = cc.scaleTo(2,3);
 * var scaleB = cc.actionTween(2,"scale",1,3);
 * @param {Number} duration
 * @param {String} key
 * @param {Number} from
 * @param {Number} to
 */
cc.ActionTween = cc.ActionInterval.extend(/** @lends cc.ActionTween */{
    key:"",
    from:0,
    to:0,
    delta:0,

	/**
     * Constructor function, override it to extend the construction behavior, remember to call "this._super()" in the extended "ctor" function. <br />
	 * Creates an initializes the action with the property name (key), and the from and to parameters.
	 * @param {Number} duration
	 * @param {String} key
	 * @param {Number} from
	 * @param {Number} to
	 */
    ctor:function(duration, key, from, to){
        cc.ActionInterval.prototype.ctor.call(this);
        this.key = "";

		to !== undefined && this.initWithDuration(duration, key, from, to);
    },

    /**
     * initializes the action with the property name (key), and the from and to parameters.
     * @param {Number} duration
     * @param {String} key
     * @param {Number} from
     * @param {Number} to
     * @return {Boolean}
     */
    initWithDuration:function (duration, key, from, to) {
        if (cc.ActionInterval.prototype.initWithDuration.call(this, duration)) {
            this.key = key;
            this.to = to;
            this.from = from;
            return true;
        }
        return false;
    },

    /**
     * Start this tween with target.
     * @param {cc.ActionTweenDelegate} target
     */
    startWithTarget:function (target) {
        if(!target || !target.updateTweenAction)
            throw "cc.ActionTween.startWithTarget(): target must be non-null, and target must implement updateTweenAction function";
        cc.ActionInterval.prototype.startWithTarget.call(this, target);
        this.delta = this.to - this.from;
    },

    /**
     * Called once per frame. Time is the number of seconds of a frame interval.
     *
     * @param {Number}  dt
     */
    update:function (dt) {
        this.target.updateTweenAction(this.to - this.delta * (1 - dt), this.key);
    },

    /**
     * returns a reversed action.
     * @return {cc.ActionTween}
     */
    reverse:function () {
        return new cc.ActionTween(this.duration, this.key, this.to, this.from);
    },

    /**
     * to copy object with deep copy.
     * returns a clone of action.
     *
     * @return {cc.ActionTween}
     */
    clone:function(){
        var action = new cc.ActionTween();
        action.initWithDuration(this._duration, this.key, this.from, this.to);
        return action;
    }
});

/**
 * Creates an initializes the action with the property name (key), and the from and to parameters.
 * @function
 * @param {Number} duration
 * @param {String} key
 * @param {Number} from
 * @param {Number} to
 * @return {cc.ActionTween}
 */
cc.actionTween = function (duration, key, from, to) {
    return new cc.ActionTween(duration, key, from, to);
};

/**
 * Please use cc.actionTween instead.
 * Creates an initializes the action with the property name (key), and the from and to parameters.
 * @static
 * @deprecated since v3.0 <br /> Please use cc.actionTween instead.
 * @param {Number} duration
 * @param {String} key
 * @param {Number} from
 * @param {Number} to
 * @return {cc.ActionTween}
 */
cc.ActionTween.create = cc.actionTween;