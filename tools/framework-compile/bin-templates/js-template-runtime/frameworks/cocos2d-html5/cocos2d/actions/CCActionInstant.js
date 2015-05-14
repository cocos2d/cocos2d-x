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
 * Instant actions are immediate actions. They don't have a duration like.
 * the CCIntervalAction actions.
 * @class
 * @extends cc.FiniteTimeAction
 */
cc.ActionInstant = cc.FiniteTimeAction.extend(/** @lends cc.ActionInstant# */{
    /**
     * return true if the action has finished.
     * @return {Boolean}
     */
    isDone:function () {
        return true;
    },

    /**
     * called every frame with it's delta time. <br />
     * DON'T override unless you know what you are doing.
     * @param {Number} dt
     */
    step:function (dt) {
        this.update(1);
    },

    /**
     * Called once per frame. Time is the number of seconds of a frame interval.
     *
     * @param {Number} dt
     */
    update:function (dt) {
        //nothing
    },

    /**
     * returns a reversed action. <br />
     * For example: <br />
     * - The action will be x coordinates of 0 move to 100. <br />
     * - The reversed action will be x of 100 move to 0.
     * - Will be rewritten
     * @returns {cc.Action}
     */
    reverse:function(){
        return this.clone();
    },

    /**
     * to copy object with deep copy.
     * returns a clone of action.
     *
     * @return {cc.FiniteTimeAction}
     */
    clone:function(){
        return new cc.ActionInstant();
    }
});

/**
 * Show the node.
 * @class
 * @extends cc.ActionInstant
 */
cc.Show = cc.ActionInstant.extend(/** @lends cc.Show# */{

    /**
     * Called once per frame. Time is the number of seconds of a frame interval.
     *
     * @param {Number} dt
     */
    update:function (dt) {
        this.target.visible = true;
    },

    /**
     * returns a reversed action. <br />
     * For example: <br />
     * - The action will be x coordinates of 0 move to 100. <br />
     * - The reversed action will be x of 100 move to 0.
     * - Will be rewritten
     * @returns {cc.Hide}
     */
    reverse:function () {
        return new cc.Hide();
    },

    /**
     * to copy object with deep copy.
     * returns a clone of action.
     *
     * @return {cc.FiniteTimeAction}
     */
    clone:function(){
        return new cc.Show();
    }
});

/**
 * Show the Node.
 * @function
 * @return {cc.Show}
 * @example
 * // example
 * var showAction = cc.show();
 */
cc.show = function () {
    return new cc.Show();
};

/**
 * Show the Node. Please use cc.show instead.
 * @static
 * @deprecated since v3.0 <br /> Please use cc.show instead.
 * @return {cc.Show}
 */
cc.Show.create = cc.show;

/**
 * Hide the node.
 * @class
 * @extends cc.ActionInstant
 */
cc.Hide = cc.ActionInstant.extend(/** @lends cc.Hide# */{

    /**
     * Called once per frame. Time is the number of seconds of a frame interval.
     *
     * @param {Number} dt
     */
    update:function (dt) {
        this.target.visible = false;
    },

    /**
     * returns a reversed action. <br />
     * For example: <br />
     * - The action will be x coordinates of 0 move to 100. <br />
     * - The reversed action will be x of 100 move to 0.
     * - Will be rewritten
     * @returns {cc.Show}
     */
    reverse:function () {
        return new cc.Show();
    },

    /**
     * to copy object with deep copy.
     * returns a clone of action.
     *
     * @return {cc.Hide}
     */
    clone:function(){
        return new cc.Hide();
    }
});

/**
 * Hide the node.
 * @function
 * @return {cc.Hide}
 * @example
 * // example
 * var hideAction = cc.hide();
 */
cc.hide = function () {
    return new cc.Hide();
};

/**
 * Hide the node. Please use cc.hide instead.
 * @static
 * @deprecated since v3.0 <br /> Please use cc.hide instead.
 * @return {cc.Hide}
 * @example
 * // example
 * var hideAction = cc.hide();
 */
cc.Hide.create = cc.hide;

/**
 * Toggles the visibility of a node.
 * @class
 * @extends cc.ActionInstant
 */
cc.ToggleVisibility = cc.ActionInstant.extend(/** @lends cc.ToggleVisibility# */{

    /**
     * Called once per frame. Time is the number of seconds of a frame interval.
     *
     * @param {Number} dt
     */
    update:function (dt) {
        this.target.visible = !this.target.visible;
    },

    /**
     * returns a reversed action.
     * @returns {cc.ToggleVisibility}
     */
    reverse:function () {
        return new cc.ToggleVisibility();
    },

    /**
     * to copy object with deep copy.
     * returns a clone of action.
     *
     * @return {cc.ToggleVisibility}
     */
    clone:function(){
        return new cc.ToggleVisibility();
    }
});

/**
 * Toggles the visibility of a node.
 * @function
 * @return {cc.ToggleVisibility}
 * @example
 * // example
 * var toggleVisibilityAction = cc.toggleVisibility();
 */
cc.toggleVisibility = function () {
    return new cc.ToggleVisibility();
};

/**
 * Toggles the visibility of a node. Please use cc.toggleVisibility instead.
 * @static
 * @deprecated since v3.0 <br /> Please use cc.toggleVisibility instead.
 * @return {cc.ToggleVisibility}
 */
cc.ToggleVisibility.create = cc.toggleVisibility;

/**
 * Delete self in the next frame.
 * @class
 * @extends cc.ActionInstant
 * @param {Boolean} [isNeedCleanUp=true]
 *
 * @example
 * // example
 * var removeSelfAction = new cc.RemoveSelf(false);
 */
cc.RemoveSelf = cc.ActionInstant.extend({
     _isNeedCleanUp: true,

	/**
     * Constructor function, override it to extend the construction behavior, remember to call "this._super()" in the extended "ctor" function. <br />
	 * Create a RemoveSelf object with a flag indicate whether the target should be cleaned up while removing.
	 * @param {Boolean} [isNeedCleanUp=true]
	 */
    ctor:function(isNeedCleanUp){
        cc.FiniteTimeAction.prototype.ctor.call(this);

	    isNeedCleanUp !== undefined && this.init(isNeedCleanUp);
    },

    /**
     * Called once per frame. Time is the number of seconds of a frame interval.
     *
     * @param {Number} dt
     */
    update:function(dt){
        this.target.removeFromParent(this._isNeedCleanUp);
    },

    /**
     * Initialization of the node, please do not call this function by yourself, you should pass the parameters to constructor to initialize it .
     * @param isNeedCleanUp
     * @returns {boolean}
     */
    init:function(isNeedCleanUp){
        this._isNeedCleanUp = isNeedCleanUp;
        return true;
    },

    /**
     * returns a reversed action.
     */
    reverse:function(){
        return new cc.RemoveSelf(this._isNeedCleanUp);
    },

    /**
     * to copy object with deep copy.
     * returns a clone of action.
     *
     * @return {cc.RemoveSelf}
     */
    clone:function(){
        return new cc.RemoveSelf(this._isNeedCleanUp);
    }
});

/**
 * Create a RemoveSelf object with a flag indicate whether the target should be cleaned up while removing.
 *
 * @function
 * @param {Boolean} [isNeedCleanUp=true]
 * @return {cc.RemoveSelf}
 *
 * @example
 * // example
 * var removeSelfAction = cc.removeSelf();
 */
cc.removeSelf = function(isNeedCleanUp){
    return new cc.RemoveSelf(isNeedCleanUp);
};

/**
 * Please use cc.removeSelf instead.
 * Create a RemoveSelf object with a flag indicate whether the target should be cleaned up while removing.
 *
 * @static
 * @deprecated since v3.0 <br /> Please use cc.removeSelf instead.
 * @param {Boolean} [isNeedCleanUp=true]
 * @return {cc.RemoveSelf}
 */
cc.RemoveSelf.create = cc.removeSelf;

/**
 * Flips the sprite horizontally.
 * @class
 * @extends cc.ActionInstant
 * @param {Boolean} flip Indicate whether the target should be flipped or not
 *
 * @example
 * var flipXAction = new cc.FlipX(true);
 */
cc.FlipX = cc.ActionInstant.extend(/** @lends cc.FlipX# */{
    _flippedX:false,

	/**
     * Constructor function, override it to extend the construction behavior, remember to call "this._super()" in the extended "ctor" function. <br />
	 * Create a FlipX action to flip or unflip the target.
	 * @param {Boolean} flip Indicate whether the target should be flipped or not
	 */
    ctor:function(flip){
        cc.FiniteTimeAction.prototype.ctor.call(this);
        this._flippedX = false;
		flip !== undefined && this.initWithFlipX(flip);
    },

    /**
     * initializes the action with a set flipX.
     * @param {Boolean} flip
     * @return {Boolean}
     */
    initWithFlipX:function (flip) {
        this._flippedX = flip;
        return true;
    },

    /**
     * Called once per frame. Time is the number of seconds of a frame interval.
     *
     * @param {Number}  dt
     */
    update:function (dt) {
        this.target.flippedX = this._flippedX;
    },

    /**
     * returns a reversed action.
     * @return {cc.FlipX}
     */
    reverse:function () {
        return new cc.FlipX(!this._flippedX);
    },

    /**
     * to copy object with deep copy.
     * returns a clone of action.
     *
     * @return {cc.FiniteTimeAction}
     */
    clone:function(){
        var action = new cc.FlipX();
        action.initWithFlipX(this._flippedX);
        return action;
    }
});

/**
 * Create a FlipX action to flip or unflip the target.
 *
 * @function
 * @param {Boolean} flip Indicate whether the target should be flipped or not
 * @return {cc.FlipX}
 * @example
 * var flipXAction = cc.flipX(true);
 */
cc.flipX = function (flip) {
    return new cc.FlipX(flip);
};

/**
 * Plese use cc.flipX instead.
 * Create a FlipX action to flip or unflip the target
 *
 * @static
 * @deprecated since v3.0 <br /> Plese use cc.flipX instead.
 * @param {Boolean} flip Indicate whether the target should be flipped or not
 * @return {cc.FlipX}
 */
cc.FlipX.create = cc.flipX;

/**
 * Flips the sprite vertically
 * @class
 * @extends cc.ActionInstant
 * @param {Boolean} flip
 * @example
 * var flipYAction = new cc.FlipY(true);
 */
cc.FlipY = cc.ActionInstant.extend(/** @lends cc.FlipY# */{
    _flippedY:false,

	/**
     * Constructor function, override it to extend the construction behavior, remember to call "this._super()" in the extended "ctor" function. <br />
	 * Create a FlipY action to flip or unflip the target.
	 *
	 * @param {Boolean} flip
	 */
    ctor: function(flip){
        cc.FiniteTimeAction.prototype.ctor.call(this);
        this._flippedY = false;

		flip !== undefined && this.initWithFlipY(flip);
    },

    /**
     * initializes the action with a set flipY.
     * @param {Boolean} flip
     * @return {Boolean}
     */
    initWithFlipY:function (flip) {
        this._flippedY = flip;
        return true;
    },

    /**
     * Called once per frame. Time is the number of seconds of a frame interval.
     *
     * @param {Number}  dt
     */
    update:function (dt) {
        this.target.flippedY = this._flippedY;
    },

    /**
     * returns a reversed action.
     * @return {cc.FlipY}
     */
    reverse:function () {
        return new cc.FlipY(!this._flippedY);
    },

    /**
     * to copy object with deep copy.
     * returns a clone of action.
     *
     * @return {cc.FlipY}
     */
    clone:function(){
        var action = new cc.FlipY();
        action.initWithFlipY(this._flippedY);
        return action;
    }
});

/**
 * Create a FlipY action to flip or unflip the target.
 *
 * @function
 * @param {Boolean} flip
 * @return {cc.FlipY}
 * @example
 * var flipYAction = cc.flipY(true);
 */
cc.flipY = function (flip) {
    return new cc.FlipY(flip);
};

/**
 * Please use cc.flipY instead
 * Create a FlipY action to flip or unflip the target
 *
 * @static
 * @deprecated since v3.0 <br /> Please use cc.flipY instead.
 * @param {Boolean} flip
 * @return {cc.FlipY}
 */
cc.FlipY.create = cc.flipY;

/**
 * Places the node in a certain position
 * @class
 * @extends cc.ActionInstant
 * @param {cc.Point|Number} pos
 * @param {Number} [y]
 * @example
 * var placeAction = new cc.Place(cc.p(200, 200));
 * var placeAction = new cc.Place(200, 200);
 */
cc.Place = cc.ActionInstant.extend(/** @lends cc.Place# */{
    _x: 0,
	_y: 0,

	/**
     * Constructor function, override it to extend the construction behavior, remember to call "this._super()" in the extended "ctor" function. <br />
	 * Creates a Place action with a position.
	 * @param {cc.Point|Number} pos
	 * @param {Number} [y]
	 */
    ctor:function(pos, y){
        cc.FiniteTimeAction.prototype.ctor.call(this);
        this._x = 0;
	    this._y = 0;

		if (pos !== undefined) {
			if (pos.x !== undefined) {
				y = pos.y;
				pos = pos.x;
			}
			this.initWithPosition(pos, y);
		}
    },

    /**
     * Initializes a Place action with a position
     * @param {number} x
     * @param {number} y
     * @return {Boolean}
     */
    initWithPosition: function (x, y) {
        this._x = x;
        this._y = y;
        return true;
    },

    /**
     * Called once per frame. Time is the number of seconds of a frame interval.
     *
     * @param {Number}  dt
     */
    update:function (dt) {
        this.target.setPosition(this._x, this._y);
    },

    /**
     * to copy object with deep copy.
     * returns a clone of action.
     *
     * @return {cc.Place}
     */
    clone:function(){
        var action = new cc.Place();
        action.initWithPosition(this._x, this._y);
        return action;
    }
});

/**
 * Creates a Place action with a position.
 * @function
 * @param {cc.Point|Number} pos
 * @param {Number} [y]
 * @return {cc.Place}
 * @example
 * // example
 * var placeAction = cc.place(cc.p(200, 200));
 * var placeAction = cc.place(200, 200);
 */
cc.place = function (pos, y) {
    return new cc.Place(pos, y);
};

/**
 * Please use cc.place instead.
 * Creates a Place action with a position.
 * @static
 * @deprecated since v3.0 <br /> Please use cc.place instead.
 * @param {cc.Point|Number} pos
 * @param {Number} [y]
 * @return {cc.Place}
 */
cc.Place.create = cc.place;


/**
 * Calls a 'callback'.
 * @class
 * @extends cc.ActionInstant
 * @param {function} selector
 * @param {object|null} [selectorTarget]
 * @param {*|null} [data] data for function, it accepts all data types.
 * @example
 * // example
 * // CallFunc without data
 * var finish = new cc.CallFunc(this.removeSprite, this);
 *
 * // CallFunc with data
 * var finish = new cc.CallFunc(this.removeFromParentAndCleanup, this,  true);
 */
cc.CallFunc = cc.ActionInstant.extend(/** @lends cc.CallFunc# */{
    _selectorTarget:null,
    _callFunc:null,
    _function:null,
    _data:null,

	/**
     * Constructor function, override it to extend the construction behavior, remember to call "this._super()" in the extended "ctor" function. <br />
	 * Creates a CallFunc action with the callback.
	 * @param {function} selector
	 * @param {object|null} [selectorTarget]
	 * @param {*|null} [data] data for function, it accepts all data types.
	 */
    ctor:function(selector, selectorTarget, data){
        cc.FiniteTimeAction.prototype.ctor.call(this);

		if(selector !== undefined){
			if(selectorTarget === undefined)
				this.initWithFunction(selector);
			else this.initWithFunction(selector, selectorTarget, data);
		}
    },

    /**
     * Initializes the action with a function or function and its target
     * @param {function} selector
     * @param {object|Null} selectorTarget
     * @param {*|Null} [data] data for function, it accepts all data types.
     * @return {Boolean}
     */
    initWithFunction:function (selector, selectorTarget, data) {
	    if (selectorTarget) {
            this._data = data;
            this._callFunc = selector;
            this._selectorTarget = selectorTarget;
	    }
	    else if (selector)
		    this._function = selector;
        return true;
    },

    /**
     * execute the function.
     */
    execute:function () {
        if (this._callFunc != null)         //CallFunc, N, ND
            this._callFunc.call(this._selectorTarget, this.target, this._data);
        else if(this._function)
            this._function.call(null, this.target);
    },

    /**
     * Called once per frame. Time is the number of seconds of a frame interval.
     *
     * @param {Number}  dt
     */
    update:function (dt) {
        this.execute();
    },

    /**
     * Get selectorTarget.
     * @return {object}
     */
    getTargetCallback:function () {
        return this._selectorTarget;
    },

    /**
     * Set selectorTarget.
     * @param {object} sel
     */
    setTargetCallback:function (sel) {
        if (sel !== this._selectorTarget) {
            if (this._selectorTarget)
                this._selectorTarget = null;
            this._selectorTarget = sel;
        }
    },

    /**
     * to copy object with deep copy.
     * returns a clone of action.
     *
     * @return {cc.CallFunc}
     */
    clone:function(){
       var action = new cc.CallFunc();
        if(this._selectorTarget){
             action.initWithFunction(this._callFunc,  this._selectorTarget, this._data)
        }else if(this._function){
             action.initWithFunction(this._function);
        }
        return action;
    }
});

/**
 * Creates the action with the callback
 * @function
 * @param {function} selector
 * @param {object|null} [selectorTarget]
 * @param {*|null} [data] data for function, it accepts all data types.
 * @return {cc.CallFunc}
 * @example
 * // example
 * // CallFunc without data
 * var finish = cc.callFunc(this.removeSprite, this);
 *
 * // CallFunc with data
 * var finish = cc.callFunc(this.removeFromParentAndCleanup, this._grossini,  true);
 */
cc.callFunc = function (selector, selectorTarget, data) {
    return new cc.CallFunc(selector, selectorTarget, data);
};

/**
 * Please use cc.callFunc instead.
 * Creates the action with the callback.
 * @static
 * @deprecated since v3.0 <br /> Please use cc.callFunc instead.
 * @param {function} selector
 * @param {object|null} [selectorTarget]
 * @param {*|null} [data] data for function, it accepts all data types.
 * @return {cc.CallFunc}
 */
cc.CallFunc.create = cc.callFunc;
