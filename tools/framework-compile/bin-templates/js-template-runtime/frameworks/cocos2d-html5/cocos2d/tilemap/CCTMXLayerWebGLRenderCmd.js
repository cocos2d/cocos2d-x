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
    cc.TMXLayer.WebGLRenderCmd = function(renderableObject){
        cc.SpriteBatchNode.WebGLRenderCmd.call(this, renderableObject);
        this._needDraw = true;
    };

    var proto = cc.TMXLayer.WebGLRenderCmd.prototype = Object.create(cc.SpriteBatchNode.WebGLRenderCmd.prototype);
    proto.constructor = cc.TMXLayer.WebGLRenderCmd;

    proto._updateCacheContext = function(){};

    proto.initImageSize = function(){
        var node = this._node;
        node.tileset.imageSize = this._textureAtlas.texture.getContentSizeInPixels();

        // By default all the tiles are aliased
        // pros:
        //  - easier to render
        // cons:
        //  - difficult to scale / rotate / etc.
        this._textureAtlas.texture.setAliasTexParameters();
    };

    proto._reusedTileWithRect = function(rect){
        var node = this._node;
        if (!node._reusedTile) {
            node._reusedTile = new cc.Sprite();
            node._reusedTile.initWithTexture(node.texture, rect, false);
            node._reusedTile.batchNode = node;
        } else {
            // XXX HACK: Needed because if "batch node" is nil,
            // then the Sprite'squad will be reset
            node._reusedTile.batchNode = null;

            // Re-init the sprite
            node._reusedTile.setTextureRect(rect, false);

            // restore the batch node
            node._reusedTile.batchNode = node;
        }
        return node._reusedTile;
    };
})();
