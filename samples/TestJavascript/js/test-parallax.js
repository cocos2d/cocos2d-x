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
//    __jsc__.garbageCollect();
}

var TAG_NODE = 100;


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


        // back menu
    }
});

//
// Parallax 1
//
ParallaxTest1 = BaseLayer.extend({

    _root:null,
    _target:null,
    _streak:null,


    ctor:function () {
        this._super();

        // Top Layer, a simple image
        var cocosImage = cc.Sprite.create("powered.png");
        // scale the image (optional)
        cocosImage.setScale(1.5);
        // change the transform anchor point to 0,0 (optional)
        cocosImage.setAnchorPoint(cc.p(0, 0));

        // Middle layer: a Tile map atlas
//        var tilemap = cc.TMXTiledMap.create("TileMaps/orthogonal-test2.tmx");
        var tilemap = cc.TileMapAtlas.create("TileMaps/tiles.png", "TileMaps/levelmap.tga", 16, 16);

        // change the transform anchor to 0,0 (optional)
        tilemap.setAnchorPoint(cc.p(0, 0));

        // Anti Aliased images
        tilemap.getTexture().setAntiAliasTexParameters();

        // background layer: another image
        var background = cc.Sprite.create("background.png");
        // scale the image (optional)
        background.setScale(1.5);
        // change the transform anchor point (optional)
        background.setAnchorPoint(cc.p(0, 0));


        // create a void node, a parent node
        var voidNode = cc.ParallaxNode.create();

        // NOW add the 3 layers to the 'void' node

        // background image is moved at a ratio of 0.4x, 0.5y
        voidNode.addChild(background, -1, cc.p(0.4, 0.5), cc.p(0,0));

        // tiles are moved at a ratio of 2.2x, 1.0y
        voidNode.addChild(tilemap, 1, cc.p(2.2, 1.0), cc.p(0, -200));

        // top image is moved at a ratio of 3.0x, 2.5y
        voidNode.addChild(cocosImage, 2, cc.p(3.0, 2.5), cc.p(200, 800));


        // now create some actions that will move the 'void' node
        // and the children of the 'void' node will move at different
        // speed, thus, simulation the 3D environment
        var goUp = cc.MoveBy.create(4, cc.p(0, -500));
        var goDown = goUp.reverse();
        var go = cc.MoveBy.create(8, cc.p(-1000, 0));
        var goBack = go.reverse();
        var seq = cc.Sequence.create(goUp, go, goDown, goBack );
        voidNode.runAction((cc.RepeatForever.create(seq) ));

        this.addChild(voidNode);
    },

    title:function () {
        return "Parallax: parent and 3 children";
    }
});


//
// Parallax 2
//
ParallaxTest2 = BaseLayer.extend({

    _root:null,
    _target:null,
    _streak:null,


    ctor:function () {
        this._super();

        var platform = __getPlatform();
        if( platform.substring(0,7) == 'desktop' )
            this.setMouseEnabled( true );
        else if( platform.substring(0,6) == 'mobile' )
            this.setTouchEnabled( true );

        // Top Layer, a simple image
        var cocosImage = cc.Sprite.create("powered.png");
        // scale the image (optional)
        cocosImage.setScale(1.5);
        // change the transform anchor point to 0,0 (optional)
        cocosImage.setAnchorPoint(cc.p(0, 0));


        // Middle layer: a Tile map atlas
        var tilemap = cc.TileMapAtlas.create("TileMaps/tiles.png", "TileMaps/levelmap.tga", 16, 16);

        // change the transform anchor to 0,0 (optional)
        tilemap.setAnchorPoint( cc.p(0, 0) );

        // Anti Aliased images
        tilemap.getTexture().setAntiAliasTexParameters();


        // background layer: another image
        var background = cc.Sprite.create("background.png");
        // scale the image (optional)
        background.setScale(1.5);
        // change the transform anchor point (optional)
        background.setAnchorPoint(cc.p(0, 0));

        // create a void node, a parent node
        var voidNode = cc.ParallaxNode.create();

        // NOW add the 3 layers to the 'void' node

        // background image is moved at a ratio of 0.4x, 0.5y
        voidNode.addChild(background, -1, cc.p(0.4, 0.5), cc.p(0,0));

        // tiles are moved at a ratio of 2.2x, 1.0y
        voidNode.addChild(tilemap, 1, cc.p(2.2, 1.0), cc.p(0, -200));

        // top image is moved at a ratio of 3.0x, 2.5y
        voidNode.addChild(cocosImage, 2, cc.p(3.0, 2.5), cc.p(200, 800));
        this.addChild(voidNode, 0, TAG_NODE);

    },

    onTouchesMoved:function (touches, event) {
        var node = this.getChildByTag(TAG_NODE);
        var currentPos = node.getPosition();
        node.setPosition( cc.pAdd( currentPos, touches[0].getDelta() ) );
    },

    onMouseDragged : function( event ) {
        var node = this.getChildByTag(TAG_NODE);
        var currentPos = node.getPosition();
        node.setPosition( cc.pAdd( currentPos, event.getDelta() ) );
    },

    title:function () {
        return "Parallax: drag screen";
    }
});

//
// Order of tests
//
scenes.push( ParallaxTest1 );
scenes.push( ParallaxTest2 );

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

