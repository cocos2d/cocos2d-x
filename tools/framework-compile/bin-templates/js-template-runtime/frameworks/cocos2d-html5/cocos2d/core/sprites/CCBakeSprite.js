/****************************************************************************
 Copyright (c) 2013-2014 Chukong Technologies Inc.

 http://www.cocos2d-x.org

 Permission is hereby granted, free of charge, to any person obtaining a copy
 of _t software and associated documentation files (the "Software"), to deal
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
 * cc.BakeSprite is a type of sprite that will be cached.
 * @class
 * @extend cc.Sprite
 */
cc.BakeSprite = cc.Sprite.extend(/** @lends cc.BakeSprite# */{
    _cacheCanvas: null,
    _cacheContext: null,

    ctor: function(){
        cc.Sprite.prototype.ctor.call(this);
        var canvasElement = document.createElement("canvas");
        canvasElement.width = canvasElement.height = 10;
        this._cacheCanvas = canvasElement;
        this._cacheContext = new cc.CanvasContextWrapper(canvasElement.getContext("2d"));

        var texture = new cc.Texture2D();
        texture.initWithElement(canvasElement);
        texture.handleLoadedTexture();
        this.setTexture(texture);
    },

    getCacheContext: function(){
        return this._cacheContext;
    },

    getCacheCanvas: function(){
        return this._cacheCanvas;
    },

    /**
     * reset the cache canvas size
     * @param {cc.Size|Number} sizeOrWidth  size or width
     * @param {Number} [height]
     */
    resetCanvasSize: function(sizeOrWidth, height){
        if(height === undefined){
            height = sizeOrWidth.height;
            sizeOrWidth = sizeOrWidth.width;
        }
        var locCanvas = this._cacheCanvas;
        locCanvas.width = sizeOrWidth;
        locCanvas.height = height;   //TODO note baidu browser      reset the context after set width or height
        this.getTexture().handleLoadedTexture();
        this.setTextureRect(cc.rect(0,0, sizeOrWidth, height), false);
    }
});
