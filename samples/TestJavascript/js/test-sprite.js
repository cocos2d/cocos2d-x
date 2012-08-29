//
// http://www.cocos2d-iphone.org
//
// Javascript + cocos2d sprite tests
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
// Sprite Touch test
//
//------------------------------------------------------------------
var SpriteTouchTest = function() {

	goog.base(this);

	this.initialize = function() {
		var platform = __getPlatform();
		if( platform.substring(0,7) == 'desktop' )
			this.setMouseEnabled( true );
		else if( platform.substring(0,6) == 'mobile' )
			this.setTouchEnabled( true );
		this.addSprite( centerPos );
	}

	this.addSprite = function(pos) {
		var sprite = this.createSprite( pos );
		this.addChild( sprite );
	}

	this.title = function () {
		return "Sprite: Simple action test";
	}

	this.subtitle = function () {
		return "Tap screen to add more sprites";
	}

	this.initialize();
}
goog.inherits(SpriteTouchTest, BaseLayer );

SpriteTouchTest.prototype.onMouseDown = function( event ) {
	this.addSprite( event.getLocation() );
}

SpriteTouchTest.prototype.onTouchesEnded = function( touches, event ) {
	var l = touches.length;
	for( var i=0; i < l; i++) {
		this.addSprite( touches[i].getLocation() );
	}
}


SpriteTouchTest.prototype.createSprite = function( pos ) {
	var idx = Math.random() * 1400 / 100;
	idx = Math.floor( idx );
	var x = Math.floor(idx%5) * 85;
	var y = Math.floor(idx/5) * 121;

	var sprite  = cc.Sprite.create("grossini_dance_atlas.png", cc.rect(x,y,85,121) );
	sprite.setPosition( pos );

	var rand = Math.random();

	if( rand < 0.20 ) {
		var action = cc.ScaleBy.create(3, 2 );
	} else if(rand < 0.40) {
		var action = cc.RotateBy.create(3, 360 );
	} else if( rand < 0.60) {
		var action = cc.Blink.create(1, 3 );
	} else if( rand < 0.8 ) {
		var action = cc.TintBy.create(2, 0, -255, -255 );
	} else {
		var action = cc.FadeOut.create( 2 );
	}
	var action_back = action.reverse();
	var seq = cc.Sequence.create(action, action_back);

	sprite.runAction( cc.RepeatForever.create( seq ) );

	return sprite;
}


//------------------------------------------------------------------
//
// Sprite Batch Touch test
//
//------------------------------------------------------------------
var SpriteBatchTouchTest = function() {

	goog.base(this);

	this.initialize = function() {
		this.batch = cc.SpriteBatchNode.create("grossini_dance_atlas.png", 50 );
		this.addChild( this.batch );

		var platform = __getPlatform();
		if( platform == 'OSX' ) {
			this.setIsMouseEnabled( true );
		} else if( platform == 'iOS' ) {
			this.setIsTouchEnabled( true );
		}
	}

	this.addSprite = function(pos) {
		var sprite = this.createSprite( pos );
		this.batch.addChild( sprite );
	}

	this.title = function () {
		return "SpriteBatch: Simple action test";
	}

	this.subtitle = function () {
		return "Tap screen to add more sprites";
	}

	this.initialize();
}
goog.inherits( SpriteBatchTouchTest, SpriteTouchTest );

//------------------------------------------------------------------
//
// Sprite vs. SpriteBatch Animation
//
//------------------------------------------------------------------
var SpriteFrameTest = function() {

	goog.base(this);

	this.initialize = function() {
		var cache = cc.SpriteFrameCache.getInstance();
		cache.addSpriteFrames( "animations/grossini.plist" );
		cache.addSpriteFrames( "animations/grossini_gray.plist", "animations/grossini_gray.png" );
		cache.addSpriteFrames( "animations/grossini_blue.plist", "animations/grossini_blue.png" );

		//
		// Animation using Sprite batch
		//
		// A CCSpriteBatchNode can reference one and only one texture (one .png file)
		// Sprites that are contained in that texture can be instantiatied as CCSprites and then added to the CCSpriteBatchNode
		// All CCSprites added to a CCSpriteBatchNode are drawn in one OpenGL ES draw call
		// If the CCSprites are not added to a CCSpriteBatchNode then an OpenGL ES draw call will be needed for each one, which is less efficient
		//
		// When you animate a sprite, CCAnimation changes the frame of the sprite using setDisplayFrame: (this is why the animation must be in the same texture)
		// When setDisplayFrame: is used in the CCAnimation it changes the frame to one specified by the CCSpriteFrames that were added to the animation,
		// but texture id is still the same and so the sprite is still a child of the CCSpriteBatchNode,
		// and therefore all the animation sprites are also drawn as part of the CCSpriteBatchNode
		//

		var sprite1 = cc.Sprite.createWithSpriteFrameName("grossini_dance_01.png");
		sprite1.setPosition( cc.p( winSize.width/2-80, winSize.height/2) );

		var spritebatch = cc.SpriteBatchNode.create("animations/grossini.pvr.gz");
		spritebatch.addChild(sprite1);
		this.addChild( spritebatch );

		var frames = []
		for( var i = 1; i < 15; i++) {

			if( i < 10 ) {
				var name = "grossini_dance_0" + i + ".png";
			} else {
				var name = "grossini_dance_" + i + ".png";
			}

			var frame = cache.getSpriteFrame( name );
			frames.push( frame );
		}

		var animation = cc.Animation.create( frames, 0.3 );
		// 14 frames * 1sec = 14 seconds
		sprite1.runAction( cc.RepeatForever.create( cc.Animate.create( animation ) ) );


		//
		// Animation using standard Sprite
		//
		//
		var sprite2 = cc.Sprite.createWithSpriteFrameName( "grossini_dance_01.png" );
		sprite2.setPosition( cc.p( winSize.width/2 + 80, winSize.height/2) );
		this.addChild( sprite2 );

		var moreFrames = []
		for(var i = 1; i < 15; i++) {
			if( i < 10 ) {
				var name = "grossini_dance_gray_0" + i + ".png";
			} else {
				var name = "grossini_dance_gray_" + i + ".png";
			}
			var frame = cache.getSpriteFrame( name );
			moreFrames.push( frame );
		}
		for( var i = 1; i < 5; i++) {
			var name = "grossini_blue_0" + i + ".png";
			var frame = cache.getSpriteFrame( name );
			moreFrames.push( frame );
		}


		moreFrames.concat( frames );
		var animMixed = cc.Animation.create( moreFrames, 0.3 );

		// 32 frames * 1 seconds = 32 seconds
		sprite2.runAction( cc.RepeatForever.create( cc.Animate.create( animMixed ) ) );

		// to test issue #732, uncomment the following line
		sprite2.setFlipX( false );
		sprite2.setFlipY( false );
	}

	this.title = function () {
		return "Sprite vs. SpriteBatchNode animation";
	}

	this.subtitle = function () {
		return "Testing issue #792";
	}

	this.initialize();
}
goog.inherits( SpriteFrameTest, BaseLayer );

//------------------------------------------------------------------
//
// SpriteAnchorPoint
//
//------------------------------------------------------------------
var SpriteAnchorPoint = function() {

	goog.base(this);

	this.initialize = function() {
		for(var i=0;i<3;i++) {
			var sprite = cc.Sprite.create("grossini_dance_atlas.png", cc.rect(85*i, 121*1, 85, 121) );
			sprite.setPosition( cc.p( winSize.width/4*(i+1), winSize.height/2) );

			var point = cc.Sprite.create( "r1.png" );
			point.setScale( 0.25 );
			point.setPosition( sprite.getPosition() );
			this.addChild( point, 10 );

			if( i == 0 ) {
				sprite.setAnchorPoint( cc.p( 0, 0) );
			} else if( i == 1 ) {
				sprite.setAnchorPoint( cc.p(0.5, 0.5) );
			} else if( i == 2 ) {
				sprite.setAnchorPoint( cc.p(1,1) );
			}

			point.setPosition( sprite.getPosition() );

			var rotate = cc.RotateBy.create(10, 360);
			var action = cc.RepeatForever.create( rotate );

			sprite.runAction( action );
			this.addChild( sprite, i );
		}
	}

	this.title = function () {
		return "Sprite: anchor point";
	}

	this.subtitle = function () {
		return "Testing 3 different anchor points";
	}

	this.initialize();
}
goog.inherits( SpriteAnchorPoint, BaseLayer );

//------------------------------------------------------------------
//
// SpriteBatchAnchorPoint
//
//------------------------------------------------------------------
var SpriteBatchAnchorPoint = function() {

	goog.base(this);

	this.initialize = function() {
		var batch = cc.SpriteBatchNode.create( "grossini_dance_atlas.png" );
		for(var i=0;i<3;i++) {
			var sprite = cc.Sprite.create("grossini_dance_atlas.png", cc.rect(85*i, 121*1, 85, 121) );
			sprite.setPosition( cc.p( winSize.width/4*(i+1), winSize.height/2) );

			var point = cc.Sprite.create( "r1.png" );
			point.setScale( 0.25 );
			point.setPosition( sprite.getPosition() );
			this.addChild( point, 10 );

			if( i == 0 ) {
				sprite.setAnchorPoint( cc.p( 0, 0) );
			} else if( i == 1 ) {
				sprite.setAnchorPoint( cc.p(0.5, 0.5) );
			} else if( i == 2 ) {
				sprite.setAnchorPoint( cc.p(1,1) );
			}

			point.setPosition( sprite.getPosition() );

			var rotate = cc.RotateBy.create(10, 360);
			var action = cc.RepeatForever.create( rotate );

			sprite.runAction( action );
			batch.addChild( sprite, i );
		}
		this.addChild( batch );
	}

	this.title = function () {
		return "Sprite Batch: anchor point";
	}

	this.subtitle = function () {
		return "Testing 3 different anchor points";
	}

	this.initialize();
}
goog.inherits( SpriteBatchAnchorPoint, BaseLayer );

//------------------------------------------------------------------
//
// SpriteOffsetAnchorFlip
//
//------------------------------------------------------------------
var SpriteOffsetAnchorFlip = function() {

	goog.base(this);

	this.initialize = function() {
		var cache = cc.SpriteFrameCache.getInstance();
		cache.addSpriteFrames("animations/grossini.plist");
		cache.addSpriteFrames("animations/grossini_gray.plist", "animations/grossini_gray.png");

		for(var i=0;i<3;i++) {
			var sprite = cc.Sprite.create("grossini_dance_atlas.png", cc.rect(85*i, 121*1, 85, 121) );
			sprite.setPosition( cc.p( winSize.width/4*(i+1), winSize.height/2) );

			var point = cc.Sprite.create( "r1.png" );
			point.setScale( 0.25 );
			point.setPosition( sprite.getPosition() );
			this.addChild( point, 10 );

			if( i == 0 ) {
				sprite.setAnchorPoint( cc.p( 0, 0) );
			} else if( i == 1 ) {
				sprite.setAnchorPoint( cc.p(0.5, 0.5) );
			} else if( i == 2 ) {
				sprite.setAnchorPoint( cc.p(1,1) );
			}

			point.setPosition( sprite.getPosition() );

			var frames = []
			for( var j = 1; j < 15; j++) {

				if( j < 10 ) {
					var name = "grossini_dance_0" + j + ".png";
				} else {
					var name = "grossini_dance_" + j + ".png";
				}

				var frame = cache.getSpriteFrame( name );
				frames.push( frame );
			}

			var animation = cc.Animation.create( frames, 0.3 );
			sprite.runAction( cc.RepeatForever.create( cc.Animate.create( animation ) ) );

			var flip = cc.FlipY.create( true );
			var flip_back = cc.FlipY.create( false );
			var delay = cc.DelayTime.create( 1 );
			var delay2 = cc.DelayTime.create( 1 );
			var seq = cc.Sequence.create( delay, flip, delay2, flip_back );
			sprite.runAction( cc.RepeatForever.create( seq ) );

			this.addChild( sprite );
		}
	}

	this.title = function () {
		return "Sprite offset + anchor + flip";
	}

	this.subtitle = function () {
		return "issue #1078";
	}

	this.initialize();
}
goog.inherits( SpriteOffsetAnchorFlip, BaseLayer );

//------------------------------------------------------------------
//
// SpriteBatchOffsetAnchorFlip
//
//------------------------------------------------------------------
var SpriteBatchOffsetAnchorFlip = function() {

	goog.base(this);

	this.initialize = function() {
		var cache = cc.SpriteFrameCache.getInstance();
		cache.addSpriteFrames("animations/grossini.plist");
		cache.addSpriteFrames("animations/grossini_gray.plist", "animations/grossini_gray.png");

		var batch = cc.SpriteBatchNode.create("animations/grossini.pvr.gz");

		for(var i=0;i<3;i++) {
			var sprite = cc.Sprite.createWithSpriteFrameName("grossini_dance_01.png");
			sprite.setPosition( cc.p( winSize.width/4*(i+1), winSize.height/2) );

			var point = cc.Sprite.create( "r1.png" );
			point.setScale( 0.25 );
			point.setPosition( sprite.getPosition() );
			this.addChild( point, 10 );

			if( i == 0 ) {
				sprite.setAnchorPoint( cc.p( 0, 0) );
			} else if( i == 1 ) {
				sprite.setAnchorPoint( cc.p(0.5, 0.5) );
			} else if( i == 2 ) {
				sprite.setAnchorPoint( cc.p(1,1) );
			}

			point.setPosition( sprite.getPosition() );

			var frames = []
			for( var j = 1; j < 15; j++) {

				if( j < 10 ) {
					var name = "grossini_dance_0" + j + ".png";
				} else {
					var name = "grossini_dance_" + j + ".png";
				}

				var frame = cache.getSpriteFrame( name );
				frames.push( frame );
			}

			var animation = cc.Animation.create( frames, 0.3 );
			sprite.runAction( cc.RepeatForever.create( cc.Animate.create( animation ) ) );

			var flip = cc.FlipY.create( true );
			var flip_back = cc.FlipY.create( false );
			var delay = cc.DelayTime.create( 1 );
			var delay2 = cc.DelayTime.create( 1 );
			var seq = cc.Sequence.create( delay, flip, delay2, flip_back );
			sprite.runAction( cc.RepeatForever.create( seq ) );

			batch.addChild( sprite );
		}
		this.addChild(batch);
	}

	this.title = function () {
		return "SpriteBatch offset + anchor + flip";
	}

	this.subtitle = function () {
		return "issue #1078";
	}

	this.initialize();
}
goog.inherits( SpriteBatchOffsetAnchorFlip, BaseLayer );


//------------------------------------------------------------------
//
// SpriteColorOpacity
//
//------------------------------------------------------------------
var SpriteColorOpacity = function() {

	goog.base(this);

	this.initialize = function() {
		var sprite1 = cc.Sprite.create('grossini_dance_atlas.png', cc.rect(85 * 0, 121 * 1, 85, 121));
		var sprite2 = cc.Sprite.create('grossini_dance_atlas.png', cc.rect(85 * 1, 121 * 1, 85, 121));
		var sprite3 = cc.Sprite.create('grossini_dance_atlas.png', cc.rect(85 * 2, 121 * 1, 85, 121));
		var sprite4 = cc.Sprite.create('grossini_dance_atlas.png', cc.rect(85 * 3, 121 * 1, 85, 121));
		var sprite5 = cc.Sprite.create('grossini_dance_atlas.png', cc.rect(85 * 0, 121 * 1, 85, 121));
		var sprite6 = cc.Sprite.create('grossini_dance_atlas.png', cc.rect(85 * 1, 121 * 1, 85, 121));
		var sprite7 = cc.Sprite.create('grossini_dance_atlas.png', cc.rect(85 * 2, 121 * 1, 85, 121));
		var sprite8 = cc.Sprite.create('grossini_dance_atlas.png', cc.rect(85 * 3, 121 * 1, 85, 121));

		sprite1.setPosition(cc.p((winSize.width / 5) * 1, (winSize.height / 3) * 1));
		sprite2.setPosition(cc.p((winSize.width / 5) * 2, (winSize.height / 3) * 1));
		sprite3.setPosition(cc.p((winSize.width / 5) * 3, (winSize.height / 3) * 1));
		sprite4.setPosition(cc.p((winSize.width / 5) * 4, (winSize.height / 3) * 1));
		sprite5.setPosition(cc.p((winSize.width / 5) * 1, (winSize.height / 3) * 2));
		sprite6.setPosition(cc.p((winSize.width / 5) * 2, (winSize.height / 3) * 2));
		sprite7.setPosition(cc.p((winSize.width / 5) * 3, (winSize.height / 3) * 2));
		sprite8.setPosition(cc.p((winSize.width / 5) * 4, (winSize.height / 3) * 2));

		var action = cc.FadeIn.create(2);
		var action_back = action.reverse();
		var fade = cc.RepeatForever.create( cc.Sequence.create( action, action_back ) );

		var tintRed = cc.TintBy.create(2, 0, -255, -255);
	//	var tintRed = cc.RotateBy.create(2, 360 );
		var tintRedBack = tintRed.reverse();
		var red = cc.RepeatForever.create(cc.Sequence.create( tintRed, tintRedBack ) );

		var tintGreen = cc.TintBy.create(2, -255, 0, -255);
		var tintGreenBack = tintGreen.reverse();
		var green = cc.RepeatForever.create(cc.Sequence.create( tintGreen, tintGreenBack ) );

		var tintBlue = cc.TintBy.create(2, -255, -255, 0);
		var tintBlueBack = tintBlue.reverse();
		var blue = cc.RepeatForever.create(cc.Sequence.create( tintBlue, tintBlueBack ) );

		sprite5.runAction(red);
		sprite6.runAction(green);
		sprite7.runAction(blue);
		sprite8.runAction(fade);

		// late add: test dirtyColor and dirtyPosition
		this.addChild(sprite1);
		this.addChild(sprite2);
		this.addChild(sprite3);
		this.addChild(sprite4);
		this.addChild(sprite5);
		this.addChild(sprite6);
		this.addChild(sprite7);
		this.addChild(sprite8);
	}

	//
	// Instance methods
	//
	this.title = function () {
		return "Sprite: Color & Opacity";
	}

	this.subtitle = function () {
		return "testing opacity and color";
	}

	this.initialize();
}
goog.inherits(SpriteColorOpacity, BaseLayer );

//------------------------------------------------------------------
//
// SpriteBatchColorOpacity
//
//------------------------------------------------------------------
var SpriteBatchColorOpacity = function() {

	goog.base(this);

	this.initialize = function() {
		var batch = cc.SpriteBatchNode.create('grossini_dance_atlas.png', 10);
		var sprite1 = cc.Sprite.create('grossini_dance_atlas.png', cc.rect(85 * 0, 121 * 1, 85, 121));
		var sprite2 = cc.Sprite.create('grossini_dance_atlas.png', cc.rect(85 * 1, 121 * 1, 85, 121));
		var sprite3 = cc.Sprite.create('grossini_dance_atlas.png', cc.rect(85 * 2, 121 * 1, 85, 121));
		var sprite4 = cc.Sprite.create('grossini_dance_atlas.png', cc.rect(85 * 3, 121 * 1, 85, 121));
		var sprite5 = cc.Sprite.create('grossini_dance_atlas.png', cc.rect(85 * 0, 121 * 1, 85, 121));
		var sprite6 = cc.Sprite.create('grossini_dance_atlas.png', cc.rect(85 * 1, 121 * 1, 85, 121));
		var sprite7 = cc.Sprite.create('grossini_dance_atlas.png', cc.rect(85 * 2, 121 * 1, 85, 121));
		var sprite8 = cc.Sprite.create('grossini_dance_atlas.png', cc.rect(85 * 3, 121 * 1, 85, 121));

		sprite1.setPosition(cc.p((winSize.width / 5) * 1, (winSize.height / 3) * 1));
		sprite2.setPosition(cc.p((winSize.width / 5) * 2, (winSize.height / 3) * 1));
		sprite3.setPosition(cc.p((winSize.width / 5) * 3, (winSize.height / 3) * 1));
		sprite4.setPosition(cc.p((winSize.width / 5) * 4, (winSize.height / 3) * 1));
		sprite5.setPosition(cc.p((winSize.width / 5) * 1, (winSize.height / 3) * 2));
		sprite6.setPosition(cc.p((winSize.width / 5) * 2, (winSize.height / 3) * 2));
		sprite7.setPosition(cc.p((winSize.width / 5) * 3, (winSize.height / 3) * 2));
		sprite8.setPosition(cc.p((winSize.width / 5) * 4, (winSize.height / 3) * 2));

		var action = cc.FadeIn.create(2);
		var action_back = action.reverse();
		var fade = cc.RepeatForever.create( cc.Sequence.create( action, action_back ) );

		var tintRed = cc.TintBy.create(2, 0, -255, -255);
	//	var tintRed = cc.RotateBy.create(2, 360 );
		var tintRedBack = tintRed.reverse();
		var red = cc.RepeatForever.create(cc.Sequence.create( tintRed, tintRedBack ) );

		var tintGreen = cc.TintBy.create(2, -255, 0, -255);
		var tintGreenBack = tintGreen.reverse();
		var green = cc.RepeatForever.create(cc.Sequence.create( tintGreen, tintGreenBack ) );

		var tintBlue = cc.TintBy.create(2, -255, -255, 0);
		var tintBlueBack = tintBlue.reverse();
		var blue = cc.RepeatForever.create(cc.Sequence.create( tintBlue, tintBlueBack ) );

		sprite5.runAction(red);
		sprite6.runAction(green);
		sprite7.runAction(blue);
		sprite8.runAction(fade);

		// late add: test dirtyColor and dirtyPosition
		this.addChild(batch);
		batch.addChild(sprite1);
		batch.addChild(sprite2);
		batch.addChild(sprite3);
		batch.addChild(sprite4);
		batch.addChild(sprite5);
		batch.addChild(sprite6);
		batch.addChild(sprite7);
		batch.addChild(sprite8);
	}

	//
	// Instance methods
	//
	this.title = function () {
		return "Sprite Batch: Color & Opacity";
	}

	this.subtitle = function () {
		return "testing opacity and color with batches";
	}

	this.initialize();
}
goog.inherits(SpriteBatchColorOpacity, BaseLayer );

//
// Order of tests
//
scenes.push( SpriteTouchTest ); scenes.push( SpriteBatchTouchTest );

scenes.push( SpriteFrameTest );

scenes.push( SpriteAnchorPoint ); scenes.push( SpriteBatchAnchorPoint );

scenes.push( SpriteOffsetAnchorFlip ); scenes.push( SpriteBatchOffsetAnchorFlip );

scenes.push( SpriteColorOpacity ); scenes.push( SpriteBatchColorOpacity );


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

