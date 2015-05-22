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
 * Color class, please use cc.color() to construct a color
 * @class cc.Color
 * @param {Number} r
 * @param {Number} g
 * @param {Number} b
 * @param {Number} a
 * @see cc.color
 */
cc.Color = function (r, g, b, a) {
    this.r = r || 0;
    this.g = g || 0;
    this.b = b || 0;
    this.a = (a == null) ? 255 : a;
};

/**
 * Generate a color object based on multiple forms of parameters
 * @example
 *
 * // 1. All channels seperately as parameters
 * var color1 = cc.color(255, 255, 255, 255);
 *
 * // 2. Convert a hex string to a color
 * var color2 = cc.color("#000000");
 *
 * // 3. An color object as parameter
 * var color3 = cc.color({r: 255, g: 255, b: 255, a: 255});
 *
 * Alpha channel is optional. Default value is 255
 *
 * @param {Number|String|cc.Color} r
 * @param {Number} g
 * @param {Number} b
 * @param {Number} [a=255]
 * @return {cc.Color}
 */
cc.color = function (r, g, b, a) {
    if (r === undefined)
        return {r: 0, g: 0, b: 0, a: 255};
    if (cc.isString(r))
        return cc.hexToColor(r);
    if (cc.isObject(r))
        return {r: r.r, g: r.g, b: r.b, a: (r.a == null) ? 255 : r.a};
    return  {r: r, g: g, b: b, a: (a == null ? 255 : a)};
};

/**
 * returns true if both ccColor3B are equal. Otherwise it returns false.
 * @function
 * @param {cc.Color} color1
 * @param {cc.Color} color2
 * @return {Boolean}  true if both ccColor3B are equal. Otherwise it returns false.
 */
cc.colorEqual = function (color1, color2) {
    return color1.r === color2.r && color1.g === color2.g && color1.b === color2.b;
};

/**
 * the device accelerometer reports values for each axis in units of g-force
 * @class cc.Acceleration
 * @constructor
 * @param {Number} x
 * @param {Number} y
 * @param {Number} z
 * @param {Number} timestamp
 */
cc.Acceleration = function (x, y, z, timestamp) {
    this.x = x || 0;
    this.y = y || 0;
    this.z = z || 0;
    this.timestamp = timestamp || 0;
};

/**
 * @class cc.Vertex2F
 * @constructor
 * @param {Number} x1
 * @param {Number} y1
 */
cc.Vertex2F = function (x1, y1) {
    this.x = x1 || 0;
    this.y = y1 || 0;
};

/**
 * Helper macro that creates an Vertex2F type composed of 2 floats: x, y
 * @function
 * @param {Number} x
 * @param {Number} y
 * @return {cc.Vertex2F}
 */
cc.vertex2 = function (x, y) {
    return new cc.Vertex2F(x, y);
};

/**
 * @class cc.Vertex3F
 * @constructor
 * @param {Number} x1
 * @param {Number} y1
 * @param {Number} z1
 */
cc.Vertex3F = function (x1, y1, z1) {
    this.x = x1 || 0;
    this.y = y1 || 0;
    this.z = z1 || 0;
};

/**
 * Helper macro that creates an Vertex3F type composed of 3 floats: x, y, z
 * @function
 * @param {Number} x
 * @param {Number} y
 * @param {Number} z
 * @return {cc.Vertex3F}
 */
cc.vertex3 = function (x, y, z) {
    return new cc.Vertex3F(x, y, z);
};

/**
 * @class cc.Tex2F
 * @constructor
 * @param {Number} u1
 * @param {Number} v1
 */
cc.Tex2F = function (u1, v1) {
    this.u = u1 || 0;
    this.v = v1 || 0;
};

/**
 * Helper macro that creates an Tex2F type: A texcoord composed of 2 floats: u, y
 * @function
 * @param {Number} u
 * @param {Number} v
 * @return {cc.Tex2F}
 */
cc.tex2 = function (u, v) {
    return new cc.Tex2F(u, v);
};

/**
 * Blend Function used for textures
 * @Class cc.BlendFunc
 * @Constructor
 * @param {Number} src1 source blend function
 * @param {Number} dst1 destination blend function
 */
cc.BlendFunc = function (src1, dst1) {
    this.src = src1;
    this.dst = dst1;
};

/**
 * @function
 * @returns {cc.BlendFunc}
 */
cc.blendFuncDisable = function () {
    return new cc.BlendFunc(cc.ONE, cc.ZERO);
};

/**
 * convert a string of color for style to Color.
 * e.g. "#ff06ff"  to : cc.color(255,6,255)
 * @function
 * @param {String} hex
 * @return {cc.Color}
 */
cc.hexToColor = function (hex) {
    hex = hex.replace(/^#?/, "0x");
    var c = parseInt(hex);
    var r = c >> 16;
    var g = (c >> 8) % 256;
    var b = c % 256;
    return cc.color(r, g, b);
};

/**
 * convert Color to a string of color for style.
 * e.g.  cc.color(255,6,255)  to : "#ff06ff"
 * @function
 * @param {cc.Color} color
 * @return {String}
 */
cc.colorToHex = function (color) {
    var hR = color.r.toString(16), hG = color.g.toString(16), hB = color.b.toString(16);
    return "#" + (color.r < 16 ? ("0" + hR) : hR) + (color.g < 16 ? ("0" + hG) : hG) + (color.b < 16 ? ("0" + hB) : hB);
};

/**
 * text alignment : left
 * @constant
 * @type Number
 */
cc.TEXT_ALIGNMENT_LEFT = 0;

/**
 * text alignment : center
 * @constant
 * @type Number
 */
cc.TEXT_ALIGNMENT_CENTER = 1;

/**
 * text alignment : right
 * @constant
 * @type Number
 */
cc.TEXT_ALIGNMENT_RIGHT = 2;

/**
 * text alignment : top
 * @constant
 * @type Number
 */
cc.VERTICAL_TEXT_ALIGNMENT_TOP = 0;

/**
 * text alignment : center
 * @constant
 * @type Number
 */
cc.VERTICAL_TEXT_ALIGNMENT_CENTER = 1;

/**
 * text alignment : bottom
 * @constant
 * @type Number
 */
cc.VERTICAL_TEXT_ALIGNMENT_BOTTOM = 2;

cc._Dictionary = cc.Class.extend({
    _keyMapTb: null,
    _valueMapTb: null,
    __currId: 0,

    ctor: function () {
        this._keyMapTb = {};
        this._valueMapTb = {};
        this.__currId = 2 << (0 | (Math.random() * 10));
    },

    __getKey: function () {
        this.__currId++;
        return "key_" + this.__currId;
    },

    setObject: function (value, key) {
        if (key == null)
            return;

        var keyId = this.__getKey();
        this._keyMapTb[keyId] = key;
        this._valueMapTb[keyId] = value;
    },

    objectForKey: function (key) {
        if (key == null)
            return null;

        var locKeyMapTb = this._keyMapTb;
        for (var keyId in locKeyMapTb) {
            if (locKeyMapTb[keyId] === key)
                return this._valueMapTb[keyId];
        }
        return null;
    },

    valueForKey: function (key) {
        return this.objectForKey(key);
    },

    removeObjectForKey: function (key) {
        if (key == null)
            return;

        var locKeyMapTb = this._keyMapTb;
        for (var keyId in locKeyMapTb) {
            if (locKeyMapTb[keyId] === key) {
                delete this._valueMapTb[keyId];
                delete locKeyMapTb[keyId];
                return;
            }
        }
    },

    removeObjectsForKeys: function (keys) {
        if (keys == null)
            return;

        for (var i = 0; i < keys.length; i++)
            this.removeObjectForKey(keys[i]);
    },

    allKeys: function () {
        var keyArr = [], locKeyMapTb = this._keyMapTb;
        for (var key in locKeyMapTb)
            keyArr.push(locKeyMapTb[key]);
        return keyArr;
    },

    removeAllObjects: function () {
        this._keyMapTb = {};
        this._valueMapTb = {};
    },

    count: function () {
        return this.allKeys().length;
    }
});

/**
 * Common usage:
 *
 * var fontDef = new cc.FontDefinition();
 * fontDef.fontName = "Arial";
 * fontDef.fontSize = 12;
 * ...
 *
 * OR using inline definition usefull for constructor injection
 *
 * var fontDef = new cc.FontDefinition({
 *  fontName: "Arial",
 *  fontSize: 12
 * });
 *
 *
 *
 * @class cc.FontDefinition
 * @param {Object} properties - (OPTIONAL) Allow inline FontDefinition
 * @constructor
 */
cc.FontDefinition = function (properties) {
    var _t = this;
    _t.fontName = "Arial";
    _t.fontSize = 12;
    _t.textAlign = cc.TEXT_ALIGNMENT_CENTER;
    _t.verticalAlign = cc.VERTICAL_TEXT_ALIGNMENT_TOP;
    _t.fillStyle = cc.color(255, 255, 255, 255);
    _t.boundingWidth = 0;
    _t.boundingHeight = 0;

    _t.strokeEnabled = false;
    _t.strokeStyle = cc.color(255, 255, 255, 255);
    _t.lineWidth = 1;
    _t.lineHeight = "normal";
    _t.fontStyle = "normal";
    _t.fontWeight = "normal";

    _t.shadowEnabled = false;
    _t.shadowOffsetX = 0;
    _t.shadowOffsetY = 0;
    _t.shadowBlur = 0;
    _t.shadowOpacity = 1.0;

    //properties mapping:
    if(properties && properties instanceof Object){
         for(var key in properties){
             _t[key] = properties[key];
         }
    }
};
/**
 * Web ONLY
 * */
cc.FontDefinition.prototype._getCanvasFontStr = function(){
    var lineHeight = !this.lineHeight.charAt ? this.lineHeight+"px" : this.lineHeight;
    return this.fontStyle + " " + this.fontWeight + " " + this.fontSize + "px/"+lineHeight+" '" + this.fontName + "'";
};

if (cc._renderType === cc._RENDER_TYPE_WEBGL) {
    cc.assert(cc.isFunction(cc._tmp.WebGLColor), cc._LogInfos.MissingFile, "CCTypesWebGL.js");
    cc._tmp.WebGLColor();
    delete cc._tmp.WebGLColor;
}

cc.assert(cc.isFunction(cc._tmp.PrototypeColor), cc._LogInfos.MissingFile, "CCTypesPropertyDefine.js");
cc._tmp.PrototypeColor();
delete cc._tmp.PrototypeColor;

