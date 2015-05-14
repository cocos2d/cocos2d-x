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
    cc.ProtectedNode.RenderCmd = {
        _updateDisplayColor: function (parentColor) {
            var node = this._node;
            var locDispColor = this._displayedColor, locRealColor = node._realColor;
            var i, len, selChildren, item;
            if (this._cascadeColorEnabledDirty && !node._cascadeColorEnabled) {
                locDispColor.r = locRealColor.r;
                locDispColor.g = locRealColor.g;
                locDispColor.b = locRealColor.b;
                var whiteColor = new cc.Color(255, 255, 255, 255);
                selChildren = node._children;
                for (i = 0, len = selChildren.length; i < len; i++) {
                    item = selChildren[i];
                    if (item && item._renderCmd)
                        item._renderCmd._updateDisplayColor(whiteColor);
                }
                this._cascadeColorEnabledDirty = false;
            } else {
                if (parentColor === undefined) {
                    var locParent = node._parent;
                    if (locParent && locParent._cascadeColorEnabled)
                        parentColor = locParent.getDisplayedColor();
                    else
                        parentColor = cc.color.WHITE;
                }
                locDispColor.r = 0 | (locRealColor.r * parentColor.r / 255.0);
                locDispColor.g = 0 | (locRealColor.g * parentColor.g / 255.0);
                locDispColor.b = 0 | (locRealColor.b * parentColor.b / 255.0);
                if (node._cascadeColorEnabled) {
                    selChildren = node._children;
                    for (i = 0, len = selChildren.length; i < len; i++) {
                        item = selChildren[i];
                        if (item && item._renderCmd){
                            item._renderCmd._updateDisplayColor(locDispColor);
                            item._renderCmd._updateColor();
                        }
                    }
                }
                selChildren = node._protectedChildren;
                for(i = 0, len = selChildren.length;i < len; i++){
                    item = selChildren[i];
                    if(item && item._renderCmd){
                        item._renderCmd._updateDisplayColor(locDispColor);
                        item._renderCmd._updateColor();
                    }
                }
            }
            this._dirtyFlag = this._dirtyFlag & cc.Node._dirtyFlags.colorDirty ^ this._dirtyFlag;
        },

        _updateDisplayOpacity: function (parentOpacity) {
            var node = this._node;
            var i, len, selChildren, item;
            if (this._cascadeOpacityEnabledDirty && !node._cascadeOpacityEnabled) {
                this._displayedOpacity = node._realOpacity;
                selChildren = node._children;
                for (i = 0, len = selChildren.length; i < len; i++) {
                    item = selChildren[i];
                    if (item && item._renderCmd)
                        item._renderCmd._updateDisplayOpacity(255);
                }
                this._cascadeOpacityEnabledDirty = false;
            } else {
                if (parentOpacity === undefined) {
                    var locParent = node._parent;
                    parentOpacity = 255;
                    if (locParent && locParent._cascadeOpacityEnabled)
                        parentOpacity = locParent.getDisplayedOpacity();
                }
                this._displayedOpacity = node._realOpacity * parentOpacity / 255.0;
                if (node._cascadeOpacityEnabled) {
                    selChildren = node._children;
                    for (i = 0, len = selChildren.length; i < len; i++) {
                        item = selChildren[i];
                        if (item && item._renderCmd){
                            item._renderCmd._updateDisplayOpacity(this._displayedOpacity);
                            item._renderCmd._updateColor();
                        }
                    }
                }
                selChildren = node._protectedChildren;
                for(i = 0, len = selChildren.length;i < len; i++){
                    item = selChildren[i];
                    if(item && item._renderCmd){
                        item._renderCmd._updateDisplayOpacity(this._displayedOpacity);
                        item._renderCmd._updateColor();
                    }
                }
            }
            this._dirtyFlag = this._dirtyFlag & cc.Node._dirtyFlags.opacityDirty ^ this._dirtyFlag;
        },

        _changeProtectedChild: function (child) {
            var cmd = child._renderCmd,
                dirty = cmd._dirtyFlag,
                flags = cc.Node._dirtyFlags;

            if (this._dirtyFlag & flags.colorDirty)
                dirty |= flags.colorDirty;

            if (this._dirtyFlag & flags.opacityDirty)
                dirty |= flags.opacityDirty;

            var colorDirty = dirty & flags.colorDirty,
                opacityDirty = dirty & flags.opacityDirty;

            if (colorDirty)
                cmd._updateDisplayColor(this._displayedColor);
            if (opacityDirty)
                cmd._updateDisplayOpacity(this._displayedOpacity);
            if (colorDirty || opacityDirty)
                cmd._updateColor();
        }
    };

    cc.ProtectedNode.CanvasRenderCmd = function (renderable) {
        cc.Node.CanvasRenderCmd.call(this, renderable);
        this._cachedParent = null;
        this._cacheDirty = false;
    };

    var proto = cc.ProtectedNode.CanvasRenderCmd.prototype = Object.create(cc.Node.CanvasRenderCmd.prototype);
    cc.inject(cc.ProtectedNode.RenderCmd, proto);
    proto.constructor = cc.ProtectedNode.CanvasRenderCmd;

    proto.visit = function(parentCmd){
        var node = this._node;
        // quick return if not visible
        if (!node._visible)
            return;

        //visit for canvas
        var i, j;
        var children = node._children, child;
        var locChildren = node._children, locProtectedChildren = node._protectedChildren;
        var childLen = locChildren.length, pLen = locProtectedChildren.length;

        this._syncStatus(parentCmd);

        node.sortAllChildren();
        node.sortAllProtectedChildren();

        var pChild;
        // draw children zOrder < 0
        for (i = 0; i < childLen; i++) {
            child = children[i];
            if (child._localZOrder < 0)
                child.visit(this);
            else
                break;
        }
        for (j = 0; j < pLen; j++) {
            pChild = locProtectedChildren[j];
            if (pChild && pChild._localZOrder < 0){
                this._changeProtectedChild(pChild);
                pChild.visit(this);
            }
            else
                break;
        }

        cc.renderer.pushRenderCommand(this);

        for (; i < childLen; i++)
            children[i] && children[i].visit(this);
        for (; j < pLen; j++){
            pChild = locProtectedChildren[j];
            if(!pChild) continue;
            this._changeProtectedChild(pChild);
            pChild.visit(this);
        }

        this._dirtyFlag = 0;
        this._cacheDirty = false;
    };

    proto.transform = function(parentCmd, recursive){
        var node = this._node;

        if(node._changePosition)
            node._changePosition();

        var t = node.getNodeToParentTransform(), worldT = this._worldTransform;
        if (parentCmd) {
            var pt = parentCmd._worldTransform;
            // cc.AffineTransformConcat is incorrect at get world transform
            worldT.a = t.a * pt.a + t.b * pt.c;                               //a
            worldT.b = t.a * pt.b + t.b * pt.d;                               //b
            worldT.c = t.c * pt.a + t.d * pt.c;                               //c
            worldT.d = t.c * pt.b + t.d * pt.d;                               //d

            worldT.tx = pt.a * t.tx + pt.c * t.ty + pt.tx;
            worldT.ty = pt.d * t.ty + pt.ty + pt.b * t.tx;
        } else {
            worldT.a = t.a;
            worldT.b = t.b;
            worldT.c = t.c;
            worldT.d = t.d;
            worldT.tx = t.tx;
            worldT.ty = t.ty;
        }
        var i, len, locChildren = node._children;
        if(recursive && locChildren && locChildren.length !== 0){
            for(i = 0, len = locChildren.length; i< len; i++){
                locChildren[i]._renderCmd.transform(this, recursive);
            }
        }
        locChildren = node._protectedChildren;
        if(recursive && locChildren && locChildren.length !== 0){
            for(i = 0, len = locChildren.length; i< len; i++){
                locChildren[i]._renderCmd.transform(this, recursive);
            }
        }
    };
})();