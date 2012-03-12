require("JS/game.js");
require("JS/block.js");

var MainMenu = {};
MainMenu.start = function () {
	var menuScene = new cocos2d.Scene();

	// add particles
	var emitter = new cocos2d.ParticleSystem("sample_particles.plist");
	menuScene.addChild(emitter);

	// create the menu
	var menu = new cocos2d.Menu();

	var label1 = new cocos2d.LabelTTF("Play","Chalkboard SE", 18.0);
	var label2 = new cocos2d.LabelTTF("Options","Chalkboard SE", 18.0);

	var item1 = new cocos2d.MenuItemLabel(label1, function () {
		debug.log("game will start");
		Game.start();
	});
	var item2 = new cocos2d.MenuItemLabel(label2, function () {
		debug.log("options");
	});
	item1.setPosition(new cocos2d.Point(160, 300));
	item2.setPosition(new cocos2d.Point(160, 150));

	menu.addChildren(item1, item2);
	menu.setPosition(new cocos2d.Point(0, 0));
	menuScene.addChild(menu);

	// preload music
	// cocos2d.AudioManager.preloadBackgroundMusic("music.mp3", true);

	// run the menu scene
	cocos2d.Director.runWithScene(menuScene);
};
