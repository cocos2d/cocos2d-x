/****************************************************************************
 Copyright (c) 2008-2010 Ricardo Quesada
 Copyright (c) 2011-2012 cocos2d-x.org
 Copyright (c) 2013-2014 Chukong Technologies Inc.
 Copyright (c) 2008-2009 Jason Booth

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

var TAG_LABEL = 1;
var TAG_SPRITE1 = 2;
var TAG_SPRITE2 = 3;

var sceneIdx = -1;

var MotionStreakTest = cc.Layer.extend({
    _streak:null,

    title:function () {
        return "No title";
    },
    subtitle:function () {
        return "";
    },

    onEnter:function () {
        this._super();

        var winSize = cc.director.getWinSize();

        var label = new cc.LabelTTF(this.title(), "Arial", 32);
        this.addChild(label, 0, TAG_LABEL);
        label.x = winSize.width / 2;
        label.y = winSize.height - 50;

        var subTitle = this.subtitle();
        if (subTitle.length > 0) {
            var l = new cc.LabelTTF(subTitle, "Arial", 16);
            this.addChild(l, 1);
            l.x = winSize.width / 2;
            l.y = winSize.height - 80;
        }

        var item1 = new cc.MenuItemImage(s_pathB1, s_pathB2, this.backCallback, this);
        var item2 = new cc.MenuItemImage(s_pathR1, s_pathR2, this.restartCallback, this);
        var item3 = new cc.MenuItemImage(s_pathF1, s_pathF2, this.nextCallback, this);

        var menu = new cc.Menu(item1, item2, item3);

        menu.x = 0;
        menu.y = 0;
        item1.x = cc.visibleRect.center.x - item2.width * 2;
        item1.y = cc.visibleRect.bottom.y + item2.height / 2;
        item2.x = cc.visibleRect.center.x;
        item2.y = cc.visibleRect.bottom.y + item2.height / 2;
        item3.x = cc.visibleRect.center.x + item2.width * 2;
        item3.y = cc.visibleRect.bottom.y + item2.height / 2;

        this.addChild(menu, 1);

        var itemMode = new cc.MenuItemToggle(new cc.MenuItemFont("Use High Quality Mode"),
            new cc.MenuItemFont("Use Fast Mode"), this.modeCallback, this);

        var menuMode = new cc.Menu(itemMode);
        this.addChild(menuMode);

        menuMode.x = winSize.width / 2;
        menuMode.y = winSize.height / 4;
    },

    restartCallback:function (sender) {
        var scene = new MotionStreakTestScene();
        scene.addChild(restartMotionAction());
        cc.director.runScene(scene);
    },

    nextCallback:function (sender) {
        var scene = new MotionStreakTestScene();
        scene.addChild(nextMotionAction());
        cc.director.runScene(scene);
    },

    backCallback:function (sender) {
        var scene = new MotionStreakTestScene;
        scene.addChild(backMotionAction());
        cc.director.runScene(scene);
    },

    modeCallback:function (sender) {
        var fastMode = this._streak.fastMode;
        this._streak.fastMode = !fastMode;
    }
});

var MotionStreakTest1 = MotionStreakTest.extend({
    _root:null,
    _target:null,

    onEnter:function () {
        this._super();

        var winSize = cc.director.getWinSize();
        // the root object just rotates around
        this._root = new cc.Sprite(s_pathR1);
        this.addChild(this._root, 1);
        this._root.x = winSize.width / 2;
        this._root.y = winSize.height / 2;

        // the target object is offset from root, and the streak is moved to follow it
        this._target = new cc.Sprite(s_pathR1);
        this._root.addChild(this._target);
        this._target.x = winSize.width / 4;
        this._target.y = 0;

        // create the streak object and add it to the scene
        this._streak = new cc.MotionStreak(2, 3, 32, cc.color.GREEN, s_streak);
        this.addChild(this._streak);
        // schedule an update on each frame so we can syncronize the streak with the target
        this.schedule(this.onUpdate);

        var a1 = cc.rotateBy(2, 360);

        var action1 = a1.repeatForever();
        var motion = cc.moveBy(2, cc.p(100, 0));
        this._root.runAction(cc.sequence(motion, motion.reverse()).repeatForever());
        this._root.runAction(action1);

        var colorAction = cc.sequence(
            cc.tintTo(0.2, 255, 0, 0),
            cc.tintTo(0.2, 0, 255, 0),
            cc.tintTo(0.2, 0, 0, 255),
            cc.tintTo(0.2, 0, 255, 255),
            cc.tintTo(0.2, 255, 255, 0),
            cc.tintTo(0.2, 255, 0, 255),
            cc.tintTo(0.2, 255, 255, 255)
        ).repeatForever();

        this._streak.runAction(colorAction);
    },

    onUpdate:function (delta) {
	    var pos = this._target.convertToWorldSpace(cc.p(this._target.width/2, 0));
        this._streak.x = pos.x;
        this._streak.y = pos.y;
    },

    title:function () {
        return "MotionStreak test 1";
    }
});

var MotionStreakTest2 = MotionStreakTest.extend({
    _root:null,
    _target:null,

    onEnter:function () {
        this._super();

        cc.eventManager.addListener({
            event: cc.EventListener.TOUCH_ALL_AT_ONCE,
            onTouchesMoved:function (touches, event) {
                if (touches.length == 0)
                    return;

                var touch = touches[0];
                var touchLocation = touch.getLocation();
                var streak = event.getCurrentTarget()._streak;
                streak.x = touchLocation.x;
                streak.y = touchLocation.y;
            }
        }, this);
        var winSize = cc.director.getWinSize();
        // create the streak object and add it to the scene
        this._streak = new cc.MotionStreak(3, 3, 64, cc.color.WHITE, s_streak);
        this.addChild(this._streak);
        this._streak.x = winSize.width / 2;
        this._streak.y = winSize.height / 2;
    },

    title:function () {
        return "MotionStreak test";
    }
});

var Issue1358 = MotionStreakTest.extend({
    _center:null,
    _radius:0,
    _angle:0,
    title:function () {
        return "Issue 1358";
    },

    subtitle:function () {
        return "The tail should use the texture";
    },

    onEnter:function () {
        this._super();

        // ask director the the window size
        var size = cc.director.getWinSize();
        this._streak = new cc.MotionStreak(2.0, 1.0, 50.0, cc.color(255, 255, 0), s_image_icon);
        this.addChild(this._streak);

        this._center = cc.p(size.width / 2, size.height / 2);
        this._radius = size.width / 3;
        this._angle = 0.0;
        this.schedule(this.update, 0);
    },

    update:function (dt) {
        this._angle += 1.0;
        this._streak.x = this._center.x + Math.cos(this._angle / 180 * Math.PI) * this._radius;
        this._streak.y = this._center.y + Math.sin(this._angle / 180 * Math.PI) * this._radius;
    }
});

var arrayOfMotionStreakTest = [
    MotionStreakTest1,
    MotionStreakTest2,
    Issue1358
];

var nextMotionAction = function () {
    sceneIdx++;
    sceneIdx = sceneIdx % arrayOfMotionStreakTest.length;
    return new arrayOfMotionStreakTest[sceneIdx]();
};

var backMotionAction = function () {
    sceneIdx--;
    if (sceneIdx < 0)
        sceneIdx += arrayOfMotionStreakTest.length;
    return new arrayOfMotionStreakTest[sceneIdx]();
};

var restartMotionAction = function () {
    return new arrayOfMotionStreakTest[sceneIdx]();
};

var MotionStreakTestScene = TestScene.extend({
    runThisTest:function (num) {
        sceneIdx = (num || num == 0) ? (num - 1) : -1;
        var pLayer = nextMotionAction();
        this.addChild(pLayer);
        cc.director.runScene(this);
    }
});



