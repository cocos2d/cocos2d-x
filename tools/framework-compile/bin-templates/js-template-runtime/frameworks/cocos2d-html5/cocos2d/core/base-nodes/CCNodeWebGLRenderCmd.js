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
// ------------------------------ The cc.Node's render command for WebGL ----------------------------------
(function() {
    cc.Node.WebGLRenderCmd = function (renderable) {
        cc.Node.RenderCmd.call(this, renderable);

        var mat4 = new cc.math.Matrix4(), mat = mat4.mat;
        mat[2] = mat[3] = mat[6] = mat[7] = mat[8] = mat[9] = mat[11] = mat[14] = 0.0;
        mat[10] = mat[15] = 1.0;
        this._transform4x4 = mat4;
        this._stackMatrix = new cc.math.Matrix4();
        this._shaderProgram = null;

        this._camera = null;
    };

    var proto = cc.Node.WebGLRenderCmd.prototype = Object.create(cc.Node.RenderCmd.prototype);
    proto.constructor = cc.Node.WebGLRenderCmd;

    proto.getNodeToParentTransform = function () {
        var node = this._node;
        if (node._usingNormalizedPosition && node._parent) {        //TODO need refactor
            var conSize = node._parent._contentSize;
            node._position.x = node._normalizedPosition.x * conSize.width;
            node._position.y = node._normalizedPosition.y * conSize.height;
            node._normalizedPositionDirty = false;
        }
        if (this._dirtyFlag & cc.Node._dirtyFlags.transformDirty) {
            // Translate values
            var x = node._position.x, y = node._position.y;
            var apx = this._anchorPointInPoints.x, napx = -apx;
            var apy = this._anchorPointInPoints.y, napy = -apy;
            var scx = node._scaleX, scy = node._scaleY;
            var rotationRadiansX = node._rotationX * 0.017453292519943295;  //0.017453292519943295 = (Math.PI / 180);   for performance
            var rotationRadiansY = node._rotationY * 0.017453292519943295;

            if (node._ignoreAnchorPointForPosition) {
                x += apx;
                y += apy;
            }

            // Rotation values
            // Change rotation code to handle X and Y
            // If we skew with the exact same value for both x and y then we're simply just rotating
            var cx = 1, sx = 0, cy = 1, sy = 0;
            if (node._rotationX !== 0 || node._rotationY !== 0) {
                cx = Math.cos(-rotationRadiansX);
                sx = Math.sin(-rotationRadiansX);
                cy = Math.cos(-rotationRadiansY);
                sy = Math.sin(-rotationRadiansY);
            }
            var needsSkewMatrix = ( node._skewX || node._skewY );

            // optimization:
            // inline anchor point calculation if skew is not needed
            // Adjusted transform calculation for rotational skew
            if (!needsSkewMatrix && (apx !== 0 || apy !== 0)) {
                x += cy * napx * scx + -sx * napy * scy;
                y += sy * napx * scx + cx * napy * scy;
            }

            // Build Transform Matrix
            // Adjusted transform calculation for rotational skew
            var t = this._transform;
            t.a = cy * scx;
            t.b = sy * scx;
            t.c = -sx * scy;
            t.d = cx * scy;
            t.tx = x;
            t.ty = y;

            // XXX: Try to inline skew
            // If skew is needed, apply skew and then anchor point
            if (needsSkewMatrix) {
                t = cc.affineTransformConcat({a: 1.0, b: Math.tan(cc.degreesToRadians(node._skewY)),
                    c: Math.tan(cc.degreesToRadians(node._skewX)), d: 1.0, tx: 0.0, ty: 0.0}, t);

                // adjust anchor point
                if (apx !== 0 || apy !== 0)
                    t = cc.affineTransformTranslate(t, napx, napy);
            }

            if (node._additionalTransformDirty) {
                t = cc.affineTransformConcat(t, node._additionalTransform);
                node._additionalTransformDirty = false;
            }
            this._transform = t;
        }
        return this._transform;
    };

    proto._syncStatus = function (parentCmd) {
        var flags = cc.Node._dirtyFlags, locFlag = this._dirtyFlag;
        var parentNode = parentCmd ? parentCmd._node : null;

        if(parentNode && parentNode._cascadeColorEnabled && (parentCmd._dirtyFlag & flags.colorDirty))
            locFlag |= flags.colorDirty;

        if(parentNode && parentNode._cascadeOpacityEnabled && (parentCmd._dirtyFlag & flags.opacityDirty))
            locFlag |= flags.opacityDirty;

        if(parentCmd && (parentCmd._dirtyFlag & flags.transformDirty))
            locFlag |= flags.transformDirty;

        var colorDirty = locFlag & flags.colorDirty,
            opacityDirty = locFlag & flags.opacityDirty;

        this._dirtyFlag = locFlag;

        if (colorDirty)
            this._syncDisplayColor();

        if (opacityDirty)
            this._syncDisplayOpacity();

        if(colorDirty || opacityDirty)
            this._updateColor();

        //if (locFlag & flags.transformDirty) {      //need update the stackMatrix every calling visit, because when projection changed, need update all scene graph element.
            //update the transform
        this.transform(parentCmd);
        //}
    };

    proto._updateColor = function(){};

    proto.visit = function (parentCmd) {
        var node = this._node;
        // quick return if not visible
        if (!node._visible)
            return;

        parentCmd = parentCmd || this.getParentRenderCmd();
        if (node._parent && node._parent._renderCmd)
            this._curLevel = node._parent._renderCmd._curLevel + 1;

        var i, currentStack = cc.current_stack;

        //optimize performance for javascript
        currentStack.stack.push(currentStack.top);
        this._syncStatus(parentCmd);
        currentStack.top = this._stackMatrix;

        var locChildren = node._children;
        if (locChildren && locChildren.length > 0) {
            var childLen = locChildren.length;
            node.sortAllChildren();
            // draw children zOrder < 0
            for (i = 0; i < childLen; i++) {
                if (locChildren[i] && locChildren[i]._localZOrder < 0)
                    locChildren[i]._renderCmd.visit(this);
                else
                    break;
            }

            cc.renderer.pushRenderCommand(this);
            // draw children zOrder >= 0
            for (; i < childLen; i++) {
                if (locChildren[i])
                    locChildren[i]._renderCmd.visit(this);
            }
        } else
            cc.renderer.pushRenderCommand(this);

        this._dirtyFlag = 0;
        //optimize performance for javascript
        currentStack.top = currentStack.stack.pop();
    };

    proto.transform = function (parentCmd, recursive) {
        var t4x4 = this._transform4x4, stackMatrix = this._stackMatrix, node = this._node;
        parentCmd = parentCmd || this.getParentRenderCmd();
        var parentMatrix = (parentCmd ? parentCmd._stackMatrix : cc.current_stack.top);

        // Convert 3x3 into 4x4 matrix
        var trans = this.getNodeToParentTransform();

        this._dirtyFlag = this._dirtyFlag & cc.Node._dirtyFlags.transformDirty ^ this._dirtyFlag;

        var t4x4Mat = t4x4.mat;
        t4x4Mat[0] = trans.a;
        t4x4Mat[4] = trans.c;
        t4x4Mat[12] = trans.tx;
        t4x4Mat[1] = trans.b;
        t4x4Mat[5] = trans.d;
        t4x4Mat[13] = trans.ty;

        // Update Z vertex manually
        t4x4Mat[14] = node._vertexZ;

        //optimize performance for Javascript
        cc.kmMat4Multiply(stackMatrix, parentMatrix, t4x4);

        // XXX: Expensive calls. Camera should be integrated into the cached affine matrix
        if (node._camera !== null && !(node.grid !== null && node.grid.isActive())) {
            var apx = this._anchorPointInPoints.x, apy = this._anchorPointInPoints.y;
            var translate = (apx !== 0.0 || apy !== 0.0);
            if (translate){
                if(!cc.SPRITEBATCHNODE_RENDER_SUBPIXEL) {
                    apx = 0 | apx;
                    apy = 0 | apy;
                }
                //cc.kmGLTranslatef(apx, apy, 0);
                var translation = cc.math.Matrix4.createByTranslation(apx, apy, 0, t4x4);      //t4x4 as a temp matrix
                stackMatrix.multiply(translation);

                node._camera._locateForRenderer(stackMatrix);

                //cc.kmGLTranslatef(-apx, -apy, 0);    optimize at here : kmGLTranslatef
                translation = cc.math.Matrix4.createByTranslation(-apx, -apy, 0, translation);
                stackMatrix.multiply(translation);
                t4x4.identity(); //reset t4x4;
            } else {
                node._camera._locateForRenderer(stackMatrix);
            }
        }
        if(!recursive || !node._children || node._children.length === 0)
            return;
        var i, len, locChildren = node._children;
        for(i = 0, len = locChildren.length; i< len; i++){
            locChildren[i]._renderCmd.transform(this, recursive);
        }
    };

    proto.setShaderProgram = function (shaderProgram) {
        this._shaderProgram = shaderProgram;
    };

    proto.getShaderProgram = function () {
        return this._shaderProgram;
    };
})();
