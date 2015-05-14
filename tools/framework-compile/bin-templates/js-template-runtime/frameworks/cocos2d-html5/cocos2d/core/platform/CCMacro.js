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
 * @constant
 * @type Number
 */
cc.INVALID_INDEX = -1;

/**
 * PI is the ratio of a circle's circumference to its diameter.
 * @constant
 * @type Number
 */
cc.PI = Math.PI;

/**
 * @constant
 * @type Number
 */
cc.FLT_MAX = parseFloat('3.402823466e+38F');

/**
 * @constant
 * @type Number
 */
cc.FLT_MIN = parseFloat("1.175494351e-38F");

/**
 * @constant
 * @type Number
 */
cc.RAD = cc.PI / 180;

/**
 * @constant
 * @type Number
 */
cc.DEG = 180 / cc.PI;

/**
 * maximum unsigned int value
 * @constant
 * @type Number
 */
cc.UINT_MAX = 0xffffffff;

/**
 * <p>
 * simple macro that swaps 2 variables<br/>
 *  modified from c++ macro, you need to pass in the x and y variables names in string, <br/>
 *  and then a reference to the whole object as third variable
 * </p>
 * @param {String} x
 * @param {String} y
 * @param {Object} ref
 * @function
 * @deprecated since v3.0
 */
cc.swap = function (x, y, ref) {
    if (cc.isObject(ref) && !cc.isUndefined(ref.x) && !cc.isUndefined(ref.y)) {
        var tmp = ref[x];
        ref[x] = ref[y];
        ref[y] = tmp;
    } else
        cc.log(cc._LogInfos.swap);
};

/**
 * <p>
 *     Linear interpolation between 2 numbers, the ratio sets how much it is biased to each end
 * </p>
 * @param {Number} a number A
 * @param {Number} b number B
 * @param {Number} r ratio between 0 and 1
 * @function
 * @example
 * cc.lerp(2,10,0.5)//returns 6<br/>
 * cc.lerp(2,10,0.2)//returns 3.6
 */
cc.lerp = function (a, b, r) {
    return a + (b - a) * r;
};

/**
 * get a random number from 0 to 0xffffff
 * @function
 * @returns {number}
 */
cc.rand = function () {
	return Math.random() * 0xffffff;
};

/**
 * returns a random float between -1 and 1
 * @return {Number}
 * @function
 */
cc.randomMinus1To1 = function () {
    return (Math.random() - 0.5) * 2;
};

/**
 * returns a random float between 0 and 1
 * @return {Number}
 * @function
 */
cc.random0To1 = Math.random;

/**
 * converts degrees to radians
 * @param {Number} angle
 * @return {Number}
 * @function
 */
cc.degreesToRadians = function (angle) {
    return angle * cc.RAD;
};

/**
 * converts radians to degrees
 * @param {Number} angle
 * @return {Number}
 * @function
 */
cc.radiansToDegrees = function (angle) {
    return angle * cc.DEG;
};
/**
 * converts radians to degrees
 * @param {Number} angle
 * @return {Number}
 * @function
 */
cc.radiansToDegress = function (angle) {
    cc.log(cc._LogInfos.radiansToDegress);
    return angle * cc.DEG;
};

/**
 * @constant
 * @type Number
 */
cc.REPEAT_FOREVER = Number.MAX_VALUE - 1;

/**
 * default gl blend src function. Compatible with premultiplied alpha images.
 * @constant
 * @type Number
 */
cc.BLEND_SRC = cc.OPTIMIZE_BLEND_FUNC_FOR_PREMULTIPLIED_ALPHA ? 1 : 0x0302;

/**
 * default gl blend dst function. Compatible with premultiplied alpha images.
 * @constant
 * @type Number
 */
cc.BLEND_DST = 0x0303;

/**
 * Helpful macro that setups the GL server state, the correct GL program and sets the Model View Projection matrix
 * @param {cc.Node} node setup node
 * @function
 */
cc.nodeDrawSetup = function (node) {
    //cc.glEnable(node._glServerState);
    if (node._shaderProgram) {
        //cc._renderContext.useProgram(node._shaderProgram._programObj);
        node._shaderProgram.use();
        node._shaderProgram.setUniformForModelViewAndProjectionMatrixWithMat4();
    }
};

/**
 * <p>
 *     GL states that are enabled:<br/>
 *       - GL_TEXTURE_2D<br/>
 *       - GL_VERTEX_ARRAY<br/>
 *       - GL_TEXTURE_COORD_ARRAY<br/>
 *       - GL_COLOR_ARRAY<br/>
 * </p>
 * @function
 */
cc.enableDefaultGLStates = function () {
    //TODO OPENGL STUFF
    /*
     glEnableClientState(GL_VERTEX_ARRAY);
     glEnableClientState(GL_COLOR_ARRAY);
     glEnableClientState(GL_TEXTURE_COORD_ARRAY);
     glEnable(GL_TEXTURE_2D);*/
};

/**
 * <p>
 *   Disable default GL states:<br/>
 *     - GL_TEXTURE_2D<br/>
 *     - GL_TEXTURE_COORD_ARRAY<br/>
 *     - GL_COLOR_ARRAY<br/>
 * </p>
 * @function
 */
cc.disableDefaultGLStates = function () {
    //TODO OPENGL
    /*
     glDisable(GL_TEXTURE_2D);
     glDisableClientState(GL_COLOR_ARRAY);
     glDisableClientState(GL_TEXTURE_COORD_ARRAY);
     glDisableClientState(GL_VERTEX_ARRAY);
     */
};

/**
 * <p>
 *  Increments the GL Draws counts by one.<br/>
 *  The number of calls per frame are displayed on the screen when the CCDirector's stats are enabled.<br/>
 * </p>
 * @param {Number} addNumber
 * @function
 */
cc.incrementGLDraws = function (addNumber) {
    cc.g_NumberOfDraws += addNumber;
};

/**
 * @constant
 * @type Number
 */
cc.FLT_EPSILON = 0.0000001192092896;

/**
 * <p>
 *     On Mac it returns 1;<br/>
 *     On iPhone it returns 2 if RetinaDisplay is On. Otherwise it returns 1
 * </p>
 * @return {Number}
 * @function
 */
cc.contentScaleFactor = cc.IS_RETINA_DISPLAY_SUPPORTED ? function () {
    return cc.director.getContentScaleFactor();
} : function () {
    return 1;
};

/**
 * Converts a Point in points to pixels
 * @param {cc.Point} points
 * @return {cc.Point}
 * @function
 */
cc.pointPointsToPixels = function (points) {
    var scale = cc.contentScaleFactor();
    return cc.p(points.x * scale, points.y * scale);
};

/**
 * Converts a Point in pixels to points
 * @param {cc.Rect} pixels
 * @return {cc.Point}
 * @function
 */
cc.pointPixelsToPoints = function (pixels) {
	var scale = cc.contentScaleFactor();
	return cc.p(pixels.x / scale, pixels.y / scale);
};

cc._pointPixelsToPointsOut = function(pixels, outPoint){
	var scale = cc.contentScaleFactor();
	outPoint.x = pixels.x / scale;
	outPoint.y = pixels.y / scale;
};

/**
 * Converts a Size in points to pixels
 * @param {cc.Size} sizeInPoints
 * @return {cc.Size}
 * @function
 */
cc.sizePointsToPixels = function (sizeInPoints) {
    var scale = cc.contentScaleFactor();
    return cc.size(sizeInPoints.width * scale, sizeInPoints.height * scale);
};

/**
 * Converts a size in pixels to points
 * @param {cc.Size} sizeInPixels
 * @return {cc.Size}
 * @function
 */
cc.sizePixelsToPoints = function (sizeInPixels) {
    var scale = cc.contentScaleFactor();
    return cc.size(sizeInPixels.width / scale, sizeInPixels.height / scale);
};

cc._sizePixelsToPointsOut = function (sizeInPixels, outSize) {
    var scale = cc.contentScaleFactor();
    outSize.width = sizeInPixels.width / scale;
    outSize.height = sizeInPixels.height / scale;
};

/**
 * Converts a rect in pixels to points
 * @param {cc.Rect} pixel
 * @return {cc.Rect}
 * @function
 */
cc.rectPixelsToPoints = cc.IS_RETINA_DISPLAY_SUPPORTED ? function (pixel) {
    var scale = cc.contentScaleFactor();
    return cc.rect(pixel.x / scale, pixel.y / scale,
        pixel.width / scale, pixel.height / scale);
} : function (p) {
    return p;
};

/**
 * Converts a rect in points to pixels
 * @param {cc.Rect} point
 * @return {cc.Rect}
 * @function
 */
cc.rectPointsToPixels = cc.IS_RETINA_DISPLAY_SUPPORTED ? function (point) {
   var scale = cc.contentScaleFactor();
    return cc.rect(point.x * scale, point.y * scale,
        point.width * scale, point.height * scale);
} : function (p) {
    return p;
};

//some gl constant variable
/**
 * @constant
 * @type Number
 */
cc.ONE = 1;

/**
 * @constant
 * @type Number
 */
cc.ZERO = 0;

/**
 * @constant
 * @type Number
 */
cc.SRC_ALPHA = 0x0302;

/**
 * @constant
 * @type Number
 */
cc.SRC_ALPHA_SATURATE = 0x308;

/**
 * @constant
 * @type Number
 */
cc.SRC_COLOR = 0x300;

/**
 * @constant
 * @type Number
 */
cc.DST_ALPHA = 0x304;

/**
 * @constant
 * @type Number
 */
cc.DST_COLOR = 0x306;

/**
 * @constant
 * @type Number
 */
cc.ONE_MINUS_SRC_ALPHA = 0x0303;

/**
 * @constant
 * @type Number
 */
cc.ONE_MINUS_SRC_COLOR = 0x301;

/**
 * @constant
 * @type Number
 */
cc.ONE_MINUS_DST_ALPHA = 0x305;

/**
 * @constant
 * @type Number
 */
cc.ONE_MINUS_DST_COLOR = 0x0307;

/**
 * @constant
 * @type Number
 */
cc.ONE_MINUS_CONSTANT_ALPHA	= 0x8004;

/**
 * @constant
 * @type Number
 */
cc.ONE_MINUS_CONSTANT_COLOR	= 0x8002;

/**
 * the constant variable equals gl.LINEAR for texture
 * @constant
 * @type Number
 */
cc.LINEAR	= 0x2601;

/**
 * the constant variable equals gl.REPEAT for texture
 * @constant
 * @type Number
 */
cc.REPEAT	= 0x2901;

/**
 * the constant variable equals gl.CLAMP_TO_EDGE for texture
 * @constant
 * @type Number
 */
cc.CLAMP_TO_EDGE	= 0x812f;

/**
 * the constant variable equals gl.MIRRORED_REPEAT for texture
 * @constant
 * @type Number
 */
cc.MIRRORED_REPEAT   = 0x8370;

/**
 * Check webgl error.Error will be shown in console if exists.
 * @function
 */
cc.checkGLErrorDebug = function () {
    if (cc.renderMode === cc._RENDER_TYPE_WEBGL) {
        var _error = cc._renderContext.getError();
        if (_error) {
            cc.log(cc._LogInfos.checkGLErrorDebug, _error);
        }
    }
};

//Possible device orientations
/**
 * Device oriented vertically, home button on the bottom (UIDeviceOrientationPortrait)
 * @constant
 * @type Number
 */
cc.DEVICE_ORIENTATION_PORTRAIT = 0;

/**
 * Device oriented horizontally, home button on the right (UIDeviceOrientationLandscapeLeft)
 * @constant
 * @type Number
 */
cc.DEVICE_ORIENTATION_LANDSCAPE_LEFT = 1;

/**
 * Device oriented vertically, home button on the top (UIDeviceOrientationPortraitUpsideDown)
 * @constant
 * @type Number
 */
cc.DEVICE_ORIENTATION_PORTRAIT_UPSIDE_DOWN = 2;

/**
 * Device oriented horizontally, home button on the left (UIDeviceOrientationLandscapeRight)
 * @constant
 * @type Number
 */
cc.DEVICE_ORIENTATION_LANDSCAPE_RIGHT = 3;

/**
 * In browsers, we only support 2 orientations by change window size.
 * @constant
 * @type Number
 */
cc.DEVICE_MAX_ORIENTATIONS = 2;


// ------------------- vertex attrib flags -----------------------------
/**
 * @constant
 * @type {Number}
 */
cc.VERTEX_ATTRIB_FLAG_NONE = 0;
/**
 * @constant
 * @type {Number}
 */
cc.VERTEX_ATTRIB_FLAG_POSITION = 1 << 0;
/**
 * @constant
 * @type {Number}
 */
cc.VERTEX_ATTRIB_FLAG_COLOR = 1 << 1;
/**
 * @constant
 * @type {Number}
 */
cc.VERTEX_ATTRIB_FLAG_TEX_COORDS = 1 << 2;
/**
 * @constant
 * @type {Number}
 */
cc.VERTEX_ATTRIB_FLAG_POS_COLOR_TEX = ( cc.VERTEX_ATTRIB_FLAG_POSITION | cc.VERTEX_ATTRIB_FLAG_COLOR | cc.VERTEX_ATTRIB_FLAG_TEX_COORDS );

/**
 * GL server side states
 * @constant
 * @type {Number}
 */
cc.GL_ALL = 0;

//-------------Vertex Attributes-----------
/**
 * @constant
 * @type {Number}
 */
cc.VERTEX_ATTRIB_POSITION = 0;
/**
 * @constant
 * @type {Number}
 */
cc.VERTEX_ATTRIB_COLOR = 1;
/**
 * @constant
 * @type {Number}
 */
cc.VERTEX_ATTRIB_TEX_COORDS = 2;
/**
 * @constant
 * @type {Number}
 */
cc.VERTEX_ATTRIB_MAX = 3;

//------------Uniforms------------------
/**
 * @constant
 * @type {Number}
 */
cc.UNIFORM_PMATRIX = 0;
/**
 * @constant
 * @type {Number}
 */
cc.UNIFORM_MVMATRIX = 1;
/**
 * @constant
 * @type {Number}
 */
cc.UNIFORM_MVPMATRIX = 2;
/**
 * @constant
 * @type {Number}
 */
cc.UNIFORM_TIME = 3;
/**
 * @constant
 * @type {Number}
 */
cc.UNIFORM_SINTIME = 4;
/**
 * @constant
 * @type {Number}
 */
cc.UNIFORM_COSTIME = 5;
/**
 * @constant
 * @type {Number}
 */
cc.UNIFORM_RANDOM01 = 6;
/**
 * @constant
 * @type {Number}
 */
cc.UNIFORM_SAMPLER = 7;
/**
 * @constant
 * @type {Number}
 */
cc.UNIFORM_MAX = 8;

//------------Shader Name---------------
/**
 * @constant
 * @type {String}
 */
cc.SHADER_POSITION_TEXTURECOLOR = "ShaderPositionTextureColor";
/**
 * @constant
 * @type {String}
 */
cc.SHADER_POSITION_TEXTURECOLORALPHATEST = "ShaderPositionTextureColorAlphaTest";
/**
 * @constant
 * @type {String}
 */
cc.SHADER_POSITION_COLOR = "ShaderPositionColor";
/**
 * @constant
 * @type {String}
 */
cc.SHADER_POSITION_TEXTURE = "ShaderPositionTexture";
/**
 * @constant
 * @type {String}
 */
cc.SHADER_POSITION_TEXTURE_UCOLOR = "ShaderPositionTexture_uColor";
/**
 * @constant
 * @type {String}
 */
cc.SHADER_POSITION_TEXTUREA8COLOR = "ShaderPositionTextureA8Color";
/**
 * @constant
 * @type {String}
 */
cc.SHADER_POSITION_UCOLOR = "ShaderPosition_uColor";
/**
 * @constant
 * @type {String}
 */
cc.SHADER_POSITION_LENGTHTEXTURECOLOR = "ShaderPositionLengthTextureColor";

//------------uniform names----------------
/**
 * @constant
 * @type {String}
 */
cc.UNIFORM_PMATRIX_S = "CC_PMatrix";
/**
 * @constant
 * @type {String}
 */
cc.UNIFORM_MVMATRIX_S = "CC_MVMatrix";
/**
 * @constant
 * @type {String}
 */
cc.UNIFORM_MVPMATRIX_S = "CC_MVPMatrix";
/**
 * @constant
 * @type {String}
 */
cc.UNIFORM_TIME_S = "CC_Time";
/**
 * @constant
 * @type {String}
 */
cc.UNIFORM_SINTIME_S = "CC_SinTime";
/**
 * @constant
 * @type {String}
 */
cc.UNIFORM_COSTIME_S = "CC_CosTime";
/**
 * @constant
 * @type {String}
 */
cc.UNIFORM_RANDOM01_S = "CC_Random01";
/**
 * @constant
 * @type {String}
 */
cc.UNIFORM_SAMPLER_S = "CC_Texture0";
/**
 * @constant
 * @type {String}
 */
cc.UNIFORM_ALPHA_TEST_VALUE_S = "CC_alpha_value";

//------------Attribute names--------------
/**
 * @constant
 * @type {String}
 */
cc.ATTRIBUTE_NAME_COLOR = "a_color";
/**
 * @constant
 * @type {String}
 */
cc.ATTRIBUTE_NAME_POSITION = "a_position";
/**
 * @constant
 * @type {String}
 */
cc.ATTRIBUTE_NAME_TEX_COORD = "a_texCoord";


/**
 * default size for font size
 * @constant
 * @type Number
 */
cc.ITEM_SIZE = 32;

/**
 * default tag for current item
 * @constant
 * @type Number
 */
cc.CURRENT_ITEM = 0xc0c05001;
/**
 * default tag for zoom action tag
 * @constant
 * @type Number
 */
cc.ZOOM_ACTION_TAG = 0xc0c05002;
/**
 * default tag for normal
 * @constant
 * @type Number
 */
cc.NORMAL_TAG = 8801;

/**
 * default selected tag
 * @constant
 * @type Number
 */
cc.SELECTED_TAG = 8802;

/**
 * default disabled tag
 * @constant
 * @type Number
 */
cc.DISABLE_TAG = 8803;


// Array utils

/**
 * Verify Array's Type
 * @param {Array} arr
 * @param {function} type
 * @return {Boolean}
 * @function
 */
cc.arrayVerifyType = function (arr, type) {
    if (arr && arr.length > 0) {
        for (var i = 0; i < arr.length; i++) {
            if (!(arr[i] instanceof  type)) {
                cc.log("element type is wrong!");
                return false;
            }
        }
    }
    return true;
};

/**
 * Searches for the first occurance of object and removes it. If object is not found the function has no effect.
 * @function
 * @param {Array} arr Source Array
 * @param {*} delObj  remove object
 */
cc.arrayRemoveObject = function (arr, delObj) {
    for (var i = 0, l = arr.length; i < l; i++) {
        if (arr[i] === delObj) {
            arr.splice(i, 1);
            break;
        }
    }
};

/**
 * Removes from arr all values in minusArr. For each Value in minusArr, the first matching instance in arr will be removed.
 * @function
 * @param {Array} arr Source Array
 * @param {Array} minusArr minus Array
 */
cc.arrayRemoveArray = function (arr, minusArr) {
    for (var i = 0, l = minusArr.length; i < l; i++) {
        cc.arrayRemoveObject(arr, minusArr[i]);
    }
};

/**
 * Inserts some objects at index
 * @function
 * @param {Array} arr
 * @param {Array} addObjs
 * @param {Number} index
 * @return {Array}
 */
cc.arrayAppendObjectsToIndex = function(arr, addObjs,index){
    arr.splice.apply(arr, [index, 0].concat(addObjs));
    return arr;
};

/**
 * Copy an array's item to a new array (its performance is better than Array.slice)
 * @param {Array} arr
 * @return {Array}
 */
cc.copyArray = function(arr){
    var i, len = arr.length, arr_clone = new Array(len);
    for (i = 0; i < len; i += 1)
        arr_clone[i] = arr[i];
    return arr_clone;
};