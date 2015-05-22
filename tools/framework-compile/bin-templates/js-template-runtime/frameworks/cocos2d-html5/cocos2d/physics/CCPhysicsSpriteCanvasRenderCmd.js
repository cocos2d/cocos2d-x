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
 * cc.PhysicsSprite's rendering objects of Canvas
 */
(function(){
    cc.PhysicsSprite.CanvasRenderCmd = function(renderableObject){
        cc.Sprite.CanvasRenderCmd.call(this, renderableObject);
        this._needDraw = true;
    };

    var proto = cc.PhysicsSprite.CanvasRenderCmd.prototype = Object.create(cc.Sprite.CanvasRenderCmd.prototype);
    proto.constructor = cc.PhysicsSprite.CanvasRenderCmd;

    proto.rendering = function(ctx, scaleX, scaleY){
        //  This is a special class
        //  Sprite can not obtain sign
        //  So here must to calculate of each frame
        var node  = this._node;
        node._syncPosition();
        if(!node._ignoreBodyRotation)
            node._syncRotation();
        this.transform(this.getParentRenderCmd());

        cc.Sprite.CanvasRenderCmd.prototype.rendering.call(this, ctx, scaleX, scaleY);
    };

    proto.getNodeToParentTransform = function(){
        var node = this._node;

        var t = this._transform;// quick reference
        // base position
        var locBody = node._body, locScaleX = node._scaleX, locScaleY = node._scaleY, locAnchorPIP = this._anchorPointInPoints;
        t.tx = locBody.p.x;
        t.ty = locBody.p.y;

        // rotation Cos and Sin
        var radians = -locBody.a;
        var Cos = 1, Sin = 0;
        if (radians && !node._ignoreBodyRotation) {
            Cos = Math.cos(radians);
            Sin = Math.sin(radians);
        }

        // base abcd
        t.a = t.d = Cos;
        t.b = -Sin;
        t.c = Sin;

        // scale
        if (locScaleX !== 1 || locScaleY !== 1) {
            t.a *= locScaleX;
            t.c *= locScaleX;
            t.b *= locScaleY;
            t.d *= locScaleY;
        }

        // adjust anchorPoint
        t.tx += Cos * -locAnchorPIP.x * locScaleX + -Sin * locAnchorPIP.y * locScaleY;
        t.ty -= Sin * -locAnchorPIP.x * locScaleX + Cos * locAnchorPIP.y * locScaleY;

        // if ignore anchorPoint
        if (this._ignoreAnchorPointForPosition) {
            t.tx += locAnchorPIP.x;
            t.ty += locAnchorPIP.y;
        }

        return this._transform;
    };

})();