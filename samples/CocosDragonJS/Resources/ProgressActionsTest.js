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
var sceneIdx_Progress = -1;
var MAX_LAYER_Progress = 7;

var nextProgressAction = function () {
    sceneIdx_Progress++;
    sceneIdx_Progress = sceneIdx_Progress % MAX_LAYER_Progress;

    return createLayer(sceneIdx_Progress);
};
var backProgressAction = function () {
    sceneIdx_Progress--;
    if (sceneIdx_Progress < 0)
        sceneIdx_Progress += MAX_LAYER_Progress;

    return createLayer(sceneIdx_Progress);
};
var restartProgressAction = function () {
    return createLayer(sceneIdx_Progress);
};

var createLayer = function (index) {
    switch (index) {
        case 0:
            return new SpriteProgressToRadial();
        case 1:
            return new SpriteProgressToHorizontal();
        case 2:
            return new SpriteProgressToVertical();
        case 3:
            return new SpriteProgressToRadialMidpointChanged();
        case 4:
            return new SpriteProgressBarVarious();
        case 5:
            return new SpriteProgressBarTintAndFade();
        case 6:
            return new SpriteProgressWithSpriteFrame();
    }
    return null;
};

var SpriteDemo = cc.Layer.extend({
    ctor:function () {
        this._super();
    },

    title:function () {
        return "ProgressActionsTest";
    },

    subtitle:function () {
        return "";
    },

    onEnter:function () {
        this._super();

        var winSize = cc.Director.getInstance().getWinSize();

        var label = cc.LabelTTF.create(this.title(), "Arial", 18);
        this.addChild(label, 1);
        label.setPosition(cc.p(winSize.width / 2, winSize.height - 50));

        var strSubtitle = this.subtitle();
        if (strSubtitle != "") {
            var l = cc.LabelTTF.create(strSubtitle, "Thonburi", 22);
            this.addChild(l, 1);
            l.setPosition(cc.p(winSize.width / 2, winSize.height - 80));
        }

        var item1 = cc.MenuItemImage.create(s_pathB1, s_pathB2, this, this.backCallback);
        var item2 = cc.MenuItemImage.create(s_pathR1, s_pathR2, this, this.restartCallback);
        var item3 = cc.MenuItemImage.create(s_pathF1, s_pathF2, this, this.nextCallback);

        var menu = cc.Menu.create(item1, item2, item3);

        menu.setPosition(cc.p(0,0));
        item1.setPosition(cc.p(winSize.width / 2 - item2.getContentSize().width * 2, item2.getContentSize().height / 2));
        item2.setPosition(cc.p(winSize.width / 2, item2.getContentSize().height / 2));
        item3.setPosition(cc.p(winSize.width / 2 + item2.getContentSize().width * 2, item2.getContentSize().height / 2));

        this.addChild(menu, 1);
        var background = cc.LayerColor.create(cc.c4b(0, 125, 0, 255));
        this.addChild(background, -10);
    },

    restartCallback:function (sender) {
        var scene = new ProgressActionsTestScene();
        scene.addChild(restartProgressAction());
        cc.Director.getInstance().replaceScene(scene);
    },

    nextCallback:function (sender) {
        var scene = new ProgressActionsTestScene();
        scene.addChild(nextProgressAction());
        cc.Director.getInstance().replaceScene(scene);
    },

    backCallback:function (sender) {
        var scene = new ProgressActionsTestScene();
        scene.addChild(backProgressAction());
        cc.Director.getInstance().replaceScene(scene);
    }
});

var SpriteProgressToRadial = SpriteDemo.extend({
    onEnter:function () {
        this._super();
        var winSize = cc.Director.getInstance().getWinSize();

        var to1 = cc.ProgressTo.create(2, 100);
        var to2 = cc.ProgressTo.create(2, 100);

        var left = cc.ProgressTimer.create(cc.Sprite.create(s_pathSister1));
        left.setType(cc.PROGRESS_TIMER_TYPE_RADIAL);
        this.addChild(left);
        left.setPosition(cc.p(200, winSize.height / 2));
        left.runAction(cc.RepeatForever.create(to1));

        var right = cc.ProgressTimer.create(cc.Sprite.create(s_pathBlock));
        right.setType(cc.PROGRESS_TIMER_TYPE_RADIAL);
        right.setReverseDirection(true);
        this.addChild(right);
        right.setPosition(cc.p(winSize.width - 200, winSize.height / 2));
        right.runAction(cc.RepeatForever.create(to2));
    },

    subtitle:function () {
        return "ProgressTo Radial";
    }
});

var SpriteProgressToHorizontal = SpriteDemo.extend({
    onEnter:function () {
        this._super();

        var winSize = cc.Director.getInstance().getWinSize();

        var to1 = cc.ProgressTo.create(2, 100);
        var to2 = cc.ProgressTo.create(2, 100);

        var left = cc.ProgressTimer.create(cc.Sprite.create(s_pathSister1));
        left.setType(cc.PROGRESS_TIMER_TYPE_BAR);
        //    Setup for a bar starting from the left since the midpoint is 0 for the x
        left.setMidpoint(cc.p(0, 0));
        //    Setup for a horizontal bar since the bar change rate is 0 for y meaning no vertical change
        left.setBarChangeRate(cc.p(1, 0));
        this.addChild(left);
        left.setPosition(cc.p(200, winSize.height / 2));
        left.runAction(cc.RepeatForever.create(to1));

        var right = cc.ProgressTimer.create(cc.Sprite.create(s_pathSister2));
        right.setType(cc.PROGRESS_TIMER_TYPE_BAR);
        //    Setup for a bar starting from the left since the midpoint is 1 for the x
        right.setMidpoint(cc.p(1, 0));
        //    Setup for a horizontal bar since the bar change rate is 0 for y meaning no vertical change
        right.setBarChangeRate(cc.p(1, 0));
        this.addChild(right);
        right.setPosition(cc.p(winSize.width - 200, winSize.height / 2));
        right.runAction(cc.RepeatForever.create(to2));
    },
    subtitle:function () {
        return "ProgressTo Horizontal";
    }
});

var SpriteProgressToVertical = SpriteDemo.extend({
    onEnter:function () {
        this._super();

        var winSize = cc.Director.getInstance().getWinSize();

        var to1 = cc.ProgressTo.create(2, 100);
        var to2 = cc.ProgressTo.create(2, 100);

        var left = cc.ProgressTimer.create(cc.Sprite.create(s_pathSister1));
        left.setType(cc.PROGRESS_TIMER_TYPE_BAR);
        //    Setup for a bar starting from the bottom since the midpoint is 0 for the y
        left.setMidpoint(cc.p(0, 0));
        //    Setup for a vertical bar since the bar change rate is 0 for x meaning no horizontal change
        left.setBarChangeRate(cc.p(0, 1));
        this.addChild(left);
        left.setPosition(cc.p(200, winSize.height / 2));
        left.runAction(cc.RepeatForever.create(to1));

        var right = cc.ProgressTimer.create(cc.Sprite.create(s_pathSister2));
        right.setType(cc.PROGRESS_TIMER_TYPE_BAR);
        //    Setup for a bar starting from the bottom since the midpoint is 0 for the y
        right.setMidpoint(cc.p(0, 1));
        //    Setup for a vertical bar since the bar change rate is 0 for x meaning no horizontal change
        right.setBarChangeRate(cc.p(0, 1));
        this.addChild(right);
        right.setPosition(cc.p(winSize.width - 200, winSize.height / 2));
        right.runAction(cc.RepeatForever.create(to2));
    },
    subtitle:function () {
        return "ProgressTo Vertical";
    }
});

var SpriteProgressToRadialMidpointChanged = SpriteDemo.extend({
    onEnter:function () {
        this._super();

        var winSize = cc.Director.getInstance().getWinSize();
        var action = cc.ProgressTo.create(2, 100);

        /**
         *  Our image on the left should be a radial progress indicator, clockwise
         */
        var left = cc.ProgressTimer.create(cc.Sprite.create(s_pathBlock));
        left.setType(cc.PROGRESS_TIMER_TYPE_RADIAL);
        this.addChild(left);
        left.setMidpoint(cc.p(0.25, 0.75));
        left.setPosition(cc.p(200, winSize.height / 2));
        left.runAction(cc.RepeatForever.create(action.copy()));

        /**
         *  Our image on the left should be a radial progress indicator, counter clockwise
         */
        var right = cc.ProgressTimer.create(cc.Sprite.create(s_pathBlock));
        right.setType(cc.PROGRESS_TIMER_TYPE_RADIAL);
        right.setMidpoint(cc.p(0.75, 0.25));
        /**
         *  Note the reverse property (default=NO) is only added to the right image. That's how
         *  we get a counter clockwise progress.
         */
        this.addChild(right);
        right.setPosition(cc.p(winSize.width - 200, winSize.height / 2));
        right.runAction(cc.RepeatForever.create(action.copy()));
    },

    subtitle:function () {
        return "Radial w/ Different Midpoints";
    }
});

var SpriteProgressBarVarious = SpriteDemo.extend({
    onEnter:function () {
        this._super();

        var s = cc.Director.getInstance().getWinSize();

        var to = cc.ProgressTo.create(2, 100);

        var left = cc.ProgressTimer.create(cc.Sprite.create(s_pathSister1));
        left.setType(cc.PROGRESS_TIMER_TYPE_BAR);

        //    Setup for a bar starting from the bottom since the midpoint is 0 for the y
        left.setMidpoint(cc.p(0.5, 0.5));
        //    Setup for a vertical bar since the bar change rate is 0 for x meaning no horizontal change
        left.setBarChangeRate(cc.p(1, 0));
        this.addChild(left);
        left.setPosition(cc.p(150, s.height / 2));
        left.runAction(cc.RepeatForever.create(to.copy()));

        var middle = cc.ProgressTimer.create(cc.Sprite.create(s_pathSister2));
        middle.setType(cc.PROGRESS_TIMER_TYPE_BAR);
        //    Setup for a bar starting from the bottom since the midpoint is 0 for the y
        middle.setMidpoint(cc.p(0.5, 0.5));
        //    Setup for a vertical bar since the bar change rate is 0 for x meaning no horizontal change
        middle.setBarChangeRate(cc.p(1, 1));
        this.addChild(middle);
        middle.setPosition(cc.p(s.width / 2, s.height / 2));
        middle.runAction(cc.RepeatForever.create(to.copy()));

        var right = cc.ProgressTimer.create(cc.Sprite.create(s_pathSister2));
        right.setType(cc.PROGRESS_TIMER_TYPE_BAR);
        //    Setup for a bar starting from the bottom since the midpoint is 0 for the y
        right.setMidpoint(cc.p(0.5, 0.5));
        //    Setup for a vertical bar since the bar change rate is 0 for x meaning no horizontal change
        right.setBarChangeRate(cc.p(0, 1));
        this.addChild(right);
        right.setPosition(cc.p(s.width - 150, s.height / 2));
        right.runAction(cc.RepeatForever.create(to.copy()));
    },

    subtitle:function () {
        return "ProgressTo Bar Mid";
    }
});

var SpriteProgressBarTintAndFade = SpriteDemo.extend({
    onEnter:function () {
        this._super();

        var winSize = cc.Director.getInstance().getWinSize();

        var to = cc.ProgressTo.create(6, 100);
        var tint = cc.Sequence.create(cc.TintTo.create(1, 255, 0, 0),
            cc.TintTo.create(1, 0, 255, 0),
            cc.TintTo.create(1, 0, 0, 255));

        var fade = cc.Sequence.create(cc.FadeTo.create(1.0, 0), cc.FadeTo.create(1.0, 255));

        var left = cc.ProgressTimer.create(cc.Sprite.create(s_pathSister1));
        left.setType(cc.PROGRESS_TIMER_TYPE_BAR);

        //    Setup for a bar starting from the bottom since the midpoint is 0 for the y
        left.setMidpoint(cc.p(0.5, 0.5));
        //    Setup for a vertical bar since the bar change rate is 0 for x meaning no horizontal change
        left.setBarChangeRate(cc.p(1, 0));
        this.addChild(left);
        left.setPosition(cc.p(150, winSize.height / 2));
        left.runAction(cc.RepeatForever.create(to.copy()));
        left.runAction(cc.RepeatForever.create(tint.copy()));

        left.addChild(cc.LabelTTF.create("Tint", "Marker Felt", 20.0));

        var middle = cc.ProgressTimer.create(cc.Sprite.create(s_pathSister2));
        middle.setType(cc.PROGRESS_TIMER_TYPE_BAR);
        //    Setup for a bar starting from the bottom since the midpoint is 0 for the y
        middle.setMidpoint(cc.p(0.5, 0.5));
        //    Setup for a vertical bar since the bar change rate is 0 for x meaning no horizontal change
        middle.setBarChangeRate(cc.p(1, 1));
        this.addChild(middle);
        middle.setPosition(cc.p(winSize.width / 2, winSize.height / 2));
        middle.runAction(cc.RepeatForever.create(to.copy()));
        middle.runAction(cc.RepeatForever.create(fade.copy()));

        middle.addChild(cc.LabelTTF.create("Fade", "Marker Felt", 20.0));

        var right = cc.ProgressTimer.create(cc.Sprite.create(s_pathSister2));
        right.setType(cc.PROGRESS_TIMER_TYPE_BAR);
        //    Setup for a bar starting from the bottom since the midpoint is 0 for the y
        right.setMidpoint(cc.p(0.5, 0.5));
        //    Setup for a vertical bar since the bar change rate is 0 for x meaning no horizontal change
        right.setBarChangeRate(cc.p(0, 1));
        this.addChild(right);
        right.setPosition(cc.p(winSize.width - 150, winSize.height / 2));
        right.runAction(cc.RepeatForever.create(to.copy()));
        right.runAction(cc.RepeatForever.create(tint.copy()));
        right.runAction(cc.RepeatForever.create(fade.copy()));

        right.addChild(cc.LabelTTF.create("Tint and Fade", "Marker Felt", 20.0));
    },

    subtitle:function () {
        return "ProgressTo Bar Mid";
    }
});

var SpriteProgressWithSpriteFrame = SpriteDemo.extend({
    onEnter:function () {
        this._super();

        var winSize = cc.Director.getInstance().getWinSize();
        var to = cc.ProgressTo.create(6, 100);

        cc.SpriteFrameCache.getInstance().addSpriteFrames(s_grossiniPlist);

        var left = cc.ProgressTimer.create(cc.Sprite.createWithSpriteFrameName("grossini_dance_01.png"));
        left.setType(cc.PROGRESS_TIMER_TYPE_BAR);
        //    Setup for a bar starting from the bottom since the midpoint is 0 for the y
        left.setMidpoint(cc.p(0.5, 0.5));
        //    Setup for a vertical bar since the bar change rate is 0 for x meaning no horizontal change
        left.setBarChangeRate(cc.p(1, 0));
        this.addChild(left);
        left.setPosition(cc.p(150, winSize.height / 2));
        left.runAction(cc.RepeatForever.create(to.copy()));

        var middle = cc.ProgressTimer.create(cc.Sprite.createWithSpriteFrameName("grossini_dance_02.png"));
        middle.setType(cc.PROGRESS_TIMER_TYPE_BAR);
        //    Setup for a bar starting from the bottom since the midpoint is 0 for the y
        middle.setMidpoint(cc.p(0.5, 0.5));
        //    Setup for a vertical bar since the bar change rate is 0 for x meaning no horizontal change
        middle.setBarChangeRate(cc.p(1, 1));
        this.addChild(middle);
        middle.setPosition(cc.p(winSize.width / 2, winSize.height / 2));
        middle.runAction(cc.RepeatForever.create(to.copy()));

        var right = cc.ProgressTimer.create(cc.Sprite.createWithSpriteFrameName("grossini_dance_03.png"));
        right.setType(cc.PROGRESS_TIMER_TYPE_RADIAL);
        //    Setup for a bar starting from the bottom since the midpoint is 0 for the y
        right.setMidpoint(cc.p(0.5, 0.5));
        //    Setup for a vertical bar since the bar change rate is 0 for x meaning no horizontal change
        right.setBarChangeRate(cc.p(0, 1));
        this.addChild(right);
        right.setPosition(cc.p(winSize.width - 150, winSize.height / 2));
        right.runAction(cc.RepeatForever.create(to.copy()));
    },

    subtitle:function () {
        return "Progress With Sprite Frame";
    }
});

var ProgressActionsTestScene = TestScene.extend({
    runThisTest:function () {
        sceneIdx_Progress = -1;
        MAX_LAYER_Progress = 7;
        this.addChild(nextProgressAction());
        cc.Director.getInstance().replaceScene(this);
    }
});
