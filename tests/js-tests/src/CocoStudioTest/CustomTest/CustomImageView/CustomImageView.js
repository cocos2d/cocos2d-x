/****************************************************************************
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

var CustomImageView = ccui.ImageView.extend({

    _label: null,

    init: function(){
        if (ccui.ImageView.prototype.init.call(this))
        {
            return true;
        }
        return false;
    },

    _initRenderer: function(){
        ccui.ImageView.prototype._initRenderer.call(this);

        this._label = new cc.LabelTTF();
        cc.ProtectedNode.prototype.addChild.call(this, this._label, this.getLocalZOrder() + 1, -1);
    },

    createInstance: function(){
        return CustomImageView;
    },

    setText: function(text){
        this._label.setString(text);
    },

    getText: function(){
        return this._label.getString();
    }
});

CustomImageView.create = function(){
    var custom = new CustomImageView();

    if (custom && custom.init())
    {
        return custom;
    }
    return null;

};