//
// http://www.cocos2d-iphone.org
//
// Javascript + chipmunk tests
//

require("js/helper.js");

director = cc.Director.getInstance();
winSize = director.getWinSize();
centerPos = cc.p( winSize.width/2, winSize.height/2 );

var scenes = []
var currentScene = 0;

var nextSpriteTestAction = function () {
	currentScene = currentScene + 1;
	if( currentScene >= scenes.length )
		currentScene = 0;

	loadScene(currentScene);
};
var backSpriteTestAction = function () {
	currentScene = currentScene -1;
	if( currentScene < 0 )
		currentScene = scenes.length -1;

	loadScene(currentScene);
};
var restartSpriteTestAction = function () {
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

//------------------------------------------------------------------
//
// BaseLayer
//
//------------------------------------------------------------------
var BaseLayer = function() {

	//
	// VERY IMPORTANT
	//
	// Only subclasses of a native classes MUST call __associateObjectWithNative
	// Failure to do so, it will crash.
	//
	var parent = goog.base(this);
	__associateObjWithNative( this, parent );
	this.init();

	this.title = function () {
	    return "No title";
	}

	this.subtitle = function () {
	    return "No Subtitle";
	}

}
goog.inherits(BaseLayer, cc.Layer );

//
// Instance 'base' methods
// XXX: Should be defined after "goog.inherits"
//
BaseLayer.prototype.onEnter = function() {
	var label = cc.LabelTTF.create(this.title(), "Arial", 28);
	this.addChild(label, 1);
	label.setPosition( cc.p(winSize.width / 2, winSize.height - 50));

	var strSubtitle = this.subtitle();
	if (strSubtitle != "") {
	    var l = cc.LabelTTF.create(strSubtitle, "Thonburi", 16);
	    this.addChild(l, 1);
	    l.setPosition( cc.p(winSize.width / 2, winSize.height - 80));
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
}

BaseLayer.prototype.restartCallback = function (sender) {
    cc.log("restart called");
    restartSpriteTestAction();
}

BaseLayer.prototype.nextCallback = function (sender) {
    cc.log("next called");
    nextSpriteTestAction();
}

BaseLayer.prototype.backCallback = function (sender) {
    cc.log("back called");
    backSpriteTestAction();
}


//------------------------------------------------------------------
//
// Chipmunk + Sprite
//
//------------------------------------------------------------------
var ChipmunkSpriteTest = function() {

	goog.base(this);

	this.addSprite = function( pos ) {
		var sprite =  this.createPhysicsSprite( pos );
		this.addChild( sprite );
	}

	this.title = function() {
		return 'Chipmunk Sprite Test';
	}

	this.subtitle = function() {
		return 'Chipmunk + cocos2d sprites tests. Tap screen.';
	}

	this.initPhysics();
}
goog.inherits( ChipmunkSpriteTest, BaseLayer );

//
// Instance 'base' methods
// XXX: Should be defined after "goog.inherits"
//

// init physics
ChipmunkSpriteTest.prototype.initPhysics = function() {
	this.space =  cp.spaceNew();
	var staticBody = cp.spaceGetStaticBody( this.space );

	// Walls
	var walls = [cp.segmentShapeNew( staticBody, cp.v(0,0), cp.v(winSize.width,0), 0 ),				// bottom
			cp.segmentShapeNew( staticBody, cp.v(0,winSize.height), cp.v(winSize.width,winSize.height), 0),	// top
			cp.segmentShapeNew( staticBody, cp.v(0,0), cp.v(0,winSize.height), 0),				// left
			cp.segmentShapeNew( staticBody, cp.v(winSize.width,0), cp.v(winSize.width,winSize.height), 0)	// right
			];
	for( var i=0; i < walls.length; i++ ) {
		var wall = walls[i];
		cp.shapeSetElasticity(wall, 1);
		cp.shapeSetFriction(wall, 1);
		cp.spaceAddStaticShape( this.space, wall );
	}

	// Gravity
	cp.spaceSetGravity( this.space, cp.v(0, -100) );
}

ChipmunkSpriteTest.prototype.createPhysicsSprite = function( pos ) {
	var body = cp.bodyNew(1, cp.momentForBox(1, 48, 108) );
	cp.bodySetPos( body, pos );
	cp.spaceAddBody( this.space, body );
	var shape = cp.boxShapeNew( body, 48, 108);
	cp.shapeSetElasticity( shape, 0.5 );
	cp.shapeSetFriction( shape, 0.5 );
	cp.spaceAddShape( this.space, shape );

	var sprite = cc.PhysicsSprite.create("Images/grossini.png");
	sprite.setBody( body );
	return sprite;
}

ChipmunkSpriteTest.prototype.onEnter = function () {

	goog.base(this, 'onEnter');

	this.scheduleUpdate();
	for(var i=0; i<10; i++) {
		this.addSprite( cp.v(winSize.width/2, winSize.height/2) );
	}

	var platform = __getPlatform();
    if( platform.substring(0,7) == 'desktop' ) {
        this.setMouseEnabled( true );
    } else if( platform.substring(0,6) == 'mobile' ) {
        this.setTouchEnabled( true );
    }
}

ChipmunkSpriteTest.prototype.update = function( delta ) {
	cp.spaceStep( this.space, delta );
}

ChipmunkSpriteTest.prototype.onMouseDown = function( event ) {
	this.addSprite( event.getLocation() );
}

ChipmunkSpriteTest.prototype.onTouchesEnded = function( touches, event ) {
	var l = touches.length;
	for( var i=0; i < l; i++) {
		this.addSprite( touches[i].getLocation() );
	}
}

//------------------------------------------------------------------
//
// Chipmunk + Sprite + Batch
//
//------------------------------------------------------------------
var ChipmunkSpriteBatchTest = function() {

	goog.base(this);

	// batch node
	this.batch = cc.SpriteBatchNode.create('Images/grossini.png', 50 );
	this.addChild( this.batch );

	this.addSprite = function( pos ) {
		var sprite =  this.createPhysicsSprite( pos );
		this.batch.addChild( sprite );
	}

	this.title = function() {
		return 'Chipmunk SpriteBatch Test';
	}

	this.subtitle = function() {
		return 'Chipmunk + cocos2d sprite batch tests. Tap screen.';
	}
}
goog.inherits( ChipmunkSpriteBatchTest, ChipmunkSpriteTest );

//------------------------------------------------------------------
//
// Chipmunk Collision Test
//
//------------------------------------------------------------------
var ChipmunkCollisionTest = function() {

	goog.base(this);

	this.messageDisplayed = false;

	this.title = function() {
		return 'Chipmunk Collision Test';
	}

	this.subtitle = function() {
		return 'Testing collision callback';
	}

	// init physics
	this.initPhysics = function() {
		this.space =  cp.spaceNew();
		var staticBody = cp.spaceGetStaticBody( this.space );

		// Walls
		var walls = [cp.segmentShapeNew( staticBody, cp.v(0,0), cp.v(winSize.width,0), 0 ),				// bottom
				cp.segmentShapeNew( staticBody, cp.v(0,winSize.height), cp.v(winSize.width,winSize.height), 0),	// top
				cp.segmentShapeNew( staticBody, cp.v(0,0), cp.v(0,winSize.height), 0),				// left
				cp.segmentShapeNew( staticBody, cp.v(winSize.width,0), cp.v(winSize.width,winSize.height), 0)	// right
				];
		for( var i=0; i < walls.length; i++ ) {
			var wall = walls[i];
			cp.shapeSetElasticity(wall, 1);
			cp.shapeSetFriction(wall, 1);
			cp.spaceAddStaticShape( this.space, wall );
		}

		// Gravity
		cp.spaceSetGravity( this.space, cp.v(0, -30) );
	}

	this.createPhysicsSprite = function( pos, file, collision_type ) {
		var body = cp.bodyNew(1, cp.momentForBox(1, 48, 108) );
		cp.bodySetPos( body, pos );
		cp.spaceAddBody( this.space, body );
		var shape = cp.boxShapeNew( body, 48, 108);
		cp.shapeSetElasticity( shape, 0.5 );
		cp.shapeSetFriction( shape, 0.5 );
		cp.shapeSetCollisionType( shape, collision_type );
		cp.spaceAddShape( this.space, shape );

		var sprite = cc.PhysicsSprite.create(file);
		sprite.setBody( body );
		return sprite;
	}

	this.onEnter = function () {
		goog.base(this, 'onEnter');

        this.initPhysics();
		this.scheduleUpdate();

		var sprite1 = this.createPhysicsSprite( cc.p(winSize.width/2, winSize.height-20), "Images/grossini.png", 1);
		var sprite2 = this.createPhysicsSprite( cc.p(winSize.width/2, 50), "Images/grossinis_sister1.png", 2);

		this.addChild( sprite1 );
		this.addChild( sprite2 );

		cp.spaceAddCollisionHandler( this.space, 1, 2, this, this.collisionBegin, this.collisionPre, this.collisionPost, this.collisionSeparate );
	}

	this.onExit = function() {
		cp.spaceRemoveCollisionHandler( this.space, 1, 2 );
        cp.spaceFree( this.space );
	}

	this.update = function( delta ) {
		cp.spaceStep( this.space, delta );
	}

	this.collisionBegin = function ( arbiter, space ) {

		if( ! this.messageDisplayed ) {
			var label = cc.LabelBMFont.create("Collision Detected", "Fonts/bitmapFontTest5.fnt");
			this.addChild( label );
			label.setPosition( centerPos );
			this.messageDisplayed = true;
		}
		cc.log('collision begin');
		var bodies = cp.arbiterGetBodies( arbiter );
		var shapes = cp.arbiterGetShapes( arbiter );
		var collTypeA = cp.shapeGetCollisionType( shapes[0] );
		var collTypeB = cp.shapeGetCollisionType( shapes[1] );
		cc.log( 'Collision Type A:' + collTypeA );
		cc.log( 'Collision Type B:' + collTypeB );
		return true
	}

	this.collisionPre = function ( arbiter, space ) {
		cc.log('collision pre');
		return true;
	}

	this.collisionPost = function ( arbiter, space ) {
		cc.log('collision post');
	}

	this.collisionSeparate = function ( arbiter, space ) {
		cc.log('collision separate');
	}

}
goog.inherits( ChipmunkCollisionTest, BaseLayer );

//------------------------------------------------------------------
//
// Chipmunk Collision Memory Leak Test
//
//------------------------------------------------------------------
var ChipmunkCollisionMemoryLeakTest = function() {

	goog.base(this);

	this.title = function() {
		return 'Chipmunk Memory Leak Test';
	}

	this.subtitle = function() {
		return 'Testing possible memory leak on the collision handler. No visual feedback';
	}

	this.collisionBegin = function ( arbiter, space ) {
		return true
	}

	this.collisionPre = function ( arbiter, space ) {
		return true;
	}

	this.collisionPost = function ( arbiter, space ) {
		cc.log('collision post');
	}

	this.collisionSeparate = function ( arbiter, space ) {
		cc.log('collision separate');
	}

    this.onEnter = function() {
        goog.base(this, 'onEnter');
		this.space =  cp.spaceNew();

        for( var i=1 ; i < 100 ; i++ )
            cp.spaceAddCollisionHandler( this.space, i, i+1, this, this.collisionBegin, this.collisionPre, this.collisionPost, this.collisionSeparate );

    }

	this.onExit = function() {

        for( var i=1 ; i < 100 ; i++ )
            cp.spaceRemoveCollisionHandler( this.space, i, i+1 );

        cp.spaceFree( this.space );
	}
}
goog.inherits( ChipmunkCollisionMemoryLeakTest, BaseLayer );
//
// Instance 'base' methods
// XXX: Should be defined after "goog.inherits"
//



//
// Order of tests
//

scenes.push( ChipmunkSpriteTest ); scenes.push( ChipmunkSpriteBatchTest );
scenes.push( ChipmunkCollisionTest );
scenes.push( ChipmunkCollisionMemoryLeakTest );


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
