/****************************************************************************
 Copyright (c) 2008-2010 Ricardo Quesada
 Copyright (c) 2011-2012 cocos2d-x.org
 Copyright (c) 2013-2014 Chukong Technologies Inc.
 Copyright (c) 2008 Radu Gruian
 Copyright (c) 2011 Vit Valentin

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

 Orignal code by Radu Gruian: http://www.codeproject.com/Articles/30838/Overhauser-Catmull-Rom-Splines-for-Camera-Animatio.So

 Adapted to cocos2d-x by Vit Valentin

 Adapted from cocos2d-x to cocos2d-iphone by Ricardo Quesada
 ****************************************************************************/

/**
 * Returns the Cardinal Spline position for a given set of control points, tension and time. <br />
 * CatmullRom Spline formula. <br />
 * s(-ttt + 2tt - t)P1 + s(-ttt + tt)P2 + (2ttt - 3tt + 1)P2 + s(ttt - 2tt + t)P3 + (-2ttt + 3tt)P3 + s(ttt - tt)P4
 *
 * @function
 * @param {cc.Point} p0
 * @param {cc.Point} p1
 * @param {cc.Point} p2
 * @param {cc.Point} p3
 * @param {Number} tension
 * @param {Number} t
 * @return {cc.Point}
 */
cc.cardinalSplineAt = function (p0, p1, p2, p3, tension, t) {
    var t2 = t * t;
    var t3 = t2 * t;

    /*
     * Formula: s(-ttt + 2tt - t)P1 + s(-ttt + tt)P2 + (2ttt - 3tt + 1)P2 + s(ttt - 2tt + t)P3 + (-2ttt + 3tt)P3 + s(ttt - tt)P4
     */
    var s = (1 - tension) / 2;

    var b1 = s * ((-t3 + (2 * t2)) - t);                      // s(-t3 + 2 t2 - t)P1
    var b2 = s * (-t3 + t2) + (2 * t3 - 3 * t2 + 1);          // s(-t3 + t2)P2 + (2 t3 - 3 t2 + 1)P2
    var b3 = s * (t3 - 2 * t2 + t) + (-2 * t3 + 3 * t2);      // s(t3 - 2 t2 + t)P3 + (-2 t3 + 3 t2)P3
    var b4 = s * (t3 - t2);                                   // s(t3 - t2)P4

    var x = (p0.x * b1 + p1.x * b2 + p2.x * b3 + p3.x * b4);
    var y = (p0.y * b1 + p1.y * b2 + p2.y * b3 + p3.y * b4);
    return cc.p(x, y);
};

/**
 * returns a new copy of the array reversed.
 *
 * @return {Array}
 */
cc.reverseControlPoints = function (controlPoints) {
    var newArray = [];
    for (var i = controlPoints.length - 1; i >= 0; i--) {
        newArray.push(cc.p(controlPoints[i].x, controlPoints[i].y));
    }
    return newArray;
};


/**
 * returns a new clone of the controlPoints
 *
 * @param controlPoints
 * @returns {Array}
 */
cc.cloneControlPoints = function (controlPoints) {
    var newArray = [];
    for (var i = 0; i < controlPoints.length; i++)
        newArray.push(cc.p(controlPoints[i].x, controlPoints[i].y));
    return newArray;
};

/**
 * returns a new clone of the controlPoints
 * @deprecated since v3.0 please use cc.cloneControlPoints() instead.
 * @param controlPoints
 * @returns {Array}
 */
cc.copyControlPoints = cc.cloneControlPoints;

/**
 * returns a point from the array
 *
 * @param {Array} controlPoints
 * @param {Number} pos
 * @return {Array}
 */
cc.getControlPointAt = function (controlPoints, pos) {
    var p = Math.min(controlPoints.length - 1, Math.max(pos, 0));
    return controlPoints[p];
};

/**
 * reverse the current control point array inline, without generating a new one <br />
 *
 * @param controlPoints
 */
cc.reverseControlPointsInline = function (controlPoints) {
    var len = controlPoints.length;
    var mid = 0 | (len / 2);
    for (var i = 0; i < mid; ++i) {
        var temp = controlPoints[i];
        controlPoints[i] = controlPoints[len - i - 1];
        controlPoints[len - i - 1] = temp;
    }
};


/**
 * Cardinal Spline path. {@link http://en.wikipedia.org/wiki/Cubic_Hermite_spline#Cardinal_spline}
 * Absolute coordinates.
 *
 * @class
 * @extends cc.ActionInterval
 * @param {Number} duration
 * @param {Array} points array of control points
 * @param {Number} tension
 *
 * @example
 * //create a cc.CardinalSplineTo
 * var action1 = cc.cardinalSplineTo(3, array, 0);
 */
cc.CardinalSplineTo = cc.ActionInterval.extend(/** @lends cc.CardinalSplineTo# */{
    /** Array of control points */
    _points:null,
    _deltaT:0,
    _tension:0,
    _previousPosition:null,
    _accumulatedDiff:null,

	/**
     * Constructor function, override it to extend the construction behavior, remember to call "this._super()" in the extended "ctor" function. <br />
	 * Creates an action with a Cardinal Spline array of points and tension.
	 * @param {Number} duration
	 * @param {Array} points array of control points
	 * @param {Number} tension
	 */
    ctor: function (duration, points, tension) {
        cc.ActionInterval.prototype.ctor.call(this);

        this._points = [];
		tension !== undefined && this.initWithDuration(duration, points, tension);
    },

    /**
     * initializes the action with a duration and an array of points
     *
     * @param {Number} duration
     * @param {Array} points array of control points
     * @param {Number} tension
     *
     * @return {Boolean}
     */
    initWithDuration:function (duration, points, tension) {
        if(!points || points.length === 0)
            throw "Invalid configuration. It must at least have one control point";

        if (cc.ActionInterval.prototype.initWithDuration.call(this, duration)) {
            this.setPoints(points);
            this._tension = tension;
            return true;
        }
        return false;
    },

    /**
     * returns a new clone of the action
     *
     * @returns {cc.CardinalSplineTo}
     */
    clone:function () {
        var action = new cc.CardinalSplineTo();
        action.initWithDuration(this._duration, cc.copyControlPoints(this._points), this._tension);
        return action;
    },

    /**
     * called before the action start. It will also set the target.
     *
     * @param {cc.Node} target
     */
    startWithTarget:function (target) {
        cc.ActionInterval.prototype.startWithTarget.call(this, target);
        // Issue #1441 from cocos2d-iphone
        this._deltaT = 1 / (this._points.length - 1);
        this._previousPosition = cc.p(this.target.getPositionX(), this.target.getPositionY());
        this._accumulatedDiff = cc.p(0, 0);
    },

    /**
     * Called once per frame. Time is the number of seconds of a frame interval.
     *
     * @param {Number}  dt
     */
    update:function (dt) {
        dt = this._computeEaseTime(dt);
        var p, lt;
        var ps = this._points;
        // eg.
        // p..p..p..p..p..p..p
        // 1..2..3..4..5..6..7
        // want p to be 1, 2, 3, 4, 5, 6
        if (dt === 1) {
            p = ps.length - 1;
            lt = 1;
        } else {
            var locDT = this._deltaT;
            p = 0 | (dt / locDT);
            lt = (dt - locDT * p) / locDT;
        }

        var newPos = cc.cardinalSplineAt(
            cc.getControlPointAt(ps, p - 1),
            cc.getControlPointAt(ps, p - 0),
            cc.getControlPointAt(ps, p + 1),
            cc.getControlPointAt(ps, p + 2),
            this._tension, lt);

        if (cc.ENABLE_STACKABLE_ACTIONS) {
            var tempX, tempY;
            tempX = this.target.getPositionX() - this._previousPosition.x;
            tempY = this.target.getPositionY() - this._previousPosition.y;
            if (tempX !== 0 || tempY !== 0) {
                var locAccDiff = this._accumulatedDiff;
                tempX = locAccDiff.x + tempX;
                tempY = locAccDiff.y + tempY;
                locAccDiff.x = tempX;
                locAccDiff.y = tempY;
                newPos.x += tempX;
                newPos.y += tempY;
            }
        }
        this.updatePosition(newPos);
    },

    /**
     * reverse a new cc.CardinalSplineTo. <br />
     * Along the track of movement in the opposite.
     *
     * @return {cc.CardinalSplineTo}
     */
    reverse:function () {
        var reversePoints = cc.reverseControlPoints(this._points);
        return cc.cardinalSplineTo(this._duration, reversePoints, this._tension);
    },

    /**
     * update position of target
     *
     * @param {cc.Point} newPos
     */
    updatePosition:function (newPos) {
        this.target.setPosition(newPos);
        this._previousPosition = newPos;
    },

    /**
     * Points getter
     *
     * @return {Array}
     */
    getPoints:function () {
        return this._points;
    },

    /**
     * Points setter
     *
     * @param {Array} points
     */
    setPoints:function (points) {
        this._points = points;
    }
});

/**
 * creates an action with a Cardinal Spline array of points and tension.
 *
 * @function
 * @param {Number} duration
 * @param {Array} points array of control points
 * @param {Number} tension
 * @return {cc.CardinalSplineTo}
 *
 * @example
 * //create a cc.CardinalSplineTo
 * var action1 = cc.cardinalSplineTo(3, array, 0);
 */
cc.cardinalSplineTo = function (duration, points, tension) {
    return new cc.CardinalSplineTo(duration, points, tension);
};

/**
 * Please use cc.cardinalSplineTo instead. <br />
 * creates an action with a Cardinal Spline array of points and tension
 *
 * @function
 * @param {Number} duration
 * @param {Array} points array of control points
 * @param {Number} tension
 * @return {cc.CardinalSplineTo}
 * @static
 * @deprecated since v3.0 please use cc.cardinalSplineTo(duration, points, tension) instead.
 */
cc.CardinalSplineTo.create = cc.cardinalSplineTo;

/**
 * Cardinal Spline path. {@link http://en.wikipedia.org/wiki/Cubic_Hermite_spline#Cardinal_spline}
 * Relative coordinates.
 *
 * @class
 * @extends cc.CardinalSplineTo
 * @param {Number} duration
 * @param {Array} points
 * @param {Number} tension
 *
 * @example
 * //create a cc.CardinalSplineBy
 * var action1 = cc.cardinalSplineBy(3, array, 0);
 */
cc.CardinalSplineBy = cc.CardinalSplineTo.extend(/** @lends cc.CardinalSplineBy# */{
    _startPosition:null,

	/**
     * Constructor function, override it to extend the construction behavior, remember to call "this._super()" in the extended "ctor" function. <br />
	 * creates an action with a Cardinal Spline array of points and tension.
	 * @param {Number} duration
	 * @param {Array} points
	 * @param {Number} tension
	 */
    ctor:function (duration, points, tension) {
        cc.CardinalSplineTo.prototype.ctor.call(this);
        this._startPosition = cc.p(0, 0);

		tension !== undefined && this.initWithDuration(duration, points, tension);
    },

    /**
     * called before the action start. It will also set the target.
     *
     * @param {cc.Node} target
     */
    startWithTarget:function (target) {
        cc.CardinalSplineTo.prototype.startWithTarget.call(this, target);
        this._startPosition.x = target.getPositionX();
        this._startPosition.y = target.getPositionY();
    },

    /**
     * reverse a new cc.CardinalSplineBy
     *
     * @return {cc.CardinalSplineBy}
     */
    reverse:function () {
        var copyConfig = this._points.slice();
        var current;
        //
        // convert "absolutes" to "diffs"
        //
        var p = copyConfig[0];
        for (var i = 1; i < copyConfig.length; ++i) {
            current = copyConfig[i];
            copyConfig[i] = cc.pSub(current, p);
            p = current;
        }

        // convert to "diffs" to "reverse absolute"
        var reverseArray = cc.reverseControlPoints(copyConfig);

        // 1st element (which should be 0,0) should be here too
        p = reverseArray[ reverseArray.length - 1 ];
        reverseArray.pop();

        p.x = -p.x;
        p.y = -p.y;

        reverseArray.unshift(p);
        for (var i = 1; i < reverseArray.length; ++i) {
            current = reverseArray[i];
            current.x = -current.x;
            current.y = -current.y;
            current.x += p.x;
            current.y += p.y;
            reverseArray[i] = current;
            p = current;
        }
        return cc.cardinalSplineBy(this._duration, reverseArray, this._tension);
    },

    /**
     * update position of target
     *
     * @param {cc.Point} newPos
     */
    updatePosition:function (newPos) {
        var pos = this._startPosition;
        var posX = newPos.x + pos.x;
        var posY = newPos.y + pos.y;
	    this._previousPosition.x = posX;
	    this._previousPosition.y = posY;
	    this.target.setPosition(posX, posY);
    },

    /**
     * returns a new clone of the action
     *
     * @returns {cc.CardinalSplineBy}
     */
    clone:function () {
        var a = new cc.CardinalSplineBy();
        a.initWithDuration(this._duration, cc.copyControlPoints(this._points), this._tension);
        return a;
    }
});

/**
 * creates an action with a Cardinal Spline array of points and tension.
 *
 * @function
 * @param {Number} duration
 * @param {Array} points
 * @param {Number} tension
 *
 * @return {cc.CardinalSplineBy}
 */
cc.cardinalSplineBy = function (duration, points, tension) {
    return new cc.CardinalSplineBy(duration, points, tension);
};

/**
 * Please use cc.cardinalSplineBy instead.
 * creates an action with a Cardinal Spline array of points and tension.
 * @function
 * @param {Number} duration
 * @param {Array} points
 * @param {Number} tension
 * @return {cc.CardinalSplineBy}
 * @static
 * @deprecated since v3.0 please use cc.cardinalSplineBy(duration, points, tension);
 */
cc.CardinalSplineBy.create = cc.cardinalSplineBy;

/**
 * An action that moves the target with a CatmullRom curve to a destination point.<br/>
 * A Catmull Rom is a Cardinal Spline with a tension of 0.5.  <br/>
 * {@link http://en.wikipedia.org/wiki/Cubic_Hermite_spline#Catmull.E2.80.93Rom_spline}
 * Absolute coordinates.
 *
 * @class
 * @extends cc.CardinalSplineTo
 * @param {Number} dt
 * @param {Array} points
 *
 * @example
 * var action1 = cc.catmullRomTo(3, array);
 */
cc.CatmullRomTo = cc.CardinalSplineTo.extend(/** @lends cc.CatmullRomTo# */{

	/**
     * Constructor function, override it to extend the construction behavior, remember to call "this._super()" in the extended "ctor" function. <br />
	 * creates an action with a Cardinal Spline array of points and tension.
	 * @param {Number} dt
	 * @param {Array} points
	 */
	ctor: function(dt, points) {
		points && this.initWithDuration(dt, points);
	},

    /**
     * Initializes the action with a duration and an array of points
     *
     * @param {Number} dt
     * @param {Array} points
     */
    initWithDuration:function (dt, points) {
        return cc.CardinalSplineTo.prototype.initWithDuration.call(this, dt, points, 0.5);
    },

    /**
     * returns a new clone of the action
     * @returns {cc.CatmullRomTo}
     */
    clone:function () {
        var action = new cc.CatmullRomTo();
        action.initWithDuration(this._duration, cc.copyControlPoints(this._points));
        return action;
    }
});

/**
 * creates an action with a Cardinal Spline array of points and tension.
 *
 * @function
 * @param {Number} dt
 * @param {Array} points
 * @return {cc.CatmullRomTo}
 *
 * @example
 * var action1 = cc.catmullRomTo(3, array);
 */
cc.catmullRomTo = function (dt, points) {
    return new cc.CatmullRomTo(dt, points);
};
/**
 * Please use cc.catmullRomTo instead.
 * creates an action with a Cardinal Spline array of points and tension.
 *
 * @param {Number} dt
 * @param {Array} points
 * @return {cc.CatmullRomTo}
 * @static
 * @deprecated since v3.0 please use cc.catmullRomTo(dt, points) instead.
 */
cc.CatmullRomTo.create = cc.catmullRomTo;

/**
 * An action that moves the target with a CatmullRom curve by a certain distance.  <br/>
 * A Catmull Rom is a Cardinal Spline with a tension of 0.5.<br/>
 * http://en.wikipedia.org/wiki/Cubic_Hermite_spline#Catmull.E2.80.93Rom_spline
 * Relative coordinates.
 *
 * @class
 * @extends cc.CardinalSplineBy
 * @param {Number} dt
 * @param {Array} points
 *
 * @example
 * var action1 = cc.catmullRomBy(3, array);
 */
cc.CatmullRomBy = cc.CardinalSplineBy.extend({

	/**
     * Constructor function, override it to extend the construction behavior, remember to call "this._super()" in the extended "ctor" function. <br />
	 * Creates an action with a Cardinal Spline array of points and tension.
	 * @param {Number} dt
	 * @param {Array} points
	 */
	ctor: function(dt, points) {
		cc.CardinalSplineBy.prototype.ctor.call(this);
		points && this.initWithDuration(dt, points);
	},

    /**
     * initializes the action with a duration and an array of points
     *
     * @function
     * @param {Number} dt
     * @param {Array} points
     */
    initWithDuration:function (dt, points) {
        return cc.CardinalSplineTo.prototype.initWithDuration.call(this, dt, points, 0.5);
    },

    /**
     * returns a new clone of the action
     * @returns {cc.CatmullRomBy}
     */
    clone:function () {
        var action = new cc.CatmullRomBy();
        action.initWithDuration(this._duration, cc.copyControlPoints(this._points));
        return action;
    }
});

/**
 * Creates an action with a Cardinal Spline array of points and tension
 * @function
 * @param {Number} dt
 * @param {Array} points
 * @return {cc.CatmullRomBy}
 * @example
 * var action1 = cc.catmullRomBy(3, array);
 */
cc.catmullRomBy = function (dt, points) {
    return new cc.CatmullRomBy(dt, points);
};
/**
 * Please use cc.catmullRomBy instead
 * Creates an action with a Cardinal Spline array of points and tension
 * @static
 * @deprecated since v3.0 please cc.catmullRomBy(dt, points) instead.
 */
cc.CatmullRomBy.create = cc.catmullRomBy;
