/**
 * trying to use the same benchmark that the guys from OA used:
 * http://openaphid.github.com/blog/2012/02/20/javascript-and-cocos2d-a-sneak-peek/
 */

// taken from goog.inherits
cocos.inherits = function(childCtor, parentCtor) {
	/** @constructor */
	function tempCtor() {};
	tempCtor.prototype = parentCtor.prototype;
	childCtor.superClass_ = parentCtor.prototype;
	childCtor.prototype = new tempCtor();
	childCtor.prototype.constructor = childCtor;
};

var scene = new cocos.Scene();
scene.init();
var background = new cocos.Sprite();
background.initWithFile("background.png");
scene.addChild(background);

var spriteFrameCache = cocos.SpriteFrameCache.sharedSpriteFrameCache();
spriteFrameCache.addSpriteFramesWithFile("tank.plist");

// wrapper around CCSprite
var Tank = function () {
	var sprite = new cocos.Sprite();
	sprite.initWithSpriteFrameName("tank1.png");

	var pos = new cocos.Point();
	pos.x = Math.random() * 320;
	pos.y = Math.random() * 480;
	sprite.position = pos;
	sprite.vx = Math.random() > 0.5 ? 100 : -100;
	sprite.vy = Math.random() > 0.5 ? 100 : -100;
	sprite.scheduleUpdate();
	sprite.update = function (delta) {
		var p = this.position;
		p.x += delta * this.vx;
		p.y += delta * this.vy;
		//set the new position
		this.position = p;

		//make sure tank is inside the screen
		if (p.x < 0) {
			p.x = 0;
			this.vx = -this.vx;
		}

		if (p.x > 320) {
			p.x = 320;
			this.vx = -this.vx;
		}

		if (p.y < 0) {
			p.y = 0;
			this.vy = -this.vy;
		}

		if (p.y > 480) {
			p.y = 480;
			this.vy = -this.vy;
		}
	};

	this.sprite = sprite;
};

// create animation
var frames = ["tank1.png", "tank2.png", "tank3.png", "tank4.png", "tank5.png"];
var animation = new cocos.Animation();
animation.init();
animation.delay = 0.1;
for (var i=0; i < frames.length; i++) {
	var frame = spriteFrameCache.spriteFrameByName(frames[i]);
	animation.addFrame(frame);
}

// do the fun
// global array to prevent GC
var tanks = new Array(100);
for (var i=0; i < tanks.length; i++) {
	var tank = new Tank();
	tank.tankId = i;
	scene.addChild(tank.sprite);
	if (i == 0) {
		// this is not working correctly (only on ccnodes)
		tank.sprite.onEnter = function () {
			cocos.log("on enter");
		}
	}

	// second argument false by default
	tank.action = new cocos.Animate();
	tank.action.initWithAnimation(animation);
	tank.repeat = new cocos.RepeatForever();
	tank.repeat.initWithAction(tank.action);
	tank.sprite.runAction(tank.repeat);

	tanks[i] = tank;
}

var layer = new cocos.Layer();
layer.onEnter = function () {
	cocos.log("layer enter");
};
layer.isTouchEnabled = true;
layer.ccTouchBegan = function (touch) {
	var point = touch.locationInView();
	cocos.log("cc touch: " + point.x + "," + point.y);
};
layer.ccTouchesBegan = function (touches) {
	for (var i=0; i < touches.length; i++) {
		var point = touches[i].locationInView();
		cocos.log("cc touches: " + point.x + "," + point.y);
	}
};
scene.addChild(layer);

var director = cocos.Director.sharedDirector();
director.runWithScene(scene);
