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

    ccs.Armature.WebGLRenderCmd = function(renderableObject){
        cc.Node.WebGLRenderCmd.call(this, renderableObject);
        this._needDraw = true;

        this._realAnchorPointInPoints = new cc.Point(0,0);
    };

    var proto = ccs.Armature.WebGLRenderCmd.prototype = Object.create(cc.Node.WebGLRenderCmd.prototype);
    cc.inject(ccs.Armature.RenderCmd, proto);
    proto.constructor = ccs.Armature.WebGLRenderCmd;

    proto.rendering = function (ctx, dontChangeMatrix) {
        var node = this._node;

        if(!dontChangeMatrix){
            cc.kmGLMatrixMode(cc.KM_GL_MODELVIEW);
            cc.kmGLPushMatrix();
            cc.kmGLLoadMatrix(this._stackMatrix);
        }

        var locChildren = node._children;
        var alphaPremultiplied = cc.BlendFunc.ALPHA_PREMULTIPLIED, alphaNonPremultipled = cc.BlendFunc.ALPHA_NON_PREMULTIPLIED;
        for (var i = 0, len = locChildren.length; i < len; i++) {
            var selBone = locChildren[i];
            if (selBone && selBone.getDisplayRenderNode) {
                var selNode = selBone.getDisplayRenderNode();
                if (null === selNode)
                    continue;
                selNode.setShaderProgram(this._shaderProgram);
                switch (selBone.getDisplayRenderNodeType()) {
                    case ccs.DISPLAY_TYPE_SPRITE:
                        if (selNode instanceof ccs.Skin) {
                            this._updateColorAndOpacity(selNode._renderCmd, selBone);   //because skin didn't call visit()
                            selNode.updateTransform();

                            var func = selBone.getBlendFunc();
                            if (func.src !== alphaPremultiplied.src || func.dst !== alphaPremultiplied.dst)
                                selNode.setBlendFunc(selBone.getBlendFunc());
                            else {
                                if ((node._blendFunc.src === alphaPremultiplied.src && node._blendFunc.dst === alphaPremultiplied.dst)
                                    && !selNode.getTexture().hasPremultipliedAlpha())
                                    selNode.setBlendFunc(alphaNonPremultipled);
                                else
                                    selNode.setBlendFunc(node._blendFunc);
                            }
                            selNode._renderCmd.rendering(ctx);
                        }
                        break;
                    case ccs.DISPLAY_TYPE_ARMATURE:
                        selNode._renderCmd.rendering(ctx, true);
                        break;
                    default:
                        selNode._renderCmd.transform();
                        selNode._renderCmd.rendering(ctx);
                        break;
                }
            } else if (selBone instanceof cc.Node) {
                selBone.setShaderProgram(this._shaderProgram);
                selBone._renderCmd.transform();
                if(selBone._renderCmd.rendering)
                    selBone._renderCmd.rendering(ctx);
            }
        }
        if(!dontChangeMatrix)
            cc.kmGLPopMatrix();
    };

    proto.initShaderCache = function(){
        this._shaderProgram = cc.shaderCache.programForKey(cc.SHADER_POSITION_TEXTURECOLOR);
    };

    proto.setShaderProgram = function(shaderProgram){
        this._shaderProgram = shaderProgram;
    };

    proto._updateColorAndOpacity = function(skinRenderCmd, bone){
        //update displayNode's color and opacity
        var parentColor = bone._renderCmd._displayedColor, parentOpacity = bone._renderCmd._displayedOpacity;
        var flags = cc.Node._dirtyFlags, locFlag = skinRenderCmd._dirtyFlag;
        var colorDirty = locFlag & flags.colorDirty,
            opacityDirty = locFlag & flags.opacityDirty;
        if(colorDirty)
            skinRenderCmd._updateDisplayColor(parentColor);
        if(opacityDirty)
            skinRenderCmd._updateDisplayOpacity(parentOpacity);
        if(colorDirty || opacityDirty)
            skinRenderCmd._updateColor();
    };

    proto.updateChildPosition = function(ctx, dis, selBone, alphaPremultiplied, alphaNonPremultipled){
        var node = this._node;
        dis.updateTransform();

        var func = selBone.getBlendFunc();
        if (func.src !== alphaPremultiplied.src || func.dst !== alphaPremultiplied.dst)
            dis.setBlendFunc(selBone.getBlendFunc());
        else {
            if ((node._blendFunc.src === alphaPremultiplied.src && node_blendFunc.dst === alphaPremultiplied.dst)
                && !dis.getTexture().hasPremultipliedAlpha())
                dis.setBlendFunc(alphaNonPremultipled);
            else
                dis.setBlendFunc(node._blendFunc);
        }
        dis.rendering(ctx);
    };

    proto.updateStatus = function () {
        var flags = cc.Node._dirtyFlags, locFlag = this._dirtyFlag;
        var colorDirty = locFlag & flags.colorDirty,
            opacityDirty = locFlag & flags.opacityDirty;
        if(colorDirty)
            this._updateDisplayColor();

        if(opacityDirty)
            this._updateDisplayOpacity();

        if(colorDirty || opacityDirty)
            this._updateColor();

        //update the transform every visit, needn't dirty flag,
        this.transform(this.getParentRenderCmd(), true);
    };

    proto.visit = function(parentCmd){
        var node = this._node;
        // quick return if not visible. children won't be drawn.
        if (!node._visible)
            return;

        var currentStack = cc.current_stack;
        currentStack.stack.push(currentStack.top);
        this.updateStatus(parentCmd);
        currentStack.top = this._stackMatrix;

        node.sortAllChildren();
        cc.renderer.pushRenderCommand(this);

        this._dirtyFlag = 0;
        currentStack.top = currentStack.stack.pop();
    };
})();