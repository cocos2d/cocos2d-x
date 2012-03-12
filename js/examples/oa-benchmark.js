/**
 * trying to use the same benchmark that the guys from OA used:
 * http://openaphid.github.com/blog/2012/02/20/javascript-and-cocos2d-a-sneak-peek/
 */

var scene = new CCScene();
var background = new CCSprite("background.png");
scene.addChild(background);

CCSpriteFrameCache.addSpriteFramesWithFile("tank.plist");

// wrapper around CCSprite
var Tank = function (frame) {
	this.sprite = new CCSprite(frame);
	this.sprite.setPosition(new CCPoint(Math.random()  * 320, Math.random() * 480));

	this.vx = Math.random() > 0.5 ? 0.1 : -0.1;
	this.vy = Math.random() > 0.5 ? 0.1 : -0.1;

	this.timerId = CCScheduler.schedule(this.onUpdate, 0, this);
};

/**
 * @param {number} delta time slice since last update, in milliseconds (1 second == 1000)
 */
Tank.prototype.onUpdate = function (delta) {
	var p = this.sprite.getPosition();
	p.x += delta * this.vx;
	p.y += delta * this.vy;

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

	//set the new position
	this.sprite.setPosition(p);
};

// do the fun
var totalTanks = 200;
var frames = ["tank1.png", "tank2.png", "tank3.png", "tank4.png", "tank5.png"];
// create animation
var animation = new CCAnimation(frames, 0.05);

for (var i=0; i < totalTanks; i++) {
	var tank = new Tank(frames[0]);
	tank.tankId = i;
	scene.addChild(tank.sprite);

	// second argument false by default
	var action = new CCAnimate(animation);
	tank.sprite.runAction(new CCRepeatForever(action));
}

CCDirector.runWithScene(scene);
