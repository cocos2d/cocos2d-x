//
// http://www.cocos2d-iphone.org
// http://www.cocos2d-html5.org
// http://www.cocos2d-x.org
//
// Javascript + cocos2d actions tests
//

require("js/helper.js");

director = cc.Director.getInstance();
_winSize = director.getWinSize();
winSize = {width:_winSize[0], height:_winSize[1]};
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
	_winSize = director.getWinSize();
	winSize = {width:_winSize[0], height:_winSize[1]};
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

var MyMenuItemFont = cc.MenuItemFont.extend({

    ctor:function () {
        var parent = new cc.MenuItemFont();
        __associateObjWithNative(this, parent);
        this.init( "hello", this, this.callback );
        },

    callback:function(sender) {
        cc.log("Button clicked");
    },
});

var BaseLayer = cc.LayerGradient.extend({

    ctor:function () {
                                
        var parent = new cc.LayerGradient();
        __associateObjWithNative(this, parent);
        this.init(cc.c4b(0, 0, 0, 255), cc.c4b(0, 128, 255, 255));


        var item = new MyMenuItemFont();
        var menu = cc.Menu.create( item );
        this.addChild( menu );
        menu.setPosition( centerPos );
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
//       previousScene();
        cc.log("3");
        __jsc__.dumpRoot();
        __jsc__.garbageCollect();
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
//        var item4 = cc.MenuItemFont.create("back", this, function() { require("js/main.js"); } );
//        item4.setFontSize( 22 );

//        var menu = cc.Menu.create(item1, item2, item3, item4 );
        var menu = cc.Menu.create(item1, item2, item3 );

        menu.setPosition( cc.p(0,0) );
        item1.setPosition( cc.p(winSize.width / 2 - 100, 30));
        item2.setPosition( cc.p(winSize.width / 2, 30));
        item3.setPosition( cc.p(winSize.width / 2 + 100, 30));
//        item4.setPosition( cc.p(winSize.width - 60, winSize.height - 30 ) );

        this.addChild(menu, 1);

        cc.log("2");
        __jsc__.dumpRoot();
    }
});

//------------------------------------------------------------------
//
// Playground 
//
//------------------------------------------------------------------
var Playground = BaseLayer.extend({
    onEnter:function () {
        this._super();

        var platform = __getPlatform();
         if( platform.substring(0,6) == 'mobile' ) {
            var accel = cc.Accelerometer.getInstance();
            accel.setCallback( this, this.onAccelerometer );

            // 2 times per second
            accel.setUpdateInterval( 1/2 );
        }
    },

    onAccelerometer:function(x,y,z,timestamp) {
        cc.log('Accel: '+ x + ' ' + y + ' ' + z );
    },
    
    title:function () {
        return "Testing Accelerometer";
    },

    subtitle:function () {
        return "See console on device";
    },
    code:function () {
        return "";
    }
});

//
// Order of tests
//

scenes.push( Playground );

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


