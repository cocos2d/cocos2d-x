var director = cc.Director.sharedDirector();
var scene = new cc.Scene();
scene.init();

// our test sprite
var sprite = new cc.Sprite();
sprite.initWithFile("Icon.png");
var pt = new cc.Point();
pt.x = 160;
pt.y = 240;
sprite.position = pt;

// will call "update" every frame if there's an update property
//sprite.scheduleUpdate();
sprite.speed = new cc.Point();
sprite.speed.x = Math.random() * 10 - 5;
sprite.speed.y = Math.random() * 10 - 5;

// the actual update function
sprite.update = function () {
	var curPos = this.position;
	curPos.x += this.speed.x;
	curPos.y += this.speed.y;
	this.position = curPos;
	if (curPos.x >= 320 || curPos.x <= 0) this.speed.x *= -1;
	if (curPos.y >= 480 || curPos.y <= 0) this.speed.y *= -1;
};

// adds the sprite to the scene
scene.addChild(sprite);

// add a menu
var item = new cc.MenuItemImage();//Sprite();
//var normal = new cc.Sprite(); normal.initWithFile("CloseNormal.png");
//var selected = new cc.Sprite(); selected.initWithFile("CloseSelected.png");
//item.initWithNormalSprite(normal, selected);
item.initFromNormalImage("CloseNormal.png", "CloseSelected.png");
item.action = function () {
	cc.log("action");
};
cc.log("normal image: " + item.normalImage);
pt.x = 20;
pt.y = 20;
item.position = pt;
var menu = new cc.Menu();
menu.init();
menu.addChild(item);

pt.x = 0;
pt.y = 0;
menu.position = pt;
scene.addChild(menu, 1);

// let the games begin
director.runWithScene(scene);
