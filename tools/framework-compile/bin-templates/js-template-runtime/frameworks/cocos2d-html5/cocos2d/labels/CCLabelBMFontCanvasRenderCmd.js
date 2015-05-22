/****************************************************************************
 Copyright (c) 2008-2010 Ricardo Quesada
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

 Use any of these editors to generate BMFonts:
 http://glyphdesigner.71squared.com/ (Commercial, Mac OS X)
 http://www.n4te.com/hiero/hiero.jnlp (Free, Java)
 http://slick.cokeandcode.com/demos/hiero.jnlp (Free, Java)
 http://www.angelcode.com/products/bmfont/ (Free, Windows only)
 ****************************************************************************/

(function(){
    cc.LabelBMFont.CanvasRenderCmd = function(renderableObject){
        cc.SpriteBatchNode.CanvasRenderCmd.call(this, renderableObject);
        this._needDraw = true;
    };

    var proto = cc.LabelBMFont.CanvasRenderCmd.prototype = Object.create(cc.SpriteBatchNode.CanvasRenderCmd.prototype);
    proto.constructor = cc.LabelBMFont.CanvasRenderCmd;

    proto.rendering = function(){
        void 0;
    };

    proto._updateCharTexture = function(fontChar, rect, key){
        if (key === 32) {
            fontChar.setTextureRect(rect, false, cc.size(0, 0));
        } else {
            // updating previous sprite
            fontChar.setTextureRect(rect, false);
            // restore to default in case they were modified
            fontChar.visible = true;
        }
    };

    proto._updateCharColorAndOpacity = function(fontChar){
        // Color MUST be set before opacity, since opacity might change color if OpacityModifyRGB is on
        fontChar._displayedColor = this._displayedColor;
        fontChar._renderCmd.setDirtyFlag(cc.Node._dirtyFlags.colorDirty);
        fontChar._displayedOpacity = this._displayedOpacity;
        fontChar._renderCmd.setDirtyFlag(cc.Node._dirtyFlags.opacityDirty);
    };

    proto._updateFntFileTexture = function(){
        var node = this._node;
        node._originalTexture = node.texture;
    };

    proto.setTexture = function (texture) {
        var node = this._node;
        var locChildren = node._children;
        var locDisplayedColor = this._displayedColor;
        for (var i = 0; i < locChildren.length; i++) {
            var selChild = locChildren[i];
            var cm = selChild._renderCmd;
            var childDColor = cm._displayedColor;
            if (this._texture !== cm._texture && (childDColor.r !== locDisplayedColor.r ||
                childDColor.g !== locDisplayedColor.g || childDColor.b !== locDisplayedColor.b))
                continue;
            selChild.texture = texture;
        }
        this._texture = texture;
    };

    if(cc.sys._supportCanvasNewBlendModes)
        proto._changeTextureColor = function(){
            var node = this._node;
            var locTexture = node.getTexture();
            if (locTexture && locTexture.getContentSize().width>0) {
                var element = this._originalTexture.getHtmlElementObj();
                if(!element)
                    return;
                var locElement = locTexture.getHtmlElementObj();
                var textureRect = cc.rect(0, 0, element.width, element.height);
                if (locElement instanceof HTMLCanvasElement && !node._rectRotated){
                    cc.Sprite.CanvasRenderCmd._generateTintImageWithMultiply(element, this._displayedColor, textureRect, locElement);
                    node.setTexture(locTexture);
                } else {
                    locElement = cc.Sprite.CanvasRenderCmd._generateTintImageWithMultiply(element, this._displayedColor, textureRect);
                    locTexture = new cc.Texture2D();
                    locTexture.initWithElement(locElement);
                    locTexture.handleLoadedTexture();
                    node.setTexture(locTexture);
                }
            }
        };
    else
        proto._changeTextureColor = function () {
            var node = this._node;
            var locElement, locTexture = node.getTexture();
            if (locTexture && locTexture.getContentSize().width > 0) {
                locElement = locTexture.getHtmlElementObj();
                if (!locElement)
                    return;
                var cacheTextureForColor = cc.textureCache.getTextureColors(this._originalTexture.getHtmlElementObj());
                if (cacheTextureForColor) {
                    if (locElement instanceof HTMLCanvasElement && !this._rectRotated) {
                        cc.Sprite.CanvasRenderCmd._generateTintImage(locElement, cacheTextureForColor, this._displayedColor, null, locElement);
                        this.setTexture(locTexture);
                    } else {
                        locElement = cc.Sprite.CanvasRenderCmd._generateTintImage(locElement, cacheTextureForColor, this._displayedColor);
                        locTexture = new cc.Texture2D();
                        locTexture.initWithElement(locElement);
                        locTexture.handleLoadedTexture();
                        node.setTexture(locTexture);
                    }
                }
            }
        };

    proto._updateChildrenDisplayedOpacity = function(locChild){
        cc.Node.prototype.updateDisplayedOpacity.call(locChild, this._displayedOpacity);
    };

    proto._updateChildrenDisplayedColor = function(locChild){
        cc.Node.prototype.updateDisplayedColor.call(locChild, this._displayedColor);
    };

    proto._initBatchTexture = function(){};

})();