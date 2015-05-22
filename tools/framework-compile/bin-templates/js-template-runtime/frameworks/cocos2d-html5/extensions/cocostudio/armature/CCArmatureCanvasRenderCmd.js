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
    ccs.Armature.RenderCmd = {
        _updateAnchorPointInPoint: function(){
            var node = this._node;
            var contentSize = node._contentSize, anchorPoint = node._anchorPoint, offsetPoint = node._offsetPoint;
            this._anchorPointInPoints.x = contentSize.width * anchorPoint.x - offsetPoint.x;
            this._anchorPointInPoints.y = contentSize.height * anchorPoint.y - offsetPoint.y;

            this._realAnchorPointInPoints.x = contentSize.width * anchorPoint.x;
            this._realAnchorPointInPoints.y = contentSize.height * anchorPoint.y;
            this.setDirtyFlag(cc.Node._dirtyFlags.transformDirty);
        },

        getAnchorPointInPoints: function(){
            return cc.p(this._realAnchorPointInPoints);
        }
    };
})();

(function(){
    ccs.Armature.CanvasRenderCmd = function(renderableObject){
        cc.Node.CanvasRenderCmd.call(this, renderableObject);
        this._needDraw = true;

        this._realAnchorPointInPoints = new cc.Point(0,0);
        this._startRenderCmd = new cc.CustomRenderCmd(this, this._startCmdCallback);
        this._RestoreRenderCmd = new cc.CustomRenderCmd(this, this._RestoreCmdCallback);
    };

    var proto = ccs.Armature.CanvasRenderCmd.prototype = Object.create(cc.Node.CanvasRenderCmd.prototype);
    cc.inject(ccs.Armature.RenderCmd, proto);
    proto.constructor = ccs.Armature.CanvasRenderCmd;

    proto._startCmdCallback = function(ctx, scaleX, scaleY){
        var node = this._node, parent = node._parent;
        this.transform(parent ? parent._renderCmd : null);

        var wrapper = ctx || cc._renderContext;
        wrapper.save();

        //set to armature mode
        wrapper._switchToArmatureMode(true, this._worldTransform, scaleX, scaleY);
    };

    proto.transform = function(parentCmd, recursive){
        ccs.Node.CanvasRenderCmd.prototype.transform.call(this, parentCmd, recursive);

        var locChildren = this._node._children;
        for (var i = 0, len = locChildren.length; i< len; i++) {
            var selBone = locChildren[i];
            if (selBone && selBone.getDisplayRenderNode) {
                var selNode = selBone.getDisplayRenderNode();
                if (selNode && selNode._renderCmd){
                    var cmd = selNode._renderCmd;
                    cmd.transform(null);   //must be null, use transform in armature mode

                    //update displayNode's color and opacity, because skin didn't call visit()
                    var parentColor = selBone._renderCmd._displayedColor, parentOpacity = selBone._renderCmd._displayedOpacity;
                    var flags = cc.Node._dirtyFlags, locFlag = cmd._dirtyFlag;
                    var colorDirty = locFlag & flags.colorDirty,
                        opacityDirty = locFlag & flags.opacityDirty;
                    if(colorDirty)
                        cmd._updateDisplayColor(parentColor);
                    if(opacityDirty)
                        cmd._updateDisplayOpacity(parentOpacity);
                }
            }
        }
    };

    proto._RestoreCmdCallback = function(wrapper){
        this._cacheDirty = false;
        //wrapper.restore();
        wrapper._switchToArmatureMode(false);
        wrapper.restore();
    };

    proto.initShaderCache = function(){};
    proto.setShaderProgram = function(){};
    proto.updateChildPosition = function(ctx, dis){
        //dis.visit(ctx);
        cc.renderer.pushRenderCommand(dis._renderCmd);
    };

    proto.rendering = function(ctx, scaleX, scaleY){
        var node = this._node;
        var locChildren = node._children;
        var alphaPremultiplied = cc.BlendFunc.ALPHA_PREMULTIPLIED, alphaNonPremultipled = cc.BlendFunc.ALPHA_NON_PREMULTIPLIED;
        for (var i = 0, len = locChildren.length; i< len; i++) {
            var selBone = locChildren[i];
            if (selBone && selBone.getDisplayRenderNode) {
                var selNode = selBone.getDisplayRenderNode();
                if (null === selNode)
                    continue;

                switch (selBone.getDisplayRenderNodeType()) {
                    case ccs.DISPLAY_TYPE_SPRITE:
                        if(selNode instanceof ccs.Skin)
                            this.updateChildPosition(ctx, selNode, selBone, alphaPremultiplied, alphaNonPremultipled);
                        break;
                    case ccs.DISPLAY_TYPE_ARMATURE:
                        selNode._renderCmd.rendering(ctx, scaleX, scaleY);
                        break;
                    default:
                        selNode.visit(this);
                        break;
                }
            } else if(selBone instanceof cc.Node) {
                this._visitNormalChild(selBone);
                //selBone.visit(this);
            }
        }
    };

    proto._visitNormalChild = function(childNode){
        if(childNode == null)
            return;

        var cmd = childNode._renderCmd;
        // quick return if not visible
        if (!childNode._visible)
            return;
        cmd._curLevel = this._curLevel + 1;

        //visit for canvas
        var i, children = childNode._children, child;
        cmd._syncStatus(this);
        //because armature use transform, not setTransform
        cmd.transform(null);

        var len = children.length;
        if (len > 0) {
            childNode.sortAllChildren();
            // draw children zOrder < 0
            for (i = 0; i < len; i++) {
                child = children[i];
                if (child._localZOrder < 0)
                    child._renderCmd.visit(cmd);
                else
                    break;
            }
            cc.renderer.pushRenderCommand(cmd);
            for (; i < len; i++)
                children[i]._renderCmd.visit(cmd);
        } else {
            cc.renderer.pushRenderCommand(cmd);
        }
        this._dirtyFlag = 0;
    };

    proto.visit = function(parentCmd){
        var node = this._node;
        // quick return if not visible. children won't be drawn.
        if (!node._visible)
            return;

        this.updateStatus(parentCmd);
        node.sortAllChildren();

        cc.renderer.pushRenderCommand(this._startRenderCmd);
        this.rendering();
        cc.renderer.pushRenderCommand(this._RestoreRenderCmd);

        this._cacheDirty = false;
    };
})();