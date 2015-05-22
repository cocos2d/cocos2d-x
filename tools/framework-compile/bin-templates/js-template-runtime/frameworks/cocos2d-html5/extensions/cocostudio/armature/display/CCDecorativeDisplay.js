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
 * Decorative a display node for Cocos Armature
 * @class
 * @extends ccs.Class
 */
ccs.DecorativeDisplay = ccs.Class.extend(/** @lends ccs.DecorativeDisplay# */{
    _display: null,
    _colliderDetector: null,
    _displayData: null,

    ctor:function () {
        this._display = null;
        this._colliderDetector = null;
        this._displayData = null;

        //ccs.DecorativeDisplay.prototype.init.call(this);
    },

    /**
     * Initializes a ccs.DecorativeDisplay
     * @returns {boolean}
     */
    init:function () {
        return true;
    },

    /**
     * Sets display node to decorative
     * @param {cc.Node} display
     */
    setDisplay:function (display) {
        if(display._parent){
            display._parent.removeChild(display);
            delete display._parent;
        }
        this._display = display;
    },

    /**
     * Returns the display node
     * @returns {cc.Node}
     */
    getDisplay:function () {
        return this._display;
    },

    /**
     * Sets collide detector
     * @param {ccs.ColliderDetector} colliderDetector
     */
    setColliderDetector:function (colliderDetector) {
        this._colliderDetector = colliderDetector;
    },

    /**
     * Returns collide detector
     * @returns {ccs.ColliderDetector}
     */
    getColliderDetector:function () {
        return this._colliderDetector;
    },

    /**
     * Sets display data
     * @param {ccs.DisplayData} displayData
     */
    setDisplayData:function (displayData) {
        this._displayData = displayData;
    },

    /**
     * Returns display data
     * @returns {ccs.DisplayData}
     */
    getDisplayData:function () {
        return this._displayData;
    },

    release:function () {
        this._display = null;
        this._displayData = null;
        this._colliderDetector = null;
    }
});

/**
 * Allocates and initializes a decorative display.
 * @return {ccs.DecorativeDisplay}
 * @deprecated since v3.1, please use new construction instead
 */
ccs.DecorativeDisplay.create = function () {
    return new ccs.DecorativeDisplay();
};