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
    cc.Sprite.CanvasRenderCmd = function (renderable) {
        cc.Node.CanvasRenderCmd.call(this, renderable);
        this._needDraw = true;
        this._textureCoord = {
            renderX: 0,                             //the x of texture coordinate for render, when texture tinted, its value doesn't equal x.
            renderY: 0,                             //the y of texture coordinate for render, when texture tinted, its value doesn't equal y.
            x: 0,                                   //the x of texture coordinate for node.
            y: 0,                                   //the y of texture coordinate for node.
            width: 0,
            height: 0,
            validRect: false
        };
        this._blendFuncStr = "source-over";
        this._colorized = false;

        this._originalTexture = null;
    };

    var proto = cc.Sprite.CanvasRenderCmd.prototype = Object.create(cc.Node.CanvasRenderCmd.prototype);
    proto.constructor = cc.Sprite.CanvasRenderCmd;

    proto._init = function () {};

    proto.setDirtyRecursively = function (value) {};

    proto._resetForBatchNode = function () {};

    proto._setTexture = function (texture) {
        var node = this._node;
        if (node._texture !== texture) {
            if (texture) {
                if(texture.getHtmlElementObj() instanceof  HTMLImageElement)
                    this._originalTexture = texture;
                node._textureLoaded = texture._textureLoaded;
            }else{
                node._textureLoaded = false;
            }
            node._texture = texture;
        }
    };

    proto._setColorDirty = function () {
        this.setDirtyFlag(cc.Node._dirtyFlags.colorDirty | cc.Node._dirtyFlags.opacityDirty);
    };

    proto.isFrameDisplayed = function (frame) {      //TODO there maybe has a bug
        var node = this._node;
        if (frame.getTexture() !== node._texture)
            return false;
        return cc.rectEqualToRect(frame.getRect(), node._rect);
    };

    proto.updateBlendFunc = function (blendFunc) {
        this._blendFuncStr = cc.Node.CanvasRenderCmd._getCompositeOperationByBlendFunc(blendFunc);
    };

    proto._setBatchNodeForAddChild = function (child) {
        return true;
    };

    proto._handleTextureForRotatedTexture = function (texture, rect, rotated, counterclockwise) {
        if (rotated && texture.isLoaded()) {
            var tempElement = texture.getHtmlElementObj();
            tempElement = cc.Sprite.CanvasRenderCmd._cutRotateImageToCanvas(tempElement, rect, counterclockwise);
            var tempTexture = new cc.Texture2D();
            tempTexture.initWithElement(tempElement);
            tempTexture.handleLoadedTexture();
            texture = tempTexture;
            rect.x = rect.y = 0;
            this._node._rect = cc.rect(0, 0, rect.width, rect.height);
        }
        return texture;
    };

    proto._checkTextureBoundary = function (texture, rect, rotated) {
        if (texture && texture.url) {
            var _x = rect.x + rect.width, _y = rect.y + rect.height;
            if (_x > texture.width)
                cc.error(cc._LogInfos.RectWidth, texture.url);
            if (_y > texture.height)
                cc.error(cc._LogInfos.RectHeight, texture.url);
        }
        this._node._originalTexture = texture;
    };

    proto.rendering = function (ctx, scaleX, scaleY) {
        var node = this._node;
        var locTextureCoord = this._textureCoord, alpha = (this._displayedOpacity / 255);
        if ((node._texture && ((locTextureCoord.width === 0 || locTextureCoord.height === 0)            //set texture but the texture isn't loaded.
            || !node._texture._textureLoaded)) || alpha === 0)
            return;

        var wrapper = ctx || cc._renderContext, context = wrapper.getContext();
        var locX = node._offsetPosition.x, locHeight = node._rect.height, locWidth = node._rect.width,
            locY = -node._offsetPosition.y - locHeight, image;

        wrapper.setTransform(this._worldTransform, scaleX, scaleY);
        wrapper.setCompositeOperation(this._blendFuncStr);
        wrapper.setGlobalAlpha(alpha);

        if(node._flippedX || node._flippedY)
            wrapper.save();
        if (node._flippedX) {
            locX = -locX - locWidth;
            context.scale(-1, 1);
        }
        if (node._flippedY) {
            locY = node._offsetPosition.y;
            context.scale(1, -1);
        }

        if (node._texture) {
            image = node._texture._htmlElementObj;
            if (node._texture._pattern !== "") {
                wrapper.setFillStyle(context.createPattern(image, node._texture._pattern));
                context.fillRect(locX * scaleX, locY * scaleY, locWidth * scaleX, locHeight * scaleY);
            } else {
                if (this._colorized) {
                    context.drawImage(image,
                        0, 0, locTextureCoord.width,locTextureCoord.height,
                        locX * scaleX,locY * scaleY, locWidth * scaleX, locHeight * scaleY);
                } else {
                    context.drawImage(image,
                        locTextureCoord.renderX, locTextureCoord.renderY, locTextureCoord.width, locTextureCoord.height,
                        locX * scaleX, locY * scaleY, locWidth * scaleX, locHeight * scaleY);
                }
            }
        } else {
            var contentSize = node._contentSize;
            if (locTextureCoord.validRect) {
                var curColor = this._displayedColor;
                wrapper.setFillStyle("rgba(" + curColor.r + "," + curColor.g + "," + curColor.b + ",1)");
                context.fillRect(locX * scaleX, locY * scaleY, contentSize.width * scaleX, contentSize.height * scaleY);
            }
        }
        if(node._flippedX || node._flippedY)
            wrapper.restore();
        cc.g_NumberOfDraws++;
    };

    if(!cc.sys._supportCanvasNewBlendModes){
        proto._updateColor = function () {
            var node = this._node, displayedColor = this._displayedColor;

            if (displayedColor.r === 255 && displayedColor.g === 255 && displayedColor.b === 255){
                if(this._colorized){
                    this._colorized = false;
                    node.texture = this._originalTexture;
                }
                return;
            }

            var locElement, locTexture = node._texture, locRect = this._textureCoord;
            if (locTexture && locRect.validRect && this._originalTexture) {
                locElement = locTexture.getHtmlElementObj();
                if (!locElement)
                    return;

                var cacheTextureForColor = cc.textureCache.getTextureColors(this._originalTexture.getHtmlElementObj());
                if (cacheTextureForColor) {
                    this._colorized = true;
                    //generate color texture cache
                    if (locElement instanceof HTMLCanvasElement && !this._rectRotated && !this._newTextureWhenChangeColor)
                        cc.Sprite.CanvasRenderCmd._generateTintImage(locElement, cacheTextureForColor, displayedColor, locRect, locElement);
                    else {
                        locElement = cc.Sprite.CanvasRenderCmd._generateTintImage(locElement, cacheTextureForColor, displayedColor, locRect);
                        locTexture = new cc.Texture2D();
                        locTexture.initWithElement(locElement);
                        locTexture.handleLoadedTexture();
                        node.texture = locTexture;
                    }
                }
            }
        };
    } else {
        proto._updateColor = function () {
            var node = this._node, displayedColor = this._displayedColor;
            if (displayedColor.r === 255 && displayedColor.g === 255 && displayedColor.b === 255) {
                if (this._colorized) {
                    this._colorized = false;
                    node.texture = this._originalTexture;
                }
                return;
            }

            var locElement, locTexture = node._texture, locRect = this._textureCoord;
            if (locTexture && locRect.validRect && this._originalTexture) {
                locElement = locTexture.getHtmlElementObj();
                if (!locElement)
                    return;

                this._colorized = true;
                if (locElement instanceof HTMLCanvasElement && !this._rectRotated && !this._newTextureWhenChangeColor
                    && this._originalTexture._htmlElementObj !== locElement)
                    cc.Sprite.CanvasRenderCmd._generateTintImageWithMultiply(this._originalTexture._htmlElementObj, displayedColor, locRect, locElement);
                else {
                    locElement = cc.Sprite.CanvasRenderCmd._generateTintImageWithMultiply(this._originalTexture._htmlElementObj, displayedColor, locRect);
                    locTexture = new cc.Texture2D();
                    locTexture.initWithElement(locElement);
                    locTexture.handleLoadedTexture();
                    node.texture = locTexture;
                }
            }
        };
    }

    proto.getQuad = function () {
        //throw an error. it doesn't support this function.
        return null;
    };

    proto._updateForSetSpriteFrame = function (pNewTexture, textureLoaded) {
        var node = this._node;
        if (node._rectRotated)
            node._originalTexture = pNewTexture;      //TODO
        this._colorized = false;
        this._textureCoord.renderX = this._textureCoord.x;
        this._textureCoord.renderY = this._textureCoord.y;
        if (textureLoaded) {
            var curColor = node.getColor();
            if (curColor.r !== 255 || curColor.g !== 255 || curColor.b !== 255)
                this._updateColor();
        }
    };

    proto.updateTransform = function () {      //TODO need delete, because Canvas needn't
        var _t = this, node = this._node;

        // re-calculate matrix only if it is dirty
        if (node.dirty) {
            // If it is not visible, or one of its ancestors is not visible, then do nothing:
            var locParent = node._parent;
            if (!node._visible || ( locParent && locParent !== node._batchNode && locParent._shouldBeHidden)) {
                node._shouldBeHidden = true;
            } else {
                node._shouldBeHidden = false;

                if (!locParent || locParent === node._batchNode) {
                    node._transformToBatch = _t.getNodeToParentTransform();
                } else {
                    //cc.assert(_t._parent instanceof cc.Sprite, "Logic error in CCSprite. Parent must be a CCSprite");
                    node._transformToBatch = cc.affineTransformConcat(_t.getNodeToParentTransform(), locParent._transformToBatch);
                }
            }
            node._recursiveDirty = false;
            node.dirty = false;
        }

        // recursively iterate over children
        if (node._hasChildren)
            node._arrayMakeObjectsPerformSelector(node._children, cc.Node._stateCallbackType.updateTransform);
    };

    proto._updateDisplayColor = function (parentColor) {
        cc.Node.CanvasRenderCmd.prototype._updateDisplayColor.call(this, parentColor);
        //this._updateColor();
    };

    proto._spriteFrameLoadedCallback = function (spriteFrame) {
        var node = this;
        node.setTextureRect(spriteFrame.getRect(), spriteFrame.isRotated(), spriteFrame.getOriginalSize());

        node._renderCmd._updateColor();
        node.dispatchEvent("load");
    };

    proto._textureLoadedCallback = function (sender) {
        var node = this;
        if (node._textureLoaded)
            return;

        node._textureLoaded = true;
        var locRect = node._rect, locRenderCmd = this._renderCmd;
        if (!locRect) {
            locRect = cc.rect(0, 0, sender.width, sender.height);
        } else if (cc._rectEqualToZero(locRect)) {
            locRect.width = sender.width;
            locRect.height = sender.height;
        }
        locRenderCmd._originalTexture = sender;

        node.texture = sender;
        node.setTextureRect(locRect, node._rectRotated);

        //set the texture's color after the it loaded
        var locColor = locRenderCmd._displayedColor;
        if (locColor.r !== 255 || locColor.g !== 255 || locColor.b !== 255)
            locRenderCmd._updateColor();

        // by default use "Self Render".
        // if the sprite is added to a batchnode, then it will automatically switch to "batchnode Render"
        node.setBatchNode(node._batchNode);
        node.dispatchEvent("load");
    };

    proto._setTextureCoords = function (rect, needConvert) {
        if (needConvert === undefined)
            needConvert = true;
        var locTextureRect = this._textureCoord,
            scaleFactor = needConvert ? cc.contentScaleFactor() : 1;
        locTextureRect.renderX = locTextureRect.x = 0 | (rect.x * scaleFactor);
        locTextureRect.renderY = locTextureRect.y = 0 | (rect.y * scaleFactor);
        locTextureRect.width = 0 | (rect.width * scaleFactor);
        locTextureRect.height = 0 | (rect.height * scaleFactor);
        locTextureRect.validRect = !(locTextureRect.width === 0 || locTextureRect.height === 0 || locTextureRect.x < 0 || locTextureRect.y < 0);

        if(this._colorized){
            this._node._texture = this._originalTexture;
            this._colorized = false;
        }
    };

    //TODO need refactor these functions
    //utils for tint
    // Tint a texture using the "multiply" operation
    cc.Sprite.CanvasRenderCmd._generateTintImageWithMultiply = function (image, color, rect, renderCanvas) {
        renderCanvas = renderCanvas || cc.newElement("canvas");
        rect = rect || cc.rect(0, 0, image.width, image.height);
        var context = renderCanvas.getContext("2d");
        if (renderCanvas.width !== rect.width || renderCanvas.height !== rect.height) {
            renderCanvas.width = rect.width;
            renderCanvas.height = rect.height;
        } else {
            context.globalCompositeOperation = "source-over";
        }

        context.fillStyle = "rgb(" + (0 | color.r) + "," + (0 | color.g) + "," + (0 | color.b) + ")";
        context.fillRect(0, 0, rect.width, rect.height);
        context.globalCompositeOperation = "multiply";
        context.drawImage(image,
            rect.x,
            rect.y,
            rect.width,
            rect.height,
            0,
            0,
            rect.width,
            rect.height);
        context.globalCompositeOperation = "destination-atop";
        context.drawImage(image,
            rect.x,
            rect.y,
            rect.width,
            rect.height,
            0,
            0,
            rect.width,
            rect.height);
        return renderCanvas;
    };

    //Generate tinted texture with lighter.
    cc.Sprite.CanvasRenderCmd._generateTintImage = function (texture, tintedImgCache, color, rect, renderCanvas) {
        if (!rect)
            rect = cc.rect(0, 0, texture.width, texture.height);

        var r = color.r / 255, g = color.g / 255, b = color.b / 255;
        var w = Math.min(rect.width, tintedImgCache[0].width);
        var h = Math.min(rect.height, tintedImgCache[0].height);
        var buff = renderCanvas, ctx;
        // Create a new buffer if required
        if (!buff) {
            buff = cc.newElement("canvas");
            buff.width = w;
            buff.height = h;
            ctx = buff.getContext("2d");
        } else {
            ctx = buff.getContext("2d");
            ctx.clearRect(0, 0, w, h);
        }
        ctx.save();
        ctx.globalCompositeOperation = 'lighter';
        // Make sure to keep the renderCanvas alpha in mind in case of overdraw
        var a = ctx.globalAlpha;
        if (r > 0) {
            ctx.globalAlpha = r * a;
            ctx.drawImage(tintedImgCache[0], rect.x, rect.y, w, h, 0, 0, w, h);
        }
        if (g > 0) {
            ctx.globalAlpha = g * a;
            ctx.drawImage(tintedImgCache[1], rect.x, rect.y, w, h, 0, 0, w, h);
        }
        if (b > 0) {
            ctx.globalAlpha = b * a;
            ctx.drawImage(tintedImgCache[2], rect.x, rect.y, w, h, 0, 0, w, h);
        }
        if (r + g + b < 1) {
            ctx.globalAlpha = a;
            ctx.drawImage(tintedImgCache[3], rect.x, rect.y, w, h, 0, 0, w, h);
        }
        ctx.restore();
        return buff;
    };

    cc.Sprite.CanvasRenderCmd._generateTextureCacheForColor = function (texture) {
        if (texture.channelCache) {
            return texture.channelCache;
        }

        var textureCache = [
            cc.newElement("canvas"),
            cc.newElement("canvas"),
            cc.newElement("canvas"),
            cc.newElement("canvas")
        ];

        function renderToCache() {
            var ref = cc.Sprite.CanvasRenderCmd._generateTextureCacheForColor;

            var w = texture.width;
            var h = texture.height;

            textureCache[0].width = w;
            textureCache[0].height = h;
            textureCache[1].width = w;
            textureCache[1].height = h;
            textureCache[2].width = w;
            textureCache[2].height = h;
            textureCache[3].width = w;
            textureCache[3].height = h;

            ref.canvas.width = w;
            ref.canvas.height = h;

            var ctx = ref.canvas.getContext("2d");
            ctx.drawImage(texture, 0, 0);

            ref.tempCanvas.width = w;
            ref.tempCanvas.height = h;

            var pixels = ctx.getImageData(0, 0, w, h).data;

            for (var rgbI = 0; rgbI < 4; rgbI++) {
                var cacheCtx = textureCache[rgbI].getContext('2d');
                cacheCtx.getImageData(0, 0, w, h).data;
                ref.tempCtx.drawImage(texture, 0, 0);

                var to = ref.tempCtx.getImageData(0, 0, w, h);
                var toData = to.data;

                for (var i = 0; i < pixels.length; i += 4) {
                    toData[i  ] = (rgbI === 0) ? pixels[i  ] : 0;
                    toData[i + 1] = (rgbI === 1) ? pixels[i + 1] : 0;
                    toData[i + 2] = (rgbI === 2) ? pixels[i + 2] : 0;
                    toData[i + 3] = pixels[i + 3];
                }
                cacheCtx.putImageData(to, 0, 0);
            }
            texture.onload = null;
        }

        try {
            renderToCache();
        } catch (e) {
            texture.onload = renderToCache;
        }

        texture.channelCache = textureCache;
        return textureCache;
    };

    cc.Sprite.CanvasRenderCmd._generateTextureCacheForColor.canvas = cc.newElement('canvas');
    cc.Sprite.CanvasRenderCmd._generateTextureCacheForColor.tempCanvas = cc.newElement('canvas');
    cc.Sprite.CanvasRenderCmd._generateTextureCacheForColor.tempCtx = cc.Sprite.CanvasRenderCmd._generateTextureCacheForColor.tempCanvas.getContext('2d');

    cc.Sprite.CanvasRenderCmd._cutRotateImageToCanvas = function (texture, rect, counterclockwise) {
        if (!texture)
            return null;

        if (!rect)
            return texture;

        counterclockwise = counterclockwise == null? true: counterclockwise;   // texture package is counterclockwise, spine is clockwise

        var nCanvas = cc.newElement("canvas");
        nCanvas.width = rect.width;
        nCanvas.height = rect.height;
        var ctx = nCanvas.getContext("2d");
        ctx.translate(nCanvas.width / 2, nCanvas.height / 2);
        if(counterclockwise)
            ctx.rotate(-1.5707963267948966);
        else
            ctx.rotate(1.5707963267948966);
        ctx.drawImage(texture, rect.x, rect.y, rect.height, rect.width, -rect.height / 2, -rect.width / 2, rect.height, rect.width);
        return nCanvas;
    };
})();
