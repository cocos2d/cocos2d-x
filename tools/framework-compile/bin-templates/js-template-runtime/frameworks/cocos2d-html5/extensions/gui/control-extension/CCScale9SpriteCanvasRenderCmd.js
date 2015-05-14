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

(function() {
    cc.Scale9Sprite.CanvasRenderCmd = function (renderable) {
        cc.Node.CanvasRenderCmd.call(this, renderable);
        this._cachedParent = null;
        this._cacheDirty = false;
        this._state = cc.Scale9Sprite.state.NORMAL;

        var node = this._node;
        var locCacheCanvas = this._cacheCanvas = cc.newElement('canvas');
        locCacheCanvas.width = 1;
        locCacheCanvas.height = 1;
        this._cacheContext = new cc.CanvasContextWrapper(locCacheCanvas.getContext("2d"));
        var locTexture = this._cacheTexture = new cc.Texture2D();
        locTexture.initWithElement(locCacheCanvas);
        locTexture.handleLoadedTexture();
        this._cacheSprite = new cc.Sprite(locTexture);
        this._cacheSprite.setAnchorPoint(0,0);
        node.addChild(this._cacheSprite);
    };

    var proto = cc.Scale9Sprite.CanvasRenderCmd.prototype = Object.create(cc.Node.CanvasRenderCmd.prototype);
    proto.constructor = cc.Scale9Sprite.CanvasRenderCmd;

    proto.visit = function(parentCmd){
        var node = this._node;
        if(!node._visible)
            return;

        if (node._positionsAreDirty) {
            node._updatePositions();
            node._positionsAreDirty = false;
            node._scale9Dirty = true;
        }
        node._scale9Dirty = false;
        this._cacheScale9Sprite();

        cc.Node.CanvasRenderCmd.prototype.visit.call(this, parentCmd);
    };

    proto.transform = function(parentCmd){
        var node = this._node;
        cc.Node.CanvasRenderCmd.prototype.transform.call(this, parentCmd);
        if (node._positionsAreDirty) {
            node._updatePositions();
            node._positionsAreDirty = false;
            node._scale9Dirty = true;
        }
        this._cacheScale9Sprite();

        var children = node._children;
        for(var i=0; i<children.length; i++){
            children[i].transform(this);
        }
    };

    proto._updateDisplayColor = function(parentColor){
        cc.Node.CanvasRenderCmd.prototype._updateDisplayColor.call(this, parentColor);

        var scale9Image = this._node._scale9Image;
        if(scale9Image){
            var scaleChildren = scale9Image.getChildren();
            for (var i = 0; i < scaleChildren.length; i++) {
                var selChild = scaleChildren[i];
                if (selChild){
                    selChild._renderCmd._updateDisplayColor(parentColor);
                    selChild._renderCmd._updateColor();
                }
            }
            this._cacheScale9Sprite();
        }

    };

    proto._cacheScale9Sprite = function(){
        var node = this._node;
        if(!node._scale9Image)
            return;

        var locScaleFactor = cc.contentScaleFactor();
        var size = node._contentSize;
        var sizeInPixels = cc.size(size.width * locScaleFactor, size.height * locScaleFactor);

        var locCanvas = this._cacheCanvas, wrapper = this._cacheContext, locContext = wrapper.getContext();

        var contentSizeChanged = false;
        if(locCanvas.width !== sizeInPixels.width || locCanvas.height !== sizeInPixels.height){
            locCanvas.width = sizeInPixels.width;
            locCanvas.height = sizeInPixels.height;
            contentSizeChanged = true;
        }

        //begin cache
        cc.renderer._turnToCacheMode(node.__instanceId);
        node._scale9Image.visit();

        //draw to cache canvas
        var selTexture = node._scale9Image.getTexture();
        if(selTexture && this._state === cc.Scale9Sprite.state.GRAY)
            selTexture._switchToGray(true);
        locContext.setTransform(1, 0, 0, 1, 0, 0);
        locContext.clearRect(0, 0, sizeInPixels.width, sizeInPixels.height);
        cc.renderer._renderingToCacheCanvas(wrapper, node.__instanceId, locScaleFactor, locScaleFactor);
        if(selTexture && this._state === cc.Scale9Sprite.state.GRAY)
            selTexture._switchToGray(false);

        if(contentSizeChanged)
            this._cacheSprite.setTextureRect(cc.rect(0,0, size.width, size.height));

        if(!this._cacheSprite.getParent())
            node.addChild(this._cacheSprite, -1);
    };

    proto.setState = function(state){
        var locScale9Image = this._node._scale9Image;
        if(!locScale9Image)
            return;
        this._state = state;
        this._cacheScale9Sprite();
    };
})();