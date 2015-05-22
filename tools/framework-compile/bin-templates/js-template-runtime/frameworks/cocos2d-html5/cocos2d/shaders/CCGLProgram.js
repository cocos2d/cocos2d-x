/****************************************************************************
 Copyright (c) 2008-2010 Ricardo Quesada
 Copyright (c) 2011-2012 cocos2d-x.org
 Copyright (c) 2013-2014 Chukong Technologies Inc.
 Copyright 2011 Jeff Lamarche
 Copyright 2012 Goffredo Marocchi

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

cc.HashUniformEntry = function (value, location, hh) {
    this.value = value;
    this.location = location;
    this.hh = hh || {};
};

/**
 * Class that implements a WebGL program
 * @class
 * @extends cc.Class
 */
cc.GLProgram = cc.Class.extend(/** @lends cc.GLProgram# */{
    _glContext: null,
    _programObj: null,
    _vertShader: null,
    _fragShader: null,
    _uniforms: null,
    _hashForUniforms: null,
    _usesTime: false,

    // Uniform cache
    _updateUniformLocation: function (location, data, bytes) {
        if (location == null)
            return false;

        var updated = true;
        var element = null;
        for (var i = 0; i < this._hashForUniforms.length; i++)
            if (this._hashForUniforms[i].location == location)
                element = this._hashForUniforms[i];

        if (!element) {
            element = new cc.HashUniformEntry();
            // key
            element.location = location;
            // value
            element.value = data;
            this._hashForUniforms.push(element);
        } else {
            if (element.value == data)
                updated = false;
            else
                element.value = data;
        }

        return updated;
    },

    _description: function () {
        return "<CCGLProgram = " + this.toString() + " | Program = " + this._programObj.toString() + ", VertexShader = " +
            this._vertShader.toString() + ", FragmentShader = " + this._fragShader.toString() + ">";
    },

    _compileShader: function (shader, type, source) {
        if (!source || !shader)
            return false;

        var preStr = cc.GLProgram._isHighpSupported() ? "precision highp float;\n" : "precision mediump float;\n";
        source = preStr
            + "uniform mat4 CC_PMatrix;         \n"
            + "uniform mat4 CC_MVMatrix;        \n"
            + "uniform mat4 CC_MVPMatrix;       \n"
            + "uniform vec4 CC_Time;            \n"
            + "uniform vec4 CC_SinTime;         \n"
            + "uniform vec4 CC_CosTime;         \n"
            + "uniform vec4 CC_Random01;        \n"
            + "uniform sampler2D CC_Texture0;   \n"
            + "//CC INCLUDES END                \n" + source;

        this._glContext.shaderSource(shader, source);
        this._glContext.compileShader(shader);
        var status = this._glContext.getShaderParameter(shader, this._glContext.COMPILE_STATUS);

        if (!status) {
            cc.log("cocos2d: ERROR: Failed to compile shader:\n" + this._glContext.getShaderSource(shader));
            if (type === this._glContext.VERTEX_SHADER)
                cc.log("cocos2d: \n" + this.vertexShaderLog());
            else
                cc.log("cocos2d: \n" + this.fragmentShaderLog());
        }
        return ( status === true );
    },

	/**
	 * Create a cc.GLProgram object
	 * @param {String} vShaderFileName
	 * @param {String} fShaderFileName
	 * @returns {cc.GLProgram}
	 */
    ctor: function (vShaderFileName, fShaderFileName, glContext) {
        this._uniforms = [];
        this._hashForUniforms = [];
        this._glContext = glContext || cc._renderContext;

		vShaderFileName && fShaderFileName && this.init(vShaderFileName, fShaderFileName);
    },

    /**
     * destroy program
     */
    destroyProgram: function () {
        this._vertShader = null;
        this._fragShader = null;
        this._uniforms = null;
        this._hashForUniforms = null;

        this._glContext.deleteProgram(this._programObj);
    },

    /**
     * Initializes the cc.GLProgram with a vertex and fragment with string
     * @param {String} vertShaderStr
     * @param {String} fragShaderStr
     * @return {Boolean}
     */
    initWithVertexShaderByteArray: function (vertShaderStr, fragShaderStr) {
        var locGL = this._glContext;
        this._programObj = locGL.createProgram();
        //cc.checkGLErrorDebug();

        this._vertShader = null;
        this._fragShader = null;

        if (vertShaderStr) {
            this._vertShader = locGL.createShader(locGL.VERTEX_SHADER);
            if (!this._compileShader(this._vertShader, locGL.VERTEX_SHADER, vertShaderStr)) {
                cc.log("cocos2d: ERROR: Failed to compile vertex shader");
            }
        }

        // Create and compile fragment shader
        if (fragShaderStr) {
            this._fragShader = locGL.createShader(locGL.FRAGMENT_SHADER);
            if (!this._compileShader(this._fragShader, locGL.FRAGMENT_SHADER, fragShaderStr)) {
                cc.log("cocos2d: ERROR: Failed to compile fragment shader");
            }
        }

        if (this._vertShader)
            locGL.attachShader(this._programObj, this._vertShader);
        cc.checkGLErrorDebug();

        if (this._fragShader)
            locGL.attachShader(this._programObj, this._fragShader);
        this._hashForUniforms.length = 0;

        cc.checkGLErrorDebug();
        return true;
    },

    /**
     * Initializes the cc.GLProgram with a vertex and fragment with string
     * @param {String} vertShaderStr
     * @param {String} fragShaderStr
     * @return {Boolean}
     */
    initWithString: function (vertShaderStr, fragShaderStr) {
        return this.initWithVertexShaderByteArray(vertShaderStr, fragShaderStr);
    },

    /**
     * Initializes the CCGLProgram with a vertex and fragment with contents of filenames
     * @param {String} vShaderFilename
     * @param {String} fShaderFileName
     * @return {Boolean}
     */
    initWithVertexShaderFilename: function (vShaderFilename, fShaderFileName) {
        var vertexSource = cc.loader.getRes(vShaderFilename);
        if(!vertexSource) throw "Please load the resource firset : " + vShaderFilename;
        var fragmentSource = cc.loader.getRes(fShaderFileName);
        if(!fragmentSource) throw "Please load the resource firset : " + fShaderFileName;
        return this.initWithVertexShaderByteArray(vertexSource, fragmentSource);
    },

    /**
     * Initializes the CCGLProgram with a vertex and fragment with contents of filenames
     * @param {String} vShaderFilename
     * @param {String} fShaderFileName
     * @return {Boolean}
     */
    init: function (vShaderFilename, fShaderFileName) {
        return this.initWithVertexShaderFilename(vShaderFilename, fShaderFileName);
    },

    /**
     * It will add a new attribute to the shader
     * @param {String} attributeName
     * @param {Number} index
     */
    addAttribute: function (attributeName, index) {
        this._glContext.bindAttribLocation(this._programObj, index, attributeName);
    },

    /**
     * links the glProgram
     * @return {Boolean}
     */
    link: function () {
        if(!this._programObj) {
            cc.log("cc.GLProgram.link(): Cannot link invalid program");
            return false;
        }

        this._glContext.linkProgram(this._programObj);

        if (this._vertShader)
            this._glContext.deleteShader(this._vertShader);
        if (this._fragShader)
            this._glContext.deleteShader(this._fragShader);

        this._vertShader = null;
        this._fragShader = null;

        if (cc.game.config[cc.game.CONFIG_KEY.debugMode]) {
            var status = this._glContext.getProgramParameter(this._programObj, this._glContext.LINK_STATUS);
            if (!status) {
                cc.log("cocos2d: ERROR: Failed to link program: " + this._glContext.getProgramInfoLog(this._programObj));
                cc.glDeleteProgram(this._programObj);
                this._programObj = null;
                return false;
            }
        }

        return true;
    },

    /**
     * it will call glUseProgram()
     */
    use: function () {
        cc.glUseProgram(this._programObj);
    },

    /**
     * It will create 4 uniforms:
     *  cc.UNIFORM_PMATRIX
     *  cc.UNIFORM_MVMATRIX
     *  cc.UNIFORM_MVPMATRIX
     *  cc.UNIFORM_SAMPLER
     */
    updateUniforms: function () {
        this._uniforms[cc.UNIFORM_PMATRIX] = this._glContext.getUniformLocation(this._programObj, cc.UNIFORM_PMATRIX_S);
        this._uniforms[cc.UNIFORM_MVMATRIX] = this._glContext.getUniformLocation(this._programObj, cc.UNIFORM_MVMATRIX_S);
        this._uniforms[cc.UNIFORM_MVPMATRIX] = this._glContext.getUniformLocation(this._programObj, cc.UNIFORM_MVPMATRIX_S);
        this._uniforms[cc.UNIFORM_TIME] = this._glContext.getUniformLocation(this._programObj, cc.UNIFORM_TIME_S);
        this._uniforms[cc.UNIFORM_SINTIME] = this._glContext.getUniformLocation(this._programObj, cc.UNIFORM_SINTIME_S);
        this._uniforms[cc.UNIFORM_COSTIME] = this._glContext.getUniformLocation(this._programObj, cc.UNIFORM_COSTIME_S);

        this._usesTime = (this._uniforms[cc.UNIFORM_TIME] != null || this._uniforms[cc.UNIFORM_SINTIME] != null || this._uniforms[cc.UNIFORM_COSTIME] != null);

        this._uniforms[cc.UNIFORM_RANDOM01] = this._glContext.getUniformLocation(this._programObj, cc.UNIFORM_RANDOM01_S);
        this._uniforms[cc.UNIFORM_SAMPLER] = this._glContext.getUniformLocation(this._programObj, cc.UNIFORM_SAMPLER_S);

        this.use();
        // Since sample most probably won't change, set it to 0 now.
        this.setUniformLocationWith1i(this._uniforms[cc.UNIFORM_SAMPLER], 0);
    },

    /**
     * calls retrieves the named uniform location for this shader program.
     * @param {String} name
     * @returns {Number}
     */
    getUniformLocationForName:function(name){
        if(!name)
            throw "cc.GLProgram.getUniformLocationForName(): uniform name should be non-null";
        if(!this._programObj)
            throw "cc.GLProgram.getUniformLocationForName(): Invalid operation. Cannot get uniform location when program is not initialized";

        return this._glContext.getUniformLocation(this._programObj, name);
    },

    /**
     * get uniform MVP matrix
     * @returns {WebGLUniformLocation}
     */
    getUniformMVPMatrix: function () {
        return this._uniforms[cc.UNIFORM_MVPMATRIX];
    },

    /**
     * get uniform sampler
     * @returns {WebGLUniformLocation}
     */
    getUniformSampler: function () {
        return this._uniforms[cc.UNIFORM_SAMPLER];
    },

    /**
     * calls glUniform1i only if the values are different than the previous call for this same shader program.
     * @param {WebGLUniformLocation} location
     * @param {Number} i1
     */
    setUniformLocationWith1i: function (location, i1) {
        var updated = this._updateUniformLocation(location, i1);
        if (updated)
            this._glContext.uniform1i(location, i1);
    },

    /**
     * calls glUniform2i only if the values are different than the previous call for this same shader program.
     * @param {WebGLUniformLocation} location
     * @param {Number} i1
     * @param {Number} i2
     */
    setUniformLocationWith2i:function(location, i1,i2){
        var intArray= [i1,i2];
        var updated =  this._updateUniformLocation(location, intArray);

        if( updated )
            this._glContext.uniform2i(location, i1, i2);
    },

    /**
     * calls glUniform3i only if the values are different than the previous call for this same shader program.
     * @param {WebGLUniformLocation} location
     * @param {Number} i1
     * @param {Number} i2
     * @param {Number} i3
     */
    setUniformLocationWith3i:function(location, i1, i2, i3){
        var intArray = [i1,i2,i3];
        var updated =  this._updateUniformLocation(location, intArray);

        if( updated )
            this._glContext.uniform3i(location, i1, i2, i3);
    },

    /**
     * calls glUniform4i only if the values are different than the previous call for this same shader program.
     * @param {WebGLUniformLocation} location
     * @param {Number} i1
     * @param {Number} i2
     * @param {Number} i3
     * @param {Number} i4
     */
    setUniformLocationWith4i:function(location, i1, i2, i3, i4){
        var intArray = [i1,i2,i3,i4];
        var updated =  this._updateUniformLocation(location, intArray);

        if( updated )
            this._glContext.uniform4i(location, i1, i2, i3, i4);
    },

    /**
     * calls glUniform2iv only if the values are different than the previous call for this same shader program.
     * @param {WebGLUniformLocation} location
     * @param {Int32Array} intArray
     * @param {Number} numberOfArrays
     */
    setUniformLocationWith2iv:function(location, intArray, numberOfArrays){
        var updated =  this._updateUniformLocation(location, intArray);

        if( updated )
            this._glContext.uniform2iv(location, intArray);
    },

    /**
     * calls glUniform3iv only if the values are different than the previous call for this same shader program.
     * @param {WebGLUniformLocation} location
     * @param {Int32Array} intArray
     * @param {Number} numberOfArrays
     */
    setUniformLocationWith3iv:function(location, intArray, numberOfArrays){
        var updated =  this._updateUniformLocation(location, intArray);

        if( updated )
            this._glContext.uniform3iv(location, intArray);
    },

    /**
     * calls glUniform4iv only if the values are different than the previous call for this same shader program.
     * @param {WebGLUniformLocation} location
     * @param {Int32Array} intArray
     * @param {Number} numberOfArrays
     */
    setUniformLocationWith4iv:function(location, intArray, numberOfArrays){
        var updated =  this._updateUniformLocation(location, intArray);

        if( updated )
            this._glContext.uniform4iv(location, intArray);
    },

    /**
     * calls glUniform1i only if the values are different than the previous call for this same shader program.
     * @param {WebGLUniformLocation} location
     * @param {Number} i1
     */
    setUniformLocationI32: function (location, i1) {
        this.setUniformLocationWith1i(arguments[0], arguments[1]);
    },

    /**
     * calls glUniform1f only if the values are different than the previous call for this same shader program.
     * @param {WebGLUniformLocation} location
     * @param {Number} f1
     */
    setUniformLocationWith1f: function (location, f1) {
        var updated = this._updateUniformLocation(location, f1);
        if (updated)
            this._glContext.uniform1f(location, f1);
    },

    /**
     * calls glUniform2f only if the values are different than the previous call for this same shader program.
     * @param {WebGLUniformLocation} location
     * @param {Number} f1
     * @param {Number} f2
     */
    setUniformLocationWith2f: function (location, f1, f2) {
        var floats = [f1, f2];
        var updated = this._updateUniformLocation(location, floats);
        if (updated)
            this._glContext.uniform2f(location, f1, f2);
    },

    /**
     * calls glUniform3f only if the values are different than the previous call for this same shader program.
     * @param {WebGLUniformLocation} location
     * @param {Number} f1
     * @param {Number} f2
     * @param {Number} f3
     */
    setUniformLocationWith3f: function (location, f1, f2, f3) {
        var floats = [f1, f2, f3];
        var updated = this._updateUniformLocation(location, floats);
        if (updated)
            this._glContext.uniform3f(location, f1, f2, f3);
    },

    /**
     * calls glUniform4f only if the values are different than the previous call for this same shader program.
     * @param {WebGLUniformLocation} location
     * @param {Number} f1
     * @param {Number} f2
     * @param {Number} f3
     * @param {Number} f4
     */
    setUniformLocationWith4f: function (location, f1, f2, f3, f4) {
        var floats = [f1, f2, f3, f4];
        var updated = this._updateUniformLocation(location, floats);
        if (updated)
            this._glContext.uniform4f(location, f1, f2, f3, f4);
    },

    /**
     * calls glUniform2fv only if the values are different than the previous call for this same shader program.
     * @param {WebGLUniformLocation} location
     * @param {Float32Array} floatArray
     * @param {Number} numberOfArrays
     */
    setUniformLocationWith2fv: function (location, floatArray, numberOfArrays) {
        var updated = this._updateUniformLocation(location, floatArray);
        if (updated)
            this._glContext.uniform2fv(location, floatArray);
    },

    /**
     * calls glUniform3fv only if the values are different than the previous call for this same shader program.
     * @param {WebGLUniformLocation} location
     * @param {Float32Array} floatArray
     * @param {Number} numberOfArrays
     */
    setUniformLocationWith3fv: function (location, floatArray, numberOfArrays) {
        var updated = this._updateUniformLocation(location, floatArray);
        if (updated)
            this._glContext.uniform3fv(location, floatArray);
    },

    /**
     * calls glUniform4fv only if the values are different than the previous call for this same shader program.
     * @param {WebGLUniformLocation} location
     * @param {Float32Array} floatArray
     * @param {Number} numberOfArrays
     */
    setUniformLocationWith4fv: function (location, floatArray, numberOfArrays) {
        var updated = this._updateUniformLocation(location, floatArray);
        if (updated)
            this._glContext.uniform4fv(location, floatArray);
    },

    /**
     * calls glUniformMatrix4fv only if the values are different than the previous call for this same shader program.
     * @param {WebGLUniformLocation} location
     * @param {Float32Array} matrixArray
     * @param {Number} numberOfMatrices
     */
    setUniformLocationWithMatrix4fv: function (location, matrixArray, numberOfMatrices) {
        var updated = this._updateUniformLocation(location, matrixArray);
        if (updated)
            this._glContext.uniformMatrix4fv(location, false, matrixArray);
    },

    setUniformLocationF32: function () {
        if (arguments.length < 2)
            return;

        switch (arguments.length) {
            case 2:
                this.setUniformLocationWith1f(arguments[0], arguments[1]);
                break;
            case 3:
                this.setUniformLocationWith2f(arguments[0], arguments[1], arguments[2]);
                break;
            case 4:
                this.setUniformLocationWith3f(arguments[0], arguments[1], arguments[2], arguments[3]);
                break;
            case 5:
                this.setUniformLocationWith4f(arguments[0], arguments[1], arguments[2], arguments[3], arguments[4]);
                break;
        }
    },

    /**
     * will update the builtin uniforms if they are different than the previous call for this same shader program.
     */
    setUniformsForBuiltins: function () {
        var matrixP = new cc.math.Matrix4();
        var matrixMV = new cc.math.Matrix4();
        var matrixMVP = new cc.math.Matrix4();

        cc.kmGLGetMatrix(cc.KM_GL_PROJECTION, matrixP);
        cc.kmGLGetMatrix(cc.KM_GL_MODELVIEW, matrixMV);

        cc.kmMat4Multiply(matrixMVP, matrixP, matrixMV);

        this.setUniformLocationWithMatrix4fv(this._uniforms[cc.UNIFORM_PMATRIX], matrixP.mat, 1);
        this.setUniformLocationWithMatrix4fv(this._uniforms[cc.UNIFORM_MVMATRIX], matrixMV.mat, 1);
        this.setUniformLocationWithMatrix4fv(this._uniforms[cc.UNIFORM_MVPMATRIX], matrixMVP.mat, 1);

        if (this._usesTime) {
            var director = cc.director;
            // This doesn't give the most accurate global time value.
            // Cocos2D doesn't store a high precision time value, so this will have to do.
            // Getting Mach time per frame per shader using time could be extremely expensive.
            var time = director.getTotalFrames() * director.getAnimationInterval();

            this.setUniformLocationWith4f(this._uniforms[cc.UNIFORM_TIME], time / 10.0, time, time * 2, time * 4);
            this.setUniformLocationWith4f(this._uniforms[cc.UNIFORM_SINTIME], time / 8.0, time / 4.0, time / 2.0, Math.sin(time));
            this.setUniformLocationWith4f(this._uniforms[cc.UNIFORM_COSTIME], time / 8.0, time / 4.0, time / 2.0, Math.cos(time));
        }

        if (this._uniforms[cc.UNIFORM_RANDOM01] !== -1)
            this.setUniformLocationWith4f(this._uniforms[cc.UNIFORM_RANDOM01], Math.random(), Math.random(), Math.random(), Math.random());
    },

    _setUniformsForBuiltinsForRenderer: function (node) {
        if(!node || !node._renderCmd)
            return;

        var matrixP = new cc.math.Matrix4();
        //var matrixMV = new cc.kmMat4();
        var matrixMVP = new cc.math.Matrix4();

        cc.kmGLGetMatrix(cc.KM_GL_PROJECTION, matrixP);
        //cc.kmGLGetMatrix(cc.KM_GL_MODELVIEW, node._stackMatrix);

        cc.kmMat4Multiply(matrixMVP, matrixP, node._renderCmd._stackMatrix);

        this.setUniformLocationWithMatrix4fv(this._uniforms[cc.UNIFORM_PMATRIX], matrixP.mat, 1);
        this.setUniformLocationWithMatrix4fv(this._uniforms[cc.UNIFORM_MVMATRIX], node._renderCmd._stackMatrix.mat, 1);
        this.setUniformLocationWithMatrix4fv(this._uniforms[cc.UNIFORM_MVPMATRIX], matrixMVP.mat, 1);

        if (this._usesTime) {
            var director = cc.director;
            // This doesn't give the most accurate global time value.
            // Cocos2D doesn't store a high precision time value, so this will have to do.
            // Getting Mach time per frame per shader using time could be extremely expensive.
            var time = director.getTotalFrames() * director.getAnimationInterval();

            this.setUniformLocationWith4f(this._uniforms[cc.UNIFORM_TIME], time / 10.0, time, time * 2, time * 4);
            this.setUniformLocationWith4f(this._uniforms[cc.UNIFORM_SINTIME], time / 8.0, time / 4.0, time / 2.0, Math.sin(time));
            this.setUniformLocationWith4f(this._uniforms[cc.UNIFORM_COSTIME], time / 8.0, time / 4.0, time / 2.0, Math.cos(time));
        }

        if (this._uniforms[cc.UNIFORM_RANDOM01] !== -1)
            this.setUniformLocationWith4f(this._uniforms[cc.UNIFORM_RANDOM01], Math.random(), Math.random(), Math.random(), Math.random());
    },

    /**
     * will update the MVP matrix on the MVP uniform if it is different than the previous call for this same shader program.
     */
    setUniformForModelViewProjectionMatrix: function () {
        this._glContext.uniformMatrix4fv(this._uniforms[cc.UNIFORM_MVPMATRIX], false,
            cc.getMat4MultiplyValue(cc.projection_matrix_stack.top, cc.modelview_matrix_stack.top));
    },

    setUniformForModelViewProjectionMatrixWithMat4: function (swapMat4) {
        cc.kmMat4Multiply(swapMat4, cc.projection_matrix_stack.top, cc.modelview_matrix_stack.top);
        this._glContext.uniformMatrix4fv(this._uniforms[cc.UNIFORM_MVPMATRIX], false, swapMat4.mat);
    },

    setUniformForModelViewAndProjectionMatrixWithMat4: function () {
        this._glContext.uniformMatrix4fv(this._uniforms[cc.UNIFORM_MVMATRIX], false, cc.modelview_matrix_stack.top.mat);
        this._glContext.uniformMatrix4fv(this._uniforms[cc.UNIFORM_PMATRIX], false, cc.projection_matrix_stack.top.mat);
    },

    _setUniformForMVPMatrixWithMat4: function(modelViewMatrix){
        if(!modelViewMatrix)
            throw "modelView matrix is undefined.";
        this._glContext.uniformMatrix4fv(this._uniforms[cc.UNIFORM_MVMATRIX], false, modelViewMatrix.mat);
        this._glContext.uniformMatrix4fv(this._uniforms[cc.UNIFORM_PMATRIX], false, cc.projection_matrix_stack.top.mat);
    },

    /**
     * returns the vertexShader error log
     * @return {String}
     */
    vertexShaderLog: function () {
        return this._glContext.getShaderInfoLog(this._vertShader);
    },

    /**
     * returns the vertexShader error log
     * @return {String}
     */
    getVertexShaderLog: function () {
        return this._glContext.getShaderInfoLog(this._vertShader);
    },

    /**
     * returns the fragmentShader error log
     * @returns {String}
     */
    getFragmentShaderLog: function () {
        return this._glContext.getShaderInfoLog(this._vertShader);
    },

    /**
     * returns the fragmentShader error log
     * @return {String}
     */
    fragmentShaderLog: function () {
        return this._glContext.getShaderInfoLog(this._fragShader);
    },

    /**
     * returns the program error log
     * @return {String}
     */
    programLog: function () {
        return this._glContext.getProgramInfoLog(this._programObj);
    },

    /**
     * returns the program error log
     * @return {String}
     */
    getProgramLog: function () {
        return this._glContext.getProgramInfoLog(this._programObj);
    },

    /**
     *  reload all shaders, this function is designed for android  <br/>
     *  when opengl context lost, so don't call it.
     */
    reset: function () {
        this._vertShader = null;
        this._fragShader = null;
        this._uniforms.length = 0;

        // it is already deallocated by android
        //ccGLDeleteProgram(m_uProgram);
        this._glContext.deleteProgram(this._programObj);
        this._programObj = null;

        // Purge uniform hash
        for (var i = 0; i < this._hashForUniforms.length; i++) {
            this._hashForUniforms[i].value = null;
            this._hashForUniforms[i] = null;
        }

        this._hashForUniforms.length = 0;
    },

    /**
     * get WebGLProgram object
     * @return {WebGLProgram}
     */
    getProgram: function () {
        return this._programObj;
    },

    /**
     * Currently JavaScript Bindings (JSB), in some cases, needs to use retain and release. This is a bug in JSB,
     * and the ugly workaround is to use retain/release. So, these 2 methods were added to be compatible with JSB.
     * This is a hack, and should be removed once JSB fixes the retain/release bug
     */
    retain: function () {
    },
    release: function () {
    }
});

/**
 * Create a cc.GLProgram object
 * @deprecated since v3.0, please use new cc.GLProgram(vShaderFileName, fShaderFileName) instead
 * @param {String} vShaderFileName
 * @param {String} fShaderFileName
 * @returns {cc.GLProgram}
 */
cc.GLProgram.create = function (vShaderFileName, fShaderFileName) {
    return new cc.GLProgram(vShaderFileName, fShaderFileName);
};

cc.GLProgram._highpSupported = null;

cc.GLProgram._isHighpSupported = function(){
    if(cc.GLProgram._highpSupported == null){
        var ctx = cc._renderContext;
        var highp = ctx.getShaderPrecisionFormat(ctx.FRAGMENT_SHADER, ctx.HIGH_FLOAT);
        cc.GLProgram._highpSupported = highp.precision !== 0;
    }
    return cc.GLProgram._highpSupported;
};

/**
 * <p>
 *     Sets the shader program for this node
 *
 *     Since v2.0, each rendering node must set its shader program.
 *     It should be set in initialize phase.
 * </p>
 * @function
 * @param {cc.Node} node
 * @param {cc.GLProgram} program The shader program which fetches from CCShaderCache.
 * @example
 * cc.setGLProgram(node, cc.shaderCache.programForKey(cc.SHADER_POSITION_TEXTURECOLOR));
 */
cc.setProgram = function (node, program) {
    node.shaderProgram = program;

    var children = node.children;
    if (!children)
        return;

    for (var i = 0; i < children.length; i++)
        cc.setProgram(children[i], program);
};
