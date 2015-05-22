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
 * The controller component for Cocostudio.
 * @class
 * @extends ccs.Component
 */
ccs.ComController = ccs.Component.extend(/** @lends ccs.ComController# */{
    /**
     * Construction of ccs.ComController.
     */
    ctor: function () {
        cc.Component.prototype.ctor.call(this);
        this._name = "ComController";
        ccs.ComController.prototype.init.call(this);
    },

    /**
     * The callback calls when controller component enter stage.
     * @override
     */
    onEnter: function () {
        if (this._owner !== null)
            this._owner.scheduleUpdate();
    },

    /**
     * Returns controller component whether is enabled
     * @returns {Boolean}
     */
    isEnabled: function () {
        return this._enabled;
    },

    /**
     * Sets controller component whether is enabled
     * @param {Boolean} bool
     */
    setEnabled: function (bool) {
        this._enabled = bool;
    }
});
/**
 * Allocates and initializes a ComController.
 * @deprecated since v3.0, please use new construction instead.
 * @return {ccs.ComController}
 * @example
 * // example
 * var com = ccs.ComController.create();
 */
ccs.ComController.create = function () {
    return new ccs.ComController();
};