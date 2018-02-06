/****************************************************************************
 Copyright (c) 2008-2010 Ricardo Quesada
 Copyright (c) 2011-2012 cocos2d-x.org
 Copyright (c) 2013-2016 Chukong Technologies Inc.
 Copyright (c) 2017-2018 Xiamen Yaji Software Co., Ltd.

 Permission is hereby granted, free of charge, to any person obtaining a copy
 of this software and associated documentation files (the "Software"), to deal
 in the Software without restriction, including without limitation the rights
 to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 copies of the Software, and to permit persons to whom the Software is
 furnished to do so, subject to the following conditions:

 The above copyright notice and this permission notice shall be included in
 all copies or substantial portions of the Software.

 THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 THE SOFTWARE.
 ****************************************************************************/


var presentationSceneIdx = -1;
var centerPos = cc.p(0,0); // will be updated later
var images_path = 'Presentation/';

//------------------------------------------------------------------
//
// PresentationBaseLayer
//
//------------------------------------------------------------------
var PresentationBaseLayer = function() {

	//
	// VERY IMPORTANT
	//
	// Only subclasses of a native classes MUST call __associateObjectWithNative
	// Failure to do so, it will crash.
	//
	var parent = BaseTestLayer.call(this, cc.color(0,0,0,255), cc.color(98,99,117,255));

	this._title =  "No title";
	this._subtitle = "No Subtitle";
	this.isMainTitle = false;

};
cc.inherits(PresentationBaseLayer, BaseTestLayer );

//
// Instance 'base' methods
// XXX: Should be defined after "cc.inherits"
//
PresentationBaseLayer.prototype.onEnter = function() {

	BaseTestLayer.prototype.onEnter.call(this);

	var fontSize = 36;
	var tl = this._title.length;
	fontSize = (winSize.width / tl) * 1.60;
	if( fontSize/winSize.width > 0.09 ) {
		fontSize = winSize.width * 0.09;
	}

	this.label = new cc.LabelTTF(this._title, "Gill Sans", fontSize);
	this.addChild(this.label, 100);

	var isMain = this.isMainTitle;

	if( isMain === true ) {
		this.label.x = centerPos.x;
		this.label.y = centerPos.y;
	}
	else {
		this.label.x = winSize.width / 2;
		this.label.y = winSize.height*11/12 ;
	}

	var subStr = this._subtitle;
	if (subStr !== "") {
		tl = this._subtitle.length;
		var subfontSize = (winSize.width / tl) * 1.3;
		if( subfontSize > fontSize *0.4 ) {
			subfontSize = fontSize *0.4;
		}

		this.sublabel = new cc.LabelTTF(subStr, "Thonburi", subfontSize);
		this.addChild(this.sublabel, 90);
		if( isMain ) {
			this.sublabel.x = winSize.width / 2;
			this.sublabel.y = winSize.height*3/8;
		}
		else {
			this.sublabel.x = winSize.width / 2;
			this.sublabel.y = winSize.height*4/5;
		}
	} else
		this.sublabel = null;

    // Opacity in Menu
    var menu = this.getChildByTag(BASE_TEST_MENU_TAG);
    var item1 = menu.getChildByTag(BASE_TEST_MENUITEM_PREV_TAG);
    var item2 = menu.getChildByTag(BASE_TEST_MENUITEM_RESET_TAG);
    var item3 = menu.getChildByTag(BASE_TEST_MENUITEM_NEXT_TAG);

	[item1, item2, item3 ].forEach( function(item) {
		item.getNormalImage().opacity = 45;
		item.getSelectedImage().opacity = 45;
		} );

	// remove "super" titles
	this.removeChildByTag(BASE_TEST_TITLE_TAG);
	this.removeChildByTag(BASE_TEST_SUBTITLE_TAG);
};

PresentationBaseLayer.prototype.prevTransition = function () {
    return cc.TransitionSlideInL;
};

PresentationBaseLayer.prototype.nextTransition = function () {
    return cc.TransitionSlideInR;
};

PresentationBaseLayer.prototype.createBulletList = function () {
	var str = "";
	for(var i=0; i<arguments.length; i++)
	{
		if(i !== 0)
			str += "\n";
		str += '- ' + arguments[i];
	}

	var fontSize = winSize.height*0.07;
	var bullets = new cc.LabelTTF( str, "Gill Sans", fontSize );
	bullets.x = centerPos.x;
	bullets.y = centerPos.y;
	this.addChild( bullets, 80 );
};

PresentationBaseLayer.prototype.createImage = function( file ) {
	var sprite = new cc.Sprite( file );
	sprite.x = centerPos.x;
	sprite.y = centerPos.y;
	this.addChild( sprite, 70 );

	return sprite;
};

// callbacks
PresentationBaseLayer.prototype.onRestartCallback = function (sender) {
    var s = new PresentationScene();
    s.addChild(restartPresentationSlide());
    director.runScene(s);
};

PresentationBaseLayer.prototype.onNextCallback = function (sender) {
    var s = new PresentationScene();
    s.addChild(nextPresentationSlide());
    director.runScene(s);
};

PresentationBaseLayer.prototype.onBackCallback = function (sender) {
    var s = new PresentationScene();
    s.addChild(previousPresentationSlide());
    director.runScene(s);
};

// automation
PresentationBaseLayer.prototype.numberOfPendingTests = function() {
    return ( (arrayOfPresentation.length-1) - presentationSceneIdx );
};

PresentationBaseLayer.prototype.getTestNumber = function() {
    return presentationSceneIdx;
};


//------------------------------------------------------------------
//
// Intro Page
//
//------------------------------------------------------------------
var IntroPage = function() {

	PresentationBaseLayer.call(this);

	this._title = 'cocos2d JS';
	this._subtitle = 'Game Development Kit';
	this.isMainTitle = true;
};
cc.inherits( IntroPage, PresentationBaseLayer );

//------------------------------------------------------------------
//
// Goal Page
//
//------------------------------------------------------------------
var GoalPage = function() {

	PresentationBaseLayer.call(this);

	this._title = 'Goals';
	this._subtitle = '';
	this.isMainTitle = false;

	this.createBulletList(
			'Rapid prototyping',
			'Rapid game development',
			'Multiplatform: Mobile & Web',
			'High quality code',
			'Good performance'
			);
};
cc.inherits( GoalPage, PresentationBaseLayer );

//------------------------------------------------------------------
//
// Solutions ?
//
//------------------------------------------------------------------
var SolutionsPage = function() {

	PresentationBaseLayer.call(this);

	this._title = 'Options';
	this._subtitle = '';
	this.isMainTitle = true;
};
cc.inherits( SolutionsPage, PresentationBaseLayer );

//------------------------------------------------------------------
//
// HTML5 engines ?
//
//------------------------------------------------------------------
var HTML5EnginesPage = function() {

	PresentationBaseLayer.call(this);

	this._title = 'Options';
	this._subtitle = 'HTML5 engines';
	this.isMainTitle = false;

	this.createBulletList(
			'cocos2d HTML5',
			'Impact JS',
			'LimeJS',
			'Construct 2',
			'etc...'
			);
};
cc.inherits( HTML5EnginesPage, PresentationBaseLayer );

//------------------------------------------------------------------
//
// Features
//
//------------------------------------------------------------------
var FeaturesHTML5Page = function() {

	PresentationBaseLayer.call(this);

	this._title = 'HTML5 Features';
	this._subtitle = '';
	this.isMainTitle = false;

	this.createBulletList(
			'Rapid prototyping',
			'Rapid game development',
			'Multiplatform: Mobile & Web',
			'High quality code ???',
			'Good Performance ???'
			);
};
cc.inherits( FeaturesHTML5Page, PresentationBaseLayer );

//------------------------------------------------------------------
//
// ComparisonPage
//
//------------------------------------------------------------------
var ComparisonPage = function() {

	PresentationBaseLayer.call(this);

	this._title = 'HTML5 Mobile performance';
	this._subtitle = 'Bad performance, even with accel frameworks';
	this.isMainTitle = false;

	this.createImage( images_path + 'comparison.png');

};
cc.inherits( ComparisonPage, PresentationBaseLayer );

//------------------------------------------------------------------
//
// WhatWeWantPage
//
//------------------------------------------------------------------
var WhatWeWantPage = function() {

	PresentationBaseLayer.call(this);

	this._title = 'Performance';
	this._subtitle = 'But what we want is...';
	this.isMainTitle = false;

	this.createBulletList(
			'Hundreds of sprites... at 60 FPS',
			'Physics... at 60 FPS',
			'Particles... at 60 FPS'
			);

};
cc.inherits( WhatWeWantPage, PresentationBaseLayer );

//------------------------------------------------------------------
//
// Chipmunk Page
//
//------------------------------------------------------------------
var ChipmunkPage = function() {

	PresentationBaseLayer.call(this);

	// batch node
	this.batch = new cc.SpriteBatchNode( s_pathGrossini, 50 );
	this.addChild( this.batch );

	this.addSprite = function( pos ) {
		var sprite =  this.createPhysicsSprite( pos );
		this.batch.addChild( sprite );
	};

	this._title = 'Performance';
	this._subtitle = 'Physics and Sprites';

	this.initPhysics();

	this.initMenu();
};
cc.inherits( ChipmunkPage, PresentationBaseLayer );

//
// Instance 'base' methods
// XXX: Should be defined after "cc.inherits"
//

ChipmunkPage.prototype.onTogglePhysicsDebug = function() {
	this.debugNode.visible = ! this.debugNode.visible ;
};

// Menu

ChipmunkPage.prototype.initMenu = function() {
	// menu
	cc.MenuItemFont.setFontSize( 16 );
	var menuItem = new cc.MenuItemFont('Toggle Physics Debug', this.onTogglePhysicsDebug, this);
	var menu = new cc.Menu( menuItem );
	this.addChild( menu, 99 );
	menu.x = winSize.width-80;
	menu.y = winSize.height-100;
};

// init physics
ChipmunkPage.prototype.initPhysics = function() {
	this.space =  new cp.Space();
	var staticBody = this.space.getStaticBody();

	// Walls
	var walls = [new cp.SegmentShape( staticBody, cp.v(0,0), cp.v(winSize.width,0), 0 ),				// bottom
			new cp.SegmentShape( staticBody, cp.v(0,winSize.height), cp.v(winSize.width,winSize.height), 0),	// top
			new cp.SegmentShape( staticBody, cp.v(0,0), cp.v(0,winSize.height), 0),				// left
			new cp.SegmentShape( staticBody, cp.v(winSize.width,0), cp.v(winSize.width,winSize.height), 0)	// right
			];
	for( var i=0; i < walls.length; i++ ) {
		var wall = walls[i];
		wall.setElasticity(1);
		wall.setFriction(1);
		this.space.addStaticShape(wall);
	}

	// Gravity
	this.space.gravity = cp.v(0, -100);


	// Physics debug layer
	this.debugNode = new cc.PhysicsDebugNode( this.space.handle );
	this.debugNode.visible = false ;
	this.addChild( this.debugNode, 100 );
};

ChipmunkPage.prototype.createPhysicsSprite = function( pos ) {
	var body = new cp.Body(1, cp.momentForBox(1, 48, 108) );
	body.setPos( pos );
	this.space.addBody( body );
	var shape = cp.BoxShape( body, 48, 108);
	shape.setElasticity( 0.5 );
	shape.setFriction( 0.5 );
	this.space.addShape( shape );

	var sprite = new cc.PhysicsSprite(s_pathGrossini);
	sprite.setBody( body.handle );
	return sprite;
};

ChipmunkPage.prototype.onEnter = function () {
	PresentationBaseLayer.prototype.onEnter.call(this);

	for(var i=0; i<20; i++) {
		var x = 40 + Math.random() * (winSize.width-80);
		var y = winSize.height/2 + Math.random() * 80;
		this.addSprite( cp.v(x, y) );
	}

    if( 'touches' in cc.sys.capabilities ){
        cc.eventManager.addListener({
            event: cc.EventListener.TOUCH_ALL_AT_ONCE,
            onTouchesEnded: function (touches, event) {
                var target = event.getCurrentTarget();
                var l = touches.length;
                for (var i = 0; i < l; i++) {
                    target.addSprite(touches[i].getLocation());
                }
            }
        }, this);
    } else if ('mouse' in cc.sys.capabilities )
       cc.eventManager.addListener({
           event: cc.EventListener.MOUSE,
           onMouseUp: function(event){
               event.getCurrentTarget().addSprite(event.getLocation());
           }
       }, this);
};

ChipmunkPage.prototype.onExitTransitionDidStart = function () {
	director.setDisplayStats( false );
};

ChipmunkPage.prototype.onEnterTransitionDidFinish = function () {
	director.setDisplayStats( true );

	this.scheduleUpdate();
};

ChipmunkPage.prototype.update = function( delta ) {
	this.space.step( delta );
};

//------------------------------------------------------------------
//
// Particles Page
//
//------------------------------------------------------------------
var ParticlesPage = function() {

	PresentationBaseLayer.call(this);

	this._title = 'Performance';
	this._subtitle = 'Particles';

	// var tex = cc.textureCache.addImage(s_fire);

	var firework = new cc.ParticleFireworks();
	// firework.texture = tex;
	this.addChild( firework );
	firework.x = centerPos.x;
	firework.y = centerPos.y;

	var sun = new cc.ParticleSun();
	// sun.texture = tex;
	this.addChild( sun );
	sun.x = winSize.width/4;
	sun.y = winSize.height/2;

	var meteor = new cc.ParticleMeteor();
	// meteor.texture = tex;
	this.addChild( meteor );
	meteor.x = winSize.width*3/4;
	meteor.y = winSize.height/2;

	var flower = new cc.ParticleSystem("Particles/Flower.plist");
	this.addChild( flower );
	flower.x = centerPos.x;
	flower.y = centerPos.y;

	this.particle = firework;

    if( 'touches' in cc.sys.capabilities ){
        cc.eventManager.addListener({
            event: cc.EventListener.TOUCH_ALL_AT_ONCE,
            onTouchesMoved: function(touches, event){
                var particle = event.getCurrentTarget().particle;
                var pos = touches[0].getLocation();
                particle.x = pos.x;
                particle.y = pos.y;
            },
            onTouchesEnded: function(touches, event){
                var particle = event.getCurrentTarget().particle;
                var pos = touches[0].getLocation();
                particle.x = pos.x;
                particle.y = pos.y;
            }
        }, this);
    } else if ('mouse' in cc.sys.capabilities )
        cc.eventManager.addListener({
            event: cc.EventListener.MOUSE,
            onMouseMove: function(event){
                var particle = event.getCurrentTarget().particle;
                particle.x = event.getLocationX();
                particle.y = event.getLocationY();
            },
            onMouseUp: function(event){
                var particle = event.getCurrentTarget().particle;
                particle.x = event.getLocationX();
                particle.y = event.getLocationY();
            }
        }, this);

	this.onExitTransitionDidStart = function () {
		director.setDisplayStats( false );
	};

	this.onEnterTransitionDidFinish = function () {
		director.setDisplayStats( true );
	};
};
cc.inherits( ParticlesPage, PresentationBaseLayer );


//------------------------------------------------------------------
//
// HowToImprovePage
//
//------------------------------------------------------------------
var HowToImprovePage = function() {

	PresentationBaseLayer.call(this);

	this._title = 'Improving the performance';
	this._subtitle = 'Redefining "fast" for mobile';
	this.isMainTitle = true;
};
cc.inherits( HowToImprovePage, PresentationBaseLayer );


//------------------------------------------------------------------
//
// HTML5AcceleratorPage
//
//------------------------------------------------------------------
var HTML5AcceleratorPage = function() {

	PresentationBaseLayer.call(this);

	this._title = 'HTML5 Mobile Accelerators';
	this._subtitle = '';
	this.isMainTitle = false;

	this.createImage( images_path + 'html5accelerator.png');
};
cc.inherits( HTML5AcceleratorPage, PresentationBaseLayer );


//------------------------------------------------------------------
//
// GDKAcceleratorPage
//
//------------------------------------------------------------------
var GDKAcceleratorPage = function() {

	PresentationBaseLayer.call(this);

	this._title = 'cocos2d Acceleration';
	this._subtitle = '';
	this.isMainTitle = false;

		this.createImage( images_path + 'gdkaccelerator.png');
};
cc.inherits( GDKAcceleratorPage, PresentationBaseLayer );

//------------------------------------------------------------------
//
// GDKComponentsPage
//
//------------------------------------------------------------------
var GDKComponentsPage = function() {

	PresentationBaseLayer.call(this);

	this._title = 'Components';
	this._subtitle = '';
	this.isMainTitle = false;

	this.createBulletList(
			'Game engine: cocos2d',
			'Physics engine: Chipmunk',
			'World Editor: CocosBuilder'
			);
};
cc.inherits( GDKComponentsPage, PresentationBaseLayer );


//------------------------------------------------------------------
//
// CocosStatusPage
//
//------------------------------------------------------------------
var CocosStatusPage = function() {

	PresentationBaseLayer.call(this);

	this._title = 'Game Engine';
	this._subtitle = '';
	this.isMainTitle = false;

    this.createImage( images_path + 'cocos2d_status.png' );
};
cc.inherits( CocosStatusPage, PresentationBaseLayer );

//------------------------------------------------------------------
//
// ChipmunkStatusPage
//
//------------------------------------------------------------------
var ChipmunkStatusPage = function() {

	PresentationBaseLayer.call(this);

	this._title = 'Physics Engine';
	this._subtitle = '';
	this.isMainTitle = false;

    this.createImage( images_path + 'chipmunk_status.png' );
};
cc.inherits( ChipmunkStatusPage, PresentationBaseLayer );

//------------------------------------------------------------------
//
// CCBStatusPage
//
//------------------------------------------------------------------
var CCBStatusPage = function() {

	PresentationBaseLayer.call(this);

	this._title = 'World Editor';
	this._subtitle = '';
	this.isMainTitle = false;

    this.createImage( images_path + 'cocosbuilder_status.png' );
};
cc.inherits( CCBStatusPage, PresentationBaseLayer );

//------------------------------------------------------------------
//
// WhoIsUsingItPage
//
//------------------------------------------------------------------
var WhoIsUsingItPage = function() {

	PresentationBaseLayer.call(this);

	this._title = "Who is using it";
	this._subtitle = '';
	this.isMainTitle = false;

	// Add companies that are using it
	this.createBulletList(
                'Zynga',
				'...and you ?'
                );
};
cc.inherits( WhoIsUsingItPage, PresentationBaseLayer );


//------------------------------------------------------------------
//
// DemoPage
//
//------------------------------------------------------------------
var DemoPage = function() {

	PresentationBaseLayer.call(this);

	this._title = 'Demo';
	this._subtitle = '';
	this.isMainTitle = true;
};
cc.inherits( DemoPage, PresentationBaseLayer );

//------------------------------------------------------------------
//
// Thanks
//
//------------------------------------------------------------------
var ThanksPage = function() {

	PresentationBaseLayer.call(this);

	this._title = 'Thanks';
	this._subtitle = '';
	this.isMainTitle = true;
};
cc.inherits( ThanksPage, PresentationBaseLayer );



//
// Entry point
//

var PresentationScene = function() {
	var parent = TestScene.call(this);
};
cc.inherits(PresentationScene, TestScene );

PresentationScene.prototype.runThisTest = function () {
    presentationSceneIdx = -1;
    centerPos = cc.p(winSize.width/2, winSize.height/2);
    var layer = nextPresentationSlide();
    this.addChild(layer);
    director.runScene(this);
};

//
// Flow control
//
var arrayOfPresentation = [
	IntroPage,
	GoalPage,
	HTML5EnginesPage,
	FeaturesHTML5Page,
	ComparisonPage,
	WhatWeWantPage,
	ChipmunkPage,
	ParticlesPage,
	HowToImprovePage,
	HTML5AcceleratorPage,
	GDKAcceleratorPage,
	GDKComponentsPage,
	// CocosStatusPage,
	// ChipmunkStatusPage,
	// CCBStatusPage,
	DemoPage,
	WhoIsUsingItPage,
	ThanksPage
];

var nextPresentationSlide = function () {
    presentationSceneIdx++;
    presentationSceneIdx = presentationSceneIdx % arrayOfPresentation.length;

    return new arrayOfPresentation[presentationSceneIdx]();
};
var previousPresentationSlide = function () {
    presentationSceneIdx--;
    if (presentationSceneIdx < 0)
        presentationSceneIdx += arrayOfPresentation.length;

    return new arrayOfPresentation[presentationSceneIdx]();
};
var restartPresentationSlide = function () {
    return new arrayOfPresentation[presentationSceneIdx]();
};

