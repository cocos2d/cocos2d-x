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


var actionsTestIdx = -1;

var SPRITE_GROSSINI_TAG = 1;
var SPRITE_TAMARA_TAG = 2;
var SPRITE_KATHIA_TAG = 3;

// the class inherit from TestScene
// every Scene each test used must inherit from TestScene,
// make sure the test have the menu item for back to main menu
var ActionsTestScene = TestScene.extend({
    runThisTest:function (num) {
        actionsTestIdx = (num || num == 0) ? (num - 1) : -1;
        this.addChild(nextActionsTest());
        director.runScene(this);
    }
});

var ActionsDemo = BaseTestLayer.extend({
    _grossini:null,
    _tamara:null,
    _kathia:null,
    _code:null,

    ctor:function () {
        this._super(cc.color(0,0,0,255), cc.color(98,99,117,255) );

        this._grossini = new cc.Sprite(s_pathGrossini);
        this._tamara = new cc.Sprite(s_pathSister1);
        this._kathia = new cc.Sprite(s_pathSister2);
        this.addChild(this._grossini, SPRITE_GROSSINI_TAG);
        this.addChild(this._tamara, SPRITE_TAMARA_TAG);
        this.addChild(this._kathia, SPRITE_KATHIA_TAG);
        var s = director.getWinSize();
        this._grossini.x = s.width / 2;
        this._grossini.y = s.height / 3;
        this._tamara.x = s.width / 2;
		this._tamara.y = 2 * s.height / 3;
        this._kathia.x = s.width / 2;
		this._kathia.y = s.height / 2;
    },

    centerSprites:function (numberOfSprites) {
        var winSize = director.getWinSize();

        if (numberOfSprites === 0) {
            this._tamara.visible = false;
            this._kathia.visible = false;
            this._grossini.visible = false;
        } else if (numberOfSprites == 1) {
            this._tamara.visible = false;
            this._kathia.visible = false;
            this._grossini.x = winSize.width / 2;
			this._grossini.y = winSize.height / 2;
        }
        else if (numberOfSprites == 2) {
            this._kathia.x = winSize.width / 3;
			this._kathia.y = winSize.height / 2;
            this._tamara.x = 2 * winSize.width / 3;
			this._tamara.y = winSize.height / 2;
            this._grossini.visible = false;
        }
        else if (numberOfSprites == 3) {
            this._grossini.x = winSize.width / 2;
			this._grossini.y = winSize.height / 2;
            this._tamara.x = winSize.width / 4;
			this._tamara.y = winSize.height / 2;
            this._kathia.x = 3 * winSize.width / 4;
			this._kathia.y = winSize.height / 2;
        }
    },
    alignSpritesLeft:function (numberOfSprites) {
        //----start47----onEnter
        var s = director.getWinSize();

        if (numberOfSprites == 1) {
            this._tamara.visible = false;
            this._kathia.visible = false;
            this._grossini.x = 60;
			this._grossini.y = s.height / 2;
        }
        else if (numberOfSprites == 2) {
            this._kathia.x = 60;
			this._kathia.y = s.height / 3;
            this._tamara.x = 60;
			this._tamara.y = 2 * s.height / 3;
            this._grossini.visible = false;
        }
        else if (numberOfSprites == 3) {
            this._grossini.x = 60;
			this._grossini.y = s.height / 2;
            this._tamara.x = 60;
			this._tamara.y = 2 * s.height / 3;
            this._kathia.x = 60;
			this._kathia.y = s.height / 3;
        }
        //----end47----
    },
    title:function () {
        return "ActionsTest";
    },
    subtitle:function () {
        return "";
    },
    onBackCallback:function (sender) {
        var s = new ActionsTestScene();
        s.addChild(previousActionsTest());
        director.runScene(s);
    },
    onRestartCallback:function (sender) {
        var s = new ActionsTestScene();
        s.addChild(restartActionsTest());
        director.runScene(s);
    },
    onNextCallback:function (sender) {
        var s = new ActionsTestScene();
        s.addChild(nextActionsTest());
        director.runScene(s);
    },
    numberOfPendingTests:function() {
        return ( (arrayOfActionsTest.length-1) - actionsTestIdx );
    },

    getTestNumber:function() {
        return actionsTestIdx;
    }
});

//------------------------------------------------------------------
//
// ActionManual
//
//------------------------------------------------------------------
var ActionManual = ActionsDemo.extend({
    _code:"sprite.x = 10; sprite.y = 20;\n" +
        "sprite.rotation = 90;\n" +
        "sprite.scale = 2;",

    onEnter:function () {
        //----start0----onEnter
        this._super();

        this._tamara.attr({
	        x: 100,
	        y: 70,
	        opacity: 128,
	        scaleX: 2.5,
	        scaleY: -1.0
        });

	    this._grossini.attr({
		    x: winSize.width / 2,
		    y: winSize.height / 2,
		    rotation: 120,
		    color: cc.color(255, 0, 0)
	    });

        this._kathia.x = winSize.width - 100;
		this._kathia.y = winSize.height / 2;
        this._kathia.color = cc.color(0, 0, 255);
        //----end0----
    },

    title:function () {
        return "Sprite properties";
    },
    subtitle:function () {
        return "Manual Transformation";
    },

    //
    // Automation
    //
    testDuration:0.1,
    getExpectedResult:function() {
        var ret = [2.5,{"x":100,"y":70},128,120,{"x":winSize.width/2,"y":winSize.height/2},{"r":255,"g":0,"b":0},{"x":winSize.width - 100,"y":winSize.height / 2},{"r":0,"g":0,"b":255}];
        return JSON.stringify(ret);
    },

    getCurrentResult:function() {
        var ret = [];
        ret.push( this._tamara.scaleX );
        ret.push( cc.p(this._tamara.x, this._tamara.y) );
        ret.push( this._tamara.opacity );

        ret.push( this._grossini.rotation );
        ret.push( cc.p(this._grossini.x, this._grossini.y) );
        ret.push( this._grossini.color );

        ret.push( cc.p(this._kathia.x, this._kathia.y) );
        ret.push( this._kathia.color );

        return JSON.stringify(ret);
    }
});


//------------------------------------------------------------------
//
//	ActionMove
//
//------------------------------------------------------------------
var ActionMove = ActionsDemo.extend({

    _code:"a =cc.moveBy( time, cc.p(x,y) );\n" +
        "a = cc.moveTo( time, cc.p(x,y) );",

    onEnter:function () {
        //----start1----onEnter
        this._super();

        this.centerSprites(3);
        var s = director.getWinSize();

        var actionTo = cc.moveTo(2, cc.p(s.width - 40, s.height - 40));

        var actionBy = cc.moveBy(1, cc.p(80, 80));
        var actionByBack = actionBy.reverse();

        this._tamara.runAction(actionTo);
        this._grossini.runAction(cc.sequence(actionBy, actionByBack));
        this._kathia.runAction(cc.moveTo(1, cc.p(40, 40)));
        //----end1----
    },
    title:function () {
        return "cc.moveTo / cc.moveBy";
    },

    //
    // Automation
    //
    testDuration:2.1,
    getExpectedResult:function() {
        var ret = [{"x":winSize.width-40,"y":winSize.height-40},{"x":winSize.width/2,"y":winSize.height/2},{"x":40,"y":40}];
        return JSON.stringify(ret);
    },

    getCurrentResult:function() {
        var ret = [];
        ret.push( cc.p(this._tamara.x, this._tamara.y) );
        ret.push( cc.p(this._grossini.x, this._grossini.y) );
        ret.push( cc.p(this._kathia.x, this._kathia.y) );

        return JSON.stringify(ret);
    }

});

//------------------------------------------------------------------
//
// ActionScale
//
//------------------------------------------------------------------
var ActionScale = ActionsDemo.extend({

    _code:"a = cc.scaleBy( time, scale );\n" +
        "a = cc.scaleTo( time, scaleX, scaleY );",

    onEnter:function () {
        //----start2----onEnter
        this._super();

        this.centerSprites(3);

        var actionTo = cc.scaleTo(2, 0.5);
        var actionBy = cc.scaleBy(2, 2);
        var actionBy2 = cc.scaleBy(2, 0.25, 4.5);

        this._tamara.runAction(actionTo);
        this._kathia.runAction(cc.sequence(actionBy2, cc.delayTime(0.25), actionBy2.reverse()));
        this._grossini.runAction(cc.sequence(actionBy, cc.delayTime(0.25), actionBy.reverse()));

        //----end2----
    },
    title:function () {
        return "cc.scaleTo / cc.scaleBy";
    },

    //
    // Automation
    //
    testDuration:2.1,
    getExpectedResult:function() {
        var ret = [0.5,2,0.25,4.5];
        return JSON.stringify(ret);
    },

    getCurrentResult:function() {
        var ret = [];
        ret.push( this._tamara.scale );
        ret.push( this._grossini.scale );
        ret.push( this._kathia.scaleX );
        ret.push( this._kathia.scaleY );

        return JSON.stringify(ret);
    }
});

//------------------------------------------------------------------
//
//  ActionRotate
//
//------------------------------------------------------------------
var ActionRotate = ActionsDemo.extend({

    _code:"a = cc.rotateBy( time, degrees );\n" +
            "a = cc.rotateTo( time, degrees );",

    onEnter:function () {
        //----start3----onEnter
        this._super();
        this.centerSprites(3);
        var actionTo = cc.rotateTo(2, 45);
        var actionTo2 = cc.rotateTo(2, -45);
        var actionTo0 = cc.rotateTo(2, 0);
        this._tamara.runAction(cc.sequence(actionTo, cc.delayTime(0.25), actionTo0));

        var actionBy = cc.rotateBy(2, 360);
        var actionByBack = actionBy.reverse();
        this._grossini.runAction(cc.sequence(actionBy, cc.delayTime(0.25), actionByBack));

        this._kathia.runAction(cc.sequence(actionTo2, cc.delayTime(0.25), actionTo0.clone()));

        //----end3----
    },
    title:function () {
        return "cc.rotateTo / cc.rotateBy";
    },
    //
    // Automation
    //
    testDuration:2.1,
    getExpectedResult:function() {
        var ret = [45,360,-45];
        return JSON.stringify(ret);
    },

    getCurrentResult:function() {
        var ret = [];
        ret.push( this._tamara.rotation );
        ret.push( this._grossini.rotation );
        ret.push( this._kathia.rotation );

        return JSON.stringify(ret);
    }

});

//------------------------------------------------------------------
//
//  ActionRotateXY
//
//------------------------------------------------------------------
var ActionRotateXY = ActionsDemo.extend({
    onEnter:function () {
        //----start4----onEnter
        this._super();
        this.centerSprites(3);
        var actionTo = cc.rotateTo(2, 37.2, -37.2);
        var actionToBack = cc.rotateTo(2, 0, 0);
        var actionBy = cc.rotateBy(2, 0, -90);
        var actionBy2 = cc.rotateBy(2, 45.0, 45.0);

        var delay = cc.delayTime(0.25);

        this._tamara.runAction(cc.sequence(actionTo, delay, actionToBack));
        this._grossini.runAction(cc.sequence(actionBy, delay.clone(), actionBy.reverse()));
        this._kathia.runAction(cc.sequence(actionBy2, delay.clone(), actionBy2.reverse()));

        if (!cc.sys.isNative && !("opengl" in cc.sys.capabilities)) {
            var label = new cc.LabelTTF("Not support Actions on HTML5-canvas", "Times New Roman", 30);
            label.x = winSize.width / 2;
			label.y = winSize.height / 2 + 50;
            this.addChild(label, 100);
        }
        //----end4----
    },
    title:function () {
        return "cc.RotateBy(x,y) / cc.RotateTo(x,y)";
    },
    //
    // Automation
    //
    testDuration:2.1,
    getExpectedResult:function() {
        var ret = ["37.20","-37.20",0,-90,45,45];
        return JSON.stringify(ret);
    },

    getCurrentResult:function() {
        var ret = [];
        ret.push( this._tamara.rotationX.toFixed(2) );
        ret.push( this._tamara.rotationY.toFixed(2) );

        ret.push( this._grossini.rotationX );
        ret.push( this._grossini.rotationY );

        ret.push( this._kathia.rotationX );
        ret.push( this._kathia.rotationY );

        return JSON.stringify(ret);
    }

});
//------------------------------------------------------------------
//
//	ActionSkew
//
//------------------------------------------------------------------
var ActionSkew = ActionsDemo.extend({

    _code:"a = cc.skewBy( time, skew );\n" +
        "a = cc.skewTo( time, skewX, skewY );",

    onEnter:function () {
        //----start5----onEnter
        this._super();
        this.centerSprites(3);
        var actionTo = cc.skewTo(2, 37.2, -37.2);
        var actionToBack = cc.skewTo(2, 0, 0);
        var actionBy = cc.skewBy(2, 0, -90);
        var actionBy2 = cc.skewBy(2, 45.0, 45.0);

        var delay = cc.delayTime(0.25);

        this._tamara.runAction(cc.sequence(actionTo, delay, actionToBack));
        this._grossini.runAction(cc.sequence(actionBy, delay.clone(), actionBy.reverse()));
        this._kathia.runAction(cc.sequence(actionBy2, delay.clone(), actionBy2.reverse()));
        //----end5----
    },
    title:function () {
        return "cc.skewTo / cc.skewBy";
    },
    //
    // Automation
    //
    testDuration:2.1,
    getExpectedResult:function() {
        var ret = ["37.20","-37.20",0,0,45,45];
        return JSON.stringify(ret);
    },

    getCurrentResult:function() {
        var ret = [];
        ret.push( this._tamara.skewX.toFixed(2) );
        ret.push( this._tamara.skewY.toFixed(2) );

        ret.push( this._grossini.skewX );
        ret.push( this._grossini.skewY );

        ret.push( this._kathia.skewX );
        ret.push( this._kathia.skewY );

        return JSON.stringify(ret);
    }
});

var ActionSkewRotateScale = ActionsDemo.extend({
    onEnter:function () {
        //----start6----onEnter
        this._super();

        this.centerSprites(0);

        var boxW = 100, boxH = 100;
        var box = new cc.LayerColor(cc.color(255, 255, 0, 255));
        box.anchorX = 0;
	    box.anchorY = 0;
        box.x = (winSize.width - boxW) / 2;
		box.y = (winSize.height - boxH) / 2;
        box.width = boxW;
        box.height = boxH;

        var markrside = 10.0;
        var uL = new cc.LayerColor(cc.color(255, 0, 0, 255));
        box.addChild(uL);
        uL.width = markrside;
        uL.height = markrside;
        uL.x = 0;
		uL.y = boxH - markrside;
	    uL.anchorX = 0;
	    uL.anchorY = 0;

        var uR = new cc.LayerColor(cc.color(0, 0, 255, 255));
        box.addChild(uR);
        uR.width = markrside;
        uR.height = markrside;
        uR.x = boxW - markrside;
		uR.y = boxH - markrside;
        uR.anchorX = 0;
	    uR.anchorY = 0;


        this.addChild(box);
        var actionTo = cc.skewTo(2, 0, 2);
        var rotateTo = cc.rotateTo(2, 61.0);
        var actionScaleTo = cc.scaleTo(2, -0.44, 0.47);

        var actionScaleToBack = cc.scaleTo(2, 1.0, 1.0);
        var rotateToBack = cc.rotateTo(2, 0);
        var actionToBack = cc.skewTo(2, 0, 0);

        var delay = cc.delayTime(0.25);

        box.runAction(cc.sequence(actionTo, delay, actionToBack));
        box.runAction(cc.sequence(rotateTo, delay.clone(), rotateToBack));
        box.runAction(cc.sequence(actionScaleTo, delay.clone(), actionScaleToBack));

        this.box = box;
        //----end6----
    },
    title:function () {
        return "Skew + Rotate + Scale";
    },
    //
    // Automation
    //
    testDuration:2.1,
    getExpectedResult:function() {
        var ret = [0,2,61,"-0.44","0.47"];
        return JSON.stringify(ret);
    },

    getCurrentResult:function() {
        var ret = [];
        ret.push( this.box.skewX );
        ret.push( this.box.skewY );
        ret.push( this.box.rotation );
        ret.push( this.box.scaleX.toFixed(2) );
        ret.push( this.box.scaleY.toFixed(2) );

        return JSON.stringify(ret);
    }

});

//------------------------------------------------------------------
//
// ActionJump
//
//------------------------------------------------------------------
var ActionJump = ActionsDemo.extend({
    _code:"a = cc.jumpBy( time, point, height, #_of_jumps );\n" +
        "a = cc.jumpTo( time, point, height, #_of_jumps );",

    onEnter:function () {
        //----start7----onEnter
        this._super();
        this.centerSprites(3);

        var actionTo = cc.jumpTo(2, cc.p(300, 300), 50, 4);
        var actionBy = cc.jumpBy(2, cc.p(300, 0), 50, 4);
        var actionUp = cc.jumpBy(2, cc.p(0, 0), 80, 4);
        var actionByBack = actionBy.reverse();

        var delay = cc.delayTime(0.25);

        this._tamara.runAction(actionTo);
        this._grossini.runAction(cc.sequence(actionBy, delay, actionByBack));

        var action = cc.sequence(actionUp, delay.clone()).repeatForever();
        this._kathia.runAction(action);
        //----end7----
    },
    title:function () {
        return "cc.jumpTo / cc.jumpBy";
    },
    subtitle:function () {
        return "Actions will stop for 0.25s after 2 seconds";
    },

    //
    // Automation
    //
    testDuration:2.1,
    getExpectedResult:function() {
        var ret = [{"x":300,"y":300},
                    {"x":winSize.width/2+300,"y":winSize.height/2},
                    {"x":3*winSize.width/4,"y":winSize.height/2}];
        return JSON.stringify(ret);
    },

    getCurrentResult:function() {
        var ret = [];
        ret.push( cc.p(this._tamara.x, this._tamara.y) );
        ret.push( cc.p(this._grossini.x, this._grossini.y) );
        ret.push( cc.p(this._kathia.x, this._kathia.y) );

        return JSON.stringify(ret);
    }

});
//------------------------------------------------------------------
//
// ActionBezier
//
//------------------------------------------------------------------
var ActionBezier = ActionsDemo.extend({
    onEnter:function () {
        //----start8----onEnter

        this._super();
        var s = director.getWinSize();

        //
        // startPosition can be any coordinate, but since the movement
        // is relative to the Bezier curve, make it (0,0)
        //

        this.centerSprites(3);

        // sprite 1

        var delay = cc.delayTime(0.25);

        // 3 and only 3 control points should be used for Bezier actions.
        var controlPoints = [ cc.p(0, 374),
                                cc.p(300, -374),
                                cc.p(300, 100) ];

        var bezierForward = cc.bezierBy(2, controlPoints);
        var rep = cc.sequence(bezierForward, delay, bezierForward.reverse(), delay.clone()).repeatForever();

        // sprite 2
        this._tamara.x = 80;
		this._tamara.y = 160;

        // 3 and only 3 control points should be used for Bezier actions.
        var controlPoints2 = [ cc.p(100, s.height / 2),
            cc.p(200, -s.height / 2),
            cc.p(240, 160) ];
        var bezierTo1 = cc.bezierTo(2, controlPoints2);

        // // sprite 3
        var controlPoints3 = controlPoints2.slice();
        this._kathia.x = 400;
		this._kathia.y = 160;
        var bezierTo2 = cc.bezierTo(2, controlPoints3);

        this._grossini.runAction(rep);
        this._tamara.runAction(bezierTo1);
        this._kathia.runAction(bezierTo2);
        //----end8----
    },
    title:function () {
        return "cc.bezierBy / cc.bezierTo";
    },
    //
    // Automation
    //
    testDuration:2.1,
    setupAutomation:function() {
        this.scheduleOnce(this.checkControl1, 0.66667);
        this.scheduleOnce(this.checkControl2, 1.33333);
    },
    checkControl1:function(dt) {
        this.control1 = cc.p(this._grossini.x, this._grossini.y);
    },
    verifyControl1:function(dt) {
        var x = Math.abs( this.control1.x - 77 - winSize.width/2 );
        var y = Math.abs( this.control1.y - 87 - winSize.height/2 );
        //  -/+ 5 pixels of error
        return ( x < 5 && y < 5);
    },
    checkControl2:function(dt) {
        this.control2 = cc.p(this._grossini.x, this._grossini.y);
    },
    verifyControl2:function(dt) {
        var x = Math.abs( this.control2.x - 222 - winSize.width/2 );
        var y = Math.abs( this.control2.y + 53 - winSize.height/2 );
        //  -/+ 5 pixels of error
        return ( x < 5 && y < 5);
    },

    getExpectedResult:function() {
        var ret = [ true,
                    true,
                    {"x":winSize.width/2+300,"y":winSize.height/2+100}];
        return JSON.stringify(ret);
    },

    getCurrentResult:function() {
        var ret = [];
        ret.push( this.verifyControl1() );
        ret.push( this.verifyControl2() );
        ret.push( cc.p(this._grossini.x, this._grossini.y) );

        return JSON.stringify(ret);
    }
});

//------------------------------------------------------------------
//
// ActionBezierToCopy
//
//------------------------------------------------------------------
var ActionBezierToCopy = ActionsDemo.extend({
    onEnter:function () {
        //----start9----onEnter
        this._super();

        //
        // startPosition can be any coordinate, but since the movement
        // is relative to the Bezier curve, make it (0,0)
        //

        this.centerSprites(2);

        // sprite 1
        this._tamara.x = 80;
		this._tamara.y = 160;

        // 3 and only 3 control points should be used for Bezier actions.
        var controlPoints2 = [ cc.p(100, winSize.height / 2),
                                cc.p(200, -winSize.height / 2),
                                cc.p(240, 160) ];
        var bezierTo1 = cc.bezierTo(2, controlPoints2);

        // sprite 2
        this._kathia.x = 80;
		this._kathia.y = 160;
        var bezierTo2 = bezierTo1.clone();

        this._tamara.runAction(bezierTo1);
        this._kathia.runAction(bezierTo2);
        //----end9----
    },
    title:function () {
        return "cc.bezierTo copy test";
    },
    subtitle:function() {
        return "Both sprites should move across the same path";
    }
});
//------------------------------------------------------------------
//
// Issue1008
//
//------------------------------------------------------------------
var Issue1008 = ActionsDemo.extend({
    onEnter:function () {

        //----start10----onEnter
        this._super();

        this.centerSprites(1);

        // sprite 1

        this._grossini.x = 428;
		this._grossini.y = 279;

        // 3 and only 3 control points should be used for Bezier actions.
        var controlPoints1 = [ cc.p(428, 279), cc.p(100, 100), cc.p(100, 100)];
        var controlPoints2 = [ cc.p(100, 100), cc.p(428, 279), cc.p(428, 279)];

        var bz1 = cc.bezierTo(1.5, controlPoints1);
        var bz2 = cc.bezierTo(1.5, controlPoints2);
        var trace = cc.callFunc(this.onTrace, this);
        var delay = cc.delayTime(0.25);

        var rep = cc.sequence(bz1, bz2, trace,delay).repeatForever();
        this._grossini.runAction(rep);

        //----end10----

        //this._grossini.runAction(cc.sequence(bz1, bz2, trace,delay));

    },
    onTrace:function (sender) {
        var pos = cc.p(sender.x, sender.y);
        cc.log("Position x: " + pos.x + ' y:' + pos.y);
        if (Math.round(pos.x) != 428 || Math.round(pos.y) != 279)
            this.log("Error: Issue 1008 is still open");

        this.tracePos = pos;
    },
    title:function () {
        return "Issue 1008";
    },
    subtitle:function () {
        return "cc.bezierTo + Repeat. See console";
    },
    //
    // Automation
    //
    testDuration:3.1,
    getExpectedResult:function() {
        var ret = {"x":428,"y":279};
        return JSON.stringify(ret);
    },

    getCurrentResult:function() {
        return JSON.stringify(this.tracePos);
    }
});
//------------------------------------------------------------------
//
// ActionBlink
//
//------------------------------------------------------------------
var ActionBlink = ActionsDemo.extend({
    _code:"a = cc.blink( time, #_of_blinks );",

    onEnter:function () {
        //----start13----onEnter
        this._super();
        this.centerSprites(2);

        var action1 = cc.blink(2, 10);
        var action2 = cc.blink(2, 5);

        this._tamara.runAction(action1);
        this._kathia.runAction(action2);
        //----end13----
    },
    title:function () {
        return "cc.blink";
    },
    //
    // Automation
    //
    testDuration:2.1,
    setupAutomation:function() {
        this.scheduleOnce(this.checkControl1,0.1);
    },
    checkControl1:function(dt){
        this.control1 = this._kathia.visible;
    },
    getExpectedResult:function() {
        var ret = [false,true,true];
        return JSON.stringify(ret);
    },
    getCurrentResult:function() {
        var ret = [];
        ret.push( this.control1 );
        ret.push( this._tamara.visible);
        ret.push( this._kathia.visible);
        return JSON.stringify(ret);
    }
});
//------------------------------------------------------------------
//
// ActionFade
//
//------------------------------------------------------------------
var ActionFade = ActionsDemo.extend({
    _code:"a = cc.fadeIn( time );\n" +
        "a = cc.fadeOut( time );",

    onEnter:function () {
        //----start14----onEnter
        this._super();
        this.centerSprites(2);
        var delay = cc.delayTime(0.25);
        this._tamara.opacity = 0;
        var action1 = cc.fadeIn(1.0);
        var action1Back = action1.reverse();

        var action2 = cc.fadeOut(1.0);
        var action2Back = action2.reverse();

        this._tamara.runAction(cc.sequence(action1, delay, action1Back));
        this._kathia.runAction(cc.sequence(action2, delay.clone(), action2Back));
        //----end14----

    },
    title:function () {
        return "cc.fadeIn / cc.fadeOut";
    },
    //
    // Automation
    //
    testDuration:1.1,
    getExpectedResult:function() {
        var ret = [255,0];
        return JSON.stringify(ret);
    },
    getCurrentResult:function() {
        var ret = [];
        ret.push( this._tamara.opacity );
        ret.push( this._kathia.opacity);
        return JSON.stringify(ret);
    }

});
//------------------------------------------------------------------
//
// ActionTint
//
//------------------------------------------------------------------
var ActionTint = ActionsDemo.extend({

    _code:"a = cc.tintBy( time, red, green, blue );\n" +
        "a = cc.tintTo( time, red, green, blue );",

    onEnter:function () {

        //----start15----onEnter
        this._super();
        this.centerSprites(2);

        var action1 = cc.tintTo(2, 255, 0, 255);
        var action2 = cc.tintBy(2, -127, -255, -127);
        var action2Back = action2.reverse();

        this._tamara.runAction(action1);
        this._kathia.runAction(cc.sequence(action2, cc.delayTime(0.25), action2Back));
        //----end15----

    },
    title:function () {
        return "cc.tintTo / cc.tintBy";
    },
    //
    // Automation
    //
    testDuration:2.1,
    getExpectedResult:function() {
        var ret = [{"r":255,"g":0,"b":255},{"r":128,"g":0,"b":128}];
        return JSON.stringify(ret);
    },
    getCurrentResult:function() {
        var ret = [];
        ret.push( this._tamara.color );
        ret.push( this._kathia.color );
        return JSON.stringify(ret);
    }

});

//------------------------------------------------------------------
//
// ActionAnimate
//
//------------------------------------------------------------------
var ActionAnimate = ActionsDemo.extend({
    onEnter:function () {

        //----start44----onEnter
        this._super();
        this.centerSprites(3);

        //
        // Manual animation
        //
        var animation = new cc.Animation();
        for (var i = 1; i < 15; i++) {
            var frameName = "Images/grossini_dance_" + ((i < 10) ? ("0" + i) : i) + ".png";
            animation.addSpriteFrameWithFile(frameName);
        }
        animation.setDelayPerUnit(2.8 / 14);
        animation.setRestoreOriginalFrame(true);

        var action = cc.animate(animation);
        this._grossini.runAction(cc.sequence(action, action.reverse()));

        //
        // File animation
        //
        // With 2 loops and reverse
        var animCache = cc.animationCache;

        animCache.addAnimations(s_animations2Plist);
        var animation2 = animCache.getAnimation("dance_1");

        var action2 = cc.animate(animation2);
        this._tamara.runAction(cc.sequence(action2, action2.reverse()));

        //
        // File animation
        //
        // with 4 loops
        var animation3 = animation2.clone();
        animation3.setLoops(4);

        var action3 = cc.animate(animation3);
        this._kathia.runAction(action3);
        //----end44----
    },

    title:function () {
        return "Animation";
    },

    subtitle:function () {
        return "Center: Manual animation. Border: using file format animation";
    }
});
//------------------------------------------------------------------
//
//	ActionSequence
//
//------------------------------------------------------------------
var ActionSequence = ActionsDemo.extend({

    _code:"a = cc.sequence( a1, a2, a3,..., aN);",

    onEnter:function () {
        //----start16----onEnter
        this._super();
        this.alignSpritesLeft(1);

        var action = cc.sequence(
            cc.moveBy(1.5, cc.p(240, 0)),
            cc.rotateBy(1.5, 540)
        );

        this._grossini.runAction(action);
        //----end16----
    },
    title:function () {
        return "cc.sequence: Move + Rotate";
    },
    //
    // Automation
    //
    testDuration:3.1,
    getExpectedResult:function() {
        var ret = [{"x":60+240,"y":winSize.height/2},540];
        return JSON.stringify(ret);
    },
    getCurrentResult:function() {
        var ret = [];
        ret.push( cc.p(this._grossini.x, this._grossini.y) );
        ret.push( this._grossini.rotation );
        return JSON.stringify(ret);
    }
});
//------------------------------------------------------------------
//
//	ActionSequence2
//
//------------------------------------------------------------------
var ActionSequence2 = ActionsDemo.extend({
    onEnter:function () {

        //----start17----onEnter
        this._super();
        this.centerSprites(1);
        this._grossini.visible = false;
        var action = cc.sequence(
            cc.place(cc.p(200, 200)),
            cc.show(),
            cc.moveBy(1, cc.p(100, 0)),
            cc.callFunc(this.onCallback1, this),
            cc.callFunc(this.onCallback2.bind(this)),
            cc.callFunc(this.onCallback3, this));
        this._grossini.runAction(action);

        this.called1 = this.called2 = this.called3 = false;
        //----end17----
    },
    onCallback1:function () {
        var s = director.getWinSize();
        var label = new cc.LabelTTF("callback 1 called", "Marker Felt", 16);
        label.x = s.width / 4 * 1;
		label.y = s.height / 2;

        this.addChild(label);
        this.called1 = true;
    },
    onCallback2:function () {
        var s = director.getWinSize();
        var label = new cc.LabelTTF("callback 2 called", "Marker Felt", 16);
        label.x = s.width / 4 * 2;
		label.y = s.height / 2;

        this.addChild(label);
        this.called2 = true;
    },
    onCallback3:function () {
        var s = director.getWinSize();
        var label = new cc.LabelTTF("callback 3 called", "Marker Felt", 16);
        label.x = s.width / 4 * 3;
		label.y = s.height / 2;

        this.addChild(label);
        this.called3 = true;
    },
    title:function () {
        return "Sequence of InstantActions";
    },
    //
    // Automation
    //
    testDuration:1.1,
    getExpectedResult:function() {
        var ret = [true,true,true,true,{"x":300,"y":200}];
        return JSON.stringify(ret);
    },
    getCurrentResult:function() {
        var ret = [];
        ret.push( this.called1 );
        ret.push( this.called2 );
        ret.push( this.called3 );
        ret.push( this._grossini.visible );
        ret.push( cc.p(this._grossini.x, this._grossini.y) );
        return JSON.stringify(ret);
    }
});
//------------------------------------------------------------------
//
//	ActionCallFunc1
//
//------------------------------------------------------------------
var ActionCallFunc1 = ActionsDemo.extend({
    _code:"a = cc.callFunc( this.callback );\n" +
        "a = cc.callFunc( this.callback, this, optional_arg );",

    onEnter:function () {
        //----start25----onEnter
        this._super();
        this.centerSprites(3);

        // Testing different ways to pass "this"
        var action = cc.sequence(
            cc.moveBy(2, cc.p(200, 0)),
            cc.callFunc(this.onCallback1.bind(this))  // 'this' is bound to the callback function using "bind"
        );

        var action2 = cc.sequence(
            cc.scaleBy(2, 2),
            cc.fadeOut(2),
            cc.callFunc(this.onCallback2, this)      // 'this' is passed as 2nd argument.
        );

        var action3 = cc.sequence(
            cc.rotateBy(3, 360),
            cc.fadeOut(2),
            cc.callFunc(this.onCallback3, this, "Hi!")  // If you want to pass a optional value, like "Hi!", then you should pass 'this' too
        );

        this._grossini.runAction(action);
        this._tamara.runAction(action2);
        this._kathia.runAction(action3);
        //----end25----

    },
    onCallback1:function (nodeExecutingAction, value) {
        var s = director.getWinSize();
        var label = new cc.LabelTTF("callback 1 called", "Marker Felt", 16);
        label.x = s.width / 4 * 1;
		label.y = s.height / 2;
        this.addChild(label);
        this.control1 = true;
    },
    onCallback2:function (nodeExecutingAction, value) {
        var s = director.getWinSize();
        var label = new cc.LabelTTF("callback 2 called", "Marker Felt", 16);
        label.x = s.width / 4 * 2;
		label.y = s.height / 2;

        this.addChild(label);
        this.control2 = true;
    },
    onCallback3:function (nodeExecutingAction, value) {
        var s = director.getWinSize();
        var label = new cc.LabelTTF("callback 3 called:" + value, "Marker Felt", 16);
        label.x = s.width / 4 * 3;
		label.y = s.height / 2;
        this.addChild(label);
        this.control3 = true;
    },
    title:function () {
        return "Callbacks: CallFunc and friends";
    },
    //
    // Automation
    //
    testDuration:5.05,
    setupAutomation:function() {
        this.control1 = this.control2 = this.control3 = false;
    },
    getExpectedResult:function() {
        var ret = [true,true,true];
        return JSON.stringify(ret);
    },
    getCurrentResult:function() {
        var ret = [];
        ret.push( this.control1 );
        ret.push( this.control2 );
        ret.push( this.control3 );
        return JSON.stringify(ret);
    }
});
//------------------------------------------------------------------
//
// ActionCallFunc2
//
//------------------------------------------------------------------
var ActionCallFunc2 = ActionsDemo.extend({
    onEnter:function () {
        //----start26----onEnter
        this._super();
        this.centerSprites(1);

        var action = cc.sequence(cc.moveBy(2.0, cc.p(200, 0)),
            cc.callFunc(this.removeFromParentAndCleanup, this._grossini, true));

        this._grossini.runAction(action);
        //----end26----
    },

    removeFromParentAndCleanup:function (nodeExecutingAction, data) {
        nodeExecutingAction.removeFromParent(data);
    },

    title:function () {
        return "cc.CallFunc + auto remove";
    },
    subtitle:function () {
        return "cc.CallFunc + removeFromParentAndCleanup. Grossini dissapears in 2s";
    },
    //
    // Automation
    //
    testDuration:2.1,
    setupAutomation:function() {
    },
    getExpectedResult:function() {
        var ret = [null];
        return JSON.stringify(ret);
    },
    getCurrentResult:function() {
        var ret = [];
        ret.push( this.getChildByTag(SPRITE_GROSSINI_TAG) );
        return JSON.stringify(ret);
    }
});

//------------------------------------------------------------------
//
// ActionCallFunc3
//
//------------------------------------------------------------------
var ActionCallFunc3 = ActionsDemo.extend({
    onEnter:function () {
        //----start27----onEnter
        this._super();
        this.centerSprites(1);

        var action = cc.callFunc(function (nodeExecutingAction, value) {
            this.control1 = "Value is: " + value;
            this.log("Object:" + nodeExecutingAction + ". " + this.control1);
        }, this, "Hello world");

        this.runAction(action);
        //----end27----
    },

    title:function () {
        return "cc.CallFunc + parameters";
    },
    subtitle:function () {
        return "cc.CallFunc + parameters. Take a look at the console";
    },
    //
    // Automation
    //
    testDuration:0.1,
    setupAutomation:function() {
    },
    getExpectedResult:function() {
        var ret = ["Value is: Hello world"];
        return JSON.stringify(ret);
    },
    getCurrentResult:function() {
        var ret = [];
        ret.push( this.control1 );
        return JSON.stringify(ret);
    }
});

//------------------------------------------------------------------
//
// ActionSpawn
//
//------------------------------------------------------------------
var ActionSpawn = ActionsDemo.extend({

    _code:"a = cc.spawn( a1, a2, ..., aN );",

    onEnter:function () {

        //----start18----onEnter
        this._super();
        this.alignSpritesLeft(1);

        var action = cc.spawn(
            cc.jumpBy(2, cc.p(300, 0), 50, 4),
            cc.rotateBy(2, 720));

        this._grossini.runAction(action);
        //----end18----

    },
    title:function () {
        return "cc.spawn: Jump + Rotate";
    },
    //
    // Automation
    //
    testDuration:2.1,
    getExpectedResult:function() {
        var ret = [{"x":300+60,"y":winSize.height/2},720];
        return JSON.stringify(ret);
    },
    getCurrentResult:function() {
        var ret = [];
        ret.push( cc.p(this._grossini.x, this._grossini.y) );
        ret.push( this._grossini.rotation );
        return JSON.stringify(ret);
    }
});
//------------------------------------------------------------------
//
// ActionRepeatForever
//
//------------------------------------------------------------------
var ActionRepeatForever = ActionsDemo.extend({
    _code:"a = action.repeatForever();",

    onEnter:function () {
        //----start22----onEnter
        this._super();
        this.centerSprites(1);
        var action = cc.sequence(
            cc.delayTime(1),
            cc.callFunc(this.repeatForever));    // not passing 'this' since it is not used by the callback func

        this._grossini.runAction(action);
        //----end22----

    },
    repeatForever:function (sender) {
        sender.runAction(cc.sequence(
                cc.rotateBy(2, 90).easing(cc.easeElasticInOut(0.5)),
                cc.rotateBy(0.5, 90)
            ).repeatForever()
        );
        cc.sys.garbageCollect();
    },
    title:function () {
        return "cc.CallFunc + cc.RepeatForever";
    },
    //
    // Automation
    //
    testDuration:3.5,
    getExpectedResult:function() {
        var ret = [true];
        return JSON.stringify(ret);
    },
    getCurrentResult:function() {
        var ret = [];
        var r = this._grossini.rotation;
        var expected = 900;
        var error = 15;
        ret.push( r < expected+error && r > expected-error );
        return JSON.stringify(ret);
    }

});
//------------------------------------------------------------------
//
// ActionRotateToRepeat
//
//------------------------------------------------------------------
var ActionRotateToRepeat = ActionsDemo.extend({
    _code:"a = action_to_repeat.repeat(#_of_times);",

    onEnter:function () {
        //----start23----onEnter
        this._super();
        this.centerSprites(2);

        var act1 = cc.rotateTo(0.5, 90);
        var act2 = cc.rotateTo(0.5, 0);
        var seq = cc.sequence(act1, act2);
        var seq2 = seq.clone();

        this._tamara.runAction(seq.repeatForever());
        this._kathia.runAction(seq2.repeat(4));
        //----end23----

    },
    title:function () {
        return "Repeat/RepeatForever + RotateTo";
    },
    //
    // Automation
    //
    testDuration:4.5,
    getExpectedResult:function() {
        var ret = [0,true];
        return JSON.stringify(ret);
    },
    getCurrentResult:function() {
        var ret = [];
        ret.push( this._kathia.rotation );
        var r = this._tamara.rotation;
        var expected = 90;
        var error = 15;
        ret.push( r < expected+error && r > expected-error );
        return JSON.stringify(ret);
    }

});
//------------------------------------------------------------------
//
// ActionRotateJerk
//
//------------------------------------------------------------------
var ActionRotateJerk = ActionsDemo.extend({
    onEnter:function () {
        //----start24----onEnter
        this._super();
        this.centerSprites(2);
        var seq = cc.sequence(
            cc.rotateTo(0.5, -20),
            cc.rotateTo(0.5, 20));

        var rep1 = seq.repeat(10);
        var rep2 = seq.clone().repeatForever();
        this._tamara.runAction(rep1);
        this._kathia.runAction(rep2);
        //----end24----
    },
    title:function () {
        return "RepeatForever / Repeat + Rotate";
    }
});
//------------------------------------------------------------------
//
// ActionReverse
//
//------------------------------------------------------------------
var ActionReverse = ActionsDemo.extend({

    _code:"a = action.reverse();",

    onEnter:function () {

        //----start19----onEnter
        this._super();
        this.alignSpritesLeft(1);

        var jump = cc.jumpBy(2, cc.p(300, 0), 50, 4);
        var delay = cc.delayTime(0.25);
        var action = cc.sequence(jump, delay, jump.reverse());

        this._grossini.runAction(action);
        //----end19----
    },
    title:function () {
        return "Reverse Jump action";
    },

    //
    // Automation
    //
    testDuration:4.4,
    setupAutomation:function() {
        this.scheduleOnce(this.checkControl1,2.1);
    },
    checkControl1:function(dt) {
        this.control1 = cc.p(this._grossini.x, this._grossini.y);
    },
    getExpectedResult:function() {
        var ret = [{"x":360,"y":winSize.height/2},{"x":60,"y":winSize.height/2}];
        return JSON.stringify(ret);
    },
    getCurrentResult:function() {
        var ret = [];
        ret.push( this.control1 );
        ret.push( cc.p(this._grossini.x, this._grossini.y) );
        return JSON.stringify(ret);
    }

});
//------------------------------------------------------------------
//
// ActionDelayTime
//
//------------------------------------------------------------------
var ActionDelayTime = ActionsDemo.extend({

    _code:"a = cc.delayTime( time );",

    onEnter:function () {
        //----start20----onEnter
        this._super();
        this.alignSpritesLeft(1);

        var move = cc.moveBy(1, cc.p(150, 0));
        var action = cc.sequence(move, cc.delayTime(2), move.clone());

        this._grossini.runAction(action);
        //----end20----
    },
    title:function () {
        return "DelayTime: m + delay + m";
    },
    //
    // Automation
    //
    testDuration:2.9,
    getExpectedResult:function() {
        var ret = [{"x":210,"y":winSize.height/2}];
        return JSON.stringify(ret);
    },
    getCurrentResult:function() {
        var ret = [];
        ret.push( cc.p(this._grossini.x, this._grossini.y) );
        return JSON.stringify(ret);
    }
});
//------------------------------------------------------------------
//
// ActionReverseSequence
//
//------------------------------------------------------------------
var ActionReverseSequence = ActionsDemo.extend({
    onEnter:function () {

        //----start28----onEnter
        this._super();
        this.alignSpritesLeft(1);

        var move1 = cc.moveBy(1, cc.p(250, 0));
        var move2 = cc.moveBy(1, cc.p(0, 50));
        var seq = cc.sequence(move1, move2, move1.reverse());
        var action = cc.sequence(seq, seq.reverse());

        this._grossini.runAction(action);
        //----end28----

    },
    subtitle:function () {
        return "Reverse a sequence";
    }
});
//------------------------------------------------------------------
//
// ActionReverseSequence2
//
//------------------------------------------------------------------
var ActionReverseSequence2 = ActionsDemo.extend({
    onEnter:function () {

        //----start29----onEnter
        this._super();
        this.alignSpritesLeft(2);


        // Test:
        //   Sequence should work both with IntervalAction and InstantActions
        var move1 = cc.moveBy(3, cc.p(250, 0));
        var move2 = cc.moveBy(3, cc.p(0, 50));
        var tog1 = cc.toggleVisibility();
        var tog2 = cc.toggleVisibility();
        var seq = cc.sequence(move1, tog1, move2, tog2, move1.reverse());

        var action = cc.sequence(seq, seq.reverse()).repeat(3);


        // Test:
        //   Also test that the reverse of Hide is Show, and vice-versa
        this._kathia.runAction(action);

        var move_tamara = cc.moveBy(1, cc.p(100, 0));
        var move_tamara2 = cc.moveBy(1, cc.p(50, 0));
        var hide = cc.hide();
        var seq_tamara = cc.sequence(move_tamara, hide, move_tamara2);
        var seq_back = seq_tamara.reverse();
        this._tamara.runAction(cc.sequence(seq_tamara, seq_back));
        //----end29----
    },
    subtitle:function () {
        return "Reverse sequence 2";
    }
});
//------------------------------------------------------------------
//
// ActionRepeat
//
//------------------------------------------------------------------
var ActionRepeat = ActionsDemo.extend({
    onEnter:function () {
        //----start21----onEnter
        this._super();
        this.alignSpritesLeft(2);


        var a1 = cc.moveBy(1, cc.p(150, 0));

        var action1 = cc.sequence(cc.place(cc.p(60, 60)), a1).repeat(3);
        var action2 = cc.sequence( a1.clone(), a1.reverse(), cc.delayTime(0.25)).repeatForever();

        this._kathia.runAction(action1);
        this._tamara.runAction(action2);
        //----end21----
    },
    title:function () {
        return "Repeat / RepeatForever actions";
    },
    //
    // Automation
    //
    testDuration:4.30,
    getExpectedResult:function() {
        var ret = [{"x":210,"y":60},{"x":60,"y":2*winSize.height/3}];
        return JSON.stringify(ret);
    },
    getCurrentResult:function() {
        var ret = [];
        ret.push( cc.p(this._kathia.x, this._kathia.y) );
        ret.push( cc.p(this._tamara.x, this._tamara.y) );
        return JSON.stringify(ret);
    }

});
//------------------------------------------------------------------
//
// ActionFollow
//
//------------------------------------------------------------------
var ActionFollow = ActionsDemo.extend({
    onEnter:function () {

        //----start30----onEnter
        this._super();
        this.centerSprites(1);
        var s = director.getWinSize();

        this._grossini.x = -(s.width / 2);
		this._grossini.y = s.height / 2;
        var move = cc.moveBy(2, cc.p(s.width * 3, 0));
        var move_back = move.reverse();
        var seq = cc.sequence(move, move_back);

        var rep = seq.repeatForever();

        this._grossini.runAction(rep);

        this.runAction(cc.follow(this._grossini, cc.rect(0, 0, s.width * 2 - 100, s.height)));
        //----end30----
    },
    subtitle:function () {
        return "Follow action";
    }
});

//------------------------------------------------------------------
//
// ActionCardinalSpline
//
//------------------------------------------------------------------
var ActionCardinalSpline = ActionsDemo.extend({
    _array:null,
    _drawNode1: null,
    _drawNode2: null,

    _code:" a = cc.cadinalSplineBy( time, array_of_points, tension );\n" +
        " a = cc.cadinalSplineTo( time, array_of_points, tension );",

    ctor:function () {
        this._super();
        this._array = [];

        //add draw node
        var winSize = cc.director.getWinSize();
        this._drawNode1 = new cc.DrawNode();
        this.addChild(this._drawNode1);
        this._drawNode1.x = 50;
        this._drawNode1.y = 50;
        this._drawNode1.setDrawColor(cc.color(255,255,255,255));

        this._drawNode2 = new cc.DrawNode();
        this.addChild(this._drawNode2);
        this._drawNode2.x = winSize.width * 0.5;
        this._drawNode2.y = 50;
        this._drawNode2.setDrawColor(cc.color(255,255,255,255));
    },

    onEnter:function () {

        //----start11----onEnter
        this._super();
        var winSize = cc.director.getWinSize();
        this.centerSprites(2);

        var delay = cc.delayTime(0.25);

        var array = [
            cc.p(0, 0),
            cc.p(winSize.width / 2 - 30, 0),
            cc.p(winSize.width / 2 - 30, winSize.height - 80),
            cc.p(0, winSize.height - 80),
            cc.p(0, 0)
        ];

        //
        // sprite 1 (By)
        //
        // Spline with no tension (tension==0)
        //
        var action1 = cc.cardinalSplineBy(2, array, 0);
        var reverse1 = action1.reverse();
        var seq = cc.sequence(action1, delay, reverse1, delay.clone() );

        this._tamara.x = 50;
		this._tamara.y = 50;
        this._tamara.runAction(seq);

        //
        // sprite 2 (By)
        //
        // Spline with high tension (tension==1)
        //
        var action2 = cc.cardinalSplineBy(2, array, 1);
        var reverse2 = action2.reverse();
        var seq2 = cc.sequence(action2, delay.clone(), reverse2, delay.clone());

        this._kathia.x = winSize.width / 2;
		this._kathia.y = 50;
        this._kathia.runAction(seq2);

        this._drawNode1.drawCardinalSpline(array, 0, 100, 1);
        this._drawNode2.drawCardinalSpline(array, 1, 100, 1);
        //----end11----
    },

    subtitle:function () {
        return "Cardinal Spline paths. Testing different tensions for one array";
    },
    title:function () {
        return "CardinalSplineBy / CardinalSplineAt";
    },
    //
    // Automation
    //
    testDuration:2.1,
    setupAutomation:function() {
        this.scheduleOnce(this.checkControl1, 0.5);
        this.scheduleOnce(this.checkControl2, 1.0);
        this.scheduleOnce(this.checkControl3, 1.5);
    },
    checkControl1:function(dt) {
        this.control1 = cc.p(this._tamara.x, this._tamara.y);
    },
    verifyControl1:function(dt) {
        var x = Math.abs( 50 + winSize.width/2 - 30 - this.control1.x);
        var y = Math.abs( 50 - this.control1.y);
        //  -/+ 5 pixels of error
        return ( x < 5 && y < 5);
    },
    checkControl2:function(dt) {
        this.control2 = cc.p(this._tamara.x, this._tamara.y);
    },
    verifyControl2:function(dt) {
        var x = Math.abs( 50 + winSize.width/2 - 30 - this.control2.x );
        var y = Math.abs( 50 + winSize.height - 80 - this.control2.y );
        //  -/+ 5 pixels of error
        return ( x < 5 && y < 5);
    },
    checkControl3:function(dt) {
        this.control3 = cc.p(this._tamara.x, this._tamara.y);
    },
    verifyControl3:function(dt) {
        var x = Math.abs( 50 - this.control3.x );
        var y = Math.abs( 50 + winSize.height - 80 - this.control3.y );
        //  -/+ 5 pixels of error
        return ( x < 5 && y < 5);
    },

    getExpectedResult:function() {
        var ret = [ true,
                    true,
                    true,
                    {"x":50,"y":50}];
        return JSON.stringify(ret);
    },

    getCurrentResult:function() {
        var ret = [];
        ret.push( this.verifyControl1() );
        ret.push( this.verifyControl2() );
        ret.push( this.verifyControl3() );
        ret.push( cc.p(this._tamara.x, this._tamara.y) );

        return JSON.stringify(ret);
    }
});

//------------------------------------------------------------------
//
// ActionCatmullRom
//
//------------------------------------------------------------------
var ActionCatmullRom = ActionsDemo.extend({
    _drawNode1: null,
    _drawNode2: null,

    _code:"a = cc.catmullRomBy( time, array_of_points );\n" +
        " a = cc.catmullRomTo( time, array_of_points );",

    ctor:function () {
        this._super();

        this._drawNode1 = new cc.DrawNode();
        this._drawNode1.x = 50;
        this._drawNode1.y = 50;
        this._drawNode1.setDrawColor(cc.color(255,255,255,255));
        this.addChild(this._drawNode1);

        this._drawNode2 = new cc.DrawNode();
        this._drawNode2.setDrawColor(cc.color(255,255,255,255));
        this.addChild(this._drawNode2);
    },

    onEnter:function () {

        //----start12----onEnter
        this._super();

        this.centerSprites(2);

        var delay = cc.delayTime(0.25);

        //
        // sprite 1 (By)
        //
        // startPosition can be any coordinate, but since the movement
        // is relative to the Catmull Rom curve, it is better to start with (0,0).
        //
        this._tamara.x = 50;
		this._tamara.y = 50;

        var array = [
            cc.p(0, 0),
            cc.p(80, 80),
            cc.p(winSize.width - 80, 80),
            cc.p(winSize.width - 80, winSize.height - 80),
            cc.p(80, winSize.height - 80),
            cc.p(80, 80),
            cc.p(winSize.width / 2, winSize.height / 2)
        ];

        var action1 = cc.catmullRomBy(3, array);
        var reverse1 = action1.reverse();
        var seq1 = cc.sequence(action1, delay, reverse1);

        this._tamara.runAction(seq1);

        //
        // sprite 2 (To)
        //
        // The startPosition is not important here, because it uses a "To" action.
        // The initial position will be the 1st point of the Catmull Rom path
        //
        var array2 = [
            cc.p(winSize.width / 2, 30),
            cc.p(winSize.width - 80, 30),
            cc.p(winSize.width - 80, winSize.height - 80),
            cc.p(winSize.width / 2, winSize.height - 80),
            cc.p(winSize.width / 2, 30) ];

        var action2 = cc.catmullRomTo(3, array2);
        var reverse2 = action2.reverse();

        var seq2 = cc.sequence(action2, delay.clone(), reverse2);

        this._kathia.runAction(seq2);

        this._drawNode1.drawCatmullRom(array,50, 1);
        this._drawNode2.drawCatmullRom(array2,50, 1);
        //----end12----
    },
    subtitle:function () {
        return "Catmull Rom spline paths. Testing reverse too";
    },
    title:function () {
        return "CatmullRomBy / CatmullRomTo";
    },
    //
    // Automation
    //
    testDuration:3.1,
    setupAutomation:function() {
        this.scheduleOnce(this.checkControl1, 3 / 4 * 0);
        this.scheduleOnce(this.checkControl2, 3 / 4 * 1);
        this.scheduleOnce(this.checkControl3, 3 / 4 * 2);
    },
    checkControl1:function(dt) {
        this.control1 = cc.p(this._kathia.x, this._kathia.y);
    },
    verifyControl1:function(dt) {
        var x = Math.abs( winSize.width/2 - this.control1.x);
        var y = Math.abs( 30 - this.control1.y);
        //  -/+ 5 pixels of error
        return ( x < 5 && y < 5);
    },
    checkControl2:function(dt) {
        this.control2 = cc.p(this._kathia.x, this._kathia.y);
    },
    verifyControl2:function(dt) {
        var x = Math.abs( winSize.width - 80 - this.control2.x );
        var y = Math.abs( 30 - this.control2.y );
        //  -/+ 5 pixels of error
        return ( x < 5 && y < 5);
    },
    checkControl3:function(dt) {
        this.control3 = cc.p(this._kathia.x, this._kathia.y);
    },
    verifyControl3:function(dt) {
        var x = Math.abs( winSize.width - 80 - this.control3.x );
        var y = Math.abs( winSize.height - 80 - this.control3.y );
        //  -/+ 5 pixels of error
        return ( x < 5 && y < 5);
    },

    getExpectedResult:function() {
        var ret = [ true,
                    true,
                    true,
                    {"x":winSize.width/2,"y":30}];
        return JSON.stringify(ret);
    },

    getCurrentResult:function() {
        var ret = [];
        ret.push( this.verifyControl1() );
        ret.push( this.verifyControl2() );
        ret.push( this.verifyControl3() );
        ret.push( cc.p(this._kathia.x, this._kathia.y) );

        return JSON.stringify(ret);
    }
});

//------------------------------------------------------------------
//
// ActionTargeted
//
//------------------------------------------------------------------
var ActionTargeted = ActionsDemo.extend({
    _code:"a = cc.targetedAction( target, action );",

    onEnter:function () {
        //----start31----onEnter
        this._super();
        this.centerSprites(2);

        var jump1 = cc.jumpBy(2, cc.p(0, 0), 100, 3);
        var jump2 = jump1.clone();
        var rot1 = cc.rotateBy(1, 360);
        var rot2 = rot1.clone();

        var t1 = cc.targetedAction(this._kathia, jump2);
        var t2 = cc.targetedAction(this._kathia, rot2);

        var seq = cc.sequence(jump1, t1, rot1, t2);

        var always = seq.repeatForever();

        this._tamara.runAction(always);
        //----end31----
    },
    title:function () {
        return "Action that runs on another target. Useful for sequences";
    },
    subtitle:function () {
        return "ActionTargeted";
    }
});

//------------------------------------------------------------------
//
// ActionTargetedCopy
//
//------------------------------------------------------------------
var ActionTargetedCopy = ActionsDemo.extend({
    onEnter:function () {
        //----start32----onEnter
        this._super();
        this.centerSprites(2);

        var jump1 = cc.jumpBy(2, cc.p(0, 0), 100, 3);
        var jump2 = jump1.clone();

        var t1 = cc.targetedAction(this._kathia, jump2);
        var t_copy = t1.clone();

        var seq = cc.sequence(jump1, t_copy);

        this._tamara.runAction(seq);
        //----end32----
    },
    title:function () {
        return "Action that runs on another target. Useful for sequences";
    },
    subtitle:function () {
        return "Testing copy on TargetedAction";
    }
});

//------------------------------------------------------------------
//
// ActionStackableMove
//
//------------------------------------------------------------------
var ActionStackableMove = ActionsDemo.extend({
    onEnter:function () {
        //----start33----onEnter
        this._super();
        this.centerSprites(1);

        this._grossini.x = 40;
		this._grossini.y = winSize.height / 2;

        // shake
        var move = cc.moveBy(0.2, cc.p(0,50));
        var move_back = move.reverse();
        var delay = cc.delayTime(0.25);
        var move_seq = cc.sequence( move, move_back );
        var move_rep = move_seq.repeatForever();
        this._grossini.runAction( move_rep );

        // move
        var action = cc.moveBy(2, cc.p(winSize.width - 80, 0));
        var back = action.reverse();
        var seq = cc.sequence(action, back);
        var repeat = seq.repeatForever();
        this._grossini.runAction(repeat);
        //----end33----

    },
    title:function () {
        return "Stackable actions: MoveBy + MoveBy";
    },
    subtitle:function () {
        return "Grossini shall move up and down while moving horizontally";
    },
    //
    // Automation
    //
    testDuration:0.2,
    getExpectedResult:function() {
        var ret = [true, true];
        return JSON.stringify(ret);
    },

    getCurrentResult:function() {
        var ret = [];
        var x = this._grossini.x, y = this._grossini.y;
        var error = 10;
        var expected_x = 40 + 0.2 * (winSize.width-80) / 2;
        var expected_y =winSize.height/2 + 50;
        var ret_x = x < expected_x+error && x > expected_x-error;
        var ret_y = y < expected_y+error && y > expected_y-error;
        ret.push( ret_x );
        ret.push( ret_y );
        return JSON.stringify(ret);
    }
});

//------------------------------------------------------------------
//
// ActionStackableJump
//
//------------------------------------------------------------------
var ActionStackableJump = ActionsDemo.extend({
    onEnter:function () {

        //----start34----onEnter
        this._super();
        this.centerSprites(1);

        this._grossini.x = 40;
		this._grossini.y = winSize.height / 2;

        // shake
        var move = cc.moveBy(0.05, cc.p(8, 8));
        var move_back = move.reverse();
        var move_seq = cc.sequence(move, move_back);
        var move_rep = move_seq.repeatForever();
        this._grossini.runAction(move_rep);

        // jump
        var action = cc.jumpBy(2, cc.p(winSize.width - 80, 0), 90, 5);
        var back = action.reverse();
        var seq = cc.sequence(action, back);
        var repeat = seq.repeatForever();
        this._grossini.runAction(repeat);
        //----end34----

    },
    title:function () {
        return "Stackable actions: MoveBy + JumpBy";
    },
    subtitle:function () {
        return "Grossini shall shake while he is jumping";
    }
});

//------------------------------------------------------------------
//
// ActionStackableBezier
//
//------------------------------------------------------------------
var ActionStackableBezier = ActionsDemo.extend({
    onEnter:function () {
        //----start35----onEnter
        this._super();
        this.centerSprites(1);

        this._grossini.x = 40;
		this._grossini.y = winSize.height / 2;

        // shake
        var move = cc.moveBy(0.05, cc.p(8, 8));
        var move_back = move.reverse();
        var move_seq = cc.sequence(move, move_back);
        var move_rep = move_seq.repeatForever();
        this._grossini.runAction(move_rep);

        // Bezier
        var controlPoints = [ cc.p(0, winSize.height / 2),
            cc.p(winSize.width - 80, -winSize.height / 2),
            cc.p(winSize.width - 80, 100) ];

        var bezierForward = cc.bezierBy(3, controlPoints);
        var repeat = cc.sequence(bezierForward, bezierForward.reverse()).repeatForever();
        this._grossini.runAction(repeat);
        //----end35----

    },
    title:function () {
        return "Stackable actions: MoveBy + BezierBy";
    },
    subtitle:function () {
        return "Grossini shall shake while he moves along a bezier path";
    }
});

//------------------------------------------------------------------
//
// ActionStackableCatmullRom
//
//------------------------------------------------------------------
var ActionStackableCatmullRom = ActionsDemo.extend({
    onEnter:function () {
        //----start36----onEnter
        this._super();
        this.centerSprites(1);

        this._grossini.x = 40;
		this._grossini.y = 40;

        // shake
        var move = cc.moveBy(0.05, cc.p(8, 8));
        var move_back = move.reverse();
        var move_seq = cc.sequence(move, move_back);
        var move_rep = move_seq.repeatForever();
        this._grossini.runAction(move_rep);

        // CatmullRom
        var array = [
            cc.p(0, 0),
            cc.p(80, 80),
            cc.p(winSize.width - 80, 80),
            cc.p(winSize.width - 80, winSize.height - 80),
            cc.p(80, winSize.height - 80),
            cc.p(80, 80),
            cc.p(winSize.width / 2, winSize.height / 2)
        ];

        var action1 = cc.catmullRomBy(6, array);
        var reverse1 = action1.reverse();
        var seq1 = cc.sequence(action1, reverse1);
        var repeat = seq1.repeatForever();
        this._grossini.runAction(repeat);
        //----end36----
    },
    title:function () {
        return "Stackable actions: MoveBy + CatmullRomBy";
    },
    subtitle:function () {
        return "Grossini shall shake while he moves along a CatmullRom path";
    }
});

//------------------------------------------------------------------
//
// ActionStackableCardinalSpline
//
//------------------------------------------------------------------
var ActionStackableCardinalSpline = ActionsDemo.extend({
    onEnter:function () {
        //----start37----onEnter
        this._super();
        this.centerSprites(1);

        this._grossini.x = 40;
		this._grossini.y = 40;

        // shake
        var move = cc.moveBy(0.05, cc.p(8, 8));
        var move_back = move.reverse();
        var move_seq = cc.sequence(move, move_back);
        var move_rep = move_seq.repeatForever();
        this._grossini.runAction(move_rep);

        // CardinalSpline
        var array = [
            cc.p(0, 0),
            cc.p(80, 80),
            cc.p(winSize.width - 80, 80),
            cc.p(winSize.width - 80, winSize.height - 80),
            cc.p(80, winSize.height - 80),
            cc.p(80, 80),
            cc.p(winSize.width / 2, winSize.height / 2)
        ];

        var action1 = cc.cardinalSplineBy(6, array, 0.9);
        var reverse1 = action1.reverse();
        var seq1 = cc.sequence(action1, reverse1);
        var repeat = seq1.repeatForever();
        this._grossini.runAction(repeat);
        //----end37----
    },
    title:function () {
        return "Stackable actions: MoveBy + CardinalSplineBy";
    },
    subtitle:function () {
        return "Grossini shall shake while he moves along a CardinalSpline path";
    }
});

//------------------------------------------------------------------
//
// PauseResumeActions
//
//------------------------------------------------------------------
var PauseResumeActions = ActionsDemo.extend({
    _pausedTargets:[],
    onEnter:function () {
        //----start38----onEnter
        this._super();
        this.centerSprites(2);

        this._tamara.runAction(cc.rotateBy(3, 360).repeatForever());
        this._grossini.runAction(cc.rotateBy(3, -360).repeatForever());
        this._kathia.runAction(cc.rotateBy(3, 360).repeatForever());

        this.schedule(this.pause, 3, false, 0);
        this.schedule(this.resume, 5, false, 0);
        //----end38----
    },

    pause:function () {
        cc.log("Pausing");
        this._pausedTargets = director.getActionManager().pauseAllRunningActions();
    },
    resume:function () {
        cc.log("Resuming");
        director.getActionManager().resumeTargets(this._pausedTargets);
    },

    title:function () {
        return "PauseResumeActions";
    },
    subtitle:function () {
        return "All actions pause at 3s and resume at 5s";
    }
});

//------------------------------------------------------------------
//
// Issue1305
//
//------------------------------------------------------------------
var Issue1305 = ActionsDemo.extend({
    _spriteTemp:null,
    onEnter:function () {
        //----start39----onEnter
        this._super();
        this.centerSprites(0);

        this._spriteTmp = new cc.Sprite(s_pathGrossini);
        this._spriteTmp.retain();
        /* c++ can't support block, so we use CCCallFuncN instead.
         [spriteTmp_ runAction:[CCCallBlockN actionWithBlock:^(CCNode* node) {
         NSLog(@"This message SHALL ONLY appear when the sprite is added to the scene, NOT BEFORE");
         }] ];
         */

        this._spriteTmp.runAction(cc.callFunc(this.onLog, this));
        this.scheduleOnce(this.onAddSprite, 2);
        //----end39----
    },
    onExit:function () {
        this._super();
        if (this._spriteTmp)
        {
            this._spriteTmp.release();
            this._spriteTmp = null;
        }
    },
    onLog:function (pSender) {
        cc.log("This message SHALL ONLY appear when the sprite is added to the scene, NOT BEFORE");
    },
    onAddSprite:function (dt) {
        this._spriteTmp.x = 250;
		this._spriteTmp.y = 250;
        if (this._spriteTmp)
        {
            this.addChild(this._spriteTmp);
            this._spriteTmp.release();
            this._spriteTmp = null;
        }
    },
    title:function () {
        return "Issue 1305";
    },
    subtitle:function () {
        return "In two seconds you should see a message on the console. NOT BEFORE.";
    }
});

//------------------------------------------------------------------
//
// Issue1305_2
//
//------------------------------------------------------------------
var Issue1305_2 = ActionsDemo.extend({
    onEnter:function () {
        //----start40----onEnter
        this._super();
        this.centerSprites(0);

        var spr = new cc.Sprite(s_pathGrossini);
        spr.x = 200;
		spr.y = 200;
        this.addChild(spr);

        var act1 = cc.moveBy(2, cc.p(0, 100));

        var act2 = cc.callFunc(this.onLog1);
        var act3 = cc.moveBy(2, cc.p(0, -100));
        var act4 = cc.callFunc(this.onLog2, this);
        var act5 = cc.moveBy(2, cc.p(100, -100));
        var act6 = cc.callFunc(this.onLog3.bind(this));
        var act7 = cc.moveBy(2, cc.p(-100, 0));
        var act8 = cc.callFunc(this.onLog4, this);

        var actF = cc.sequence(act1, act2, act3, act4, act5, act6, act7, act8);

        //    [spr runAction:actF];
        director.getActionManager().addAction(actF, spr, false);
        //----end40----
    },
    onLog1:function () {
        cc.log("1st block");
    },
    onLog2:function () {
        cc.log("2nd block");
    },
    onLog3:function () {
        cc.log("3rd block");
    },
    onLog4:function () {
        cc.log("4th block");
    },
    title:function () {
        return "Issue 1305 #2";
    },
    subtitle:function () {
        return "See console. You should only see one message for each block";
    }
});

//------------------------------------------------------------------
//
// Issue1288
//
//------------------------------------------------------------------
var Issue1288 = ActionsDemo.extend({
    onEnter:function () {
        //----start41----onEnter
        this._super();
        this.centerSprites(0);

        var spr = new cc.Sprite(s_pathGrossini);
        spr.x = 100;
		spr.y = 100;
        this.addChild(spr);

        var act1 = cc.moveBy(0.5, cc.p(100, 0));
        var act2 = act1.reverse();
        var act3 = cc.sequence(act1, act2);
        var act4 = act3.repeat(2);

        spr.runAction(act4);
        //----end41----
    },
    title:function () {
        return "Issue 1288";
    },
    subtitle:function () {
        return "Sprite should end at the position where it started.";
    }
});

//------------------------------------------------------------------
//
// Issue1288_2
//
//------------------------------------------------------------------
var Issue1288_2 = ActionsDemo.extend({
    onEnter:function () {
        //----start42----onEnter
        this._super();
        this.centerSprites(0);

        var spr = new cc.Sprite(s_pathGrossini);
        spr.x = 100;
		spr.y = 100;
        this.addChild(spr);

        var act1 = cc.moveBy(0.5, cc.p(100, 0));
        spr.runAction(act1.repeat(1));
        //----end42----
    },
    title:function () {
        return "Issue 1288 #2";
    },
    subtitle:function () {
        return "Sprite should move 100 pixels, and stay there";
    }
});

//------------------------------------------------------------------
//
// Issue1327
//
//------------------------------------------------------------------
var Issue1327 = ActionsDemo.extend({
    onEnter:function () {
        //----start43----onEnter
        this._super();
        this.centerSprites(0);

        var spr = new cc.Sprite(s_pathGrossini);
        spr.x = 100;
        spr.y = 100;
        this.addChild(spr);

        var act1 = cc.callFunc(this.onLogSprRotation);
        var act2 = cc.rotateBy(0.25, 45);
        var act3 = cc.callFunc(this.onLogSprRotation, this);
        var act4 = cc.rotateBy(0.25, 45);
        var act5 = cc.callFunc(this.onLogSprRotation.bind(this));
        var act6 = cc.rotateBy(0.25, 45);
        var act7 = cc.callFunc(this.onLogSprRotation);
        var act8 = cc.rotateBy(0.25, 45);
        var act9 = cc.callFunc(this.onLogSprRotation);

        var actF = cc.sequence(act1, act2, act3, act4, act5, act6, act7, act8, act9);
        spr.runAction(actF);
        //----end43----
    },
    onLogSprRotation:function (pSender) {
        cc.log(pSender.rotation);
    },
    title:function () {
        return "Issue 1327";
    },
    subtitle:function () {
        return "See console: You should see: 0, 45, 90, 135, 180";
    }
});

//------------------------------------------------------------------
//
// Issue1438
//
//------------------------------------------------------------------
var Issue1438 = ActionsDemo.extend({
    onEnter:function () {
        //----start45----onEnter
        this._super();
        this.centerSprites(2);

        //
        // manual animation
        //
        var animation = new cc.Animation();

        // Add 60 frames
        for (var j = 0; j < 4; j++) {
            for (var i = 1; i < 15; i++) {
                var frameName = "Images/grossini_dance_" + ((i < 10) ? ("0" + i) : i) + ".png";
                animation.addSpriteFrameWithFile(frameName);
            }
        }
        // And display 60 frames per second
        animation.setDelayPerUnit(1 / 60);
        animation.setRestoreOriginalFrame(true);

        var action = cc.animate(animation);
        this._kathia.runAction(action);

        //
        // File animation
        //
        var animCache = cc.animationCache;
        animCache.addAnimations(s_animations2Plist);
        var animation2 = animCache.getAnimation("dance_1");
        animation2.setDelayPerUnit(1 / 60);

        var action2 = cc.animate(animation2);
        this._tamara.runAction(cc.sequence(action2, action2.reverse()));
        //----end45----
    },

    title:function () {
        return "Animation";
    },

    subtitle:function () {
        return "Issue 1438. Set FPS to 30 to test this bug.";
    }
});

//------------------------------------------------------------------
//
// Issue1438
//
//------------------------------------------------------------------
var Issue1446 = ActionsDemo.extend({
    title:function () {
        return "Sequence + Speed in 'reverse mode'";
    },

    subtitle:function () {
        return "Issue #1446. 'Hello World' should be visible for only 0.1 seconds";
    },

    onEnter:function () {
        //----start46----onEnter
        this._super();
        this.centerSprites(0);
        var label = this.label = new cc.LabelTTF("Hello World", "Arial", 64);

        label.x = winSize.width / 2;
	    label.y = winSize.height / 2;
        label.opacity = 0;

        this.addChild(label);

        this.backwardsFade = cc.speed(cc.sequence(
            cc.delayTime(2),
            cc.fadeTo(1, 255),
            cc.delayTime(2)), 1);
        label.runAction(this.backwardsFade);

        // Comment out to see that 1.0 in the update function is called which is expected
        // Leave it uncommented to see that 0.0 is never called when going in reverse
        this.scheduleOnce(this.stepForwardGoBackward, 0.1);
        //----end46----
    },

    stepForwardGoBackward:function () {
        var action = this.backwardsFade.getInnerAction();
        action.step(2.5);
        // Try with -10.0f and you can see the opacity not fully faded out. Try with lower values to see it 'almost' fade out
        this.backwardsFade.setSpeed(-10);
    }
});

var SequenceRepeatTest = ActionsDemo.extend({
    onEnter:function () {
        //----start47----onEnter
        this._super();
        this.centerSprites(2);

        this._kathia.runAction(cc.repeat(cc.sequence(cc.blink(2, 3), cc.delayTime(2)), 3));

        var move = cc.moveBy(1, cc.p(50, 0));
        var move_back = move.reverse();
        var move_seq = cc.sequence(move, cc.delayTime(1), move_back, cc.delayTime(1));
        this._tamara.runAction(move_seq.repeat(3));
        //----end47----
    },

    title:function () {
        return "Sequence.repeat()";
    },

    subtitle:function () {
        return "Tests sequence.repeat function.";
    }
});

// custom action sample code
var customMoveBy = cc.MoveBy.extend({
    ctor:function (duration, deltaPos, deltaY) {
        this._super(duration, deltaPos, deltaY);
    },
    update:function (dt) {
        this._super(dt);

        if (this.getTarget()) { // rand color
            this.getTarget().setColor(cc.color(cc.rand()%255, cc.rand()%255, cc.rand()%255));
        }

    }
});

// special code, just for reduce code redundancy
var createCustomAction = function(actionObject) {
    var customAction = actionObject.extend({
        ctor:function () {
            actionObject.prototype.ctor.apply(this, arguments);
        },
        update:function (dt) {
            this._super(dt);
            if (this.getTarget()) { // rand color
                this.getTarget().setColor(cc.color(cc.rand()%255, cc.rand()%255, cc.rand()%255));
            }

        }
    });
    return customAction;
}

var ActionCustomTest = ActionsDemo.extend({
    _spritePos:null,
    _layer:null,
    onEnter:function () {
        //----start47----onEnter
        this._super();

        this.centerSprites(0);

        this._layer = new cc.Layer();
        this.addChild(this._layer);

        var label1 = new cc.MenuItemLabel(new cc.LabelTTF("showInterval(click me)", "arial", 25), this.createActionInterval, this);
        var label2 = new cc.MenuItemLabel(new cc.LabelTTF("showInstant(click me)", "arial", 25), this.createActionInstant, this);
        var buttonTemp = new cc.Menu(label1, label2);
        buttonTemp.alignItemsVerticallyWithPadding(10);
        buttonTemp.setPosition(cc.p(100, cc.winSize.height / 2 + 100));
        this.addChild(buttonTemp);

        this.createActionInterval();

    },
    initActionProperty:function(){
        this._spritePos = cc.p(25, 50);
        this._layer.removeAllChildren();
    },
    createActionInstant:function(){
        this.initActionProperty();

        /**
         * group 1
         */
        var spriteTemp = this.addandCreateSpriteTemp("cc.Show");
        spriteTemp.setVisible(false);
        var show = new (createCustomAction(cc.Show))();
        spriteTemp.runAction(show);

        spriteTemp = this.addandCreateSpriteTemp("cc.Hide", true);
        var hide = new (createCustomAction(cc.Hide))();
        spriteTemp.runAction(hide);

        spriteTemp = this.addandCreateSpriteTemp("cc.FlipX");
        var flipX = new (createCustomAction(cc.FlipX))(true);
        spriteTemp.runAction(flipX);

        /**
         * group 2
         */

        spriteTemp = this.addandCreateSpriteTemp("cc.FlipY");
        var flipY = new (createCustomAction(cc.FlipY))(true);
        spriteTemp.runAction(flipY);

        // RemoveSelf action don't need test
        // skip

        spriteTemp = this.addandCreateSpriteTemp("cc.Place");
        var place = new (createCustomAction(cc.Place))(spriteTemp.getPosition());
        spriteTemp.runAction(place);

        spriteTemp = this.addandCreateSpriteTemp("cc.CallFunc");
        var callFunc = new (createCustomAction(cc.CallFunc))(function(){cc.log("callfunc");}, this);
        spriteTemp.runAction(callFunc);
    },
    createActionInterval:function(){
        this.initActionProperty();

        /**
         * group 1
         */
        var spriteTemp = this.addandCreateSpriteTemp("cc.MoveBy");
        var move = new customMoveBy(5, cc.p(50, 0));
        spriteTemp.runAction(move);

        spriteTemp = this.addandCreateSpriteTemp("cc.MoveTo");
        var customMoveTo = new (createCustomAction(cc.MoveTo))(5, cc.p(spriteTemp.getPosition().x + 50, spriteTemp.getPosition().y));
        spriteTemp.runAction(customMoveTo);

        spriteTemp = this.addandCreateSpriteTemp("cc.sequence");
        var moveSeq = cc.sequence(new (createCustomAction(cc.MoveBy))(5, cc.p(50, 0)), cc.delayTime(1),
            new (createCustomAction(cc.MoveBy))(5, cc.p(50, 0)), cc.delayTime(1));
        spriteTemp.runAction(moveSeq);
        /**
         * group 2
         */
        spriteTemp = this.addandCreateSpriteTemp("cc.repeat");
        var moveRepeat = cc.repeat(new (createCustomAction(cc.MoveBy))(5, cc.p(50, 0)), 2);
        spriteTemp.runAction(moveRepeat);

        spriteTemp = this.addandCreateSpriteTemp("cc.repeatForever");
        var moveRepeatForever = cc.repeatForever(cc.sequence(new (createCustomAction(cc.MoveBy))(5, cc.p(50, 0)),
            new (createCustomAction(cc.MoveBy))(5, cc.p(-50, 0))));
        spriteTemp.runAction(moveRepeatForever);

        spriteTemp = this.addandCreateSpriteTemp("cc.spawn");
        var moveRoationSpawn = cc.spawn(new (createCustomAction(cc.MoveBy))(5, cc.p(50, 0)),
            new (createCustomAction(cc.RotateBy))(5, 360));
        spriteTemp.runAction(moveRoationSpawn);

        /**
         * group 3
         */
        spriteTemp = this.addandCreateSpriteTemp("cc.RotateTo");
        var rotateTo = new (createCustomAction(cc.RotateTo))(5, 180);
        spriteTemp.runAction(rotateTo);

        spriteTemp = this.addandCreateSpriteTemp("cc.RotateBy");
        var rotateBy = new (createCustomAction(cc.RotateBy))(5, 270);
        spriteTemp.runAction(rotateBy);

        spriteTemp = this.addandCreateSpriteTemp("cc.SkewTo");
        var skewTo = new (createCustomAction(cc.SkewTo))(5, 20, 20);
        spriteTemp.runAction(skewTo);

        /**
         * group 4
         */
        spriteTemp = this.addandCreateSpriteTemp("cc.SkewBy");
        var skewBy = new (createCustomAction(cc.SkewBy))(5, 20, 20);
        spriteTemp.runAction(skewBy);

        spriteTemp = this.addandCreateSpriteTemp("cc.JumpBy");
        var jumpBy = new (createCustomAction(cc.JumpBy))(5, spriteTemp.getPosition(), 50, 4);
        spriteTemp.runAction(jumpBy);

        spriteTemp = this.addandCreateSpriteTemp("cc.JumpTo");
        var jumpTo = new (createCustomAction(cc.JumpTo))(5, spriteTemp.getPosition(), 50, 4);
        spriteTemp.runAction(jumpTo);

        /**
         * group 5
         */
        spriteTemp = this.addandCreateSpriteTemp("cc.BezierBy");
        var bezierBy = new (createCustomAction(cc.BezierBy))(5, [spriteTemp.getPosition(), cc.p(0, spriteTemp.getPosition().y),
            cc.p(cc.winSize.x, spriteTemp.getPosition().y), spriteTemp.getPosition()]);
        spriteTemp.runAction(bezierBy);

        spriteTemp = this.addandCreateSpriteTemp("cc.BezierTo");
        var bezierTo = new (createCustomAction(cc.BezierTo))(5, [cc.p(0, cc.winSize.height / 2), cc.p(300, -cc.winSize.height / 2), cc.p(300, 100)]);
        spriteTemp.runAction(bezierTo);

        spriteTemp = this.addandCreateSpriteTemp("cc.ScaleTo");
        var scaleTo = new (createCustomAction(cc.ScaleTo))(5, 0.5);
        spriteTemp.runAction(scaleTo);

        /**
         * group 6
         */
        spriteTemp = this.addandCreateSpriteTemp("cc.ScaleBy");
        var scaleBy = new (createCustomAction(cc.ScaleBy))(5, 1.5);
        spriteTemp.runAction(scaleBy);

        spriteTemp = this.addandCreateSpriteTemp("cc.Blink");
        var blink = new (createCustomAction(cc.Blink))(5, 2);
        spriteTemp.runAction(blink);

        spriteTemp = this.addandCreateSpriteTemp("cc.FadeTo");
        var fadeTo = new (createCustomAction(cc.FadeTo))(5, 64);
        spriteTemp.runAction(fadeTo);

        /**
         * group 7
         */
        spriteTemp = this.addandCreateSpriteTemp("cc.FadeIn");
        spriteTemp.setOpacity(128);
        var fadeIn = new (createCustomAction(cc.FadeIn))(5);
        spriteTemp.runAction(fadeIn);

        spriteTemp = this.addandCreateSpriteTemp("cc.FadeOut");
        spriteTemp.setOpacity(128);
        var fadeOut = new (createCustomAction(cc.FadeOut))(5);
        spriteTemp.runAction(fadeOut);

        spriteTemp = this.addandCreateSpriteTemp("cc.TintTo");
        var tintTo = new (createCustomAction(cc.TintTo))(5, 255, 0, 255);
        spriteTemp.runAction(tintTo);

        /**
         * group 8
         */
        spriteTemp = this.addandCreateSpriteTemp("cc.TintBy");
        var tintBy = new (createCustomAction(cc.TintBy))(5, -127, -255, -127);
        spriteTemp.runAction(tintBy);

        spriteTemp = this.addandCreateSpriteTemp("cc.Animate");
        var animation = new cc.Animation();
        for (var i = 1; i < 15; i++) {
            var frameName = "Images/grossini_dance_" + ((i < 10) ? ("0" + i) : i) + ".png";
            animation.addSpriteFrameWithFile(frameName);
        }
        animation.setDelayPerUnit(5 / 14);
        animation.setRestoreOriginalFrame(true);
        var animate = new (createCustomAction(cc.Animate))(animation);
        spriteTemp.runAction(animate);
    },
    addandCreateSpriteTemp:function(actionTypeName, addLabelInLayerFlag){
        var spriteTemp = new cc.Sprite(s_pathGrossini);
        this._layer.addChild(spriteTemp);
        spriteTemp.setPosition(this._spritePos);
        var spriteContentSize = spriteTemp.getContentSize();
        this._spritePos.y += spriteContentSize.height;
        if (this._spritePos.y > cc.winSize.height - spriteContentSize.height){
            this._spritePos.x += spriteContentSize.width;
            this._spritePos.y = 50;
        }

        if (actionTypeName){
            var label = new cc.LabelTTF(actionTypeName, "arial", 18);
            if (addLabelInLayerFlag){
                label.setPosition(spriteTemp.getPosition());
                this._layer.addChild(label);
            }
            else{
                label.setPosition(spriteContentSize.width/2, spriteContentSize.height / 2);
                spriteTemp.addChild(label);
            }

        }

        return spriteTemp;
    },
    title:function () {
        return "ActionCustomTest";
    },

    subtitle:function () {
        return "Tests custom action, every sprite changing rand color when they run actions";
    }
});

var ActionIssue13605 = ActionsDemo.extend({
    onEnter:function () {
        //----start47----onEnter
        this._super();
        this.centerSprites(2);

        var move = new customMoveBy(2, cc.p(50, 0));
        var move_back = move.reverse();
        var move_seq = cc.sequence(move, cc.delayTime(1), move_back, cc.delayTime(1));
        this._kathia.runAction(move_seq.repeat(2));

        var moveClone = move.clone();
        var moveCloneBack = moveClone.reverse();
        var moveCloneSeq = cc.sequence(moveClone, cc.delayTime(1), moveCloneBack, cc.delayTime(1));
        this._tamara.runAction(moveCloneSeq.repeat(2));
        //----end47----
    },

    title:function () {
        return "action reverse and clone issue";
    },

    subtitle:function () {
        return "action move and back will change rand color";
    }
});


//-
//
// Flow control
//
var arrayOfActionsTest = [
    ActionManual,
    ActionMove,
    ActionScale,
    ActionRotate,
    ActionRotateXY,
    ActionSkew,
    ActionSkewRotateScale,
    ActionJump,
    ActionBezier,
    ActionBezierToCopy,
    Issue1008,
    ActionCardinalSpline,
    ActionCatmullRom,
    ActionBlink,
    ActionFade,
    ActionTint,
    ActionSequence,
    ActionSequence2,
    ActionSpawn,
    ActionReverse,
    ActionDelayTime,
    ActionRepeat,
    ActionRepeatForever,
    ActionRotateToRepeat,
    ActionRotateJerk,
    ActionCallFunc1,
    ActionCallFunc2,
    ActionCallFunc3,
    ActionReverseSequence,
    ActionReverseSequence2,

    ActionFollow,
    ActionTargeted,
    ActionTargetedCopy,

    ActionStackableMove,
    ActionStackableJump,
    ActionStackableBezier,
    ActionStackableCatmullRom,
    ActionStackableCardinalSpline,

    PauseResumeActions,
    Issue1305,
    Issue1305_2,
    Issue1288,
    Issue1288_2,
    Issue1327,
    ActionAnimate,
    Issue1438,
    Issue1446,
    SequenceRepeatTest,
    ActionCustomTest,
    ActionIssue13605
];

var nextActionsTest = function () {
    actionsTestIdx++;
    actionsTestIdx = actionsTestIdx % arrayOfActionsTest.length;

    if(window.sideIndexBar){
        actionsTestIdx = window.sideIndexBar.changeTest(actionsTestIdx, 1);
    }

    return new arrayOfActionsTest[actionsTestIdx]();
};
var previousActionsTest = function () {
    actionsTestIdx--;
    if (actionsTestIdx < 0)
        actionsTestIdx += arrayOfActionsTest.length;

    if(window.sideIndexBar){
        actionsTestIdx = window.sideIndexBar.changeTest(actionsTestIdx, 1);
    }

    return new arrayOfActionsTest[actionsTestIdx]();
};
var restartActionsTest = function () {
    return new arrayOfActionsTest[actionsTestIdx]();
};
