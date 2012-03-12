try {
	var scene = new CCScene();

	var curTime = Date.now();
	for (var i=0; i < 10; i++)
	{
		var sprite = new CCSprite("mapletree.png");
		sprite.setPosition(30 + i*40, 70);
		if (i % 3 === 0) {
			sprite.setOpacity(128);
		}
		if (i % 2 === 0) {
			sprite.setColor(0, 255, 0);
		}
		scene.addChild(sprite);
	}
	CCDirector.runWithScene(scene);
	var endTime = Date.now();
	debug.log("js delta\t" + (endTime - curTime) / 1000.0);

	var sprite = new CCSprite("mapletree.png");
	sprite.setPosition(160, 320);
	sprite.registerAsTouchHandler();
	sprite.touchesBegan = function (points) {
		debug.log("began: " + points.length);
		debug.log("first point: " + points[0][0] + "," + points[0][1]);
	};
	sprite.touchesMoved = function (points) {
		debug.log("moved: " + points.length);
		debug.log("first point: " + points[0][0] + "," + points[0][1]);
	};
	sprite.touchesEnded = function (points) {
		debug.log("ended: " + points.length);
		debug.log("first point: " + points[0][0] + "," + points[0][1]);
	};
	scene.addChild(sprite);

	var label = new CCLabelTTF("Testing labels", "Chalkboard SE", 12.0);
	label.setPosition(160, 300);
	scene.addChild(label);

	label.setString("Really testing labels");
} catch (e) {
	debug.log("error: " + e);
}
