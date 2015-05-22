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
    cc.ScrollView.WebGLRenderCmd = function(renderable){
        cc.Layer.WebGLRenderCmd.call(this, renderable);
        this._needDraw = false;

        this.startCmd = new cc.CustomRenderCmd(this, this._startCmd);
        this.endCmd = new cc.CustomRenderCmd(this, this._endCmd);
    };

    var proto = cc.ScrollView.WebGLRenderCmd.prototype = Object.create(cc.Layer.WebGLRenderCmd.prototype);
    proto.constructor = cc.ScrollView.WebGLRenderCmd;

    proto._startCmd = function(){
        var node = this._node;
        var EGLViewer = cc.view;
        var frame = node._getViewRect();
        if(EGLViewer.isScissorEnabled()){
            node._scissorRestored = true;
            node._parentScissorRect = EGLViewer.getScissorRect();
            //set the intersection of m_tParentScissorRect and frame as the new scissor rect
            if (cc.rectIntersection(frame, node._parentScissorRect)) {
                var locPSRect = node._parentScissorRect;
                var x = Math.max(frame.x, locPSRect.x);
                var y = Math.max(frame.y, locPSRect.y);
                var xx = Math.min(frame.x + frame.width, locPSRect.x + locPSRect.width);
                var yy = Math.min(frame.y + frame.height, locPSRect.y + locPSRect.height);
                EGLViewer.setScissorInPoints(x, y, xx - x, yy - y);
            }
        }else{
            var ctx = cc._renderContext;
            ctx.enable(ctx.SCISSOR_TEST);
            //clip
            EGLViewer.setScissorInPoints(frame.x, frame.y, frame.width, frame.height);
        }
    };

    proto._endCmd = function(){
        var node = this._node;
        if (node._scissorRestored) {  //restore the parent's scissor rect
            var rect = node._parentScissorRect;
            cc.view.setScissorInPoints(rect.x, rect.y, rect.width, rect.height)
        }else{
            var ctx = cc._renderContext;
            ctx.disable(ctx.SCISSOR_TEST);
        }
    };

    proto.visit = function(parendCmd){
        var node = this._node;

        var i, locChildren = node._children, selChild, childrenLen;

        cc.kmGLPushMatrix();

        this.transform(parendCmd);

        if (node._clippingToBounds) {
            cc.renderer.pushRenderCommand(this.startCmd);
        }

        if (locChildren && locChildren.length > 0) {
            childrenLen = locChildren.length;
            // draw children zOrder < 0
            for (i = 0; i < childrenLen; i++) {
                selChild = locChildren[i];
                if (selChild && selChild._localZOrder < 0)
                    selChild._renderCmd.visit();
                else
                    break;
            }

            // draw children zOrder >= 0
            for (; i < childrenLen; i++)
                locChildren[i]._renderCmd.visit();
        }

        if (node._clippingToBounds) {
            cc.renderer.pushRenderCommand(this.endCmd);
        }

        this._dirtyFlag = 0;
        cc.kmGLPopMatrix();
    };
})();