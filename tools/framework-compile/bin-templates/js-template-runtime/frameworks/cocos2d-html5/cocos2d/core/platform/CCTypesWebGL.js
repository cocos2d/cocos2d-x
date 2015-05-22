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

var cc = cc || {};
cc._tmp = cc._tmp || {};

cc._tmp.WebGLColor = function () {
    //redefine some types with ArrayBuffer for WebGL
    /**
     * @class cc.Color
     * @param {Number} r
     * @param {Number}g
     * @param {Number} b
     * @param {Number} a
     * @param {Array} arrayBuffer
     * @param {Number} offset
     * @returns {cc.Color}
     */
    cc.color = function (r, g, b, a, arrayBuffer, offset) {
        if (r === undefined)
            return new cc.Color(0, 0, 0, 255, arrayBuffer, offset);
        if (cc.isString(r)) {
            var color = cc.hexToColor(r);
            return new cc.Color(color.r, color.g, color.b, color.a);
        }
        if (cc.isObject(r))
            return new cc.Color(r.r, r.g, r.b, r.a, r.arrayBuffer, r.offset);
        return new cc.Color(r, g, b, a, arrayBuffer, offset);
    };
    //redefine cc.Color
    /**
     * @class cc.Color
     * @param {Number} r
     * @param {Number}g
     * @param {Number} b
     * @param {Number} a
     * @param {Array} arrayBuffer
     * @param {Number} offset
     * @constructor
     */
    cc.Color = function (r, g, b, a, arrayBuffer, offset) {
        this._arrayBuffer = arrayBuffer || new ArrayBuffer(cc.Color.BYTES_PER_ELEMENT);
        this._offset = offset || 0;

        var locArrayBuffer = this._arrayBuffer, locOffset = this._offset, locElementLen = Uint8Array.BYTES_PER_ELEMENT;
        this._rU8 = new Uint8Array(locArrayBuffer, locOffset, 1);
        this._gU8 = new Uint8Array(locArrayBuffer, locOffset + locElementLen, 1);
        this._bU8 = new Uint8Array(locArrayBuffer, locOffset + locElementLen * 2, 1);
        this._aU8 = new Uint8Array(locArrayBuffer, locOffset + locElementLen * 3, 1);

        this._rU8[0] = r || 0;
        this._gU8[0] = g || 0;
        this._bU8[0] = b || 0;
        this._aU8[0] = (a == null) ? 255 : a;

        if (a === undefined)
            this.a_undefined = true;
    };
    /**
     * @constant
     * @type {number}
     */
    cc.Color.BYTES_PER_ELEMENT = 4;
    var _p = cc.Color.prototype;
    _p._getR = function () {
        return this._rU8[0];
    };
    _p._setR = function (value) {
        this._rU8[0] = value < 0 ? 0 : value;
    };
    _p._getG = function () {
        return this._gU8[0];
    };
    _p._setG = function (value) {
        this._gU8[0] = value < 0 ? 0 : value;
    };
    _p._getB = function () {
        return this._bU8[0];
    };
    _p._setB = function (value) {
        this._bU8[0] = value < 0 ? 0 : value;
    };
    _p._getA = function () {
        return this._aU8[0];
    };
    _p._setA = function (value) {
        this._aU8[0] = value < 0 ? 0 : value;
    };
    /** @expose */
    _p.r;
    cc.defineGetterSetter(_p, "r", _p._getR, _p._setR);
    /** @expose */
    _p.g;
    cc.defineGetterSetter(_p, "g", _p._getG, _p._setG);
    /** @expose */
    _p.b;
    cc.defineGetterSetter(_p, "b", _p._getB, _p._setB);
    /** @expose */
    _p.a;
    cc.defineGetterSetter(_p, "a", _p._getA, _p._setA);

    //redefine cc.Vertex2F
    /**
     * @class cc.Vertex2F
     * @param {Number} x
     * @param {Number}y
     * @param {Array} arrayBuffer
     * @param {Number}offset
     * @constructor
     */
    cc.Vertex2F = function (x, y, arrayBuffer, offset) {
        this._arrayBuffer = arrayBuffer || new ArrayBuffer(cc.Vertex2F.BYTES_PER_ELEMENT);
        this._offset = offset || 0;

        this._xF32 = new Float32Array(this._arrayBuffer, this._offset, 1);
        this._yF32 = new Float32Array(this._arrayBuffer, this._offset + 4, 1);
        this._xF32[0] = x || 0;
        this._yF32[0] = y || 0;
    };
    /**
     * @constant
     * @type {number}
     */
    cc.Vertex2F.BYTES_PER_ELEMENT = 8;

    _p = cc.Vertex2F.prototype;
    _p._getX = function () {
        return this._xF32[0];
    };
    _p._setX = function (xValue) {
        this._xF32[0] = xValue;
    };
    _p._getY = function () {
        return this._yF32[0];
    };
    _p._setY = function (yValue) {
        this._yF32[0] = yValue;
    };
    /** @expose */
    _p.x;
    cc.defineGetterSetter(_p, "x", _p._getX, _p._setX);
    /** @expose */
    _p.y;
    cc.defineGetterSetter(_p, "y", _p._getY, _p._setY);

    // redefine cc.Vertex3F
    /**
     * @class cc.Vertex3F
     * @param {Number} x
     * @param {Number} y
     * @param {Number}z
     * @param {Array} arrayBuffer
     * @param {Number} offset
     * @constructor
     */
    cc.Vertex3F = function (x, y, z, arrayBuffer, offset) {
        this._arrayBuffer = arrayBuffer || new ArrayBuffer(cc.Vertex3F.BYTES_PER_ELEMENT);
        this._offset = offset || 0;

        var locArrayBuffer = this._arrayBuffer, locOffset = this._offset;
        this._xF32 = new Float32Array(locArrayBuffer, locOffset, 1);
        this._xF32[0] = x || 0;
        this._yF32 = new Float32Array(locArrayBuffer, locOffset + Float32Array.BYTES_PER_ELEMENT, 1);
        this._yF32[0] = y || 0;
        this._zF32 = new Float32Array(locArrayBuffer, locOffset + Float32Array.BYTES_PER_ELEMENT * 2, 1);
        this._zF32[0] = z || 0;
    };
    /**
     * @constant
     * @type {number}
     */
    cc.Vertex3F.BYTES_PER_ELEMENT = 12;

    _p = cc.Vertex3F.prototype;
    _p._getX = function () {
        return this._xF32[0];
    };
    _p._setX = function (xValue) {
        this._xF32[0] = xValue;
    };
    _p._getY = function () {
        return this._yF32[0];
    };
    _p._setY = function (yValue) {
        this._yF32[0] = yValue;
    };
    _p._getZ = function () {
        return this._zF32[0];
    };
    _p._setZ = function (zValue) {
        this._zF32[0] = zValue;
    };
    /** @expose */
    _p.x;
    cc.defineGetterSetter(_p, "x", _p._getX, _p._setX);
    /** @expose */
    _p.y;
    cc.defineGetterSetter(_p, "y", _p._getY, _p._setY);
    /** @expose */
    _p.z;
    cc.defineGetterSetter(_p, "z", _p._getZ, _p._setZ);

    // redefine cc.Tex2F
    /**
     * @class cc.Tex2F
     * @param {Number} u
     * @param {Number} v
     * @param {Array} arrayBuffer
     * @param {Number} offset
     * @constructor
     */
    cc.Tex2F = function (u, v, arrayBuffer, offset) {
        this._arrayBuffer = arrayBuffer || new ArrayBuffer(cc.Tex2F.BYTES_PER_ELEMENT);
        this._offset = offset || 0;

        this._uF32 = new Float32Array(this._arrayBuffer, this._offset, 1);
        this._vF32 = new Float32Array(this._arrayBuffer, this._offset + 4, 1);
        this._uF32[0] = u || 0;
        this._vF32[0] = v || 0;
    };
    /**
     * @constants
     * @type {number}
     */
    cc.Tex2F.BYTES_PER_ELEMENT = 8;

    _p = cc.Tex2F.prototype;
    _p._getU = function () {
        return this._uF32[0];
    };
    _p._setU = function (xValue) {
        this._uF32[0] = xValue;
    };
    _p._getV = function () {
        return this._vF32[0];
    };
    _p._setV = function (yValue) {
        this._vF32[0] = yValue;
    };
    /** @expose */
    _p.u;
    cc.defineGetterSetter(_p, "u", _p._getU, _p._setU);
    /** @expose */
    _p.v;
    cc.defineGetterSetter(_p, "v", _p._getV, _p._setV);

    //redefine cc.Quad2
    /**
     * @class cc.Quad2
     * @param {cc.Vertex2F} tl
     * @param {cc.Vertex2F} tr
     * @param {cc.Vertex2F} bl
     * @param {cc.Vertex2F} br
     * @param {Array} arrayBuffer
     * @param {Number} offset
     * @constructor
     */
    cc.Quad2 = function (tl, tr, bl, br, arrayBuffer, offset) {
        this._arrayBuffer = arrayBuffer || new ArrayBuffer(cc.Quad2.BYTES_PER_ELEMENT);
        this._offset = offset || 0;

        var locArrayBuffer = this._arrayBuffer, locElementLen = cc.Vertex2F.BYTES_PER_ELEMENT;
        this._tl = tl ? new cc.Vertex2F(tl.x, tl.y, locArrayBuffer, 0) : new cc.Vertex2F(0, 0, locArrayBuffer, 0);
        this._tr = tr ? new cc.Vertex2F(tr.x, tr.y, locArrayBuffer, locElementLen) : new cc.Vertex2F(0, 0, locArrayBuffer, locElementLen);
        this._bl = bl ? new cc.Vertex2F(bl.x, bl.y, locArrayBuffer, locElementLen * 2) : new cc.Vertex2F(0, 0, locArrayBuffer, locElementLen * 2);
        this._br = br ? new cc.Vertex2F(br.x, br.y, locArrayBuffer, locElementLen * 3) : new cc.Vertex2F(0, 0, locArrayBuffer, locElementLen * 3);
    };
    /**
     * @constant
     * @type {number}
     */
    cc.Quad2.BYTES_PER_ELEMENT = 32;

    _p = cc.Quad2.prototype;
    _p._getTL = function () {
        return this._tl;
    };
    _p._setTL = function (tlValue) {
        this._tl.x = tlValue.x;
        this._tl.y = tlValue.y;
    };
    _p._getTR = function () {
        return this._tr;
    };
    _p._setTR = function (trValue) {
        this._tr.x = trValue.x;
        this._tr.y = trValue.y;
    };
    _p._getBL = function() {
        return this._bl;
    };
    _p._setBL = function (blValue) {
        this._bl.x = blValue.x;
        this._bl.y = blValue.y;
    };
    _p._getBR = function () {
        return this._br;
    };
    _p._setBR = function (brValue) {
        this._br.x = brValue.x;
        this._br.y = brValue.y;
    };

    /** @expose */
    _p.tl;
    cc.defineGetterSetter(_p, "tl", _p._getTL, _p._setTL);
    /** @expose */
    _p.tr;
    cc.defineGetterSetter(_p, "tr", _p._getTR, _p._setTR);
    /** @expose */
    _p.bl;
    cc.defineGetterSetter(_p, "bl", _p._getBL, _p._setBL);
    /** @expose */
    _p.br;
    cc.defineGetterSetter(_p, "br", _p._getBR, _p._setBR);

    /**
     * A 3D Quad. 4 * 3 floats
     * @Class cc.Quad3
     * @Construct
     * @param {cc.Vertex3F} bl1
     * @param {cc.Vertex3F} br1
     * @param {cc.Vertex3F} tl1
     * @param {cc.Vertex3F} tr1
     */
    cc.Quad3 = function (bl1, br1, tl1, tr1) {
        this.bl = bl1 || new cc.Vertex3F(0, 0, 0);
        this.br = br1 || new cc.Vertex3F(0, 0, 0);
        this.tl = tl1 || new cc.Vertex3F(0, 0, 0);
        this.tr = tr1 || new cc.Vertex3F(0, 0, 0);
    };

    //redefine cc.V3F_C4B_T2F
    /**
     * @class cc.V3F_C4B_T2F
     * @param {cc.Vertex3F} vertices
     * @param { cc.color} colors
     * @param {cc.Tex2F} texCoords
     * @param {Array} arrayBuffer
     * @param {Number} offset
     * @constructor
     */
    cc.V3F_C4B_T2F = function (vertices, colors, texCoords, arrayBuffer, offset) {
        this._arrayBuffer = arrayBuffer || new ArrayBuffer(cc.V3F_C4B_T2F.BYTES_PER_ELEMENT);
        this._offset = offset || 0;

        var locArrayBuffer = this._arrayBuffer, locOffset = this._offset, locElementLen = cc.Vertex3F.BYTES_PER_ELEMENT;
        this._vertices = vertices ? new cc.Vertex3F(vertices.x, vertices.y, vertices.z, locArrayBuffer, locOffset) :
            new cc.Vertex3F(0, 0, 0, locArrayBuffer, locOffset);
        this._colors = colors ? cc.color(colors.r, colors.g, colors.b, colors.a, locArrayBuffer, locOffset + locElementLen) :
            cc.color(0, 0, 0, 0, locArrayBuffer, locOffset + locElementLen);
        this._texCoords = texCoords ? new cc.Tex2F(texCoords.u, texCoords.v, locArrayBuffer, locOffset + locElementLen + cc.Color.BYTES_PER_ELEMENT) :
            new cc.Tex2F(0, 0, locArrayBuffer, locOffset + locElementLen + cc.Color.BYTES_PER_ELEMENT);
    };
    /**
     * @constant
     * @type {number}
     */
    cc.V3F_C4B_T2F.BYTES_PER_ELEMENT = 24;

    _p = cc.V3F_C4B_T2F.prototype;
    _p._getVertices = function () {
        return this._vertices;
    };
    _p._setVertices = function (verticesValue) {
        var locVertices = this._vertices;
        locVertices.x = verticesValue.x;
        locVertices.y = verticesValue.y;
        locVertices.z = verticesValue.z;
    };
    _p._getColor = function () {
        return this._colors;
    };
    _p._setColor = function (colorValue) {
        var locColors = this._colors;
        locColors.r = colorValue.r;
        locColors.g = colorValue.g;
        locColors.b = colorValue.b;
        locColors.a = colorValue.a;
    };
    _p._getTexCoords = function () {
        return this._texCoords;
    };
    _p._setTexCoords = function (texValue) {
        this._texCoords.u = texValue.u;
        this._texCoords.v = texValue.v;
    };
    /** @expose */
    _p.vertices;
    cc.defineGetterSetter(_p, "vertices", _p._getVertices, _p._setVertices);
    /** @expose */
    _p.colors;
    cc.defineGetterSetter(_p, "colors", _p._getColor, _p._setColor);
    /** @expose */
    _p.texCoords;
    cc.defineGetterSetter(_p, "texCoords", _p._getTexCoords, _p._setTexCoords);

    //redefine cc.V3F_C4B_T2F_Quad
    /**
     * @cc.class cc.V3F_C4B_T2F_Quad
     * @param {cc.V3F_C4B_T2F} tl
     * @param {cc.V3F_C4B_T2F} bl
     * @param {cc.V3F_C4B_T2F} tr
     * @param {cc.V3F_C4B_T2F} br
     * @param {Array} arrayBuffer
     * @param {Number} offset
     * @constructor
     */
    cc.V3F_C4B_T2F_Quad = function (tl, bl, tr, br, arrayBuffer, offset) {
        this._arrayBuffer = arrayBuffer || new ArrayBuffer(cc.V3F_C4B_T2F_Quad.BYTES_PER_ELEMENT);
        this._offset = offset || 0;

        var locArrayBuffer = this._arrayBuffer, locOffset = this._offset, locElementLen = cc.V3F_C4B_T2F.BYTES_PER_ELEMENT;
        this._tl = tl ? new cc.V3F_C4B_T2F(tl.vertices, tl.colors, tl.texCoords, locArrayBuffer, locOffset) :
            new cc.V3F_C4B_T2F(null, null, null, locArrayBuffer, locOffset);
        this._bl = bl ? new cc.V3F_C4B_T2F(bl.vertices, bl.colors, bl.texCoords, locArrayBuffer, locOffset + locElementLen) :
            new cc.V3F_C4B_T2F(null, null, null, locArrayBuffer, locOffset + locElementLen);
        this._tr = tr ? new cc.V3F_C4B_T2F(tr.vertices, tr.colors, tr.texCoords, locArrayBuffer, locOffset + locElementLen * 2) :
            new cc.V3F_C4B_T2F(null, null, null, locArrayBuffer, locOffset + locElementLen * 2);
        this._br = br ? new cc.V3F_C4B_T2F(br.vertices, br.colors, br.texCoords, locArrayBuffer, locOffset + locElementLen * 3) :
            new cc.V3F_C4B_T2F(null, null, null, locArrayBuffer, locOffset + locElementLen * 3);
    };
    /**
     * @constant
     * @type {number}
     */
    cc.V3F_C4B_T2F_Quad.BYTES_PER_ELEMENT = 96;
    _p = cc.V3F_C4B_T2F_Quad.prototype;
    _p._getTL = function () {
        return this._tl;
    };
    _p._setTL = function (tlValue) {
        var locTl = this._tl;
        locTl.vertices = tlValue.vertices;
        locTl.colors = tlValue.colors;
        locTl.texCoords = tlValue.texCoords;
    };
    _p._getBL = function () {
        return this._bl;
    };
    _p._setBL = function (blValue) {
        var locBl = this._bl;
        locBl.vertices = blValue.vertices;
        locBl.colors = blValue.colors;
        locBl.texCoords = blValue.texCoords;
    };
    _p._getTR = function () {
        return this._tr;
    };
    _p._setTR = function (trValue) {
        var locTr = this._tr;
        locTr.vertices = trValue.vertices;
        locTr.colors = trValue.colors;
        locTr.texCoords = trValue.texCoords;
    };
    _p._getBR = function () {
        return this._br;
    };
    _p._setBR = function (brValue) {
        var locBr = this._br;
        locBr.vertices = brValue.vertices;
        locBr.colors = brValue.colors;
        locBr.texCoords = brValue.texCoords;
    };
    _p._getArrayBuffer = function () {
        return this._arrayBuffer;
    };

    /** @expose */
    _p.tl;
    cc.defineGetterSetter(_p, "tl", _p._getTL, _p._setTL);
    /** @expose */
    _p.tr;
    cc.defineGetterSetter(_p, "tr", _p._getTR, _p._setTR);
    /** @expose */
    _p.bl;
    cc.defineGetterSetter(_p, "bl", _p._getBL, _p._setBL);
    /** @expose */
    _p.br;
    cc.defineGetterSetter(_p, "br", _p._getBR, _p._setBR);
    /** @expose */
    _p.arrayBuffer;
    cc.defineGetterSetter(_p, "arrayBuffer", _p._getArrayBuffer, null);

    /**
     * @function
     * @returns {cc.V3F_C4B_T2F_Quad}
     */
    cc.V3F_C4B_T2F_QuadZero = function () {
        return new cc.V3F_C4B_T2F_Quad();
    };

    /**
     * @function
     * @param {cc.V3F_C4B_T2F_Quad} sourceQuad
     * @return {cc.V3F_C4B_T2F_Quad}
     */
    cc.V3F_C4B_T2F_QuadCopy = function (sourceQuad) {
        if (!sourceQuad)
            return  cc.V3F_C4B_T2F_QuadZero();

        //return new cc.V3F_C4B_T2F_Quad(sourceQuad,tl,sourceQuad,bl,sourceQuad.tr,sourceQuad.br,null,0);
        var srcTL = sourceQuad.tl, srcBL = sourceQuad.bl, srcTR = sourceQuad.tr, srcBR = sourceQuad.br;
        return {
            tl: {vertices: {x: srcTL.vertices.x, y: srcTL.vertices.y, z: srcTL.vertices.z},
                colors: {r: srcTL.colors.r, g: srcTL.colors.g, b: srcTL.colors.b, a: srcTL.colors.a},
                texCoords: {u: srcTL.texCoords.u, v: srcTL.texCoords.v}},
            bl: {vertices: {x: srcBL.vertices.x, y: srcBL.vertices.y, z: srcBL.vertices.z},
                colors: {r: srcBL.colors.r, g: srcBL.colors.g, b: srcBL.colors.b, a: srcBL.colors.a},
                texCoords: {u: srcBL.texCoords.u, v: srcBL.texCoords.v}},
            tr: {vertices: {x: srcTR.vertices.x, y: srcTR.vertices.y, z: srcTR.vertices.z},
                colors: {r: srcTR.colors.r, g: srcTR.colors.g, b: srcTR.colors.b, a: srcTR.colors.a},
                texCoords: {u: srcTR.texCoords.u, v: srcTR.texCoords.v}},
            br: {vertices: {x: srcBR.vertices.x, y: srcBR.vertices.y, z: srcBR.vertices.z},
                colors: {r: srcBR.colors.r, g: srcBR.colors.g, b: srcBR.colors.b, a: srcBR.colors.a},
                texCoords: {u: srcBR.texCoords.u, v: srcBR.texCoords.v}}
        };
    };

    /**
     * @function
     * @param {Array} sourceQuads
     * @returns {Array}
     */
    cc.V3F_C4B_T2F_QuadsCopy = function (sourceQuads) {
        if (!sourceQuads)
            return [];

        var retArr = [];
        for (var i = 0; i < sourceQuads.length; i++) {
            retArr.push(cc.V3F_C4B_T2F_QuadCopy(sourceQuads[i]));
        }
        return retArr;
    };

    //redefine cc.V2F_C4B_T2F
    /**
     * @class cc.V2F_C4B_T2F
     * @param {cc.Vertex2F} vertices
     * @param {cc.color} colors
     * @param {cc.Tex2F} texCoords
     * @param {Array} arrayBuffer
     * @param {Number} offset
     * @constructor
     */
    cc.V2F_C4B_T2F = function (vertices, colors, texCoords, arrayBuffer, offset) {
        this._arrayBuffer = arrayBuffer || new ArrayBuffer(cc.V2F_C4B_T2F.BYTES_PER_ELEMENT);
        this._offset = offset || 0;

        var locArrayBuffer = this._arrayBuffer, locOffset = this._offset, locElementLen = cc.Vertex2F.BYTES_PER_ELEMENT;
        this._vertices = vertices ? new cc.Vertex2F(vertices.x, vertices.y, locArrayBuffer, locOffset) :
            new cc.Vertex2F(0, 0, locArrayBuffer, locOffset);
        this._colors = colors ? cc.color(colors.r, colors.g, colors.b, colors.a, locArrayBuffer, locOffset + locElementLen) :
            cc.color(0, 0, 0, 0, locArrayBuffer, locOffset + locElementLen);
        this._texCoords = texCoords ? new cc.Tex2F(texCoords.u, texCoords.v, locArrayBuffer, locOffset + locElementLen + cc.Color.BYTES_PER_ELEMENT) :
            new cc.Tex2F(0, 0, locArrayBuffer, locOffset + locElementLen + cc.Color.BYTES_PER_ELEMENT);
    };

    /**
     * @constant
     * @type {number}
     */
    cc.V2F_C4B_T2F.BYTES_PER_ELEMENT = 20;
    _p = cc.V2F_C4B_T2F.prototype;
    _p._getVertices = function () {
        return this._vertices;
    };
    _p._setVertices = function (verticesValue) {
        this._vertices.x = verticesValue.x;
        this._vertices.y = verticesValue.y;
    };
    _p._getColor = function () {
        return this._colors;
    };
    _p._setColor = function (colorValue) {
        var locColors = this._colors;
        locColors.r = colorValue.r;
        locColors.g = colorValue.g;
        locColors.b = colorValue.b;
        locColors.a = colorValue.a;
    };
    _p._getTexCoords = function () {
        return this._texCoords;
    };
    _p._setTexCoords = function (texValue) {
        this._texCoords.u = texValue.u;
        this._texCoords.v = texValue.v;
    };

    /** @expose */
    _p.vertices;
    cc.defineGetterSetter(_p, "vertices", _p._getVertices, _p._setVertices);
    /** @expose */
    _p.colors;
    cc.defineGetterSetter(_p, "colors", _p._getColor, _p._setColor);
    /** @expose */
    _p.texCoords;
    cc.defineGetterSetter(_p, "texCoords", _p._getTexCoords, _p._setTexCoords);

    //redefine cc.V2F_C4B_T2F_Triangle
    /**
     * @class cc.V2F_C4B_T2F_Triangle
     * @param {cc.V2F_C4B_T2F} a
     * @param {cc.V2F_C4B_T2F} b
     * @param {cc.V2F_C4B_T2F} c
     * @param {Array} arrayBuffer
     * @param {Number} offset
     * @constructor
     */
    cc.V2F_C4B_T2F_Triangle = function (a, b, c, arrayBuffer, offset) {
        this._arrayBuffer = arrayBuffer || new ArrayBuffer(cc.V2F_C4B_T2F_Triangle.BYTES_PER_ELEMENT);
        this._offset = offset || 0;

        var locArrayBuffer = this._arrayBuffer, locOffset = this._offset, locElementLen = cc.V2F_C4B_T2F.BYTES_PER_ELEMENT;
        this._a = a ? new cc.V2F_C4B_T2F(a.vertices, a.colors, a.texCoords, locArrayBuffer, locOffset) :
            new cc.V2F_C4B_T2F(null, null, null, locArrayBuffer, locOffset);
        this._b = b ? new cc.V2F_C4B_T2F(b.vertices, b.colors, b.texCoords, locArrayBuffer, locOffset + locElementLen) :
            new cc.V2F_C4B_T2F(null, null, null, locArrayBuffer, locOffset + locElementLen);
        this._c = c ? new cc.V2F_C4B_T2F(c.vertices, c.colors, c.texCoords, locArrayBuffer, locOffset + locElementLen * 2) :
            new cc.V2F_C4B_T2F(null, null, null, locArrayBuffer, locOffset + locElementLen * 2);
    };
    /**
     * @constant
     * @type {number}
     */
    cc.V2F_C4B_T2F_Triangle.BYTES_PER_ELEMENT = 60;
    _p = cc.V2F_C4B_T2F_Triangle.prototype;
    _p._getA = function () {
        return this._a;
    };
    _p._setA = function (aValue) {
        var locA = this._a;
        locA.vertices = aValue.vertices;
        locA.colors = aValue.colors;
        locA.texCoords = aValue.texCoords;
    };
    _p._getB = function () {
        return this._b;
    };
    _p._setB = function (bValue) {
        var locB = this._b;
        locB.vertices = bValue.vertices;
        locB.colors = bValue.colors;
        locB.texCoords = bValue.texCoords;
    };
    _p._getC = function () {
        return this._c;
    };
    _p._setC = function (cValue) {
        var locC = this._c;
        locC.vertices = cValue.vertices;
        locC.colors = cValue.colors;
        locC.texCoords = cValue.texCoords;
    };

    /** @expose */
    _p.a;
    cc.defineGetterSetter(_p, "a", _p._getA, _p._setA);
    /** @expose */
    _p.b;
    cc.defineGetterSetter(_p, "b", _p._getB, _p._setB);
    /** @expose */
    _p.c;
    cc.defineGetterSetter(_p, "c", _p._getC, _p._setC);
};