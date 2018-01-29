/****************************************************************************
 Copyright (c) 2008-2010 Ricardo Quesada
 Copyright (c) 2011-2012 cocos2d-x.org
 Copyright (c) 2013-2016 Chukong Technologies Inc.
 Copyright (c) 2017-2018 Xiamen Yaji Software Co., Ltd.

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
var MID_runScene = 103;
var MID_runSceneTRAN = 104;
var MID_GOBACK = 105;

var SceneTestLayer1 = cc.Layer.extend({
    ctor:function () {
        //----start0----Scene1-ctor
        this._super();
        this.init();

        var s = director.getWinSize();
        var item1 = new cc.MenuItemFont("Test pushScene", this.onPushScene, this);
        var item2 = new cc.MenuItemFont("Test pushScene w/transition", this.onPushSceneTran, this);
        var item3 = new cc.MenuItemFont("Quit", function () {
            cc.log("quit!");
        }, this);
        var item4 = new cc.MenuItemFont("setNotificationNode", function () {
            var layerTemp = new cc.LayerColor(cc.color(0, 255, 255, 120));
            var sprite = new cc.Sprite(s_pathGrossini);
            sprite.setPosition(cc.p(winSize.width/2,winSize.height/2));
            layerTemp.addChild(sprite);
            cc.director.setNotificationNode(layerTemp);
            var rotation = cc.rotateBy(2,360);
            sprite.runAction(rotation.repeatForever());
            cc.log("setNotificationNode!");
        }, this);
        var item5 = new cc.MenuItemFont("clearNotificationNode", function () {
            cc.log("clearNotificationNode!");
            cc.director.setNotificationNode(null);
        }, this);

        var menu = new cc.Menu(item1, item2, item3, item4, item5);
        menu.alignItemsVertically();
        this.addChild(menu);

        var sprite = new cc.Sprite(s_pathGrossini);
        this.addChild(sprite);
        sprite.x = s.width - 40;
        sprite.y = s.height / 2;
        var rotate = cc.rotateBy(2, 360);
        var repeat = rotate.repeatForever();
        sprite.runAction(repeat);
        //----end0----

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
        director.pushScene(scene);
    },

    onPushSceneTran:function (sender) {
        var scene = new SceneTestScene();
        var layer = new SceneTestLayer2();
        scene.addChild(layer, 0);

        director.pushScene(new cc.TransitionSlideInT(1, scene));
    },
    onExit:function (sender) {
        cc.director.setNotificationNode(null);
        this._super();
    }

    //CREATE_NODE(SceneTestLayer1);
});

var SceneTestLayer2 = cc.Layer.extend({

    timeCounter:0,

    ctor:function () {
        //----start0----Scene2-ctor
        this._super();
        this.init();

        this.timeCounter = 0;

        var s = director.getWinSize();

        var item1 = new cc.MenuItemFont("runScene", this.runScene, this);
        var item2 = new cc.MenuItemFont("runScene w/transition", this.runSceneTran, this);
        var item3 = new cc.MenuItemFont("Go Back", this.onGoBack, this);

        var menu = new cc.Menu(item1, item2, item3);
        menu.alignItemsVertically();
        this.addChild(menu);

        var sprite = new cc.Sprite(s_pathGrossini);
        this.addChild(sprite);

        sprite.x = s.width - 40;
        sprite.y = s.height / 2;
        var rotate = cc.rotateBy(2, 360);
        var repeat = rotate.repeatForever();
        sprite.runAction(repeat);
        //----end0----

        //cc.schedule(this.testDealloc);
    },

    testDealloc:function (dt) {

    },

    onGoBack:function (sender) {
        director.popScene();
    },

    runScene:function (sender) {
        var scene = new SceneTestScene();
        var layer = new SceneTestLayer3();
        scene.addChild(layer, 0);
        director.runScene(scene);

    },

    runSceneTran:function (sender) {
        var scene = new SceneTestScene();
        var layer = new SceneTestLayer3();
        scene.addChild(layer, 0);
        director.runScene(new cc.TransitionSlideInT(2, scene));
    }

    //CREATE_NODE(SceneTestLayer2);
});

var SceneTestLayer3 = cc.LayerColor.extend({
    
    ctor:function () {

        //----start0----Scene3-ctor
        this._super();
        this.init( cc.color(0,128,255,255) );

        var label = new cc.LabelTTF("Touch to popScene", "Arial", 28);
        this.addChild(label);
        var s = director.getWinSize();
        label.x = s.width / 2;
        label.y = s.height / 2;

        var sprite = new cc.Sprite(s_pathGrossini);
        this.addChild(sprite);

        sprite.x = s.width - 40;

        sprite.y = s.height / 2;
        var rotate = cc.rotateBy(2, 360);
        var repeat = rotate.repeatForever();
        sprite.runAction(repeat);
        //----end0----
    },
    
    onEnterTransitionDidFinish: function () {
        if ('touches' in cc.sys.capabilities){
            cc.eventManager.addListener({
                event: cc.EventListener.TOUCH_ALL_AT_ONCE,
                onTouchesEnded: function(touches, event){
                    director.popScene();
                }
            }, this);
        } else if ('mouse' in cc.sys.capabilities)
            cc.eventManager.addListener({
                event: cc.EventListener.MOUSE,
                onMouseUp: function(event){
                    director.popScene();
                }
            }, this);
    },

    testDealloc:function (dt) {

    }

    //CREATE_NODE(SceneTestLayer3);
});

SceneTestScene = TestScene.extend({

    runThisTest:function () {
        var layer = new SceneTestLayer1();
        this.addChild(layer);

        director.runScene(this);

    }
});

var arrayOfSceneTest = [
    SceneTestLayer1
];
