//
// http://www.cocos2d-iphone.org
// http://www.cocos2d-html5.org
// http://www.cocos2d-x.org
//
// Javascript + cocos2d actions tests
//

require("js/helpers.js");

director = cc.Director.sharedDirector();
_winSize = director.getWinSize();
winSize = {width:_winSize[0], height:_winSize[1]};
centerPos = cc.p( winSize.width/2, winSize.height/2 );

scenes = []
currentScene = 0;

cc.log("main2.js:1");

nextScene = function () {
	currentScene = currentScene + 1;
	if( currentScene >= scenes.length )
		currentScene = 0;

	withTransition = true;
	loadScene(currentScene);
};

previousScene = function () {
	currentScene = currentScene -1;
	if( currentScene < 0 )
		currentScene = scenes.length -1;

	withTransition = true;
	loadScene(currentScene);
};

restartScene = function () {
	loadScene( currentScene );
};

loadScene = function (sceneIdx)
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
//    __jsc__.garbageCollect();
}


cc.log("main2.js:2");

//
// Base Layer
//

BaseLayer = cc.LayerGradient.extend({

    ctor:function () {
                                
        var parent = new cc.LayerGradient();
        __associateObjWithNative(this, parent);
        this.init(cc.c4(0, 0, 0, 255), cc.c4(0, 128, 255, 255));
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
        // DO NOT CALL this._super()
//        this._super();
        cc.log("baselayer.onenter");
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
            labelbg.setColor( cc.c3(10,10,255) );
            labelbg.setPosition( cc.p( winSize.width/2 +1, winSize.height-120 -1) );
            this.addChild( labelbg,9);
        }
    }
});


cc.log("main2.js:3");

//------------------------------------------------------------------
//
// MainTest
//
//------------------------------------------------------------------
MainTest = BaseLayer.extend({

    _menu : null,

    onEnter:function () {
        this._super();
  
        cc.MenuItemFont.setFontSize(24);
        var item1 = cc.MenuItemFont.create("Actions: Basic Tests", this, function() { require("js/test-actions.js"); } );
        var item2 = cc.MenuItemFont.create("Actions: Ease Tests", this, function() { require("js/test-easeactions.js"); } );
        var item3 = cc.MenuItemFont.create("Actions: Progress Tests", this, function() { require("js/test-actionsprogress.js"); } );
        var item4 = cc.MenuItemFont.create("Chipmunk Tests", this, function() { require("js/test-chipmunk.js"); } );
        var item5 = cc.MenuItemFont.create("Effects Tests", this, function() { require("js/test-effects.js"); } );
        var item6 = cc.MenuItemFont.create("Label Tests", this, function() { require("js/test-label.js"); } );
        var item7 = cc.MenuItemFont.create("Menu Tests", this, function() { require("js/test-menu.js"); } );
        var item8 = cc.MenuItemFont.create("Parallax Tests", this, function() { require("js/test-parallax.js"); } );
        var item9 = cc.MenuItemFont.create("Particle Tests", this, function() { require("js/test-particles.js"); } );
        var item10 = cc.MenuItemFont.create("RenderTexture Tests", this, function() { require("js/test-rendertexture.js"); } );
        var item11 = cc.MenuItemFont.create("Sprite Tests", this, function() { require("js/test-sprite.js"); } );
        var item12 = cc.MenuItemFont.create("Tilemap Tests", this, function() { require("js/test-tilemap.js"); } );
        var item13 = cc.MenuItemFont.create("CocosDenshion Tests", this, function() { require("js/test-cocosdenshion.js"); } );
        var item14 = cc.MenuItemFont.create("cocos2d presentation", this, function() { require("js/test-cocos2djs.js"); } );


        this._menu = cc.Menu.create(item1, item2, item3, item4, item5, item6, item7, item8, item9, item10, item11, item12, item13, item14);
        this._menu.alignItemsVertically();

        this._menu.setPosition( cc.p( winSize.width/2, winSize.height/2) );

        this.addChild( this._menu );

        var platform = __getPlatform();
        if( platform.substring(0,7) == 'desktop' )
            this.setMouseEnabled( true );
        else if( platform.substring(0,6) == 'mobile' )
            this.setTouchEnabled( true );
    },

    onTouchesMoved:function (touches, event) {
        var delta = touches[0].getDelta();
        var current = this._menu.getPosition();
        this._menu.setPosition( cc.p( current[0], current[1] + delta[1] ) );
        return true;
    },

    onMouseDragged : function( event ) {
        var delta = event.getDelta();
        var current = this._menu.getPosition();
        this._menu.setPosition( cc.p( current[0], current[1] + delta[1] ) );
        return true;
    },

    title:function () {
        return "Javascript tests";
    },

});

cc.log("main2.js:4");

//
// Order of tests
//

scenes.push( MainTest);

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
        director.replaceScene( cc.TransitionSplitCols.create(1, scene, cc.c3(0, 0, 0) ) );

    director.setDisplayStats(true);
}

cc.log("main2.js:5");
run();
cc.log("main2.js:6");
