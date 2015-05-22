/****************************************************************************
 Copyright (c) 2008-2010 Ricardo Quesada
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
 * <p>NodeGrid class is a class serves as a decorator of cc.Node,<br/>
 * Grid node can run grid actions over all its children   (WebGL only)
 * </p>
 * @type {Class}
 *
 * @property {cc.GridBase}  grid    - Grid object that is used when applying effects
 * @property {cc.Node}      target  - <@writeonly>Target
 */
cc.NodeGrid = cc.Node.extend({
    grid: null,
    _target: null,

    /**
     * Gets the grid object.
     * @returns {cc.GridBase}
     */
    getGrid: function () {
        return this.grid;
    },

    /**
     * Set the grid object.
     * @param {cc.GridBase} grid
     */
    setGrid: function (grid) {
        this.grid = grid;
    },

    /**
     * Set the target
     * @param {cc.Node} target
     */
    setTarget: function (target) {
        this._target = target;
    },

    _transformForWebGL: function () {
        //optimize performance for javascript
        var t4x4 = this._transform4x4, topMat4 = cc.current_stack.top;

        // Convert 3x3 into 4x4 matrix
        var trans = this.getNodeToParentTransform();
        var t4x4Mat = t4x4.mat;
        t4x4Mat[0] = trans.a;
        t4x4Mat[4] = trans.c;
        t4x4Mat[12] = trans.tx;
        t4x4Mat[1] = trans.b;
        t4x4Mat[5] = trans.d;
        t4x4Mat[13] = trans.ty;

        // Update Z vertex manually
        //this._transform4x4.mat[14] = this._vertexZ;
        t4x4Mat[14] = this._vertexZ;

        //optimize performance for Javascript
        topMat4.multiply(t4x4) ; // = cc.kmGLMultMatrix(this._transform4x4);

        // XXX: Expensive calls. Camera should be integrated into the cached affine matrix
        if (this._camera !== null && !(this.grid && this.grid.isActive())) {
            var app = this._renderCmd._anchorPointInPoints,
                apx = app.x, apy = app.y,
                translate = (apx !== 0.0 || apy !== 0.0);
            if (translate) {
                if(!cc.SPRITEBATCHNODE_RENDER_SUBPIXEL) {
                    apx = 0 | apx;
                    apy = 0 | apy;
                }
                cc.kmGLTranslatef(apx, apy, 0);
                this._camera.locate();
                cc.kmGLTranslatef(-apx, -apy, 0);
            } else {
                this._camera.locate();
            }
        }
    },

    _createRenderCmd: function(){
        if (cc._renderType === cc._RENDER_TYPE_WEBGL)
            return new cc.NodeGrid.WebGLRenderCmd(this);
        else
            return new cc.Node.CanvasRenderCmd(this);            // cc.NodeGrid doesn't support Canvas mode.
    }
});

var _p = cc.NodeGrid.prototype;
// Extended property
/** @expose */
_p.grid;
/** @expose */
_p.target;
cc.defineGetterSetter(_p, "target", null, _p.setTarget);


/**
 * Creates a NodeGrid. <br />
 * Implementation cc.NodeGrid
 * @deprecated since v3.0 please new cc.NodeGrid instead.
 * @return {cc.NodeGrid}
 */
cc.NodeGrid.create = function () {
    return new cc.NodeGrid();
};