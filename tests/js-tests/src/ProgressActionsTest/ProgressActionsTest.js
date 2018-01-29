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
var ProgressTestSceneIdx = -1;

var SpriteDemo = BaseTestLayer.extend({

    title:function () {
        return "ProgressActionsTest";
    },

    subtitle:function () {
        return "";
    },

    onBackCallback:function (sender) {
        var scene = new ProgressActionsTestScene();
        scene.addChild(previousProgressTest());
        director.runScene(scene);
    },

    onRestartCallback:function (sender) {
        var scene = new ProgressActionsTestScene();
        scene.addChild(restartProgressTest());
        director.runScene(scene);
    },

    onNextCallback:function (sender) {
        var scene = new ProgressActionsTestScene();
        scene.addChild(nextProgressTest());
        director.runScene(scene);
    },
    // automation
    numberOfPendingTests:function() {
        return ( (arrayOfProgressTest.length-1) - ProgressTestSceneIdx );
    },

    getTestNumber:function() {
        return ProgressTestSceneIdx;
    }

});

var SpriteProgressToRadial = SpriteDemo.extend({
    onEnter:function () {
        //----start0----onEnter
        this._super();

        var to1 = cc.progressFromTo(2, 0, 100);
        var to2 = cc.progressFromTo(2, 0, 100);

        var left = new cc.ProgressTimer(new cc.Sprite(s_pathSister1));
        left.type = cc.ProgressTimer.TYPE_RADIAL;
        this.addChild(left);
        left.x = 200;
        left.y = winSize.height / 2;
        left.runAction(to1.repeatForever());

        var right = new cc.ProgressTimer(new cc.Sprite(s_pathBlock));
        right.type = cc.ProgressTimer.TYPE_RADIAL;
        right.setReverseDirection(true);
        this.addChild(right);
        right.x = winSize.width - 200;
        right.y = winSize.height / 2;
        right.runAction(to2.repeatForever());
        //----end0----
    },

    title:function () {
        return "ProgressFromTo Radial";
    }
});

var SpriteProgressToHorizontal = SpriteDemo.extend({
    onEnter:function () {
        //----start1----onEnter
        this._super();

        var to1 = cc.sequence(cc.progressTo(2, 100), cc.progressTo(0, 0));
        var to2 = cc.sequence(cc.progressTo(2, 100), cc.progressTo(0, 0));

        var left = new cc.ProgressTimer(new cc.Sprite(s_pathSister1));
        left.type = cc.ProgressTimer.TYPE_BAR;
        //    Setup for a bar starting from the left since the midpoint is 0 for the x
        left.midPoint = cc.p(0, 0);
        //    Setup for a horizontal bar since the bar change rate is 0 for y meaning no vertical change
        left.barChangeRate = cc.p(1, 0);
        this.addChild(left);
        left.x = 200;
        left.y = winSize.height / 2;
        left.runAction(to1.repeatForever());

        var right = new cc.ProgressTimer(new cc.Sprite(s_pathSister2));
        right.type = cc.ProgressTimer.TYPE_BAR;
        //    Setup for a bar starting from the left since the midpoint is 1 for the x
        right.midPoint = cc.p(1, 0);
        //    Setup for a horizontal bar since the bar change rate is 0 for y meaning no vertical change
        right.barChangeRate = cc.p(1, 0);
        this.addChild(right);
        right.x = winSize.width - 200;
        right.y = winSize.height / 2;
        right.runAction(to2.repeatForever());
        //----end1----
    },
    title:function () {
        return "ProgressTo Horizontal";
    }
});

var SpriteProgressToVertical = SpriteDemo.extend({
    onEnter:function () {
        //----start2----onEnter
        this._super();

        var to1 = cc.sequence(cc.progressTo(2, 100), cc.progressTo(0, 0));
        var to2 = cc.sequence(cc.progressTo(2, 100), cc.progressTo(0, 0));

        var left = new cc.ProgressTimer(new cc.Sprite(s_pathSister1));
        left.type = cc.ProgressTimer.TYPE_BAR;
        //    Setup for a bar starting from the bottom since the midpoint is 0 for the y
        left.midPoint = cc.p(0, 0);
        //    Setup for a vertical bar since the bar change rate is 0 for x meaning no horizontal change
        left.barChangeRate = cc.p(0, 1);
        this.addChild(left);
        left.x = 200;
        left.y = winSize.height / 2;
        left.runAction(to1.repeatForever());

        var right = new cc.ProgressTimer(new cc.Sprite(s_pathSister2));
        right.type = cc.ProgressTimer.TYPE_BAR;
        //    Setup for a bar starting from the bottom since the midpoint is 0 for the y
        right.midPoint = cc.p(0, 1);
        //    Setup for a vertical bar since the bar change rate is 0 for x meaning no horizontal change
        right.barChangeRate = cc.p(0, 1);
        this.addChild(right);
        right.x = winSize.width - 200;
        right.y = winSize.height / 2;
        right.runAction(to2.repeatForever());
        //----end2----
    },
    title:function () {
        return "ProgressTo Vertical";
    }
});

var SpriteProgressToRadialMidpointChanged = SpriteDemo.extend({
    onEnter:function () {
        //----start3----onEnter
        this._super();

        var action = cc.sequence(cc.progressTo(2, 100), cc.progressTo(0, 0));

        /**
         *  Our image on the left should be a radial progress indicator, clockwise
         */
        var left = new cc.ProgressTimer(new cc.Sprite(s_pathBlock));
        left.type = cc.ProgressTimer.TYPE_RADIAL;
        this.addChild(left);
        left.midPoint = cc.p(0.25, 0.75);
        left.x = 200;
        left.y = winSize.height / 2;
        left.runAction(action.clone().repeatForever());

        /**
         *  Our image on the left should be a radial progress indicator, counter clockwise
         */
        var right = new cc.ProgressTimer(new cc.Sprite(s_pathBlock));
        right.type = cc.ProgressTimer.TYPE_RADIAL;
        right.midPoint = cc.p(0.75, 0.25);
        /**
         *  Note the reverse property (default=NO) is only added to the right image. That's how
         *  we get a counter clockwise progress.
         */
        this.addChild(right);
        right.x = winSize.width - 200;
        right.y = winSize.height / 2;
        right.runAction(action.clone().repeatForever());
        //----end3----
    },

    title:function () {
        return "Radial w/ Different Midpoints";
    }
});

var SpriteProgressBarVarious = SpriteDemo.extend({
    onEnter:function () {
        //----start4----onEnter
        this._super();

        var to = cc.progressFromTo(2, 0, 100);

        var left = new cc.ProgressTimer(new cc.Sprite(s_pathSister1));
        left.type = cc.ProgressTimer.TYPE_BAR;

        //    Setup for a bar starting from the bottom since the midpoint is 0 for the y
        left.midPoint = cc.p(0.5, 0.5);
        //    Setup for a vertical bar since the bar change rate is 0 for x meaning no horizontal change
        left.barChangeRate = cc.p(1, 0);
        this.addChild(left);
        left.x = 150;
        left.y = winSize.height / 2;
        left.runAction(to.clone().repeatForever());

        var middle = new cc.ProgressTimer(new cc.Sprite(s_pathSister2));
        middle.type = cc.ProgressTimer.TYPE_BAR;
        //    Setup for a bar starting from the bottom since the midpoint is 0 for the y
        middle.midPoint = cc.p(0.5, 0.5);
        //    Setup for a vertical bar since the bar change rate is 0 for x meaning no horizontal change
        middle.barChangeRate = cc.p(1, 1);
        this.addChild(middle);
        middle.x = winSize.width / 2;
        middle.y = winSize.height / 2;
        middle.runAction(to.clone().repeatForever());

        var right = new cc.ProgressTimer(new cc.Sprite(s_pathSister2));
        right.type = cc.ProgressTimer.TYPE_BAR;
        //    Setup for a bar starting from the bottom since the midpoint is 0 for the y
        right.midPoint = cc.p(0.5, 0.5);
        //    Setup for a vertical bar since the bar change rate is 0 for x meaning no horizontal change
        right.barChangeRate = cc.p(0, 1);
        this.addChild(right);
        right.x = winSize.width - 150;
        right.y = winSize.height / 2;
        right.runAction(to.clone().repeatForever());
        //----end4----
    },

    title:function () {
        return "ProgressFromTo Bar Mid";
    }
});

var SpriteProgressBarTintAndFade = SpriteDemo.extend({
    onEnter:function () {
        //----start5----onEnter
        this._super();

        var to = cc.progressFromTo(6, 0, 100);
        var tint = cc.sequence(
            cc.tintTo(1, 255, 0, 0),
            cc.tintTo(1, 0, 255, 0),
            cc.tintTo(1, 0, 0, 255)
        );

        var fade = cc.sequence(cc.fadeTo(1.0, 0), cc.fadeTo(1.0, 255));

        var left = new cc.ProgressTimer(new cc.Sprite(s_pathSister1));
        left.type = cc.ProgressTimer.TYPE_BAR;

        //    Setup for a bar starting from the bottom since the midpoint is 0 for the y
        left.midPoint = cc.p(0.5, 0.5);
        //    Setup for a vertical bar since the bar change rate is 0 for x meaning no horizontal change
        left.barChangeRate = cc.p(1, 0);
        this.addChild(left);
        left.x = 150;
        left.y = winSize.height / 2;
        left.runAction(to.clone().repeatForever());
        left.runAction(tint.clone().repeatForever());

        left.addChild(new cc.LabelTTF("Tint", "Marker Felt", 20.0));

        var middle = new cc.ProgressTimer(new cc.Sprite(s_pathSister2));
        middle.type = cc.ProgressTimer.TYPE_BAR;
        //    Setup for a bar starting from the bottom since the midpoint is 0 for the y
        middle.midPoint = cc.p(0.5, 0.5);
        //    Setup for a vertical bar since the bar change rate is 0 for x meaning no horizontal change
        middle.barChangeRate = cc.p(1, 1);
        this.addChild(middle);
        middle.x = winSize.width / 2;
        middle.y = winSize.height / 2;
        middle.runAction(to.clone().repeatForever());
        middle.runAction(fade.clone().repeatForever());

        middle.addChild(new cc.LabelTTF("Fade", "Marker Felt", 20.0));

        var right = new cc.ProgressTimer(new cc.Sprite(s_pathSister2));
        right.type = cc.ProgressTimer.TYPE_BAR;
        //    Setup for a bar starting from the bottom since the midpoint is 0 for the y
        right.midPoint = cc.p(0.5, 0.5);
        //    Setup for a vertical bar since the bar change rate is 0 for x meaning no horizontal change
        right.barChangeRate = cc.p(0, 1);
        this.addChild(right);
        right.x = winSize.width - 150;
        right.y = winSize.height / 2;
        right.runAction(to.clone().repeatForever());
        right.runAction(tint.clone().repeatForever());
        right.runAction(fade.clone().repeatForever());

        right.addChild(new cc.LabelTTF("Tint and Fade", "Marker Felt", 20.0));
        //----end5----
    },

    title:function () {
        return "ProgressFromTo Bar Mid";
    }
});

var SpriteProgressWithSpriteFrame = SpriteDemo.extend({
    onEnter:function () {
        //----start6----onEnter
        this._super();

        var to = cc.progressFromTo(6, 0, 100);

        cc.spriteFrameCache.addSpriteFrames(s_grossiniPlist);

        var left = new cc.ProgressTimer(new cc.Sprite("#grossini_dance_01.png"));
        left.type = cc.ProgressTimer.TYPE_BAR;
        //    Setup for a bar starting from the bottom since the midpoint is 0 for the y
        left.midpoint = cc.p(0.5, 0.5);
        //    Setup for a vertical bar since the bar change rate is 0 for x meaning no horizontal change
        left.barChangeRate = cc.p(1, 0);
        this.addChild(left);
        left.x = 150;
        left.y = winSize.height / 2;
        left.runAction(to.clone().repeatForever());

        var middle = new cc.ProgressTimer(new cc.Sprite("#grossini_dance_02.png"));
        middle.type = cc.ProgressTimer.TYPE_BAR;
        //    Setup for a bar starting from the bottom since the midpoint is 0 for the y
        middle.midpoint = cc.p(0.5, 0.5);
        //    Setup for a vertical bar since the bar change rate is 0 for x meaning no horizontal change
        middle.barChangeRate = cc.p(1, 1);
        this.addChild(middle);
        middle.x = winSize.width / 2;
        middle.y = winSize.height / 2;
        middle.runAction(to.clone().repeatForever());

        var right = new cc.ProgressTimer(new cc.Sprite("#grossini_dance_03.png"));
        right.type = cc.ProgressTimer.TYPE_RADIAL;
        //    Setup for a bar starting from the bottom since the midpoint is 0 for the y
        right.midPoint = cc.p(0.5, 0.5);
        //    Setup for a vertical bar since the bar change rate is 0 for x meaning no horizontal change
        right.barChangeRate = cc.p(0, 1);
        this.addChild(right);
        right.x = winSize.width - 150;
        right.y = winSize.height / 2;
        right.runAction(to.clone().repeatForever());
        //----end6----
    },

    title:function () {
        return "Progress With Sprite Frame";
    }
});

var ProgressActionsTestScene = TestScene.extend({

    runThisTest:function (num) {
        ProgressTestSceneIdx = (num || num == 0) ? (num - 1) : -1;
        this.addChild(nextProgressTest());
        director.runScene(this);
    }
});


var arrayOfProgressTest = [
    SpriteProgressToRadial,
    SpriteProgressToHorizontal,
    SpriteProgressToVertical,
    SpriteProgressToRadialMidpointChanged,
    SpriteProgressBarVarious,
    SpriteProgressBarTintAndFade,
    SpriteProgressWithSpriteFrame
];

var nextProgressTest = function () {
    ProgressTestSceneIdx++;
    ProgressTestSceneIdx = ProgressTestSceneIdx % arrayOfProgressTest.length;

    if(window.sideIndexBar){
        ProgressTestSceneIdx = window.sideIndexBar.changeTest(ProgressTestSceneIdx, 30);
    }

    return new arrayOfProgressTest[ProgressTestSceneIdx]();
};
var previousProgressTest = function () {
    ProgressTestSceneIdx--;
    if (ProgressTestSceneIdx < 0)
        ProgressTestSceneIdx += arrayOfProgressTest.length;

    if(window.sideIndexBar){
        ProgressTestSceneIdx = window.sideIndexBar.changeTest(ProgressTestSceneIdx, 30);
    }

    return new arrayOfProgressTest[ProgressTestSceneIdx]();
};
var restartProgressTest = function () {
    return new arrayOfProgressTest[ProgressTestSceneIdx]();
};
