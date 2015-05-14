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
    cc.NodeGrid.WebGLRenderCmd = function(renderable){
        cc.Node.WebGLRenderCmd.call(this, renderable);
        this._needDraw = false;
        this._gridBeginCommand = new cc.CustomRenderCmd(this, this.onGridBeginDraw);
        this._gridEndCommand = new cc.CustomRenderCmd(this, this.onGridEndDraw);
    };

    var proto = cc.NodeGrid.WebGLRenderCmd.prototype = Object.create(cc.Node.WebGLRenderCmd.prototype);
    proto.constructor = cc.NodeGrid.WebGLRenderCmd;

    proto.visit = function(parentCmd) {
        var node = this._node;
        // quick return if not visible
        if (!node._visible)
            return;

        parentCmd = parentCmd || this.getParentRenderCmd();
        if (node._parent && node._parent._renderCmd)
            this._curLevel = node._parent._renderCmd._curLevel + 1;

        var currentStack = cc.current_stack;
        currentStack.stack.push(currentStack.top);
        this._syncStatus(parentCmd);
        currentStack.top = this._stackMatrix;

        /*var beforeProjectionType = cc.director.PROJECTION_DEFAULT;
        if (locGrid && locGrid._active) {
            //var backMatrix = new cc.kmMat4();
            //cc.kmMat4Assign(backMatrix, this._stackMatrix);

            beforeProjectionType = cc.director.getProjection();
            //locGrid.set2DProjection();

            //reset this._stackMatrix to current_stack.top
            //cc.kmMat4Assign(currentStack.top, backMatrix);
        }*/
        cc.renderer.pushRenderCommand(this._gridBeginCommand);

        if (node._target)
            node._target.visit();

        var locChildren = node._children;
        if (locChildren && locChildren.length > 0) {
            var childLen = locChildren.length;
            node.sortAllChildren();
            // draw children
            for (var i = 0; i < childLen; i++) {
                var child = locChildren[i];
                child && child.visit();
            }
        }

        //if (locGrid && locGrid._active) {
            //cc.director.setProjection(beforeProjectionType);
        //}
        cc.renderer.pushRenderCommand(this._gridEndCommand);

        this._dirtyFlag = 0;
        currentStack.top = currentStack.stack.pop();
    };

    proto.onGridBeginDraw = function(){
        var locGrid = this._node.grid;
        if (locGrid && locGrid._active)
            locGrid.beforeDraw();
    };

    proto.onGridEndDraw = function(){
        var locGrid = this._node.grid;
        if (locGrid && locGrid._active)
            locGrid.afterDraw(this._node);
    };
})();
