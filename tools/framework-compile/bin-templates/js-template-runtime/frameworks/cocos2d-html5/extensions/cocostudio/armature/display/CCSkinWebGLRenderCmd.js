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

(function(){
    ccs.Skin.WebGLRenderCmd = function(renderable){
        cc.Sprite.WebGLRenderCmd.call(this, renderable);
    };

    var proto = ccs.Skin.WebGLRenderCmd.prototype = Object.create(cc.Sprite.WebGLRenderCmd.prototype);
    cc.inject(ccs.Skin.RenderCmd, proto);
    proto.constructor = ccs.Skin.WebGLRenderCmd;

    proto.updateTransform = function(){
        var node = this._node;
        var locQuad = this._quad;
        // If it is not visible, or one of its ancestors is not visible, then do nothing:
        if( !node._visible)
            locQuad.br.vertices = locQuad.tl.vertices = locQuad.tr.vertices = locQuad.bl.vertices = {x: 0, y: 0, z: 0};
        else {
            //
            // calculate the Quad based on the Affine Matrix
            //
            var transform = this.getNodeToParentTransform();         //this._transform;
            var size = node._rect;

            var x1 = node._offsetPosition.x, y1 = node._offsetPosition.y;

            var x2 = x1 + size.width, y2 = y1 + size.height;
            var x = transform.tx, y = transform.ty;

            var cr = transform.a, sr = transform.b;
            var cr2 = transform.d, sr2 = -transform.c;
            var ax = x1 * cr - y1 * sr2 + x;
            var ay = x1 * sr + y1 * cr2 + y;

            var bx = x2 * cr - y1 * sr2 + x;
            var by = x2 * sr + y1 * cr2 + y;

            var cx = x2 * cr - y2 * sr2 + x;
            var cy = x2 * sr + y2 * cr2 + y;

            var dx = x1 * cr - y2 * sr2 + x;
            var dy = x1 * sr + y2 * cr2 + y;

            var locVertexZ = node._vertexZ;
            if(!cc.SPRITEBATCHNODE_RENDER_SUBPIXEL) {
                ax = 0 | ax;
                ay = 0 | ay;
                bx = 0 | bx;
                by = 0 | by;
                cx = 0 | cx;
                cy = 0 | cy;
                dx = 0 | dx;
                dy = 0 | dy;
            }
            this.SET_VERTEX3F(locQuad.bl.vertices,ax, ay,locVertexZ);
            this.SET_VERTEX3F(locQuad.br.vertices,bx, by,locVertexZ);
            this.SET_VERTEX3F(locQuad.tl.vertices,dx, dy,locVertexZ);
            this.SET_VERTEX3F(locQuad.tr.vertices,cx, cy,locVertexZ);
        }

        // MARMALADE CHANGE: ADDED CHECK FOR nullptr, TO PERMIT SPRITES WITH NO BATCH NODE / TEXTURE ATLAS
        if (node.textureAtlas)
            node.textureAtlas.updateQuad(locQuad, node.textureAtlas.getTotalQuads());
        this._quadDirty = true;
    };

    proto.SET_VERTEX3F = function(_v_, _x_, _y_, _z_){
        (_v_).x = (_x_);
        (_v_).y = (_y_);
        (_v_).z = (_z_);
    };

    proto.rendering = function(ctx){
        var node = this._node;
        if (!node._textureLoaded)
            return;

        var gl = ctx || cc._renderContext, locTexture = node._texture;
        if (locTexture && locTexture._textureLoaded) {
            this._shaderProgram.use();
            this._shaderProgram.setUniformForModelViewAndProjectionMatrixWithMat4();

            cc.glBlendFunc(node._blendFunc.src, node._blendFunc.dst);
            //optimize performance for javascript
            cc.glBindTexture2DN(0, locTexture);                   // = cc.glBindTexture2D(locTexture);
            cc.glEnableVertexAttribs(cc.VERTEX_ATTRIB_FLAG_POS_COLOR_TEX);

            gl.bindBuffer(gl.ARRAY_BUFFER, this._quadWebBuffer);
            if (this._quadDirty) {
                gl.bufferData(gl.ARRAY_BUFFER, this._quad.arrayBuffer, gl.DYNAMIC_DRAW);
                this._quadDirty = false;
            }
            gl.vertexAttribPointer(0, 3, gl.FLOAT, false, 24, 0);                   //cc.VERTEX_ATTRIB_POSITION
            gl.vertexAttribPointer(1, 4, gl.UNSIGNED_BYTE, true, 24, 12);           //cc.VERTEX_ATTRIB_COLOR
            gl.vertexAttribPointer(2, 2, gl.FLOAT, false, 24, 16);                  //cc.VERTEX_ATTRIB_TEX_COORDS

            gl.drawArrays(gl.TRIANGLE_STRIP, 0, 4);
        }

        cc.g_NumberOfDraws++;
        if (cc.SPRITE_DEBUG_DRAW === 0 && !node._showNode)
            return;

        if (cc.SPRITE_DEBUG_DRAW === 1 || node._showNode) {
            // draw bounding box
            var locQuad = this._quad;
            var verticesG1 = [
                cc.p(locQuad.tl.vertices.x, locQuad.tl.vertices.y),
                cc.p(locQuad.bl.vertices.x, locQuad.bl.vertices.y),
                cc.p(locQuad.br.vertices.x, locQuad.br.vertices.y),
                cc.p(locQuad.tr.vertices.x, locQuad.tr.vertices.y)
            ];
            cc._drawingUtil.drawPoly(verticesG1, 4, true);
        } else if (cc.SPRITE_DEBUG_DRAW === 2) {
            // draw texture box
            var drawRectG2 = node.getTextureRect();
            var offsetPixG2 = node.getOffsetPosition();
            var verticesG2 = [cc.p(offsetPixG2.x, offsetPixG2.y), cc.p(offsetPixG2.x + drawRectG2.width, offsetPixG2.y),
                cc.p(offsetPixG2.x + drawRectG2.width, offsetPixG2.y + drawRectG2.height), cc.p(offsetPixG2.x, offsetPixG2.y + drawRectG2.height)];
            cc._drawingUtil.drawPoly(verticesG2, 4, true);
        } // CC_SPRITE_DEBUG_DRAW
    };
})();