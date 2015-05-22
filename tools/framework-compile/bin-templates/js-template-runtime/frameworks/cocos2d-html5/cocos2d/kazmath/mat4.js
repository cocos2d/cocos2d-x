/**
 Copyright (c) 2008-2010 Ricardo Quesada
 Copyright (c) 2011-2012 cocos2d-x.org
 Copyright (c) 2013-2014 Chukong Technologies Inc.
 Copyright (c) 2008, Luke Benstead.
 All rights reserved.

 Redistribution and use in source and binary forms, with or without modification,
 are permitted provided that the following conditions are met:

 * Redistributions of source code must retain the above copyright notice,
 this list of conditions and the following disclaimer.
 * Redistributions in binary form must reproduce the above copyright notice,
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
     * <p>
     * A 4x4 matrix                         </br>
     * </br>
     * mat =                                 </br>
     * | 0   4   8  12 |                     </br>
     * | 1   5   9  13 |                     </br>
     * | 2   6  10  14 |                     </br>
     * | 3   7  11  15 |
     * </p>
     * @param {cc.math.Matrix4} [mat4]
     */
    cc.math.Matrix4 = function (mat4) {
        if(mat4 && mat4.mat){
            this.mat = new Float32Array(mat4.mat);
        } else {
            this.mat = new Float32Array(16);
        }
    };
    cc.kmMat4 = cc.math.Matrix4;
    var proto = cc.math.Matrix4.prototype;

    /**
     * Fills a cc.math.Matrix4 structure with the values from a 16 element array of floats
     * @param {Array} scalarArr
     */
    proto.fill = function(scalarArr){        //cc.kmMat4Fill
         var mat = this.mat;
        for(var i = 0; i < 16; i++){
            mat[i] = scalarArr[i];
        }
        return this;
    };

    /**
     * Sets pOut to an identity matrix returns pOut
     * @Params pOut - A pointer to the matrix to set to identity
     * @Return Returns pOut so that the call can be nested
     */
    cc.kmMat4Identity = function (pOut) {
        var mat = pOut.mat;
        mat[1] = mat[2] = mat[3] = mat[4] = mat[6] = mat[7]
            = mat[8] = mat[9] = mat[11] = mat[12] = mat[13] = mat[14] = 0;
        mat[0] = mat[5] = mat[10] = mat[15] = 1.0;
        return pOut;
    };

    /**
     * Sets matrix to identity value.
     * @returns {cc.math.Matrix4}
     */
    proto.identity = function(){
        var mat = this.mat;
        mat[1] = mat[2] = mat[3] = mat[4] = mat[6] = mat[7]
            = mat[8] = mat[9] = mat[11] = mat[12] = mat[13] = mat[14] = 0;
        mat[0] = mat[5] = mat[10] = mat[15] = 1.0;
        return this;
    };

    proto.get = function(row, col){
        return this.mat[row + 4 * col];
    };

    proto.set = function(row, col, value){
        this.mat[row + 4 * col] = value;
    };

    proto.swap = function(r1, c1, r2, c2) {
/*        var tmp = this.get(r1, c1);
        this.set(r1, c1, this.get(r2, c2));
        this.set(r2, c2, tmp);*/
        var mat = this.mat, tmp = mat[r1 + 4 * c1];
        mat[r1 + 4 * c1] = mat[r2 + 4 * c2];
        mat[r2 + 4 * c2] = tmp;
    };

    //Returns an upper and a lower triangular matrix which are L and R in the Gauss algorithm
    cc.math.Matrix4._gaussj = function (a, b) {
        var i, icol = 0, irow = 0, j, k, l, ll, n = 4, m = 4, selElement;
        var big, dum, pivinv;
        var indxc = [0, 0, 0, 0], indxr = [0, 0, 0, 0], ipiv = [0, 0, 0, 0];

        /*    for (j = 0; j < n; j++) {
         ipiv[j] = 0;
         }*/

        for (i = 0; i < n; i++) {
            big = 0.0;
            for (j = 0; j < n; j++) {
                if (ipiv[j] !== 1) {
                    for (k = 0; k < n; k++) {
                        if (ipiv[k] === 0) {
                            selElement = Math.abs(a.get(j, k));
                            if (selElement >= big) {
                                big = selElement;
                                irow = j;
                                icol = k;
                            }
                        }
                    }
                }
            }
            ++(ipiv[icol]);
            if (irow !== icol) {
                for (l = 0; l < n; l++)
                    a.swap(irow, l, icol, l);
                for (l = 0; l < m; l++)
                    b.swap(irow, l, icol, l);
            }
            indxr[i] = irow;
            indxc[i] = icol;
            if (a.get(icol, icol) === 0.0)
                return false;

            pivinv = 1.0 / a.get(icol, icol);
            a.set(icol, icol, 1.0);
            for (l = 0; l < n; l++)
                a.set(icol, l, a.get(icol, l) * pivinv);

            for (l = 0; l < m; l++)
                b.set(icol, l, b.get(icol, l) * pivinv);

            for (ll = 0; ll < n; ll++) {
                if (ll !== icol) {
                    dum = a.get(ll, icol);
                    a.set(ll, icol, 0.0);
                    for (l = 0; l < n; l++)
                        a.set(ll, l, a.get(ll, l) - a.get(icol, l) * dum);

                    for (l = 0; l < m; l++)
                        b.set(ll, l, a.get(ll, l) - b.get(icol, l) * dum);
                }
            }
        }
        //    This is the end of the main loop over columns of the reduction. It only remains to unscram-
        //    ble the solution in view of the column interchanges. We do this by interchanging pairs of
        //    columns in the reverse order that the permutation was built up.
        for (l = n - 1; l >= 0; l--) {
            if (indxr[l] !== indxc[l]) {
                for (k = 0; k < n; k++)
                    a.swap(k, indxr[l], k, indxc[l]);
            }
        }
        return true;
    };

    var identityMatrix = new cc.math.Matrix4().identity();
    /**
     * Calculates the inverse of pM and stores the result in pOut.
     * Please use matrix4's inverse function instead.
     * @Return Returns NULL if there is no inverse, else pOut
     */
    cc.kmMat4Inverse = function (pOut, pM) {
        var inv = new cc.math.Matrix4(pM);
        if (cc.math.Matrix4._gaussj(inv, identityMatrix) === false)
            return null;
        pOut.assignFrom(inv);
        return pOut;
    };

    /**
     * Calculates the inverse of current matrix.
     * @returns {cc.math.Matrix4} Returns null if there is no inverse, else returns a new inverse matrix object
     */
    proto.inverse = function(){    //cc.kmMat4Inverse
        var inv = new cc.math.Matrix4(this);
        if (cc.math.Matrix4._gaussj(inv, identityMatrix) === false)
            return null;
        return inv;
    };

    /**
     * Returns true if current matrix is an identity matrix, false otherwise
     */
    proto.isIdentity = function () {       // cc.kmMat4IsIdentity
        var mat = this.mat;
        return (mat[0] === 1 && mat[1] === 0 && mat[2] === 0 && mat[3] === 0
        && mat[4] === 0 && mat[5] === 1 && mat[6] === 0 && mat[7] === 0
        && mat[8] === 0 && mat[9] === 0 && mat[10] === 1 && mat[11] === 0
        && mat[12] === 0 && mat[13] === 0 && mat[14] === 0 && mat[15] === 1);
    };

    /**
     *  transpose the current matrix
     */
    proto.transpose = function() {        // cc.kmMat4Transpose
        var mat = this.mat;
        var m1 = mat[1], m2 = mat[2], m3 = mat[3],
            m4 = mat[4], m6 = mat[6], m7 = mat[7],
            m8 = mat[8], m9 = mat[9], m11 = mat[11],
            m12 = mat[12], m13 = mat[13], m14 = mat[14];
        mat[1] = m4;
        mat[2] = m8;
        mat[3] = m12;

        mat[4] = m1;
        mat[6] = m9;
        mat[7] = m13;

        mat[8] = m2;
        mat[9] = m6;
        mat[11] = m14;

        mat[12] = m3;
        mat[13] = m7;
        mat[14] = m11;
        return this;
    };

    /**
     * Multiplies pM1 with pM2, stores the result in pOut, returns pOut
     */
    cc.kmMat4Multiply = function (pOut, pM1, pM2) {
        // Cache the matrix values (makes for huge speed increases!)
        var outArray = pOut.mat, mat1 = pM1.mat, mat2 = pM2.mat;
        var a00 = mat1[0], a01 = mat1[1], a02 = mat1[2], a03 = mat1[3];
        var a10 = mat1[4], a11 = mat1[5], a12 = mat1[6], a13 = mat1[7];
        var a20 = mat1[8], a21 = mat1[9], a22 = mat1[10], a23 = mat1[11];
        var a30 = mat1[12], a31 = mat1[13], a32 = mat1[14], a33 = mat1[15];

        var b00 = mat2[0], b01 = mat2[1], b02 = mat2[2], b03 = mat2[3];
        var b10 = mat2[4], b11 = mat2[5], b12 = mat2[6], b13 = mat2[7];
        var b20 = mat2[8], b21 = mat2[9], b22 = mat2[10], b23 = mat2[11];
        var b30 = mat2[12], b31 = mat2[13], b32 = mat2[14], b33 = mat2[15];

        outArray[0] = b00 * a00 + b01 * a10 + b02 * a20 + b03 * a30;
        outArray[1] = b00 * a01 + b01 * a11 + b02 * a21 + b03 * a31;
        outArray[2] = b00 * a02 + b01 * a12 + b02 * a22 + b03 * a32;
        outArray[3] = b00 * a03 + b01 * a13 + b02 * a23 + b03 * a33;
        outArray[4] = b10 * a00 + b11 * a10 + b12 * a20 + b13 * a30;
        outArray[5] = b10 * a01 + b11 * a11 + b12 * a21 + b13 * a31;
        outArray[6] = b10 * a02 + b11 * a12 + b12 * a22 + b13 * a32;
        outArray[7] = b10 * a03 + b11 * a13 + b12 * a23 + b13 * a33;
        outArray[8] = b20 * a00 + b21 * a10 + b22 * a20 + b23 * a30;
        outArray[9] = b20 * a01 + b21 * a11 + b22 * a21 + b23 * a31;
        outArray[10] = b20 * a02 + b21 * a12 + b22 * a22 + b23 * a32;
        outArray[11] = b20 * a03 + b21 * a13 + b22 * a23 + b23 * a33;
        outArray[12] = b30 * a00 + b31 * a10 + b32 * a20 + b33 * a30;
        outArray[13] = b30 * a01 + b31 * a11 + b32 * a21 + b33 * a31;
        outArray[14] = b30 * a02 + b31 * a12 + b32 * a22 + b33 * a32;
        outArray[15] = b30 * a03 + b31 * a13 + b32 * a23 + b33 * a33;
        return pOut;
    };

    /**
     * current matrix multiplies with other matrix mat4
     * @param {cc.math.Matrix4} mat4
     * @returns {cc.math.Matrix4}
     */
    proto.multiply = function(mat4){
        // Cache the matrix values (makes for huge speed increases!)
        var mat = this.mat, mat2 = mat4.mat;
        var a00 = mat[0], a01 = mat[1], a02 = mat[2], a03 = mat[3];
        var a10 = mat[4], a11 = mat[5], a12 = mat[6], a13 = mat[7];
        var a20 = mat[8], a21 = mat[9], a22 = mat[10], a23 = mat[11];
        var a30 = mat[12], a31 = mat[13], a32 = mat[14], a33 = mat[15];

        var b00 = mat2[0], b01 = mat2[1], b02 = mat2[2], b03 = mat2[3];
        var b10 = mat2[4], b11 = mat2[5], b12 = mat2[6], b13 = mat2[7];
        var b20 = mat2[8], b21 = mat2[9], b22 = mat2[10], b23 = mat2[11];
        var b30 = mat2[12], b31 = mat2[13], b32 = mat2[14], b33 = mat2[15];

        mat[0] = b00 * a00 + b01 * a10 + b02 * a20 + b03 * a30;
        mat[1] = b00 * a01 + b01 * a11 + b02 * a21 + b03 * a31;
        mat[2] = b00 * a02 + b01 * a12 + b02 * a22 + b03 * a32;
        mat[3] = b00 * a03 + b01 * a13 + b02 * a23 + b03 * a33;
        mat[4] = b10 * a00 + b11 * a10 + b12 * a20 + b13 * a30;
        mat[5] = b10 * a01 + b11 * a11 + b12 * a21 + b13 * a31;
        mat[6] = b10 * a02 + b11 * a12 + b12 * a22 + b13 * a32;
        mat[7] = b10 * a03 + b11 * a13 + b12 * a23 + b13 * a33;
        mat[8] = b20 * a00 + b21 * a10 + b22 * a20 + b23 * a30;
        mat[9] = b20 * a01 + b21 * a11 + b22 * a21 + b23 * a31;
        mat[10] = b20 * a02 + b21 * a12 + b22 * a22 + b23 * a32;
        mat[11] = b20 * a03 + b21 * a13 + b22 * a23 + b23 * a33;
        mat[12] = b30 * a00 + b31 * a10 + b32 * a20 + b33 * a30;
        mat[13] = b30 * a01 + b31 * a11 + b32 * a21 + b33 * a31;
        mat[14] = b30 * a02 + b31 * a12 + b32 * a22 + b33 * a32;
        mat[15] = b30 * a03 + b31 * a13 + b32 * a23 + b33 * a33;
        return this;
    };

    cc.getMat4MultiplyValue = function (pM1, pM2) {
        var m1 = pM1.mat, m2 = pM2.mat;
        var mat = new Float32Array(16);

        mat[0] = m1[0] * m2[0] + m1[4] * m2[1] + m1[8] * m2[2] + m1[12] * m2[3];
        mat[1] = m1[1] * m2[0] + m1[5] * m2[1] + m1[9] * m2[2] + m1[13] * m2[3];
        mat[2] = m1[2] * m2[0] + m1[6] * m2[1] + m1[10] * m2[2] + m1[14] * m2[3];
        mat[3] = m1[3] * m2[0] + m1[7] * m2[1] + m1[11] * m2[2] + m1[15] * m2[3];

        mat[4] = m1[0] * m2[4] + m1[4] * m2[5] + m1[8] * m2[6] + m1[12] * m2[7];
        mat[5] = m1[1] * m2[4] + m1[5] * m2[5] + m1[9] * m2[6] + m1[13] * m2[7];
        mat[6] = m1[2] * m2[4] + m1[6] * m2[5] + m1[10] * m2[6] + m1[14] * m2[7];
        mat[7] = m1[3] * m2[4] + m1[7] * m2[5] + m1[11] * m2[6] + m1[15] * m2[7];

        mat[8] = m1[0] * m2[8] + m1[4] * m2[9] + m1[8] * m2[10] + m1[12] * m2[11];
        mat[9] = m1[1] * m2[8] + m1[5] * m2[9] + m1[9] * m2[10] + m1[13] * m2[11];
        mat[10] = m1[2] * m2[8] + m1[6] * m2[9] + m1[10] * m2[10] + m1[14] * m2[11];
        mat[11] = m1[3] * m2[8] + m1[7] * m2[9] + m1[11] * m2[10] + m1[15] * m2[11];

        mat[12] = m1[0] * m2[12] + m1[4] * m2[13] + m1[8] * m2[14] + m1[12] * m2[15];
        mat[13] = m1[1] * m2[12] + m1[5] * m2[13] + m1[9] * m2[14] + m1[13] * m2[15];
        mat[14] = m1[2] * m2[12] + m1[6] * m2[13] + m1[10] * m2[14] + m1[14] * m2[15];
        mat[15] = m1[3] * m2[12] + m1[7] * m2[13] + m1[11] * m2[14] + m1[15] * m2[15];

        return mat;
    };

    /**
     * Assigns the value of pIn to pOut
     */
    cc.kmMat4Assign = function (pOut, pIn) {
        if (pOut === pIn) {
            cc.log("cc.kmMat4Assign(): pOut equals pIn");
            return pOut;
        }

        var outArr = pOut.mat;
        var inArr = pIn.mat;

        outArr[0] = inArr[0];
        outArr[1] = inArr[1];
        outArr[2] = inArr[2];
        outArr[3] = inArr[3];

        outArr[4] = inArr[4];
        outArr[5] = inArr[5];
        outArr[6] = inArr[6];
        outArr[7] = inArr[7];

        outArr[8] = inArr[8];
        outArr[9] = inArr[9];
        outArr[10] = inArr[10];
        outArr[11] = inArr[11];

        outArr[12] = inArr[12];
        outArr[13] = inArr[13];
        outArr[14] = inArr[14];
        outArr[15] = inArr[15];
        return pOut;
    };

    /**
     * Assigns the value of current matrix from mat4
     * @param {cc.math.Matrix4} mat4
     * @returns {cc.math.Matrix4}
     */
    proto.assignFrom = function(mat4) {
        if (this === mat4) {
            cc.log("cc.mat.Matrix4.assignFrom(): mat4 equals current matrix");
            return this;
        }
        var outArr = this.mat, inArr = mat4.mat;

        outArr[0] = inArr[0];
        outArr[1] = inArr[1];
        outArr[2] = inArr[2];
        outArr[3] = inArr[3];

        outArr[4] = inArr[4];
        outArr[5] = inArr[5];
        outArr[6] = inArr[6];
        outArr[7] = inArr[7];

        outArr[8] = inArr[8];
        outArr[9] = inArr[9];
        outArr[10] = inArr[10];
        outArr[11] = inArr[11];

        outArr[12] = inArr[12];
        outArr[13] = inArr[13];
        outArr[14] = inArr[14];
        outArr[15] = inArr[15];
        return this;
    };

    /**
     * Returns true if current matrix equal mat4 (approximately)
     * @param {cc.math.Matrix4} mat4
     * @returns {boolean}
     */
    proto.equals = function(mat4) {
        if (this === mat4) {
            cc.log("cc.kmMat4AreEqual(): pMat1 and pMat2 are same object.");
            return true;
        }
        var matA = this.mat, matB = mat4.mat, EPSILON = cc.math.EPSILON;
        for (var i = 0; i < 16; i++) {
            if (!(matA[i] + EPSILON > matB[i] && matA[i] - EPSILON < matB[i]))
                return false;
        }
        return true;
    };

    /**
     * Builds an X-axis rotation matrix and stores it in matrix, returns matrix, if matrix is null, create a new matrix
     * @param {Number} radians
     * @param {cc.math.Matrix4} [matrix]
     * @returns {cc.math.Matrix4}
     */
    cc.math.Matrix4.createByRotationX = function(radians, matrix) {    //cc.kmMat4RotationX
        /*
         |  1  0       0       0 |
         M = |  0  cos(A) -sin(A)  0 |
         |  0  sin(A)  cos(A)  0 |
         |  0  0       0       1 |
         */
        matrix = matrix || new cc.math.Matrix4();
        var mat = matrix.mat;
        mat[0] = 1.0;
        mat[3] = mat[2] = mat[1] = 0.0;

        mat[4] = 0.0;
        mat[5] = Math.cos(radians);
        mat[6] = Math.sin(radians);
        mat[7] = 0.0;

        mat[8] = 0.0;
        mat[9] = -Math.sin(radians);
        mat[10] = Math.cos(radians);
        mat[11] = 0.0;

        mat[14] = mat[13] = mat[12] = 0.0;
        mat[15] = 1.0;
        return matrix;
    };

    /**
     * Builds a rotation matrix using the rotation around the Y-axis, The result is stored in matrix, matrix is returned.
     * @param {Number} radians
     * @param {cc.math.Matrix4} [matrix]
     * @returns {*}
     */
    cc.math.Matrix4.createByRotationY = function(radians, matrix) {      // cc.kmMat4RotationY
        /*
         |  cos(A)  0   sin(A)  0 |
         M = |  0       1   0       0 |
         | -sin(A)  0   cos(A)  0 |
         |  0       0   0       1 |
         */
        matrix = matrix || new cc.math.Matrix4();
        var mat = matrix.mat;
        mat[0] = Math.cos(radians);
        mat[1] = 0.0;
        mat[2] = -Math.sin(radians);
        mat[3] = 0.0;

        mat[7] = mat[6] = mat[4] = 0.0;
        mat[5] = 1.0;

        mat[8] = Math.sin(radians);
        mat[9] = 0.0;
        mat[10] = Math.cos(radians);
        mat[11] = 0.0;

        mat[14] = mat[13] = mat[12] = 0.0;
        mat[15] = 1.0;
        return matrix;
    };

    /**
     * Builds a rotation matrix around the Z-axis. The resulting matrix is stored in matrix. matrix is returned.
     * @param {Number} radians
     * @param {cc.math.Matrix4} matrix
     * @return {cc.math.Matrix4}
     */
    cc.math.Matrix4.createByRotationZ = function(radians, matrix){    // cc.kmMat4RotationZ
        /*
         |  cos(A)  -sin(A)   0   0 |
         M = |  sin(A)   cos(A)   0   0 |
         |  0        0        1   0 |
         |  0        0        0   1 |
         */
        matrix = matrix || new cc.math.Matrix4();
        var mat = matrix.mat;
        mat[0] = Math.cos(radians);
        mat[1] = Math.sin(radians);
        mat[3] = mat[2] = 0.0;

        mat[4] = -Math.sin(radians);
        mat[5] = Math.cos(radians);
        mat[7] = mat[6] = 0.0;

        mat[11] = mat[9] = mat[8] = 0.0;
        mat[10] = 1.0;

        mat[14] = mat[13] = mat[12] = 0.0;
        mat[15] = 1.0;

        return matrix;
    };

    /**
     * Builds a rotation matrix from pitch, yaw and roll. The resulting matrix is stored in parameter matrix and returns.
     * @param {Number} pitch
     * @param {Number} yaw
     * @param {Number} roll
     * @param {cc.math.Matrix4} [matrix] if matrix is undefined, creates a new matrix.
     * @returns {cc.math.Matrix4}
     */
    cc.math.Matrix4.createByPitchYawRoll = function(pitch, yaw, roll, matrix) {
        matrix = matrix || new cc.math.Matrix4();
        var cr = Math.cos(pitch), sr = Math.sin(pitch);
        var cp = Math.cos(yaw), sp = Math.sin(yaw);
        var cy = Math.cos(roll), sy = Math.sin(roll);
        var srsp = sr * sp, crsp = cr * sp;
        var mat = matrix.mat;

        mat[0] = cp * cy;
        mat[4] = cp * sy;
        mat[8] = -sp;

        mat[1] = srsp * cy - cr * sy;
        mat[5] = srsp * sy + cr * cy;
        mat[9] = sr * cp;

        mat[2] = crsp * cy + sr * sy;
        mat[6] = crsp * sy - sr * cy;
        mat[10] = cr * cp;

        mat[3] = mat[7] = mat[11] = 0.0;
        mat[15] = 1.0;
        return matrix;
    };

    /**
     * Builds a matrix by a quaternion.
     * @param {cc.math.Quaternion} quaternion
     * @param {cc.math.Matrix4} [matrix] if matrix is undefined, creates a new matrix.
     * @returns {cc.math.Matrix4}
     */
    cc.math.Matrix4.createByQuaternion = function(quaternion, matrix) {
        matrix = matrix || new cc.math.Matrix4();
        var mat = matrix.mat;
        mat[0] = 1.0 - 2.0 * (quaternion.y * quaternion.y + quaternion.z * quaternion.z );
        mat[1] = 2.0 * (quaternion.x * quaternion.y + quaternion.z * quaternion.w);
        mat[2] = 2.0 * (quaternion.x * quaternion.z - quaternion.y * quaternion.w);
        mat[3] = 0.0;

        // Second row
        mat[4] = 2.0 * ( quaternion.x * quaternion.y - quaternion.z * quaternion.w );
        mat[5] = 1.0 - 2.0 * ( quaternion.x * quaternion.x + quaternion.z * quaternion.z );
        mat[6] = 2.0 * (quaternion.z * quaternion.y + quaternion.x * quaternion.w );
        mat[7] = 0.0;

        // Third row
        mat[8] = 2.0 * ( quaternion.x * quaternion.z + quaternion.y * quaternion.w );
        mat[9] = 2.0 * ( quaternion.y * quaternion.z - quaternion.x * quaternion.w );
        mat[10] = 1.0 - 2.0 * ( quaternion.x * quaternion.x + quaternion.y * quaternion.y );
        mat[11] = 0.0;

        // Fourth row
        mat[14] = mat[13] = mat[12] = 0;
        mat[15] = 1.0;
        return matrix;
    };

    /**
     * Build a 4x4 OpenGL transformation matrix using a 3x3 rotation matrix, and a 3d vector representing a translation.
     * @param {cc.math.Matrix3} rotation
     * @param {cc.math.Vec3} translation
     * @param {cc.math.Matrix4} [matrix] if matrix is undefined, creates a new matrix.
     * @returns {cc.math.Matrix4}
     */
    cc.math.Matrix4.createByRotationTranslation = function(rotation, translation, matrix) {
        matrix = matrix || new cc.math.Matrix4();
        var mat = matrix.mat, rMat = rotation.mat;
        mat[0] = rMat[0];
        mat[1] = rMat[1];
        mat[2] = rMat[2];
        mat[3] = 0.0;

        mat[4] = rMat[3];
        mat[5] = rMat[4];
        mat[6] = rMat[5];
        mat[7] = 0.0;

        mat[8] = rMat[6];
        mat[9] = rMat[7];
        mat[10] = rMat[8];
        mat[11] = 0.0;

        mat[12] = translation.x;
        mat[13] = translation.y;
        mat[14] = translation.z;
        mat[15] = 1.0;
        return matrix;
    };

    /**
     * Builds a scaling matrix
     * @param {Number} x
     * @param {Number} y
     * @param {Number} z
     * @param {cc.math.Matrix4} [matrix] if matrix is undefined, creates a new matrix.
     * @returns {cc.math.Matrix4}
     */
    cc.math.Matrix4.createByScale = function(x, y, z, matrix) {  //cc.kmMat4Scaling
        matrix = matrix || new cc.math.Matrix4();
        var mat = matrix.mat;
        mat[0] = x;
        mat[5] = y;
        mat[10] = z;
        mat[15] = 1.0;
        mat[1] = mat[2] = mat[3] = mat[4] = mat[6] = mat[7] =
            mat[8] = mat[9] = mat[11] = mat[12] = mat[13] = mat[14] = 0;
         return matrix;
    };

    /**
     * Builds a translation matrix. All other elements in the matrix
     * will be set to zero except for the diagonal which is set to 1.0
     */
    cc.kmMat4Translation = function (pOut, x, y, z) {
        //FIXME: Write a test for this
        pOut.mat[0] = pOut.mat[5] = pOut.mat[10] = pOut.mat[15] = 1.0;
        pOut.mat[1] = pOut.mat[2] = pOut.mat[3] =
            pOut.mat[4] = pOut.mat[6] = pOut.mat[7] =
                pOut.mat[8] = pOut.mat[9] = pOut.mat[11] = 0.0;
        pOut.mat[12] = x;
        pOut.mat[13] = y;
        pOut.mat[14] = z;
        return pOut;
    };

    /**
     *  Builds a translation matrix.
     * @param {Number} x
     * @param {Number} y
     * @param {Number} z
     * @param {cc.math.Matrix4} [matrix] if matrix is undefined, creates a new matrix.
     * @returns {cc.math.Matrix4}
     */
    cc.math.Matrix4.createByTranslation = function(x, y, z, matrix){       //cc.kmMat4Translation
        matrix = matrix || new cc.math.Matrix4();
        matrix.identity();
        matrix.mat[12] = x;
        matrix.mat[13] = y;
        matrix.mat[14] = z;
        return matrix;
    };

    /**
     *  Get the up vector from a matrix.
     *  @returns {cc.math.Vec3}
     */
    proto.getUpVec3 = function() {
        var mat = this.mat;
        var ret = new cc.math.Vec3(mat[4],mat[5], mat[6]);
        return ret.normalize();
    };

    /**
     * Extract the right vector from a 4x4 matrix.
     * @returns {cc.math.Vec3}
     */
    proto.getRightVec3 = function(){
        var mat = this.mat;
        var ret = new cc.math.Vec3(mat[0],mat[1], mat[2]);
        return ret.normalize();
    };

    /**
     * Extract the forward vector from a 4x4 matrix.
     * @returns {cc.math.Vec3}
     */
    proto.getForwardVec3 = function() {
        var mat = this.mat;
        var ret = new cc.math.Vec3(mat[8],mat[9], mat[10]);
        return ret.normalize();
    };

    /**
     * Creates a perspective projection matrix in the
     * same way as gluPerspective
     */
    cc.kmMat4PerspectiveProjection = function (pOut, fovY, aspect, zNear, zFar) {
        var r = cc.degreesToRadians(fovY / 2);
        var deltaZ = zFar - zNear;
        var s = Math.sin(r);

        if (deltaZ === 0 || s === 0 || aspect === 0)
            return null;

        //cos(r) / sin(r) = cot(r)
        var cotangent = Math.cos(r) / s;
        pOut.identity();
        pOut.mat[0] = cotangent / aspect;
        pOut.mat[5] = cotangent;
        pOut.mat[10] = -(zFar + zNear) / deltaZ;
        pOut.mat[11] = -1;
        pOut.mat[14] = -2 * zNear * zFar / deltaZ;
        pOut.mat[15] = 0;

        return pOut;
    };

    /**
     * Creates a perspective projection matrix in the same way as gluPerspective
     * @param {Number} fovY
     * @param {Number} aspect
     * @param {Number} zNear
     * @param {Number} zFar
     * @returns {cc.math.Matrix4|Null}
     */
    cc.math.Matrix4.createPerspectiveProjection = function(fovY, aspect, zNear, zFar){
        var r = cc.degreesToRadians(fovY / 2), deltaZ = zFar - zNear;
        var s = Math.sin(r);

        if (deltaZ === 0 || s === 0 || aspect === 0)
            return null;

        //cos(r) / sin(r) = cot(r)
        var cotangent = Math.cos(r) / s;
        var matrix = new cc.math.Matrix4(), mat = matrix.mat;
        matrix.identity();
        mat[0] = cotangent / aspect;
        mat[5] = cotangent;
        mat[10] = -(zFar + zNear) / deltaZ;
        mat[11] = -1;
        mat[14] = -2 * zNear * zFar / deltaZ;
        mat[15] = 0;
        return matrix;
    };

    /** Creates an orthographic projection matrix like glOrtho */
    cc.kmMat4OrthographicProjection = function (pOut, left, right, bottom, top, nearVal, farVal) {
        pOut.identity();
        pOut.mat[0] = 2 / (right - left);
        pOut.mat[5] = 2 / (top - bottom);
        pOut.mat[10] = -2 / (farVal - nearVal);
        pOut.mat[12] = -((right + left) / (right - left));
        pOut.mat[13] = -((top + bottom) / (top - bottom));
        pOut.mat[14] = -((farVal + nearVal) / (farVal - nearVal));
        return pOut;
    };

    /**
     * Creates an orthographic projection matrix like glOrtho
     * @param {Number} left
     * @param {Number} right
     * @param {Number} bottom
     * @param {Number} top
     * @param {Number} nearVal
     * @param {Number} farVal
     * @returns {cc.math.Matrix4}
     */
    cc.math.Matrix4.createOrthographicProjection = function (left, right, bottom, top, nearVal, farVal) {
        var matrix = new cc.math.Matrix4(), mat = matrix.mat;
        matrix.identity();
        mat[0] = 2 / (right - left);
        mat[5] = 2 / (top - bottom);
        mat[10] = -2 / (farVal - nearVal);
        mat[12] = -((right + left) / (right - left));
        mat[13] = -((top + bottom) / (top - bottom));
        mat[14] = -((farVal + nearVal) / (farVal - nearVal));
        return matrix;
    };

    /**
     * Builds a translation matrix in the same way as gluLookAt()
     * the resulting matrix is stored in pOut. pOut is returned.
     */
    cc.kmMat4LookAt = function (pOut, pEye, pCenter, pUp) {
        var f = new cc.math.Vec3(pCenter), up = new cc.math.Vec3(pUp);
        f.subtract(pEye);
        f.normalize();
        up.normalize();

        var s = new cc.math.Vec3(f);
        s.cross(up);
        s.normalize();

        var u = new cc.math.Vec3(s);
        u.cross(f);
        s.normalize();

        pOut.identity();

        pOut.mat[0] = s.x;
        pOut.mat[4] = s.y;
        pOut.mat[8] = s.z;

        pOut.mat[1] = u.x;
        pOut.mat[5] = u.y;
        pOut.mat[9] = u.z;

        pOut.mat[2] = -f.x;
        pOut.mat[6] = -f.y;
        pOut.mat[10] = -f.z;

        var translate = cc.math.Matrix4.createByTranslation(-pEye.x, -pEye.y, -pEye.z);
        pOut.multiply(translate);
        return pOut;
    };

    var tempMatrix = new cc.math.Matrix4();         // an internal matrix
    proto.lookAt = function(eyeVec, centerVec, upVec) {
        var f = new cc.math.Vec3(centerVec), up = new cc.math.Vec3(upVec), mat = this.mat;
        f.subtract(eyeVec);
        f.normalize();
        up.normalize();

        var s = new cc.math.Vec3(f);
        s.cross(up);
        s.normalize();

        var u = new cc.math.Vec3(s);
        u.cross(f);
        s.normalize();

        this.identity();
        mat[0] = s.x;
        mat[4] = s.y;
        mat[8] = s.z;

        mat[1] = u.x;
        mat[5] = u.y;
        mat[9] = u.z;

        mat[2] = -f.x;
        mat[6] = -f.y;
        mat[10] = -f.z;

        tempMatrix = cc.math.Matrix4.createByTranslation(-eyeVec.x, -eyeVec.y, -eyeVec.z, tempMatrix);
        this.multiply(tempMatrix);
        return this;
    };

    /**
     * Build a rotation matrix from an axis and an angle. Result is stored in pOut.
     * pOut is returned.
     */
    cc.kmMat4RotationAxisAngle = function (pOut, axis, radians) {
        var rcos = Math.cos(radians), rsin = Math.sin(radians);

        var normalizedAxis = new cc.math.Vec3(axis);
        normalizedAxis.normalize();

        pOut.mat[0] = rcos + normalizedAxis.x * normalizedAxis.x * (1 - rcos);
        pOut.mat[1] = normalizedAxis.z * rsin + normalizedAxis.y * normalizedAxis.x * (1 - rcos);
        pOut.mat[2] = -normalizedAxis.y * rsin + normalizedAxis.z * normalizedAxis.x * (1 - rcos);
        pOut.mat[3] = 0.0;

        pOut.mat[4] = -normalizedAxis.z * rsin + normalizedAxis.x * normalizedAxis.y * (1 - rcos);
        pOut.mat[5] = rcos + normalizedAxis.y * normalizedAxis.y * (1 - rcos);
        pOut.mat[6] = normalizedAxis.x * rsin + normalizedAxis.z * normalizedAxis.y * (1 - rcos);
        pOut.mat[7] = 0.0;

        pOut.mat[8] = normalizedAxis.y * rsin + normalizedAxis.x * normalizedAxis.z * (1 - rcos);
        pOut.mat[9] = -normalizedAxis.x * rsin + normalizedAxis.y * normalizedAxis.z * (1 - rcos);
        pOut.mat[10] = rcos + normalizedAxis.z * normalizedAxis.z * (1 - rcos);
        pOut.mat[11] = 0.0;

        pOut.mat[12] = 0.0;
        pOut.mat[13] = 0.0;
        pOut.mat[14] = 0.0;
        pOut.mat[15] = 1.0;

        return pOut;
    };

    /**
     * Build a rotation matrix from an axis and an angle.
     * @param {cc.math.Vec3} axis
     * @param {Number} radians
     * @param {cc.math.Matrix4} [matrix]
     * @returns {cc.math.Matrix4}
     */
    cc.math.Matrix4.createByAxisAndAngle = function(axis, radians, matrix) {
        matrix = matrix || new cc.math.Matrix4();
        var mat = this.mat, rcos = Math.cos(radians), rsin = Math.sin(radians) ;

        var normalizedAxis = new cc.math.Vec3(axis);
        normalizedAxis.normalize();

        mat[0] = rcos + normalizedAxis.x * normalizedAxis.x * (1 - rcos);
        mat[1] = normalizedAxis.z * rsin + normalizedAxis.y * normalizedAxis.x * (1 - rcos);
        mat[2] = -normalizedAxis.y * rsin + normalizedAxis.z * normalizedAxis.x * (1 - rcos);
        mat[3] = 0.0;

        mat[4] = -normalizedAxis.z * rsin + normalizedAxis.x * normalizedAxis.y * (1 - rcos);
        mat[5] = rcos + normalizedAxis.y * normalizedAxis.y * (1 - rcos);
        mat[6] = normalizedAxis.x * rsin + normalizedAxis.z * normalizedAxis.y * (1 - rcos);
        mat[7] = 0.0;

        mat[8] = normalizedAxis.y * rsin + normalizedAxis.x * normalizedAxis.z * (1 - rcos);
        mat[9] = -normalizedAxis.x * rsin + normalizedAxis.y * normalizedAxis.z * (1 - rcos);
        mat[10] = rcos + normalizedAxis.z * normalizedAxis.z * (1 - rcos);
        mat[11] = 0.0;

        mat[12] = mat[13] = mat[14] = 0.0;
        mat[15] = 1.0;
        return matrix;
    };

    /**
     * Extract a 3x3 rotation matrix from the input 4x4 transformation.
     * @returns {cc.math.Matrix3}
     */
    proto.extractRotation = function(){
        var matrix = new cc.math.Matrix3(), mat4 = this.mat, mat3 = matrix.mat;
        mat3[0] = mat4[0];
        mat3[1] = mat4[1];
        mat3[2] = mat4[2];

        mat3[3] = mat4[4];
        mat3[4] = mat4[5];
        mat3[5] = mat4[6];

        mat3[6] = mat4[8];
        mat3[7] = mat4[9];
        mat3[8] = mat4[10];
        return matrix;
    };

    proto.extractPlane = function(planeType) {
        var plane = new cc.math.Plane(), mat = this.mat;
        switch (planeType) {
            case cc.math.Plane.RIGHT:
                plane.a = mat[3] - mat[0];
                plane.b = mat[7] - mat[4];
                plane.c = mat[11] - mat[8];
                plane.d = mat[15] - mat[12];
                break;
            case cc.math.Plane.LEFT:
                plane.a = mat[3] + mat[0];
                plane.b = mat[7] + mat[4];
                plane.c = mat[11] + mat[8];
                plane.d = mat[15] + mat[12];
                break;
            case cc.math.Plane.BOTTOM:
                plane.a = mat[3] + mat[1];
                plane.b = mat[7] + mat[5];
                plane.c = mat[11] + mat[9];
                plane.d = mat[15] + mat[13];
                break;
            case cc.math.Plane.TOP:
                plane.a = mat[3] - mat[1];
                plane.b = mat[7] - mat[5];
                plane.c = mat[11] - mat[9];
                plane.d = mat[15] - mat[13];
                break;
            case cc.math.Plane.FAR:
                plane.a = mat[3] - mat[2];
                plane.b = mat[7] - mat[6];
                plane.c = mat[11] - mat[10];
                plane.d = mat[15] - mat[14];
                break;
            case cc.math.Plane.NEAR:
                plane.a = mat[3] + mat[2];
                plane.b = mat[7] + mat[6];
                plane.c = mat[11] + mat[10];
                plane.d = mat[15] + mat[14];
                break;
            default:
                cc.log("cc.math.Matrix4.extractPlane: Invalid plane index");
                break;
        }

        var t = Math.sqrt(plane.a * plane.a + plane.b * plane.b + plane.c * plane.c);
        plane.a /= t;
        plane.b /= t;
        plane.c /= t;
        plane.d /= t;
        return plane;
    };

    /**
     * Take the rotation from a 4x4 transformation matrix, and return it as an axis and an angle (in radians)
     * @returns {*|{axis: cc.math.Vec3, angle: number}}
     */
    proto.toAxisAndAngle = function() {
        /*Surely not this easy?*/
        var rotation = this.extractRotation();
        var temp = cc.math.Quaternion.rotationMatrix(rotation);
        return temp.toAxisAndAngle();
    };
})(cc);




