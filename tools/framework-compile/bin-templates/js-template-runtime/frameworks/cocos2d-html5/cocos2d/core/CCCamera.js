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
 * <p>
 *     A CCCamera is used in every CCNode.                                                                                 <br/>
 *     The OpenGL gluLookAt() function is used to locate the camera.                                                       <br/>
 *                                                                                                                         <br/>
 *     If the object is transformed by any of the scale, rotation or position attributes, then they will override the camera.          <br/>
 *                                                                                                                                     <br/>
 *     IMPORTANT: Either your use the camera or the rotation/scale/position properties. You can't use both.                            <br/>
 *     World coordinates won't work if you use the camera.                                                                             <br/>
 *                                                                                                                                     <br/>
 *     Limitations:                                                                                                                    <br/>
 *     - Some nodes, like CCParallaxNode, CCParticle uses world node coordinates, and they won't work properly if you move them (or any of their ancestors)           <br/>
 *     using the camera.                                                                                                               <br/>
 *                                                                                                                                     <br/>
 *     - It doesn't work on batched nodes like CCSprite objects when they are parented to a CCSpriteBatchNode object.                  <br/>
 *                                                                                                                                     <br/>
 *     - It is recommended to use it ONLY if you are going to create 3D effects. For 2D effecs, use the action CCFollow or position/scale/rotate. *
 * </p>
 */
cc.Camera = cc.Class.extend({
    _eyeX:null,
    _eyeY:null,
    _eyeZ:null,

    _centerX:null,
    _centerY:null,
    _centerZ:null,

    _upX:null,
    _upY:null,
    _upZ:null,

    _dirty:false,
    _lookupMatrix:null,
    /**
     * constructor of cc.Camera
     */
    ctor:function () {
        this._lookupMatrix = new cc.math.Matrix4();
        this.restore();
    },

    /**
     * Description of cc.Camera
     * @return {String}
     */
    description:function () {
        return "<CCCamera | center =(" + this._centerX + "," + this._centerY + "," + this._centerZ + ")>";
    },

    /**
     * sets the dirty value
     * @param value
     */
    setDirty:function (value) {
        this._dirty = value;
    },

    /**
     * get the dirty value
     * @return {Boolean}
     */
    isDirty:function () {
        return this._dirty;
    },

    /**
     * sets the camera in the default position
     */
    restore:function () {
        this._eyeX = this._eyeY = 0.0;
        this._eyeZ = cc.Camera.getZEye();

        this._centerX = this._centerY = this._centerZ = 0.0;

        this._upX = 0.0;
        this._upY = 1.0;
        this._upZ = 0.0;

        this._lookupMatrix.identity();

        this._dirty = false;
    },

    /**
     * Sets the camera using gluLookAt using its eye, center and up_vector
     */
    locate:function () {
        if (this._dirty) {
            var eye = new cc.math.Vec3(this._eyeX, this._eyeY , this._eyeZ),
                center = new cc.math.Vec3(this._centerX, this._centerY, this._centerZ),
                up = new cc.math.Vec3(this._upX, this._upY, this._upZ);
            this._lookupMatrix.lookAt(eye, center, up);
            this._dirty = false;
        }
        cc.kmGLMultMatrix( this._lookupMatrix);
    },

    _locateForRenderer: function(matrix){
        if (this._dirty) {
            var eye = new cc.math.Vec3(this._eyeX, this._eyeY , this._eyeZ),
                center = new cc.math.Vec3(this._centerX, this._centerY, this._centerZ),
                up = new cc.math.Vec3(this._upX, this._upY, this._upZ);
            this._lookupMatrix.lookAt(eye, center, up);
            this._dirty = false;
        }
        matrix.multiply(this._lookupMatrix);
    },

    /**
     * sets the eye values in points
     * @param {Number} eyeX
     * @param {Number} eyeY
     * @param {Number} eyeZ
     * @deprecated This function will be deprecated sooner or later please use setEye instead.
     */
    setEyeXYZ:function (eyeX, eyeY, eyeZ) {
        this.setEye(eyeX,eyeY,eyeZ);
    },

    /**
     * sets the eye values in points
     * @param {Number} eyeX
     * @param {Number} eyeY
     * @param {Number} eyeZ
     */
    setEye:function (eyeX, eyeY, eyeZ) {
        this._eyeX = eyeX ;
        this._eyeY = eyeY ;
        this._eyeZ = eyeZ ;

        this._dirty = true;
    },

    /**
     * sets the center values in points
     * @param {Number} centerX
     * @param {Number} centerY
     * @param {Number} centerZ
     * @deprecated  This function will be deprecated sooner or later please use setCenter instead.
     */
    setCenterXYZ:function (centerX, centerY, centerZ) {
        this.setCenter(centerX,centerY,centerZ);
    },

    /**
     * sets the center values in points
     * @param {Number} centerX
     * @param {Number} centerY
     * @param {Number} centerZ
     */
    setCenter:function (centerX, centerY, centerZ) {
        this._centerX = centerX ;
        this._centerY = centerY ;
        this._centerZ = centerZ ;

        this._dirty = true;
    },

    /**
     * sets the up values
     * @param {Number} upX
     * @param {Number} upY
     * @param {Number} upZ
     * @deprecated This function will be deprecated sooner or later.
     */
    setUpXYZ:function (upX, upY, upZ) {
        this.setUp(upX, upY, upZ);
    },

    /**
     * sets the up values
     * @param {Number} upX
     * @param {Number} upY
     * @param {Number} upZ
     */
    setUp:function (upX, upY, upZ) {
        this._upX = upX;
        this._upY = upY;
        this._upZ = upZ;

        this._dirty = true;
    },

    /**
     * get the eye vector values in points  (return an object like {x:1,y:1,z:1} in HTML5)
     * @param {Number} eyeX
     * @param {Number} eyeY
     * @param {Number} eyeZ
     * @return {Object}
     * @deprecated This function will be deprecated sooner or later, please use getEye instead.
     */
    getEyeXYZ:function (eyeX, eyeY, eyeZ) {
        return {x:this._eyeX , y:this._eyeY , z: this._eyeZ };
    },

    /**
     * get the eye vector values in points  (return an object like {x:1,y:1,z:1} in HTML5)
     * @return {Object}
     */
    getEye:function () {
        return {x:this._eyeX , y:this._eyeY , z: this._eyeZ };
    },

    /**
     * get the center vector values int points (return an object like {x:1,y:1,z:1} in HTML5)
     * @param {Number} centerX
     * @param {Number} centerY
     * @param {Number} centerZ
     * @return {Object}
     * @deprecated This function will be deprecated sooner or later,please use getCenter instead.
     */
    getCenterXYZ:function (centerX, centerY, centerZ) {
        return {x:this._centerX ,y:this._centerY ,z:this._centerZ };
    },

    /**
     * get the center vector values int points (return an object like {x:1,y:1,z:1} in HTML5)
     * @return {Object}
     */
    getCenter:function () {
        return {x:this._centerX ,y:this._centerY ,z:this._centerZ };
    },

    /**
     * get the up vector values (return an object like {x:1,y:1,z:1} in HTML5)
     * @param {Number} upX
     * @param {Number} upY
     * @param {Number} upZ
     * @return {Object}
     * @deprecated This function will be deprecated sooner or later,please use getUp instead.
     */
    getUpXYZ:function (upX, upY, upZ) {
        return {x:this._upX,y:this._upY,z:this._upZ};
    },

    /**
     * get the up vector values (return an object like {x:1,y:1,z:1} in HTML5)
     * @return {Object}
     */
    getUp:function () {
        return {x:this._upX,y:this._upY,z:this._upZ};
    },

    _DISALLOW_COPY_AND_ASSIGN:function (CCCamera) {

    }
});

/**
 * returns the Z eye
 * @return {Number}
 */
cc.Camera.getZEye = function () {
    return cc.FLT_EPSILON;
};
