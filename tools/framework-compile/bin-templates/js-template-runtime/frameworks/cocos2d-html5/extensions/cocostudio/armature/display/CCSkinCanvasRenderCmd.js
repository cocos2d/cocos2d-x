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
    ccs.Skin.RenderCmd = {
        updateArmatureTransform: function () {
            var node = this._node;
            this._transform = cc.affineTransformConcat(
                node._skinTransform,
                node.bone.getNodeToArmatureTransform()
            );
            this._dirtyFlag = this._dirtyFlag & cc.Node._dirtyFlags.transformDirty ^ this._dirtyFlag;
        },

        getNodeToWorldTransform: function () {
            return cc.affineTransformConcat(this._transform, this._node.bone.getArmature().getNodeToWorldTransform());
        },

        getNodeToWorldTransformAR: function () {
            var displayTransform = this._transform, node = this._node;
            this._anchorPointInPoints = cc.pointApplyAffineTransform(this._anchorPointInPoints, displayTransform);
            displayTransform.tx = this._anchorPointInPoints.x;
            displayTransform.ty = this._anchorPointInPoints.y;
            return cc.affineTransformConcat(displayTransform, node.bone.getArmature().getNodeToWorldTransform());
        }
    };

    ccs.Skin.CanvasRenderCmd = function(renderable){
        cc.Sprite.CanvasRenderCmd.call(this, renderable);
        this._needDraw = true;
    };

    var proto = ccs.Skin.CanvasRenderCmd.prototype = Object.create(cc.Sprite.CanvasRenderCmd.prototype);
    cc.inject(ccs.Skin.RenderCmd, proto);
    proto.constructor = ccs.Skin.CanvasRenderCmd;
})();
