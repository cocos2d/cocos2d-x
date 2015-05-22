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

/**
 * A batchNode to Armature
 * @class ccs.BatchNode
 * @extends cc.Node
 */
ccs.BatchNode = cc.Node.extend(/** @lends ccs.BatchNode# */{
    _atlas:null,
    _className:"BatchNode",

    ctor:function () {
        this._atlas = null;

        ccs.BatchNode.prototype.init.call(this);
    },

    init:function () {
        var ret = cc.Node.prototype.init.call(this);
        this.setShaderProgram(cc.shaderCache.programForKey(cc.SHADER_POSITION_TEXTURE_UCOLOR));
        return ret;
    },

    addChild:function (child, zOrder, tag) {
        cc.Node.prototype.addChild.call(this, child, zOrder, tag);
        if (child instanceof cc.Armature){
            child.setBatchNode(this);
        }
    },

    removeChild: function(child, cleanup){
        if (child instanceof cc.Armature)
            child.setBatchNode(null);
        cc.Node.prototype.removeChild.call(this, child, cleanup);
    },

    visit:function (renderer, parentTransform, parentTransformUpdated) {
        // quick return if not visible. children won't be drawn.
        if (!this._visible)
            return;

        var dirty = parentTransformUpdated || this._transformUpdated;
        if(dirty)
            this._modelViewTransform = this.transform(parentTransform);
        this._transformUpdated = false;

        // IMPORTANT:
        // To ease the migration to v3.0, we still support the kmGL stack,
        // but it is deprecated and your code should not rely on it
        cc.kmGLPushMatrixWitMat4(this._stackMatrix);

        if (this.grid && this.grid.isActive())
            this.grid.beforeDraw();

        this.sortAllChildren();
        this.draw(renderer, this._modelViewTransform, dirty);

        if (this.grid && this.grid.isActive())
            this.grid.afterDraw(this);

        cc.kmGLPopMatrix();
    },

    draw:function (renderer, transform, transformUpdated) {
        var locChildren = this._children;
        if(locChildren.length === 0)
            return;

        var child = null;
        for (var i = 0, len = locChildren.length; i < len; i++) {
            child = locChildren[i];
            child.visit();
            if (child instanceof cc.Armature) {
                this._atlas = child.getTextureAtlas();
            }
        }
        if (this._atlas) {
            this._atlas.drawQuads();
            this._atlas.removeAllQuads();
        }
    }
});

/**
 *
 * @returns {ccs.BatchNode}
 * @deprecated since v3.1, please use new construction instead
 */
ccs.BatchNode.create = function () {
    return new ccs.BatchNode();
};