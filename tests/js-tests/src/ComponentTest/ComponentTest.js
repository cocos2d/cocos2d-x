/****************************************************************************
 Copyright (c) 2015 Chukong Technologies Inc.

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

var ComponentTestLayer = cc.Layer.extend({

    ctor:function () {
        this._super();

        // set background color
        var bgLayer = new cc.LayerColor(cc.color(0, 128, 255, 255));
        this.addChild(bgLayer);

        // create game scene
        var sceneJSComponent = new cc.ComponentJS("src/ComponentTest/scene.js");
        sceneJSComponent.setName("sceneJSComponent");
        this.addComponent(sceneJSComponent);

        // add player
        var player = new cc.Sprite("components/Player.png", cc.rect(0, 0, 27, 40));
        var visibleSize = cc.director.getVisibleSize();
        var origin = cc.director.getVisibleOrigin();
        player.setPosition(origin.x + player.getContentSize().width/2,
                           origin.y + visibleSize.height/2);
        var playerComponent = new cc.ComponentJS("src/ComponentTest/player.js");
        player.addComponent(playerComponent);
        this.addChild(player);

        cc.eventManager.addListener({
            event: cc.EventListener.CUSTOM,
            eventName: "component game over",
            callback: this.onEvent
        }, 1);
    },

    onEvent: function(event) {
        jsb.AudioEngine.stopAll();
        var scene = new ComponentTestScene();
        scene.runThisTest();
    },
    onExit: function () {
        jsb.AudioEngine.stopAll();
        this._super();
    }
});

var ComponentTestScene = TestScene.extend({
    runThisTest:function () {
        var layer = new ComponentTestLayer();
        this.addChild(layer);

        cc.director.runScene(this);
    }
});
