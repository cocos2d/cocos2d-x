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

cc.rendererWebGL = {
    childrenOrderDirty: true,
    _transformNodePool: [],                              //save nodes transform dirty
    _renderCmds: [],                                     //save renderer commands

    _isCacheToBufferOn: false,                          //a switch that whether cache the rendererCmd to cacheToCanvasCmds
    _cacheToBufferCmds: {},                              // an array saves the renderer commands need for cache to other canvas
    _cacheInstanceIds: [],
    _currentID: 0,

    getRenderCmd: function (renderableObject) {
        //TODO Add renderCmd pool here
        return renderableObject._createRenderCmd();
    },

    /**
     * drawing all renderer command to context (default is cc._renderContext)
     * @param {WebGLRenderingContext} [ctx=cc._renderContext]
     */
    rendering: function (ctx) {
        var locCmds = this._renderCmds,
            i,
            len;
        var context = ctx || cc._renderContext;
        for (i = 0, len = locCmds.length; i < len; i++) {
            locCmds[i].rendering(context);
        }
    },

    _turnToCacheMode: function (renderTextureID) {
        this._isCacheToBufferOn = true;
        renderTextureID = renderTextureID || 0;
        this._cacheToBufferCmds[renderTextureID] = [];
        this._cacheInstanceIds.push(renderTextureID);
        this._currentID = renderTextureID;
    },

    _turnToNormalMode: function () {
        this._isCacheToBufferOn = false;
    },

    /**
     * drawing all renderer command to cache canvas' context
     * @param {Number} [renderTextureId]
     */
    _renderingToBuffer: function (renderTextureId) {
        renderTextureId = renderTextureId || this._currentID;
        var locCmds = this._cacheToBufferCmds[renderTextureId], i, len;
        var ctx = cc._renderContext, locIDs = this._cacheInstanceIds;
        for (i = 0, len = locCmds.length; i < len; i++) {
            locCmds[i].rendering(ctx);
        }
        locCmds.length = 0;
        delete this._cacheToBufferCmds[renderTextureId];
        cc.arrayRemoveObject(locIDs, renderTextureId);

        if (locIDs.length === 0)
            this._isCacheToBufferOn = false;
        else
            this._currentID = locIDs[locIDs.length - 1];
    },

    //reset renderer's flag
    resetFlag: function () {
        this.childrenOrderDirty = false;
        this._transformNodePool.length = 0;
    },

    //update the transform data
    transform: function () {
        var locPool = this._transformNodePool;
        //sort the pool
        locPool.sort(this._sortNodeByLevelAsc);
        //transform node
        for (var i = 0, len = locPool.length; i < len; i++) {
             locPool[i].updateStatus();
        }
        locPool.length = 0;
    },

    transformDirty: function () {
        return this._transformNodePool.length > 0;
    },

    _sortNodeByLevelAsc: function (n1, n2) {
        return n1._curLevel - n2._curLevel;
    },

    pushDirtyNode: function (node) {
        //if (this._transformNodePool.indexOf(node) === -1)
        this._transformNodePool.push(node);
    },

    clearRenderCommands: function () {
        this._renderCmds.length = 0;
    },

    pushRenderCommand: function (cmd) {
        if(!cmd._needDraw)
            return;
        if (this._isCacheToBufferOn) {
            var currentId = this._currentID, locCmdBuffer = this._cacheToBufferCmds;
            var cmdList = locCmdBuffer[currentId];
            if (cmdList.indexOf(cmd) === -1)
                cmdList.push(cmd);
        } else {
            if (this._renderCmds.indexOf(cmd) === -1)
                this._renderCmds.push(cmd);
        }
    }
};
if (cc._renderType === cc._RENDER_TYPE_WEBGL)
    cc.renderer = cc.rendererWebGL;
