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
 * The touch event class
 * @class
 * @extends cc.Class
 *
 * @param {Number} x
 * @param {Number} y
 * @param {Number} id
 */
cc.Touch = cc.Class.extend(/** @lends cc.Touch# */{
    _point:null,
    _prevPoint:null,
    _id:0,
    _startPointCaptured: false,
    _startPoint:null,

    ctor:function (x, y, id) {
        this._point = cc.p(x || 0, y || 0);
        this._id = id || 0;
    },

    /**
     * Returns the current touch location in OpenGL coordinates
     * @return {cc.Point}
     */
    getLocation:function () {
        //TODO
        //return cc.director.convertToGL(this._point);
        return {x: this._point.x, y: this._point.y};
    },

	/**
	 * Returns X axis location value
	 * @returns {number}
	 */
	getLocationX: function () {
		return this._point.x;
	},

	/**
     * Returns Y axis location value
	 * @returns {number}
	 */
	getLocationY: function () {
		return this._point.y;
	},

    /**
     * Returns the previous touch location in OpenGL coordinates
     * @return {cc.Point}
     */
    getPreviousLocation:function () {
        //TODO
        //return cc.director.convertToGL(this._prevPoint);
        return {x: this._prevPoint.x, y: this._prevPoint.y};
    },

    /**
     * Returns the start touch location in OpenGL coordinates
     * @returns {cc.Point}
     */
    getStartLocation: function() {
        //TODO
        //return cc.director.convertToGL(this._startPoint);
        return {x: this._startPoint.x, y: this._startPoint.y};
    },

    /**
     * Returns the delta distance from the previous touche to the current one in screen coordinates
     * @return {cc.Point}
     */
    getDelta:function () {
        return cc.pSub(this._point, this._prevPoint);
    },

    /**
     * Returns the current touch location in screen coordinates
     * @return {cc.Point}
     */
    getLocationInView: function() {
        return {x: this._point.x, y: this._point.y};
    },

    /**
     * Returns the previous touch location in screen coordinates
     * @return {cc.Point}
     */
    getPreviousLocationInView: function(){
        return {x: this._prevPoint.x, y: this._prevPoint.y};
    },

    /**
     * Returns the start touch location in screen coordinates
     * @return {cc.Point}
     */
    getStartLocationInView: function(){
        return {x: this._startPoint.x, y: this._startPoint.y};
    },

    /**
     * Returns the id of cc.Touch
     * @return {Number}
     */
    getID:function () {
        return this._id;
    },

    /**
     * Returns the id of cc.Touch
     * @return {Number}
     * @deprecated since v3.0, please use getID() instead
     */
    getId:function () {
        cc.log("getId is deprecated. Please use getID instead.")
        return this._id;
    },

    /**
     * Sets information to touch
     * @param {Number} id
     * @param  {Number} x
     * @param  {Number} y
     */
    setTouchInfo:function (id, x, y) {
        this._prevPoint = this._point;
        this._point = cc.p(x || 0, y || 0);
        this._id = id;
        if(!this._startPointCaptured){
            this._startPoint = cc.p(this._point);
            this._startPointCaptured = true;
        }
    },

    _setPoint: function(x, y){
        if(y === undefined){
            this._point.x = x.x;
            this._point.y = x.y;
        }else{
            this._point.x = x;
            this._point.y = y;
        }
    },

    _setPrevPoint:function (x, y) {
        if(y === undefined)
            this._prevPoint = cc.p(x.x, x.y);
        else
            this._prevPoint = cc.p(x || 0, y || 0);
    }
});