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

var s_pathSister1 = "Images/grossinis_sister1.png";
var s_pathSister2 = "Images/grossinis_sister2.png";
var s_pathBlock = "Images/blocks.png";
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
        return "Effects Test";
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
        this.addChild(label, 10);
        label.setPosition( cc.p(winSize.width / 2, winSize.height - 40));

        var strSubtitle = this.subtitle();
        if (strSubtitle != "") {
            var l = cc.LabelTTF.create(strSubtitle, "Thonburi", 16);
            this.addChild(l, 10);
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

        this.addChild(menu, 10);


        // Specific to Effects

        var node = cc.Node.create();
        node.runAction( this.getEffect(3) );
        this.addChild( node );

        var bg = cc.Sprite.create("Images/background3.png");
        bg.setPosition( cc._p( winSize.width/2, winSize.height/2) );
        node.addChild( bg );

        var sister1 = cc.Sprite.create("Images/grossinis_sister1.png");
        sister1.setPosition( cc._p( winSize.width/3, winSize.height/2 ) );
        node.addChild( sister1, 1 );

        var sister2 = cc.Sprite.create("Images/grossinis_sister2.png");
        sister2.setPosition( cc._p( winSize.width*2/3, winSize.height/2 ) );
        node.addChild( sister2, 1 );

		var sc = cc.ScaleBy.create(2, 5);
        var sc_back = sc.reverse();
        var seq = cc.Sequence.create( sc, sc_back );
        var repeat = cc.RepeatForever.create( seq );

        sister1.runAction( repeat );
        sister2.runAction( repeat.copy() );
    },

    getEffect:function(duration) {
        // override me
        return cc.MoveBy.create(2, cc._p(10,10) );
    },
});

//------------------------------------------------------------------
//
// Tests 
//
//------------------------------------------------------------------
var Shaky3DTest = BaseLayer.extend({
    subtitle:function () {
        return "Shaky 3D";
    },
    code:function () {
        return "a = cc.Shaky3D.create(range, shakeZ, gridSize, duration )";
    },
    getEffect:function(duration) {
        return cc.Shaky3D.create(5, false, cc.g(15,10), duration );
    },
});

var Waves3DTest = BaseLayer.extend({
    subtitle:function () {
        return "Waves 3D";
    },
    code:function () {
        return "a = cc.Waves3D.create(range, shakeZ, gridSize, duration )";
    },
    getEffect:function(duration) {
        return cc.Waves3D.create(5, 40, cc.g(15,10), duration );
    },
});

var FlipXTest = BaseLayer.extend({
    subtitle:function () {
        return "FlipX3D";
    },
    code:function () {
        return "a = cc.FlipX3D.create(duration )";
    },
    getEffect:function(duration) {
        var a = cc.FlipX3D.create(duration );
        var delay = cc.DelayTime.create(2);
        var r = a.reverse();
        return cc.Sequence.create( a, delay, r );
    },
});

var FlipYTest = BaseLayer.extend({
    subtitle:function () {
        return "FlipY3D";
    },
    code:function () {
        return "a = cc.FlipY3D.create(duration )";
    },
    getEffect:function(duration) {
        var a = cc.FlipY3D.create(duration );
        var delay = cc.DelayTime.create(2);
        var r = a.reverse();
        return cc.Sequence.create( a, delay, r );
    },
});

//
// Order of tests
//
scenes.push( Shaky3DTest );
scenes.push( Waves3DTest );
scenes.push( FlipXTest );
scenes.push( FlipYTest );

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


