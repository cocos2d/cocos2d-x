/*
 * showcasing actions
 */

/**
 * simple wrappers
 */
cocos.Point.create = function (x, y) {
	var pt = new cocos.Point();
	pt.x = x;
	pt.y = y;
	return pt;
};

cocos.Size.create = function (w, h) {
	var sz = new cocos.Size();
	sz.width = w;
	sz.height = h;
	return sz;
};

cocos.Sprite.create = function (file) {
	var s = new cocos.Sprite();
	s.initWithFile(file);
	return s;
};

var pointZero = cocos.Point.create(0, 0);
var sizeZero = cocos.Size.create(0, 0);

var director = cocos.Director.sharedDirector();
var winSize = director.winSize;

var scenes = {};
scenes.currentScene = 1;

/**
 * tests the most basic function: moveTo and moveBy
 */
scenes['test_move'] = function () {
	var s1 = new cocos.Sprite.create("grossini_dance_05.png");
	s1.position = cocos.Point.create(winSize.width / 2 + 50, winSize.height / 2);
	var s2 = new cocos.Sprite.create("grossinis_sister1.png");
	s2.position = cocos.Point.create(winSize.width / 2 - 50, winSize.height / 2);

	var moveTo = new cocos.MoveTo();
	moveTo.initWithDuration(2.0, cocos.Point.create(winSize.width, winSize.height / 2));
	var moveBy = new cocos.MoveBy();
	moveBy.initWithDuration(2.0, cocos.Point.create(100, 100));

	s1.runAction(moveTo);
	s2.runAction(moveBy);

	var scene = new cocos.Scene(); scene.init();
	scene.addChild(s1);
	scene.addChild(s2);

	// add the menu
	var menu = createMenu("Test Move");
	scene.addChild(menu, 1);

	return scene;
};

scenes['test_rotate'] = function () {
	var s1 = new cocos.Sprite.create("grossini_dance_05.png");
	s1.position = cocos.Point.create(winSize.width / 2 + 50, winSize.height / 2);
	var s2 = new cocos.Sprite.create("grossinis_sister1.png");
	s2.rotation = 90;
	s2.position = cocos.Point.create(winSize.width / 2 - 100, winSize.height / 2);

	var rotateTo = new cocos.RotateTo();
	rotateTo.initWithDuration(1.0, 180.0);
	var rotateBy = new cocos.RotateBy();
	rotateBy.initWithDuration(2.0, 90);

	s1.runAction(rotateTo);
	s2.runAction(rotateBy);

	var scene = new cocos.Scene(); scene.init();
	scene.addChild(s1);
	scene.addChild(s2);

	// add the menu
	var menu = createMenu("Test Rotate");
	scene.addChild(menu, 1);

	return scene;
};

scenes['test_animation'] = function () {
	var spriteFrameCache = cocos.SpriteFrameCache.sharedSpriteFrameCache();
	spriteFrameCache.addSpriteFramesWithFile("tank.plist");

	// create a new sprite with a sprite frame
	var sprite = new cocos.Sprite();
	sprite.initWithSpriteFrameName("tank1.png");
	sprite.position = cocos.Point.create(winSize.width / 2, winSize.height / 2);

	// create animation
	var frames = ["tank1.png", "tank2.png", "tank3.png", "tank4.png", "tank5.png"];
	var animation = new cocos.Animation();
	animation.init();
	// set the delay
	animation.delay = 0.1;
	// add the frames
	for (var i=0; i < frames.length; i++) {
		var frame = spriteFrameCache.spriteFrameByName(frames[i]);
		animation.addFrame(frame);
	}
	// action stored in the sprite to avoid GC
	sprite.anim = new cocos.Animate();
	sprite.anim.initWithAnimation(animation);
	sprite.runAction(sprite.anim);

	var scene = new cocos.Scene(); scene.init();
	scene.addChild(sprite);

	// add the menu
	var menu = createMenu("Test Animation");
	scene.addChild(menu, 1);

	return scene;
};

scenes['test_repeat'] = function () {
	var s1 = new cocos.Sprite.create("grossinis_sister1.png");
	s1.position = cocos.Point.create(winSize.width / 2, winSize.height / 2);

	var rotateBy = new cocos.RotateBy();
	rotateBy.initWithDuration(1.0, 90);

	var repeat = new cocos.RepeatForever();
	repeat.initWithAction(rotateBy);

	s1.runAction(repeat);
	var scene = new cocos.Scene(); scene.init();
	scene.addChild(s1);

	// add the menu
	var menu = createMenu("Test Repeat");
	scene.addChild(menu, 1);

	return scene;
};

scenes['test_sequence'] = function () {
	var s1 = new cocos.Sprite.create("grossini_dance_05.png");
	s1.position = cocos.Point.create(winSize.width / 2 + 50, winSize.height / 2);

	var rotate1 = new cocos.RotateBy();
	rotate1.initWithDuration(1.0, 90);
	var moveBy = new cocos.MoveBy();
	moveBy.initWithDuration(2.0, cocos.Point.create(100, 100));
	var rotate2 = rotate1.reverse();

	var seq = cocos.Sequence.actions(rotate1, moveBy, rotate2);
	s1.runAction(seq);

	var scene = new cocos.Scene(); scene.init();
	scene.addChild(s1);

	// add the menu
	var menu = createMenu("Test Sequence");
	scene.addChild(menu, 1);

	return scene;
};

scenes['test_easein'] = function () {
	var s1 = new cocos.Sprite.create("grossinis_sister1.png");
	s1.position = cocos.Point.create(50, winSize.height * 3 / 4 );

	var s2 = new cocos.Sprite.create("grossini_dance_05.png");
	s2.position = cocos.Point.create(50, winSize.height * 2 / 4);

	var s3 = new cocos.Sprite.create("grossinis_sister2.png");
	s3.position = cocos.Point.create(50, winSize.height * 1 / 4);

	var moveBy1 = new cocos.MoveBy();
	var moveBy2 = new cocos.MoveBy();
	var moveBy3 = new cocos.MoveBy();

	moveBy1.initWithDuration(2.0, cocos.Point.create( winSize.width-100, 0));
	moveBy2.initWithDuration(2.0, cocos.Point.create( winSize.width-100, 0));
	moveBy3.initWithDuration(2.0, cocos.Point.create( winSize.width-100, 0));
	
	var easein = cocos.EaseIn.actionWithAction(moveBy1, 0.2);
	var seq1 = cocos.Sequence.actions(easein, easein.reverse );
	s1.runAction(easein.reverse);

	var seq2 = cocos.Sequence.actions( moveBy2. moveBy2.reverse );
	s2.runAction( seq2 );

	var easeout = cocos.EaseOut.actionWithAction(moveBy3, 0.2);
	var seq3 = cocos.Sequence.actions(easeout, easeout.reverse );
	s3.runAction( seq3 );

	var scene = new cocos.Scene(); scene.init();
	scene.addChild(s1);
	scene.addChild(s2);
	scene.addChild(s3);
	
	// add the menu
	var menu = createMenu("Test EaseIn / EaseOut");
	scene.addChild(menu, 1);
	
	return scene;
};

/**
 * from here on there's code that can be shared between different tests
 * basically is the hud and the scene handling
 */

// changes to the next scene
var nextScene = function () {
	var l = Object.keys(scenes).length;
	scenes.currentScene = (scenes.currentScene + 1) % l;
	if (scenes.currentScene === 0) {
		scenes.currentScene = 1;
	}
	playCurrentScene();
};

// changes to the previous scene
var prevScene = function  () {
	var l = Object.keys(scenes).length;
	scenes.currentScene -= 1;
	if (scenes.currentScene < 1) {
		scenes.currentScene = l - 1;
	}
	playCurrentScene();
};

var playCurrentScene = function () {
	var name = Object.keys(scenes)[scenes.currentScene];
	var scene = scenes[name]();
	// cocos.log("running scene: " + name + "(" + scene + ")");
	if (director.runningScene === null) {
		director.runWithScene(scene);
	} else {
		director.replaceScene(scene);
	}
};

// creates the hud
var createMenu = function (labelText) {
	var hudMenu = new cocos.Menu();
	hudMenu.init();

	var b1 = new cocos.Sprite(); b1.initWithFile("b1.png");
	var b2 = new cocos.Sprite(); b2.initWithFile("b2.png");
	item1 = new cocos.MenuItemSprite();
	item1.initFromNormalSprite(b1, b2);
	item1.action = function () {
		prevScene();
	};

	var r1 = new cocos.Sprite(); r1.initWithFile("r1.png");
	var r2 = new cocos.Sprite(); r2.initWithFile("r2.png");
	item2 = new cocos.MenuItemSprite();
	item2.initFromNormalSprite(r1, r2);
	item2.action = function () {
		// cocos.executeScript("JS/1to1/test_actions.js");
		playCurrentScene();
	};

	var f1 = new cocos.Sprite(); f1.initWithFile("f1.png");
	var f2 = new cocos.Sprite(); f2.initWithFile("f2.png");
	item3 = new cocos.MenuItemSprite();
	item3.initFromNormalSprite(f1, f2);
	item3.action = function () {
		nextScene();
	};

	var c1 = new cocos.Sprite(); c1.initWithFile("r1.png");
	var c2 = new cocos.Sprite(); c2.initWithFile("r2.png");
	item4 = new cocos.MenuItemSprite();
	item4.initFromNormalSprite(c1, c2);
	item4.action = function () {
		cocos.executeScript("JS/1to1/test_actions.js");
	};

	item1.position = cocos.Point.create(winSize.width / 2 - 100, 30);
	item2.position = cocos.Point.create(winSize.width / 2      , 30);
	item3.position = cocos.Point.create(winSize.width / 2 + 100, 30);
	item4.position = cocos.Point.create(30, winSize.height - 30);

	hudMenu.addChild(item1);
	hudMenu.addChild(item2);
	hudMenu.addChild(item3);
	hudMenu.addChild(item4);
	hudMenu.position = pointZero;

	if (labelText) {
		var label = new cocos.LabelTTF();
		// initWithString: text, size, alignment, font, fontSize
		label.initWithString(labelText, sizeZero, 0, "Arial", 18.0);
		label.position = cocos.Point.create(winSize.width / 2, winSize.height - 30);
		hudMenu.addChild(label);
	}

	// just to avoid GC
	hudMenu.items = [item1, item2, item3];
	return hudMenu;
};

playCurrentScene();
