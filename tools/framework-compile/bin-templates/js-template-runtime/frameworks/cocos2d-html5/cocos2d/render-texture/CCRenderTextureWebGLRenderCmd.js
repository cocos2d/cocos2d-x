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
    cc.RenderTexture.WebGLRenderCmd = function(renderableObject){
        cc.Node.WebGLRenderCmd.call(this, renderableObject);
        this._needDraw = true;

        this._fBO = null;
        this._oldFBO = null;
        this._textureCopy = null;
        this._depthRenderBuffer = null;

        this._rtTextureRect = new cc.Rect();
        this._fullRect = new cc.Rect();
        this._fullViewport = new cc.Rect();
    };

    var proto = cc.RenderTexture.WebGLRenderCmd.prototype = Object.create(cc.Node.WebGLRenderCmd.prototype);
    proto.constructor = cc.RenderTexture.WebGLRenderCmd;

    proto.setVirtualViewport = function(rtBegin, fullRect, fullViewport) {
        this._rtTextureRect.x = rtBegin.x;
        this._rtTextureRect.y = rtBegin.y;

        this._fullRect = fullRect;
        this._fullViewport = fullViewport;
    };

    proto.rendering = function (ctx) {
        var gl = ctx || cc._renderContext;
        var node = this._node;
        if (node.autoDraw) {
            node.begin();

            var locClearFlags = node.clearFlags;
            if (locClearFlags) {
                var oldClearColor = [0.0, 0.0, 0.0, 0.0];
                var oldDepthClearValue = 0.0;
                var oldStencilClearValue = 0;

                // backup and set
                if (locClearFlags & gl.COLOR_BUFFER_BIT) {
                    oldClearColor = gl.getParameter(gl.COLOR_CLEAR_VALUE);
                    gl.clearColor(node._clearColor.r / 255, node._clearColor.g / 255, node._clearColor.b / 255, node._clearColor.a / 255);
                }

                if (locClearFlags & gl.DEPTH_BUFFER_BIT) {
                    oldDepthClearValue = gl.getParameter(gl.DEPTH_CLEAR_VALUE);
                    gl.clearDepth(node.clearDepthVal);
                }

                if (locClearFlags & gl.STENCIL_BUFFER_BIT) {
                    oldStencilClearValue = gl.getParameter(gl.STENCIL_CLEAR_VALUE);
                    gl.clearStencil(node.clearStencilVal);
                }

                // clear
                gl.clear(locClearFlags);

                // restore
                if (locClearFlags & gl.COLOR_BUFFER_BIT)
                    gl.clearColor(oldClearColor[0], oldClearColor[1], oldClearColor[2], oldClearColor[3]);

                if (locClearFlags & gl.DEPTH_BUFFER_BIT)
                    gl.clearDepth(oldDepthClearValue);

                if (locClearFlags & gl.STENCIL_BUFFER_BIT)
                    gl.clearStencil(oldStencilClearValue);
            }

            //! make sure all children are drawn
            node.sortAllChildren();
            var locChildren = node._children;
            for (var i = 0; i < locChildren.length; i++) {
                var getChild = locChildren[i];
                if (getChild !== node.sprite){
                    getChild._renderCmd.visit(node.sprite._renderCmd);    //TODO it's very Strange
                }
            }
            node.end();
        }
    };

    proto.clearStencil = function(stencilValue) {
        var gl = cc._renderContext;
        // save old stencil value
        var stencilClearValue = gl.getParameter(gl.STENCIL_CLEAR_VALUE);

        gl.clearStencil(stencilValue);
        gl.clear(gl.STENCIL_BUFFER_BIT);

        // restore clear color
        gl.clearStencil(stencilClearValue);
    };

    proto.cleanup = function(){
        var node = this._node;
        //node.sprite = null;
        this._textureCopy = null;

        var gl = cc._renderContext;
        gl.deleteFramebuffer(this._fBO);
        if (this._depthRenderBuffer)
            gl.deleteRenderbuffer(this._depthRenderBuffer);
    };

    proto.updateClearColor = function(clearColor){ };

    proto.initWithWidthAndHeight = function(width, height, format, depthStencilFormat){
        var node = this._node;
        if(format === cc.Texture2D.PIXEL_FORMAT_A8)
            cc.log( "cc.RenderTexture._initWithWidthAndHeightForWebGL() : only RGB and RGBA formats are valid for a render texture;");

        var gl = cc._renderContext, locScaleFactor = cc.contentScaleFactor();
        this._fullRect = new cc.Rect(0,0, width, height);
        this._fullViewport = new cc.Rect(0,0, width, height);

        width = 0 | (width * locScaleFactor);
        height = 0 | (height * locScaleFactor);

        this._oldFBO = gl.getParameter(gl.FRAMEBUFFER_BINDING);

        // textures must be power of two squared
        var powW , powH;

        if (cc.configuration.supportsNPOT()) {
            powW = width;
            powH = height;
        } else {
            powW = cc.NextPOT(width);
            powH = cc.NextPOT(height);
        }

        //void *data = malloc(powW * powH * 4);
        var dataLen = powW * powH * 4;
        var data = new Uint8Array(dataLen);
        //memset(data, 0, (int)(powW * powH * 4));
        for (var i = 0; i < powW * powH * 4; i++)
            data[i] = 0;

        this._pixelFormat = format;

        var locTexture = node._texture = new cc.Texture2D();
        if (!node._texture)
            return false;

        locTexture.initWithData(data, node._pixelFormat, powW, powH, cc.size(width, height));
        //free( data );

        var oldRBO = gl.getParameter(gl.RENDERBUFFER_BINDING);

        if (cc.configuration.checkForGLExtension("GL_QCOM")) {
            this._textureCopy = new cc.Texture2D();
            if (!this._textureCopy)
                return false;
            this._textureCopy.initWithData(data, node._pixelFormat, powW, powH, cc.size(width, height));
        }

        // generate FBO
        this._fBO = gl.createFramebuffer();
        gl.bindFramebuffer(gl.FRAMEBUFFER, this._fBO);

        // associate texture with FBO
        gl.framebufferTexture2D(gl.FRAMEBUFFER, gl.COLOR_ATTACHMENT0, gl.TEXTURE_2D, locTexture._webTextureObj, 0);

        if (depthStencilFormat !== 0) {
            //create and attach depth buffer
            this._depthRenderBuffer = gl.createRenderbuffer();
            gl.bindRenderbuffer(gl.RENDERBUFFER, this._depthRenderBuffer);
            gl.renderbufferStorage(gl.RENDERBUFFER, depthStencilFormat, powW, powH);
            if(depthStencilFormat === gl.DEPTH_STENCIL)
                gl.framebufferRenderbuffer(gl.FRAMEBUFFER, gl.DEPTH_STENCIL_ATTACHMENT, gl.RENDERBUFFER, this._depthRenderBuffer);
            else if(depthStencilFormat === gl.STENCIL_INDEX || depthStencilFormat === gl.STENCIL_INDEX8)
                gl.framebufferRenderbuffer(gl.FRAMEBUFFER, gl.STENCIL_ATTACHMENT, gl.RENDERBUFFER, this._depthRenderBuffer);
            else if(depthStencilFormat === gl.DEPTH_COMPONENT16)
                gl.framebufferRenderbuffer(gl.FRAMEBUFFER, gl.DEPTH_ATTACHMENT, gl.RENDERBUFFER, this._depthRenderBuffer);
        }

        // check if it worked (probably worth doing :) )
        if(gl.checkFramebufferStatus(gl.FRAMEBUFFER) !== gl.FRAMEBUFFER_COMPLETE)
            cc.log("Could not attach texture to the framebuffer");

        locTexture.setAliasTexParameters();

        var locSprite = node.sprite = new cc.Sprite(locTexture);
        locSprite.scaleY = -1;
        locSprite.setBlendFunc(gl.ONE, gl.ONE_MINUS_SRC_ALPHA);

        gl.bindRenderbuffer(gl.RENDERBUFFER, oldRBO);
        gl.bindFramebuffer(gl.FRAMEBUFFER, this._oldFBO);

        // Disabled by default.
        node.autoDraw = false;

        // add sprite for backward compatibility
        node.addChild(locSprite);
        return true;
    };

    proto.begin = function(){
        var node = this._node;
        // Save the current matrix
        cc.kmGLMatrixMode(cc.KM_GL_PROJECTION);
        cc.kmGLPushMatrix();
        cc.kmGLMatrixMode(cc.KM_GL_MODELVIEW);
        cc.kmGLPushMatrix();

        var gl = cc._renderContext;

        var director = cc.director;
        director.setProjection(director.getProjection());

        var texSize = node._texture.getContentSizeInPixels();

        // Calculate the adjustment ratios based on the old and new projections
        var size = cc.director.getWinSizeInPixels();
        var widthRatio = size.width / texSize.width;
        var heightRatio = size.height / texSize.height;

        var orthoMatrix = cc.math.Matrix4.createOrthographicProjection(-1.0 / widthRatio, 1.0 / widthRatio,
            -1.0 / heightRatio, 1.0 / heightRatio, -1, 1);
        cc.kmGLMultMatrix(orthoMatrix);

        //calculate viewport
        var viewport = new cc.Rect(0, 0, 0, 0);
        viewport.width = this._fullViewport.width;
        viewport.height = this._fullViewport.height;
        var viewPortRectWidthRatio = viewport.width / this._fullRect.width;
        var viewPortRectHeightRatio = viewport.height / this._fullRect.height;
        viewport.x = (this._fullRect.x - this._rtTextureRect.x) * viewPortRectWidthRatio;
        viewport.y = (this._fullRect.y - this._rtTextureRect.y) * viewPortRectHeightRatio;
        gl.viewport(viewport.x, viewport.y, viewport.width, viewport.height);

        this._oldFBO = gl.getParameter(gl.FRAMEBUFFER_BINDING);
        gl.bindFramebuffer(gl.FRAMEBUFFER, this._fBO);//Will direct drawing to the frame buffer created above

        /*  Certain Qualcomm Andreno gpu's will retain data in memory after a frame buffer switch which corrupts the render to the texture.
         *   The solution is to clear the frame buffer before rendering to the texture. However, calling glClear has the unintended result of clearing the current texture.
         *   Create a temporary texture to overcome this. At the end of CCRenderTexture::begin(), switch the attached texture to the second one, call glClear,
         *   and then switch back to the original texture. This solution is unnecessary for other devices as they don't have the same issue with switching frame buffers.
         */
        if (cc.configuration.checkForGLExtension("GL_QCOM")) {
            // -- bind a temporary texture so we can clear the render buffer without losing our texture
            gl.framebufferTexture2D(gl.FRAMEBUFFER, gl.COLOR_ATTACHMENT0, gl.TEXTURE_2D, this._textureCopy._webTextureObj, 0);
            //cc.checkGLErrorDebug();
            gl.clear(gl.COLOR_BUFFER_BIT | gl.DEPTH_BUFFER_BIT);
            gl.framebufferTexture2D(gl.FRAMEBUFFER, gl.COLOR_ATTACHMENT0, gl.TEXTURE_2D, node._texture._webTextureObj, 0);
        }
    };

    proto._beginWithClear = function(r, g, b, a, depthValue, stencilValue, flags){
        r = r / 255;
        g = g / 255;
        b = b / 255;
        a = a / 255;

        var gl = cc._renderContext;

        // save clear color
        var clearColor = [0.0, 0.0, 0.0, 0.0];
        var depthClearValue = 0.0;
        var stencilClearValue = 0;

        if (flags & gl.COLOR_BUFFER_BIT) {
            clearColor = gl.getParameter(gl.COLOR_CLEAR_VALUE);
            gl.clearColor(r, g, b, a);
        }

        if (flags & gl.DEPTH_BUFFER_BIT) {
            depthClearValue = gl.getParameter(gl.DEPTH_CLEAR_VALUE);
            gl.clearDepth(depthValue);
        }

        if (flags & gl.STENCIL_BUFFER_BIT) {
            stencilClearValue = gl.getParameter(gl.STENCIL_CLEAR_VALUE);
            gl.clearStencil(stencilValue);
        }

        gl.clear(flags);

        // restore
        if (flags & gl.COLOR_BUFFER_BIT)
            gl.clearColor(clearColor[0], clearColor[1], clearColor[2], clearColor[3]);

        if (flags & gl.DEPTH_BUFFER_BIT)
            gl.clearDepth(depthClearValue);

        if (flags & gl.STENCIL_BUFFER_BIT)
            gl.clearStencil(stencilClearValue);
    };

    proto.end = function(){
        var node = this._node;
        cc.renderer._renderingToBuffer(node.__instanceId);

        var gl = cc._renderContext;
        var director = cc.director;
        gl.bindFramebuffer(gl.FRAMEBUFFER, this._oldFBO);

        //restore viewport
        director.setViewport();
        cc.kmGLMatrixMode(cc.KM_GL_PROJECTION);
        cc.kmGLPopMatrix();
        cc.kmGLMatrixMode(cc.KM_GL_MODELVIEW);
        cc.kmGLPopMatrix();

        /* var size = director.getWinSizeInPixels();

         // restore viewport
         gl.viewport(0, 0, size.width * cc.contentScaleFactor(), size.height * cc.contentScaleFactor());

         // special viewport for 3d projection + retina display
         if (director.getProjection() == cc.Director.PROJECTION_3D && cc.contentScaleFactor() != 1) {
         gl.viewport((-size.width / 2), (-size.height / 2), (size.width * cc.contentScaleFactor()), (size.height * cc.contentScaleFactor()));
         }

         director.setProjection(director.getProjection());*/
    };

    proto.clearRect = function(x, y, width, height){
        //TODO need to implement
    };

    proto.clearDepth = function(depthValue){
        var node = this._node;
        node.begin();

        var gl = cc._renderContext;
        //! save old depth value
        var depthClearValue = gl.getParameter(gl.DEPTH_CLEAR_VALUE);

        gl.clearDepth(depthValue);
        gl.clear(gl.DEPTH_BUFFER_BIT);

        // restore clear color
        gl.clearDepth(depthClearValue);
        node.end();
    };

    proto.visit = function(parentCmd){
        var node = this._node;
        if (!node._visible)
            return;
        cc.kmGLPushMatrix();

        //TODO using GridNode
        /*        var locGrid = this.grid;
         if (locGrid && locGrid.isActive()) {
         locGrid.beforeDraw();
         this.transformAncestors();
         }*/

        this._syncStatus(parentCmd);
        //this.toRenderer();
        cc.renderer.pushRenderCommand(this);
        node.sprite.visit(this);

        //TODO GridNode
        /*        if (locGrid && locGrid.isActive())
         locGrid.afterDraw(this);*/

        this._dirtyFlag = 0;
        cc.kmGLPopMatrix();
    };
})();