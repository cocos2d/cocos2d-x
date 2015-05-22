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

(function(){
    /**
     * cc.ParticleBatchNode's rendering objects of WebGL
     */
    cc.ParticleBatchNode.WebGLRenderCmd = function(renderable){
        cc.Node.WebGLRenderCmd.call(this, renderable);
        this._needDraw = true;
    };

    var proto = cc.ParticleBatchNode.WebGLRenderCmd.prototype = Object.create(cc.Node.WebGLRenderCmd.prototype);
    proto.constructor = cc.ParticleBatchNode.WebGLRenderCmd;

    proto.rendering = function (ctx) {
        var _t = this._node;
        if (_t.textureAtlas.totalQuads === 0)
            return;

        this._shaderProgram.use();
        this._shaderProgram._setUniformForMVPMatrixWithMat4(this._stackMatrix);
        cc.glBlendFuncForParticle(_t._blendFunc.src, _t._blendFunc.dst);
        _t.textureAtlas.drawQuads();
    };

    proto._initWithTexture = function(){
        this._shaderProgram = cc.shaderCache.programForKey(cc.SHADER_POSITION_TEXTURECOLOR);
    };

    proto.visit = function(parentCmd){
        var node = this._node;
        // CAREFUL:
        // This visit is almost identical to cc.Node#visit
        // with the exception that it doesn't call visit on it's children
        //
        // The alternative is to have a void cc.Sprite#visit, but
        // although this is less mantainable, is faster
        //
        if (!node._visible)
            return;

        var currentStack = cc.current_stack;
        currentStack.stack.push(currentStack.top);
        this._syncStatus(parentCmd);
        currentStack.top = this._stackMatrix;
        //this.draw(ctx);
        cc.renderer.pushRenderCommand(this);

        this._dirtyFlag = 0;
        cc.kmGLPopMatrix();
    };
})();