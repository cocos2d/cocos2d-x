/*
 * showcasing layer and touch events
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
scenes['test_layer_1'] = function () {
	var layer = new cc.Layer(); layer.init();
	layer.isTouchEnabled = true;
	layer.ccTouchesBegan = function (touches) {
		for (var i in touches) {
			var pt = touches[i].locationInView();
			pt = director.convertToGL(pt);
			var s = new cc.Sprite.create("grossinis_sister1.png");
			s.position = pt;
			s.rotation = Math.random() * 360;
			this.addChild(s);
		}
	};

	var scene = new cc.Scene(); scene.init();
	scene.addChild(layer);

	// add the menu
	var menu = createMenu("Test Layer 1");
	scene.addChild(menu, 1);

	return scene;
};

scenes['test_layer_2'] = function () {
	var layer = new cc.Layer(); layer.init();
	layer.isTouchEnabled = true;
	layer.currentSprite = null;

	layer.ccTouchesBegan = function (touches) {
		for (var i in touches) {
			var pt = touches[i].locationInView();
			pt = director.convertToGL(pt);
			var s = new cc.Sprite.create("grossinis_sister1.png");
			s.position = pt;
			s.rotation = Math.random() * 360;
			this.addChild(s);
			// only the first
			if (this.currentSprite === null) {
				this.currentSprite = s;
			}
		}
	};

	layer.ccTouchesMoved = function (touches) {
		pt = touches[0].locationInView();
		pt = director.convertToGL(pt);
		if (this.currentSprite) {
			this.currentSprite.position = pt;
		}
	};

	layer.ccTouchesEnded = function (touches) {
		this.currentSprite = null;
	};

	var scene = new cc.Scene(); scene.init();
	scene.addChild(layer);

	// add the menu
	var menu = createMenu("Test Layer 2");
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
		cc.executeScript("JS/1to1/test_layer.js");
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
