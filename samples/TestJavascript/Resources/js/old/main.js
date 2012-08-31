require("js/helper.js");

var randColorComp = function () {
	return Math.round(Math.random() * 255);
};

var director = cc.Director.getInstance();
var audioEngine = cc.AudioEngine.getInstance();
var _winSize = director.getWinSize();
var winSize = {width:_winSize[0], height:_winSize[1]};

log("size: " + winSize.width + "," + winSize.height);

var scene = cc.Scene.create();
var layer = cc.LayerGradient.create(cc.c4(0, 0, 0, 255), cc.c4(0, 128, 255, 255));
scene.addChild(layer, 0, 1337);

for (var i=0; i < 30; i++) {
	var sprite = cc.Sprite.create("Icon.png");
	var pos = cc.p(Math.random() * winSize.width, Math.random() * winSize.height);
	sprite.setPosition(pos);
	sprite.setColor(cc.c3(randColorComp(), randColorComp(), randColorComp()));
	layer.addChild(sprite);
}

var menu = cc.Menu.create();
var label = cc.LabelTTF.create("Testing Label TTF", "Arial", 20.0);
label.func = function () {
	log("menu action from label " + this);
}
var item = cc.MenuItemLabel.create(label, menu, label.func);
menu.addChild(item);
menu.setPosition(cc.p(winSize.width / 2, winSize.height / 2));

var touch = new cc.Touch();
var pt = touch.locationInView();
log("touch: " + touch.x + "," + touch.y);

layer.addChild(menu);

//audioEngine.setBackgroundMusicVolume(0.5);
//audioEngine.playBackgroundMusic("bgmusic.mp3", true);

var testLayer = scene.getChildByTag(1337);
log("layer == testLayer: " + (layer == testLayer));

director.runWithScene(scene);
