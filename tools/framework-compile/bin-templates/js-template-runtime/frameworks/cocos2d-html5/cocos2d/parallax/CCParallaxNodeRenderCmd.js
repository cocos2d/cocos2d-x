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

//TODO find a way to simple these code.

(function(){
    cc.ParallaxNode.CanvasRenderCmd = function(renderable){
        cc.Node.CanvasRenderCmd.call(this, renderable);
        this._needDraw = false;
    };

    var proto = cc.ParallaxNode.CanvasRenderCmd.prototype = Object.create(cc.Node.CanvasRenderCmd.prototype);
    proto.constructor = cc.ParallaxNode.CanvasRenderCmd;

    proto.updateStatus = function(){
        this._node._updateParallaxPosition();
        cc.Node.CanvasRenderCmd.prototype.updateStatus.call(this);
    };

    proto._syncStatus = function(parentCmd){
        this._node._updateParallaxPosition();
        cc.Node.CanvasRenderCmd.prototype._syncStatus.call(this, parentCmd);
    }
})();

(function(){
    if(cc._renderType !== cc._RENDER_TYPE_WEBGL)
        return;

    cc.ParallaxNode.WebGLRenderCmd = function(renderable){
        cc.Node.WebGLRenderCmd.call(this, renderable);
        this._needDraw = false;
    };

    var proto = cc.ParallaxNode.WebGLRenderCmd.prototype = Object.create(cc.Node.WebGLRenderCmd.prototype);
    proto.constructor = cc.ParallaxNode.WebGLRenderCmd;

    proto.updateStatus = function(){
        this._node._updateParallaxPosition();
        cc.Node.WebGLRenderCmd.prototype.updateStatus.call(this);
    };

    proto._syncStatus = function(parentCmd){
        this._node._updateParallaxPosition();
        cc.Node.WebGLRenderCmd.prototype._syncStatus.call(this, parentCmd);
    }
})();

