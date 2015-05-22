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

if (cc._renderType === cc._RENDER_TYPE_CANVAS) {
    (function () {
        ccui.Widget.CanvasRenderCmd = function (renderable) {
            cc.ProtectedNode.CanvasRenderCmd.call(this, renderable);
            this._needDraw = false;
        };

        var proto = ccui.Widget.CanvasRenderCmd.prototype = Object.create(cc.ProtectedNode.CanvasRenderCmd.prototype);
        proto.constructor = ccui.Widget.CanvasRenderCmd;

        proto.visit = function (parentCmd) {
            var node = this._node;
            if (node._visible) {
                node._adaptRenderers();
                cc.ProtectedNode.CanvasRenderCmd.prototype.visit.call(this, parentCmd);
            }
        };

        proto.transform = function (parentCmd, recursive) {
            var node = this._node;

            if (node._visible) {
                node._adaptRenderers();
                if(!this._usingLayoutComponent){
                    var widgetParent = node.getWidgetParent();
                    if (widgetParent) {
                        var parentSize = widgetParent.getContentSize();
                        if (parentSize.width !== 0 && parentSize.height !== 0) {
                            node._position.x = parentSize.width * node._positionPercent.x;
                            node._position.y = parentSize.height * node._positionPercent.y;
                        }
                    }
                }
                cc.ProtectedNode.CanvasRenderCmd.prototype.transform.call(this, parentCmd, recursive);
            }
        };
    })();
} else {
    (function () {
        ccui.Widget.WebGLRenderCmd = function (renderable) {
            cc.ProtectedNode.WebGLRenderCmd.call(this, renderable);
            this._needDraw = false;
        };

        var proto = ccui.Widget.WebGLRenderCmd.prototype = Object.create(cc.ProtectedNode.WebGLRenderCmd.prototype);
        proto.constructor = ccui.Widget.WebGLRenderCmd;

        proto.visit = function (parentCmd) {
            var node = this._node;
            if (node._visible) {
                node._adaptRenderers();
                cc.ProtectedNode.WebGLRenderCmd.prototype.visit.call(this, parentCmd);
            }
        };

        proto.transform = function(parentCmd, recursive){
            var node = this._node;
            if (node._visible) {
                node._adaptRenderers();

                if(!this._usingLayoutComponent) {
                    var widgetParent = node.getWidgetParent();
                    if (widgetParent) {
                        var parentSize = widgetParent.getContentSize();
                        if (parentSize.width !== 0 && parentSize.height !== 0) {
                            node._position.x = parentSize.width * node._positionPercent.x;
                            node._position.y = parentSize.height * node._positionPercent.y;
                        }
                    }
                }
                cc.ProtectedNode.WebGLRenderCmd.prototype.transform.call(this, parentCmd, recursive);
            }
        };
    })();
}

