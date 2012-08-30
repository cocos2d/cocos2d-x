//
// http://www.cocos2d-iphone.org
// http://www.cocos2d-html5.org
// http://www.cocos2d-x.org
//
// Javascript + cocos2d actions tests
//

require("js/helper.js");

director = cc.Director.getInstance();
winSize = director.getWinSize();
centerPos = cc.p( winSize.width/2, winSize.height/2 );
spriteFrameCache = cc.SpriteFrameCache.getInstance();

var scenes = [];
var currentScene = 0;

var nextScene = function () {
	currentScene = currentScene + 1;
	if( currentScene >= scenes.length )
		currentScene = 0;

	withTransition = true;
	loadScene(currentScene);
};

var previousScene = function () {
	currentScene = currentScene -1;
	if( currentScene < 0 )
		currentScene = scenes.length -1;

	withTransition = true;
	loadScene(currentScene);
};

var restartScene = function () {
	loadScene( currentScene );
};

var loadScene = function (sceneIdx)
{
	winSize = director.getWinSize();
	centerPos = cc.p( winSize.width/2, winSize.height/2 );

	var scene = new cc.Scene();
	scene.init();
	var layer = new scenes[ sceneIdx ]();

	scene.addChild( layer );

//	scene.walkSceneGraph(0);

	director.replaceScene( scene );
//    __jsc__.garbageCollect();
}

var s_pathSister1 = "grossinis_sister1.png";
var s_pathSister2 = "grossinis_sister2.png";
var s_pathBlock = "blocks.png";
var s_grossiniPlist = "animations/grossini.plist";

//
// Base Layer
//

var BaseLayer = cc.LayerGradient.extend({

    ctor:function () {
                                
        var parent = new cc.LayerGradient();
        __associateObjWithNative(this, parent);
        this.init(cc.c4b(0, 0, 0, 255), cc.c4b(0, 128, 255, 255));
    },

    title:function () {
        return "Progress Actions";
    },

    subtitle:function () {
        return "";
    },

    code:function () {
        return "";
    },

    restartCallback:function (sender) {
        restartScene();
    },

    nextCallback:function (sender) {
        nextScene();
    },

    backCallback:function (sender) {
       previousScene();
    },

    onEnter:function () {
        // DO NOT CALL this._super()
//        this._super();

        // add title and subtitle
        var label = cc.LabelTTF.create(this.title(), "Arial", 28);
        this.addChild(label, 1);
        label.setPosition( cc.p(winSize.width / 2, winSize.height - 40));

        var strSubtitle = this.subtitle();
        if (strSubtitle != "") {
            var l = cc.LabelTTF.create(strSubtitle, "Thonburi", 16);
            this.addChild(l, 1);
            l.setPosition( cc.p(winSize.width / 2, winSize.height - 70));
        }

        var strCode = this.code();
        if( strCode !="" ) {
            var label = cc.LabelTTF.create(strCode, 'CourierNewPSMT', 16);
            label.setPosition( cc.p( winSize.width/2, winSize.height-120) );
            this.addChild( label,10 );

            var labelbg = cc.LabelTTF.create(strCode, 'CourierNewPSMT', 16);
            labelbg.setColor( cc.c3b(10,10,255) );
            labelbg.setPosition( cc.p( winSize.width/2 +1, winSize.height-120 -1) );
            this.addChild( labelbg,9);
        }

        // Menu
        var item1 = cc.MenuItemImage.create("b1.png", "b2.png", this, this.backCallback);
        var item2 = cc.MenuItemImage.create("r1.png", "r2.png", this, this.restartCallback);
        var item3 = cc.MenuItemImage.create("f1.png", "f2.png", this, this.nextCallback);
        var item4 = cc.MenuItemFont.create("back", this, function() { require("js/main.js"); } );
        item4.setFontSize( 22 );

        var menu = cc.Menu.create(item1, item2, item3, item4 );

        menu.setPosition( cc.p(0,0) );
        item1.setPosition( cc.p(winSize.width / 2 - 100, 30));
        item2.setPosition( cc.p(winSize.width / 2, 30));
        item3.setPosition( cc.p(winSize.width / 2 + 100, 30));
        item4.setPosition( cc.p(winSize.width - 60, winSize.height - 30 ) );

        this.addChild(menu, 1);
    }
});

//------------------------------------------------------------------
//
// Tests 
//
//------------------------------------------------------------------
var SpriteProgressToRadial = BaseLayer.extend({
    onEnter:function () {
        this._super();

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

var SpriteProgressToHorizontal = BaseLayer.extend({
    onEnter:function () {
        this._super();

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

var SpriteProgressToVertical = BaseLayer.extend({
    onEnter:function () {
        this._super();

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

var SpriteProgressToRadialMidpointChanged = BaseLayer.extend({
    onEnter:function () {
        this._super();

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

var SpriteProgressBarVarious = BaseLayer.extend({
    onEnter:function () {
        this._super();

        var to = cc.ProgressTo.create(2, 100);

        var left = cc.ProgressTimer.create(cc.Sprite.create(s_pathSister1));
        left.setType(cc.PROGRESS_TIMER_TYPE_BAR);

        //    Setup for a bar starting from the bottom since the midpoint is 0 for the y
        left.setMidpoint(cc.p(0.5, 0.5));
        //    Setup for a vertical bar since the bar change rate is 0 for x meaning no horizontal change
        left.setBarChangeRate(cc.p(1, 0));
        this.addChild(left);
        left.setPosition(cc.p(150, winSize.height / 2));
        left.runAction(cc.RepeatForever.create(to.copy()));

        var middle = cc.ProgressTimer.create(cc.Sprite.create(s_pathSister2));
        middle.setType(cc.PROGRESS_TIMER_TYPE_BAR);
        //    Setup for a bar starting from the bottom since the midpoint is 0 for the y
        middle.setMidpoint(cc.p(0.5, 0.5));
        //    Setup for a vertical bar since the bar change rate is 0 for x meaning no horizontal change
        middle.setBarChangeRate(cc.p(1, 1));
        this.addChild(middle);
        middle.setPosition(cc.p(winSize.width / 2, winSize.height / 2));
        middle.runAction(cc.RepeatForever.create(to.copy()));

        var right = cc.ProgressTimer.create(cc.Sprite.create(s_pathSister2));
        right.setType(cc.PROGRESS_TIMER_TYPE_BAR);
        //    Setup for a bar starting from the bottom since the midpoint is 0 for the y
        right.setMidpoint(cc.p(0.5, 0.5));
        //    Setup for a vertical bar since the bar change rate is 0 for x meaning no horizontal change
        right.setBarChangeRate(cc.p(0, 1));
        this.addChild(right);
        right.setPosition(cc.p(winSize.width - 150, winSize.height / 2));
        right.runAction(cc.RepeatForever.create(to.copy()));
    },

    subtitle:function () {
        return "ProgressTo Bar Mid";
    }
});

var SpriteProgressBarTintAndFade = BaseLayer.extend({
    onEnter:function () {
        this._super();

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

var SpriteProgressWithSpriteFrame = BaseLayer.extend({
    onEnter:function () {
        this._super();

        var to = cc.ProgressTo.create(6, 100);

        // XXX-riq: We should simplify the API in this case.
//        spriteFrameCache.addSpriteFramesWithFile(s_grossiniPlist);
        spriteFrameCache.addSpriteFrames(s_grossiniPlist);

        // XXX-riq: This is incorrect. It is creating the Sprite with a FrameName, not a Frame
//        var left = cc.ProgressTimer.create(cc.Sprite.createWithSpriteFrame("grossini_dance_01.png"));
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
//
// Order of tests
//

scenes.push( SpriteProgressToRadial );
scenes.push( SpriteProgressToHorizontal );
scenes.push( SpriteProgressToVertical );
scenes.push( SpriteProgressToRadialMidpointChanged );
scenes.push( SpriteProgressBarVarious );
scenes.push( SpriteProgressBarTintAndFade );
scenes.push( SpriteProgressWithSpriteFrame );

//------------------------------------------------------------------
//
// Main entry point
//
//------------------------------------------------------------------
function run()
{
    var scene = cc.Scene.create();
    var layer = new scenes[currentScene]();
    scene.addChild( layer );

    var runningScene = director.getRunningScene();
    if( runningScene == null )
        director.runWithScene( scene );
    else
        director.replaceScene( cc.TransitionFade.create(0.5, scene ) );
}

run();


