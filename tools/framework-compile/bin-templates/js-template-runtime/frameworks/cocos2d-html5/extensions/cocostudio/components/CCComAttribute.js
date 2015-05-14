/****************************************************************************
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
 * The attribute component for Cocostudio.
 * @class
 * @extends ccs.Component
 */
ccs.ComAttribute = ccs.Component.extend(/** @lends ccs.ComAttribute# */{
    _jsonDict: null,
    _filePath: "",

    /**
     * Construction of ccs.ComAttribute
     */
    ctor: function () {
        cc.Component.prototype.ctor.call(this);
        this._jsonDict = {};
        this._filePath = "";
        this._name = "CCComAttribute";
        ccs.ComAttribute.prototype.init.call(this);
    },

    /**
     * Initializes a ccs.ComAttribute
     * @returns {boolean}
     */
    init: function () {
        this._jsonDict = {};
        return true;
    },

    /**
     * Sets int attribute
     * @param {String} key
     * @param {number} value
     */
    setInt: function (key, value) {
        if (!key) {
            cc.log("Argument must be non-nil");
            return;
        }
        this._jsonDict[key] = value;
    },

    /**
     * Sets double attribute
     * @param {String} key
     * @param {number} value
     */
    setDouble: function (key, value) {
        if (!key) {
            cc.log("Argument must be non-nil");
            return;
        }
        this._jsonDict[key] = value;
    },

    /**
     * Sets float attribute
     * @param {String} key
     * @param {number} value
     */
    setFloat: function (key, value) {
        if (!key) {
            cc.log("Argument must be non-nil");
            return;
        }
        this._jsonDict[key] = value;
    },

    /**
     * Sets boolean attribute
     * @param {String} key
     * @param {Boolean} value
     */
    setBool: function (key, value) {
        if (!key) {
            cc.log("Argument must be non-nil");
            return;
        }
        this._jsonDict[key] = value;
    },

    /**
     * Sets string attribute
     * @param {String} key
     * @param {Boolean} value
     */
    setString: function (key, value) {
        if (!key) {
            cc.log("Argument must be non-nil");
            return;
        }
        this._jsonDict[key] = value;
    },

    /**
     * Sets object attribute
     * @param {String} key
     * @param {Object} value
     */
    setObject: function (key, value) {
        if (!key) {
            cc.log("Argument must be non-nil");
            return;
        }
        this._jsonDict[key] = value;
    },

    /**
     * Returns int value from attribute
     * @param {String} key
     * @returns {Number}
     */
    getInt: function (key) {
        var ret = this._jsonDict[key];
        return parseInt(ret || 0);
    },

    /**
     * Returns double value from attribute
     * @param {String} key
     * @returns {Number}
     */
    getDouble: function (key) {
        var ret = this._jsonDict[key];
        return parseFloat(ret || 0.0);
    },

    /**
     * Returns float value from attribute
     * @param {String} key
     * @returns {Number}
     */
    getFloat: function (key) {
        var ret = this._jsonDict[key];
        return parseFloat(ret || 0.0);
    },

    /**
     * Returns boolean value from attribute
     * @param {String} key
     * @returns {Boolean}
     */
    getBool: function (key) {
        var ret = this._jsonDict[key];
        return Boolean(ret || false);
    },

    /**
     * Returns string value from attribute
     * @param {String} key
     * @returns {String}
     */
    getString: function (key) {
        var ret = this._jsonDict[key];
        return ret || "";
    },

    /**
     * Returns object value from attribute
     * @param {String} key
     * @returns {Object}
     */
    getObject: function (key) {
        return this._jsonDict[key];
    },

    /**
     * Parses json file.
     * @param  filename
     */
    parse:function(filename){
        this._jsonDict = cc.loader.getRes(filename);
    }
});
/**
 * allocates and initializes a ComAttribute.
 * @deprecated since v3.0, please use new construction instead.
 * @return {ccs.ComAttribute}
 * @example
 * // example
 * var com = ccs.ComAttribute.create();
 */
ccs.ComAttribute.create = function () {
    return new ccs.ComAttribute();
};