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

/**
 * cc.AtlasNode's rendering objects of Canvas
 */
(function(){
    cc.AtlasNode.CanvasRenderCmd = function(renderableObject){
        cc.Node.CanvasRenderCmd.call(this, renderableObject);
        this._needDraw = false;
        this._colorUnmodified = cc.color.WHITE;
        this._originalTexture = null;
        this._texture = null;
    };

    var proto = cc.AtlasNode.CanvasRenderCmd.prototype = Object.create(cc.Node.CanvasRenderCmd.prototype);
    proto.constructor = cc.AtlasNode.CanvasRenderCmd;

    proto.initWithTexture = function(texture, tileWidth, tileHeight, itemsToRender){
        var node = this._node;
        node._itemWidth = tileWidth;
        node._itemHeight = tileHeight;

        node._opacityModifyRGB = true;
        this._originalTexture = texture;
        if (!this._originalTexture) {
            cc.log(cc._LogInfos.AtlasNode__initWithTexture);
            return false;
        }
        this._texture = this._originalTexture;
        this._calculateMaxItems();

        node.quadsToDraw = itemsToRender;
        return true;
    };

    proto.setColor = function(color3){
        var node = this._node;
        var locRealColor = node._realColor;
        if ((locRealColor.r === color3.r) && (locRealColor.g === color3.g) && (locRealColor.b === color3.b))
            return;
        this._colorUnmodified = color3;
        this._changeTextureColor();
    };

    if(cc.sys._supportCanvasNewBlendModes)
        proto._changeTextureColor = function(){
            var node = this._node;
            var locTexture = node.getTexture();
            if (locTexture && this._originalTexture) {
                var element = this._originalTexture.getHtmlElementObj();
                if(!element)
                    return;
                var locElement = locTexture.getHtmlElementObj();
                var textureRect = cc.rect(0, 0, element.width, element.height);
                if (locElement instanceof HTMLCanvasElement)
                    cc.Sprite.CanvasRenderCmd._generateTintImageWithMultiply(element, this._colorUnmodified, textureRect, locElement);
                else {
                    locElement = cc.Sprite.CanvasRenderCmd._generateTintImageWithMultiply(element, this._colorUnmodified, textureRect);
                    locTexture = new cc.Texture2D();
                    locTexture.initWithElement(locElement);
                    locTexture.handleLoadedTexture();
                    node.setTexture(locTexture);
                }
            }
        };
    else
        proto._changeTextureColor = function(){
            var node = this._node;
            var locElement, locTexture = node.getTexture();
            if (locTexture && this._originalTexture) {
                locElement = locTexture.getHtmlElementObj();
                if (!locElement)
                    return;
                var element = this._originalTexture.getHtmlElementObj();
                var cacheTextureForColor = cc.textureCache.getTextureColors(element);
                if (cacheTextureForColor) {
                    var textureRect = cc.rect(0, 0, element.width, element.height);
                    if (locElement instanceof HTMLCanvasElement)
                        cc.Sprite.CanvasRenderCmd._generateTintImage(locElement, cacheTextureForColor, this._displayedColor, textureRect, locElement);
                    else {
                        locElement = cc.Sprite.CanvasRenderCmd._generateTintImage(locElement, cacheTextureForColor, this._displayedColor, textureRect);
                        locTexture = new cc.Texture2D();
                        locTexture.initWithElement(locElement);
                        locTexture.handleLoadedTexture();
                        node.setTexture(locTexture);
                    }
                }
            }
        };

    proto.setOpacity = function(opacity){
        var node = this._node;
        cc.Node.prototype.setOpacity.call(node, opacity);
        // special opacity for premultiplied textures
        //if (node._opacityModifyRGB) {
        //    node.color = this._colorUnmodified;
        //}
    };

    proto.getTexture = function(){
        return this._texture;
    };

    proto.setTexture = function (texture) {
        this._texture = texture;
    };

    proto._calculateMaxItems = function(){
        var node = this._node;
        var selTexture = this._texture;
        var size = selTexture.getContentSize();

        node._itemsPerColumn = 0 | (size.height / node._itemHeight);
        node._itemsPerRow = 0 | (size.width / node._itemWidth);
    };
})();
