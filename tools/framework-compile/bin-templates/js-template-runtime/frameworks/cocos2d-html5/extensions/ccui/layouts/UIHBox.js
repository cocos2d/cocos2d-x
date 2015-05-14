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
 * The horizontal box of Cocos UI. Its layout type is ccui.Layout.LINEAR_HORIZONTAL.
 * @class
 * @extends ccui.Layout
 */
ccui.HBox = ccui.Layout.extend(/** @lends ccui.HBox# */{
    /**
     * The constructor of ccui.HBox
     * @function
     * @param {cc.Size} [size]
     */
    ctor: function(size){
        ccui.Layout.prototype.ctor.call(this, size);
        if(size !== undefined)
            this.initWithSize(size);
        else
           this.init();
    },

    /**
     * Initialize a HBox. please do not call this function by yourself, you should pass the parameters to constructor to initialize it.
     * @override
     * @returns {boolean}
     */
    init: function(){
        if(ccui.Layout.prototype.init.call(this)){
            this.setLayoutType(ccui.Layout.LINEAR_HORIZONTAL);
            return true;
        }
        return false;
    },

    /**
     * Initializes a HBox with size.
     * @param size
     * @returns {boolean}
     */
    initWithSize: function(size){
        if(this.init()){
            this.setContentSize(size);
            return true;
        }
        return false;
    }
});

/**
 * Creates a HBox object
 * @deprecated since v3.0, please use new ccui.HBox(size) instead.
 * @param {cc.Size} size
 * @returns {ccui.HBox}
 */
ccui.HBox.create = function(size){
    return new ccui.HBox(size);
};