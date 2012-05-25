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
 * Manual Particle
 */
scenes['test_manual'] = function () {
	
	var scene = new cocos.Scene(); scene.init();

	var p1 = new cocos.ParticleSystem();
	p1.initWithTotalParticles(250);
	p1.position = cocos.Point.create(winSize.width / 2, winSize.height / 2 );
	
	scene.addChild(p1);

	p1.texture = cocos.TextureCache.sharedTextureCache().addImage( "stars2.png" );
	
	p1.duration = 3;
    
    // gravity
	p1.gravity = cocos.Point.create(0, -5);
    
    // angle
	p1.angle = 90;
	p1.angleVar = 360;
    
    // speed of particles
	p1.speed = 160;
	p1.speedVar = 20;
    
    // radial
	p1.radialAccel = -120;
	p1.radialAccelVar = 0;
    
    // tagential
	p1.tangentialAccel = 30;
	p1.tangentialAccelVar = 0;
    
    // emitter position
//	p1.position = cocos.Point.create(0, 0);
	p1.posVar = cocos.Point.create(0, 0);
    
    // life of particles
	p1.life = 4;
	p1.lifeVar = 1;
    
    // spin of particles
	p1.startSpin = 0;
	p1.startSizeVar = 0;
	p1.endSpin = 0;
	p1.endSpinVar = 0;
    
    // color of particles
	p1.startColor = [0.5, 0.5, 0.5, 1.0];
	p1.startColorVar = [0.5, 0.5, 0.5, 1.0];
	p1.endColor = [0.1, 0.1, 0.1, 0.2];
	p1.endColorVar = [0.1, 0.1, 0.1, 0.2];
    
    // size, in pixels
	p1.startSize = 30;
	p1.startSizeVar = 0;
//	p1.endSize = kParticleStartSizeEqualToEndSize;
    
    // emits per second
	p1.emissionRate = 500;
    
    // additive
	p1.isBlendAdditive = true;
	
	
	// add the menu
	var menu = createMenu("Particle: Manual Particle");
	scene.addChild(menu, 1);
	
	return scene;
};

/**
 * test particle
 */
scenes['test_lava_flow'] = function () {

	var scene = new cocos.Scene(); scene.init();
	
	var p1 = cocos.ParticleSystem.particleWithFile("LavaFlow.plist");
	p1.position = cocos.Point.create(winSize.width / 2, winSize.height / 2 );
	scene.addChild(p1);

	// add the menu
	var menu = createMenu("Particle: Lave Flow");
	scene.addChild(menu, 1);

	return scene;
};


/**
 * test particle
 */
scenes['test_forest_fire'] = function () {
	
	var scene = new cocos.Scene(); scene.init();
	
	var p1 = cocos.ParticleSystem.particleWithFile("ForestFire.plist");
	p1.position = cocos.Point.create(winSize.width / 2, winSize.height / 2 );
	scene.addChild(p1);
	
	// add the menu
	var menu = createMenu("Particle: Forest Fire");
	scene.addChild(menu, 1);
	
	return scene;
};

/**
 * test particle
 */
scenes['test_boiling_foam'] = function () {
	
	var scene = new cocos.Scene(); scene.init();
	
	var p1 = cocos.ParticleSystem.particleWithFile("BoilingFoam.plist");
	p1.position = cocos.Point.create(winSize.width / 2, winSize.height / 2 );
	scene.addChild(p1);
	
	// add the menu
	var menu = createMenu("Particle: Boiling Foam");
	scene.addChild(menu, 1);
	
	return scene;
};


/**
 * test particle
 */
scenes['test_burst_pipe'] = function () {
	
	var scene = new cocos.Scene(); scene.init();
	
	var p1 = cocos.ParticleSystem.particleWithFile("BurstPipe.plist");
	p1.position = cocos.Point.create(winSize.width / 2, winSize.height / 2 );
	scene.addChild(p1);
	
	// add the menu
	var menu = createMenu("Particle: Burst Pipe");
	scene.addChild(menu, 1);
	
	return scene;
};

/**
 * test particle
 */
scenes['test_comet'] = function () {
	
	var scene = new cocos.Scene(); scene.init();
	
	var p1 = cocos.ParticleSystem.particleWithFile("Comet.plist");
	p1.position = cocos.Point.create(winSize.width / 2, winSize.height / 2 );
	scene.addChild(p1);
	
	// add the menu
	var menu = createMenu("Particle: Comet");
	scene.addChild(menu, 1);
	
	return scene;
};

/**
 * test particle
 */
scenes['test_debian'] = function () {
	
	var scene = new cocos.Scene(); scene.init();
	
	var p1 = cocos.ParticleSystem.particleWithFile("debian.plist");
	p1.position = cocos.Point.create(winSize.width / 2, winSize.height / 2 );
	scene.addChild(p1);
	
	// add the menu
	var menu = createMenu("Particle: Debian");
	scene.addChild(menu, 1);
	
	return scene;
};

/**
 * test particle
 */
scenes['test_exploding_ring'] = function () {
	
	var scene = new cocos.Scene(); scene.init();
	
	var p1 = cocos.ParticleSystem.particleWithFile("ExplodingRing.plist");
	p1.position = cocos.Point.create(winSize.width / 2, winSize.height / 2 );
	scene.addChild(p1);
	
	// add the menu
	var menu = createMenu("Particle: Exploding Ring");
	scene.addChild(menu, 1);
	
	return scene;
};

/**
 * test particle
 */
scenes['test_flower'] = function () {
	
	var scene = new cocos.Scene(); scene.init();
	
	var p1 = cocos.ParticleSystem.particleWithFile("Flower.plist");
	p1.position = cocos.Point.create(winSize.width / 2, winSize.height / 2 );
	scene.addChild(p1);
	
	// add the menu
	var menu = createMenu("Particle: Flower");
	scene.addChild(menu, 1);
	
	return scene;
};

/**
 * test particle
 */
scenes['test_galaxy'] = function () {
	
	var scene = new cocos.Scene(); scene.init();
	
	var p1 = cocos.ParticleSystem.particleWithFile("Galaxy.plist");
	p1.position = cocos.Point.create(winSize.width / 2, winSize.height / 2 );
	scene.addChild(p1);
	
	// add the menu
	var menu = createMenu("Particle: Galaxy");
	scene.addChild(menu, 1);
	
	return scene;
};

/**
 * test particle
 */
scenes['test_phoenix'] = function () {
	
	var scene = new cocos.Scene(); scene.init();
	
	var p1 = cocos.ParticleSystem.particleWithFile("Phoenix.plist");
	p1.position = cocos.Point.create(winSize.width / 2, winSize.height / 2 );
	scene.addChild(p1);
	
	// add the menu
	var menu = createMenu("Particle: Phoenix");
	scene.addChild(menu, 1);
	
	return scene;
};

/**
 * test particle
 */
scenes['test_small_sun'] = function () {
	
	var scene = new cocos.Scene(); scene.init();
	
	var p1 = cocos.ParticleSystem.particleWithFile("SmallSun.plist");
	p1.position = cocos.Point.create(winSize.width / 2, winSize.height / 2 );
	scene.addChild(p1);
	
	// add the menu
	var menu = createMenu("Particle: Small Sun");
	scene.addChild(menu, 1);
	
	return scene;
};

/**
 * test particle
 */
scenes['test_spinningpeas'] = function () {
	
	var scene = new cocos.Scene(); scene.init();
	
	var p1 = cocos.ParticleSystem.particleWithFile("SpinningPeas.plist");
	p1.position = cocos.Point.create(winSize.width / 2, winSize.height / 2 );
	scene.addChild(p1);
	
	// add the menu
	var menu = createMenu("Particle: Spinning Peas");
	scene.addChild(menu, 1);
	
	return scene;
};

/**
 * test particle
 */
scenes['test_spiral'] = function () {
	
	var scene = new cocos.Scene(); scene.init();
	
	var p1 = cocos.ParticleSystem.particleWithFile("Spiral.plist");
	p1.position = cocos.Point.create(winSize.width / 2, winSize.height / 2 );
	scene.addChild(p1);
	
	// add the menu
	var menu = createMenu("Particle: Spiral");
	scene.addChild(menu, 1);
	
	return scene;
};

/**
 * test particle
 */
scenes['test_sookypeas'] = function () {
	
	var scene = new cocos.Scene(); scene.init();
	
	var p1 = cocos.ParticleSystem.particleWithFile("SpookyPeas.plist");
	p1.position = cocos.Point.create(winSize.width / 2, winSize.height / 2 );
	scene.addChild(p1);
	
	// add the menu
	var menu = createMenu("Particle: Spooky Peas");
	scene.addChild(menu, 1);
	
	return scene;
};

/**
 * test particle
 */
scenes['test_upsidedown'] = function () {
	
	var scene = new cocos.Scene(); scene.init();
	
	var p1 = cocos.ParticleSystem.particleWithFile("Upsidedown.plist");
	p1.position = cocos.Point.create(winSize.width / 2, winSize.height / 2 );
	scene.addChild(p1);
	
	// add the menu
	var menu = createMenu("Particle: Upside Down test");
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
	item1.initWithNormalSprite(b1, b2);
	item1.action = function () {
		prevScene();
	};

	var r1 = new cocos.Sprite(); r1.initWithFile("r1.png");
	var r2 = new cocos.Sprite(); r2.initWithFile("r2.png");
	item2 = new cocos.MenuItemSprite();
	item2.initWithNormalSprite(r1, r2);
	item2.action = function () {
		// cocos.executeScript("JS/1to1/test_actions.js");
		playCurrentScene();
	};

	var f1 = new cocos.Sprite(); f1.initWithFile("f1.png");
	var f2 = new cocos.Sprite(); f2.initWithFile("f2.png");
	item3 = new cocos.MenuItemSprite();
	item3.initWithNormalSprite(f1, f2);
	item3.action = function () {
		nextScene();
	};

	var c1 = new cocos.Sprite(); c1.initWithFile("r1.png");
	var c2 = new cocos.Sprite(); c2.initWithFile("r2.png");
	item4 = new cocos.MenuItemSprite();
	item4.initWithNormalSprite(c1, c2);
	item4.action = function () {
		cocos.executeScript("JS/1to1/test_particles.js");
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
        var menuLabel = new cocos.MenuItemLabel();
        menuLabel.initWithLabel(label);
		menuLabel.position = cocos.Point.create(winSize.width / 2, winSize.height - 30);
		hudMenu.addChild(menuLabel);
	}

	// just to avoid GC
	hudMenu.items = [item1, item2, item3];
	return hudMenu;
};

playCurrentScene();
