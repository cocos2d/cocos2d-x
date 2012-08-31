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
        return "Render Texture";
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

        this.addChild(menu, 10);
    }
});

//------------------------------------------------------------------
//
// Tests 
//
//------------------------------------------------------------------
var RenderTextureSave = BaseLayer.extend({
    _brush : null,
    _target : null,
    _lastLocation : null,
    _counter :0,

    onEnter:function () {
        this._super();

        var platform = __getPlatform();
        if( platform.substring(0,7) == 'desktop' )
            this.setMouseEnabled( true );
        else if( platform.substring(0,6) == 'mobile' )
            this.setTouchEnabled( true );

        this._brush = cc.Sprite.create("fire.png");
        this._brush.retain();

        this._brush.setColor( cc.RED );
        this._brush.setOpacity( 20 );


        var save = cc.MenuItemFont.create("Save", this, this.saveCB );
        var clear = cc.MenuItemFont.create("Clear", this, this.clearCB );
        var menu = cc.Menu.create( save, clear );
        menu.alignItemsVertically();
        menu.setPosition( cc.p( winSize.width-70, winSize.height-80 ) );
        this.addChild( menu, 10 );

		// create a render texture
		var target = cc.RenderTexture.create( winSize.width, winSize.height );
		target.setPosition( cc.p (winSize.width/2, winSize.height/2) );
        this.addChild( target, 1 );

        this._target = target;

        this._lastLocation = cc.p( winSize.width/2, winSize.height/2);

    },

    onExit:function() {
        this._brush.release();
    },

    saveCB:function(sender) {
        var namePNG = "image-" + this._counter + ".png";
        var nameJPG = "image-" + this._counter + ".jpg";

        this._target.saveToFile( nameJPG, cc.IMAGE_FORMAT_JPEG );
        this._target.saveToFile( namePNG, cc.IMAGE_FORMAT_PNG );

        cc.log("images saved!");
        this._counter++;
    },

    clearCB:function(sender) {
        this._target.clear( Math.random(), Math.random(), Math.random(), 1 );
    },

    drawInLocation: function( location ) {
        var distance = cc.pDistance( location, this._lastLocation );
        if( distance > 1 ) {
            this._target.begin();
            for( var i=0; i < distance; i++ ) {
                var diffX = this._lastLocation.x - location.x;
                var diffY = this._lastLocation.y - location.y;

                var delta = i / distance;

                this._brush.setPosition( cc._p( location.x + diffX * delta, location.y + diffY * delta ) );
                this._brush.setRotation( Math.random() * 360 );
                this._brush.setScale( Math.random() * 2 );
                this._brush.setColor( cc._c3b( Math.random()*255, 255, 255) );
                this._brush.visit();
            }
            this._target.end();
        }
        this._lastLocation = location;
    },

    onTouchesBegan:function (touches, event) {
        this._lastLocation = touches[0].getLocation();
        return true;
    },

    onTouchesMoved:function (touches, event) {
        this.drawInLocation( touches[0].getLocation() );
        return true;
    },

    onMouseDown : function( event ) {
        this._lastLocation = event.getLocation();
        return true;
    },

    onMouseDragged : function( event ) {
        this.drawInLocation( event.getLocation() );
        return true;
    },

    subtitle:function () {
        return "Testing 'save'";
    }
});

//
// Order of tests
//

scenes.push( RenderTextureSave );

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


