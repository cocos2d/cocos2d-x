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
 * Base class for cc.Camera actions
 * @class
 * @extends cc.ActionInterval
 */
cc.ActionCamera = cc.ActionInterval.extend(/** @lends cc.ActionCamera# */{
    _centerXOrig:0,
    _centerYOrig:0,
    _centerZOrig:0,
    _eyeXOrig:0,
    _eyeYOrig:0,
    _eyeZOrig:0,
    _upXOrig:0,
    _upYOrig:0,
    _upZOrig:0,

    /**
     * Constructor function, override it to extend the construction behavior, remember to call "this._super()" in the extended "ctor" function.
     */
    ctor:function(){
        var _t = this;
        cc.ActionInterval.prototype.ctor.call(_t);

        _t._centerXOrig=0;
        _t._centerYOrig=0;
        _t._centerZOrig=0;
        _t._eyeXOrig=0;
        _t._eyeYOrig=0;
        _t._eyeZOrig=0;
        _t._upXOrig=0;
        _t._upYOrig=0;
        _t._upZOrig=0;
    },

    /**
     * called before the action start. It will also set the target.
     *
     * @param {cc.Node} target
     */
    startWithTarget:function (target) {
        var _t = this;
        cc.ActionInterval.prototype.startWithTarget.call(_t, target);

        var camera = target.getCamera();
        var centerXYZ = camera.getCenter();
        _t._centerXOrig = centerXYZ.x;
        _t._centerYOrig = centerXYZ.y;
        _t._centerZOrig = centerXYZ.z;

        var eyeXYZ = camera.getEye();
        _t._eyeXOrig = eyeXYZ.x;
        _t._eyeYOrig = eyeXYZ.y;
        _t._eyeZOrig = eyeXYZ.z;

        var upXYZ = camera.getUp();
        _t._upXOrig = upXYZ.x;
        _t._upYOrig = upXYZ.y;
        _t._upZOrig = upXYZ.z;
    },

    /**
     * to copy object with deep copy.
     * returns a new clone of the action
     *
     * @returns {cc.ActionCamera}
     */
    clone:function(){
       return new cc.ActionCamera();
    },

    /**
     * returns a reversed action. <br />
     * For example: <br />
     * - The action will be x coordinates of 0 move to 100. <br />
     * - The reversed action will be x of 100 move to 0.
     * - Will be rewritten
     *
     */
    reverse:function () {
        return new cc.ReverseTime(this);
    }
});

/**
 * Orbits the camera around the center of the screen using spherical coordinates.
 *
 * @param {Number} t time
 * @param {Number} radius
 * @param {Number} deltaRadius
 * @param {Number} angleZ
 * @param {Number} deltaAngleZ
 * @param {Number} angleX
 * @param {Number} deltaAngleX
 *
 * @class
 * @extends cc.ActionCamera
 */
cc.OrbitCamera = cc.ActionCamera.extend(/** @lends cc.OrbitCamera# */{
    _radius: 0.0,
    _deltaRadius: 0.0,
    _angleZ: 0.0,
    _deltaAngleZ: 0.0,
    _angleX: 0.0,
    _deltaAngleX: 0.0,
    _radZ: 0.0,
    _radDeltaZ: 0.0,
    _radX: 0.0,
    _radDeltaX: 0.0,

	/**
     * Constructor function, override it to extend the construction behavior, remember to call "this._super()" in the extended "ctor" function. <br />
	 * creates a cc.OrbitCamera action with radius, delta-radius,  z, deltaZ, x, deltaX.
	 * @param {Number} t time
	 * @param {Number} radius
	 * @param {Number} deltaRadius
	 * @param {Number} angleZ
	 * @param {Number} deltaAngleZ
	 * @param {Number} angleX
	 * @param {Number} deltaAngleX
	 */
    ctor:function(t, radius, deltaRadius, angleZ, deltaAngleZ, angleX, deltaAngleX){
        cc.ActionCamera.prototype.ctor.call(this);

		deltaAngleX !== undefined && this.initWithDuration(t, radius, deltaRadius, angleZ, deltaAngleZ, angleX, deltaAngleX);
    },

    /**
     * initializes a cc.OrbitCamera action with radius, delta-radius,  z, deltaZ, x, deltaX
     * @param {Number} t time
     * @param {Number} radius
     * @param {Number} deltaRadius
     * @param {Number} angleZ
     * @param {Number} deltaAngleZ
     * @param {Number} angleX
     * @param {Number} deltaAngleX
     * @return {Boolean}
     */
    initWithDuration:function (t, radius, deltaRadius, angleZ, deltaAngleZ, angleX, deltaAngleX) {
        if (cc.ActionInterval.prototype.initWithDuration.call(this, t)) {
            var _t = this;
            _t._radius = radius;
            _t._deltaRadius = deltaRadius;
            _t._angleZ = angleZ;
            _t._deltaAngleZ = deltaAngleZ;
            _t._angleX = angleX;
            _t._deltaAngleX = deltaAngleX;

            _t._radDeltaZ = cc.degreesToRadians(deltaAngleZ);
            _t._radDeltaX = cc.degreesToRadians(deltaAngleX);
            return true;
        }
        return false;
    },

    /**
     * positions the camera according to spherical coordinates
     * @return {Object}
     */
    sphericalRadius:function () {
        var newRadius, zenith, azimuth;
        var camera = this.target.getCamera();
        var eyeXYZ = camera.getEye();
        var centerXYZ = camera.getCenter();

        var x = eyeXYZ.x - centerXYZ.x, y = eyeXYZ.y - centerXYZ.y, z = eyeXYZ.z - centerXYZ.z;

        var r = Math.sqrt(Math.pow(x, 2) + Math.pow(y, 2) + Math.pow(z, 2));
        var s = Math.sqrt(Math.pow(x, 2) + Math.pow(y, 2));
        if (s === 0.0)
            s = cc.FLT_EPSILON;
        if (r === 0.0)
            r = cc.FLT_EPSILON;

        zenith = Math.acos(z / r);
        if (x < 0)
            azimuth = Math.PI - Math.asin(y / s);
        else
            azimuth = Math.asin(y / s);
        newRadius = r / cc.Camera.getZEye();
        return {newRadius:newRadius, zenith:zenith, azimuth:azimuth};
    },

    /**
     * called before the action start. It will also set the target.
     *
     * @param {cc.Node} target
     */
    startWithTarget:function (target) {
        var _t = this;
        cc.ActionInterval.prototype.startWithTarget.call(_t, target);
        var retValue = _t.sphericalRadius();
        if (isNaN(_t._radius))
            _t._radius = retValue.newRadius;

        if (isNaN(_t._angleZ))
            _t._angleZ = cc.radiansToDegrees(retValue.zenith);

        if (isNaN(_t._angleX))
            _t._angleX = cc.radiansToDegrees(retValue.azimuth);

        _t._radZ = cc.degreesToRadians(_t._angleZ);
        _t._radX = cc.degreesToRadians(_t._angleX);
    },

    /**
     * to copy object with deep copy.
     * returns a new clone of the action
     *
     * @returns {cc.ActionCamera}
     */
    clone:function(){
        var a = new cc.OrbitCamera(), _t = this;
        a.initWithDuration(_t._duration, _t._radius, _t._deltaRadius, _t._angleZ, _t._deltaAngleZ, _t._angleX, _t._deltaAngleX);
        return a;
    },

    /**
     * Called once per frame. Time is the number of seconds of a frame interval.
     *
     * @param {Number}  dt
     */
    update:function (dt) {
        dt = this._computeEaseTime(dt);
        var r = (this._radius + this._deltaRadius * dt) * cc.Camera.getZEye();
        var za = this._radZ + this._radDeltaZ * dt;
        var xa = this._radX + this._radDeltaX * dt;

        var i = Math.sin(za) * Math.cos(xa) * r + this._centerXOrig;
        var j = Math.sin(za) * Math.sin(xa) * r + this._centerYOrig;
        var k = Math.cos(za) * r + this._centerZOrig;

        this.target.getCamera().setEye(i, j, k);
        this.target.setNodeDirty();
    }
});

/**
 * creates a cc.OrbitCamera action with radius, delta-radius,  z, deltaZ, x, deltaX
 * @function
 * @param {Number} t time
 * @param {Number} radius
 * @param {Number} deltaRadius
 * @param {Number} angleZ
 * @param {Number} deltaAngleZ
 * @param {Number} angleX
 * @param {Number} deltaAngleX
 * @return {cc.OrbitCamera}
 */
cc.orbitCamera = function (t, radius, deltaRadius, angleZ, deltaAngleZ, angleX, deltaAngleX) {
    return new cc.OrbitCamera(t, radius, deltaRadius, angleZ, deltaAngleZ, angleX, deltaAngleX);
};

/**
 * Please use cc.orbitCamera instead
 * creates a cc.OrbitCamera action with radius, delta-radius,  z, deltaZ, x, deltaX
 * @param {Number} t time
 * @param {Number} radius
 * @param {Number} deltaRadius
 * @param {Number} angleZ
 * @param {Number} deltaAngleZ
 * @param {Number} angleX
 * @param {Number} deltaAngleX
 * @return {cc.OrbitCamera}
 * @static
 * @deprecated since v3.0 please use cc.orbitCamera() instead.
 */
cc.OrbitCamera.create = cc.orbitCamera;
