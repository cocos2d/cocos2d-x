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

var Float32Array = Float32Array || Array;
(function(cc){
    cc.math.Matrix3 = function(mat3) {
        if (mat3 && mat3.mat) {
            this.mat = new Float32Array(mat3.mat);
        } else {
            this.mat = new Float32Array(9);
        }
    };
    cc.kmMat3 = cc.math.Matrix3;
    var proto = cc.math.Matrix3.prototype;

    proto.fill = function(mat3) {            //cc.kmMat3Fill
        var mat = this.mat, matIn = mat3.mat;
        mat[0] = matIn[0];
        mat[1] = matIn[1];
        mat[2] = matIn[2];
        mat[3] = matIn[3];
        mat[4] = matIn[4];
        mat[5] = matIn[5];
        mat[6] = matIn[6];
        mat[7] = matIn[7];
        mat[8] = matIn[8];
        return this;
    };

    proto.adjugate = function(){   //= cc.kmMat3Adjugate
        var mat = this.mat;
        var m0 = mat[0], m1 = mat[1], m2 = mat[2], m3 = mat[3], m4 = mat[4],
            m5 = mat[5], m6 = mat[6], m7 = mat[7], m8 = mat[8];
        mat[0] = m4 * m8 - m5 * m7;
        mat[1] = m2 * m7 - m1 * m8;
        mat[2] = m1 * m5 - m2 * m4;
        mat[3] = m5 * m6 - m3 * m8;
        mat[4] = m0 * m8 - m2 * m6;
        mat[5] = m2 * m3 - m0 * m5;
        mat[6] = m3 * m7 - m4 * m6;

        // XXX: pIn.mat[9] is invalid!
        //mat[7] = m1 * m6 - pIn.mat[9] * m7;
        mat[8] = m0 * m4 - m1 * m3;
        return this;
    };

    proto.identity = function() { //cc.kmMat3Identity
        var mat = this.mat;
        mat[1] = mat[2] = mat[3] =
            mat[5] = mat[6] = mat[7] = 0;
        mat[0] = mat[4] = mat[8] = 1.0;
        return this;
    };

    var tmpMatrix = new cc.math.Matrix3();          // internal matrix

    proto.inverse = function(determinate){         //cc.kmMat3Inverse
        if (determinate === 0.0)
            return this;
        tmpMatrix.assignFrom(this);
        var detInv = 1.0 / determinate;
        this.adjugate();
        this.multiplyScalar(detInv);
        return this;
    };

    proto.isIdentity = function(){    //= cc.kmMat3IsIdentity
        var mat = this.mat;
        return (mat[0] === 1 && mat[1] === 0 && mat[2] === 0
        && mat[3] === 0 && mat[4] === 1 && mat[5] === 0
        && mat[6] === 0 && mat[7] === 0 && mat[8] === 1);
    };

    proto.transpose = function(){     // cc.kmMat3Transpose
        var mat = this.mat;
        var  m1 = mat[1], m2 = mat[2], m3 = mat[3],  m5 = mat[5],
            m6 = mat[6], m7 = mat[7];
        // m0 = mat[0],m8 = mat[8], m4 = mat[4];
        //mat[0] = m0;
        //mat[8]  = m8;
        //mat[4] = m4
        mat[1] = m3;
        mat[2] = m6;
        mat[3] = m1;
        mat[5] = m7;
        mat[6] = m2;
        mat[7] = m5;
        return this;
    };

    proto.determinant = function(){
        var mat = this.mat;
        /*
         calculating the determinant following the rule of sarus,
         | 0  3  6 | 0  3 |
         m = | 1  4  7 | 1  4 |
         | 2  5  8 | 2  5 |
         now sum up the products of the diagonals going to the right (i.e. 0,4,8)
         and substract the products of the other diagonals (i.e. 2,4,6)
         */
        var output = mat[0] * mat[4] * mat[8] + mat[1] * mat[5] * mat[6] + mat[2] * mat[3] * mat[7];
        output -= mat[2] * mat[4] * mat[6] + mat[0] * mat[5] * mat[7] + mat[1] * mat[3] * mat[8];
        return output;
    };

    proto.multiply = function(mat3){
        var m1 = this.mat, m2 = mat3.mat;
        var a0 = m1[0], a1 = m1[1], a2 = m1[2], a3 = m1[3], a4 = m1[4], a5 = m1[5],
            a6 = m1[6], a7 = m1[7], a8 = m1[8];
        var b0 = m2[0], b1 = m2[1], b2 = m2[2], b3 = m2[3], b4 = m2[4], b5 = m2[5],
            b6 = m2[6], b7 = m2[7], b8 = m2[8];

        m1[0] = a0 * b0 + a3 * b1 + a6 * b2;
        m1[1] = a1 * b0 + a4 * b1 + a7 * b2;
        m1[2] = a2 * b0 + a5 * b1 + a8 * b2;

        m1[3] = a2 * b0 + a5 * b1 + a8 * b2;
        m1[4] = a1 * b3 + a4 * b4 + a7 * b5;
        m1[5] = a2 * b3 + a5 * b4 + a8 * b5;

        m1[6] = a0 * b6 + a3 * b7 + a6 * b8;
        m1[7] = a1 * b6 + a4 * b7 + a7 * b8;
        m1[8] = a2 * b6 + a5 * b7 + a8 * b8;
        return this;
    };

    proto.multiplyScalar = function(factor) {
        var mat = this.mat;
        mat[0] *= factor;
        mat[1] *= factor;
        mat[2] *= factor;
        mat[3] *= factor;
        mat[4] *= factor;
        mat[5] *= factor;
        mat[6] *= factor;
        mat[7] *= factor;
        mat[8] *= factor;
        return this;
    };

    cc.math.Matrix3.rotationAxisAngle = function(axis, radians) {    //cc.kmMat3RotationAxisAngle
        var rcos = Math.cos(radians), rsin = Math.sin(radians);
        var retMat = new cc.math.Matrix3();
        var mat = retMat.mat;

        mat[0] = rcos + axis.x * axis.x * (1 - rcos);
        mat[1] = axis.z * rsin + axis.y * axis.x * (1 - rcos);
        mat[2] = -axis.y * rsin + axis.z * axis.x * (1 - rcos);

        mat[3] = -axis.z * rsin + axis.x * axis.y * (1 - rcos);
        mat[4] = rcos + axis.y * axis.y * (1 - rcos);
        mat[5] = axis.x * rsin + axis.z * axis.y * (1 - rcos);

        mat[6] = axis.y * rsin + axis.x * axis.z * (1 - rcos);
        mat[7] = -axis.x * rsin + axis.y * axis.z * (1 - rcos);
        mat[8] = rcos + axis.z * axis.z * (1 - rcos);

        return retMat;
    };

    proto.assignFrom = function(matIn){      // cc.kmMat3Assign
        if(this === matIn) {
            cc.log("cc.math.Matrix3.assign(): current matrix equals matIn");
            return this;
        }
        var mat = this.mat, m2 = matIn.mat;
        mat[0] = m2[0];
        mat[1] = m2[1];
        mat[2] = m2[2];
        mat[3] = m2[3];
        mat[4] = m2[4];
        mat[5] = m2[5];
        mat[6] = m2[6];
        mat[7] = m2[7];
        mat[8] = m2[8];
        return this;
    };

    proto.equals = function(mat3) {
        if (this === mat3)
            return true;
        var EPSILON = cc.math.EPSILON,m1 = this.mat, m2 = mat3.mat;
        for (var i = 0; i < 9; ++i) {
            if (!(m1[i] + EPSILON > m2[i] && m1[i] - EPSILON < m2[i]))
                return false;
        }
        return true;
    };

    cc.math.Matrix3.createByRotationX = function(radians) {
        var retMat = new cc.math.Matrix3(), mat = retMat.mat;
        mat[0] = 1.0;
        mat[1] = 0.0;
        mat[2] = 0.0;

        mat[3] = 0.0;
        mat[4] = Math.cos(radians);
        mat[5] = Math.sin(radians);

        mat[6] = 0.0;
        mat[7] = -Math.sin(radians);
        mat[8] = Math.cos(radians);
        return retMat;
    };

    cc.math.Matrix3.createByRotationY = function(radians) {
        /*
         |  cos(A)  0   sin(A) |
         M = |  0       1   0      |
         | -sin(A)  0   cos(A) |
         */
        var retMat = new cc.math.Matrix3(), mat = retMat.mat;
        mat[0] = Math.cos(radians);
        mat[1] = 0.0;
        mat[2] = -Math.sin(radians);

        mat[3] = 0.0;
        mat[4] = 1.0;
        mat[5] = 0.0;

        mat[6] = Math.sin(radians);
        mat[7] = 0.0;
        mat[8] = Math.cos(radians);
        return retMat;
    };

    cc.math.Matrix3.createByRotationZ = function(radians) {
        /*
         |  cos(A)  -sin(A)   0  |
         M = |  sin(A)   cos(A)   0  |
         |  0        0        1  |
         */
        var retMat = new cc.math.Matrix3(), mat = retMat.mat;
        mat[0] = Math.cos(radians);
        mat[1] = -Math.sin(radians);
        mat[2] = 0.0;

        mat[3] = Math.sin(radians);
        mat[4] = Math.cos(radians);
        mat[5] = 0.0;

        mat[6] = 0.0;
        mat[7] = 0.0;
        mat[8] = 1.0;
        return retMat;
    };

    cc.math.Matrix3.createByRotation = function(radians) {
        /*
         |  cos(A)  -sin(A)   0  |
         M = |  sin(A)   cos(A)   0  |
         |  0        0        1  |
         */
        var retMat = new cc.math.Matrix3(), mat = retMat.mat;
        mat[0] = Math.cos(radians);
        mat[1] = Math.sin(radians);
        mat[2] = 0.0;

        mat[3] = -Math.sin(radians);
        mat[4] = Math.cos(radians);
        mat[5] = 0.0;

        mat[6] = 0.0;
        mat[7] = 0.0;
        mat[8] = 1.0;
        return retMat;
    };

    cc.math.Matrix3.createByScale = function(x, y) {
        var ret = new cc.math.Matrix3();
        ret.identity();
        ret.mat[0] = x;
        ret.mat[4] = y;
        return ret;
    };

    cc.math.Matrix3.createByTranslation = function(x, y){
        var ret = new cc.math.Matrix3();
        ret.identity();
        ret.mat[6] = x;
        ret.mat[7] = y;
        return ret;
    };

    cc.math.Matrix3.createByQuaternion = function(quaternion) {     //cc.kmMat3RotationQuaternion
        if(!quaternion)
            return null;

        var ret = new cc.math.Matrix3(), mat = ret.mat;
        // First row
        mat[0] = 1.0 - 2.0 * (quaternion.y * quaternion.y + quaternion.z * quaternion.z);
        mat[1] = 2.0 * (quaternion.x * quaternion.y - quaternion.w * quaternion.z);
        mat[2] = 2.0 * (quaternion.x * quaternion.z + quaternion.w * quaternion.y);

        // Second row
        mat[3] = 2.0 * (quaternion.x * quaternion.y + quaternion.w * quaternion.z);
        mat[4] = 1.0 - 2.0 * (quaternion.x * quaternion.x + quaternion.z * quaternion.z);
        mat[5] = 2.0 * (quaternion.y * quaternion.z - quaternion.w * quaternion.x);

        // Third row
        mat[6] = 2.0 * (quaternion.x * quaternion.z - quaternion.w * quaternion.y);
        mat[7] = 2.0 * (quaternion.y * quaternion.z + quaternion.w * quaternion.x);
        mat[8] = 1.0 - 2.0 * (quaternion.x * quaternion.x + quaternion.y * quaternion.y);
        return ret;
    };

    proto.rotationToAxisAngle = function() {           //cc.kmMat3RotationToAxisAngle
        return cc.math.Quaternion.rotationMatrix(this).toAxisAndAngle();
    }
})(cc);







