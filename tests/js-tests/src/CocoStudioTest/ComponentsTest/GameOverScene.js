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

var GameOverLayer = cc.LayerColor.extend({
    _label: null,
    init: function () {
        if (this._super(cc.color(255, 255, 255, 255))) {
            var winSize = cc.director.getWinSize();
            this._label = new cc.LabelTTF("", "Artial", 32);
            this._label.retain();
            this._label.color = cc.color(0, 0, 0);
            this._label.x = winSize.width / 2;
            this._label.y = winSize.height / 2;
            this.addChild(this._label);
            this.runAction(cc.sequence(cc.delayTime(3), cc.callFunc(this.gameOverDone, this)));
            var itemBack = new cc.MenuItemFont("Back", this.toExtensionsMainLayer, this);
            itemBack.color = cc.color(0, 0, 0);
            itemBack.x = cc.visibleRect.bottomRight.x - 50;
            itemBack.y = cc.visibleRect.bottomRight.y + 25;
            var menuBack = new cc.Menu(itemBack);
            menuBack.x = 0;
            menuBack.y = 0;
            this.addChild(menuBack);
            return true;
        }
        return false;
    },
    gameOverDone: function () {
        cc.director.runScene(ComponentsTestLayer.scene());
    },
    getLabel: function () {
        return this._label;
    }
});
var GameOverScene = cc.Scene.extend({
    _layer: null,
    init: function () {
        this._super();
        this._layer = new GameOverLayer();
        this._layer.init();
        this.addChild(this._layer);
    },
    getLayer: function () {
        return this._layer;
    }
});
GameOverScene.create = function () {
    var scene = new GameOverScene();
    scene.init();
    return scene;
};
