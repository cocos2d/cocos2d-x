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
    //SpriteBatchNode's WebGL render command
    cc.SpriteBatchNode.WebGLRenderCmd = function(renderable){
        cc.Node.WebGLRenderCmd.call(this, renderable);
        this._needDraw = true;

        this._textureAtlas = null;
    };

    var proto = cc.SpriteBatchNode.WebGLRenderCmd.prototype = Object.create(cc.Node.WebGLRenderCmd.prototype);
    proto.constructor = cc.SpriteBatchNode.WebGLRenderCmd;

    proto.isValidChild = function(child){
        if (!(child instanceof cc.Sprite)) {
            cc.log(cc._LogInfos.Sprite_addChild_4);
            return false;
        }
        if (child.texture != this.getTexture()) {
            cc.log(cc._LogInfos.Sprite_addChild_5);
            return false;
        }
        return true;
    };

    proto.rendering = function () {
        var node = this._node;
        if (this._textureAtlas.totalQuads === 0)
            return;

        this._shaderProgram.use();
        this._shaderProgram._setUniformForMVPMatrixWithMat4(this._stackMatrix);
        node._arrayMakeObjectsPerformSelector(node._children, cc.Node._stateCallbackType.updateTransform);
        cc.glBlendFunc(node._blendFunc.src, node._blendFunc.dst);

        this._textureAtlas.drawQuads();
    };

    proto.visit = function(parentCmd){
        var node = this._node;
        // quick return if not visible
        if (!node._visible)
            return;

        if (node._parent && node._parent._renderCmd)
            this._curLevel = node._parent._renderCmd._curLevel + 1;

        var currentStack = cc.current_stack;

        //optimize performance for javascript
        currentStack.stack.push(currentStack.top);

        if(!(this._dirtyFlag & cc.Node._dirtyFlags.transformDirty))  //batchNode's transform must update in visit
            this.transform(parentCmd);
        this.updateStatus(parentCmd);                       //because batchNode doesn't visit its children.
        currentStack.top = this._stackMatrix;

        node.sortAllChildren();

        cc.renderer.pushRenderCommand(this);

        this._dirtyFlag = 0;
        //optimize performance for javascript
        currentStack.top = currentStack.stack.pop();
    };

    proto.checkAtlasCapacity = function(index){
        // make needed room
        var locAtlas = this._textureAtlas;
        while (index >= locAtlas.capacity || locAtlas.capacity === locAtlas.totalQuads) {
            this.increaseAtlasCapacity();
        }
    };

    proto.increaseAtlasCapacity = function(){
        // if we're going beyond the current TextureAtlas's capacity,
        // all the previously initialized sprites will need to redo their texture coords
        // this is likely computationally expensive
        var locCapacity = this._textureAtlas.capacity;
        var quantity = Math.floor((locCapacity + 1) * 4 / 3);

        cc.log(cc._LogInfos.SpriteBatchNode_increaseAtlasCapacity, locCapacity, quantity);

        if (!this._textureAtlas.resizeCapacity(quantity)) {
            // serious problems
            cc.log(cc._LogInfos.SpriteBatchNode_increaseAtlasCapacity_2);
        }
    };

    proto.initWithTexture = function(texture, capacity){
        this._textureAtlas = new cc.TextureAtlas();
        this._textureAtlas.initWithTexture(texture, capacity);
        this._updateBlendFunc();
        this._shaderProgram = cc.shaderCache.programForKey(cc.SHADER_POSITION_TEXTURECOLOR);
    };

    proto.insertQuad = function(sprite, index){
        var locTextureAtlas = this._textureAtlas;
        if (locTextureAtlas.totalQuads >= locTextureAtlas.capacity)
            this.increaseAtlasCapacity();
        locTextureAtlas.insertQuad(sprite.quad, index);
    };

    proto.removeQuadAtIndex = function(index){
        this._textureAtlas.removeQuadAtIndex(index);   // remove from TextureAtlas
    };

    proto.getTexture = function(){
        return this._textureAtlas.texture;
    };

    proto.setTexture = function(texture){
        this._textureAtlas.setTexture(texture);
        if(texture)
            this._updateBlendFunc();
    };

    proto.removeAllQuads = function(){
        this._textureAtlas.removeAllQuads();
    };

    proto._swap = function (oldIndex, newIndex) {
        var locDescendants = this._node._descendants;
        var locTextureAtlas = this._textureAtlas;
        var quads = locTextureAtlas.quads;
        var tempItem = locDescendants[oldIndex];
        var tempIteQuad = cc.V3F_C4B_T2F_QuadCopy(quads[oldIndex]);

        //update the index of other swapped item
        locDescendants[newIndex].atlasIndex = oldIndex;
        locDescendants[oldIndex] = locDescendants[newIndex];

        locTextureAtlas.updateQuad(quads[newIndex], oldIndex);
        locDescendants[newIndex] = tempItem;
        locTextureAtlas.updateQuad(tempIteQuad, newIndex);
    };

    proto._updateAtlasIndex = function (sprite, curIndex) {
        var count = 0;
        var pArray = sprite.children;
        if (pArray)
            count = pArray.length;

        var oldIndex = 0;
        if (count === 0) {
            oldIndex = sprite.atlasIndex;
            sprite.atlasIndex = curIndex;
            sprite.arrivalOrder = 0;
            if (oldIndex !== curIndex)
                this._swap(oldIndex, curIndex);
            curIndex++;
        } else {
            var needNewIndex = true;
            if (pArray[0].zIndex >= 0) {
                //all children are in front of the parent
                oldIndex = sprite.atlasIndex;
                sprite.atlasIndex = curIndex;
                sprite.arrivalOrder = 0;
                if (oldIndex !== curIndex)
                    this._swap(oldIndex, curIndex);
                curIndex++;
                needNewIndex = false;
            }
            for (var i = 0; i < pArray.length; i++) {
                var child = pArray[i];
                if (needNewIndex && child.zIndex >= 0) {
                    oldIndex = sprite.atlasIndex;
                    sprite.atlasIndex = curIndex;
                    sprite.arrivalOrder = 0;
                    if (oldIndex !== curIndex) {
                        this._swap(oldIndex, curIndex);
                    }
                    curIndex++;
                    needNewIndex = false;
                }
                curIndex = this._updateAtlasIndex(child, curIndex);
            }

            if (needNewIndex) {
                //all children have a zOrder < 0)
                oldIndex = sprite.atlasIndex;
                sprite.atlasIndex = curIndex;
                sprite.arrivalOrder = 0;
                if (oldIndex !== curIndex) {
                    this._swap(oldIndex, curIndex);
                }
                curIndex++;
            }
        }
        return curIndex;
    };

    proto.updateChildrenAtlasIndex = function(children){
        var index = 0;
        //fast dispatch, give every child a new atlasIndex based on their relative zOrder (keep parent -> child relations intact)
        // and at the same time reorder descedants and the quads to the right index
        for (var i = 0; i < children.length; i++)
            index = this._updateAtlasIndex(children[i], index);
    };

    proto._updateBlendFunc = function () {
        if (!this._textureAtlas.texture.hasPremultipliedAlpha()) {
            var blendFunc = this._node._blendFunc;
            blendFunc.src = cc.SRC_ALPHA;
            blendFunc.dst = cc.ONE_MINUS_SRC_ALPHA;
        }
    };

    proto.getTextureAtlas = function(){
        return this._textureAtlas;
    };

    proto.setTextureAtlas = function(textureAtlas){
        if (textureAtlas !== this._textureAtlas) {
            this._textureAtlas = textureAtlas;
        }
    };

    proto.cutting = function(){};
})();
