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
var withTransition = false;

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

	var transitions = [ cc.TransitionSplitCols, cc.TransitionSplitRows,
				cc.TransitionSlideInL, cc.TransitionSlideInR, cc.TransitionSlideInT, cc.TransitionSlideInB,
				cc.TransitionFade, cc.TransitionCrossFade,
				cc.TransitionFlipX, cc.TransitionFlipY,
				cc.TransitionProgressRadialCCW, cc.TransitionProgressRadialCW, cc.TransitionProgressVertical, cc.TransitionProgressHorizontal,
				cc.TransitionShrinkGrow,
				];
	var idx = Math.floor(  Math.random() * transitions.length );
	var transition = transitions[ idx ];

	if( withTransition == true )
		director.replaceScene( transition.create( 0.9, scene ) );
	else
		director.replaceScene( scene );

	withTransition = false;
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
	this.init( cc.c4b(0,0,0,255), cc.c4b(0,128,255,255));

	this.title =  "No title";
	this.subtitle = "No Subtitle";
	this.isMainTitle = false;

}
goog.inherits(BaseLayer, cc.LayerGradient );

//
// Instance 'base' methods
// XXX: Should be defined after "goog.inherits"
//
BaseLayer.prototype.onEnter = function() {

	var fontSize = 36;
	var tl = this.title.length;
	fontSize = (winSize.width / tl) * 1.60;
	if( fontSize/winSize.width > 0.09 ) {
		fontSize = winSize.width * 0.09;
	}

	this.label = cc.LabelTTF.create(this.title, "Gill Sans", fontSize);
	this.addChild(this.label, 100);

	var isMain = this.isMainTitle;

	if( isMain == true )
		this.label.setPosition( centerPos );
	else
		this.label.setPosition( cc.p(winSize.width / 2, winSize.height*11/12) );

	var subStr = this.subtitle;
	if (subStr != "") {
		tl = this.subtitle.length;
		var subfontSize = (winSize.width / tl) * 1.3;
		if( subfontSize > fontSize *0.6 ) {
			subfontSize = fontSize *0.6;
		}

		this.sublabel = cc.LabelTTF.create(subStr, "Thonburi", subfontSize);
		this.addChild(this.sublabel, 90);
		if( isMain )
			this.sublabel.setPosition( cc.p(winSize.width / 2, winSize.height*3/8 ));
		else
			this.sublabel.setPosition( cc.p(winSize.width / 2, winSize.height*5/6 ));
	} else
		this.sublabel = null;

    // Menu
    var item1 = cc.MenuItemImage.create("b1.png", "b2.png", this, this.backCallback);
    var item2 = cc.MenuItemImage.create("r1.png", "r2.png", this, this.restartCallback);
    var item3 = cc.MenuItemImage.create("f1.png", "f2.png", this, this.nextCallback);
    var item4 = cc.MenuItemFont.create("back", this, function() { require("js/main.js"); } );
    item4.setFontSize( 22 );

	 [item1, item2, item3 ].forEach( function(item) {
		item.normalImage().setOpacity(45);
		item.selectedImage().setOpacity(45);
		} );

	var menu = cc.Menu.create( item1, item2, item3, item4 );

	menu.setPosition( cc.p(0,0) );
	item1.setPosition( cc.p(winSize.width / 2 - 100, 30));
	item2.setPosition( cc.p(winSize.width / 2, 30));
	item3.setPosition( cc.p(winSize.width / 2 + 100, 30));
    item4.setPosition( cc.p(winSize.width - 60, winSize.height - 30 ) );

	this.addChild(menu, 80);
}

BaseLayer.prototype.createBulletList = function () {
	var str = "";
	for(var i=0; i<arguments.length; i++)
	{
		if(i != 0)
			str += "\n";
		str += '- ' + arguments[i];
	}

	cc.log( str );

	var fontSize = winSize.height*0.07;
	var bullets = cc.LabelTTF.create( str, "Gill Sans", fontSize );
	bullets.setPosition( centerPos );
	this.addChild( bullets, 80 );
}

BaseLayer.prototype.createImage = function( file ) {
	var sprite = cc.Sprite.create( file );
	sprite.setPosition( centerPos );
	this.addChild( sprite, 70 );

	return sprite;
}


BaseLayer.prototype.restartCallback = function (sender) {
	restartScene();
}

BaseLayer.prototype.nextCallback = function (sender) {
	nextScene();
}

BaseLayer.prototype.backCallback = function (sender) {
	previousScene();
}

//------------------------------------------------------------------
//
// Intro Page
//
//------------------------------------------------------------------
var IntroPage = function() {

	goog.base(this);

	this.background1 = this.createImage( 'Official-cocos2d-Icon-Angry.png');
	this.background2 = this.createImage( 'Official-cocos2d-Icon-Happy.png');

	this.background2.setOpacity( 0 );

	// Not working setZOrder() ??
//	sprite.setZOrder( -200 );

	this.title = 'cocos2d + JS'
	this.subtitle = 'Javascript bindings for cocos2d';
	this.isMainTitle = true;

	this.onEnterTransitionDidFinish =  function() {
		var fade_out1 = cc.FadeOut.create( 2 );
		var fade_in1 = fade_out1.reverse();
		var delay1 = cc.DelayTime.create(4);

		var seq1 = cc.Sequence.create( fade_out1, fade_in1, delay1 );
		this.background1.runAction( cc.RepeatForever.create( seq1 ) );

		var delay2 = cc.DelayTime.create(4);
		var fade_out2 = cc.FadeOut.create( 2 );
		var fade_in2 = fade_out2.reverse();

		var seq2 = cc.Sequence.create( delay2, fade_in2, fade_out2 );
		this.background2.runAction( cc.RepeatForever.create( seq2 ) );
	}
}
goog.inherits( IntroPage, BaseLayer );

//------------------------------------------------------------------
//
// About Page
//
//------------------------------------------------------------------
var AboutPage = function() {

	goog.base(this);

	this.title = 'About';
	this.subtitle = 'What is cocos2d + JS ?';
	this.isMainTitle = false;

	this.createBulletList( 'Javascript bindings for cocos2d',
				'Same JS API as cocos2d-html5',
				'Works on iOS and Mac',
				'Faster development',
				'Great prototyping tool');
}
goog.inherits( AboutPage, BaseLayer );


//------------------------------------------------------------------
//
// Sprites Page
//
//------------------------------------------------------------------
var SpritesPage = function() {

	goog.base(this);

	this.title = 'Sprites';
	this.subtitle = ''

	var fontSize = winSize.height * 0.05;

	var label = cc.LabelTTF.create('cc.Sprite.create("grossini.png");', 'CourierNewPSMT', fontSize );
	label.setPosition( cc.p( winSize.width/2, winSize.height*1/5) );
	this.addChild( label );

	var sprite1 = cc.Sprite.create("grossinis_sister1.png");
	sprite1.setPosition( cc.p( winSize.width*1/4, winSize.height/2) );

	var sprite2 = cc.Sprite.create("grossini.png");
	sprite2.setPosition( cc.p( winSize.width*2/4, winSize.height/2) );

	var sprite3 = cc.Sprite.create("grossinis_sister2.png");
	sprite3.setPosition( cc.p( winSize.width*3/4, winSize.height/2) );

	this.addChild( sprite1 );
	this.addChild( sprite2 );
	this.addChild( sprite3 );
}
goog.inherits( SpritesPage, BaseLayer );




//------------------------------------------------------------------
//
// Labels Page
//
//------------------------------------------------------------------
var LabelsPage = function() {

	goog.base(this);

	this.title = 'Labels';
	this.subtitle = ''

	var fontSize = winSize.height * 0.03;

	var label = cc.LabelTTF.create('cc.LabelTTF.create("Hello JS World", "Marker Felt", 32);\ncc.LabelBMFont.create("Hello World", "font.fnt")', 'CourierNewPSMT', fontSize );
	label.setPosition( cc.p( winSize.width/2, winSize.height*1/5) );
	this.addChild( label );


	var labelTTF = cc.LabelTTF.create('Label TTF', 'Marker Felt', 48 );
	labelTTF.setPosition( cc.p( winSize.width*1/4, winSize.height/2) );
	this.addChild( labelTTF );

	var labelBM = cc.LabelBMFont.create('Label BMFont', 'futura-48.fnt');
	labelBM.setPosition( cc.p( winSize.width*3/4, winSize.height/2) );
	this.addChild( labelBM );

//	var labelAtlas = cc.LabelAtlas.create('Atlas', 'tuffy_bold_italic-charmap.plist');
//	labelAtlas.setPosition( cc.p( winSize.width*3/5, winSize.height/2) );
//	this.addChild( labelAtlas );

}
goog.inherits( LabelsPage, BaseLayer );


//------------------------------------------------------------------
//
// Actions Page
//
//------------------------------------------------------------------
var ActionsPage = function() {

	goog.base(this);

	this.title = 'Actions';
	this.subtitle = ''

	var fontSize = winSize.height * 0.05;

	var label = cc.LabelTTF.create('cc.RotateBy.create(8, 360);', 'CourierNewPSMT', fontSize );
	label.setPosition( cc.p( winSize.width/2, winSize.height*1/5) );
	this.addChild( label );

	this.sprite = cc.Sprite.create("grossini.png");
	this.sprite.setPosition( cc.p( winSize.width*2/4, winSize.height/2) );
	this.addChild( this.sprite );

	this.onEnterTransitionDidFinish = function() {
		var action = cc.RotateBy.create(8, 360);
		this.sprite.runAction( action );
	}
}
goog.inherits( ActionsPage, BaseLayer );

//------------------------------------------------------------------
//
// Actions Complex Page
//
//------------------------------------------------------------------
var ActionsComplexPage = function() {

	goog.base(this);

	this.title = 'Complex Actions';
	this.subtitle = ''

	var fontSize = winSize.height * 0.05;

	var label = cc.LabelTTF.create('cc.Sequence.create(action1, action2,...);', 'CourierNewPSMT', fontSize );
	label.setPosition( cc.p( winSize.width/2, winSize.height*1/5) );
	this.addChild( label );

	this.sprite = cc.Sprite.create("grossini.png");
	this.sprite.setPosition( cc.p( winSize.width*2/4, winSize.height/2) );
	this.addChild( this.sprite );

	// This function is not portable to cocos2d-html5
	this.sprite.getTexture().setAliasTexParameters();

	this.onEnterTransitionDidFinish = function() {
		var rot = cc.RotateBy.create(1, 360);
		var rot_back = rot.reverse();
		var scale = cc.ScaleBy.create(1, 7);
		var scale_back = scale.reverse();
		var seq = cc.Sequence.create( rot, scale, rot_back, scale_back );

		this.sprite.runAction( cc.RepeatForever.create( seq ) );
	}
}
goog.inherits( ActionsComplexPage, BaseLayer );

//------------------------------------------------------------------
//
// Actions Ease Page
//
//------------------------------------------------------------------
var ActionsEasePage = function() {

	goog.base(this);

	this.title = 'Ease Actions';
	this.subtitle = ''

	var fontSize = winSize.height * 0.05;

	var label = cc.LabelTTF.create('cc.EaseIn.create(action1, rate);', 'CourierNewPSMT', fontSize );
	label.setPosition( cc.p( winSize.width/2, winSize.height*1/5) );
	this.addChild( label );

	this.sprite1 = cc.Sprite.create("grossini.png");
	this.sprite2 = cc.Sprite.create("grossinis_sister1.png");
	this.sprite3 = cc.Sprite.create("grossinis_sister2.png");

	this.addChild( this.sprite1 );
	this.addChild( this.sprite2 );
	this.addChild( this.sprite3 );

	this.sprite1.setPosition( cc.p(60, winSize.height*1/5) );
	this.sprite2.setPosition( cc.p(60, winSize.height*2.5/5) );
	this.sprite3.setPosition( cc.p(60, winSize.height*4/5) );

	this.onEnterTransitionDidFinish = function() {
		var move = cc.MoveBy.create( 3, cc.p(winSize.width-130,0) );
		var move_back = move.reverse();

		var move_ease_in = cc.EaseIn.create( move.copy(),  2.5 );
		var move_ease_in_back = move_ease_in.reverse();

		var move_ease_out = cc.EaseOut.create( move.copy(), 2.5 );
		var move_ease_out_back = move_ease_out.reverse();

		var delay = cc.DelayTime.create( 0.25 );

		var seq1 = cc.Sequence.create( move, delay, move_back, delay.copy());
		var seq2 = cc.Sequence.create( move_ease_in, delay.copy(), move_ease_in_back, delay.copy() );
		var seq3 = cc.Sequence.create( move_ease_out, delay.copy(), move_ease_out_back, delay.copy() );

		this.sprite1.runAction( cc.RepeatForever.create( seq1 ) );
		this.sprite2.runAction( cc.RepeatForever.create( seq2 ) );
		this.sprite3.runAction( cc.RepeatForever.create( seq3 ) );
	}
}
goog.inherits( ActionsEasePage, BaseLayer );

//------------------------------------------------------------------
//
// Particles Page
//
//------------------------------------------------------------------
var ParticlesPage = function() {

	goog.base(this);

	this.title = 'Particles';
	this.subtitle = ''

	var fontSize = winSize.height * 0.05;

	var label = cc.LabelTTF.create('cc.ParticleSystem.create("myparticle.plist");', 'CourierNewPSMT', fontSize );
	label.setPosition( cc.p( winSize.width/2, winSize.height*1/5) );
	this.addChild( label );

	this.particle = cc.ParticleSystem.create("Particles/Flower.plist");
	this.addChild( this.particle );
	this.particle.setPosition( centerPos );

	var platform = __getPlatform();
    if( platform.substring(0,7) == 'desktop' )
        this.setMouseEnabled( true );
    else if( platform.substring(0,6) == 'mobile' )
        this.setTouchEnabled( true );

	this.onMouseDown = function( event ) {
		this.particle.setPosition( event.getLocation() );
	}

	this.onMouseDragged = function( event ) {
		return this.onMouseDown( event );
	}

	this.onTouchesEnded = function( touches, event ) {
		var l = touches.length;
		for( var i=0; i < l; i++) {
			this.particle.setPosition( touches[i].getLocation() );
		}
	}

	this.onTouchesMoved = function( touches, event ) {
		return this.onTouchesEnded( touches, event );
	}

}
goog.inherits( ParticlesPage, BaseLayer );


//------------------------------------------------------------------
//
// Chipmunk Page
//
//------------------------------------------------------------------
var ChipmunkPage = function() {

	goog.base(this);

	// batch node
	this.batch = cc.SpriteBatchNode.create('grossini.png', 50 );
	this.addChild( this.batch );

	this.addSprite = function( pos ) {
		var sprite =  this.createPhysicsSprite( pos );
		this.batch.addChild( sprite );
	}

	this.title = 'Physics Integration';
	this.subtitle = 'Integration with Chipmunk Physics Engine';

	this.initPhysics();
}
goog.inherits( ChipmunkPage, BaseLayer );

//
// Instance 'base' methods
// XXX: Should be defined after "goog.inherits"
//

// init physics
ChipmunkPage.prototype.initPhysics = function() {
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

ChipmunkPage.prototype.createPhysicsSprite = function( pos ) {
	var body = cp.bodyNew(1, cp.momentForBox(1, 48, 108) );
	cp.bodySetPos( body, pos );
	cp.spaceAddBody( this.space, body );
	var shape = cp.boxShapeNew( body, 48, 108);
	cp.shapeSetElasticity( shape, 0.5 );
	cp.shapeSetFriction( shape, 0.5 );
	cp.spaceAddShape( this.space, shape );

	var sprite = cc.ChipmunkSprite.create("grossini.png");
	sprite.setBody( body );
	return sprite;
}

ChipmunkPage.prototype.onEnter = function () {

	goog.base(this, 'onEnter');

	for(var i=0; i<20; i++) {
		var x = 40 + Math.random() * (winSize.width-80);
		var y = winSize.height/2 + Math.random() * 80;
		this.addSprite( cp.v(x, y) );
	}

	var platform = __getPlatform();
    if( platform.substring(0,7) == 'desktop' )
        this.setMouseEnabled( true );
    else if( platform.substring(0,6) == 'mobile' )
        this.setTouchEnabled( true );
}

ChipmunkPage.prototype.onEnterTransitionDidFinish = function () {
	this.scheduleUpdate();
}


ChipmunkPage.prototype.update = function( delta ) {
	cp.spaceStep( this.space, delta );
}

ChipmunkPage.prototype.onMouseDown = function( event ) {
	this.addSprite( event.getLocation() );
}

ChipmunkPage.prototype.onTouchesEnded = function( touches, event ) {
	var l = touches.length;
	for( var i=0; i < l; i++) {
		this.addSprite( touches[i].getLocation() );
	}
}


//------------------------------------------------------------------
//
// Behind The Scenes Page
//
//------------------------------------------------------------------
var BehindTheScenesPage = function() {

	goog.base(this);

	this.title = 'Behind The Scenes';
	this.subtitle = '';
	this.isMainTitle = true;

}
goog.inherits( BehindTheScenesPage, BaseLayer );

//------------------------------------------------------------------
//
// ParserFeaturesPage Page
//
//------------------------------------------------------------------
var ParserFeaturesPage = function() {

	goog.base(this);

	this.title = 'Parser Features';
	this.subtitle = '';
	this.isMainTitle = false;

	this.createBulletList( 'Any Objective-C / C library',
				'No need to modify generated code',
				'No need to modify parsed library',
				'Easy to maintain and extend',
				'Powerful config file' );
}
goog.inherits( ParserFeaturesPage, BaseLayer );

//------------------------------------------------------------------
//
// Internals
//
//------------------------------------------------------------------
var InternalsPage = function() {

	goog.base(this);

	this.title = 'Internals';
	this.subtitle = 'Solid internal design';
	this.isMainTitle = false;

	this.onEnterTransitionDidFinish = function() {
		// super onEnter
//		goog.base( this, 'onEnterTransitionDidFinish' );

		var spr = this.createImage( 'Presentation/proxy_model.png' );
		spr.setScale( 0.1 );
		var scaleAction = cc.ScaleTo.create( 0.7, 1);
		spr.runAction( scaleAction );
	}
}
goog.inherits( InternalsPage, BaseLayer );

//------------------------------------------------------------------
//
// DemoPage
//
//------------------------------------------------------------------
var DemoPage = function() {

	goog.base(this);

	this.title = 'Demo';
	this.subtitle = '';
	this.isMainTitle = true;
}
goog.inherits( DemoPage, BaseLayer );

//------------------------------------------------------------------
//
// OneMoreThing
//
//------------------------------------------------------------------
var OneMoreThingPage = function() {

	goog.base(this);

	this.title = 'One More Thing';
	this.subtitle = '';
	this.isMainTitle = true;
}
goog.inherits( OneMoreThingPage, BaseLayer );

//------------------------------------------------------------------
//
// Thanks
//
//------------------------------------------------------------------
var ThanksPage = function() {

	goog.base(this);

	this.title = 'Thanks';
	this.subtitle = '';
	this.isMainTitle = true;
}
goog.inherits( ThanksPage, BaseLayer );


//
// Order of tests
//
scenes.push( IntroPage );
scenes.push( AboutPage );
scenes.push( SpritesPage );
scenes.push( LabelsPage );
scenes.push( ActionsPage );
scenes.push( ActionsComplexPage );
scenes.push( ActionsEasePage );
scenes.push( ParticlesPage );
scenes.push( ChipmunkPage );
scenes.push( BehindTheScenesPage );
scenes.push( ParserFeaturesPage );
scenes.push( InternalsPage );
scenes.push( DemoPage );
scenes.push( OneMoreThingPage );
scenes.push( ThanksPage );


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

	director.setDisplayStats( false );

    var runningScene = director.getRunningScene();
    if( runningScene == null )
        director.runWithScene( scene );
    else
        director.replaceScene( cc.TransitionFade.create(0.5, scene ) );
}

run();

