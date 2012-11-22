/****************************************************************************
 Copyright (c) 2010-2012 cocos2d-x.org
 Copyright (c) 2008-2010 Ricardo Quesada
 Copyright (c) 2011      Zynga Inc.

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

var MID_PUSHSCENE = 100;
var MID_PUSHSCENETRAN = 101;
var MID_QUIT = 102;
var MID_REPLACESCENE = 103;
var MID_REPLACESCENETRAN = 104;
var MID_GOBACK = 105;

SceneTestLayer1 = cc.Layer.extend({

    ctor:function () {
        var s = cc.Director.getInstance().getWinSize();
        var item1 = cc.MenuItemFont.create("Test pushScene", this, this.onPushScene);
        var item2 = cc.MenuItemFont.create("Test pushScene w/transition", this, this.onPushSceneTran);
        var item3 = cc.MenuItemFont.create("Quit", this, function () {
            alert("quit")
        });

        var menu = cc.Menu.create(item1, item2, item3);
        menu.alignItemsVertically();
        this.addChild(menu);

        var sprite = cc.Sprite.create(s_pathGrossini);
        this.addChild(sprite);
        sprite.setPosition(cc.p(s.width - 40, s.height / 2));
        var rotate = cc.RotateBy.create(2, 360);
        var repeat = cc.RepeatForever.create(rotate);
        sprite.runAction(repeat);
        this._super();
        //cc.schedule(this.testDealloc);
    },


    onEnter:function () {
        cc.log("SceneTestLayer1#onEnter");
        this._super();
    },

    onEnterTransitionDidFinish:function () {
        cc.log("SceneTestLayer1#onEnterTransitionDidFinish");
        this._super();
    },

    testDealloc:function (dt) {
        //cc.log("SceneTestLayer1:testDealloc");
    },

    onPushScene:function (sender) {
        var scene = new SceneTestScene();
        var layer = new SceneTestLayer2();
        scene.addChild(layer, 0);
        cc.Director.getInstance().pushScene(scene);
    },

    onPushSceneTran:function (sender) {
        var scene = new SceneTestScene();
        var layer = new SceneTestLayer2();
        scene.addChild(layer, 0);

        cc.Director.getInstance().pushScene(cc.TransitionSlideInT.create(1, scene));
    },
    onQuit:function (sender) {

    }

    //CREATE_NODE(SceneTestLayer1);
});

SceneTestLayer2 = cc.Layer.extend({

    timeCounter:0,

    ctor:function () {
        this.timeCounter = 0;

        var s = cc.Director.getInstance().getWinSize();

        var item1 = cc.MenuItemFont.create("replaceScene", this, this.onReplaceScene);
        var item2 = cc.MenuItemFont.create("replaceScene w/transition", this, this.onReplaceSceneTran);
        var item3 = cc.MenuItemFont.create("Go Back", this, this.onGoBack);

        var menu = cc.Menu.create(item1, item2, item3, null);
        menu.alignItemsVertically();
        this.addChild(menu);

        var sprite = cc.Sprite.create(s_pathGrossini);
        this.addChild(sprite);

        sprite.setPosition(cc.p(s.width - 40, s.height / 2));
        var rotate = cc.RotateBy.create(2, 360);
        var repeat = cc.RepeatForever.create(rotate);
        sprite.runAction(repeat);

        //cc.schedule(this.testDealloc);
        this._super();


    },

    testDealloc:function (dt) {

    },

    onGoBack:function (sender) {
        cc.Director.getInstance().popScene();
    },

    onReplaceScene:function (sender) {
        var scene = new SceneTestScene();
        var layer = new SceneTestLayer3();
        scene.addChild(layer, 0);
        cc.Director.getInstance().replaceScene(scene);

    },

    onReplaceSceneTran:function (sender) {
        var scene = new SceneTestScene();
        var layer = new SceneTestLayer3();
        scene.addChild(layer, 0);
        cc.Director.getInstance().replaceScene(cc.TransitionSlideInT.create(2, scene));

    }

    //CREATE_NODE(SceneTestLayer2);
});

SceneTestLayer3 = cc.LayerColor.extend({


    ctor:function () {
        this._super();
        this.setTouchEnabled(true);
        var label = cc.LabelTTF.create("Touch to popScene", "Arial", 28);
        this.addChild(label);
        var s = cc.Director.getInstance().getWinSize();
        label.setPosition(cc.p(s.width / 2, s.height / 2));

        var sprite = cc.Sprite.create(s_pathGrossini);
        this.addChild(sprite);

        sprite.setPosition(cc.p(s.width - 40, s.height / 2));
        var rotate = cc.RotateBy.create(2, 360);
        var repeat = cc.RepeatForever.create(rotate);
        sprite.runAction(repeat);
    },

    testDealloc:function (dt) {

    },

    onTouchesEnded:function (touches, event) {
        cc.Director.getInstance().popScene();
    }

    //CREATE_NODE(SceneTestLayer3);
});

SceneTestScene = TestScene.extend({

    runThisTest:function () {
        var layer = new SceneTestLayer1();
        this.addChild(layer);

        cc.Director.getInstance().replaceScene(this);

    }
});
