/****************************************************************************
 Copyright (c) 2008-2010 Ricardo Quesada
 Copyright (c) 2011-2012 cocos2d-x.org
 Copyright (c) 2013-2014 Chukong Technologies Inc.
 Copyright (c) 2009      On-Core

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
 * Base class for cc.Grid
 * @class
 * @extends cc.Class
 */
cc.GridBase = cc.Class.extend(/** @lends cc.GridBase# */{
    _active:false,
    _reuseGrid:0,
    _gridSize:null,
    _texture:null,
    _step:null,
    _grabber:null,
    _isTextureFlipped:false,
    _shaderProgram:null,
    _directorProjection:0,

    _dirty:false,

    /**
     * create one cc.GridBase Object
     * Constructor of cc.GridBase
     * @param {cc.Size} gridSize
     * @param {cc.Texture2D} [texture=]
     * @param {Boolean} [flipped=]
     */
    ctor:function (gridSize, texture, flipped) {
        cc._checkWebGLRenderMode();
        this._active=false;
        this._reuseGrid=0;
        this._gridSize=null;
        this._texture=null;
        this._step = cc.p(0, 0);
        this._grabber=null;
        this._isTextureFlipped=false;
        this._shaderProgram=null;
        this._directorProjection=0;
        this._dirty=false;

        if(gridSize !== undefined)
            this.initWithSize(gridSize, texture, flipped);
    },

    /**
     * whether or not the grid is active
     * @return {Boolean}
     */
    isActive:function () {
        return this._active;
    },

    /**
     * whether or not the grid is active
     * @param {Number} active
     */
    setActive:function (active) {
        this._active = active;
        if (!active) {
            var director = cc.director;
            var proj = director.getProjection();
            director.setProjection(proj);
        }
    },

    /**
     * get number of times that the grid will be reused
     * @return {Number}
     */
    getReuseGrid:function () {
        return this._reuseGrid;
    },
    /**
     * set number of times that the grid will be reused
     * @param reuseGrid
     */
    setReuseGrid:function (reuseGrid) {
        this._reuseGrid = reuseGrid;
    },

    /**
     * get size of the grid
     * @return {cc.Size}
     */
    getGridSize:function () {
        return cc.size(this._gridSize.width, this._gridSize.height);
    },

    /**
     * set size of the grid
     * @param {cc.Size} gridSize
     */
    setGridSize:function (gridSize) {
        this._gridSize.width = parseInt(gridSize.width);
        this._gridSize.height = parseInt(gridSize.height);
    },

    /**
     * get pixels between the grids
     * @return {cc.Point}
     */
    getStep:function () {
        return cc.p(this._step.x, this._step.y);
    },

    /**
     * set pixels between the grids
     * @param {cc.Point} step
     */
    setStep:function (step) {
        this._step.x = step.x;
        this._step.y = step.y;
    },

    /**
     * get whether or not the texture is flipped
     * @return {Boolean}
     */
    isTextureFlipped:function () {
        return this._isTextureFlipped;
    },

    /**
     * set whether or not the texture is flipped
     * @param {Boolean} flipped
     */
    setTextureFlipped:function (flipped) {
        if (this._isTextureFlipped !== flipped) {
            this._isTextureFlipped = flipped;
            this.calculateVertexPoints();
        }
    },

    /**
     *
     * @param {cc.Size} gridSize
     * @param {cc.Texture2D} [texture=]
     * @param {Boolean} [flipped=false]
     * @returns {boolean}
     */
    initWithSize:function (gridSize, texture, flipped) {
        if (!texture) {
            var director = cc.director;
            var winSize = director.getWinSizeInPixels();

            var POTWide = cc.NextPOT(winSize.width);
            var POTHigh = cc.NextPOT(winSize.height);

            var data = new Uint8Array(POTWide * POTHigh * 4);
            if (!data) {
                cc.log("cocos2d: CCGrid: not enough memory.");
                return false;
            }

            texture = new cc.Texture2D();
            // we only use rgba8888
            texture.initWithData(data, cc.Texture2D.PIXEL_FORMAT_RGBA8888, POTWide, POTHigh, winSize);
            if (!texture) {
                cc.log("cocos2d: CCGrid: error creating texture");
                return false;
            }
        }

        flipped = flipped || false;

        this._active = false;
        this._reuseGrid = 0;
        this._gridSize = gridSize;
        this._texture = texture;
        this._isTextureFlipped = flipped;

        this._step.x = this._texture.width / gridSize.width;
        this._step.y = this._texture.height / gridSize.height;

        this._grabber = new cc.Grabber();
        if (!this._grabber)
            return false;
        this._grabber.grab(this._texture);
        this._shaderProgram = cc.shaderCache.programForKey(cc.SHADER_POSITION_TEXTURE);
        this.calculateVertexPoints();
        return true;
    },

    beforeDraw:function () {
        // save projection
        this._directorProjection = cc.director.getProjection();

        //this.set2DProjection();    //TODO why?
        this._grabber.beforeRender(this._texture);
    },

    afterDraw:function (target) {
        this._grabber.afterRender(this._texture);

        // restore projection
        //cc.director.setProjection(this._directorProjection);

        if (target && target.getCamera().isDirty()) {
            var offset = target.getAnchorPointInPoints();

            //TODO hack
            var stackMatrix = target._renderCmd._stackMatrix;
            //
            // XXX: Camera should be applied in the AnchorPoint
            //
            //cc.kmGLTranslatef(offset.x, offset.y, 0);
            var translation = cc.math.Matrix4.createByTranslation(offset.x, offset.y, 0);
            stackMatrix.multiply(translation);

            //target.getCamera().locate();
            target._camera._locateForRenderer(stackMatrix);

            //cc.kmGLTranslatef(-offset.x, -offset.y, 0);
            translation = cc.math.Matrix4.createByTranslation(-offset.x, -offset.y, 0, translation);
            stackMatrix.multiply(translation);
        }

        cc.glBindTexture2D(this._texture);
        this.beforeBlit();
        this.blit(target);
        this.afterBlit();
    },

    beforeBlit: function () {
    },

    afterBlit: function () {
    },

    blit:function () {
        cc.log("cc.GridBase.blit(): Shall be overridden in subclass.");
    },

    reuse:function () {
        cc.log("cc.GridBase.reuse(): Shall be overridden in subclass.");
    },

    calculateVertexPoints:function () {
        cc.log("cc.GridBase.calculateVertexPoints(): Shall be overridden in subclass.");
    },

    set2DProjection:function () {
        var winSize = cc.director.getWinSizeInPixels();

        var gl = cc._renderContext;
        gl.viewport(0, 0, winSize.width , winSize.height);
        cc.kmGLMatrixMode(cc.KM_GL_PROJECTION);
        cc.kmGLLoadIdentity();

        var orthoMatrix = cc.math.Matrix4.createOrthographicProjection(0, winSize.width, 0, winSize.height, -1, 1);
        cc.kmGLMultMatrix(orthoMatrix);

        cc.kmGLMatrixMode(cc.KM_GL_MODELVIEW);
        cc.kmGLLoadIdentity();
        cc.setProjectionMatrixDirty()
    }
});

/**
 * create one cc.GridBase Object
 * @deprecated
 * @param {cc.Size} gridSize
 * @param {cc.Texture2D} [texture=]
 * @param {Boolean} [flipped=]
 * @return {cc.GridBase}
 */
cc.GridBase.create = function (gridSize, texture, flipped) {
    return new cc.GridBase(gridSize, texture, flipped);
};

/**
 * cc.Grid3D is a 3D grid implementation. Each vertex has 3 dimensions: x,y,z
 * @class
 * @extends cc.GridBase
 */
cc.Grid3D = cc.GridBase.extend(/** @lends cc.Grid3D# */{
    _texCoordinates:null,
    _vertices:null,
    _originalVertices:null,
    _indices:null,

    _texCoordinateBuffer:null,
    _verticesBuffer:null,
    _indicesBuffer:null,

    _needDepthTestForBlit: false,
    _oldDepthTestValue: false,
    _oldDepthWriteValue: false,

    /**
     * create one Grid3D object
     * Constructor of cc.Grid3D
     * @param {cc.Size} gridSize
     * @param {cc.Texture2D} [texture=]
     * @param {Boolean} [flipped=]
     */
    ctor:function (gridSize, texture, flipped) {
        cc.GridBase.prototype.ctor.call(this);
        this._texCoordinates=null;
        this._vertices=null;
        this._originalVertices=null;
        this._indices=null;

        this._texCoordinateBuffer=null;
        this._verticesBuffer=null;
        this._indicesBuffer=null;

        if(gridSize !== undefined)
            this.initWithSize(gridSize, texture, flipped);
    },

    /**
     * returns the vertex at a given position      <br/>
     * It will be deprecated in future, please use getVertex instead.
     * @param {cc.Point} pos
     * @return {cc.Vertex3F}
     */
    vertex:function (pos) {
         return this.getVertex(pos);
    },

    /**
     * returns the vertex at a given position
     * @param {cc.Point} pos
     * @return {cc.Vertex3F}
     */
    getVertex: function(pos){
        if(pos.x !== (0| pos.x) || pos.y !== (0| pos.y))
            cc.log("cc.Grid3D.vertex() : Numbers must be integers");
        var index = 0 | ((pos.x * (this._gridSize.height + 1) + pos.y) * 3);
        var locVertices = this._vertices;
        return new cc.Vertex3F(locVertices[index], locVertices[index + 1], locVertices[index + 2]);
    },

    /**
     * returns the original (non-transformed) vertex at a given position             <br/>
     * It will be deprecated in future, please use getOriginalVertex instead.
     * @param {cc.Point} pos
     * @return {cc.Vertex3F}
     */
    originalVertex:function (pos) {
        return this.getOriginalVertex(pos);
    },

    /**
     * returns the original (non-transformed) vertex at a given position
     * @param {cc.Point} pos
     * @return {cc.Vertex3F}
     */
    getOriginalVertex: function(pos) {
        if(pos.x !== (0| pos.x) || pos.y !== (0| pos.y))
            cc.log("cc.Grid3D.originalVertex() : Numbers must be integers");
        var index = 0 | ((pos.x * (this._gridSize.height + 1) + pos.y) * 3);
        var locOriginalVertices = this._originalVertices;
        return new cc.Vertex3F(locOriginalVertices[index], locOriginalVertices[index + 1], locOriginalVertices[index + 2]);
    },

    /**
     * sets a new vertex at a given position
     * @param {cc.Point} pos
     * @param {cc.Vertex3F} vertex
     */
    setVertex:function (pos, vertex) {
        if(pos.x !== (0| pos.x) || pos.y !== (0| pos.y))
            cc.log("cc.Grid3D.setVertex() : Numbers must be integers");
        var index = 0 | ((pos.x * (this._gridSize.height + 1) + pos.y) * 3);
        var vertArray = this._vertices;
        vertArray[index] = vertex.x;
        vertArray[index + 1] = vertex.y;
        vertArray[index + 2] = vertex.z;
        this._dirty = true;
    },

    beforeBlit: function () {
        if (this._needDepthTestForBlit) {
            var gl = cc._renderContext;
            this._oldDepthTestValue = gl.isEnabled(gl.DEPTH_TEST);
            this._oldDepthWriteValue = gl.getParameter(gl.DEPTH_WRITEMASK);
            //CHECK_GL_ERROR_DEBUG();
            gl.enable(gl.DEPTH_TEST);
            gl.depthMask(true);
        }
    },

    afterBlit: function () {
        if (this._needDepthTestForBlit) {
            var gl = cc._renderContext;
            if (this._oldDepthTestValue)
                gl.enable(gl.DEPTH_TEST);
            else
                gl.disable(gl.DEPTH_TEST);
            gl.depthMask(this._oldDepthWriteValue);
        }
    },

    blit:function (target) {
        var n = this._gridSize.width * this._gridSize.height;
        cc.glEnableVertexAttribs(cc.VERTEX_ATTRIB_FLAG_POSITION | cc.VERTEX_ATTRIB_FLAG_TEX_COORDS);
        this._shaderProgram.use();
        //this._shaderProgram.setUniformsForBuiltins();
        this._shaderProgram._setUniformForMVPMatrixWithMat4(target._renderCmd._stackMatrix);

        var gl = cc._renderContext, locDirty = this._dirty;
        //
        // Attributes
        //
        // position
        gl.bindBuffer(gl.ARRAY_BUFFER, this._verticesBuffer);
        if (locDirty)
            gl.bufferData(gl.ARRAY_BUFFER, this._vertices, gl.DYNAMIC_DRAW);
        gl.vertexAttribPointer(cc.VERTEX_ATTRIB_POSITION, 3, gl.FLOAT, false, 0, 0);

        // texCoords
        gl.bindBuffer(gl.ARRAY_BUFFER, this._texCoordinateBuffer);
        if (locDirty)
            gl.bufferData(gl.ARRAY_BUFFER, this._texCoordinates, gl.DYNAMIC_DRAW);
        gl.vertexAttribPointer(cc.VERTEX_ATTRIB_TEX_COORDS, 2, gl.FLOAT, false, 0, 0);

        gl.bindBuffer(gl.ELEMENT_ARRAY_BUFFER, this._indicesBuffer);
        if (locDirty)
            gl.bufferData(gl.ELEMENT_ARRAY_BUFFER, this._indices, gl.STATIC_DRAW);
        gl.drawElements(gl.TRIANGLES, n * 6, gl.UNSIGNED_SHORT, 0);
        if (locDirty)
            this._dirty = false;
        cc.incrementGLDraws(1);
    },

    reuse:function () {
        if (this._reuseGrid > 0) {
            var locOriginalVertices = this._originalVertices, locVertices = this._vertices;
            for (var i = 0, len =  this._vertices.length; i < len; i++)
                locOriginalVertices[i] = locVertices[i];
            --this._reuseGrid;
        }
    },

    calculateVertexPoints:function () {
        var gl = cc._renderContext;

        var width = this._texture.pixelsWidth;
        var height = this._texture.pixelsHeight;
        var imageH = this._texture.getContentSizeInPixels().height;
        var locGridSize = this._gridSize;

        var numOfPoints = (locGridSize.width + 1) * (locGridSize.height + 1);
        this._vertices = new Float32Array(numOfPoints * 3);
        this._texCoordinates = new Float32Array(numOfPoints * 2);
        this._indices = new Uint16Array(locGridSize.width * locGridSize.height * 6);

        if(this._verticesBuffer)
            gl.deleteBuffer(this._verticesBuffer);
        this._verticesBuffer = gl.createBuffer();
        if(this._texCoordinateBuffer)
            gl.deleteBuffer(this._texCoordinateBuffer);
        this._texCoordinateBuffer = gl.createBuffer();
        if(this._indicesBuffer)
            gl.deleteBuffer(this._indicesBuffer);
        this._indicesBuffer = gl.createBuffer();

        var x, y, i, locIndices = this._indices, locTexCoordinates = this._texCoordinates;
        var locIsTextureFlipped = this._isTextureFlipped, locVertices = this._vertices;
        for (x = 0; x < locGridSize.width; ++x) {
            for (y = 0; y < locGridSize.height; ++y) {
                var idx = (y * locGridSize.width) + x;
                var x1 = x * this._step.x;
                var x2 = x1 + this._step.x;
                var y1 = y * this._step.y;
                var y2 = y1 + this._step.y;

                var a = (x * (locGridSize.height + 1) + y);
                var b = ((x + 1) * (locGridSize.height + 1) + y);
                var c = ((x + 1) * (locGridSize.height + 1) + (y + 1));
                var d = (x * (locGridSize.height + 1) + (y + 1));

                locIndices[idx * 6] = a;
                locIndices[idx * 6 + 1] = b;
                locIndices[idx * 6 + 2] = d;
                locIndices[idx * 6 + 3] = b;
                locIndices[idx * 6 + 4] = c;
                locIndices[idx * 6 + 5] = d;

                var l1 = [a * 3, b * 3, c * 3, d * 3];
                var e = {x:x1, y:y1, z:0};   //new cc.Vertex3F(x1, y1, 0);
                var f = {x:x2, y:y1, z:0};   //new cc.Vertex3F(x2, y1, 0);
                var g = {x:x2, y:y2, z:0};   // new cc.Vertex3F(x2, y2, 0);
                var h = {x:x1, y:y2, z:0};   //new cc.Vertex3F(x1, y2, 0);

                var l2 = [e, f, g, h];
                var tex1 = [a * 2, b * 2, c * 2, d * 2];
                var tex2 = [cc.p(x1, y1), cc.p(x2, y1), cc.p(x2, y2), cc.p(x1, y2)];
                for (i = 0; i < 4; ++i) {
                    locVertices[l1[i]] = l2[i].x;
                    locVertices[l1[i] + 1] = l2[i].y;
                    locVertices[l1[i] + 2] = l2[i].z;
                    locTexCoordinates[tex1[i]] = tex2[i].x / width;
                    if (locIsTextureFlipped)
                        locTexCoordinates[tex1[i] + 1] = (imageH - tex2[i].y) / height;
                    else
                        locTexCoordinates[tex1[i] + 1] = tex2[i].y / height;
                }
            }
        }
        this._originalVertices = new Float32Array(this._vertices);

        gl.bindBuffer(gl.ARRAY_BUFFER, this._verticesBuffer);
        gl.bufferData(gl.ARRAY_BUFFER, this._vertices, gl.DYNAMIC_DRAW);
        gl.bindBuffer(gl.ARRAY_BUFFER, this._texCoordinateBuffer);
        gl.bufferData(gl.ARRAY_BUFFER, this._texCoordinates, gl.DYNAMIC_DRAW);
        gl.bindBuffer(gl.ELEMENT_ARRAY_BUFFER, this._indicesBuffer);
        gl.bufferData(gl.ELEMENT_ARRAY_BUFFER, this._indices, gl.STATIC_DRAW);
        this._dirty = true;
    },

    setNeedDepthTestForBlit: function(needDepthTest){
        this._needDepthTestForBlit = needDepthTest;
    },

    getNeedDepthTestForBlit: function(){
        return this._needDepthTestForBlit;
    }
});

/**
 * create one Grid3D object
 * @deprecated
 * @param {cc.Size} gridSize
 * @param {cc.Texture2D} [texture=]
 * @param {Boolean} [flipped=]
 * @return {cc.Grid3D}
 */
cc.Grid3D.create = function (gridSize, texture, flipped) {
    return new cc.Grid3D(gridSize, texture, flipped);
};

/**
 * cc.TiledGrid3D is a 3D grid implementation. It differs from Grid3D in that   <br/>
 * the tiles can be separated from the grid.
 * @class
 * @extends cc.GridBase
 */
cc.TiledGrid3D = cc.GridBase.extend(/** @lends cc.TiledGrid3D# */{
    _texCoordinates:null,
    _vertices:null,
    _originalVertices:null,
    _indices:null,

    _texCoordinateBuffer:null,
    _verticesBuffer:null,
    _indicesBuffer:null,

    /**
     * create one TiledGrid3D object
     * Constructor of cc.TiledGrid3D
     * @param {cc.Size} gridSize
     * @param {cc.Texture2D} [texture=]
     * @param {Boolean} [flipped=]
     */
    ctor:function (gridSize, texture, flipped) {
        cc.GridBase.prototype.ctor.call(this);
        this._texCoordinates=null;
        this._vertices=null;
        this._originalVertices=null;
        this._indices=null;

        this._texCoordinateBuffer=null;
        this._verticesBuffer=null;
        this._indicesBuffer=null;

        if(gridSize !== undefined)
            this.initWithSize(gridSize, texture, flipped);
    },

    /**
     * returns the tile at the given position    <br/>
     * It will be deprecated in future, please use getTile instead.
     * @param {cc.Point} pos
     * @return {cc.Quad3}
     */
    tile:function (pos) {
        return this.getTile(pos);
    },

    /**
     * returns the tile at the given position
     * @param {cc.Point} pos
     * @return {cc.Quad3}
     */
    getTile: function(pos){
        if(pos.x !== (0| pos.x) || pos.y !== (0| pos.y))
            cc.log("cc.TiledGrid3D.tile() : Numbers must be integers");

        var idx = (this._gridSize.height * pos.x + pos.y) * 4 * 3;
        var locVertices = this._vertices;
        return new cc.Quad3(new cc.Vertex3F(locVertices[idx], locVertices[idx + 1], locVertices[idx + 2]),
            new cc.Vertex3F(locVertices[idx + 3], locVertices[idx + 4], locVertices[idx + 5]),
            new cc.Vertex3F(locVertices[idx + 6 ], locVertices[idx + 7], locVertices[idx + 8]),
            new cc.Vertex3F(locVertices[idx + 9], locVertices[idx + 10], locVertices[idx + 11]));
    },

    /**
     * returns the original tile (untransformed) at the given position
     * @param {cc.Point} pos
     * @return {cc.Quad3}
     */
    getOriginalTile:function (pos) {
        if(pos.x !== (0| pos.x) || pos.y !== (0| pos.y))
            cc.log("cc.TiledGrid3D.originalTile() : Numbers must be integers");

        var idx = (this._gridSize.height * pos.x + pos.y) * 4 * 3;
        var locOriginalVertices = this._originalVertices;
        return new cc.Quad3(new cc.Vertex3F(locOriginalVertices[idx], locOriginalVertices[idx + 1], locOriginalVertices[idx + 2]),
            new cc.Vertex3F(locOriginalVertices[idx + 3], locOriginalVertices[idx + 4], locOriginalVertices[idx + 5]),
            new cc.Vertex3F(locOriginalVertices[idx + 6 ], locOriginalVertices[idx + 7], locOriginalVertices[idx + 8]),
            new cc.Vertex3F(locOriginalVertices[idx + 9], locOriginalVertices[idx + 10], locOriginalVertices[idx + 11]));
    },

    /**
     * returns the original tile (untransformed) at the given position.      <br/>
     * It will be deprecated in future, please use getOriginalTile instead.
     * @param {cc.Point} pos
     * @return {cc.Quad3}
     */
    originalTile: function(pos) {
        return this.getOriginalTile(pos);
    },

    /**
     * sets a new tile
     * @param {cc.Point} pos
     * @param {cc.Quad3} coords
     */
    setTile:function (pos, coords) {
        if(pos.x !== (0| pos.x) || pos.y !== (0| pos.y))
            cc.log("cc.TiledGrid3D.setTile() : Numbers must be integers");

        var idx = (this._gridSize.height * pos.x + pos.y) * 12;
        var locVertices = this._vertices;
        locVertices[idx] = coords.bl.x;
        locVertices[idx + 1] = coords.bl.y;
        locVertices[idx + 2] = coords.bl.z;
        locVertices[idx + 3] = coords.br.x;
        locVertices[idx + 4] = coords.br.y;
        locVertices[idx + 5] = coords.br.z;
        locVertices[idx + 6] = coords.tl.x;
        locVertices[idx + 7] = coords.tl.y;
        locVertices[idx + 8] = coords.tl.z;
        locVertices[idx + 9] = coords.tr.x;
        locVertices[idx + 10] = coords.tr.y;
        locVertices[idx + 11] = coords.tr.z;
        this._dirty = true;
    },

    blit: function (target) {
        var n = this._gridSize.width * this._gridSize.height;

        this._shaderProgram.use();
        this._shaderProgram._setUniformForMVPMatrixWithMat4(target._renderCmd._stackMatrix);
        //this._shaderProgram.setUniformsForBuiltins();

        //
        // Attributes
        //
        var gl = cc._renderContext, locDirty = this._dirty;
        cc.glEnableVertexAttribs(cc.VERTEX_ATTRIB_FLAG_POSITION | cc.VERTEX_ATTRIB_FLAG_TEX_COORDS);

        // position
        gl.bindBuffer(gl.ARRAY_BUFFER, this._verticesBuffer);
        if (locDirty)
            gl.bufferData(gl.ARRAY_BUFFER, this._vertices, gl.DYNAMIC_DRAW);
        gl.vertexAttribPointer(cc.VERTEX_ATTRIB_POSITION, 3, gl.FLOAT, false, 0, this._vertices);

        // texCoords
        gl.bindBuffer(gl.ARRAY_BUFFER, this._texCoordinateBuffer);
        if (locDirty)
            gl.bufferData(gl.ARRAY_BUFFER, this._texCoordinates, gl.DYNAMIC_DRAW);
        gl.vertexAttribPointer(cc.VERTEX_ATTRIB_TEX_COORDS, 2, gl.FLOAT, false, 0, this._texCoordinates);

        gl.bindBuffer(gl.ELEMENT_ARRAY_BUFFER, this._indicesBuffer);
        if (locDirty)
            gl.bufferData(gl.ELEMENT_ARRAY_BUFFER, this._indices, gl.STATIC_DRAW);
        gl.drawElements(gl.TRIANGLES, n * 6, gl.UNSIGNED_SHORT, 0);
        if (locDirty)
            this._dirty = false;
        cc.incrementGLDraws(1);
    },

    reuse:function () {
        if (this._reuseGrid > 0) {
            var locVertices = this._vertices, locOriginalVertices = this._originalVertices;
            for (var i = 0; i < locVertices.length; i++)
                locOriginalVertices[i] = locVertices[i];
            --this._reuseGrid;
        }
    },

    calculateVertexPoints:function () {
        var width = this._texture.pixelsWidth;
        var height = this._texture.pixelsHeight;
        var imageH = this._texture.getContentSizeInPixels().height;
        var locGridSize = this._gridSize;

        var numQuads = locGridSize.width * locGridSize.height;
        this._vertices = new Float32Array(numQuads * 12);
        this._texCoordinates = new Float32Array(numQuads * 8);
        this._indices = new Uint16Array(numQuads * 6);

        var gl = cc._renderContext;
        if(this._verticesBuffer)
            gl.deleteBuffer(this._verticesBuffer);
        this._verticesBuffer = gl.createBuffer();
        if(this._texCoordinateBuffer)
            gl.deleteBuffer(this._texCoordinateBuffer);
        this._texCoordinateBuffer = gl.createBuffer();
        if(this._indicesBuffer)
            gl.deleteBuffer(this._indicesBuffer);
        this._indicesBuffer = gl.createBuffer();

        var x, y, i = 0;
        var locStep = this._step, locVertices = this._vertices, locTexCoords = this._texCoordinates, locIsTextureFlipped = this._isTextureFlipped;
        for (x = 0; x < locGridSize.width; x++) {
            for (y = 0; y < locGridSize.height; y++) {
                var x1 = x * locStep.x;
                var x2 = x1 + locStep.x;
                var y1 = y * locStep.y;
                var y2 = y1 + locStep.y;

                locVertices[i * 12] = x1;
                locVertices[i * 12 + 1] = y1;
                locVertices[i * 12 + 2] = 0;
                locVertices[i * 12 + 3] = x2;
                locVertices[i * 12 + 4] = y1;
                locVertices[i * 12 + 5] = 0;
                locVertices[i * 12 + 6] = x1;
                locVertices[i * 12 + 7] = y2;
                locVertices[i * 12 + 8] = 0;
                locVertices[i * 12 + 9] = x2;
                locVertices[i * 12 + 10] = y2;
                locVertices[i * 12 + 11] = 0;

                var newY1 = y1;
                var newY2 = y2;

                if (locIsTextureFlipped) {
                    newY1 = imageH - y1;
                    newY2 = imageH - y2;
                }

                locTexCoords[i * 8] = x1 / width;
                locTexCoords[i * 8 + 1] = newY1 / height;
                locTexCoords[i * 8 + 2] = x2 / width;
                locTexCoords[i * 8 + 3] = newY1 / height;
                locTexCoords[i * 8 + 4] = x1 / width;
                locTexCoords[i * 8 + 5] = newY2 / height;
                locTexCoords[i * 8 + 6] = x2 / width;
                locTexCoords[i * 8 + 7] = newY2 / height;
                i++;
            }
        }

        var locIndices = this._indices;
        for (x = 0; x < numQuads; x++) {
            locIndices[x * 6 + 0] = (x * 4 + 0);
            locIndices[x * 6 + 1] = (x * 4 + 1);
            locIndices[x * 6 + 2] = (x * 4 + 2);

            locIndices[x * 6 + 3] = (x * 4 + 1);
            locIndices[x * 6 + 4] = (x * 4 + 2);
            locIndices[x * 6 + 5] = (x * 4 + 3);
        }
        this._originalVertices = new Float32Array(this._vertices);

        gl.bindBuffer(gl.ARRAY_BUFFER, this._verticesBuffer);
        gl.bufferData(gl.ARRAY_BUFFER, this._vertices, gl.DYNAMIC_DRAW);
        gl.bindBuffer(gl.ARRAY_BUFFER, this._texCoordinateBuffer);
        gl.bufferData(gl.ARRAY_BUFFER, this._texCoordinates, gl.DYNAMIC_DRAW);
        gl.bindBuffer(gl.ELEMENT_ARRAY_BUFFER, this._indicesBuffer);
        gl.bufferData(gl.ELEMENT_ARRAY_BUFFER, this._indices, gl.DYNAMIC_DRAW);
        this._dirty = true;
    }
});

/**
 * create one TiledGrid3D object
 * @deprecated since v3.0, please use new cc.TiledGrid3D(gridSize, texture, flipped) instead
 * @param {cc.Size} gridSize
 * @param {cc.Texture2D} [texture=]
 * @param {Boolean} [flipped=]
 * @return {cc.TiledGrid3D}
 */
cc.TiledGrid3D.create = function (gridSize, texture, flipped) {
    return new cc.TiledGrid3D(gridSize, texture, flipped);
};
