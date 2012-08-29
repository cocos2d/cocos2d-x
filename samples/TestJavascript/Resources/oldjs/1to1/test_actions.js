/*
 * showcasing actions
 */

/**
 * simple wrappers
 */
cc.Point.create = function (x, y) {
	var pt = new cc.Point();
	pt.x = x;
	pt.y = y;
	return pt;
};

cc.Size.create = function (w, h) {
	var sz = new cc.Size();
	sz.width = w;
	sz.height = h;
	return sz;
};

cc.Sprite.create = function (file) {
	var s = new cc.Sprite();
	s.initWithFile(file);
	return s;
};

var pointZero = cc.Point.create(0, 0);
var sizeZero = cc.Size.create(0, 0);

var director = cc.Director.sharedDirector();
var winSize = director.winSize;

var scenes = {};
scenes.currentScene = 1;

/**
 * tests the most basic function: moveTo and moveBy
 */
scenes['test_move'] = function () {
	var s1 = cc.Sprite.create("grossini_dance_05.png");
	s1.position = cc.Point.create(winSize.width / 2 + 50, winSize.height / 2);
	var s2 = cc.Sprite.create("grossinis_sister1.png");
	s2.position = cc.Point.create(winSize.width / 2 - 50, winSize.height / 2);

	var moveTo = new cc.MoveTo();
	moveTo.initWithDuration(2.0, cc.Point.create(winSize.width, winSize.height / 2));
	var moveBy = new cc.MoveBy();
	moveBy.initWithDuration(2.0, cc.Point.create(100, 100));

	s1.runAction(moveTo);
	s2.runAction(moveBy);

	var scene = new cc.Scene(); scene.init();
	scene.addChild(s1);
	scene.addChild(s2);

	// add the menu
	var menu = createMenu("Test Move");
	scene.addChild(menu, 1);

	return scene;
};

scenes['test_rotate'] = function () {
	var s1 = cc.Sprite.create("grossini_dance_05.png");
	s1.position = cc.Point.create(winSize.width / 2 + 50, winSize.height / 2);
	var s2 = cc.Sprite.create("grossinis_sister1.png");
	s2.rotation = 90;
	s2.position = cc.Point.create(winSize.width / 2 - 100, winSize.height / 2);

	var rotateTo = new cc.RotateTo();
	rotateTo.initWithDuration(1.0, 180.0);
	var rotateBy = new cc.RotateBy();
	rotateBy.initWithDuration(2.0, 90);

	s1.runAction(rotateTo);
	s2.runAction(rotateBy);

	var scene = new cc.Scene(); scene.init();
	scene.addChild(s1);
	scene.addChild(s2);

	// add the menu
	var menu = createMenu("Test Rotate");
	scene.addChild(menu, 1);

	return scene;
};

scenes['test_animation'] = function () {
	var spriteFrameCache = cc.SpriteFrameCache.sharedSpriteFrameCache();
	spriteFrameCache.addSpriteFramesWithFile("tank.plist");

	// create a new sprite with a sprite frame
	var sprite = new cc.Sprite();
	sprite.initWithSpriteFrameName("tank1.png");
	sprite.position = cc.Point.create(winSize.width / 2, winSize.height / 2);

	// create animation
	var frames = ["tank1.png", "tank2.png", "tank3.png", "tank4.png", "tank5.png"];
	var animation = new cc.Animation();
	animation.init();
	// set the delay
	animation.delayPerUnit = 0.1;
	// add the frames
	for (var i=0; i < frames.length; i++) {
		var frame = spriteFrameCache.spriteFrameByName(frames[i]);
		animation.addSpriteFrame(frame);
	}
	// action stored in the sprite to avoid GC
	sprite.anim = new cc.Animate();
	sprite.anim.initWithAnimation(animation);
	sprite.runAction(sprite.anim);

	var scene = new cc.Scene(); scene.init();
	scene.addChild(sprite);

	// add the menu
	var menu = createMenu("Test Animation");
	scene.addChild(menu, 1);

	return scene;
};

scenes['test_repeat'] = function () {
	var s1 = cc.Sprite.create("grossinis_sister1.png");
	s1.position = cc.Point.create(winSize.width / 2, winSize.height / 2);

	var rotateBy = new cc.RotateBy();
	rotateBy.initWithDuration(1.0, 90);

	var repeat = new cc.RepeatForever();
	repeat.initWithAction(rotateBy);

	s1.runAction(repeat);
	var scene = new cc.Scene(); scene.init();
	scene.addChild(s1);

	// add the menu
	var menu = createMenu("Test Repeat");
	scene.addChild(menu, 1);

	return scene;
};

scenes['test_sequence'] = function () {
	var s1 = cc.Sprite.create("grossini_dance_05.png");
	s1.position = cc.Point.create(winSize.width / 2 + 50, winSize.height / 2);

	var rotate1 = new cc.RotateBy();
	rotate1.initWithDuration(1.0, 90);
	var moveBy = new cc.MoveBy();
	moveBy.initWithDuration(2.0, cc.Point.create(100, 100));
	var rotate2 = rotate1.reverse();
	var delay = cc.DelayTime.actionWithDuration(1.5);

	var seq = cc.Sequence.actions(rotate1, moveBy, delay, rotate2);
	s1.runAction(seq);

	var scene = new cc.Scene(); scene.init();
	scene.addChild(s1);

	// add the menu
	var menu = createMenu("Test Sequence");
	scene.addChild(menu, 1);

	return scene;
};

scenes['test_wave3d'] = function () {
	var node = new cc.Node();
	var s1 = cc.Sprite.create("grossini_dance_05.png");
	s1.position = cc.Point.create(winSize.width / 2 + 50, winSize.height / 2);

	var rotate1 = new cc.RotateBy();
	rotate1.initWithDuration(1.0, 90);
	var moveBy = new cc.MoveBy();
	moveBy.initWithDuration(2.0, cc.Point.create(100, 100));
	var rotate2 = rotate1.reverse();
	var delay = cc.DelayTime.actionWithDuration(1.5);
	
	var seq = cc.Sequence.actions(rotate1, moveBy, delay, rotate2);
	s1.runAction(seq);

	var scene = new cc.Scene(); scene.init();
	node.addChild(s1);

	// simple wave 3d
	var gridSize = new cc.GridSize;
	gridSize.x = 15;
	gridSize.y = 10;
	var wave = cc.Waves3D.actionWithWaves(5, 40, gridSize, 3);
	scene.runAction(wave);

	// add the menu
	var menu = createMenu("Test Sequence");
	scene.addChild(node);
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
	// cc.log("running scene: " + name + "(" + scene + ")");
	if (director.runningScene === null) {
		director.runWithScene(scene);
	} else {
		director.replaceScene(scene);
	}
};

// creates the hud
var createMenu = function (labelText) {
	var hudMenu = new cc.Menu();
	hudMenu.init();

	var b1 = new cc.Sprite(); b1.initWithFile("b1.png");
	var b2 = new cc.Sprite(); b2.initWithFile("b2.png");
	item1 = new cc.MenuItemSprite();
	item1.initWithNormalSprite(b1, b2);
	item1.action = function () {
		prevScene();
	};

	var r1 = new cc.Sprite(); r1.initWithFile("r1.png");
	var r2 = new cc.Sprite(); r2.initWithFile("r2.png");
	item2 = new cc.MenuItemSprite();
	item2.initWithNormalSprite(r1, r2);
	item2.action = function () {
		// cc.executeScript("JS/1to1/test_actions.js");
		playCurrentScene();
	};

	var f1 = new cc.Sprite(); f1.initWithFile("f1.png");
	var f2 = new cc.Sprite(); f2.initWithFile("f2.png");
	item3 = new cc.MenuItemSprite();
	item3.initWithNormalSprite(f1, f2);
	item3.action = function () {
		nextScene();
	};

	var c1 = new cc.Sprite(); c1.initWithFile("r1.png");
	var c2 = new cc.Sprite(); c2.initWithFile("r2.png");
	item4 = new cc.MenuItemSprite();
	item4.initWithNormalSprite(c1, c2);
	item4.action = function () {
		cc.executeScript("JS/1to1/test_actions.js");
	};

	item1.position = cc.Point.create(winSize.width / 2 - 100, 30);
	item2.position = cc.Point.create(winSize.width / 2      , 30);
	item3.position = cc.Point.create(winSize.width / 2 + 100, 30);
	item4.position = cc.Point.create(30, winSize.height - 30);

	hudMenu.addChild(item1);
	hudMenu.addChild(item2);
	hudMenu.addChild(item3);
	hudMenu.addChild(item4);
	hudMenu.position = pointZero;

	if (labelText) {
		var label = new cc.LabelTTF();
		// initWithString: text, size, alignment, font, fontSize
		label.initWithString(labelText, sizeZero, 0, "Arial", 18.0);
        var menuLabel = new cc.MenuItemLabel();
        menuLabel.initWithLabel(label);
		menuLabel.position = cc.Point.create(winSize.width / 2, winSize.height - 30);
		hudMenu.addChild(menuLabel);
	}

	// just to avoid GC
	hudMenu.items = [item1, item2, item3];
	return hudMenu;
};

playCurrentScene();
