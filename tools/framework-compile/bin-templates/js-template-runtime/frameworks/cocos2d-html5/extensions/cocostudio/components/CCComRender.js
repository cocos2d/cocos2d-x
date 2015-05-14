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
 * The render component for Cocostudio.
 * @class
 * @extends ccs.Component
 */
ccs.ComRender = ccs.Component.extend(/** @lends ccs.ComRender# */{
    _render: null,
    /**
     * Construction of ccs.ComRender
     * @param {cc.Node} node
     * @param {String} comName
     */
    ctor: function (node, comName) {
        cc.Component.prototype.ctor.call(this);
        this._render = node;
        this._name = comName;
        this.isRenderer = true;
        ccs.ComRender.prototype.init.call(this);
    },

    /**
     * The callback calls when a render component enter stage.
     */
    onEnter: function () {
        if (this._owner)
            this._owner.addChild(this._render);
    },

    /**
     * The callback calls when a render component exit stage.
     */
    onExit: function () {
        if (this._owner) {
            this._owner.removeChild(this._render, true);
            this._render = null;
        }
    },

    /**
     * Returns a render node
     * @returns {cc.Node}
     */
    getNode: function () {
        return this._render;
    },

    /**
     * Sets a render node to component.
     * @param {cc.Node} node
     */
    setNode: function (node) {
        this._render = node;
    }
});

/**
 * allocates and initializes a ComRender.
 * @deprecated since v3.0, please use new construction instead.
 * @return {ccs.ComRender}
 * @example
 * // example
 * var com = ccs.ComRender.create();
 */
ccs.ComRender.create = function (node, comName) {
    return new ccs.ComRender(node, comName);
};
