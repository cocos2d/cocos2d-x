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

// ------------------------------- ClippingNode's WebGL render cmd ------------------------------
(function(){
    cc.ClippingNode.WebGLRenderCmd = function(renderable){
        cc.Node.WebGLRenderCmd.call(this, renderable);
        this._needDraw = false;

        this._beforeVisitCmd = new cc.CustomRenderCmd(this, this._onBeforeVisit);
        this._afterDrawStencilCmd = new cc.CustomRenderCmd(this, this._onAfterDrawStencil);
        this._afterVisitCmd = new cc.CustomRenderCmd(this, this._onAfterVisit);

        this._currentStencilFunc = null;
        this._currentStencilRef = null;
        this._currentStencilValueMask = null;
        this._currentStencilFail = null;
        this._currentStencilPassDepthFail = null;
        this._currentStencilPassDepthPass = null;
        this._currentStencilWriteMask = null;
        this._currentStencilEnabled = null;
        this._currentDepthWriteMask = null;
        this._mask_layer_le = null;
    };

    var proto = cc.ClippingNode.WebGLRenderCmd.prototype = Object.create(cc.Node.WebGLRenderCmd.prototype);
    proto.constructor = cc.ClippingNode.WebGLRenderCmd;

    cc.ClippingNode.WebGLRenderCmd._init_once = null;
    cc.ClippingNode.WebGLRenderCmd._visit_once = null;
    cc.ClippingNode.WebGLRenderCmd._layer = -1;

    proto.initStencilBits = function(){
        // get (only once) the number of bits of the stencil buffer
        cc.ClippingNode.WebGLRenderCmd._init_once = true;
        if (cc.ClippingNode.WebGLRenderCmd._init_once) {
            cc.stencilBits = cc._renderContext.getParameter(cc._renderContext.STENCIL_BITS);
            if (cc.stencilBits <= 0)
                cc.log("Stencil buffer is not enabled.");
            cc.ClippingNode.WebGLRenderCmd._init_once = false;
        }
    };

    proto.transform = function(parentCmd, recursive){
        var node = this._node;
        cc.Node.WebGLRenderCmd.prototype.transform.call(this, parentCmd, recursive);
        if(node._stencil)
            node._stencil._renderCmd.transform(this, recursive);
    };

    proto.visit = function(parentCmd){
        var node = this._node;
        // quick return if not visible
        if (!node._visible)
            return;

        if( node._parent && node._parent._renderCmd)
            this._curLevel = node._parent._renderCmd._curLevel + 1;

        // if stencil buffer disabled
        if (cc.stencilBits < 1) {
            // draw everything, as if there where no stencil
            cc.Node.WebGLRenderCmd.prototype.visit.call(this, parentCmd);
            return;
        }

        if (!node._stencil || !node._stencil.visible) {
            if (node.inverted)
                cc.Node.WebGLRenderCmd.prototype.visit.call(this, parentCmd);   // draw everything
            return;
        }

        if (cc.ClippingNode.WebGLRenderCmd._layer + 1 === cc.stencilBits) {
            cc.ClippingNode.WebGLRenderCmd._visit_once = true;
            if (cc.ClippingNode.WebGLRenderCmd._visit_once) {
                cc.log("Nesting more than " + cc.stencilBits + "stencils is not supported. Everything will be drawn without stencil for this node and its children.");
                cc.ClippingNode.WebGLRenderCmd._visit_once = false;
            }
            // draw everything, as if there where no stencil
            cc.Node.WebGLRenderCmd.prototype.visit.call(this, parentCmd);
            return;
        }

        cc.renderer.pushRenderCommand(this._beforeVisitCmd);

        //optimize performance for javascript
        var currentStack = cc.current_stack;
        currentStack.stack.push(currentStack.top);
        this._syncStatus(parentCmd);
        currentStack.top = this._stackMatrix;

        //this._stencil._stackMatrix = this._stackMatrix;
        node._stencil._renderCmd.visit(this);

        cc.renderer.pushRenderCommand(this._afterDrawStencilCmd);

        // draw (according to the stencil test func) this node and its children
        var locChildren = node._children;
        if (locChildren && locChildren.length > 0) {
            var childLen = locChildren.length;
            node.sortAllChildren();
            // draw children zOrder < 0
            for (var i = 0; i < childLen; i++) {
                locChildren[i]._renderCmd.visit(this);
            }
        }

        cc.renderer.pushRenderCommand(this._afterVisitCmd);

        this._dirtyFlag = 0;
        //optimize performance for javascript
        currentStack.top = currentStack.stack.pop();
    };

    proto.setStencil = function(stencil){
        var node = this._node;
        if(node._stencil)
            node._stencil._parent = null;
        node._stencil = stencil;
        if(node._stencil)
            node._stencil._parent = node;
    };

    proto._drawFullScreenQuadClearStencil = function () {
        // draw a fullscreen solid rectangle to clear the stencil buffer
        var projStack = cc.projection_matrix_stack;
        //cc.kmGLMatrixMode(cc.KM_GL_PROJECTION);
        //cc.kmGLPushMatrix();
        //cc.kmGLLoadIdentity();
        projStack.push();
        projStack.top.identity();

        //cc.kmGLMatrixMode(cc.KM_GL_MODELVIEW);
        //cc.kmGLPushMatrix();
        //cc.kmGLLoadIdentity();
        var modelViewStack = cc.modelview_matrix_stack;
        modelViewStack.push();
        modelViewStack.top.identity();

        cc._drawingUtil.drawSolidRect(cc.p(-1, -1), cc.p(1, 1), cc.color(255, 255, 255, 255));

        //cc.kmGLMatrixMode(cc.KM_GL_PROJECTION);
        //cc.kmGLPopMatrix();
        projStack.pop();

        //cc.kmGLMatrixMode(cc.KM_GL_MODELVIEW);
        //cc.kmGLPopMatrix();
        modelViewStack.pop();
    };

    proto._onBeforeVisit = function(ctx){
        var gl = ctx || cc._renderContext, node = this._node;
        cc.ClippingNode.WebGLRenderCmd._layer++;

        // mask of the current layer (ie: for layer 3: 00000100)
        var mask_layer = 0x1 << cc.ClippingNode.WebGLRenderCmd._layer;
        // mask of all layers less than the current (ie: for layer 3: 00000011)
        var mask_layer_l = mask_layer - 1;
        // mask of all layers less than or equal to the current (ie: for layer 3: 00000111)
        //var mask_layer_le = mask_layer | mask_layer_l;
        this._mask_layer_le = mask_layer | mask_layer_l;
        // manually save the stencil state
        this._currentStencilEnabled = gl.isEnabled(gl.STENCIL_TEST);
        this._currentStencilWriteMask = gl.getParameter(gl.STENCIL_WRITEMASK);
        this._currentStencilFunc = gl.getParameter(gl.STENCIL_FUNC);
        this._currentStencilRef = gl.getParameter(gl.STENCIL_REF);
        this._currentStencilValueMask = gl.getParameter(gl.STENCIL_VALUE_MASK);
        this._currentStencilFail = gl.getParameter(gl.STENCIL_FAIL);
        this._currentStencilPassDepthFail = gl.getParameter(gl.STENCIL_PASS_DEPTH_FAIL);
        this._currentStencilPassDepthPass = gl.getParameter(gl.STENCIL_PASS_DEPTH_PASS);

        // enable stencil use
        gl.enable(gl.STENCIL_TEST);
        gl.stencilMask(mask_layer);
        this._currentDepthWriteMask = gl.getParameter(gl.DEPTH_WRITEMASK);

        gl.depthMask(false);

        gl.stencilFunc(gl.NEVER, mask_layer, mask_layer);
        gl.stencilOp(!node.inverted ? gl.ZERO : gl.REPLACE, gl.KEEP, gl.KEEP);

        this._drawFullScreenQuadClearStencil();

        gl.stencilFunc(gl.NEVER, mask_layer, mask_layer);
        gl.stencilOp(!node.inverted ? gl.REPLACE : gl.ZERO, gl.KEEP, gl.KEEP);

        if (node.alphaThreshold < 1) {            //TODO desktop
            var program = cc.shaderCache.programForKey(cc.SHADER_POSITION_TEXTURECOLORALPHATEST);
            var alphaValueLocation = gl.getUniformLocation(program.getProgram(), cc.UNIFORM_ALPHA_TEST_VALUE_S);
            // set our alphaThreshold
            cc.glUseProgram(program.getProgram());
            program.setUniformLocationWith1f(alphaValueLocation, node.alphaThreshold);
            cc.setProgram(node._stencil, program);
        }
    };

    proto._onAfterDrawStencil = function(ctx){
        var gl = ctx || cc._renderContext;
        gl.depthMask(this._currentDepthWriteMask);

        gl.stencilFunc(gl.EQUAL, this._mask_layer_le, this._mask_layer_le);
        gl.stencilOp(gl.KEEP, gl.KEEP, gl.KEEP);
    };

    proto._onAfterVisit = function(ctx){
        var gl = ctx || cc._renderContext;

        gl.stencilFunc(this._currentStencilFunc, this._currentStencilRef, this._currentStencilValueMask);
        gl.stencilOp(this._currentStencilFail, this._currentStencilPassDepthFail, this._currentStencilPassDepthPass);
        gl.stencilMask(this._currentStencilWriteMask);
        if (!this._currentStencilEnabled)
            gl.disable(gl.STENCIL_TEST);

        // we are done using this layer, decrement
        cc.ClippingNode.WebGLRenderCmd._layer--;
    }
})();
