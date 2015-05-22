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
    cc.LabelAtlas.WebGLRenderCmd = function(renderable){
        cc.AtlasNode.WebGLRenderCmd.call(this, renderable);
        this._needDraw = true;
    };

    var proto = cc.LabelAtlas.WebGLRenderCmd.prototype = Object.create(cc.AtlasNode.WebGLRenderCmd.prototype);
    proto.constructor = cc.LabelAtlas.WebGLRenderCmd;

    proto.setCascade = function(){
        var node = this._node;
        node._cascadeOpacityEnabled = true;
        node._cascadeColorEnabled = true;
    };

    proto.rendering = function(ctx){
        cc.AtlasNode.WebGLRenderCmd.prototype.rendering.call(this, ctx);
        if (cc.LABELATLAS_DEBUG_DRAW) {
            var s = this._node.getContentSize();
            var vertices = [cc.p(0, 0), cc.p(s.width, 0),
                cc.p(s.width, s.height), cc.p(0, s.height)];
            cc._drawingUtil.drawPoly(vertices, 4, true);
        }
    };

    proto.updateAtlasValues = function(){
        var node = this._node;
        var locString = node._string;
        var n = locString.length;
        var locTextureAtlas = this._textureAtlas;

        var texture = locTextureAtlas.texture;
        var textureWide = texture.pixelsWidth;
        var textureHigh = texture.pixelsHeight;
        var itemWidthInPixels = node._itemWidth;
        var itemHeightInPixels = node._itemHeight;
        if (!node._ignoreContentScaleFactor) {
            itemWidthInPixels = node._itemWidth * cc.contentScaleFactor();
            itemHeightInPixels = node._itemHeight * cc.contentScaleFactor();
        }
        if (n > locTextureAtlas.getCapacity())
            cc.log("cc.LabelAtlas._updateAtlasValues(): Invalid String length");
        var quads = locTextureAtlas.quads;
        var locDisplayedColor = this._displayedColor;
        var curColor = {r: locDisplayedColor.r, g: locDisplayedColor.g, b: locDisplayedColor.b, a: node._displayedOpacity};
        var locItemWidth = node._itemWidth;
        for (var i = 0; i < n; i++) {
            var a = locString.charCodeAt(i) - node._mapStartChar.charCodeAt(0);
            var row = a % node._itemsPerRow;
            var col = 0 | (a / node._itemsPerRow);

            var left, right, top, bottom;
            if (cc.FIX_ARTIFACTS_BY_STRECHING_TEXEL) {
                // Issue #938. Don't use texStepX & texStepY
                left = (2 * row * itemWidthInPixels + 1) / (2 * textureWide);
                right = left + (itemWidthInPixels * 2 - 2) / (2 * textureWide);
                top = (2 * col * itemHeightInPixels + 1) / (2 * textureHigh);
                bottom = top + (itemHeightInPixels * 2 - 2) / (2 * textureHigh);
            } else {
                left = row * itemWidthInPixels / textureWide;
                right = left + itemWidthInPixels / textureWide;
                top = col * itemHeightInPixels / textureHigh;
                bottom = top + itemHeightInPixels / textureHigh;
            }
            var quad = quads[i];
            var locQuadTL = quad.tl, locQuadTR = quad.tr, locQuadBL = quad.bl, locQuadBR = quad.br;
            locQuadTL.texCoords.u = left;
            locQuadTL.texCoords.v = top;
            locQuadTR.texCoords.u = right;
            locQuadTR.texCoords.v = top;
            locQuadBL.texCoords.u = left;
            locQuadBL.texCoords.v = bottom;
            locQuadBR.texCoords.u = right;
            locQuadBR.texCoords.v = bottom;

            locQuadBL.vertices.x = (i * locItemWidth);
            locQuadBL.vertices.y = 0;
            locQuadBL.vertices.z = 0.0;
            locQuadBR.vertices.x = (i * locItemWidth + locItemWidth);
            locQuadBR.vertices.y = 0;
            locQuadBR.vertices.z = 0.0;
            locQuadTL.vertices.x = i * locItemWidth;
            locQuadTL.vertices.y = node._itemHeight;
            locQuadTL.vertices.z = 0.0;
            locQuadTR.vertices.x = i * locItemWidth + locItemWidth;
            locQuadTR.vertices.y = node._itemHeight;
            locQuadTR.vertices.z = 0.0;
            locQuadTL.colors = curColor;
            locQuadTR.colors = curColor;
            locQuadBL.colors = curColor;
            locQuadBR.colors = curColor;
        }
        if (n > 0) {
            locTextureAtlas.dirty = true;
            var totalQuads = locTextureAtlas.totalQuads;
            if (n > totalQuads)
                locTextureAtlas.increaseTotalQuadsWith(n - totalQuads);
        }
    };

    proto.setString = function(label){
        var len = label.length;
        if (len > this._textureAtlas.totalQuads)
            this._textureAtlas.resizeCapacity(len);
    };

    proto._addChild = function(){};
})();