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

cc.MotionStreak.WebGLRenderCmd = function(renderableObject){
    cc.Node.WebGLRenderCmd.call(this, renderableObject);
    this._needDraw = true;
    this._shaderProgram = cc.shaderCache.programForKey(cc.SHADER_POSITION_TEXTURECOLOR);
};

cc.MotionStreak.WebGLRenderCmd.prototype = Object.create(cc.Node.WebGLRenderCmd.prototype);
cc.MotionStreak.WebGLRenderCmd.prototype.constructor = cc.Sprite.WebGLRenderCmd;

cc.MotionStreak.WebGLRenderCmd.prototype.rendering = function(ctx){
    var node = this._node;
    if (node._nuPoints <= 1)
        return;

    if (node.texture && node.texture.isLoaded()) {
        ctx = ctx || cc._renderContext;
        this._shaderProgram.use();
        this._shaderProgram._setUniformForMVPMatrixWithMat4(this._stackMatrix);
        cc.glEnableVertexAttribs(cc.VERTEX_ATTRIB_FLAG_POS_COLOR_TEX);
        cc.glBlendFunc(node._blendFunc.src, node._blendFunc.dst);

        cc.glBindTexture2D(node.texture);

        //position
        ctx.bindBuffer(ctx.ARRAY_BUFFER, node._verticesBuffer);
        ctx.bufferData(ctx.ARRAY_BUFFER, node._vertices, ctx.DYNAMIC_DRAW);
        ctx.vertexAttribPointer(cc.VERTEX_ATTRIB_POSITION, 2, ctx.FLOAT, false, 0, 0);

        //texcoords
        ctx.bindBuffer(ctx.ARRAY_BUFFER, node._texCoordsBuffer);
        ctx.bufferData(ctx.ARRAY_BUFFER, node._texCoords, ctx.DYNAMIC_DRAW);
        ctx.vertexAttribPointer(cc.VERTEX_ATTRIB_TEX_COORDS, 2, ctx.FLOAT, false, 0, 0);

        //colors
        ctx.bindBuffer(ctx.ARRAY_BUFFER, node._colorPointerBuffer);
        ctx.bufferData(ctx.ARRAY_BUFFER, node._colorPointer, ctx.DYNAMIC_DRAW);
        ctx.vertexAttribPointer(cc.VERTEX_ATTRIB_COLOR, 4, ctx.UNSIGNED_BYTE, true, 0, 0);

        ctx.drawArrays(ctx.TRIANGLE_STRIP, 0, node._nuPoints * 2);
        cc.g_NumberOfDraws++;
    }
};