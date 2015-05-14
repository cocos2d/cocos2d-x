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
    cc.TMXLayer.CanvasRenderCmd = function(renderable){
        cc.SpriteBatchNode.CanvasRenderCmd.call(this, renderable);
        this._needDraw = true;
        this._realWorldTransform = {a: 1, b: 0, c: 0, d: 1, tx: 0, ty: 0};

        var locCanvas = cc._canvas;
        var tmpCanvas = cc.newElement('canvas');
        tmpCanvas.width = locCanvas.width;
        tmpCanvas.height = locCanvas.height;
        this._cacheCanvas = tmpCanvas;
        this._cacheContext = new cc.CanvasContextWrapper(this._cacheCanvas.getContext('2d'));
        var tempTexture = new cc.Texture2D();
        tempTexture.initWithElement(tmpCanvas);
        tempTexture.handleLoadedTexture();
        this._cacheTexture = tempTexture;
        // This class uses cache, so its default cachedParent should be himself
        this._cacheDirty = false;
    };

    var proto = cc.TMXLayer.CanvasRenderCmd.prototype = Object.create(cc.SpriteBatchNode.CanvasRenderCmd.prototype);
    proto.constructor = cc.TMXLayer.CanvasRenderCmd;

    //set the cache dirty flag for canvas
    proto._setNodeDirtyForCache = function () {
        this._cacheDirty  = true;
    };

    proto._renderingChildToCache = function () {
        if (this._cacheDirty) {
            var wrapper = this._cacheContext,
                context = wrapper.getContext(), locCanvas = this._cacheCanvas;

            //wrapper.save();
            context.setTransform(1, 0, 0, 1, 0, 0);
            context.clearRect(0, 0, locCanvas.width, locCanvas.height);
            //reset the cache context

            var locChildren = this._node._children;
            for (var i = 0, len =  locChildren.length; i < len; i++) {
                if (locChildren[i]){
                    var selCmd = locChildren[i]._renderCmd;
                    if(selCmd){
                        selCmd.rendering(wrapper, 1, 1);
                        selCmd._cacheDirty = false;
                    }
                }
            }

            //wrapper.restore();
            this._cacheDirty = false;
        }
    };

    proto.rendering = function (ctx, scaleX, scaleY) {
        var alpha = this._displayedOpacity / 255;
        if (alpha <= 0)
            return;

        var node = this._node;
        this._renderingChildToCache();
        var wrapper = ctx || cc._renderContext, context = wrapper.getContext();
        wrapper.setGlobalAlpha(alpha);

        var locCacheCanvas = this._cacheCanvas;
        //direct draw image by canvas drawImage
        if (locCacheCanvas && locCacheCanvas.width !== 0 && locCacheCanvas.height !== 0) {
            wrapper.setTransform(this._realWorldTransform, scaleX, scaleY);
            var locCanvasHeight = locCacheCanvas.height * scaleY;
            if (node.layerOrientation === cc.TMX_ORIENTATION_HEX) {
                var halfTileSize = node._mapTileSize.height * 0.5 * scaleY;
                context.drawImage(locCacheCanvas, 0, 0, locCacheCanvas.width, locCacheCanvas.height,
                    0, -locCanvasHeight + halfTileSize, locCacheCanvas.width * scaleX, locCanvasHeight);
            } else {
                context.drawImage(locCacheCanvas, 0, 0, locCacheCanvas.width, locCacheCanvas.height,
                    0, -locCanvasHeight, locCacheCanvas.width * scaleX, locCanvasHeight);
            }
        }
        cc.g_NumberOfDraws++;
    };

    proto._updateCacheContext = function(size, height){
        var node = this._node,
            locContentSize = node._contentSize,
            locCanvas = this._cacheCanvas,
            scaleFactor = cc.contentScaleFactor();
        locCanvas.width = 0 | (locContentSize.width * 1.5 * scaleFactor);
        locCanvas.height = 0 | (locContentSize.height * 1.5 * scaleFactor);

        //todo: need change the wrapper's height
        if(node.layerOrientation === cc.TMX_ORIENTATION_HEX)
            this._cacheContext.setOffset(0, -node._mapTileSize.height * 0.5);                  //translate for hexagonal
        else
            this._cacheContext.setOffset(0, 0);
        var locTexContentSize = this._cacheTexture._contentSize;
        locTexContentSize.width = locCanvas.width;
        locTexContentSize.height = locCanvas.height;
    };

    proto.getTexture = function(){
        return this._cacheTexture;
    };

    proto.visit = function(parentCmd){
        var node = this._node;
        //TODO: it will implement dynamic compute child cutting automation.
        var i, len, locChildren = node._children;
        // quick return if not visible
        if (!node._visible || !locChildren || locChildren.length === 0)
            return;

        parentCmd = parentCmd || this.getParentRenderCmd();
        if (parentCmd)
            this._curLevel = parentCmd._curLevel + 1;

        this._syncStatus(parentCmd);
        if (this._cacheDirty) {
            var wrapper = this._cacheContext, locCanvas = this._cacheCanvas, context = wrapper.getContext(),
                instanceID = node.__instanceId, renderer = cc.renderer;
            //begin cache
            renderer._turnToCacheMode(instanceID);

            node.sortAllChildren();
            for (i = 0, len =  locChildren.length; i < len; i++) {
                if (locChildren[i]){
                    var selCmd = locChildren[i]._renderCmd;
                    if(selCmd){
                        selCmd.visit(this);
                        selCmd._cacheDirty = false;
                    }
                }
            }

            //wrapper.save();
            context.setTransform(1, 0, 0, 1, 0, 0);
            context.clearRect(0, 0, locCanvas.width, locCanvas.height);
            //set the wrapper's offset

            //draw to cache canvas
            renderer._renderingToCacheCanvas(wrapper, instanceID);
            //wrapper.restore();                           //todo: it can be reserve.
            this._cacheDirty = false
        }
        cc.renderer.pushRenderCommand(this);
        this._dirtyFlag = 0;
    };

    proto.transform = function (parentCmd, recursive) {
        // transform for canvas
        var t = this.getNodeToParentTransform(),
            worldT = this._realWorldTransform;         //get the world transform

        if (parentCmd) {
            var pt = parentCmd._worldTransform;
            // cc.AffineTransformConcat is incorrect at get world transform
            worldT.a = t.a * pt.a + t.b * pt.c;                               //a
            worldT.b = t.a * pt.b + t.b * pt.d;                               //b
            worldT.c = t.c * pt.a + t.d * pt.c;                               //c
            worldT.d = t.c * pt.b + t.d * pt.d;                               //d

            worldT.tx = pt.a * t.tx + pt.c * t.ty + pt.tx;
            worldT.ty = pt.d * t.ty + pt.ty + pt.b * t.tx;
        } else {
            worldT.a = t.a;
            worldT.b = t.b;
            worldT.c = t.c;
            worldT.d = t.d;
            worldT.tx = t.tx;
            worldT.ty = t.ty;
        }
        if (recursive) {
            var locChildren = this._node._children;
            if (!locChildren || locChildren.length === 0)
                return;
            var i, len;
            for (i = 0, len = locChildren.length; i < len; i++) {
                locChildren[i]._renderCmd.transform(this, recursive);
            }
        }
    };

    proto.initImageSize = function(){
        var node = this._node;
        node.tileset.imageSize = this._originalTexture.getContentSizeInPixels();
    };

    proto._reusedTileWithRect = function(rect){
        var node = this._node;
        node._reusedTile = new cc.Sprite();
        node._reusedTile.initWithTexture(node._renderCmd._texture, rect, false);
        node._reusedTile.batchNode = node;
        node._reusedTile.parent = node;
        node._reusedTile._renderCmd._cachedParent = node._renderCmd;
        return node._reusedTile;
    };
})();