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

cc.INT_VALUE = 0;

cc.FLOAT_VALUE = 1;

cc.POINTER_VALUE = 2;

cc.BOOL_VALUE = 3;

cc.UNSIGNEDCHAR_VALUE = 4;


cc.Color3BWapper = cc.Class.extend({
    _color:null,
    ctor:function () {
        this._color = cc.color(0, 0, 0);
    },
    getColor:function () {
        return this._color;
    }
});

cc.Color3BWapper.create = function (color) {
    var ret = new cc.Color3BWapper();
    if (ret) {
        ret._color.r = color.r;
        ret._color.g = color.g;
        ret._color.b = color.b;
    }
    return ret;
};

cc.BuilderValue = cc.Class.extend({
    _value:null,
    _type:0,

    getIntValue:function () {
    },
    getFloatValue:function () {
    },
    getBoolValue:function () {
    },
    getByteValue:function () {
    },
    getPointer:function () {
    },

    getValue:function(){
        return this._value;
    }
});

cc.BuilderValue.create = function (value) {
    return new cc.BuilderValue();
};

