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

//
// EaseIn / EaseOut
//
scenes['test_easein'] = function () {
	var s1 = new cc.Sprite.create("grossinis_sister1.png");
	s1.position = cc.Point.create(50, winSize.height * 3 / 4 );

	var s2 = new cc.Sprite.create("grossini_dance_05.png");
	s2.position = cc.Point.create(50, winSize.height * 2 / 4);

	var s3 = new cc.Sprite.create("grossinis_sister2.png");
	s3.position = cc.Point.create(50, winSize.height * 1 / 4);

	var moveBy1 = new cc.MoveBy();
	var moveBy2 = new cc.MoveBy();
	var moveBy3 = new cc.MoveBy();

	moveBy1.initWithDuration(2.0, cc.Point.create( winSize.width-100, 0));
	moveBy2.initWithDuration(2.0, cc.Point.create( winSize.width-100, 0));
	moveBy3.initWithDuration(2.0, cc.Point.create( winSize.width-100, 0));
	
	var easein = cc.EaseIn.actionWithAction(moveBy1, 0.2);
	var easein_back = cc.EaseIn.actionWithAction( moveBy1.reverse(), 1/0.2 );
	var seq1 = cc.Sequence.actions(easein, easein_back);
	s1.runAction(seq1);

	var seq2 = cc.Sequence.actions(moveBy2, moveBy2.reverse());
	s2.runAction(seq2);

	var easeout = cc.EaseOut.actionWithAction(moveBy3, 0.2);
	var seq3 = cc.Sequence.actions(easeout, easeout.reverse());
	s3.runAction(seq3);

	var scene = new cc.Scene(); scene.init();
	scene.addChild(s1);
	scene.addChild(s2);
	scene.addChild(s3);
	
	// add the menu
	var menu = createMenu("Test EaseIn / EaseOut");
	scene.addChild(menu, 1);
	
	return scene;
};

//
// EaseIn / EaseOut
//
scenes['test_easeinout'] = function () {

	var s1 = new cc.Sprite.create("grossinis_sister1.png");
	s1.position = cc.Point.create(50, winSize.height * 3 / 4 );
	
	var s2 = new cc.Sprite.create("grossini_dance_05.png");
	s2.position = cc.Point.create(50, winSize.height * 2 / 4);
	
	var s3 = new cc.Sprite.create("grossinis_sister2.png");
	s3.position = cc.Point.create(50, winSize.height * 1 / 4);

	
	var move1 = cc.MoveBy.actionWithDuration(3, cc.Point.create(winSize.width-130,0) );
	var move2 = cc.MoveBy.actionWithDuration(3, cc.Point.create(winSize.width-130,0) );
	var move3 = cc.MoveBy.actionWithDuration(3, cc.Point.create(winSize.width-130,0) );

	var move_ease_inout1 = cc.EaseInOut.actionWithAction( move1, 2 );
	var move_ease_inout_back1 = move_ease_inout1.reverse();
	
	var move_ease_inout2 = cc.EaseInOut.actionWithAction( move2, 3 );
	var move_ease_inout_back2 = move_ease_inout2.reverse();
	
	var move_ease_inout3 = cc.EaseInOut.actionWithAction( move3, 4 );
	var move_ease_inout_back3 = move_ease_inout3.reverse();
	
//	var delay = [CCDelayTime actionWithDuration:0.25f];
	
	var seq1 = cc.Sequence.actions( move_ease_inout1, move_ease_inout_back1 );
	var seq2 = cc.Sequence.actions( move_ease_inout2, move_ease_inout_back2 );
	var seq3 = cc.Sequence.actions( move_ease_inout3, move_ease_inout_back3 );
	
	s1.runAction( cc.RepeatForever.actionWithAction( seq1 ) );
	s2.runAction( cc.RepeatForever.actionWithAction( seq2 ) );
	s3.runAction( cc.RepeatForever.actionWithAction( seq3 ) );

	var scene = new cc.Scene(); scene.init();
	scene.addChild(s1);
	scene.addChild(s2);
	scene.addChild(s3);
	
	// add the menu
	var menu = createMenu("Test EaseInOut and reverse");
	scene.addChild(menu, 1);
	
	return scene;
};

//
// Ease BounceIn / Out
//
scenes['test_bouncein'] = function () {
	var s1 = new cc.Sprite.create("grossinis_sister1.png");
	s1.position = cc.Point.create(50, winSize.height * 3 / 4 );

	var s2 = new cc.Sprite.create("grossini_dance_05.png");
	s2.position = cc.Point.create(50, winSize.height * 2 / 4);

	var s3 = new cc.Sprite.create("grossinis_sister2.png");
	s3.position = cc.Point.create(50, winSize.height * 1 / 4);

	var move1 = cc.MoveBy.actionWithDuration(3, cc.Point.create(winSize.width-130,0) );
	var move2 = cc.MoveBy.actionWithDuration(3, cc.Point.create(winSize.width-130,0) );
	var move3 = cc.MoveBy.actionWithDuration(3, cc.Point.create(winSize.width-130,0) );

	var move1_back = move1.reverse();

	var move_ease_in = cc.EaseBounceIn.actionWithAction( move2 );
	var move_ease_in_back = move_ease_in.reverse();

	var move_ease_out = cc.EaseBounceOut.actionWithAction( move3 );
	var move_ease_out_back = move_ease_out.reverse();

	var seq1 = cc.Sequence.actions( move1, move1_back );
	var seq2 = cc.Sequence.actions( move_ease_in, move_ease_in_back );
	var seq3 = cc.Sequence.actions( move_ease_out, move_ease_out_back );

	s1.runAction( cc.RepeatForever.actionWithAction( seq1 ) );
	s2.runAction( cc.RepeatForever.actionWithAction( seq2 ) );
	s3.runAction( cc.RepeatForever.actionWithAction( seq3 ) );

	var scene = new cc.Scene(); scene.init();
	scene.addChild(s1);
	scene.addChild(s2);
	scene.addChild(s3);

	// add the menu
	var menu = createMenu("Test EaseBounceIn / Out and reverse");
	scene.addChild(menu, 1);

	return scene;
};

//
// Ease BounceInOut
//
scenes['test_bounceinout'] = function () {
	
	var s1 = new cc.Sprite.create("grossinis_sister1.png");
	s1.position = cc.Point.create(50, winSize.height * 3 / 4 );
	
	var s2 = new cc.Sprite.create("grossinis_sister2.png");
	s2.position = cc.Point.create(50, winSize.height * 1 / 4);
	
	
	var move1 = cc.MoveBy.actionWithDuration(3, cc.Point.create(winSize.width-130,0) );
	var move2 = cc.MoveBy.actionWithDuration(3, cc.Point.create(winSize.width-130,0) );
	
	var move1_back = move1.reverse();
	
	var move_ease = cc.EaseBounceInOut.actionWithAction( move2 );
	var move_ease_back = move_ease.reverse();
	
	var seq1 = cc.Sequence.actions( move1, move1_back );
	var seq2 = cc.Sequence.actions( move_ease, move_ease_back );
	
	
	s1.runAction( cc.RepeatForever.actionWithAction( seq1 ) );
	s2.runAction( cc.RepeatForever.actionWithAction( seq2 ) );
	
	var scene = new cc.Scene(); scene.init();
	scene.addChild(s1);
	scene.addChild(s2);
	
	// add the menu
	var menu = createMenu("Test EaseBounceInOut + reverse");
	scene.addChild(menu, 1);
	
	return scene;
};

//
// EaseBackIn / Out
//
scenes['test_backin_out'] = function () {
	
	var s1 = new cc.Sprite.create("grossinis_sister1.png");
	s1.position = cc.Point.create(50, winSize.height * 3 / 4 );
	
	var s2 = new cc.Sprite.create("grossini_dance_05.png");
	s2.position = cc.Point.create(50, winSize.height * 2 / 4);
	
	var s3 = new cc.Sprite.create("grossinis_sister2.png");
	s3.position = cc.Point.create(50, winSize.height * 1 / 4);
	
	
	var move1 = cc.MoveBy.actionWithDuration(3, cc.Point.create(winSize.width-130,0) );
	var move2 = cc.MoveBy.actionWithDuration(3, cc.Point.create(winSize.width-130,0) );
	var move3 = cc.MoveBy.actionWithDuration(3, cc.Point.create(winSize.width-130,0) );
	
	var move1_back = move1.reverse();
	
	
	var move_ease_in = cc.EaseBackIn.actionWithAction( move2 );
	var move_ease_in_back = move_ease_in.reverse();
	
	var move_ease_out = cc.EaseBackOut.actionWithAction( move3 );
	var move_ease_out_back = move_ease_out.reverse();
	
	var seq1 = cc.Sequence.actions( move1, move1_back );
	var seq2 = cc.Sequence.actions( move_ease_in, move_ease_in_back );
	var seq3 = cc.Sequence.actions( move_ease_out, move_ease_out_back );
	
	s1.runAction( cc.RepeatForever.actionWithAction( seq1 ) );
	s2.runAction( cc.RepeatForever.actionWithAction( seq2 ) );
	s3.runAction( cc.RepeatForever.actionWithAction( seq3 ) );
	
	var scene = new cc.Scene(); scene.init();
	scene.addChild(s1);
	scene.addChild(s2);
	scene.addChild(s3);
	
	// add the menu
	var menu = createMenu("Test EaseBackIn / Out and reverse");
	scene.addChild(menu, 1);
	
	return scene;
};

//
// EaseBackInOut
//
scenes['test_backinout'] = function () {
	
	var s1 = new cc.Sprite.create("grossinis_sister1.png");
	s1.position = cc.Point.create(50, winSize.height * 3 / 4 );
	
	var s2 = new cc.Sprite.create("grossinis_sister2.png");
	s2.position = cc.Point.create(50, winSize.height * 1 / 4);
	
	
	var move1 = cc.MoveBy.actionWithDuration(3, cc.Point.create(winSize.width-130,0) );
	var move2 = cc.MoveBy.actionWithDuration(3, cc.Point.create(winSize.width-130,0) );
	
	var move1_back = move1.reverse();
	
	var move_ease = cc.EaseBackInOut.actionWithAction( move2 );
	var move_ease_back = move_ease.reverse();
	
	var seq1 = cc.Sequence.actions( move1, move1_back );
	var seq2 = cc.Sequence.actions( move_ease, move_ease_back );
	
	
	s1.runAction( cc.RepeatForever.actionWithAction( seq1 ) );
	s2.runAction( cc.RepeatForever.actionWithAction( seq2 ) );
	
	var scene = new cc.Scene(); scene.init();
	scene.addChild(s1);
	scene.addChild(s2);
	
	// add the menu
	var menu = createMenu("Test EaseBackInOut + reverse");
	scene.addChild(menu, 1);
	
	return scene;
};

//
// EaseBounceIn / Out
//
scenes['test_sinein_out'] = function () {
	
	var s1 = new cc.Sprite.create("grossinis_sister1.png");
	s1.position = cc.Point.create(50, winSize.height * 3 / 4 );
	
	var s2 = new cc.Sprite.create("grossini_dance_05.png");
	s2.position = cc.Point.create(50, winSize.height * 2 / 4);
	
	var s3 = new cc.Sprite.create("grossinis_sister2.png");
	s3.position = cc.Point.create(50, winSize.height * 1 / 4);
	
	
	var move1 = cc.MoveBy.actionWithDuration(3, cc.Point.create(winSize.width-130,0) );
	var move2 = cc.MoveBy.actionWithDuration(3, cc.Point.create(winSize.width-130,0) );
	var move3 = cc.MoveBy.actionWithDuration(3, cc.Point.create(winSize.width-130,0) );
	
	var move1_back = move1.reverse();
	
	
	var move_ease_in = cc.EaseSineIn.actionWithAction( move2 );
	var move_ease_in_back = move_ease_in.reverse();
	
	var move_ease_out = cc.EaseSineOut.actionWithAction( move3 );
	var move_ease_out_back = move_ease_out.reverse();
	
	var seq1 = cc.Sequence.actions( move1, move1_back );
	var seq2 = cc.Sequence.actions( move_ease_in, move_ease_in_back );
	var seq3 = cc.Sequence.actions( move_ease_out, move_ease_out_back );
	
	s1.runAction( cc.RepeatForever.actionWithAction( seq1 ) );
	s2.runAction( cc.RepeatForever.actionWithAction( seq2 ) );
	s3.runAction( cc.RepeatForever.actionWithAction( seq3 ) );
	
	var scene = new cc.Scene(); scene.init();
	scene.addChild(s1);
	scene.addChild(s2);
	scene.addChild(s3);
	
	// add the menu
	var menu = createMenu("Test EaseSineIn / Out and reverse");
	scene.addChild(menu, 1);
	
	return scene;
};

//
// EaseSineInOut
//
scenes['test_sineinout'] = function () {
	
	var s1 = new cc.Sprite.create("grossinis_sister1.png");
	s1.position = cc.Point.create(50, winSize.height * 3 / 4 );
	
	var s2 = new cc.Sprite.create("grossinis_sister2.png");
	s2.position = cc.Point.create(50, winSize.height * 1 / 4);
	
	
	var move1 = cc.MoveBy.actionWithDuration(3, cc.Point.create(winSize.width-130,0) );
	var move2 = cc.MoveBy.actionWithDuration(3, cc.Point.create(winSize.width-130,0) );
	
	var move1_back = move1.reverse();
	
	var move_ease = cc.EaseSineInOut.actionWithAction( move2 );
	var move_ease_back = move_ease.reverse();
	
	var seq1 = cc.Sequence.actions( move1, move1_back );
	var seq2 = cc.Sequence.actions( move_ease, move_ease_back );
	
	
	s1.runAction( cc.RepeatForever.actionWithAction( seq1 ) );
	s2.runAction( cc.RepeatForever.actionWithAction( seq2 ) );
	
	var scene = new cc.Scene(); scene.init();
	scene.addChild(s1);
	scene.addChild(s2);
	
	// add the menu
	var menu = createMenu("Test EaseSineInOut + reverse");
	scene.addChild(menu, 1);
	
	return scene;
};

//
// EaseElasticIn / Out
//
scenes['test_elasticin_out'] = function () {
	
	var s1 = new cc.Sprite.create("grossinis_sister1.png");
	s1.position = cc.Point.create(50, winSize.height * 3 / 4 );
	
	var s2 = new cc.Sprite.create("grossini_dance_05.png");
	s2.position = cc.Point.create(50, winSize.height * 2 / 4);
	
	var s3 = new cc.Sprite.create("grossinis_sister2.png");
	s3.position = cc.Point.create(50, winSize.height * 1 / 4);
	
	
	var move1 = cc.MoveBy.actionWithDuration(3, cc.Point.create(winSize.width-130,0) );
	var move2 = cc.MoveBy.actionWithDuration(3, cc.Point.create(winSize.width-130,0) );
	var move3 = cc.MoveBy.actionWithDuration(3, cc.Point.create(winSize.width-130,0) );
	
	var move1_back = move1.reverse();
	
	var move_ease_in = cc.EaseElasticIn.actionWithAction( move2 );
	var move_ease_in_back = move_ease_in.reverse();
	
	var move_ease_out = cc.EaseElasticOut.actionWithAction( move3 );
	var move_ease_out_back = move_ease_out.reverse();
	
	var seq1 = cc.Sequence.actions( move1, move1_back );
	var seq2 = cc.Sequence.actions( move_ease_in, move_ease_in_back );
	var seq3 = cc.Sequence.actions( move_ease_out, move_ease_out_back );
	
	s1.runAction( cc.RepeatForever.actionWithAction( seq1 ) );
	s2.runAction( cc.RepeatForever.actionWithAction( seq2 ) );
	s3.runAction( cc.RepeatForever.actionWithAction( seq3 ) );
	
	var scene = new cc.Scene(); scene.init();
	scene.addChild(s1);
	scene.addChild(s2);
	scene.addChild(s3);
	
	// add the menu
	var menu = createMenu("Test EaseElasticIn / Out and reverse");
	scene.addChild(menu, 1);
	
	return scene;
};

//
// EaseElasticInOut
//
scenes['test_elasticinout'] = function () {
	
	var s1 = new cc.Sprite.create("grossinis_sister1.png");
	s1.position = cc.Point.create(50, winSize.height * 3 / 4 );
	
	var s2 = new cc.Sprite.create("grossinis_sister2.png");
	s2.position = cc.Point.create(50, winSize.height * 1 / 4);
	
	
	var move1 = cc.MoveBy.actionWithDuration(3, cc.Point.create(winSize.width-130,0) );
	var move2 = cc.MoveBy.actionWithDuration(3, cc.Point.create(winSize.width-130,0) );
	
	var move1_back = move1.reverse();
	
	var move_ease = cc.EaseElasticInOut.actionWithAction( move2 );
	var move_ease_back = move_ease.reverse();
	
	var seq1 = cc.Sequence.actions( move1, move1_back );
	var seq2 = cc.Sequence.actions( move_ease, move_ease_back );
	
	
	s1.runAction( cc.RepeatForever.actionWithAction( seq1 ) );
	s2.runAction( cc.RepeatForever.actionWithAction( seq2 ) );
	
	var scene = new cc.Scene(); scene.init();
	scene.addChild(s1);
	scene.addChild(s2);
	
	// add the menu
	var menu = createMenu("Test EaseElasticInOut + reverse");
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
		cc.executeScript("JS/1to1/test_ease_actions.js");
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
