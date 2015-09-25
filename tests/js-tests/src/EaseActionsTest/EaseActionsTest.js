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

TAG_ACTION1_EASE_ACTIONS = 1;
TAG_ACTION2_EASE_ACTIONS = 2;
TAG_SLIDER_EASE_ACTIONS = 1;

var easeActionsTestIdx = -1;

// the class inherit from TestScene
// every .Scene each test used must inherit from TestScene,
// make sure the test have the menu item for back to main menu
var EaseActionsTestScene = TestScene.extend({
    runThisTest:function (num) {
        easeActionsTestIdx = (num || num == 0) ? (num - 1) : -1;
        this.addChild(nextEaseActionsTest());
        director.runScene(this);
    }
});


var EaseSpriteDemo = BaseTestLayer.extend({
    _grossini:null,
    _tamara:null,
    _kathia:null,
    _title:null,

    ctor:function () {
        this._super(cc.color(0, 0, 0, 255), cc.color(98, 99, 117, 255));
    },

    title:function () {
        return "No title";
    },
    onEnter:function () {
        this._super();

        // Or you can create an sprite using a filename. PNG and BMP files are supported. Probably TIFF too
        this._grossini = new cc.Sprite(s_pathGrossini);
        this._tamara = new cc.Sprite(s_pathSister1);
        this._kathia = new cc.Sprite(s_pathSister2);

        this.addChild(this._grossini, 3);
        this.addChild(this._kathia, 2);
        this.addChild(this._tamara, 1);

        this._grossini.x = 60;

        this._grossini.y = winSize.height / 5;
        this._kathia.x = 60;
        this._kathia.y = winSize.height / 2;
        this._tamara.x = 60;
        this._tamara.y = winSize.height * 4 / 5;

        this.twoSprites = false;
    },

    onRestartCallback:function (sender) {
        var s = new EaseActionsTestScene();//cc.Scene.create();
        s.addChild(restartEaseActionsTest());
        director.runScene(s);
    },
    onNextCallback:function (sender) {
        var s = new EaseActionsTestScene();//cc.Scene.create();
        s.addChild(nextEaseActionsTest());
        director.runScene(s);
    },
    onBackCallback:function (sender) {
        var s = new EaseActionsTestScene();//cc.Scene.create();
        s.addChild(previousEaseActionsTest());
        director.runScene(s);
    },
    positionForTwo:function () {
        this.twoSprites = true;
        this._grossini.x = 60;
	    this._grossini.y = winSize.height / 5;
        this._tamara.x = 60;
	    this._tamara.y = winSize.height * 4 / 5;
        this._kathia.visible = false;
    },

    //
    // Automation
    //
    numberOfPendingTests:function() {
        return ( (arrayOfEaseActionsTest.length-1) - easeActionsTestIdx );
    },

    getTestNumber:function() {
        return easeActionsTestIdx;
    },

    // default values for automation
    testDuration:2.05,
    getExpectedResult:function() {
        var ret;
        var w = 60 + winSize.width - 80;
        if( this.twoSprites )
            ret = [w, w];
        else
            ret = [w, w, w];
        return JSON.stringify(ret);
    },

    getCurrentResult:function() {
        var ret;
        if( this.twoSprites)
            ret = [ this._grossini.x, this._tamara.x];
        else
            ret = [ this._grossini.x, this._tamara.x, this._kathia.x ];
        return JSON.stringify(ret);
    }

});

//------------------------------------------------------------------
//
// SpriteEase
//
//------------------------------------------------------------------
var SpriteEase = EaseSpriteDemo.extend({

    onEnter:function () {
        //----start0----onEnter
        this._super();

        var move = cc.moveBy(2, cc.p(winSize.width - 80, 0));
        var move_back = move.reverse();

        //old api
        //var move_ease_in = cc.EaseIn.create(move.clone(), 2.0);

        var move_ease_in = move.clone().easing(cc.easeIn(2.0));
        var move_ease_in_back = move_ease_in.reverse();

        //old api
        //var move_ease_out = cc.EaseOut.create(move.clone(), 2.0);

        var move_ease_out = move.clone().easing(cc.easeOut(2.0));
        var move_ease_out_back = move_ease_out.reverse();


        var delay = cc.delayTime(0.10);

        var seq1 = cc.sequence(move, delay, move_back, delay.clone());
        var seq2 = cc.sequence(move_ease_in, delay.clone(), move_ease_in_back, delay.clone());
        var seq3 = cc.sequence(move_ease_out, delay.clone(), move_ease_out_back, delay.clone());


        var a2 = this._grossini.runAction(seq1.repeatForever());
        a2.tag = 1;

        var a1 = this._tamara.runAction(seq2.repeatForever());
        a1.tag = 1;

        var a = this._kathia.runAction(seq3.repeatForever());
        a.tag = 1;

        this.scheduleOnce(this.testStopAction, 4.1);
        //----end0----
    },
    title:function () {
        return "EaseIn - EaseOut - Stop";
    },

    testStopAction:function (dt) {
        this._tamara.stopActionByTag(1);
        this._kathia.stopActionByTag(1);
        this._grossini.stopActionByTag(1);
    },

    //
    // Automation
    //
    testDuration:4.2,
    getExpectedResult:function() {
        var ret = [60,60,60];
        return JSON.stringify(ret);
    },

    getCurrentResult:function() {
        var ret = [ this._grossini.x, this._tamara.x, this._kathia.x ];
        return JSON.stringify(ret);
    }

});

//------------------------------------------------------------------
//
// SpriteEaseInOut
//
//------------------------------------------------------------------
var SpriteEaseInOut = EaseSpriteDemo.extend({

    onEnter:function () {
        //----start1----onEnter
        this._super();

        var move = cc.moveBy(2, cc.p(winSize.width - 80, 0));
        //	id move_back = move.reverse();

        //old api
        //var move_ease_inout1 = cc.EaseInOut.create(move.clone(), 2.0);

        var move_ease_inout1 = move.clone().easing(cc.easeInOut(2.0));
        var move_ease_inout_back1 = move_ease_inout1.reverse();

        //old api
        //var move_ease_inout2 = cc.EaseInOut.create(move.clone(), 3.0);

        var move_ease_inout2 = move.clone().easing(cc.easeInOut(3.0));
        var move_ease_inout_back2 = move_ease_inout2.reverse();

        //old api
        //var move_ease_inout3 = cc.EaseInOut.create(move.clone(), 4.0);

        var move_ease_inout3 = move.clone().easing(cc.easeInOut(4.0));
        var move_ease_inout_back3 = move_ease_inout3.reverse();

        var delay = cc.delayTime(0.1);

        var seq1 = cc.sequence(move_ease_inout1, delay, move_ease_inout_back1, delay.clone());
        var seq2 = cc.sequence(move_ease_inout2, delay.clone(), move_ease_inout_back2, delay.clone());
        var seq3 = cc.sequence(move_ease_inout3, delay.clone(), move_ease_inout_back3, delay.clone());

        this._tamara.runAction(seq1.repeatForever());
        this._kathia.runAction(seq2.repeatForever());
        this._grossini.runAction(seq3.repeatForever());
        //----end1----
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
        //----start2----onEnter
        this._super();

        var move = cc.moveBy(2, cc.p(winSize.width - 80, 0));
        var move_back = move.reverse();

        //old api
        //var move_ease_in = cc.EaseExponentialIn.create(move.clone());

        var move_ease_in = move.clone().easing(cc.easeExponentialIn());
        var move_ease_in_back = move_ease_in.reverse();

        var move_ease_out = move.clone().easing(cc.easeExponentialOut());
        var move_ease_out_back = move_ease_out.reverse();

        var delay = cc.delayTime(0.1);

        var seq1 = cc.sequence(move, delay, move_back, delay.clone());
        var seq2 = cc.sequence(move_ease_in, delay.clone(), move_ease_in_back, delay.clone());
        var seq3 = cc.sequence(move_ease_out, delay.clone(), move_ease_out_back, delay.clone());


        this._grossini.runAction(seq1.repeatForever());
        this._tamara.runAction(seq2.repeatForever());
        this._kathia.runAction(seq3.repeatForever());
        //----end2-----
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
        //----start3----onEnter
        this._super();

        var move = cc.moveBy(2, cc.p(winSize.width - 80, 0));
        var move_back = move.reverse();

        //old api
        //var move_ease = cc.EaseExponentialInOut.create(move.clone());

        var move_ease = move.clone().easing(cc.easeExponentialInOut());
        var move_ease_back = move_ease.reverse();

        var delay = cc.delayTime(0.1);

        var seq1 = cc.sequence(move, delay, move_back, delay.clone());
        var seq2 = cc.sequence(move_ease, delay.clone(), move_ease_back, delay.clone());

        this.positionForTwo();

        this._grossini.runAction(seq1.repeatForever());
        this._tamara.runAction(seq2.repeatForever());
        //----end3----
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
        //----start4----onEnter
        this._super();

        var move = cc.moveBy(2, cc.p(winSize.width - 80, 0));
        var move_back = move.reverse();

        //old api
        //var move_ease_in = cc.EaseSineIn.create(move.clone());

        var move_ease_in = move.clone().easing(cc.easeSineIn());
        var move_ease_in_back = move_ease_in.reverse();

        //old api
        //var move_ease_out = cc.EaseSineOut.create(move.clone());

        var move_ease_out = move.clone().easing(cc.easeSineOut());
        var move_ease_out_back = move_ease_out.reverse();

        var delay = cc.delayTime(0.1);

        var seq1 = cc.sequence(move, delay, move_back, delay.clone());
        var seq2 = cc.sequence(move_ease_in, delay, move_ease_in_back, delay.clone());
        var seq3 = cc.sequence(move_ease_out, delay, move_ease_out_back, delay.clone());


        this._grossini.runAction(seq1.repeatForever());
        this._tamara.runAction(seq2.repeatForever());
        this._kathia.runAction(seq3.repeatForever());
        //----end4----
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
        //----start5----onEnter
        this._super();

        var move = cc.moveBy(2, cc.p(winSize.width - 80, 0));
        var move_back = move.reverse();

        //old api
        //var move_ease = cc.EaseSineInOut.create(move.clone());

        var move_ease = move.clone().easing(cc.easeSineInOut());
        var move_ease_back = move_ease.reverse();

        var delay = cc.delayTime(0.1);

        var seq1 = cc.sequence(move, delay, move_back, delay.clone());
        var seq2 = cc.sequence(move_ease, delay.clone(), move_ease_back, delay.clone());

        this.positionForTwo();

        this._grossini.runAction(seq1.repeatForever());
        this._tamara.runAction(seq2.repeatForever());
        //----end5----
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
        //----start6----onEnter
        this._super();

        var move = cc.moveBy(2, cc.p(winSize.width - 80, 0));
        var move_back = move.reverse();

        //old api
        //var move_ease_in = cc.EaseElasticIn.create(move.clone());

        var move_ease_in = move.clone().easing(cc.easeElasticIn());
        var move_ease_in_back = move_ease_in.reverse();

        //old api
        //var move_ease_out = cc.EaseElasticOut.create(move.clone());

        var move_ease_out = move.clone().easing(cc.easeElasticOut());
        var move_ease_out_back = move_ease_out.reverse();

        var delay = cc.delayTime(0.1);

        var seq1 = cc.sequence(move, delay, move_back, delay.clone());
        var seq2 = cc.sequence(move_ease_in, delay.clone(), move_ease_in_back, delay.clone());
        var seq3 = cc.sequence(move_ease_out, delay.clone(), move_ease_out_back, delay.clone());

        this._grossini.runAction(seq1.repeatForever());
        this._tamara.runAction(seq2.repeatForever());
        this._kathia.runAction(seq3.repeatForever());
        //----end6----
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
        //----start7----onEnter
        this._super();

        var move = cc.moveBy(2, cc.p(winSize.width - 80, 0));

        //old api
        //var move_ease_inout1 = cc.EaseElasticInOut.create(move.clone(), 0.3);

        var move_ease_inout1 = move.clone().easing(cc.easeElasticInOut(0.3));
        var move_ease_inout_back1 = move_ease_inout1.reverse();

        //old api
        //var move_ease_inout2 = cc.EaseElasticInOut.create(move.clone(), 0.45);

        var move_ease_inout2 = move.clone().easing(cc.easeElasticInOut(0.45));
        var move_ease_inout_back2 = move_ease_inout2.reverse();

        //old api
        //var move_ease_inout3 = cc.EaseElasticInOut.create(move.clone(), 0.6);

        var move_ease_inout3 = move.clone().easing(cc.easeElasticInOut(0.6));
        var move_ease_inout_back3 = move_ease_inout3.reverse();

        var delay = cc.delayTime(0.1);

        var seq1 = cc.sequence(move_ease_inout1, delay, move_ease_inout_back1, delay.clone());
        var seq2 = cc.sequence(move_ease_inout2, delay.clone(), move_ease_inout_back2, delay.clone());
        var seq3 = cc.sequence(move_ease_inout3, delay.clone(), move_ease_inout_back3, delay.clone());

        this._tamara.runAction(seq1.repeatForever());
        this._kathia.runAction(seq2.repeatForever());
        this._grossini.runAction(seq3.repeatForever());
        //----end7----
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
        //----start8----onEnter
        this._super();

        var move = cc.moveBy(2, cc.p(winSize.width - 80, 0));
        var move_back = move.reverse();

        //old api
        //var move_ease_in = cc.EaseBounceIn.create(move.clone());

        var move_ease_in = move.clone().easing(cc.easeBounceIn());
        var move_ease_in_back = move_ease_in.reverse();

        //old api
        //var move_ease_out = cc.EaseBounceOut.create(move.clone());

        var move_ease_out = move.clone().easing(cc.easeBounceOut());
        var move_ease_out_back = move_ease_out.reverse();

        var delay = cc.delayTime(0.1);

        var seq1 = cc.sequence(move, delay, move_back, delay.clone());
        var seq2 = cc.sequence(move_ease_in, delay.clone(), move_ease_in_back, delay.clone());
        var seq3 = cc.sequence(move_ease_out, delay.clone(), move_ease_out_back, delay.clone());

        this._grossini.runAction(seq1.repeatForever());
        this._tamara.runAction(seq2.repeatForever());
        this._kathia.runAction(seq3.repeatForever());
        //----end8----
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
        //----start9----onEnter
        this._super();

        var move = cc.moveBy(2, cc.p(winSize.width - 80, 0));
        var move_back = move.reverse();

        //old api
        //var move_ease = cc.EaseBounceInOut.create(move.clone());

        var move_ease = move.clone().easing(cc.easeBounceInOut());
        var move_ease_back = move_ease.reverse();

        var delay = cc.delayTime(0.1);

        var seq1 = cc.sequence(move, delay, move_back, delay.clone());
        var seq2 = cc.sequence(move_ease, delay.clone(), move_ease_back, delay.clone());

        this.positionForTwo();

        this._grossini.runAction(seq1.repeatForever());
        this._tamara.runAction(seq2.repeatForever());
        //----end9----
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
        //----start10----onEnter
        this._super();

        var move = cc.moveBy(2, cc.p(winSize.width - 80, 0));
        var move_back = move.reverse();

        //old api
        //var move_ease_in = cc.EaseBackIn.create(move.clone());

        var move_ease_in = move.clone().easing(cc.easeBackIn());
        var move_ease_in_back = move_ease_in.reverse();

        //old api
        //var move_ease_out = cc.EaseBackOut.create(move.clone());

        var move_ease_out = move.clone().easing(cc.easeBackOut());
        var move_ease_out_back = move_ease_out.reverse();

        var delay = cc.delayTime(0.1);

        var seq1 = cc.sequence(move, delay, move_back, delay.clone());
        var seq2 = cc.sequence(move_ease_in, delay.clone(), move_ease_in_back, delay.clone());
        var seq3 = cc.sequence(move_ease_out, delay.clone(), move_ease_out_back, delay.clone());

        this._grossini.runAction(seq1.repeatForever());
        this._tamara.runAction(seq2.repeatForever());
        this._kathia.runAction(seq3.repeatForever());
        //----end10----
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
        //----start11----onEnter
        this._super();

        var move = cc.moveBy(2, cc.p(winSize.width - 80, 0));
        var move_back = move.reverse();

        //old api
        //var move_ease = cc.EaseBackInOut.create(move.clone());

        var move_ease = move.clone().easing(cc.easeBackInOut());
        var move_ease_back = move_ease.reverse();

        var delay = cc.delayTime(0.1);

        var seq1 = cc.sequence(move, delay, move_back, delay.clone());
        var seq2 = cc.sequence(move_ease, delay.clone(), move_ease_back, delay.clone());

        this.positionForTwo();

        this._grossini.runAction(seq1.repeatForever());
        this._tamara.runAction(seq2.repeatForever());
        //----end11----
    },
    title:function () {
        return "EaseBackInOut action";
    }
});

var SpeedTest = EaseSpriteDemo.extend({
    onEnter:function () {
        //----start12----onEnter
        this._super();

        // rotate and jump
        var jump1 = cc.jumpBy(4, cc.p(-winSize.width + 80, 0), 100, 4);
        var jump2 = jump1.reverse();
        var rot1 = cc.rotateBy(4, 360 * 2);
        var rot2 = rot1.reverse();

        var seq3_1 = cc.sequence(jump2, jump1);
        var seq3_2 = cc.sequence(rot1, rot2);
        var spawn = cc.spawn(seq3_1, seq3_2);

        var action = spawn.repeatForever().speed(2);
        action.tag = TAG_ACTION1_EASE_ACTIONS;

        var action2 = action.clone();
        var action3 = action.clone();

        action2.tag = TAG_ACTION1_EASE_ACTIONS;
        action3.tag = TAG_ACTION1_EASE_ACTIONS;

        this._grossini.runAction(action2);
        this._tamara.runAction(action3);
        this._kathia.runAction(action);

        this.schedule(this.altertime, 1.0);
        //----end12----
    },
    title:function () {
        return "Speed action";
    },

    altertime:function (dt) {
        //----start12----altertime
        var action1 = this._grossini.getActionByTag(TAG_ACTION1_EASE_ACTIONS);
        var action2 = this._tamara.getActionByTag(TAG_ACTION1_EASE_ACTIONS);
        var action3 = this._kathia.getActionByTag(TAG_ACTION1_EASE_ACTIONS);

        action1.setSpeed(Math.random() * 2);
        action2.setSpeed(Math.random() * 2);
        action3.setSpeed(Math.random() * 2);
        //----end12----
    },
    // automation
    testDuration:0.1,
    getExpectedResult:function() {
        throw "Not Implemented";
    },
    getCurrentResult:function() {
        throw "Not Implemented";
    }
});

//------------------------------------------------------------------
//
// SchedulerTest
//
//------------------------------------------------------------------
var SchedulerTest = EaseSpriteDemo.extend({
    onEnter:function () {
        //----start13----onEnter
        this._super();

        // rotate and jump
        var jump1 = cc.jumpBy(4, cc.p(-winSize.width + 80, 0), 100, 4);
        var jump2 = jump1.reverse();
        var rot1 = cc.rotateBy(4, 360 * 2);
        var rot2 = rot1.reverse();

        var seq3_1 = cc.sequence(jump2, jump1);
        var seq3_2 = cc.sequence(rot1, rot2);
        var spawn = cc.spawn(seq3_1, seq3_2);
        var action = spawn.repeatForever();

        var action2 = action.clone();
        var action3 = action.clone();

        //old api
        //this._grossini.runAction(cc.speed(action, 0.5));
        //this._tamara.runAction(cc.speed(action2, 1.5));
        //this._kathia.runAction(cc.speed(action3, 1.0));

        this._grossini.runAction(action.speed(0.5));
        this._tamara.runAction(action2.speed(1.5));
        this._kathia.runAction(action3.speed(1.0));

        var emitter = new cc.ParticleFireworks();
        emitter.setTotalParticles(250);
        emitter.texture = cc.textureCache.addImage("Images/fire.png");
        this.addChild(emitter);
        //----end13----
    },
    title:function () {
        return "Scheduler scaleTime Test";
    },

    // automation
    testDuration:0.1,
    getExpectedResult:function() {
        throw "Not Implemented";
    },
    getCurrentResult:function() {
        throw "Not Implemented";
    }
});

//
// SpriteEaseBezier action
//
var SpriteEaseBezierTest = EaseSpriteDemo.extend({

    onEnter: function(){
        this._super();
        //----start14----onEnter

        var size = director.getWinSize();

        //
        // startPosition can be any coordinate, but since the movement
        // is relative to the Bezier curve, make it (0,0)
        //

        this._grossini.setPosition( cc.p(size.width/2, size.height/2));
        this._tamara.setPosition( cc.p(size.width/4, size.height/2));
        this._kathia.setPosition( cc.p(3 * size.width/4, size.height/2));

        // sprite 1
        var bezier = [
            cc.p(0, size.height / 2),
            cc.p(300 / 480 * 800, -size.height / 2),
            cc.p(300 / 480 * 800, 100 / 320 * 450)
        ];
        var bezierForward = cc.bezierBy(3, bezier);
        //var bezierEaseForward = cc.EaseBezierAction.create(bezierForward);
        //bezierEaseForward.setBezierParamer(0.5, 0.5, 1.0, 1.0);
        var bezierEaseForward = bezierForward.easing(cc.easeBezierAction(0.5, 0.5, 1.0, 1.0));

        var bezierEaseBack = bezierEaseForward.reverse();
        var bezierEaseTo = cc.sequence(bezierEaseForward, bezierEaseBack).repeatForever();

        // sprite 2
        this._tamara.setPosition(cc.p(135,225));
        var bezier2 = [
            cc.p(100 / 480 * 800, size.height / 2),
            cc.p(200 / 480 * 800, -size.height / 2),
            cc.p(200 / 480 * 800, 160 / 320 * 450)
        ];
        var bezierTo1 = cc.bezierTo(2, bezier2);
        //var bezierEaseTo1 = cc.EaseBezierAction.create(bezierTo1);
        //bezierEaseTo1.setBezierParamer(0.5, 0.5, 1.0, 1.0);
        var bezierEaseTo1 = bezierTo1.easing(cc.easeBezierAction(0.5, 0.5, 1.0, 1.0));

        // sprite 3
        this._kathia.setPosition(cc.p(667, 225));
        var bezierTo2 = cc.bezierTo(2, bezier2);
        //var bezierEaseTo2 = cc.EaseBezierAction.create(bezierTo2);
        //bezierEaseTo2.setBezierParamer(0.0, 0.5, -5.0, 1.0);
        var bezierEaseTo2 = bezierTo2.easing(cc.easeBezierAction(0.0, 0.5, -5.0, 1.0));


        this._grossini.runAction(bezierEaseTo);
        this._tamara.runAction(bezierEaseTo1);
        this._kathia.runAction(bezierEaseTo2);

        //----end14----
    },
    title: function(){
        return "SpriteEaseBezier action";
    }
});


//
// SpriteEaseQuadratic
//
var SpriteEaseQuadraticTest = EaseSpriteDemo.extend({

    onEnter: function(){
        this._super();
        //----start15----onEnter

        var move = cc.moveBy(3, cc.p(winSize.width - 130, 0));
        var move_back = move.reverse();

        //var move_ease_in = cc.EaseQuadraticActionIn.create(move.clone());
        var move_ease_in = move.clone().easing(cc.easeQuadraticActionIn());
        var move_ease_in_back = move_ease_in.reverse();

        //var move_ease_out = cc.EaseQuadraticActionOut.create(move.clone());
        var move_ease_out = move.clone().easing(cc.easeQuadraticActionOut());
        var move_ease_out_back = move_ease_out.reverse();

        var delay = cc.delayTime(0.25);

        var seq1 = cc.sequence(move, delay, move_back, delay.clone());
        var seq2 = cc.sequence(move_ease_in, delay.clone(), move_ease_in_back, delay.clone());
        var seq3 = cc.sequence(move_ease_out, delay.clone(), move_ease_out_back, delay.clone());

        this._grossini.runAction( seq1.repeatForever() );
        this._tamara.runAction( seq2.repeatForever() );
        this._kathia.runAction( seq3.repeatForever() );

        //----end15----
    },
    title: function(){
        return "SpriteEaseQuadratic action";
    }
});

//
// SpriteEaseQuadraticInOut
//
var SpriteEaseQuadraticInOutTest = EaseSpriteDemo.extend({

    onEnter: function(){
        this._super();
        //----start16----onEnter

        var move = cc.moveBy(3, cc.p(winSize.width - 130, 0));
        var move_back = move.reverse();

        //var move_ease = cc.EaseQuadraticActionInOut.create(move.clone());
        var move_ease = move.clone().easing(cc.easeQuadraticActionInOut());
        var move_ease_back = move_ease.reverse();

        var delay = cc.delayTime(0.25);

        var seq1 = cc.sequence(move, delay, move_back, delay.clone()).repeatForever();
        var seq2 = cc.sequence(move_ease, delay.clone(), move_ease_back, delay.clone()).repeatForever();

        this.positionForTwo();

        this._grossini.runAction( seq1 );
        this._tamara.runAction( seq2 );
        //----end16----
    },
    title: function(){
        return "SpriteEaseQuadraticInOut action";
    }
});

//
// SpriteEaseQuartic
//
var SpriteEaseQuarticTest = EaseSpriteDemo.extend({

    onEnter: function(){
        this._super();
        //----start17----onEnter

        var move = cc.moveBy(3, cc.p(winSize.width - 130, 0));
        var move_back = move.reverse();

        //var move_ease_in = cc.EaseQuarticActionIn.create(move.clone() );
        var move_ease_in = move.clone().easing(cc.easeQuarticActionIn());
        var move_ease_in_back = move_ease_in.reverse();

        //var move_ease_out = cc.EaseQuarticActionOut.create(move.clone() );
        var move_ease_out = move.clone().easing(cc.easeQuarticActionOut());
        var move_ease_out_back = move_ease_out.reverse();

        var delay = cc.delayTime(0.25);

        var seq1 = cc.sequence(move, delay, move_back, delay.clone());
        var seq2 = cc.sequence(move_ease_in, delay.clone(), move_ease_in_back, delay.clone());
        var seq3 = cc.sequence(move_ease_out, delay.clone(), move_ease_out_back, delay.clone());

        this._grossini.runAction( seq1.repeatForever() );
        this._tamara.runAction( seq2.repeatForever() );
        this._kathia.runAction( seq3.repeatForever() );
        //----end17----
    },
    title: function(){
        return "SpriteEaseQuartic action";
    }
});

//
// SpriteEaseQuarticInOut
//
var SpriteEaseQuarticInOutTest = EaseSpriteDemo.extend({
    onEnter: function(){
        this._super();
        //----start18----onEnter

        var move = cc.moveBy(3, cc.p(winSize.width - 130, 0));
        var move_back = move.reverse();

        //var move_ease = cc.EaseQuarticActionInOut.create(move.clone() );
        var move_ease = move.clone().easing(cc.easeQuarticActionInOut());
        var move_ease_back = move_ease.reverse();

        var delay = cc.delayTime(0.25);

        var seq1 = cc.sequence(move, delay, move_back, delay.clone());
        var seq2 = cc.sequence(move_ease, delay.clone(), move_ease_back, delay.clone());

        this.positionForTwo();

        this._grossini.runAction( seq1.repeatForever() );
        this._tamara.runAction( seq2.repeatForever() );

        //----end18----
    },
    title: function(){
        return "SpriteEaseQuarticInOut action";
    }
});

//
// SpriteEaseQuintic
//
var SpriteEaseQuinticTest = EaseSpriteDemo.extend({
    onEnter: function(){
        this._super();
        //----start19----onEnter

        var move = cc.moveBy(3, cc.p(winSize.width - 130, 0));
        var move_back = move.reverse();

        //var move_ease_in = cc.EaseQuinticActionIn.create(move.clone() );
        var move_ease_in = move.clone().easing(cc.easeQuinticActionIn());
        var move_ease_in_back = move_ease_in.reverse();

        //var move_ease_out = cc.EaseQuinticActionOut.create(move.clone() );
        var move_ease_out = move.clone().easing(cc.easeQuinticActionOut());
        var move_ease_out_back = move_ease_out.reverse();

        var delay = cc.delayTime(0.25);

        var seq1 = cc.sequence(move, delay, move_back, delay.clone());
        var seq2 = cc.sequence(move_ease_in, delay.clone(), move_ease_in_back, delay.clone());
        var seq3 = cc.sequence(move_ease_out, delay.clone(), move_ease_out_back, delay.clone());

        this._grossini.runAction( seq1.repeatForever() );
        this._tamara.runAction( seq2.repeatForever() );
        this._kathia.runAction( seq3.repeatForever() );


        //----end19----
    },
    title: function(){
        return "SpriteEaseQuintic action";
    }
});

//
// SpriteEaseQuinticInOut
//
var SpriteEaseQuinticInOutTest = EaseSpriteDemo.extend({
    onEnter: function(){
        this._super();
        //----start20----onEnter

        var move = cc.moveBy(3, cc.p(winSize.width - 130, 0));
        var move_back = move.reverse();

        //var move_ease = cc.EaseQuinticActionInOut.create(move.clone() );
        var move_ease = move.clone().easing(cc.easeQuinticActionInOut());
        var move_ease_back = move_ease.reverse();

        var delay = cc.delayTime(0.25);

        var seq1 = cc.sequence(move, delay, move_back, delay.clone());
        var seq2 = cc.sequence(move_ease, delay.clone(), move_ease_back, delay.clone());

        this.positionForTwo();

        this._grossini.runAction( seq1.repeatForever() );
        this._tamara.runAction( seq2.repeatForever() );

        //----end20----
    },
    title: function(){
        return "SpriteEaseQuinticInOut action";
    }
});

//
// SpriteEaseCircle
//
var SpriteEaseCircleTest = EaseSpriteDemo.extend({
    onEnter: function(){
        this._super();
        //----start21----onEnter

        var move = cc.moveBy(3, cc.p(winSize.width - 130, 0));
        var move_back = move.reverse();

        //var move_ease_in = cc.EaseCircleActionIn.create(move.clone() );
        var move_ease_in = move.clone().easing(cc.easeCircleActionIn());
        var move_ease_in_back = move_ease_in.reverse();

        //var move_ease_out = cc.EaseCircleActionOut.create(move.clone() );
        var move_ease_out = move.clone().easing(cc.easeCircleActionOut());
        var move_ease_out_back = move_ease_out.reverse();

        var delay = cc.delayTime(0.25);

        var seq1 = cc.sequence(move, delay, move_back, delay.clone());
        var seq2 = cc.sequence(move_ease_in, delay.clone(), move_ease_in_back, delay.clone());
        var seq3 = cc.sequence(move_ease_out, delay.clone(), move_ease_out_back, delay.clone());

        this._grossini.runAction( seq1.repeatForever() );
        this._tamara.runAction( seq2.repeatForever() );
        this._kathia.runAction( seq3.repeatForever() );

        //----end21----
    },
    title: function(){
        return "SpriteEaseCircle action";
    }
});

//
// SpriteEaseCircleInOut
//
var SpriteEaseCircleInOutTest = EaseSpriteDemo.extend({
    onEnter: function(){
        this._super();
        //----start22----onEnter

        var move = cc.moveBy(3, cc.p(winSize.width - 130, 0));
        var move_back = move.reverse();

        //var move_ease = cc.EaseCircleActionInOut.create(move.clone() );
        var move_ease = move.clone().easing(cc.easeCircleActionInOut());
        var move_ease_back = move_ease.reverse();

        var delay = cc.delayTime(0.25);

        var seq1 = cc.sequence(move, delay, move_back, delay.clone());
        var seq2 = cc.sequence(move_ease, delay.clone(), move_ease_back, delay.clone());

        this.positionForTwo();

        this._grossini.runAction( seq1.repeatForever() );
        this._tamara.runAction( seq2.repeatForever() );

        //----end22----
    },
    title: function(){
        return "SpriteEaseCircleInOut action";
    }
});

//
// SpriteEaseCubic
//
var SpriteEaseCubicTest = EaseSpriteDemo.extend({
    onEnter: function(){
        this._super();
        //----start23----onEnter

        var move = cc.moveBy(3, cc.p(winSize.width - 130, 0));
        var move_back = move.reverse();

        //var move_ease_in = cc.EaseCubicActionIn.create(move.clone() );
        var move_ease_in = move.clone().easing(cc.easeCubicActionIn());
        var move_ease_in_back = move_ease_in.reverse();

        //var move_ease_out = cc.EaseCubicActionOut.create(move.clone() );
        var move_ease_out = move.clone().easing(cc.easeCubicActionOut());
        var move_ease_out_back = move_ease_out.reverse();

        var delay = cc.delayTime(0.25);

        var seq1 = cc.sequence(move, delay, move_back, delay.clone());
        var seq2 = cc.sequence(move_ease_in, delay.clone(), move_ease_in_back, delay.clone());
        var seq3 = cc.sequence(move_ease_out, delay.clone(), move_ease_out_back, delay.clone());

        this._grossini.runAction( seq1.repeatForever() );
        this._tamara.runAction( seq2.repeatForever() );
        this._kathia.runAction( seq3.repeatForever() );


        //----end23----
    },
    title: function(){
        return "SpriteEaseCubic action";
    }
});

//
// SpriteEaseCubicInOut
//
var SpriteEaseCubicInOutTest = EaseSpriteDemo.extend({
    onEnter: function(){
        this._super();
        //----start24----onEnter

        var move = cc.moveBy(3, cc.p(winSize.width - 130, 0));
        var move_back = move.reverse();

        //var move_ease = cc.EaseCubicActionInOut.create(move.clone() );
        var move_ease = move.clone().easing(cc.easeCubicActionInOut());
        var move_ease_back = move_ease.reverse();

        var delay = cc.delayTime(0.25);

        var seq1 = cc.sequence(move, delay, move_back, delay.clone());
        var seq2 = cc.sequence(move_ease, delay.clone(), move_ease_back, delay.clone());

        this.positionForTwo();

        this._grossini.runAction( seq1.repeatForever() );
        this._tamara.runAction( seq2.repeatForever() );


        //----end24----
    },
    title: function(){
        return "SpriteEaseCubicInOut action";
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
    SchedulerTest,
    SpriteEaseBezierTest,
    SpriteEaseQuadraticTest,
    SpriteEaseQuadraticInOutTest,
    SpriteEaseQuarticTest,
    SpriteEaseQuarticInOutTest,
    SpriteEaseQuinticTest,
    SpriteEaseQuinticInOutTest,
    SpriteEaseCircleTest,
    SpriteEaseCircleInOutTest,
    SpriteEaseCubicTest,
    SpriteEaseCubicInOutTest
];

var nextEaseActionsTest = function () {
    easeActionsTestIdx++;
    easeActionsTestIdx = easeActionsTestIdx % arrayOfEaseActionsTest.length;

    if(window.sideIndexBar){
        easeActionsTestIdx = window.sideIndexBar.changeTest(easeActionsTestIdx, 10);
    }

    return new arrayOfEaseActionsTest[easeActionsTestIdx]();
};
var previousEaseActionsTest = function () {
    easeActionsTestIdx--;
    if (easeActionsTestIdx < 0)
        easeActionsTestIdx += arrayOfEaseActionsTest.length;

    if(window.sideIndexBar){
        easeActionsTestIdx = window.sideIndexBar.changeTest(easeActionsTestIdx, 10);
    }

    return new arrayOfEaseActionsTest[easeActionsTestIdx]();
};
var restartEaseActionsTest = function () {
    return new arrayOfEaseActionsTest[easeActionsTestIdx]();
};
