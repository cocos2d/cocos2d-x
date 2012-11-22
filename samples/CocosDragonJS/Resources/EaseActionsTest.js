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

TAG_ACTION1_EASE_ACTIONS = 1;
TAG_ACTION2_EASE_ACTIONS = 2;
TAG_SLIDER_EASE_ACTIONS = 1;

var sceneIdx = -1;

// the class inherit from TestScene
// every .Scene each test used must inherit from TestScene,
// make sure the test have the menu item for back to main menu
var EaseActionsTestScene = TestScene.extend({
    runThisTest:function () {
        sceneIdx = -1;
        this.addChild(nextEaseActionsTest());
        director.replaceScene(this);
    }
});


var EaseSpriteDemo = cc.Layer.extend({
    _grossini:null,
    _tamara:null,
    _kathia:null,
    _title:null,

    ctor:function() {
        cc.associateWithNative( this, cc.Layer );
        this.init();
    },
    init:function() {
        // this._super(cc.c4b(0, 0, 0, 255), cc.c4b(0, 128, 255, 255));
        this._super();
    },

    title:function () {
        return "No title";
    },
    onEnter:function () {
        this._super();

        // Or you can create an sprite using a filename. PNG and BMP files are supported. Probably TIFF too
        this._grossini = cc.Sprite.create(s_pathGrossini);
        this._tamara = cc.Sprite.create(s_pathSister1);
        this._kathia = cc.Sprite.create(s_pathSister2);

        this.addChild(this._grossini, 3);
        this.addChild(this._kathia, 2);
        this.addChild(this._tamara, 1);

        this._grossini.setPosition(cc.p(60, winSize.height*1/5));
        this._kathia.setPosition(cc.p(60, winSize.height/2));
        this._tamara.setPosition(cc.p(60, winSize.height*4/5));

        var label = cc.LabelTTF.create(this.title(), "Arial", 32);
        this.addChild(label);
        label.setPosition(cc.p(winSize.width / 2, winSize.height - 50));

        var item1 = cc.MenuItemImage.create(s_pathB1, s_pathB2, this, this.backCallback);
        var item2 = cc.MenuItemImage.create(s_pathR1, s_pathR2, this, this.restartCallback);
        var item3 = cc.MenuItemImage.create(s_pathF1, s_pathF2, this, this.nextCallback);

        var menu = cc.Menu.create(item1, item2, item3);

        menu.setPosition(cc.p(0,0));

        var cs = item2.getContentSize();
        item1.setPosition( cc.p(winSize.width/2 - cs.width*2, cs.height/2) );
        item2.setPosition( cc.p(winSize.width/2, cs.height/2) );
        item3.setPosition( cc.p(winSize.width/2 + cs.width*2, cs.height/2) );

        this.addChild(menu, 1);
    },

    restartCallback:function (sender) {
        var s = new EaseActionsTestScene();//cc.Scene.create();
        s.addChild(restartEaseActionsTest());
        director.replaceScene(s);
    },
    nextCallback:function (sender) {
        var s = new EaseActionsTestScene();//cc.Scene.create();
        s.addChild(nextEaseActionsTest());
        director.replaceScene(s);
    },
    backCallback:function (sender) {
        var s = new EaseActionsTestScene();//cc.Scene.create();
        s.addChild(previousEaseActionsTest());
        director.replaceScene(s);
    },
    positionForTwo:function () {
        this._grossini.setPosition(cc.p(60, winSize.height*1/5));
        this._tamara.setPosition(cc.p(60, winSize.height*4/5));
        this._kathia.setVisible(false);
    }
});

//------------------------------------------------------------------
//
// SpriteEase
//
//------------------------------------------------------------------
var SpriteEase = EaseSpriteDemo.extend({

    onEnter:function () {
        this._super();

        var move = cc.MoveBy.create(3, cc.p(winSize.width-80, 0));
        var move_back = move.reverse();

        var move_ease_in = cc.EaseIn.create(move.copy(), 3.0);
        var move_ease_in_back = move_ease_in.reverse();

        var move_ease_out = cc.EaseOut.create(move.copy(), 3.0);
        var move_ease_out_back = move_ease_out.reverse();


        var seq1 = cc.Sequence.create(move, move_back);
        var seq2 = cc.Sequence.create(move_ease_in, move_ease_in_back);
        var seq3 = cc.Sequence.create(move_ease_out, move_ease_out_back);


        var a2 = this._grossini.runAction(cc.RepeatForever.create(seq1));
        a2.setTag(1);

        var a1 = this._tamara.runAction(cc.RepeatForever.create(seq2));
        a1.setTag(1);

        var a = this._kathia.runAction(cc.RepeatForever.create(seq3));
        a.setTag(1);

        this.schedule(this.testStopAction, 6);
    },
    title:function () {
        return "EaseIn - EaseOut - Stop";
    },

    testStopAction:function (dt) {
        this.unschedule(this.testStopAction);
        this._tamara.stopActionByTag(1);
        this._kathia.stopActionByTag(1);
        this._grossini.stopActionByTag(1);
    }
});

//------------------------------------------------------------------
//
// SpriteEaseInOut
//
//------------------------------------------------------------------
var SpriteEaseInOut = EaseSpriteDemo.extend({

    onEnter:function () {
        this._super();

        var move = cc.MoveBy.create(3, cc.p(winSize.width-80, 0));
        //	id move_back = move.reverse();

        var move_ease_inout1 = cc.EaseInOut.create(move.copy(), 2.0);
        var move_ease_inout_back1 = move_ease_inout1.reverse();

        var move_ease_inout2 = cc.EaseInOut.create(move.copy(), 3.0);
        var move_ease_inout_back2 = move_ease_inout2.reverse();

        var move_ease_inout3 = cc.EaseInOut.create(move.copy(), 4.0);
        var move_ease_inout_back3 = move_ease_inout3.reverse();


        var seq1 = cc.Sequence.create(move_ease_inout1, move_ease_inout_back1);
        var seq2 = cc.Sequence.create(move_ease_inout2, move_ease_inout_back2);
        var seq3 = cc.Sequence.create(move_ease_inout3, move_ease_inout_back3);

        this._tamara.runAction(cc.RepeatForever.create(seq1));
        this._kathia.runAction(cc.RepeatForever.create(seq2));
        this._grossini.runAction(cc.RepeatForever.create(seq3));
    },
    title:function () {
        return "EaseInOut and rates";
    }
});

//------------------------------------------------------------------
//
// SpriteEaseExponential
//
//------------------------------------------------------------------
var SpriteEaseExponential = EaseSpriteDemo.extend({

    onEnter:function () {
        this._super();

        var move = cc.MoveBy.create(3, cc.p(winSize.width-80, 0));
        var move_back = move.reverse();

        var move_ease_in = cc.EaseExponentialIn.create(move.copy());
        var move_ease_in_back = move_ease_in.reverse();

        var move_ease_out = cc.EaseExponentialOut.create(move.copy());
        var move_ease_out_back = move_ease_out.reverse();


        var seq1 = cc.Sequence.create(move, move_back);
        var seq2 = cc.Sequence.create(move_ease_in, move_ease_in_back);
        var seq3 = cc.Sequence.create(move_ease_out, move_ease_out_back);


        this._grossini.runAction(cc.RepeatForever.create(seq1));
        this._tamara.runAction(cc.RepeatForever.create(seq2));
        this._kathia.runAction(cc.RepeatForever.create(seq3));
    },
    title:function () {
        return "ExpIn - ExpOut actions";
    }
});

//------------------------------------------------------------------
//
// SpriteEaseExponentialInOut
//
//------------------------------------------------------------------
var SpriteEaseExponentialInOut = EaseSpriteDemo.extend({

    onEnter:function () {
        this._super();

        var move = cc.MoveBy.create(3, cc.p(winSize.width-80, 0));
        var move_back = move.reverse();

        var move_ease = cc.EaseExponentialInOut.create(move.copy());
        var move_ease_back = move_ease.reverse();	//-. reverse()

        var seq1 = cc.Sequence.create(move, move_back);
        var seq2 = cc.Sequence.create(move_ease, move_ease_back);

        this.positionForTwo();

        this._grossini.runAction(cc.RepeatForever.create(seq1));
        this._tamara.runAction(cc.RepeatForever.create(seq2));
    },
    title:function () {
        return "EaseExponentialInOut action";
    }
});

//------------------------------------------------------------------
//
// SpriteEaseSine
//
//------------------------------------------------------------------
var SpriteEaseSine = EaseSpriteDemo.extend({
    onEnter:function () {
        this._super();

        var move = cc.MoveBy.create(3, cc.p(winSize.width-80, 0));
        var move_back = move.reverse();

        var move_ease_in = cc.EaseSineIn.create(move.copy());
        var move_ease_in_back = move_ease_in.reverse();

        var move_ease_out = cc.EaseSineOut.create(move.copy());
        var move_ease_out_back = move_ease_out.reverse();


        var seq1 = cc.Sequence.create(move, move_back);
        var seq2 = cc.Sequence.create(move_ease_in, move_ease_in_back);
        var seq3 = cc.Sequence.create(move_ease_out, move_ease_out_back);


        this._grossini.runAction(cc.RepeatForever.create(seq1));
        this._tamara.runAction(cc.RepeatForever.create(seq2));
        this._kathia.runAction(cc.RepeatForever.create(seq3));

    },
    title:function () {
        return "EaseSineIn - EaseSineOut";
    }
});

//------------------------------------------------------------------
//
// SpriteEaseSineInOut
//
//------------------------------------------------------------------
var SpriteEaseSineInOut = EaseSpriteDemo.extend({
    onEnter:function () {
        this._super();

        var move = cc.MoveBy.create(3, cc.p(winSize.width-80, 0));
        var move_back = move.reverse();

        var move_ease = cc.EaseSineInOut.create(move.copy());
        var move_ease_back = move_ease.reverse();

        var seq1 = cc.Sequence.create(move, move_back);
        var seq2 = cc.Sequence.create(move_ease, move_ease_back);

        this.positionForTwo();

        this._grossini.runAction(cc.RepeatForever.create(seq1));
        this._tamara.runAction(cc.RepeatForever.create(seq2));
    },
    title:function () {
        return "EaseSineInOut action";
    }
});

//------------------------------------------------------------------
//
// SpriteEaseElastic
//
//------------------------------------------------------------------
var SpriteEaseElastic = EaseSpriteDemo.extend({
    onEnter:function () {
        this._super();

        var move = cc.MoveBy.create(3, cc.p(winSize.width-80, 0));
        var move_back = move.reverse();

        var move_ease_in = cc.EaseElasticIn.create(move.copy());
        var move_ease_in_back = move_ease_in.reverse();

        var move_ease_out = cc.EaseElasticOut.create(move.copy());
        var move_ease_out_back = move_ease_out.reverse();

        var seq1 = cc.Sequence.create(move, move_back);
        var seq2 = cc.Sequence.create(move_ease_in, move_ease_in_back);
        var seq3 = cc.Sequence.create(move_ease_out, move_ease_out_back);

        this._grossini.runAction(cc.RepeatForever.create(seq1));
        this._tamara.runAction(cc.RepeatForever.create(seq2));
        this._kathia.runAction(cc.RepeatForever.create(seq3));
    },
    title:function () {
        return "Elastic In - Out actions";
    }
});

//------------------------------------------------------------------
//
// SpriteEaseElasticInOut
//
//------------------------------------------------------------------
var SpriteEaseElasticInOut = EaseSpriteDemo.extend({
    onEnter:function () {
        this._super();

        var move = cc.MoveBy.create(3, cc.p(winSize.width-80, 0));

        var move_ease_inout1 = cc.EaseElasticInOut.create(move.copy(), 0.3);
        var move_ease_inout_back1 = move_ease_inout1.reverse();

        var move_ease_inout2 = cc.EaseElasticInOut.create(move.copy(), 0.45);
        var move_ease_inout_back2 = move_ease_inout2.reverse();

        var move_ease_inout3 = cc.EaseElasticInOut.create(move.copy(), 0.6);
        var move_ease_inout_back3 = move_ease_inout3.reverse();


        var seq1 = cc.Sequence.create(move_ease_inout1, move_ease_inout_back1);
        var seq2 = cc.Sequence.create(move_ease_inout2, move_ease_inout_back2);
        var seq3 = cc.Sequence.create(move_ease_inout3, move_ease_inout_back3);

        this._tamara.runAction(cc.RepeatForever.create(seq1));
        this._kathia.runAction(cc.RepeatForever.create(seq2));
        this._grossini.runAction(cc.RepeatForever.create(seq3));
    },
    title:function () {
        return "EaseElasticInOut action";
    }
});

//------------------------------------------------------------------
//
// SpriteEaseBounce
//
//------------------------------------------------------------------
var SpriteEaseBounce = EaseSpriteDemo.extend({
    onEnter:function () {
        this._super();

        var move = cc.MoveBy.create(3, cc.p(winSize.width-80, 0));
        var move_back = move.reverse();

        var move_ease_in = cc.EaseBounceIn.create(move.copy());
        var move_ease_in_back = move_ease_in.reverse();

        var move_ease_out = cc.EaseBounceOut.create(move.copy());
        var move_ease_out_back = move_ease_out.reverse();

        var seq1 = cc.Sequence.create(move, move_back);
        var seq2 = cc.Sequence.create(move_ease_in, move_ease_in_back);
        var seq3 = cc.Sequence.create(move_ease_out, move_ease_out_back);

        this._grossini.runAction(cc.RepeatForever.create(seq1));
        this._tamara.runAction(cc.RepeatForever.create(seq2));
        this._kathia.runAction(cc.RepeatForever.create(seq3));
    },
    title:function () {
        return "Bounce In - Out actions";
    }
});

//------------------------------------------------------------------
//
// SpriteEaseBounceInOut
//
//------------------------------------------------------------------
var SpriteEaseBounceInOut = EaseSpriteDemo.extend({
    onEnter:function () {
        this._super();

        var move = cc.MoveBy.create(3, cc.p(winSize.width-80, 0));
        var move_back = move.reverse();

        var move_ease = cc.EaseBounceInOut.create(move.copy());
        var move_ease_back = move_ease.reverse();

        var seq1 = cc.Sequence.create(move, move_back);
        var seq2 = cc.Sequence.create(move_ease, move_ease_back);

        this.positionForTwo();

        this._grossini.runAction(cc.RepeatForever.create(seq1));
        this._tamara.runAction(cc.RepeatForever.create(seq2));
    },
    title:function () {
        return "EaseBounceInOut action";
    }
});

//------------------------------------------------------------------
//
// SpriteEaseBack
//
//------------------------------------------------------------------
var SpriteEaseBack = EaseSpriteDemo.extend({
    onEnter:function () {
        this._super();

        var move = cc.MoveBy.create(3, cc.p(winSize.width-80, 0));
        var move_back = move.reverse();

        var move_ease_in = cc.EaseBackIn.create(move.copy());
        var move_ease_in_back = move_ease_in.reverse();

        var move_ease_out = cc.EaseBackOut.create(move.copy());
        var move_ease_out_back = move_ease_out.reverse();

        var seq1 = cc.Sequence.create(move, move_back);
        var seq2 = cc.Sequence.create(move_ease_in, move_ease_in_back);
        var seq3 = cc.Sequence.create(move_ease_out, move_ease_out_back);

        this._grossini.runAction(cc.RepeatForever.create(seq1));
        this._tamara.runAction(cc.RepeatForever.create(seq2));
        this._kathia.runAction(cc.RepeatForever.create(seq3));
    },
    title:function () {
        return "Back In - Out actions";
    }
});

//------------------------------------------------------------------
//
// SpriteEaseBackInOut
//
//------------------------------------------------------------------
var SpriteEaseBackInOut = EaseSpriteDemo.extend({
    onEnter:function () {
        this._super();

        var move = cc.MoveBy.create(3, cc.p(winSize.width-80, 0));
        var move_back = move.reverse();

        var move_ease = cc.EaseBackInOut.create(move.copy());
        var move_ease_back = move_ease.reverse();

        var seq1 = cc.Sequence.create(move, move_back);
        var seq2 = cc.Sequence.create(move_ease, move_ease_back);

        this.positionForTwo();

        this._grossini.runAction(cc.RepeatForever.create(seq1));
        this._tamara.runAction(cc.RepeatForever.create(seq2));
    },
    title:function () {
        return "EaseBackInOut action";
    }
});

var SpeedTest = EaseSpriteDemo.extend({
    onEnter:function () {
        this._super();

        // rotate and jump
        var jump1 = cc.JumpBy.create(4, cc.p(-winSize.width+80, 0), 100, 4);
        var jump2 = jump1.reverse();
        var rot1 = cc.RotateBy.create(4, 360 * 2);
        var rot2 = rot1.reverse();

        var seq3_1 = cc.Sequence.create(jump2, jump1);
        var seq3_2 = cc.Sequence.create(rot1, rot2);
        var spawn = cc.Spawn.create(seq3_1, seq3_2);
        var action = cc.Speed.create(cc.RepeatForever.create(spawn), 1.0);
        action.setTag(TAG_ACTION1_EASE_ACTIONS);

        var action2 = action.copy();
        var action3 = action.copy();

        action2.setTag(TAG_ACTION1_EASE_ACTIONS);
        action3.setTag(TAG_ACTION1_EASE_ACTIONS);

        this._grossini.runAction(action2);
        this._tamara.runAction(action3);
        this._kathia.runAction(action);

        this.schedule(this.altertime, 1.0);//:@selector(altertime:) interval:1.0];
    },
    title:function () {
        return "Speed action";
    },

    altertime:function (dt) {
        var action1 = this._grossini.getActionByTag(TAG_ACTION1_EASE_ACTIONS);
        var action2 = this._tamara.getActionByTag(TAG_ACTION1_EASE_ACTIONS);
        var action3 = this._kathia.getActionByTag(TAG_ACTION1_EASE_ACTIONS);

        action1.setSpeed(Math.random() * 2);
        action2.setSpeed(Math.random() * 2);
        action3.setSpeed(Math.random() * 2);
    }
});

//------------------------------------------------------------------
//
// SchedulerTest
//
//------------------------------------------------------------------
var SchedulerTest = EaseSpriteDemo.extend({
    onEnter:function () {
        this._super();

        // rotate and jump
        var jump1 = cc.JumpBy.create(4, cc.p(-winSize.width+80, 0), 100, 4);
        var jump2 = jump1.reverse();
        var rot1 = cc.RotateBy.create(4, 360 * 2);
        var rot2 = rot1.reverse();

        var seq3_1 = cc.Sequence.create(jump2, jump1);
        var seq3_2 = cc.Sequence.create(rot1, rot2);
        var spawn = cc.Spawn.create(seq3_1, seq3_2);
        var action = cc.RepeatForever.create(spawn);

        var action2 = action.copy();
        var action3 = action.copy();

        this._grossini.runAction(cc.Speed.create(action, 0.5));
        this._tamara.runAction(cc.Speed.create(action2, 1.5));
        this._kathia.runAction(cc.Speed.create(action3, 1.0));

        var emitter = new cc.ParticleFireworks();
        emitter.initWithTotalParticles(250);
        emitter.setTexture(cc.TextureCache.getInstance().addImage("res/Images/fire.png"));
        this.addChild(emitter);
    },
    title:function () {
        return "Scheduler scaleTime Test";
    }
});

//
// Flow control
//
var arrayOfEaseActionsTest = [
    SpriteEase,
    SpriteEaseInOut,
    SpriteEaseExponential,
    SpriteEaseExponentialInOut,
    SpriteEaseSine,
    SpriteEaseSineInOut,
    SpriteEaseElastic,
    SpriteEaseElasticInOut,
    SpriteEaseBounce,
    SpriteEaseBounceInOut,
    SpriteEaseBack,
    SpriteEaseBackInOut,
    SpeedTest,
    SchedulerTest
];

var nextEaseActionsTest = function () {
    sceneIdx++;
    sceneIdx = sceneIdx % arrayOfEaseActionsTest.length;

    return new arrayOfEaseActionsTest[sceneIdx]();
};
var previousEaseActionsTest = function () {
    sceneIdx--;
    if (sceneIdx < 0)
        sceneIdx += arrayOfEaseActionsTest.length;

    return new arrayOfEaseActionsTest[sceneIdx]();
};
var restartEaseActionsTest = function () {
    return new arrayOfEaseActionsTest[sceneIdx]();
};
