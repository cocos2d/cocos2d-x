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
 * cc.shaderCache is a singleton object that stores manages GL shaders
 * @class
 * @name cc.shaderCache
 */
cc.shaderCache = /** @lends cc.shaderCache# */{

	/**
	 * @public
	 * @constant
	 * @type {Number}
	 */
	TYPE_POSITION_TEXTURECOLOR: 0,
	/**
	 * @public
	 * @constant
	 * @type {Number}
	 */
	TYPE_POSITION_TEXTURECOLOR_ALPHATEST: 1,
	/**
	 * @public
	 * @constant
	 * @type {Number}
	 */
	TYPE_POSITION_COLOR: 2,
	/**
	 * @public
	 * @constant
	 * @type {Number}
	 */
	TYPE_POSITION_TEXTURE: 3,
	/**
	 * @public
	 * @constant
	 * @type {Number}
	 */
	TYPE_POSITION_TEXTURE_UCOLOR: 4,
	/**
	 * @public
	 * @constant
	 * @type {Number}
	 */
	TYPE_POSITION_TEXTURE_A8COLOR: 5,
	/**
	 * @public
	 * @constant
	 * @type {Number}
	 */
	TYPE_POSITION_UCOLOR: 6,
	/**
	 * @public
	 * @constant
	 * @type {Number}
	 */
	TYPE_POSITION_LENGTH_TEXTURECOLOR: 7,
	/**
	 * @public
	 * @constant
	 * @type {Number}
	 */
	TYPE_MAX: 8,

    _programs: {},

    _init: function () {
        this.loadDefaultShaders();
        return true;
    },

    _loadDefaultShader: function (program, type) {
        switch (type) {
            case this.TYPE_POSITION_TEXTURECOLOR:
                program.initWithVertexShaderByteArray(cc.SHADER_POSITION_TEXTURE_COLOR_VERT, cc.SHADER_POSITION_TEXTURE_COLOR_FRAG);

                program.addAttribute(cc.ATTRIBUTE_NAME_POSITION, cc.VERTEX_ATTRIB_POSITION);
                program.addAttribute(cc.ATTRIBUTE_NAME_COLOR, cc.VERTEX_ATTRIB_COLOR);
                program.addAttribute(cc.ATTRIBUTE_NAME_TEX_COORD, cc.VERTEX_ATTRIB_TEX_COORDS);
                break;
            case this.TYPE_POSITION_TEXTURECOLOR_ALPHATEST:
                program.initWithVertexShaderByteArray(cc.SHADER_POSITION_TEXTURE_COLOR_VERT, cc.SHADER_POSITION_TEXTURE_COLOR_ALPHATEST_FRAG);

                program.addAttribute(cc.ATTRIBUTE_NAME_POSITION, cc.VERTEX_ATTRIB_POSITION);
                program.addAttribute(cc.ATTRIBUTE_NAME_COLOR, cc.VERTEX_ATTRIB_COLOR);
                program.addAttribute(cc.ATTRIBUTE_NAME_TEX_COORD, cc.VERTEX_ATTRIB_TEX_COORDS);
                break;
            case this.TYPE_POSITION_COLOR:
                program.initWithVertexShaderByteArray(cc.SHADER_POSITION_COLOR_VERT, cc.SHADER_POSITION_COLOR_FRAG);

                program.addAttribute(cc.ATTRIBUTE_NAME_POSITION, cc.VERTEX_ATTRIB_POSITION);
                program.addAttribute(cc.ATTRIBUTE_NAME_COLOR, cc.VERTEX_ATTRIB_COLOR);
                break;
            case this.TYPE_POSITION_TEXTURE:
                program.initWithVertexShaderByteArray(cc.SHADER_POSITION_TEXTURE_VERT, cc.SHADER_POSITION_TEXTURE_FRAG);

                program.addAttribute(cc.ATTRIBUTE_NAME_POSITION, cc.VERTEX_ATTRIB_POSITION);
                program.addAttribute(cc.ATTRIBUTE_NAME_TEX_COORD, cc.VERTEX_ATTRIB_TEX_COORDS);
                break;
            case this.TYPE_POSITION_TEXTURE_UCOLOR:
                program.initWithVertexShaderByteArray(cc.SHADER_POSITION_TEXTURE_UCOLOR_VERT, cc.SHADER_POSITION_TEXTURE_UCOLOR_FRAG);

                program.addAttribute(cc.ATTRIBUTE_NAME_POSITION, cc.VERTEX_ATTRIB_POSITION);
                program.addAttribute(cc.ATTRIBUTE_NAME_TEX_COORD, cc.VERTEX_ATTRIB_TEX_COORDS);
                break;
            case this.TYPE_POSITION_TEXTURE_A8COLOR:
                program.initWithVertexShaderByteArray(cc.SHADER_POSITION_TEXTURE_A8COLOR_VERT, cc.SHADER_POSITION_TEXTURE_A8COLOR_FRAG);

                program.addAttribute(cc.ATTRIBUTE_NAME_POSITION, cc.VERTEX_ATTRIB_POSITION);
                program.addAttribute(cc.ATTRIBUTE_NAME_COLOR, cc.VERTEX_ATTRIB_COLOR);
                program.addAttribute(cc.ATTRIBUTE_NAME_TEX_COORD, cc.VERTEX_ATTRIB_TEX_COORDS);
                break;
            case this.TYPE_POSITION_UCOLOR:
                program.initWithVertexShaderByteArray(cc.SHADER_POSITION_UCOLOR_VERT, cc.SHADER_POSITION_UCOLOR_FRAG);
                program.addAttribute("aVertex", cc.VERTEX_ATTRIB_POSITION);
                break;
            case this.TYPE_POSITION_LENGTH_TEXTURECOLOR:
                program.initWithVertexShaderByteArray(cc.SHADER_POSITION_COLOR_LENGTH_TEXTURE_VERT, cc.SHADER_POSITION_COLOR_LENGTH_TEXTURE_FRAG);

                program.addAttribute(cc.ATTRIBUTE_NAME_POSITION, cc.VERTEX_ATTRIB_POSITION);
                program.addAttribute(cc.ATTRIBUTE_NAME_TEX_COORD, cc.VERTEX_ATTRIB_TEX_COORDS);
                program.addAttribute(cc.ATTRIBUTE_NAME_COLOR, cc.VERTEX_ATTRIB_COLOR);
                break;
            default:
                cc.log("cocos2d: cc.shaderCache._loadDefaultShader, error shader type");
                return;
        }

        program.link();
        program.updateUniforms();

        //cc.checkGLErrorDebug();
    },

    /**
     * loads the default shaders
     */
    loadDefaultShaders: function () {
        // Position Texture Color shader
        var program = new cc.GLProgram();
        this._loadDefaultShader(program, this.TYPE_POSITION_TEXTURECOLOR);
        this._programs[cc.SHADER_POSITION_TEXTURECOLOR] = program;
        this._programs["ShaderPositionTextureColor"] = program;

        // Position Texture Color alpha test
        program = new cc.GLProgram();
        this._loadDefaultShader(program, this.TYPE_POSITION_TEXTURECOLOR_ALPHATEST);
        this._programs[cc.SHADER_POSITION_TEXTURECOLORALPHATEST] = program;
        this._programs["ShaderPositionTextureColorAlphaTest"] = program;

        //
        // Position, Color shader
        //
        program = new cc.GLProgram();
        this._loadDefaultShader(program, this.TYPE_POSITION_COLOR);
        this._programs[cc.SHADER_POSITION_COLOR] = program;
        this._programs["ShaderPositionColor"] = program;

        //
        // Position Texture shader
        //
        program = new cc.GLProgram();
        this._loadDefaultShader(program, this.TYPE_POSITION_TEXTURE);
        this._programs[cc.SHADER_POSITION_TEXTURE] = program;
        this._programs["ShaderPositionTexture"] = program;

        //
        // Position, Texture attribs, 1 Color as uniform shader
        //
        program = new cc.GLProgram();
        this._loadDefaultShader(program, this.TYPE_POSITION_TEXTURE_UCOLOR);
        this._programs[cc.SHADER_POSITION_TEXTURE_UCOLOR] = program;
        this._programs["ShaderPositionTextureUColor"] = program;

        //
        // Position Texture A8 Color shader
        //
        program = new cc.GLProgram();
        this._loadDefaultShader(program, this.TYPE_POSITION_TEXTURE_A8COLOR);
        this._programs[cc.SHADER_POSITION_TEXTUREA8COLOR] = program;
        this._programs["ShaderPositionTextureA8Color"] = program;

        //
        // Position and 1 color passed as a uniform (to similate glColor4ub )
        //
        program = new cc.GLProgram();
        this._loadDefaultShader(program, this.TYPE_POSITION_UCOLOR);
        this._programs[cc.SHADER_POSITION_UCOLOR] = program;
        this._programs["ShaderPositionUColor"] = program;

        //
        // Position, Legth(TexCoords, Color (used by Draw Node basically )
        //
        program = new cc.GLProgram();
        this._loadDefaultShader(program, this.TYPE_POSITION_LENGTH_TEXTURECOLOR);
        this._programs[cc.SHADER_POSITION_LENGTHTEXTURECOLOR] = program;
        this._programs["ShaderPositionLengthTextureColor"] = program;
    },

    /**
     * reload the default shaders
     */
    reloadDefaultShaders: function () {
        // reset all programs and reload them

        // Position Texture Color shader
        var program = this.programForKey(cc.SHADER_POSITION_TEXTURECOLOR);
        program.reset();
        this._loadDefaultShader(program, this.TYPE_POSITION_TEXTURECOLOR);

        // Position Texture Color alpha test
        program = this.programForKey(cc.SHADER_POSITION_TEXTURECOLORALPHATEST);
        program.reset();
        this._loadDefaultShader(program, this.TYPE_POSITION_TEXTURECOLOR_ALPHATEST);

        //
        // Position, Color shader
        //
        program = this.programForKey(cc.SHADER_POSITION_COLOR);
        program.reset();
        this._loadDefaultShader(program, this.TYPE_POSITION_COLOR);

        //
        // Position Texture shader
        //
        program = this.programForKey(cc.SHADER_POSITION_TEXTURE);
        program.reset();
        this._loadDefaultShader(program, this.TYPE_POSITION_TEXTURE);

        //
        // Position, Texture attribs, 1 Color as uniform shader
        //
        program = this.programForKey(cc.SHADER_POSITION_TEXTURE_UCOLOR);
        program.reset();
        this._loadDefaultShader(program, this.TYPE_POSITION_TEXTURE_UCOLOR);

        //
        // Position Texture A8 Color shader
        //
        program = this.programForKey(cc.SHADER_POSITION_TEXTUREA8COLOR);
        program.reset();
        this._loadDefaultShader(program, this.TYPE_POSITION_TEXTURE_A8COLOR);

        //
        // Position and 1 color passed as a uniform (to similate glColor4ub )
        //
        program = this.programForKey(cc.SHADER_POSITION_UCOLOR);
        program.reset();
        this._loadDefaultShader(program, this.TYPE_POSITION_UCOLOR);
    },

    /**
     * returns a GL program for a given key
     * @param {String} key
     */
    programForKey: function (key) {
        return this._programs[key];
    },

    /**
     * returns a GL program for a shader name
     * @param {String} shaderName
     * @return {cc.GLProgram}
     */
    getProgram: function (shaderName) {
        return this._programs[shaderName];
    },

    /**
     * adds a CCGLProgram to the cache for a given name
     * @param {cc.GLProgram} program
     * @param {String} key
     */
    addProgram: function (program, key) {
        this._programs[key] = program;
    }
};