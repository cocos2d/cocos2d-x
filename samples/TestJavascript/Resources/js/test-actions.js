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

var scenes = []
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
    __jsc__.dumpRoot();
    __jsc__.garbageCollect();
}


//
// Base Layer
//

var BaseLayer = cc.LayerGradient.extend({

    ctor:function () {
                                
        var parent = new cc.LayerGradient();
        __associateObjWithNative(this, parent);
        this.init(cc.c4b(0, 0, 0, 255), cc.c4b(0, 128, 255, 255));
    },

    centerSprites : function (numberOfSprites) {

        if (numberOfSprites == 0) {
            this._tamara.setVisible(false);
            this._kathia.setVisible(false);
            this._grossini.setVisible(false);
        }
        else if (numberOfSprites == 1) {
            this._tamara.setVisible(false);
            this._kathia.setVisible(false);
            this._grossini.setPosition(cc.p(winSize.width / 2, winSize.height / 2));
        }
        else if (numberOfSprites == 2) {
            this._kathia.setPosition(cc.p(winSize.width / 3, winSize.height / 2));
            this._tamara.setPosition(cc.p(2 * winSize.width / 3, winSize.height / 2));
            this._grossini.setVisible(false);
        }
        else if (numberOfSprites == 3) {
            this._grossini.setPosition(cc.p(winSize.width / 2, winSize.height / 2));
            this._tamara.setPosition(cc.p(winSize.width / 4, winSize.height / 2));
            this._kathia.setPosition(cc.p(3 * winSize.width / 4, winSize.height / 2));
        }
    },

    alignSpritesLeft : function (numberOfSprites) {

        if (numberOfSprites == 1) {
            this._tamara.setVisible(false);
            this._kathia.setVisible(false);
            this._grossini.setPosition(cc.p(60, winSize.height / 2));
        }
        else if (numberOfSprites == 2) {
            this._kathia.setPosition(cc.p(60, winSize.height / 3));
            this._tamara.setPosition(cc.p(60, 2 * winSize.height / 3));
            this._grossini.setVisible(false);
        }
        else if (numberOfSprites == 3) {
            this._grossini.setPosition(cc.p(60, winSize.height / 2));
            this._tamara.setPosition(cc.p(60, 2 * winSize.height / 3));
            this._kathia.setPosition(cc.p(60, winSize.height / 3));
        }
    },

    title:function () {
        return "No Title";
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
        var item1 = cc.MenuItemImage.create("Images/b1.png", "Images/b2.png", this, this.backCallback);
        var item2 = cc.MenuItemImage.create("Images/r1.png", "Images/r2.png", this, this.restartCallback);
        var item3 = cc.MenuItemImage.create("Images/f1.png", "Images/f2.png", this, this.nextCallback);
        var item4 = cc.MenuItemFont.create("back", this, function() { require("js/main.js"); } );
        item4.setFontSize( 22 );

        var menu = cc.Menu.create(item1, item2, item3, item4 );

        menu.setPosition( cc.p(0,0) );
        item1.setPosition( cc.p(winSize.width / 2 - 100, 30));
        item2.setPosition( cc.p(winSize.width / 2, 30));
        item3.setPosition( cc.p(winSize.width / 2 + 100, 30));
        item4.setPosition( cc.p(winSize.width - 60, winSize.height - 30 ) );

        this.addChild(menu, 1);

        // Setup Sprites for this:w
        this._grossini = cc.Sprite.create("Images/grossini.png");
        this._tamara = cc.Sprite.create("Images/grossinis_sister1.png");
        this._kathia = cc.Sprite.create("Images/grossinis_sister2.png");
        this.addChild(this._grossini, 1);
        this.addChild(this._tamara, 2);
        this.addChild(this._kathia, 3);
        this._grossini.setPosition(cc.p(winSize.width / 2, winSize.height / 3));
        this._tamara.setPosition(cc.p(winSize.width / 2, 2 * winSize.height / 3));
        this._kathia.setPosition(cc.p(winSize.width / 2, winSize.height / 2));
    }
});

//------------------------------------------------------------------
//
// ActionManual
//
//------------------------------------------------------------------
var ActionManual = BaseLayer.extend({
    onEnter:function () {
        this._super();

        this._tamara.setScaleX(2.5);
        //window.tam = this._tamara;
        this._tamara.setScaleY(-1.0);
        this._tamara.setPosition(cc.p(100, 70));
        this._tamara.setOpacity(128);

        this._grossini.setRotation(120);
        this._grossini.setPosition(cc.p(winSize.width / 2, winSize.height / 2));
        this._grossini.setColor( cc.c3b(255, 0, 0) );

        this._kathia.setPosition(cc.p(winSize.width - 100, winSize.height / 2));
        this._kathia.setColor(cc.c3b(0,0,255) );

    },
    title:function () {
        return "Manual Transformation";
    },
    code:function () {
        return "sprite.setPosition( cc.p(10,20) );\n" +
                "sprite.setRotation( 90 );\n" +
                "sprite.setScale( 2 );";
    }

});


//------------------------------------------------------------------
//
//	ActionMove
//
//------------------------------------------------------------------
var ActionMove = BaseLayer.extend({
    onEnter:function () {
        this._super();

        this.centerSprites(3);

        var actionTo = cc.MoveTo.create(2, cc.p(winSize.width - 40, winSize.height - 40));

        var actionBy = cc.MoveBy.create(2, cc.p(80, 80));
        var actionByBack = actionBy.reverse();

        this._tamara.runAction(actionTo);
        this._grossini.runAction(cc.Sequence.create(actionBy, actionByBack));
        this._kathia.runAction(cc.MoveTo.create(1, cc.p(40, 40)));
    },
    title:function () {
        return "MoveTo / MoveBy";
    },
    code:function () {
        return "a = cc.MoveBy.create( time, cc.p(x,y) );\n" +
               "a = cc.MoveTo.create( time, cc.p(x,y) );";
    },
});

//------------------------------------------------------------------
//
// ActionScale
//
//------------------------------------------------------------------
var ActionScale = BaseLayer.extend({
    onEnter:function () {
        this._super();

        this.centerSprites(3);

        var actionTo = cc.ScaleTo.create(2, 0.5);
        var actionBy = cc.ScaleBy.create(2, 2);
        var actionBy2 = cc.ScaleBy.create(2, 0.25, 4.5);
        var actionByBack = actionBy.reverse();
        var actionBy2Back = actionBy2.reverse();

        this._tamara.runAction(actionTo);
        this._kathia.runAction(cc.Sequence.create(actionBy2, actionBy2Back) );
        this._grossini.runAction(cc.Sequence.create(actionBy, actionByBack) );

    },
    title:function () {
        return "ScaleTo / ScaleBy";
    },
    code:function () {
        return "a = cc.ScaleBy.create( time, scale );\n" +
               "a = cc.ScaleTo.create( time, scaleX, scaleY );";
    },
});

//------------------------------------------------------------------
//
//	ActionSkew
//
//------------------------------------------------------------------
var ActionSkew = BaseLayer.extend({
    onEnter:function () {
        this._super();
        this.centerSprites(3);
        var actionTo = cc.SkewTo.create(2, 37.2, -37.2);
        var actionToBack = cc.SkewTo.create(2, 0, 0);
        var actionBy = cc.SkewBy.create(2, 0, -90);
        var actionBy2 = cc.SkewBy.create(2, 45.0, 45.0);
        var actionByBack = actionBy.reverse();
        var actionBy2Back = actionBy2.reverse();


        this._tamara.runAction(cc.Sequence.create(actionTo, actionToBack ));
        this._grossini.runAction(cc.Sequence.create(actionBy, actionByBack ));

        this._kathia.runAction(cc.Sequence.create(actionBy2, actionBy2Back ));


    },
    title:function () {
        return "SkewTo / SkewBy";
    },
    code:function () {
        return "a = cc.SkewBy.create( time, skew );\n" +
               "a = cc.SkewTo.create( time, skewX, skewY );";
    },
});

//------------------------------------------------------------------
//
//	ActionSkewRotateScale
//
//------------------------------------------------------------------
var ActionSkewRotateScale = BaseLayer.extend({
    onEnter:function () {
        this._super();
        this._tamara.removeFromParentAndCleanup(true);
        this._grossini.removeFromParentAndCleanup(true);
        this._kathia.removeFromParentAndCleanup(true);

        var boxSize = cc.size(100.0, 100.0);
        var box = cc.LayerColor.create(cc.c4b(255, 255, 0, 255));
        box.setAnchorPoint(cc.p(0, 0));
        box.setPosition(cc.p((winSize.width - boxSize.width) / 2, (winSize.height - boxSize.height) / 2));
        box.setContentSize(boxSize);

        var markrside = 10.0;
        var uL = cc.LayerColor.create(cc.c4b(255, 0, 0, 255));
        box.addChild(uL);
        uL.setContentSize(cc.size(markrside, markrside));
        uL.setPosition(cc.p(0, boxSize.height - markrside));
        uL.setAnchorPoint(cc.p(0, 0));

        var uR = cc.LayerColor.create(cc.c4b(0, 0, 255, 255));
        box.addChild(uR);
        uR.setContentSize(cc.size(markrside, markrside));
        uR.setPosition(cc.p(boxSize.width - markrside, boxSize.height - markrside));
        uR.setAnchorPoint(cc.p(0, 0));


        this.addChild(box);
        var actionTo = cc.SkewTo.create(2, 0., 2.);
        var rotateTo = cc.RotateTo.create(2, 61.0);
        var actionScaleTo = cc.ScaleTo.create(2, -0.44, 0.47);

        var actionScaleToBack = cc.ScaleTo.create(2, 1.0, 1.0);
        var rotateToBack = cc.RotateTo.create(2, 0);
        var actionToBack = cc.SkewTo.create(2, 0, 0);

        box.runAction(cc.Sequence.create(actionTo, actionToBack ));
        box.runAction(cc.Sequence.create(rotateTo, rotateToBack ));
        box.runAction(cc.Sequence.create(actionScaleTo, actionScaleToBack ));
    },
    title:function () {
        return "Skew + Rotate + Scale";
    },
});

//------------------------------------------------------------------
//
//	ActionRotate
//
//------------------------------------------------------------------
var ActionRotate = BaseLayer.extend({
    onEnter:function () {
        this._super();
        this.centerSprites(3);
        var actionTo = cc.RotateTo.create(2, 45);
        var actionTo2 = cc.RotateTo.create(2, -45);
        var actionTo0 = cc.RotateTo.create(2, 0);
        this._tamara.runAction(cc.Sequence.create(actionTo, actionTo0));

        var actionBy = cc.RotateBy.create(2, 360);
        var actionByBack = actionBy.reverse();
        this._grossini.runAction(cc.Sequence.create(actionBy, actionByBack ));

        this._kathia.runAction(cc.Sequence.create(actionTo2, actionTo0.copy() ));

    },
    title:function () {
        return "RotateTo / RotateBy";
    },
    code:function () {
        return "a = cc.RotateBy.create( time, degrees );\n" +
                "a = cc.RotateTo.create( time, degrees );";
    },
});


//------------------------------------------------------------------
//
// ActionJump
//
//------------------------------------------------------------------
var ActionJump = BaseLayer.extend({
    onEnter:function () {
        this._super();
        this.centerSprites(3);

        var actionTo = cc.JumpTo.create(2, cc.p(300, 300), 50, 4);
        var actionBy = cc.JumpBy.create(2, cc.p(300, 0), 50, 4);
        var actionUp = cc.JumpBy.create(2, cc.p(0, 0), 80, 4);
        var actionByBack = actionBy.reverse();

        this._tamara.runAction(actionTo);
        this._grossini.runAction(cc.Sequence.create(actionBy, actionByBack ));
        this._kathia.runAction(cc.RepeatForever.create(actionUp));

    },
    title:function () {
        return "JumpTo / JumpBy";
    },
    code:function () {
        return "a = cc.JumpBy.create( time, point, height, #_of_jumps );\n" +
               "a = cc.JumpTo.create( time, point, height, #_of_jumps );";
    },
});

//------------------------------------------------------------------
//
// ActionBezier
//
//------------------------------------------------------------------
var ActionBezier = BaseLayer.extend({
    onEnter:function () {
        this._super();

        //
        // startPosition can be any coordinate, but since the movement
        // is relative to the Bezier curve, make it (0,0)
        //

        this.centerSprites(3);

        // sprite 1
        var bezier = new cc.BezierConfig();
        bezier.controlPoint_1 = cc.p(0, winSize.height / 2);
        bezier.controlPoint_2 = cc.p(300, -winSize.height / 2);
        bezier.endPosition = cc.p(300, 100);

        var bezierForward = cc.BezierBy.create(3, bezier);
        var bezierBack = bezierForward.reverse();
        var rep = cc.RepeatForever.create(cc.Sequence.create(bezierForward, bezierBack ));


        // sprite 2
        this._tamara.setPosition(cc.p(80, 160));
        var bezier2 = new cc.BezierConfig();
        bezier2.controlPoint_1 = cc.p(100, winSize.height / 2);
        bezier2.controlPoint_2 = cc.p(200, -winSize.height / 2);
        bezier2.endPosition = cc.p(240, 160);

        var bezierTo1 = cc.BezierTo.create(2, bezier2);

        // sprite 3
        this._kathia.setPosition(cc.p(400, 160));
        var bezierTo2 = cc.BezierTo.create(2, bezier2);

        this._grossini.id = "gro";
        this._tamara.id = "tam";
        this._kathia.id = "kat";

        this._grossini.runAction(rep);
        this._tamara.runAction(bezierTo1);
        this._kathia.runAction(bezierTo2);

    },
    title:function () {
        return "BezierBy / BezierTo";
    }
});
//------------------------------------------------------------------
//
// ActionBlink
//
//------------------------------------------------------------------
var ActionBlink = BaseLayer.extend({
    onEnter:function () {
        this._super();
        this.centerSprites(2);

        var action1 = cc.Blink.create(2, 10);
        var action2 = cc.Blink.create(2, 5);

        this._tamara.runAction(action1);
        this._kathia.runAction(action2);

    },
    title:function () {
        return "Blink";
    },
    code:function () {
        return "a = cc.Blink.create( time, #_of_blinks );\n";
    },
});
//------------------------------------------------------------------
//
// ActionFade
//
//------------------------------------------------------------------
var ActionFade = BaseLayer.extend({
    onEnter:function () {
        this._super();
        this.centerSprites(2);
        this._tamara.setOpacity(0);
        var action1 = cc.FadeIn.create(1.0);
        var action1Back = action1.reverse();

        var action2 = cc.FadeOut.create(1.0);
        var action2Back = action2.reverse();

        this._tamara.runAction(cc.Sequence.create(action1, action1Back ));
        this._kathia.runAction(cc.Sequence.create(action2, action2Back ));


    },
    title:function () {
        return "FadeIn / FadeOut";
    },
    code:function () {
        return "" +
            "a = cc.FadeIn.create( time );\n" +
            "a = cc.FadeOut.create( time );\n"
    },
});
//------------------------------------------------------------------
//
// ActionTint
//
//------------------------------------------------------------------
var ActionTint = BaseLayer.extend({
    onEnter:function () {
        this._super();
        this.centerSprites(2);

        var action1 = cc.TintTo.create(2, 255, 0, 255);
        var action2 = cc.TintBy.create(2, -127, -255, -127);
        var action2Back = action2.reverse();

        this._tamara.runAction(action1);
        this._kathia.runAction(cc.Sequence.create(action2, action2Back));

    },
    title:function () {
        return "TintTo / TintBy";
    },
    code:function () {
        return "" +
            "a = cc.TintBy.create( time, red, green, blue );\n" +
            "a = cc.TintTo.create( time, red, green, blue );\n"
    },
});

//------------------------------------------------------------------
//
// ActionAnimate
//
//------------------------------------------------------------------
var ActionAnimate = BaseLayer.extend({
    onEnter:function () {
        this._super();
        this.centerSprites(3);

        //
        // Manual animation
        //
        var animation = cc.Animation.create();
        for (var i = 1; i < 15; i++) {
            var frameName = "Images/grossini_dance_" + ((i < 10) ? ("0" + i) : i) + ".png";
            animation.addSpriteFrameWithFilename(frameName);
        }
        animation.setDelayPerUnit(2.8 / 14);
        animation.setRestoreOriginalFrame(true);

        var action = cc.Animate.create(animation);
        this._grossini.runAction(cc.Sequence.create(action, action.reverse()));

        //
        // File animation
        //
        // With 2 loops and reverse
        var animCache = cc.AnimationCache.getInstance();

        animCache.addAnimations("animations/animations-2.plist");
        var animation2 = animCache.getAnimation("dance_1");

        var action2 = cc.Animate.create(animation2);
        this._tamara.runAction(cc.Sequence.create(action2, action2.reverse()));

        //
        // File animation
        //
        // with 4 loops
        var animation3 = animation2.copy();
        animation3.setLoops(4);

        var action3 = cc.Animate.create(animation3);
        this._kathia.runAction(action3);
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
var ActionSequence = BaseLayer.extend({
    onEnter:function () {
        this._super();
        this.alignSpritesLeft(1);

        var action = cc.Sequence.create(
            cc.MoveBy.create(2, cc.p(240, 0)),
            cc.RotateBy.create(2, 540) );

        this._grossini.runAction(action);

    },
    title:function () {
        return "Sequence: Move + Rotate";
    },
    code:function () {
        return "" +
            "a = cc.Sequence.create( a1, a2, a3,..., aN);\n";
    },
});
//------------------------------------------------------------------
//
//	ActionSequence2
//
//------------------------------------------------------------------
var ActionSequence2 = BaseLayer.extend({
    onEnter:function () {
        this._super();
        this.centerSprites(1);
        this._grossini.setVisible(false);
        var action = cc.Sequence.create(
            cc.Place.create(cc.p(200, 200)),
            cc.Show.create(),
            cc.MoveBy.create(1, cc.p(100, 0)),
            cc.CallFunc.create(this, this.callback1),
            cc.CallFunc.create(this, this.callback2),
            cc.CallFunc.create(this, this.callback3) );
        this._grossini.runAction(action);

    },
    callback1:function () {
        var label = cc.LabelTTF.create("callback 1 called", "Marker Felt", 16);
        label.setPosition(cc.p(winSize.width / 4 * 1, winSize.height / 2));

        this.addChild(label);
    },
    callback2:function () {
        var label = cc.LabelTTF.create("callback 2 called", "Marker Felt", 16);
        label.setPosition(cc.p(winSize.width / 4 * 2, winSize.height / 2));

        this.addChild(label);
    },
    callback3:function () {
        var label = cc.LabelTTF.create("callback 3 called", "Marker Felt", 16);
        label.setPosition(cc.p(winSize.width / 4 * 3, winSize.height / 2));

        this.addChild(label);
    },
    title:function () {
        return "Sequence of InstantActions";
    }
});
//------------------------------------------------------------------
//
//	ActionCallFunc
//
//------------------------------------------------------------------
var ActionCallFunc = BaseLayer.extend({
    onEnter:function () {
        this._super();
        this.centerSprites(3);

        var action = cc.Sequence.create(
            cc.MoveBy.create(2, cc.p(200, 0)),
            cc.CallFunc.create(this, this.callback1)
        );

        var action2 = cc.Sequence.create(
            cc.ScaleBy.create(2, 2),
            cc.FadeOut.create(2),
            cc.CallFunc.create(this, this.callback2)
        );

        var action3 = cc.Sequence.create(
            cc.RotateBy.create(3, 360),
            cc.FadeOut.create(2),
            cc.CallFunc.create(this, this.callback3, 0xbebabeba)
        );

        this._grossini.runAction(action);
        this._tamara.runAction(action2);
        this._kathia.runAction(action3);

    },
    callback1:function () {
        var label = cc.LabelTTF.create("callback 1 called", "Marker Felt", 16);
        label.setPosition(cc.p(winSize.width / 4 * 1, winSize.height / 2));
        this.addChild(label);
    },
    callback2:function () {
        var label = cc.LabelTTF.create("callback 2 called", "Marker Felt", 16);
        label.setPosition(cc.p(winSize.width / 4 * 2, winSize.height / 2));

        this.addChild(label);
    },
    callback3:function () {
        var label = cc.LabelTTF.create("callback 3 called", "Marker Felt", 16);
        label.setPosition(cc.p(winSize.width / 4 * 3, winSize.height / 2));
        this.addChild(label);
    },
    title:function () {
        return "Callbacks: CallFunc and friends";
    },
    code:function () {
        return "" +
            "a = cc.CallFunc.create( this, this.callback );\n" +
            "a = cc.CallFunc.create( this, this.callback, optional_arg );";
    },
});
//------------------------------------------------------------------
//
// ActionCallFuncND
//
//------------------------------------------------------------------
var ActionCallFuncND = BaseLayer.extend({
    onEnter:function () {
        this._super();
        this.centerSprites(1);

        var action = cc.Sequence.create(cc.MoveBy.create(2.0, cc.p(200, 0)),
            cc.CallFunc.create(this, this.removeGrossini, this._grossini) );

        this._grossini.runAction(action);

    },

    removeGrossini : function( spriteToRemove ) {
        spriteToRemove.removeFromParentAndCleanup( true );
    },

    title:function () {
        return "CallFunc + auto remove";
    },
    subtitle:function () {
        return "CallFunc + removeFromParentAndCleanup. Grossini dissapears in 2s";
    },
    code:function () {
        return "" +
            "a = cc.CallFunc.create( this, this.callback );\n" +
            "a = cc.CallFunc.create( this, this.callback, optional_arg );";
    },
});
//------------------------------------------------------------------
//
// ActionSpawn
//
//------------------------------------------------------------------
var ActionSpawn = BaseLayer.extend({
    onEnter:function () {
        this._super();
        this.alignSpritesLeft(1);

        var action = cc.Spawn.create(
            cc.JumpBy.create(2, cc.p(300, 0), 50, 4),
            cc.RotateBy.create(2, 720) );

        this._grossini.runAction(action);

    },
    title:function () {
        return "Spawn: Jump + Rotate";
    },
    code:function () {
        return "" +
            "a = cc.Spawn.create( a1, a2, ..., aN );";
    },
});
//------------------------------------------------------------------
//
// ActionRepeatForever
//
//------------------------------------------------------------------
var ActionRepeatForever = BaseLayer.extend({
    onEnter:function () {
        this._super();
        this.centerSprites(1);
        var action = cc.Sequence.create(
            cc.DelayTime.create(1),
            cc.CallFunc.create(this, this.repeatForever) );

        this._grossini.runAction(action);


    },
    repeatForever:function (sender) {
        var repeat = cc.RepeatForever.create(cc.RotateBy.create(1.0, 360));
        sender.runAction(repeat)
    },
    title:function () {
        return "CallFunc + RepeatForever";
    },
    code:function () {
        return "" +
            "a = cc.RepeatForever.create( action_to_repeat );";
    },
});
//------------------------------------------------------------------
//
// ActionRotateToRepeat
//
//------------------------------------------------------------------
var ActionRotateToRepeat = BaseLayer.extend({
    onEnter:function () {
        this._super();
        this.centerSprites(2);

        var act1 = cc.RotateTo.create(1, 90);
        var act2 = cc.RotateTo.create(1, 0);
        var seq = cc.Sequence.create(act1, act2);
        var rep1 = cc.RepeatForever.create(seq);
        var rep2 = cc.Repeat.create((seq.copy()), 10);

        this._tamara.runAction(rep1);
        this._kathia.runAction(rep2);

    },
    title:function () {
        return "Repeat/RepeatForever + RotateTo";
    },
    code:function () {
        return "" +
            "a = cc.Repeat.create( action_to_repeat, #_of_times );";
    },
});
//------------------------------------------------------------------
//
// ActionRotateJerk
//
//------------------------------------------------------------------
var ActionRotateJerk = BaseLayer.extend({
    onEnter:function () {
        this._super();
        this.centerSprites(2);
        var seq = cc.Sequence.create(
            cc.RotateTo.create(0.5, -20),
            cc.RotateTo.create(0.5, 20) );

        var rep1 = cc.Repeat.create(seq, 10);
        var rep2 = cc.RepeatForever.create((seq.copy()));

        this._tamara.runAction(rep1);
        this._kathia.runAction(rep2);
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
var ActionReverse = BaseLayer.extend({
    onEnter:function () {
        this._super();
        this.alignSpritesLeft(1);

        var jump = cc.JumpBy.create(2, cc.p(300, 0), 50, 4);
        var action = cc.Sequence.create(jump, jump.reverse() );

        this._grossini.runAction(action);
    },
    title:function () {
        return "Reverse an action";
    },
    code:function () {
        return "" +
            "a = action.reverse();";
    },
});
//------------------------------------------------------------------
//
// ActionDelayTime
//
//------------------------------------------------------------------
var ActionDelayTime = BaseLayer.extend({
    onEnter:function () {
        this._super();
        this.alignSpritesLeft(1);

        var move = cc.MoveBy.create(1, cc.p(150, 0));
        var action = cc.Sequence.create(move, cc.DelayTime.create(2), move );

        this._grossini.runAction(action);
    },
    title:function () {
        return "DelayTime: m + delay + m";
    },
    code:function () {
        return "" +
            "a = cc.DelayTime.create( time );";
    },
});
//------------------------------------------------------------------
//
// ActionReverseSequence
//
//------------------------------------------------------------------
var ActionReverseSequence = BaseLayer.extend({
    onEnter:function () {
        this._super();
        this.alignSpritesLeft(1);

        var move1 = cc.MoveBy.create(1, cc.p(250, 0));
        var move2 = cc.MoveBy.create(1, cc.p(0, 50));
        var seq = cc.Sequence.create(move1, move2, move1.reverse() );
        var action = cc.Sequence.create(seq, seq.reverse() );

        this._grossini.runAction(action);

    },
    title:function () {
        return "Reverse a sequence";
    }
});
//------------------------------------------------------------------
//
// ActionReverseSequence2
//
//------------------------------------------------------------------
var ActionReverseSequence2 = BaseLayer.extend({
    onEnter:function () {
        this._super();
        this.alignSpritesLeft(2);


        // Test:
        //   Sequence should work both with IntervalAction and InstantActions
        var move1 = cc.MoveBy.create(3, cc.p(250, 0));
        var move2 = cc.MoveBy.create(3, cc.p(0, 50));
        var tog1 = cc.ToggleVisibility.create();
        var tog2 = cc.ToggleVisibility.create();
        var seq = cc.Sequence.create(move1, tog1, move2, tog2, move1.reverse() );
        var action = cc.Repeat.create(
            cc.Sequence.create(
                seq,
                seq.reverse()
            ),
            3
        );


        // Test:
        //   Also test that the reverse of Hide is Show, and vice-versa
        this._kathia.runAction(action);

        var move_tamara = cc.MoveBy.create(1, cc.p(100, 0));
        var move_tamara2 = cc.MoveBy.create(1, cc.p(50, 0));
        var hide = cc.Hide.create()
        var seq_tamara = cc.Sequence.create(move_tamara, hide, move_tamara2 );
        var seq_back = seq_tamara.reverse();
        this._tamara.runAction(cc.Sequence.create(seq_tamara, seq_back ));
    },
    title:function () {
        return "Reverse sequence 2";
    }
});
//------------------------------------------------------------------
//
// ActionRepeat
//
//------------------------------------------------------------------
var ActionRepeat = BaseLayer.extend({
    onEnter:function () {
        this._super();
        this.alignSpritesLeft(2);


        var a1 = cc.MoveBy.create(1, cc.p(150, 0));
        var action1 = cc.Repeat.create(
            cc.Sequence.create(cc.Place.create(cc.p(60, 60)), a1 ),
            3);
        var action2 = cc.RepeatForever.create(
            (cc.Sequence.create((a1.copy()), a1.reverse() ))
        );

        this._kathia.runAction(action1);
        this._tamara.runAction(action2);
    },
    title:function () {
        return "Repeat / RepeatForever actions";
    }
});
//------------------------------------------------------------------
//
// ActionOrbit
//
//------------------------------------------------------------------
var ActionOrbit = BaseLayer.extend({
    onEnter:function () {
        this._super();
        this.centerSprites(3);

        var orbit1 = cc.OrbitCamera.create(2, 1, 0, 0, 180, 0, 0);
        var action1 = cc.Sequence.create(
            orbit1,
            orbit1.reverse());

        var orbit2 = cc.OrbitCamera.create(2, 1, 0, 0, 180, -45, 0);
        var action2 = cc.Sequence.create(
            orbit2,
            orbit2.reverse());

        var orbit3 = cc.OrbitCamera.create(2, 1, 0, 0, 180, 90, 0);
        var action3 = cc.Sequence.create(
            orbit3,
            orbit3.reverse() );

        this._kathia.runAction(cc.RepeatForever.create(action1));
        this._tamara.runAction(cc.RepeatForever.create(action2));
        this._grossini.runAction(cc.RepeatForever.create(action3));

        var move = cc.MoveBy.create(3, cc.p(100, -100));
        var move_back = move.reverse();
        var seq = cc.Sequence.create(move, move_back );
        var rfe = cc.RepeatForever.create(seq);
        this._kathia.runAction(rfe);
        this._tamara.runAction((rfe.copy()));
        this._grossini.runAction((rfe.copy()));

    },
    title:function () {
        return "OrbitCamera action";
    }
});
//------------------------------------------------------------------
//
// ActionFollow
//
//------------------------------------------------------------------
var ActionFollow = BaseLayer.extend({
    onEnter:function () {
        this._super();
        this.centerSprites(1);

        this._grossini.setPosition(cc.p(-200, winSize.height / 2));
        var move = cc.MoveBy.create(2, cc.p(winSize.width * 3, 0));
        var move_back = move.reverse();
        var seq = cc.Sequence.create(move, move_back );
        var rep = cc.RepeatForever.create(seq);

        this._grossini.runAction(rep);

        this.runAction(cc.Follow.create(this._grossini, cc.rect(0, 0, winSize.width * 2 - 100, winSize.height)));
    },
    title:function () {
        return "Follow action";
    }
});

//------------------------------------------------------------------
//
// ActionCardinalSpline
//
//------------------------------------------------------------------
var ActionCardinalSpline = BaseLayer.extend({

    onEnter:function () {
        this._super();

        this.centerSprites(2);

        var array = cc.PointArray.create(10);

        array.addControlPoint(cc.p(0, 0));
        array.addControlPoint(cc.p(winSize.width / 2 - 30, 0));
        array.addControlPoint(cc.p(winSize.width / 2 - 30, winSize.height - 80));
        array.addControlPoint(cc.p(0, winSize.height - 80));
        array.addControlPoint(cc.p(0, 0));

        //
        // sprite 1 (By)
        //
        // Spline with no tension (tension==0)
        //
        var action1 = cc.CardinalSplineBy.create(3, array, 0);
        var reverse1 = action1.reverse();
        var seq = cc.Sequence.create(action1, reverse1);

        this._tamara.setPosition(cc.p(50, 50));
        this._tamara.runAction(seq);

        //
        // sprite 2 (By)
        //
        // Spline with high tension (tension==1)
        //
        var action2 = cc.CardinalSplineBy.create(3, array, 1);
        var reverse2 = action2.reverse();
        var seq2 = cc.Sequence.create(action2, reverse2);

        this._kathia.setPosition(cc.p(winSize.width / 2, 50));
        this._kathia.runAction(seq2);
    },

    subtitle:function () {
        return "Cardinal Spline paths. Testing different tensions for one array";
    },
    title:function () {
        return "CardinalSplineBy / CardinalSplineAt";
    },
    code:function() {
        return "" +
            " a = cc.CadinalSplineBy.create( time, array_of_points, tension );\n" +
            " a = cc.CadinalSplineTo.create( time, array_of_points, tension );\n";
    
    },
});

//------------------------------------------------------------------
//
// ActionCatmullRom
//
//------------------------------------------------------------------
var ActionCatmullRom = BaseLayer.extend({

    onEnter:function () {
        this._super();

        this.centerSprites(2);

        var array1 = cc.PointArray.create( 10 );
        var array2 = cc.PointArray.create( 10 );

        //
        // sprite 1 (By)
        //
        // startPosition can be any coordinate, but since the movement
        // is relative to the Catmull Rom curve, it is better to start with (0,0).
        //
        this._tamara.setPosition(cc.p(50, 50));

        array1.addControlPoint(cc.p(0, 0));
        array1.addControlPoint(cc.p(80, 80));
        array1.addControlPoint(cc.p(winSize.width - 80, 80));
        array1.addControlPoint(cc.p(winSize.width - 80, winSize.height - 80));
        array1.addControlPoint(cc.p(80, winSize.height - 80));
        array1.addControlPoint(cc.p(80, 80));
        array1.addControlPoint(cc.p(winSize.width / 2, winSize.height / 2));

        var action1 = cc.CatmullRomBy.create(3, array1);
        var reverse1 = action1.reverse();
        var seq1 = cc.Sequence.create(action1, reverse1);

        this._tamara.runAction(seq1);

        //
        // sprite 2 (To)
        //
        // The startPosition is not important here, because it uses a "To" action.
        // The initial position will be the 1st point of the Catmull Rom path
        //
        array2.addControlPoint(cc.p(winSize.width / 2, 30));
        array2.addControlPoint(cc.p(winSize.width - 80, 30));
        array2.addControlPoint(cc.p(winSize.width - 80, winSize.height - 80));
        array2.addControlPoint(cc.p(winSize.width / 2, winSize.height - 80));
        array2.addControlPoint(cc.p(winSize.width / 2, 30));

        var action2 = cc.CatmullRomTo.create(3, array2);
        var reverse2 = action2.reverse();

        var seq2 = cc.Sequence.create(action2, reverse2);

        this._kathia.runAction(seq2);
    },
    subtitle:function () {
        return "Catmull Rom spline paths. Testing reverse too";
    },
    title:function () {
        return "CatmullRomBy / CatmullRomTo";
    },
    code:function() {
        return "" +
            " a = cc.CatmullRomBy.create( time, array_of_points );\n" +
            " a = cc.CatmullRomTo.create( time, array_of_points );\n";
    },
});

var ActionTargeted = BaseLayer.extend({
    onEnter:function () {
        this._super();
        this.centerSprites(2);

        var jump1 = cc.JumpBy.create(2, cc.p(0,0), 100, 3);
        var jump2 = jump1.copy();
        var rot1 =  cc.RotateBy.create(1, 360);
        var rot2 = rot1.copy();

        var t1 = cc.TargetedAction.create(this._kathia, jump2);
        var t2 = cc.TargetedAction.create(this._kathia, rot2);

        var seq = cc.Sequence.create(jump1, t1, rot1, t2);
        var always = cc.RepeatForever.create(seq);

        this._tamara.runAction(always);
    },
    subtitle:function () {
        return "Action that runs on another target. Useful for sequences";
    },
    title:function () {
        return "Targeted Action";
    },
    code:function () {
        return "a = cc.TargetedAction.create( target, action );";
    },
});

var PauseResumeActions = BaseLayer.extend({
    _pausedTargets:[],
    _elapsedTime : 0,
    _calledResume : false,
    _calledPause : false,
    onEnter:function () {
        this._super();
        this.centerSprites(2);

        this._tamara.runAction(cc.RepeatForever.create(cc.RotateBy.create(3, 360)));
        this._grossini.runAction(cc.RepeatForever.create(cc.RotateBy.create(3, -360)));
        this._kathia.runAction(cc.RepeatForever.create(cc.RotateBy.create(3, 360)));

        this.scheduleUpdate();
    },

    update:function (dt) {
        this._elapsedTime += dt;
        if( this._elapsedTime > 3 && ! this._calledPause ) {
            this.pause();
            this._calledPause = true;
        }
        if( this._elapsedTime > 5 && ! this._calledResume) {
            this.resume();
            this._calledResume = true;
        }
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

var Issue1305 = BaseLayer.extend({
    _spriteTemp:null,
    _elapsedTime:0,
    onEnter:function () {
        this._super();
        this.centerSprites(0);

        this._spriteTmp = cc.Sprite.create("Images/grossini.png");
        /* c++ can't support block, so we use CCCallFuncN instead.
         [spriteTmp_ runAction:[CCCallBlockN actionWithBlock:^(CCNode* node) {
         NSLog(@"This message SHALL ONLY appear when the sprite is added to the scene, NOT BEFORE");
         }] ];
         */

        this._spriteTmp.runAction(cc.CallFunc.create(this, this.log));
        this.scheduleUpdate();
    },
    onExit:function () {
        this._super();
    },
    log:function (pSender) {
        cc.log("This message SHALL ONLY appear when the sprite is added to the scene, NOT BEFORE");
    },
    update:function (dt) {
        this._elapsedTime += dt;
        if( this._elapsedTime > 2 ) {
            this.addSprite();
            this.unscheduleUpdate();
        }
    },
    addSprite:function () {
        this._spriteTmp.setPosition(cc.p(250,250));
        this.addChild(this._spriteTmp);
    },
    title:function () {
        return "Issue 1305";
    },
    subtitle:function () {
        return "In two seconds you should see a message on the console. NOT BEFORE.";
    }
});

var Issue1305_2 = BaseLayer.extend({
    onEnter:function () {
        this._super();
        this.centerSprites(0);

        var spr = cc.Sprite.create("Images/grossini.png");
        spr.setPosition(cc.p(200,200));
        this.addChild(spr);

        var act1 = cc.MoveBy.create(2 ,cc.p(0, 100));

        var act2 = cc.CallFunc.create(this, this.log1) ;
        var act3 = cc.MoveBy.create(2, cc.p(0, -100));
        var act4 = cc.CallFunc.create(this, this.log2) ;
        var act5 = cc.MoveBy.create(2, cc.p(100, -100));
        var act6 = cc.CallFunc.create(this, this.log3) ;
        var act7 = cc.MoveBy.create(2, cc.p(-100, 0));
        var act8 = cc.CallFunc.create(this, this.log4) ;

        var actF = cc.Sequence.create(act1, act2, act3, act4, act5, act6, act7, act8);

        //    [spr runAction:actF];
        director.getActionManager().addAction(actF ,spr, false);
    },
    log1:function () {
        cc.log("1st block");
    },
    log2:function () {
        cc.log("2nd block");
    },
    log3:function () {
        cc.log("3rd block");
    },
    log4:function () {
        cc.log("4th block");
    },
    title:function () {
        return "Issue 1305 #2";
    },
    subtitle:function () {
        return "See console. You should only see one message for each block";
    }
});

var Issue1288 = BaseLayer.extend({
    onEnter:function () {
        this._super();
        this.centerSprites(0);

        var spr = cc.Sprite.create("Images/grossini.png");
        spr.setPosition(cc.p(100, 100));
        this.addChild(spr);

        var act1 = cc.MoveBy.create(0.5, cc.p(100, 0));
        var act2 = act1.reverse();
        var act3 = cc.Sequence.create(act1, act2);
        var act4 = cc.Repeat.create(act3, 2);

        spr.runAction(act4);
    },
    title:function () {
        return "Issue 1288";
    },
    subtitle:function () {
        return "Sprite should end at the position where it started.";
    }
});

var Issue1288_2 = BaseLayer.extend({
    onEnter:function () {
        this._super();
        this.centerSprites(0);

        var spr = cc.Sprite.create("Images/grossini.png");
        spr.setPosition(cc.p(100, 100));
        this.addChild(spr);

        var act1 = cc.MoveBy.create(0.5, cc.p(100, 0));
        spr.runAction(cc.Repeat.create(act1, 1));
    },
    title:function () {
        return "Issue 1288 #2";
    },
    subtitle:function () {
        return "Sprite should move 100 pixels, and stay there";
    }
});

var Issue1327 = BaseLayer.extend({
    onEnter:function () {
        this._super();
        this.centerSprites(0);

        var spr = cc.Sprite.create("Images/grossini.png");
        spr.setPosition(cc.p(100, 100));
        this.addChild(spr);

        var act1 = cc.CallFunc.create(this, this.logSprRotation);
        var act2 = cc.RotateBy.create(0.25, 45);
        var act3 = cc.CallFunc.create(this, this.logSprRotation);
        var act4 = cc.RotateBy.create(0.25, 45);
        var act5 = cc.CallFunc.create(this, this.logSprRotation);
        var act6 = cc.RotateBy.create(0.25, 45);
        var act7 = cc.CallFunc.create(this, this.logSprRotation);
        var act8 = cc.RotateBy.create(0.25, 45);
        var act9 = cc.CallFunc.create(this, this.logSprRotation);

        var actF = cc.Sequence.create(act1, act2, act3, act4, act5, act6, act7, act8, act9);
        spr.runAction(actF);
    },
    logSprRotation:function (pSender) {
        cc.log(pSender.getRotation());
    },
    title:function () {
        return "Issue 1327";
    },
    subtitle:function () {
        return "See console: You should see: 0, 45, 90, 135, 180";
    }
});
//
// Order of tests
//

scenes.push( ActionManual );
scenes.push( ActionMove );
scenes.push( ActionScale );
scenes.push( ActionRotate );
scenes.push( ActionSkew );
scenes.push( ActionSkewRotateScale );
scenes.push( ActionJump );
//scenes.push( ActionBezier );
scenes.push( ActionCardinalSpline );
scenes.push( ActionCatmullRom );
scenes.push( ActionBlink );
scenes.push( ActionFade );
scenes.push( ActionTint );
scenes.push( ActionSequence );
scenes.push( ActionSequence2 );
scenes.push( ActionSpawn );
scenes.push( ActionReverse );
scenes.push( ActionDelayTime );
scenes.push( ActionRepeat );
scenes.push( ActionRepeatForever );
scenes.push( ActionRotateToRepeat );
scenes.push( ActionRotateJerk );
scenes.push( ActionCallFunc );
scenes.push( ActionCallFuncND );
scenes.push( ActionReverseSequence );
scenes.push( ActionReverseSequence2 );
scenes.push( ActionAnimate );
scenes.push( ActionTargeted );
scenes.push( PauseResumeActions );
scenes.push( Issue1305 );
scenes.push( Issue1305_2 );
scenes.push( Issue1288 );
scenes.push( Issue1288_2 );
scenes.push( Issue1327 );

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


