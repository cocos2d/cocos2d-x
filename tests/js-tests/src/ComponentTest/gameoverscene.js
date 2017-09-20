/****************************************************************************
 Copyright (c) 2015-2017 Chukong Technologies Inc.

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

var GameOverLayer = cc.LayerColor.extend({
    
    ctor: function(content) {
        this._super(cc.color(0, 128, 255, 255));
        var label = new cc.LabelTTF(content, "fonts/Marker Felt.ttf", 32);
        label.setColor(cc.color(0, 0, 0));
        label.setPosition(cc.winSize.width/2, cc.winSize.height/2);

        this.addChild(label);
        this.runAction(cc.sequence(cc.delayTime(3), cc.callFunc(this.gameOverDone)));
    },

    gameOverDone: function() {
        cc.director.getEventDispatcher().dispatchCustomEvent("component game over");
    }

});

var GameOverScene = {
    create: function (label) {
        var scene = new cc.Scene();
        var layer = new GameOverLayer(label);
        scene.addChild(layer);

        return scene;
    }
};