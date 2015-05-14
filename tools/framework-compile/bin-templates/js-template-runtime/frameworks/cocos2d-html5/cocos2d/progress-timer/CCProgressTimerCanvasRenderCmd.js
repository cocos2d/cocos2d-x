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
 * cc.ProgressTimer's rendering objects of Canvas
 */
(function(){
    cc.ProgressTimer.CanvasRenderCmd = function(renderableObject){
        cc.Node.CanvasRenderCmd.call(this, renderableObject);
        this._needDraw = true;

        this._PI180 = Math.PI / 180;
        this._barRect = cc.rect(0, 0, 0, 0);
        this._origin = cc.p(0, 0);
        this._radius = 0;
        this._startAngle = 270;
        this._endAngle = 270;
        this._counterClockWise = false;
    };

    var proto = cc.ProgressTimer.CanvasRenderCmd.prototype = Object.create(cc.Node.CanvasRenderCmd.prototype);
    proto.constructor = cc.ProgressTimer.CanvasRenderCmd;

    proto.rendering = function (ctx, scaleX, scaleY) {
        var wrapper = ctx || cc._renderContext,context = wrapper.getContext(), node = this._node, locSprite = node._sprite;
        var locTextureCoord = locSprite._renderCmd._textureCoord, alpha = locSprite._renderCmd._displayedOpacity / 255;

        if (locTextureCoord.width === 0 || locTextureCoord.height === 0)
            return;
        if (!locSprite._texture || !locTextureCoord.validRect || alpha === 0)
            return;

        wrapper.setTransform(this._worldTransform, scaleX, scaleY);
        wrapper.setCompositeOperation(locSprite._blendFuncStr);
        wrapper.setGlobalAlpha(alpha);

        var locRect = locSprite._rect, locOffsetPosition = locSprite._offsetPosition;
        var locX = locOffsetPosition.x,
            locY = -locOffsetPosition.y - locRect.height,
            locWidth = locRect.width,
            locHeight = locRect.height;

        wrapper.save();
        if (locSprite._flippedX) {
            locX = -locX - locWidth;
            context.scale(-1, 1);
        }
        if (locSprite._flippedY) {
            locY = locOffsetPosition.y;
            context.scale(1, -1);
        }

        //clip
        if (node._type === cc.ProgressTimer.TYPE_BAR) {
            var locBarRect = this._barRect;
            context.beginPath();
            context.rect(locBarRect.x * scaleX, locBarRect.y * scaleY, locBarRect.width * scaleX, locBarRect.height * scaleY);
            context.clip();
            context.closePath();
        } else if (node._type === cc.ProgressTimer.TYPE_RADIAL) {
            var locOriginX = this._origin.x * scaleX;
            var locOriginY = this._origin.y * scaleY;
            context.beginPath();
            context.arc(locOriginX, locOriginY, this._radius * scaleY, this._PI180 * this._startAngle, this._PI180 * this._endAngle, this._counterClockWise);
            context.lineTo(locOriginX, locOriginY);
            context.clip();
            context.closePath();
        }

        //draw sprite
        var image = locSprite._texture.getHtmlElementObj();
        if (locSprite._colorized) {
            context.drawImage(image,
                0, 0, locTextureCoord.width, locTextureCoord.height,
                locX * scaleX, locY * scaleY, locWidth * scaleX, locHeight * scaleY);
        } else {
            context.drawImage(image,
                locTextureCoord.renderX, locTextureCoord.renderY, locTextureCoord.width, locTextureCoord.height,
                locX * scaleX, locY * scaleY, locWidth * scaleX, locHeight * scaleY);
        }
        wrapper.restore();
        cc.g_NumberOfDraws++;
    };

    proto.releaseData = function(){};

    proto.initCmd = function(){};

    proto._updateProgress = function(){
        var node = this._node;
        var locSprite = node._sprite;
        var sw = locSprite.width, sh = locSprite.height;
        var locMidPoint = node._midPoint;

        if (node._type === cc.ProgressTimer.TYPE_RADIAL) {
            this._radius = Math.round(Math.sqrt(sw * sw + sh * sh));
            var locStartAngle, locEndAngle, locCounterClockWise = false, locOrigin = this._origin;
            locOrigin.x = sw * locMidPoint.x;
            locOrigin.y = -sh * locMidPoint.y;

            if (node._reverseDirection) {
                locEndAngle = 270;
                locStartAngle = 270 - 3.6 * node._percentage;
            } else {
                locStartAngle = -90;
                locEndAngle = -90 + 3.6 * node._percentage;
            }

            if (locSprite._flippedX) {
                locOrigin.x -= sw * (node._midPoint.x * 2);
                locStartAngle = -locStartAngle;
                locEndAngle = -locEndAngle;
                locStartAngle -= 180;
                locEndAngle -= 180;
                locCounterClockWise = !locCounterClockWise;
            }
            if (locSprite._flippedY) {
                locOrigin.y += sh * (node._midPoint.y * 2);
                locCounterClockWise = !locCounterClockWise;
                locStartAngle = -locStartAngle;
                locEndAngle = -locEndAngle;
            }

            this._startAngle = locStartAngle;
            this._endAngle = locEndAngle;
            this._counterClockWise = locCounterClockWise;
        } else {
            var locBarChangeRate = node._barChangeRate;
            var percentageF = node._percentage / 100;
            var locBarRect = this._barRect;

            var drewSize = cc.size((sw * (1 - locBarChangeRate.x)), (sh * (1 - locBarChangeRate.y)));
            var drawingSize = cc.size((sw - drewSize.width) * percentageF, (sh - drewSize.height) * percentageF);
            var currentDrawSize = cc.size(drewSize.width + drawingSize.width, drewSize.height + drawingSize.height);

            var startPoint = cc.p(sw * locMidPoint.x, sh * locMidPoint.y);

            var needToLeft = startPoint.x - currentDrawSize.width / 2;
            if ((locMidPoint.x > 0.5) && (currentDrawSize.width / 2 >= sw - startPoint.x))
                needToLeft = sw - currentDrawSize.width;

            var needToTop = startPoint.y - currentDrawSize.height / 2;
            if ((locMidPoint.y > 0.5) && (currentDrawSize.height / 2 >= sh - startPoint.y))
                needToTop = sh - currentDrawSize.height;

            //left pos
            locBarRect.x = 0;
            var flipXNeed = 1;
            if (locSprite._flippedX) {
                locBarRect.x -= currentDrawSize.width;
                flipXNeed = -1;
            }

            if (needToLeft > 0)
                locBarRect.x += needToLeft * flipXNeed;

            //right pos
            locBarRect.y = 0;
            var flipYNeed = 1;
            if (locSprite._flippedY) {
                locBarRect.y += currentDrawSize.height;
                flipYNeed = -1;
            }

            if (needToTop > 0)
                locBarRect.y -= needToTop * flipYNeed;

            //clip width and clip height
            locBarRect.width = currentDrawSize.width;
            locBarRect.height = -currentDrawSize.height;
        }
    };

    proto._updateColor = function(){};

    proto._syncStatus = function (parentCmd) {
        var node = this._node;
        if(!node._sprite)
            return;
        var flags = cc.Node._dirtyFlags, locFlag = this._dirtyFlag;
        var parentNode = parentCmd ? parentCmd._node : null;

        if(parentNode && parentNode._cascadeColorEnabled && (parentCmd._dirtyFlag & flags.colorDirty))
            locFlag |= flags.colorDirty;

        if(parentNode && parentNode._cascadeOpacityEnabled && (parentCmd._dirtyFlag & flags.opacityDirty))
            locFlag |= flags.opacityDirty;

        if(parentCmd && (parentCmd._dirtyFlag & flags.transformDirty))
            locFlag |= flags.transformDirty;

        this._dirtyFlag = locFlag;

        var spriteCmd = node._sprite._renderCmd;
        var spriteFlag = spriteCmd._dirtyFlag;

        var colorDirty = spriteFlag & flags.colorDirty,
            opacityDirty = spriteFlag & flags.opacityDirty;

        if (colorDirty){
            spriteCmd._syncDisplayColor();
        }

        if (opacityDirty){
            spriteCmd._syncDisplayOpacity();
        }

/*        if(colorDirty || opacityDirty){
            spriteCmd._updateColor();
            this._updateColor();
        }*/

        if (locFlag & flags.transformDirty) {
            //update the transform
            this.transform(parentCmd);
        }
    };

    proto.updateStatus = function () {
        var node = this._node;
        if(!node._sprite)
            return;
        var flags = cc.Node._dirtyFlags, locFlag = this._dirtyFlag;
        var spriteCmd = node._sprite._renderCmd;
        var spriteFlag = spriteCmd._dirtyFlag;

        var colorDirty = spriteFlag & flags.colorDirty,
            opacityDirty = spriteFlag & flags.opacityDirty;

        if(colorDirty){
            spriteCmd._updateDisplayColor();
        }

        if(opacityDirty){
            spriteCmd._updateDisplayOpacity();
        }

/*        if(colorDirty || opacityDirty){
            spriteCmd._updateColor();
            this._updateColor();
        }*/

        if(locFlag & flags.transformDirty){
            //update the transform
            this.transform(this.getParentRenderCmd(), true);
        }
        this._dirtyFlag = 0;
    };
})();