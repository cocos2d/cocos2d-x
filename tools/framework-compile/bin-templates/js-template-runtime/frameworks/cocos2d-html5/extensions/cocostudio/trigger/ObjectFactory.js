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
 * The singleton object that creating object factory, it creates object with class name, and manager the type mapping.
 * @class
 * @name ccs.objectFactory
 */
ccs.objectFactory = /** @lends ccs.objectFactory# */{
    _typeMap: {},

    /**
     * Creates object with class name. if the the class name without register in type map, it returns null.
     * @param {String} className
     * @returns {*}
     */
    createObject: function (className) {
        var o = null;
        var t = this._typeMap[className];
        if (t) {
            if(cc.isFunction(t._fun))
                o = new t._fun();
            else
                o = t._fun;
        }
        return o;
    },

    /**
     * Registers class type in type map.
     * @param {ccs.TInfo} t
     */
    registerType: function (t) {
        this._typeMap[t._className] = t;
    },

    /**
     * Creates ccui widget object.
     * @param {String} name widget name
     * @returns {ccui.Widget|null}
     */
    createGUI: function(name){
        var object = null;
        if(name === "Panel")
            name = "Layout";
        else if(name === "TextArea")
            name = "Label";
        else if(name === "TextButton")
            name = "Button";

        var t = this._typeMap[name];
        if(t && t._fun)
            object = t._fun;

        return object;
    },

    removeAll: function(){
        this._typeMap = {};
    }
};

ccs.TInfo = ccs.Class.extend({
    _className: "",
    _fun: null,

    ctor: function (c, f) {
        if (f) {
            this._className = c;
            this._fun = f;
        } else {
            this._className = c._className;
            this._fun = c._fun;
        }
        ccs.objectFactory.registerType(this);
    }
});
