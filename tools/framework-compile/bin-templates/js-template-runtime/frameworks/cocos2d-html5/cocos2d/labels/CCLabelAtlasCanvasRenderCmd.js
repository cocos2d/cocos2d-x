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
    cc.LabelAtlas.CanvasRenderCmd = function(renderableObject){
        cc.AtlasNode.CanvasRenderCmd.call(this, renderableObject);
        this._needDraw = false;
    };

    var proto = cc.LabelAtlas.CanvasRenderCmd.prototype = Object.create(cc.AtlasNode.CanvasRenderCmd.prototype);
    proto.constructor = cc.LabelAtlas.CanvasRenderCmd;

    proto.setCascade = function(){
        var node = this._node;
        node._cascadeOpacityEnabled = true;
        node._cascadeColorEnabled = false;
    };

    proto.updateAtlasValues = function(){
        var node = this._node;
        var locString = node._string || "";
        var n = locString.length;
        var texture = this._texture;
        var locItemWidth = node._itemWidth , locItemHeight = node._itemHeight;     //needn't multiply cc.contentScaleFactor(), because sprite's draw will do this

        for (var i = 0; i < n; i++) {
            var a = locString.charCodeAt(i) - node._mapStartChar.charCodeAt(0);
            var row = parseInt(a % node._itemsPerRow, 10);
            var col = parseInt(a / node._itemsPerRow, 10);

            var rect = cc.rect(row * locItemWidth, col * locItemHeight, locItemWidth, locItemHeight);
            var c = locString.charCodeAt(i);
            var fontChar = node.getChildByTag(i);
            if (!fontChar) {
                fontChar = new cc.Sprite();
                if (c === 32) {
                    fontChar.init();
                    fontChar.setTextureRect(cc.rect(0, 0, 10, 10), false, cc.size(0, 0));
                } else
                    fontChar.initWithTexture(texture, rect);

                cc.Node.prototype.addChild.call(node, fontChar, 0, i);
            } else {
                if (c === 32) {
                    fontChar.init();
                    fontChar.setTextureRect(cc.rect(0, 0, 10, 10), false, cc.size(0, 0));
                } else {
                    // reusing fonts
                    fontChar.initWithTexture(texture, rect);
                    // restore to default in case they were modified
                    fontChar.visible = true;
                }
            }
            fontChar.setPosition(i * locItemWidth + locItemWidth / 2, locItemHeight / 2);
        }
    };

    proto.setString = function(label){
        var node = this._node;
        if (node._children) {
            var locChildren = node._children;
            var len = locChildren.length;
            for (var i = 0; i < len; i++) {
                var child = locChildren[i];
                if (child && !child._lateChild)
                    child.visible = false;
            }
        }
    };

    proto._addChild = function(){
        child._lateChild = true;
    };
})();