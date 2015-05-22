/**
 Copyright (c) 2008-2010 Ricardo Quesada
 Copyright (c) 2011-2012 cocos2d-x.org
 Copyright (c) 2013-2014 Chukong Technologies Inc.
 Copyright (c) 2008, Luke Benstead.
 All rights reserved.

 Redistribution and use in source and binary forms, with or without modification,
 are permitted provided that the following conditions are met:

 Redistributions of source code must retain the above copyright notice,
 this list of conditions and the following disclaimer.
 Redistributions in binary form must reproduce the above copyright notice,
 this list of conditions and the following disclaimer in the documentation
 and/or other materials provided with the distribution.

 THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
 ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
 WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS BE LIABLE FOR
 ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON
 ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
 SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

(function(cc) {
    /**
     * The Quaternion class
     * @param {Number|cc.math.Quaternion} [x=0]
     * @param {Number} [y=0]
     * @param {Number} [z=0]
     * @param {Number} [w=0]
     * @constructor
     */
    cc.math.Quaternion = function (x, y, z, w) {
        if (x && y === undefined) {
            this.x = x.x;
            this.y = x.y;
            this.z = x.z;
            this.w = x.w;
        } else {
            this.x = x || 0;
            this.y = y || 0;
            this.z = z || 0;
            this.w = w || 0;
        }
    };
    cc.kmQuaternion = cc.math.Quaternion;
    var proto = cc.math.Quaternion.prototype;

    /**
     * Sets the conjugate of quaternion to self
     * @param {cc.math.Quaternion} quaternion
     */
    proto.conjugate = function (quaternion) {   //= cc.kmQuaternionConjugate
        this.x = -quaternion.x;
        this.y = -quaternion.y;
        this.z = -quaternion.z;
        this.w = quaternion.w;
        return this;
    };

    /**
     * Returns the dot product of the current quaternion and parameter quaternion
     * @param quaternion
     * @returns {number}
     */
    proto.dot = function(quaternion) {    // = cc.kmQuaternionDot
        // A dot B = B dot A = AtBt + AxBx + AyBy + AzBz
        return (this.w * quaternion.w + this.x * quaternion.x + this.y * quaternion.y + this.z * quaternion.z);
    };

    /**
     * Returns the exponential of the quaternion, this function doesn't implemented.
     * @returns {cc.math.Quaternion}
     */
    proto.exponential = function(){   //=cc.kmQuaternionExp
        return this;
    };

    /**
     * Makes the current quaternion an identity quaternion
     */
    proto.identity = function(){   //=cc.kmQuaternionIdentity
        this.x = 0.0;
        this.y = 0.0;
        this.z = 0.0;
        this.w = 1.0;
        return this;
    };

    /**
     * Inverses the value of current Quaternion
     */
    proto.inverse = function(){           //=cc.kmQuaternionInverse
        var len = this.length();
        if (Math.abs(len) > cc.math.EPSILON) {
            this.x = 0.0;
            this.y = 0.0;
            this.z = 0.0;
            this.w = 0.0;
            return this;
        }

        ///Get the conjugute and divide by the length
        this.conjugate(this).scale(1.0 / len);
        return this;
    };

    /**
     * Returns true if the quaternion is an identity quaternion
     * @returns {boolean}
     */
    proto.isIdentity = function(){     //=cc.kmQuaternionIsIdentity
        return (this.x === 0.0 && this.y === 0.0 && this.z === 0.0 && this.w === 1.0);
    };

    /**
     * Returns the length of the quaternion
     * @returns {number}
     */
    proto.length = function() {       //=cc.kmQuaternionLength
        return Math.sqrt(this.lengthSq());
    };

    /**
     * Returns the length of the quaternion squared (prevents a sqrt)
     * @returns {number}
     */
    proto.lengthSq = function() {   //=cc.kmQuaternionLengthSq
        return this.x * this.x + this.y * this.y + this.z * this.z + this.w * this.w;
    };

    /**
     * Uses current quaternion multiplies other quaternion.
     * @param {cc.math.Quaternion} quaternion
     * @returns {cc.math.Quaternion}
     */
    proto.multiply = function(quaternion) {     //cc.kmQuaternionMultiply
        var x = this.x, y = this.y, z = this.z, w = this.w;
        this.w = w * quaternion.w - x * quaternion.x - y * quaternion.y - z * quaternion.z;
        this.x = w * quaternion.x + x * quaternion.w + y * quaternion.z - z * quaternion.y;
        this.y = w * quaternion.y + y * quaternion.w + z * quaternion.x - x * quaternion.z;
        this.z = w * quaternion.z + z * quaternion.w + x * quaternion.y - y * quaternion.x;
        return this;
    };

    /**
     * Normalizes a quaternion
     * @returns {cc.math.Quaternion}
     */
    proto.normalize = function(){     //=cc.kmQuaternionNormalize
        var length = this.length();
        if (Math.abs(length) <= cc.math.EPSILON)
            throw "current quaternion is an invalid value";
        this.scale(1.0 / length);
        return this;
    };

    /**
     * Rotates a quaternion around an axis and an angle
     * @param {cc.math.Vec3} axis
     * @param {Number} angle
     */
    proto.rotationAxis = function(axis, angle){        //cc.kmQuaternionRotationAxis
        var rad = angle * 0.5, scale = Math.sin(rad);
        this.w = Math.cos(rad);
        this.x = axis.x * scale;
        this.y = axis.y * scale;
        this.z = axis.z * scale;
        return this;
    };

    /**
     *  Creates a quaternion from a rotation matrix
     * @param mat3
     * @returns {*}
     */
    cc.math.Quaternion.rotationMatrix = function (mat3) {        //cc.kmQuaternionRotationMatrix
        if (!mat3)
            return null;

        var x, y, z, w;
        var m4x4 = [], mat = mat3.mat, scale = 0.0;

        /*    0 3 6
         1 4 7
         2 5 8

         0 1 2 3
         4 5 6 7
         8 9 10 11
         12 13 14 15*/
        m4x4[0] = mat[0];
        m4x4[1] = mat[3];
        m4x4[2] = mat[6];
        m4x4[4] = mat[1];
        m4x4[5] = mat[4];
        m4x4[6] = mat[7];
        m4x4[8] = mat[2];
        m4x4[9] = mat[5];
        m4x4[10] = mat[8];
        m4x4[15] = 1;
        var pMatrix = m4x4[0];

        var diagonal = pMatrix[0] + pMatrix[5] + pMatrix[10] + 1;
        if (diagonal > cc.math.EPSILON) {
            // Calculate the scale of the diagonal
            scale = Math.sqrt(diagonal) * 2;

            // Calculate the x, y, x and w of the quaternion through the respective equation
            x = ( pMatrix[9] - pMatrix[6] ) / scale;
            y = ( pMatrix[2] - pMatrix[8] ) / scale;
            z = ( pMatrix[4] - pMatrix[1] ) / scale;
            w = 0.25 * scale;
        } else {
            // If the first element of the diagonal is the greatest value
            if (pMatrix[0] > pMatrix[5] && pMatrix[0] > pMatrix[10]) {
                // Find the scale according to the first element, and double that value
                scale = Math.sqrt(1.0 + pMatrix[0] - pMatrix[5] - pMatrix[10]) * 2.0;

                // Calculate the x, y, x and w of the quaternion through the respective equation
                x = 0.25 * scale;
                y = (pMatrix[4] + pMatrix[1] ) / scale;
                z = (pMatrix[2] + pMatrix[8] ) / scale;
                w = (pMatrix[9] - pMatrix[6] ) / scale;
            }
            // Else if the second element of the diagonal is the greatest value
            else if (pMatrix[5] > pMatrix[10]) {
                // Find the scale according to the second element, and double that value
                scale = Math.sqrt(1.0 + pMatrix[5] - pMatrix[0] - pMatrix[10]) * 2.0;

                // Calculate the x, y, x and w of the quaternion through the respective equation
                x = (pMatrix[4] + pMatrix[1] ) / scale;
                y = 0.25 * scale;
                z = (pMatrix[9] + pMatrix[6] ) / scale;
                w = (pMatrix[2] - pMatrix[8] ) / scale;
            } else {
                // Else the third element of the diagonal is the greatest value

                // Find the scale according to the third element, and double that value
                scale = Math.sqrt(1.0 + pMatrix[10] - pMatrix[0] - pMatrix[5]) * 2.0;

                // Calculate the x, y, x and w of the quaternion through the respective equation
                x = (pMatrix[2] + pMatrix[8] ) / scale;
                y = (pMatrix[9] + pMatrix[6] ) / scale;
                z = 0.25 * scale;
                w = (pMatrix[4] - pMatrix[1] ) / scale;
            }
        }
        return new cc.math.Quaternion(x, y, z, w);
    };

    /**
     * Create a quaternion from yaw, pitch and roll
     * @param yaw
     * @param pitch
     * @param roll
     * @returns {cc.math.Quaternion}
     */
    cc.math.Quaternion.rotationYawPitchRoll = function (yaw, pitch, roll) {     //cc.kmQuaternionRotationYawPitchRoll
        var ex, ey, ez;        // temp half euler angles
        var cr, cp, cy, sr, sp, sy, cpcy, spsy;        // temp vars in roll,pitch yaw

        ex = cc.degreesToRadians(pitch) / 2.0;    // convert to rads and half them
        ey = cc.degreesToRadians(yaw) / 2.0;
        ez = cc.degreesToRadians(roll) / 2.0;

        cr = Math.cos(ex);
        cp = Math.cos(ey);
        cy = Math.cos(ez);

        sr = Math.sin(ex);
        sp = Math.sin(ey);
        sy = Math.sin(ez);

        cpcy = cp * cy;
        spsy = sp * sy;

        var ret = new cc.math.Quaternion();
        ret.w = cr * cpcy + sr * spsy;
        ret.x = sr * cpcy - cr * spsy;
        ret.y = cr * sp * cy + sr * cp * sy;
        ret.z = cr * cp * sy - sr * sp * cy;
        ret.normalize();
        return ret;
    };

    /**
     * Interpolate with other quaternions
     * @param {cc.math.Quaternion} quaternion
     * @param {Number} t
     * @returns {cc.math.Quaternion}
     */
    proto.slerp = function(quaternion, t) {            //=cc.kmQuaternionSlerp
        if (this.x === quaternion.x && this.y === quaternion.y && this.z === quaternion.z && this.w === quaternion.w) {
            return this;
        }
        var ct = this.dot(quaternion), theta = Math.acos(ct), st = Math.sqrt(1.0 - cc.math.square(ct));
        var stt = Math.sin(t * theta) / st, somt = Math.sin((1.0 - t) * theta) / st;
        var temp2 = new cc.math.Quaternion(quaternion);
        this.scale(somt);
        temp2.scale(stt);
        this.add(temp2);
        return this;
    };

    /**
     * Get the axis and angle of rotation from a quaternion
     * @returns {{axis: cc.math.Vec3, angle: number}}
     */
    proto.toAxisAndAngle = function(){    //=cc.kmQuaternionToAxisAngle
        var tempAngle;        // temp angle
        var scale;            // temp vars
        var retAngle, retAxis = new cc.math.Vec3();

        tempAngle = Math.acos(this.w);
        scale = Math.sqrt(cc.math.square(this.x) + cc.math.square(this.y) + cc.math.square(this.z));

        if (((scale > -cc.math.EPSILON) && scale < cc.math.EPSILON)
            || (scale < 2 * Math.PI + cc.math.EPSILON && scale > 2 * Math.PI - cc.math.EPSILON)) {       // angle is 0 or 360 so just simply set axis to 0,0,1 with angle 0
            retAngle = 0.0;
            retAxis.x = 0.0;
            retAxis.y = 0.0;
            retAxis.z = 1.0;
        } else {
            retAngle = tempAngle * 2.0;        // angle in radians
            retAxis.x = this.x / scale;
            retAxis.y = this.y / scale;
            retAxis.z = this.z / scale;
            retAxis.normalize();
        }
         return {axis: retAxis, angle: retAngle};
    };

    /**
     * Scale a quaternion
     * @param {Number} scale
     */
    proto.scale = function(scale) {   //cc.kmQuaternionScale
        this.x *= scale;
        this.y *= scale;
        this.z *= scale;
        this.w *= scale;
        return this;
    };

    /**
     * Assign current quaternion value from a quaternion.
     * @param {cc.math.Quaternion} quaternion
     * @returns {cc.math.Quaternion}  current quaternion
     */
    proto.assignFrom = function(quaternion){     //=cc.kmQuaternionAssign
        this.x = quaternion.x;
        this.y = quaternion.y;
        this.z = quaternion.z;
        this.w = quaternion.w;
        return this;
    };

    /**
     * Adds other quaternion
     * @param {cc.math.Quaternion} quaternion
     * @returns {cc.math.Quaternion}
     */
    proto.add = function(quaternion) {              //cc.kmQuaternionAdd
        this.x += quaternion.x;
        this.y += quaternion.y;
        this.z += quaternion.z;
        this.w += quaternion.w;
        return this;
    };

    /**
     * <p>
     *     Adapted from the OGRE engine!                                                            <br/>
     *     Gets the shortest arc quaternion to rotate this vector to the destination vector.        <br/>
     *     @remarks                                                                                <br/>
     *     If you call this with a destination vector that is close to the inverse                  <br/>
     *     of this vector, we will rotate 180 degrees around the 'fallbackAxis'                     <br/>
     *     (if specified, or a generated axis if not) since in this case ANY axis of rotation is valid.
     * </p>
     * @param {cc.math.Vec3} vec1
     * @param {cc.math.Vec3} vec2
     * @param {cc.math.Vec3} fallback
     * @returns {cc.math.Quaternion}
     */
    cc.math.Quaternion.rotationBetweenVec3 = function(vec1, vec2, fallback) {            //cc.kmQuaternionRotationBetweenVec3
        var v1 = new cc.math.Vec3(vec1), v2 = new cc.math.Vec3(vec2);
        v1.normalize();
        v2.normalize();
        var a = v1.dot(v2), quaternion = new cc.math.Quaternion();

        if (a >= 1.0) {
            quaternion.identity();
            return quaternion;
        }

        if (a < (1e-6 - 1.0)) {
            if (Math.abs(fallback.lengthSq()) < cc.math.EPSILON) {
                quaternion.rotationAxis(fallback, Math.PI);
            } else {
                var axis = new cc.math.Vec3(1.0, 0.0, 0.0);
                axis.cross(vec1);

                //If axis is zero
                if (Math.abs(axis.lengthSq()) < cc.math.EPSILON) {
                    axis.fill(0.0, 1.0, 0.0);
                    axis.cross(vec1);
                }
                axis.normalize();
                quaternion.rotationAxis(axis, Math.PI);
            }
        } else {
            var s = Math.sqrt((1 + a) * 2), invs = 1 / s;
            v1.cross(v2);
            quaternion.x = v1.x * invs;
            quaternion.y = v1.y * invs;
            quaternion.z = v1.z * invs;
            quaternion.w = s * 0.5;
            quaternion.normalize();
        }
        return quaternion;
    };

    /**
     * Current quaternion multiplies a vec3
     * @param {cc.math.Vec3} vec
     * @returns {cc.math.Vec3}
     */
    proto.multiplyVec3 = function(vec){        //=cc.kmQuaternionMultiplyVec3
        var x = this.x, y = this.y, z = this.z, retVec = new cc.math.Vec3(vec);
        var uv = new cc.math.Vec3(x, y, z), uuv = new cc.math.Vec3(x, y, z);
        uv.cross(vec);
        uuv.cross(uv);
        uv.scale((2.0 * q.w));
        uuv.scale(2.0);

        retVec.add(uv);
        retVec.add(uuv);
        return retVec;
    };
})(cc);













