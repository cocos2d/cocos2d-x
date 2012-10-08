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

var TAG_ACTION1_EASE_ACTIONS = 1001;

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
//    __jsc__.garbageCollect();
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

    positionForTwo:function () {
        this._grossini.setPosition(cc.p(60, winSize.height*2/3));
        this._tamara.setPosition(cc.p(60, winSize.height*1/3));
        this._kathia.setVisible(false);
    },

    onEnter:function () {
        // DO NOT CALL this._super()
//        this._super();

        // add title and subtitle
        var label = cc.LabelTTF.create(this.title(), "Arial", 28);
        this.addChild(label, 1);
        label.setPosition( cc.p(winSize.width / 2, winSize.height - 50));

        var strSubtitle = this.subtitle();
        if (strSubtitle != "") {
            var l = cc.LabelTTF.create(strSubtitle, "Thonburi", 16);
            this.addChild(l, 1);
            l.setPosition( cc.p(winSize.width / 2, winSize.height - 80));
        }

        var strCode = this.code();
        if( strCode !="" ) {
            var label = cc.LabelTTF.create(strCode, 'CourierNewPSMT', 16);
            label.setPosition( cc.p( winSize.width/2, winSize.height-100) );
            this.addChild( label,10 );

            var labelbg = cc.LabelTTF.create(strCode, 'CourierNewPSMT', 16);
            labelbg.setColor( cc.c3b(10,10,255) );
            labelbg.setPosition( cc.p( winSize.width/2 +1, winSize.height-100 -1) );
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
        this._grossini.setPosition(cc.p(60, winSize.height*3/4));
        this._kathia.setPosition(cc.p(60, winSize.height*2/4));
        this._tamara.setPosition(cc.p(60, winSize.height*1/4));
    }
});


//------------------------------------------------------------------
//
// SpriteEase
//
//------------------------------------------------------------------
var SpriteEase = BaseLayer.extend({

    elapsedTime: 0,

    onEnter:function () {
        this._super();

        var move = cc.MoveBy.create(3, cc.p(winSize.width-80, 0));
        var move_back = move.reverse();

        var move_ease_in = cc.EaseIn.create(move.copy(), 3.0);
        var move_ease_in_back = move_ease_in.reverse();

        var move_ease_out = cc.EaseOut.create(move.copy(), 3.0);
        var move_ease_out_back = move_ease_out.reverse();


        var seq1 = cc.Sequence.create(move, move_back );
        var seq2 = cc.Sequence.create(move_ease_in, move_ease_in_back );
        var seq3 = cc.Sequence.create(move_ease_out, move_ease_out_back );


        var a2 = this._grossini.runAction(cc.RepeatForever.create(seq1));
        a2.setTag(1);

        var a1 = this._tamara.runAction(cc.RepeatForever.create(seq2));
        a1.setTag(1);

        var a = this._kathia.runAction(cc.RepeatForever.create(seq3));
        a.setTag(1);

        this.scheduleUpdate();
    },
    title:function () {
        return "EaseIn - EaseOut - Stop";
    },

    code:function () {
        return "var actionIn = cc.EaseIn.create( action, rate );\n" + 
                "var actionOut = cc.EaseOut.create( action, rate );";
    },

    testStopAction:function (dt) {
        elapsedTime += dt;
        
        if( dt > 6 ) {
            this.unscheduleUpdate();
            this._tamara.stopActionByTag(1);
            this._kathia.stopActionByTag(1);
            this._grossini.stopActionByTag(1);
        }
    }
});

//------------------------------------------------------------------
//
// SpriteEaseInOut
//
//------------------------------------------------------------------
var SpriteEaseInOut = BaseLayer.extend({

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


        var seq1 = cc.Sequence.create(move_ease_inout1, move_ease_inout_back1 );
        var seq2 = cc.Sequence.create(move_ease_inout2, move_ease_inout_back2 );
        var seq3 = cc.Sequence.create(move_ease_inout3, move_ease_inout_back3 );

        this._tamara.runAction(cc.RepeatForever.create(seq1));
        this._kathia.runAction(cc.RepeatForever.create(seq2));
        this._grossini.runAction(cc.RepeatForever.create(seq3));
    },
    title:function () {
        return "EaseInOut and rates";
    },

    code:function () {
        return "var actionInOut = cc.EaseInOut.create( action, rate );";
    },
});

//------------------------------------------------------------------
//
// SpriteEaseExponential
//
//------------------------------------------------------------------
var SpriteEaseExponential = BaseLayer.extend({

    onEnter:function () {
        this._super();

        var move = cc.MoveBy.create(3, cc.p(winSize.width-80, 0));
        var move_back = move.reverse();

        var move_ease_in = cc.EaseExponentialIn.create(move.copy());
        var move_ease_in_back = move_ease_in.reverse();

        var move_ease_out = cc.EaseExponentialOut.create(move.copy());
        var move_ease_out_back = move_ease_out.reverse();


        var seq1 = cc.Sequence.create(move, move_back );
        var seq2 = cc.Sequence.create(move_ease_in, move_ease_in_back );
        var seq3 = cc.Sequence.create(move_ease_out, move_ease_out_back );


        this._grossini.runAction(cc.RepeatForever.create(seq1));
        this._tamara.runAction(cc.RepeatForever.create(seq2));
        this._kathia.runAction(cc.RepeatForever.create(seq3));
    },
    title:function () {
        return "ExpIn - ExpOut actions";
    },

    code:function () {
        return "var actionIn = cc.EaseExponentialIn.create( action );\n" + 
                "var actionOut = cc.EaseExponentialOut.create( action );";
    },
});

//------------------------------------------------------------------
//
// SpriteEaseExponentialInOut
//
//------------------------------------------------------------------
var SpriteEaseExponentialInOut = BaseLayer.extend({

    onEnter:function () {
        this._super();

        var move = cc.MoveBy.create(3, cc.p(winSize.width-80, 0));
        var move_back = move.reverse();

        var move_ease = cc.EaseExponentialInOut.create(move.copy());
        var move_ease_back = move_ease.reverse();	//-. reverse()

        var seq1 = cc.Sequence.create(move, move_back );
        var seq2 = cc.Sequence.create(move_ease, move_ease_back );

        this.positionForTwo();

        this._grossini.runAction(cc.RepeatForever.create(seq1));
        this._tamara.runAction(cc.RepeatForever.create(seq2));
    },
    title:function () {
        return "EaseExponentialInOut action";
    },
    code:function () {
        return "var actionIn = cc.EaseExponentialInOut.create( action );";
    },
});

//------------------------------------------------------------------
//
// SpriteEaseSine
//
//------------------------------------------------------------------
var SpriteEaseSine = BaseLayer.extend({
    onEnter:function () {
        this._super();

        var move = cc.MoveBy.create(3, cc.p(winSize.width-80, 0));
        var move_back = move.reverse();

        var move_ease_in = cc.EaseSineIn.create(move.copy());
        var move_ease_in_back = move_ease_in.reverse();

        var move_ease_out = cc.EaseSineOut.create(move.copy());
        var move_ease_out_back = move_ease_out.reverse();


        var seq1 = cc.Sequence.create(move, move_back );
        var seq2 = cc.Sequence.create(move_ease_in, move_ease_in_back );
        var seq3 = cc.Sequence.create(move_ease_out, move_ease_out_back );


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
var SpriteEaseSineInOut = BaseLayer.extend({
    onEnter:function () {
        this._super();

        var move = cc.MoveBy.create(3, cc.p(winSize.width-80, 0));
        var move_back = move.reverse();

        var move_ease = cc.EaseSineInOut.create(move.copy());
        var move_ease_back = move_ease.reverse();

        var seq1 = cc.Sequence.create(move, move_back );
        var seq2 = cc.Sequence.create(move_ease, move_ease_back );

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
var SpriteEaseElastic = BaseLayer.extend({
    onEnter:function () {
        this._super();

        var move = cc.MoveBy.create(3, cc.p(winSize.width-80, 0));
        var move_back = move.reverse();

        var move_ease_in = cc.EaseElasticIn.create(move.copy());
        var move_ease_in_back = move_ease_in.reverse();

        var move_ease_out = cc.EaseElasticOut.create(move.copy());
        var move_ease_out_back = move_ease_out.reverse();

        var seq1 = cc.Sequence.create(move, move_back );
        var seq2 = cc.Sequence.create(move_ease_in, move_ease_in_back );
        var seq3 = cc.Sequence.create(move_ease_out, move_ease_out_back );

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
var SpriteEaseElasticInOut = BaseLayer.extend({
    onEnter:function () {
        this._super();

        var move = cc.MoveBy.create(3, cc.p(winSize.width-80, 0));

        var move_ease_inout1 = cc.EaseElasticInOut.create(move.copy(), 0.3);
        var move_ease_inout_back1 = move_ease_inout1.reverse();

        var move_ease_inout2 = cc.EaseElasticInOut.create(move.copy(), 0.45);
        var move_ease_inout_back2 = move_ease_inout2.reverse();

        var move_ease_inout3 = cc.EaseElasticInOut.create(move.copy(), 0.6);
        var move_ease_inout_back3 = move_ease_inout3.reverse();


        var seq1 = cc.Sequence.create(move_ease_inout1, move_ease_inout_back1 );
        var seq2 = cc.Sequence.create(move_ease_inout2, move_ease_inout_back2 );
        var seq3 = cc.Sequence.create(move_ease_inout3, move_ease_inout_back3 );

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
var SpriteEaseBounce = BaseLayer.extend({
    onEnter:function () {
        this._super();

        var move = cc.MoveBy.create(3, cc.p(winSize.width-80, 0));
        var move_back = move.reverse();

        var move_ease_in = cc.EaseBounceIn.create(move.copy());
        var move_ease_in_back = move_ease_in.reverse();

        var move_ease_out = cc.EaseBounceOut.create(move.copy());
        var move_ease_out_back = move_ease_out.reverse();

        var seq1 = cc.Sequence.create(move, move_back );
        var seq2 = cc.Sequence.create(move_ease_in, move_ease_in_back );
        var seq3 = cc.Sequence.create(move_ease_out, move_ease_out_back );

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
var SpriteEaseBounceInOut = BaseLayer.extend({
    onEnter:function () {
        this._super();

        var move = cc.MoveBy.create(3, cc.p(winSize.width-80, 0));
        var move_back = move.reverse();

        var move_ease = cc.EaseBounceInOut.create(move.copy());
        var move_ease_back = move_ease.reverse();

        var seq1 = cc.Sequence.create(move, move_back );
        var seq2 = cc.Sequence.create(move_ease, move_ease_back );

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
var SpriteEaseBack = BaseLayer.extend({
    onEnter:function () {
        this._super();

        var move = cc.MoveBy.create(3, cc.p(winSize.width-80, 0));
        var move_back = move.reverse();

        var move_ease_in = cc.EaseBackIn.create(move.copy());
        var move_ease_in_back = move_ease_in.reverse();

        var move_ease_out = cc.EaseBackOut.create(move.copy());
        var move_ease_out_back = move_ease_out.reverse();

        var seq1 = cc.Sequence.create(move, move_back );
        var seq2 = cc.Sequence.create(move_ease_in, move_ease_in_back );
        var seq3 = cc.Sequence.create(move_ease_out, move_ease_out_back );

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
var SpriteEaseBackInOut = BaseLayer.extend({
    onEnter:function () {
        this._super();

        var move = cc.MoveBy.create(3, cc.p(winSize.width-80, 0));
        var move_back = move.reverse();

        var move_ease = cc.EaseBackInOut.create(move.copy());
        var move_ease_back = move_ease.reverse();

        var seq1 = cc.Sequence.create(move, move_back );
        var seq2 = cc.Sequence.create(move_ease, move_ease_back );

        this.positionForTwo();

        this._grossini.runAction(cc.RepeatForever.create(seq1));
        this._tamara.runAction(cc.RepeatForever.create(seq2));
    },
    title:function () {
        return "EaseBackInOut action";
    }
});

var SpeedTest = BaseLayer.extend({
    onEnter:function () {
        this._super();

        // rotate and jump
        var jump1 = cc.JumpBy.create(4, cc.p(-400, 0), 100, 4);
        var jump2 = jump1.reverse();
        var rot1 = cc.RotateBy.create(4, 360 * 2);
        var rot2 = rot1.reverse();

        var seq3_1 = cc.Sequence.create(jump2, jump1 );
        var seq3_2 = cc.Sequence.create(rot1, rot2 );
        var spawn = cc.Spawn.create(seq3_1, seq3_2 );
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

        action1.setSpeed(cc.RANDOM_0_1() * 2);
        action2.setSpeed(cc.RANDOM_0_1() * 2);
        action3.setSpeed(cc.RANDOM_0_1() * 2);
    }
});

//
// Order of tests
//
scenes.push( SpriteEase );
scenes.push( SpriteEaseInOut );
scenes.push( SpriteEaseExponential );
scenes.push( SpriteEaseExponentialInOut );
scenes.push( SpriteEaseSine );
scenes.push( SpriteEaseSineInOut );
scenes.push( SpriteEaseElastic );
scenes.push( SpriteEaseElasticInOut );
scenes.push( SpriteEaseBounce );
scenes.push( SpriteEaseBounceInOut );
scenes.push( SpriteEaseBack );
scenes.push( SpriteEaseBackInOut );
scenes.push( SpeedTest );

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

