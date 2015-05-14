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
 * cc.Waves3D action. <br />
 * Reference the test cases (Effects Advanced Test)
 * @class
 * @extends cc.Grid3DAction
 * @param {Number} duration
 * @param {cc.Size} gridSize
 * @param {Number} waves
 * @param {Number} amplitude
 */
cc.Waves3D = cc.Grid3DAction.extend(/** @lends cc.Waves3D# */{
    _waves: 0,
    _amplitude: 0,
    _amplitudeRate: 0,

	/**
     * Constructor function, override it to extend the construction behavior, remember to call "this._super()" in the extended "ctor" function. <br />
	 * Create a wave 3d action with duration, grid size, waves and amplitude.
	 * @param {Number} duration
	 * @param {cc.Size} gridSize
	 * @param {Number} waves
	 * @param {Number} amplitude
	 */
    ctor:function (duration, gridSize, waves, amplitude) {
        cc.GridAction.prototype.ctor.call(this);
		amplitude !== undefined && this.initWithDuration(duration, gridSize, waves, amplitude);
    },

    /**
     * get Amplitude
     * @return {Number}
     */
    getAmplitude:function () {
        return this._amplitude;
    },

    /**
     * set Amplitude
     * @param {Number} amplitude
     */
    setAmplitude:function (amplitude) {
        this._amplitude = amplitude;
    },

    /**
     * get Amplitude Rate
     * @return {Number}
     */
    getAmplitudeRate:function () {
        return this._amplitudeRate;
    },

    /**
     * set Amplitude Rate
     * @param {Number} amplitudeRate
     */
    setAmplitudeRate:function (amplitudeRate) {
        this._amplitudeRate = amplitudeRate;
    },

    /**
     * initializes an action with duration, grid size, waves and amplitude
     * @param {Number} duration
     * @param {cc.Size} gridSize
     * @param {Number} waves
     * @param {Number} amplitude
     * @return {Boolean}
     */
    initWithDuration:function (duration, gridSize, waves, amplitude) {
        if (cc.Grid3DAction.prototype.initWithDuration.call(this, duration, gridSize)) {
            this._waves = waves;
            this._amplitude = amplitude;
            this._amplitudeRate = 1.0;
            return true;
        }
        return false;
    },

    /**
     * Called once per frame. Time is the number of seconds of a frame interval.
     *
     * @param {Number}  dt
     */
    update:function (dt) {
        var locGridSize = this._gridSize;
        var locAmplitude = this._amplitude, locPos = cc.p(0, 0);
        var locAmplitudeRate = this._amplitudeRate, locWaves = this._waves;
        for (var i = 0; i < locGridSize.width + 1; ++i) {
            for (var j = 0; j < locGridSize.height + 1; ++j) {
                locPos.x = i;
                locPos.y = j;
                var v = this.originalVertex(locPos);
                v.z += (Math.sin(Math.PI * dt * locWaves * 2 + (v.y + v.x) * 0.01) * locAmplitude * locAmplitudeRate);
                //cc.log("v.z offset is" + (Math.sin(Math.PI * dt * this._waves * 2 + (v.y + v.x) * 0.01) * this._amplitude * this._amplitudeRate));
                this.setVertex(locPos, v);
            }
        }
    }
});

/**
 * Create a wave 3d action with duration, grid size, waves and amplitude.
 * @function
 * @param {Number} duration
 * @param {cc.Size} gridSize
 * @param {Number} waves
 * @param {Number} amplitude
 */
cc.waves3D = function (duration, gridSize, waves, amplitude) {
    return new cc.Waves3D(duration, gridSize, waves, amplitude);
};
/**
 * Please use cc.waves3D instead. <br />
 * Create a wave 3d action with duration, grid size, waves and amplitude.
 * @param {Number} duration
 * @param {cc.Size} gridSize
 * @param {Number} waves
 * @param {Number} amplitude
 * @static
 * @deprecated since v3.0 <br /> Please use cc.waves3D instead.
 */
cc.Waves3D.create = cc.waves3D;

/**
 * cc.FlipX3D action. <br />
 * Flip around. <br />
 * Reference the test cases (Effects Test)
 * @class
 * @extends cc.Grid3DAction
 * @param {Number} duration
 */
cc.FlipX3D = cc.Grid3DAction.extend(/** @lends cc.FlipX3D# */{

	/**
     * Constructor function, override it to extend the construction behavior, remember to call "this._super()" in the extended "ctor" function. <br />
	 * Create a Flip X 3D action with duration.
	 * @param {Number} duration
	 */
	ctor: function(duration) {
		if (duration !== undefined)
			cc.GridAction.prototype.ctor.call(this, duration, cc.size(1, 1));
		else cc.GridAction.prototype.ctor.call(this);
	},

    /**
     * initializes the action with duration
     * @param {Number} duration
     * @return {Boolean}
     */
    initWithDuration:function (duration) {
        return cc.Grid3DAction.prototype.initWithDuration.call(this, duration, cc.size(1, 1));
    },

    /**
     * initializes the action with gridSize and duration
     * @param {cc.Size} gridSize
     * @param {Number} duration
     * @return {Boolean}
     */
    initWithSize:function (gridSize, duration) {
        if (gridSize.width !== 1 || gridSize.height !== 1) {
            // Grid size must be (1,1)
            cc.log("Grid size must be (1,1)");
            return false;
        }
        return  cc.Grid3DAction.prototype.initWithDuration.call(this, duration, gridSize);
    },

    /**
     * Called once per frame. Time is the number of seconds of a frame interval.
     *
     * @param {Number}  dt
     */
    update:function (dt) {
        var angle = Math.PI * dt; // 180 degrees
        var mz = Math.sin(angle);
        angle = angle / 2.0; // x calculates degrees from 0 to 90
        var mx = Math.cos(angle);

        var diff = new cc.Vertex3F();
        var tempVer = cc.p(0, 0);
        tempVer.x = tempVer.y = 1;
        var v0 = this.originalVertex(tempVer);
        tempVer.x = tempVer.y = 0;
        var v1 = this.originalVertex(tempVer);

        var x0 = v0.x;
        var x1 = v1.x;
        var x;
        var a, b, c, d;

        if (x0 > x1) {
            // Normal Grid
            a = cc.p(0, 0);
            b = cc.p(0, 1);
            c = cc.p(1, 0);
            d = cc.p(1, 1);
            x = x0;
        } else {
            // Reversed Grid
            c = cc.p(0, 0);
            d = cc.p(0, 1);
            a = cc.p(1, 0);
            b = cc.p(1, 1);
            x = x1;
        }

        diff.x = ( x - x * mx );
        diff.z = Math.abs(parseFloat((x * mz) / 4.0));

        // bottom-left
        var v = this.originalVertex(a);
        v.x = diff.x;
        v.z += diff.z;
        this.setVertex(a, v);

        // upper-left
        v = this.originalVertex(b);
        v.x = diff.x;
        v.z += diff.z;
        this.setVertex(b, v);

        // bottom-right
        v = this.originalVertex(c);
        v.x -= diff.x;
        v.z -= diff.z;
        this.setVertex(c, v);

        // upper-right
        v = this.originalVertex(d);
        v.x -= diff.x;
        v.z -= diff.z;
        this.setVertex(d, v);
    }
});

/**
 * Create a Flip X 3D action with duration. <br />
 * Flip around.
 * @function
 * @param {Number} duration
 * @return {cc.FlipX3D}
 */
cc.flipX3D = function (duration) {
    return new cc.FlipX3D(duration);
};

/**
 * Please use cc.flipX3D instead. <br />
 * Create a Flip X 3D action with duration. <br />
 * Flip around.
 * @param {Number} duration
 * @return {cc.FlipX3D}
 * @static
 * @deprecated since v3.0 <br /> Please use cc.flipX3D instead.
 */
cc.FlipX3D.create = cc.flipX3D;

/**
 * cc.FlipY3D action. <br />
 * Upside down. <br />
 * Reference the test cases (Effects Test)
 * @class
 * @extends cc.FlipX3D
 * @param {Number} duration
 */
cc.FlipY3D = cc.FlipX3D.extend(/** @lends cc.FlipY3D# */{

	/**
     * Constructor function, override it to extend the construction behavior, remember to call "this._super()" in the extended "ctor" function. <br />
	 * Create a flip Y 3d action with duration.
	 * @param {Number} duration
	 */
	ctor: function(duration) {
		if (duration !== undefined)
			cc.GridAction.prototype.ctor.call(this, duration, cc.size(1, 1));
		else cc.GridAction.prototype.ctor.call(this);
	},

    /**
     * Called once per frame. Time is the number of seconds of a frame interval.
     *
     * @param {Number}  dt
     */
    update:function (dt) {
        var angle = Math.PI * dt; // 180 degrees
        var mz = Math.sin(angle);
        angle = angle / 2.0;     // x calculates degrees from 0 to 90
        var my = Math.cos(angle);

        var diff = new cc.Vertex3F();

        var tempP = cc.p(0, 0);
        tempP.x = tempP.y = 1;
        var v0 = this.originalVertex(tempP);
        tempP.x = tempP.y = 0;
        var v1 = this.originalVertex(tempP);

        var y0 = v0.y;
        var y1 = v1.y;
        var y;
        var a, b, c, d;

        if (y0 > y1) {
            // Normal Grid
            a = cc.p(0, 0);
            b = cc.p(0, 1);
            c = cc.p(1, 0);
            d = cc.p(1, 1);
            y = y0;
        } else {
            // Reversed Grid
            b = cc.p(0, 0);
            a = cc.p(0, 1);
            d = cc.p(1, 0);
            c = cc.p(1, 1);
            y = y1;
        }

        diff.y = y - y * my;
        diff.z = Math.abs(parseFloat(y * mz) / 4.0);

        // bottom-left
        var v = this.originalVertex(a);
        v.y = diff.y;
        v.z += diff.z;
        this.setVertex(a, v);

        // upper-left
        v = this.originalVertex(b);
        v.y -= diff.y;
        v.z -= diff.z;
        this.setVertex(b, v);

        // bottom-right
        v = this.originalVertex(c);
        v.y = diff.y;
        v.z += diff.z;
        this.setVertex(c, v);

        // upper-right
        v = this.originalVertex(d);
        v.y -= diff.y;
        v.z -= diff.z;
        this.setVertex(d, v);
    }
});

/**
 * Create a flip Y 3d action with duration. <br />
 * Upside down.
 * @function
 * @param {Number} duration
 * @return {cc.FlipY3D}
 */
cc.flipY3D = function (duration) {
    return new cc.FlipY3D(duration);
};

/**
 * Please use cc.flipY3D instead. <br />
 * Create a flip Y 3d action with duration.
 * @param {Number} duration
 * @return {cc.FlipY3D}
 * @static
 * @deprecated since v3.0 <br /> Please use cc.flipY3D instead.
 */
cc.FlipY3D.create = cc.flipY3D;

/**
 * cc.Lens3D action. <br />
 * Upside down. <br />
 * Reference the test cases (Effects Test)
 * @class
 * @extends cc.Grid3DAction
 * @param {Number} duration
 * @param {cc.Size} gridSize
 * @param {cc.Point} position
 * @param {Number} radius
 */
cc.Lens3D = cc.Grid3DAction.extend(/** @lends cc.Lens3D# */{
    //lens center position
    _position:null,
    _radius:0,
    //lens effect. Defaults to 0.7 - 0 means no effect, 1 is very strong effect
    _lensEffect:0,
    //lens is concave. (true = concave, false = convex) default is convex i.e. false
    _concave:false,
    _dirty:false,

	/**
     * Constructor function, override it to extend the construction behavior, remember to call "this._super()" in the extended "ctor" function. <br />
	 * creates a lens 3d action with center position, radius.
	 * @param {Number} duration
	 * @param {cc.Size} gridSize
	 * @param {cc.Point} position
	 * @param {Number} radius
	 */
    ctor:function (duration, gridSize, position, radius) {
        cc.GridAction.prototype.ctor.call(this);

        this._position = cc.p(0, 0);
		radius !== undefined && this.initWithDuration(duration, gridSize, position, radius);
    },

    /**
     * Get lens center position
     * @return {Number}
     */
    getLensEffect:function () {
        return this._lensEffect;
    },

    /**
     * Set lens center position
     * @param {Number} lensEffect
     */
    setLensEffect:function (lensEffect) {
        this._lensEffect = lensEffect;
    },

    /**
     * Set whether lens is concave
     * @param {Boolean} concave
     */
    setConcave:function (concave) {
        this._concave = concave;
    },

    /**
     * get Position
     * @return {cc.Point}
     */
    getPosition:function () {
        return this._position;
    },

    /**
     * set Position
     * @param {cc.Point} position
     */
    setPosition:function (position) {
        if (!cc.pointEqualToPoint(position, this._position)) {
            this._position.x = position.x;
            this._position.y = position.y;
            this._dirty = true;
        }
    },

    /**
     * initializes the action with center position, radius, a grid size and duration
     * @param {Number} duration
     * @param {cc.Size} gridSize
     * @param {cc.Point} position
     * @param {Number} radius
     * @return {Boolean}
     */
    initWithDuration:function (duration, gridSize, position, radius) {
        if (cc.Grid3DAction.prototype.initWithDuration.call(this, duration, gridSize)) {
            this.setPosition(position);
            this._radius = radius;
            this._lensEffect = 0.7;
            this._dirty = true;
            return true;
        }
        return false;
    },

    /**
     * Called once per frame. Time is the number of seconds of a frame interval.
     *
     * @param {Number}  dt
     */
    update:function (dt) {
        if (this._dirty) {
            var locGridSizeWidth = this._gridSize.width, locGridSizeHeight = this._gridSize.height;
            var locRadius = this._radius, locLensEffect = this._lensEffect;
            var locPos = cc.p(0, 0);
            var vect = cc.p(0, 0);
            var v, r, l, new_r, pre_log;
            for (var i = 0; i < locGridSizeWidth + 1; ++i) {
                for (var j = 0; j < locGridSizeHeight + 1; ++j) {
                    locPos.x = i;
                    locPos.y = j;
                    v = this.originalVertex(locPos);
                    vect.x = this._position.x - v.x;
                    vect.y = this._position.y - v.y;
                    r = cc.pLength(vect);

                    if (r < locRadius) {
                        r = locRadius - r;
                        pre_log = r / locRadius;
                        if (pre_log === 0)
                            pre_log = 0.001;

                        l = Math.log(pre_log) * locLensEffect;
                        new_r = Math.exp(l) * locRadius;

                        r = cc.pLength(vect);
                        if (r > 0) {
                            vect.x = vect.x / r;
                            vect.y = vect.y / r;

                            vect.x = vect.x * new_r;
                            vect.y = vect.y * new_r;
                            v.z += cc.pLength(vect) * locLensEffect;
                        }
                    }
                    this.setVertex(locPos, v);
                }
            }
            this._dirty = false;
        }
    }
});

/**
 * creates a lens 3d action with center position, radius
 * @function
 * @param {Number} duration
 * @param {cc.Size} gridSize
 * @param {cc.Point} position
 * @param {Number} radius
 * @return {cc.Lens3D}
 */
cc.lens3D = function (duration, gridSize, position, radius) {
    return new cc.Lens3D(duration, gridSize, position, radius);
};

/**
 * Please use cc.lens3D instead
 * creates a lens 3d action with center position, radius
 * @param {Number} duration
 * @param {cc.Size} gridSize
 * @param {cc.Point} position
 * @param {Number} radius
 * @return {cc.Lens3D}
 * @static
 * @deprecated since v3.0 <br /> Please use cc.lens3D instead.
 */
cc.Lens3D.create = cc.lens3D;

/**
 * cc.Ripple3D action. <br />
 * Reference the test cases (Effects Test)
 * @class
 * @extends cc.Grid3DAction
 * @param {Number} duration
 * @param {cc.Size} gridSize
 * @param {cc.Point} position
 * @param {Number} radius
 * @param {Number} waves
 * @param {Number} amplitude
 */
cc.Ripple3D = cc.Grid3DAction.extend(/** @lends cc.Ripple3D# */{
    /* center position */
    _position: null,
    _radius: 0,
    _waves: 0,
    _amplitude: 0,
    _amplitudeRate: 0,

	/**
     * Constructor function, override it to extend the construction behavior, remember to call "this._super()" in the extended "ctor" function. <br />
	 * creates a ripple 3d action with radius, number of waves, amplitude.
	 * @param {Number} duration
	 * @param {cc.Size} gridSize
	 * @param {cc.Point} position
	 * @param {Number} radius
	 * @param {Number} waves
	 * @param {Number} amplitude
	 */
    ctor:function (duration, gridSize, position, radius, waves, amplitude) {
        cc.GridAction.prototype.ctor.call(this);

        this._position = cc.p(0, 0);
		amplitude !== undefined && this.initWithDuration(duration, gridSize, position, radius, waves, amplitude);
    },

    /**
     * get center position
     * @return {cc.Point}
     */
    getPosition:function () {
        return this._position;
    },

    /**
     * set center position
     * @param {cc.Point} position
     */
    setPosition:function (position) {
        this._position.x = position.x;
        this._position.y = position.y;
    },

    /**
     * get Amplitude
     * @return {Number}
     */
    getAmplitude:function () {
        return this._amplitude;
    },

    /**
     * set Amplitude
     * @param {Number} amplitude
     */
    setAmplitude:function (amplitude) {
        this._amplitude = amplitude;
    },

    /**
     * get Amplitude rate
     * @return {*}
     */
    getAmplitudeRate:function () {
        return this._amplitudeRate;
    },

    /**
     * get amplitude rate
     * @param {Number} amplitudeRate
     */
    setAmplitudeRate:function (amplitudeRate) {
        this._amplitudeRate = amplitudeRate;
    },

    /**
     * initializes the action with radius, number of waves, amplitude, a grid size and duration
     * @param {Number} duration
     * @param {cc.Size} gridSize
     * @param {cc.Point} position
     * @param {Number} radius
     * @param {Number} waves
     * @param {Number} amplitude
     * @return {Boolean}
     */
    initWithDuration:function (duration, gridSize, position, radius, waves, amplitude) {
        if (cc.Grid3DAction.prototype.initWithDuration.call(this, duration, gridSize)) {
            this.setPosition(position);
            this._radius = radius;
            this._waves = waves;
            this._amplitude = amplitude;
            this._amplitudeRate = 1.0;
            return true;
        }
        return false;
    },

    /**
     * Called once per frame. Time is the number of seconds of a frame interval.
     *
     * @param {Number}  dt
     */
    update:function (dt) {
        var locGridSizeWidth = this._gridSize.width, locGridSizeHeight = this._gridSize.height;
        var locPos = cc.p(0, 0), locRadius = this._radius;
        var locWaves = this._waves, locAmplitude = this._amplitude, locAmplitudeRate = this._amplitudeRate;
        var v, r, tempPos = cc.p(0, 0);
        for (var i = 0; i < (locGridSizeWidth + 1); ++i) {
            for (var j = 0; j < (locGridSizeHeight + 1); ++j) {
                locPos.x = i;
                locPos.y = j;
                v = this.originalVertex(locPos);

                tempPos.x = this._position.x - v.x;
                tempPos.y = this._position.y - v.y;
                r = cc.pLength(tempPos);

                if (r < locRadius) {
                    r = locRadius - r;
                    var rate = Math.pow(r / locRadius, 2);
                    v.z += (Math.sin(dt * Math.PI * locWaves * 2 + r * 0.1) * locAmplitude * locAmplitudeRate * rate);
                }
                this.setVertex(locPos, v);
            }
        }
    }
});

/**
 * creates a ripple 3d action with radius, number of waves, amplitude
 * @function
 * @param {Number} duration
 * @param {cc.Size} gridSize
 * @param {cc.Point} position
 * @param {Number} radius
 * @param {Number} waves
 * @param {Number} amplitude
 * @return {cc.Ripple3D}
 */
cc.ripple3D = function (duration, gridSize, position, radius, waves, amplitude) {
    return new cc.Ripple3D(duration, gridSize, position, radius, waves, amplitude);
};

/**
 * Please use cc.ripple3D instead
 * creates a ripple 3d action with radius, number of waves, amplitude
 * @param {Number} duration
 * @param {cc.Size} gridSize
 * @param {cc.Point} position
 * @param {Number} radius
 * @param {Number} waves
 * @param {Number} amplitude
 * @return {cc.Ripple3D}
 * @static
 * @deprecated since v3.0 <br /> Please use cc.ripple3D instead.
 */
cc.Ripple3D.create = cc.ripple3D;

/**
 * cc.Shaky3D action. <br />
 * Reference the test cases (Effects Test)
 * @class
 * @extends cc.Grid3DAction
 * @param {Number} duration
 * @param {cc.Size} gridSize
 * @param {Number} range
 * @param {Boolean} shakeZ
 */
cc.Shaky3D = cc.Grid3DAction.extend(/** @lends cc.Shaky3D# */{
    _randRange: 0,
    _shakeZ: false,

	/**
     * Constructor function, override it to extend the construction behavior, remember to call "this._super()" in the extended "ctor" function. <br />
	 * Create a shaky3d action with a range, shake Z vertices.
	 * @param {Number} duration
	 * @param {cc.Size} gridSize
	 * @param {Number} range
	 * @param {Boolean} shakeZ
	 */
    ctor:function (duration, gridSize, range, shakeZ) {
        cc.GridAction.prototype.ctor.call(this);
		shakeZ !== undefined && this.initWithDuration(duration, gridSize, range, shakeZ);
    },

    /**
     * initializes the action with a range, shake Z vertices, a grid and duration
     * @param {Number} duration
     * @param {cc.Size} gridSize
     * @param {Number} range
     * @param {Boolean} shakeZ
     * @return {Boolean}
     */
    initWithDuration:function (duration, gridSize, range, shakeZ) {
        if (cc.Grid3DAction.prototype.initWithDuration.call(this, duration, gridSize)) {
            this._randRange = range;
            this._shakeZ = shakeZ;
            return true;
        }
        return false;
    },

    /**
     * Called once per frame. Time is the number of seconds of a frame interval.
     *
     * @param {Number}  dt
     */
    update:function (dt) {
        var locGridSizeWidth = this._gridSize.width, locGridSizeHeight = this._gridSize.height;
        var locRandRange = this._randRange, locShakeZ = this._shakeZ, locP = cc.p(0, 0);
        var v;
        for (var i = 0; i < (locGridSizeWidth + 1); ++i) {
            for (var j = 0; j < (locGridSizeHeight + 1); ++j) {
                locP.x = i;
                locP.y = j;
                v = this.originalVertex(locP);
                v.x += (cc.rand() % (locRandRange * 2)) - locRandRange;
                v.y += (cc.rand() % (locRandRange * 2)) - locRandRange;
                if (locShakeZ)
                    v.z += (cc.rand() % (locRandRange * 2)) - locRandRange;
                this.setVertex(locP, v);
            }
        }
    }
});

/**
 * creates the action with a range, shake Z vertices, a grid and duration
 * @function
 * @param {Number} duration
 * @param {cc.Size} gridSize
 * @param {Number} range
 * @param {Boolean} shakeZ
 * @return {cc.Shaky3D}
 */
cc.shaky3D = function (duration, gridSize, range, shakeZ) {
    return new cc.Shaky3D(duration, gridSize, range, shakeZ);
};

/**
 * Please use cc.shaky3D instead
 * creates the action with a range, shake Z vertices, a grid and duration
 * @param {Number} duration
 * @param {cc.Size} gridSize
 * @param {Number} range
 * @param {Boolean} shakeZ
 * @return {cc.Shaky3D}
 * @static
 * @deprecated since v3.0 <br /> Please use cc.shaky3D instead.
 */
cc.Shaky3D.create = cc.shaky3D;

/**
 * cc.Liquid action. <br />
 * Reference the test cases (Effects Test)
 * @class
 * @extends cc.Grid3DAction
 * @param {Number} duration
 * @param {cc.Size} gridSize
 * @param {Number} waves
 * @param {Number} amplitude
 */
cc.Liquid = cc.Grid3DAction.extend(/** @lends cc.Liquid# */{
    _waves: 0,
    _amplitude: 0,
    _amplitudeRate: 0,

	/**
     * Constructor function, override it to extend the construction behavior, remember to call "this._super()" in the extended "ctor" function. <br />
	 * Create a liquid action with amplitude, a grid and duration.
	 * @param {Number} duration
	 * @param {cc.Size} gridSize
	 * @param {Number} waves
	 * @param {Number} amplitude
	 */
    ctor: function (duration, gridSize, waves, amplitude) {
        cc.GridAction.prototype.ctor.call(this);
		amplitude !== undefined && this.initWithDuration(duration, gridSize, waves, amplitude);
    },

    /**
     * get amplitude
     * @return {Number}
     */
    getAmplitude:function () {
        return this._amplitude;
    },

    /**
     * set amplitude
     * @param {Number} amplitude
     */
    setAmplitude:function (amplitude) {
        this._amplitude = amplitude;
    },

    /**
     * get amplitude rate
     * @return {Number}
     */
    getAmplitudeRate:function () {
        return this._amplitudeRate;
    },

    /**
     * set amplitude rate
     * @param {Number} amplitudeRate
     */
    setAmplitudeRate:function (amplitudeRate) {
        this._amplitudeRate = amplitudeRate;
    },

    /**
     * initializes the action with amplitude, a grid and duration
     * @param {Number} duration
     * @param {cc.Size} gridSize
     * @param {Number} waves
     * @param {Number} amplitude
     * @return {Boolean}
     */
    initWithDuration:function (duration, gridSize, waves, amplitude) {
        if (cc.Grid3DAction.prototype.initWithDuration.call(this, duration, gridSize)) {
            this._waves = waves;
            this._amplitude = amplitude;
            this._amplitudeRate = 1.0;
            return true;
        }
        return false;
    },

    /**
     * Called once per frame. Time is the number of seconds of a frame interval.
     *
     * @param {Number}  dt
     */
    update:function (dt) {
        var locSizeWidth = this._gridSize.width, locSizeHeight = this._gridSize.height, locPos = cc.p(0, 0);
        var locWaves = this._waves, locAmplitude = this._amplitude, locAmplitudeRate = this._amplitudeRate;
        var v;
        for (var i = 1; i < locSizeWidth; ++i) {
            for (var j = 1; j < locSizeHeight; ++j) {
                locPos.x = i;
                locPos.y = j;
                v = this.originalVertex(locPos);
                v.x = (v.x + (Math.sin(dt * Math.PI * locWaves * 2 + v.x * .01) * locAmplitude * locAmplitudeRate));
                v.y = (v.y + (Math.sin(dt * Math.PI * locWaves * 2 + v.y * .01) * locAmplitude * locAmplitudeRate));
                this.setVertex(locPos, v);
            }
        }
    }
});

/**
 * creates the action with amplitude, a grid and duration
 * @function
 * @param {Number} duration
 * @param {cc.Size} gridSize
 * @param {Number} waves
 * @param {Number} amplitude
 * @return {cc.Liquid}
 */
cc.liquid = function (duration, gridSize, waves, amplitude) {
    return new cc.Liquid(duration, gridSize, waves, amplitude);
};

/**
 * Please use cc.liquid instead
 * creates the action with amplitude, a grid and duration
 * @param {Number} duration
 * @param {cc.Size} gridSize
 * @param {Number} waves
 * @param {Number} amplitude
 * @return {cc.Liquid}
 * @static
 * @deprecated since v3.0 <br /> Please use cc.liquid instead.
 */
cc.Liquid.create = cc.liquid;

/**
 * cc.Waves action. <br />
 * Reference the test cases (Effects Test)
 * @class
 * @extends cc.Grid3DAction
 * @param {Number} duration
 * @param {cc.Size} gridSize
 * @param {Number} waves
 * @param {Number} amplitude
 * @param {Boolean} horizontal
 * @param {Boolean} vertical
 */
cc.Waves = cc.Grid3DAction.extend(/** @lends cc.Waves# */{
    _waves: 0,
    _amplitude: 0,
    _amplitudeRate: 0,
    _vertical: false,
    _horizontal: false,

	/**
     * Constructor function, override it to extend the construction behavior, remember to call "this._super()" in the extended "ctor" function. <br />
	 * Create a wave action with amplitude, horizontal sin, vertical sin, a grid and duration.
	 * @param {Number} duration
	 * @param {cc.Size} gridSize
	 * @param {Number} waves
	 * @param {Number} amplitude
	 * @param {Boolean} horizontal
	 * @param {Boolean} vertical
	 */
    ctor: function (duration, gridSize, waves, amplitude, horizontal, vertical) {
        cc.GridAction.prototype.ctor.call(this);
		vertical !== undefined && this.initWithDuration(duration, gridSize, waves, amplitude, horizontal, vertical);
    },

    /**
     * get amplitude
     * @return {Number}
     */
    getAmplitude:function () {
        return this._amplitude;
    },

    /**
     * set amplitude
     * @param {Number} amplitude
     */
    setAmplitude:function (amplitude) {
        this._amplitude = amplitude;
    },

    /**
     * get amplitude rate
     * @return {Number}
     */
    getAmplitudeRate:function () {
        return this._amplitudeRate;
    },

    /**
     * set amplitude rate
     * @param {Number} amplitudeRate
     */
    setAmplitudeRate:function (amplitudeRate) {
        this._amplitudeRate = amplitudeRate;
    },

    /**
     * initializes the action with amplitude, horizontal sin, vertical sin, a grid and duration
     * @param {Number} duration
     * @param {cc.Size} gridSize
     * @param {Number} waves
     * @param {Number} amplitude
     * @param {Boolean} horizontal
     * @param {Boolean} vertical
     * @return {Boolean}
     */
    initWithDuration:function (duration, gridSize, waves, amplitude, horizontal, vertical) {
        if (cc.Grid3DAction.prototype.initWithDuration.call(this, duration, gridSize)) {
            this._waves = waves;
            this._amplitude = amplitude;
            this._amplitudeRate = 1.0;
            this._horizontal = horizontal;
            this._vertical = vertical;
            return true;
        }
        return false;
    },

    /**
     * Called once per frame. Time is the number of seconds of a frame interval.
     *
     * @param {Number}  dt
     */
    update:function (dt) {
        var locSizeWidth = this._gridSize.width, locSizeHeight = this._gridSize.height, locPos = cc.p(0, 0);
        var locVertical = this._vertical, locHorizontal = this._horizontal;
        var locWaves = this._waves, locAmplitude = this._amplitude, locAmplitudeRate = this._amplitudeRate;
        var v;
        for (var i = 0; i < locSizeWidth + 1; ++i) {
            for (var j = 0; j < locSizeHeight + 1; ++j) {
                locPos.x = i;
                locPos.y = j;
                v = this.originalVertex(locPos);
                if (locVertical)
                    v.x = (v.x + (Math.sin(dt * Math.PI * locWaves * 2 + v.y * .01) * locAmplitude * locAmplitudeRate));
                if (locHorizontal)
                    v.y = (v.y + (Math.sin(dt * Math.PI * locWaves * 2 + v.x * .01) * locAmplitude * locAmplitudeRate));
                this.setVertex(locPos, v);
            }
        }
    }
});

/**
 * initializes the action with amplitude, horizontal sin, vertical sin, a grid and duration
 * @function
 * @param {Number} duration
 * @param {cc.Size} gridSize
 * @param {Number} waves
 * @param {Number} amplitude
 * @param {Boolean} horizontal
 * @param {Boolean} vertical
 * @return {cc.Waves}
 */
cc.waves = function (duration, gridSize, waves, amplitude, horizontal, vertical) {
    return new cc.Waves(duration, gridSize, waves, amplitude, horizontal, vertical);
};

/**
 * Please use cc.waves instead
 * initializes the action with amplitude, horizontal sin, vertical sin, a grid and duration
 * @param {Number} duration
 * @param {cc.Size} gridSize
 * @param {Number} waves
 * @param {Number} amplitude
 * @param {Boolean} horizontal
 * @param {Boolean} vertical
 * @return {cc.Waves}
 * @static
 * @deprecated since v3.0 <br /> Please use cc.waves instead.
 */
cc.Waves.create = cc.waves;

/** @brief  */
/**
 * cc.Twirl action. <br />
 * Reference the test cases (Effects Test)
 * @class
 * @extends cc.Grid3DAction
 * @param {Number} duration
 * @param {cc.Size} gridSize
 * @param {cc.Point} position
 * @param {Number} twirls
 * @param {Number} amplitude
 */
cc.Twirl = cc.Grid3DAction.extend(/** @lends cc.Twirl# */{
    /* twirl center */
    _position: null,
    _twirls: 0,
    _amplitude: 0,
    _amplitudeRate: 0,

	/**
     * Constructor function, override it to extend the construction behavior, remember to call "this._super()" in the extended "ctor" function. <br />
	 * Create a grid 3d action with center position, number of twirls, amplitude, a grid size and duration.
	 * @param {Number} duration
	 * @param {cc.Size} gridSize
	 * @param {cc.Point} position
	 * @param {Number} twirls
	 * @param {Number} amplitude
	 */
    ctor:function (duration, gridSize, position, twirls, amplitude) {
        cc.GridAction.prototype.ctor.call(this);

        this._position = cc.p(0, 0);
		amplitude !== undefined && this.initWithDuration(duration, gridSize, position, twirls, amplitude);
    },

    /**
     * get twirl center
     * @return {cc.Point}
     */
    getPosition:function () {
        return this._position;
    },

    /**
     * set twirl center
     * @param {cc.Point} position
     */
    setPosition:function (position) {
        this._position.x = position.x;
        this._position.y = position.y;
    },

    /**
     * get amplitude
     * @return {Number}
     */
    getAmplitude:function () {
        return this._amplitude;
    },

    /**
     * set amplitude
     * @param {Number} amplitude
     */
    setAmplitude:function (amplitude) {
        this._amplitude = amplitude;
    },

    /**
     * get amplitude rate
     * @return {Number}
     */
    getAmplitudeRate:function () {
        return this._amplitudeRate;
    },

    /**
     * set amplitude rate
     * @param {Number} amplitudeRate
     */
    setAmplitudeRate:function (amplitudeRate) {
        this._amplitudeRate = amplitudeRate;
    },

    /** initializes the action with center position, number of twirls, amplitude, a grid size and duration */
    initWithDuration:function (duration, gridSize, position, twirls, amplitude) {
        if (cc.Grid3DAction.prototype.initWithDuration.call(this, duration, gridSize)) {
            this.setPosition(position);
            this._twirls = twirls;
            this._amplitude = amplitude;
            this._amplitudeRate = 1.0;
            return true;
        }
        return false;
    },

    /**
     * Called once per frame. Time is the number of seconds of a frame interval.
     *
     * @param {Number}  dt
     */
    update:function (dt) {
        var c = this._position;
        var locSizeWidth = this._gridSize.width, locSizeHeight = this._gridSize.height, locPos = cc.p(0, 0);
        var amp = 0.1 * this._amplitude * this._amplitudeRate;
        var locTwirls = this._twirls;
        var v, a, dX, dY, avg = cc.p(0, 0);
        for (var i = 0; i < (locSizeWidth + 1); ++i) {
            for (var j = 0; j < (locSizeHeight + 1); ++j) {
                locPos.x = i;
                locPos.y = j;
                v = this.originalVertex(locPos);

                avg.x = i - (locSizeWidth / 2.0);
                avg.y = j - (locSizeHeight / 2.0);

                a = cc.pLength(avg) * Math.cos(Math.PI / 2.0 + dt * Math.PI * locTwirls * 2) * amp;

                dX = Math.sin(a) * (v.y - c.y) + Math.cos(a) * (v.x - c.x);
                dY = Math.cos(a) * (v.y - c.y) - Math.sin(a) * (v.x - c.x);

                v.x = c.x + dX;
                v.y = c.y + dY;

                this.setVertex(locPos, v);
            }
        }
    }
});

/**
 * creates the action with center position, number of twirls, amplitude, a grid size and duration
 * @function
 * @param {Number} duration
 * @param {cc.Size} gridSize
 * @param {cc.Point} position
 * @param {Number} twirls
 * @param {Number} amplitude
 * @return {cc.Twirl}
 */
cc.twirl = function (duration, gridSize, position, twirls, amplitude) {
    return new cc.Twirl(duration, gridSize, position, twirls, amplitude);
};

/**
 * Please use cc.twirl instead
 * creates the action with center position, number of twirls, amplitude, a grid size and duration
 * @param {Number} duration
 * @param {cc.Size} gridSize
 * @param {cc.Point} position
 * @param {Number} twirls
 * @param {Number} amplitude
 * @return {cc.Twirl}
 * @static
 * @deprecated since v3.0 <br /> Please use cc.twirl instead.
 */
cc.Twirl.create = cc.twirl;